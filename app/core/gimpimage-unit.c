begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattisbvf  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-unit.h"
end_include

begin_include
include|#
directive|include
file|"gimpunit.h"
end_include

begin_function
name|gdouble
DECL|function|gimp_image_unit_get_factor (GimpImage * gimage)
name|gimp_image_unit_get_factor
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
return|return
name|_gimp_unit_get_factor
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|gimage
operator|->
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_image_unit_get_digits (GimpImage * gimage)
name|gimp_image_unit_get_digits
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
return|return
name|_gimp_unit_get_digits
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|gimage
operator|->
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_image_unit_get_identifier (GimpImage * gimage)
name|gimp_image_unit_get_identifier
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
return|return
name|_gimp_unit_get_identifier
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|gimage
operator|->
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_image_unit_get_symbol (GimpImage * gimage)
name|gimp_image_unit_get_symbol
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
return|return
name|_gimp_unit_get_symbol
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|gimage
operator|->
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_image_unit_get_abbreviation (GimpImage * gimage)
name|gimp_image_unit_get_abbreviation
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
return|return
name|_gimp_unit_get_abbreviation
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|gimage
operator|->
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_image_unit_get_singular (GimpImage * gimage)
name|gimp_image_unit_get_singular
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
return|return
name|_gimp_unit_get_singular
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|gimage
operator|->
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_image_unit_get_plural (GimpImage * gimage)
name|gimp_image_unit_get_plural
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
return|return
name|_gimp_unit_get_plural
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|gimage
operator|->
name|unit
argument_list|)
return|;
block|}
end_function

end_unit

