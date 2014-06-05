#pragma once
#if (!defined _WIN32) || (_MSC_VER >= 1600)
#  include <stdint.h>
#endif

#ifdef _WIN32
#  include <crtdefs.h>
#endif

#if (!defined _WIN32) || (_MSC_VER >= 1600)
typedef int64_t  fsp_map_size_t;
#else
typedef __int64  fsp_map_size_t;
#endif
