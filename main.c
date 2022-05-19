#include "matrix.h"

int main()
{
    init_window();
    set_window();

    while (TRUE)
    {
        if (window.screen_x != COLS || window.screen_y != LINES) { init_data(); }

        window.screen_x = COLS;
        window.screen_y = LINES;

        if (window.status == MOVE)
        {
            move_char();
            add_char();
            delete_char();
            display_char();
            window.status = WAIT;
        }

        window.exit_code = getch();
        if (window.exit_code == ESC)
        {
            unset_window();
            return 0;
        }
        usleep(DELAY);
    }
}