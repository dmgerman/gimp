begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * EXIF-handling code for the jpeg plugin.  May eventually be better  * to move this stuff into libgimpbase and make it available for  * other plugins.  */
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|jpeg_query
parameter_list|(
specifier|const
name|gchar
modifier|*
name|primary
parameter_list|,
specifier|const
name|gchar
modifier|*
name|secondary
parameter_list|,
specifier|const
name|gchar
modifier|*
name|cancel_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ok_label
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|jpeg_apply_exif_data_to_image (const gchar * filename,const gint32 image_ID)
name|jpeg_apply_exif_data_to_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gint32
name|image_ID
parameter_list|)
block|{
name|ExifData
modifier|*
name|exif_data
init|=
name|NULL
decl_stmt|;
name|ExifEntry
modifier|*
name|entry
decl_stmt|;
name|gint
name|byte_order
decl_stmt|;
name|exif_data
operator|=
name|exif_data_new_from_file
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|exif_data
condition|)
return|return;
comment|/*    * Unfortunately libexif may return a non-null exif_data even if the file    * contains no exif data.  We check for validity by making sure it    * has an ExifVersion tag.   */
if|if
condition|(
operator|!
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|EXIF_IFD_EXIF
index|]
argument_list|,
name|EXIF_TAG_EXIF_VERSION
argument_list|)
condition|)
return|return;
name|gimp_metadata_store_exif
argument_list|(
name|image_ID
argument_list|,
name|exif_data
argument_list|)
expr_stmt|;
name|byte_order
operator|=
name|exif_data_get_byte_order
argument_list|(
name|exif_data
argument_list|)
expr_stmt|;
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
name|gint
name|orient
init|=
name|exif_get_short
argument_list|(
name|entry
operator|->
name|data
argument_list|,
name|byte_order
argument_list|)
decl_stmt|;
if|if
condition|(
name|load_interactive
operator|&&
name|orient
operator|>
literal|1
operator|&&
name|orient
operator|<=
literal|8
operator|&&
name|jpeg_query
argument_list|(
name|_
argument_list|(
literal|"According to the EXIF data, this image is rotated."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Would you like GIMP to rotate it into the standard "
literal|"orientation?"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Keep Orientation"
argument_list|)
argument_list|,
name|GIMP_STOCK_TOOL_ROTATE
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|orient
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
break|break;
default|default:
comment|/* can't happen                     */
break|break;
block|}
block|}
block|}
name|exif_data_unref
argument_list|(
name|exif_data
argument_list|)
expr_stmt|;
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
comment|/* set software to "The GIMP" */
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
literal|"The GIMP"
argument_list|)
expr_stmt|;
name|entry
operator|->
name|size
operator|=
name|strlen
argument_list|(
literal|"The GIMP"
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
name|EXIF_IFD_0
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
name|EXIF_IFD_0
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
comment|/*    *remove entries that don't apply to jpeg    *(may have come from tiff or raw)   */
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
specifier|static
name|gboolean
DECL|function|jpeg_query (const gchar * primary,const gchar * secondary,const gchar * cancel_label,const gchar * ok_label)
name|jpeg_query
parameter_list|(
specifier|const
name|gchar
modifier|*
name|primary
parameter_list|,
specifier|const
name|gchar
modifier|*
name|secondary
parameter_list|,
specifier|const
name|gchar
modifier|*
name|cancel_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ok_label
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gint
name|response
decl_stmt|;
comment|/*  FIXME: jpeg_query() needs to know about it's parent window  */
name|dialog
operator|=
name|gtk_message_dialog_new
argument_list|(
name|NULL
argument_list|,
literal|0
argument_list|,
name|GTK_MESSAGE_QUESTION
argument_list|,
name|GTK_BUTTONS_NONE
argument_list|,
literal|"%s"
argument_list|,
name|primary
argument_list|)
expr_stmt|;
name|gtk_message_dialog_format_secondary_text
argument_list|(
name|GTK_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"%s"
argument_list|,
name|secondary
argument_list|)
expr_stmt|;
name|gtk_dialog_add_buttons
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|cancel_label
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|ok_label
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
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
name|response
operator|=
name|gtk_dialog_run
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
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

