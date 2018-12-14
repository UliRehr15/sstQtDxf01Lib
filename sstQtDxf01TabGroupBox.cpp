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
// sstQtDxf01TabGroupBox.cpp    14.12.18  Re.   11.10.18  Re.
//
// Tree View Widget for group of dxf entity view tables

#include <assert.h>

#include <string>

#include <dl_dxf.h>
#include <dl_creationadapter.h>

#include <rs_color.h>
#include <rs_vector.h>

#include <QtWidgets>
#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTextBrowser>

#include <sstStr01Lib.h>
#include <sstMath01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstQt01Lib.h>
#include <sstDxf03Lib.h>
#include <sstQtDxf01QtTab.h>
#include <sstQtDxf01Lib.h>

//==============================================================================
// sstQtDxf01TabGroupBoxCls::sstQtDxf01TabGroupBoxCls(sstMisc01PrtFilCls *poPrt, sstDxf03DbCls *poDxfDb)
sstQtDxf01TabGroupBoxCls::sstQtDxf01TabGroupBoxCls(sstMisc01PrtFilCls *poPrt,
                                                   sstDxf03DbCls *poDxfDb,
                                                   sstQtDxf01PathConvertCls  *poDxfPathConvert)
{
  this->poDxfPathCnvt = poDxfPathConvert;
  this->poDxfDb       = poDxfDb;
  this->poPrt         = poPrt;

  this->setTitle("Test-Tabellen");

  this->poTabLineView = new sstQtDxf01TabViewLineCls( poPrt, poDxfDb);
  this->poTabCircleView = new sstQtDxf01TabViewCircleCls( poPrt, poDxfDb);
  this->poTabMTextView = new sstQtDxf01TabViewMTextCls( poPrt, poDxfDb);
  this->poTabPointView = new sstQtDxf01TabViewPointCls( poPrt, poDxfDb);
  this->poTabTextView = new sstQtDxf01TabViewTextCls( poPrt, poDxfDb);

  poTextWidget1 = new QTextBrowser;
  poTextWidget1->setPlainText(tr("TextWidget1"));

  stackedWidget = new QStackedWidget;
  stackedWidget->addWidget(poTextWidget1);
  stackedWidget->addWidget(poTabLineView);
  stackedWidget->addWidget(poTabCircleView);
  stackedWidget->addWidget(poTabMTextView);
  stackedWidget->addWidget(poTabPointView);
  stackedWidget->addWidget(poTabTextView);

  treeView = new QTreeView(this);
  standardModel = new QStandardItemModel ;
  QStandardItem *rootNode = standardModel->invisibleRootItem();

  //defining a couple of items
  QStandardItem *rootItem = new QStandardItem("Dxf File");
  QStandardItem *tabItem1 = new QStandardItem("LINE Table");
  QStandardItem *tabItem2 = new QStandardItem("CIRCLE Table");
  QStandardItem *tabItem3 = new QStandardItem("MTEXT Table");
  QStandardItem *tabItem4 = new QStandardItem("POINT Table");
  QStandardItem *tabItem5 = new QStandardItem("TEXT Table");

  //building up the hierarchy
  rootNode->appendRow(rootItem);
  rootItem->appendRow(tabItem1);
  rootItem->appendRow(tabItem2);
  rootItem->appendRow(tabItem3);
  rootItem->appendRow(tabItem4);
  rootItem->appendRow(tabItem5);

  //register the model
  treeView->setModel(standardModel);
  treeView->expandAll();

  //selection changes shall trigger a slot
  QItemSelectionModel *selectionModel= treeView->selectionModel();
  connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
          this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));

  // Update tables
  connect(this, SIGNAL(sstSgnlTabChanged(sstQt01ShapeItem)), this->poTabLineView, SLOT(sstSlotUpdateTabLine(sstQt01ShapeItem)));
  connect(this, SIGNAL(sstSgnlTabChanged(sstQt01ShapeItem)), this->poTabCircleView, SLOT(sstSlotUpdateTabCircle(sstQt01ShapeItem)));

  // Update map
  connect(this->poTabLineView, SIGNAL(sstSgnlTabLineChanged(sstQt01MapSignalCls)), this, SLOT(sstSlotUpdateMap(sstQt01MapSignalCls)));
  connect(this->poTabCircleView, SIGNAL(sstSgnlTabCircleChanged(sstQt01MapSignalCls)), this, SLOT(sstSlotUpdateMap(sstQt01MapSignalCls)));

  // horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
  QHBoxLayout *layout = new QHBoxLayout;

  layout->addWidget(treeView);

  layout->addWidget(stackedWidget);

  this->setLayout(layout);

}
//==============================================================================
sstQtDxf01TabGroupBoxCls::~sstQtDxf01TabGroupBoxCls()
{
  delete poTextWidget1;

  delete poTabLineView;
  delete poTabCircleView;
  delete poTabMTextView;
  delete poTabPointView;
  delete poTabTextView;

  delete treeView;
  delete stackedWidget;
  delete standardModel;
}
//==============================================================================
void sstQtDxf01TabGroupBoxCls::selectionChangedSlot(const QItemSelection & /*newSelection*/, const QItemSelection & /*oldSelection*/)
{
    //get the text of the selected item
    const QModelIndex index = treeView->selectionModel()->currentIndex();
    QString selectedText = index.data(Qt::DisplayRole).toString();
    int selectedInt = index.row();  // get actual row of tree
    //find out the hierarchy level of the selected item
    int hierarchyLevel=1;
    QModelIndex seekRoot = index;
    while(seekRoot.parent() != QModelIndex())
    {
        seekRoot = seekRoot.parent();
        hierarchyLevel++;
    }
    QString showString = QString("%1, Level %2").arg(selectedText)
                         .arg(hierarchyLevel);
    setWindowTitle(showString);
    if (hierarchyLevel == 1)
    {
      stackedWidget->setCurrentIndex(0);
    }
    else
    {
      if (selectedInt == 0) stackedWidget->setCurrentIndex(1);
      else stackedWidget->setCurrentIndex(2);
    }
}
//=============================================================================
void sstQtDxf01TabGroupBoxCls::sstSlotUpdateTab(sstQt01ShapeItem oShapeItem)
{
  if (this->poDxfPathCnvt == 0) return;

  int iStat = 0;
  DL_Attributes oAttrib;
  dREC04RECNUMTYP dRecNo = 0;
  dREC04RECNUMTYP dMainRecNo = 0;
  std::string oEntTypeStr = oShapeItem.getExternStr();
  // sstDxf03DbCls oDxfDb;
  RS2::EntityType eDxfEntTyp =  this->poDxfDb->CnvtTypeString2Enum(oEntTypeStr);
  switch (eDxfEntTyp)
  {
  case RS2::EntityLine:
{
  // Convert ShapeItem to DxfLineRec
  DL_LineData oLineRec(0,0,0,0,0,0);
  this->poDxfPathCnvt->WriteItemPathtoLINE ( 0, oShapeItem, &oLineRec);
  dRecNo = oShapeItem.getExternId();
  iStat = this->poDxfDb->WriteLine(0,oLineRec,oAttrib,&dRecNo,&dMainRecNo);
  assert(iStat == 0);
  emit this->poTabLineView->sstSgnlTabLineUpdated(oShapeItem);
}
  break;
  case RS2::EntityCircle:
{
  // Convert ShapeItem to DxfLineRec
    DL_CircleData oCircleRec(0,0,0,1);    // Entity Circle from dxflib
  this->poDxfPathCnvt->WriteItemPathtoCIRCLE ( 0, oShapeItem, &oCircleRec);
  dRecNo = oShapeItem.getExternId();
  iStat = this->poDxfDb->WriteCircle(0,oCircleRec,oAttrib,&dRecNo,&dMainRecNo);
  assert(iStat == 0);
  emit this->poTabCircleView->sstSgnlTabCircleUpdated(oShapeItem);
}
  break;
  default: assert(0); break;
  }

}
//=============================================================================
// void sstQtDxf01TabGroupBoxCls::sstSlotUpdateMap(dREC04RECNUMTYP dLineRecNo)
void sstQtDxf01TabGroupBoxCls::sstSlotUpdateMap(sstQt01MapSignalCls oMapSignal)
{
  if (this->poDxfPathCnvt == 0) return;

  sstDxf03EntityTypeCls oDxfEntityCnvt;
  RS2::EntityType eEntType;
  eEntType = oDxfEntityCnvt.String2Enum(oMapSignal.getExternTypeStr());
  dREC04RECNUMTYP dEntRecNo = oMapSignal.getExternTypeTabRecNo();
  sstQt01ShapeItem oShapeItem;
  dREC04RECNUMTYP dItemNo = 0;
  dItemNo = this->poDxfDb->getSectEntRecNo(0,eEntType,dEntRecNo);
  // record number in main table
  // dItemNo = oMapSignal.getShapeItemListRecNo();
  dREC04RECNUMTYP dItemNo2 = 0;  // list number of Shape Item
  // Get ShapeItem List number for main record number
  dItemNo2 = this->poDxfPathCnvt->getItemListNo( 0, dItemNo);
  // assert(iStat == 0);
  oMapSignal.setShapeItemListRecNo(dItemNo2);

  // Convert Dxf Entity to Qt Shape Item for Mapping
  switch (eEntType)
  {
  case (RS2::EntityLine):
    this->poDxfPathCnvt->WriteLINEtoItemPath( 0, dEntRecNo, &oShapeItem);
    // this->poDxfDb->
    break;
  case (RS2::EntityCircle):
    this->poDxfPathCnvt->WriteCIRCLEtoItemPath( 0, dEntRecNo, &oShapeItem);
    break;
  default: assert(0); break;
  }

  std::string oTypeStr;
  oTypeStr = this->poDxfDb->CnvtTypeEnum2String(eEntType);
  oShapeItem.setExternStr(oTypeStr);
  oShapeItem.setExternId(dEntRecNo);
  oShapeItem.setInternId(dItemNo2);

  // Send to map
  emit this->sstSgnlTabChanged(oShapeItem);
}
//=============================================================================
