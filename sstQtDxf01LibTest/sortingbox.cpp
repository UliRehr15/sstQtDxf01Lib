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

#include <list>

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
#include "sortingbox.h"

//=============================================================================
SortingBox::SortingBox()
{

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


    this->oPrt = new (sstMisc01PrtFilCls);
    this->oPrt->SST_PrtAuf(1,(char*) "sstQtDxf01LibTest.log");

    this->oPathStorage = new (sstQt01PathStorageCls);

    // Create new sstDxf Database
    // sstDxf03DbCls oDxfDb(this->oPrt);

    // store whole dxf file into sst Dxf Database
    // iStat = oDxfDb.ReadAllFromDxf(0,"sstQtDxf01LibTest.dxf");
    // assert(iStat == 0);
    // iStat = -1;

    // sstQtDxf01LibPathCls oDxfDbPath(&oDxfDb);
    sstQtDxf01PathStorageCls oDxfDbPath;

    if (iStat < 0)
    {
      // create square, triangle and circle item from templates and add to list
      iStat = this->ItemsCreate(0);
    }
    else
    {
      // read items from sst table into path item list
      // iStat = this->ItemsLoadFromDxfDb( 0, &oDxfDbPath);
      iStat = this->ItemsLoadFromDxfDb( 0, &oDxfDbPath);
      assert(iStat <= 0);
    }

    // iStat = oDxfDb.WritAll2Csv(0,"Test4.dxf");
    // assert(iStat == 0);

    delete (this->oPathStorage);
    this->oPathStorage = NULL;

    this->oPrt->SST_PrtZu(1);
    delete (this->oPrt);
    this->oPrt = NULL;

}
//=============================================================================
SortingBox::~SortingBox()
{

  this->oPathStorage = new (sstQt01PathStorageCls);
  sstQtDxf01PathStorageCls *poPath2Dxf = new (sstQtDxf01PathStorageCls);

  QPoint myPoint;
  foreach (sstQt01ShapeItem shapeItem, shapeItems)
  {
      myPoint = shapeItem.getPosition();
      QPainterPath oPath = shapeItem.getPath();
      oPath.translate(myPoint.x(), myPoint.y());

      QColor oColor = shapeItem.getColor();

      // Append path object to path storage
      // this->oPathStorage->AppendPath(0,oPath,oColor);

      // Write one path into dxf database
      poPath2Dxf->WrtPath2Dxf( 0, oPath, oColor);

  }

  // write all path to csv
  // this->oPathStorage->StoreAllPathToFile(0,"Test1.csv");

  // write dxf database to csv
  // poPath2Dxf->poDxfDb->WritAll2Csv( 0,"Test1.dxf");

  // write dxf database to csv files
  // int iStat = poPath2Dxf->WriteDxfDbToCsv( 0, "Test1.dxf");
  // assert(iStat == 0);

  // write whole contents of path storage to csv file
  delete (this->oPathStorage);
  this->oPathStorage = NULL;

  delete (poPath2Dxf);
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
//=============================================================================
void SortingBox::resizeEvent(QResizeEvent * /* event */)
{
    int margin = style()->pixelMetric(QStyle::PM_DefaultTopLevelMargin);
    int x = width() - margin;
    int y = height() - margin;

    y = updateButtonGeometry(newCircleButton, x, y);
    y = updateButtonGeometry(newSquareButton, x, y);
    updateButtonGeometry(newTriangleButton, x, y);
}
//=============================================================================
void SortingBox::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    foreach (sstQt01ShapeItem shapeItem, shapeItems) {
        painter.translate(shapeItem.getPosition());
        painter.setBrush(shapeItem.getColor());
        painter.drawPath(shapeItem.getPath());
        painter.translate(-shapeItem.getPosition());
    }
}
//=============================================================================
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
//=============================================================================
void SortingBox::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && itemInMotion)
        moveItemTo(event->pos());
}
//=============================================================================
void SortingBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && itemInMotion) {
        moveItemTo(event->pos());
        itemInMotion = 0;
    }
}
//=============================================================================
void SortingBox::createNewCircle()
{
    static int count = 1;
    createShapeItem(circlePath, tr("Circle <%1>").arg(++count),
                    randomItemPosition(), randomItemColor());
}
//=============================================================================
void SortingBox::createNewSquare()
{
    static int count = 1;
    createShapeItem(squarePath, tr("Square <%1>").arg(++count),
                    randomItemPosition(), randomItemColor());
}
//=============================================================================
void SortingBox::createNewTriangle()
{
    static int count = 1;
    createShapeItem(trianglePath, tr("Triangle <%1>").arg(++count),
                    randomItemPosition(), randomItemColor());
}
//=============================================================================
int SortingBox::itemAt(const QPoint &pos)
{
    for (int i = shapeItems.size() - 1; i >= 0; --i) {
        const sstQt01ShapeItem &item = shapeItems[i];
        if (item.getPath().contains(pos - item.getPosition()))
            return i;
    }
    return -1;
}
//=============================================================================
void SortingBox::moveItemTo(const QPoint &pos)
{
    QPoint offset = pos - previousPosition;
    itemInMotion->setPosition(itemInMotion->getPosition() + offset);
    previousPosition = pos;
    update();
}
//=============================================================================
int SortingBox::updateButtonGeometry(QToolButton *button, int x, int y)
{
    QSize size = button->sizeHint();
    button->setGeometry(x - size.rwidth(), y - size.rheight(),
                        size.rwidth(), size.rheight());

    return y - size.rheight()
           - style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing);
}
//=============================================================================
void SortingBox::createShapeItem(const QPainterPath &path,
                                 const QString &toolTip, const QPoint &pos,
                                 const QColor &color)
{
    sstQt01ShapeItem shapeItem;
    shapeItem.setPath(path);
    shapeItem.setToolTip(toolTip);
    shapeItem.setPosition(pos);
    shapeItem.setColor(color);
    shapeItems.append(shapeItem);
    update();

}
//=============================================================================
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
//=============================================================================
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
//=============================================================================
QPoint SortingBox::randomItemPosition()
{
    return QPoint(qrand() % (width() - 120), qrand() % (height() - 120));
}
//=============================================================================
QColor SortingBox::initialItemColor()
{
    return QColor::fromHsv(((shapeItems.size() + 1) * 85) % 256, 255, 190);
}
//=============================================================================
QColor SortingBox::randomItemColor()
{
    return QColor::fromHsv(qrand() % 256, 255, 190);
}
//=============================================================================
int SortingBox::ItemsLoadFromFile (int iKey)
//-----------------------------------------------------------------------------
{
  QPoint oPnt(0,0);
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
// int SortingBox::ItemsLoadFromDxfDb (int iKey, sstQtDxf01LibPathCls *poDxfPath)
int SortingBox::ItemsLoadFromDxfDb (int iKey, sstQtDxf01PathStorageCls *poDxfPath)
//-----------------------------------------------------------------------------
{
  QPoint oPnt(0,0);
  QPainterPath *poPath;
  QColor oColor;


  int iRet  = 0;
  int iStat = 0;
  int iStat1 = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecNo = 1;
  poPath = new (QPainterPath);

  // read next path from dxf database
  // iStat1 = poDxfPath->ReadNextPath(0,&dMainRecNo, poPath, &oColor);
  iStat1 = poDxfPath->ReadNextPath( 0, &dMainRecNo, poPath, &oColor);

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
    // iStat1 = poDxfPath->ReadNextPath(0,&dMainRecNo, poPath, &oColor);
    iStat1 = poDxfPath->ReadNextPath(0, &dMainRecNo, poPath, &oColor);
    iStat = 0;
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

  createShapeItem(circlePath, tr("Circle"), initialItemPosition(circlePath),
                  initialItemColor());
  createShapeItem(squarePath, tr("Square"), initialItemPosition(squarePath),
                  initialItemColor());
  createShapeItem(trianglePath, tr("Triangle"),
                  initialItemPosition(trianglePath), initialItemColor());

  return iRet;
}
//=============================================================================
//sstQtDxf01LibPathCls::sstQtDxf01LibPathCls(sstDxf03DbCls *poTmpDxfDb)
//{
//  if (poTmpDxfDb == NULL) assert(0);
//  this->poDxfDb = poTmpDxfDb;
//}
//=============================================================================
//int sstQtDxf01LibPathCls::ReadNextPath(int iKey,dREC04RECNUMTYP *dMainRecNo, QPainterPath *poPath, QColor *poColor)
//{
//  sstQtDxf01PathStorageCls oPathHandler;

//  int iRet  = 0;
//  int iStat = 0;
//  //-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;

//  dREC04RECNUMTYP dMainRecs =  this->poDxfDb->MainCount();
//  if (dMainRecs <= 0) return -2;  // Dxf Database is empty

//  if (*dMainRecNo >= dMainRecs) return -3;  // Read position after end of table?

//    RS2::EntityType eEntityType = RS2::EntityUnknown;
//    dREC04RECNUMTYP dEntRecNo = 0;
//    iStat = this->poDxfDb->ReadMainTable(0,*dMainRecNo,&eEntityType,&dEntRecNo);
//    switch(eEntityType)
//    {
//      case RS2::EntityHatch:
//    {
//      DL_HatchData oDLHatch;
//      DL_Attributes oDLAttributes;
//        iStat = this->poDxfDb->ReadHatch(0,dEntRecNo,&oDLHatch,&oDLAttributes);
//        if (oDLHatch.numLoops <= 0) assert (0);

//        int iColor = oDLAttributes.getColor();

//        // transform dxf color to QColor
//        *poColor = oPathHandler.numberToColor(iColor);

//        *dMainRecNo = *dMainRecNo + 1;
//        iStat = this->poDxfDb->ReadMainTable(0,*dMainRecNo,&eEntityType,&dEntRecNo);
//        if (eEntityType != RS2::EntityHatchLoop) assert (0);
//        DL_HatchLoopData oDLHatchLoop;
//        iStat = this->poDxfDb->ReadHatchLoop( 0, dEntRecNo, &oDLHatchLoop);
//        if (oDLHatchLoop.numEdges <= 0) assert(0);
//        for (int dd = 1; dd <= oDLHatchLoop.numEdges; dd++)
//        {
//          *dMainRecNo = *dMainRecNo + 1;
//          iStat = this->poDxfDb->ReadMainTable(0,*dMainRecNo,&eEntityType,&dEntRecNo);
//          if (eEntityType != RS2::EntityHatchEdge) assert (0);
//          DL_HatchEdgeData oDLHatchEdge;
//          iStat = this->poDxfDb->ReadHatchEdge( 0, dEntRecNo, &oDLHatchEdge);
//          assert(iStat >= 0);
//          // transform coordinates of HatchEdge from would to device coordinate system
//          oPathHandler.Transform_WC_DC(0,&oDLHatchEdge);
//          switch (oDLHatchEdge.type)
//          {
//            case 1:
//            if (dd == 1)
//            {
//              poPath->moveTo(oDLHatchEdge.x1,oDLHatchEdge.y1);
//              poPath->lineTo(oDLHatchEdge.x2,oDLHatchEdge.y2);
//            }  // End first edge
//            // polygon element
//            else
//              poPath->lineTo(oDLHatchEdge.x2,oDLHatchEdge.y2);
//            break;
//          case 2:  // Circle
//          {
//            QPointF center;
//            center.setX(oDLHatchEdge.cx);
//            center.setY(oDLHatchEdge.cy);
//            poPath->addEllipse(center,oDLHatchEdge.radius,oDLHatchEdge.radius);
//          }
//            break;
//          default:
//            break;
//          }  // end switch edge type
//        }  // end all hatch loops
//    }  // end process type hatch
//        break;
//    case RS2::EntityCircle:
//    {
//      DL_CircleData oDLCircle(0,0,0,0);
//      DL_Attributes oDLAttributes;
//      iStat = this->poDxfDb->ReadCircle( 0, dEntRecNo, &oDLCircle, &oDLAttributes);
//      assert(iStat == 0);
//      oPathHandler.Transform_WC_DC(0,&oDLCircle.cx,&oDLCircle.cy);
//      QPointF center;
//      center.setX(oDLCircle.cx);
//      center.setY(oDLCircle.cy);
//      poPath->addEllipse(center,oDLCircle.radius,oDLCircle.radius);
//    } // end process type circle
//      break;
//    default:
//    {
//      iStat = 0;
//    }  // end process all not defined dxf entity types
//      break;
//    } // end switch dxf entity type

//    *dMainRecNo = *dMainRecNo + 1;

//    // Fatal Errors goes to an assert
//  assert(iRet >= 0);

//  // Small Errors will given back
//  iRet = iStat;

//  return iRet;
//}
//=============================================================================
//int sstQt01PathStorageCls::ReadNextPath(int iKey, QPainterPath *oTmpPath, QColor *oTmpColor)
//{
//  sstQt01PathElementCsvCls oShapeItemCsv1;
//  sstQt01PathElementCsvCls oShapeItemCsv2;
//  sstQt01PathElementCsvCls oShapeItemCsv3;
//  //-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;

//  // PainterPath object should be empty
//  if (oTmpPath->elementCount() != 0) return -2;

//  // stop reading at end of table
//  if (this->dActualReadPos >= this->poShapeItemRecTable->count()) return -3;

//  // first element had to be type 0 start path element
//  this->poShapeItemRecTable->Read( 0, this->dActualReadPos, &oShapeItemCsv1);
//  if (oShapeItemCsv1.getIType() != 0) return -4;

//  oTmpColor->setBlue(oShapeItemCsv1.getIColB());
//  oTmpColor->setGreen(oShapeItemCsv1.getIColG());
//  oTmpColor->setRed(oShapeItemCsv1.getIColR());

//  oTmpPath->moveTo(oShapeItemCsv1.getIXX(),oShapeItemCsv1.getIYY());

//  // loop over all record in sst table
//  for (dREC04RECNUMTYP ll=this->dActualReadPos+1; ll <= this->poShapeItemRecTable->count();ll++)
//  {
//    // Read record from table
//    this->poShapeItemRecTable->Read( 0, ll, &oShapeItemCsv1);
//    switch (oShapeItemCsv1.getIType())
//    {
//    case 0:
//    {
//      // next path object found, stop here
//      this->dActualReadPos = ll;
//      return 0;
//    }
//      break;
//    case 1:
//      // polygon element
//      oTmpPath->lineTo(oShapeItemCsv1.getIXX(),oShapeItemCsv1.getIYY());
//      break;
//    case 2:
//      // Read additional two Type 3 records and create 1/4 circle
//      this->poShapeItemRecTable->Read( 0, ll+1, &oShapeItemCsv2);
//      this->poShapeItemRecTable->Read( 0, ll+2, &oShapeItemCsv3);
//      oTmpPath->cubicTo(oShapeItemCsv1.getIXX(),oShapeItemCsv1.getIYY(),
//                        oShapeItemCsv2.getIXX(),oShapeItemCsv2.getIYY(),
//                        oShapeItemCsv3.getIXX(),oShapeItemCsv3.getIYY());
//      ll = ll + 2;
//      break;
//    case 3:
//      assert (0);
//      break;
//    default:
//      assert (0);
//      break;
//    }

//  }

//  // last path object in file ended here
//  this->dActualReadPos = this->poShapeItemRecTable->count() + 1;

//  return 0;
//}
////=============================================================================

