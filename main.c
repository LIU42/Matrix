#include "matrix.h"

struct window window;

int main()
{
    srand((unsigned)time(NULL));

    init_window();
    set_window();
    set_color();

    while (window.status != EXIT)
    {
        update();
        events();
        display();
        usleep(DELAY_USEC);
    }
    unset_window();
    return 0;
}
