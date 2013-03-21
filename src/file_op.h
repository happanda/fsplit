#pragma once
#include <stdint.h>
#include <stdio.h>

static int64_t file_size(char const* path)
{
    FILE*    file;
    int64_t  size;

    file = fopen(path, "r");
    if (file == NULL)
        return -1;

    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    fclose(file);

    return size;
}

