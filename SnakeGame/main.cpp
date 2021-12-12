#include "snake.h"

#include <ncurses.h>

#include <ctime>

#include <string>
using std::string;


void initial(Snake& snake);
void draw(const vec ve, const char thing[]);
Motion get_action(Snake::Action& action);
bool move(Snake& snake, Snake::Action action, unsigned int& score);
bool get_time(unsigned int& time);
string int_to_str(unsigned int i);


const char food[3] = "()";
const char body[3] = "[]";
const char head[3] = "@@";

int main()
{
    Snake snake(25, 20);
    clock_t fram = 0.2 * CLOCKS_PER_SEC;

    initscr();

    initial(snake);

    unsigned score = 0;
    unsigned show_time = 0;
    bool dead = false;

    Motion motion = Motion::nothing;
    Snake::Action action = Snake::Action::right;
    clock_t t = clock();

    while (motion != Motion::quit)
    {
        motion = get_action(action);

        if (!dead)
        {
            if (clock() - t >= fram )
            {
                t = clock();
                dead = !move(snake, action, score);
            }

            if (get_time(show_time))
            {
                move(snake.get_size().y +2, 8);
                addstr(int_to_str(show_time).c_str());
                refresh();
            }

        }
        else
        {
            draw( vec{3, 3}, "YOU DEAD!!" );
            refresh();
        }

        if (motion == Motion::reset)
        {
            snake = Snake(snake.get_size().x, snake.get_size().y);
            initial(snake);

            score = 0;
            show_time = 0;
            dead = false;
            t = clock();
            action = Snake::Action::right;
        }
    }

    endwin();

    return 0;

}
void initial(Snake& snake)
{
    noecho();
    timeout(0);
    curs_set(0);
    clear();

    // draw frame
    move(0, 1);
    hline('-', snake.get_size().x *2);
    move(0, 0);
    vline('|', snake.get_size().y +2);
    move(snake.get_size().y +1, 1);
    hline('-', snake.get_size().x *2);
    move(0, snake.get_size().x *2 +1);
    vline('|', snake.get_size().y +2);

    // draw information
    move(snake.get_size().y +2, 0);
    addstr("Time  : 0000");
    move(snake.get_size().y +3, 0);
    addstr("score : 0000");

    // draw description
    move(snake.get_size().y +2, 15);
    addstr("q for quit");
    move(snake.get_size().y +3, 15);
    addstr("r for reset");

    // draw snake
    draw(snake.get_tail(), body);
    draw(snake.get_head(), head);

    //draw food
    draw(snake.get_food(), food);

    refresh();
}

bool move(Snake& snake, Snake::Action action, unsigned int& score)
{
    vec _tail = snake.get_tail();

    // let head of last time be body of this time
    draw(snake.get_head(), body);


    bool life = snake.Move(action);


    // if least time no eat the food, or snake life let snake tail move
    if (!snake.is_eat && life)
    {
        draw(_tail, "  ");
    }

    // draw head
    draw(snake.get_head(), head);

    // if head cover the food, darw new food
    if (snake.is_eat)
    {
        draw(snake.get_food(), food);

        // update score information
        ++score;
        move(snake.get_size().y +3, 8);
        addstr(int_to_str(score).c_str());
    }

    refresh();
    return life;
}

void draw(const vec ve, const char thing[])
{
    move(ve.y, ve.x *2 -1);
    addstr(thing);
}

bool get_time(unsigned int& time)
{
    // return true, time has change
    static clock_t t = clock();

    if (clock() - t >= CLOCKS_PER_SEC)
    {
        t = clock();
        ++time;
        return true;
    }
    return false;
}
string int_to_str(unsigned int i)
{
    string str;
    str = std::to_string(i);

    // add to 4 chars
    for (int j = 4 - str.size(); j > 0; --j)
    {
        str = '0' + str;
    }
    return str;
}

Motion get_action(Snake::Action& action)
{
    switch(getch())
    {
        case 'q':
            return Motion::quit;
        case 'p':
            return Motion::pause;
        case 'r':
            return Motion::reset;

        case 'w':
            if (action != Snake::Action::down)
                action = Snake::Action::up;
            return Motion::nothing;
        case 'a':
            if (action != Snake::Action::right)
                action = Snake::Action::left;
            return Motion::nothing;
        case 's':
            if (action != Snake::Action::up)
                action = Snake::Action::down;
            return Motion::nothing;
        case 'd':
            if (action != Snake::Action::left)
                action = Snake::Action::right;
            return Motion::nothing;
        default:
            return Motion::nothing;
    }
}
