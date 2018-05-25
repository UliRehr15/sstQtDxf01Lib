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
// TabTest_Dialog.cpp    25.05.18  Re.   25.05.18  Re.
//

#include <assert.h>

#include <QtWidgets>
#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTextBrowser>

#include <string>

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
#include <sstQtDxf01QtTab.h>
#include <sstQtDxf01Lib.h>

#include "sstQtDxf01TabTest.h"
// #include "sstQt01LibTestTab2.h"

Dialog::Dialog()
{

  int iStat = 0;

  this->poPrt = new sstMisc01PrtFilCls;
  this->poPrt->SST_PrtAuf(1,(char*)"sstQt01TabTest2.log");

  std::string oDxfFilNam = "Test_Line_Utm.dxf";

  this->poDxfDb = new sstDxf03DbCls(this->poPrt);
  iStat = this->poDxfDb->ReadAllFromDxf(0,oDxfFilNam);
  assert(iStat == 0);

  this->poTab1View = new sstQtDxf01TabViewLineCls(this->poPrt,this->poDxfDb);
  this->poTab2View = new sstQtDxf01TabViewCircleCls(this->poPrt,this->poDxfDb);
  this->poTab3View = new sstQtDxf01TabViewMTextCls(this->poPrt,this->poDxfDb);
  this->poTab4View = new sstQtDxf01TabViewPointCls(this->poPrt,this->poDxfDb);
  this->poTab5View = new sstQtDxf01TabViewTextCls(this->poPrt,this->poDxfDb);

  poTextWidget1 = new QTextBrowser;
  poTextWidget1->setPlainText(tr("TextWidget1"));

  stackedWidget = new QStackedWidget;
        stackedWidget->addWidget(poTextWidget1);
        stackedWidget->addWidget(poTab1View);
        stackedWidget->addWidget(poTab2View);
        stackedWidget->addWidget(poTab3View);
        stackedWidget->addWidget(poTab4View);
        stackedWidget->addWidget(poTab5View);

  treeView = new QTreeView(this);
  standardModel = new QStandardItemModel ;
  QStandardItem *rootNode = standardModel->invisibleRootItem();


  //defining a couple of items
  QStandardItem *rootItem = new QStandardItem("Dxf File");
  QStandardItem *tabItem1 =  new QStandardItem("LINE Table");
  QStandardItem *tabItem2 =     new QStandardItem("CIRCLE Table");
  QStandardItem *tabItem3 =     new QStandardItem("MTEXT Table");
  QStandardItem *tabItem4 =     new QStandardItem("POINT Table");
  QStandardItem *tabItem5 =     new QStandardItem("TEXT Table");

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
    createMenu();
    createHorizontalGroupBox();

    bigEditor = new QTextEdit;
    bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                               "in the top-level layout."));

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));
}

Dialog::~Dialog()
{
  delete this->buttonBox;
  delete this->bigEditor;

  delete this->poTab5View;
  delete this->poTab4View;
  delete this->poTab3View;
  delete this->poTab2View;
  delete this->poTab1View;
  int iStat = this->poDxfDb->WritAll2DxfFil(0,"Test_Line_Utm.dxf");
  assert(iStat == 0);
  delete this->poDxfDb;
  this->poPrt->SST_PrtZu(1);
  delete this->poPrt;
}

void Dialog::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}

void Dialog::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(treeView);

    layout->addWidget(stackedWidget);

    horizontalGroupBox->setLayout(layout);
}

//QLabel *Dialog::createLabel(const QString &text)
//{
//    QLabel *label = new QLabel(text);
//    label->setFrameStyle(QFrame::Box | QFrame::Raised);
//    return label;
//}

void Dialog::selectionChangedSlot(const QItemSelection & /*newSelection*/, const QItemSelection & /*oldSelection*/)
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
