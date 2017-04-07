/**********************************************************************
 *
 * sstQtDxf01Lib - sst qt dxf library
 * Hosted on github
 *
 * Copyright (C) 2016 Uli Rehr
 *
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation and appearing in the file gpl-2.0.txt included in the
 * packaging of this file.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * This copyright notice MUST APPEAR in all copies of the script!
 *
**********************************************************************/
// sstQtDxf01LibTest.cpp    14.08.16  Re.    14.08.16  Re.

#ifndef SORTINGBOX_H
#define SORTINGBOX_H

#include <QWidget>

#include <dl_dxf.h>
#include <dl_creationadapter.h>

#include <rs_vector.h>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstDxf03Lib.h>
#include <sstQt01Lib.h>
#include <sstQtDxf01Lib.h>

#include "sstQtDxf01LibTest.h"
// #include "shapeitem.h"

QT_BEGIN_NAMESPACE
class QAction;
class QPoint;
class QToolButton;
QT_END_NAMESPACE

class sstQtDxf01LibPathCls;

class SortingBox : public QWidget
{
    Q_OBJECT

public:
  SortingBox();
  ~SortingBox();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void createNewCircle();
    void createNewSquare();
    void createNewTriangle();

private:
    int updateButtonGeometry(QToolButton *button, int x, int y);
    void createShapeItem(const QPainterPath &path, const QString &toolTip,
                         const QPoint &pos, const QColor &color);
    int itemAt(const QPoint &pos);
    void moveItemTo(const QPoint &pos);
    int ItemsLoadFromFile (int iKey);
    // int ItemsLoadFromDxfDb (int iKey,sstQtDxf01LibPathCls *poDxfPath);
    int ItemsLoadFromDxfDb (int iKey,sstQtDxf01PathStorageCls *poDxfPath);
    int ItemsCreate (int iKey);
    QPoint initialItemPosition(const QPainterPath &path);
    QPoint randomItemPosition();
    QColor initialItemColor();
    QColor randomItemColor();
    QToolButton *createToolButton(const QString &toolTip, const QIcon &icon,
                                  const char *member);

    QList<sstQt01ShapeItem> shapeItems;
    QPainterPath circlePath;
    QPainterPath squarePath;
    QPainterPath trianglePath;

    QPoint previousPosition;
    sstQt01ShapeItem *itemInMotion;

    QToolButton *newCircleButton;
    QToolButton *newSquareButton;
    QToolButton *newTriangleButton;
    sstQt01PathStorageCls *oPathStorage;
    sstMisc01PrtFilCls *oPrt;
};

//==============================================================================
/**
* @brief // sstQtDxf01LibPathCls <BR>
*
* template for sst base class <BR>
*
* Changed: 09.07.15  Re.
*
* @ingroup sstTemplateLib
*
* @author Re.
*
* @date 09.07.15
*/
// ----------------------------------------------------------------------------
//class sstQtDxf01LibPathCls
//{
//  public:   // Public functions
//  sstQtDxf01LibPathCls(sstDxf03DbCls *poDxfDb);  // Constructor
//    //~sstTestBaseCls();  // Destructor
//     //==============================================================================
//     /**
//     * @brief // read object from dxf db into PainterPath <BR>
//     * iStat = oPathDxfDbConvert.ReadNextPath ( iKey, &dMainRecNo, &poPath, &poColor);
//     *
//     * @param iKey [in] For the moment 0
//     * @param dMainRecNo [in out] actual record number in dxf-db main table
//     * @param poPath     [in out] return filled path
//     * @param poColor    [in out] return color of path
//     *
//     * @return Errorstate
//     *
//     * @retval   = 0: OK
//     * @retval   < 0: Unspecified Error
//     */
//     // ----------------------------------------------------------------------------
//  int ReadNextPath(int iKey,dREC04RECNUMTYP *dMainRecNo, QPainterPath *poPath,  QColor *poColor);
//// ----------------------------------------------------------------------------
//  private:  // Private functions
//  sstDxf03DbCls *poDxfDb;  /**< Adress of Dxf Database */
//};
//-----------------------------------------------------------------------------


#endif
