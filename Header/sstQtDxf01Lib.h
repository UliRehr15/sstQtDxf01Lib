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
* @brief storage class for painter path objects <BR>
*
* FIFO storage, reading/writing to csv file <BR>
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
class sstQtDxf01PathStorageCls
{
  public:   // Public functions
     sstQtDxf01PathStorageCls();  // Constructor
    ~sstQtDxf01PathStorageCls();  // Destructor
     //==============================================================================
     /**
     * @brief // Load all pathes from csv file in sst table object.  <BR>
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
     * @brief // store all pathes from sst table object into csv file.  <BR>
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
     * @brief // Write one QPainterPath to sst dxf database  <BR>
     *
     * @param iKey   [in] For the moment 0
     * @param oPath  [in] QPainterPath object to write to dxf
     * @param oColor [in] Color of Path
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WrtPath2Dxf(int iKey,  QPainterPath oPath, QColor oColor);
     //==============================================================================
     /**
     * @brief // read next QPainterPath object from sst table object.  <BR>
     *
     * @param iKey   [in] For the moment 0
     * @param oPath  [out] QPainterPath object
     * @param oColor [out] Color of Path
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int ReadNextPath(int iKey,  QPainterPath *oPath, QColor *oColor);
     //==============================================================================
     /**
     * @brief // transform coordinates of HatchEdge from device to world coordinate system  <BR>
     * iStat = oPathStore.Transform_DC_WC(iKey, &oDLHatchEdge);
     *
     * @param iKey          [in] For the moment 0
     * @param oDLHatchEdge  [in out] HatchEdge object
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int Transform_DC_WC (int iKey, DL_HatchEdgeData *oDLHatchEdge);
     //==============================================================================
     /**
     * @brief // transform coordinates of HatchEdge from device to world coordinate system  <BR>
     * iStat = oPathStore.Transform_DC_WC(iKey, &dX, &dY);
     *
     * @param iKey  [in] For the moment 0
     * @param dX    [in out] X Value
     * @param dY    [in out] Y Value
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int Transform_DC_WC (int iKey, double *dX, double *dY);
     //==============================================================================
     /**
     * @brief // transform coordinates of HatchEdge from would to device coordinate system  <BR>
     * iStat = oPathStore.Transform_WC_DC(iKey, &oDLHatchEdge);
     *
     * @param iKey          [in] For the moment 0
     * @param oDLHatchEdge  [in out] HatchEdge object
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int Transform_WC_DC (int iKey, DL_HatchEdgeData *oDLHatchEdge);
     //==============================================================================
     /**
     * @brief // transform coordinates of HatchEdge from would to device coordinate system  <BR>
     * iStat = oPathStore.Transform_WC_DC(iKey, &dX, &dY);
     *
     * @param iKey  [in] For the moment 0
     * @param dX    [in out] HatchEdge object
     * @param dY    [in out] HatchEdge object
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int Transform_WC_DC (int iKey, double *dX, double *dY);
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
     * @brief // write dxf database to csv files  <BR>
     * iStat = oPathStore.WriteDxfDbtoCsv( iKey, oFilNam);
     *
     * @param iKey    [in] For the moment zero
     * @param oFilNam [in] File Name
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WriteDxfDbToCsv(int iKey, std::string oFilNam);
     //==============================================================================
     /**
     * @brief // Read full Dxf Database from Csv files  <BR>
     * iStat = oPathStore.ReadDxfDbFromCsv( iKey, oFilNam);
     *
     * @param iKey    [in] For the moment zero
     * @param oFilNam [in] File Name
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int ReadDxfDbFromCsv(int iKey, std::string oFilNam);
     //==============================================================================

// ----------------------------------------------------------------------------
  private:  // Private functions
     sstRec04Cls *poShapeItemRecTable;  /**< painter path element table */
     dREC04RECNUMTYP dActualReadPos;    /**< actual read position in table */
     sstDxf03DbCls *poDxfDb;
     sstMisc01PrtFilCls oPrt;
};
//==============================================================================

#endif // SSTQTDXF01LIB_H
