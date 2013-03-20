#ifdef _WIN32
#   include <Windows.h>
#elif __linux__
#else
#   error "Unsupported platform"
#endif

#include "file_mapping.h"


#ifdef _WIN32

mapped_file::mapped_file()
    : region   (0)
    , reg_start(0)
    , hFile    (0)
    , hMapping (0)
{
}

mapped_file map_file(std::string const& file, map_size_t buf_size,
    map_size_t offset, bool write_access)
{
    mapped_file mf;

    DWORD open_file_access = GENERIC_READ | (write_access  ? GENERIC_WRITE : 0);
    DWORD flProtect        = write_access ? PAGE_READWRITE : PAGE_READONLY;
    DWORD map_view_access  = write_access ? FILE_MAP_WRITE : FILE_MAP_READ;

    mf.hFile = CreateFileA(file.c_str(), open_file_access,
        FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, 0);
    if (mf.hFile != INVALID_HANDLE_VALUE)
    {
        // TODO: can use more precise sizes instead of double zero here
        mf.hMapping = CreateFileMapping(mf.hFile, 0, flProtect, 0, 0, 0);
        if (mf.hMapping != NULL)
        {
            // TODO: fix the OffsetHigh and OffsetLow
            mf.reg_start = MapViewOfFileEx(mf.hMapping, map_view_access, 0, DWORD(offset), SIZE_T(buf_size), 0);
            mf.region = mf.reg_start; // TODO: cals region
        }
    }
    return mf;
}

bool unmap_file(mapped_file const& mf)
{
    return (mf.region == 0 || UnmapViewOfFile(mf.region) != 0)
        && (mf.hMapping == 0 || CloseHandle(mf.hMapping) != 0)
        && (mf.hFile == 0 || mf.hFile == INVALID_HANDLE_VALUE || CloseHandle(mf.hFile) != 0);
}

#elif __linux__
#else
#endif

