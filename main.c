#include "matrix.h"

struct Window window;

int main()
{
    srand((unsigned)time(NULL));

    initWindow();
    setWindow();
    setColor();

    while (window.status != EXIT)
    {
        update();
        events();
        display();
        usleep(DELAY_USEC);
    }
    unsetWindow();
    return 0;
}
