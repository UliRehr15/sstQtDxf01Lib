#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T06:04:05
#
#-------------------------------------------------

TEMPLATE	= lib
CONFIG		+= warn_on
CONFIG    += qt
CONFIG += c++11


# CONFIG    -= debug  # ist RELEASE aktiv
CONFIG    -= release  # ist DEBUG aktiv


TARGET = sstQtDxf01Lib
TEMPLATE = lib
CONFIG += staticlib

QT += widgets

INCLUDEPATH +=  ../dxflib/src
INCLUDEPATH +=  ../sstLibreCAD2Lib/Header
INCLUDEPATH +=  ../sst_dxf03_lib/Header
INCLUDEPATH +=  ../sstQt01Lib/Header
INCLUDEPATH +=  ../sst_rec04_lib/Header
INCLUDEPATH +=  ../sst_misc01_lib/Header
INCLUDEPATH +=  ../sstMath01Lib/Header
INCLUDEPATH +=  ../sst_str01_lib/Header
INCLUDEPATH +=  ./Header


SOURCES += \
    sstQtDxf01PathStorage.cpp \
    sstQtDxf01TabMdlCircle.cpp \
    sstQtDxf01TabMdlLine.cpp \
    sstQtDxf01TabMdlMText.cpp \
    sstQtDxf01TabMdlPoint.cpp \
    sstQtDxf01TabMdlText.cpp \
    sstQtDxf01TabViewAll.cpp \
    sstQtDxf01TabGroupBox.cpp


HEADERS += ./Header/sstQtDxf01Lib.h \
           ./Header/sstQtDxf01QtTab.h

OTHER_FILES += README.md

unix {
    target.path = /usr/lib
    INSTALLS += target
}

debug{
  TARGET		= sstQtDxf01Lib_d
}
release{
  TARGET		= sstQtDxf01Lib_r
}


DESTDIR     = ../libs

DISTFILES += \
    sstQtDxf01Lib.odt
