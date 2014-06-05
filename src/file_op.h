#pragma once
#include <stdio.h>

#include "size_types.h"

static fsp_map_size_t file_size(char const* path)
{
    FILE*  file;
    fsp_map_size_t  size;

    file = fopen(path, "r");
    if (file == NULL)
        return -1;

    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    fclose(file);

    return size;
}

