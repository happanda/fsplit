DEV_ROOT = ../../.
include($$DEV_ROOT/qtcreator/fsplit.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.c

LIBS += -L$$DEV_ROOT/qtcreator/bin/$$PATH_SUFFIX

LIBS += -lfsplit
