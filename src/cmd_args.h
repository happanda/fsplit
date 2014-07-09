#pragma once
#include <stdlib.h>
#include "export.h"


typedef API_PUBLIC struct
{
    char const*  file;
    char const*  pattern;
} fsp_cmd_args;

API_PUBLIC void fsp_zero(fsp_cmd_args* args)
{
    memset(args, 0, sizeof(fsp_cmd_args));
}

API_PUBLIC int fsp_parse(int argc, char* argv[], fsp_cmd_args* args)
{
    int i = 0;
    fsp_zero(args);

    for (i = 0; i < argc; ++i)
    {
        if (!strcmp("-f", argv[i]) && i + 1 < argc)
        {
            args->file = argv[i + 1];
        }
        else if (!strcmp("-s", argv[i]) && i + 1 < argc)
        {
            args->pattern = argv[i + 1];
        }
    }
    return (0 != args->file && 0 != args->pattern) ? 1 : 0;
}
