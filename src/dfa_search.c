#include <stdlib.h>
#include <string.h>
#include "dfa_search.h"


size_t const ALPHABET_SIZE = 256;

int fsp_automation_init(fsp_automation* aut, char const* pattern, size_t pattern_len)
{
    int i = 0
      , j = 0;

    aut->state = 0;
    aut->pattern_len = pattern_len;
    aut->delta       = calloc(ALPHABET_SIZE * aut->pattern_len, sizeof(int));
    aut->pattern     = calloc(aut->pattern_len, sizeof(char));

    if (0 == aut->delta || 0 == aut->pattern)
    {
        fsp_automation_free(aut);
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

int fsp_automation_find_in(fsp_automation* aut, char const* str, size_t str_len)
{
    int i = 0;

    for (i = 0; i < str_len; ++i) {
        aut->state = aut->delta[ALPHABET_SIZE * aut->state + (unsigned char)str[i]];
        if (aut->state >= aut->pattern_len)
            return i;
    }

    return -1;
}
