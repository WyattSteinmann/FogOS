#include "stdlib.h"
#include "kb.h"
#include "string.h"

void RunShell()
{
    Print_Prompt("root", "/");

    string ch = readline();
    if (strEql(ch, "help"))
    {
        prints("Available commands: help, clear, edit, echo, exit\n");
    }
    else if (strEql(ch, "clear"))
    {
        clear_console();
    }
    else if (strEql(ch, "edit"))
    {
        edit();
    }
    else if (strEql(ch, "exit"))
    {
        prints("Exiting...\n");
        prints("It Is Safe To Turn Off Your Computer!");
        while (1)
        {
        }
    }
    else if (strEql(ch, "echo"))
    {
        echo();
    }
    else if (strEql(ch, ""))
    {
        // Ignore this command
        return;
    }
    else
    {
        prints("Command \"");
        prints(ch);
        prints("\" Not Found!\n");
    }
}

void Print_Prompt(string Username, string Dir)
{
    set_console_color(COLOR_GREEN, COLOR_BLACK);
    prints(Username);
    prints("@FogOS");
    set_console_color(COLOR_WHITE, COLOR_BLACK);
    printc(':');
    set_console_color(COLOR_LIGHT_BLUE, COLOR_BLACK);
    prints(Dir);
    set_console_color(COLOR_WHITE, COLOR_BLACK);
    prints("# ");
}

void echo()
{
    prints("Enter a string to echo: ");
    string str = readline();
    prints(str);
    printc('\n');
}

void edit()
{
    clear_console();
    EDITOR_readline();
}