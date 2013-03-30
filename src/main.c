#include <stdio.h>
#include <Windows.h>

#include "file_stream.h"

int main(int argc, char* argv[])
{
    size_t size = 8;
    SYSTEM_INFO  sys_info;
    mapped_file  mf;
    DWORD   err;
    char    buf[120];
    int     i;

    //mf = map_file("input", size, 0, 0);
    //err = GetLastError();
    //buf = (char*)mf.region;
    //for (i = 0; i < mf.size; ++i)
    //    printf("%c", buf[i]);
    //unmap_file(&mf);
    //GetSystemInfo(&sys_info);

    file_stream fs;
    int rb = 0;

    fs = open_file("input", om_read);
    while ((rb = read(&fs, buf, 15)) > 0)
    {
        for (i = 0; i < rb; ++i)
            printf("%d ", (int)buf[i]);
    }


    return 0;
}
