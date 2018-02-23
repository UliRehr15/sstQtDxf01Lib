/**********************************************************************
 *
 * sstQtDxf01Lib - sst Qt Dxf library
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
// sstQtDxf01PathStorage.cpp    23.02.2018  Re.    17.07.17  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>
#include <list>

#include <dl_dxf.h>
#include <dl_creationadapter.h>

#include <rs_color.h>
#include <rs_vector.h>

#include <QtWidgets>
#include <QColor>
#include <QPainterPath>
#include <QPoint>

#include <sstStr01Lib.h>
#include <sstStr01FixColWidth.h>
#include <sstMath01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstQt01Lib.h>
#include <sstDxf03Lib.h>

#include "sstQtDxf01Lib.h"

//=============================================================================
sstQtDxf01PathStorageCls::sstQtDxf01PathStorageCls(sstMisc01PrtFilCls *poTmpPrt)
{
  if (poTmpPrt == NULL) assert(0);
  this->poPrt = poTmpPrt;

  // Create new empty sstDxf database
  this->poDxfDb = new sstDxf03DbCls(this->poPrt);
}
//=============================================================================
sstQtDxf01PathStorageCls::~sstQtDxf01PathStorageCls()
{
  delete this->poDxfDb;
}
//=============================================================================
int sstQtDxf01PathStorageCls::ReadNextEntity2Path(int iKey,dREC04RECNUMTYP dLineRecNo, QPainterPath *poPath, QColor *poColor)
{
  sstMath01dPnt2Cls d2Pnt1;
  sstMath01dPnt2Cls d2Pnt2;

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityLine);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dLineRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert all model LINE entities
  DL_LineData  	  oLineRec(0,0,0,0,0,0);
  DL_Attributes 	oAttribRec;

  iStat = this->poDxfDb->ReadLine( 0, dLineRecNo, &oLineRec, &oAttribRec);
  std::string oLayStr = oAttribRec.getLayer();
  if (oLayStr.length() > 0)
  {

    d2Pnt1.x = oLineRec.x1;
    d2Pnt1.y = oLineRec.y1;
    this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

    d2Pnt2.x = oLineRec.x2;
    d2Pnt2.y = oLineRec.y2;
    this->Transform_WC_DC(0, &d2Pnt2.x,&d2Pnt2.y);

    poPath->moveTo(d2Pnt1.x,d2Pnt1.y);
    poPath->lineTo(d2Pnt2.x,d2Pnt2.y);

    poColor->setBlue(0);
    poColor->setRed(0);
    poColor->setGreen(0);
  }

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathStorageCls::colorToNumber(const QColor& col, int *rgb)
{
    *rgb = -1;

  // Special color black is not in the table but white represents both
    // black and white
    if (col.red()==0 && col.green()==0 && col.blue()==0) {
        return 7;
    }

    // All other colors
    else {
        int num=0;
        int diff=255*3;  // smallest difference to a color in the table found so far

        if(diff != 0) {
            *rgb = 0;
            *rgb = col.red()<<16 | col.green()<<8 | col.blue();
        }
        return num;
    }
}
//=============================================================================
int sstQtDxf01PathStorageCls::WritAlltoPathStorage(int iKey, sstQt01PathStorageCls *poTmpPathStore)
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  QPainterPath *poPath;
  sstQt01ShapeItem *poItemPath;
  QColor oColor;
  QPoint oPnt(0,0);
  dREC04RECNUMTYP dNumRecords = 0;

  dNumRecords = this->poDxfDb->EntityCount(RS2::EntityLine);

  for (dREC04RECNUMTYP ii=1; ii <= dNumRecords; ii++)
  {
    poPath = new QPainterPath;
    poItemPath = new sstQt01ShapeItem;

    // read next path from Dxf database
    iStat = this->ReadNextEntity2Path( 0, ii, poPath, &oColor);

    poItemPath->setColor(oColor);
    poItemPath->setPath(*poPath);
    poItemPath->setPosition(oPnt);
    poItemPath->setShapeType(eSstQt01PathLine);

    poItemPath->setToolTip("Line");

    poTmpPathStore->appendShapeItem(*poItemPath);

    delete poPath;
    delete poItemPath;
  }

  return iStat;
}
//=============================================================================
int sstQtDxf01PathStorageCls::LoadDxfFile(int iKey, std::string oDxfNamStr)
{
  if ( iKey != 0) return -1;
  int iStat = 0;
    iStat = this->poDxfDb->ReadAllFromDxf(0, oDxfNamStr);

    if (iStat < 0)
    {
      this->poPrt->SST_PrtWrtChar(1,(char*)oDxfNamStr.c_str(),(char*)"File not found: ");
      this->poPrt->SST_PrtZu(1);
      assert(0);
    }
  sstMath01Mbr2Cls oMbr = this->poDxfDb->getMbrModel();

  // Recalculate Coordinate Transformation
  iStat = this->Calc_All( 0, oMbr, 1000000, 200.0);
  assert(iStat >= 0);

  return iStat;
}
//=============================================================================
int sstQtDxf01PathStorageCls::WriteAllPath2Dxf(int iKey, sstQt01PathStorageCls *poTmpPathStore)
{

  if ( iKey != 0) return -1;
  int iStat = 0;

  sstQt01ShapeItem *poShapeItem;
  QPoint myPoint(0,0);

  poShapeItem = new sstQt01ShapeItem;

  int iNumItems = poTmpPathStore->countItems();

  for (int ii=1;ii <= iNumItems; ii++)
  {
    *poShapeItem = poTmpPathStore->getShapeItem(ii);

    myPoint = poShapeItem->getPosition();
    QPainterPath oPath = poShapeItem->getPath();
    oPath.translate(myPoint.x(), myPoint.y());

    // QColor oColor = poShapeItem->getColor();

    // Write one path into sstDxf database
    // this->WrtPath2Dxf( 0, oPath, oColor);
  }

  return iStat;
}
//=============================================================================

