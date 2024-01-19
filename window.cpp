#include "window.h"

terminal_window::terminal_window()
{
    srand((unsigned)time(NULL));
    init_window();
    init_ncurses();
    init_color();
}

terminal_window::~terminal_window()
{
    unset_ncurses();
}

void terminal_window::init_window()
{
    status = window_status::STATUS_RUNNING;
    screen_rows = 0;
    screen_cols = 0;
}

void terminal_window::init_ncurses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

void terminal_window::init_color()
{
    start_color();
    init_pair(char_stream::WHITE_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(char_stream::GREEN_COLOR, COLOR_GREEN, COLOR_BLACK);
}

void terminal_window::unset_ncurses()
{
    nocbreak();
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void terminal_window::add_streams()
{
    for (int x = 1; x < screen_rows; x += 2)
    {
        is_enables[x] = true;
    }
    for (char_stream& stream : stream_list)
    {
        if (stream.get_head_y() <= stream.get_length())
        {
            is_enables[stream.get_head_x()] = false;
        }
    }
    for (int x = 1; x < screen_rows; x += 2)
    {
        if (is_enables[x] && rand() % RANDOM_MOD <= RANDOM_ADD)
        {
            stream_list.push_back(char_stream(x));
        }
    }
}

void terminal_window::move_streams()
{
    for (char_stream& stream : stream_list)
    {
        stream.move();
    }
}

void terminal_window::remove_streams()
{
    for (auto stream_iter = stream_list.begin(); stream_iter != stream_list.end();)
    {
        if (stream_iter->get_head_y() > screen_cols + stream_iter->get_length())
        {
            stream_iter = stream_list.erase(stream_iter);
            continue;
        }
        ++stream_iter;
    }
}

bool terminal_window::is_running()
{
    return status == window_status::STATUS_RUNNING;
}

void terminal_window::update()
{
    move_streams();
    add_streams();
    remove_streams();
}

void terminal_window::events()
{
    int keyCode = getch();

    if (keyCode == KEY_ESC)
    {
        status = window_status::STATUS_EXIT;
    }
    if (screen_rows != COLS || screen_cols != LINES)
    {
        screen_rows = min(SCREEN_ROWS_MAX, COLS);
        screen_cols = min(SCREEN_COLS_MAX, LINES);
        stream_list.clear();
    }
}

void terminal_window::display()
{
    clear();

    for (char_stream& stream : stream_list)
    {
        stream.display();
    }
    refresh();
}

void terminal_window::delay()
{
    usleep(DELAY_USEC);
}
