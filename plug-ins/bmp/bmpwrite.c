begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* bmpwrite.c   Writes Bitmap files. Even RLE encoded ones.      */
end_comment

begin_comment
comment|/*              (Windows (TM) doesn't read all of those, but who */
end_comment

begin_comment
comment|/*              cares? ;-)                                       */
end_comment

begin_comment
comment|/*              I changed a few things over the time, so perhaps */
end_comment

begin_comment
comment|/*              it dos now, but now there's no Windows left on   */
end_comment

begin_comment
comment|/*              my computer...                                   */
end_comment

begin_comment
comment|/* Alexander.Schulz@stud.uni-karlsruhe.de                        */
end_comment

begin_comment
comment|/*  * The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  * ----------------------------------------------------------------------------  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
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

begin_decl_stmt
DECL|variable|cur_progress
specifier|static
name|gint
name|cur_progress
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|max_progress
specifier|static
name|gint
name|max_progress
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|encoded
specifier|static
name|gint
name|encoded
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|WriteImage
parameter_list|(
name|FILE
modifier|*
name|f
parameter_list|,
name|guchar
modifier|*
name|src
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|encoded
parameter_list|,
name|gint
name|channels
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|spzeile
parameter_list|,
name|gint
name|MapSize
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|save_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|FromL (gint32 wert,guchar * bopuffer)
name|FromL
parameter_list|(
name|gint32
name|wert
parameter_list|,
name|guchar
modifier|*
name|bopuffer
parameter_list|)
block|{
name|bopuffer
index|[
literal|0
index|]
operator|=
operator|(
name|wert
operator|&
literal|0x000000ff
operator|)
operator|>>
literal|0x00
expr_stmt|;
name|bopuffer
index|[
literal|1
index|]
operator|=
operator|(
name|wert
operator|&
literal|0x0000ff00
operator|)
operator|>>
literal|0x08
expr_stmt|;
name|bopuffer
index|[
literal|2
index|]
operator|=
operator|(
name|wert
operator|&
literal|0x00ff0000
operator|)
operator|>>
literal|0x10
expr_stmt|;
name|bopuffer
index|[
literal|3
index|]
operator|=
operator|(
name|wert
operator|&
literal|0xff000000
operator|)
operator|>>
literal|0x18
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|FromS (gint16 wert,guchar * bopuffer)
name|FromS
parameter_list|(
name|gint16
name|wert
parameter_list|,
name|guchar
modifier|*
name|bopuffer
parameter_list|)
block|{
name|bopuffer
index|[
literal|0
index|]
operator|=
operator|(
name|wert
operator|&
literal|0x00ff
operator|)
operator|>>
literal|0x00
expr_stmt|;
name|bopuffer
index|[
literal|1
index|]
operator|=
operator|(
name|wert
operator|&
literal|0xff00
operator|)
operator|>>
literal|0x08
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|WriteColorMap (FILE * f,gint red[MAXCOLORS],gint green[MAXCOLORS],gint blue[MAXCOLORS],gint size)
name|WriteColorMap
parameter_list|(
name|FILE
modifier|*
name|f
parameter_list|,
name|gint
name|red
index|[
name|MAXCOLORS
index|]
parameter_list|,
name|gint
name|green
index|[
name|MAXCOLORS
index|]
parameter_list|,
name|gint
name|blue
index|[
name|MAXCOLORS
index|]
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|gchar
name|trgb
index|[
literal|4
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|size
operator|/=
literal|4
expr_stmt|;
name|trgb
index|[
literal|3
index|]
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|size
condition|;
name|i
operator|++
control|)
block|{
name|trgb
index|[
literal|0
index|]
operator|=
operator|(
name|guchar
operator|)
name|blue
index|[
name|i
index|]
expr_stmt|;
name|trgb
index|[
literal|1
index|]
operator|=
operator|(
name|guchar
operator|)
name|green
index|[
name|i
index|]
expr_stmt|;
name|trgb
index|[
literal|2
index|]
operator|=
operator|(
name|guchar
operator|)
name|red
index|[
name|i
index|]
expr_stmt|;
name|Write
argument_list|(
name|f
argument_list|,
name|trgb
argument_list|,
literal|4
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpPDBStatusType
DECL|function|WriteBMP (const gchar * filename,gint32 image,gint32 drawable_ID)
name|WriteBMP
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|image
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|FILE
modifier|*
name|outfile
decl_stmt|;
name|gint
name|Red
index|[
name|MAXCOLORS
index|]
decl_stmt|;
name|gint
name|Green
index|[
name|MAXCOLORS
index|]
decl_stmt|;
name|gint
name|Blue
index|[
name|MAXCOLORS
index|]
decl_stmt|;
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|gint
name|rows
decl_stmt|,
name|cols
decl_stmt|,
name|Spcols
decl_stmt|,
name|channels
decl_stmt|,
name|MapSize
decl_stmt|,
name|SpZeile
decl_stmt|;
name|glong
name|BitsPerPixel
decl_stmt|;
name|gint
name|colors
decl_stmt|;
name|gchar
modifier|*
name|temp_buf
decl_stmt|;
name|guchar
modifier|*
name|pixels
decl_stmt|;
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpImageType
name|drawable_type
decl_stmt|;
name|guchar
name|puffer
index|[
literal|50
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/* first: can we save this image? */
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
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot save images with alpha channel."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
block|}
comment|/* We can save it. So what colors do we use? */
switch|switch
condition|(
name|drawable_type
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
name|colors
operator|=
literal|0
expr_stmt|;
name|BitsPerPixel
operator|=
literal|24
expr_stmt|;
name|MapSize
operator|=
literal|0
expr_stmt|;
name|channels
operator|=
literal|3
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
name|colors
operator|=
literal|256
expr_stmt|;
name|BitsPerPixel
operator|=
literal|8
expr_stmt|;
name|MapSize
operator|=
literal|1024
expr_stmt|;
name|channels
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|colors
condition|;
name|i
operator|++
control|)
block|{
name|Red
index|[
name|i
index|]
operator|=
name|i
expr_stmt|;
name|Green
index|[
name|i
index|]
operator|=
name|i
expr_stmt|;
name|Blue
index|[
name|i
index|]
operator|=
name|i
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_INDEXED_IMAGE
case|:
name|cmap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|,
operator|&
name|colors
argument_list|)
expr_stmt|;
name|MapSize
operator|=
literal|4
operator|*
name|colors
expr_stmt|;
name|channels
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|colors
operator|>
literal|16
condition|)
name|BitsPerPixel
operator|=
literal|8
expr_stmt|;
elseif|else
if|if
condition|(
name|colors
operator|>
literal|2
condition|)
name|BitsPerPixel
operator|=
literal|4
expr_stmt|;
else|else
name|BitsPerPixel
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|colors
condition|;
name|i
operator|++
control|)
block|{
name|Red
index|[
name|i
index|]
operator|=
operator|*
name|cmap
operator|++
expr_stmt|;
name|Green
index|[
name|i
index|]
operator|=
operator|*
name|cmap
operator|++
expr_stmt|;
name|Blue
index|[
name|i
index|]
operator|=
operator|*
name|cmap
operator|++
expr_stmt|;
block|}
break|break;
default|default:
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot operate on unknown image types."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
block|}
comment|/* Perhaps someone wants RLE encoded Bitmaps */
name|encoded
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|(
name|BitsPerPixel
operator|==
literal|8
operator|||
name|BitsPerPixel
operator|==
literal|4
operator|)
operator|&&
name|interactive_bmp
condition|)
block|{
if|if
condition|(
operator|!
name|save_dialog
argument_list|()
condition|)
return|return
name|GIMP_PDB_CANCEL
return|;
block|}
comment|/* Let's take some file */
name|outfile
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|outfile
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Could not open '%s' for writing: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
block|}
comment|/* fetch the image */
name|pixels
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
name|height
operator|*
name|channels
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|pixels
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
comment|/* And let's begin the progress */
name|temp_buf
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Saving '%s'..."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
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
name|cur_progress
operator|=
literal|0
expr_stmt|;
name|max_progress
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
comment|/* Now, we need some further information ... */
name|cols
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|rows
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
comment|/* ... that we write to our headers. */
if|if
condition|(
operator|(
name|BitsPerPixel
operator|!=
literal|24
operator|)
operator|&&
operator|(
name|cols
operator|%
operator|(
literal|8
operator|/
name|BitsPerPixel
operator|)
operator|)
condition|)
name|Spcols
operator|=
operator|(
operator|(
operator|(
name|cols
operator|/
operator|(
literal|8
operator|/
name|BitsPerPixel
operator|)
operator|)
operator|+
literal|1
operator|)
operator|*
operator|(
literal|8
operator|/
name|BitsPerPixel
operator|)
operator|)
expr_stmt|;
else|else
name|Spcols
operator|=
name|cols
expr_stmt|;
if|if
condition|(
operator|(
operator|(
operator|(
name|Spcols
operator|*
name|BitsPerPixel
operator|)
operator|/
literal|8
operator|)
operator|%
literal|4
operator|)
operator|==
literal|0
condition|)
name|SpZeile
operator|=
operator|(
operator|(
name|Spcols
operator|*
name|BitsPerPixel
operator|)
operator|/
literal|8
operator|)
expr_stmt|;
else|else
name|SpZeile
operator|=
operator|(
call|(
name|gint
call|)
argument_list|(
operator|(
operator|(
name|Spcols
operator|*
name|BitsPerPixel
operator|)
operator|/
literal|8
operator|)
operator|/
literal|4
argument_list|)
operator|+
literal|1
operator|)
operator|*
literal|4
expr_stmt|;
name|Bitmap_File_Head
operator|.
name|bfSize
operator|=
literal|0x36
operator|+
name|MapSize
operator|+
operator|(
name|rows
operator|*
name|SpZeile
operator|)
expr_stmt|;
name|Bitmap_File_Head
operator|.
name|zzHotX
operator|=
literal|0
expr_stmt|;
name|Bitmap_File_Head
operator|.
name|zzHotY
operator|=
literal|0
expr_stmt|;
name|Bitmap_File_Head
operator|.
name|bfOffs
operator|=
literal|0x36
operator|+
name|MapSize
expr_stmt|;
name|Bitmap_File_Head
operator|.
name|biSize
operator|=
literal|40
expr_stmt|;
name|Bitmap_Head
operator|.
name|biWidth
operator|=
name|cols
expr_stmt|;
name|Bitmap_Head
operator|.
name|biHeight
operator|=
name|rows
expr_stmt|;
name|Bitmap_Head
operator|.
name|biPlanes
operator|=
literal|1
expr_stmt|;
name|Bitmap_Head
operator|.
name|biBitCnt
operator|=
name|BitsPerPixel
expr_stmt|;
if|if
condition|(
name|encoded
operator|==
literal|0
condition|)
name|Bitmap_Head
operator|.
name|biCompr
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|BitsPerPixel
operator|==
literal|8
condition|)
name|Bitmap_Head
operator|.
name|biCompr
operator|=
literal|1
expr_stmt|;
elseif|else
if|if
condition|(
name|BitsPerPixel
operator|==
literal|4
condition|)
name|Bitmap_Head
operator|.
name|biCompr
operator|=
literal|2
expr_stmt|;
else|else
name|Bitmap_Head
operator|.
name|biCompr
operator|=
literal|0
expr_stmt|;
name|Bitmap_Head
operator|.
name|biSizeIm
operator|=
name|SpZeile
operator|*
name|rows
expr_stmt|;
block|{
name|gdouble
name|xresolution
decl_stmt|;
name|gdouble
name|yresolution
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xresolution
argument_list|,
operator|&
name|yresolution
argument_list|)
expr_stmt|;
if|if
condition|(
name|xresolution
operator|>
name|GIMP_MIN_RESOLUTION
operator|&&
name|yresolution
operator|>
name|GIMP_MIN_RESOLUTION
condition|)
block|{
comment|/*          * xresolution and yresolution are in dots per inch.          * the BMP spec says that biXPels and biYPels are in          * pixels per meter as long ints (actually, "DWORDS"),          * so...          *    n dots    inch     100 cm   m dots          *    ------ * ------- * ------ = ------          *     inch    2.54 cm     m       inch          */
name|Bitmap_Head
operator|.
name|biXPels
operator|=
operator|(
name|long
name|int
operator|)
name|xresolution
operator|*
literal|100.0
operator|/
literal|2.54
expr_stmt|;
name|Bitmap_Head
operator|.
name|biYPels
operator|=
operator|(
name|long
name|int
operator|)
name|yresolution
operator|*
literal|100.0
operator|/
literal|2.54
expr_stmt|;
block|}
block|}
if|if
condition|(
name|BitsPerPixel
operator|<
literal|24
condition|)
name|Bitmap_Head
operator|.
name|biClrUsed
operator|=
name|colors
expr_stmt|;
else|else
name|Bitmap_Head
operator|.
name|biClrUsed
operator|=
literal|0
expr_stmt|;
name|Bitmap_Head
operator|.
name|biClrImp
operator|=
name|Bitmap_Head
operator|.
name|biClrUsed
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"\nSize: %u, Colors: %u, Bits: %u, Width: %u, Height: %u, Comp: %u, Zeile: %u\n"
argument_list|,
operator|(
name|int
operator|)
name|Bitmap_File_Head
operator|.
name|bfSize
argument_list|,
operator|(
name|int
operator|)
name|Bitmap_Head
operator|.
name|biClrUsed
argument_list|,
name|Bitmap_Head
operator|.
name|biBitCnt
argument_list|,
operator|(
name|int
operator|)
name|Bitmap_Head
operator|.
name|biWidth
argument_list|,
operator|(
name|int
operator|)
name|Bitmap_Head
operator|.
name|biHeight
argument_list|,
operator|(
name|int
operator|)
name|Bitmap_Head
operator|.
name|biCompr
argument_list|,
name|SpZeile
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* And now write the header and the colormap (if any) to disk */
name|Write
argument_list|(
name|outfile
argument_list|,
literal|"BM"
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_File_Head
operator|.
name|bfSize
argument_list|,
operator|&
name|puffer
index|[
literal|0x00
index|]
argument_list|)
expr_stmt|;
name|FromS
argument_list|(
name|Bitmap_File_Head
operator|.
name|zzHotX
argument_list|,
operator|&
name|puffer
index|[
literal|0x04
index|]
argument_list|)
expr_stmt|;
name|FromS
argument_list|(
name|Bitmap_File_Head
operator|.
name|zzHotY
argument_list|,
operator|&
name|puffer
index|[
literal|0x06
index|]
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_File_Head
operator|.
name|bfOffs
argument_list|,
operator|&
name|puffer
index|[
literal|0x08
index|]
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_File_Head
operator|.
name|biSize
argument_list|,
operator|&
name|puffer
index|[
literal|0x0C
index|]
argument_list|)
expr_stmt|;
name|Write
argument_list|(
name|outfile
argument_list|,
name|puffer
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_Head
operator|.
name|biWidth
argument_list|,
operator|&
name|puffer
index|[
literal|0x00
index|]
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_Head
operator|.
name|biHeight
argument_list|,
operator|&
name|puffer
index|[
literal|0x04
index|]
argument_list|)
expr_stmt|;
name|FromS
argument_list|(
name|Bitmap_Head
operator|.
name|biPlanes
argument_list|,
operator|&
name|puffer
index|[
literal|0x08
index|]
argument_list|)
expr_stmt|;
name|FromS
argument_list|(
name|Bitmap_Head
operator|.
name|biBitCnt
argument_list|,
operator|&
name|puffer
index|[
literal|0x0A
index|]
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_Head
operator|.
name|biCompr
argument_list|,
operator|&
name|puffer
index|[
literal|0x0C
index|]
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_Head
operator|.
name|biSizeIm
argument_list|,
operator|&
name|puffer
index|[
literal|0x10
index|]
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_Head
operator|.
name|biXPels
argument_list|,
operator|&
name|puffer
index|[
literal|0x14
index|]
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_Head
operator|.
name|biYPels
argument_list|,
operator|&
name|puffer
index|[
literal|0x18
index|]
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_Head
operator|.
name|biClrUsed
argument_list|,
operator|&
name|puffer
index|[
literal|0x1C
index|]
argument_list|)
expr_stmt|;
name|FromL
argument_list|(
name|Bitmap_Head
operator|.
name|biClrImp
argument_list|,
operator|&
name|puffer
index|[
literal|0x20
index|]
argument_list|)
expr_stmt|;
name|Write
argument_list|(
name|outfile
argument_list|,
name|puffer
argument_list|,
literal|36
argument_list|)
expr_stmt|;
name|WriteColorMap
argument_list|(
name|outfile
argument_list|,
name|Red
argument_list|,
name|Green
argument_list|,
name|Blue
argument_list|,
name|MapSize
argument_list|)
expr_stmt|;
comment|/* After that is done, we write the image ... */
name|WriteImage
argument_list|(
name|outfile
argument_list|,
name|pixels
argument_list|,
name|cols
argument_list|,
name|rows
argument_list|,
name|encoded
argument_list|,
name|channels
argument_list|,
name|BitsPerPixel
argument_list|,
name|SpZeile
argument_list|,
name|MapSize
argument_list|)
expr_stmt|;
comment|/* ... and exit normally */
name|fclose
argument_list|(
name|outfile
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|WriteImage (FILE * f,guchar * src,gint width,gint height,gint encoded,gint channels,gint bpp,gint spzeile,gint MapSize)
name|WriteImage
parameter_list|(
name|FILE
modifier|*
name|f
parameter_list|,
name|guchar
modifier|*
name|src
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|encoded
parameter_list|,
name|gint
name|channels
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|spzeile
parameter_list|,
name|gint
name|MapSize
parameter_list|)
block|{
name|guchar
name|buf
index|[
literal|16
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|guchar
name|puffer
index|[
literal|8
index|]
decl_stmt|;
name|guchar
modifier|*
name|temp
decl_stmt|,
name|v
decl_stmt|;
name|guchar
modifier|*
name|Zeile
decl_stmt|,
modifier|*
name|ketten
decl_stmt|;
name|gint
name|xpos
decl_stmt|,
name|ypos
decl_stmt|,
name|i
decl_stmt|,
name|j
decl_stmt|,
name|rowstride
decl_stmt|,
name|laenge
decl_stmt|,
name|thiswidth
decl_stmt|;
name|gint
name|breite
decl_stmt|,
name|k
decl_stmt|;
name|guchar
name|n
decl_stmt|;
name|xpos
operator|=
literal|0
expr_stmt|;
name|rowstride
operator|=
name|width
operator|*
name|channels
expr_stmt|;
comment|/* We'll begin with the 24 bit Bitmaps, they are easy :-) */
if|if
condition|(
name|bpp
operator|==
literal|24
condition|)
block|{
for|for
control|(
name|ypos
operator|=
name|height
operator|-
literal|1
init|;
name|ypos
operator|>=
literal|0
condition|;
name|ypos
operator|--
control|)
comment|/* for each row   */
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
condition|;
name|i
operator|++
control|)
comment|/* for each pixel */
block|{
name|temp
operator|=
name|src
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
name|buf
index|[
literal|2
index|]
operator|=
operator|(
name|guchar
operator|)
operator|*
name|temp
expr_stmt|;
name|temp
operator|++
expr_stmt|;
name|buf
index|[
literal|1
index|]
operator|=
operator|(
name|guchar
operator|)
operator|*
name|temp
expr_stmt|;
name|temp
operator|++
expr_stmt|;
name|buf
index|[
literal|0
index|]
operator|=
operator|(
name|guchar
operator|)
operator|*
name|temp
expr_stmt|;
name|xpos
operator|++
expr_stmt|;
name|Write
argument_list|(
name|f
argument_list|,
name|buf
argument_list|,
literal|3
argument_list|)
expr_stmt|;
block|}
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|buf
index|[
literal|3
index|]
argument_list|,
name|spzeile
operator|-
operator|(
name|width
operator|*
literal|3
operator|)
argument_list|)
expr_stmt|;
name|cur_progress
operator|++
expr_stmt|;
if|if
condition|(
operator|(
name|cur_progress
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|cur_progress
operator|/
operator|(
name|gdouble
operator|)
name|max_progress
argument_list|)
expr_stmt|;
name|xpos
operator|=
literal|0
expr_stmt|;
block|}
block|}
else|else
block|{
switch|switch
condition|(
name|encoded
condition|)
comment|/* now it gets more difficult */
block|{
comment|/* uncompressed 1,4 and 8 bit */
case|case
literal|0
case|:
block|{
name|thiswidth
operator|=
operator|(
name|width
operator|/
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|width
operator|%
operator|(
literal|8
operator|/
name|bpp
operator|)
condition|)
name|thiswidth
operator|++
expr_stmt|;
for|for
control|(
name|ypos
operator|=
name|height
operator|-
literal|1
init|;
name|ypos
operator|>=
literal|0
condition|;
name|ypos
operator|--
control|)
comment|/* for each row */
block|{
for|for
control|(
name|xpos
operator|=
literal|0
init|;
name|xpos
operator|<
name|width
condition|;
control|)
comment|/* for each _byte_ */
block|{
name|v
operator|=
literal|0
expr_stmt|;
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
name|width
operator|)
condition|;
name|i
operator|++
operator|,
name|xpos
operator|++
control|)
comment|/* for each pixel */
block|{
name|temp
operator|=
name|src
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
name|v
operator|=
name|v
operator||
operator|(
operator|(
name|guchar
operator|)
operator|*
name|temp
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
expr_stmt|;
block|}
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|v
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|buf
index|[
literal|3
index|]
argument_list|,
name|spzeile
operator|-
name|thiswidth
argument_list|)
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
name|cur_progress
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|cur_progress
operator|/
operator|(
name|gdouble
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
default|default:
block|{
comment|/* Save RLE encoded file, quite difficult */
name|laenge
operator|=
literal|0
expr_stmt|;
name|buf
index|[
literal|12
index|]
operator|=
literal|0
expr_stmt|;
name|buf
index|[
literal|13
index|]
operator|=
literal|1
expr_stmt|;
name|buf
index|[
literal|14
index|]
operator|=
literal|0
expr_stmt|;
name|buf
index|[
literal|15
index|]
operator|=
literal|0
expr_stmt|;
name|Zeile
operator|=
operator|(
name|guchar
operator|*
operator|)
name|g_malloc
argument_list|(
name|width
operator|/
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|+
literal|10
argument_list|)
expr_stmt|;
name|ketten
operator|=
operator|(
name|guchar
operator|*
operator|)
name|g_malloc
argument_list|(
name|width
operator|/
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|+
literal|10
argument_list|)
expr_stmt|;
for|for
control|(
name|ypos
operator|=
name|height
operator|-
literal|1
init|;
name|ypos
operator|>=
literal|0
condition|;
name|ypos
operator|--
control|)
block|{
comment|/* each row separately */
name|j
operator|=
literal|0
expr_stmt|;
comment|/* first copy the pixels to a buffer,                  * making one byte from two 4bit pixels                  */
for|for
control|(
name|xpos
operator|=
literal|0
init|;
name|xpos
operator|<
name|width
condition|;
control|)
block|{
name|v
operator|=
literal|0
expr_stmt|;
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
name|width
operator|)
condition|;
name|i
operator|++
operator|,
name|xpos
operator|++
control|)
block|{
comment|/* for each pixel */
name|temp
operator|=
name|src
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
name|v
operator|=
name|v
operator||
operator|(
operator|(
name|guchar
operator|)
operator|*
name|temp
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
expr_stmt|;
block|}
name|Zeile
index|[
name|j
operator|++
index|]
operator|=
name|v
expr_stmt|;
block|}
name|breite
operator|=
name|width
operator|/
operator|(
literal|8
operator|/
name|bpp
operator|)
expr_stmt|;
if|if
condition|(
name|width
operator|%
operator|(
literal|8
operator|/
name|bpp
operator|)
condition|)
name|breite
operator|++
expr_stmt|;
comment|/* then check for strings of equal bytes */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|breite
condition|;
control|)
block|{
name|j
operator|=
literal|0
expr_stmt|;
while|while
condition|(
operator|(
name|i
operator|+
name|j
operator|<
name|breite
operator|)
operator|&&
operator|(
name|j
operator|<
operator|(
literal|255
operator|/
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|)
operator|)
operator|&&
operator|(
name|Zeile
index|[
name|i
operator|+
name|j
index|]
operator|==
name|Zeile
index|[
name|i
index|]
operator|)
condition|)
name|j
operator|++
expr_stmt|;
name|ketten
index|[
name|i
index|]
operator|=
name|j
expr_stmt|;
name|i
operator|+=
name|j
expr_stmt|;
block|}
comment|/* then write the strings and the other pixels to the file */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|breite
condition|;
control|)
block|{
if|if
condition|(
name|ketten
index|[
name|i
index|]
operator|<
literal|3
condition|)
comment|/* strings of different pixels ... */
block|{
name|j
operator|=
literal|0
expr_stmt|;
while|while
condition|(
operator|(
name|i
operator|+
name|j
operator|<
name|breite
operator|)
operator|&&
operator|(
name|j
operator|<
operator|(
literal|255
operator|/
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|)
operator|)
operator|&&
operator|(
name|ketten
index|[
name|i
operator|+
name|j
index|]
operator|<
literal|3
operator|)
condition|)
name|j
operator|+=
name|ketten
index|[
name|i
operator|+
name|j
index|]
expr_stmt|;
comment|/* this can only happen if j jumps over                          * the end with a 2 in ketten[i+j]                          */
if|if
condition|(
name|j
operator|>
operator|(
literal|255
operator|/
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|)
condition|)
name|j
operator|-=
literal|2
expr_stmt|;
comment|/* 00 01 and 00 02 are reserved */
if|if
condition|(
name|j
operator|>
literal|2
condition|)
block|{
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|buf
index|[
literal|12
index|]
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|n
operator|=
name|j
operator|*
operator|(
literal|8
operator|/
name|bpp
operator|)
expr_stmt|;
if|if
condition|(
name|n
operator|+
name|i
operator|*
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|>
name|width
condition|)
name|n
operator|--
expr_stmt|;
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|n
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|laenge
operator|+=
literal|2
expr_stmt|;
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|Zeile
index|[
name|i
index|]
argument_list|,
name|j
argument_list|)
expr_stmt|;
name|laenge
operator|+=
name|j
expr_stmt|;
if|if
condition|(
operator|(
name|j
operator|)
operator|%
literal|2
condition|)
block|{
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|buf
index|[
literal|12
index|]
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|laenge
operator|++
expr_stmt|;
block|}
block|}
else|else
block|{
for|for
control|(
name|k
operator|=
name|i
init|;
name|k
operator|<
name|i
operator|+
name|j
condition|;
name|k
operator|++
control|)
block|{
name|n
operator|=
operator|(
literal|8
operator|/
name|bpp
operator|)
expr_stmt|;
if|if
condition|(
name|n
operator|+
name|i
operator|*
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|>
name|width
condition|)
name|n
operator|--
expr_stmt|;
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|n
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|Zeile
index|[
name|k
index|]
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/*printf("%i.#|",n); */
name|laenge
operator|+=
literal|2
expr_stmt|;
block|}
block|}
name|i
operator|+=
name|j
expr_stmt|;
block|}
else|else
comment|/* strings of equal pixels */
block|{
name|n
operator|=
name|ketten
index|[
name|i
index|]
operator|*
operator|(
literal|8
operator|/
name|bpp
operator|)
expr_stmt|;
if|if
condition|(
name|n
operator|+
name|i
operator|*
operator|(
literal|8
operator|/
name|bpp
operator|)
operator|>
name|width
condition|)
name|n
operator|--
expr_stmt|;
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|n
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|Zeile
index|[
name|i
index|]
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|i
operator|+=
name|ketten
index|[
name|i
index|]
expr_stmt|;
name|laenge
operator|+=
literal|2
expr_stmt|;
block|}
block|}
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|buf
index|[
literal|14
index|]
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/* End of row */
name|laenge
operator|+=
literal|2
expr_stmt|;
name|cur_progress
operator|++
expr_stmt|;
if|if
condition|(
operator|(
name|cur_progress
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|cur_progress
operator|/
operator|(
name|gdouble
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
name|fseek
argument_list|(
name|f
argument_list|,
operator|-
literal|2
argument_list|,
name|SEEK_CUR
argument_list|)
expr_stmt|;
comment|/* Overwrite last End of row ... */
name|Write
argument_list|(
name|f
argument_list|,
operator|&
name|buf
index|[
literal|12
index|]
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/* ... with End of file */
name|fseek
argument_list|(
name|f
argument_list|,
literal|0x22
argument_list|,
name|SEEK_SET
argument_list|)
expr_stmt|;
comment|/* Write length of image */
name|FromL
argument_list|(
name|laenge
argument_list|,
name|puffer
argument_list|)
expr_stmt|;
name|Write
argument_list|(
name|f
argument_list|,
name|puffer
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|fseek
argument_list|(
name|f
argument_list|,
literal|0x02
argument_list|,
name|SEEK_SET
argument_list|)
expr_stmt|;
comment|/* Write length of file */
name|laenge
operator|+=
operator|(
literal|0x36
operator|+
name|MapSize
operator|)
expr_stmt|;
name|FromL
argument_list|(
name|laenge
argument_list|,
name|puffer
argument_list|)
expr_stmt|;
name|Write
argument_list|(
name|f
argument_list|,
name|puffer
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ketten
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|Zeile
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
name|gimp_progress_update
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|save_dialog (void)
name|save_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Save as BMP"
argument_list|)
argument_list|,
literal|"bmp"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"file-bmp-save"
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_RLE encoded"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|encoded
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|encoded
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dlg
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

