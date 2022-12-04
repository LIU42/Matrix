#include "matrix.h"

int main()
{
    srand((unsigned)time(NULL));

    init_window();
    set_window();
    set_color();

    while (is_running())
    {
        update();
        events();
        display();
        usleep(DELAY_USEC);
    }
    unset_window();
    return 0;
}
