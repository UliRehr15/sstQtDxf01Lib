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
// shapeitem.cpp    14.08.16  Re.    14.08.16  Re.

#include <QtWidgets>

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

#include "shapeitem.h"

//! [0]
QPainterPath ShapeItem::getPath() const
{
    return myPath;
}
//! [0]

//! [1]
QPoint ShapeItem::getPosition() const
{
    return myPosition;
}
//! [1]

//! [2]
QColor ShapeItem::getColor() const
{
    return myColor;
}
//! [2]

//! [3]
QString ShapeItem::getToolTip() const
{
    return myToolTip;
}
//! [3]

//! [4]
void ShapeItem::setPath(const QPainterPath &path)
{
    myPath = path;
}
//! [4]

//! [5]
void ShapeItem::setToolTip(const QString &toolTip)
{
    myToolTip = toolTip;
}
//! [5]

//! [6]
void ShapeItem::setPosition(const QPoint &position)
{
    myPosition = position;
}
//! [6]

//! [7]
void ShapeItem::setColor(const QColor &color)
{
    myColor = color;
}
//! [7]
//sstQt01PathElementCsvCls::sstQt01PathElementCsvCls()
//{
//  this->iType = 0;        /**< Shape Item Type */
//  this->iXX = 0;          /**< Coordinate X */
//  this->iYY = 0;          /**< Coordinate Y */
//  this->iColR = 0;        /**< Color Red */
//  this->iColG = 0;        /**< Color Green */
//  this->iColB = 0;        /**< Color Blue */

//}
////=============================================================================
//int sstQt01PathElementCsvCls::ReadFromCsv(int iKey, std::string oCsvStr, std::string *oErrStr)
//{
//  sstStr01Cls oCsvCnvt;

//  int iStat = 0;
//  // int iVal = 0;
//  //-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;

//  if (iStat >= 0) iStat = oCsvCnvt.CsvString2_Int2( 0, &oCsvStr,&this->iType);  // Type
//  if (iStat >= 0) iStat = oCsvCnvt.CsvString2_Int2( 0, &oCsvStr,&this->iXX);  // X
//  if (iStat >= 0) iStat = oCsvCnvt.CsvString2_Int2( 0, &oCsvStr,&this->iYY);  // Y
//  if (iStat >= 0) iStat = oCsvCnvt.CsvString2_Int2( 0, &oCsvStr,&this->iColR);  // Color R
//  if (iStat >= 0) iStat = oCsvCnvt.CsvString2_Int2( 0, &oCsvStr,&this->iColG);  // Color G
//  if (iStat >= 0) iStat = oCsvCnvt.CsvString2_Int2( 0, &oCsvStr,&this->iColB);  // Color B
//  *oErrStr = oCsvCnvt.GetErrorString();
//  return iStat;
//}
////=============================================================================
//int sstQt01PathElementCsvCls::WriteToCsv(int iKey, std::string *oCsvStr, std::string *oErrStr)
//{
//  sstStr01Cls oCsvCnvt;
//  int iStat = 0;
//  //-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;

//  if (iStat >= 0) iStat = oCsvCnvt.Csv_Int2_2String( 0, this->iType, oCsvStr);
//  if (iStat >= 0) iStat = oCsvCnvt.Csv_Int2_2String( 0, this->iXX, oCsvStr);
//  if (iStat >= 0) iStat = oCsvCnvt.Csv_Int2_2String( 0, this->iYY, oCsvStr);
//  if (iStat >= 0) iStat = oCsvCnvt.Csv_Int2_2String( 0, this->iColR, oCsvStr);
//  if (iStat >= 0) iStat = oCsvCnvt.Csv_Int2_2String( 0, this->iColG, oCsvStr);
//  if (iStat >= 0) iStat = oCsvCnvt.Csv_Int2_2String( 0, this->iColB, oCsvStr);
//  *oErrStr = oCsvCnvt.GetErrorString();

//  return iStat;
//}
////=============================================================================
//// void sstQt01PathElementCsvCls::setAll(int iTmpType,int iTmpXX, int iTmpYY, int iTmpColR, int iTmpColG, int iTmpColB )
//void sstQt01PathElementCsvCls::setAll(int iTmpType,int iTmpXX, int iTmpYY, QColor oTmpCol)
//{
//  int iTmpColR = 0;
//  int iTmpColG = 0;
//  int iTmpColB = 0;

//  oTmpCol.getRgb(&iTmpColR,&iTmpColG,&iTmpColB);

//  this->iType = iTmpType;
//  this->iXX = iTmpXX;
//  this->iYY = iTmpYY;
//  this->iColR = iTmpColR;
//  this->iColG = iTmpColG;
//  this->iColB = iTmpColB;
//}
////=============================================================================
//int sstQt01PathElementCsvCls::getIType() const
//{
//  return iType;
//}
////=============================================================================
//void sstQt01PathElementCsvCls::setIType(int value)
//{
//  iType = value;
//}
////=============================================================================
//int sstQt01PathElementCsvCls::getIXX() const
//{
//  return iXX;
//}
////=============================================================================
//void sstQt01PathElementCsvCls::setIXX(int value)
//{
//  iXX = value;
//}
////=============================================================================
//int sstQt01PathElementCsvCls::getIYY() const
//{
//  return iYY;
//}
////=============================================================================
//void sstQt01PathElementCsvCls::setIYY(int value)
//{
//  iYY = value;
//}
////=============================================================================
//int sstQt01PathElementCsvCls::getIColR() const
//{
//  return iColR;
//}
////=============================================================================
//void sstQt01PathElementCsvCls::setIColR(int value)
//{
//  iColR = value;
//}
////=============================================================================
//int sstQt01PathElementCsvCls::getIColG() const
//{
//  return iColG;
//}
////=============================================================================
//void sstQt01PathElementCsvCls::setIColG(int value)
//{
//  iColG = value;
//}
////=============================================================================
//int sstQt01PathElementCsvCls::getIColB() const
//{
//  return iColB;
//}
////=============================================================================
//void sstQt01PathElementCsvCls::setIColB(int value)
//{
//  iColB = value;
//}
////=============================================================================
