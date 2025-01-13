#include "stdlib.h"
#include "shell.h"
#include "panic.h"
#include "xramfs.h"

void kernel_main()
{
    set_console_color(COLOR_CYAN, COLOR_WHITE);
    clear_console();
    prints("Welcome to FogOS!\n\n");
    prints("How to use a CLI:\n");
    prints("1. Type the command you wish to run you can get a list by running 'help'.\n");
    prints("2. Press enter to run it.\n");
    prints("3. You just ran a command!!!!\n\n");
    while (1)
    {
        RunShell("root");
    }
}

int64 Syscall_math(int64 num1, char op, int64 num2)
{
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        if (num2 == 0)
        {
            kernel_panic_recoverable("Division by zero");
        }
        return num1 / num2;
    case '%':
        if (num2 == 0)
        {
            kernel_panic_recoverable("Division by zero");
        }
        return num1 % num2;
    default:
        return 0;
    }
}