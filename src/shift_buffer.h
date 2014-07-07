#pragma once
#include "export.h"


typedef API_PUBLIC struct
{
    char*   data;
    size_t  size;
    size_t  capacity;

} fsp_shift_buffer;


API_PUBLIC int  fsp_sbuf_init(fsp_shift_buffer* buf, size_t size);
API_PUBLIC void fsp_sbuf_free(fsp_shift_buffer* buf);

API_PUBLIC int fsp_sbuf_push(fsp_shift_buffer* buf, char const* data, size_t len);
