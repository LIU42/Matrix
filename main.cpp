#include "terminal.h"

int main(int argc, char* argv[])
{
    Terminal terminal;

    while (terminal.isRunning())
    {
        terminal.update();
        terminal.events();
        terminal.display();
        terminal.delay();
    }
    return EXIT_SUCCESS;
}