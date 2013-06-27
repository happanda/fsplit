DEV_ROOT = ../.
TEMPLATE = lib

include($$DEV_ROOT/qtcreator/fsplit.pri)

CONFIG -= qt

HEADERS += \
    $$SRC_DIR/file_mapping.h \
    $$SRC_DIR/file_stream.h \
    $$SRC_DIR/file_op.h \
    $$SRC_DIR/dyn_lib.h \
    $$SRC_DIR/export.h

SOURCES += \
    $$SRC_DIR/file_mapping.c \
    $$SRC_DIR/file_stream.c
