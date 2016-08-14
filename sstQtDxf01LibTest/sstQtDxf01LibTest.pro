QT += widgets

# CONFIG       -= debug  # RELEASE ist aktiv
CONFIG       -= release  # DEBUG ist aktiv

INCLUDEPATH +=  ../../sst_str01_lib/Header
INCLUDEPATH +=  ../../sst_misc01_lib/Header
INCLUDEPATH +=  ../../sst_rec04_lib/Header

debug{
  LIBS        += ../../libs/libsst_dxf02_lib_d.a
  LIBS        += ../../libs/libsst_rec04_lib_d.a
  LIBS        += ../../libs/libsst_misc01_lib_d.a
  LIBS        += ../../libs/libsst_str01_lib_d.a
  LIBS        += ../../libs/libdxflib_d.a
}
release{

  win32-g++:QMAKE_LFLAGS += -static
  win32-g++:QMAKE_LFLAGS -= -mthreads
  win32-g++:QMAKE_LFLAGS_EXCEPTIONS_ON -= -mthreads
  win32-g++:QMAKE_CXXFLAGS_EXCEPTIONS_ON -= -mthreads


  LIBS        += ../../libs/libsst_dxf02_lib_r.a
  LIBS        += ../../libs/libsst_rec04_lib_r.a
  LIBS        += ../../libs/libsst_misc01_lib_r.a
  LIBS        += ../../libs/libsst_str01_lib_r.a
  LIBS        += ../../libs/libdxflib_r.a
}


HEADERS       = shapeitem.h \
                sortingbox.h
SOURCES       = \
                shapeitem.cpp \
                sortingbox.cpp \
    sstQtDxf01LibTest.cpp
RESOURCES     = tooltips.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/tooltips
INSTALLS += target
