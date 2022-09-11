#include "matrix.h"

void init_window()
{
    window.status = RUNNING;
    window.screen_rows = 0;
    window.screen_cols = 0;
    window.exit_code = 0;
    window.char_count = 0;
    strcpy(window.char_list, CHAR_LIST);
}

void set_window()
{
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void set_color()
{
    start_color();
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
}

void unset_window()
{
    nocbreak();
    keypad(stdscr, TRUE);
    curs_set(TRUE);
    echo();
    endwin();
}

void init_data()
{
    for (int i = 0; i < CHAR_MAX_COUNT; i++)
    {
        window.char_data[i].x = NONE;
        window.char_data[i].y = NONE;
        window.char_data[i].color = NONE;
        window.char_data[i].ch = NONE_CHAR;
    }
    for (int i = 0; i < ADD_CHAR_COUNT; i++)
    {
        window.add_data[i].len = 0;
        window.add_data[i].ch = NONE_CHAR;
    }
    window.char_count = 0;
}

void add_char()
{
    for (int i = 0; i < window.screen_rows; i += 2)
    {
        int is_need_add = FALSE;

        for (int j = 0; j < window.char_count; j++)
        {
            if (window.char_data[j].x == i && window.char_data[j].y == 1) { is_need_add = TRUE; }
        }
        if (is_need_add && window.add_data[i].len != 0)
        {
            window.char_data[window.char_count].x = i;
            window.char_data[window.char_count].y = 0;
            window.char_data[window.char_count].color = GREEN;
            window.char_data[window.char_count].ch = window.add_data[i].ch;
            window.char_count += 1;
            window.add_data[i].len -= 1;
        }
        else if (rand() % RANDOM_BASE <= RANDOM_ADD)
        {
            window.add_data[i].len = rand() % (STRING_MAX_LEN - STRING_MIN_LEN) + STRING_MIN_LEN;
            window.add_data[i].ch = window.char_list[rand() % strlen(window.char_list)];
            window.char_data[window.char_count].x = i;
            window.char_data[window.char_count].y = 0;
            window.char_data[window.char_count].color = WHITE;
            window.char_data[window.char_count].ch = window.add_data[i].ch;
            window.char_count += 1;
        }
    }
}

void move_char()
{
    for (int i = 0; i < window.char_count; i++)
    {
        window.char_data[i].y += 1;
    }
    for (int i = window.char_count - 1; i >= 0; i--)
    {
        int is_bottom_one = TRUE;

        for (int j = 0; j < window.char_count; j++)
        {
            if (window.char_data[j].y == window.char_data[i].y + 1 && window.char_data[j].x == window.char_data[i].x)
            {
                window.char_data[i].ch = window.char_data[j].ch;
                is_bottom_one = FALSE;
            }
        }
        if (is_bottom_one) { window.char_data[i].ch = window.char_list[rand() % strlen(window.char_list)]; }
    }
}

void delete_char()
{
    for (int i = 0; i < window.char_count; i++)
    {
        if (window.char_data[i].y >= window.screen_cols)
        {
            for (int j = i; window.char_data[j].x != -1; j++) { window.char_data[j] = window.char_data[j + 1]; }
            window.char_count -= 1;
        }
    }
}

void update()
{
    move_char();
    add_char();
    delete_char();
}

void events()
{
    window.exit_code = getch();

    if (window.exit_code == KEY_ESC)
    {
        window.status = EXIT;
    }
    if (window.screen_rows != COLS || window.screen_cols != LINES)
    {
        window.screen_rows = COLS;
        window.screen_cols = LINES;
        init_data();
    }
}

void display()
{
    erase();

    for (int i = 0; i < window.char_count; i++)
    {
        if (window.char_data[i].y < window.screen_cols)
        {
            attron(COLOR_PAIR(window.char_data[i].color));
            mvaddch(window.char_data[i].y, window.char_data[i].x, window.char_data[i].ch);
        }
    }
    refresh();
}
