#pragma once
#include "export.h"
#include "size_types.h"


extern size_t const ALPHABET_SIZE;

typedef API_PUBLIC struct
{
    int pattern_len;
    char*  pattern;
    char*  delta;

} fsp_automation;


API_PUBLIC int  fsp_automation_init(fsp_automation* aut, char const* pattern);
API_PUBLIC void fsp_automation_free(fsp_automation* aut);

API_PUBLIC int  fsp_find_in(fsp_automation const* aut, char const* str);
