begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes/gimp-layer-modes.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-edit.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilloptions.h"
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
DECL|function|gimp_drawable_edit_clear (GimpDrawable * drawable,GimpContext * context)
name|gimp_drawable_edit_clear
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpFillOptions
modifier|*
name|options
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|gimp_fill_options_new
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|gimp_fill_options_set_by_fill_type
argument_list|(
name|options
argument_list|,
name|context
argument_list|,
name|GIMP_FILL_TRANSPARENT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|gimp_fill_options_set_by_fill_type
argument_list|(
name|options
argument_list|,
name|context
argument_list|,
name|GIMP_FILL_BACKGROUND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_edit_fill
argument_list|(
name|drawable
argument_list|,
name|options
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Clear"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_edit_fill (GimpDrawable * drawable,GimpFillOptions * options,const gchar * undo_desc)
name|gimp_drawable_edit_fill
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
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
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
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
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
return|return;
comment|/*  nothing to do, but the fill succeeded  */
name|buffer
operator|=
name|gimp_fill_options_create_buffer
argument_list|(
name|options
argument_list|,
name|drawable
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|undo_desc
condition|)
name|undo_desc
operator|=
name|gimp_fill_options_get_undo_desc
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_buffer
argument_list|(
name|drawable
argument_list|,
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|undo_desc
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|,
name|GIMP_LAYER_COLOR_SPACE_AUTO
argument_list|,
name|GIMP_LAYER_COLOR_SPACE_AUTO
argument_list|,
name|gimp_layer_mode_get_paint_composite_mode
argument_list|(
name|gimp_context_get_paint_mode
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

