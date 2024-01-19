#ifndef __STREAM_H__
#define __STREAM_H__

#include <ncurses.h>
#include <stdlib.h>
#include <list>

using namespace std;

class char_stream
{
    private:
        static constexpr int MAX_LENGTH = 25;
        static constexpr int MIN_LENGTH = 5;

    public:
        static constexpr int WHITE_COLOR = 1;
        static constexpr int GREEN_COLOR = 2;

    private:
        list<char> char_list;
        int head_x;
        int head_y;

    private:
        int get_random_length();
        char get_random_char();

    public:
        char_stream(int);

    public:
        void move();
        void display();

    public:
        int get_head_x();
        int get_head_y();
        int get_length();
};
#endif