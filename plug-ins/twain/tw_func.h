begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*    * TWAIN Plug-in  * Copyright (C) 1999 Craig Setera  * Craig Setera<setera@home.com>  * 03/31/1999  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  *  * Based on (at least) the following plug-ins:  * Screenshot  * GIF  * Randomize  *  * Any suggestions, bug-reports or patches are welcome.  *   * This plug-in interfaces to the TWAIN support library in order  * to capture images from TWAIN devices directly into GIMP images.  * The plug-in is capable of acquiring the following type of  * images:  * - B/W (1 bit images translated to grayscale B/W)  * - Grayscale up to 16 bits per pixel  * - RGB up to 16 bits per sample (24, 30, 36, etc.)  * - Paletted images (both Gray and RGB)  *  * Prerequisites:  *  This plug-in will not compile on anything other than a Win32  *  platform.  Although the TWAIN documentation implies that there  *  is TWAIN support available on Macintosh, I neither have a   *  Macintosh nor the interest in porting this.  If anyone else  *  has an interest, consult www.twain.org for more information on  *  interfacing to TWAIN.  *  * Known problems:  * - Multiple image transfers will hang the plug-in.  The current  *   configuration compiles with a maximum of single image transfers.  */
end_comment

begin_comment
comment|/*   * Revision history  *  (02/07/99)  v0.1   First working version (internal)  *  (02/09/99)  v0.2   First release to anyone other than myself  *  (02/15/99)  v0.3   Added image dump and read support for debugging  *  (03/31/99)  v0.5   Added support for multi-byte samples and paletted   *                     images.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_TW_FUNC_H
end_ifndef

begin_define
DECL|macro|_TW_FUNC_H
define|#
directive|define
name|_TW_FUNC_H
end_define

begin_include
include|#
directive|include
file|"twain.h"
end_include

begin_comment
comment|/*  * Pre-image transfer function type  *  * Sent to the caller before any of the  * images are transferred to the application.  */
end_comment

begin_typedef
DECL|typedef|TW_PRE_TXFR_CB
typedef|typedef
name|void
function_decl|(
modifier|*
name|TW_PRE_TXFR_CB
function_decl|)
parameter_list|(
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  * Image transfer begin function type  *  * Sent to the caller when an image transfer  * is about to begin.  The caller may return  * FALSE if the transfer should not continue.  * Otherwise, the function should return a  * TRUE value.  */
end_comment

begin_typedef
DECL|typedef|TW_TXFR_BEGIN_CB
typedef|typedef
name|int
function_decl|(
modifier|*
name|TW_TXFR_BEGIN_CB
function_decl|)
parameter_list|(
name|pTW_IMAGEINFO
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  * Image transfer callback function type  *  * Expected to return true if the image transfer  * should continue.  False if the transfer should  * be cancelled.  */
end_comment

begin_typedef
DECL|typedef|TW_TXFR_DATA_CB
typedef|typedef
name|int
function_decl|(
modifier|*
name|TW_TXFR_DATA_CB
function_decl|)
parameter_list|(
name|pTW_IMAGEINFO
parameter_list|,
name|pTW_IMAGEMEMXFER
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  * Image transfer end function type  *  * Sent to the caller when an image transfer  * is completed.  The caller will be handed  * the image transfer completion state.  The  * following values (defined in twain.h) are  * possible:  *  * TWRC_XFERDONE  *  The transfer completed successfully  * TWRC_CANCEL  *  The transfer was completed by the user  * TWRC_FAILURE  *  The transfer failed.  */
end_comment

begin_typedef
DECL|typedef|TW_TXFR_END_CB
typedef|typedef
name|int
function_decl|(
modifier|*
name|TW_TXFR_END_CB
function_decl|)
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  * Post-image transfer callback  *  * This callback function is called after all  * of the possible images have been transferred  * from the datasource.  */
end_comment

begin_typedef
DECL|typedef|TW_POST_TXFR_CB
typedef|typedef
name|void
function_decl|(
modifier|*
name|TW_POST_TXFR_CB
function_decl|)
parameter_list|(
name|int
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  * The following structure defines the  * three callback functions that are called  * while an image is being transferred.  * The types of these functions are defined  * above.  Any function that is NULL will just  * not be called.  */
end_comment

begin_typedef
DECL|struct|_TXFR_CB_FUNCS
typedef|typedef
struct|struct
name|_TXFR_CB_FUNCS
block|{
comment|/* Pre-transfer function */
DECL|member|preTxfrCb
name|TW_PRE_TXFR_CB
name|preTxfrCb
decl_stmt|;
comment|/* Begin function */
DECL|member|txfrBeginCb
name|TW_TXFR_BEGIN_CB
name|txfrBeginCb
decl_stmt|;
comment|/* Data transfer */
DECL|member|txfrDataCb
name|TW_TXFR_DATA_CB
name|txfrDataCb
decl_stmt|;
comment|/* End function */
DECL|member|txfrEndCb
name|TW_TXFR_END_CB
name|txfrEndCb
decl_stmt|;
comment|/* Post-transfer function */
DECL|member|postTxfrCb
name|TW_POST_TXFR_CB
name|postTxfrCb
decl_stmt|;
DECL|typedef|TXFR_CB_FUNCS
DECL|typedef|pTXFR_CB_FUNCS
block|}
name|TXFR_CB_FUNCS
operator|,
typedef|*
name|pTXFR_CB_FUNCS
typedef|;
end_typedef

begin_comment
comment|/*  * Data representing a TWAIN  * application to data source  * session.  */
end_comment

begin_typedef
DECL|struct|_TWAIN_SESSION
typedef|typedef
struct|struct
name|_TWAIN_SESSION
block|{
comment|/* The window handle related to the TWAIN application */
DECL|member|hwnd
name|HWND
name|hwnd
decl_stmt|;
comment|/* The current TWAIN return code */
DECL|member|twRC
name|TW_UINT16
name|twRC
decl_stmt|;
comment|/* The application's TWAIN identity */
DECL|member|appIdentity
name|pTW_IDENTITY
name|appIdentity
decl_stmt|;
comment|/* The datasource's TWAIN identity */
DECL|member|dsIdentity
name|pTW_IDENTITY
name|dsIdentity
decl_stmt|;
comment|/* The image data transfer functions */
DECL|member|transferFunctions
name|pTXFR_CB_FUNCS
name|transferFunctions
decl_stmt|;
comment|/* Client data that is associated with the image    * transfer callback    */
DECL|member|clientData
name|void
modifier|*
name|clientData
decl_stmt|;
comment|/*    * The following variable tracks the current state    * as related to the TWAIN engine.  The states are:    *    * 1) Pre-session: The DSM has not been loaded    * 2) Source Manager Loaded (not opened)    * 3) Source Manager Opened    * 4) Source Open    * 5) Source Enabled    * 6) Transfer ready    * 7) Transferring    */
DECL|member|twainState
name|int
name|twainState
decl_stmt|;
DECL|typedef|TW_SESSION
DECL|typedef|pTW_SESSION
block|}
name|TW_SESSION
operator|,
typedef|*
name|pTW_SESSION
typedef|;
end_typedef

begin_comment
comment|/* Session structure access  * macros  */
end_comment

begin_comment
comment|/* #define pAPP_IDENTITY(tw_session) (&(tw_session->appIdentity)) */
end_comment

begin_define
DECL|macro|APP_IDENTITY (tw_session)
define|#
directive|define
name|APP_IDENTITY
parameter_list|(
name|tw_session
parameter_list|)
value|(tw_session->appIdentity)
end_define

begin_comment
comment|/* #define pDS_IDENTITY(tw_session) (&(tw_session->dsIdentity)) */
end_comment

begin_define
DECL|macro|DS_IDENTITY (tw_session)
define|#
directive|define
name|DS_IDENTITY
parameter_list|(
name|tw_session
parameter_list|)
value|(tw_session->dsIdentity)
end_define

begin_comment
comment|/* State macros... Each expects  * a Twain Session pointer  */
end_comment

begin_define
DECL|macro|TWAIN_LOADED (tw_session)
define|#
directive|define
name|TWAIN_LOADED
parameter_list|(
name|tw_session
parameter_list|)
value|(tw_session->twainState>= 2)
end_define

begin_define
DECL|macro|TWAIN_UNLOADED (tw_session)
define|#
directive|define
name|TWAIN_UNLOADED
parameter_list|(
name|tw_session
parameter_list|)
value|(tw_session->twainState< 2)
end_define

begin_define
DECL|macro|DSM_IS_OPEN (tw_session)
define|#
directive|define
name|DSM_IS_OPEN
parameter_list|(
name|tw_session
parameter_list|)
value|(tw_session->twainState>= 3)
end_define

begin_define
DECL|macro|DSM_IS_CLOSED (tw_session)
define|#
directive|define
name|DSM_IS_CLOSED
parameter_list|(
name|tw_session
parameter_list|)
value|(tw_session->twainState< 3)
end_define

begin_define
DECL|macro|DS_IS_OPEN (tw_session)
define|#
directive|define
name|DS_IS_OPEN
parameter_list|(
name|tw_session
parameter_list|)
value|(tw_session->twainState>= 4)
end_define

begin_define
DECL|macro|DS_IS_CLOSED (tw_session)
define|#
directive|define
name|DS_IS_CLOSED
parameter_list|(
name|tw_session
parameter_list|)
value|(tw_session->twainState< 4)
end_define

begin_define
DECL|macro|DS_IS_ENABLED (tw_session)
define|#
directive|define
name|DS_IS_ENABLED
parameter_list|(
name|tw_session
parameter_list|)
value|(tw_session->twainState>= 5)
end_define

begin_define
DECL|macro|DS_IS_DISABLED (tw_session)
define|#
directive|define
name|DS_IS_DISABLED
parameter_list|(
name|tw_session
parameter_list|)
value|(tw_session->twainState< 5)
end_define

begin_comment
comment|/* Function declarations */
end_comment

begin_function_decl
name|TW_UINT16
name|callDSM
parameter_list|(
name|pTW_IDENTITY
parameter_list|,
name|pTW_IDENTITY
parameter_list|,
name|TW_UINT32
parameter_list|,
name|TW_UINT16
parameter_list|,
name|TW_UINT16
parameter_list|,
name|TW_MEMREF
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|twainError
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|currentTwainError
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|twainIsAvailable
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|getImage
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|loadTwainLibrary
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|openDSM
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|selectDS
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|selectDefaultDS
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|openDS
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|requestImageAcquire
parameter_list|(
name|pTW_SESSION
parameter_list|,
name|BOOL
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|disableDS
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|closeDS
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|closeDSM
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|unloadTwainLibrary
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|twainMessageLoop
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|cancelPendingTransfers
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TW_FIX32
name|FloatToFix32
parameter_list|(
name|float
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|FIX32ToFloat
parameter_list|(
name|TW_FIX32
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pTW_SESSION
name|newSession
parameter_list|(
name|pTW_IDENTITY
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|registerWindowHandle
parameter_list|(
name|pTW_SESSION
parameter_list|,
name|HWND
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|registerTransferCallbacks
parameter_list|(
name|pTW_SESSION
parameter_list|,
name|pTXFR_CB_FUNCS
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|setClientData
parameter_list|(
name|pTW_SESSION
name|session
parameter_list|,
name|void
modifier|*
name|clientData
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _TW_FUNC_H */
end_comment

end_unit

