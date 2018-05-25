TEMPLATE	    = app
CONFIG	 	   += warn_on
CONFIG       += qt
CONFIG       += windows
CONFIG       += c++11


QT += widgets

# CONFIG       -= debug  # RELEASE ist aktiv
CONFIG       -= release  # DEBUG ist aktiv


INCLUDEPATH +=  ../../sstMath01Lib/Header
INCLUDEPATH +=  ../../sstLibreCAD2Lib/Header
INCLUDEPATH +=  ../../dxflib/Header
INCLUDEPATH +=  ../../sst_str01_lib/Header
INCLUDEPATH +=  ../../sst_misc01_lib/Header
INCLUDEPATH +=  ../../sst_rec04_lib/Header
INCLUDEPATH +=  ../../sstQt01Lib/Header
INCLUDEPATH +=  ../../sstQtDxf01Lib/Header
INCLUDEPATH +=  ../../sst_dxf03_lib/Header


HEADERS     = \
    sstQtDxf01TabTest.h

SOURCES     = \
    sstQtDxf01TabTest.cpp \
    TabTest_Dialog.cpp


debug{
  LIBS        += ../../libs/libsstQtDxf01Lib_d.a
  LIBS        += ../../libs/libsstQt01Lib_d.a
  LIBS        += ../../libs/libsst_dxf03_lib_d.a
  LIBS        += ../../libs/libsst_rec04_lib_d.a
  LIBS        += ../../libs/libsst_misc01_lib_d.a
  LIBS        += ../../libs/libsstMath01Lib_d.a
  LIBS        += ../../libs/libsst_str01_lib_d.a
  LIBS        += ../../libs/libsstLibreCAD2Lib_d.a
  LIBS        += ../../libs/libdxflib_d.a
}

release{

  win32-g++:QMAKE_LFLAGS += -static
  win32-g++:QMAKE_LFLAGS -= -mthreads
  win32-g++:QMAKE_LFLAGS_EXCEPTIONS_ON -= -mthreads
  win32-g++:QMAKE_CXXFLAGS_EXCEPTIONS_ON -= -mthreads

  LIBS        += ../../libs/libsstQt01Lib_r.a
  LIBS        += ../../libs/libsst_dxf03_lib_r.a
  LIBS        += ../../libs/libsst_rec04_lib_r.a
  LIBS        += ../../libs/libsst_misc01_lib_r.a
  LIBS        += ../../libs/libsstMath01Lib_r.a
  LIBS        += ../../libs/libsst_str01_lib_r.a
  LIBS        += ../../libs/libsstLibreCAD2Lib_r.a
  LIBS        += ../../libs/libdxflib_r.a

}

TARGET	  	= sstQtDxf01TabTest

# copy to deployment directory
# DESTDIR     = ../../../local_deploy
