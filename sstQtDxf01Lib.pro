#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T06:04:05
#
#-------------------------------------------------

QT       -= gui

TARGET = sstQtDxf01Lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    sstQtDxf01Lib.cpp

HEADERS += \
    sstQtDxf01Lib.h

OTHER_FILES += README.md

unix {
    target.path = /usr/lib
    INSTALLS += target
}
