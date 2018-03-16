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
// sstQtDxf01LibTest.cpp    23.02.18  Re.    14.08.16  Re.

#include <assert.h>

#include <QApplication>
#include <QtWidgets>

#include <list>

#include <dl_dxf.h>
#include <dl_creationadapter.h>

#include <rs_vector.h>

#include <sstStr01Lib.h>
#include <sstMath01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstDxf03Lib.h>
#include <sstQt01Lib.h>
#include <sstQtDxf01Lib.h>

#include "sstQtDxf01LibTest.h"

//==============================================================================
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dialog dialog;
    dialog.show();

    return app.exec();
}
//==============================================================================
Dialog::Dialog()
{
  int iStat = 0;
  std::string oDxfNamStr = "sstQtDxf01LibTest.dxf";
  // open protocol system
  this->poPrt = new sstMisc01PrtFilCls;
  this->poPrt->SST_PrtAuf(1,(char*)"sstQtDxf01LibTest.log");

  // Create new empty sstDxf database
  this->poDxfDb = new sstDxf03DbCls(this->poPrt);

  iStat = this->poDxfDb->ReadAllFromDxf( 0, oDxfNamStr);

  if (iStat < 0)
  {
    this->poPrt->SST_PrtWrtChar(1,(char*)oDxfNamStr.c_str(),(char*)"File not found: ");
    this->poPrt->SST_PrtZu(1);
    assert(0);
  }

  // create new map widget with sstpainterpath storage
  this->poPathStorage = new sstQt01PathStorageCls(this->poPrt);

  // open new Dxf_Path converter object
  this->poDxfPathConvert = new sstQtDxf01PathConvertCls(this->poDxfDb,this->poPathStorage, this->poPrt);

  // fill Path Storage from Dxf database
  iStat = poDxfPathConvert->WritAlltoPathStorage( 0);
  assert(iStat == 0);

  this->poPathWidget = new sstQt01PathPaintWidgetCls(this->poPrt, this->poPathStorage);

  createMenu();
    createHorizontalGroupBox();
    createGridGroupBox();
    createFormGroupBox();

    bigEditor = new QTextEdit;
    bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                               "in the top-level layout."));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    // mainLayout->addWidget(horizontalGroupBox);
    // mainLayout->addWidget(gridGroupBox);
    // mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(this->poPathWidget);
    mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));
}
//==============================================================================
Dialog::~Dialog()
{
  // write all path from intern path storage to inter sst sstDxf database
  int iStat = poDxfPathConvert->WriteAllPath2Dxf(0);
  assert(iStat == 0);

  // Write intern sst dxf database to dxf file
  iStat = poDxfPathConvert->WriteAll2Dxf(0,"sstQtDxf01LibTest.dxf");
  assert(iStat == 0);

  delete poDxfPathConvert;
  delete this->poPathWidget;
  delete this->poPathStorage;
  delete   this->poDxfDb;
  this->poPrt->SST_PrtZu(1);
  delete this->poPrt;
}
//==============================================================================
void Dialog::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}
//==============================================================================
void Dialog::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
    QHBoxLayout *layout = new QHBoxLayout;

    for (int i = 0; i < NumButtons; ++i) {
        buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
        layout->addWidget(buttons[i]);
    }
    horizontalGroupBox->setLayout(layout);
}
//==============================================================================
void Dialog::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("Grid layout"));
    QGridLayout *layout = new QGridLayout;

    for (int i = 0; i < NumGridRows; ++i) {
        labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
        lineEdits[i] = new QLineEdit;
        layout->addWidget(labels[i], i + 1, 0);
        layout->addWidget(lineEdits[i], i + 1, 1);
    }

    smallEditor = new QTextEdit;
    smallEditor->setPlainText(tr("This widget takes up about two thirds of the "
                                 "grid layout."));
    layout->addWidget(smallEditor, 0, 2, 4, 1);

    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}
//==============================================================================
void Dialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Form layout"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
    layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
    layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
    formGroupBox->setLayout(layout);
}
//==============================================================================
