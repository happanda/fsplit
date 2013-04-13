#pragma once

#include "dyn_lib.h"

#ifdef FSPLIT_LIB
# define FSPLIT_API __HELPER_DL_EXPORT
#else
# define FSPLIT_API __HELPER_DL_IMPORT
#endif
