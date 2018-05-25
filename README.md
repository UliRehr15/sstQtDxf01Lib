# sstQtDxf01Lib

sst Qt/Dxf Classes and functions.

Show dxf data in tables and map at the same time.

Compile with QT 5.5 and QTCreator 3.5.1

Structure of coding projects should be:

.. [libs]  <BR>
   [dxflib] from github <BR>
   [sstLibreCad2Lib] <BR>
   [sst_str01_lib]  <BR>
   [sst_math01_lib]  <BR>
   [sst_misc01_lib]  <BR>
   [sst_rec04_lib]  <BR>
   [sst_dxf03_lib]  <BR>
   [sstQt01Lib]  <BR>

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
