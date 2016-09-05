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

#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include <QColor>
#include <QPainterPath>
#include <QPoint>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstQt01Lib.h>

#include "sstQtDxf01LibTest.h"


//! [0]
class ShapeItem
{
public:
    void setPath(const QPainterPath &Path);
    void setToolTip(const QString &ToolTip);
    void setPosition(const QPoint &Position);
    void setColor(const QColor &Color);

    QPainterPath getPath() const;
    QPoint getPosition() const;
    QColor getColor() const;
    QString getToolTip() const;

private:
    QPainterPath myPath;
    QPoint myPosition;
    QColor myColor;
    QString myToolTip;
};
////==============================================================================
///**
//* @brief Definition Class sstQt01PathElementCsvCls
//*
//* template for sst base class <BR>
//*
//* Changed: 10.08.16  Re.
//*
//* @ingroup sstQtDxf01Lib
//*
//* @author Re.
//*
//* @date 10.08.16
//*/
//// ----------------------------------------------------------------------------
//class sstQt01PathElementCsvCls
//{
//  public:   // Public functions
//     sstQt01PathElementCsvCls();  // Constructor
//    //~sstTestBaseCls();  // Destructor
//     //==============================================================================
//     /**
//     * @brief // Shortstory <BR>
//     * iStat = oTestBase.Func_1(iKey);
//     *
//     * @param iKey [in] For the moment 0
//     *
//     * @return Errorstate
//     *
//     * @retval   = 0: OK
//     * @retval   < 0: Unspecified Error
//     */
//     // ----------------------------------------------------------------------------
//    // int Func_1(int iKey);
//     int ReadFromCsv(int iKey, std::string oCsvStr, std::string *oErrStr);
//     int WriteToCsv(int iKey, std::string *oCsvStr, std::string *oErrStr);
//     // void setAll(int iType,int iXX, int iYY, int iColR, int iColG, int iColB );
//     void setAll(int iType,int iXX, int iYY, QColor oCol);

//// ----------------------------------------------------------------------------
//     int getIType() const;
//     void setIType(int value);

//     int getIXX() const;
//     void setIXX(int value);

//     int getIYY() const;
//     void setIYY(int value);

//     int getIColR() const;
//     void setIColR(int value);

//     int getIColG() const;
//     void setIColG(int value);

//     int getIColB() const;
//     void setIColB(int value);

//private:  // Private functions
//     int iType;        /**< Shape Item Type */
//     int iXX;          /**< Coordinate X */
//     int iYY;          /**< Coordinate Y */
//     int iColR;        /**< Color Red */
//     int iColG;        /**< Color Green */
//     int iColB;        /**< Color Blue */
//};
////-----------------------------------------------------------------------------

//! [0]

#endif
