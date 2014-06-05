#include <stdlib.h>
#include "dfa_search.h"


size_t const ALPHABET_SIZE = 256;

int fsp_automation_init(fsp_automation* aut, char const* pattern)
{
    int i = 0
      , j = 0;

    aut->pattern_len = strlen(pattern);

    aut->delta = calloc(ALPHABET_SIZE * aut->pattern_len, sizeof(int));
    if (0 == aut->delta)
        return 0;

    aut->pattern = calloc(aut->pattern_len, sizeof(char));
    if (0 == aut->pattern)
    {
        free(aut->delta);
        return 0;
    }

    strncpy(aut->pattern, pattern, aut->pattern_len);

    for (j = 0; j < aut->pattern_len; ++j)
    {
        i = aut->delta[j * ALPHABET_SIZE + (unsigned char)aut->pattern[j]];
        aut->delta[j * ALPHABET_SIZE + (unsigned char)aut->pattern[j]] = j + 1;
        memcpy(&(aut->delta[(j + 1) * ALPHABET_SIZE]),
               &(aut->delta[i * ALPHABET_SIZE]),
               ALPHABET_SIZE * sizeof(int));
    }

    return 1;
}

void fsp_automation_free(fsp_automation* aut)
{
    if (0 != aut->delta)
        free(aut->delta);
    if (0 != aut->pattern)
        free(aut->pattern);
}

int fsp_find_in(fsp_automation const* aut, char const* str)
{
    int i = 0
      , j = 0
      , str_len = strlen(str);

    for (i = 0; i < str_len; ++i) {
        j = aut->delta[ALPHABET_SIZE * j + (unsigned char)str[i]];
        if (j >= aut->pattern_len)
            return (i - aut->pattern_len + 1);
    }

    return -1;
}
