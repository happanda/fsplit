#include <stdlib.h>
#include "cycle_buffer.h"


int fsp_cbuf_init(fsp_cycle_buffer* buf, size_t size)
{
    buf->data = malloc((size + 1) * sizeof(char));
    if (!buf)
    {
        buf->data  = 0;
        buf->first = 0;
        buf->last  = 0;
        return 0;
    }

    buf->size  = size;
    buf->first = 0;
    buf->last  = 0;
}

int fsp_cbuf_free(fsp_cycle_buffer* buf)
{
    if (0 != buf->data)
        free(buf->data);
}

void fsp_cbuf_push(fsp_cycle_buffer* buf, char const* data, size_t len)
{
    
}

void fsp_cbuf_pop (fsp_cycle_buffer* buf, size_t len)
{

}
