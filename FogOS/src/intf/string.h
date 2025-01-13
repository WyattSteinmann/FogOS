#pragma once
#include "types.h"
#include "stddef.h"

uint16 strlength(string ch);
uint8 strEql(string ch1, string ch2);
uint8 strEndsWith(string ch, string suffix);
uint8 strContains(string haystack, string needle);
string strcpy(char *dest, const char *src);
string strcmp(string ch1, string ch2);
int strtoint(const char *str);