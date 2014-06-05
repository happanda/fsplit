#pragma once
#include "export.h"
#include "size_types.h"


typedef API_PUBLIC struct
{
    int pattern_len;
    char*  pattern;
    char*  delta;

    // do not use directly
    int state;
} fsp_automation;


API_PUBLIC int  fsp_automation_init(fsp_automation* aut, char const* pattern, size_t pattern_len);
API_PUBLIC void fsp_automation_free(fsp_automation* aut);

API_PUBLIC int  fsp_automation_find_in(fsp_automation* aut, char const* str, size_t str_len);
