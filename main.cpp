#include "window.h"

int main(int argc, char* argv[])
{
    terminal_window window;

    while (window.is_running())
    {
        window.update();
        window.events();
        window.display();
        window.delay();
    }
    return EXIT_SUCCESS;
}