SRC_DIR  = $$DEV_ROOT/src

CONFIG(debug,debug|release){
    PATH_SUFFIX = debug

    message("Debug Configuration")
} else {
    PATH_SUFFIX = release

    message("Release Configuration")
}


#############
# build paths
BUILD_PATH  = $$DEV_ROOT/qtcreator/bin/$$PATH_SUFFIX
MISC_PATH   = $$DEV_ROOT/qtcreator/obj/$$PATH_SUFFIX
OUT_PWD     = $$MISC_PATH
DESTDIR     = $$BUILD_PATH
OBJECTS_DIR = $$MISC_PATH
MOC_DIR     = $$MISC_PATH
UI_DIR      = $$MISC_PATH
RCC_DIR     = $$MISC_PATH


INCLUDEPATH += $$SRC_DIR

message($$TEMPLATE)
contains(TEMPLATE, lib)|contains(TEMPLATE, vclib){
    DEFINES += BUILDING_DLL
}

