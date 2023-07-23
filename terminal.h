#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <list>

#include "stream.h"

using namespace std;

enum Status { RUNNING, EXIT };

class Terminal
{
    private:
        static const int SCREEN_ROWS_MAX = 1000;
        static const int SCREEN_COLS_MAX = 1000;

    private:
        static const int DELAY_USEC = 35000;
        static const int KEY_ESC = 27;
        static const int RANDOM_ADD = 5;
        static const int RANDOM_MOD = 100;

    private:
        bool isEnableList[SCREEN_ROWS_MAX];
        int screenRows;
        int screenCols;

    private:
        list<Stream> streamList;
        Status status;

    private:
        void initTerminal();
        void setCurses();
        void setColor();
        void unsetCurses();

    private:
        void addNewStreams();
        void moveStreams();
        void deleteStreams();
        
    public:
        Terminal();
        ~Terminal();

    public:
        bool isRunning();
        void update();
        void events();
        void display();
        void delay();
};
#endif