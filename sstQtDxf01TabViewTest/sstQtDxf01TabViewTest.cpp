/**********************************************************************
 *
 * sstQt01Lib - sst Qt library
 * Hosted on github
 *
 * Copyright (C) 2016 Uli Rehr
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/
// sstQtDxf01TabViewTest.cpp   24.09.18  Re.   24.09.18  Re.
//
// This testtool combines map and table widget with refreshing in both direction
// when editing qt painter path data.


#include <string>

#include <QApplication>
#include <QtWidgets>
#include <QTextBrowser>
#include <QLabel>

#include <list>
#include <dl_dxf.h>
#include <dl_creationadapter.h>
#include <rs_vector.h>

#include <sstStr01Lib.h>
#include <sstMath01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstQt01Lib.h>
#include <sstDxf03Lib.h>
#include <sstQtDxf01QtTab.h>
#include <sstQtDxf01Lib.h>

#include "sstQtDxf01TabViewTest.h"

int main(int argc, char *argv[])
{
    // Q_INIT_RESOURCE(basicdrawing);

  if (argc != 2) return 0;

  QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}
