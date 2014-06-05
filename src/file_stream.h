#pragma once
#include "file_mapping.h"
#include "export.h"

typedef enum
{
    om_read = 1,
    om_write   ,
    om_append
} fsp_open_mode;

typedef API_PUBLIC struct
{
    char*      path;
    fsp_open_mode  mode;

    union
    {
        struct
        {
            fsp_mapped_file  mf;
            size_t  buf_offset;
            size_t  pos_in_buf;
        };
        FILE*  file;
    } stream;
} fsp_file_stream;

API_PUBLIC int fsp_bad       (fsp_file_stream const* fs);
API_PUBLIC int fsp_close_file(fsp_file_stream* fs);
API_PUBLIC fsp_file_stream fsp_open_file (char const* path, fsp_open_mode om);

API_PUBLIC int fsp_read (fsp_file_stream* fs, char*       buf, size_t buf_size);
API_PUBLIC int fsp_write(fsp_file_stream* fs, char const* buf, size_t buf_size);

