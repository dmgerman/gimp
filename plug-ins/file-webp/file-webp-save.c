begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-webp - WebP file format plug-in for the GIMP  * Copyright (C) 2015  Nathan Osman  * Copyright (C) 2016  Ben Touchette  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation, either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<glib/gstdio.h>
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
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|<webp/mux.h>
end_include

begin_include
include|#
directive|include
file|"file-webp-save.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
name|int
name|webp_anim_file_writer
parameter_list|(
name|FILE
modifier|*
name|outfile
parameter_list|,
specifier|const
name|uint8_t
modifier|*
name|data
parameter_list|,
name|size_t
name|data_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|webp_file_writer
parameter_list|(
specifier|const
name|uint8_t
modifier|*
name|data
parameter_list|,
name|size_t
name|data_size
parameter_list|,
specifier|const
name|WebPPicture
modifier|*
name|picture
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|webp_file_progress
parameter_list|(
name|int
name|percent
parameter_list|,
specifier|const
name|WebPPicture
modifier|*
name|picture
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|webp_error_string
parameter_list|(
name|WebPEncodingError
name|error_code
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|save_layer
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|nLayers
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|WebPSaveParams
modifier|*
name|params
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|save_animation
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|nLayers
parameter_list|,
name|gint32
modifier|*
name|allLayers
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|WebPSaveParams
modifier|*
name|params
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|int
DECL|function|webp_anim_file_writer (FILE * outfile,const uint8_t * data,size_t data_size)
name|webp_anim_file_writer
parameter_list|(
name|FILE
modifier|*
name|outfile
parameter_list|,
specifier|const
name|uint8_t
modifier|*
name|data
parameter_list|,
name|size_t
name|data_size
parameter_list|)
block|{
name|int
name|ok
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|data
operator|==
name|NULL
condition|)
return|return
literal|0
return|;
name|ok
operator|=
operator|(
name|fwrite
argument_list|(
name|data
argument_list|,
name|data_size
argument_list|,
literal|1
argument_list|,
name|outfile
argument_list|)
operator|==
literal|1
operator|)
expr_stmt|;
return|return
name|ok
return|;
block|}
end_function

begin_function
name|int
DECL|function|webp_file_writer (const uint8_t * data,size_t data_size,const WebPPicture * picture)
name|webp_file_writer
parameter_list|(
specifier|const
name|uint8_t
modifier|*
name|data
parameter_list|,
name|size_t
name|data_size
parameter_list|,
specifier|const
name|WebPPicture
modifier|*
name|picture
parameter_list|)
block|{
name|FILE
modifier|*
name|outfile
decl_stmt|;
comment|/* Obtain the FILE* and write the data to the file */
name|outfile
operator|=
operator|(
name|FILE
operator|*
operator|)
name|picture
operator|->
name|custom_ptr
expr_stmt|;
return|return
name|fwrite
argument_list|(
name|data
argument_list|,
sizeof|sizeof
argument_list|(
name|uint8_t
argument_list|)
argument_list|,
name|data_size
argument_list|,
name|outfile
argument_list|)
operator|==
name|data_size
return|;
block|}
end_function

begin_function
name|int
DECL|function|webp_file_progress (int percent,const WebPPicture * picture)
name|webp_file_progress
parameter_list|(
name|int
name|percent
parameter_list|,
specifier|const
name|WebPPicture
modifier|*
name|picture
parameter_list|)
block|{
return|return
name|gimp_progress_update
argument_list|(
name|percent
operator|/
literal|100.0
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|webp_error_string (WebPEncodingError error_code)
name|webp_error_string
parameter_list|(
name|WebPEncodingError
name|error_code
parameter_list|)
block|{
switch|switch
condition|(
name|error_code
condition|)
block|{
case|case
name|VP8_ENC_ERROR_OUT_OF_MEMORY
case|:
return|return
name|_
argument_list|(
literal|"out of memory"
argument_list|)
return|;
case|case
name|VP8_ENC_ERROR_BITSTREAM_OUT_OF_MEMORY
case|:
return|return
name|_
argument_list|(
literal|"not enough memory to flush bits"
argument_list|)
return|;
case|case
name|VP8_ENC_ERROR_NULL_PARAMETER
case|:
return|return
name|_
argument_list|(
literal|"NULL parameter"
argument_list|)
return|;
case|case
name|VP8_ENC_ERROR_INVALID_CONFIGURATION
case|:
return|return
name|_
argument_list|(
literal|"invalid configuration"
argument_list|)
return|;
case|case
name|VP8_ENC_ERROR_BAD_DIMENSION
case|:
return|return
name|_
argument_list|(
literal|"bad image dimensions"
argument_list|)
return|;
case|case
name|VP8_ENC_ERROR_PARTITION0_OVERFLOW
case|:
return|return
name|_
argument_list|(
literal|"partition is bigger than 512K"
argument_list|)
return|;
case|case
name|VP8_ENC_ERROR_PARTITION_OVERFLOW
case|:
return|return
name|_
argument_list|(
literal|"partition is bigger than 16M"
argument_list|)
return|;
case|case
name|VP8_ENC_ERROR_BAD_WRITE
case|:
return|return
name|_
argument_list|(
literal|"unable to flush bytes"
argument_list|)
return|;
case|case
name|VP8_ENC_ERROR_FILE_TOO_BIG
case|:
return|return
name|_
argument_list|(
literal|"file is larger than 4GiB"
argument_list|)
return|;
case|case
name|VP8_ENC_ERROR_USER_ABORT
case|:
return|return
name|_
argument_list|(
literal|"user aborted encoding"
argument_list|)
return|;
case|case
name|VP8_ENC_ERROR_LAST
case|:
return|return
name|_
argument_list|(
literal|"list terminator"
argument_list|)
return|;
default|default:
return|return
name|_
argument_list|(
literal|"unknown error"
argument_list|)
return|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|save_layer (const gchar * filename,gint32 nLayers,gint32 image_ID,gint32 drawable_ID,WebPSaveParams * params,GError ** error)
name|save_layer
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|nLayers
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|WebPSaveParams
modifier|*
name|params
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|status
init|=
name|FALSE
decl_stmt|;
name|FILE
modifier|*
name|outfile
init|=
name|NULL
decl_stmt|;
name|WebPConfig
name|config
init|=
block|{
literal|0
block|}
decl_stmt|;
name|WebPPicture
name|picture
init|=
block|{
literal|0
block|}
decl_stmt|;
name|guchar
modifier|*
name|buffer
init|=
name|NULL
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
decl_stmt|;
name|GeglBuffer
modifier|*
name|geglbuffer
init|=
name|NULL
decl_stmt|;
name|GeglRectangle
name|extent
decl_stmt|;
name|gchar
modifier|*
name|indata
decl_stmt|;
name|gsize
name|indatalen
decl_stmt|;
name|struct
name|stat
name|stsz
decl_stmt|;
name|int
name|fd_outfile
decl_stmt|;
name|WebPData
name|chunk
decl_stmt|;
name|int
name|res
decl_stmt|;
comment|/* The do...while() loop is a neat little trick that makes it easier    * to jump to error handling code while still ensuring proper    * cleanup    */
do|do
block|{
comment|/* Begin displaying export progress */
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Saving '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Attempt to open the output file */
if|if
condition|(
operator|(
name|outfile
operator|=
name|g_fopen
argument_list|(
name|filename
argument_list|,
literal|"wb+"
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
literal|"Unable to open '%s' for writing"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* Obtain the drawable type */
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
else|else
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
comment|/* Retrieve the buffer for the layer */
name|geglbuffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|extent
operator|=
operator|*
name|gegl_buffer_get_extent
argument_list|(
name|geglbuffer
argument_list|)
expr_stmt|;
name|w
operator|=
name|extent
operator|.
name|width
expr_stmt|;
name|h
operator|=
name|extent
operator|.
name|height
expr_stmt|;
comment|/* Initialize the WebP configuration with a preset and fill in the        * remaining values */
name|WebPConfigPreset
argument_list|(
operator|&
name|config
argument_list|,
name|params
operator|->
name|preset
argument_list|,
name|params
operator|->
name|quality
argument_list|)
expr_stmt|;
name|config
operator|.
name|lossless
operator|=
name|params
operator|->
name|lossless
expr_stmt|;
name|config
operator|.
name|method
operator|=
literal|6
expr_stmt|;
comment|/* better quality */
name|config
operator|.
name|alpha_quality
operator|=
name|params
operator|->
name|alpha_quality
expr_stmt|;
comment|/* Prepare the WebP structure */
name|WebPPictureInit
argument_list|(
operator|&
name|picture
argument_list|)
expr_stmt|;
name|picture
operator|.
name|use_argb
operator|=
literal|1
expr_stmt|;
name|picture
operator|.
name|width
operator|=
name|w
expr_stmt|;
name|picture
operator|.
name|height
operator|=
name|h
expr_stmt|;
name|picture
operator|.
name|writer
operator|=
name|webp_file_writer
expr_stmt|;
name|picture
operator|.
name|custom_ptr
operator|=
name|outfile
expr_stmt|;
name|picture
operator|.
name|progress_hook
operator|=
name|webp_file_progress
expr_stmt|;
comment|/* Attempt to allocate a buffer of the appropriate size */
name|buffer
operator|=
name|g_try_malloc
argument_list|(
name|w
operator|*
name|h
operator|*
name|bpp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|buffer
condition|)
break|break;
comment|/* Read the region into the buffer */
name|gegl_buffer_get
argument_list|(
name|geglbuffer
argument_list|,
operator|&
name|extent
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|buffer
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
comment|/* Use the appropriate function to import the data from the buffer */
if|if
condition|(
operator|!
name|has_alpha
condition|)
block|{
name|WebPPictureImportRGB
argument_list|(
operator|&
name|picture
argument_list|,
name|buffer
argument_list|,
name|w
operator|*
name|bpp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|WebPPictureImportRGBA
argument_list|(
operator|&
name|picture
argument_list|,
name|buffer
argument_list|,
name|w
operator|*
name|bpp
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
comment|/* Perform the actual encode */
if|if
condition|(
operator|!
name|WebPEncode
argument_list|(
operator|&
name|config
argument_list|,
operator|&
name|picture
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"WebP error: '%s'"
argument_list|,
name|webp_error_string
argument_list|(
name|picture
operator|.
name|error_code
argument_list|)
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|picture
operator|.
name|error_code
argument_list|,
name|_
argument_list|(
literal|"WebP error: '%s'"
argument_list|)
argument_list|,
name|webp_error_string
argument_list|(
name|picture
operator|.
name|error_code
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* The cleanup stuff still needs to run but indicate that everything        * completed successfully        */
name|status
operator|=
name|TRUE
expr_stmt|;
block|}
do|while
condition|(
literal|0
condition|)
do|;
comment|/* Flush the drawable and detach */
if|if
condition|(
name|geglbuffer
condition|)
block|{
name|gegl_buffer_flush
argument_list|(
name|geglbuffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|geglbuffer
argument_list|)
expr_stmt|;
block|}
name|fflush
argument_list|(
name|outfile
argument_list|)
expr_stmt|;
name|fd_outfile
operator|=
name|fileno
argument_list|(
name|outfile
argument_list|)
expr_stmt|;
name|fstat
argument_list|(
name|fd_outfile
argument_list|,
operator|&
name|stsz
argument_list|)
expr_stmt|;
name|indatalen
operator|=
name|stsz
operator|.
name|st_size
expr_stmt|;
if|if
condition|(
name|indatalen
operator|>
literal|0
condition|)
block|{
name|indata
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_malloc
argument_list|(
name|indatalen
argument_list|)
expr_stmt|;
name|rewind
argument_list|(
name|outfile
argument_list|)
expr_stmt|;
name|res
operator|=
name|fread
argument_list|(
name|indata
argument_list|,
literal|1
argument_list|,
name|indatalen
argument_list|,
name|outfile
argument_list|)
expr_stmt|;
if|if
condition|(
name|res
operator|>
literal|0
condition|)
block|{
name|WebPMux
modifier|*
name|mux
decl_stmt|;
name|WebPData
name|wp_data
decl_stmt|;
name|wp_data
operator|.
name|bytes
operator|=
operator|(
name|uint8_t
operator|*
operator|)
name|indata
expr_stmt|;
name|wp_data
operator|.
name|size
operator|=
name|indatalen
expr_stmt|;
name|mux
operator|=
name|WebPMuxCreate
argument_list|(
operator|&
name|wp_data
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|mux
condition|)
block|{
name|gboolean
name|saved
init|=
name|FALSE
decl_stmt|;
comment|/* Save ICC data */
name|profile
operator|=
name|gimp_image_get_color_profile
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
specifier|const
name|guint8
modifier|*
name|icc_data
decl_stmt|;
name|gsize
name|icc_data_size
decl_stmt|;
name|saved
operator|=
name|TRUE
expr_stmt|;
name|icc_data
operator|=
name|gimp_color_profile_get_icc_profile
argument_list|(
name|profile
argument_list|,
operator|&
name|icc_data_size
argument_list|)
expr_stmt|;
name|chunk
operator|.
name|bytes
operator|=
name|icc_data
expr_stmt|;
name|chunk
operator|.
name|size
operator|=
name|icc_data_size
expr_stmt|;
name|WebPMuxSetChunk
argument_list|(
name|mux
argument_list|,
literal|"ICCP"
argument_list|,
operator|&
name|chunk
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|saved
operator|==
name|TRUE
condition|)
block|{
name|WebPMuxAssemble
argument_list|(
name|mux
argument_list|,
operator|&
name|wp_data
argument_list|)
expr_stmt|;
name|rewind
argument_list|(
name|outfile
argument_list|)
expr_stmt|;
name|webp_anim_file_writer
argument_list|(
name|outfile
argument_list|,
name|wp_data
operator|.
name|bytes
argument_list|,
name|wp_data
operator|.
name|size
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"ERROR: Cannot create mux. Can't save features update.\n"
argument_list|)
expr_stmt|;
block|}
name|WebPDataClear
argument_list|(
operator|&
name|wp_data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"ERROR: No data read for features. Can't save features update.\n"
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"ERROR: No data for features. Can't save features update.\n"
argument_list|)
expr_stmt|;
block|}
comment|/* Free any resources */
if|if
condition|(
name|outfile
condition|)
name|fclose
argument_list|(
name|outfile
argument_list|)
expr_stmt|;
name|WebPPictureFree
argument_list|(
operator|&
name|picture
argument_list|)
expr_stmt|;
return|return
name|status
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|parse_ms_tag (const gchar * str)
name|parse_ms_tag
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|)
block|{
name|gint
name|sum
init|=
literal|0
decl_stmt|;
name|gint
name|offset
init|=
literal|0
decl_stmt|;
name|gint
name|length
decl_stmt|;
name|length
operator|=
name|strlen
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|find_another_bra
label|:
while|while
condition|(
operator|(
name|offset
operator|<
name|length
operator|)
operator|&&
operator|(
name|str
index|[
name|offset
index|]
operator|!=
literal|'('
operator|)
condition|)
name|offset
operator|++
expr_stmt|;
if|if
condition|(
name|offset
operator|>=
name|length
condition|)
return|return
operator|-
literal|1
return|;
if|if
condition|(
operator|!
name|g_ascii_isdigit
argument_list|(
name|str
index|[
operator|++
name|offset
index|]
argument_list|)
condition|)
goto|goto
name|find_another_bra
goto|;
do|do
block|{
name|sum
operator|*=
literal|10
expr_stmt|;
name|sum
operator|+=
name|str
index|[
name|offset
index|]
operator|-
literal|'0'
expr_stmt|;
name|offset
operator|++
expr_stmt|;
block|}
do|while
condition|(
operator|(
name|offset
operator|<
name|length
operator|)
operator|&&
operator|(
name|g_ascii_isdigit
argument_list|(
name|str
index|[
name|offset
index|]
argument_list|)
operator|)
condition|)
do|;
if|if
condition|(
name|length
operator|-
name|offset
operator|<=
literal|2
condition|)
return|return
operator|-
literal|3
return|;
if|if
condition|(
operator|(
name|g_ascii_toupper
argument_list|(
name|str
index|[
name|offset
index|]
argument_list|)
operator|!=
literal|'M'
operator|)
operator|||
operator|(
name|g_ascii_toupper
argument_list|(
name|str
index|[
name|offset
operator|+
literal|1
index|]
argument_list|)
operator|!=
literal|'S'
operator|)
condition|)
return|return
operator|-
literal|4
return|;
return|return
name|sum
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|get_layer_delay (gint32 layer)
name|get_layer_delay
parameter_list|(
name|gint32
name|layer
parameter_list|)
block|{
name|gchar
modifier|*
name|layer_name
decl_stmt|;
name|gint
name|delay_ms
decl_stmt|;
name|layer_name
operator|=
name|gimp_item_get_name
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|delay_ms
operator|=
name|parse_ms_tag
argument_list|(
name|layer_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|layer_name
argument_list|)
expr_stmt|;
return|return
name|delay_ms
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|save_animation (const gchar * filename,gint32 nLayers,gint32 * allLayers,gint32 image_ID,gint32 drawable_ID,WebPSaveParams * params,GError ** error)
name|save_animation
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|nLayers
parameter_list|,
name|gint32
modifier|*
name|allLayers
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|WebPSaveParams
modifier|*
name|params
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|status
init|=
name|TRUE
decl_stmt|;
name|FILE
modifier|*
name|outfile
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|buffer
init|=
name|NULL
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
decl_stmt|;
name|WebPAnimEncoderOptions
name|enc_options
decl_stmt|;
name|WebPData
name|webp_data
decl_stmt|;
name|int
name|frame_timestamp
init|=
literal|0
decl_stmt|;
name|WebPAnimEncoder
modifier|*
name|enc
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|nLayers
operator|<
literal|1
condition|)
return|return
name|FALSE
return|;
name|gimp_image_undo_freeze
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|WebPDataInit
argument_list|(
operator|&
name|webp_data
argument_list|)
expr_stmt|;
do|do
block|{
name|gint
name|loop
decl_stmt|;
name|gint
name|default_delay
init|=
name|params
operator|->
name|delay
decl_stmt|;
name|gboolean
name|force_delay
init|=
name|params
operator|->
name|force_delay
decl_stmt|;
comment|/* Begin displaying export progress */
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Saving '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Attempt to open the output file */
if|if
condition|(
operator|(
name|outfile
operator|=
name|g_fopen
argument_list|(
name|filename
argument_list|,
literal|"wb"
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
literal|"Unable to open '%s' for writing"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|status
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|!
name|WebPAnimEncoderOptionsInit
argument_list|(
operator|&
name|enc_options
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"ERROR: verion mismatch\n"
argument_list|)
expr_stmt|;
name|status
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
name|enc_options
operator|.
name|anim_params
operator|.
name|loop_count
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|params
operator|->
name|loop
condition|)
name|enc_options
operator|.
name|anim_params
operator|.
name|loop_count
operator|=
literal|1
expr_stmt|;
name|enc_options
operator|.
name|allow_mixed
operator|=
name|params
operator|->
name|lossless
condition|?
literal|0
else|:
literal|1
expr_stmt|;
name|enc_options
operator|.
name|minimize_size
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
name|nLayers
condition|;
name|loop
operator|++
control|)
block|{
name|GeglBuffer
modifier|*
name|geglbuffer
decl_stmt|;
name|GeglRectangle
name|extent
decl_stmt|;
name|WebPConfig
name|config
decl_stmt|;
name|WebPPicture
name|picture
decl_stmt|;
name|WebPMemoryWriter
name|mw
init|=
block|{
literal|0
block|}
decl_stmt|;
name|gint32
name|drawable
init|=
name|allLayers
index|[
name|nLayers
operator|-
literal|1
operator|-
name|loop
index|]
decl_stmt|;
name|gint
name|delay
init|=
name|get_layer_delay
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
comment|/* Obtain the drawable type */
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
else|else
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
comment|/* fix layers to avoid offset errors */
name|gimp_layer_resize_to_image_size
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
comment|/* Retrieve the buffer for the layer */
name|geglbuffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|extent
operator|=
operator|*
name|gegl_buffer_get_extent
argument_list|(
name|geglbuffer
argument_list|)
expr_stmt|;
name|w
operator|=
name|extent
operator|.
name|width
expr_stmt|;
name|h
operator|=
name|extent
operator|.
name|height
expr_stmt|;
if|if
condition|(
name|loop
operator|==
literal|0
condition|)
block|{
name|enc
operator|=
name|WebPAnimEncoderNew
argument_list|(
name|w
argument_list|,
name|h
argument_list|,
operator|&
name|enc_options
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|enc
condition|)
block|{
name|g_printerr
argument_list|(
literal|"ERROR: enc == null\n"
argument_list|)
expr_stmt|;
name|status
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
block|}
comment|/* Attempt to allocate a buffer of the appropriate size */
name|buffer
operator|=
name|g_try_malloc
argument_list|(
name|w
operator|*
name|h
operator|*
name|bpp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|buffer
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Buffer error: 'buffer null'\n"
argument_list|)
expr_stmt|;
name|status
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
name|WebPConfigPreset
argument_list|(
operator|&
name|config
argument_list|,
name|params
operator|->
name|preset
argument_list|,
name|params
operator|->
name|quality
argument_list|)
expr_stmt|;
name|config
operator|.
name|lossless
operator|=
name|params
operator|->
name|lossless
expr_stmt|;
name|config
operator|.
name|method
operator|=
literal|6
expr_stmt|;
comment|/* better quality */
name|config
operator|.
name|alpha_quality
operator|=
name|params
operator|->
name|alpha_quality
expr_stmt|;
name|config
operator|.
name|exact
operator|=
literal|1
expr_stmt|;
name|WebPMemoryWriterInit
argument_list|(
operator|&
name|mw
argument_list|)
expr_stmt|;
comment|/* Prepare the WebP structure */
name|WebPPictureInit
argument_list|(
operator|&
name|picture
argument_list|)
expr_stmt|;
name|picture
operator|.
name|use_argb
operator|=
literal|1
expr_stmt|;
name|picture
operator|.
name|argb_stride
operator|=
name|w
operator|*
name|bpp
expr_stmt|;
name|picture
operator|.
name|width
operator|=
name|w
expr_stmt|;
name|picture
operator|.
name|height
operator|=
name|h
expr_stmt|;
name|picture
operator|.
name|custom_ptr
operator|=
operator|&
name|mw
expr_stmt|;
name|picture
operator|.
name|writer
operator|=
name|WebPMemoryWrite
expr_stmt|;
comment|/* Read the region into the buffer */
name|gegl_buffer_get
argument_list|(
name|geglbuffer
argument_list|,
operator|&
name|extent
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|buffer
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
comment|/* Use the appropriate function to import the data from the buffer */
if|if
condition|(
operator|!
name|has_alpha
condition|)
block|{
name|WebPPictureImportRGB
argument_list|(
operator|&
name|picture
argument_list|,
name|buffer
argument_list|,
name|w
operator|*
name|bpp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|WebPPictureImportRGBA
argument_list|(
operator|&
name|picture
argument_list|,
name|buffer
argument_list|,
name|w
operator|*
name|bpp
argument_list|)
expr_stmt|;
block|}
comment|/* Perform the actual encode */
if|if
condition|(
operator|!
name|WebPAnimEncoderAdd
argument_list|(
name|enc
argument_list|,
operator|&
name|picture
argument_list|,
name|frame_timestamp
argument_list|,
operator|&
name|config
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"ERROR[%d]: %s\n"
argument_list|,
name|picture
operator|.
name|error_code
argument_list|,
name|webp_error_string
argument_list|(
name|picture
operator|.
name|error_code
argument_list|)
argument_list|)
expr_stmt|;
name|status
operator|=
name|FALSE
expr_stmt|;
block|}
name|WebPMemoryWriterClear
argument_list|(
operator|&
name|mw
argument_list|)
expr_stmt|;
name|WebPPictureFree
argument_list|(
operator|&
name|picture
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|FALSE
condition|)
break|break;
comment|/* Flush the drawable and detach */
name|gegl_buffer_flush
argument_list|(
name|geglbuffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|geglbuffer
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|loop
operator|+
literal|1.0
operator|)
operator|/
name|nLayers
argument_list|)
expr_stmt|;
name|frame_timestamp
operator|+=
operator|(
name|delay
operator|<=
literal|0
operator|||
name|force_delay
operator|)
condition|?
name|default_delay
else|:
name|delay
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|FALSE
condition|)
break|break;
name|WebPAnimEncoderAdd
argument_list|(
name|enc
argument_list|,
name|NULL
argument_list|,
name|frame_timestamp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|WebPAnimEncoderAssemble
argument_list|(
name|enc
argument_list|,
operator|&
name|webp_data
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"ERROR: %s\n"
argument_list|,
name|WebPAnimEncoderGetError
argument_list|(
name|enc
argument_list|)
argument_list|)
expr_stmt|;
name|status
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
comment|/* Create a mux object if profile is present */
name|profile
operator|=
name|gimp_image_get_color_profile
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
name|WebPMux
modifier|*
name|mux
decl_stmt|;
name|WebPData
name|chunk
decl_stmt|;
specifier|const
name|guint8
modifier|*
name|icc_data
decl_stmt|;
name|gsize
name|icc_data_size
decl_stmt|;
name|mux
operator|=
name|WebPMuxCreate
argument_list|(
operator|&
name|webp_data
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|mux
operator|==
name|NULL
condition|)
block|{
name|g_printerr
argument_list|(
literal|"ERROR: could not extract muxing object\n"
argument_list|)
expr_stmt|;
name|status
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
comment|/* Save ICC data */
name|icc_data
operator|=
name|gimp_color_profile_get_icc_profile
argument_list|(
name|profile
argument_list|,
operator|&
name|icc_data_size
argument_list|)
expr_stmt|;
name|chunk
operator|.
name|bytes
operator|=
name|icc_data
expr_stmt|;
name|chunk
operator|.
name|size
operator|=
name|icc_data_size
expr_stmt|;
name|WebPMuxSetChunk
argument_list|(
name|mux
argument_list|,
literal|"ICCP"
argument_list|,
operator|&
name|chunk
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
name|WebPDataClear
argument_list|(
operator|&
name|webp_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|WebPMuxAssemble
argument_list|(
name|mux
argument_list|,
operator|&
name|webp_data
argument_list|)
operator|!=
name|WEBP_MUX_OK
condition|)
block|{
name|g_printerr
argument_list|(
literal|"ERROR: could not assemble final bytestream\n"
argument_list|)
expr_stmt|;
name|status
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
block|}
name|webp_anim_file_writer
argument_list|(
name|outfile
argument_list|,
name|webp_data
operator|.
name|bytes
argument_list|,
name|webp_data
operator|.
name|size
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
literal|0
condition|)
do|;
comment|/* Free any resources */
name|WebPDataClear
argument_list|(
operator|&
name|webp_data
argument_list|)
expr_stmt|;
name|WebPAnimEncoderDelete
argument_list|(
name|enc
argument_list|)
expr_stmt|;
if|if
condition|(
name|outfile
condition|)
name|fclose
argument_list|(
name|outfile
argument_list|)
expr_stmt|;
return|return
name|status
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|save_image (const gchar * filename,gint32 nLayers,gint32 * allLayers,gint32 image_ID,gint32 drawable_ID,WebPSaveParams * params,GError ** error)
name|save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|nLayers
parameter_list|,
name|gint32
modifier|*
name|allLayers
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|WebPSaveParams
modifier|*
name|params
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|GimpMetadataSaveFlags
name|metadata_flags
decl_stmt|;
name|gboolean
name|status
init|=
name|FALSE
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
if|if
condition|(
name|nLayers
operator|==
literal|0
condition|)
return|return
name|FALSE
return|;
name|g_printerr
argument_list|(
literal|"Saving WebP file %s\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|nLayers
operator|==
literal|1
condition|)
block|{
name|status
operator|=
name|save_layer
argument_list|(
name|filename
argument_list|,
name|nLayers
argument_list|,
name|image_ID
argument_list|,
name|drawable_ID
argument_list|,
name|params
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|params
operator|->
name|animation
condition|)
block|{
name|status
operator|=
name|save_layer
argument_list|(
name|filename
argument_list|,
name|nLayers
argument_list|,
name|image_ID
argument_list|,
name|drawable_ID
argument_list|,
name|params
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|save_animation
argument_list|(
name|filename
argument_list|,
name|nLayers
argument_list|,
name|allLayers
argument_list|,
name|image_ID
argument_list|,
name|drawable_ID
argument_list|,
name|params
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
block|}
name|metadata
operator|=
name|gimp_image_metadata_save_prepare
argument_list|(
name|image_ID
argument_list|,
literal|"image/webp"
argument_list|,
operator|&
name|metadata_flags
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
name|gimp_metadata_set_bits_per_sample
argument_list|(
name|metadata
argument_list|,
literal|8
argument_list|)
expr_stmt|;
if|if
condition|(
name|params
operator|->
name|exif
condition|)
name|metadata_flags
operator||=
name|GIMP_METADATA_SAVE_EXIF
expr_stmt|;
else|else
name|metadata_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_EXIF
expr_stmt|;
comment|/* WebP doesn't support iptc natively and          sets it via xmp */
if|if
condition|(
name|params
operator|->
name|xmp
condition|)
block|{
name|metadata_flags
operator||=
name|GIMP_METADATA_SAVE_XMP
expr_stmt|;
name|metadata_flags
operator||=
name|GIMP_METADATA_SAVE_IPTC
expr_stmt|;
block|}
else|else
block|{
name|metadata_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_XMP
expr_stmt|;
name|metadata_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_IPTC
expr_stmt|;
block|}
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_image_metadata_save_finish
argument_list|(
name|image_ID
argument_list|,
literal|"image/webp"
argument_list|,
name|metadata
argument_list|,
name|metadata_flags
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
comment|/* Return the status */
return|return
name|status
return|;
block|}
end_function

end_unit

