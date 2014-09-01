#pragma once
#include <stdio.h>


void fsp_gen_name(char* buf, size_t buf_len, char const* basename, size_t num)
{
#ifdef _WIN32
    _snprintf_s(buf, buf_len, buf_len - 1, "%s_%04d.fsplit", basename, num);
#elif
    snprintf(buf, buf_len, "%s_%04d.fsplit", basename, num);
#endif  
}
