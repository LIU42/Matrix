#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "config.h"

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

struct Window
{
    struct CharData charData[CHAR_MAX_COUNT];
    struct AddData addData[ADD_CHAR_COUNT];
    char charList[CHAR_LIST_LEN];
    int status;
    int screenX;
    int screenY;
    int exitCode;
    int charCount;
};

void initWindow();
void setWindow();
void setColor();
void unsetWindow();
void initData();
void addChar();
void moveChar();
void deleteChar();
void update();
void events();
void display();

extern struct Window window;
#endif
