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
comment|/* History:  *  *   08/07/99 Implementation and release.  *	 08/10/99 Big speed increase by using gimp_tile_cache_size()  *			  Thanks to Kevin Turner's documentation at:  *			  http://www.poboxes.com/kevint/gimp/doc/plugin-doc-2.1.html  *  * TODO (maybe):  *  *   - Support for 4,2,1 bit bitmaps  *   - Unsupported formats could be delegated to GIMP Loader (e.g. wmf)  *   - ...  */
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
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
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

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GimpPlugInInfo
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
name|GimpParamDef
name|copy_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to save"
block|}
block|}
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
literal|"Copy to Clipboard"
argument_list|)
argument_list|,
literal|"INDEXED*, RGB*, GRAY*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|copy_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|copy_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
literal|"plug_in_clipboard_copy"
argument_list|,
literal|"<Image>/Edit"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|2
index|]
decl_stmt|;
name|GimpRunMode
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
name|GIMP_PDB_STATUS
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
name|GIMP_PDB_CALLING_ERROR
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
name|GIMP_RUN_INTERACTIVE
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
name|GIMP_PDB_SUCCESS
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
name|GIMP_PDB_EXECUTION_ERROR
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpImageType
name|drawable_type
decl_stmt|;
name|GimpPixelRgn
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
name|GIMP_INDEXED_IMAGE
operator|==
name|drawable_type
operator|||
name|GIMP_GRAY_IMAGE
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
name|g_message
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
name|GIMP_INDEXED_IMAGE
operator|==
name|drawable_type
operator|||
name|GIMP_GRAY_IMAGE
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
name|GIMP_INDEXED_IMAGE
operator|==
name|drawable_type
operator|||
name|GIMP_GRAY_IMAGE
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
name|g_message
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
name|GIMP_INDEXED_IMAGE
operator|==
name|drawable_type
operator|||
name|GIMP_GRAY_IMAGE
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
init|=
name|NULL
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
if|if
condition|(
name|GIMP_GRAY_IMAGE
operator|!=
name|drawable_type
condition|)
name|cmap
operator|=
name|gimp_image_get_colormap
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
elseif|else
if|if
condition|(
name|GIMP_GRAY_IMAGE
operator|==
name|drawable_type
condition|)
block|{
comment|/* fill with identity palette */
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
name|i
expr_stmt|;
name|pPal
index|[
name|i
index|]
operator|.
name|rgbGreen
operator|=
name|i
expr_stmt|;
name|pPal
index|[
name|i
index|]
operator|.
name|rgbBlue
operator|=
name|i
expr_stmt|;
block|}
name|bRet
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
name|g_message
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
name|g_message
argument_list|(
literal|"Failed to lock DIB Palette"
argument_list|)
expr_stmt|;
block|}
comment|/* indexed or grayscale */
comment|/* following the slow part ... */
if|if
condition|(
name|interactive
condition|)
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Copying..."
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
name|GIMP_INDEXED_IMAGE
operator|==
name|drawable_type
operator|||
name|GIMP_GRAY_IMAGE
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
comment|/*pData[x+y*drawable->width*3+3] = 0;*/
comment|/* reserved */
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
name|GlobalUnlock
argument_list|(
name|hDIB
argument_list|)
expr_stmt|;
block|}
comment|/* (pData) */
else|else
name|g_message
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
name|g_message
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
name|g_message
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
name|g_message
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
name|g_message
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

end_unit

