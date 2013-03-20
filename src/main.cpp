#include <iostream>
#include <vector>
#include <Windows.h>

#include "file_mapping.h"

int main(int argc, char* argv[])
{
    size_t size = 12;

    mapped_file mf = map_file("input", size);
    DWORD err = GetLastError();
    std::cout << "'";
    char* buf = (char*)mf.region;
    for (size_t i = 0; i < size; ++i)
        std::cout << buf[i];
    std::cout << "'";
    unmap_file(mf);

    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    return 0;
}
