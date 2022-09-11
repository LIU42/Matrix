#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "config.h"

struct char_data
{
    int x;
    int y;
    int color;
    char ch;
};

struct add_data
{
    int len;
    char ch;
};

struct window
{
    struct char_data char_data[CHAR_MAX_COUNT];
    struct add_data add_data[ADD_CHAR_COUNT];
    char char_list[CHAR_LIST_LEN];
    int status;
    int screen_rows;
    int screen_cols;
    int exit_code;
    int char_count;
};

void init_window();
void set_window();
void set_color();
void unset_window();
void init_data();
void add_char();
void move_char();
void delete_char();
void update();
void events();
void display();

extern struct window window;
#endif
