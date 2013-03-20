#ifdef _WIN32
#   include <Windows.h>
#elif __linux__
#else
#   error "Unsupported platform"
#endif

#include "file_mapping.h"


#ifdef _WIN32

struct mapped_file::impl
{
    void*   region   ;
#ifdef _WIN32
    void*   reg_start;
    HANDLE  hFile    ;
    HANDLE  hMapping ;
#elif __linux__
#endif
};

void ctor_mapped_file(mapped_file& mf)
{
    mf.pimpl = new mapped_file::impl;
    mf.pimpl->region    = 0;
    mf.pimpl->reg_start = 0;
    mf.pimpl->hFile     = 0;
    mf.pimpl->hMapping  = 0;
}

void dtor_mapped_file(mapped_file& mf)
{
    delete mf.pimpl;
    mf.pimpl = 0;
}


mapped_file map_file(char const* file, map_size_t buf_size,
    map_size_t offset, bool write_access)
{
    mapped_file mf;
    ctor_mapped_file(mf);

    DWORD open_file_access = GENERIC_READ | (write_access  ? GENERIC_WRITE : 0);
    DWORD flProtect        = write_access ? PAGE_READWRITE : PAGE_READONLY;
    DWORD map_view_access  = write_access ? FILE_MAP_WRITE : FILE_MAP_READ;

    mf.pimpl->hFile = CreateFileA(file, open_file_access,
        FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, 0);
    if (mf.pimpl->hFile != INVALID_HANDLE_VALUE)
    {
        // TODO: can use more precise sizes instead of double zero here
        mf.pimpl->hMapping = CreateFileMapping(mf.pimpl->hFile, 0, flProtect, 0, 0, 0);
        if (mf.pimpl->hMapping != NULL)
        {
            // TODO: fix the OffsetHigh and OffsetLow
            mf.pimpl->reg_start = MapViewOfFileEx(mf.pimpl->hMapping, map_view_access, 0, DWORD(offset), SIZE_T(buf_size), 0);
            mf.pimpl->region = mf.pimpl->reg_start; // TODO: calculate region
        }
    }
    return mf;
}

bool unmap_file(mapped_file const& mf)
{
    return (mf.pimpl->region == 0 || UnmapViewOfFile(mf.pimpl->region) != 0)
        && (mf.pimpl->hMapping == 0 || CloseHandle(mf.pimpl->hMapping) != 0)
        && (mf.pimpl->hFile == 0 || mf.pimpl->hFile == INVALID_HANDLE_VALUE || CloseHandle(mf.pimpl->hFile) != 0);
}

#elif __linux__
#else
#endif

void* region(mapped_file const& mf)
{
    return mf.pimpl->region;
}


