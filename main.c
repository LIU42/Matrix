#include "matrix.h"

int main(int argc, char* argv[])
{
    Matrix matrix;

    srand((unsigned)time(NULL));

    initWindow(&matrix);
    setWindow(&matrix);
    setColor(&matrix);

    while (isRunning(&matrix))
    {
        update(&matrix);
        events(&matrix);
        display(&matrix);
        usleep(DELAY_USEC);
    }
    unsetWindow(&matrix);
    return EXIT_SUCCESS;
}
