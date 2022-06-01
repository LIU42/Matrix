#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

#include "config.h"

struct CharDataNode
{
    int x;
    int y;
    int color;
    char ch;
};

struct AddDataNode
{
    int len;
    char ch;
};

struct Window
{
    pthread_t counter;
    int status;
    int screenX;
    int screenY;
    int exitCode;
    int charCount;
};

extern struct Window window;

void initWindow();
void setWindow();
void unsetWindow();
void initData();
void addChar();
void moveChar();
void deleteChar();
void displayChar();
void exitInterval();
#endif