#include "matrix.h"

struct Window window;
struct Point char_data[CHAR_MAX_COUNT];
struct String add_data[ADD_CHAR_COUNT];

const char char_list[CHAR_LIST_LEN] = CHAR_LIST;

void* function_counter()
{
    while (TRUE)
    {
        window.status = MOVE;
        usleep(INTERVAL);
    }
}

void init_window()
{
    srand((unsigned int)time(NULL));
    pthread_create(&window.counter, NULL, function_counter, NULL);
}

void set_window()
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
        char_data[i].x = NONE;
        char_data[i].y = NONE;
        char_data[i].color = NONE;
        char_data[i].ch = NONE_CHAR;
    }
    for (int i = 0; i < ADD_CHAR_COUNT; i++)
    {
        add_data[i].len = 0;
        add_data[i].ch = NONE_CHAR;
    }
    window.char_count = 0;
}

void add_char()
{
    for (int i = 0; i < window.screen_x; i += 2)
    {
        int flag = FALSE;
        for (int j = 0; j < window.char_count; j++)
        {
            if (char_data[j].x == i && char_data[j].y == 1) { flag = TRUE; }
        }
        if (flag == TRUE)
        {
            if (add_data[i].len != 0)
            {
                char_data[window.char_count].x = i;
                char_data[window.char_count].y = 0;
                char_data[window.char_count].color = GREEN;
                char_data[window.char_count].ch = add_data[i].ch;
                window.char_count += 1;
                add_data[i].len -= 1;
            }
        }
        else
        {
            int num = rand() % P_BASE;
            if (num <= P_ADD)
            {
                add_data[i].len = rand() % (STRING_MAX_LEN - STRING_MIN_LEN) + STRING_MIN_LEN;
                add_data[i].ch = char_list[rand() % CHAR_LIST_LEN];
                char_data[window.char_count].x = i;
                char_data[window.char_count].y = 0;
                char_data[window.char_count].color = WHITE;
                char_data[window.char_count].ch = add_data[i].ch;
                window.char_count += 1;
            }
        }
    }
}

void move_char()
{
    for (int i = 0; i < window.char_count; i++) { char_data[i].y += 1; }
    for (int i = window.char_count - 1; i >= 0; i--)
    {
        int flag = FALSE;
        for (int j = 0; j < window.char_count; j++)
        {
            if (char_data[j].y == char_data[i].y + 1 && char_data[j].x == char_data[i].x)
            {
                char_data[i].ch = char_data[j].ch;
                flag = TRUE;
            }
        }
        if (flag == FALSE) { char_data[i].ch = char_list[rand() % CHAR_LIST_LEN]; }
    }
}

void delete_char()
{
    for (int i = 0; i < window.char_count; i++)
    {
        if (char_data[i].y >= window.screen_y)
        {
            for (int j = i; char_data[j].x != -1; j++) { char_data[j] = char_data[j + 1]; }
            window.char_count -= 1;
        }
    }
}

void display_char()
{
    erase();
    for (int i = 0; i < window.char_count; i++)
    {
        if (char_data[i].y < window.screen_y)
        {
            attron(COLOR_PAIR(char_data[i].color));
            mvaddch(char_data[i].y, char_data[i].x, char_data[i].ch);
        }
    }
    refresh();
}

void exit_interval()
{
    window.exit_code = getch();
    if (window.exit_code == KEY_ESC) { window.status = EXIT; }
}