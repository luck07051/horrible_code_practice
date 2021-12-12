#ifndef SNAKE_H_
#define SNAKE_H_

#include <deque>
using std::deque;

#include <set>
using std::set;


typedef unsigned int term;


enum Motion { nothing, quit, pause, reset };

struct vec
{
    term x, y;
};

bool operator<(const vec& a, const vec& b);
bool operator==(const vec& a, const vec& b);

class Snake
{
    private:
        vec size; // game size
        deque<vec> body; // store body coordinate
        vec head, tail,food;


    public:
        bool is_eat;
        enum Action { right, left, up, down };

        Snake(term x, term y); // argument for game size
        bool Move(const Action action); // return dead or not
        void makefood(); // let food is random number but without body

        vec get_head() const { return head; }
        vec get_tail() const { return tail; }
        vec get_food() const { return food; }
        vec get_size() const { return size; }

};

deque<vec>::iterator find(const deque<vec> de, const vec t);

#endif
