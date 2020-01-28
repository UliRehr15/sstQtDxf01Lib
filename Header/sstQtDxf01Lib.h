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
// sstQtDxf01Lib.h   25.01.19  Re.   05.07.16  Re.
//
// Public Classes and functions for system "sstQtDxf01Lib"
//

#ifndef SST_QT_DXF01_LIB_HEADER
#define SST_QT_DXF01_LIB_HEADER

/**
 * @defgroup sstQtDxf01Lib sstQtDxf01Lib: cpp sst Qt Dxf library (Version 1)
 *
 * cpp sst qt dxf library <BR>
 *
 */

#include <dl_dxf.h>
#include <dl_creationadapter.h>

#include <rs_color.h>
#include <rs_vector.h>

#include <QtWidgets>
#include <QColor>
#include <QPainterPath>
#include <QPoint>

#include <sstStr01Lib.h>
#include <sstStr01FixColWidth.h>
#include <sstMath01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstQt01Lib.h>
#include <sstDxf03Lib.h>
#include "sstQtDxf01QtTab.h"
#include "sstQtDxf01Lib.h"



//==============================================================================
/**
* @brief converting between dxf and painter path objects <BR>
*
* Changed: 05.09.16  Re.
*
* @ingroup sstQtDxf01Lib
*
* @author Re.
*
* @date 05.09.16
*/
// ----------------------------------------------------------------------------
class sstQtDxf01PathConvertCls: public sstMath01CoorTrnCls
{
  public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor.  <BR>
  *
  * @param poDxfDb      [in out] Pointer to open sst Dxf Database object
  * @param poPathStore  [in out] Pointer to open sst Painter path storage object
  * @param poPrt        [in out] Pointer to open sst Protocol object
  */
  // ----------------------------------------------------------------------------
     sstQtDxf01PathConvertCls(sstDxf03DbCls *poDxfDb, sstQt01PathStoreViewCls *poPathStore, sstMisc01PrtFilCls *poPrt);  // Constructor
    ~sstQtDxf01PathConvertCls();  // Destructor
     //==============================================================================
     /**
     * @brief // Load all pathes from Dxf file in sstPathDxf object.  <BR>
     *
     * @param iKey    [in] For the moment 0
     * @param oFilNam [in] File name
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int LoadAllPathFromFile (int iKey, std::string oFilNam);
     //==============================================================================
     /**
     * @brief // store all pathes from sstPathDxf object into Dxf file.  <BR>
     *
     * @param iKey    [in] For the moment 0
     * @param oFilNam [in] File name
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int StoreAllPathToFile (int iKey, std::string oFilNam);
     //==============================================================================
     /**
     * @brief // read LINE object from sstDxf DB, transform to Device coordinates and write into open sstPath.  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param dLineRecNo  [in]  record number of LINE in sstDxf database
     * @param poPath      [in out] Qt PainterPath object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteLINEtoQtPath(int iKey, dREC04RECNUMTYP dLineRecNo, QPainterPath *poPath);
     //==============================================================================
     /**
     * @brief // read LINE from sstDxf DB, transform to Devices and write into open sstPath.  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param dLineRecNo  [in]  record number of LINE in sstDxf database
     * @param oBlkTrn     [in]  Transformation object from block to world
     * @param poPath      [in out] qt Path object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteLINEtoQtPathBlk(int iKey,
                                dREC04RECNUMTYP   dLineRecNo,
                                sstMath01TrnCls   oBlkTrn,
                                QPainterPath      *poPath);
     //==============================================================================
     /**
     * @brief // read POLYLINE from sstDxf DB, transform to Devices and write into open sstPath.  <BR>
     *
     * @param iKey          [in]  For the moment 0
     * @param dEntityRecNo  [in]  record number of LINE in sstDxf database
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritePOLYLINEtoQtPathBlk(int iKey,
                                  dREC04RECNUMTYP   dEntityRecNo);
     //==============================================================================
     /**
     * @brief // read HATCH from sstDxf DB, transform to Devices and write into open sstPath.  <BR>
     *
     * @param iKey          [in]  For the moment 0
     * @param dEntityRecNo  [in]  record number of LINE in sstDxf database
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteHATCHtoQtPathBlk(int iKey,
                               dREC04RECNUMTYP   dEntityRecNo);
     //==============================================================================
     /**
     * @brief // read HATCHLOOP from sstDxf DB, transform to Devices and write into open sstPath.  <BR>
     *
     * @param iKey          [in]  For the moment 0
     * @param dEntityRecNo  [in]  record number of LINE in sstDxf database
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteHATCHLOOPtoQtPathBlk(int iKey,
                                   dREC04RECNUMTYP   dEntityRecNo);
     //==============================================================================
     /**
     * @brief // read VERTEX from sstDxf DB, transform to Devices and write into open sstPath.  <BR>
     *
     * @param iKey          [in]  For the moment 0
     * @param dEntityRecNo  [in]  record number of VERTEX in sstDxf database
     * @param oBlkTrn       [in]  Transformation object from block to world
     * @param poPath        [in out] qt Path object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteVERTEXtoQtPathBlk(int iKey,
                                dREC04RECNUMTYP   dEntityRecNo,
                                sstMath01TrnCls   oBlkTrn,
                                QPainterPath      *poPath);
     //==============================================================================
     /**
     * @brief // convert sstShapeItem with QPainterPath to LINE Entity  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param oPathItem   [in]  sstShapeItem object
     * @param poDLLine    [out] Dxf LINE Entity
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteItemPathtoLINE(int                     iKey,
                             const sstQt01ShapeItem  oPathItem,
                             DL_LineData            *poDLLine);
     //==============================================================================
     /**
     * @brief // read INSERT object from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey          [in]  For the moment 0
     * @param dInsertRecNo  [in]  record number of INSERT in sstDxf database
     * @param poPath        [in out] Qt PainterPath object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteINSERTtoQtPath(int iKey, dREC04RECNUMTYP dInsertRecNo, QPainterPath *poPath);
     //==============================================================================
     /**
     * @brief // convert sstShapeItem with QPainterPath to INSERT Entity  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param oPathItem   [in]  sstShapeItem object
     * @param poDLInsert  [out] Dxf INSERT Entity
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteItemPathtoINSERT(int                     iKey,
                               const sstQt01ShapeItem  oPathItem,
                               DL_InsertData            *poDLInsert);
     //==============================================================================
     /**
     * @brief // read CIRCLE object from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey          [in]  For the moment 0
     * @param dCircleRecNo  [in]  record number of CIRCLE in sstDxf database
     * @param poPath        [in out] Qt PainterPath object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteCIRCLEtoQtPath(int               iKey,
                             dREC04RECNUMTYP   dCircleRecNo,
                             QPainterPath     *poPath);
     //==============================================================================
     /**
     * @brief // read CIRCLE object from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey          [in]  For the moment 0
     * @param dCircleRecNo  [in]  record number of CIRCLE in sstDxf database
     * @param oBlkTrn       [in]  Transformation object from block to world
     * @param poPath        [in out] qt Path object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteCIRCLEtoQtPathBlk(int               iKey,
                                dREC04RECNUMTYP   dCircleRecNo,
                                sstMath01TrnCls   oBlkTrn,
                                QPainterPath      *poPath);
     //==============================================================================
     /**
     * @brief // read POINT object from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey          [in]  For the moment 0
     * @param dPointRecNo   [in]  record number of POINT in sstDxf database
     * @param poPath        [in out] Qt PainterPath object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritePOINTtoQtPath(int               iKey,
                            dREC04RECNUMTYP   dPointRecNo,
                            QPainterPath     *poPath);
     //==============================================================================
     /**
     * @brief // read POLYLINE object from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey             [in]  For the moment 0
     * @param dPolylineRecNo   [in]  record number of POLYLINE in sstDxf database
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritePOLYLINEtoQtPath(int               iKey,
                                 dREC04RECNUMTYP   dPolylineRecNo);
     //==============================================================================
     /**
     * @brief // read HATCH object from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey           [in]  For the moment 0
     * @param dEntityRecNo   [in]  record number of Entity in sstDxf database
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteHATCHtoQtPath(int               iKey,
                            dREC04RECNUMTYP   dEntityRecNo);
     //==============================================================================
     /**
     * @brief // read HATCHLOOP object from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey           [in]  For the moment 0
     * @param dEntityRecNo   [in]  record number of Entity in sstDxf database
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteHATCHLOOPtoQtPath(int               iKey,
                                dREC04RECNUMTYP   dEntityRecNo);
     //==============================================================================
     /**
     * @brief // read VERTEX from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey           [in]  For the moment 0
     * @param dVertexRecNo   [in]  record number of VERTEX in sstDxf database
     * @param poPath         [in out] qt Path object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteVERTEXtoQtPath(int               iKey,
                               dREC04RECNUMTYP   dVertexRecNo,
                               QPainterPath     *poPath);
     //==============================================================================
     /**
     * @brief // read HATCHEDGE from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey           [in]  For the moment 0
     * @param dEntityRecNo   [in]  record number of Entity in sstDxf database
     * @param poPath         [in out] qt Path object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteHATCHEDGEtoQtPath(int               iKey,
                                dREC04RECNUMTYP   dEntityRecNo,
                                QPainterPath     *poPath);
     //==============================================================================
     /**
     * @brief // read HATCHEDGE from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey           [in]  For the moment 0
     * @param dEntityRecNo   [in]  record number of Entity in sstDxf database
     * @param oBlkTrn        [in]  Transformation object from block to world
     * @param poPath         [in out] qt Path object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No Entities found
     * @retval   = -3: Found end of list
     * @retval   = -4: Layer name empty
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteHATCHEDGEtoQtPathBlk(int               iKey,
                                   dREC04RECNUMTYP   dEntityRecNo,
                                   sstMath01TrnCls   oBlkTrn,
                                   QPainterPath     *poPath);
     //==============================================================================
     /**
     * @brief // convert sstShapeItem with QPainterPath to LINE Entity  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param oPathItem   [in]  sstShapeItem object
     * @param poDlCircle  [out] DxfLib CIRCLE Entity
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteItemPathtoCIRCLE(int                     iKey,
                             const sstQt01ShapeItem  oPathItem,
                             DL_CircleData            *poDlCircle);
     //==============================================================================
     /**
     * @brief // convert sstShapeItem with QPainterPath to LINE Entity  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param oPathItem   [in]  sstShapeItem object
     * @param poDlPoint   [out] DxfLib POINT Entity
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteItemPathtoPOINT(int                      iKey,
                              const sstQt01ShapeItem   oPathItem,
                              DL_PointData            *poDlPoint);
     //==============================================================================
     /**
     * @brief // convert sstShapeItem with QPainterPath to POLYLINE Entity  <BR>
     *
     * @param iKey         [in]  For the moment 0
     * @param oPathItem    [in]  sstShapeItem object
     * @param poDlPolyline [out] DxfLib POLYLINE Entity
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteItemPathtoPOLYLINE(int                      iKey,
                                 const sstQt01ShapeItem   oPathItem,
                                 DL_PolylineData         *poDlPolyline);
     //==============================================================================
     /**
     * @brief // convert sstShapeItem with QPainterPath to HATCH Entity  <BR>
     *
     * @param iKey         [in]  For the moment 0
     * @param oPathItem    [in]  sstShapeItem object
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteItemPathtoHATCH(int                      iKey,
                              const sstQt01ShapeItem   oPathItem);
     //==============================================================================
     /**
     * @brief // convert QtPainterPath Element to VERTEX, Coordinate Transformation Device to World <BR>
     * iStat = oDxfPathConvert.WritePathElementToVERTEX( iKey, oPathElement, &poDlVertex);
     *
     * @param iKey         [in]  For the moment 0
     * @param oPathElement [in]  Qt Painter Path Element
     * @param poDlVertex   [out] DxfLib VERTEX Entity
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritePathElementToVERTEX(int                          iKey,
                                  const QPainterPath::Element  oPathElement,
                                  DL_VertexData               *poDlVertex);
     //==============================================================================
     /**
     * @brief // convert QtPainterPath Element to HATCHEDGE, Coordinate Transformation Device to World <BR>
     * iStat = oDxfPathConvert.WritePathElementToVERTEX( iKey, oPathElement, &poDlVertex);
     *
     * @param iKey          [in]  For the moment 0
     * @param oPathElement1 [in]  Qt Painter Path Element
     * @param oPathElement2 [in]  Qt Painter Path Element
     * @param poHatchEdge   [in out] DxfLib HATCHEDGE Entity
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritePathElementToHATCHEDGE(int                          iKey,
                                     const QPainterPath::Element  oPathElement1,
                                     const QPainterPath::Element  oPathElement2,
                                     DL_HatchEdgeData *poHatchEdge);
     //==============================================================================
     /**
     * @brief // HATCHEDGE_Trn <BR>
     * iStat = oDxfPathConvert.HATCHEDGE_Trn( iKey, oTrn, &poHatchEdge);
     *
     * @param iKey [in] For the moment 0
     * @param oTrn [in] Tranformation
     * @param poHatchEdge [in out] Hatch Edge
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int HATCHEDGE_Trn(int               iKey,
                       sstMath01TrnCls   oTrn,
                       DL_HatchEdgeData *poHatchEdge);
     //==============================================================================
     /**
     * @brief // transform dxf color to QColor  <BR>
     * oQtCol = oPathStore.numberToColor ( iDxfNo);
     *
     * @param iDxfNo  [in] dxf color number
     *
     * @return QColor value
     */
     // ----------------------------------------------------------------------------
     QColor numberToColor(int iDxfNo);
     //==============================================================================
     /**
     * @brief // transform QColor to dxf color number  <BR>
     * iStat = oPathStore.colorToNumber( col, &rgb);
     *
     * @param col  [in]  QColor value
     * @param rgb  [out] RGB value
     *
     * @return dxf color number
     */
     // ----------------------------------------------------------------------------
     int colorToNumber(const QColor& col, int *rgb);
     //==============================================================================
     /**
     * @brief // write all sstDxf data from database into sst path storage <BR>
     * iStat = oPathDxfDb.WritAlltoPathStorage(iKey,poTmpPathStore);
     *
     * @param iKey [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritAlltoPathStorage(int               iKey);
     //==============================================================================
     /**
     * @brief // write all sstDxf data from database into sst path storage <BR>
     * iStat = oPathDxfDb.WritAlltoDxf ( iKey, oDxfFilNamStr);
     *
     * iKey=1: Write Dxf csv files too.
     *
     * @param iKey           [in] 0 or 1
     * @param oDxfFilNamStr  [in] Dxf File Name String
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteAll2Dxf(int iKey, const std::string oDxfFilNamStr);
     //==============================================================================
     /**
     * @brief // write all path from storage to sstDxf database <BR>
     * iStat = oPathDxfDb.WriteAllPath2Dxf ( iKey, poTmpPathStore);
     *
     * @param iKey [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteAllPath2Dxf(int iKey);
     //==============================================================================
     /**
     * @brief // Get position of ShapeItem in Display list <BR>
     * iStat = oPathDxfDb.getItemListNo ( iKey, dRecNo);
     *
     * @param iKey   [in] For the moment 0
     * @param dRecNo [in] Record number in main list
     *
     * @return Record number in ShapeItem display list
     */
     // ----------------------------------------------------------------------------
     dREC04RECNUMTYP getItemListNo(int iKey, dREC04RECNUMTYP dRecNo );
     //==============================================================================
     /**
     * @brief // Fill open sst Path Item <BR>
     * iStat = oPathCnvt.FillPathItem( iKey, poPath, dItemListNo, poItemPath);
     *
     * @param iKey        [in] For the moment 0
     * @param poPath      [in] Add PainterPath to Item Path
     * @param dItemListNo [in] For Display List
     * @param poItemPath  [in out] return filled Item Path
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     //==============================================================================
     int FillPathItem (int               iKey,
                       QPainterPath     *poPath,
                       dREC04RECNUMTYP   dItemListNo,
                       sstQt01ShapeItem *poItemPath);
     //==============================================================================

// ----------------------------------------------------------------------------
  private:  // Private functions
    sstDxf03DbCls           *poDxfDb;             /**< sst dxf database from outside */
    sstMisc01PrtFilCls      *poPrt;               /**< protocol object from outside */
    sstQt01PathStoreViewCls *poPathStore;         /**< sstPainterPath Store object from outside */
    sstRec04Cls             *poMainDisplayList;   /**< Order List from ShapeItem List to Main Table   */
    sstDxf03EntityTypeCls    oEntStrCnvt;         /**< convert EntityType to EntityString */
    RS2::EntityType eGrpEntType;                  /**< Group Entity Type like POLYLINE / HATCH */
    dREC04RECNUMTYP dGrpMainID;                   /**< Group Main ID/RecNo */
    dREC04RECNUMTYP dGrpSubID;                    /**< Sub Group ID/RecNo like HatchLoop */
    dREC04RECNUMTYP dGrpRecNum;                   /**< Number of entities of actual group */
    dREC04RECNUMTYP dGrpRecPos;                   /**< Position of group element */
    DL_Attributes 	oAttribRec;                   /**< Attributes of last handled entity */
};
//==============================================================================
/**
* @brief View Class for Dxf Entity Table
*
* Changed: 25.05.18  Re.
*
* @ingroup sstQtDxf01Lib
*
* @author Re.
*
* @date 25.05.18
*/
// ----------------------------------------------------------------------------
class sstQtDxf01TabViewCircleCls : public sstQt01TabViewCls
{
  Q_OBJECT

public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor for sstQtDxf01TabViewLineCls <BR>
  *
  * @param poPrt         [in] Adress of Protocoll
  * @param poDxfDb       [in] Adress of sst Dxf Database object
  */
  // ----------------------------------------------------------------------------
     sstQtDxf01TabViewCircleCls(sstMisc01PrtFilCls    *poPrt,
                              sstDxf03DbCls         *poDxfDb);  // Constructor
     ~sstQtDxf01TabViewCircleCls();  // Destructor
// ----------------------------------------------------------------------------
public slots:
     //==============================================================================
     /**
     * @brief // Slot Update Table from Map <BR>
     *
     * @param oMapSignal      [in] Send objectdata from Map to GroupBox
     */
     // ----------------------------------------------------------------------------
     void sstSlotChangeTabCircle(sstQt01MapSignalCls oMapSignal);
     //==============================================================================
     /**
     * @brief // Slot Update Table from Map <BR>
     *
     * @param oShapeItem       [in] Send ShapeItem from GroupBox to Map
     */
     // ----------------------------------------------------------------------------
     void sstSlotUpdateTabCircle(sstQt01ShapeItem oShapeItem);

signals:
     //==============================================================================
     /**
     * @brief Signal -Table data changed- direction table to map
     */
     // ----------------------------------------------------------------------------
     // void sstSgnlTabCircleChanged(dREC04RECNUMTYP dLineRecNo);
     void sstSgnlTabCircleChanged(sstQt01MapSignalCls oMapSignal);
     //==============================================================================
     /**
     * @brief Signal -Table data changed- direction table to map
     */
     // ----------------------------------------------------------------------------
     void sstSgnlTabCircleUpdated(sstQt01ShapeItem oShapeItem);

private:  // Private functions
     sstQtDxf01TabMdlCircleCls  *poTabMdl; /**< Table Model Object */
};
//==============================================================================
/**
* @brief View Class for Dxf Entity Table
*
* Changed: 25.05.18  Re.
*
* @ingroup sstQtDxf01Lib
*
* @author Re.
*
* @date 25.05.18
*/
// ----------------------------------------------------------------------------
class sstQtDxf01TabViewLineCls : public sstQt01TabViewCls
{
  Q_OBJECT

  public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor for sstQtDxf01TabViewLineCls <BR>
  *
  * @param poPrt         [in] Adress of Protocoll
  * @param poDxfDb       [in] Adress of sst Dxf Database object
  */
  // ----------------------------------------------------------------------------
     sstQtDxf01TabViewLineCls(sstMisc01PrtFilCls    *poPrt,
                              sstDxf03DbCls         *poDxfDb);  // Constructor
     ~sstQtDxf01TabViewLineCls();  // Destructor
// ----------------------------------------------------------------------------
public slots:
     //==============================================================================
     /**
     * @brief // Slot Update Map from Table <BR>
     *
     * @param oMapSignal    [in] Send Record Number/TypeString from GroupBox to Map
     */
     // ----------------------------------------------------------------------------
     void sstSlotChangeTabLine(sstQt01MapSignalCls oMapSignal);
     //==============================================================================
     /**
     * @brief // Slot Update Table from Map <BR>
     *
     * @param oShapeItem       [in] Send ShapeItem from GroupBox to Map
     */
     // ----------------------------------------------------------------------------
     void sstSlotUpdateTabLine(sstQt01ShapeItem oShapeItem);

signals:
     //==============================================================================
     /**
     * @brief Signal -Table data changed- direction table to map
     */
     // ----------------------------------------------------------------------------
     // void sstSgnlTabLineChanged(dREC04RECNUMTYP dLineRecNo);
     void sstSgnlTabLineChanged(sstQt01MapSignalCls oMapSignal);
     //==============================================================================
     /**
     * @brief Signal -Table data changed- direction table to map
     */
     // ----------------------------------------------------------------------------
     void sstSgnlTabLineUpdated(sstQt01ShapeItem oShapeItem);



private:  // Private functions
     sstQtDxf01TabMdlLineCls  *poTabMdl; /**< Table Model Object */
};
//==============================================================================
/**
* @brief View Class for Dxf Entity Table
*
* Changed: 25.05.18  Re.
*
* @ingroup sstQtDxf01Lib
*
* @author Re.
*
* @date 25.05.18
*/
// ----------------------------------------------------------------------------
class sstQtDxf01TabViewMTextCls : public sstQt01TabViewCls
{
  public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor for sstQtDxf01TabViewMTextCls <BR>
  *
  * @param poPrt         [in] Adress of Protocoll
  * @param poDxfDb       [in] Adress of sst Dxf Database object
  */
  // ----------------------------------------------------------------------------
     sstQtDxf01TabViewMTextCls(sstMisc01PrtFilCls    *poPrt,
                              sstDxf03DbCls         *poDxfDb);  // Constructor
     ~sstQtDxf01TabViewMTextCls();  // Destructor
// ----------------------------------------------------------------------------
private:  // Private functions
     sstQtDxf01TabMdlMTextCls  *poTabMdl; /**< Table Model Object */
};
//==============================================================================
/**
* @brief View Class for Dxf Entity Table
*
* Changed: 25.05.18  Re.
*
* @ingroup sstQtDxf01Lib
*
* @author Re.
*
* @date 25.05.18
*/
// ----------------------------------------------------------------------------
class sstQtDxf01TabViewPointCls : public sstQt01TabViewCls
{
  public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor for sstQtDxf01TabViewPointCls <BR>
  *
  * @param poPrt         [in] Adress of Protocoll
  * @param poDxfDb       [in] Adress of sst Dxf Database object
  *
  */
  // ----------------------------------------------------------------------------
     sstQtDxf01TabViewPointCls(sstMisc01PrtFilCls    *poPrt,
                               sstDxf03DbCls         *poDxfDb);  // Constructor
     ~sstQtDxf01TabViewPointCls();  // Destructor
// ----------------------------------------------------------------------------
private:  // Private functions
     sstQtDxf01TabMdlPointCls  *poTabMdl; /**< Table Model Object */
};
//==============================================================================
/**
* @brief View Class for Dxf Entity Table
*
* Changed: 25.05.18  Re.
*
* @ingroup sstQtDxf01Lib
*
* @author Re.
*
* @date 25.05.18
*/
// ----------------------------------------------------------------------------
class sstQtDxf01TabViewTextCls : public sstQt01TabViewCls
{
  public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor for sstQtDxf01TabViewTextCls <BR>
  *
  * @param poPrt         [in] Adress of sst Protocoll object
  * @param poDxfDb       [in] Adress of sst Dxf Database object
  */
  // ----------------------------------------------------------------------------
     sstQtDxf01TabViewTextCls(sstMisc01PrtFilCls    *poPrt,
                              sstDxf03DbCls         *poDxfDb);  // Constructor
     ~sstQtDxf01TabViewTextCls();  // Destructor
// ----------------------------------------------------------------------------
private:  // Private functions
     sstQtDxf01TabMdlTextCls  *poTabMdl; /**< Table Model Object */
};
//==============================================================================
/**
* @brief Group Box Widget for Dxf Entity Tables <BR>
*
* Changed: 18.10.18  Re.
*
* @ingroup sstQtDxf01Lib
*
* @author Re.
*
* @date 18.10.18
*/
// ----------------------------------------------------------------------------
class sstQtDxf01TabGroupBoxCls : public QGroupBox
{
    Q_OBJECT

public:
  //==============================================================================
  /**
  * @brief // Constructor for sstQtDxf01TabGroupBoxCls <BR>
  *
  * @param poPrt            [in] Adress of sst Protocoll object
  * @param poDxfDb          [in] Adress of sst Dxf Database object
  * @param poDxfPathConvert [in] Adress of sst Dxf PainterPath Coordinates Convert object
  */
  // ----------------------------------------------------------------------------
  // sstQtDxf01TabGroupBoxCls(sstMisc01PrtFilCls *poPrt, sstDxf03DbCls *poDxfDb);
  sstQtDxf01TabGroupBoxCls(sstMisc01PrtFilCls        *poPrt,
                           sstDxf03DbCls             *poDxfDb,
                           sstQtDxf01PathConvertCls  *poDxfPathConvert);
    ~sstQtDxf01TabGroupBoxCls();

private slots:
    void selectionChangedSlot(const QItemSelection & newSelection, const QItemSelection & oldSelection);
    // void sstSlotUpdateMap(dREC04RECNUMTYP dRecNo);
    void sstSlotUpdateMap(sstQt01MapSignalCls oMapSignal);
    void sstSlotUpdateTab(sstQt01ShapeItem oShapeItem);

signals:
    //==============================================================================
    /**
    * @brief Signal -Table data changed- direction table to map
    */
    // ----------------------------------------------------------------------------
    void sstSgnlTabChanged(sstQt01ShapeItem oShapeItem);

private:
    sstQtDxf01PathConvertCls *poDxfPathCnvt;
    sstDxf03DbCls            *poDxfDb;
    sstMisc01PrtFilCls       *poPrt;

    QStackedWidget        *stackedWidget;
    QTextBrowser          *poTextWidget1;
    QTreeView             *treeView;
    QStandardItemModel    *standardModel;

    sstQtDxf01TabViewLineCls    *poTabLineView;
    sstQtDxf01TabViewCircleCls  *poTabCircleView;
    sstQtDxf01TabViewMTextCls   *poTabMTextView;
    sstQtDxf01TabViewPointCls   *poTabPointView;
    sstQtDxf01TabViewTextCls    *poTabTextView;

    QStandardItem *rootItem;
    QStandardItem *tabItem1;
    QStandardItem *tabItem2;
    QStandardItem *tabItem3;
    QStandardItem *tabItem4;
    QStandardItem *tabItem5;

};



#endif // SSTQTDXF01LIB_H
