#pragma once
#include <cstdint>
#include <string>
#include <memory>

typedef uint64_t  map_size_t;

struct mapped_file
{
    mapped_file();

    void*  region;

#ifdef _WIN32

    void*   reg_start;
    HANDLE  hFile;
    HANDLE  hMapping;

#elif __linux__

#else
#error "Unsupported platform"
#endif
};

mapped_file map_file(std::string const& file, map_size_t buf_size,
    map_size_t offset = 0, bool write_access = false);

bool unmap_file(mapped_file const& buf);

