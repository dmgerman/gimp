begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*    * TWAIN Plug-in  * Copyright (C) 1999 Craig Setera  * Craig Setera, setera@infonet.isl.net  * 03/31/1999  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  *  * Based on (at least) the following plug-ins:  * Screenshot  * GIF  * Randomize  *  * Any suggestions, bug-reports or patches are welcome.  *   * This plug-in interfaces to the TWAIN support library in order  * to capture images from TWAIN devices directly into GIMP images.  * The plug-in is capable of acquiring the following type of  * images:  * - B/W (1 bit images translated to grayscale B/W)  * - Grayscale up to 16 bits per pixel  * - RGB up to 16 bits per sample (24, 30, 36, etc.)  * - Paletted images (both Gray and RGB)  *  * Prerequisites:  *  This plug-in will not compile on anything other than a Win32  *  platform.  Although the TWAIN documentation implies that there  *  is TWAIN support available on Macintosh, I neither have a   *  Macintosh nor the interest in porting this.  If anyone else  *  has an interest, consult www.twain.org for more information on  *  interfacing to TWAIN.  *  * Known problems:  * - Multiple image transfers will hang the plug-in.  The current  *   configuration compiles with a maximum of single image transfers.  */
end_comment

begin_comment
comment|/*   * Revision history  *  (02/07/99)  v0.1   First working version (internal)  *  (02/09/99)  v0.2   First release to anyone other than myself  *  (02/15/99)  v0.3   Added image dump and read support for debugging  *  (03/31/99)  v0.5   Added support for multi-byte samples and paletted   *                     images.  */
end_comment

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|"twain.h"
end_include

begin_include
include|#
directive|include
file|"tw_func.h"
end_include

begin_comment
comment|/*  * newSession  *  * Create a new TWAIN session.  */
end_comment

begin_function
name|pTW_SESSION
DECL|function|newSession (pTW_IDENTITY appIdentity)
name|newSession
parameter_list|(
name|pTW_IDENTITY
name|appIdentity
parameter_list|)
block|{
comment|/* Create the structure */
name|pTW_SESSION
name|session
init|=
operator|(
name|pTW_SESSION
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|TW_SESSION
argument_list|)
argument_list|)
decl_stmt|;
comment|/* Set the structure fields */
name|session
operator|->
name|hwnd
operator|=
literal|0
expr_stmt|;
name|session
operator|->
name|twRC
operator|=
name|TWRC_SUCCESS
expr_stmt|;
name|session
operator|->
name|appIdentity
operator|=
name|appIdentity
expr_stmt|;
name|session
operator|->
name|dsIdentity
operator|=
operator|(
name|pTW_IDENTITY
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|TW_IDENTITY
argument_list|)
argument_list|)
expr_stmt|;
name|session
operator|->
name|dsIdentity
operator|->
name|Id
operator|=
literal|0
expr_stmt|;
name|session
operator|->
name|dsIdentity
operator|->
name|ProductName
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|session
operator|->
name|transferFunctions
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|twainIsAvailable
argument_list|()
condition|)
name|session
operator|->
name|twainState
operator|=
literal|2
expr_stmt|;
else|else
name|session
operator|->
name|twainState
operator|=
literal|0
expr_stmt|;
return|return
name|session
return|;
block|}
end_function

begin_comment
comment|/*  * registerWindowHandle  *  * Register the window handle to be used for this  * session.  */
end_comment

begin_function
name|void
DECL|function|registerWindowHandle (pTW_SESSION session,HWND hwnd)
name|registerWindowHandle
parameter_list|(
name|pTW_SESSION
name|session
parameter_list|,
name|HWND
name|hwnd
parameter_list|)
block|{
name|session
operator|->
name|hwnd
operator|=
name|hwnd
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * registerTransferCallback  *  * Register the callback to use when transferring  * image data.  */
end_comment

begin_function
name|void
DECL|function|registerTransferCallbacks (pTW_SESSION session,pTXFR_CB_FUNCS txfrFuncs,void * clientData)
name|registerTransferCallbacks
parameter_list|(
name|pTW_SESSION
name|session
parameter_list|,
name|pTXFR_CB_FUNCS
name|txfrFuncs
parameter_list|,
name|void
modifier|*
name|clientData
parameter_list|)
block|{
name|session
operator|->
name|transferFunctions
operator|=
name|txfrFuncs
expr_stmt|;
name|session
operator|->
name|clientData
operator|=
name|clientData
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * setClientData  *  * Set the client data associated with the specified  * TWAIN session.  */
end_comment

begin_function
name|void
DECL|function|setClientData (pTW_SESSION session,void * clientData)
name|setClientData
parameter_list|(
name|pTW_SESSION
name|session
parameter_list|,
name|void
modifier|*
name|clientData
parameter_list|)
block|{
name|session
operator|->
name|clientData
operator|=
name|clientData
expr_stmt|;
block|}
end_function

end_unit

