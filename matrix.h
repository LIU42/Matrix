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

void Matrix_InitWindow(Matrix*);
void Matrix_SetWindow(Matrix*);
void Matrix_SetColor(Matrix*);
void Matrix_UnsetWindow(Matrix*);
void Matrix_InitData(Matrix*);
bool Matrix_IsRunning(Matrix*);
void Matrix_AddChar(Matrix*);
void Matrix_MoveChar(Matrix*);
void Matrix_DeleteChar(Matrix*);
void Matrix_Update(Matrix*);
void Matrix_Events(Matrix*);
void Matrix_Display(Matrix*);

#endif