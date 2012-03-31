begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-nodes.h  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimp-gegl-nodes.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-utils.h"
end_include

begin_function
name|GeglNode
modifier|*
DECL|function|gimp_gegl_create_flatten_node (const GimpRGB * background)
name|gimp_gegl_create_flatten_node
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|background
parameter_list|)
block|{
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|GeglNode
modifier|*
name|input
decl_stmt|;
name|GeglNode
modifier|*
name|output
decl_stmt|;
name|GeglNode
modifier|*
name|color
decl_stmt|;
name|GeglNode
modifier|*
name|over
decl_stmt|;
name|GeglColor
modifier|*
name|c
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|background
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|node
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|input
operator|=
name|gegl_node_get_input_proxy
argument_list|(
name|node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|output
operator|=
name|gegl_node_get_output_proxy
argument_list|(
name|node
argument_list|,
literal|"output"
argument_list|)
expr_stmt|;
name|c
operator|=
name|gimp_gegl_color_new
argument_list|(
name|background
argument_list|)
expr_stmt|;
name|color
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:color"
argument_list|,
literal|"value"
argument_list|,
name|c
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|c
argument_list|)
expr_stmt|;
name|over
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:over"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|over
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|color
argument_list|,
literal|"output"
argument_list|,
name|over
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|over
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
return|return
name|node
return|;
block|}
end_function

begin_function
name|GeglNode
modifier|*
DECL|function|gimp_gegl_create_apply_opacity_node (GeglBuffer * mask,gint mask_offset_x,gint mask_offset_y,gdouble opacity)
name|gimp_gegl_create_apply_opacity_node
parameter_list|(
name|GeglBuffer
modifier|*
name|mask
parameter_list|,
name|gint
name|mask_offset_x
parameter_list|,
name|gint
name|mask_offset_y
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
block|{
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|GeglNode
modifier|*
name|input
decl_stmt|;
name|GeglNode
modifier|*
name|output
decl_stmt|;
name|GeglNode
modifier|*
name|opacity_node
decl_stmt|;
name|GeglNode
modifier|*
name|mask_source
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|mask
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|node
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|input
operator|=
name|gegl_node_get_input_proxy
argument_list|(
name|node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|output
operator|=
name|gegl_node_get_output_proxy
argument_list|(
name|node
argument_list|,
literal|"output"
argument_list|)
expr_stmt|;
name|opacity_node
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:opacity"
argument_list|,
literal|"value"
argument_list|,
name|opacity
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|mask_source
operator|=
name|gimp_gegl_add_buffer_source
argument_list|(
name|node
argument_list|,
name|mask
argument_list|,
name|mask_offset_x
argument_list|,
name|mask_offset_y
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|opacity_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|mask_source
argument_list|,
literal|"output"
argument_list|,
name|opacity_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|opacity_node
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
return|return
name|node
return|;
block|}
end_function

begin_function
name|GeglNode
modifier|*
DECL|function|gimp_gegl_create_apply_buffer_node (GeglBuffer * buffer,gint buffer_offset_x,gint buffer_offset_y,gint src_offset_x,gint src_offset_y,gint dest_offset_x,gint dest_offset_y,GeglBuffer * mask,gint mask_offset_x,gint mask_offset_y,gdouble opacity,GimpLayerModeEffects mode)
name|gimp_gegl_create_apply_buffer_node
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|buffer_offset_x
parameter_list|,
name|gint
name|buffer_offset_y
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|gint
name|dest_offset_x
parameter_list|,
name|gint
name|dest_offset_y
parameter_list|,
name|GeglBuffer
modifier|*
name|mask
parameter_list|,
name|gint
name|mask_offset_x
parameter_list|,
name|gint
name|mask_offset_y
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|)
block|{
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|GeglNode
modifier|*
name|input
decl_stmt|;
name|GeglNode
modifier|*
name|output
decl_stmt|;
name|GeglNode
modifier|*
name|buffer_source
decl_stmt|;
name|GeglNode
modifier|*
name|mask_source
decl_stmt|;
name|GeglNode
modifier|*
name|opacity_node
decl_stmt|;
name|GeglNode
modifier|*
name|mode_node
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|mask
operator|==
name|NULL
operator|||
name|GEGL_IS_BUFFER
argument_list|(
name|mask
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|node
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|buffer_source
operator|=
name|gimp_gegl_add_buffer_source
argument_list|(
name|node
argument_list|,
name|buffer
argument_list|,
name|buffer_offset_x
argument_list|,
name|buffer_offset_y
argument_list|)
expr_stmt|;
name|input
operator|=
name|gegl_node_get_input_proxy
argument_list|(
name|node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_offset_x
operator|!=
literal|0
operator|||
name|src_offset_y
operator|!=
literal|0
condition|)
block|{
name|GeglNode
modifier|*
name|translate
init|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:translate"
argument_list|,
literal|"x"
argument_list|,
operator|(
name|gdouble
operator|)
name|src_offset_x
argument_list|,
literal|"y"
argument_list|,
operator|(
name|gdouble
operator|)
name|src_offset_y
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|translate
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|input
operator|=
name|translate
expr_stmt|;
block|}
name|output
operator|=
name|gegl_node_get_output_proxy
argument_list|(
name|node
argument_list|,
literal|"output"
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_offset_x
operator|!=
literal|0
operator|||
name|dest_offset_y
operator|!=
literal|0
condition|)
block|{
name|GeglNode
modifier|*
name|translate
init|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:translate"
argument_list|,
literal|"x"
argument_list|,
operator|(
name|gdouble
operator|)
name|dest_offset_x
argument_list|,
literal|"y"
argument_list|,
operator|(
name|gdouble
operator|)
name|dest_offset_y
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gegl_node_connect_to
argument_list|(
name|translate
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|output
operator|=
name|translate
expr_stmt|;
block|}
if|if
condition|(
name|mask
condition|)
name|mask_source
operator|=
name|gimp_gegl_add_buffer_source
argument_list|(
name|node
argument_list|,
name|mask
argument_list|,
name|mask_offset_x
argument_list|,
name|mask_offset_y
argument_list|)
expr_stmt|;
else|else
name|mask_source
operator|=
name|NULL
expr_stmt|;
name|opacity_node
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:opacity"
argument_list|,
literal|"value"
argument_list|,
name|opacity
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|buffer_source
argument_list|,
literal|"output"
argument_list|,
name|opacity_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask_source
condition|)
name|gegl_node_connect_to
argument_list|(
name|mask_source
argument_list|,
literal|"output"
argument_list|,
name|opacity_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|mode_node
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"gegl:nop"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gegl_node_set_layer_mode
argument_list|(
name|node
argument_list|,
name|mode
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|opacity_node
argument_list|,
literal|"output"
argument_list|,
name|mode_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|mode_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|mode_node
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
return|return
name|node
return|;
block|}
end_function

begin_function
name|GeglNode
modifier|*
DECL|function|gimp_gegl_add_buffer_source (GeglNode * parent,GeglBuffer * buffer,gint offset_x,gint offset_y)
name|gimp_gegl_add_buffer_source
parameter_list|(
name|GeglNode
modifier|*
name|parent
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
block|{
name|GeglNode
modifier|*
name|buffer_source
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_NODE
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer_source
operator|=
name|gegl_node_new_child
argument_list|(
name|parent
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|offset_x
operator|!=
literal|0
operator|||
name|offset_y
operator|!=
literal|0
condition|)
block|{
name|GeglNode
modifier|*
name|translate
init|=
name|gegl_node_new_child
argument_list|(
name|parent
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:translate"
argument_list|,
literal|"x"
argument_list|,
operator|(
name|gdouble
operator|)
name|offset_x
argument_list|,
literal|"y"
argument_list|,
operator|(
name|gdouble
operator|)
name|offset_y
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gegl_node_connect_to
argument_list|(
name|buffer_source
argument_list|,
literal|"output"
argument_list|,
name|translate
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|buffer_source
operator|=
name|translate
expr_stmt|;
block|}
return|return
name|buffer_source
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_node_set_layer_mode (GeglNode * node,GimpLayerModeEffects mode,gboolean premultiplied)
name|gimp_gegl_node_set_layer_mode
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|,
name|gboolean
name|premultiplied
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|operation
init|=
literal|"gimp:normal-mode"
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_NODE
argument_list|(
name|node
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_BEHIND_MODE
case|:
case|case
name|GIMP_MULTIPLY_MODE
case|:
case|case
name|GIMP_SCREEN_MODE
case|:
case|case
name|GIMP_OVERLAY_MODE
case|:
case|case
name|GIMP_DIFFERENCE_MODE
case|:
case|case
name|GIMP_ADDITION_MODE
case|:
case|case
name|GIMP_SUBTRACT_MODE
case|:
case|case
name|GIMP_DARKEN_ONLY_MODE
case|:
case|case
name|GIMP_LIGHTEN_ONLY_MODE
case|:
case|case
name|GIMP_HUE_MODE
case|:
case|case
name|GIMP_SATURATION_MODE
case|:
case|case
name|GIMP_COLOR_MODE
case|:
case|case
name|GIMP_VALUE_MODE
case|:
case|case
name|GIMP_DIVIDE_MODE
case|:
case|case
name|GIMP_DODGE_MODE
case|:
case|case
name|GIMP_BURN_MODE
case|:
case|case
name|GIMP_HARDLIGHT_MODE
case|:
case|case
name|GIMP_SOFTLIGHT_MODE
case|:
case|case
name|GIMP_GRAIN_EXTRACT_MODE
case|:
case|case
name|GIMP_GRAIN_MERGE_MODE
case|:
case|case
name|GIMP_COLOR_ERASE_MODE
case|:
case|case
name|GIMP_ERASE_MODE
case|:
case|case
name|GIMP_REPLACE_MODE
case|:
case|case
name|GIMP_ANTI_ERASE_MODE
case|:
name|gegl_node_set
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:point-layer-mode"
argument_list|,
literal|"blend-mode"
argument_list|,
name|mode
argument_list|,
literal|"premultiplied"
argument_list|,
name|premultiplied
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return;
default|default:
break|break;
block|}
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_NORMAL_MODE
case|:
name|operation
operator|=
literal|"gimp:normal-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_DISSOLVE_MODE
case|:
name|operation
operator|=
literal|"gimp:dissolve-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_BEHIND_MODE
case|:
name|operation
operator|=
literal|"gimp:behind-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_MULTIPLY_MODE
case|:
name|operation
operator|=
literal|"gimp:multiply-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_SCREEN_MODE
case|:
name|operation
operator|=
literal|"gimp:screen-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_OVERLAY_MODE
case|:
name|operation
operator|=
literal|"gimp:overlay-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_DIFFERENCE_MODE
case|:
name|operation
operator|=
literal|"gimp:difference-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_ADDITION_MODE
case|:
name|operation
operator|=
literal|"gimp:addition-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_SUBTRACT_MODE
case|:
name|operation
operator|=
literal|"gimp:subtract-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_DARKEN_ONLY_MODE
case|:
name|operation
operator|=
literal|"gimp:darken-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_LIGHTEN_ONLY_MODE
case|:
name|operation
operator|=
literal|"gimp:lighten-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_HUE_MODE
case|:
name|operation
operator|=
literal|"gimp:hue-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_SATURATION_MODE
case|:
name|operation
operator|=
literal|"gimp:saturation-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_MODE
case|:
name|operation
operator|=
literal|"gimp:color-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_VALUE_MODE
case|:
name|operation
operator|=
literal|"gimp:value-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_DIVIDE_MODE
case|:
name|operation
operator|=
literal|"gimp:divide-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_DODGE_MODE
case|:
name|operation
operator|=
literal|"gimp:dodge-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_BURN_MODE
case|:
name|operation
operator|=
literal|"gimp:burn-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_HARDLIGHT_MODE
case|:
name|operation
operator|=
literal|"gimp:hardlight-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_SOFTLIGHT_MODE
case|:
name|operation
operator|=
literal|"gimp:softlight-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_GRAIN_EXTRACT_MODE
case|:
name|operation
operator|=
literal|"gimp:grain-extract-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_GRAIN_MERGE_MODE
case|:
name|operation
operator|=
literal|"gimp:grain-merge-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_ERASE_MODE
case|:
name|operation
operator|=
literal|"gimp:color-erase-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_ERASE_MODE
case|:
name|operation
operator|=
literal|"gimp:erase-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_REPLACE_MODE
case|:
name|operation
operator|=
literal|"gimp:replace-mode"
expr_stmt|;
break|break;
case|case
name|GIMP_ANTI_ERASE_MODE
case|:
name|operation
operator|=
literal|"gimp:anti-erase-mode"
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|gegl_node_set
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
name|operation
argument_list|,
literal|"premultiplied"
argument_list|,
name|premultiplied
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_node_set_matrix (GeglNode * node,const GimpMatrix3 * matrix)
name|gimp_gegl_node_set_matrix
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
name|gchar
modifier|*
name|matrix_string
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_NODE
argument_list|(
name|node
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|matrix_string
operator|=
name|gegl_matrix3_to_string
argument_list|(
operator|(
name|GeglMatrix3
operator|*
operator|)
name|matrix
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|node
argument_list|,
literal|"transform"
argument_list|,
name|matrix_string
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|matrix_string
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

