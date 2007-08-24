begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * jpeg-settings.c  * Copyright (C) 2007 RaphaÃ«l Quinet<raphael@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * Structure of the "jpeg-settings" parasite:  *       1 byte  - JPEG color space (JCS_YCbCr, JCS_GRAYSCALE, JCS_CMYK, ...)  *       1 byte  - quality (1..100 according to the IJG scale, or 0)  *       1 byte  - number of components (0..4)  *       1 byte  - number of quantization tables (0..4)  *   C * 2 bytes - sampling factors for each component (1..4)  * T * 128 bytes - quantization tables (only if different from IJG tables)  *  * Additional data following the quantization tables is currently  * ignored and can be used for future extensions.  *  * In order to improve the compatibility with future versions of the  * plug-in that may support more subsampling types ("subsmp"), the  * parasite contains the original subsampling for each component  * instead of saving only one byte containing the subsampling type as  * used by the jpeg plug-in.  The same applies to the other settings:  * for example, up to 4 quantization tables will be saved in the  * parasite even if the current code cannot restore more than 2 of  * them (4 tables may be needed by unusual JPEG color spaces such as  * JCS_CMYK or JCS_YCCK).  */
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
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<jpeglib.h>
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

begin_include
include|#
directive|include
file|"jpeg-quality.h"
end_include

begin_include
include|#
directive|include
file|"jpeg-settings.h"
end_include

begin_comment
comment|/**  * jpeg_detect_original_settings:  * @cinfo: a pointer to a JPEG decompressor info.  * @image_ID: the image to which the parasite should be attached.  *  * Analyze the image being decompressed (@cinfo) and extract the  * sampling factors, quantization tables and overall image quality.  * Store this information in a parasite and attach it to @image_ID.  *  * This function must be called after jpeg_read_header() so that  * @cinfo contains the quantization tables and the sampling factors  * for each component.  *  * Return Value: TRUE if a parasite has been attached to @image_ID.  */
end_comment

begin_function
name|gboolean
DECL|function|jpeg_detect_original_settings (struct jpeg_decompress_struct * cinfo,gint32 image_ID)
name|jpeg_detect_original_settings
parameter_list|(
name|struct
name|jpeg_decompress_struct
modifier|*
name|cinfo
parameter_list|,
name|gint32
name|image_ID
parameter_list|)
block|{
name|guint
name|parasite_size
decl_stmt|;
name|guchar
modifier|*
name|parasite_data
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|gint
name|quality
decl_stmt|;
name|gint
name|num_quant_tables
init|=
literal|0
decl_stmt|;
name|gint
name|t
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cinfo
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|cinfo
operator|->
name|jpeg_color_space
operator|==
name|JCS_UNKNOWN
operator|||
name|cinfo
operator|->
name|out_color_space
operator|==
name|JCS_UNKNOWN
condition|)
return|return
name|FALSE
return|;
name|quality
operator|=
name|jpeg_detect_quality
argument_list|(
name|cinfo
argument_list|)
expr_stmt|;
comment|/* no need to attach quantization tables if they are the ones from IJG */
if|if
condition|(
name|quality
operator|<=
literal|0
condition|)
block|{
for|for
control|(
name|t
operator|=
literal|0
init|;
name|t
operator|<
literal|4
condition|;
name|t
operator|++
control|)
if|if
condition|(
name|cinfo
operator|->
name|quant_tbl_ptrs
index|[
name|t
index|]
condition|)
name|num_quant_tables
operator|++
expr_stmt|;
block|}
name|parasite_size
operator|=
literal|4
operator|+
name|cinfo
operator|->
name|num_components
operator|*
literal|2
operator|+
name|num_quant_tables
operator|*
literal|128
expr_stmt|;
name|parasite_data
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|parasite_size
argument_list|)
expr_stmt|;
name|dest
operator|=
name|parasite_data
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|CLAMP0255
argument_list|(
name|cinfo
operator|->
name|jpeg_color_space
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|ABS
argument_list|(
name|quality
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|CLAMP0255
argument_list|(
name|cinfo
operator|->
name|num_components
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|num_quant_tables
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cinfo
operator|->
name|num_components
condition|;
name|i
operator|++
control|)
block|{
operator|*
name|dest
operator|++
operator|=
name|CLAMP0255
argument_list|(
name|cinfo
operator|->
name|comp_info
index|[
name|i
index|]
operator|.
name|h_samp_factor
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|CLAMP0255
argument_list|(
name|cinfo
operator|->
name|comp_info
index|[
name|i
index|]
operator|.
name|v_samp_factor
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|quality
operator|<=
literal|0
condition|)
block|{
for|for
control|(
name|t
operator|=
literal|0
init|;
name|t
operator|<
literal|4
condition|;
name|t
operator|++
control|)
if|if
condition|(
name|cinfo
operator|->
name|quant_tbl_ptrs
index|[
name|t
index|]
condition|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|DCTSIZE2
condition|;
name|i
operator|++
control|)
block|{
name|guint16
name|c
init|=
name|cinfo
operator|->
name|quant_tbl_ptrs
index|[
name|t
index|]
operator|->
name|quantval
index|[
name|i
index|]
decl_stmt|;
operator|*
name|dest
operator|++
operator|=
name|c
operator|/
literal|256
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|c
operator|&
literal|255
expr_stmt|;
block|}
block|}
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"jpeg-settings"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|parasite_size
argument_list|,
name|parasite_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|parasite_data
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
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
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * TODO: compare the JPEG color space found in the parasite with the  * GIMP color space of the drawable to be saved.  If one of them is  * grayscale and the other isn't, then the quality setting may be used  * but the subsampling parameters and quantization tables should be  * ignored.  The drawable_ID needs to be passed around because the  * color space of the drawable may be different from that of the image  * (e.g., when saving a mask or channel).  */
end_comment

begin_comment
comment|/**  * jpeg_restore_original_settings:  * @image_ID: the image that may contain original jpeg settings in a parasite.  * @quality: where to store the original jpeg quality.  * @subsmp: where to store the original subsampling type.  * @num_quant_tables: where to store the number of quantization tables found.  *  * Retrieve the original JPEG settings (quality, type of subsampling  * and number of quantization tables) from the parasite attached to  * @image_ID.  If the number of quantization tables is greater than  * zero, then these tables can be retrieved from the parasite by  * calling jpeg_restore_original_tables().  *  * Return Value: TRUE if a valid parasite was attached to the image  */
end_comment

begin_function
name|gboolean
DECL|function|jpeg_restore_original_settings (gint32 image_ID,gint * quality,gint * subsmp,gint * num_quant_tables)
name|jpeg_restore_original_settings
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|quality
parameter_list|,
name|gint
modifier|*
name|subsmp
parameter_list|,
name|gint
modifier|*
name|num_quant_tables
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|glong
name|src_size
decl_stmt|;
name|gint
name|color_space
decl_stmt|;
name|gint
name|q
decl_stmt|;
name|gint
name|num_components
decl_stmt|;
name|gint
name|num_tables
decl_stmt|;
name|guchar
name|h
index|[
literal|3
index|]
decl_stmt|;
name|guchar
name|v
index|[
literal|3
index|]
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|quality
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|subsmp
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|num_quant_tables
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_image_parasite_find
argument_list|(
name|image_ID
argument_list|,
literal|"jpeg-settings"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|src
operator|=
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|src_size
operator|=
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_size
operator|>=
literal|4
condition|)
block|{
name|color_space
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|q
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|num_components
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|num_tables
operator|=
operator|*
name|src
operator|++
expr_stmt|;
if|if
condition|(
name|src_size
operator|>=
operator|(
literal|4
operator|+
name|num_components
operator|*
literal|2
operator|+
name|num_tables
operator|*
literal|128
operator|)
operator|&&
name|q
operator|<=
literal|100
operator|&&
name|num_tables
operator|<=
literal|4
condition|)
block|{
operator|*
name|quality
operator|=
name|q
expr_stmt|;
comment|/* the current plug-in can only create grayscale or YCbCr JPEGs */
if|if
condition|(
name|color_space
operator|==
name|JCS_GRAYSCALE
operator|||
name|color_space
operator|==
name|JCS_YCbCr
condition|)
operator|*
name|num_quant_tables
operator|=
name|num_tables
expr_stmt|;
else|else
operator|*
name|num_quant_tables
operator|=
operator|-
literal|1
expr_stmt|;
comment|/* the current plug-in can only use subsampling for YCbCr (3) */
operator|*
name|subsmp
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|num_components
operator|==
literal|3
condition|)
block|{
name|h
index|[
literal|0
index|]
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|v
index|[
literal|0
index|]
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|h
index|[
literal|1
index|]
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|v
index|[
literal|1
index|]
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|h
index|[
literal|2
index|]
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|v
index|[
literal|2
index|]
operator|=
operator|*
name|src
operator|++
expr_stmt|;
if|if
condition|(
name|h
index|[
literal|1
index|]
operator|==
literal|1
operator|&&
name|v
index|[
literal|1
index|]
operator|==
literal|1
operator|&&
name|h
index|[
literal|2
index|]
operator|==
literal|1
operator|&&
name|v
index|[
literal|2
index|]
operator|==
literal|1
condition|)
block|{
if|if
condition|(
name|h
index|[
literal|0
index|]
operator|==
literal|1
operator|&&
name|v
index|[
literal|0
index|]
operator|==
literal|1
condition|)
operator|*
name|subsmp
operator|=
literal|2
expr_stmt|;
elseif|else
if|if
condition|(
name|h
index|[
literal|0
index|]
operator|==
literal|2
operator|&&
name|v
index|[
literal|0
index|]
operator|==
literal|1
condition|)
operator|*
name|subsmp
operator|=
literal|1
expr_stmt|;
elseif|else
if|if
condition|(
name|h
index|[
literal|0
index|]
operator|==
literal|1
operator|&&
name|v
index|[
literal|0
index|]
operator|==
literal|2
condition|)
operator|*
name|subsmp
operator|=
literal|3
expr_stmt|;
elseif|else
if|if
condition|(
name|h
index|[
literal|0
index|]
operator|==
literal|2
operator|&&
name|v
index|[
literal|0
index|]
operator|==
literal|2
condition|)
operator|*
name|subsmp
operator|=
literal|0
expr_stmt|;
block|}
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
operator|*
name|quality
operator|=
operator|-
literal|1
expr_stmt|;
operator|*
name|subsmp
operator|=
operator|-
literal|1
expr_stmt|;
operator|*
name|num_quant_tables
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * jpeg_restore_original_tables:  * @image_ID: the image that may contain original jpeg settings in a parasite.  * @num_quant_tables: the number of quantization tables to restore.  *  * Retrieve the original quantization tables from the parasite  * attached to @image_ID.  Each table is an array of coefficients that  * can be associated with a component of a JPEG image when saving it.  *  * An array of newly allocated tables is returned if @num_quant_tables  * matches the number of tables saved in the parasite.  These tables  * are returned as arrays of unsigned integers even if they will never  * use more than 16 bits (8 bits in most cases) because the IJG JPEG  * library expects arrays of unsigned integers.  When these tables are  * not needed anymore, the caller should free them using g_free().  If  * no parasite exists or if it cannot be used, this function returns  * NULL.  *  * Return Value: an array of quantization tables, or NULL.  */
end_comment

begin_function
name|guint
modifier|*
modifier|*
DECL|function|jpeg_restore_original_tables (gint32 image_ID,gint num_quant_tables)
name|jpeg_restore_original_tables
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|num_quant_tables
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|glong
name|src_size
decl_stmt|;
name|gint
name|num_components
decl_stmt|;
name|gint
name|num_tables
decl_stmt|;
name|guint
modifier|*
modifier|*
name|quant_tables
decl_stmt|;
name|gint
name|t
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|parasite
operator|=
name|gimp_image_parasite_find
argument_list|(
name|image_ID
argument_list|,
literal|"jpeg-settings"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|src_size
operator|=
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_size
operator|>=
literal|4
condition|)
block|{
name|src
operator|=
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|num_components
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
name|num_tables
operator|=
name|src
index|[
literal|3
index|]
expr_stmt|;
if|if
condition|(
name|src_size
operator|>=
operator|(
literal|4
operator|+
name|num_components
operator|*
literal|2
operator|+
name|num_tables
operator|*
literal|128
operator|)
operator|&&
name|num_tables
operator|==
name|num_quant_tables
condition|)
block|{
name|src
operator|+=
literal|4
operator|+
name|num_components
operator|*
literal|2
expr_stmt|;
name|quant_tables
operator|=
name|g_new
argument_list|(
name|guint
operator|*
argument_list|,
name|num_tables
argument_list|)
expr_stmt|;
for|for
control|(
name|t
operator|=
literal|0
init|;
name|t
operator|<
name|num_tables
condition|;
name|t
operator|++
control|)
block|{
name|quant_tables
index|[
name|t
index|]
operator|=
name|g_new
argument_list|(
name|guint
argument_list|,
literal|128
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
literal|64
condition|;
name|i
operator|++
control|)
block|{
name|guint
name|c
decl_stmt|;
name|c
operator|=
operator|*
name|src
operator|++
operator|*
literal|256
expr_stmt|;
name|c
operator|+=
operator|*
name|src
operator|++
expr_stmt|;
name|quant_tables
index|[
name|t
index|]
index|[
name|i
index|]
operator|=
name|c
expr_stmt|;
block|}
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|quant_tables
return|;
block|}
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * jpeg_swap_original_settings:  * @image_ID: the image that may contain original jpeg settings in a parasite.  *  * Swap the horizontal and vertical axis for the saved subsampling  * parameters and quantization tables.  This should be done if the  * image has been rotated by +90 or -90 degrees or if it has been  * mirrored along its diagonal.  */
end_comment

begin_function
name|void
DECL|function|jpeg_swap_original_settings (gint32 image_ID)
name|jpeg_swap_original_settings
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|glong
name|src_size
decl_stmt|;
name|gint
name|num_components
decl_stmt|;
name|gint
name|num_tables
decl_stmt|;
name|guchar
modifier|*
name|new_data
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|gint
name|t
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|j
decl_stmt|;
name|parasite
operator|=
name|gimp_image_parasite_find
argument_list|(
name|image_ID
argument_list|,
literal|"jpeg-settings"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|src_size
operator|=
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_size
operator|>=
literal|4
condition|)
block|{
name|src
operator|=
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|num_components
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
name|num_tables
operator|=
name|src
index|[
literal|3
index|]
expr_stmt|;
if|if
condition|(
name|src_size
operator|>=
operator|(
literal|4
operator|+
name|num_components
operator|*
literal|2
operator|+
name|num_tables
operator|*
literal|128
operator|)
condition|)
block|{
name|new_data
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|src_size
argument_list|)
expr_stmt|;
name|dest
operator|=
name|new_data
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_components
condition|;
name|i
operator|++
control|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|dest
operator|+=
literal|2
expr_stmt|;
name|src
operator|+=
literal|2
expr_stmt|;
block|}
for|for
control|(
name|t
operator|=
literal|0
init|;
name|t
operator|<
name|num_tables
condition|;
name|t
operator|++
control|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|8
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|8
condition|;
name|j
operator|++
control|)
block|{
name|dest
index|[
name|i
operator|*
literal|16
operator|+
name|j
operator|*
literal|2
index|]
operator|=
name|src
index|[
name|j
operator|*
literal|16
operator|+
name|i
operator|*
literal|2
index|]
expr_stmt|;
name|dest
index|[
name|i
operator|*
literal|16
operator|+
name|j
operator|*
literal|2
operator|+
literal|1
index|]
operator|=
name|src
index|[
name|j
operator|*
literal|16
operator|+
name|i
operator|*
literal|2
operator|+
literal|1
index|]
expr_stmt|;
block|}
block|}
name|dest
operator|+=
literal|128
expr_stmt|;
name|src
operator|+=
literal|128
expr_stmt|;
if|if
condition|(
name|src_size
operator|>
operator|(
literal|4
operator|+
name|num_components
operator|*
literal|2
operator|+
name|num_tables
operator|*
literal|128
operator|)
condition|)
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
name|src_size
operator|-
operator|(
literal|4
operator|+
name|num_components
operator|*
literal|2
operator|+
name|num_tables
operator|*
literal|128
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"jpeg-settings"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|src_size
argument_list|,
name|new_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|new_data
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image_ID
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

