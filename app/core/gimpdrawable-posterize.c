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
file|"base/gimplut.h"
end_include

begin_include
include|#
directive|include
file|"base/lut-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimpposterizeconfig.h"
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
file|"gimpdrawable-operation.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-posterize.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-process.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_posterize (GimpDrawable * drawable,GimpProgress * progress,gint levels)
name|gimp_drawable_posterize
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gint
name|levels
parameter_list|)
block|{
name|GimpPosterizeConfig
modifier|*
name|config
decl_stmt|;
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
operator|!
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
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
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_POSTERIZE_CONFIG
argument_list|,
literal|"levels"
argument_list|,
name|levels
argument_list|,
name|NULL
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
name|node
decl_stmt|;
name|node
operator|=
name|g_object_new
argument_list|(
name|GEGL_TYPE_NODE
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:posterize"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|node
argument_list|,
literal|"config"
argument_list|,
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_operation
argument_list|(
name|drawable
argument_list|,
name|progress
argument_list|,
name|_
argument_list|(
literal|"Posterize"
argument_list|)
argument_list|,
name|node
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|node
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|posterize_lut_new
argument_list|(
name|config
operator|->
name|levels
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_process_lut
argument_list|(
name|drawable
argument_list|,
name|progress
argument_list|,
name|_
argument_list|(
literal|"Posterize"
argument_list|)
argument_list|,
name|lut
argument_list|)
expr_stmt|;
name|gimp_lut_free
argument_list|(
name|lut
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

