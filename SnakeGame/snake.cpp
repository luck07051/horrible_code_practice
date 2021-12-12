#include "snake.h"

#include <vector>
using std::vector;

#include <deque>
using std::deque;

#include <algorithm>
using std::find;

#include <random>


///////////////////////////

// for makefood
std::random_device rd;
std::default_random_engine gen = std::default_random_engine(rd());

////////////////////////
bool operator<(const vec& a, const vec& b)
{
    if (a.x == b.x)
        return a.y < b.y;
    else
        return a.x < b.x;
}

bool operator==(const vec& a, const vec& b)
{
    return (a.x == b.x && a.y == b.y);
}

//////////////////////////////

Snake::Snake(term x, term y)
{
    size = { .x = x, .y = y };

    body.push_back(vec{2, 4});
    body.push_back(vec{3, 4});

    head = vec{3, 4};
    tail = vec{2, 4};

    makefood();

    is_eat = false;
}

bool Snake::Move(const Action action)
{
    // where of next head
    vec next;

    // specify next head and check daed or not
    switch (action)
    {
        case right:
            next = vec{head.x +1, head.y};
            if (next.x == size.x +1)
                return false;
            break;

        case left:
            next = vec{head.x -1, head.y};
            if (next.x == 0)
                return false;
            break;

        case up:
            next = vec{head.x, head.y -1};
            if (next.y == 0)
                return false;
            break;

        case down:
            next = vec{head.x, head.y +1};
            if (next.y == size.y +1)
                return false;
            break;
    }
    if (find(body.begin(), body.end(), next) != body.end())
        return false;

    // after moving, check is_eat
    is_eat = next == food;

    // move head
    body.push_back(next);
    head = next;

    if (!is_eat)
    {
        // if no eat the food, let tail move
        body.pop_front();
        tail = body.front();
    }
    else
    {
        // if eat the food, increase lenght, keep tail not move and create the food
        makefood();
    }

    return true;
}

void Snake::makefood()
{
    std::uniform_int_distribution<term> x_dis(1, size.x);
    std::uniform_int_distribution<term> y_dis(1, size.y);

    vec ran;
    do
    {
        ran = vec{x_dis(gen), y_dis(gen)};
    } while (find(body.begin(), body.end(), ran) != body.end());

    food = ran;
}
