#pragma once
#if (!defined _WIN32) || (_MSC_VER >= 1600)
#  include <stdint.h>
#endif

#if (!defined _WIN32) || (_MSC_VER >= 1600)
typedef int64_t  map_size_t;
#else
typedef __int64  map_size_t;
#endif
