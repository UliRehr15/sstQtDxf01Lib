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
// sstQtDxf01TabViewTest.h   24.09.18  Re.   24.09.18  Re.
//
// Testframe for parallel using of
// Class DxfDbTableViewEditWidget
// Class DxfDbMapViewEditWidget
//

#ifndef SST_QT_DXF01_TABVIEWTEST_HEADER
#define SST_QT_DXF01_TABVIEWTEST_HEADER

#include <string>

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

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;
QT_END_NAMESPACE
class sstQt01TestPaintWidgetCls;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();

private slots:
//    void shapeChanged();
//    void penChanged();
//    void brushChanged();

private:
    sstQtDxf01TabGroupBoxCls  *poTabGroupBoxWidget;
    sstQt01PathPaintWidgetCls *poPathMapWidget;
    sstMisc01PrtFilCls        *poPrt;
    sstDxf03DbCls             *poDxfDb;              /**< sst dxf database */
    sstQt01PathStoreViewCls   *poPathViewStorage;    // sst Painter Path Map View storage
    sstQtDxf01PathConvertCls  *poDxfPathConvert;     // object to convert from dxf to painterpath and back
    std::string                oDxfNamStr;
};

#endif // WINDOW_H
