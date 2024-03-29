begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGrid  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-grid.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GimpGrid
modifier|*
DECL|function|gimp_image_get_grid (GimpImage * image)
name|gimp_image_get_grid
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|grid
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_set_grid (GimpImage * image,GimpGrid * grid,gboolean push_undo)
name|gimp_image_set_grid
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGrid
modifier|*
name|grid
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GRID
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_config_is_equal_to
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|private
operator|->
name|grid
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|grid
argument_list|)
argument_list|)
condition|)
return|return;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_image_grid
argument_list|(
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Grid"
argument_list|)
argument_list|,
name|private
operator|->
name|grid
argument_list|)
expr_stmt|;
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|private
operator|->
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

