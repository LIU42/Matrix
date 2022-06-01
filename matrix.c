#include "matrix.h"

struct Window window;
struct CharDataNode charData[CHAR_MAX_COUNT];
struct AddDataNode addData[ADD_CHAR_COUNT];

const char charList[CHAR_LIST_LEN] = CHAR_LIST;

void* counterFunction()
{
    while (TRUE)
    {
        window.status = MOVE;
        usleep(INTERVAL);
    }
}

void initWindow()
{
    srand((unsigned int)time(NULL));
    pthread_create(&window.counter, NULL, counterFunction, NULL);
}

void setWindow()
{
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
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
        charData[i].x = NONE;
        charData[i].y = NONE;
        charData[i].color = NONE;
        charData[i].ch = NONE_CHAR;
    }
    for (int i = 0; i < ADD_CHAR_COUNT; i++)
    {
        addData[i].len = 0;
        addData[i].ch = NONE_CHAR;
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
            if (charData[j].x == i && charData[j].y == 1) { isNeedAdd = TRUE; }
        }
        if (isNeedAdd)
        {
            if (addData[i].len != 0)
            {
                charData[window.charCount].x = i;
                charData[window.charCount].y = 0;
                charData[window.charCount].color = GREEN;
                charData[window.charCount].ch = addData[i].ch;
                window.charCount += 1;
                addData[i].len -= 1;
            }
        }
        else
        {
            if (rand() % P_BASE <= P_ADD)
            {
                addData[i].len = rand() % (STRING_MAX_LEN - STRING_MIN_LEN) + STRING_MIN_LEN;
                addData[i].ch = charList[rand() % CHAR_LIST_LEN];
                charData[window.charCount].x = i;
                charData[window.charCount].y = 0;
                charData[window.charCount].color = WHITE;
                charData[window.charCount].ch = addData[i].ch;
                window.charCount += 1;
            }
        }
    }
}

void moveChar()
{
    for (int i = 0; i < window.charCount; i++) { charData[i].y += 1; }
    for (int i = window.charCount - 1; i >= 0; i--)
    {
        int isBottomOne = TRUE;
        for (int j = 0; j < window.charCount; j++)
        {
            if (charData[j].y == charData[i].y + 1 && charData[j].x == charData[i].x)
            {
                charData[i].ch = charData[j].ch;
                isBottomOne = FALSE;
            }
        }
        if (isBottomOne) { charData[i].ch = charList[rand() % CHAR_LIST_LEN]; }
    }
}

void deleteChar()
{
    for (int i = 0; i < window.charCount; i++)
    {
        if (charData[i].y >= window.screenY)
        {
            for (int j = i; charData[j].x != -1; j++) { charData[j] = charData[j + 1]; }
            window.charCount -= 1;
        }
    }
}

void displayChar()
{
    erase();
    for (int i = 0; i < window.charCount; i++)
    {
        if (charData[i].y < window.screenY)
        {
            attron(COLOR_PAIR(charData[i].color));
            mvaddch(charData[i].y, charData[i].x, charData[i].ch);
        }
    }
    refresh();
}

void exitInterval()
{
    window.exitCode = getch();
    if (window.exitCode == KEY_ESC) { window.status = EXIT; }
}
