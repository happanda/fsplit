#include <string.h>
#ifdef _WIN32
#   include <Windows.h>
#elif __linux__
#   include <fcntl.h>
#   include <sys/mman.h>
#   include <unistd.h>
#else
#   error "Unsupported platform"
#endif

#include "file_mapping.h"
#include "file_op.h"


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
        granularity = getpagesize();
#endif
    }

    return granularity;
}

#ifdef _WIN32

mapped_file map_file(char const* file, map_size_t buf_size,
    map_size_t offset, int write_access)
{
    map_size_t   fsize;
    mapped_file  mf;

    DWORD        true_offset;
    SIZE_T       true_size  ;
    size_t       shift_bytes;

    DWORD open_file_access = GENERIC_READ | (write_access != 0 ? GENERIC_WRITE : 0);
    DWORD flProtect        = write_access != 0 ? PAGE_READWRITE : PAGE_READONLY;
    DWORD map_view_access  = write_access != 0 ? FILE_MAP_WRITE : FILE_MAP_READ;

    memset(&mf, 0, sizeof(mf));

    fsize = file_size(file);
    if (fsize <= 0)
        return mf;

    mf.hFile = CreateFileA(file, open_file_access,
        FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, 0);
    if (mf.hFile != INVALID_HANDLE_VALUE)
    {
        // TODO: can use more precise sizes instead of double zero here
        mf.hMapping = CreateFileMapping(mf.hFile, 0, flProtect, 0, 0, 0);
        if (mf.hMapping != NULL)
        {
            true_offset = (DWORD)(offset / get_granularity()) * get_granularity();
            shift_bytes = offset % get_granularity();
            true_size   = (SIZE_T)(buf_size + shift_bytes);
            if (true_size + true_offset > fsize)
                true_size = (SIZE_T)(fsize - true_offset);

            mf.reg_start = MapViewOfFileEx(mf.hMapping, map_view_access, 0,
                true_offset, true_size, 0);
            mf.region = (char*)mf.reg_start + shift_bytes;
            mf.size   = true_size - shift_bytes;
        }
    }
    return mf;
}

int unmap_file(mapped_file const* mf)
{
    if ((mf->region == 0 || UnmapViewOfFile(mf->region) != 0)
        && (mf->hMapping == 0 || CloseHandle(mf->hMapping) != 0)
        && (mf->hFile == 0 || mf->hFile == INVALID_HANDLE_VALUE || CloseHandle(mf->hFile) != 0))
        return 1;
    else
        return 0;
}

#elif __linux__

mapped_file map_file(char const* file, map_size_t buf_size,
    map_size_t offset, int write_access)
{
    map_size_t   fsize;
    mapped_file  mf;
    int          fd;
    int          open_flags;

    size_t       true_offset;
    size_t       true_size  ;
    size_t       shift_bytes;

    int prot = PROT_READ;
    if (write_access)
        prot |= PROT_WRITE;
    open_flags = write_access ? O_RDWR : O_RDONLY;


    memset(&mf, 0, sizeof(mf));

    fsize = file_size(file);
    if (fsize <= 0)
        return mf;

    fd = open(file, open_flags);
    if (fd != -1)
    {
        true_offset = (offset / get_granularity()) * get_granularity();
        shift_bytes = offset % get_granularity();
        true_size   = buf_size + shift_bytes;
        if ((map_size_t)(true_size + true_offset) > fsize)
            true_size = fsize - true_offset;

        mf.reg_start = mmap(0, buf_size, prot, MAP_PRIVATE, fd, offset);
        if (mf.reg_start == MAP_FAILED)
        {
            mf.region   = (char*)mf.reg_start + shift_bytes;
            mf.reg_size = true_size;
            mf.size     = true_size - shift_bytes;
        }
    }

    return mf;
}

int unmap_file(mapped_file const* mf)
{
    if (mf->region == 0 || munmap(mf->reg_start, mf->reg_size) == 0)
        return 1;
    else
        return 0;
}

#else
#endif


