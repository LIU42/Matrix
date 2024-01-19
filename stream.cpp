#include "stream.h"

char_stream::char_stream(int x)
{
    int length = get_random_length();

    for (int i = 0; i < length; i++)
    {
        char_list.push_back(get_random_char());
    }
    head_x = x;
    head_y = 0;
}

int char_stream::get_random_length()
{
    return rand() % (MAX_LENGTH - MIN_LENGTH) + MIN_LENGTH;
}

char char_stream::get_random_char()
{
    return rand() % ('Z' - 'A' + 1) + 'A';
}

void char_stream::move()
{
    char_list.push_front(get_random_char());
    char_list.pop_back();
    head_y += 1;
}

void char_stream::display()
{
    int char_index = 0;

    for (auto char_iter = char_list.begin(); char_iter != char_list.end(); ++char_iter, ++char_index)
    {
        attron(COLOR_PAIR((char_index == 0) ? WHITE_COLOR : GREEN_COLOR));
        mvaddch(head_y - char_index, head_x, *char_iter);
    }
}

int char_stream::get_head_x()
{
    return head_x;
}

int char_stream::get_head_y()
{
    return head_y;
}

int char_stream::get_length()
{
    return char_list.size();
}
