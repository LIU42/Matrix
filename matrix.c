#include "matrix.h"

void initWindow()
{
    window.status = RUNNING;
    window.screenX = 0;
    window.screenY = 0;
    window.exitCode = 0;
    window.charCount = 0;
    strcpy(window.charList, CHAR_LIST);
}

void setWindow()
{
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void setColor()
{
    start_color();
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
}

void unsetWindow()
{
    nocbreak();
    keypad(stdscr, TRUE);
    curs_set(TRUE);
    echo();
    endwin();
}

void initData()
{
    for (int i = 0; i < CHAR_MAX_COUNT; i++)
    {
        window.charData[i].x = NONE;
        window.charData[i].y = NONE;
        window.charData[i].color = NONE;
        window.charData[i].ch = NONE_CHAR;
    }
    for (int i = 0; i < ADD_CHAR_COUNT; i++)
    {
        window.addData[i].len = 0;
        window.addData[i].ch = NONE_CHAR;
    }
    window.charCount = 0;
}

void addChar()
{
    for (int i = 0; i < window.screenX; i += 2)
    {
        int isNeedAdd = FALSE;

        for (int j = 0; j < window.charCount; j++)
        {
            if (window.charData[j].x == i && window.charData[j].y == 1) { isNeedAdd = TRUE; }
        }
        if (isNeedAdd && window.addData[i].len != 0)
        {
            window.charData[window.charCount].x = i;
            window.charData[window.charCount].y = 0;
            window.charData[window.charCount].color = GREEN;
            window.charData[window.charCount].ch = window.addData[i].ch;
            window.charCount += 1;
            window.addData[i].len -= 1;
        }
        else if (rand() % RANDOM_BASE <= RANDOM_ADD)
        {
            window.addData[i].len = rand() % (STRING_MAX_LEN - STRING_MIN_LEN) + STRING_MIN_LEN;
            window.addData[i].ch = window.charList[rand() % strlen(window.charList)];
            window.charData[window.charCount].x = i;
            window.charData[window.charCount].y = 0;
            window.charData[window.charCount].color = WHITE;
            window.charData[window.charCount].ch = window.addData[i].ch;
            window.charCount += 1;
        }
    }
}

void moveChar()
{
    for (int i = 0; i < window.charCount; i++)
    {
        window.charData[i].y += 1;
    }
    for (int i = window.charCount - 1; i >= 0; i--)
    {
        int isBottomOne = TRUE;

        for (int j = 0; j < window.charCount; j++)
        {
            if (window.charData[j].y == window.charData[i].y + 1 && window.charData[j].x == window.charData[i].x)
            {
                window.charData[i].ch = window.charData[j].ch;
                isBottomOne = FALSE;
            }
        }
        if (isBottomOne) { window.charData[i].ch = window.charList[rand() % strlen(window.charList)]; }
    }
}

void deleteChar()
{
    for (int i = 0; i < window.charCount; i++)
    {
        if (window.charData[i].y >= window.screenY)
        {
            for (int j = i; window.charData[j].x != -1; j++) { window.charData[j] = window.charData[j + 1]; }
            window.charCount -= 1;
        }
    }
}

void update()
{
    addChar();
    moveChar();
    deleteChar();
}

void events()
{
    window.exitCode = getch();

    if (window.exitCode == KEY_ESC)
    {
        window.status = EXIT;
    }
    if (window.screenX != COLS || window.screenY != LINES)
    {
        window.screenX = COLS;
        window.screenY = LINES;
        initData();
    }
}

void display()
{
    erase();

    for (int i = 0; i < window.charCount; i++)
    {
        if (window.charData[i].y < window.screenY)
        {
            attron(COLOR_PAIR(window.charData[i].color));
            mvaddch(window.charData[i].y, window.charData[i].x, window.charData[i].ch);
        }
    }
    refresh();
}
