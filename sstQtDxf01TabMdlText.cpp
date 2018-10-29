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
//  sstQtDxf01TabMdlText.cpp   25.05.18  Re.   21.03.18  Re.
//
//  Functions for Class "sstQtDxf01TabMdlText"
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
sstQtDxf01TabMdlTextCls::sstQtDxf01TabMdlTextCls(QObject *parent, sstMisc01PrtFilCls *poTmpPrt, sstDxf03DbCls *poTmpDatabase):sstQt01TabMdlCls(parent)
{
  this->poPrt = poTmpPrt;
  this->poDatabase = poTmpDatabase;
  
  dREC04RECNUMTYP dRecNum = this->poDatabase->EntityCount(RS2::EntityText);
  
  for (dREC04RECNUMTYP ll=1; ll<=dRecNum; ++ll)
  {
    this->sstTabVector.push_back(ll);
  }

  connect(this,SIGNAL(sstSgnlTabUpdated(sstQt01ShapeItem)),this,SLOT(sstSlotUpdateTab(sstQt01ShapeItem)));

}
 
// // Constructor
sstQtDxf01TabMdlTextCls::~sstQtDxf01TabMdlTextCls()
{
 
}
 
// Count actual number of records
int sstQtDxf01TabMdlTextCls::rowCount(const QModelIndex &) const
{
  int iStat = 0;
//  Bloc Code Generation Start
  iStat = this->poDatabase->EntityCount(RS2::EntityText);
//  Bloc Code Generation End
  return iStat;
}
 
// return number of table columns
int sstQtDxf01TabMdlTextCls::columnCount(const QModelIndex &) const
{
  int iStat = 0;
//  Bloc Code Generation Start
  iStat = 14;
//  Bloc Code Generation End
  return iStat;
}
 
// return number of table columns
QVariant sstQtDxf01TabMdlTextCls::data(const QModelIndex &index, int role) const
{
//  Bloc Code Generation Start
  DL_TextData oTypRec(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0,0,0,"","",0.0);
  DL_Attributes oDLAttributes;
 
  int iStat = this->poDatabase->ReadText( 0, this->sstTabVector[index.row()], &oTypRec, &oDLAttributes);
  assert (iStat == 0);
 
  switch(role){
  case Qt::DisplayRole:
    {
      switch (index.column())
      {
        case 0: return QString::number(oTypRec.ipx, 'f', 4); break;
        case 1: return QString::number(oTypRec.ipy, 'f', 4); break;
        case 2: return QString::number(oTypRec.ipz, 'f', 4); break;
        case 3: return QString::number(oTypRec.apx, 'f', 4); break;
        case 4: return QString::number(oTypRec.apy, 'f', 4); break;
        case 5: return QString::number(oTypRec.apz, 'f', 4); break;
        case 6: return QString::number(oTypRec.height, 'f', 4); break;
        case 7: return QString::number(oTypRec.xScaleFactor, 'f', 4); break;
        case 8: return oTypRec.textGenerationFlags; break;
        case 9: return oTypRec.hJustification; break;
        case 10: return oTypRec.vJustification; break;
        case 11: return QString::fromUtf8(oTypRec.text.c_str()); break;
        case 12: return QString::fromUtf8(oTypRec.style.c_str()); break;
        case 13: return QString::number(oTypRec.angle, 'f', 4); break;
      }
    }
  }
  return QVariant();
//  Bloc Code Generation End
}
 
// return number of table columns
QVariant sstQtDxf01TabMdlTextCls::headerData(int section, Qt::Orientation orientation, int role) const
{
//  Bloc Code Generation Start
  if (role == Qt::DisplayRole)
  {
      if (orientation == Qt::Horizontal) {
          switch (section)
          {
        case 0: return QString("ipx");
        case 1: return QString("ipy");
        case 2: return QString("ipz");
        case 3: return QString("apx");
        case 4: return QString("apy");
        case 5: return QString("apz");
        case 6: return QString("height");
        case 7: return QString("xScaleFactor");
        case 8: return QString("textGenerationFlags");
        case 9: return QString("hJustification");
        case 10: return QString("vJustification");
        case 11: return QString("text");
        case 12: return QString("style");
        case 13: return QString("angle");
      }
    }
  }
  return QVariant();
//  Bloc Code Generation End
}
 
// return number of table columns
bool sstQtDxf01TabMdlTextCls::setData(const QModelIndex & index, const QVariant & value, int role)
{
//  Bloc Code Generation Start
 
if (role == Qt::EditRole)
{
  //save value from editor to oTestRecDss
  DL_TextData oTypRec(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0,0,0,"","",0.0);
  DL_Attributes oDLAttributes;
  dREC04RECNUMTYP dMainRecNo = 0;
 
  dREC04RECNUMTYP dRecNo = index.row() +1;
  this->poDatabase->ReadText( 0, this->sstTabVector[index.row()], &oTypRec, &oDLAttributes);
 
  bool bOK = 1;
      switch (index.column())
      {
        case 0: 
      {
        oTypRec.ipx = value.toDouble(&bOK); break;
      }
        case 1: 
      {
        oTypRec.ipy = value.toDouble(&bOK); break;
      }
        case 2: 
      {
        oTypRec.ipz = value.toDouble(&bOK); break;
      }
        case 3: 
      {
        oTypRec.apx = value.toDouble(&bOK); break;
      }
        case 4: 
      {
        oTypRec.apy = value.toDouble(&bOK); break;
      }
        case 5: 
      {
        oTypRec.apz = value.toDouble(&bOK); break;
      }
        case 6: 
      {
        oTypRec.height = value.toDouble(&bOK); break;
      }
        case 7: 
      {
        oTypRec.xScaleFactor = value.toDouble(&bOK); break;
      }
        case 8: 
      {
        oTypRec.textGenerationFlags = value.toInt(&bOK); break;
      }
        case 9: 
      {
        oTypRec.hJustification = value.toInt(&bOK); break;
      }
        case 10: 
      {
        oTypRec.vJustification = value.toInt(&bOK); break;
      }
        case 11: 
      {
        QString locStr = value.toString();
        oTypRec.text = locStr.toStdString(); break;
      }
        case 12: 
      {
        QString locStr = value.toString();
        oTypRec.style = locStr.toStdString(); break;
      }
        case 13: 
      {
        oTypRec.angle = value.toDouble(&bOK); break;
      }
 
  }
  if (bOK) this->poDatabase->WriteText( 0, oTypRec, oDLAttributes, &dRecNo, &dMainRecNo);
 
  }
  return true;
//  Bloc Code Generation End
}
 
// return number of table columns
Qt::ItemFlags sstQtDxf01TabMdlTextCls::flags(const QModelIndex &index) const
{
//  Bloc Code Generation Start
  return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
//  Bloc Code Generation End
}
 
// return number of table columns
bool sstQtDxf01TabMdlTextCls::removeRows(int position, int rows, const QModelIndex &index)
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
bool sstQtDxf01TabMdlTextCls::insertRows(int position, int rows, const QModelIndex &index)
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
//=============================================================================
void sstQtDxf01TabMdlTextCls::sstSlotUpdateTab(sstQt01ShapeItem oShapeItem)
{

  // Update path storage with shapeitem at index position
  // int iStat = this->poPathStorage->ReplaceShape( 0, oShapeItem.getExternId(), oShapeItem);
  // assert(iStat >= 0);

  // Get actual size of path data table
  // int iRow = (int) this->poPathStorage->RecordCount();
  // int iCol = (int) this->poPathStorage->ColumnCount();
  int iRow = (int) this->poDatabase->EntityCount(RS2::EntityText);
  int iCol = (int) this->poDatabase->ColumnCount(RS2::EntityText);

  // Indexing whole model table
  QModelIndex oIndex1 = this->index(0,0);
  QModelIndex oIndex2 = this->index(iRow-1,iCol-1);

  // emit system signal -dataChanged- is necessary, because
  // data are changed outside of Table Model in map.
  emit this->dataChanged(oIndex1,oIndex2);
}
//=============================================================================
