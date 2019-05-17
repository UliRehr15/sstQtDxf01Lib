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
// sstQtDxf01PathStorage.cpp    14.12.18  Re.    17.07.17  Re.
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
  int iStat = oMbr.OK2(0);
  if (iStat != 0)
  {
    this->poPrt->SST_PrtWrtChar(1,(char*)"Calculate Mbr from block Paperspace",(char*)"Error: ");
    this->poPrt->SST_PrtZu(1);
    assert(0);
  }

  // Recalculate Coordinate Transformation
  iStat = this->Calc_All( 0, oMbr, 1000000, 200.0);
  assert(iStat >= 0);

  int iShapeItemListNr = 0;
  this->poMainDisplayList = new sstRec04Cls(sizeof(iShapeItemListNr));
}
//=============================================================================
sstQtDxf01PathConvertCls::~sstQtDxf01PathConvertCls()
{
  delete this->poMainDisplayList;
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
  // if (oLayStr.length() == 0) return -4;
  if (oLayStr.length() >= 0)
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

    oColor = this->numberToColor(oAttribRec.getColor());

    poItemPath->setColor(oColor);
    poItemPath->setPath(*poPath);
    // poItemPath->setPosition(oPnt);
    poItemPath->setShapeType(eSstQt01PathLine);
    poItemPath->setExternId(dLineRecNo);  // Set DXF Entity ID to Path object

    sstStr01Cls oStrCnvt;
    oStrCnvt.SetSeparator(0,(char*) "_");
    std::string oTooltipStr = "ID";
    oStrCnvt.Csv_UInt4_2String(0,dLineRecNo,&oTooltipStr);
    oStrCnvt.Csv_Str_2String(0,"Line",&oTooltipStr);
    poItemPath->setToolTip( oTooltipStr);

    delete poPath;

  }
  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteItemPathtoLINE(int                      iKey,
                                                  const sstQt01ShapeItem   oItemPath,
                                                  DL_LineData             *poDLLine)
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
int sstQtDxf01PathConvertCls::WriteINSERTtoItemPath(int               iKey,
                                                    dREC04RECNUMTYP   dInsertRecNo,
                                                    sstQt01ShapeItem *poItemPath)
{
  QColor oColor;

  sstMath01dPnt2Cls d2Pnt1;  // local point

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityInsert);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dInsertRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert POINT entitie
  // DL_PointData oPointRec(0,0,0);
  DL_InsertData oDlInsert("test",0,0,0,0,0,0,0,0,0,0,0);
  DL_Attributes 	oAttribRec;

  iStat = this->poDxfDb->ReadInsert( 0, dInsertRecNo, &oDlInsert, &oAttribRec);
  std::string oLayStr = oAttribRec.getLayer();
  // if (oLayStr.length() == 0) return -4;
  if (oLayStr.length() >= 0)
  {

    d2Pnt1.x = oDlInsert.ipx;
    d2Pnt1.y = oDlInsert.ipy;
    this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

    QPainterPath *poPath = new QPainterPath;
    QPointF oCenterPnt(d2Pnt1.getX(),d2Pnt1.getY());

    // Add Circle to Path
    poPath->addEllipse( oCenterPnt, this->Transform_WC_DC_Dist(0.1),  // Radius = 0.1
                                    this->Transform_WC_DC_Dist(0.1)); // Radius = 0.1

    oColor = this->numberToColor(oAttribRec.getColor());

    poItemPath->setColor(oColor);
    poItemPath->setPath(*poPath);
    poItemPath->setShapeType(eSstQt01PathCircle);  // Really written to path storage is type circle
    poItemPath->setExternId(dInsertRecNo);  // Set DXF Entity ID to Path object

    sstStr01Cls oStrCnvt;
    oStrCnvt.SetSeparator(0,(char*) "_");
    std::string oTooltipStr = "ID";
    oStrCnvt.Csv_UInt4_2String(0,dInsertRecNo,&oTooltipStr);
    oStrCnvt.Csv_Str_2String(0,this->oEntStrCnvt.Enum2String(RS2::EntityInsert),&oTooltipStr);
    poItemPath->setToolTip( oTooltipStr);

    delete poPath;

  }
  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteItemPathtoINSERT(int                      iKey,
                                                    const sstQt01ShapeItem   oItemPath,
                                                    DL_InsertData           *poDlInsert)
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
  assert(iEleNum == 13);
  QPainterPath::Element oElement;
  oElement = poPath->elementAt(0);
  QRectF oBBox = poPath->boundingRect();
  QPointF oQPnt = oBBox.center();

  d2Pnt1.x = oQPnt.x();
  d2Pnt1.y = oQPnt.y();
  this->Transform_DC_WC(0, &d2Pnt1.x,&d2Pnt1.y);
  poDlInsert->ipx = d2Pnt1.x;
  poDlInsert->ipy = d2Pnt1.y;

  delete poPath;

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteCIRCLEtoItemPath(int               iKey,
                                                    dREC04RECNUMTYP   dCircleRecNo,
                                                    sstQt01ShapeItem *poItemPath)
{
  QColor oColor;

  sstMath01dPnt2Cls d2Pnt1;  // local double points
  // sstMath01dPnt2Cls d2Pnt2;

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityCircle);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dCircleRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert all model LINE entities
  DL_CircleData   oCircleRec(0,0,0,0);
  DL_Attributes 	oAttribRec;

  iStat = this->poDxfDb->ReadCircle( 0, dCircleRecNo, &oCircleRec, &oAttribRec);
  std::string oLayStr = oAttribRec.getLayer();
  // if (oLayStr.length() == 0) return -4;
  if (oLayStr.length() >= 0)
  {

    d2Pnt1.x = oCircleRec.cx;
    d2Pnt1.y = oCircleRec.cy;
    this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

    QPainterPath *poPath = new QPainterPath;
    QPointF oCenterPnt(d2Pnt1.getX(),d2Pnt1.getY());

    // Add Circle to Path
    poPath->addEllipse( oCenterPnt, this->Transform_WC_DC_Dist(oCircleRec.radius),
                                    this->Transform_WC_DC_Dist(oCircleRec.radius));

    oColor = this->numberToColor(oAttribRec.getColor());
    // oColor.setBlue(0);
    // oColor.setRed(0);
    // oColor.setGreen(0);

    poItemPath->setColor(oColor);
    poItemPath->setPath(*poPath);
    // poItemPath->setPosition(oPnt);
    poItemPath->setShapeType(eSstQt01PathCircle);
    poItemPath->setExternId(dCircleRecNo);  // Set DXF Entity ID to Path object

    sstStr01Cls oStrCnvt;
    oStrCnvt.SetSeparator(0,(char*) "_");
    std::string oTooltipStr = "ID";
    oStrCnvt.Csv_UInt4_2String(0,dCircleRecNo,&oTooltipStr);
    oStrCnvt.Csv_Str_2String(0,"Circle",&oTooltipStr);
    poItemPath->setToolTip( oTooltipStr);

    delete poPath;

  }
  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WritePOINTtoItemPath(int               iKey,
                                                    dREC04RECNUMTYP   dEntityRecNo,
                                                    sstQt01ShapeItem *poItemPath)
{
  QColor oColor;

  sstMath01dPnt2Cls d2Pnt1;  // local point

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityPoint);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dEntityRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert POINT entitie
  DL_PointData oPointRec(0,0,0);
  DL_Attributes 	oAttribRec;

  iStat = this->poDxfDb->ReadPoint( 0, dEntityRecNo, &oPointRec, &oAttribRec);
  std::string oLayStr = oAttribRec.getLayer();
  // if (oLayStr.length() == 0) return -4;
  if (oLayStr.length() >= 0)
  {

    d2Pnt1.x = oPointRec.x;
    d2Pnt1.y = oPointRec.y;
    this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

    QPainterPath *poPath = new QPainterPath;
    QPointF oCenterPnt(d2Pnt1.getX(),d2Pnt1.getY());

    // Add Circle to Path
    poPath->addEllipse( oCenterPnt, this->Transform_WC_DC_Dist(0.1),  // Radius = 0.1
                                    this->Transform_WC_DC_Dist(0.1)); // Radius = 0.1

    oColor = this->numberToColor(oAttribRec.getColor());

    poItemPath->setColor(oColor);
    poItemPath->setPath(*poPath);
    poItemPath->setShapeType(eSstQt01PathCircle);  // Really written to path storage is type circle
    poItemPath->setExternId(dEntityRecNo);  // Set DXF Entity ID to Path object

    sstStr01Cls oStrCnvt;
    oStrCnvt.SetSeparator(0,(char*) "_");
    std::string oTooltipStr = "ID";
    oStrCnvt.Csv_UInt4_2String(0,dEntityRecNo,&oTooltipStr);
    oStrCnvt.Csv_Str_2String(0,this->oEntStrCnvt.Enum2String(RS2::EntityPoint),&oTooltipStr);
    poItemPath->setToolTip( oTooltipStr);

    delete poPath;

  }
  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteItemPathtoCIRCLE(int                    iKey,
                                                  const sstQt01ShapeItem   oItemPath,
                                                  DL_CircleData           *poDlCircle)
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
  assert(iEleNum == 13);
  QPainterPath::Element oElement;
  oElement = poPath->elementAt(0);
  QRectF oBBox = poPath->boundingRect();
  QPointF oQPnt = oBBox.center();

//  d2Pnt1.x = oElement.x;
//  d2Pnt1.y = oElement.y;
  d2Pnt1.x = oQPnt.x();
  d2Pnt1.y = oQPnt.y();
  this->Transform_DC_WC(0, &d2Pnt1.x,&d2Pnt1.y);
  poDlCircle->cx = d2Pnt1.x;
  poDlCircle->cy = d2Pnt1.y;

  delete poPath;

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteItemPathtoPOINT(int                      iKey,
                                                   const sstQt01ShapeItem   oItemPath,
                                                   DL_PointData            *poDlPoint)
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
  assert(iEleNum == 13);
  QPainterPath::Element oElement;
  oElement = poPath->elementAt(0);
  QRectF oBBox = poPath->boundingRect();
  QPointF oQPnt = oBBox.center();

//  d2Pnt1.x = oElement.x;
//  d2Pnt1.y = oElement.y;
  d2Pnt1.x = oQPnt.x();
  d2Pnt1.y = oQPnt.y();
  this->Transform_DC_WC(0, &d2Pnt1.x,&d2Pnt1.y);
  poDlPoint->x = d2Pnt1.x;
  poDlPoint->y = d2Pnt1.y;

  delete poPath;

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
//=============================================================================
//int sstQtDxf01PathConvertCls::ReadItemPathfromLine(int               iKey,
//                                                  dREC04RECNUMTYP   dLineRecNo,
//                                                  sstQt01ShapeItem *poItemPath)
//{
//  QPainterPath *poPath = new QPainterPath;
//  QColor oColor;

//  sstMath01dPnt2Cls d2Pnt1;  // local double points
//  sstMath01dPnt2Cls d2Pnt2;

//  int iRet  = 0;
//  int iStat = 0;
//  //-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;

//  dREC04RECNUMTYP dMainRecs = 0;
//  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityLine);
//  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

//  if (dLineRecNo > dMainRecs) return -3;  // Read position after end of table?

//  // Insert all model LINE entities
//  DL_LineData  	  oLineRec(0,0,0,0,0,0);
//  DL_Attributes 	oAttribRec;

//  iStat = this->poDxfDb->ReadLine( 0, dLineRecNo, &oLineRec, &oAttribRec);
//  std::string oLayStr = oAttribRec.getLayer();
//  if (oLayStr.length() > 0)
//  {

//    d2Pnt1.x = oLineRec.x1;
//    d2Pnt1.y = oLineRec.y1;
//    this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

//    d2Pnt2.x = oLineRec.x2;
//    d2Pnt2.y = oLineRec.y2;
//    this->Transform_WC_DC(0, &d2Pnt2.x,&d2Pnt2.y);

//    poPath->moveTo(d2Pnt1.x,d2Pnt1.y);
//    poPath->lineTo(d2Pnt2.x,d2Pnt2.y);

//    oColor.setBlue(0);
//    oColor.setRed(0);
//    oColor.setGreen(0);
//  }

//  poItemPath->setColor(oColor);
//  poItemPath->setPath(*poPath);
//  // poItemPath->setPosition(oPnt);
//  poItemPath->setShapeType(eSstQt01PathLine);
//  poItemPath->setExternId(dLineRecNo);  // Set DXF Entity ID to Path object

//  poItemPath->setToolTip((std::string) "Line");

//  delete poPath;

//  // Fatal Errors goes to an assert
//  assert(iRet >= 0);

//  // Small Errors will given back
//  iRet = iStat;

//  return iRet;
//}
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
QColor sstQtDxf01PathConvertCls::numberToColor(int iDxfNo)
{
  QColor oQtCol;
  RS_Color oDxfCol; // (iDxfNo);
  switch (iDxfNo)
  {
  case 0: return QColor(Qt::black);break;
  case 1: return QColor(Qt::red);break;
  case 2: return QColor(Qt::yellow);break;
  default:
  {
    oDxfCol.fromIntColor(iDxfNo);
    oQtCol = oDxfCol.toQColor();
    break;
  }
  }
    return oQtCol;
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
  RS2::EntityType eEntityType;
  dREC04RECNUMTYP dEntRecNo = 0;

  int iShapeItemRecs = 0;
  dREC04RECNUMTYP dItemRecNo = 0;

  // Count entities of section entities
  dNumRecords = this->poDxfDb->countEntities(0,0);

  // Create empty MainDistplay List
  for (dREC04RECNUMTYP ii=1; ii <= dNumRecords; ii++)
  {
    this->poMainDisplayList->WritNew(0,&iShapeItemRecs,&dItemRecNo);
  }

  for (dREC04RECNUMTYP ii=1; ii <= dNumRecords; ii++)
    {
    // return type/Tab Rec No of entity in block with main tab no <BR>
    iStat = this->poDxfDb->ReadEntityType ( 0, 0, ii, &eEntityType, &dEntRecNo);
    assert(iStat == 0);

    poItemPath = new sstQt01ShapeItem;

    switch (eEntityType) {
    case RS2::EntityLine:
    {
      // read next LINE Entity from Dxf database and write into painterpath
      iStat = this->WriteLINEtoItemPath( 0, dEntRecNo, poItemPath);
      iShapeItemRecs++;
      this->poMainDisplayList->Writ(0,&iShapeItemRecs, ii);

      std::string oTypeStr;
      oTypeStr = this->poDxfDb->CnvtTypeEnum2String(eEntityType);
      poItemPath->setExternStr(oTypeStr);
      poItemPath->setInternId(iShapeItemRecs);
      if(iStat >= 0) iStat = this->poPathStore->appendShapeItem(*poItemPath);
      break;
    }
    case RS2::EntityInsert:
    {
      // read next LINE Entity from Dxf database and write into painterpath
      iStat = this->WriteINSERTtoItemPath( 0, dEntRecNo, poItemPath);
      iShapeItemRecs++;
      this->poMainDisplayList->Writ(0,&iShapeItemRecs, ii);

      std::string oTypeStr;
      oTypeStr = this->poDxfDb->CnvtTypeEnum2String(eEntityType);
      poItemPath->setExternStr(oTypeStr);
      poItemPath->setInternId(iShapeItemRecs);
      if(iStat >= 0) iStat = this->poPathStore->appendShapeItem(*poItemPath);
      break;
    }
    case RS2::EntityPoint:
    {
      // read next POINT Entity from Dxf database and write into painterpath
      iStat = this->WritePOINTtoItemPath( 0, dEntRecNo, poItemPath);
      iShapeItemRecs++;
      this->poMainDisplayList->Writ(0,&iShapeItemRecs, ii);

      std::string oTypeStr;
      oTypeStr = this->poDxfDb->CnvtTypeEnum2String(eEntityType);
      poItemPath->setExternStr(oTypeStr);
      poItemPath->setInternId(iShapeItemRecs);
      if(iStat >= 0) iStat = this->poPathStore->appendShapeItem(*poItemPath);
      break;
    }
    case RS2::EntityCircle:
    {
      // read next CIRCLE Entity from Dxf database and write into painterpath
      iStat = this->WriteCIRCLEtoItemPath( 0, dEntRecNo, poItemPath);
      iShapeItemRecs++;
      this->poMainDisplayList->Writ(0,&iShapeItemRecs, ii);

      std::string oTypeStr;
      oTypeStr = this->poDxfDb->CnvtTypeEnum2String(eEntityType);
      poItemPath->setExternStr(oTypeStr);
      poItemPath->setInternId(iShapeItemRecs);
      if(iStat >= 0) iStat = this->poPathStore->appendShapeItem(*poItemPath);
      break;
    }

    default:
      // all other entity type are not displayed and not inserted to Display list
      break;
    }
    delete poItemPath;
    }

//  dNumRecords = this->poDxfDb->EntityCount(RS2::EntityLine);

//  for (dREC04RECNUMTYP ii=1; ii <= dNumRecords; ii++)
//  {
//    // poPath = new QPainterPath;
//    poItemPath = new sstQt01ShapeItem;

//    // read next LINE Entity from Dxf database and write into painterpath
//    iStat = this->WriteLINEtoItemPath( 0, ii, poItemPath);

//    poItemPath->setColor(oColor);
//    poItemPath->setPath(*poPath);
//    // poItemPath->setPosition(oPnt);
//    poItemPath->setShapeType(eSstQt01PathLine);
//    poItemPath->setId(ii);

//    poItemPath->setToolTip("Line");

//    if(iStat >= 0) iStat = this->poPathStore->appendShapeItem(*poItemPath);

//    // delete poPath;
//    delete poItemPath;
//  }

//  dNumRecords = this->poDxfDb->EntityCount(RS2::EntityCircle);

//  for (dREC04RECNUMTYP ii=1; ii <= dNumRecords; ii++)
//  {
//    // poPath = new QPainterPath;
//    poItemPath = new sstQt01ShapeItem;

//    // read next LINE Entity from Dxf database and write into painterpath
//    iStat = this->WriteCIRCLEtoItemPath( 0, ii, poItemPath);

//    poItemPath->setColor(oColor);
//    poItemPath->setPath(*poPath);
//    // poItemPath->setPosition(oPnt);
//    poItemPath->setShapeType(eSstQt01PathLine);
//    poItemPath->setId(ii);

//    poItemPath->setToolTip("Line");

//    if(iStat >= 0) iStat = this->poPathStore->appendShapeItem(*poItemPath);

//    // delete poPath;
//    delete poItemPath;
//  }

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
  DL_CircleData oDL_Circle(0,0,0,0);
  DL_PointData oDL_Point(0,0,0);
  DL_HatchData oDL_Hatch(0,0,0.0,0.0,"pattern",0.0,0.0);
  DL_LineData oDL_Line(0,0,0,0,0,0);
  DL_PolylineData oDL_Polyline(0,0,0,0);
  DL_VertexData oDL_Vertex(0,0);
  // DL_BlockData oDL_Block("",0,0,0,0);
  DL_Attributes oDL_Attributes;

  sstQt01ShapeItem *poShapeItem;
  QPoint myPoint(0,0);

  poShapeItem = new sstQt01ShapeItem;
  dREC04RECNUMTYP dDxfEntNo = 0;  // Dxf Entity Number
  dREC04RECNUMTYP dDxfMainNo = 0;  // Dxf Main Number
  RS2::EntityType eEntType;

  int iNumItems = this->poPathStore->countItems();

  for (int ii=1;ii <= iNumItems; ii++)
  {
    *poShapeItem = this->poPathStore->getShapeItem(ii);

    // Update position of path with translate position
    myPoint = poShapeItem->getPosition();
    QPainterPath oPath = poShapeItem->getPath();
    oPath.translate(myPoint.x(), myPoint.y());
    poShapeItem->setPath(oPath);

    // Get Dxf Entity Type from Extern ID
    dDxfEntNo = poShapeItem->getExternId();
    std::string oTypeStr = poShapeItem->getExternStr();
    eEntType = this->poDxfDb->CnvtTypeString2Enum(oTypeStr);
    // iStat = this->poDxfDb->ReadMainTable( 0, dDxfMainNo, &eEntType, &dDxfEntNo);

    // std::string oEntityTypeStr = poShapeItem->g
    // iStat = poDxfDb->ReadEntityType( 0, 0, ii, &eEntType, &dDxfEntNo);
    // assert(iStat >= 0);

    switch (eEntType)
    {
    case (RS2::EntityCircle):
    {
      iStat = poDxfDb->ReadCircle( 0, dDxfEntNo, &oDL_Circle, &oDL_Attributes);
      // Update dxf entity CIRCLE with data from Itempath
      iStat = this->WriteItemPathtoCIRCLE( 0, *poShapeItem, &oDL_Circle);
      iStat = poDxfDb->WriteCircle( 0, oDL_Circle, oDL_Attributes, &dDxfEntNo, &dDxfMainNo);
      break;
    }
    case (RS2::EntityPoint):
    {
      iStat = poDxfDb->ReadPoint( 0, dDxfEntNo, &oDL_Point, &oDL_Attributes);
      // Update dxf entity CIRCLE with data from Itempath
      iStat = this->WriteItemPathtoPOINT( 0, *poShapeItem, &oDL_Point);
      iStat = poDxfDb->WritePoint( 0, oDL_Point, oDL_Attributes, &dDxfEntNo, &dDxfMainNo);
      break;
    }
//    case (RS2::EntityHatch):
//    {
//      iStat = poDxfDb->ReadHatch( 0, dDxfEntNo, &oDL_Hatch, &oDL_Attributes);
//      // Update dxf entity HATCH with data from Itempath
//      // iStat = this->WriteItemPathtoCIRCLE( 0, *poShapeItem, &oDL_Circle);
//      // iStat = poDxfDb->WriteHatch( 0, oDL_Hatch, oDL_Attributes, &dDxfEntNo, &dDxfMainNo);
//      break;
//    }
    case (RS2::EntityLine):
    {
      iStat = poDxfDb->ReadLine( 0, dDxfEntNo, &oDL_Line, &oDL_Attributes);
      // Update dxf entity LINE with data from Itempath
      iStat = this->WriteItemPathtoLINE( 0, *poShapeItem, &oDL_Line);
      iStat = poDxfDb->WriteLine( 0, oDL_Line, oDL_Attributes, &dDxfEntNo, &dDxfMainNo);
      break;
    }
    case (RS2::EntityInsert):
    {
      DL_InsertData oDL_Insert ("test",0,0,0,0,0,0,0,0,0,0,0);
      iStat = poDxfDb->ReadInsert( 0, dDxfEntNo, &oDL_Insert, &oDL_Attributes);
      // Update dxf entity INSERT with data from Itempath
      iStat = this->WriteItemPathtoINSERT( 0, *poShapeItem, &oDL_Insert);
      iStat = poDxfDb->WriteInsert( 0, oDL_Insert, oDL_Attributes, &dDxfEntNo, &dDxfMainNo);
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
    case (RS2::EntityHatch):
    case (RS2::EntityHatchEdge):
    case (RS2::EntityHatchLoop):
    case (RS2::EntityText):
    {
      // Skip entity, do nothing
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
dREC04RECNUMTYP sstQtDxf01PathConvertCls::getItemListNo(int iKey, dREC04RECNUMTYP dRecNo )
{
  if ( iKey != 0) return -1;
  dREC04RECNUMTYP dResultNo = 0;
  int iStat = this->poMainDisplayList->Read( 0, dRecNo, &dResultNo);
  assert(iStat == 0);
  return dResultNo;
}
//=============================================================================
