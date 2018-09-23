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
//  sstQtDxf01TabMdlCircle.cpp   25.05.18  Re.   21.03.18  Re.
//
//  Functions for Class "sstQtDxf01TabMdlCircle"
//
//  Class Code generated by github/UliRehr15/sstCpp01Lib/sst_generate_qttab_lib

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
#include <string>
 
#include <sstStr01Lib.h>
#include <sstMath01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
 
#include <list>
#include <dl_dxf.h>
#include <dl_creationadapter.h>
#include <rs_vector.h>
#include <QtWidgets>
#include <sstQt01Lib.h>
// #include <sstDxf03TypLib.h>
#include <sstDxf03Lib.h>
 
#include "sstQtDxf01QtTab.h"
#include "sstQtDxf01Lib.h"

// // Constructor
sstQtDxf01TabMdlCircleCls::sstQtDxf01TabMdlCircleCls(QObject *parent, sstMisc01PrtFilCls *poTmpPrt, sstDxf03DbCls *poTmpDatabase):sstQt01TabMdlCls(parent)
{
  this->poPrt = poTmpPrt;
  this->poDatabase = poTmpDatabase;
  
  dREC04RECNUMTYP dRecNum = this->poDatabase->EntityCount(RS2::EntityCircle);
  
  for (dREC04RECNUMTYP ll=1; ll<=dRecNum; ++ll)
  {
    this->sstTabVector.push_back(ll);
  }
}
 
// // Constructor
sstQtDxf01TabMdlCircleCls::~sstQtDxf01TabMdlCircleCls()
{
 
}
 
// Count actual number of records
int sstQtDxf01TabMdlCircleCls::rowCount(const QModelIndex &) const
{
  int iStat = 0;
//  Bloc Code Generation Start
  iStat = this->poDatabase->EntityCount(RS2::EntityCircle);
//  Bloc Code Generation End
  return iStat;
}
 
// return number of table columns
int sstQtDxf01TabMdlCircleCls::columnCount(const QModelIndex &) const
{
  int iStat = 0;
//  Bloc Code Generation Start
  iStat = 4;
//  Bloc Code Generation End
  return iStat;
}
 
// return number of table columns
QVariant sstQtDxf01TabMdlCircleCls::data(const QModelIndex &index, int role) const
{
//  Bloc Code Generation Start
  DL_CircleData oTypRec(0,0,0,1);
  DL_Attributes oDLAttributes;
 
  int iStat = this->poDatabase->ReadCircle( 0, this->sstTabVector[index.row()], &oTypRec, &oDLAttributes);
  assert (iStat == 0);
 
  switch(role){
  case Qt::DisplayRole:
    {
      switch (index.column())
      {
        case 0: return QString::number(oTypRec.cx, 'f', 4); break;
        case 1: return QString::number(oTypRec.cy, 'f', 4); break;
        case 2: return QString::number(oTypRec.cz, 'f', 4); break;
        case 3: return QString::number(oTypRec.radius, 'f', 4); break;
      }
    }
  }
  return QVariant();
//  Bloc Code Generation End
}
 
// return number of table columns
QVariant sstQtDxf01TabMdlCircleCls::headerData(int section, Qt::Orientation orientation, int role) const
{
//  Bloc Code Generation Start
  if (role == Qt::DisplayRole)
  {
      if (orientation == Qt::Horizontal) {
          switch (section)
          {
        case 0: return QString("cx");
        case 1: return QString("cy");
        case 2: return QString("cz");
        case 3: return QString("radius");
      }
    }
  }
  return QVariant();
//  Bloc Code Generation End
}
 
// return number of table columns
bool sstQtDxf01TabMdlCircleCls::setData(const QModelIndex & index, const QVariant & value, int role)
{
//  Bloc Code Generation Start
 
if (role == Qt::EditRole)
{
  //save value from editor to oTestRecDss
  DL_CircleData oTypRec(0,0,0,1);
  DL_Attributes oDLAttributes;
  dREC04RECNUMTYP dMainRecNo = 0;
 
  dREC04RECNUMTYP dRecNo = index.row() +1;
  this->poDatabase->ReadCircle( 0, this->sstTabVector[index.row()], &oTypRec, &oDLAttributes);
 
  bool bOK = 1;
      switch (index.column())
      {
        case 0: 
      {
        oTypRec.cx = value.toDouble(&bOK); break;
      }
        case 1: 
      {
        oTypRec.cy = value.toDouble(&bOK); break;
      }
        case 2: 
      {
        oTypRec.cz = value.toDouble(&bOK); break;
      }
        case 3: 
      {
        oTypRec.radius = value.toDouble(&bOK); break;
      }
 
  }
  if (bOK) this->poDatabase->WriteCircle( 0, oTypRec, oDLAttributes, &dRecNo, &dMainRecNo);
 
  }
  return true;
//  Bloc Code Generation End
}
 
// return number of table columns
Qt::ItemFlags sstQtDxf01TabMdlCircleCls::flags(const QModelIndex &index) const
{
//  Bloc Code Generation Start
  return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
//  Bloc Code Generation End
}
 
// return number of table columns
bool sstQtDxf01TabMdlCircleCls::removeRows(int position, int rows, const QModelIndex &index)
{
//  Bloc Code Generation Start
  Q_UNUSED(index);
  beginRemoveRows(QModelIndex(), position, position + rows - 1);
 
  // rows is always = 1 at the moment
  // Position is 0 > n-1
 
  for (int row = 0; row < rows; ++row) {
    // this->poDatabase->RecSetDeleted(0,position+1);
  }
  endRemoveRows();
 
  this->sstTabVector.erase (this->sstTabVector.begin()+position);
 
  return true;
//  Bloc Code Generation End
}
 
// return number of table columns
bool sstQtDxf01TabMdlCircleCls::insertRows(int position, int rows, const QModelIndex &index)
{
//  Bloc Code Generation Start
  Q_UNUSED(index);
  beginInsertRows(QModelIndex(), position, position + rows - 1);
  
  // rows is always = 1 at the moment
  // Position is 0 > n-1
  dREC04RECNUMTYP dRecNo = 0;
  
  for (int row = 0; row < rows; ++row) {
    // this->poDatabase->Read(0,this->poDatabase->count(),&this->oTypeRec);
    // this->poDatabase->WritNew( 0, &this->oTypeRec, &dRecNo);
  }
 
  endInsertRows();
 
  this->sstTabVector.push_back(dRecNo);
  
  return true;
//  Bloc Code Generation End
}