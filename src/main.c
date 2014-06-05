#include <stdio.h>
#ifdef _WIN32
#   include <Windows.h>
#endif

#include "file_stream.h"
#include "name_gen.h"


int main(int argc, char* argv[])
{
#ifdef _WIN32
    SYSTEM_INFO  sys_info;
    DWORD   err;
#endif
    unsigned char  buf[120];
    int  i;
    char filename[1000];

    //mf = fsp_map_file("input", size, 0, 0);
    //err = GetLastError();
    //buf = (char*)mf.region;
    //for (i = 0; i < mf.size; ++i)
    //    printf("%c", buf[i]);
    //fsp_unmap_file(&mf);
    //GetSystemInfo(&sys_info);

    fsp_file_stream fs;
    int rb = 0;

    fs = fsp_open_file("input", om_read);
    if (fsp_bad(&fs))
    {
        printf("Can't open file specified: 'input'");
        return 1;
    }

    while ((rb = fsp_read(&fs, buf, 15)) > 0)
    {
        for (i = 0; i < rb; ++i)
            printf("%d ", (int)buf[i]);
    }

    fsp_gen_name(filename, 1000, "AllYourBase", 1);
    return 0;
}
