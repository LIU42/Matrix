#include "terminal.h"

Terminal::Terminal()
{
    srand((unsigned)time(NULL));
    initTerminal();
    setCurses();
    setColor();
}

Terminal::~Terminal()
{
    unsetCurses();
}

void Terminal::initTerminal()
{
    status = RUNNING;
    screenRows = 0;
    screenCols = 0;
}

void Terminal::setCurses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

void Terminal::setColor()
{
    start_color();
    init_pair(Stream::WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(Stream::GREEN, COLOR_GREEN, COLOR_BLACK);
}

void Terminal::unsetCurses()
{
    nocbreak();
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void Terminal::addNewStreams()
{
    for (int x = 1; x < screenRows; x += 2)
    {
        isEnableList[x] = true;
    }
    for (auto streamIter = streamList.begin(); streamIter != streamList.end(); ++streamIter)
    {
        if (streamIter->getHeadY() <= streamIter->getLength())
        {
            isEnableList[streamIter->getHeadX()] = false;
        }
    }
    for (int x = 1; x < screenRows; x += 2)
    {
        if (isEnableList[x] && rand() % RANDOM_MOD <= RANDOM_ADD)
        {
            streamList.push_back(Stream(x));
        }
    }
}

void Terminal::moveStreams()
{
    for (auto streamIter = streamList.begin(); streamIter != streamList.end(); ++streamIter)
    {
        streamIter->move();
    }
}

void Terminal::deleteStreams()
{
    for (auto streamIter = streamList.begin(); streamIter != streamList.end();)
    {
        if (streamIter->getHeadY() > screenCols + streamIter->getLength())
        {
            streamIter = streamList.erase(streamIter);
        }
        else { ++streamIter; }
    }
}

bool Terminal::isRunning()
{
    return status == RUNNING;
}

void Terminal::update()
{
    moveStreams();
    addNewStreams();
    deleteStreams();
}

void Terminal::events()
{
    int keyCode = getch();

    if (keyCode == KEY_ESC)
    {
        status = EXIT;
    }
    if (screenRows != COLS || screenCols != LINES)
    {
        screenRows = (COLS > SCREEN_ROWS_MAX) ? SCREEN_ROWS_MAX : COLS;
        screenCols = (LINES > SCREEN_COLS_MAX) ? SCREEN_COLS_MAX : LINES;
        streamList.clear();
    }
}

void Terminal::display()
{
    erase();

    for (auto streamIter = streamList.begin(); streamIter != streamList.end(); ++streamIter)
    {
        streamIter->display();
    }
    refresh();
}

void Terminal::delay()
{
    usleep(DELAY_USEC);
}
