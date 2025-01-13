#include "stdlib.h"

void kernel_panic(char *kernel_panic_msg)
{
    prints("Kernel Panic: ");
    prints(kernel_panic_msg);
    printc("\n");
    prints("Basicly Your Machine Has Failed And Is Now Halting\n");
    while (1)
    {
    }
}

void kernel_panic_recoverable(char *kernel_panic_msg)
{
    prints("Kernel Panic: ");
    prints(kernel_panic_msg);
    printc("\n");
    prints("Press any key to continue...");
    kbReadScancode();
}