cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

# includes path
include_directories(.)

add_definitions(-DBUILDING_LIBRARY)

# source files
source_group(include REGULAR_EXPRESSION ".*\\.h")
source_group(core REGULAR_EXPRESSION ".*\\.c")

file(GLOB fsplit_HEADERS . *.h)
file(GLOB fsplit_SOURCES . *.c)

# compilation
add_executable(fsplit ${fsplit_HEADERS} ${fsplit_SOURCES})


