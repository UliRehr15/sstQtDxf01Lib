# sstQtDxf01Lib

sst Qt/Dxf Classes and functions.

Show and editing of dxf data in Qt tables view and map view at the same time.

Test Apps:
sstQtDxf01LibTest: General testing of lib classes and functions
sstQtDxf01TabTest: Testframe for Table View Widget: Editing of Dxf Data in Tables
sstQtDxf01ViewTest: Testframe for Map Widget: Editing of Dxf Data in PainterPath Mapping Widget
sstQtDxf01TabViewTest: Testframe for parallel use of Tables and Map Widget

This Library is created with QT 5.9.5, QtCreator 4.5.2 and gcc 7.3.0.

Structure of coding projects should be:

.. [libs]  <BR>
.. [boost_1_68_0]  from www.boost.org <BR>
.. [muParser]  Version 2.2.5 from https://github.com/beltoforion/muparser <BR>
.. [dxflib]  Version 3.12.2 from www.qcad.org/Download <BR>
.. [sstLibreCad2Lib] <BR>
.. [sst_str01_lib]  <BR>
.. [sst_math01_lib]  <BR>
.. [sst_misc01_lib]  <BR>
.. [sst_rec04_lib]  <BR>
.. [sst_dxf03_lib]  <BR>
.. [sstQt01Lib]  <BR>

05.07.16: Version 1.0: github project created. <BR>
14.08.16: Version 1.1: qt example widgets/tooltips with storing path geometry in csv file. <BR>
05.09.16: Version 1.2: qt example widgets/tooltips with loading path geometry from csv file. <BR>
23.12.16: Version 1.3: qt example widgets/tooltips: Reading/Writing Hatches to Dxf-Format. <BR>
07.04.17: Version 1.4: New function ReadNextPath for PathStorageCls Class. <BR>
21.05.17: Version 1.5: Creating of sstDxf Database outside of widget. <BR>
23.02.18: Version 1.6: New function LineToPath with coordinate transformation. <BR>
                       Rewrite test-tool: Read/Draw of Line-Entities in world coordinates. <BR>
15.03.18: Version 1.7: New function PathtoLine with coordinate transformation. <BR>
                       Write with painterpath moved lines back to dxf file. <BR>
25.05.18: Version 1.8: Add Table classes for Entities LINE, POINT, CIRCLE, TEXT and MTEXT. <BR>
25.05.18: Version 1.9: Testframe for sst qt dxf entity tables.
21.09.18: Version 1.10: Updated to QT 5.9.5, QtCreator 4.5.2 and gcc 7.3.0. <BR>
                        Updated to dxflib 3.12.2. Exchange Path Tab Store with Path List Store. <BR>
23.09.18: Version 1.11: Fix problem backwriting into dxf in View changed PainterPath. <BR>
                        Fix problem with showing tooltip strings. <BR>
18.10.18: Version 1.12: Grouped Dxf Table Views in DxfTabGroupBoxWidget. <BR>
23.10.18: Version 1.13: Create new test frame for combined working with dxf map and tables. <BR>
29.10.18: Version 1.14: Signals ans Slots for refreshing tables from map and vice versa. <BR>
                        First only for Entity LINE in section entities. <BR>
01.11.18: Version 1.15: Better "in cell" editing for all tables. <BR>
06.11.18: Version 1.16: App TabViewTest: Call with dxf file name. <BR>
16.11.18: Version 1.17: new functions convert path to Circle and viceversa. <BR>
24.11.18: Version 1.18: Correct Convert function for circle. <BR>
14.12.18: Version 1.19: Fix problems updating tab from map / map from tab for LINE and CIRCLE. <BR>
                        New Display list in PathConvertObject, because not all items in main list <BR>
                        are displayed in map. <BR>
                        Use MapSignal Class for updating map from tab. <BR>
25.01.19: Version 1.20: Small Changes in documentation. <BR>
08.02.19: Version 1.21: New App Testframe sstQtDxf01ViewTest for DxfDbMappingViewWidget. <BR>

