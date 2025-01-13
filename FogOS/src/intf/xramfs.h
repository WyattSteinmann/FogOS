#ifndef XRAMFS_H
#define XRAMFS_H

#include "stddef.h"

// Constants for file system limits
#define MAX_FILECONTENT_LEN 1024
#define MAX_FILES 1024

// File structure
typedef struct File
{
    char content[MAX_FILECONTENT_LEN];
    int ID;
} File;

// Function declarations

/**
 * Creates a new file with the given content.
 * Returns 0 on success, -1 on failure.
 */
int createFile(const char *content);

/**
 * Lists all files currently in the RAM-based file system.
 */
void listFiles();

// distroys the file system
void clearFileSystem();

// Read A File By ID
char *readFile(int id);

// Stress Test FS Function
void stressTestFS();

#endif // XRAMFS_H