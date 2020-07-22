/**********************************************************************
 *
 * sstQtDxf01Lib - sst Qt Dxf library
 * Hosted on github
 *
 * Copyright (C) 2020 Uli Rehr
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
// sstQtDxf01Convert.cpp    02.05.20 Re.    02.05.20  Re.
//
// Converting Attributes between Qt and Dxf

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
sstQtDxf01CnvtCls::sstQtDxf01CnvtCls()
{

}
//=============================================================================
int sstQtDxf01CnvtCls::colorToNumber(const QColor& col, int *rgb)
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
QColor sstQtDxf01CnvtCls::numberToColor(int iDxfNo)
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

