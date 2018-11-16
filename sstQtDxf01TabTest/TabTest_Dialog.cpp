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

  int my_argc = qApp->arguments().count();
  if (my_argc != 2) assert(0);
  QString my_argv_1 = qApp->arguments().at(1);

  this->poPrt = new sstMisc01PrtFilCls;
  this->poPrt->SST_PrtAuf(1,(char*)"sstQt01TabTest.log");

  // std::string oDxfFilNam = "Test_Line_Utm.dxf";
  this->oDxfFilNam = my_argv_1.toStdString();

  this->poDxfDb = new sstDxf03DbCls(this->poPrt);
  iStat = this->poDxfDb->ReadAllFromDxf(0,this->oDxfFilNam);
  if (iStat < 0)
  {
    this->poPrt->SST_PrtWrtChar(1,(char*)oDxfFilNam.c_str(),(char*)"File not found: ");
    this->poPrt->SST_PrtWrt(1,(char*) "Tool aborted");
    this->poPrt->SST_PrtZu(1);
    exit(0);
  }

    this->poDxfGroupBox = new sstQtDxf01TabGroupBoxCls(this->poPrt, this->poDxfDb, 0);

    createMenu();

    bigEditor = new QTextEdit;
    bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                               "in the top-level layout."));

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(poDxfGroupBox);
    mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));
}

Dialog::~Dialog()
{
  delete this->buttonBox;
  delete this->bigEditor;

  // int iStat = this->poDxfDb->WritAll2DxfFil(0,"Test_Line_Utm.dxf");
  int iStat = this->poDxfDb->WritAll2DxfFil( 0, this->oDxfFilNam);
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

