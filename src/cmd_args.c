#pragma once
#include <string.h>
#include "cmd_args.h"


int fsp_get_token_count(char const* pattern)
{
    int count = 0;
    int len = 1 + strlen(pattern);
    char* fst = NULL;
    char* tok = NULL;
    
    fst = (char*)malloc(len * sizeof(char));
    strncpy(fst, pattern, len);
    
    tok = strtok(fst, " ");
    while (NULL != tok)
    {
        ++count;
        tok = strtok(NULL, " ");
    }
    free(fst);
    return count;
}

char* fsp_translate_bytes(char const* text)
{
    int count = fsp_get_token_count(text);
    int len = 1 + strlen(text);
    char* fst = NULL;
    char* tok = NULL;
    char* pattern = NULL;
    int number = 0;
    int i = 0;
    
    if (0 == count)
    {
        pattern = (char*)malloc(sizeof(char));
        *pattern = '\0';
        return pattern;
    }
    else
    {
        pattern = (char*)malloc((1 + count) * sizeof(char));
        
        fst = (char*)malloc(len * sizeof(char));
        strncpy(fst, text, len);
        
        i = 0;
        tok = strtok(fst, " ");
        while (NULL != tok)
        {
            number = atoi(tok);
            if (number > 255 || number < 0)
            {
                free(pattern);
                free(fst);
                return NULL;
            }
            pattern[i++] = (char)number;
            
            tok = strtok(NULL, " ");
        }
        free(fst);
        
        pattern[count] = 0;
        return pattern;
    }
}

void fsp_cmd_args_zero(fsp_cmd_args* args)
{
    memset(args, 0, sizeof(fsp_cmd_args));
}

int fsp_cmd_args_parse(int argc, char* argv[], fsp_cmd_args* args)
{
    int i = 0;
    int len = 0;
    fsp_cmd_args_zero(args);

    for (i = 0; i < argc; ++i)
    {
        if (!strcmp("-f", argv[i]) && i + 1 < argc)
        {
            len = 1 + strlen(argv[i + 1]);
            args->file = (char*)malloc(len * sizeof(char));
            strncpy(args->file, argv[i + 1], len);
            args->file[len - 1] = 0;
        }
        else if (!strcmp("-s", argv[i]) && i + 1 < argc)
        {
            len = 1 + strlen(argv[i + 1]);
            args->pattern = (char*)malloc(len * sizeof(char));
            strncpy(args->pattern, argv[i + 1], len);
            args->pattern[len - 1] = 0;
        }
        else if (!strcmp("-b", argv[i]) && i + 1 < argc)
        {
            len = 1 + strlen(argv[i + 1]);
            args->pattern = fsp_translate_bytes(argv[i + 1]);
        }
    }
    return (0 != args->file && 0 != args->pattern) ? 1 : 0;
}

void fsp_cmd_args_free(fsp_cmd_args* args)
{
    free(args->file);
    free(args->pattern);
    fsp_cmd_args_zero(args);
}
