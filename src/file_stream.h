#pragma once
#include "file_mapping.h"
#include "export.h"

typedef enum
{
    om_read = 1,
    om_write   ,
    om_append
} open_mode;

typedef API_PUBLIC struct
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

API_PUBLIC file_stream open_file (char const* path, open_mode om);
API_PUBLIC int         close_file(file_stream* fs);

API_PUBLIC int read (file_stream* fs, char*       buf, size_t buf_size);
API_PUBLIC int write(file_stream* fs, char const* buf, size_t buf_size);

