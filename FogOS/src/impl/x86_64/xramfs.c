#include "string.h"
#include "types.h"
#include "stdlib.h"

#define MAX_FILENAME_LEN 256
#define MAX_FILES 16

typedef struct File
{
    char name[MAX_FILENAME_LEN];
    int size;
} File;

File fileSystem[MAX_FILES];
int fileCount = 0; // Tracks the number of files

int createFile(const char *name)
{
    if (fileCount >= MAX_FILES)
    {
        prints("File system full!\n");
        return -1;
    }
    if (strlength(name) > MAX_FILENAME_LEN)
    {
        prints("File text too large!\n");
        return -1;
    }
    strcpy(fileSystem[fileCount].name, name);
    fileSystem[fileCount].size = 0;
    fileCount++;
    prints("File created.\n");
    return 0;
}

void listFiles()
{
    if (fileCount == 0)
    {
        prints("No files in the fs.\n");
        return;
    }
    prints("Files:\n");
    for (int i = 0; i < fileCount; i++)
    {
        prints("File Text:\n");
        prints(fileSystem[i].name);
        printc('\n');
    }
}

void clearFileSystem()
{
    fileCount = 0;
    prints("File system cleared.\n");
}