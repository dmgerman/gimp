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
file|<stdint.h>
end_include

begin_include
include|#
directive|include
file|<webp/decode.h>
end_include

begin_include
include|#
directive|include
file|<webp/demux.h>
end_include

begin_include
include|#
directive|include
file|<webp/mux.h>
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
file|"file-webp-load.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function
specifier|static
name|void
DECL|function|create_layer (gint32 image_ID,uint8_t * layer_data,gint32 position,gchar * name,gint width,gint height)
name|create_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|uint8_t
modifier|*
name|layer_data
parameter_list|,
name|gint32
name|position
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|gint32
name|layer_ID
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglRectangle
name|extent
decl_stmt|;
name|layer_ID
operator|=
name|gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|name
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGBA_IMAGE
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|image_ID
argument_list|,
name|layer_ID
argument_list|,
operator|-
literal|1
argument_list|,
name|position
argument_list|)
expr_stmt|;
comment|/* Retrieve the buffer for the layer */
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|layer_ID
argument_list|)
expr_stmt|;
comment|/* Copy the image data to the region */
name|gegl_rectangle_set
argument_list|(
operator|&
name|extent
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
operator|&
name|extent
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|layer_data
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
comment|/* Flush the drawable and detach */
name|gegl_buffer_flush
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint32
DECL|function|load_image (const gchar * filename,gboolean interactive,GError ** error)
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|interactive
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|uint8_t
modifier|*
name|indata
init|=
name|NULL
decl_stmt|;
name|gsize
name|indatalen
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|WebPMux
modifier|*
name|mux
decl_stmt|;
name|WebPData
name|wp_data
decl_stmt|;
name|uint32_t
name|flags
decl_stmt|;
name|gboolean
name|animation
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|icc
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|exif
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|xmp
init|=
name|FALSE
decl_stmt|;
comment|/* Attempt to read the file contents from disk */
if|if
condition|(
operator|!
name|g_file_get_contents
argument_list|(
name|filename
argument_list|,
operator|(
name|gchar
operator|*
operator|*
operator|)
operator|&
name|indata
argument_list|,
operator|&
name|indatalen
argument_list|,
name|error
argument_list|)
condition|)
block|{
return|return
operator|-
literal|1
return|;
block|}
comment|/* Validate WebP data */
if|if
condition|(
operator|!
name|WebPGetInfo
argument_list|(
name|indata
argument_list|,
name|indatalen
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Invalid WebP file '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|wp_data
operator|.
name|bytes
operator|=
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
operator|!
name|mux
condition|)
return|return
operator|-
literal|1
return|;
name|WebPMuxGetFeatures
argument_list|(
name|mux
argument_list|,
operator|&
name|flags
argument_list|)
expr_stmt|;
if|if
condition|(
name|flags
operator|&
name|ANIMATION_FLAG
condition|)
name|animation
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|flags
operator|&
name|ICCP_FLAG
condition|)
name|icc
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|flags
operator|&
name|EXIF_FLAG
condition|)
name|exif
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|flags
operator|&
name|XMP_FLAG
condition|)
name|xmp
operator|=
name|TRUE
expr_stmt|;
comment|/* TODO: decode the image in "chunks" or "tiles" */
comment|/* TODO: check if an alpha channel is present */
comment|/* Create the new image and associated layer */
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|animation
condition|)
block|{
name|uint8_t
modifier|*
name|outdata
decl_stmt|;
comment|/* Attempt to decode the data as a WebP image */
name|outdata
operator|=
name|WebPDecodeRGBA
argument_list|(
name|indata
argument_list|,
name|indatalen
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
comment|/* Check to ensure the image data was loaded correctly */
if|if
condition|(
operator|!
name|outdata
condition|)
return|return
operator|-
literal|1
return|;
name|create_layer
argument_list|(
name|image_ID
argument_list|,
name|outdata
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
comment|/* Free the image data */
name|free
argument_list|(
name|outdata
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|WebPAnimDecoder
modifier|*
name|dec
init|=
name|NULL
decl_stmt|;
name|WebPAnimInfo
name|anim_info
decl_stmt|;
name|WebPAnimDecoderOptions
name|dec_options
decl_stmt|;
name|gint
name|frame_num
init|=
literal|1
decl_stmt|;
if|if
condition|(
operator|!
name|WebPAnimDecoderOptionsInit
argument_list|(
operator|&
name|dec_options
argument_list|)
condition|)
block|{
name|error
label|:
if|if
condition|(
name|dec
condition|)
name|WebPAnimDecoderDelete
argument_list|(
name|dec
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* dec_options.color_mode is MODE_RGBA by default here */
name|dec
operator|=
name|WebPAnimDecoderNew
argument_list|(
operator|&
name|wp_data
argument_list|,
operator|&
name|dec_options
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dec
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Failed to decode animated WebP file '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|error
goto|;
block|}
if|if
condition|(
operator|!
name|WebPAnimDecoderGetInfo
argument_list|(
name|dec
argument_list|,
operator|&
name|anim_info
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Failed to decode animated WebP information from '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|error
goto|;
block|}
comment|/* Attempt to decode the data as a WebP animation image */
while|while
condition|(
name|WebPAnimDecoderHasMoreFrames
argument_list|(
name|dec
argument_list|)
condition|)
block|{
name|uint8_t
modifier|*
name|outdata
decl_stmt|;
name|int
name|timestamp
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
if|if
condition|(
operator|!
name|WebPAnimDecoderGetNext
argument_list|(
name|dec
argument_list|,
operator|&
name|outdata
argument_list|,
operator|&
name|timestamp
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Failed to decode animated WebP frame from '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|error
goto|;
block|}
name|name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Frame %d"
argument_list|)
argument_list|,
name|frame_num
argument_list|)
expr_stmt|;
name|create_layer
argument_list|(
name|image_ID
argument_list|,
name|outdata
argument_list|,
literal|0
argument_list|,
name|name
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|frame_num
operator|++
expr_stmt|;
block|}
name|WebPAnimDecoderDelete
argument_list|(
name|dec
argument_list|)
expr_stmt|;
block|}
comment|/* Free the original compressed data */
name|g_free
argument_list|(
name|indata
argument_list|)
expr_stmt|;
if|if
condition|(
name|icc
condition|)
block|{
name|WebPData
name|icc_profile
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
decl_stmt|;
name|WebPMuxGetChunk
argument_list|(
name|mux
argument_list|,
literal|"ICCP"
argument_list|,
operator|&
name|icc_profile
argument_list|)
expr_stmt|;
name|profile
operator|=
name|gimp_color_profile_new_from_icc_profile
argument_list|(
name|icc_profile
operator|.
name|bytes
argument_list|,
name|icc_profile
operator|.
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
name|gimp_image_set_color_profile
argument_list|(
name|image_ID
argument_list|,
name|profile
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|exif
operator|||
name|xmp
condition|)
block|{
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
if|if
condition|(
name|exif
condition|)
block|{
name|WebPData
name|exif
decl_stmt|;
name|WebPMuxGetChunk
argument_list|(
name|mux
argument_list|,
literal|"EXIF"
argument_list|,
operator|&
name|exif
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|xmp
condition|)
block|{
name|WebPData
name|xmp
decl_stmt|;
name|WebPMuxGetChunk
argument_list|(
name|mux
argument_list|,
literal|"XMP "
argument_list|,
operator|&
name|xmp
argument_list|)
expr_stmt|;
block|}
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|metadata
operator|=
name|gimp_image_metadata_load_prepare
argument_list|(
name|image_ID
argument_list|,
literal|"image/webp"
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
name|gimp_image_metadata_load_finish
argument_list|(
name|image_ID
argument_list|,
literal|"image/webp"
argument_list|,
name|metadata
argument_list|,
name|GIMP_METADATA_LOAD_ALL
argument_list|,
name|interactive
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

end_unit

