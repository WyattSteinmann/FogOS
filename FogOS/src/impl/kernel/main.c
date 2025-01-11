#include "stdlib.h"
#include "shell.h"

void kernel_main()
{
    clear_console();
    prints("Welcome to FogOS\n");
    while (1)
    {
        RunShell();
    }
}