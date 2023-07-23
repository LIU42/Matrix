#ifndef __STREAM_H__
#define __STREAM_H__

#include <ncurses.h>
#include <stdlib.h>
#include <list>

using namespace std;

class Stream
{
    private:
        static const int MAX_LENGTH = 25;
        static const int MIN_LENGTH = 5;

    public:
        static const int WHITE = 1;
        static const int GREEN = 2;

    private:
        int headX;
        int headY;

    private:
        list<char> charList;

    private:
        int getRandomLength();
        char getRandomChar();

    public:
        Stream(int);

    public:
        void move();
        void display();

    public:
        int getHeadX();
        int getHeadY();
        int getLength();
};
#endif