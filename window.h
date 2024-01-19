#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <list>

#include "stream.h"

using namespace std;

enum class window_status
{
    STATUS_RUNNING,
    STATUS_EXIT
};

class terminal_window
{
    private:
        static constexpr int SCREEN_ROWS_MAX = 1000;
        static constexpr int SCREEN_COLS_MAX = 1000;

    private:
        static constexpr int DELAY_USEC = 32000;
        static constexpr int KEY_ESC = 27;
        static constexpr int RANDOM_ADD = 5;
        static constexpr int RANDOM_MOD = 100;

    private:
        bool is_enables[SCREEN_ROWS_MAX];
        int screen_rows;
        int screen_cols;

    private:
        list<char_stream> stream_list;
        window_status status;

    private:
        void init_window();
        void init_ncurses();
        void init_color();
        void unset_ncurses();

    private:
        void add_streams();
        void move_streams();
        void remove_streams();
        
    public:
        terminal_window();
        ~terminal_window();

    public:
        bool is_running();
        void update();
        void events();
        void display();
        void delay();
};
#endif