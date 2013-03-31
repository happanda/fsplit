SRC_DIR = ../src

INCLUDE_PATH += $$SRC_DIR

TEMPLATE = app
CONFIG += console
CONFIG -= qt

HEADERS += \
    $$SRC_DIR/file_mapping.h \
    $$SRC_DIR/file_stream.h \
    $$SRC_DIR/file_op.h \
    $$SRC_DIR/file_mapping.h

SOURCES += \
    $$SRC_DIR/main.c \
    $$SRC_DIR/file_mapping.c \
    $$SRC_DIR/main.c \
    $$SRC_DIR/file_stream.c \
    $$SRC_DIR/file_mapping.c
