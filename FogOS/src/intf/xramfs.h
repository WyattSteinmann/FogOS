#ifndef XRAMFS_H
#define XRAMFS_H

#include "stddef.h"

// Constants for file system limits
#define MAX_FILENAME_LEN 256
#define MAX_FILES 16

// File structure
typedef struct File
{
    char name[MAX_FILENAME_LEN];
    int size;
} File;

// Function declarations

/**
 * Creates a new file with the given name.
 * Returns 0 on success, -1 on failure.
 */
int createFile(const char *name);

/**
 * Lists all files currently in the RAM-based file system.
 */
void listFiles();

/*
    distroys the file system
*/
void clearFileSystem();

#endif // XRAMFS_H