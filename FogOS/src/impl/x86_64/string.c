#include <stdint.h>
#include <stddef.h>

typedef char *string;

uint16_t strlength(const string ch)
{
    uint16_t i = 0;
    while (ch[i])
        i++;
    return i;
}

uint8_t strEql(string ch1, string ch2)
{
    uint8_t result = 1;
    uint16_t size = strlength(ch1);
    if (size != strlength(ch2))
        result = 0;
    else
    {
        for (uint16_t i = 0; i <= size; i++)
        {
            if (ch1[i] != ch2[i])
                result = 0;
        }
    }
    return result;
}

uint8_t strEndsWith(string ch, string suffix)
{
    uint16_t chLen = strlength(ch);
    uint16_t suffixLen = strlength(suffix);

    if (suffixLen > chLen)
        return 0;

    uint16_t offset = chLen - suffixLen;
    for (uint16_t i = 0; i < suffixLen; i++)
    {
        if (ch[offset + i] != suffix[i])
            return 0;
    }

    return 1;
}

uint8_t strContains(string haystack, string needle)
{
    uint16_t hayLen = strlength(haystack);
    uint16_t needleLen = strlength(needle);

    if (needleLen > hayLen)
        return 0;

    for (uint16_t i = 0; i <= hayLen - needleLen; i++)
    {
        uint8_t found = 1;
        for (uint16_t j = 0; j < needleLen; j++)
        {
            if (haystack[i + j] != needle[j])
            {
                found = 0;
                break;
            }
        }
        if (found)
            return 1;
    }

    return 0;
}

uint8_t strcmp(const string ch1, const string ch2)
{
    uint16_t size1 = strlength(ch1);
    uint16_t size2 = strlength(ch2);
    if (size1 != size2)
        return 0;
    for (uint16_t i = 0; i < size1; i++)
    {
        if (ch1[i] != ch2[i])
            return 0;
    }
    return 1;
}

string strcpy(char *dest, const char *src)
{
    if (dest == NULL || src == NULL)
        return NULL;
    char *d = dest;
    while ((*d++ = *src++) != '\0')
        ;
    return dest;
}