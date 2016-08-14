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

#include <QtWidgets>

#include <stdlib.h>
#include <assert.h>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>

#include "sortingbox.h"

SortingBox::SortingBox()
{
  sstMisc01AscFilCls oPainterCsvFile;
  sstStr01Cls oCsvCnvt;
  sstQtDxf01ShapeItemCsvCls oShapeItemCsv;
  std::string oErrStr;

  // int iVal = 0;
  int iStat = 0;

  iStat = oPainterCsvFile.fopenRd(0,"Paint.csv");
  std::string oCsvStr;
  int iStat1 = oPainterCsvFile.Rd_StrDS1(0,&oCsvStr);
  while (iStat1 >= 0)
  {
    iStat = oShapeItemCsv.ReadFromCsv( 0, oCsvStr, &oErrStr);
    assert (iStat == 0);
    switch (oShapeItemCsv.getIType())
    {
    case 0: break;  // New element
    case 1: break;  // Polygon point
    case 2: break;  // Begin ARC
    case 3: break;  // ARC Element 1 or 2
    default: assert (0); break;
    }

    iStat1 = oPainterCsvFile.Rd_StrDS1(0,&oCsvStr);
  }
  oPainterCsvFile.fcloseFil(0);
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

    createShapeItem(circlePath, tr("Circle"), initialItemPosition(circlePath),
                    initialItemColor());
    createShapeItem(squarePath, tr("Square"), initialItemPosition(squarePath),
                    initialItemColor());
    createShapeItem(trianglePath, tr("Triangle"),
                    initialItemPosition(trianglePath), initialItemColor());
}
SortingBox::~SortingBox()
{
  sstMisc01AscFilCls oPainterCsvFile;
  int iStat = 0;
  std::string oPathStr;
  sstStr01Cls oCsvCnvt;
  iStat = oPainterCsvFile.fopenWr(0,"Paint.csv");
  assert(iStat == 0);
  // oPainterCsvFile.wr_txt(0,(char*) "Test");

  // QPainter painter(this);
  QPoint myPoint;
  // painter.setRenderHint(QPainter::Antialiasing);
  foreach (ShapeItem shapeItem, shapeItems)
  {
      myPoint = shapeItem.getPosition();
      QPainterPath oPath = shapeItem.getPath();
      QColor oColor = shapeItem.getColor();
      int iEleNum = oPath.elementCount();
      // oPathStr.clear();
      // oPainterCsvFile.Wr_StrDS1(1,&oPathStr);
      for (int ii =1; ii <= iEleNum; ii++)
      {
        QPainterPath::Element oElement;
        oElement = oPath.elementAt(ii-1);
        oPathStr.clear();
        int iColR=0, iColG = 0, iColB = 0, iColT = 0;
        oColor.getRgb(&iColR,&iColG,&iColB,&iColT);
        iStat = oCsvCnvt.Csv_Int2_2String(0,oElement.type, &oPathStr);
        iStat = oCsvCnvt.Csv_Int2_2String(0,(oElement.x + myPoint.rx()), &oPathStr);
        iStat = oCsvCnvt.Csv_Int2_2String(0,(oElement.y + myPoint.ry()), &oPathStr);
        iStat = oCsvCnvt.Csv_Int2_2String(0,iColR, &oPathStr);
        iStat = oCsvCnvt.Csv_Int2_2String(0,iColG, &oPathStr);
        iStat = oCsvCnvt.Csv_Int2_2String(0,iColB, &oPathStr);
        oPainterCsvFile.Wr_StrDS1(0,&oPathStr);
      }
//      oPathStr.clear();
//      iStat = oCsvCnvt.Csv_Int2_2String(0,myPoint.rx(), &oPathStr);
//      iStat = oCsvCnvt.Csv_Int2_2String(0,myPoint.ry(), &oPathStr);
//      oPainterCsvFile.Wr_StrDS1(0,&oPathStr);
      // iStat = 1;
  }
  oPainterCsvFile.fcloseFil(0);

}

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

//! [12]
void SortingBox::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && itemInMotion)
        moveItemTo(event->pos());
}
//! [12]

//! [13]
void SortingBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && itemInMotion) {
        moveItemTo(event->pos());
        itemInMotion = 0;
    }
}
//! [13]

//! [14]
void SortingBox::createNewCircle()
{
    static int count = 1;
    createShapeItem(circlePath, tr("Circle <%1>").arg(++count),
                    randomItemPosition(), randomItemColor());
}
//! [14]

//! [15]
void SortingBox::createNewSquare()
{
    static int count = 1;
    createShapeItem(squarePath, tr("Square <%1>").arg(++count),
                    randomItemPosition(), randomItemColor());
}
//! [15]

//! [16]
void SortingBox::createNewTriangle()
{
    static int count = 1;
    createShapeItem(trianglePath, tr("Triangle <%1>").arg(++count),
                    randomItemPosition(), randomItemColor());
}
//! [16]

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
}
//! [21]

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

//! [23]
QPoint SortingBox::initialItemPosition(const QPainterPath &path)
{
    int x;
    int y = (height() - (int)path.controlPointRect().height()) / 2;
    if (shapeItems.size() == 0)
        x = ((3 * width()) / 2 - (int)path.controlPointRect().width()) / 2;
    else
        x = (width() / shapeItems.size()
             - (int)path.controlPointRect().width()) / 2;

    return QPoint(x, y);
}
//! [23]

//! [24]
QPoint SortingBox::randomItemPosition()
{
    return QPoint(qrand() % (width() - 120), qrand() % (height() - 120));
}
//! [24]

//! [25]
QColor SortingBox::initialItemColor()
{
    return QColor::fromHsv(((shapeItems.size() + 1) * 85) % 256, 255, 190);
}
//! [25]

//! [26]
QColor SortingBox::randomItemColor()
{
    return QColor::fromHsv(qrand() % 256, 255, 190);
}
//! [26]
