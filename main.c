#include "matrix.h"

struct Window window;

int main()
{
    int startTick;
    int endTick;
    int delayTick;

    srand((unsigned)time(NULL));

    initWindow();
    setWindow();
    setColor();

    while (window.status != EXIT)
    {
        startTick = clock();

        events();
        update();
        display();

        endTick = clock();
        delayTick = (INTERVAL - (endTick - startTick)) * 1000;

        usleep((delayTick > 0) ? delayTick : 0);
    }
    unsetWindow();
    return 0;
}
