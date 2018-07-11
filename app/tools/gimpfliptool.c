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
file|"config/gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-transform.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpguide.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-pick-item.h"
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
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpcanvasitem.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-appearance.h"
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
name|gimp_flip_tool_button_press
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
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonPressType
name|press_type
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
name|gimp_flip_tool_oper_update
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
name|gboolean
name|proximity
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
name|void
name|gimp_flip_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_flip_tool_get_undo_desc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglBuffer
modifier|*
name|gimp_flip_tool_transform
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

begin_function_decl
specifier|static
name|GimpOrientationType
name|gimp_flip_tool_get_flip_type
parameter_list|(
name|GimpFlipTool
modifier|*
name|flip
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
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
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
name|GIMP_ICON_TOOL_FLIP
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
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
init|=
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpTransformToolClass
modifier|*
name|tr_class
init|=
name|GIMP_TRANSFORM_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_flip_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_flip_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_flip_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_flip_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_flip_tool_draw
expr_stmt|;
name|tr_class
operator|->
name|get_undo_desc
operator|=
name|gimp_flip_tool_get_undo_desc
expr_stmt|;
name|tr_class
operator|->
name|transform
operator|=
name|gimp_flip_tool_transform
expr_stmt|;
name|tr_class
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Flipping"
argument_list|)
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
name|flip_tool
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_flip_tool_button_press (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|gimp_flip_tool_button_press
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
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonPressType
name|press_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_transform_tool_transform
argument_list|(
name|tr_tool
argument_list|,
name|display
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
name|gimp_get_toggle_behavior_mask
argument_list|()
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
DECL|function|gimp_flip_tool_oper_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_flip_tool_oper_update
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
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFlipTool
modifier|*
name|flip
init|=
name|GIMP_FLIP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpFlipOptions
modifier|*
name|options
init|=
name|GIMP_FLIP_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp_display_shell_get_show_guides
argument_list|(
name|shell
argument_list|)
operator|&&
name|proximity
condition|)
block|{
name|gint
name|snap_distance
init|=
name|display
operator|->
name|config
operator|->
name|snap_distance
decl_stmt|;
name|guide
operator|=
name|gimp_image_pick_guide
argument_list|(
name|image
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|,
name|FUNSCALEX
argument_list|(
name|shell
argument_list|,
name|snap_distance
argument_list|)
argument_list|,
name|FUNSCALEY
argument_list|(
name|shell
argument_list|,
name|snap_distance
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|flip
operator|->
name|guide
operator|!=
name|guide
operator|||
operator|(
name|guide
operator|&&
operator|!
name|gimp_draw_tool_is_active
argument_list|(
name|draw_tool
argument_list|)
operator|)
condition|)
block|{
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_draw_tool_is_active
argument_list|(
name|draw_tool
argument_list|)
operator|&&
name|draw_tool
operator|->
name|display
operator|!=
name|display
condition|)
name|gimp_draw_tool_stop
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
name|flip
operator|->
name|guide
operator|=
name|guide
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_draw_tool_is_active
argument_list|(
name|draw_tool
argument_list|)
condition|)
name|gimp_draw_tool_start
argument_list|(
name|draw_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|options
operator|->
name|direction_frame
argument_list|,
name|guide
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|oper_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|proximity
argument_list|,
name|display
argument_list|)
expr_stmt|;
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
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpFlipTool
modifier|*
name|flip
init|=
name|GIMP_FLIP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_transform_tool_check_active_item
argument_list|(
name|tr_tool
argument_list|,
name|display
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|gimp_tool_control_get_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|)
argument_list|,
name|gimp_tool_control_get_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|)
argument_list|,
name|GIMP_CURSOR_MODIFIER_BAD
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_tool_control_set_toggled
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|gimp_flip_tool_get_flip_type
argument_list|(
name|flip
argument_list|)
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
name|void
DECL|function|gimp_flip_tool_draw (GimpDrawTool * draw_tool)
name|gimp_flip_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpFlipTool
modifier|*
name|flip
init|=
name|GIMP_FLIP_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|flip
operator|->
name|guide
condition|)
block|{
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
name|GimpGuideStyle
name|style
decl_stmt|;
name|style
operator|=
name|gimp_guide_get_style
argument_list|(
name|flip
operator|->
name|guide
argument_list|)
expr_stmt|;
name|item
operator|=
name|gimp_draw_tool_add_guide
argument_list|(
name|draw_tool
argument_list|,
name|gimp_guide_get_orientation
argument_list|(
name|flip
operator|->
name|guide
argument_list|)
argument_list|,
name|gimp_guide_get_position
argument_list|(
name|flip
operator|->
name|guide
argument_list|)
argument_list|,
name|style
argument_list|)
expr_stmt|;
name|gimp_canvas_item_set_highlight
argument_list|(
name|item
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_flip_tool_get_undo_desc (GimpTransformTool * tr_tool)
name|gimp_flip_tool_get_undo_desc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpFlipTool
modifier|*
name|flip
init|=
name|GIMP_FLIP_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|gimp_flip_tool_get_flip_type
argument_list|(
name|flip
argument_list|)
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
return|return
name|g_strdup
argument_list|(
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Flip horizontally"
argument_list|)
argument_list|)
return|;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
return|return
name|g_strdup
argument_list|(
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Flip vertically"
argument_list|)
argument_list|)
return|;
default|default:
comment|/* probably this is not actually reached today, but        * could be if someone defined FLIP_DIAGONAL, say...        */
return|return
name|g_strdup
argument_list|(
name|C_
argument_list|(
literal|"undo-desc"
argument_list|,
literal|"Flip"
argument_list|)
argument_list|)
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|GeglBuffer
modifier|*
DECL|function|gimp_flip_tool_transform (GimpTransformTool * tr_tool,GimpItem * active_item,GeglBuffer * orig_buffer,gint orig_offset_x,gint orig_offset_y,GimpColorProfile ** buffer_profile,gint * new_offset_x,gint * new_offset_y)
name|gimp_flip_tool_transform
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
name|GimpFlipTool
modifier|*
name|flip
init|=
name|GIMP_FLIP_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GimpFlipOptions
modifier|*
name|options
init|=
name|GIMP_FLIP_TOOL_GET_OPTIONS
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GimpTransformOptions
modifier|*
name|tr_options
init|=
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
argument_list|(
name|tr_tool
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
name|GimpOrientationType
name|flip_type
init|=
name|GIMP_ORIENTATION_UNKNOWN
decl_stmt|;
name|gdouble
name|axis
init|=
literal|0.0
decl_stmt|;
name|gboolean
name|clip_result
init|=
name|FALSE
decl_stmt|;
name|GeglBuffer
modifier|*
name|ret
init|=
name|NULL
decl_stmt|;
name|flip_type
operator|=
name|gimp_flip_tool_get_flip_type
argument_list|(
name|flip
argument_list|)
expr_stmt|;
if|if
condition|(
name|flip
operator|->
name|guide
condition|)
block|{
name|axis
operator|=
name|gimp_guide_get_position
argument_list|(
name|flip
operator|->
name|guide
argument_list|)
expr_stmt|;
block|}
else|else
block|{
switch|switch
condition|(
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
name|tr_tool
operator|->
name|x1
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|tr_tool
operator|->
name|x2
operator|-
name|tr_tool
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
name|tr_tool
operator|->
name|y1
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|tr_tool
operator|->
name|y2
operator|-
name|tr_tool
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
block|}
switch|switch
condition|(
name|tr_options
operator|->
name|clip
condition|)
block|{
case|case
name|GIMP_TRANSFORM_RESIZE_ADJUST
case|:
name|clip_result
operator|=
name|FALSE
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSFORM_RESIZE_CLIP
case|:
name|clip_result
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
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
name|clip_result
operator|=
name|TRUE
expr_stmt|;
name|ret
operator|=
name|gimp_drawable_transform_buffer_flip
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
name|flip_type
argument_list|,
name|axis
argument_list|,
name|clip_result
argument_list|,
name|buffer_profile
argument_list|,
name|new_offset_x
argument_list|,
name|new_offset_y
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  this happens for entire drawables, paths and layer groups  */
comment|/*  always clip layer masks so they keep their size        */
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|active_item
argument_list|)
condition|)
name|clip_result
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|gimp_item_get_linked
argument_list|(
name|active_item
argument_list|)
condition|)
block|{
name|gimp_item_linked_flip
argument_list|(
name|active_item
argument_list|,
name|context
argument_list|,
name|flip_type
argument_list|,
name|axis
argument_list|,
name|clip_result
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_item_flip
argument_list|(
name|active_item
argument_list|,
name|context
argument_list|,
name|flip_type
argument_list|,
name|axis
argument_list|,
name|clip_result
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|ret
return|;
block|}
end_function

begin_function
specifier|static
name|GimpOrientationType
DECL|function|gimp_flip_tool_get_flip_type (GimpFlipTool * flip)
name|gimp_flip_tool_get_flip_type
parameter_list|(
name|GimpFlipTool
modifier|*
name|flip
parameter_list|)
block|{
name|GimpFlipOptions
modifier|*
name|options
init|=
name|GIMP_FLIP_TOOL_GET_OPTIONS
argument_list|(
name|flip
argument_list|)
decl_stmt|;
if|if
condition|(
name|flip
operator|->
name|guide
condition|)
block|{
switch|switch
condition|(
name|gimp_guide_get_orientation
argument_list|(
name|flip
operator|->
name|guide
argument_list|)
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
return|return
name|GIMP_ORIENTATION_VERTICAL
return|;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
return|return
name|GIMP_ORIENTATION_HORIZONTAL
return|;
default|default:
return|return
name|gimp_guide_get_orientation
argument_list|(
name|flip
operator|->
name|guide
argument_list|)
return|;
block|}
block|}
else|else
block|{
return|return
name|options
operator|->
name|flip_type
return|;
block|}
block|}
end_function

end_unit

