begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* bmpread.c	reads any bitmap I could get for testing */
end_comment

begin_comment
comment|/*		except OS2 bitmaps (wrong colors)        */
end_comment

begin_comment
comment|/* Alexander.Schulz@stud.uni-karlsruhe.de                */
end_comment

begin_comment
comment|/*   * The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  * ----------------------------------------------------------------------------  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"bmp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function
name|gint32
DECL|function|ReadBMP (char * name)
name|ReadBMP
parameter_list|(
name|char
modifier|*
name|name
parameter_list|)
block|{
name|FILE
modifier|*
name|fd
decl_stmt|;
name|char
modifier|*
name|temp_buf
decl_stmt|;
name|char
name|buf
index|[
literal|5
index|]
decl_stmt|;
name|int
name|ColormapSize
decl_stmt|,
name|SpeicherZeile
decl_stmt|,
name|Maps
decl_stmt|,
name|Grey
decl_stmt|;
name|unsigned
name|char
name|ColorMap
index|[
literal|256
index|]
index|[
literal|3
index|]
decl_stmt|;
name|guchar
name|puffer
index|[
literal|50
index|]
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
if|if
condition|(
name|interactive_bmp
condition|)
block|{
name|temp_buf
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|11
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|temp_buf
argument_list|,
name|_
argument_list|(
literal|"Loading %s:"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
block|}
name|filename
operator|=
name|name
expr_stmt|;
name|fd
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
expr_stmt|;
comment|/* Is this a valid File? Should never be used because gimp tests it. */
if|if
condition|(
operator|!
name|fd
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"%s: can't open \"%s\"\n"
argument_list|)
argument_list|,
name|prog_name
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* It is a File. Now is it a Bitmap? */
if|if
condition|(
operator|!
name|ReadOK
argument_list|(
name|fd
argument_list|,
name|buf
argument_list|,
literal|2
argument_list|)
operator|||
operator|(
name|strncmp
argument_list|(
name|buf
argument_list|,
literal|"BM"
argument_list|,
literal|2
argument_list|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"%s: not a valid BMP file %s\n"
argument_list|)
argument_list|,
name|prog_name
argument_list|,
name|buf
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* How long is the Header? */
if|if
condition|(
operator|!
name|ReadOK
argument_list|(
name|fd
argument_list|,
name|puffer
argument_list|,
literal|0x10
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"%s: error reading BMP file header\n"
argument_list|)
argument_list|,
name|prog_name
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* bring them to the right byteorder. Not too nice, but it should work */
name|Bitmap_File_Head
operator|.
name|bfSize
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|Bitmap_File_Head
operator|.
name|reserverd
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|4
index|]
argument_list|)
expr_stmt|;
name|Bitmap_File_Head
operator|.
name|bfOffs
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|8
index|]
argument_list|)
expr_stmt|;
name|Bitmap_File_Head
operator|.
name|biSize
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|12
index|]
argument_list|)
expr_stmt|;
comment|/* Is it a Windows (R) Bitmap or not */
if|if
condition|(
name|Bitmap_File_Head
operator|.
name|biSize
operator|!=
literal|40
condition|)
block|{
name|g_warning
argument_list|(
name|_
argument_list|(
literal|"OS/2 unsupported!\n"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|ReadOK
argument_list|(
name|fd
argument_list|,
name|puffer
argument_list|,
name|Bitmap_File_Head
operator|.
name|biSize
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"%s: error reading BMP file header\n"
argument_list|)
argument_list|,
name|prog_name
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|Bitmap_OS2_Head
operator|.
name|bcWidth
operator|=
name|ToS
argument_list|(
operator|&
name|puffer
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|Bitmap_OS2_Head
operator|.
name|bcHeight
operator|=
name|ToS
argument_list|(
operator|&
name|puffer
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|Bitmap_OS2_Head
operator|.
name|bcPlanes
operator|=
name|ToS
argument_list|(
operator|&
name|puffer
index|[
literal|4
index|]
argument_list|)
expr_stmt|;
name|Bitmap_OS2_Head
operator|.
name|bcBitCnt
operator|=
name|ToS
argument_list|(
operator|&
name|puffer
index|[
literal|6
index|]
argument_list|)
expr_stmt|;
name|Bitmap_Head
operator|.
name|biPlanes
operator|=
name|Bitmap_OS2_Head
operator|.
name|bcPlanes
expr_stmt|;
name|Bitmap_Head
operator|.
name|biBitCnt
operator|=
name|Bitmap_OS2_Head
operator|.
name|bcBitCnt
expr_stmt|;
name|Bitmap_File_Head
operator|.
name|bfSize
operator|=
operator|(
name|Bitmap_File_Head
operator|.
name|bfSize
operator|*
literal|4
operator|)
operator|-
operator|(
name|Bitmap_File_Head
operator|.
name|bfOffs
operator|*
literal|3
operator|)
expr_stmt|;
name|Bitmap_Head
operator|.
name|biHeight
operator|=
name|Bitmap_OS2_Head
operator|.
name|bcHeight
expr_stmt|;
name|Bitmap_Head
operator|.
name|biWidth
operator|=
name|Bitmap_OS2_Head
operator|.
name|bcWidth
expr_stmt|;
name|Bitmap_Head
operator|.
name|biClrUsed
operator|=
literal|0
expr_stmt|;
name|Bitmap_Head
operator|.
name|biCompr
operator|=
literal|0
expr_stmt|;
name|Maps
operator|=
literal|3
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|ReadOK
argument_list|(
name|fd
argument_list|,
name|puffer
argument_list|,
literal|36
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"%s: error reading BMP file header\n"
argument_list|)
argument_list|,
name|prog_name
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|Bitmap_Head
operator|.
name|biWidth
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|0x00
index|]
argument_list|)
expr_stmt|;
comment|/* 12 */
name|Bitmap_Head
operator|.
name|biHeight
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|0x04
index|]
argument_list|)
expr_stmt|;
comment|/* 16 */
name|Bitmap_Head
operator|.
name|biPlanes
operator|=
name|ToS
argument_list|(
operator|&
name|puffer
index|[
literal|0x08
index|]
argument_list|)
expr_stmt|;
comment|/* 1A */
name|Bitmap_Head
operator|.
name|biBitCnt
operator|=
name|ToS
argument_list|(
operator|&
name|puffer
index|[
literal|0x0A
index|]
argument_list|)
expr_stmt|;
comment|/* 1C */
name|Bitmap_Head
operator|.
name|biCompr
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|0x0C
index|]
argument_list|)
expr_stmt|;
comment|/* 1E */
name|Bitmap_Head
operator|.
name|biSizeIm
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|0x10
index|]
argument_list|)
expr_stmt|;
comment|/* 22 */
name|Bitmap_Head
operator|.
name|biXPels
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|0x14
index|]
argument_list|)
expr_stmt|;
comment|/* 26 */
name|Bitmap_Head
operator|.
name|biYPels
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|0x18
index|]
argument_list|)
expr_stmt|;
comment|/* 2A */
name|Bitmap_Head
operator|.
name|biClrUsed
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|0x1C
index|]
argument_list|)
expr_stmt|;
comment|/* 2E */
name|Bitmap_Head
operator|.
name|biClrImp
operator|=
name|ToL
argument_list|(
operator|&
name|puffer
index|[
literal|0x20
index|]
argument_list|)
expr_stmt|;
comment|/* 32 */
comment|/* 36 */
name|Maps
operator|=
literal|4
expr_stmt|;
block|}
comment|/* This means wrong file Format. I test this because it could crash the */
comment|/* entire gimp.							  */
if|if
condition|(
name|Bitmap_Head
operator|.
name|biBitCnt
operator|>
literal|24
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"%s: too many colors: %u\n"
argument_list|)
argument_list|,
name|prog_name
argument_list|,
operator|(
name|unsigned
name|int
operator|)
name|Bitmap_Head
operator|.
name|biBitCnt
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* There should be some colors used! */
name|ColormapSize
operator|=
operator|(
name|Bitmap_File_Head
operator|.
name|bfOffs
operator|-
name|Bitmap_File_Head
operator|.
name|biSize
operator|-
literal|14
operator|)
operator|/
name|Maps
expr_stmt|;
if|if
condition|(
operator|(
name|Bitmap_Head
operator|.
name|biClrUsed
operator|==
literal|0
operator|)
operator|&&
operator|(
name|Bitmap_Head
operator|.
name|biBitCnt
operator|<
literal|24
operator|)
condition|)
name|Bitmap_Head
operator|.
name|biClrUsed
operator|=
name|ColormapSize
expr_stmt|;
if|if
condition|(
name|Bitmap_Head
operator|.
name|biBitCnt
operator|==
literal|24
condition|)
name|SpeicherZeile
operator|=
operator|(
operator|(
name|Bitmap_File_Head
operator|.
name|bfSize
operator|-
name|Bitmap_File_Head
operator|.
name|bfOffs
operator|)
operator|/
name|Bitmap_Head
operator|.
name|biHeight
operator|)
expr_stmt|;
else|else
name|SpeicherZeile
operator|=
operator|(
operator|(
name|Bitmap_File_Head
operator|.
name|bfSize
operator|-
name|Bitmap_File_Head
operator|.
name|bfOffs
operator|)
operator|/
name|Bitmap_Head
operator|.
name|biHeight
operator|)
operator|*
operator|(
literal|8
operator|/
name|Bitmap_Head
operator|.
name|biBitCnt
operator|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"\nSize: %u, Colors: %u, Bits: %u, Width: %u, Height: %u, Comp: %u, Zeile: %u\n"
argument_list|,
name|Bitmap_File_Head
operator|.
name|bfSize
argument_list|,
name|Bitmap_Head
operator|.
name|biClrUsed
argument_list|,
name|Bitmap_Head
operator|.
name|biBitCnt
argument_list|,
name|Bitmap_Head
operator|.
name|biWidth
argument_list|,
name|Bitmap_Head
operator|.
name|biHeight
argument_list|,
name|Bitmap_Head
operator|.
name|biCompr
argument_list|,
name|SpeicherZeile
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* Get the Colormap */
if|if
condition|(
name|ReadColorMap
argument_list|(
name|fd
argument_list|,
name|ColorMap
argument_list|,
name|ColormapSize
argument_list|,
name|Maps
argument_list|,
operator|&
name|Grey
argument_list|)
operator|==
operator|-
literal|1
condition|)
return|return
operator|-
literal|1
return|;
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"Colormap read\n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* Get the Image and return the ID or -1 on error*/
name|image_ID
operator|=
name|ReadImage
argument_list|(
name|fd
argument_list|,
name|Bitmap_Head
operator|.
name|biWidth
argument_list|,
name|Bitmap_Head
operator|.
name|biHeight
argument_list|,
name|ColorMap
argument_list|,
name|Bitmap_Head
operator|.
name|biClrUsed
argument_list|,
name|Bitmap_Head
operator|.
name|biBitCnt
argument_list|,
name|Bitmap_Head
operator|.
name|biCompr
argument_list|,
name|SpeicherZeile
argument_list|,
name|Grey
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HAVE_RESOLUTION_INFO
block|{
comment|/* quick hack by the muppet, scott@asofyet.org, 19 dec 1999 */
name|double
name|xresolution
decl_stmt|;
name|double
name|yresolution
decl_stmt|;
comment|/*      * xresolution and yresolution are in dots per inch.      * the BMP spec says that biXPels and biYPels are in      * pixels per meter as long ints (actually, "DWORDS").      * this means we've lost some accuracy in the numbers.      * typically, the dots per inch settings on BMPs will      * be integer numbers of dots per inch, which is freaky      * because they're stored in the BMP as metric.  *sigh*      * so, we'll round this off, even though the gimp wants      * a floating point number...      */
DECL|macro|LROUND (x)
define|#
directive|define
name|LROUND
parameter_list|(
name|x
parameter_list|)
value|((long int)((x)+0.5))
name|xresolution
operator|=
name|LROUND
argument_list|(
operator|(
name|Bitmap_Head
operator|.
name|biXPels
operator|*
literal|2.54
operator|/
literal|100.0
operator|)
argument_list|)
expr_stmt|;
name|yresolution
operator|=
name|LROUND
argument_list|(
operator|(
name|Bitmap_Head
operator|.
name|biYPels
operator|*
literal|2.54
operator|/
literal|100.0
operator|)
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|LROUND
name|gimp_image_set_resolution
argument_list|(
name|image_ID
argument_list|,
name|xresolution
argument_list|,
name|yresolution
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
comment|/* GIMP_HAVE_RESOLUTION_INFO */
return|return
operator|(
name|image_ID
operator|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|ReadColorMap (FILE * fd,unsigned char buffer[256][3],int number,int size,int * grey)
name|ReadColorMap
parameter_list|(
name|FILE
modifier|*
name|fd
parameter_list|,
name|unsigned
name|char
name|buffer
index|[
literal|256
index|]
index|[
literal|3
index|]
parameter_list|,
name|int
name|number
parameter_list|,
name|int
name|size
parameter_list|,
name|int
modifier|*
name|grey
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
name|unsigned
name|char
name|rgb
index|[
literal|4
index|]
decl_stmt|;
operator|*
name|grey
operator|=
operator|(
name|number
operator|>
literal|2
operator|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|number
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|ReadOK
argument_list|(
name|fd
argument_list|,
name|rgb
argument_list|,
name|size
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"%s: bad colormap\n"
argument_list|)
argument_list|,
name|prog_name
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* Bitmap save the colors in another order! But change only once! */
if|if
condition|(
name|size
operator|==
literal|4
condition|)
block|{
name|buffer
index|[
name|i
index|]
index|[
literal|0
index|]
operator|=
name|rgb
index|[
literal|2
index|]
expr_stmt|;
name|buffer
index|[
name|i
index|]
index|[
literal|1
index|]
operator|=
name|rgb
index|[
literal|1
index|]
expr_stmt|;
name|buffer
index|[
name|i
index|]
index|[
literal|2
index|]
operator|=
name|rgb
index|[
literal|0
index|]
expr_stmt|;
block|}
else|else
block|{
comment|/* this one is for old os2 Bitmaps, but it dosn't work well */
name|buffer
index|[
name|i
index|]
index|[
literal|0
index|]
operator|=
name|rgb
index|[
literal|1
index|]
expr_stmt|;
name|buffer
index|[
name|i
index|]
index|[
literal|1
index|]
operator|=
name|rgb
index|[
literal|0
index|]
expr_stmt|;
name|buffer
index|[
name|i
index|]
index|[
literal|2
index|]
operator|=
name|rgb
index|[
literal|2
index|]
expr_stmt|;
block|}
operator|*
name|grey
operator|=
operator|(
operator|(
operator|*
name|grey
operator|)
operator|&&
operator|(
name|rgb
index|[
literal|0
index|]
operator|==
name|rgb
index|[
literal|1
index|]
operator|)
operator|&&
operator|(
name|rgb
index|[
literal|1
index|]
operator|==
name|rgb
index|[
literal|2
index|]
operator|)
operator|)
expr_stmt|;
block|}
return|return
operator|(
literal|0
operator|)
return|;
block|}
end_function

begin_function
name|Image
DECL|function|ReadImage (FILE * fd,int len,int height,unsigned char cmap[256][3],int ncols,int bpp,int compression,int spzeile,int grey)
name|ReadImage
parameter_list|(
name|FILE
modifier|*
name|fd
parameter_list|,
name|int
name|len
parameter_list|,
name|int
name|height
parameter_list|,
name|unsigned
name|char
name|cmap
index|[
literal|256
index|]
index|[
literal|3
index|]
parameter_list|,
name|int
name|ncols
parameter_list|,
name|int
name|bpp
parameter_list|,
name|int
name|compression
parameter_list|,
name|int
name|spzeile
parameter_list|,
name|int
name|grey
parameter_list|)
block|{
name|char
modifier|*
name|name_buf
decl_stmt|;
name|unsigned
name|char
name|v
decl_stmt|,
name|wieviel
decl_stmt|;
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|char
name|buf
index|[
literal|16
index|]
decl_stmt|;
name|int
name|xpos
init|=
literal|0
decl_stmt|,
name|ypos
init|=
literal|0
decl_stmt|;
name|Image
name|image
decl_stmt|;
name|gint32
name|layer
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|,
modifier|*
name|temp
decl_stmt|;
name|guchar
name|gimp_cmap
index|[
literal|768
index|]
decl_stmt|;
name|long
name|rowstride
decl_stmt|,
name|channels
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|cur_progress
decl_stmt|,
name|max_progress
decl_stmt|,
name|egal
decl_stmt|;
comment|/* Make a new image in the gimp */
if|if
condition|(
name|grey
condition|)
block|{
name|image
operator|=
name|gimp_image_new
argument_list|(
name|len
argument_list|,
name|height
argument_list|,
name|GRAY
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|len
argument_list|,
name|height
argument_list|,
name|GRAY_IMAGE
argument_list|,
literal|100
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
name|channels
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|bpp
operator|<
literal|24
condition|)
block|{
name|image
operator|=
name|gimp_image_new
argument_list|(
name|len
argument_list|,
name|height
argument_list|,
name|INDEXED
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|len
argument_list|,
name|height
argument_list|,
name|INDEXED_IMAGE
argument_list|,
literal|100
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
name|channels
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
name|image
operator|=
name|gimp_image_new
argument_list|(
name|len
argument_list|,
name|height
argument_list|,
name|RGB
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|len
argument_list|,
name|height
argument_list|,
name|RGB_IMAGE
argument_list|,
literal|100
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
name|channels
operator|=
literal|3
expr_stmt|;
block|}
block|}
name|name_buf
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|filename
argument_list|)
operator|+
literal|10
argument_list|)
expr_stmt|;
name|strcpy
argument_list|(
name|name_buf
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
name|image
argument_list|,
name|name_buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name_buf
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|dest
operator|=
name|g_malloc
argument_list|(
name|drawable
operator|->
name|width
operator|*
name|drawable
operator|->
name|height
operator|*
name|channels
argument_list|)
expr_stmt|;
name|rowstride
operator|=
name|drawable
operator|->
name|width
operator|*
name|channels
expr_stmt|;
name|ypos
operator|=
name|height
operator|-
literal|1
expr_stmt|;
comment|/* Bitmaps begin in the lower left corner */
name|cur_progress
operator|=
literal|0
expr_stmt|;
name|max_progress
operator|=
name|height
expr_stmt|;
if|if
condition|(
name|bpp
operator|==
literal|24
condition|)
block|{
while|while
condition|(
name|ReadOK
argument_list|(
name|fd
argument_list|,
name|buf
argument_list|,
literal|3
argument_list|)
condition|)
block|{
name|temp
operator|=
name|dest
operator|+
operator|(
name|ypos
operator|*
name|rowstride
operator|)
operator|+
operator|(
name|xpos
operator|*
name|channels
operator|)
expr_stmt|;
operator|*
name|temp
operator|=
name|buf
index|[
literal|2
index|]
expr_stmt|;
name|temp
operator|++
expr_stmt|;
operator|*
name|temp
operator|=
name|buf
index|[
literal|1
index|]
expr_stmt|;
name|temp
operator|++
expr_stmt|;
operator|*
name|temp
operator|=
name|buf
index|[
literal|0
index|]
expr_stmt|;
name|xpos
operator|++
expr_stmt|;
if|if
condition|(
name|xpos
operator|==
name|len
condition|)
block|{
name|egal
operator|=
name|ReadOK
argument_list|(
name|fd
argument_list|,
name|buf
argument_list|,
name|spzeile
operator|-
operator|(
name|len
operator|*
literal|3
operator|)
argument_list|)
expr_stmt|;
name|ypos
operator|--
expr_stmt|;
name|xpos
operator|=
literal|0
expr_stmt|;
name|cur_progress
operator|++
expr_stmt|;
if|if
condition|(
operator|(
name|interactive_bmp
operator|)
operator|&&
operator|(
operator|(
name|cur_progress
operator|%
literal|5
operator|)
operator|==
literal|0
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|cur_progress
operator|/
operator|(
name|double
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ypos
operator|<
literal|0
condition|)
break|break;
block|}
block|}
else|else
block|{
switch|switch
condition|(
name|compression
condition|)
block|{
case|case
literal|0
case|:
comment|/* uncompressed */
block|{
while|while
condition|(
name|ReadOK
argument_list|(
name|fd
argument_list|,
operator|&
name|v
argument_list|,
literal|1
argument_list|)
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|1
init|;
operator|(
name|i
operator|<=
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|)
operator|&&
operator|(
name|xpos
operator|<
name|len
operator|)
condition|;
name|i
operator|++
operator|,
name|xpos
operator|++
control|)
block|{
name|temp
operator|=
name|dest
operator|+
operator|(
name|ypos
operator|*
name|rowstride
operator|)
operator|+
operator|(
name|xpos
operator|*
name|channels
operator|)
expr_stmt|;
operator|*
name|temp
operator|=
operator|(
name|v
operator|&
operator|(
operator|(
operator|(
literal|1
operator|<<
name|bpp
operator|)
operator|-
literal|1
operator|)
operator|<<
operator|(
literal|8
operator|-
operator|(
name|i
operator|*
name|bpp
operator|)
operator|)
operator|)
operator|)
operator|>>
operator|(
literal|8
operator|-
operator|(
name|i
operator|*
name|bpp
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|grey
condition|)
operator|*
name|temp
operator|=
name|cmap
index|[
operator|*
name|temp
index|]
index|[
literal|0
index|]
expr_stmt|;
block|}
if|if
condition|(
name|xpos
operator|==
name|len
condition|)
block|{
name|egal
operator|=
name|ReadOK
argument_list|(
name|fd
argument_list|,
name|buf
argument_list|,
operator|(
name|spzeile
operator|-
name|len
operator|)
operator|/
operator|(
literal|8
operator|/
name|bpp
operator|)
argument_list|)
expr_stmt|;
name|ypos
operator|--
expr_stmt|;
name|xpos
operator|=
literal|0
expr_stmt|;
name|cur_progress
operator|++
expr_stmt|;
if|if
condition|(
operator|(
name|interactive_bmp
operator|)
operator|&&
operator|(
operator|(
name|cur_progress
operator|%
literal|5
operator|)
operator|==
literal|0
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|cur_progress
operator|/
operator|(
name|double
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ypos
operator|<
literal|0
condition|)
break|break;
block|}
break|break;
block|}
default|default:
comment|/* Compressed images */
block|{
while|while
condition|(
name|TRUE
condition|)
block|{
name|egal
operator|=
name|ReadOK
argument_list|(
name|fd
argument_list|,
name|buf
argument_list|,
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|0
index|]
operator|!=
literal|0
condition|)
comment|/* Count + Color - record */
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
operator|(
operator|(
name|unsigned
name|char
operator|)
name|j
operator|<
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|0
index|]
operator|)
operator|&&
operator|(
name|xpos
operator|<
name|len
operator|)
condition|;
control|)
block|{
ifdef|#
directive|ifdef
name|DEBUG2
name|printf
argument_list|(
literal|"%u %u | "
argument_list|,
name|xpos
argument_list|,
name|len
argument_list|)
expr_stmt|;
endif|#
directive|endif
for|for
control|(
name|i
operator|=
literal|1
init|;
operator|(
operator|(
name|i
operator|<=
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|)
operator|&&
operator|(
name|xpos
operator|<
name|len
operator|)
operator|&&
operator|(
operator|(
name|unsigned
name|char
operator|)
name|j
operator|<
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|0
index|]
operator|)
operator|)
condition|;
name|i
operator|++
operator|,
name|xpos
operator|++
operator|,
name|j
operator|++
control|)
block|{
name|temp
operator|=
name|dest
operator|+
operator|(
name|ypos
operator|*
name|rowstride
operator|)
operator|+
operator|(
name|xpos
operator|*
name|channels
operator|)
expr_stmt|;
operator|*
name|temp
operator|=
operator|(
name|buf
index|[
literal|1
index|]
operator|&
operator|(
operator|(
operator|(
literal|1
operator|<<
name|bpp
operator|)
operator|-
literal|1
operator|)
operator|<<
operator|(
literal|8
operator|-
operator|(
name|i
operator|*
name|bpp
operator|)
operator|)
operator|)
operator|)
operator|>>
operator|(
literal|8
operator|-
operator|(
name|i
operator|*
name|bpp
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|grey
condition|)
operator|*
name|temp
operator|=
name|cmap
index|[
operator|*
name|temp
index|]
index|[
literal|0
index|]
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
operator|(
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|0
index|]
operator|==
literal|0
operator|)
operator|&&
operator|(
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|1
index|]
operator|>
literal|2
operator|)
condition|)
comment|/* uncompressed record */
block|{
name|wieviel
operator|=
name|buf
index|[
literal|1
index|]
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|wieviel
condition|;
name|j
operator|+=
operator|(
literal|8
operator|/
name|bpp
operator|)
control|)
block|{
name|egal
operator|=
name|ReadOK
argument_list|(
name|fd
argument_list|,
operator|&
name|v
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|i
operator|=
literal|1
expr_stmt|;
while|while
condition|(
operator|(
name|i
operator|<=
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|)
operator|&&
operator|(
name|xpos
operator|<
name|len
operator|)
condition|)
block|{
name|temp
operator|=
name|dest
operator|+
operator|(
name|ypos
operator|*
name|rowstride
operator|)
operator|+
operator|(
name|xpos
operator|*
name|channels
operator|)
expr_stmt|;
operator|*
name|temp
operator|=
operator|(
name|v
operator|&
operator|(
operator|(
operator|(
literal|1
operator|<<
name|bpp
operator|)
operator|-
literal|1
operator|)
operator|<<
operator|(
literal|8
operator|-
operator|(
name|i
operator|*
name|bpp
operator|)
operator|)
operator|)
operator|)
operator|>>
operator|(
literal|8
operator|-
operator|(
name|i
operator|*
name|bpp
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|grey
condition|)
operator|*
name|temp
operator|=
name|cmap
index|[
operator|*
name|temp
index|]
index|[
literal|0
index|]
expr_stmt|;
name|i
operator|++
expr_stmt|;
name|xpos
operator|++
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|(
name|wieviel
operator|%
literal|2
operator|)
operator|&&
operator|(
name|bpp
operator|==
literal|4
operator|)
condition|)
name|wieviel
operator|++
expr_stmt|;
if|if
condition|(
operator|(
name|wieviel
operator|/
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|)
operator|%
literal|2
condition|)
name|egal
operator|=
name|ReadOK
argument_list|(
name|fd
argument_list|,
operator|&
name|v
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/*if odd(x div (8 div bpp )) then blockread(f,z^,1);*/
block|}
if|if
condition|(
operator|(
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|0
index|]
operator|==
literal|0
operator|)
operator|&&
operator|(
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|1
index|]
operator|==
literal|0
operator|)
condition|)
comment|/* Zeilenende */
block|{
name|ypos
operator|--
expr_stmt|;
name|xpos
operator|=
literal|0
expr_stmt|;
name|cur_progress
operator|++
expr_stmt|;
if|if
condition|(
operator|(
name|interactive_bmp
operator|)
operator|&&
operator|(
operator|(
name|cur_progress
operator|%
literal|5
operator|)
operator|==
literal|0
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|cur_progress
operator|/
operator|(
name|double
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|0
index|]
operator|==
literal|0
operator|)
operator|&&
operator|(
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|1
index|]
operator|==
literal|1
operator|)
condition|)
comment|/* Bitmapende */
block|{
break|break;
block|}
if|if
condition|(
operator|(
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|0
index|]
operator|==
literal|0
operator|)
operator|&&
operator|(
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|1
index|]
operator|==
literal|2
operator|)
condition|)
comment|/* Deltarecord */
block|{
name|xpos
operator|+=
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|2
index|]
expr_stmt|;
name|ypos
operator|+=
operator|(
name|unsigned
name|char
operator|)
name|buf
index|[
literal|3
index|]
expr_stmt|;
block|}
block|}
break|break;
block|}
block|}
block|}
name|fclose
argument_list|(
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
name|bpp
operator|<
literal|24
condition|)
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|j
operator|=
literal|0
init|;
name|i
operator|<
name|ncols
condition|;
name|i
operator|++
control|)
block|{
name|gimp_cmap
index|[
name|j
operator|++
index|]
operator|=
name|cmap
index|[
name|i
index|]
index|[
literal|0
index|]
expr_stmt|;
name|gimp_cmap
index|[
name|j
operator|++
index|]
operator|=
name|cmap
index|[
name|i
index|]
index|[
literal|1
index|]
expr_stmt|;
name|gimp_cmap
index|[
name|j
operator|++
index|]
operator|=
name|cmap
index|[
name|i
index|]
index|[
literal|2
index|]
expr_stmt|;
block|}
if|if
condition|(
name|interactive_bmp
condition|)
name|gimp_progress_update
argument_list|(
literal|1
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
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|dest
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
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|!
name|grey
operator|)
operator|&&
operator|(
name|bpp
operator|<
literal|24
operator|)
condition|)
name|gimp_image_set_cmap
argument_list|(
name|image
argument_list|,
name|gimp_cmap
argument_list|,
name|ncols
argument_list|)
expr_stmt|;
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
name|g_free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
return|return
operator|(
name|image
operator|)
return|;
block|}
end_function

end_unit

