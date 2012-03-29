begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gegl/gimplevelsconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-histogram.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-levels.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-operation.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogram.h"
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_levels_stretch (GimpDrawable * drawable,GimpProgress * progress)
name|gimp_drawable_levels_stretch
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpLevelsConfig
modifier|*
name|config
decl_stmt|;
name|GimpHistogram
modifier|*
name|histogram
decl_stmt|;
name|GeglNode
modifier|*
name|levels
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
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
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
if|if
condition|(
operator|!
name|gimp_item_mask_intersect
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
return|return;
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_LEVELS_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|histogram
operator|=
name|gimp_histogram_new
argument_list|()
expr_stmt|;
name|gimp_drawable_calculate_histogram
argument_list|(
name|drawable
argument_list|,
name|histogram
argument_list|)
expr_stmt|;
name|gimp_levels_config_stretch
argument_list|(
name|config
argument_list|,
name|histogram
argument_list|,
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_histogram_unref
argument_list|(
name|histogram
argument_list|)
expr_stmt|;
name|levels
operator|=
name|g_object_new
argument_list|(
name|GEGL_TYPE_NODE
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:levels"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|levels
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
literal|"Levels"
argument_list|)
argument_list|,
name|levels
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|levels
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

