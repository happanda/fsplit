cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

# includes path
include_directories(.)

# source files
set(fsplit_SOURCES
cmd_args.c
dfa_search.c
file_mapping.c
file_stream.c
main.c
shift_buffer.c
)

# compilation
add_executable(fsplit ${fsplit_SOURCES})


