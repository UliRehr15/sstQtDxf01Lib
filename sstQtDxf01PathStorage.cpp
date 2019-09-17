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
// sstQtDxf01PathStorage.cpp    05.07.19  Re.    17.07.17  Re.
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

  this->eGrpEntType = RS2::EntityUnknown;  /**< Group Entity Type like POLYLINE / HATCH */
  this->dGrpMainID = 0;                    /**< Group Main ID/RecNo */
  this->dGrpSubID = 0;                     /**< Sub Group ID/RecNo like HatchLoop */
  this->dGrpRecNum = 0;                    /**< Number of entities of actual group */
  this->dGrpRecPos = 0;                    /**< Position of group element */

  sstMath01Mbr2Cls oMbr = this->poDxfDb->getMbrModel();
  int iStat = oMbr.OK2(0);
  if (iStat != 0)
  {
    this->poPrt->SST_PrtWrtChar(1,(char*)"Calculate Mbr from block Modelspace",(char*)"Error: ");
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
int sstQtDxf01PathConvertCls::WriteLINEtoQtPath(int               iKey,
                                                dREC04RECNUMTYP   dLineRecNo,
                                                QPainterPath     *poPath)
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

    poPath->moveTo(d2Pnt1.x,d2Pnt1.y);
    poPath->lineTo(d2Pnt2.x,d2Pnt2.y);
  }
  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteLINEtoQtPathBlk(int               iKey,
                                                     dREC04RECNUMTYP   dLineRecNo,
                                                     sstMath01TrnCls   oBlkTrn,
                                                     QPainterPath      *poPath)
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
    oBlkTrn.CalcPntX2(0,&d2Pnt1);
    this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

    d2Pnt2.x = oLineRec.x2;
    d2Pnt2.y = oLineRec.y2;
    oBlkTrn.CalcPntX2(0,&d2Pnt2);
    this->Transform_WC_DC(0, &d2Pnt2.x,&d2Pnt2.y);

    poPath->moveTo(d2Pnt1.x,d2Pnt1.y);
    poPath->lineTo(d2Pnt2.x,d2Pnt2.y);

    oColor = this->numberToColor(oAttribRec.getColor());

  }

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WritePOLYLINEtoQtPathBlk(int               iKey,
                                                       dREC04RECNUMTYP   dPLineRecNo,
                                                       QPainterPath      *poPath)
{
  QColor oColor;

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityPolyline);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dPLineRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert all model LINE entities
  DL_PolylineData  	  oPolylineRec(0,0,0,0);
  DL_Attributes 	oAttribRec;

  iStat = this->poDxfDb->ReadPolyline( 0, dPLineRecNo, &oPolylineRec, &oAttribRec);
  std::string oLayStr = oAttribRec.getLayer();
  // if (oLayStr.length() == 0) return -4;
  if (oLayStr.length() >= 0)
  {
    oColor = this->numberToColor(oAttribRec.getColor());
    this->dGrpRecNum = oPolylineRec.number;
  }

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteHATCHtoQtPathBlk(int               iKey,
                                                    dREC04RECNUMTYP   dEntityRecNo,
                                                    QPainterPath      *poPath)
{
  QColor oColor;

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityPolyline);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dEntityRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert all model LINE entities
  //DL_PolylineData  	  oPolylineRec(0,0,0,0);
  DL_HatchData    oHatchRec(1,1,1,0,"SOLID");
  DL_Attributes 	oAttribRec;

  iStat = this->poDxfDb->ReadHatch( 0, dEntityRecNo, &oHatchRec, &oAttribRec);
  std::string oLayStr = oAttribRec.getLayer();
  // if (oLayStr.length() == 0) return -4;
  if (oLayStr.length() >= 0)
  {
    oColor = this->numberToColor(oAttribRec.getColor());
    this->dGrpRecNum = dEntityRecNo;
  }

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteHATCHLOOPtoQtPathBlk(int               iKey,
                                                        dREC04RECNUMTYP   dEntityRecNo,
                                                        QPainterPath      *poPath)
{
  QColor oColor;

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityPolyline);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dEntityRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert all model LINE entities
  //DL_PolylineData  	  oPolylineRec(0,0,0,0);
  DL_HatchLoopData    oHatchLoopRec;
  // DL_Attributes 	oAttribRec;

  iStat = this->poDxfDb->ReadHatchLoop( 0, dEntityRecNo, &oHatchLoopRec);
  std::string oLayStr = oAttribRec.getLayer();
  // if (oLayStr.length() == 0) return -4;
  if (oLayStr.length() >= 0)
  {
    oColor = this->numberToColor(oAttribRec.getColor());
    this->dGrpRecNum = dEntityRecNo;
  }

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteVERTEXtoQtPathBlk(int               iKey,
                                                     dREC04RECNUMTYP   dVertexRecNo,
                                                     sstMath01TrnCls   oBlkTrn,
                                                     QPainterPath      *poPath)
{
  sstMath01dPnt2Cls d2Pnt1;  // local double point

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityVertex);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dVertexRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert model VERTEX entity
  DL_VertexData  	  oVertexRec;

  iStat = this->poDxfDb->ReadVertex( 0, dVertexRecNo, &oVertexRec);

  d2Pnt1.x = oVertexRec.x;
  d2Pnt1.y = oVertexRec.y;
  oBlkTrn.CalcPntX2(0,&d2Pnt1);
  this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

  if (this->dGrpRecPos < 2) assert(0);

  if (this->dGrpRecPos == 2)
  {
    poPath->moveTo(d2Pnt1.x,d2Pnt1.y);
  }
  else
  {
    poPath->lineTo(d2Pnt1.x,d2Pnt1.y);
  }

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteHATCHEDGEtoQtPathBlk(int               iKey,
                                                        dREC04RECNUMTYP   dEntityRecNo,
                                                        sstMath01TrnCls   oBlkTrn,
                                                        QPainterPath      *poPath)
{
  sstMath01dPnt2Cls d2Pnt1;  // local double point

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityVertex);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dEntityRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert model VERTEX entity
//  DL_VertexData  	  oVertexRec;
  DL_HatchEdgeData oHatchEdgeRec(0,0,0,0);  // area border point

  iStat = this->poDxfDb->ReadHatchEdge( 0, dEntityRecNo, &oHatchEdgeRec);

  d2Pnt1.x = oHatchEdgeRec.cx;
  d2Pnt1.y = oHatchEdgeRec.cy;

  oBlkTrn.CalcPntX2(0,&d2Pnt1);
  this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

  if (this->dGrpRecPos < 2) assert(0);

  if (this->dGrpRecPos == 2)
  {
    poPath->moveTo(d2Pnt1.x,d2Pnt1.y);
  }
  else
  {
    poPath->lineTo(d2Pnt1.x,d2Pnt1.y);
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
int sstQtDxf01PathConvertCls::WriteINSERTtoQtPath(int               iKey,
                                                  dREC04RECNUMTYP   dInsertRecNo,
                                                  QPainterPath     *poPath)
{
  QColor oColor;

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dEntRecs = 0;
  dEntRecs = this->poDxfDb->EntityCount( RS2::EntityInsert);
  if (dEntRecs <= 0) return -2;  // sstDxf Database is empty

  if (dInsertRecNo > dEntRecs) return -3;  // Read position after end of table?

  // INSERT entity
  DL_InsertData oDlInsert("test",0,0,0,0,0,0,0,0,0,0,0);
  DL_Attributes 	oAttribRec;

  // Read Insert from Table
  iStat = this->poDxfDb->ReadInsert( 0, dInsertRecNo, &oDlInsert, &oAttribRec);

  // Calculate Coordinate Transformation for Block points
  sstMath01TrnCls oBlkTrn;
  oBlkTrn.SetMov( 0, oDlInsert.ipx, oDlInsert.ipy, oDlInsert.ipz);
  oBlkTrn.SetScal( 0, oDlInsert.sx, oDlInsert.sy, oDlInsert.sz);
  oBlkTrn.SetRotZ( 0, oDlInsert.angle);

  //
  std::string oLayStr = oAttribRec.getLayer();
  if (oLayStr.length() > 0)
  {

    // Open Block and read/transform block geometry
    dREC04RECNUMTYP dBlkNo = this->poDxfDb->searchBlkNoWithName( 0, oDlInsert.name);
    assert(dBlkNo > 0);

    RS2::EntityType eEntityType = RS2::EntityInsert;
    dREC04RECNUMTYP dEntRecNo = 0;


    // return number of entities in actual block in sstDxfDb
    dREC04RECNUMTYP dNumEntities = this->poDxfDb->countEntities (0, dBlkNo);
    assert(dNumEntities > 0);

    // return start of entities of actual block in Main table
    dREC04RECNUMTYP dStartBlkMainTab = this->poDxfDb->getBlkStartMainTab (0, dBlkNo);
    assert(dStartBlkMainTab > 0);

    // int iGrpEntCount = 0;
    this->dGrpRecPos = 0;

    // Loop over all entities of actual block
    for (dREC04RECNUMTYP kk = dStartBlkMainTab; kk <= dStartBlkMainTab+dNumEntities-1; kk++)
    {
      iStat = this->poDxfDb->ReadMainTable( 0, kk, &eEntityType, &dEntRecNo);
      assert(iStat >= 0);

      // Group or Subgroup?
      if (eEntityType == RS2::EntityVertex ||
          // eEntityType == RS2::EntityHatchLoop ||
          eEntityType == RS2::EntityHatchEdge)
      {  // Subgroup
        this->dGrpRecPos++;
      }
      else
      {  // Group
        this->dGrpRecPos = 1;
      }
      switch (eEntityType) {
      case RS2::EntityCircle:
      {
        // read CIRCLE Entity from Dxf database and write into painterpath
        iStat = this->WriteCIRCLEtoQtPathBlk( 0, dEntRecNo, oBlkTrn, poPath);
        break;
      }
      case RS2::EntityHatch:
      {
        // read HATCH Entity from Dxf database and write into painterpath
        break;
      }
      case RS2::EntityHatchLoop:
      {
        // read HATCHLOOP Entity from Dxf database and write into painterpath
        break;
      }
      case RS2::EntityHatchEdge:
      {
        // read HATCHEDGE Entity from Dxf database and write into painterpath
        // iStat = this->WriteHATCHEDGEtoItemPathBlk( 0, dEntRecNo, oBlkTrn, poPath);
        break;
      }
      case RS2::EntityLine:
      {
        // read LINE Entity from Dxf database and write into painterpath
        iStat = this->WriteLINEtoQtPathBlk( 0, dEntRecNo, oBlkTrn, poPath);
        break;
      }
      case RS2::EntityPolyline:
      {
        // read POLYLINE Entity from Dxf database and write into painterpath
        iStat = this->WritePOLYLINEtoQtPathBlk( 0, dEntRecNo, poPath);
        break;
      }
      case RS2::EntityVertex:
      {
        // read POLYLINE Entity from Dxf database and write into painterpath
        iStat = this->WriteVERTEXtoQtPathBlk( 0, dEntRecNo, oBlkTrn, poPath);
        break;
      }
      case RS2::EntityUnknown:
        assert(0);
        break;
      default:
        assert(0);
        break;
      }  // end switch
      assert(iStat >= 0);
    }  // layer filled
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
  assert(iEleNum > 1);
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
int sstQtDxf01PathConvertCls::WriteCIRCLEtoQtPath(int               iKey,
                                                  dREC04RECNUMTYP   dCircleRecNo,
                                                  QPainterPath     *poPath)
{
  sstMath01dPnt2Cls d2Pnt1;  // local double points

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
  if (oLayStr.length() > 0)
  {

    d2Pnt1.x = oCircleRec.cx;
    d2Pnt1.y = oCircleRec.cy;
    this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

    QPointF oCenterPnt(d2Pnt1.getX(),d2Pnt1.getY());

    // Add Circle to Path
    poPath->addEllipse( oCenterPnt, this->Transform_WC_DC_Dist(oCircleRec.radius),
                                    this->Transform_WC_DC_Dist(oCircleRec.radius));
  }
  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteCIRCLEtoQtPathBlk(int               iKey,
                                                       dREC04RECNUMTYP   dCircleRecNo,
                                                       sstMath01TrnCls   oBlkTrn,
                                                       QPainterPath      *poPath)
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
    oBlkTrn.CalcPntX2( 0, &d2Pnt1);
    this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);

    // QPainterPath *poPath = new QPainterPath;
    QPointF oCenterPnt(d2Pnt1.getX(),d2Pnt1.getY());

    // Add Circle to Path
    poPath->addEllipse( oCenterPnt, this->Transform_WC_DC_Dist(oCircleRec.radius),
                                    this->Transform_WC_DC_Dist(oCircleRec.radius));

    oColor = this->numberToColor(oAttribRec.getColor());

  }
  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WritePOINTtoQtPath(int               iKey,
                                                 dREC04RECNUMTYP   dEntityRecNo,
                                                 QPainterPath     *poPath)
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

    QPointF oCenterPnt(d2Pnt1.getX(),d2Pnt1.getY());

    // Add Circle to Path
    poPath->addEllipse( oCenterPnt, this->Transform_WC_DC_Dist(0.1),  // Radius = 0.1
                                    this->Transform_WC_DC_Dist(0.1)); // Radius = 0.1

  }
  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WritePOLYLINEtoQtPath(int               iKey,
                                                      dREC04RECNUMTYP   dEntityRecNo)
{
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dEntRecs = 0;
  dEntRecs = this->poDxfDb->EntityCount( RS2::EntityPolyline);
  if (dEntRecs <= 0) return -2;  // Entity Table is empty

  if (dEntityRecNo > dEntRecs) return -3;  // Read position after end of table?

  this->eGrpEntType = RS2::EntityPolyline;  /**< Group Entity Type like POLYLINE / HATCH */
  this->dGrpMainID = 0;                     /**< Group Main ID/RecNo */
  this->dGrpSubID = 0;                      /**< Sub Group ID/RecNo like HatchLoop */
  this->dGrpRecNum = 0;                     /**< Number of entities of actual group */
  this->dGrpRecPos = 0;                     /**< Position of group element */

  DL_PolylineData oPolylineRec(0,0,0,0);
  DL_Attributes 	oPLineAttrib;

  // Read POLYLINE Entity from Table
  iStat = this->poDxfDb->ReadPolyline( 0, dEntityRecNo, &oPolylineRec, &oPLineAttrib);
  assert(iStat >= 0);
  this->dGrpRecNum = oPolylineRec.number;
  this->oAttribRec = oPLineAttrib;
  this->dGrpMainID = dEntityRecNo;

  return iStat;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteHATCHtoQtPath(int               iKey,
                                                 dREC04RECNUMTYP   dEntityRecNo)
{
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dEntRecs = 0;
  dEntRecs = this->poDxfDb->EntityCount( RS2::EntityHatch);
  if (dEntRecs <= 0) return -2;  // Entity Table is empty

  if (dEntityRecNo > dEntRecs) return -3;  // Read position after end of table?

  this->eGrpEntType = RS2::EntityHatch;     /**< Group Entity Type like POLYLINE / HATCH */
  this->dGrpMainID = 0;                     /**< Group Main ID/RecNo */
  this->dGrpSubID = 0;                      /**< Sub Group ID/RecNo like HatchLoop */
  this->dGrpRecNum = 0;                     /**< Number of entities of actual group */
  this->dGrpRecPos = 0;                     /**< Position of group element */

  // DL_HatchData    oHatchRec(0,0,0,0);
  DL_HatchData    oHatchRec(1,1,1,0,"SOLID");

  DL_Attributes 	oAttrib;

  // Read HATCH Entity from Table
  iStat = this->poDxfDb->ReadHatch( 0, dEntityRecNo, &oHatchRec, &oAttrib);
  assert(iStat >= 0);
  this->dGrpRecNum = 0;
  this->oAttribRec = oAttrib;
  this->dGrpMainID = dEntityRecNo;

  return iStat;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteHATCHLOOPtoQtPath(int               iKey,
                                                     dREC04RECNUMTYP   dEntityRecNo)
{
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dEntRecs = 0;
  dEntRecs = this->poDxfDb->EntityCount( RS2::EntityHatch);
  if (dEntRecs <= 0) return -2;  // Entity Table is empty

  if (dEntityRecNo > dEntRecs) return -3;  // Read position after end of table?

  this->eGrpEntType = RS2::EntityHatch;     /**< Group Entity Type like POLYLINE / HATCH */
  this->dGrpMainID = 0;                     /**< Group Main ID/RecNo */
  this->dGrpSubID = 0;                      /**< Sub Group ID/RecNo like HatchLoop */
  this->dGrpRecNum = 0;                     /**< Number of entities of actual group */
  this->dGrpRecPos = 0;                     /**< Position of group element */

  DL_HatchLoopData    oHatchLoopRec;

  // DL_Attributes 	oAttrib;

  // Read HATCH Entity from Table
  iStat = this->poDxfDb->ReadHatchLoop( 0, dEntityRecNo, &oHatchLoopRec);
  assert(iStat >= 0);
  this->dGrpRecNum = oHatchLoopRec.numEdges;

  return iStat;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteVERTEXtoQtPath(int               iKey,
                                                  dREC04RECNUMTYP   dEntityRecNo,
                                                  QPainterPath     *poPath)
{
  sstMath01dPnt2Cls d2Pnt;  // local point
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityVertex);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dEntityRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert VERTEX entitiy
  DL_VertexData oVertexRec(0,0,0,0);

  iStat = this->poDxfDb->ReadVertex( 0, dEntityRecNo, &oVertexRec);

    d2Pnt.x = oVertexRec.x;
    d2Pnt.y = oVertexRec.y;
    this->Transform_WC_DC(0, &d2Pnt.x,&d2Pnt.y);

    this->dGrpRecPos++;  // Vertex position in POLYLINE Entity

    if (this->dGrpRecPos == 1)
    { // First Vertex, move to new coordinate position
      poPath->moveTo(d2Pnt.x,d2Pnt.y);
    }
    else
    {
      poPath->lineTo(d2Pnt.x,d2Pnt.y);
    }

  return iStat;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteHATCHEDGEtoQtPath(int               iKey,
                                                     dREC04RECNUMTYP   dEntityRecNo,
                                                     QPainterPath     *poPath)
{
  sstMath01dPnt2Cls d2Pnt1;  // local point 1
  sstMath01dPnt2Cls d2Pnt2;  // local point 2
  sstMath01dPnt2Cls d2PntC;  // local point Circle
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs = 0;
  dMainRecs = this->poDxfDb->EntityCount( RS2::EntityHatchEdge);
  if (dMainRecs <= 0) return -2;  // sstDxf Database is empty

  if (dEntityRecNo > dMainRecs) return -3;  // Read position after end of table?

  // Insert HATCH EDGE entitiy
  DL_HatchEdgeData oHatchEdgeRec(0,0,0,0);

  iStat = this->poDxfDb->ReadHatchEdge( 0, dEntityRecNo, &oHatchEdgeRec);

  d2Pnt1.x = oHatchEdgeRec.x1;
  d2Pnt1.y = oHatchEdgeRec.y1;
  d2Pnt2.x = oHatchEdgeRec.x2;
  d2Pnt2.y = oHatchEdgeRec.y2;
  d2PntC.x = oHatchEdgeRec.cx;
  d2PntC.y = oHatchEdgeRec.cy;
  this->Transform_WC_DC(0, &d2Pnt1.x,&d2Pnt1.y);
  this->Transform_WC_DC(0, &d2Pnt2.x,&d2Pnt2.y);
  this->Transform_WC_DC(0, &d2PntC.x,&d2PntC.y);
  double dLocRadius = 0.0;
  dLocRadius = this->Transform_WC_DC_Dist(oHatchEdgeRec.radius);
  double dLocAng1 = oHatchEdgeRec.angle1 / dSSTMATH01_PI * 180.0;  // from rad to degrees

  this->dGrpRecPos++;  // EDGE position in HATCH Entity

  if (this->dGrpRecPos == 1)
  {  // first element in group

    if (this->dGrpRecNum == 1 && oHatchEdgeRec.type == 2)
    {
      // Circle
      poPath->moveTo(d2PntC.getX()+ dLocRadius, d2PntC.getY());
      poPath->arcTo(d2PntC.getX() - dLocRadius, d2PntC.getY() - dLocRadius,
                    dLocRadius*2, dLocRadius*2,
                    0.0, 360.0);
      // return iStat;

    }
    else
    {
      // First Edge move to new coordinate position
      poPath->moveTo(d2Pnt1.x,d2Pnt1.y);
      poPath->lineTo(d2Pnt2.x,d2Pnt2.y);
    }


//    if (oHatchEdgeRec.type == 2)
//      poPath->arcTo(d2PntC.getX()-dLocRadius,d2PntC.getY() - dLocRadius,
//                    dLocRadius * 2,
//                    dLocRadius * 2,
//                    60.0, 240);
//    else
  }
  else
  {  // next element in group
    if (oHatchEdgeRec.type == 2)
    {
      double dSweepLength = 0.0;
      sstMath01AngCalcCls oAngCalc;
      oAngCalc.AngleDiff(0,oHatchEdgeRec.angle1,oHatchEdgeRec.angle2, &dSweepLength);
      dSweepLength = dSweepLength / M_PI * 180.0;   // Delta Angle in degrees
      poPath->lineTo(d2PntC.getX(),d2PntC.getX());  // Move back to center
      poPath->arcTo(d2PntC.getX() - dLocRadius,
                    d2PntC.getY() - dLocRadius,
                    dLocRadius * 2.0,
                    dLocRadius * 2.0,
                    dLocAng1, dSweepLength);
    }
    else
      poPath->lineTo(d2Pnt2.x,d2Pnt2.y);
  }

  return iStat;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteItemPathtoCIRCLE(int                      iKey,
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
  // QColor oColor;

  sstMath01dPnt2Cls d2Pnt1;  // local double points

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
int sstQtDxf01PathConvertCls::WriteItemPathtoPOLYLINE(int                      iKey,
                                                      const sstQt01ShapeItem   oItemPath,
                                                      DL_PolylineData         *poDlPolyline)
{
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  int iPathIndex = 0;
  QPainterPath oPath;
  oPath = oItemPath.getPath();

  // Get Main Record from entity record
  dREC04RECNUMTYP dMainRecNo =  this->poDxfDb->getMainTabRecNo(0,RS2::EntityPolyline,oItemPath.getExternId());

  // Next record in maintable should by Entity type Vertex
  // loop over all vertex records after polyline record in main table
  for (dREC04RECNUMTYP ll = dMainRecNo+1; ll <= dMainRecNo+poDlPolyline->number;ll++)
  {  // loop in maintable
    RS2::EntityType eEntTyp = RS2::EntityUnknown;
    dREC04RECNUMTYP dEntRecNo = 0;
    iStat = this->poDxfDb->ReadMainTable( 0, ll, &eEntTyp, &dEntRecNo);
    assert(iStat >= 0);
    assert(eEntTyp == RS2::EntityVertex);
    DL_VertexData oDlVertex(0,0,0,0);
    iStat = this->poDxfDb->ReadVertex( 0, dEntRecNo, &oDlVertex);
    iPathIndex++;
    // Convert path element to vertex and coordinate transformation from Device to World
    this->WritePathElementToVERTEX(0,oPath.elementAt(iPathIndex-1),&oDlVertex);
    iStat = this->poDxfDb->WriteVertex( 0, oDlVertex, &dEntRecNo, &dMainRecNo);
  }

  return iStat;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WriteItemPathtoHATCH(int                      iKey,
                                                   const sstQt01ShapeItem   oItemPath,
                                                   DL_HatchData    *poHatch)
//                                                   DL_PolylineData         *poDlPolyline)
{
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  int iPathIndex = 0;
  QPainterPath oPath;
  oPath = oItemPath.getPath();

  // Get Main Record from entity record
  dREC04RECNUMTYP dMainRecNo =  this->poDxfDb->getMainTabRecNo(0,RS2::EntityPolyline,oItemPath.getExternId());

  // Next record in maintable should by Entity type Vertex
  // loop over all vertex records after polyline record in main table
  // for (dREC04RECNUMTYP ll = dMainRecNo+1; ll <= dMainRecNo+poDlPolyline->number;ll++)
  for (dREC04RECNUMTYP ll = dMainRecNo+1; ll <= dMainRecNo;ll++)
  {  // loop in maintable
    RS2::EntityType eEntTyp = RS2::EntityUnknown;
    dREC04RECNUMTYP dEntRecNo = 0;
    iStat = this->poDxfDb->ReadMainTable( 0, ll, &eEntTyp, &dEntRecNo);
    assert(iStat >= 0);
    assert(eEntTyp == RS2::EntityHatchEdge);
    // DL_VertexData oDlVertex(0,0,0,0);
    DL_HatchEdgeData oDlHatchEdge(0,0,0,0);
    iStat = this->poDxfDb->ReadHatchEdge( 0, dEntRecNo, &oDlHatchEdge);
    iPathIndex++;
    // Convert path element to vertex and coordinate transformation from Device to World
    this->WritePathElementToHATCHEDGE(0,oPath.elementAt(iPathIndex-1),&oDlHatchEdge);
    iStat = this->poDxfDb->WriteHatchEdge( 0, oDlHatchEdge, &dEntRecNo, &dMainRecNo);
  }

  return iStat;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WritePathElementToVERTEX(int                      iKey,
                                                    const   QPainterPath::Element oElement,
                                                    DL_VertexData            *poDlVertex)
{
  sstMath01dPnt2Cls d2Pnt1;  // local double points

  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  d2Pnt1.x = oElement.x;
  d2Pnt1.y = oElement.y;
  iStat = this->Transform_DC_WC(0, &d2Pnt1.x,&d2Pnt1.y);
  poDlVertex->x = d2Pnt1.x;
  poDlVertex->y = d2Pnt1.y;

  return iStat;
}
//=============================================================================
int sstQtDxf01PathConvertCls::WritePathElementToHATCHEDGE(int                      iKey,
                                                          const   QPainterPath::Element oElement,
                                                          DL_HatchEdgeData *poHatchEdge)
//                                                          DL_VertexData          *poDlVertex)
{
  sstMath01dPnt2Cls d2Pnt1;  // local double points

  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  d2Pnt1.x = oElement.x;
  d2Pnt1.y = oElement.y;
  iStat = this->Transform_DC_WC(0, &d2Pnt1.x,&d2Pnt1.y);
  poHatchEdge->cx = d2Pnt1.x;
  poHatchEdge->cy = d2Pnt1.y;

  return iStat;
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
  QPainterPath *poPath;
  dREC04RECNUMTYP dNumRecords = 0;
  RS2::EntityType eEntityType = RS2::EntityUnknown;
  dREC04RECNUMTYP dEntRecNo = 0;

  int iShapeItemRecs = 0;
  dREC04RECNUMTYP dItemRecNo = 0;

  // Count entities of section entities
  dNumRecords = this->poDxfDb->countEntities(0,0);

  // Create empty MainDistplay List
//  for (dREC04RECNUMTYP ii=1; ii <= dNumRecords; ii++)
//  {
//    this->poMainDisplayList->WritNew(0,&iShapeItemRecs,&dItemRecNo);
//  }

  poPath = new QPainterPath;

  for (dREC04RECNUMTYP ii=1; ii <= dNumRecords; ii++)
    {
    // return type/Tab Rec No of entity in block with main tab no <BR>
    iStat = this->poDxfDb->ReadEntityType ( 0, 0, ii, &eEntityType, &dEntRecNo);
    assert(iStat == 0);

    // poItemPath = new sstQt01ShapeItem;

    // Group or Subgroup?
    if (eEntityType == RS2::EntityVertex ||
        eEntityType == RS2::EntityHatchLoop ||
        eEntityType == RS2::EntityHatchEdge)
    {  // Subgroup

    }
    else
    {  // Group
      // if (eEntityType != this->eGrpEntType && poPath->elementCount() > 0)
      if (poPath->elementCount() > 0)
      { // New Group, write existing path to storage

        // poPath->elementCount();
        poItemPath = new sstQt01ShapeItem;

        // Fill open sst Path Item <BR>
        iStat = this->FillPathItem( iKey, poPath, iShapeItemRecs, poItemPath);

        if(iStat >= 0) iStat = this->poPathStore->appendShapeItem(*poItemPath);

        iShapeItemRecs++;
        // this->poMainDisplayList->Writ(0,&iShapeItemRecs, ii);
        this->poMainDisplayList->WritNew( 0, &iShapeItemRecs, &dItemRecNo);

        delete poItemPath;
        delete poPath;
         poPath = new QPainterPath;
       }
      this->eGrpEntType = eEntityType;
      this->dGrpMainID = dEntRecNo;
    }

    switch (eEntityType) {
    case RS2::EntityCircle:
    {
      // read next CIRCLE Entity from Dxf database and write into painterpath
      iStat = this->WriteCIRCLEtoQtPath( 0, dEntRecNo, poPath);
      break;
    }
    case RS2::EntityInsert:
    {
      // read next LINE Entity from Dxf database and write into painterpath
      iStat = this->WriteINSERTtoQtPath( 0, dEntRecNo, poPath);
      break;
    }
    case RS2::EntityLine:
    {
      // read next LINE Entity from Dxf database and write into painterpath
      iStat = this->WriteLINEtoQtPath( 0, dEntRecNo, poPath);
      break;
    }
    case RS2::EntityPoint:
    {
      // read next POINT Entity from Dxf database and write into painterpath
      iStat = this->WritePOINTtoQtPath( 0, dEntRecNo, poPath);
      break;
    }
    case RS2::EntityPolyline:
    {
      // read next POLYLINE Entity from Dxf database and write header
      iStat = this->WritePOLYLINEtoQtPath( 0, dEntRecNo);
      break;
    }
    case RS2::EntityVertex:
    {
      // read next VERTEX Entity from Dxf database and write into painterpath
      iStat = this->WriteVERTEXtoQtPath( 0, dEntRecNo, poPath);
      break;
    }
    case RS2::EntityHatch:
    {
      // read next HATCH Entity from Dxf database and write into painterpath
      iStat = this->WriteHATCHtoQtPath( 0, dEntRecNo);
      break;
    }
    case RS2::EntityHatchLoop:
    {
      // read next HATCHLOOP Entity from Dxf database and write into painterpath
      iStat = this->WriteHATCHLOOPtoQtPath( 0, dEntRecNo);
      break;
    }
    case RS2::EntityHatchEdge:
    {
      // read next HATCHEDGE Entity from Dxf database and write into painterpath
      iStat = this->WriteHATCHEDGEtoQtPath( 0, dEntRecNo, poPath);
      break;
    }

    default:
      assert(0);
      // all other entity type are not displayed and not inserted to Display list
      break;
    }
    }

  // Write last path into storage

  if (poPath->elementCount() > 0)
  { // New Group, write existing path to storage

    // poPath->elementCount();
    poItemPath = new sstQt01ShapeItem;

    // Fill open sst Path Item <BR>
    iStat = this->FillPathItem( iKey,
                                poPath,
                                // this->dGrpMainID,  // dEntRecNo,
                                iShapeItemRecs,
                                // this->eGrpEntType,  // eEntityType,
                                poItemPath);


//    QColor oColor;
//    oColor = this->numberToColor(this->oAttribRec.getColor());
//    poItemPath->setColor(oColor);
//    poItemPath->setPath(*poPath);
//    poItemPath->setShapeType(eSstQt01PathCircle);
//    poItemPath->setExternId(dEntRecNo);  // Set DXF Entity ID to Path object

//    sstStr01Cls oStrCnvt;
//    oStrCnvt.SetSeparator(0,(char*) "_");
//    std::string oTooltipStr = "ID";
//    oStrCnvt.Csv_UInt4_2String(0,dEntRecNo,&oTooltipStr);
//    oStrCnvt.Csv_Str_2String(0,"Circle",&oTooltipStr);
//    poItemPath->setToolTip( oTooltipStr);

//    std::string oTypeStr;
//    oTypeStr = this->poDxfDb->CnvtTypeEnum2String(eEntityType);
//    poItemPath->setExternStr(oTypeStr);
//    poItemPath->setInternId(iShapeItemRecs);
    if(iStat >= 0) iStat = this->poPathStore->appendShapeItem(*poItemPath);
    delete poItemPath;
    delete poPath;
  }

    //  dNumRecords = this->poDxfDb->EntityCount(RS2::EntityLine);

//  for (dREC04RECNUMTYP ii=1; ii <= dNumRecords; ii++)
//  {
//    // poPath = new QPainterPath;
//    poItemPath = new sstQt01ShapeItem;

//    // read next LINE Entity from Dxf database and write into painterpath
//    iStat = this->WriteLINEtoQtPath( 0, ii, poItemPath);

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
//    iStat = this->WriteCIRCLEtoQtPath( 0, ii, poItemPath);

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
      // Update dxf entity POINT with data from Itempath
      iStat = this->WriteItemPathtoPOINT( 0, *poShapeItem, &oDL_Point);
      iStat = poDxfDb->WritePoint( 0, oDL_Point, oDL_Attributes, &dDxfEntNo, &dDxfMainNo);
      break;
    }
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
      // Update dxf entity POLYLINE with data from Itempath
      iStat = this->WriteItemPathtoPOLYLINE( 0, *poShapeItem, &oDL_Polyline);
      break;
    }
    case (RS2::EntityVertex):
    {
      // assert(0);
      poDxfDb->ReadVertex( 0, dDxfEntNo, &oDL_Vertex);
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
int sstQtDxf01PathConvertCls::FillPathItem (int               iKey,
                                            QPainterPath     *poPath,
                                            // dREC04RECNUMTYP   dEntRecNo,
                                            dREC04RECNUMTYP   dItemListNo,
                                            // RS2::EntityType   eEntityType,
                                            sstQt01ShapeItem *poItemPath)
//-----------------------------------------------------------------------------
{
  int iRet = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  QColor oColor;
  oColor = this->numberToColor(this->oAttribRec.getColor());
  poItemPath->setColor(oColor);
  poItemPath->setPath(*poPath);

  sstQt01ShapeType_enum eItemPathTyp = eSstQt01PathNoObj;

  switch (this->eGrpEntType) {
  case RS2::EntityArc:
      eItemPathTyp = eSstQt01PathArc;
    break;
  case RS2::EntityCircle:
      eItemPathTyp = eSstQt01PathCircle;
    break;
  case RS2::EntityInsert:
      eItemPathTyp = eSstQt01PathObject;
    break;
  case RS2::EntityLine:
      eItemPathTyp = eSstQt01PathLine;
    break;
  case RS2::EntityPolyline:
      eItemPathTyp = eSstQt01PathPLine;
    break;
  case RS2::EntityHatch:
      eItemPathTyp = eSstQt01PathArea;
    break;
  case RS2::EntityText:
  case RS2::EntityMText:
      eItemPathTyp = eSstQt01PathText;
    break;
  default:
    assert(0);
    break;
  }
  poItemPath->setShapeType(eItemPathTyp);
  poItemPath->setExternId(this->dGrpMainID);  // Set DXF Entity ID to Path object

  std::string oTypeStr;
  oTypeStr = this->poDxfDb->CnvtTypeEnum2String(this->eGrpEntType);
  poItemPath->setExternStr(oTypeStr);
  poItemPath->setInternId(dItemListNo);

  sstStr01Cls oStrCnvt;
  oStrCnvt.SetSeparator(0,(char*) "_");
  std::string oTooltipStr = "ID";
  oStrCnvt.Csv_UInt4_2String(0,this->dGrpMainID,&oTooltipStr);
  oStrCnvt.Csv_Str_2String(0,oTypeStr,&oTooltipStr);
  poItemPath->setToolTip( oTooltipStr);

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
