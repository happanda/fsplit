#include <stdio.h>
#include <Windows.h>

#include "file_mapping.h"

int main(int argc, char* argv[])
{
    size_t size = 12;
    SYSTEM_INFO  sys_info;
    mapped_file  mf;
    DWORD   err;
    char*   buf;
    size_t  i;

    mf = map_file("input", size);
    err = GetLastError();
    printf("'");
    buf = (char*)region(mf);
    for (i = 0; i < size; ++i)
        printf("%c", buf[i]);
    printf("'");
    unmap_file(mf);

    GetSystemInfo(&sys_info);

    return 0;
}
