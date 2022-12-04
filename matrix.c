#include "matrix.h"

struct matrix matrix;

void init_window()
{
    matrix.status = RUNNING;
    matrix.screen_rows = 0;
    matrix.screen_cols = 0;
    matrix.key_code = 0;
    matrix.char_count = 0;
}

void set_window()
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
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
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void init_data()
{
    for (int i = 0; i < CHAR_DATA_LEN; i++)
    {
        matrix.char_data[i].x = -1;
        matrix.char_data[i].y = -1;
        matrix.char_data[i].color = -1;
        matrix.char_data[i].ch = '\0';
    }
    for (int i = 0; i < ADD_DATA_LEN; i++)
    {
        matrix.add_data[i].len = 0;
        matrix.add_data[i].ch = '\0';
    }
    matrix.char_count = 0;
}

bool is_running()
{
    return matrix.status != EXIT;
}

void add_char()
{
    for (int i = 0; i < matrix.screen_rows; i += 2)
    {
        bool is_need_add = false;

        for (int j = 0; j < matrix.char_count; j++)
        {
            if (matrix.char_data[j].x == i && matrix.char_data[j].y == 1) { is_need_add = true; }
        }
        if (is_need_add && matrix.add_data[i].len != 0)
        {
            matrix.char_data[matrix.char_count].x = i;
            matrix.char_data[matrix.char_count].y = 0;
            matrix.char_data[matrix.char_count].color = GREEN;
            matrix.char_data[matrix.char_count].ch = matrix.add_data[i].ch;
            matrix.char_count += 1;
            matrix.add_data[i].len -= 1;
        }
        else if (rand() % RANDOM_BASE <= RANDOM_ADD)
        {
            matrix.add_data[i].len = rand() % (STRING_MAX_LEN - STRING_MIN_LEN) + STRING_MIN_LEN;
            matrix.add_data[i].ch = rand() % ('Z' - 'A' + 1) + 'A';
            matrix.char_data[matrix.char_count].x = i;
            matrix.char_data[matrix.char_count].y = 0;
            matrix.char_data[matrix.char_count].color = WHITE;
            matrix.char_data[matrix.char_count].ch = matrix.add_data[i].ch;
            matrix.char_count += 1;
        }
    }
}

void move_char()
{
    for (int i = 0; i < matrix.char_count; i++)
    {
        matrix.char_data[i].y += 1;
    }
    for (int i = matrix.char_count - 1; i >= 0; i--)
    {
        bool is_bottom_one = true;

        for (int j = 0; j < matrix.char_count; j++)
        {
            if (matrix.char_data[j].y == matrix.char_data[i].y + 1 && matrix.char_data[j].x == matrix.char_data[i].x)
            {
                matrix.char_data[i].ch = matrix.char_data[j].ch;
                is_bottom_one = false;
            }
        }
        if (is_bottom_one) { matrix.char_data[i].ch = rand() % ('Z' - 'A' + 1) + 'A'; }
    }
}

void delete_char()
{
    for (int i = 0; i < matrix.char_count; i++)
    {
        if (matrix.char_data[i].y >= matrix.screen_cols)
        {
            for (int j = i; matrix.char_data[j].x != -1; j++) { matrix.char_data[j] = matrix.char_data[j + 1]; }
            matrix.char_count -= 1;
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
    matrix.key_code = getch();

    if (matrix.key_code == KEY_ESC)
    {
        matrix.status = EXIT;
    }
    if (matrix.screen_rows != COLS || matrix.screen_cols != LINES)
    {
        matrix.screen_rows = COLS;
        matrix.screen_cols = LINES;
        init_data();
    }
}

void display()
{
    erase();

    for (int i = 0; i < matrix.char_count; i++)
    {
        if (matrix.char_data[i].y < matrix.screen_cols)
        {
            attron(COLOR_PAIR(matrix.char_data[i].color));
            mvaddch(matrix.char_data[i].y, matrix.char_data[i].x, matrix.char_data[i].ch);
        }
    }
    refresh();
}
