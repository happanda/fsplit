#include "file_stream.h"

int main(int argc, char* argv[])
{
    char buf[35];
    int  i;

    file_stream fs;
    int rb = 0;

    fs = open_file("input", om_read);
    while ((rb = read(&fs, buf, 35)) > 0)
    {
        for (i = 0; i < rb; ++i)
            printf("%d ", (int)buf[i]);
    }


    return 0;
}
