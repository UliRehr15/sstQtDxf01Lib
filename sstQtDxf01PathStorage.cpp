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
// sstQt01PathStorage.cpp    02.09.16  Re.    02.09.16  Re.
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

#include <QColor>
#include <QPainterPath>
#include <QPoint>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstQt01Lib.h>
#include <sstDxf03Lib.h>

#include "sstQtDxf01Lib.h"

//=============================================================================
sstQtDxf01PathStorageCls::sstQtDxf01PathStorageCls()
{
  this->poDxfDb = new sstDxf03DbCls(&this->oPrt);
  int iStat = poDxfDb->ReadAllFromDxf( 0, "sstQtDxf01LibTest.dxf");
  assert(iStat == 0);
  dActualReadPos = 1;  // table reading starts at begin of table
}
//=============================================================================
sstQtDxf01PathStorageCls::~sstQtDxf01PathStorageCls()
{
  int iStat = poDxfDb->WritAll2DxfFil( 0, "sstQtDxf01LibTest.dxf");
  assert(iStat == 0);
  delete this->poDxfDb;
}
//=============================================================================
int sstQtDxf01PathStorageCls::WrtPath2Dxf(int iKey, QPainterPath oTmpPath, QColor oTmpColor)
{

  // sstQtDxf01PathElementCls oShapeItemCsv;
  QPainterPath::Element oElement0;
  QPainterPath::Element oElement1;
  QPainterPath::Element oElement2;
  QPainterPath::Element oElement3;
  QPainterPath::Element oElementFirst;  // first element of object
  QPainterPath::Element oElementCorner[4];  // 4 Corner point of circle
  QPainterPath::Element oElementCtr;  // Center of circle
  DL_HatchData oDLHatch(1,1,1,0,"SOLID");
  DL_HatchEdgeData oDLHatchEdge(0,0,0,0);  // area border point
  DL_Attributes oDLAttributes;
  dREC04RECNUMTYP oEntRecNo = 0;
  dREC04RECNUMTYP oMainRecNo = 0;
  unsigned int uiCircleCorner = 0;
  int iDxfColor = 0;

  // dREC04RECNUMTYP dRecNo = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  int ePrevType = 0;
  int iEleNum = oTmpPath.elementCount();

  // convert qt color to dxf color
  int iRGB = 0;
  iDxfColor = this->colorToNumber(oTmpColor, &iRGB);

  oDLAttributes.setLayer("0");
  oDLAttributes.setLineType("CONTINUOUS");

  for (int ii =1; ii <= iEleNum; ii++)
  {
    QPainterPath::Element oElement_ii;
    oElement_ii = oTmpPath.elementAt(ii-1);

    switch (oElement_ii.type)
    {
    case 0:
    {
      oElement0 = oElement_ii;
    }
      break;
    case 1:
      {
      if (ePrevType == 0)
      { // new element
        // open new dxflib hatch object in sstDxfDb
        oDLAttributes.setColor(iDxfColor);
        iStat = poDxfDb->OpenNewHatch( 0, oDLHatch, oDLAttributes, &oEntRecNo, &oMainRecNo);
        oElementFirst = oElement_ii;
      }
        else
        {
        // DL_HatchEdgeData oDLHatchEdge(1,1,2,2);  // area border point
          // write new dxflib hatch edge into sstDxfDb hatch object
          oDLHatchEdge.x1 = oElement1.x;
          oDLHatchEdge.y1 = oElement1.y;
          oDLHatchEdge.x2 = oElement_ii.x;
          oDLHatchEdge.y2 = oElement_ii.y;
          iStat = this->Transform_DC_WC( 0, &oDLHatchEdge);
          iStat = poDxfDb->WriteNewHatchEdge ( 0, oDLHatchEdge, &oEntRecNo, &oMainRecNo);
        }
        oElement1 = oElement_ii;
      }
      break;
    case 2:
    {
      // New circle area
      if (ePrevType == 3)
      {
        // close last circle
        oElementCorner[uiCircleCorner] = oElement3;
        uiCircleCorner++;
      }

      // open new dxflib hatch object in sstDxfDb

      oElement2 = oElement_ii;
    }
      break;
    case 3:
    {

      oElement3 = oElement_ii;
    }
      break;
    default:
      break;
    }
    ePrevType = oElement_ii.type;
  }

  // close open objects before leaving PainterPath
  if (ePrevType == 1)
  { // new element
    // open new dxflib hatch object in sstDxfDb
    oDLHatchEdge.x1 = oElement1.x;
    oDLHatchEdge.y1 = oElement1.y;
    oDLHatchEdge.x2 = oElementFirst.x;
    oDLHatchEdge.y2 = oElementFirst.y;
    iStat = this->Transform_DC_WC( 0, &oDLHatchEdge);
    iStat = poDxfDb->WriteNewHatchEdge ( 0, oDLHatchEdge, &oEntRecNo, &oMainRecNo);
  }
  if (ePrevType == 3)
  {
    oElementCorner[uiCircleCorner] = oElement3;

    oElementCtr.x = (oElementCorner[0].x + oElementCorner[2].x) / 2.0;
    oElementCtr.y = (oElementCorner[0].y + oElementCorner[2].y) / 2.0;

    int iRad = oElementCtr.y - oElementCorner[2].y;
    if (iRad < 0) iRad = iRad * -1.0;

    // open new dxflib hatch object in sstDxfDb
    oDLHatchEdge.cx = oElementCtr.x;
    oDLHatchEdge.cy = oElementCtr.y;
    oDLHatchEdge.angle1 = 0;
    oDLHatchEdge.angle2 = 2*M_PI;
    oDLHatchEdge.radius = iRad;
    oDLHatchEdge.ccw = 1;
    oDLHatchEdge.type = 2;
    oDLHatchEdge.defined = true;

    oDLAttributes.setColor(iDxfColor);
    iStat = poDxfDb->OpenNewHatch( 0, oDLHatch, oDLAttributes, &oEntRecNo, &oMainRecNo);

    iStat = this->Transform_DC_WC( 0, &oDLHatchEdge);
    iStat = poDxfDb->WriteNewHatchEdge ( 0, oDLHatchEdge, &oEntRecNo, &oMainRecNo);
  }

  return iStat;
}
//=============================================================================
int sstQtDxf01PathStorageCls::ReadNextPath(int iKey,dREC04RECNUMTYP *dMainRecNo, QPainterPath *poPath, QColor *poColor)
{
  // sstQtDxf01PathStorageCls oPathHandler;

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  dREC04RECNUMTYP dMainRecs =  this->poDxfDb->MainCount();
  if (dMainRecs <= 0) return -2;  // Dxf Database is empty

  if (*dMainRecNo >= dMainRecs) return -3;  // Read position after end of table?

    RS2::EntityType eEntityType = RS2::EntityUnknown;
    dREC04RECNUMTYP dEntRecNo = 0;
    iStat = this->poDxfDb->ReadMainTable(0,*dMainRecNo,&eEntityType,&dEntRecNo);
    switch(eEntityType)
    {
      case RS2::EntityHatch:
    {
      DL_HatchData oDLHatch;
      DL_Attributes oDLAttributes;
        iStat = this->poDxfDb->ReadHatch(0,dEntRecNo,&oDLHatch,&oDLAttributes);
        if (oDLHatch.numLoops <= 0) assert (0);

        int iColor = oDLAttributes.getColor();

        // transform dxf color to QColor
        *poColor = this->numberToColor(iColor);

        *dMainRecNo = *dMainRecNo + 1;
        iStat = this->poDxfDb->ReadMainTable(0,*dMainRecNo,&eEntityType,&dEntRecNo);
        if (eEntityType != RS2::EntityHatchLoop) assert (0);
        DL_HatchLoopData oDLHatchLoop;
        iStat = this->poDxfDb->ReadHatchLoop( 0, dEntRecNo, &oDLHatchLoop);
        if (oDLHatchLoop.numEdges <= 0) assert(0);
        for (int dd = 1; dd <= oDLHatchLoop.numEdges; dd++)
        {
          *dMainRecNo = *dMainRecNo + 1;
          iStat = this->poDxfDb->ReadMainTable(0,*dMainRecNo,&eEntityType,&dEntRecNo);
          if (eEntityType != RS2::EntityHatchEdge) assert (0);
          DL_HatchEdgeData oDLHatchEdge;
          iStat = this->poDxfDb->ReadHatchEdge( 0, dEntRecNo, &oDLHatchEdge);
          assert(iStat >= 0);
          // transform coordinates of HatchEdge from would to device coordinate system
          this->Transform_WC_DC( 0, &oDLHatchEdge);
          switch (oDLHatchEdge.type)
          {
            case 1:
            if (dd == 1)
            {
              poPath->moveTo(oDLHatchEdge.x1,oDLHatchEdge.y1);
              poPath->lineTo(oDLHatchEdge.x2,oDLHatchEdge.y2);
            }  // End first edge
            // polygon element
            else
              poPath->lineTo(oDLHatchEdge.x2,oDLHatchEdge.y2);
            break;
          case 2:  // Circle
          {
            QPointF center;
            center.setX(oDLHatchEdge.cx);
            center.setY(oDLHatchEdge.cy);
            poPath->addEllipse(center,oDLHatchEdge.radius,oDLHatchEdge.radius);
          }
            break;
          default:
            break;
          }  // end switch edge type
        }  // end all hatch loops
    }  // end process type hatch
        break;
    case RS2::EntityCircle:
    {
      DL_CircleData oDLCircle(0,0,0,0);
      DL_Attributes oDLAttributes;
      iStat = this->poDxfDb->ReadCircle( 0, dEntRecNo, &oDLCircle, &oDLAttributes);
      assert(iStat == 0);
      this->Transform_WC_DC( 0, &oDLCircle.cx, &oDLCircle.cy);
      QPointF center;
      center.setX(oDLCircle.cx);
      center.setY(oDLCircle.cy);
      poPath->addEllipse(center,oDLCircle.radius,oDLCircle.radius);
    } // end process type circle
      break;
    default:
    {
      iStat = 0;
    }  // end process all not defined dxf entity types
      break;
    } // end switch dxf entity type

    *dMainRecNo = *dMainRecNo + 1;

    // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathStorageCls::Transform_DC_WC (int iKey, DL_HatchEdgeData *oDLHatchEdge)
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  oDLHatchEdge->cy = (oDLHatchEdge->cy * -1.0) + 400.0;
  oDLHatchEdge->y1 = (oDLHatchEdge->y1 * -1.0) + 400.0;
  oDLHatchEdge->y2 = (oDLHatchEdge->y2 * -1.0) + 400.0;

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathStorageCls::Transform_DC_WC (int iKey, double *dX, double *dY)
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  *dX = (*dX * -1.0) + 400.0;
  *dY = (*dY * -1.0) + 400.0;

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathStorageCls::Transform_WC_DC (int iKey, DL_HatchEdgeData *oDLHatchEdge)
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  oDLHatchEdge->cy = (oDLHatchEdge->cy - 400.0) * -1.0;
  oDLHatchEdge->y1 = (oDLHatchEdge->y1 - 400.0) * -1.0;
  oDLHatchEdge->y2 = (oDLHatchEdge->y2 - 400.0) * -1.0;

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathStorageCls::Transform_WC_DC (int iKey, double *dX, double *dY)
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  *dX = *dX * 1.0;
  *dY = (*dY - 400.0) * -1.0;

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
QColor sstQtDxf01PathStorageCls::numberToColor(int num) {
        if (num==0) {
            return QColor(RS2::FlagByBlock);
        } else if (num==256) {
            return QColor(RS2::FlagByLayer);
        } else if (num<=255 && num>=0) {
            return QColor( (dxfColors[num][0]*255),
                           (dxfColors[num][1]*255),
                           (dxfColors[num][2]*255));
        } else {
            return QColor(RS2::FlagByLayer);
        }

    return QColor();
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

        // Run through the whole table and compare
        for (int i=1; i<=255; i++) {
            int d =   abs(col.red()  - (dxfColors[i][0] * 255))
                    + abs(col.green()- (dxfColors[i][1] * 255))
                    + abs(col.blue() - (dxfColors[i][2] * 255));

            if (d<diff) {
                diff = d;
                num = i;
                if (d==0) {
                    break;
                }
            }
        }
        if(diff != 0) {
            *rgb = 0;
            *rgb = col.red()<<16 | col.green()<<8 | col.blue();
        }
        return num;
    }
}
//=============================================================================
int sstQtDxf01PathStorageCls::WriteDxfDbToCsv(int iKey, std::string oFilNam)
{

  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = this->poDxfDb->WritAll2Csv( 0, oFilNam);

  // Fatal Errors goes to an assert

  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstQtDxf01PathStorageCls::ReadDxfDbFromCsv(int iKey, std::string oFilNam)
{
  int iRet  = 0;
  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = this->poDxfDb->ReadAllCsvFiles(0,oFilNam);

  // Fatal Errors goes to an assert

  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
