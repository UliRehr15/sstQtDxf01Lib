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
// window.h   24.09.18  Re.   24.09.18  Re.

#ifndef SST_WINDOW_H
#define SST_WINDOW_H

#include <string>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstQt01Lib.h>

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;
QT_END_NAMESPACE
class sstQt01TestPaintWidgetCls;

//! [0]
class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();

private slots:
    void shapeChanged();
    void penChanged();
    void brushChanged();

private:
    sstQt01TestPaintWidgetCls *sstQt01TestPaintWidgetCls1;
    sstQt01TestPaintWidgetCls *sstQt01TestPaintWidgetCls2;

    sstQt01PathTabViewCls *poPathTabWidget;

    sstQt01PathPaintWidgetCls *poPathMapWidget;

    sstMisc01PrtFilCls *oPrt;
    sstQt01PathStorageCls   *poPathTabStorage;     // sst Painter Path Table storage
    sstQt01PathStoreViewCls *poPathViewStorage;  // sst Painter Path Map View storage

};
//! [0]

#endif // WINDOW_H
