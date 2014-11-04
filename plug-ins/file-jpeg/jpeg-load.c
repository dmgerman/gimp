begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<setjmp.h>
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<gexiv2/gexiv2.h>
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

begin_include
include|#
directive|include
file|<lcms2.h>
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"jpeg.h"
end_include

begin_include
include|#
directive|include
file|"jpeg-icc.h"
end_include

begin_include
include|#
directive|include
file|"jpeg-settings.h"
end_include

begin_include
include|#
directive|include
file|"jpeg-load.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|jpeg_load_resolution
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|struct
name|jpeg_decompress_struct
modifier|*
name|cinfo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|jpeg_load_sanitize_comment
parameter_list|(
name|gchar
modifier|*
name|comment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|jpeg_load_cmyk_transform
parameter_list|(
name|guint8
modifier|*
name|profile_data
parameter_list|,
name|gsize
name|profile_len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|jpeg_load_cmyk_to_rgb
parameter_list|(
name|guchar
modifier|*
name|buf
parameter_list|,
name|glong
name|pixels
parameter_list|,
name|gpointer
name|transform
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|preview_image_ID
name|gint32
specifier|volatile
name|preview_image_ID
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|preview_layer_ID
name|gint32
name|preview_layer_ID
decl_stmt|;
end_decl_stmt

begin_function
name|gint32
DECL|function|load_image (const gchar * filename,GimpRunMode runmode,gboolean preview,gboolean * resolution_loaded,GError ** error)
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GimpRunMode
name|runmode
parameter_list|,
name|gboolean
name|preview
parameter_list|,
name|gboolean
modifier|*
name|resolution_loaded
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gint32
specifier|volatile
name|image_ID
decl_stmt|;
name|gint32
name|layer_ID
decl_stmt|;
name|struct
name|jpeg_decompress_struct
name|cinfo
decl_stmt|;
name|struct
name|my_error_mgr
name|jerr
decl_stmt|;
name|jpeg_saved_marker_ptr
name|marker
decl_stmt|;
name|FILE
modifier|*
name|infile
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
modifier|*
modifier|*
name|rowbuf
decl_stmt|;
name|GimpImageBaseType
name|image_type
decl_stmt|;
name|GimpImageType
name|layer_type
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
init|=
name|NULL
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|tile_height
decl_stmt|;
name|gint
name|scanlines
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|start
decl_stmt|,
name|end
decl_stmt|;
name|cmsHTRANSFORM
name|cmyk_transform
init|=
name|NULL
decl_stmt|;
comment|/* We set up the normal JPEG error routines. */
name|cinfo
operator|.
name|err
operator|=
name|jpeg_std_error
argument_list|(
operator|&
name|jerr
operator|.
name|pub
argument_list|)
expr_stmt|;
name|jerr
operator|.
name|pub
operator|.
name|error_exit
operator|=
name|my_error_exit
expr_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
block|{
name|jerr
operator|.
name|pub
operator|.
name|output_message
operator|=
name|my_output_message
expr_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Opening '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|infile
operator|=
name|g_fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
operator|)
operator|==
name|NULL
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|g_file_error_from_errno
argument_list|(
name|errno
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
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
operator|-
literal|1
return|;
block|}
name|image_ID
operator|=
operator|-
literal|1
expr_stmt|;
comment|/* Establish the setjmp return context for my_error_exit to use. */
if|if
condition|(
name|setjmp
argument_list|(
name|jerr
operator|.
name|setjmp_buffer
argument_list|)
condition|)
block|{
comment|/* If we get here, the JPEG code has signaled an error.        * We need to clean up the JPEG object, close the input file, and return.        */
name|jpeg_destroy_decompress
argument_list|(
operator|&
name|cinfo
argument_list|)
expr_stmt|;
if|if
condition|(
name|infile
condition|)
name|fclose
argument_list|(
name|infile
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
operator|&&
operator|!
name|preview
condition|)
name|gimp_image_delete
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview
condition|)
name|destroy_preview
argument_list|()
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* Now we can initialize the JPEG decompression object. */
name|jpeg_create_decompress
argument_list|(
operator|&
name|cinfo
argument_list|)
expr_stmt|;
comment|/* Step 2: specify data source (eg, a file) */
name|jpeg_stdio_src
argument_list|(
operator|&
name|cinfo
argument_list|,
name|infile
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
block|{
comment|/* - step 2.1: tell the lib to save the comments */
name|jpeg_save_markers
argument_list|(
operator|&
name|cinfo
argument_list|,
name|JPEG_COM
argument_list|,
literal|0xffff
argument_list|)
expr_stmt|;
comment|/* - step 2.2: tell the lib to save APP1 data (Exif or XMP) */
name|jpeg_save_markers
argument_list|(
operator|&
name|cinfo
argument_list|,
name|JPEG_APP0
operator|+
literal|1
argument_list|,
literal|0xffff
argument_list|)
expr_stmt|;
comment|/* - step 2.3: tell the lib to save APP2 data (ICC profiles) */
name|jpeg_save_markers
argument_list|(
operator|&
name|cinfo
argument_list|,
name|JPEG_APP0
operator|+
literal|2
argument_list|,
literal|0xffff
argument_list|)
expr_stmt|;
block|}
comment|/* Step 3: read file parameters with jpeg_read_header() */
name|jpeg_read_header
argument_list|(
operator|&
name|cinfo
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* We can ignore the return value from jpeg_read_header since    *   (a) suspension is not possible with the stdio data source, and    *   (b) we passed TRUE to reject a tables-only JPEG file as an error.    * See libjpeg.doc for more info.    */
comment|/* Step 4: set parameters for decompression */
comment|/* In this example, we don't need to change any of the defaults set by    * jpeg_read_header(), so we do nothing here.    */
comment|/* Step 5: Start decompressor */
name|jpeg_start_decompress
argument_list|(
operator|&
name|cinfo
argument_list|)
expr_stmt|;
comment|/* We may need to do some setup of our own at this point before reading    * the data.  After jpeg_start_decompress() we have the correct scaled    * output image dimensions available, as well as the output colormap    * if we asked for color quantization.    */
comment|/* temporary buffer */
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|tile_height
operator|*
name|cinfo
operator|.
name|output_width
operator|*
name|cinfo
operator|.
name|output_components
argument_list|)
expr_stmt|;
name|rowbuf
operator|=
name|g_new
argument_list|(
name|guchar
operator|*
argument_list|,
name|tile_height
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|tile_height
condition|;
name|i
operator|++
control|)
name|rowbuf
index|[
name|i
index|]
operator|=
name|buf
operator|+
name|cinfo
operator|.
name|output_width
operator|*
name|cinfo
operator|.
name|output_components
operator|*
name|i
expr_stmt|;
switch|switch
condition|(
name|cinfo
operator|.
name|output_components
condition|)
block|{
case|case
literal|1
case|:
name|image_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|layer_type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
literal|4
case|:
if|if
condition|(
name|cinfo
operator|.
name|out_color_space
operator|==
name|JCS_CMYK
condition|)
block|{
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
block|}
comment|/*fallthrough*/
default|default:
name|g_message
argument_list|(
literal|"Don't know how to load JPEG images "
literal|"with %d color channels, using colorspace %d (%d)."
argument_list|,
name|cinfo
operator|.
name|output_components
argument_list|,
name|cinfo
operator|.
name|out_color_space
argument_list|,
name|cinfo
operator|.
name|jpeg_color_space
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
break|break;
block|}
if|if
condition|(
name|preview
condition|)
block|{
name|image_ID
operator|=
name|preview_image_ID
expr_stmt|;
block|}
else|else
block|{
name|image_ID
operator|=
name|gimp_image_new_with_precision
argument_list|(
name|cinfo
operator|.
name|output_width
argument_list|,
name|cinfo
operator|.
name|output_height
argument_list|,
name|image_type
argument_list|,
name|GIMP_PRECISION_U8_GAMMA
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|preview
condition|)
block|{
name|preview_layer_ID
operator|=
name|gimp_layer_new
argument_list|(
name|preview_image_ID
argument_list|,
name|_
argument_list|(
literal|"JPEG preview"
argument_list|)
argument_list|,
name|cinfo
operator|.
name|output_width
argument_list|,
name|cinfo
operator|.
name|output_height
argument_list|,
name|layer_type
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|layer_ID
operator|=
name|preview_layer_ID
expr_stmt|;
block|}
else|else
block|{
name|layer_ID
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
name|cinfo
operator|.
name|output_width
argument_list|,
name|cinfo
operator|.
name|output_height
argument_list|,
name|layer_type
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|preview
condition|)
block|{
name|GString
modifier|*
name|comment_buffer
init|=
name|NULL
decl_stmt|;
name|guint8
modifier|*
name|profile
init|=
name|NULL
decl_stmt|;
name|guint
name|profile_size
init|=
literal|0
decl_stmt|;
comment|/* Step 5.0: save the original JPEG settings in a parasite */
name|jpeg_detect_original_settings
argument_list|(
operator|&
name|cinfo
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
comment|/* Step 5.1: check for comments, or Exif metadata in APP1 markers */
for|for
control|(
name|marker
operator|=
name|cinfo
operator|.
name|marker_list
init|;
name|marker
condition|;
name|marker
operator|=
name|marker
operator|->
name|next
control|)
block|{
specifier|const
name|gchar
modifier|*
name|data
init|=
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|marker
operator|->
name|data
decl_stmt|;
name|gsize
name|len
init|=
name|marker
operator|->
name|data_length
decl_stmt|;
if|if
condition|(
name|marker
operator|->
name|marker
operator|==
name|JPEG_COM
condition|)
block|{
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
name|g_print
argument_list|(
literal|"jpeg-load: found image comment (%d bytes)\n"
argument_list|,
name|marker
operator|->
name|data_length
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|comment_buffer
condition|)
block|{
name|comment_buffer
operator|=
name|g_string_new_len
argument_list|(
name|data
argument_list|,
name|len
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* concatenate multiple comments, separate them with LF */
name|g_string_append_c
argument_list|(
name|comment_buffer
argument_list|,
literal|'\n'
argument_list|)
expr_stmt|;
name|g_string_append_len
argument_list|(
name|comment_buffer
argument_list|,
name|data
argument_list|,
name|len
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|(
name|marker
operator|->
name|marker
operator|==
name|JPEG_APP0
operator|+
literal|1
operator|)
operator|&&
operator|(
name|len
operator|>
sizeof|sizeof
argument_list|(
name|JPEG_APP_HEADER_EXIF
argument_list|)
operator|+
literal|8
operator|)
operator|&&
operator|!
name|strcmp
argument_list|(
name|JPEG_APP_HEADER_EXIF
argument_list|,
name|data
argument_list|)
condition|)
block|{
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
name|g_print
argument_list|(
literal|"jpeg-load: found Exif block (%d bytes)\n"
argument_list|,
call|(
name|gint
call|)
argument_list|(
name|len
operator|-
sizeof|sizeof
argument_list|(
name|JPEG_APP_HEADER_EXIF
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
if|if
condition|(
name|jpeg_load_resolution
argument_list|(
name|image_ID
argument_list|,
operator|&
name|cinfo
argument_list|)
condition|)
block|{
if|if
condition|(
name|resolution_loaded
condition|)
operator|*
name|resolution_loaded
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* if we found any comments, then make a parasite for them */
if|if
condition|(
name|comment_buffer
operator|&&
name|comment_buffer
operator|->
name|len
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|jpeg_load_sanitize_comment
argument_list|(
name|comment_buffer
operator|->
name|str
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-comment"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|comment_buffer
operator|->
name|str
argument_list|)
operator|+
literal|1
argument_list|,
name|comment_buffer
operator|->
name|str
argument_list|)
expr_stmt|;
name|gimp_image_attach_parasite
argument_list|(
name|image_ID
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|comment_buffer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
comment|/* Step 5.3: check for an embedded ICC profile in APP2 markers */
name|jpeg_icc_read_profile
argument_list|(
operator|&
name|cinfo
argument_list|,
operator|&
name|profile
argument_list|,
operator|&
name|profile_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|cinfo
operator|.
name|out_color_space
operator|==
name|JCS_CMYK
condition|)
block|{
name|cmyk_transform
operator|=
name|jpeg_load_cmyk_transform
argument_list|(
name|profile
argument_list|,
name|profile_size
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|profile
condition|)
comment|/* don't attach the profile if we are transforming */
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"icc-profile"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
operator||
name|GIMP_PARASITE_UNDOABLE
argument_list|,
name|profile_size
argument_list|,
name|profile
argument_list|)
expr_stmt|;
name|gimp_image_attach_parasite
argument_list|(
name|image_ID
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|profile
argument_list|)
expr_stmt|;
comment|/* Do not attach the "jpeg-save-options" parasite to the image        * because this conflicts with the global defaults (bug #75398).        */
block|}
comment|/* Step 6: while (scan lines remain to be read) */
comment|/*           jpeg_read_scanlines(...); */
comment|/* Here we use the library's state variable cinfo.output_scanline as the    * loop counter, so that we don't have to keep track ourselves.    */
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|layer_ID
argument_list|)
expr_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
name|image_type
operator|==
name|GIMP_RGB
condition|?
literal|"R'G'B' u8"
else|:
literal|"Y' u8"
argument_list|)
expr_stmt|;
while|while
condition|(
name|cinfo
operator|.
name|output_scanline
operator|<
name|cinfo
operator|.
name|output_height
condition|)
block|{
name|start
operator|=
name|cinfo
operator|.
name|output_scanline
expr_stmt|;
name|end
operator|=
name|cinfo
operator|.
name|output_scanline
operator|+
name|tile_height
expr_stmt|;
name|end
operator|=
name|MIN
argument_list|(
name|end
argument_list|,
name|cinfo
operator|.
name|output_height
argument_list|)
expr_stmt|;
name|scanlines
operator|=
name|end
operator|-
name|start
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|scanlines
condition|;
name|i
operator|++
control|)
name|jpeg_read_scanlines
argument_list|(
operator|&
name|cinfo
argument_list|,
operator|(
name|JSAMPARRAY
operator|)
operator|&
name|rowbuf
index|[
name|i
index|]
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|cinfo
operator|.
name|out_color_space
operator|==
name|JCS_CMYK
condition|)
name|jpeg_load_cmyk_to_rgb
argument_list|(
name|buf
argument_list|,
name|cinfo
operator|.
name|output_width
operator|*
name|scanlines
argument_list|,
name|cmyk_transform
argument_list|)
expr_stmt|;
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|start
argument_list|,
name|cinfo
operator|.
name|output_width
argument_list|,
name|scanlines
argument_list|)
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|buf
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
operator|&&
operator|(
name|cinfo
operator|.
name|output_scanline
operator|%
literal|32
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|cinfo
operator|.
name|output_scanline
operator|/
operator|(
name|gdouble
operator|)
name|cinfo
operator|.
name|output_height
argument_list|)
expr_stmt|;
block|}
comment|/* Step 7: Finish decompression */
name|jpeg_finish_decompress
argument_list|(
operator|&
name|cinfo
argument_list|)
expr_stmt|;
comment|/* We can ignore the return value since suspension is not possible    * with the stdio data source.    */
if|if
condition|(
name|cmyk_transform
condition|)
name|cmsDeleteTransform
argument_list|(
name|cmyk_transform
argument_list|)
expr_stmt|;
comment|/* Step 8: Release JPEG decompression object */
comment|/* This is an important step since it will release a good deal of memory. */
name|jpeg_destroy_decompress
argument_list|(
operator|&
name|cinfo
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
comment|/* free up the temporary buffers */
name|g_free
argument_list|(
name|rowbuf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
comment|/* After finish_decompress, we can close the input file.    * Here we postpone it until after no more JPEG errors are possible,    * so as to simplify the setjmp error logic above.  (Actually, I don't    * think that jpeg_destroy can do an error exit, but why assume anything...)    */
name|fclose
argument_list|(
name|infile
argument_list|)
expr_stmt|;
comment|/* At this point you may want to check to see whether any corrupt-data    * warnings occurred (test whether jerr.num_warnings is nonzero).    */
comment|/* Detach from the drawable and add it to the image.    */
if|if
condition|(
operator|!
name|preview
condition|)
block|{
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
block|}
name|gimp_image_insert_layer
argument_list|(
name|image_ID
argument_list|,
name|layer_ID
argument_list|,
operator|-
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|jpeg_load_resolution (gint32 image_ID,struct jpeg_decompress_struct * cinfo)
name|jpeg_load_resolution
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|struct
name|jpeg_decompress_struct
modifier|*
name|cinfo
parameter_list|)
block|{
if|if
condition|(
name|cinfo
operator|->
name|saw_JFIF_marker
operator|&&
name|cinfo
operator|->
name|X_density
operator|!=
literal|0
operator|&&
name|cinfo
operator|->
name|Y_density
operator|!=
literal|0
condition|)
block|{
name|gdouble
name|xresolution
init|=
name|cinfo
operator|->
name|X_density
decl_stmt|;
name|gdouble
name|yresolution
init|=
name|cinfo
operator|->
name|Y_density
decl_stmt|;
name|gdouble
name|asymmetry
init|=
literal|1.0
decl_stmt|;
switch|switch
condition|(
name|cinfo
operator|->
name|density_unit
condition|)
block|{
case|case
literal|0
case|:
comment|/* unknown -> set the aspect ratio but use the default                  *  image resolution                  */
name|asymmetry
operator|=
name|xresolution
operator|/
name|yresolution
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image_ID
argument_list|,
operator|&
name|xresolution
argument_list|,
operator|&
name|yresolution
argument_list|)
expr_stmt|;
name|xresolution
operator|*=
name|asymmetry
expr_stmt|;
break|break;
case|case
literal|1
case|:
comment|/* dots per inch */
break|break;
case|case
literal|2
case|:
comment|/* dots per cm */
name|xresolution
operator|*=
literal|2.54
expr_stmt|;
name|yresolution
operator|*=
literal|2.54
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|image_ID
argument_list|,
name|GIMP_UNIT_MM
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_message
argument_list|(
literal|"Unknown density unit %d, assuming dots per inch."
argument_list|,
name|cinfo
operator|->
name|density_unit
argument_list|)
expr_stmt|;
break|break;
block|}
name|gimp_image_set_resolution
argument_list|(
name|image_ID
argument_list|,
name|xresolution
argument_list|,
name|yresolution
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  * A number of JPEG files have comments written in a local character set  * instead of UTF-8.  Some of these files may have been saved by older  * versions of GIMP.  It is not possible to reliably detect the character  * set used, but it is better to keep all characters in the ASCII range  * and replace the non-ASCII characters instead of discarding the whole  * comment.  This is especially useful if the comment contains only a few  * non-ASCII characters such as a copyright sign, a soft hyphen, etc.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|jpeg_load_sanitize_comment (gchar * comment)
name|jpeg_load_sanitize_comment
parameter_list|(
name|gchar
modifier|*
name|comment
parameter_list|)
block|{
if|if
condition|(
operator|!
name|g_utf8_validate
argument_list|(
name|comment
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|c
decl_stmt|;
for|for
control|(
name|c
operator|=
name|comment
init|;
operator|*
name|c
condition|;
name|c
operator|++
control|)
block|{
if|if
condition|(
operator|*
name|c
operator|>
literal|126
operator|||
operator|(
operator|*
name|c
operator|<
literal|32
operator|&&
operator|*
name|c
operator|!=
literal|'\t'
operator|&&
operator|*
name|c
operator|!=
literal|'\n'
operator|&&
operator|*
name|c
operator|!=
literal|'\r'
operator|)
condition|)
operator|*
name|c
operator|=
literal|'?'
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|gint32
DECL|function|load_thumbnail_image (GFile * file,gint * width,gint * height,GimpImageType * type,GError ** error)
name|load_thumbnail_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|GimpImageType
modifier|*
name|type
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gint32
specifier|volatile
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|struct
name|jpeg_decompress_struct
name|cinfo
decl_stmt|;
name|struct
name|my_error_mgr
name|jerr
decl_stmt|;
name|FILE
modifier|*
name|infile
init|=
name|NULL
decl_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Opening thumbnail for '%s'"
argument_list|)
argument_list|,
name|g_file_get_parse_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|image_ID
operator|=
name|gimp_image_metadata_load_thumbnail
argument_list|(
name|file
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|<
literal|1
condition|)
return|return
operator|-
literal|1
return|;
name|cinfo
operator|.
name|err
operator|=
name|jpeg_std_error
argument_list|(
operator|&
name|jerr
operator|.
name|pub
argument_list|)
expr_stmt|;
name|jerr
operator|.
name|pub
operator|.
name|error_exit
operator|=
name|my_error_exit
expr_stmt|;
name|jerr
operator|.
name|pub
operator|.
name|output_message
operator|=
name|my_output_message
expr_stmt|;
if|if
condition|(
operator|(
name|infile
operator|=
name|g_fopen
argument_list|(
name|g_file_get_path
argument_list|(
name|file
argument_list|)
argument_list|,
literal|"rb"
argument_list|)
operator|)
operator|==
name|NULL
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|g_file_error_from_errno
argument_list|(
name|errno
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|g_file_get_parse_name
argument_list|(
name|file
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
name|gimp_image_delete
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* Establish the setjmp return context for my_error_exit to use. */
if|if
condition|(
name|setjmp
argument_list|(
name|jerr
operator|.
name|setjmp_buffer
argument_list|)
condition|)
block|{
comment|/* If we get here, the JPEG code has signaled an error.  We        * need to clean up the JPEG object, close the input file,        * and return.        */
name|jpeg_destroy_decompress
argument_list|(
operator|&
name|cinfo
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
name|gimp_image_delete
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* Now we can initialize the JPEG decompression object. */
name|jpeg_create_decompress
argument_list|(
operator|&
name|cinfo
argument_list|)
expr_stmt|;
comment|/* Step 2: specify data source (eg, a file) */
name|jpeg_stdio_src
argument_list|(
operator|&
name|cinfo
argument_list|,
name|infile
argument_list|)
expr_stmt|;
comment|/* Step 3: read file parameters with jpeg_read_header() */
name|jpeg_read_header
argument_list|(
operator|&
name|cinfo
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|jpeg_start_decompress
argument_list|(
operator|&
name|cinfo
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
name|cinfo
operator|.
name|output_width
expr_stmt|;
operator|*
name|height
operator|=
name|cinfo
operator|.
name|output_height
expr_stmt|;
switch|switch
condition|(
name|cinfo
operator|.
name|output_components
condition|)
block|{
case|case
literal|1
case|:
operator|*
name|type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
literal|3
case|:
operator|*
name|type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
literal|4
case|:
if|if
condition|(
name|cinfo
operator|.
name|out_color_space
operator|==
name|JCS_CMYK
condition|)
block|{
operator|*
name|type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
block|}
comment|/*fallthrough*/
default|default:
name|g_message
argument_list|(
literal|"Don't know how to load JPEG images "
literal|"with %d color channels, using colorspace %d (%d)."
argument_list|,
name|cinfo
operator|.
name|output_components
argument_list|,
name|cinfo
operator|.
name|out_color_space
argument_list|,
name|cinfo
operator|.
name|jpeg_color_space
argument_list|)
expr_stmt|;
name|gimp_image_delete
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|image_ID
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
comment|/* Step 4: Release JPEG decompression object */
comment|/* This is an important step since it will release a good deal    * of memory.    */
name|jpeg_destroy_decompress
argument_list|(
operator|&
name|cinfo
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|infile
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_function
specifier|static
name|gpointer
DECL|function|jpeg_load_cmyk_transform (guint8 * profile_data,gsize profile_len)
name|jpeg_load_cmyk_transform
parameter_list|(
name|guint8
modifier|*
name|profile_data
parameter_list|,
name|gsize
name|profile_len
parameter_list|)
block|{
name|GimpColorConfig
modifier|*
name|config
init|=
name|gimp_get_color_configuration
argument_list|()
decl_stmt|;
name|cmsHPROFILE
name|cmyk_profile
init|=
name|NULL
decl_stmt|;
name|cmsHPROFILE
name|rgb_profile
init|=
name|NULL
decl_stmt|;
name|cmsUInt32Number
name|flags
init|=
literal|0
decl_stmt|;
name|cmsHTRANSFORM
name|transform
decl_stmt|;
comment|/*  try to load the embedded CMYK profile  */
if|if
condition|(
name|profile_data
condition|)
block|{
name|cmyk_profile
operator|=
name|cmsOpenProfileFromMem
argument_list|(
name|profile_data
argument_list|,
name|profile_len
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmyk_profile
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_lcms_profile_is_cmyk
argument_list|(
name|cmyk_profile
argument_list|)
condition|)
block|{
name|cmsCloseProfile
argument_list|(
name|cmyk_profile
argument_list|)
expr_stmt|;
name|cmyk_profile
operator|=
name|NULL
expr_stmt|;
block|}
block|}
block|}
comment|/*  if that fails, try to load the CMYK profile configured in the prefs  */
if|if
condition|(
operator|!
name|cmyk_profile
operator|&&
name|config
operator|->
name|cmyk_profile
condition|)
block|{
name|cmyk_profile
operator|=
name|cmsOpenProfileFromFile
argument_list|(
name|config
operator|->
name|cmyk_profile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmyk_profile
operator|&&
operator|!
name|gimp_lcms_profile_is_cmyk
argument_list|(
name|cmyk_profile
argument_list|)
condition|)
block|{
name|cmsCloseProfile
argument_list|(
name|cmyk_profile
argument_list|)
expr_stmt|;
name|cmyk_profile
operator|=
name|NULL
expr_stmt|;
block|}
block|}
comment|/*  bail out if we can't load any CMYK profile  */
if|if
condition|(
operator|!
name|cmyk_profile
condition|)
block|{
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/*  try to load the RGB profile configured in the prefs  */
if|if
condition|(
name|config
operator|->
name|rgb_profile
condition|)
block|{
name|rgb_profile
operator|=
name|cmsOpenProfileFromFile
argument_list|(
name|config
operator|->
name|rgb_profile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|rgb_profile
operator|&&
operator|!
name|gimp_lcms_profile_is_rgb
argument_list|(
name|rgb_profile
argument_list|)
condition|)
block|{
name|cmsCloseProfile
argument_list|(
name|rgb_profile
argument_list|)
expr_stmt|;
name|rgb_profile
operator|=
name|NULL
expr_stmt|;
block|}
block|}
comment|/*  make the real sRGB profile as a fallback  */
if|if
condition|(
operator|!
name|rgb_profile
condition|)
block|{
name|rgb_profile
operator|=
name|gimp_lcms_create_srgb_profile
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|config
operator|->
name|display_intent
operator|==
name|GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
condition|)
block|{
name|flags
operator||=
name|cmsFLAGS_BLACKPOINTCOMPENSATION
expr_stmt|;
block|}
name|transform
operator|=
name|cmsCreateTransform
argument_list|(
name|cmyk_profile
argument_list|,
name|TYPE_CMYK_8_REV
argument_list|,
name|rgb_profile
argument_list|,
name|TYPE_RGB_8
argument_list|,
name|config
operator|->
name|display_intent
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|cmyk_profile
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|rgb_profile
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
return|return
name|transform
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|jpeg_load_cmyk_to_rgb (guchar * buf,glong pixels,gpointer transform)
name|jpeg_load_cmyk_to_rgb
parameter_list|(
name|guchar
modifier|*
name|buf
parameter_list|,
name|glong
name|pixels
parameter_list|,
name|gpointer
name|transform
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|buf
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|buf
decl_stmt|;
if|if
condition|(
name|transform
condition|)
block|{
name|cmsDoTransform
argument_list|(
name|transform
argument_list|,
name|buf
argument_list|,
name|buf
argument_list|,
name|pixels
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* NOTE: The following code assumes inverted CMYK values, even when an      APP14 marker doesn't exist. This is the behavior of recent versions      of PhotoShop as well. */
while|while
condition|(
name|pixels
operator|--
condition|)
block|{
name|guint
name|c
init|=
name|src
index|[
literal|0
index|]
decl_stmt|;
name|guint
name|m
init|=
name|src
index|[
literal|1
index|]
decl_stmt|;
name|guint
name|y
init|=
name|src
index|[
literal|2
index|]
decl_stmt|;
name|guint
name|k
init|=
name|src
index|[
literal|3
index|]
decl_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
operator|(
name|c
operator|*
name|k
operator|)
operator|/
literal|255
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
operator|(
name|m
operator|*
name|k
operator|)
operator|/
literal|255
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
operator|(
name|y
operator|*
name|k
operator|)
operator|/
literal|255
expr_stmt|;
name|src
operator|+=
literal|4
expr_stmt|;
name|dest
operator|+=
literal|3
expr_stmt|;
block|}
block|}
end_function

end_unit

