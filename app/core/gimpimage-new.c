begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-new.h"
end_include

begin_include
include|#
directive|include
file|"gimptemplate.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GimpTemplate
modifier|*
DECL|function|gimp_image_new_get_last_template (Gimp * gimp,GimpImage * gimage)
name|gimp_image_new_get_last_template
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimage
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_template_new
argument_list|(
literal|"image new values"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
name|gimp_template_set_from_image
argument_list|(
name|template
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
else|else
name|gimp_config_sync
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|image_new_last_template
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|global_buffer
operator|&&
name|gimp
operator|->
name|have_current_cut_buffer
condition|)
block|{
name|g_object_set
argument_list|(
name|template
argument_list|,
literal|"width"
argument_list|,
name|gimp_buffer_get_width
argument_list|(
name|gimp
operator|->
name|global_buffer
argument_list|)
argument_list|,
literal|"height"
argument_list|,
name|gimp_buffer_get_height
argument_list|(
name|gimp
operator|->
name|global_buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|template
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_new_set_last_template (Gimp * gimp,GimpTemplate * template)
name|gimp_image_new_set_last_template
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_sync
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|template
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|image_new_last_template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|have_current_cut_buffer
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

