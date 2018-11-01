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
// sstQtDxf01TabGroupBox.cpp    29.10.18  Re.   11.10.18  Re.
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

  connect(this, SIGNAL(sstSgnlTabChanged(sstQt01ShapeItem)), this->poTabLineView, SLOT(sstSlotUpdateTabLine(sstQt01ShapeItem)));
  connect(this->poTabLineView, SIGNAL(sstSgnlTabLineChanged(dREC04RECNUMTYP)), this, SLOT(sstSlotUpdateMap(dREC04RECNUMTYP)));

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

  DL_LineData oLineRec(0,0,0,0,0,0);
  DL_Attributes oAttrib;
  dREC04RECNUMTYP dRecNo = 0;
  dREC04RECNUMTYP dMainRecNo = 0;
  // Convert ShapeItem to DxfLineRec
  this->poDxfPathCnvt->WriteItemPathtoLINE ( 0, oShapeItem, &oLineRec);
  dRecNo = oShapeItem.getExternId();
  this->poDxfDb->WriteLine(0,oLineRec,oAttrib,&dRecNo,&dMainRecNo);

  emit this->poTabLineView->sstSgnlTabLineUpdated(oShapeItem);
}
//=============================================================================
void sstQtDxf01TabGroupBoxCls::sstSlotUpdateMap(dREC04RECNUMTYP dLineRecNo)
{
  if (this->poDxfPathCnvt == 0) return;

  sstQt01ShapeItem oShapeItem;
  // Convert ShapeItem to DxfLineRec
  this->poDxfPathCnvt->WriteLINEtoItemPath( 0, dLineRecNo, &oShapeItem);

  emit this->sstSgnlTabChanged(oShapeItem);
}
//=============================================================================
