#include "matrix.h"

int main()
{
    init_window();
    set_window();

    while (window.status != EXIT)
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
        exit_interval();
        usleep(DELAY);
    }
    unset_window();
    return 0;
}