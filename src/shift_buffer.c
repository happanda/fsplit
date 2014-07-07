#include <stdlib.h>
#include <string.h>
#include "shift_buffer.h"


void fsp_zero_sbuf(fsp_shift_buffer* sbuf)
{
    sbuf->data = NULL;
    sbuf->size = 0;
    sbuf->capacity = 0;
}

int fsp_sbuf_init(fsp_shift_buffer* buf, size_t size)
{
    fsp_zero_sbuf(buf);

    buf->data = malloc(size * sizeof(char));

    if (!buf)
    {
        return 0;
    }

    buf->size = 0;
    buf->capacity = size;

    return size;
}

void fsp_sbuf_free(fsp_shift_buffer* buf)
{
    if (0 != buf->data)
        free(buf->data);
    fsp_zero_sbuf(buf);
}

int fsp_sbuf_push(fsp_shift_buffer* buf, char const* data, size_t len)
{
    size_t extra_bytes = 0;
    size_t free_bytes = buf->capacity - buf->size;

    if (len > buf->capacity)
        len = buf->capacity;

    if (free_bytes >= len)
    {
        memcpy(buf->data + buf->size, data, len);
        buf->size += len;
    }
    else
    {
        extra_bytes = len - free_bytes;
        memmove(buf->data, buf->data + extra_bytes, buf->size - extra_bytes);
        memcpy(buf->data + buf->capacity - len, data, len);
    }

    return len;
}
