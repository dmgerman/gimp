begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-babl-compat.h  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
if|if
condition|(
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y u16"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y float"
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
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"YA u16"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"YA float"
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
name|format
operator|==
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"RGB u16"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"RGB float"
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
name|format
operator|==
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"RGBA u16"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"RGBA float"
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

end_unit

