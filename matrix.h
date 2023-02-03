#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

enum Constant
{
    DELAY_USEC = 35000,
    KEY_ESC = 27,
    RANDOM_ADD = 5,
    RANDOM_BASE = 100,
    STRING_MAX_LEN = 25,
    STRING_MIN_LEN = 5,
    CHAR_DATA_LEN = 5000,
    ADD_DATA_LEN = 200
};

enum Status
{
    RUNNING = 0,
    EXIT = 1
};

enum Color
{
    WHITE = 1,
    GREEN = 2
};

typedef enum Status Status;
typedef enum Color Color;

struct CharData
{
    int x;
    int y;
    int color;
    char ch;
};

struct AddData
{
    int len;
    char ch;
};

typedef struct CharData CharData;
typedef struct AddData AddData;

struct Matrix
{
    CharData char_data[CHAR_DATA_LEN];
    AddData add_data[ADD_DATA_LEN];
    Status status;
    int screen_rows;
    int screen_cols;
    int key_code;
    int char_count;
};

typedef struct Matrix Matrix;

void init_window(Matrix*);
void set_window(Matrix*);
void set_color(Matrix*);
void unset_window(Matrix*);
void init_data(Matrix*);
bool is_running(Matrix*);
void add_char(Matrix*);
void move_char(Matrix*);
void delete_char(Matrix*);
void update(Matrix*);
void events(Matrix*);
void display(Matrix*);

#endif