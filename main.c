#include "matrix.h"

int main()
{
    Matrix matrix;

    srand((unsigned)time(NULL));

    Matrix_InitWindow(&matrix);
    Matrix_SetWindow(&matrix);
    Matrix_SetColor(&matrix);

    while (Matrix_IsRunning(&matrix))
    {
        Matrix_Update(&matrix);
        Matrix_Events(&matrix);
        Matrix_Display(&matrix);
        usleep(DELAY_USEC);
    }
    Matrix_UnsetWindow(&matrix);
    return 0;
}
