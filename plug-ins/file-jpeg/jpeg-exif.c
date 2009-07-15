begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * EXIF-handling code for the jpeg plugin.  May eventually be better  * to move this stuff into libgimpbase or a new libgimpmetadata and  * make it available for other plugins.  */
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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<setjmp.h>
end_include

begin_include
include|#
directive|include
file|<jpeglib.h>
end_include

begin_include
include|#
directive|include
file|<jerror.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXIF
end_ifdef

begin_include
include|#
directive|include
file|<libexif/exif-content.h>
end_include

begin_include
include|#
directive|include
file|<libexif/exif-data.h>
end_include

begin_include
include|#
directive|include
file|<libexif/exif-utils.h>
end_include

begin_define
DECL|macro|EXIF_HEADER_SIZE
define|#
directive|define
name|EXIF_HEADER_SIZE
value|8
end_define

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
file|"gimpexif.h"
end_include

begin_include
include|#
directive|include
file|"jpeg.h"
end_include

begin_include
include|#
directive|include
file|"jpeg-settings.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|THUMBNAIL_SIZE
define|#
directive|define
name|THUMBNAIL_SIZE
value|128
end_define

begin_define
DECL|macro|JPEG_EXIF_ROTATE_PARASITE
define|#
directive|define
name|JPEG_EXIF_ROTATE_PARASITE
value|"exif-orientation-rotate"
end_define

begin_function_decl
specifier|static
name|gboolean
name|jpeg_exif_rotate_query_dialog
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Replacement for exif_data_new_from_file() to work around  *  filename encoding problems (see bug #335391).  */
end_comment

begin_function
name|ExifData
modifier|*
DECL|function|jpeg_exif_data_new_from_file (const gchar * filename,GError ** error)
name|jpeg_exif_data_new_from_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|ExifData
modifier|*
name|data
decl_stmt|;
name|GMappedFile
modifier|*
name|file
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_mapped_file_new
argument_list|(
name|filename
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
return|return
name|NULL
return|;
name|data
operator|=
name|exif_data_new_from_data
argument_list|(
operator|(
name|guchar
operator|*
operator|)
name|g_mapped_file_get_contents
argument_list|(
name|file
argument_list|)
argument_list|,
name|g_mapped_file_get_length
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|g_mapped_file_free
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

begin_function
name|gint
DECL|function|jpeg_exif_get_orientation (ExifData * exif_data)
name|jpeg_exif_get_orientation
parameter_list|(
name|ExifData
modifier|*
name|exif_data
parameter_list|)
block|{
name|ExifEntry
modifier|*
name|entry
decl_stmt|;
name|gint
name|byte_order
init|=
name|exif_data_get_byte_order
argument_list|(
name|exif_data
argument_list|)
decl_stmt|;
comment|/* get orientation and rotate image accordingly if necessary */
if|if
condition|(
operator|(
name|entry
operator|=
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|EXIF_IFD_0
index|]
argument_list|,
name|EXIF_TAG_ORIENTATION
argument_list|)
operator|)
condition|)
block|{
return|return
name|exif_get_short
argument_list|(
name|entry
operator|->
name|data
argument_list|,
name|byte_order
argument_list|)
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_function
name|void
DECL|function|jpeg_setup_exif_for_save (ExifData * exif_data,const gint32 image_ID)
name|jpeg_setup_exif_for_save
parameter_list|(
name|ExifData
modifier|*
name|exif_data
parameter_list|,
specifier|const
name|gint32
name|image_ID
parameter_list|)
block|{
name|ExifRational
name|r
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|ExifEntry
modifier|*
name|entry
decl_stmt|;
name|gint
name|byte_order
init|=
name|exif_data_get_byte_order
argument_list|(
name|exif_data
argument_list|)
decl_stmt|;
comment|/* set orientation to top - left */
if|if
condition|(
operator|(
name|entry
operator|=
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|EXIF_IFD_0
index|]
argument_list|,
name|EXIF_TAG_ORIENTATION
argument_list|)
operator|)
condition|)
block|{
name|exif_set_short
argument_list|(
name|entry
operator|->
name|data
argument_list|,
name|byte_order
argument_list|,
operator|(
name|ExifShort
operator|)
literal|1
argument_list|)
expr_stmt|;
block|}
comment|/* set x and y resolution */
name|gimp_image_get_resolution
argument_list|(
name|image_ID
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|r
operator|.
name|numerator
operator|=
name|xres
expr_stmt|;
name|r
operator|.
name|denominator
operator|=
literal|1
expr_stmt|;
if|if
condition|(
operator|(
name|entry
operator|=
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|EXIF_IFD_0
index|]
argument_list|,
name|EXIF_TAG_X_RESOLUTION
argument_list|)
operator|)
condition|)
block|{
name|exif_set_rational
argument_list|(
name|entry
operator|->
name|data
argument_list|,
name|byte_order
argument_list|,
name|r
argument_list|)
expr_stmt|;
block|}
name|r
operator|.
name|numerator
operator|=
name|yres
expr_stmt|;
if|if
condition|(
operator|(
name|entry
operator|=
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|EXIF_IFD_0
index|]
argument_list|,
name|EXIF_TAG_Y_RESOLUTION
argument_list|)
operator|)
condition|)
block|{
name|exif_set_rational
argument_list|(
name|entry
operator|->
name|data
argument_list|,
name|byte_order
argument_list|,
name|r
argument_list|)
expr_stmt|;
block|}
comment|/* set resolution unit, always inches */
if|if
condition|(
operator|(
name|entry
operator|=
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|EXIF_IFD_0
index|]
argument_list|,
name|EXIF_TAG_RESOLUTION_UNIT
argument_list|)
operator|)
condition|)
block|{
name|exif_set_short
argument_list|(
name|entry
operator|->
name|data
argument_list|,
name|byte_order
argument_list|,
operator|(
name|ExifShort
operator|)
literal|2
argument_list|)
expr_stmt|;
block|}
comment|/* set software to "GIMP" and include the version number */
if|if
condition|(
operator|(
name|entry
operator|=
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|EXIF_IFD_0
index|]
argument_list|,
name|EXIF_TAG_SOFTWARE
argument_list|)
operator|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
literal|"GIMP "
name|GIMP_VERSION
decl_stmt|;
name|entry
operator|->
name|data
operator|=
operator|(
name|guchar
operator|*
operator|)
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|entry
operator|->
name|size
operator|=
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|1
expr_stmt|;
name|entry
operator|->
name|components
operator|=
name|entry
operator|->
name|size
expr_stmt|;
block|}
comment|/* set the width and height */
if|if
condition|(
operator|(
name|entry
operator|=
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|EXIF_IFD_EXIF
index|]
argument_list|,
name|EXIF_TAG_PIXEL_X_DIMENSION
argument_list|)
operator|)
condition|)
block|{
name|exif_set_long
argument_list|(
name|entry
operator|->
name|data
argument_list|,
name|byte_order
argument_list|,
operator|(
name|ExifLong
operator|)
name|gimp_image_width
argument_list|(
name|image_ID
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|entry
operator|=
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|EXIF_IFD_EXIF
index|]
argument_list|,
name|EXIF_TAG_PIXEL_Y_DIMENSION
argument_list|)
operator|)
condition|)
block|{
name|exif_set_long
argument_list|(
name|entry
operator|->
name|data
argument_list|,
name|byte_order
argument_list|,
operator|(
name|ExifLong
operator|)
name|gimp_image_height
argument_list|(
name|image_ID
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*    * set the date& time image was saved    * note, date& time of original photo is stored elsewwhere, we    * aren't losing it.    */
if|if
condition|(
operator|(
name|entry
operator|=
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|EXIF_IFD_0
index|]
argument_list|,
name|EXIF_TAG_DATE_TIME
argument_list|)
operator|)
condition|)
block|{
comment|/* small memory leak here */
name|entry
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|exif_entry_initialize
argument_list|(
name|entry
argument_list|,
name|EXIF_TAG_DATE_TIME
argument_list|)
expr_stmt|;
block|}
comment|/* should set components configuration, don't know how */
comment|/*    * remove entries that don't apply to jpeg    * (may have come from tiff or raw)    */
name|gimp_exif_data_remove_entry
argument_list|(
name|exif_data
argument_list|,
name|EXIF_IFD_0
argument_list|,
name|EXIF_TAG_COMPRESSION
argument_list|)
expr_stmt|;
name|gimp_exif_data_remove_entry
argument_list|(
name|exif_data
argument_list|,
name|EXIF_IFD_0
argument_list|,
name|EXIF_TAG_IMAGE_WIDTH
argument_list|)
expr_stmt|;
name|gimp_exif_data_remove_entry
argument_list|(
name|exif_data
argument_list|,
name|EXIF_IFD_0
argument_list|,
name|EXIF_TAG_IMAGE_LENGTH
argument_list|)
expr_stmt|;
name|gimp_exif_data_remove_entry
argument_list|(
name|exif_data
argument_list|,
name|EXIF_IFD_0
argument_list|,
name|EXIF_TAG_BITS_PER_SAMPLE
argument_list|)
expr_stmt|;
name|gimp_exif_data_remove_entry
argument_list|(
name|exif_data
argument_list|,
name|EXIF_IFD_0
argument_list|,
name|EXIF_TAG_SAMPLES_PER_PIXEL
argument_list|)
expr_stmt|;
name|gimp_exif_data_remove_entry
argument_list|(
name|exif_data
argument_list|,
name|EXIF_IFD_0
argument_list|,
name|EXIF_TAG_PHOTOMETRIC_INTERPRETATION
argument_list|)
expr_stmt|;
name|gimp_exif_data_remove_entry
argument_list|(
name|exif_data
argument_list|,
name|EXIF_IFD_0
argument_list|,
name|EXIF_TAG_STRIP_OFFSETS
argument_list|)
expr_stmt|;
name|gimp_exif_data_remove_entry
argument_list|(
name|exif_data
argument_list|,
name|EXIF_IFD_0
argument_list|,
name|EXIF_TAG_PLANAR_CONFIGURATION
argument_list|)
expr_stmt|;
name|gimp_exif_data_remove_entry
argument_list|(
name|exif_data
argument_list|,
name|EXIF_IFD_0
argument_list|,
name|EXIF_TAG_YCBCR_SUB_SAMPLING
argument_list|)
expr_stmt|;
comment|/* should set thumbnail attributes */
block|}
end_function

begin_function
name|void
DECL|function|jpeg_exif_rotate (gint32 image_ID,gint orientation)
name|jpeg_exif_rotate
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|orientation
parameter_list|)
block|{
switch|switch
condition|(
name|orientation
condition|)
block|{
case|case
literal|1
case|:
comment|/* standard orientation, do nothing */
break|break;
case|case
literal|2
case|:
comment|/* flipped right-left               */
name|gimp_image_flip
argument_list|(
name|image_ID
argument_list|,
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
comment|/* rotated 180                      */
name|gimp_image_rotate
argument_list|(
name|image_ID
argument_list|,
name|GIMP_ROTATE_180
argument_list|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
comment|/* flipped top-bottom               */
name|gimp_image_flip
argument_list|(
name|image_ID
argument_list|,
name|GIMP_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
break|break;
case|case
literal|5
case|:
comment|/* flipped diagonally around '\'    */
name|gimp_image_rotate
argument_list|(
name|image_ID
argument_list|,
name|GIMP_ROTATE_90
argument_list|)
expr_stmt|;
name|jpeg_swap_original_settings
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|gimp_image_flip
argument_list|(
name|image_ID
argument_list|,
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
break|break;
case|case
literal|6
case|:
comment|/* 90 CW                            */
name|gimp_image_rotate
argument_list|(
name|image_ID
argument_list|,
name|GIMP_ROTATE_90
argument_list|)
expr_stmt|;
name|jpeg_swap_original_settings
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
break|break;
case|case
literal|7
case|:
comment|/* flipped diagonally around '/'    */
name|gimp_image_rotate
argument_list|(
name|image_ID
argument_list|,
name|GIMP_ROTATE_90
argument_list|)
expr_stmt|;
name|jpeg_swap_original_settings
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|gimp_image_flip
argument_list|(
name|image_ID
argument_list|,
name|GIMP_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
break|break;
case|case
literal|8
case|:
comment|/* 90 CCW                           */
name|gimp_image_rotate
argument_list|(
name|image_ID
argument_list|,
name|GIMP_ROTATE_270
argument_list|)
expr_stmt|;
name|jpeg_swap_original_settings
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
break|break;
default|default:
comment|/* shouldn't happen                 */
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|jpeg_exif_rotate_query (gint32 image_ID,gint orientation)
name|jpeg_exif_rotate_query
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|orientation
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gboolean
name|query
init|=
name|load_interactive
decl_stmt|;
if|if
condition|(
name|orientation
operator|<
literal|2
operator|||
name|orientation
operator|>
literal|8
condition|)
return|return;
name|parasite
operator|=
name|gimp_parasite_find
argument_list|(
name|JPEG_EXIF_ROTATE_PARASITE
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
if|if
condition|(
name|strncmp
argument_list|(
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
literal|"yes"
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
name|query
operator|=
name|FALSE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
literal|"no"
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|query
operator|&&
operator|!
name|jpeg_exif_rotate_query_dialog
argument_list|(
name|image_ID
argument_list|)
condition|)
return|return;
name|jpeg_exif_rotate
argument_list|(
name|image_ID
argument_list|,
name|orientation
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|jpeg_exif_rotate_query_dialog (gint32 image_ID)
name|jpeg_exif_rotate_query_dialog
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|gint
name|response
decl_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Rotate Image?"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"_Keep Orientation"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GIMP_STOCK_TOOL_ROTATE
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_window_set_transient
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
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
name|hbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gimp_image_get_thumbnail
argument_list|(
name|image_ID
argument_list|,
name|THUMBNAIL_SIZE
argument_list|,
name|THUMBNAIL_SIZE
argument_list|,
name|GIMP_PIXBUF_SMALL_CHECKS
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
block|{
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|image
operator|=
name|gtk_image_new_from_pixbuf
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|image
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_image_get_name
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gtk_label_set_ellipsize
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ELLIPSIZE_MIDDLE
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|label
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_LABEL
argument_list|,
literal|"label"
argument_list|,
name|_
argument_list|(
literal|"According to the EXIF data, "
literal|"this image is rotated."
argument_list|)
argument_list|,
literal|"wrap"
argument_list|,
name|TRUE
argument_list|,
literal|"justify"
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|,
literal|"xalign"
argument_list|,
literal|0.0
argument_list|,
literal|"yalign"
argument_list|,
literal|0.5
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_SCALE
argument_list|,
name|PANGO_SCALE_LARGE
argument_list|,
name|PANGO_ATTR_WEIGHT
argument_list|,
name|PANGO_WEIGHT_BOLD
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_LABEL
argument_list|,
literal|"label"
argument_list|,
name|_
argument_list|(
literal|"Would you like GIMP to rotate it "
literal|"into the standard orientation?"
argument_list|)
argument_list|,
literal|"wrap"
argument_list|,
name|TRUE
argument_list|,
literal|"justify"
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|,
literal|"xalign"
argument_list|,
literal|0.0
argument_list|,
literal|"yalign"
argument_list|,
literal|0.5
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Don't ask me again"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
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
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|response
operator|=
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|)
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|str
init|=
operator|(
name|response
operator|==
name|GTK_RESPONSE_OK
operator|)
condition|?
literal|"yes"
else|:
literal|"no"
decl_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
name|JPEG_EXIF_ROTATE_PARASITE
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|str
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|gimp_parasite_attach
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
operator|(
name|response
operator|==
name|GTK_RESPONSE_OK
operator|)
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_EXIF */
end_comment

end_unit

