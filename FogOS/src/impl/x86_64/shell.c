#include "stdlib.h"
#include "kb.h"
#include "string.h"
#include "panic.h"
#include "xramfs.h"

uint8 theme_active = 1; // the theme of the shell
string uname = "";
bool SafeMODE = false;

void RunShell(string username)
{
    if (!SafeMODE)
        uname = username;
    Print_Prompt(uname, "/");

    string str = readline();
    if (strEndsWith(str, ":dev/null")) // Black Hole
    {
        prints("Input discarded to black hole: dev/null\n");
        return;
    }
    else if (strEql(str, "help"))
    {
        prints("Available tags: dev/null\n");
        prints("Available commands:\n");
        prints("------------------------------------------------\n");
        prints("help     - Displays this help message\n");
        prints("helpman  - Displays this help message about the system\n");
        prints("cls      - Clears the console\n");
        prints("edit     - Opens a text editor for editing\n");
        prints("echo     - Prints the given arguments to the console\n");
        prints("exit     - Exits the shell\n");
        prints("theme    - Changes the shell theme\n");
        prints("whoami   - Displays the current user's username\n");
        prints("neofetch - Displays system information and system updates\n");
        prints("kill     - Kill a process\n");
        prints("mk       - Makes a file\n");
        prints("ls       - Lists files and directories in the current directory\n");
        prints("clearfs  - Nukes the file system\n");
        prints("untrace  - Resets the system good if you have data that you need safe\n");
        prints("cat      - Reads a file by id\n");
        prints("stressfs - Stress test the fs\n");
        prints("------------------------------------------------\n");
        prints("dev/null - A black hole, discards all input and does not produce any output\n");
        prints("Note: XRAMFS Is Not A Noraml Filesystem. You Create Files But You Don't -\nWrite To Them The File Name Is The Data. And The ID Is The Name\n");
    }
    else if (strEql(str, "helpman"))
    {
        prints("How to use a CLI:\n");
        prints("1. Type the command you wish to run you can get a list by running 'help'.\n");
        prints("2. Press enter to run it.\n");
        prints("3. You just ran a command!!!!\n");
    }
    else if (strEql(str, "untrace"))
    {
        clear_console();
        prints("Full System Reset...\n");
        prints("Cleared Screen.\n");
        clearFileSystem();
        uname = "Untraced";
        prints("Cleared Username.\n");
        SafeMODE = true;
    }
    else if (strEql(str, "stressfs"))
    {
        stressTestFS();
    }
    else if (strEql(str, "cls"))
    {
        clear_console();
    }
    else if (strEql(str, "edit"))
    {
        edit();
    }
    else if (strEql(str, "exit"))
    {
        prints("Exiting...\n");
        prints("It is safe to turn off your computer!\n");
        while (1)
        {
        }
    }
    else if (strEql(str, "echo"))
    {
        echo();
    }
    else if (strEql(str, "theme"))
    {
        theme();
    }
    else if (strEql(str, "whoami"))
    {
        whoami();
    }
    else if (strEql(str, "neofetch"))
    {
        version();
        update();
    }
    else if (strEql(str, "kill"))
    {
        prints("What process to kill: ");
        str = readline();
        kill(str);
    }
    else if (strEql(str, "clearfs"))
    {
        clearFileSystem();
    }
    else if (strEql(str, "ls"))
    {
        listFiles();
    }
    else if (strEql(str, "mk"))
    {
        prints("What is the file data: ");
        str = readline();
        createFile(str);
    }
    else if (strEql(str, "cat"))
    {
        prints("What file to read ID: ");
        str = readline();
        prints(readFile(strtoint(str)));
        printc('\n');
    }
    else
    {
        command_not_found(str);
    }
}

void Print_Prompt(string Username, string Dir)
{
    if (theme_active == 0)
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
    else if (theme_active == 3)
    {
        set_console_color(COLOR_GREEN, COLOR_BLACK);
        prints(Username);
        prints("@FogOS");
        printc(':');
        prints(Dir);
        prints("# ");
    }
    else if (theme_active == 1)
    {
        set_console_color(COLOR_GREEN, COLOR_WHITE);
        prints(Username);
        prints("@FogOS");
        set_console_color(COLOR_CYAN, COLOR_WHITE);
        printc(':');
        set_console_color(COLOR_LIGHT_BLUE, COLOR_WHITE);
        prints(Dir);
        set_console_color(COLOR_CYAN, COLOR_WHITE);
        prints("# ");
    }
    else if (theme_active == 2)
    {
        set_console_color(COLOR_GREEN, COLOR_RED);
        prints(Username);
        prints("@FogOS");
        set_console_color(COLOR_LIGHT_RED, COLOR_RED);
        printc(':');
        prints(Dir);
        prints("# ");
    }
}

void echo()
{
    prints("Enter a string to echo: ");
    string str = readline();
    if (strEndsWith(str, ":dev/null"))
    {
        return;
    }
    prints(str);
    printc('\n');
}

void edit()
{
    clear_console();
    string Text = EDITOR_readline();
    createFile(Text);
}

void theme()
{
    prints("The current theme is: ");
    if (theme_active == 0)
    {
        prints("Unix\n"); // Linux TTY-like
    }
    else if (theme_active == 1)
    {
        prints("Snow\n"); // White and Cyan with extras (favorite theme)
    }
    else if (theme_active == 2)
    {
        prints("Fire\n"); // Red and Orange with extras
    }
    else
    {
        prints("Unknown\n"); // Black and Green with extras
    }

    prints("1 - Unix\n");
    prints("2 - Snow\n");
    prints("3 - Fire\n");
    prints("4 - Unknown\n");
    prints("Enter the number of the theme you want to set: ");
    string str = readline();
    if (strEql(str, "1"))
    {
        set_console_color(COLOR_WHITE, COLOR_BLACK);
        theme_active = 0;
        prints("Theme set to Unix.\n");
    }
    else if (strEql(str, "2"))
    {
        set_console_color(COLOR_CYAN, COLOR_WHITE);
        theme_active = 1;
        prints("Theme set to Snow.\n");
    }
    else if (strEql(str, "3"))
    {
        set_console_color(COLOR_LIGHT_RED, COLOR_RED);
        theme_active = 2;
        prints("Theme set to Fire.\n");
    }
    else if (strEql(str, "4"))
    {
        set_console_color(COLOR_GREEN, COLOR_BLACK);
        theme_active = 3;
        prints("Theme set to Unknown.\n");
    }
    else
    {
        prints("Invalid theme number! Please enter a valid number (1-4).\n");
    }
    clear_console(); // Update the console
}

void whoami()
{
    prints("Current user: ");
    prints(uname);
    prints("\nYou are logged into FogOS.\n");
}

void version()
{
    prints("FogOS Version 0.0.2 (Dev)\n");
}

void update()
{
    prints("Package ID: 1325D\n");
}

void kill(string process)
{
    prints("Killing process: ");
    prints(process);
    prints("\n");
    if (strEql(process, "kernel"))
    {
        kernel_panic_recoverable("CRITICAL PROCESS DIED!");
    }
    else
    {
        prints("Process not found! Please ensure the process name is correct.\n");
    }
}

void command_not_found(string str)
{
    // EXTRA USER FRINDLY:
    if (strContains(str, "clear"))
    {
        prints("Use 'cls' instead of 'clear' to clear the console.\n");
    }
    else if (strContains(str, "list"))
    {
        prints("Use 'ls' instead of 'list' to list all files to the console.\n");
    }
    else if (strContains(str, "make"))
    {
        prints("Use 'mk' instead of 'make' to make a file.\n");
    }
    else if (strContains(str, "delete"))
    {
        prints("Use 'rm' instead of 'delete' to delete a file.\n");
    }
    else if (strContains(str, "list"))
    {
        prints("Use 'ls' instead of 'list' to list all files to the console.\n");
    }
    else if (strContains(str, "time") || strContains(str, "date"))
    {
        prints("idk man ):\n");
    }
    else if (strContains(str, "ver"))
    {
        prints("Use 'neofetch' instead of 'ver' or 'version' to get the system info.\n");
    }
    else if (strContains(str, "exit"))
    {
        prints("Use 'exit' to leave the shell.\n");
    }
    else if (strContains(str, "kill"))
    {
        prints("Use 'kill' to kill a process.\n");
    }
    else
    {
        // litle msg
        prints("Command '");
        prints(str);
        prints("' not found. Please check the spelling and try again.\n");
        prints("You can type 'help' for a list of available commands.\n");
        prints("You can also type 'helpman' for help with the system.\n");
    }
}
