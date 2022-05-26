#include "matrix.h"

int main()
{
    initWindow();
    setWindow();

    while (window.status != EXIT)
    {
        if (window.screenX != COLS || window.screenY != LINES) { initData(); }

        window.screenX = COLS;
        window.screenY = LINES;

        if (window.status == MOVE)
        {
            moveChar();
            addChar();
            deleteChar();
            displayChar();
            window.status = WAIT;
        }
        exitInterval();
        usleep(DELAY);
    }
    unsetWindow();
    return 0;
}