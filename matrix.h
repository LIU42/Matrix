#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

#include "config.h"

struct Point
{
    int x;
    int y;
    int color;
    char ch;
};

struct String
{
    int len;
    char ch;
};

struct Window
{
    pthread_t counter;
    int status;
    int screen_x;
    int screen_y;
    int exit_code;
    int char_count;
};

extern struct Window window;

void init_window();
void set_window();
void unset_window();
void init_data();
void add_char();
void move_char();
void delete_char();
void display_char();
#endif