#pragma once
#include <stdint.h>

typedef uint64_t  map_size_t;

struct mapped_file
{
    struct  impl;
    impl*   pimpl;
};

mapped_file map_file(char const* file, map_size_t buf_size,
    map_size_t offset = 0, bool write_access = false);

bool unmap_file(mapped_file const& mf);

void* region(mapped_file const& mf);

