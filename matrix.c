#include "matrix.h"

void Matrix_InitWindow(Matrix* this)
{
    this->status = RUNNING;
    this->screen_rows = 0;
    this->screen_cols = 0;
    this->key_code = 0;
    this->char_count = 0;
}

void Matrix_SetWindow(Matrix* this)
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

void Matrix_SetColor(Matrix* this)
{
    start_color();
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
}

void Matrix_UnsetWindow(Matrix* this)
{
    nocbreak();
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void Matrix_InitData(Matrix* this)
{
    for (int i = 0; i < CHAR_DATA_LEN; i++)
    {
        this->char_data[i].x = -1;
        this->char_data[i].y = -1;
        this->char_data[i].color = -1;
        this->char_data[i].ch = '\0';
    }
    for (int i = 0; i < ADD_DATA_LEN; i++)
    {
        this->add_data[i].len = 0;
        this->add_data[i].ch = '\0';
    }
    this->char_count = 0;
}

bool Matrix_IsRunning(Matrix* this)
{
    return this->status != EXIT;
}

void Matrix_AddChar(Matrix* this)
{
    for (int i = 0; i < this->screen_rows; i += 2)
    {
        bool is_need_add = false;

        for (int j = 0; j < this->char_count; j++)
        {
            if (this->char_data[j].x == i && this->char_data[j].y == 1) { is_need_add = true; }
        }
        if (is_need_add && this->add_data[i].len != 0)
        {
            this->char_data[this->char_count].x = i;
            this->char_data[this->char_count].y = 0;
            this->char_data[this->char_count].color = GREEN;
            this->char_data[this->char_count].ch = this->add_data[i].ch;
            this->char_count += 1;
            this->add_data[i].len -= 1;
        }
        else if (rand() % RANDOM_BASE <= RANDOM_ADD)
        {
            this->add_data[i].len = rand() % (STRING_MAX_LEN - STRING_MIN_LEN) + STRING_MIN_LEN;
            this->add_data[i].ch = rand() % ('Z' - 'A' + 1) + 'A';
            this->char_data[this->char_count].x = i;
            this->char_data[this->char_count].y = 0;
            this->char_data[this->char_count].color = WHITE;
            this->char_data[this->char_count].ch = this->add_data[i].ch;
            this->char_count += 1;
        }
    }
}

void Matrix_MoveChar(Matrix* this)
{
    for (int i = 0; i < this->char_count; i++)
    {
        this->char_data[i].y += 1;
    }
    for (int i = this->char_count - 1; i >= 0; i--)
    {
        bool is_bottom_one = true;

        for (int j = 0; j < this->char_count; j++)
        {
            if (this->char_data[j].y == this->char_data[i].y + 1 && this->char_data[j].x == this->char_data[i].x)
            {
                this->char_data[i].ch = this->char_data[j].ch;
                is_bottom_one = false;
            }
        }
        if (is_bottom_one) { this->char_data[i].ch = rand() % ('Z' - 'A' + 1) + 'A'; }
    }
}

void Matrix_DeleteChar(Matrix* this)
{
    for (int i = 0; i < this->char_count; i++)
    {
        if (this->char_data[i].y >= this->screen_cols)
        {
            for (int j = i; this->char_data[j].x != -1; j++) { this->char_data[j] = this->char_data[j + 1]; }
            this->char_count -= 1;
        }
    }
}

void Matrix_Update(Matrix* this)
{
    Matrix_MoveChar(this);
    Matrix_AddChar(this);
    Matrix_DeleteChar(this);
}

void Matrix_Events(Matrix* this)
{
    this->key_code = getch();

    if (this->key_code == KEY_ESC)
    {
        this->status = EXIT;
    }
    if (this->screen_rows != COLS || this->screen_cols != LINES)
    {
        this->screen_rows = COLS;
        this->screen_cols = LINES;
        Matrix_InitData(this);
    }
}

void Matrix_Display(Matrix* this)
{
    erase();

    for (int i = 0; i < this->char_count; i++)
    {
        if (this->char_data[i].y < this->screen_cols)
        {
            attron(COLOR_PAIR(this->char_data[i].color));
            mvaddch(this->char_data[i].y, this->char_data[i].x, this->char_data[i].ch);
        }
    }
    refresh();
}
