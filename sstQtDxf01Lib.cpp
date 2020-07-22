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
// sstQtDxf01Lib.cpp    14.08.16  Re.    14.08.16  Re.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>
#include <list>

#include <dl_dxf.h>
#include <dl_creationadapter.h>

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


//SstQtDxf01Lib::SstQtDxf01Lib()
//{
//}

RS2::EntityType sstQtDxf01PathConvertCls::getEGrpEntType() const
{
  return eGrpEntType;
}

void sstQtDxf01PathConvertCls::setEGrpEntType(const RS2::EntityType &value)
{
  eGrpEntType = value;
}

dREC04RECNUMTYP sstQtDxf01PathConvertCls::getDGrpMainID() const
{
  return dGrpMainID;
}

void sstQtDxf01PathConvertCls::setDGrpMainID(const dREC04RECNUMTYP &value)
{
  dGrpMainID = value;
}
