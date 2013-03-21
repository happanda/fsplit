#include <stdio.h>
#include <Windows.h>

#include "file_mapping.h"

int main(int argc, char* argv[])
{
    size_t size = 8;
    SYSTEM_INFO  sys_info;
    mapped_file  mf;
    DWORD   err;
    char*   buf;
    size_t  i;

    mf = map_file("input", size, 0, 0);
    err = GetLastError();
    buf = (char*)mf.region;
    for (i = 0; i < mf.size; ++i)
        printf("%c", buf[i]);
    unmap_file(&mf);

    GetSystemInfo(&sys_info);

    return 0;
}
