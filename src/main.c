#include <conio.h>
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
#define FILENAME_LEN 256

int main(int argc, char* argv[])
{
    fsp_cmd_args cmd_args;
    fsp_file_stream fs, out_file;
    fsp_automation aut;
    fsp_shift_buffer sbuf;
    int i;
    int num_read = 0
      , f_pos = 0
      , read_size = 0
      , write_size = 0
      , buf_size = 0
      , fragment_num = 0
      , found = 0
      , stick_shift = 0;
    char filename[FILENAME_LEN];
    unsigned char buf[BUF_SIZE];


    if (!fsp_cmd_args_parse(argc, argv, &cmd_args))
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
    fragment_num = 0;

    fsp_zero_fstream(&out_file);

    while ((num_read = fsp_read(&fs, buf, read_size)) > 0 || sbuf.size > 0)
    {
        fsp_sbuf_push(&sbuf, buf, num_read);

        f_pos = fsp_automation_find_in(&aut, sbuf.data + stick_shift, sbuf.size);

        if (fsp_aut_not_found == f_pos)
        {
            read_size = sbuf.size;
            write_size = read_size;
            stick_shift = 0;
        }
        else
        {
            f_pos += stick_shift;
            stick_shift = 0;

            read_size = f_pos + aut.pattern_len;
            write_size = f_pos;
            
            if (stick_right == cmd_args.stick)
            {
                read_size -= aut.pattern_len;
                stick_shift = aut.pattern_len;
            }
            else if (stick_left == cmd_args.stick)
            {
                write_size += aut.pattern_len;
                stick_shift = 0;
            }
            else if (stick_both == cmd_args.stick)
            {
                read_size -= aut.pattern_len;
                write_size += aut.pattern_len;
                stick_shift = aut.pattern_len;
            }
            found = 1;
        }

        // write to output
        if (!fsp_is_opened(&out_file))
        {
            fsp_gen_name(filename, FILENAME_LEN, cmd_args.file, fragment_num);
            out_file = fsp_open_file(filename, om_write);
            ++fragment_num;
        }

        fsp_write(&out_file, sbuf.data, write_size);
        fsp_sbuf_pop(&sbuf, read_size);
        if (found)
        {
            fsp_close_file(&out_file);
            found = 0;
        }

#ifdef FSPLIT_DEBUG
        //for (i = 0; i < read_size; ++i)
        //    printf("%c", sbuf.data[i]);
        //printf("\n");
#endif
    }

    if (fsp_is_opened(&out_file))
    {
        fsp_write(&out_file, sbuf.data, sbuf.size);
        fsp_close_file(&out_file);
    }

    fsp_automation_free(&aut);
    fsp_sbuf_free(&sbuf);
    fsp_close_file(&fs);
    fsp_cmd_args_free(&cmd_args);
    
    //test();
    //_getche();
    return 0;
}
