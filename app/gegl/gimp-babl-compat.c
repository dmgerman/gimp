begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-babl-compat.h  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gimp-babl-compat.h"
end_include

begin_function
name|GimpImageType
DECL|function|gimp_babl_format_get_image_type (const Babl * format)
name|gimp_babl_format_get_image_type
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|name
operator|=
name|babl_get_name
argument_list|(
name|babl_format_get_model
argument_list|(
name|format
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"Y"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"Y'"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"Y~"
argument_list|)
condition|)
block|{
return|return
name|GIMP_GRAY_IMAGE
return|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"YA"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"Y'A"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"Y~A"
argument_list|)
condition|)
block|{
return|return
name|GIMP_GRAYA_IMAGE
return|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"RGB"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"R'G'B'"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"R~G~B~"
argument_list|)
condition|)
block|{
return|return
name|GIMP_RGB_IMAGE
return|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"RGBA"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"R'G'B'A"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"R~G~B~A"
argument_list|)
condition|)
block|{
return|return
name|GIMP_RGBA_IMAGE
return|;
block|}
elseif|else
if|if
condition|(
name|babl_format_is_palette
argument_list|(
name|format
argument_list|)
condition|)
block|{
if|if
condition|(
name|babl_format_has_alpha
argument_list|(
name|format
argument_list|)
condition|)
return|return
name|GIMP_INDEXEDA_IMAGE
return|;
else|else
return|return
name|GIMP_INDEXED_IMAGE
return|;
block|}
name|g_return_val_if_reached
argument_list|(
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_babl_compat_u8_format (const Babl * format)
name|gimp_babl_compat_u8_format
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  indexed images only exist in u8, return the same format  */
if|if
condition|(
name|babl_format_is_palette
argument_list|(
name|format
argument_list|)
condition|)
return|return
name|format
return|;
return|return
name|gimp_babl_format
argument_list|(
name|gimp_babl_format_get_base_type
argument_list|(
name|format
argument_list|)
argument_list|,
name|GIMP_PRECISION_U8_NON_LINEAR
argument_list|,
name|babl_format_has_alpha
argument_list|(
name|format
argument_list|)
argument_list|,
name|babl_format_get_space
argument_list|(
name|format
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_babl_compat_u8_mask_format (const Babl * format)
name|gimp_babl_compat_u8_mask_format
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_babl_format
argument_list|(
name|gimp_babl_format_get_base_type
argument_list|(
name|format
argument_list|)
argument_list|,
name|GIMP_PRECISION_U8_LINEAR
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

end_unit

