begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/desaturate.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimpdesaturateconfig.h"
end_include

begin_comment
comment|/* temp */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-desaturate.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-operation.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-process.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_drawable_desaturate (GimpDrawable * drawable,GimpProgress * progress,GimpDesaturateMode mode)
name|gimp_drawable_desaturate
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpDesaturateMode
name|mode
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_use_gegl
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
operator|->
name|image
operator|->
name|gimp
argument_list|)
condition|)
block|{
name|GeglNode
modifier|*
name|desaturate
decl_stmt|;
name|GObject
modifier|*
name|config
decl_stmt|;
name|desaturate
operator|=
name|g_object_new
argument_list|(
name|GEGL_TYPE_NODE
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp-desaturate"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DESATURATE_CONFIG
argument_list|,
literal|"mode"
argument_list|,
name|mode
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|desaturate
argument_list|,
literal|"config"
argument_list|,
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_operation
argument_list|(
name|drawable
argument_list|,
name|desaturate
argument_list|,
name|TRUE
argument_list|,
name|progress
argument_list|,
name|_
argument_list|(
literal|"Desaturate"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|desaturate
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_process
argument_list|(
name|drawable
argument_list|,
name|progress
argument_list|,
name|_
argument_list|(
literal|"Desaturate"
argument_list|)
argument_list|,
operator|(
name|PixelProcessorFunc
operator|)
name|desaturate_region
argument_list|,
operator|&
name|mode
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

