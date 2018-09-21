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
 * @defgroup sstQtDxf01Lib sstQtDxf01Lib: cpp sst Qt Dxf library (Version 1)
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
     * @brief // read LINE object from sstDxf database and write into sstPath.  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param dLineRecNo  [in]  record number of LINE in sstDxf database
     * @param poPathItem  [out] sstPath object
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
     int WriteLINEtoItemPath(int iKey, dREC04RECNUMTYP dLineRecNo, sstQt01ShapeItem *poPathItem);
     //==============================================================================
     /**
     * @brief // read sstPath and convert to LINE Entity  <BR>
     *
     * @param iKey        [in]  For the moment 0
     * @param oPathItem   [in] sstPath object
     * @param poDLLine    [in out]  LINE Entity
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
     sstQt01PathStoreViewCls *poPathStore; /**< sstPainterPath object from outside */
};
//==============================================================================
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


#endif // SSTQTDXF01LIB_H
