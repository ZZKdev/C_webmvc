#pragma once
#include "types.h"
#include "request.h"
#include <string.h>
#include <stdio.h>

#define isSpace(x) ((x == ' ') ? (1) : (0))


char* readLine(DataBuffer* buffer)
{
    char* start = &(buffer->data[buffer->offset]);
    while(buffer->data[(buffer->offset)++] != '\n');
    if(buffer->data[buffer->offset - 2] == '\r')
    {
        buffer->data[buffer->offset - 2] = '\0';
    }
    else
    {
        buffer->data[buffer->offset - 1] = '\0';
    }

    return start;
}

char* getMethod(char* string)
{
    char* method[] = {"GET", "POST"};
    int length = sizeof(method) / sizeof(char*);
    int i;
    for(i = 0; i < length; i++)
    {
        if(stricmp(string, method[i]) == 0)
        {
            return method[i];
        }
    }
    return "Undefined";
}
