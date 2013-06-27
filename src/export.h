#pragma once

#include "dyn_lib.h"

#ifdef BUILDING_DLL
# define API_PUBLIC __HELPER_DL_EXPORT
#else
# define API_PUBLIC __HELPER_DL_IMPORT
#endif
