#############################################################################
# Makefile for building: libsstQtDxf01Lib_d.a
# Generated by qmake (3.1) (Qt 5.12.8)
# Project:  sstQtDxf01Lib.pro
# Template: lib
# Command: /usr/lib/qt5/bin/qmake -o Makefile sstQtDxf01Lib.pro -spec linux-clang CONFIG+=debug CONFIG+=qml_debug
#############################################################################

MAKEFILE      = Makefile

EQ            = =

####### Compiler, tools and options

CC            = clang
CXX           = clang++
DEFINES       = -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_QML_DEBUG
CFLAGS        = -pipe -g -fPIC -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -fPIC -std=gnu++11 -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I. -I../dxflib/src -I../sstLibreCAD2Lib/Header -I../sst_dxf03_lib/Header -I../sstQt01Lib/Header -I../sst_rec04_lib/Header -I../sst_misc01_lib/Header -I../sstMath01Lib/Header -I../sst_str01_lib/Header -IHeader -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtWidgets -isystem /usr/include/x86_64-linux-gnu/qt5/QtGui -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-clang
QMAKE         = /usr/lib/qt5/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
QINSTALL      = /usr/lib/qt5/bin/qmake -install qinstall
QINSTALL_PROGRAM = /usr/lib/qt5/bin/qmake -install qinstall -exe
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = sstQtDxf01Lib_d1.0.0
DISTDIR = /home/uli/Entwicklung/sstQtDxf01Lib/.tmp/sstQtDxf01Lib_d1.0.0
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = sstQtDxf01PathStorage.cpp \
		sstQtDxf01TabMdlCircle.cpp \
		sstQtDxf01TabMdlLine.cpp \
		sstQtDxf01TabMdlMText.cpp \
		sstQtDxf01TabMdlPoint.cpp \
		sstQtDxf01TabMdlText.cpp \
		sstQtDxf01TabViewAll.cpp \
		sstQtDxf01TabGroupBox.cpp \
		sstQtDxf01Convert.cpp moc_sstQtDxf01Lib.cpp \
		moc_sstQtDxf01QtTab.cpp
OBJECTS       = sstQtDxf01PathStorage.o \
		sstQtDxf01TabMdlCircle.o \
		sstQtDxf01TabMdlLine.o \
		sstQtDxf01TabMdlMText.o \
		sstQtDxf01TabMdlPoint.o \
		sstQtDxf01TabMdlText.o \
		sstQtDxf01TabViewAll.o \
		sstQtDxf01TabGroupBox.o \
		sstQtDxf01Convert.o \
		moc_sstQtDxf01Lib.o \
		moc_sstQtDxf01QtTab.o
DIST          = sstQtDxf01Lib.odt \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/clang.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-clang/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qml_debug.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		sstQtDxf01Lib.pro Header/sstQtDxf01Lib.h \
		Header/sstQtDxf01QtTab.h sstQtDxf01PathStorage.cpp \
		sstQtDxf01TabMdlCircle.cpp \
		sstQtDxf01TabMdlLine.cpp \
		sstQtDxf01TabMdlMText.cpp \
		sstQtDxf01TabMdlPoint.cpp \
		sstQtDxf01TabMdlText.cpp \
		sstQtDxf01TabViewAll.cpp \
		sstQtDxf01TabGroupBox.cpp \
		sstQtDxf01Convert.cpp
QMAKE_TARGET  = sstQtDxf01Lib_d
DESTDIR       = ../libs/
TARGET        = libsstQtDxf01Lib_d.a


first: all
####### Build rules

staticlib: ../libs/$(TARGET)

../libs/libsstQtDxf01Lib_d.a:  $(OBJECTS) $(OBJCOMP) 
	@test -d ../libs/ || mkdir -p ../libs/
	-$(DEL_FILE) ../libs/$(TARGET)
	$(AR) $(DESTDIR)$(TARGET) $(OBJECTS)


Makefile: sstQtDxf01Lib.pro /usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-clang/qmake.conf /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/clang.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-clang/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qml_debug.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		sstQtDxf01Lib.pro
	$(QMAKE) -o Makefile sstQtDxf01Lib.pro -spec linux-clang CONFIG+=debug CONFIG+=qml_debug
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/clang.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-clang/qmake.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf:
.qmake.stash:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qml_debug.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf:
sstQtDxf01Lib.pro:
qmake: FORCE
	@$(QMAKE) -o Makefile sstQtDxf01Lib.pro -spec linux-clang CONFIG+=debug CONFIG+=qml_debug

qmake_all: FORCE


all: Makefile ../libs/libsstQtDxf01Lib_d.a

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp $(DISTDIR)/
	$(COPY_FILE) --parents Header/sstQtDxf01Lib.h Header/sstQtDxf01QtTab.h $(DISTDIR)/
	$(COPY_FILE) --parents sstQtDxf01PathStorage.cpp sstQtDxf01TabMdlCircle.cpp sstQtDxf01TabMdlLine.cpp sstQtDxf01TabMdlMText.cpp sstQtDxf01TabMdlPoint.cpp sstQtDxf01TabMdlText.cpp sstQtDxf01TabViewAll.cpp sstQtDxf01TabGroupBox.cpp sstQtDxf01Convert.cpp $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) ../libs/$(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_objc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_objc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_predefs_make_all: moc_predefs.h
compiler_moc_predefs_clean:
	-$(DEL_FILE) moc_predefs.h
moc_predefs.h: /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp
	clang++ -pipe -g -fPIC -std=gnu++11 -dM -E -o moc_predefs.h /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp

compiler_moc_header_make_all: moc_sstQtDxf01Lib.cpp moc_sstQtDxf01QtTab.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_sstQtDxf01Lib.cpp moc_sstQtDxf01QtTab.cpp
moc_sstQtDxf01Lib.cpp: Header/sstQtDxf01Lib.h \
		../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs_color.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sstLibreCAD2Lib/Header/rs_flags.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sst_str01_lib/Header/sstStr01Lib.h \
		../sst_str01_lib/Header/sstStr01FixColWidth.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		Header/sstQtDxf01QtTab.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/uli/Entwicklung/sstQtDxf01Lib/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-clang -I/home/uli/Entwicklung/sstQtDxf01Lib -I/home/uli/Entwicklung/dxflib/src -I/home/uli/Entwicklung/sstLibreCAD2Lib/Header -I/home/uli/Entwicklung/sst_dxf03_lib/Header -I/home/uli/Entwicklung/sstQt01Lib/Header -I/home/uli/Entwicklung/sst_rec04_lib/Header -I/home/uli/Entwicklung/sst_misc01_lib/Header -I/home/uli/Entwicklung/sstMath01Lib/Header -I/home/uli/Entwicklung/sst_str01_lib/Header -I/home/uli/Entwicklung/sstQtDxf01Lib/Header -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/7.3.0 -I/usr/include/x86_64-linux-gnu/c++/7.3.0 -I/usr/include/c++/7.3.0/backward -I/usr/include/clang/6.0.0/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include Header/sstQtDxf01Lib.h -o moc_sstQtDxf01Lib.cpp

moc_sstQtDxf01QtTab.cpp: Header/sstQtDxf01QtTab.h \
		../sst_str01_lib/Header/sstStr01Lib.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/uli/Entwicklung/sstQtDxf01Lib/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-clang -I/home/uli/Entwicklung/sstQtDxf01Lib -I/home/uli/Entwicklung/dxflib/src -I/home/uli/Entwicklung/sstLibreCAD2Lib/Header -I/home/uli/Entwicklung/sst_dxf03_lib/Header -I/home/uli/Entwicklung/sstQt01Lib/Header -I/home/uli/Entwicklung/sst_rec04_lib/Header -I/home/uli/Entwicklung/sst_misc01_lib/Header -I/home/uli/Entwicklung/sstMath01Lib/Header -I/home/uli/Entwicklung/sst_str01_lib/Header -I/home/uli/Entwicklung/sstQtDxf01Lib/Header -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/7.3.0 -I/usr/include/x86_64-linux-gnu/c++/7.3.0 -I/usr/include/c++/7.3.0/backward -I/usr/include/clang/6.0.0/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include Header/sstQtDxf01QtTab.h -o moc_sstQtDxf01QtTab.cpp

compiler_moc_objc_header_make_all:
compiler_moc_objc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_predefs_clean compiler_moc_header_clean 

####### Compile

sstQtDxf01PathStorage.o: sstQtDxf01PathStorage.cpp ../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs_color.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sstLibreCAD2Lib/Header/rs_flags.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sst_str01_lib/Header/sstStr01Lib.h \
		../sst_str01_lib/Header/sstStr01FixColWidth.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		Header/sstQtDxf01QtTab.h \
		Header/sstQtDxf01Lib.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sstQtDxf01PathStorage.o sstQtDxf01PathStorage.cpp

sstQtDxf01TabMdlCircle.o: sstQtDxf01TabMdlCircle.cpp ../sst_str01_lib/Header/sstStr01Lib.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		Header/sstQtDxf01QtTab.h \
		Header/sstQtDxf01Lib.h \
		../sstLibreCAD2Lib/Header/rs_color.h \
		../sstLibreCAD2Lib/Header/rs_flags.h \
		../sst_str01_lib/Header/sstStr01FixColWidth.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sstQtDxf01TabMdlCircle.o sstQtDxf01TabMdlCircle.cpp

sstQtDxf01TabMdlLine.o: sstQtDxf01TabMdlLine.cpp ../sst_str01_lib/Header/sstStr01Lib.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		Header/sstQtDxf01QtTab.h \
		Header/sstQtDxf01Lib.h \
		../sstLibreCAD2Lib/Header/rs_color.h \
		../sstLibreCAD2Lib/Header/rs_flags.h \
		../sst_str01_lib/Header/sstStr01FixColWidth.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sstQtDxf01TabMdlLine.o sstQtDxf01TabMdlLine.cpp

sstQtDxf01TabMdlMText.o: sstQtDxf01TabMdlMText.cpp ../sst_str01_lib/Header/sstStr01Lib.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		Header/sstQtDxf01QtTab.h \
		Header/sstQtDxf01Lib.h \
		../sstLibreCAD2Lib/Header/rs_color.h \
		../sstLibreCAD2Lib/Header/rs_flags.h \
		../sst_str01_lib/Header/sstStr01FixColWidth.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sstQtDxf01TabMdlMText.o sstQtDxf01TabMdlMText.cpp

sstQtDxf01TabMdlPoint.o: sstQtDxf01TabMdlPoint.cpp ../sst_str01_lib/Header/sstStr01Lib.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		Header/sstQtDxf01QtTab.h \
		Header/sstQtDxf01Lib.h \
		../sstLibreCAD2Lib/Header/rs_color.h \
		../sstLibreCAD2Lib/Header/rs_flags.h \
		../sst_str01_lib/Header/sstStr01FixColWidth.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sstQtDxf01TabMdlPoint.o sstQtDxf01TabMdlPoint.cpp

sstQtDxf01TabMdlText.o: sstQtDxf01TabMdlText.cpp ../sst_str01_lib/Header/sstStr01Lib.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		Header/sstQtDxf01QtTab.h \
		Header/sstQtDxf01Lib.h \
		../sstLibreCAD2Lib/Header/rs_color.h \
		../sstLibreCAD2Lib/Header/rs_flags.h \
		../sst_str01_lib/Header/sstStr01FixColWidth.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sstQtDxf01TabMdlText.o sstQtDxf01TabMdlText.cpp

sstQtDxf01TabViewAll.o: sstQtDxf01TabViewAll.cpp ../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sst_str01_lib/Header/sstStr01Lib.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		Header/sstQtDxf01QtTab.h \
		Header/sstQtDxf01Lib.h \
		../sstLibreCAD2Lib/Header/rs_color.h \
		../sstLibreCAD2Lib/Header/rs_flags.h \
		../sst_str01_lib/Header/sstStr01FixColWidth.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sstQtDxf01TabViewAll.o sstQtDxf01TabViewAll.cpp

sstQtDxf01TabGroupBox.o: sstQtDxf01TabGroupBox.cpp ../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs_color.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sstLibreCAD2Lib/Header/rs_flags.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sst_str01_lib/Header/sstStr01Lib.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		Header/sstQtDxf01QtTab.h \
		Header/sstQtDxf01Lib.h \
		../sst_str01_lib/Header/sstStr01FixColWidth.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sstQtDxf01TabGroupBox.o sstQtDxf01TabGroupBox.cpp

sstQtDxf01Convert.o: sstQtDxf01Convert.cpp ../dxflib/src/dl_dxf.h \
		../dxflib/src/dl_global.h \
		../dxflib/src/dl_attributes.h \
		../dxflib/src/dl_codes.h \
		../dxflib/src/dl_entities.h \
		../dxflib/src/dl_writer_ascii.h \
		../dxflib/src/dl_writer.h \
		../dxflib/src/dl_creationadapter.h \
		../dxflib/src/dl_creationinterface.h \
		../dxflib/src/dl_extrusion.h \
		../sstLibreCAD2Lib/Header/rs_color.h \
		../sstLibreCAD2Lib/Header/rs.h \
		../sstLibreCAD2Lib/Header/rs_flags.h \
		../sstLibreCAD2Lib/Header/rs_vector.h \
		../sst_str01_lib/Header/sstStr01Lib.h \
		../sst_str01_lib/Header/sstStr01FixColWidth.h \
		../sstMath01Lib/Header/sstMath01Lib.h \
		../sst_misc01_lib/Header/sstMisc01Lib.h \
		../sst_rec04_lib/Header/sstRec04Lib.h \
		../sstQt01Lib/Header/sstQt01Lib.h \
		../sst_dxf03_lib/Header/sstDxf03Lib.h \
		Header/sstQtDxf01QtTab.h \
		Header/sstQtDxf01Lib.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sstQtDxf01Convert.o sstQtDxf01Convert.cpp

moc_sstQtDxf01Lib.o: moc_sstQtDxf01Lib.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_sstQtDxf01Lib.o moc_sstQtDxf01Lib.cpp

moc_sstQtDxf01QtTab.o: moc_sstQtDxf01QtTab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_sstQtDxf01QtTab.o moc_sstQtDxf01QtTab.cpp

####### Install

install_target: first FORCE
	@test -d $(INSTALL_ROOT)/usr/lib || mkdir -p $(INSTALL_ROOT)/usr/lib
	-$(QINSTALL) ../libs/$(TARGET) $(INSTALL_ROOT)/usr/lib/$(TARGET)

uninstall_target: FORCE
	-$(DEL_FILE) $(INSTALL_ROOT)/usr/lib/$(TARGET)
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/lib/ 


install: install_target  FORCE

uninstall: uninstall_target  FORCE

FORCE:

