#pragma once
#include <stdio.h>
#include <Windows.h>

typedef int  map_size_t;

typedef struct
{
    void*   region   ;
#ifdef _WIN32
    void*   reg_start;
    HANDLE  hFile    ;
    HANDLE  hMapping ;
#elif __linux__
#else
#   error "Unsupported platform"
#endif
} mapped_file;

mapped_file map_file(char const* file, map_size_t buf_size, map_size_t offset, int write_access);

int unmap_file(mapped_file const* mf);

