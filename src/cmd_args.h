#pragma once
#include <stdlib.h>
#include "export.h"


typedef API_PUBLIC struct
{
    char*  pattern;
} fsp_cmd_args;


int fsp_parse(int argc, char* argv[], fsp_cmd_args* args)
{
    int i = 0;
    args->pattern = 0;

    for (i = 0; i < argc; ++i)
    {
        if (!strcmp("-s", argv[i]) && i + 1 < argc)
        {
            args->pattern = argv[i + 1];
        }
    }
    return 0 != args->pattern ? 1 : 0;
}
