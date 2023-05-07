#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

typedef enum Status Status;
typedef enum Color Color;

typedef struct CharData CharData;
typedef struct AddData AddData;
typedef struct Matrix Matrix;

enum Constant
{
    DELAY_USEC = 35000,
    KEY_ESC = 27,
    RANDOM_ADD = 5,
    RANDOM_MOD = 100,
    STRING_MAX_LENGTH = 25,
    STRING_MIN_LENGTH = 5,
    CHAR_LIST_LENGTH = 5000,
    ADD_LIST_LENGTH = 200
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

struct CharData
{
    int x;
    int y;
    char character;
    Color color;
};

struct AddData
{
    int length;
    char character;
};

struct Matrix
{
    CharData charDataList[CHAR_LIST_LENGTH];
    AddData addDataList[ADD_LIST_LENGTH];
    Status status;
    int screenRows;
    int screenCols;
    int keyCode;
    int charCount;
};

void initWindow(Matrix*);
void setWindow(Matrix*);
void setColor(Matrix*);
void unsetWindow(Matrix*);
void initData(Matrix*);
bool isRunning(Matrix*);
void addChar(Matrix*);
void moveChar(Matrix*);
void deleteChar(Matrix*);
void update(Matrix*);
void events(Matrix*);
void display(Matrix*);

#endif