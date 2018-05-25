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
// sstQtDxf01TabTest.h    25.05.18  Re.   25.05.18  Re.
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
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();
    ~Dialog();

private slots:
    void selectionChangedSlot(const QItemSelection & newSelection, const QItemSelection & oldSelection);

private:
    void createMenu();
    void createHorizontalGroupBox();

    enum { NumGridRows = 3, NumButtons = 2 };

    QMenuBar *menuBar;
    QGroupBox *horizontalGroupBox;
    QTextEdit *bigEditor;
    QDialogButtonBox *buttonBox;

    QMenu *fileMenu;
    QAction *exitAction;

    QTreeView *treeView;
    QStandardItemModel *standardModel;
    QTextBrowser *poTextWidget1;
    QVBoxLayout *mainLayout;
    QStackedWidget *stackedWidget;

    sstQtDxf01TabViewLineCls    *poTab1View;
    sstQtDxf01TabViewCircleCls  *poTab2View;
    sstQtDxf01TabViewMTextCls   *poTab3View;
    sstQtDxf01TabViewPointCls   *poTab4View;
    sstQtDxf01TabViewTextCls    *poTab5View;
    sstMisc01PrtFilCls *poPrt;

    sstDxf03DbCls *poDxfDb;

};

#endif // DIALOG_H
