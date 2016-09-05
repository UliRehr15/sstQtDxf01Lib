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
// sortingbox.cpp    14.08.16  Re.    14.08.16  Re.

#include <QtWidgets>

#include <stdlib.h>
#include <assert.h>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstQt01Lib.h>

#include "sstQtDxf01LibTest.h"
#include "sortingbox.h"

//=============================================================================
SortingBox::SortingBox()
{
  sstMisc01AscFilCls oPainterCsvFile;
  sstStr01Cls oCsvCnvt;
  sstQt01PathElementCsvCls oShapeItemCsv;

  int iStat = 0;

  setMouseTracking(true);
    setBackgroundRole(QPalette::Base);

    itemInMotion = 0;

    newCircleButton = createToolButton(tr("New Circle"),
                                       QIcon(":/images/circle.png"),
                                       SLOT(createNewCircle()));

    newSquareButton = createToolButton(tr("New Square"),
                                       QIcon(":/images/square.png"),
                                       SLOT(createNewSquare()));

    newTriangleButton = createToolButton(tr("New Triangle"),
                                         QIcon(":/images/triangle.png"),
                                         SLOT(createNewTriangle()));

    //=============================================================================
    // Create item templates
    circlePath.addEllipse(QRect(0, 0, 100, 100));
    squarePath.addRect(QRect(0, 0, 100, 100));

    qreal x = trianglePath.currentPosition().x();
    qreal y = trianglePath.currentPosition().y();
    trianglePath.moveTo(x + 120 / 2, y);
    trianglePath.lineTo(0, 100);
    trianglePath.lineTo(120, 100);
    trianglePath.lineTo(x + 120 / 2, y);

    setWindowTitle(tr("Tool Tips"));
    resize(500, 300);

    this->oPathStorage = new (sstQt01PathStorageCls);

    iStat = this->oPathStorage->LoadAllPathFromFile(0,"Paint.csv");
    // assert(iStat == 0);

    if (iStat < 0)
    {
      // create square, triangle and circle item from templates and add to list
      iStat = this->ItemsCreate(0);
    }
    else
    {
      // read items from file into item list
      iStat = this->ItemsLoadFromFile3( 0);
      assert(iStat <= 0);
    }

    delete (this->oPathStorage);
    this->oPathStorage = NULL;

}
//=============================================================================
SortingBox::~SortingBox()
{

  this->oPathStorage = new (sstQt01PathStorageCls);

  QPoint myPoint;
  foreach (ShapeItem shapeItem, shapeItems)
  {
      myPoint = shapeItem.getPosition();
      QPainterPath oPath = shapeItem.getPath();
      oPath.translate(myPoint.x(), myPoint.y());

      QColor oColor = shapeItem.getColor();

      // Append path object to path storage
      this->oPathStorage->AppendPath(0,oPath,oColor);

  }

  // write whole contents of path storage to csv file
  this->oPathStorage->StoreAllPathToFile(0,"Paint.csv");
  delete (this->oPathStorage);
  this->oPathStorage = NULL;
}
//=============================================================================
bool SortingBox::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
        int index = itemAt(helpEvent->pos());
        if (index != -1) {
            QToolTip::showText(helpEvent->globalPos(), shapeItems[index].getToolTip());
        } else {
            QToolTip::hideText();
            event->ignore();
        }

        return true;
    }
    return QWidget::event(event);
}
//! [6]
//=============================================================================
//! [7]
void SortingBox::resizeEvent(QResizeEvent * /* event */)
{
    int margin = style()->pixelMetric(QStyle::PM_DefaultTopLevelMargin);
    int x = width() - margin;
    int y = height() - margin;

    y = updateButtonGeometry(newCircleButton, x, y);
    y = updateButtonGeometry(newSquareButton, x, y);
    updateButtonGeometry(newTriangleButton, x, y);
}
//! [7]
//=============================================================================
//! [8]
void SortingBox::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    foreach (ShapeItem shapeItem, shapeItems) {
//! [8] //! [9]
        painter.translate(shapeItem.getPosition());
//! [9] //! [10]
        painter.setBrush(shapeItem.getColor());
        painter.drawPath(shapeItem.getPath());
        painter.translate(-shapeItem.getPosition());
    }
}
//! [10]
//=============================================================================
//! [11]
void SortingBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int index = itemAt(event->pos());
        if (index != -1) {
            itemInMotion = &shapeItems[index];
            previousPosition = event->pos();
            shapeItems.move(index, shapeItems.size() - 1);
            update();
        }
    }
}
//! [11]
//=============================================================================
//! [12]
void SortingBox::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && itemInMotion)
        moveItemTo(event->pos());
}
//! [12]
//=============================================================================
//! [13]
void SortingBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && itemInMotion) {
        moveItemTo(event->pos());
        itemInMotion = 0;
    }
}
//! [13]
//=============================================================================
//! [14]
void SortingBox::createNewCircle()
{
    static int count = 1;
    createShapeItem(circlePath, tr("Circle <%1>").arg(++count),
                    randomItemPosition(), randomItemColor());
}
//! [14]
//=============================================================================
//! [15]
void SortingBox::createNewSquare()
{
    static int count = 1;
    createShapeItem(squarePath, tr("Square <%1>").arg(++count),
                    randomItemPosition(), randomItemColor());
}
//! [15]
//=============================================================================
//! [16]
void SortingBox::createNewTriangle()
{
    static int count = 1;
    createShapeItem(trianglePath, tr("Triangle <%1>").arg(++count),
                    randomItemPosition(), randomItemColor());
}
//! [16]
//=============================================================================
//! [17]
int SortingBox::itemAt(const QPoint &pos)
{
    for (int i = shapeItems.size() - 1; i >= 0; --i) {
        const ShapeItem &item = shapeItems[i];
        if (item.getPath().contains(pos - item.getPosition()))
            return i;
    }
    return -1;
}
//! [17]
//=============================================================================
//! [18]
void SortingBox::moveItemTo(const QPoint &pos)
{
    QPoint offset = pos - previousPosition;
    itemInMotion->setPosition(itemInMotion->getPosition() + offset);
//! [18] //! [19]
    previousPosition = pos;
    update();
}
//! [19]
//=============================================================================
//! [20]
int SortingBox::updateButtonGeometry(QToolButton *button, int x, int y)
{
    QSize size = button->sizeHint();
    button->setGeometry(x - size.rwidth(), y - size.rheight(),
                        size.rwidth(), size.rheight());

    return y - size.rheight()
           - style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing);
}
//! [20]
//=============================================================================
//! [21]
void SortingBox::createShapeItem(const QPainterPath &path,
                                 const QString &toolTip, const QPoint &pos,
                                 const QColor &color)
{
    ShapeItem shapeItem;
    shapeItem.setPath(path);
    shapeItem.setToolTip(toolTip);
    shapeItem.setPosition(pos);
    shapeItem.setColor(color);
    shapeItems.append(shapeItem);
    update();

//    QPainterPath oTmpPath = path;
//    oTmpPath.translate(pos.x(),pos.y());

//    this->oPathStorage.AppendPath(0,oTmpPath,color);
}
//! [21]
//=============================================================================
//! [22]
QToolButton *SortingBox::createToolButton(const QString &toolTip,
                                          const QIcon &icon, const char *member)
{
    QToolButton *button = new QToolButton(this);
    button->setToolTip(toolTip);
    button->setIcon(icon);
    button->setIconSize(QSize(32, 32));
    connect(button, SIGNAL(clicked()), this, member);

    return button;
}
//! [22]
//=============================================================================
//! [23]
QPoint SortingBox::initialItemPosition(const QPainterPath &path)
{
  int x = 0;
  int y = 0;
    y = (height() - (int)path.controlPointRect().height()) / 2;
    if (shapeItems.size() == 0)
        x = ((3 * width()) / 2 - (int)path.controlPointRect().width()) / 2;
    else
        x = (width() / shapeItems.size()
             - (int)path.controlPointRect().width()) / 2;

    return QPoint(x, y);
}
//! [23]
//=============================================================================
//! [24]
QPoint SortingBox::randomItemPosition()
{
    return QPoint(qrand() % (width() - 120), qrand() % (height() - 120));
}
//! [24]
//=============================================================================
//! [25]
QColor SortingBox::initialItemColor()
{
    return QColor::fromHsv(((shapeItems.size() + 1) * 85) % 256, 255, 190);
}
//! [25]
//=============================================================================
//! [26]
QColor SortingBox::randomItemColor()
{
    return QColor::fromHsv(qrand() % 256, 255, 190);
}
//! [26]
//=============================================================================
int SortingBox::ItemsLoadFromFile (int iKey, sstMisc01AscFilCls *oPainterCsvFile)
//-----------------------------------------------------------------------------
{
  sstQt01PathElementCsvCls oShapeItemCsv;
  sstRec04Cls oShapeItemRecTable(sizeof(oShapeItemCsv));
  dREC04RECNUMTYP dRecNo = 0;
  dREC04RECNUMTYP dItemStart = 0;
  dREC04RECNUMTYP dItemEnd = 0;
  std::string oErrStr;

  int iRet  = 0;
  int iStat = 0;
  int iStat1 = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;
  std::string oCsvStr;

  // load csv file into sst record table
  iStat1 = oPainterCsvFile->Rd_StrDS1( 0, &oCsvStr);
  while (iStat1 >= 0)
  {
    iStat = oShapeItemCsv.ReadFromCsv( 0, oCsvStr, &oErrStr);
    assert (iStat == 0);

    iStat = oShapeItemRecTable.WritNew(0,&oShapeItemCsv,&dRecNo);

    iStat1 = oPainterCsvFile->Rd_StrDS1(0,&oCsvStr);
  }

  QPoint oPnt(0,0);
  QColor oCol;

  for (dREC04RECNUMTYP ll=1; ll <= oShapeItemRecTable.count();ll++)
  {
    // Read record from table
    oShapeItemRecTable.Read(0,ll,&oShapeItemCsv);

    // if type eq. 0 or end of table
    if(oShapeItemCsv.getIType() == 0 || ll == oShapeItemRecTable.count())
    {
      // new item found in csv
      // calculate start and end of item in table
      dItemStart = dItemEnd+1;

      if (oShapeItemCsv.getIType() == 0) dItemEnd = ll-1;
      else dItemEnd = ll;

      if (dItemEnd > dItemStart)
      {
        oShapeItemRecTable.Read(0,dItemStart+1,&oShapeItemCsv);
        switch (oShapeItemCsv.getIType())
        {
        case 1:
          if((dItemEnd-dItemStart) == 4)
          {  // Square
            QPainterPath squarePathFil;

            oShapeItemRecTable.Read(0,dItemStart,&oShapeItemCsv);
            oCol.setBlue(oShapeItemCsv.getIColB());
            oCol.setGreen(oShapeItemCsv.getIColG());
            oCol.setRed(oShapeItemCsv.getIColR());

            squarePathFil.moveTo(oShapeItemCsv.getIXX(),oShapeItemCsv.getIYY());
            for (dREC04RECNUMTYP kk = dItemStart+1;kk <= dItemEnd; kk++)
            {
              oShapeItemRecTable.Read(0,kk,&oShapeItemCsv);
              squarePathFil.lineTo(oShapeItemCsv.getIXX(),oShapeItemCsv.getIYY());
            }
            createShapeItem(squarePathFil, tr("Square"), oPnt, oCol);

          }
          else
          {  // triangle
            QPainterPath trianglePathFil;
            oShapeItemRecTable.Read(0,dItemStart,&oShapeItemCsv);
            oCol.setBlue(oShapeItemCsv.getIColB());
            oCol.setGreen(oShapeItemCsv.getIColG());
            oCol.setRed(oShapeItemCsv.getIColR());
            trianglePathFil.moveTo(oShapeItemCsv.getIXX(),oShapeItemCsv.getIYY());
            for (dREC04RECNUMTYP kk = dItemStart+1;kk <= dItemEnd; kk++)
            {
              oShapeItemRecTable.Read(0,kk,&oShapeItemCsv);
              trianglePathFil.lineTo(oShapeItemCsv.getIXX(),oShapeItemCsv.getIYY());
            }
            createShapeItem(trianglePathFil, tr("Triangle"), oPnt, oCol);
          }
          break;  // square or triangle
        case 2:  // ARC
        {
          QPainterPath circlePathFil;
          sstQt01PathElementCsvCls oShapeItemCsv2;
          sstQt01PathElementCsvCls oShapeItemCsv3;
          sstQt01PathElementCsvCls oShapeItemCsv4;

          oShapeItemRecTable.Read(0,dItemStart,&oShapeItemCsv);
          oCol.setBlue(oShapeItemCsv.getIColB());
          oCol.setGreen(oShapeItemCsv.getIColG());
          oCol.setRed(oShapeItemCsv.getIColR());
          circlePathFil.moveTo(oShapeItemCsv.getIXX(),oShapeItemCsv.getIYY());

          oShapeItemRecTable.Read(0,dItemStart+1,&oShapeItemCsv2);
          oShapeItemRecTable.Read(0,dItemStart+2,&oShapeItemCsv3);
          oShapeItemRecTable.Read(0,dItemStart+3,&oShapeItemCsv4);
          circlePathFil.cubicTo(oShapeItemCsv2.getIXX(),oShapeItemCsv2.getIYY(),
                                oShapeItemCsv3.getIXX(),oShapeItemCsv3.getIYY(),
                                oShapeItemCsv4.getIXX(),oShapeItemCsv4.getIYY());

          //---

          oShapeItemRecTable.Read(0,dItemStart+4,&oShapeItemCsv2);
          oShapeItemRecTable.Read(0,dItemStart+5,&oShapeItemCsv3);
          oShapeItemRecTable.Read(0,dItemStart+6,&oShapeItemCsv4);
          circlePathFil.cubicTo(oShapeItemCsv2.getIXX(),oShapeItemCsv2.getIYY(),
                                oShapeItemCsv3.getIXX(),oShapeItemCsv3.getIYY(),
                                oShapeItemCsv4.getIXX(),oShapeItemCsv4.getIYY());

          //---

          oShapeItemRecTable.Read(0,dItemStart+7,&oShapeItemCsv2);
          oShapeItemRecTable.Read(0,dItemStart+8,&oShapeItemCsv3);
          oShapeItemRecTable.Read(0,dItemStart+9,&oShapeItemCsv4);
          circlePathFil.cubicTo(oShapeItemCsv2.getIXX(),oShapeItemCsv2.getIYY(),
                                oShapeItemCsv3.getIXX(),oShapeItemCsv3.getIYY(),
                                oShapeItemCsv4.getIXX(),oShapeItemCsv4.getIYY());

          //---

          oShapeItemRecTable.Read(0,dItemStart+10,&oShapeItemCsv2);
          oShapeItemRecTable.Read(0,dItemStart+11,&oShapeItemCsv3);
          oShapeItemRecTable.Read(0,dItemStart+12,&oShapeItemCsv4);
          circlePathFil.cubicTo(oShapeItemCsv2.getIXX(),oShapeItemCsv2.getIYY(),
                                oShapeItemCsv3.getIXX(),oShapeItemCsv3.getIYY(),
                                oShapeItemCsv4.getIXX(),oShapeItemCsv4.getIYY());


          createShapeItem(circlePathFil, tr("Circle"), oPnt, oCol);
        }
          break;
          // arc move to
        default: assert (0); break;
        }
      }
    }
  }

  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int SortingBox::ItemsLoadFromFile2 (int iKey, sstMisc01AscFilCls *oPainterCsvFile)
//-----------------------------------------------------------------------------
{
  sstQt01PathElementCsvCls oShapeItemCsv1;
  sstQt01PathElementCsvCls oShapeItemCsv2;
  sstQt01PathElementCsvCls oShapeItemCsv3;
  sstRec04Cls oShapeItemRecTable(sizeof(oShapeItemCsv1));
  dREC04RECNUMTYP dRecNo = 0;
  // dREC04RECNUMTYP dItemStart = 0;
  // dREC04RECNUMTYP dItemEnd = 0;
  std::string oErrStr;

  int iRet  = 0;
  int iStat = 0;
  int iStat1 = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;
  std::string oCsvStr;

  // load csv file into sst record table
  iStat1 = oPainterCsvFile->Rd_StrDS1( 0, &oCsvStr);
  while (iStat1 >= 0)
  {
    iStat = oShapeItemCsv1.ReadFromCsv( 0, oCsvStr, &oErrStr);
    assert (iStat == 0);

    iStat = oShapeItemRecTable.WritNew(0,&oShapeItemCsv1,&dRecNo);

    iStat1 = oPainterCsvFile->Rd_StrDS1(0,&oCsvStr);
  }

  QPoint oPnt(0,0);
  QColor oCol;
  QPainterPath *poPath;
  poPath = new (QPainterPath);

  // loop over all record in sst table
  for (dREC04RECNUMTYP ll=1; ll <= oShapeItemRecTable.count();ll++)
  {
    // Read record from table
    oShapeItemRecTable.Read(0,ll,&oShapeItemCsv1);
    switch (oShapeItemCsv1.getIType())
    {
    case 0:
    {
      // new path object begins, store actual
      switch (poPath->elementCount())
      {
      case 0:
        break;
      default:
        createShapeItem(*poPath, tr("Circle"), oPnt, oCol);
        break;
      }
      delete poPath;
      poPath = new (QPainterPath);
      oCol.setBlue(oShapeItemCsv1.getIColB());
      oCol.setGreen(oShapeItemCsv1.getIColG());
      oCol.setRed(oShapeItemCsv1.getIColR());
      poPath->moveTo(oShapeItemCsv1.getIXX(),oShapeItemCsv1.getIYY());
    }
      break;
    case 1:
      poPath->lineTo(oShapeItemCsv1.getIXX(),oShapeItemCsv1.getIYY());
      break;
    case 2:
      // Read two Type 3 records and create circle
      oShapeItemRecTable.Read(0,ll+1,&oShapeItemCsv2);
      oShapeItemRecTable.Read(0,ll+2,&oShapeItemCsv3);
      poPath->cubicTo(oShapeItemCsv1.getIXX(),oShapeItemCsv1.getIYY(),
                      oShapeItemCsv2.getIXX(),oShapeItemCsv2.getIYY(),
                      oShapeItemCsv3.getIXX(),oShapeItemCsv3.getIYY());
      ll = ll + 2;
      break;
    case 3:
      assert (0);
      break;
      // arc move to
    default:
      assert (0);
      break;
    }

  }

  // new path object begins, store actual
  switch (poPath->elementCount())
  {
  case 0:
    break;
  default:
    createShapeItem(*poPath, tr("Circle"), oPnt, oCol);
    break;
  }
  delete poPath;

  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int SortingBox::ItemsLoadFromFile3 (int iKey)
//-----------------------------------------------------------------------------
{
//  sstQt01PathElementCsvCls oShapeItemCsv1;
//  sstQt01PathElementCsvCls oShapeItemCsv2;
//  sstQt01PathElementCsvCls oShapeItemCsv3;
//  sstRec04Cls oShapeItemRecTable(sizeof(oShapeItemCsv1));
  // dREC04RECNUMTYP dRecNo = 0;
  QPoint oPnt(0,0);
  // std::string oErrStr;
  QPainterPath *poPath;
  QColor oColor;

  int iRet  = 0;
  int iStat = 0;
  int iStat1 = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  poPath = new (QPainterPath);
  iStat1 = this->oPathStorage->ReadNextPath( 0, poPath, &oColor);

  while (iStat1 >= 0)
  {
    int iElements = poPath->elementCount();
    switch (iElements)
    {
      case 4:
      createShapeItem( *poPath, tr("Triangle"), oPnt, oColor);
      break;
    case 5:
      createShapeItem( *poPath, tr("Square"), oPnt, oColor);
      break;
    case 13:
      createShapeItem( *poPath, tr("Circle"), oPnt, oColor);
      break;
    default:
      assert(0);
      break;
    }

    delete poPath;
    poPath = new (QPainterPath);
    iStat1 = this->oPathStorage->ReadNextPath( 0, poPath, &oColor);
  }

  delete poPath;

  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int SortingBox::ItemsCreate (int iKey) // v  -> For the moment 0
//-----------------------------------------------------------------------------
{
  QColor oColor;
  QPoint oPos;
  int iRet  = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;


//  oPos = initialItemPosition(circlePath);
//  oColor = initialItemColor();
//  QPainterPath oTmpPath = circlePath;
//  oTmpPath.translate(oPos.x(),oPos.y());
//  this->oPathStorage.AppendPath(0,oTmpPath,oColor);
//  createShapeItem(circlePath, tr("Circle"), oPos, oColor);

//  oPos = initialItemPosition(squarePath);
//  oColor = initialItemColor();
//  oTmpPath = squarePath;
//  oTmpPath.translate(oPos.x(),oPos.y());
//  this->oPathStorage.AppendPath(0,oTmpPath,oColor);
//  createShapeItem(squarePath, tr("Square"), oPos, oColor);

//  oPos = initialItemPosition(trianglePath);
//  oColor = initialItemColor();
//  oTmpPath = trianglePath;
//  oTmpPath.translate(oPos.x(),oPos.y());
//  this->oPathStorage.AppendPath(0,oTmpPath,oColor);
//  createShapeItem(trianglePath, tr("Triangle"), oPos , oColor);

  createShapeItem(circlePath, tr("Circle"), initialItemPosition(circlePath),
                  initialItemColor());
  createShapeItem(squarePath, tr("Square"), initialItemPosition(squarePath),
                  initialItemColor());
  createShapeItem(trianglePath, tr("Triangle"),
                  initialItemPosition(trianglePath), initialItemColor());

  // this->oPathStorage.StoreAllPathToFile(0,"paint2.csv");

  return iRet;
}
//=============================================================================
