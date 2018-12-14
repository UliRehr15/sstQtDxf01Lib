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
// sstQtDxf01TabViewAll.cpp    14.12.18  Re.    25.05.18  Re.
//

#include <QtWidgets>
#include <QFont>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <list>
#include <dl_dxf.h>
#include <dl_creationadapter.h>
#include <rs_vector.h>

#include <sstStr01Lib.h>
#include <sstMath01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstQt01Lib.h>
#include <sstDxf03Lib.h>

#include "sstQtDxf01QtTab.h"
#include "sstQtDxf01Lib.h"

//=============================================================================
sstQtDxf01TabViewCircleCls::sstQtDxf01TabViewCircleCls(sstMisc01PrtFilCls *poTmpPrt,
                                                       sstDxf03DbCls      *poDxfDb)
  : sstQt01TabViewCls(poTmpPrt)
{
  poTabMdl = new sstQtDxf01TabMdlCircleCls(0, poTmpPrt, poDxfDb);
  this->setModel( poTabMdl );

  connect(this,SIGNAL(sstSgnlTabCircleUpdated(sstQt01ShapeItem)),this,SLOT(sstSlotUpdateTabCircle(sstQt01ShapeItem)));
  connect(this->poTabMdl,SIGNAL(sstSgnlTabCircleChanged(sstQt01MapSignalCls)),this,SLOT(sstSlotChangeTabCircle(sstQt01MapSignalCls)));

}
//=============================================================================
sstQtDxf01TabViewCircleCls::~sstQtDxf01TabViewCircleCls()
{
  delete poTabMdl;
}
//=============================================================================
void sstQtDxf01TabViewCircleCls::sstSlotChangeTabCircle(sstQt01MapSignalCls oMapSignal)
{
  emit this->sstSgnlTabCircleChanged(oMapSignal);
}
//=============================================================================
void sstQtDxf01TabViewCircleCls::sstSlotUpdateTabCircle(sstQt01ShapeItem oShapeItem)
{
  emit this->poTabMdl->sstSgnlTabCircleUpdated(oShapeItem);
  this->resizeRowsToContents();
}
//=============================================================================
sstQtDxf01TabViewLineCls::sstQtDxf01TabViewLineCls(sstMisc01PrtFilCls *poTmpPrt,
                                                   sstDxf03DbCls      *poDxfDb)
  : sstQt01TabViewCls(poTmpPrt)
{
  poTabMdl = new sstQtDxf01TabMdlLineCls(0, poTmpPrt, poDxfDb);
  this->setModel( poTabMdl );

  connect(this,SIGNAL(sstSgnlTabLineUpdated(sstQt01ShapeItem)),this,SLOT(sstSlotUpdateTabLine(sstQt01ShapeItem)));
  connect(this->poTabMdl,SIGNAL(sstSgnlTabLineChanged(sstQt01MapSignalCls)),this,SLOT(sstSlotChangeTabLine(sstQt01MapSignalCls)));

}
//=============================================================================
sstQtDxf01TabViewLineCls::~sstQtDxf01TabViewLineCls()
{
  delete poTabMdl;
}
//=============================================================================
void sstQtDxf01TabViewLineCls::sstSlotChangeTabLine(sstQt01MapSignalCls oMapSignal)
{
  emit this->sstSgnlTabLineChanged(oMapSignal);
}
//=============================================================================
void sstQtDxf01TabViewLineCls::sstSlotUpdateTabLine(sstQt01ShapeItem oShapeItem)
{
  emit this->poTabMdl->sstSgnlTabLineUpdated(oShapeItem);
  this->resizeRowsToContents();
}
//=============================================================================
sstQtDxf01TabViewMTextCls::sstQtDxf01TabViewMTextCls(sstMisc01PrtFilCls *poTmpPrt,
                                                     sstDxf03DbCls      *poDxfDb)
  : sstQt01TabViewCls(poTmpPrt)
{
  poTabMdl = new sstQtDxf01TabMdlMTextCls(0, poTmpPrt, poDxfDb);
  this->setModel( poTabMdl);

  connect(this->poTabMdl,SIGNAL(sstSgnlTabChanged(sstQt01ShapeItem)),this,SLOT(sstSlotChangeTab(sstQt01ShapeItem)));

}
//=============================================================================
sstQtDxf01TabViewMTextCls::~sstQtDxf01TabViewMTextCls()
{
  delete poTabMdl;
}
//=============================================================================
sstQtDxf01TabViewPointCls::sstQtDxf01TabViewPointCls(sstMisc01PrtFilCls *poTmpPrt,
                                                     sstDxf03DbCls      *poDxfDb)
  : sstQt01TabViewCls(poTmpPrt)
{
  poTabMdl = new sstQtDxf01TabMdlPointCls(0, poTmpPrt, poDxfDb);
  this->setModel( poTabMdl);

  connect(this->poTabMdl,SIGNAL(sstSgnlTabChanged(sstQt01ShapeItem)),this,SLOT(sstSlotChangeTab(sstQt01ShapeItem)));

}
//=============================================================================
sstQtDxf01TabViewPointCls::~sstQtDxf01TabViewPointCls()
{
  delete poTabMdl;
}
//=============================================================================
sstQtDxf01TabViewTextCls::sstQtDxf01TabViewTextCls(sstMisc01PrtFilCls *poTmpPrt,
                                                   sstDxf03DbCls      *poDxfDb)
  : sstQt01TabViewCls(poTmpPrt)
{
  poTabMdl = new sstQtDxf01TabMdlTextCls(0, poTmpPrt, poDxfDb);
  this->setModel( poTabMdl);

  connect(this->poTabMdl,SIGNAL(sstSgnlTabChanged(sstQt01ShapeItem)),this,SLOT(sstSlotChangeTab(sstQt01ShapeItem)));

}
//=============================================================================
sstQtDxf01TabViewTextCls::~sstQtDxf01TabViewTextCls()
{
  delete poTabMdl;
}
//=============================================================================
