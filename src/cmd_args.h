#pragma once
#include <stdlib.h>
#include "export.h"


typedef API_PUBLIC struct
{
    char*  file;
    char*  pattern;
} fsp_cmd_args;

API_PUBLIC void fsp_cmd_args_zero(fsp_cmd_args* args);

API_PUBLIC int  fsp_cmd_args_parse(int argc, char* argv[], fsp_cmd_args* args);
API_PUBLIC void fsp_cmd_args_free(fsp_cmd_args* args);
