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

#include "sstQtDxf01QtTab.h"
#include "sstQtDxf01Lib.h"

//=============================================================================
sstQtDxf01PathConvertCls::sstQtDxf01PathConvertCls(sstDxf03DbCls *poTmpDxfDb,
                                                   sstQt01PathStoreViewCls *poTmpPathStore,
                                                   sstMisc01PrtFilCls *poTmpPrt)
{
  if (poTmpPrt == NULL) assert(0);
  if (poTmpDxfDb == NULL) assert(0);
  if (poTmpPathStore == NULL) assert(0);
  this->poPrt = poTmpPrt;
  this->poDxfDb = poTmpDxfDb;
  this->poPathStore = poTmpPathStore;

  sstMath01Mbr2Cls oMbr = this->poDxfDb->getMbrModel();

  // Recalculate Coordinate Transformation
  int iStat = this->Calc_All( 0, oMbr, 1000000, 200.0);
  assert(iStat >= 0);

  // Create new empty sstDxf database
  // this->poDxfDb = new sstDxf03DbCls(this->poPrt);
}
//=============================================================================
sstQtDxf01PathConvertCls::~sstQtDxf01PathConvertCls()
{
  // delete this->poDxfDb;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteLINEtoItemPath(int               iKey,
                                                  dREC04RECNUMTYP   dLineRecNo,
                                                  sstQt01ShapeItem *poItemPath)
{
  QColor oColor;

  sstMath01dPnt2Cls d2Pnt1;  // local double points
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
  if (oLayStr.length() == 0) return -4;
  if (oLayStr.length() > 0)
  {

    d2Pnt1.x = oLineRec.x1;
    d2Pnt1.y = oLineRec.y1;
    this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

    d2Pnt2.x = oLineRec.x2;
    d2Pnt2.y = oLineRec.y2;
    this->Transform_WC_DC(0, &d2Pnt2.x,&d2Pnt2.y);

    QPainterPath *poPath = new QPainterPath;

    poPath->moveTo(d2Pnt1.x,d2Pnt1.y);
    poPath->lineTo(d2Pnt2.x,d2Pnt2.y);

    oColor.setBlue(0);
    oColor.setRed(0);
    oColor.setGreen(0);

  poItemPath->setColor(oColor);
  poItemPath->setPath(*poPath);
  // poItemPath->setPosition(oPnt);
  poItemPath->setShapeType(eSstQt01PathLine);
  poItemPath->setExternId(dLineRecNo);  // Set DXF Entity ID to Path object

  poItemPath->setToolTip("Line");

  delete poPath;

  }
  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteItemPathtoLINE(int                iKey,
                                                  const sstQt01ShapeItem  oItemPath,
                                                  DL_LineData  *poDLLine)
{
  QPainterPath *poPath = new QPainterPath;
  QColor oColor;

  sstMath01dPnt2Cls d2Pnt1;  // local double points
  sstMath01dPnt2Cls d2Pnt2;

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  *poPath = oItemPath.getPath();

  int iEleNum = poPath->elementCount();
  assert(iEleNum == 2);
  QPainterPath::Element oElement;
  oElement = poPath->elementAt(0);

  d2Pnt1.x = oElement.x;
  d2Pnt1.y = oElement.y;
  this->Transform_DC_WC(0, &d2Pnt1.x,&d2Pnt1.y);
  poDLLine->x1 = d2Pnt1.x;
  poDLLine->y1 = d2Pnt1.y;

  oElement = poPath->elementAt(1);
  d2Pnt2.x = oElement.x;
  d2Pnt2.y = oElement.y;
  this->Transform_DC_WC(0, &d2Pnt2.x,&d2Pnt2.y);
  poDLLine->x2 = d2Pnt2.x;
  poDLLine->y2 = d2Pnt2.y;

  delete poPath;

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::ReadItemPathfromLine(int               iKey,
                                                  dREC04RECNUMTYP   dLineRecNo,
                                                  sstQt01ShapeItem *poItemPath)
{
  QPainterPath *poPath = new QPainterPath;
  QColor oColor;

  sstMath01dPnt2Cls d2Pnt1;  // local double points
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

    oColor.setBlue(0);
    oColor.setRed(0);
    oColor.setGreen(0);
  }

  poItemPath->setColor(oColor);
  poItemPath->setPath(*poPath);
  // poItemPath->setPosition(oPnt);
  poItemPath->setShapeType(eSstQt01PathLine);
  poItemPath->setExternId(dLineRecNo);  // Set DXF Entity ID to Path object

  poItemPath->setToolTip("Line");

  delete poPath;

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::colorToNumber(const QColor& col, int *rgb)
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
int sstQtDxf01PathConvertCls::WritAlltoPathStorage(int iKey)
{
  if ( iKey != 0) return -1;
  int iStat = 0;

  // QPainterPath *poPath;
  sstQt01ShapeItem *poItemPath;
  // QColor oColor;
  // QPoint oPnt(0,0);
  dREC04RECNUMTYP dNumRecords = 0;

  dNumRecords = this->poDxfDb->EntityCount(RS2::EntityLine);

  for (dREC04RECNUMTYP ii=1; ii <= dNumRecords; ii++)
  {
    // poPath = new QPainterPath;
    poItemPath = new sstQt01ShapeItem;

    // read next LINE Entity from Dxf database and write into painterpath
    iStat = this->WriteLINEtoItemPath( 0, ii, poItemPath);

//    poItemPath->setColor(oColor);
//    poItemPath->setPath(*poPath);
//    // poItemPath->setPosition(oPnt);
//    poItemPath->setShapeType(eSstQt01PathLine);
//    poItemPath->setId(ii);

//    poItemPath->setToolTip("Line");

    if(iStat >= 0) iStat = this->poPathStore->appendShapeItem(*poItemPath);

    // delete poPath;
    delete poItemPath;
  }

  return iStat;
}
//=============================================================================
//int sstQtDxf01PathConvertCls::LoadDxfFile(int iKey, std::string oDxfNamStr)
//{
//  if ( iKey != 0) return -1;
//  int iStat = 0;
////    iStat = this->poDxfDb->ReadAllFromDxf(0, oDxfNamStr);

////    if (iStat < 0)
////    {
////      this->poPrt->SST_PrtWrtChar(1,(char*)oDxfNamStr.c_str(),(char*)"File not found: ");
////      this->poPrt->SST_PrtZu(1);
////      assert(0);
////    }
//  sstMath01Mbr2Cls oMbr = this->poDxfDb->getMbrModel();

//  // Recalculate Coordinate Transformation
//  iStat = this->Calc_All( 0, oMbr, 1000000, 200.0);
//  assert(iStat >= 0);

//  return iStat;
//}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteAllPath2Dxf(int iKey)
{

  if ( iKey != 0) return -1;
  int iStat = 0;
  // RS2::EntityType eEntType = RS2::EntityUnknown;
  DL_LineData oDL_Line(0,0,0,0,0,0);
  DL_PolylineData oDL_Polyline(0,0,0,0);
  DL_VertexData oDL_Vertex(0,0);
  // DL_BlockData oDL_Block("",0,0,0,0);
  DL_Attributes oDL_Attributes;


  sstQt01ShapeItem *poShapeItem;
  QPoint myPoint(0,0);

  poShapeItem = new sstQt01ShapeItem;
  dREC04RECNUMTYP dDxfEntNo;  // Dxf Entity Number
  RS2::EntityType eEntType;

  int iNumItems = this->poPathStore->countItems();

  for (int ii=1;ii <= iNumItems; ii++)
  {
    *poShapeItem = this->poPathStore->getShapeItem(ii);

    myPoint = poShapeItem->getPosition();
    QPainterPath oPath = poShapeItem->getPath();
    oPath.translate(myPoint.x(), myPoint.y());
    dREC04RECNUMTYP dDxfMainNo = poShapeItem->getExternId();
    iStat = this->poDxfDb->ReadMainTable( 0, dDxfMainNo, &eEntType, &dDxfEntNo);

    // iStat = oDxfDB->ReadEntityType( 0, ii, ll, &eEntType, &dEntNo);
    assert(iStat >= 0);
    switch (eEntType)
    {
    case (RS2::EntityLine):
    {
      poDxfDb->ReadLine( 0, dDxfEntNo, &oDL_Line, &oDL_Attributes);
      // Update dxf entity LINE with data from Itempath
      this->WriteItemPathtoLINE( 0, *poShapeItem, &oDL_Line);
      poDxfDb->WriteLine( 0, oDL_Line, oDL_Attributes, &dDxfEntNo, &dDxfMainNo);
      break;
    }
    case (RS2::EntityPolyline):
    {
      poDxfDb->ReadPolyline( 0, dDxfEntNo, &oDL_Polyline, &oDL_Attributes);
      // oDxf2Nap.addPolyline(oDL_Polyline);
      break;
    }
    case (RS2::EntityVertex):
    {
      // assert(0);
      poDxfDb->ReadVertex( 0, dDxfEntNo, &oDL_Vertex);
      // oDxf2Nap.addVertex(oDL_Vertex);
      break;
    }
    case (RS2::EntityText):
    {
      // Skip text
      break;
    }
      default:
      assert(0);
      break;
    }
//  }


    // QColor oColor = poShapeItem->getColor();

    // Write one path into sstDxf database
    // this->WrtPath2Dxf( 0, oPath, oColor);
  }

  return iStat;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteAll2Dxf(int iKey, const std::string oDxfNamStr)
{
  if ( iKey != 0) return -1;
  int iStat = 0;
    iStat = poDxfDb->WritAll2DxfFil( 0, oDxfNamStr);
    if (iStat < 0)
    {
      this->poPrt->SST_PrtWrtChar(1,(char*)"sstQtDxf01LibTest.dxf",(char*)"File not found: ");
      this->poPrt->SST_PrtZu(1);
      assert(0);
    }

  return iStat;
}
//=============================================================================
