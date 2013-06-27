#pragma once
#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32
#   include <Windows.h>
#endif

#include "export.h"

typedef int64_t  map_size_t;

typedef API_PUBLIC struct
{
    void*       region;
    map_size_t  size  ;

    // do not use
    void*   reg_start;
#ifdef _WIN32    
    HANDLE  hFile    ;
    HANDLE  hMapping ;
#elif __linux__
    size_t  reg_size ;
#else
#   error "Unsupported platform"
#endif
} mapped_file;


API_PUBLIC mapped_file map_file(char const* file, map_size_t buf_size, map_size_t offset, int write_access);

API_PUBLIC int unmap_file(mapped_file const* mf);

API_HIDDEN int get_granularity();
