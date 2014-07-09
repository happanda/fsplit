#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#   include <Windows.h>
#elif __linux__
#else
#   error "Unsupported platform"
#endif

#include "file_stream.h"


int fsp_bad(fsp_file_stream const* fs)
{
    if (NULL == fs)
        return 0;

    if (fs->mode == om_read)
        return (fs->stream.mf.region == 0) ? 1 : 0;

    return (fs->stream.file == 0) ? 1 : 0;
}

fsp_file_stream fsp_open_file(char const* path, fsp_open_mode om)
{
    fsp_file_stream fs;
    size_t      path_len;

    memset(&fs, 0, sizeof(fs));
    path_len = strlen(path) + 1;

    fs.mode = om;
    fs.path = malloc(path_len);
    if (!fs.path)
        return fs;

    strncpy(fs.path, path, path_len);

    switch (fs.mode)
    {
    case om_read:
        {
            fs.stream.buf_offset = 0;
            fs.stream.pos_in_buf = 0;
            fs.stream.mf         = fsp_map_file(fs.path, fsp_get_granularity(), 0, 0);
            break;
        }
    case om_write:
        {
            fs.stream.file = fopen(path, "wb");
            break;
        }
    case om_append:
        {
            fs.stream.file = fopen(path, "ab");
            break;
        }
    }

    return fs;
}

int fsp_close_file(fsp_file_stream* fs)
{
    int result = 0;

    if (fs->path != 0)
        free(fs->path);

    switch (fs->mode)
    {
    case om_read:
        {
            if (fs->stream.mf.region != 0)
            {
                result = fsp_unmap_file(&fs->stream.mf);
                memset(fs, 0, sizeof(fs));
            }
            break;
        }
    case om_write:
    case om_append:
        {
            result = fclose(fs->stream.file);
            break;
        }
    }

    return result;
}

int fsp_read(fsp_file_stream* fs, char* buf, size_t num_bytes)
{
    size_t read_bytes = 0;
    size_t min_buf    = 0;
    size_t bytes_left = 0;

    assert(fs->mode == om_read);

    while (read_bytes < num_bytes)
    {
        bytes_left = (size_t)(fs->stream.mf.size - fs->stream.pos_in_buf);
        min_buf = num_bytes < bytes_left ? num_bytes : bytes_left;

        memcpy(buf, (char*)fs->stream.mf.region + fs->stream.pos_in_buf, min_buf);
        fs->stream.pos_in_buf += min_buf;
        read_bytes            += min_buf;

        if ((fsp_map_size_t)fs->stream.pos_in_buf == fs->stream.mf.size)
        {   // move mapped region further in file
            fs->stream.buf_offset += (size_t)fs->stream.mf.size;
            fs->stream.pos_in_buf = 0;

            if (!fsp_unmap_file(&fs->stream.mf))
                return read_bytes;

            fs->stream.mf = fsp_map_file(fs->path, fs->stream.mf.size, fs->stream.buf_offset, 0);
            if (!fs->stream.mf.region || fs->stream.mf.size == 0)
                return read_bytes;
        }
    }

    return read_bytes;
}

int fsp_write(fsp_file_stream* fs, char const* buf, size_t num_bytes)
{
    assert(fs->mode == om_write || fs->mode == om_append);

    return fwrite(buf, sizeof(char), num_bytes, fs->stream.file);
}

