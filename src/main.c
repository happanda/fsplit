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


#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
    fsp_cmd_args cmd_args;
    fsp_file_stream fs;
    int i;
    int rb = 0;
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

    while ((rb = fsp_read(&fs, buf, BUF_SIZE)) > 0)
    {
        for (i = 0; i < rb; ++i)
            printf("%d ", (int)buf[i]);
    }

    //test();
    _getche();
    return 0;
}
