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
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-equalize.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-histogram.h"
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
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_drawable_equalize (GimpDrawable * drawable,gboolean mask_only)
name|gimp_drawable_equalize
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|mask_only
parameter_list|)
block|{
name|GimpHistogram
modifier|*
name|hist
decl_stmt|;
name|GeglNode
modifier|*
name|equalize
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
name|hist
operator|=
name|gimp_histogram_new
argument_list|()
expr_stmt|;
name|gimp_drawable_calculate_histogram
argument_list|(
name|drawable
argument_list|,
name|hist
argument_list|)
expr_stmt|;
name|equalize
operator|=
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:equalize"
argument_list|,
literal|"histogram"
argument_list|,
name|hist
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_operation
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Equalize"
argument_list|)
argument_list|,
name|equalize
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|equalize
argument_list|)
expr_stmt|;
name|gimp_histogram_unref
argument_list|(
name|hist
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

