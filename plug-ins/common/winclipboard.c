begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * WinClipboard Win32 Windoze Copy&Paste Plug-in  * Copyright (C) 1999 Hans Breuer  * Hans Breuer, Hans@Breuer.org  * 08/07/99  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * Based on (at least) the following plug-ins:  *  Header  *  WinSnap  *  * Any suggestions, bug-reports or patches are welcome.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* History:  *    *   08/07/99 Implementation and release.  *	 08/10/99 Big speed increase by using gimp_tile_cache_size()  *			  Thanks to Kevin Turner's documentation at:  *			  http://www.poboxes.com/kevint/gimp/doc/plugin-doc-2.1.html  *  * TODO (maybe):  *  *   - Support for 4,2,1 bit bitmaps  *   - Unsupported formats could be delegated to GIMP Loader (e.g. wmf)  *   - ...  */
end_comment

begin_comment
comment|/* How many steps the progress control should do  */
end_comment

begin_define
DECL|macro|PROGRESS_STEPS
define|#
directive|define
name|PROGRESS_STEPS
value|25
end_define

begin_define
DECL|macro|StepProgress (one,all)
define|#
directive|define
name|StepProgress
parameter_list|(
name|one
parameter_list|,
name|all
parameter_list|)
define|\
value|(0 == (one % ((all / PROGRESS_STEPS)+1)))
end_define

begin_comment
comment|/* FIXME: I'll use -1 as IMAGE_NONE. Is it correct ???  */
end_comment

begin_define
DECL|macro|IMAGE_NONE
define|#
directive|define
name|IMAGE_NONE
value|-1
end_define

begin_comment
comment|/* Declare some local functions.  */
end_comment

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Plugin function prototypes  */
end_comment

begin_function_decl
specifier|static
name|int
name|CB_CopyImage
parameter_list|(
name|gboolean
name|interactive
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|CB_PasteImage
parameter_list|(
name|gboolean
name|interactive
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|()
block|{
specifier|static
name|GParamDef
name|copy_args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to save"
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|ncopy_args
init|=
sizeof|sizeof
argument_list|(
name|copy_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|copy_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_clipboard_copy"
argument_list|,
literal|"copy image to clipboard"
argument_list|,
literal|"Copies the active drawable to the clipboard."
argument_list|,
literal|"Hans Breuer"
argument_list|,
literal|"Hans Breuer"
argument_list|,
literal|"1999"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Edit/Copy to Clipboard"
argument_list|)
argument_list|,
literal|"INDEXED*, RGB*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|ncopy_args
argument_list|,
literal|0
argument_list|,
name|copy_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_clipboard_paste"
argument_list|,
literal|"paste image from clipboard"
argument_list|,
literal|"Paste image from clipboard into active image."
argument_list|,
literal|"Hans Breuer"
argument_list|,
literal|"Hans Breuer"
argument_list|,
literal|"1999"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Edit/Paste from Clipboard"
argument_list|)
argument_list|,
literal|"INDEXED*, RGB*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|ncopy_args
argument_list|,
literal|0
argument_list|,
name|copy_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"extension_clipboard_paste"
argument_list|,
literal|"Get image from clipboard"
argument_list|,
literal|"Get an image from the Windows clipboard, creating a new image"
argument_list|,
literal|"Hans Breuer"
argument_list|,
literal|"Hans Breuer"
argument_list|,
literal|"1999"
argument_list|,
name|N_
argument_list|(
literal|"<Toolbox>/File/Acquire/From Clipboard"
argument_list|)
argument_list|,
literal|""
argument_list|,
name|PROC_EXTENSION
argument_list|,
name|ncopy_args
argument_list|,
literal|0
argument_list|,
name|copy_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GParam * param,gint * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GParam
name|values
index|[
literal|2
index|]
decl_stmt|;
name|GRunModeType
name|run_mode
decl_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|PARAM_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug_in_clipboard_copy"
argument_list|)
operator|==
literal|0
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|CB_CopyImage
argument_list|(
name|RUN_INTERACTIVE
operator|==
name|run_mode
argument_list|,
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
condition|)
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_SUCCESS
expr_stmt|;
else|else
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug_in_clipboard_paste"
argument_list|)
operator|==
literal|0
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|CB_PasteImage
argument_list|(
name|RUN_INTERACTIVE
operator|==
name|run_mode
argument_list|,
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
condition|)
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_SUCCESS
expr_stmt|;
else|else
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"extension_clipboard_paste"
argument_list|)
operator|==
literal|0
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|CB_PasteImage
argument_list|(
name|RUN_INTERACTIVE
operator|==
name|run_mode
argument_list|,
name|IMAGE_NONE
argument_list|,
name|IMAGE_NONE
argument_list|)
condition|)
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_SUCCESS
expr_stmt|;
else|else
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* Plugin Function implementation  */
end_comment

begin_function
specifier|static
name|int
DECL|function|CB_CopyImage (gboolean interactive,gint32 image_ID,gint32 drawable_ID)
name|CB_CopyImage
parameter_list|(
name|gboolean
name|interactive
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|GDrawableType
name|drawable_type
decl_stmt|;
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|gchar
modifier|*
name|sStatus
init|=
name|NULL
decl_stmt|;
name|int
name|nSizeDIB
init|=
literal|0
decl_stmt|;
name|int
name|nSizePal
init|=
literal|0
decl_stmt|;
name|int
name|nSizeLine
init|=
literal|0
decl_stmt|;
comment|/* DIB lines are 32 bit aligned */
name|HANDLE
name|hDIB
decl_stmt|;
name|BOOL
name|bRet
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|drawable_type
operator|=
name|gimp_drawable_type
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* allocate room for DIB */
if|if
condition|(
name|INDEXED_IMAGE
operator|==
name|drawable_type
condition|)
block|{
name|nSizeLine
operator|=
operator|(
operator|(
name|drawable
operator|->
name|width
operator|-
literal|1
operator|)
operator|/
literal|4
operator|+
literal|1
operator|)
operator|*
literal|4
expr_stmt|;
name|nSizeDIB
operator|=
sizeof|sizeof
argument_list|(
name|RGBQUAD
argument_list|)
operator|*
literal|256
comment|/* always full color map size */
operator|+
name|nSizeLine
operator|*
name|drawable
operator|->
name|height
operator|+
sizeof|sizeof
argument_list|(
name|BITMAPINFOHEADER
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|nSizeLine
operator|=
operator|(
operator|(
name|drawable
operator|->
name|width
operator|*
literal|3
operator|-
literal|1
operator|)
operator|/
literal|4
operator|+
literal|1
operator|)
operator|*
literal|4
expr_stmt|;
name|nSizeDIB
operator|=
name|nSizeLine
operator|*
name|drawable
operator|->
name|height
operator|+
sizeof|sizeof
argument_list|(
name|BITMAPINFOHEADER
argument_list|)
expr_stmt|;
block|}
name|hDIB
operator|=
name|GlobalAlloc
argument_list|(
name|GMEM_MOVEABLE
operator||
name|GMEM_DDESHARE
argument_list|,
name|nSizeDIB
argument_list|)
expr_stmt|;
if|if
condition|(
name|NULL
operator|==
name|hDIB
condition|)
block|{
name|g_warning
argument_list|(
literal|"Failed to allocate DIB"
argument_list|)
expr_stmt|;
name|bRet
operator|=
name|FALSE
expr_stmt|;
block|}
comment|/* fill header info */
if|if
condition|(
name|bRet
condition|)
block|{
name|BITMAPINFOHEADER
modifier|*
name|pInfo
decl_stmt|;
name|bRet
operator|=
name|FALSE
expr_stmt|;
name|pInfo
operator|=
name|GlobalLock
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
if|if
condition|(
name|pInfo
condition|)
block|{
name|pInfo
operator|->
name|biSize
operator|=
sizeof|sizeof
argument_list|(
name|BITMAPINFOHEADER
argument_list|)
expr_stmt|;
name|pInfo
operator|->
name|biWidth
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|pInfo
operator|->
name|biHeight
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
name|pInfo
operator|->
name|biPlanes
operator|=
literal|1
expr_stmt|;
name|pInfo
operator|->
name|biBitCount
operator|=
operator|(
name|INDEXED_IMAGE
operator|==
name|drawable_type
condition|?
literal|8
else|:
literal|24
operator|)
expr_stmt|;
name|pInfo
operator|->
name|biCompression
operator|=
name|BI_RGB
expr_stmt|;
comment|/* none */
name|pInfo
operator|->
name|biSizeImage
operator|=
literal|0
expr_stmt|;
comment|/* not calculated/needed */
name|pInfo
operator|->
name|biXPelsPerMeter
operator|=
name|pInfo
operator|->
name|biYPelsPerMeter
operator|=
literal|0
expr_stmt|;
comment|/* color map size */
name|pInfo
operator|->
name|biClrUsed
operator|=
operator|(
name|INDEXED_IMAGE
operator|==
name|drawable_type
condition|?
literal|256
else|:
literal|0
operator|)
expr_stmt|;
name|pInfo
operator|->
name|biClrImportant
operator|=
literal|0
expr_stmt|;
comment|/* all */
name|GlobalUnlock
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
name|bRet
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* (pInfo) */
else|else
name|g_warning
argument_list|(
literal|"Failed to lock DIB Header"
argument_list|)
expr_stmt|;
block|}
comment|/* fill color map */
if|if
condition|(
name|bRet
operator|&&
operator|(
name|INDEXED_IMAGE
operator|==
name|drawable_type
operator|)
condition|)
block|{
name|char
modifier|*
name|pBmp
decl_stmt|;
name|bRet
operator|=
name|FALSE
expr_stmt|;
name|pBmp
operator|=
name|GlobalLock
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
if|if
condition|(
name|pBmp
condition|)
block|{
name|RGBQUAD
modifier|*
name|pPal
decl_stmt|;
name|int
name|nColors
decl_stmt|;
name|unsigned
name|char
modifier|*
name|cmap
decl_stmt|;
name|pPal
operator|=
operator|(
name|RGBQUAD
operator|*
operator|)
operator|(
name|pBmp
operator|+
sizeof|sizeof
argument_list|(
name|BITMAPINFOHEADER
argument_list|)
operator|)
expr_stmt|;
name|nSizePal
operator|=
sizeof|sizeof
argument_list|(
name|RGBQUAD
argument_list|)
operator|*
literal|256
expr_stmt|;
comment|/* get the gimp colormap */
name|cmap
operator|=
name|gimp_image_get_cmap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|nColors
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmap
condition|)
block|{
name|int
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
operator|(
name|i
operator|<
literal|256
operator|)
operator|&&
operator|(
name|i
operator|<
name|nColors
operator|)
condition|;
name|i
operator|++
control|)
block|{
name|pPal
index|[
name|i
index|]
operator|.
name|rgbReserved
operator|=
literal|0
expr_stmt|;
comment|/* is this alpha? */
name|pPal
index|[
name|i
index|]
operator|.
name|rgbRed
operator|=
name|cmap
index|[
literal|3
operator|*
name|i
index|]
expr_stmt|;
name|pPal
index|[
name|i
index|]
operator|.
name|rgbGreen
operator|=
name|cmap
index|[
literal|3
operator|*
name|i
operator|+
literal|1
index|]
expr_stmt|;
name|pPal
index|[
name|i
index|]
operator|.
name|rgbBlue
operator|=
name|cmap
index|[
literal|3
operator|*
name|i
operator|+
literal|2
index|]
expr_stmt|;
block|}
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
name|bRet
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* (cmap) */
else|else
name|g_warning
argument_list|(
literal|"Can't get color map"
argument_list|)
expr_stmt|;
name|GlobalUnlock
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
block|}
comment|/* (pBmp) */
else|else
name|g_warning
argument_list|(
literal|"Failed to lock DIB Palette"
argument_list|)
expr_stmt|;
block|}
comment|/* indexed */
comment|/* following the slow part ... */
if|if
condition|(
name|interactive
condition|)
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Copying ..."
argument_list|)
argument_list|)
expr_stmt|;
comment|/* speed it up with: */
name|gimp_tile_cache_size
argument_list|(
name|drawable
operator|->
name|width
operator|*
name|gimp_tile_height
argument_list|()
operator|*
name|drawable
operator|->
name|bpp
argument_list|)
expr_stmt|;
comment|/* copy data to DIB */
if|if
condition|(
name|bRet
condition|)
block|{
name|unsigned
name|char
modifier|*
name|pData
decl_stmt|;
name|bRet
operator|=
name|FALSE
expr_stmt|;
name|pData
operator|=
name|GlobalLock
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
if|if
condition|(
name|pData
condition|)
block|{
name|unsigned
name|char
modifier|*
name|pLine
decl_stmt|;
comment|/* calculate real offset */
name|pData
operator|+=
operator|(
sizeof|sizeof
argument_list|(
name|BITMAPINFOHEADER
argument_list|)
operator|+
name|nSizePal
operator|)
expr_stmt|;
name|pLine
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|drawable
operator|->
name|width
operator|*
name|drawable
operator|->
name|bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|pLine
condition|)
block|{
if|if
condition|(
name|INDEXED_IMAGE
operator|==
name|drawable_type
condition|)
block|{
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|drawable
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|interactive
operator|)
operator|&&
operator|(
name|StepProgress
argument_list|(
name|y
argument_list|,
name|drawable
operator|->
name|height
argument_list|)
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|pLine
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|height
operator|-
name|y
operator|-
literal|1
argument_list|,
comment|/* invert it */
name|drawable
operator|->
name|width
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|drawable
operator|->
name|width
condition|;
name|x
operator|++
control|)
name|pData
index|[
name|x
operator|+
name|y
operator|*
name|nSizeLine
index|]
operator|=
name|pLine
index|[
name|x
operator|*
name|drawable
operator|->
name|bpp
index|]
expr_stmt|;
block|}
block|}
else|else
block|{
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|drawable
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|interactive
operator|)
operator|&&
operator|(
name|StepProgress
argument_list|(
name|y
argument_list|,
name|drawable
operator|->
name|height
argument_list|)
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|pLine
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|height
operator|-
name|y
operator|-
literal|1
argument_list|,
comment|/* invert it */
name|drawable
operator|->
name|width
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|drawable
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
comment|/* RGBQUAD: blue, green, red, reserved */
name|pData
index|[
name|x
operator|*
literal|3
operator|+
name|y
operator|*
name|nSizeLine
index|]
operator|=
name|pLine
index|[
name|x
operator|*
name|drawable
operator|->
name|bpp
operator|+
literal|2
index|]
expr_stmt|;
comment|/* blue */
name|pData
index|[
name|x
operator|*
literal|3
operator|+
name|y
operator|*
name|nSizeLine
operator|+
literal|1
index|]
operator|=
name|pLine
index|[
name|x
operator|*
name|drawable
operator|->
name|bpp
operator|+
literal|1
index|]
expr_stmt|;
comment|/* green */
name|pData
index|[
name|x
operator|*
literal|3
operator|+
name|y
operator|*
name|nSizeLine
operator|+
literal|2
index|]
operator|=
name|pLine
index|[
name|x
operator|*
name|drawable
operator|->
name|bpp
index|]
expr_stmt|;
comment|/* red */
comment|//pData[x+y*drawable->width*3+3] = 0;          /* reserved */
block|}
block|}
block|}
name|g_free
argument_list|(
name|pLine
argument_list|)
expr_stmt|;
name|bRet
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* (pLine) */
else|else
name|g_warning
argument_list|(
literal|"Failed to get line buffer"
argument_list|)
expr_stmt|;
name|GlobalUnlock
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
block|}
comment|/* (pData) */
else|else
name|g_warning
argument_list|(
literal|"Failed to lock DIB Data"
argument_list|)
expr_stmt|;
block|}
comment|/* copy data to DIB */
comment|/* copy DIB to ClipBoard */
if|if
condition|(
name|bRet
condition|)
block|{
if|if
condition|(
operator|!
name|OpenClipboard
argument_list|(
name|NULL
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"Cannot open the Clipboard!"
argument_list|)
expr_stmt|;
name|bRet
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|bRet
operator|&&
operator|!
name|EmptyClipboard
argument_list|()
condition|)
block|{
name|g_warning
argument_list|(
literal|"Cannot empty the Clipboard"
argument_list|)
expr_stmt|;
name|bRet
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|bRet
condition|)
block|{
if|if
condition|(
name|NULL
operator|!=
name|SetClipboardData
argument_list|(
name|CF_DIB
argument_list|,
name|hDIB
argument_list|)
condition|)
name|hDIB
operator|=
name|NULL
expr_stmt|;
comment|/* data now owned by clipboard */
else|else
name|g_warning
argument_list|(
literal|"Failed to set clipboard data "
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|CloseClipboard
argument_list|()
condition|)
name|g_warning
argument_list|(
literal|"Failed to close Clipboard"
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* done */
if|if
condition|(
name|hDIB
condition|)
name|GlobalFree
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|bRet
return|;
block|}
end_function

begin_comment
comment|/* CB_CopyImage */
end_comment

begin_function
specifier|static
name|int
DECL|function|CB_PasteImage (gboolean interactive,gint32 image_ID,gint32 drawable_ID)
name|CB_PasteImage
parameter_list|(
name|gboolean
name|interactive
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|UINT
name|fmt
decl_stmt|;
name|BOOL
name|bRet
init|=
name|TRUE
decl_stmt|;
name|HANDLE
name|hDIB
decl_stmt|;
name|gint32
name|nWidth
init|=
literal|0
decl_stmt|;
name|gint32
name|nHeight
init|=
literal|0
decl_stmt|;
name|gint32
name|nBitsPS
init|=
literal|0
decl_stmt|;
name|gint32
name|nColors
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|OpenClipboard
argument_list|(
name|NULL
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"Failed to open clipboard"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|fmt
operator|=
name|EnumClipboardFormats
argument_list|(
literal|0
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|CF_BITMAP
operator|!=
name|fmt
operator|)
operator|&&
operator|(
name|CF_DIB
operator|!=
name|fmt
operator|)
operator|&&
operator|(
literal|0
operator|!=
name|fmt
operator|)
condition|)
name|fmt
operator|=
name|EnumClipboardFormats
argument_list|(
name|fmt
argument_list|)
expr_stmt|;
if|if
condition|(
literal|0
operator|==
name|fmt
condition|)
block|{
name|g_message
argument_list|(
literal|"Unsupported format or Clipboard empty!"
argument_list|)
expr_stmt|;
name|bRet
operator|=
name|FALSE
expr_stmt|;
block|}
comment|/* there is something supported */
if|if
condition|(
name|bRet
condition|)
block|{
name|hDIB
operator|=
name|GetClipboardData
argument_list|(
name|CF_DIB
argument_list|)
expr_stmt|;
if|if
condition|(
name|NULL
operator|==
name|hDIB
condition|)
block|{
name|g_warning
argument_list|(
literal|"Can't get Clipboard data"
argument_list|)
expr_stmt|;
name|bRet
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
comment|/* read header */
if|if
condition|(
name|bRet
operator|&&
name|hDIB
condition|)
block|{
name|BITMAPINFOHEADER
modifier|*
name|pInfo
decl_stmt|;
name|pInfo
operator|=
name|GlobalLock
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
if|if
condition|(
name|NULL
operator|==
name|pInfo
condition|)
block|{
name|g_warning
argument_list|(
literal|"Can't lock clipboard data!"
argument_list|)
expr_stmt|;
name|bRet
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|bRet
operator|)
operator|&&
operator|(
operator|(
name|pInfo
operator|->
name|biSize
operator|!=
sizeof|sizeof
argument_list|(
name|BITMAPINFOHEADER
argument_list|)
operator|||
operator|(
name|pInfo
operator|->
name|biCompression
operator|!=
name|BI_RGB
operator|)
operator|)
operator|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"Unupported bitmap format!"
argument_list|)
expr_stmt|;
name|bRet
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|bRet
operator|&&
name|pInfo
condition|)
block|{
name|nWidth
operator|=
name|pInfo
operator|->
name|biWidth
expr_stmt|;
name|nHeight
operator|=
name|pInfo
operator|->
name|biHeight
expr_stmt|;
name|nBitsPS
operator|=
name|pInfo
operator|->
name|biBitCount
expr_stmt|;
name|nColors
operator|=
name|pInfo
operator|->
name|biClrUsed
expr_stmt|;
block|}
name|GlobalUnlock
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
literal|0
operator|!=
name|nWidth
operator|)
operator|&&
operator|(
literal|0
operator|!=
name|nHeight
operator|)
condition|)
block|{
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|char
modifier|*
name|pData
decl_stmt|;
name|GParam
modifier|*
name|params
decl_stmt|;
name|gint
name|retval
decl_stmt|;
name|gboolean
name|bIsNewImage
init|=
name|TRUE
decl_stmt|;
name|gint
name|oldBPP
init|=
literal|0
decl_stmt|;
comment|/* Check if clipboard data and existing image are compatible */
if|if
condition|(
name|IMAGE_NONE
operator|!=
name|drawable_ID
condition|)
block|{
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|oldBPP
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|IMAGE_NONE
operator|==
name|image_ID
operator|)
operator|||
operator|(
literal|3
operator|!=
name|oldBPP
operator|)
operator|||
operator|(
literal|24
operator|!=
name|nBitsPS
operator|)
condition|)
block|{
comment|/* create new image */
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
name|nWidth
argument_list|,
name|nHeight
argument_list|,
name|nBitsPS
operator|<=
literal|8
condition|?
name|INDEXED
else|:
name|RGB
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|drawable_ID
operator|=
name|gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|nWidth
argument_list|,
name|nHeight
argument_list|,
name|nBitsPS
operator|<=
literal|8
condition|?
name|INDEXED_IMAGE
else|:
name|RGB_IMAGE
argument_list|,
literal|100
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* ??? gimp_convert_rgb(image_ID); 			 */
name|drawable_ID
operator|=
name|gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|_
argument_list|(
literal|"Pasted"
argument_list|)
argument_list|,
name|nWidth
argument_list|,
name|nHeight
argument_list|,
name|nBitsPS
operator|<=
literal|8
condition|?
name|INDEXED_IMAGE
else|:
name|RGB_IMAGE
argument_list|,
literal|100
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
name|bIsNewImage
operator|=
name|FALSE
expr_stmt|;
block|}
name|gimp_image_add_layer
argument_list|(
name|image_ID
argument_list|,
name|drawable_ID
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* following the slow part ... */
if|if
condition|(
name|interactive
condition|)
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Pasting..."
argument_list|)
argument_list|)
expr_stmt|;
name|pData
operator|=
name|GlobalLock
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
if|if
condition|(
name|pData
condition|)
block|{
name|guchar
modifier|*
name|pLine
decl_stmt|;
name|RGBQUAD
modifier|*
name|pPal
decl_stmt|;
name|int
name|nSizeLine
init|=
literal|0
decl_stmt|;
comment|/* DIB lines are 32 bit aligned */
name|nSizeLine
operator|=
operator|(
operator|(
name|nWidth
operator|*
operator|(
name|nBitsPS
operator|/
literal|8
operator|)
operator|-
literal|1
operator|)
operator|/
literal|4
operator|+
literal|1
operator|)
operator|*
literal|4
expr_stmt|;
comment|/* adjust pointer */
name|pPal
operator|=
operator|(
name|RGBQUAD
operator|*
operator|)
operator|(
name|pData
operator|+
sizeof|sizeof
argument_list|(
name|BITMAPINFOHEADER
argument_list|)
operator|)
expr_stmt|;
name|pData
operator|=
operator|(
name|guchar
operator|*
operator|)
name|pPal
operator|+
sizeof|sizeof
argument_list|(
name|RGBQUAD
argument_list|)
operator|*
name|nColors
expr_stmt|;
comment|/*  create palette */
if|if
condition|(
literal|0
operator|!=
name|nColors
condition|)
block|{
name|int
name|c
decl_stmt|;
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|cmap
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|nColors
operator|*
literal|3
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmap
condition|)
block|{
for|for
control|(
name|c
operator|=
literal|0
init|;
name|c
operator|<
name|nColors
condition|;
name|c
operator|++
control|)
block|{
name|cmap
index|[
name|c
operator|*
literal|3
index|]
operator|=
name|pPal
index|[
name|c
index|]
operator|.
name|rgbRed
expr_stmt|;
name|cmap
index|[
name|c
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|pPal
index|[
name|c
index|]
operator|.
name|rgbGreen
expr_stmt|;
name|cmap
index|[
name|c
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|pPal
index|[
name|c
index|]
operator|.
name|rgbBlue
expr_stmt|;
block|}
name|gimp_image_set_cmap
argument_list|(
name|image_ID
argument_list|,
name|cmap
argument_list|,
name|nColors
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* speed it up with: */
name|gimp_tile_cache_size
argument_list|(
name|drawable
operator|->
name|width
operator|*
name|gimp_tile_height
argument_list|()
operator|*
name|drawable
operator|->
name|bpp
argument_list|)
expr_stmt|;
comment|/* change data format and copy data */
if|if
condition|(
literal|24
operator|==
name|nBitsPS
condition|)
block|{
name|pLine
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|drawable
operator|->
name|width
operator|*
name|drawable
operator|->
name|bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|pLine
condition|)
block|{
name|int
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|drawable
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
name|int
name|x
decl_stmt|;
if|if
condition|(
operator|(
name|interactive
operator|)
operator|&&
operator|(
name|StepProgress
argument_list|(
name|y
argument_list|,
name|drawable
operator|->
name|height
argument_list|)
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|drawable
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
name|pLine
index|[
name|x
operator|*
name|drawable
operator|->
name|bpp
index|]
operator|=
name|pData
index|[
name|y
operator|*
name|nSizeLine
operator|+
name|x
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
name|pLine
index|[
name|x
operator|*
name|drawable
operator|->
name|bpp
operator|+
literal|1
index|]
operator|=
name|pData
index|[
name|y
operator|*
name|nSizeLine
operator|+
name|x
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|pLine
index|[
name|x
operator|*
name|drawable
operator|->
name|bpp
operator|+
literal|2
index|]
operator|=
name|pData
index|[
name|y
operator|*
name|nSizeLine
operator|+
name|x
operator|*
literal|3
index|]
expr_stmt|;
block|}
comment|/* copy data to GIMP */
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|pLine
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|height
operator|-
literal|1
operator|-
name|y
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|pLine
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
literal|8
operator|==
name|nBitsPS
condition|)
block|{
name|int
name|y
decl_stmt|;
comment|/* copy line by line */
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|drawable
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|interactive
operator|)
operator|&&
operator|(
name|StepProgress
argument_list|(
name|y
argument_list|,
name|drawable
operator|->
name|height
argument_list|)
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
name|pLine
operator|=
name|pData
operator|+
name|y
operator|*
name|nSizeLine
expr_stmt|;
comment|/* adjust pointer */
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|pLine
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|height
operator|-
literal|1
operator|-
name|y
argument_list|,
name|drawable
operator|->
name|width
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/* copy and shift bits */
name|g_message
argument_list|(
literal|"%d bits per sample not yet supported!"
argument_list|,
name|nBitsPS
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
comment|/* Don't miss to display the new image! 		 */
if|if
condition|(
name|bIsNewImage
condition|)
name|gimp_display_new
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
else|else
block|{
name|gimp_layer_set_visible
argument_list|(
name|drawable_ID
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
block|}
comment|/* done */
comment|/* clear clipboard? */
if|if
condition|(
name|NULL
operator|!=
name|hDIB
condition|)
name|GlobalFree
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
name|CloseClipboard
argument_list|()
expr_stmt|;
comment|/* shouldn't this be done by caller?? */
name|gimp_image_undo_enable
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
return|return
name|bRet
return|;
block|}
end_function

begin_comment
comment|/* CB_PasteImage */
end_comment

begin_comment
comment|/*  * Local Variables:  * tab-width: 4  * End:  */
end_comment

end_unit

