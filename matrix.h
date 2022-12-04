#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define DELAY_USEC 35000
#define KEY_ESC 27

#define RANDOM_ADD 5
#define RANDOM_BASE 100
#define STRING_MAX_LEN 25
#define STRING_MIN_LEN 5

#define CHAR_DATA_LEN 5000
#define ADD_DATA_LEN 200

enum status_enum
{
    RUNNING = 0,
    EXIT = 1
};

enum color_enum
{
    WHITE = 1,
    GREEN = 2
};

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

struct matrix
{
    struct char_data char_data[CHAR_DATA_LEN];
    struct add_data add_data[ADD_DATA_LEN];
    enum status_enum status;
    int screen_rows;
    int screen_cols;
    int key_code;
    int char_count;
};

void init_window();
void set_window();
void set_color();
void unset_window();
void init_data();
bool is_running();
void add_char();
void move_char();
void delete_char();
void update();
void events();
void display();

#endif
