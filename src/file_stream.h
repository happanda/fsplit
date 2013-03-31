#pragma once
#include "file_mapping.h"

typedef enum
{
    om_read = 1,
    om_write   ,
    om_append
} open_mode;

typedef struct
{
    char*      path;
    open_mode  mode;

    union
    {
        struct
        {
            mapped_file  mf;
            size_t       buf_offset;
            size_t       pos_in_buf;
        };
        FILE*  file;
    } stream;
} file_stream;

file_stream open_file (char const* path, open_mode om);
int         close_file(file_stream* fs);

int read (file_stream* fs, char*       buf, size_t buf_size);
int write(file_stream* fs, char const* buf, size_t buf_size);

