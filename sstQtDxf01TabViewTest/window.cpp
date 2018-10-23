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
// window.cpp   23.10.18  Re.   24.09.18  Re.

#include <assert.h>

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

#include "window.h"

//==============================================================================
Window::Window()
{
  int iStat = 0;
  std::string oDxfNamStr = "sstQtDxf01LibTest.dxf";

  this->poPrt = new sstMisc01PrtFilCls;
  poPrt->SST_PrtAuf(1,(char*)"sstQtDxf01TabViewTest.log");

  // Create new empty sstDxf database
  this->poDxfDb = new sstDxf03DbCls(this->poPrt);
  // Load Dxf Data from file
  iStat = this->poDxfDb->ReadAllFromDxf( 0, oDxfNamStr);

  if (iStat < 0)
  {
    this->poPrt->SST_PrtWrtChar(1,(char*)oDxfNamStr.c_str(),(char*)"File not found: ");
    this->poPrt->SST_PrtZu(1);
    assert(0);
  }

  // create sstpainterpath storage for map widget
  this->poPathViewStorage = new sstQt01PathStoreViewCls(this->poPrt);

  // open new Dxf_Path converter object
  this->poDxfPathConvert = new sstQtDxf01PathConvertCls(this->poDxfDb,this->poPathViewStorage, this->poPrt);

  // fill Path Storage from Dxf database
  iStat = poDxfPathConvert->WritAlltoPathStorage( 0);
  assert(iStat == 0);

  // Create GroupBoxWidget with all dxf entity tables
  poTabGroupBoxWidget = new sstQtDxf01TabGroupBoxCls( poPrt, this->poDxfDb);

  // create new map widget with sstpainterpath storage
  poPathMapWidget = new sstQt01PathPaintWidgetCls( poPrt,this->poPathViewStorage);

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(poPathMapWidget, 0, 0, 1, 4);
    mainLayout->addWidget(poTabGroupBoxWidget, 1, 0, 1, 4);

    setLayout(mainLayout);

    setWindowTitle(tr("Basic Drawing"));

    // For refreshing map from table
//    connect(poPathTabWidget, SIGNAL(sstSgnlTabChanged(sstQt01ShapeItem)), poPathMapWidget, SLOT(sstPaintEvent(sstQt01ShapeItem)));
//    // for refreshing table from map
//    connect(poPathMapWidget, SIGNAL(sstPathMoveReleaseSgnl(sstQt01ShapeItem)), poPathTabWidget, SLOT(sstSlotUpdateTab(sstQt01ShapeItem)));

//    connect(poPathMapWidget,SIGNAL(sstSgnlBeginInsertRows(int,int)),poPathTabWidget,SLOT(sstSlotBeginInsertRows(int,int)));
//    connect(poPathMapWidget,SIGNAL(sstSgnlEndInsertRows()),poPathTabWidget,SLOT(sstSlotEndInsertRows()));

//    connect(poPathMapWidget,SIGNAL(sstSgnlBeginRemoveRows(int,int)),poPathTabWidget,SLOT(sstSlotBeginRemoveRows(int,int)));
//    connect(poPathMapWidget,SIGNAL(sstSgnlEndRemoveRows()),poPathTabWidget,SLOT(sstSlotEndRemoveRows()));
}
//==============================================================================
Window::~Window()
{
  int iStat = 0;
  // write all path from intern path storage to inter sst sstDxf database
  iStat = poDxfPathConvert->WriteAllPath2Dxf(0);
  assert(iStat == 0);

  // Write intern sst dxf database to dxf file
  iStat = poDxfPathConvert->WriteAll2Dxf(0,"sstQtDxf01LibTest.dxf");
  assert(iStat == 0);

  delete poDxfPathConvert;
  delete this->poPathViewStorage;
  delete this->poPathMapWidget;
  delete   this->poDxfDb;
  this->poPrt->SST_PrtZu(1);
  delete this->poPrt;
}
//==============================================================================
