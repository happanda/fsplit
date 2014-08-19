#pragma once
#include <stdlib.h>
#include "export.h"


typedef API_PUBLIC struct
{
    char const*  file;
    char const*  pattern;
} fsp_cmd_args;

API_PUBLIC void fsp_zero(fsp_cmd_args* args);

API_PUBLIC int fsp_parse(int argc, char* argv[], fsp_cmd_args* args);
