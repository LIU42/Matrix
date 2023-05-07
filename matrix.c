#include "matrix.h"

void initWindow(Matrix* pMatrix)
{
    pMatrix->status = RUNNING;
    pMatrix->screenRows = 0;
    pMatrix->screenCols = 0;
    pMatrix->keyCode = 0;
    pMatrix->charCount = 0;
}

void setWindow(Matrix* pMatrix)
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

void setColor(Matrix* pMatrix)
{
    start_color();
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
}

void unsetWindow(Matrix* pMatrix)
{
    nocbreak();
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void initData(Matrix* pMatrix)
{
    for (int i = 0; i < CHAR_LIST_LENGTH; i++)
    {
        pMatrix->charDataList[i].x = -1;
        pMatrix->charDataList[i].y = -1;
        pMatrix->charDataList[i].color = WHITE;
        pMatrix->charDataList[i].character = '\0';
    }
    for (int i = 0; i < ADD_LIST_LENGTH; i++)
    {
        pMatrix->addDataList[i].length = 0;
        pMatrix->addDataList[i].character = '\0';
    }
    pMatrix->charCount = 0;
}

bool isRunning(Matrix* pMatrix)
{
    return pMatrix->status != EXIT;
}

void addChar(Matrix* pMatrix)
{
    for (int i = 0; i < pMatrix->screenRows; i += 2)
    {
        bool isNeedAdd = false;

        for (int j = 0; j < pMatrix->charCount; j++)
        {
            if (pMatrix->charDataList[j].x == i && pMatrix->charDataList[j].y == 1) { isNeedAdd = true; }
        }
        if (isNeedAdd && pMatrix->addDataList[i].length != 0)
        {
            pMatrix->charDataList[pMatrix->charCount].x = i;
            pMatrix->charDataList[pMatrix->charCount].y = 0;
            pMatrix->charDataList[pMatrix->charCount].color = GREEN;
            pMatrix->charDataList[pMatrix->charCount].character = pMatrix->addDataList[i].character;
            pMatrix->charCount += 1;
            pMatrix->addDataList[i].length -= 1;
        }
        else if (rand() % RANDOM_MOD <= RANDOM_ADD)
        {
            pMatrix->addDataList[i].length = rand() % (STRING_MAX_LENGTH - STRING_MIN_LENGTH) + STRING_MIN_LENGTH;
            pMatrix->addDataList[i].character = rand() % ('Z' - 'A' + 1) + 'A';
            pMatrix->charDataList[pMatrix->charCount].x = i;
            pMatrix->charDataList[pMatrix->charCount].y = 0;
            pMatrix->charDataList[pMatrix->charCount].color = WHITE;
            pMatrix->charDataList[pMatrix->charCount].character = pMatrix->addDataList[i].character;
            pMatrix->charCount += 1;
        }
    }
}

void moveChar(Matrix* pMatrix)
{
    for (int i = 0; i < pMatrix->charCount; i++)
    {
        pMatrix->charDataList[i].y += 1;
    }
    for (int i = pMatrix->charCount - 1; i >= 0; i--)
    {
        bool isBottomOne = true;

        for (int j = 0; j < pMatrix->charCount; j++)
        {
            if (pMatrix->charDataList[j].y == pMatrix->charDataList[i].y + 1 && pMatrix->charDataList[j].x == pMatrix->charDataList[i].x)
            {
                pMatrix->charDataList[i].character = pMatrix->charDataList[j].character;
                isBottomOne = false;
            }
        }
        if (isBottomOne) { pMatrix->charDataList[i].character = rand() % ('Z' - 'A' + 1) + 'A'; }
    }
}

void deleteChar(Matrix* pMatrix)
{
    for (int i = 0; i < pMatrix->charCount; i++)
    {
        if (pMatrix->charDataList[i].y >= pMatrix->screenCols)
        {
            for (int j = i; pMatrix->charDataList[j].x != -1; j++)
            {
                pMatrix->charDataList[j] = pMatrix->charDataList[j + 1];
            }
            pMatrix->charCount -= 1;
        }
    }
}

void update(Matrix* pMatrix)
{
    moveChar(pMatrix);
    addChar(pMatrix);
    deleteChar(pMatrix);
}

void events(Matrix* pMatrix)
{
    pMatrix->keyCode = getch();

    if (pMatrix->keyCode == KEY_ESC)
    {
        pMatrix->status = EXIT;
    }
    if (pMatrix->screenRows != COLS || pMatrix->screenCols != LINES)
    {
        pMatrix->screenRows = COLS;
        pMatrix->screenCols = LINES;
        initData(pMatrix);
    }
}

void display(Matrix* pMatrix)
{
    erase();

    for (int i = 0; i < pMatrix->charCount; i++)
    {
        if (pMatrix->charDataList[i].y < pMatrix->screenCols)
        {
            attron(COLOR_PAIR(pMatrix->charDataList[i].color));
            mvaddch(pMatrix->charDataList[i].y, pMatrix->charDataList[i].x, pMatrix->charDataList[i].character);
        }
    }
    refresh();
}
