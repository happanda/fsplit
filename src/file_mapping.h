#pragma once
#include <stdio.h>
#ifdef _WIN32
#   include <Windows.h>
#endif

#include "export.h"
#include "size_types.h"

typedef API_PUBLIC struct
{
    void*  region;
    fsp_map_size_t  size;

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
} fsp_mapped_file;


API_PUBLIC fsp_mapped_file fsp_map_file(char const* file, fsp_map_size_t buf_size,
                                    fsp_map_size_t offset, int write_access);

API_PUBLIC int fsp_unmap_file(fsp_mapped_file const* mf);

API_HIDDEN int fsp_get_granularity();
