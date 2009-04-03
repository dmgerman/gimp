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
file|<string.h>
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-transform.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
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
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpflipoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpfliptool.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_flip_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_flip_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TileManager
modifier|*
name|gimp_flip_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gboolean
name|mask_empty
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpFlipTool,gimp_flip_tool,GIMP_TYPE_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFlipTool
argument_list|,
argument|gimp_flip_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_flip_tool_parent_class
end_define

begin_function
name|void
name|gimp_flip_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_FLIP_TOOL
argument_list|,
name|GIMP_TYPE_FLIP_OPTIONS
argument_list|,
name|gimp_flip_options_gui
argument_list|,
name|GIMP_CONTEXT_BACKGROUND_MASK
argument_list|,
literal|"gimp-flip-tool"
argument_list|,
name|_
argument_list|(
literal|"Flip"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Flip Tool: "
literal|"Reverse the layer, selection or path horizontally or vertically"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Flip"
argument_list|)
argument_list|,
literal|"<shift>F"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_FLIP
argument_list|,
name|GIMP_STOCK_TOOL_FLIP
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_flip_tool_class_init (GimpFlipToolClass * klass)
name|gimp_flip_tool_class_init
parameter_list|(
name|GimpFlipToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpTransformToolClass
modifier|*
name|trans_class
init|=
name|GIMP_TRANSFORM_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_flip_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_flip_tool_cursor_update
expr_stmt|;
name|trans_class
operator|->
name|transform
operator|=
name|gimp_flip_tool_transform
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_flip_tool_init (GimpFlipTool * flip_tool)
name|gimp_flip_tool_init
parameter_list|(
name|GimpFlipTool
modifier|*
name|flip_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|flip_tool
argument_list|)
decl_stmt|;
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|flip_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_snap_to
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_precision
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_PRECISION_PIXEL_CENTER
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_MOUSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_toggle_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_MOUSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_FLIP_HORIZONTAL
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_toggle_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_FLIP_VERTICAL
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"command"
argument_list|,
literal|"Flip"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_flip_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_flip_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFlipOptions
modifier|*
name|options
init|=
name|GIMP_FLIP_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|key
operator|==
name|GDK_CONTROL_MASK
condition|)
block|{
switch|switch
condition|(
name|options
operator|->
name|flip_type
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"flip-type"
argument_list|,
name|GIMP_ORIENTATION_VERTICAL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"flip-type"
argument_list|,
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_flip_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_flip_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFlipOptions
modifier|*
name|options
init|=
name|GIMP_FLIP_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpCursorModifier
name|modifier
init|=
name|GIMP_CURSOR_MODIFIER_BAD
decl_stmt|;
if|if
condition|(
name|gimp_image_coords_in_active_pickable
argument_list|(
name|display
operator|->
name|image
argument_list|,
name|coords
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_NONE
expr_stmt|;
block|}
name|gimp_tool_control_set_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|modifier
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_toggle_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|modifier
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_toggled
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|options
operator|->
name|flip_type
operator|==
name|GIMP_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|TileManager
modifier|*
DECL|function|gimp_flip_tool_transform (GimpTransformTool * trans_tool,GimpItem * active_item,gboolean mask_empty,GimpDisplay * display)
name|gimp_flip_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|trans_tool
parameter_list|,
name|GimpItem
modifier|*
name|active_item
parameter_list|,
name|gboolean
name|mask_empty
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFlipOptions
modifier|*
name|options
init|=
name|GIMP_FLIP_TOOL_GET_OPTIONS
argument_list|(
name|trans_tool
argument_list|)
decl_stmt|;
name|GimpTransformOptions
modifier|*
name|tr_options
init|=
name|GIMP_TRANSFORM_OPTIONS
argument_list|(
name|options
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
name|gdouble
name|axis
init|=
literal|0.0
decl_stmt|;
name|TileManager
modifier|*
name|ret
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|options
operator|->
name|flip_type
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|axis
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|trans_tool
operator|->
name|x1
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|trans_tool
operator|->
name|x2
operator|-
name|trans_tool
operator|->
name|x1
argument_list|)
operator|/
literal|2.0
operator|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|axis
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|trans_tool
operator|->
name|y1
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|trans_tool
operator|->
name|y2
operator|-
name|trans_tool
operator|->
name|y1
argument_list|)
operator|/
literal|2.0
operator|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|gimp_item_get_linked
argument_list|(
name|active_item
argument_list|)
condition|)
name|gimp_item_linked_flip
argument_list|(
name|active_item
argument_list|,
name|context
argument_list|,
name|options
operator|->
name|flip_type
argument_list|,
name|axis
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|active_item
argument_list|)
operator|&&
name|gimp_layer_get_mask
argument_list|(
name|GIMP_LAYER
argument_list|(
name|active_item
argument_list|)
argument_list|)
operator|&&
name|mask_empty
condition|)
block|{
name|GimpLayerMask
modifier|*
name|mask
init|=
name|gimp_layer_get_mask
argument_list|(
name|GIMP_LAYER
argument_list|(
name|active_item
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_item_flip
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|,
name|context
argument_list|,
name|options
operator|->
name|flip_type
argument_list|,
name|axis
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
switch|switch
condition|(
name|tr_options
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_TRANSFORM_TYPE_LAYER
case|:
case|case
name|GIMP_TRANSFORM_TYPE_SELECTION
case|:
if|if
condition|(
name|trans_tool
operator|->
name|original
condition|)
name|ret
operator|=
name|gimp_drawable_transform_tiles_flip
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|active_item
argument_list|)
argument_list|,
name|context
argument_list|,
name|trans_tool
operator|->
name|original
argument_list|,
name|options
operator|->
name|flip_type
argument_list|,
name|axis
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_PATH
case|:
name|gimp_item_flip
argument_list|(
name|active_item
argument_list|,
name|context
argument_list|,
name|options
operator|->
name|flip_type
argument_list|,
name|axis
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|ret
return|;
block|}
end_function

end_unit

