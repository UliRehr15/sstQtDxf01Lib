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
// sstQtDxf01TabTest.h    18.10.18  Re.   25.05.18  Re.
//
// Testframe for Class DxfDbTableViewEditWidget
//

#ifndef SSTQTDXF01TABTEST_H
#define SSTQTDXF01TABTEST_H

#include <QtWidgets>
#include <QDialog>
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


QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
// class QView;
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();
    ~Dialog();

private:
    void createMenu();

    enum { NumGridRows = 3, NumButtons = 2 };

    QMenuBar *menuBar;
    QTextEdit *bigEditor;
    QDialogButtonBox *buttonBox;

    QMenu *fileMenu;
    QAction *exitAction;

    sstQtDxf01TabGroupBoxCls *poDxfGroupBox;

    QVBoxLayout *mainLayout;
    sstMisc01PrtFilCls *poPrt;

    sstDxf03DbCls *poDxfDb;
    std::string    oDxfFilNam;  // Dxf File Name


};

#endif // DIALOG_H
