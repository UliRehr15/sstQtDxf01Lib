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
// sstQtDxf01Lib.h   22.12.16  Re.   05.07.16  Re.
//
// Public Classes and functions for system "sstQtDxf01Lib"
//

#ifndef SST_QT_DXF01_LIB_HEADER
#define SST_QT_DXF01_LIB_HEADER

/**
 * @defgroup sstQtDxf01Lib sstQtDxf01Lib: cpp sst dxf library (Version 3)
 *
 * cpp sst qt dxf library <BR>
 *
 */


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
  * @param poPrt    [in] Pointer to open sst Protocol object
  */
  // ----------------------------------------------------------------------------
     sstQtDxf01PathConvertCls(sstDxf03DbCls *poDxfDb, sstQt01PathStorageCls *poPathStore, sstMisc01PrtFilCls *poPrt);  // Constructor
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
     * @brief // read LINE object from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param dLineRecNo  [in]  record number of LINE in sstDxf database
     * @param poPathItem  [out] sstPath object
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteLINEtoItemPath(int iKey, dREC04RECNUMTYP dLineRecNo, sstQt01ShapeItem *poPathItem);
     //==============================================================================
     /**
     * @brief // read sstPath and convert to LINE Entity  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param poPathItem  [in] sstPath object
     * @param dDLLine     [in out]  LINE Entity
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteItemPathtoLINE(int iKey,
                             const sstQt01ShapeItem oPathItem,
                             DL_LineData  *poDLLine);
     //==============================================================================
     /**
     * @brief // read sst path object and update sstdxf LINE object.  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param dLineRecNo  [in]  record number of LINE in sstDxf database
     * @param poPathItem  [out] sstPath object
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int ReadItemPathfromLine(int iKey, dREC04RECNUMTYP dLineRecNo, sstQt01ShapeItem *poPathItem);
     //==============================================================================
     /**
     * @brief // transform dxf color to QColor  <BR>
     * iStat = oPathStore.numberToColor ( num);
     *
     * @param num  [in] dxf color number
     *
     * @return QColor value
     */
     // ----------------------------------------------------------------------------
     QColor numberToColor(int num);
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
     * @param poTmpPathStore [in out] sst Path Storage to fill
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritAlltoPathStorage(int iKey);
     //==============================================================================
     /**
     * @brief // LoadDxfFile <BR>
     * iStat = oPathDxfDb.LoadDxfFile(iKey,poTmpPathStore);
     *
     * @param iKey        [in] For the moment 0
     * @param oDxfNamStr  [in] sstDxf File to fill
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     // int LoadDxfFile(int iKey, std::string oDxfNamStr);
     //==============================================================================
     /**
     * @brief // write all sstDxf data from database into sst path storage <BR>
     * iStat = oPathDxfDb.WritAlltoPathStorage(iKey,poTmpPathStore);
     *
     * @param iKey        [in] For the moment 0
     * @param oDxfNamStr  [in] sst Path Storage to fill
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteAll2Dxf(int iKey, const std::string oDxfNamStr);
     //==============================================================================
     /**
     * @brief // write all path from storage to sstDxf database <BR>
     * iStat = oPathDxfDb.WriteAllPath2Dxf ( iKey, poTmpPathStore);
     *
     * @param iKey [in] For the moment 0
     * @param poTmpPathStore [in out] sst Path Storage to read from
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteAllPath2Dxf(int iKey);
     //==============================================================================

// ----------------------------------------------------------------------------
  private:  // Private functions
     sstDxf03DbCls *poDxfDb;            /**< sst dxf database from outside */
     sstMisc01PrtFilCls *poPrt;         /**< protocol object from outside */
     sstQt01PathStorageCls *poPathStore; /**< sstPainterPath object from outside */
};
//==============================================================================


#endif // SSTQTDXF01LIB_H
