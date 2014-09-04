#pragma once
#include <stdlib.h>
#include "export.h"


typedef enum
{
    stick_none ,
    stick_left ,
    stick_right,
    stick_both
} stick_to;

typedef API_PUBLIC struct
{
    char*  file;
    char*  pattern;
    // where the found pattern is put: to previous text, following text, both or nowhere
    stick_to stick;
} fsp_cmd_args;

API_PUBLIC void fsp_cmd_args_zero(fsp_cmd_args* args);

API_PUBLIC int  fsp_cmd_args_parse(int argc, char* argv[], fsp_cmd_args* args);
API_PUBLIC void fsp_cmd_args_free(fsp_cmd_args* args);
