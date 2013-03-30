#include <assert.h>

#ifdef _WIN32
#   include <Windows.h>
#elif __linux__
#else
#   error "Unsupported platform"
#endif

#include "file_stream.h"

int get_granularity()
{
    static int granularity = 0;

    if (granularity == 0)
    {
#ifdef _WIN32
        SYSTEM_INFO sys_info;
        GetSystemInfo(&sys_info);
        granularity = (int)sys_info.dwAllocationGranularity;
#elif __linux__
        granularity = 4096; // TODO: replace this
#endif
    }

    return granularity;
}


file_stream open_file(char const* path, open_mode om)
{
    file_stream fs;
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
            fs.stream.mf         = map_file(fs.path, get_granularity(), 0, 0);
            break;
        }
    case om_write:
        {
            fs.stream.file = fopen(path, "w");
            break;
        }
    case om_append:
        {
            fs.stream.file = fopen(path, "a");
            break;
        }
    }

    return fs;
}

int read(file_stream* fs, char* buf, int num_bytes)
{
    int read_bytes = 0;
    int min_buf    = 0;
    int bytes_left = 0;

    assert(fs->mode == om_read);

    while (read_bytes < num_bytes)
    {
        bytes_left = fs->stream.mf.size - fs->stream.pos_in_buf;
        min_buf = num_bytes < bytes_left ? num_bytes : bytes_left;

        memcpy(buf, (char*)fs->stream.mf.region + fs->stream.pos_in_buf, min_buf);
        fs->stream.pos_in_buf += min_buf;
        read_bytes            += min_buf;

        if (fs->stream.pos_in_buf == fs->stream.mf.size)
        {   // move mapped region further in file
            fs->stream.buf_offset += fs->stream.mf.size;
            fs->stream.pos_in_buf = 0;

            if (!unmap_file(&fs->stream.mf))
                return read_bytes;

            fs->stream.mf = map_file(fs->path, fs->stream.mf.size, fs->stream.buf_offset, 0);
            if (!fs->stream.mf.region || fs->stream.mf.size == 0)
                return read_bytes;
        }
    }

    return read_bytes;
}

int write(file_stream* fs, char const* buf, int num_bytes)
{
    assert(fs->mode == om_write || fs->mode == om_append);

    fwrite(buf, sizeof(char), num_bytes, fs->stream.file);
}

