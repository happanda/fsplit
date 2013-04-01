SRC_DIR = ../src

CONFIG(debug,debug|release){
    PATH_SUFFIX = debug

    message("Debug Configuration")
} else {
    PATH_SUFFIX = release

    message("Release Configuration")
}


#############
# build paths
BUILD_PATH  = bin/$$PATH_SUFFIX
MISC_PATH   = obj/$$PATH_SUFFIX
OUT_PWD     = $$MISC_PATH
DESTDIR     = $$BUILD_PATH
OBJECTS_DIR = $$MISC_PATH
MOC_DIR     = $$MISC_PATH
UI_DIR      = $$MISC_PATH
RCC_DIR     = $$MISC_PATH


INCLUDE_PATH += $$SRC_DIR

TEMPLATE = app
CONFIG += console
CONFIG -= qt

HEADERS += \
    $$SRC_DIR/file_mapping.h \
    $$SRC_DIR/file_stream.h \
    $$SRC_DIR/file_op.h

SOURCES += \
    $$SRC_DIR/main.c \
    $$SRC_DIR/file_mapping.c \
    $$SRC_DIR/file_stream.c

