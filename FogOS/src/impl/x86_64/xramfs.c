#include "string.h"
#include "types.h"
#include "stdlib.h"

#define MAX_FILECONTENT_LEN 1024 // 1KB File Length
#define MAX_FILES 1024

typedef struct File
{
    char content[MAX_FILECONTENT_LEN];
    int ID;
} File;

File fileSystem[MAX_FILES];
int fileCount = 0; // Tracks the number of files

int createFile(const char *content)
{
    if (fileCount >= MAX_FILES)
    {
        prints("File system full!\n");
        return -1;
    }
    if (strlength(content) > MAX_FILECONTENT_LEN)
    {
        prints("File text too large!\n");
        return -1;
    }
    strcpy(fileSystem[fileCount].content, content);
    fileSystem[fileCount].ID = fileCount;
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
        prints(fileSystem[i].content);
        printc('\n');
    }
}

char *readFile(int id)
{
    if (fileCount == 0)
    {
        return "No files in the fs.\n";
    }
    for (int i = 0; i < fileCount; i++)
    {
        if (fileSystem[i].ID == id)
        {
            return fileSystem[i].content;
        }
    }
    return "INVALID ID!\n";
}

void clearFileSystem()
{
    fileCount = 0;
    prints("File system cleared.\n");
}

void stressTestFS()
{
    // Create a string of maximum content size (1KB)
    char content[MAX_FILECONTENT_LEN];
    for (int i = 0; i < MAX_FILECONTENT_LEN - 1; i++)
    {
        content[i] = 'A'; // Fill the content with 'A' characters
    }
    content[MAX_FILECONTENT_LEN - 1] = '\0'; // Null-terminate the string

    // Try creating files until the file system is full
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (createFile(content) == -1)
        {
            prints("Failed to create a file.\n");
            prints("\n");
            break;
        }
    }

    prints("Stress test completed.\n");
}
