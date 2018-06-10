begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-transform.h"
end_include

begin_include
include|#
directive|include
file|"core/gimperror.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem-linked.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimptransformoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptransformtool.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|GeglBuffer
modifier|*
name|gimp_transform_tool_real_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GeglBuffer
modifier|*
name|orig_buffer
parameter_list|,
name|gint
name|orig_offset_x
parameter_list|,
name|gint
name|orig_offset_y
parameter_list|,
name|GimpColorProfile
modifier|*
modifier|*
name|buffer_profile
parameter_list|,
name|gint
modifier|*
name|new_offset_x
parameter_list|,
name|gint
modifier|*
name|new_offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTransformTool,gimp_transform_tool,GIMP_TYPE_DRAW_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTransformTool
argument_list|,
argument|gimp_transform_tool
argument_list|,
argument|GIMP_TYPE_DRAW_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_transform_tool_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_transform_tool_class_init
parameter_list|(
name|GimpTransformToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|klass
operator|->
name|recalc_matrix
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|get_undo_desc
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|transform
operator|=
name|gimp_transform_tool_real_transform
expr_stmt|;
name|klass
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Transforming"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_tool_init (GimpTransformTool * tr_tool)
name|gimp_transform_tool_init
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|gimp_matrix3_identity
argument_list|(
operator|&
name|tr_tool
operator|->
name|transform
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|transform_valid
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GeglBuffer
modifier|*
DECL|function|gimp_transform_tool_real_transform (GimpTransformTool * tr_tool,GimpItem * active_item,GeglBuffer * orig_buffer,gint orig_offset_x,gint orig_offset_y,GimpColorProfile ** buffer_profile,gint * new_offset_x,gint * new_offset_y)
name|gimp_transform_tool_real_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpItem
modifier|*
name|active_item
parameter_list|,
name|GeglBuffer
modifier|*
name|orig_buffer
parameter_list|,
name|gint
name|orig_offset_x
parameter_list|,
name|gint
name|orig_offset_y
parameter_list|,
name|GimpColorProfile
modifier|*
modifier|*
name|buffer_profile
parameter_list|,
name|gint
modifier|*
name|new_offset_x
parameter_list|,
name|gint
modifier|*
name|new_offset_y
parameter_list|)
block|{
name|GimpTransformToolClass
modifier|*
name|klass
init|=
name|GIMP_TRANSFORM_TOOL_GET_CLASS
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GimpTransformOptions
modifier|*
name|options
init|=
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|ret
init|=
name|NULL
decl_stmt|;
name|GimpTransformResize
name|clip
init|=
name|options
operator|->
name|clip
decl_stmt|;
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|tool
argument_list|)
argument_list|,
name|FALSE
argument_list|,
literal|"%s"
argument_list|,
name|klass
operator|->
name|progress_text
argument_list|)
expr_stmt|;
if|if
condition|(
name|orig_buffer
condition|)
block|{
comment|/*  this happens when transforming a selection cut out of a        *  normal drawable, or the selection        */
comment|/*  always clip the selection and unfloated channels        *  so they keep their size        */
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|active_item
argument_list|)
operator|&&
operator|!
name|babl_format_has_alpha
argument_list|(
name|gegl_buffer_get_format
argument_list|(
name|orig_buffer
argument_list|)
argument_list|)
condition|)
name|clip
operator|=
name|GIMP_TRANSFORM_RESIZE_CLIP
expr_stmt|;
name|ret
operator|=
name|gimp_drawable_transform_buffer_affine
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|active_item
argument_list|)
argument_list|,
name|context
argument_list|,
name|orig_buffer
argument_list|,
name|orig_offset_x
argument_list|,
name|orig_offset_y
argument_list|,
operator|&
name|tr_tool
operator|->
name|transform
argument_list|,
name|options
operator|->
name|direction
argument_list|,
name|options
operator|->
name|interpolation
argument_list|,
name|clip
argument_list|,
name|buffer_profile
argument_list|,
name|new_offset_x
argument_list|,
name|new_offset_y
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  this happens for entire drawables, paths and layer groups  */
if|if
condition|(
name|gimp_item_get_linked
argument_list|(
name|active_item
argument_list|)
condition|)
block|{
name|gimp_item_linked_transform
argument_list|(
name|active_item
argument_list|,
name|context
argument_list|,
operator|&
name|tr_tool
operator|->
name|transform
argument_list|,
name|options
operator|->
name|direction
argument_list|,
name|options
operator|->
name|interpolation
argument_list|,
name|clip
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  always clip layer masks so they keep their size            */
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|active_item
argument_list|)
condition|)
name|clip
operator|=
name|GIMP_TRANSFORM_RESIZE_CLIP
expr_stmt|;
name|gimp_item_transform
argument_list|(
name|active_item
argument_list|,
name|context
argument_list|,
operator|&
name|tr_tool
operator|->
name|transform
argument_list|,
name|options
operator|->
name|direction
argument_list|,
name|options
operator|->
name|interpolation
argument_list|,
name|clip
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_transform_tool_bounds (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_transform_tool_bounds
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTransformOptions
modifier|*
name|options
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gboolean
name|non_empty
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TRANSFORM_TOOL
argument_list|(
name|tr_tool
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_TRANSFORM_TYPE_LAYER
case|:
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|non_empty
operator|=
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
expr_stmt|;
name|tr_tool
operator|->
name|x1
operator|=
name|x
operator|+
name|offset_x
expr_stmt|;
name|tr_tool
operator|->
name|y1
operator|=
name|y
operator|+
name|offset_y
expr_stmt|;
name|tr_tool
operator|->
name|x2
operator|=
name|x
operator|+
name|width
operator|+
name|offset_x
expr_stmt|;
name|tr_tool
operator|->
name|y2
operator|=
name|y
operator|+
name|height
operator|+
name|offset_y
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_SELECTION
case|:
block|{
name|gimp_item_bounds
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|,
operator|&
name|tr_tool
operator|->
name|x1
argument_list|,
operator|&
name|tr_tool
operator|->
name|y1
argument_list|,
operator|&
name|tr_tool
operator|->
name|x2
argument_list|,
operator|&
name|tr_tool
operator|->
name|y2
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|x2
operator|+=
name|tr_tool
operator|->
name|x1
expr_stmt|;
name|tr_tool
operator|->
name|y2
operator|+=
name|tr_tool
operator|->
name|y1
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_PATH
case|:
block|{
name|GimpChannel
modifier|*
name|selection
init|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
decl_stmt|;
comment|/* if selection is not empty, use its bounds to perform the          * transformation of the path          */
if|if
condition|(
operator|!
name|gimp_channel_is_empty
argument_list|(
name|selection
argument_list|)
condition|)
block|{
name|gimp_item_bounds
argument_list|(
name|GIMP_ITEM
argument_list|(
name|selection
argument_list|)
argument_list|,
operator|&
name|tr_tool
operator|->
name|x1
argument_list|,
operator|&
name|tr_tool
operator|->
name|y1
argument_list|,
operator|&
name|tr_tool
operator|->
name|x2
argument_list|,
operator|&
name|tr_tool
operator|->
name|y2
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* without selection, test the emptiness of the path bounds :              * if empty, use the canvas bounds              * else use the path bounds              */
if|if
condition|(
operator|!
name|gimp_item_bounds
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|,
operator|&
name|tr_tool
operator|->
name|x1
argument_list|,
operator|&
name|tr_tool
operator|->
name|y1
argument_list|,
operator|&
name|tr_tool
operator|->
name|x2
argument_list|,
operator|&
name|tr_tool
operator|->
name|y2
argument_list|)
condition|)
block|{
name|tr_tool
operator|->
name|x1
operator|=
literal|0
expr_stmt|;
name|tr_tool
operator|->
name|y1
operator|=
literal|0
expr_stmt|;
name|tr_tool
operator|->
name|x2
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|y2
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
name|tr_tool
operator|->
name|x2
operator|+=
name|tr_tool
operator|->
name|x1
expr_stmt|;
name|tr_tool
operator|->
name|y2
operator|+=
name|tr_tool
operator|->
name|y1
expr_stmt|;
block|}
break|break;
block|}
return|return
name|non_empty
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_tool_recalc_matrix (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_transform_tool_recalc_matrix
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TRANSFORM_TOOL
argument_list|(
name|tr_tool
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_transform_tool_bounds
argument_list|(
name|tr_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TRANSFORM_TOOL_GET_CLASS
argument_list|(
name|tr_tool
argument_list|)
operator|->
name|recalc_matrix
condition|)
name|GIMP_TRANSFORM_TOOL_GET_CLASS
argument_list|(
name|tr_tool
argument_list|)
operator|->
name|recalc_matrix
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_transform_tool_get_active_item (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_transform_tool_get_active_item
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTransformOptions
modifier|*
name|options
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpItem
modifier|*
name|item
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TRANSFORM_TOOL
argument_list|(
name|tr_tool
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
expr_stmt|;
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
switch|switch
condition|(
name|options
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_TRANSFORM_TYPE_LAYER
case|:
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_SELECTION
case|:
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_channel_is_empty
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|item
argument_list|)
argument_list|)
condition|)
name|item
operator|=
name|NULL
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_PATH
case|:
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|item
return|;
block|}
end_function

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_transform_tool_check_active_item (GimpTransformTool * tr_tool,GimpDisplay * display,GError ** error)
name|gimp_transform_tool_check_active_item
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpTransformOptions
modifier|*
name|options
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|null_message
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|locked_message
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TRANSFORM_TOOL
argument_list|(
name|tr_tool
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
name|item
operator|=
name|gimp_transform_tool_get_active_item
argument_list|(
name|tr_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_TRANSFORM_TYPE_LAYER
case|:
name|null_message
operator|=
name|_
argument_list|(
literal|"There is no layer to transform."
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
condition|)
block|{
if|if
condition|(
name|gimp_item_is_content_locked
argument_list|(
name|item
argument_list|)
condition|)
name|locked_message
operator|=
name|_
argument_list|(
literal|"The active layer's pixels are locked."
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|gimp_item_is_position_locked
argument_list|(
name|item
argument_list|)
condition|)
name|locked_message
operator|=
name|_
argument_list|(
literal|"The active layer's position and size are locked."
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_is_visible
argument_list|(
name|item
argument_list|)
operator|&&
name|GIMP_DRAWABLE
argument_list|(
name|item
argument_list|)
operator|!=
name|tr_tool
operator|->
name|drawable
condition|)
comment|/* see bug #759194 */
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"The active layer is not visible."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
operator|!
name|gimp_transform_tool_bounds
argument_list|(
name|tr_tool
argument_list|,
name|display
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"The selection does not intersect with the layer."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_SELECTION
case|:
name|null_message
operator|=
name|_
argument_list|(
literal|"There is no selection to transform."
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
condition|)
block|{
comment|/* cannot happen, so don't translate these messages */
if|if
condition|(
name|gimp_item_is_content_locked
argument_list|(
name|item
argument_list|)
condition|)
name|locked_message
operator|=
literal|"The selection's pixels are locked."
expr_stmt|;
elseif|else
if|if
condition|(
name|gimp_item_is_position_locked
argument_list|(
name|item
argument_list|)
condition|)
name|locked_message
operator|=
literal|"The selection's position and size are locked."
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_PATH
case|:
name|null_message
operator|=
name|_
argument_list|(
literal|"There is no path to transform."
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
condition|)
block|{
if|if
condition|(
name|gimp_item_is_content_locked
argument_list|(
name|item
argument_list|)
condition|)
name|locked_message
operator|=
name|_
argument_list|(
literal|"The active path's strokes are locked."
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|gimp_item_is_position_locked
argument_list|(
name|item
argument_list|)
condition|)
name|locked_message
operator|=
name|_
argument_list|(
literal|"The active path's position is locked."
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|gimp_vectors_get_n_strokes
argument_list|(
name|GIMP_VECTORS
argument_list|(
name|item
argument_list|)
argument_list|)
condition|)
name|locked_message
operator|=
name|_
argument_list|(
literal|"The active path has no strokes."
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
if|if
condition|(
operator|!
name|item
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|null_message
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|locked_message
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|locked_message
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|item
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_transform_tool_transform (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_transform_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpTransformOptions
modifier|*
name|options
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpItem
modifier|*
name|active_item
decl_stmt|;
name|GeglBuffer
modifier|*
name|orig_buffer
init|=
name|NULL
decl_stmt|;
name|gint
name|orig_offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|orig_offset_y
init|=
literal|0
decl_stmt|;
name|GeglBuffer
modifier|*
name|new_buffer
decl_stmt|;
name|gint
name|new_offset_x
decl_stmt|;
name|gint
name|new_offset_y
decl_stmt|;
name|GimpColorProfile
modifier|*
name|buffer_profile
decl_stmt|;
name|gchar
modifier|*
name|undo_desc
init|=
name|NULL
decl_stmt|;
name|gboolean
name|new_layer
init|=
name|FALSE
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TRANSFORM_TOOL
argument_list|(
name|tr_tool
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|active_item
operator|=
name|gimp_transform_tool_check_active_item
argument_list|(
name|tr_tool
argument_list|,
name|display
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|active_item
condition|)
block|{
name|gimp_tool_message_literal
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_transform_tool_recalc_matrix
argument_list|(
name|tr_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tr_tool
operator|->
name|transform_valid
condition|)
block|{
name|gimp_tool_message_literal
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|_
argument_list|(
literal|"The current transform is invalid"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|GIMP_TRANSFORM_TOOL_GET_CLASS
argument_list|(
name|tr_tool
argument_list|)
operator|->
name|recalc_matrix
operator|&&
name|gimp_matrix3_is_identity
argument_list|(
operator|&
name|tr_tool
operator|->
name|transform
argument_list|)
condition|)
block|{
comment|/* No need to commit an identity transformation! */
return|return
name|TRUE
return|;
block|}
name|gimp_set_busy
argument_list|(
name|display
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/*  We're going to dirty this image, but we want to keep the tool around  */
name|gimp_tool_control_push_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|undo_desc
operator|=
name|GIMP_TRANSFORM_TOOL_GET_CLASS
argument_list|(
name|tr_tool
argument_list|)
operator|->
name|get_undo_desc
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_TRANSFORM
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|undo_desc
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_TRANSFORM_TYPE_LAYER
case|:
if|if
condition|(
operator|!
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|tool
operator|->
name|drawable
argument_list|)
argument_list|)
operator|&&
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
condition|)
block|{
name|orig_buffer
operator|=
name|gimp_drawable_transform_cut
argument_list|(
name|tool
operator|->
name|drawable
argument_list|,
name|context
argument_list|,
operator|&
name|orig_offset_x
argument_list|,
operator|&
name|orig_offset_y
argument_list|,
operator|&
name|new_layer
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_SELECTION
case|:
name|orig_buffer
operator|=
name|g_object_ref
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|active_item
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_PATH
case|:
break|break;
block|}
comment|/*  Send the request for the transformation to the tool...    */
name|new_buffer
operator|=
name|GIMP_TRANSFORM_TOOL_GET_CLASS
argument_list|(
name|tr_tool
argument_list|)
operator|->
name|transform
argument_list|(
name|tr_tool
argument_list|,
name|active_item
argument_list|,
name|orig_buffer
argument_list|,
name|orig_offset_x
argument_list|,
name|orig_offset_y
argument_list|,
operator|&
name|buffer_profile
argument_list|,
operator|&
name|new_offset_x
argument_list|,
operator|&
name|new_offset_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|orig_buffer
condition|)
name|g_object_unref
argument_list|(
name|orig_buffer
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_TRANSFORM_TYPE_LAYER
case|:
if|if
condition|(
name|new_buffer
condition|)
block|{
comment|/*  paste the new transformed image to the image...also implement            *  undo...            */
name|gimp_drawable_transform_paste
argument_list|(
name|tool
operator|->
name|drawable
argument_list|,
name|new_buffer
argument_list|,
name|buffer_profile
argument_list|,
name|new_offset_x
argument_list|,
name|new_offset_y
argument_list|,
name|new_layer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_buffer
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_SELECTION
case|:
if|if
condition|(
name|new_buffer
condition|)
block|{
name|gimp_channel_push_undo
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|active_item
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_set_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|active_item
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|new_buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_buffer
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_PATH
case|:
comment|/*  Nothing to be done  */
break|break;
block|}
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/*  We're done dirtying the image, and would like to be restarted if    *  the image gets dirty while the tool exists    */
name|gimp_tool_control_pop_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|display
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

