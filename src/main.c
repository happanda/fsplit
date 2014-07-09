#include <stdio.h>
#ifdef _WIN32
#   include <Windows.h>
#endif

#include "cmd_args.h"
#include "dfa_search.h"
#include "file_stream.h"
#include "name_gen.h"
#include "shift_buffer.h"
#include "testing.h"


#define BUF_SIZE 16

int main(int argc, char* argv[])
{
    fsp_cmd_args cmd_args;
    fsp_file_stream fs;
    fsp_automation aut;
    fsp_shift_buffer sbuf;
    int i;
    int num_read = 0;
    int f_pos = 0;
    int read_size = 0;
    int buf_size = 0;
    unsigned char buf[BUF_SIZE];


    if (!fsp_parse(argc, argv, &cmd_args))
    {
        printf("Arguments parse error\n");
        return 1;
    }

    fs = fsp_open_file(cmd_args.file, om_read);
    if (fsp_bad(&fs))
    {
        printf("Can't open file specified: %s\n", cmd_args.file);
        return 1;
    }

    fsp_sbuf_init(&sbuf, BUF_SIZE);
    fsp_automation_init(&aut, cmd_args.pattern, strlen(cmd_args.pattern));

    buf_size = BUF_SIZE;
    if (buf_size / 2 < aut.pattern_len)
        buf_size = aut.pattern_len * 2;
    read_size = buf_size;
    while ((num_read = fsp_read(&fs, buf, read_size)) > 0)
    {
        fsp_sbuf_push(&sbuf, buf, num_read);

        for (i = 0; i < sbuf.size; ++i)
            printf("%c", sbuf.data[i]);
        printf("\n");

        f_pos = fsp_automation_find_in(&aut, sbuf.data, sbuf.size);
        if (fsp_aut_not_found == f_pos)
        {
            read_size = buf_size - aut.pattern_len;
        }
        else
        {
            read_size = f_pos + aut.pattern_len;
        }
        printf("%d\n", f_pos);
    }

    fsp_automation_free(&aut);
    fsp_sbuf_free(&sbuf);
    fsp_close_file(&fs);

    //test();
    _getche();
    return 0;
}
