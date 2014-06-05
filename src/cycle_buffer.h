#pragma once
#include "export.h"


typedef API_PUBLIC struct
{
    char*   data;
    size_t  first;
    size_t  last;
    size_t  size;
    size_t  capacity;

} fsp_cycle_buffer;


API_PUBLIC int  fsp_cbuf_init(fsp_cycle_buffer* buf, size_t size);
API_PUBLIC void fsp_cbuf_free(fsp_cycle_buffer* buf);

API_PUBLIC void fsp_cbuf_push(fsp_cycle_buffer* buf, char const* data, size_t len);
API_PUBLIC void fsp_cbuf_pop (fsp_cycle_buffer* buf, size_t len);
