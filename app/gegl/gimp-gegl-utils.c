begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-utils.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimp-gegl-utils.h"
end_include

begin_comment
comment|/**  * gimp_bpp_to_babl_format:  * @bpp: bytes per pixel  * @linear: whether the pixels are linear or gamma-corrected.  *  * Return the Babl format to use for a given number of bytes per pixel.  * This function assumes that the data is 8bit.  *  * Return value: the Babl format to use  **/
end_comment

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_bpp_to_babl_format (guint bpp,gboolean linear)
name|gimp_bpp_to_babl_format
parameter_list|(
name|guint
name|bpp
parameter_list|,
name|gboolean
name|linear
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|bpp
operator|>
literal|0
operator|&&
name|bpp
operator|<=
literal|4
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|linear
condition|)
block|{
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
return|return
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
return|;
case|case
literal|2
case|:
return|return
name|babl_format
argument_list|(
literal|"YA u8"
argument_list|)
return|;
case|case
literal|3
case|:
return|return
name|babl_format
argument_list|(
literal|"RGB u8"
argument_list|)
return|;
case|case
literal|4
case|:
return|return
name|babl_format
argument_list|(
literal|"RGBA u8"
argument_list|)
return|;
block|}
block|}
else|else
block|{
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
return|return
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
return|;
case|case
literal|2
case|:
return|return
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
return|;
case|case
literal|3
case|:
return|return
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
return|;
case|case
literal|4
case|:
return|return
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

