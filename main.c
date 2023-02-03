#include "matrix.h"

int main()
{
    Matrix matrix;

    srand((unsigned)time(NULL));

    init_window(&matrix);
    set_window(&matrix);
    set_color(&matrix);

    while (is_running(&matrix))
    {
        update(&matrix);
        events(&matrix);
        display(&matrix);
        usleep(DELAY_USEC);
    }
    unset_window(&matrix);
    return 0;
}
