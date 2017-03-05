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
file|"libgimpmath/gimpmath.h"
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
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-cairo.h"
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
file|"core/gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-pick-layer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer-floating-selection.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpundostack.h"
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
file|"display/gimpdisplayshell-selection.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimpeditselectiontool.h"
end_include

begin_include
include|#
directive|include
file|"gimpguidetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpmoveoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpmovetool.h"
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
name|gimp_move_tool_button_press
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
name|gimp_move_tool_button_release
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
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_move_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
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
name|gimp_move_tool_modifier_key
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
name|gimp_move_tool_oper_update
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
name|gimp_move_tool_cursor_update
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
name|gimp_move_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpMoveTool,gimp_move_tool,GIMP_TYPE_DRAW_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMoveTool
argument_list|,
argument|gimp_move_tool
argument_list|,
argument|GIMP_TYPE_DRAW_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_move_tool_parent_class
end_define

begin_function
name|void
name|gimp_move_tool_register
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
name|GIMP_TYPE_MOVE_TOOL
argument_list|,
name|GIMP_TYPE_MOVE_OPTIONS
argument_list|,
name|gimp_move_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-move-tool"
argument_list|,
name|C_
argument_list|(
literal|"tool"
argument_list|,
literal|"Move"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Move Tool: Move layers, selections, and other objects"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Move"
argument_list|)
argument_list|,
literal|"M"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_MOVE
argument_list|,
name|GIMP_ICON_TOOL_MOVE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_class_init (GimpMoveToolClass * klass)
name|gimp_move_tool_class_init
parameter_list|(
name|GimpMoveToolClass
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
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_move_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_move_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|key_press
operator|=
name|gimp_move_tool_key_press
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_move_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_move_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_move_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_move_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_init (GimpMoveTool * move_tool)
name|gimp_move_tool_init
parameter_list|(
name|GimpMoveTool
modifier|*
name|move_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|move_tool
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
name|gimp_tool_control_set_handle_empty_image
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_MOVE
argument_list|)
expr_stmt|;
name|move_tool
operator|->
name|floating_layer
operator|=
name|NULL
expr_stmt|;
name|move_tool
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
name|move_tool
operator|->
name|saved_type
operator|=
name|GIMP_TRANSFORM_TYPE_LAYER
expr_stmt|;
name|move_tool
operator|->
name|old_active_layer
operator|=
name|NULL
expr_stmt|;
name|move_tool
operator|->
name|old_active_vectors
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_button_press (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|gimp_move_tool_button_press
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
name|GimpMoveTool
modifier|*
name|move
init|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpMoveOptions
modifier|*
name|options
init|=
name|GIMP_MOVE_TOOL_GET_OPTIONS
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
name|GimpItem
modifier|*
name|active_item
init|=
name|NULL
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
name|tool
operator|->
name|display
operator|=
name|display
expr_stmt|;
name|move
operator|->
name|floating_layer
operator|=
name|NULL
expr_stmt|;
name|move
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|options
operator|->
name|move_current
condition|)
block|{
if|if
condition|(
name|options
operator|->
name|move_type
operator|==
name|GIMP_TRANSFORM_TYPE_PATH
condition|)
block|{
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
if|if
condition|(
name|gimp_draw_tool_on_vectors
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|display
argument_list|,
name|coords
argument_list|,
literal|7
argument_list|,
literal|7
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|vectors
argument_list|)
condition|)
block|{
name|move
operator|->
name|old_active_vectors
operator|=
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_set_active_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  no path picked  */
return|return;
block|}
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|move_type
operator|==
name|GIMP_TRANSFORM_TYPE_LAYER
condition|)
block|{
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
specifier|const
name|gint
name|snap_distance
init|=
name|display
operator|->
name|config
operator|->
name|snap_distance
decl_stmt|;
if|if
condition|(
name|gimp_display_shell_get_show_guides
argument_list|(
name|shell
argument_list|)
operator|&&
operator|(
name|guide
operator|=
name|gimp_image_find_guide
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
operator|)
condition|)
block|{
name|move
operator|->
name|guide
operator|=
name|guide
expr_stmt|;
name|gimp_guide_tool_start_edit
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|guide
argument_list|)
expr_stmt|;
return|return;
block|}
elseif|else
if|if
condition|(
operator|(
name|layer
operator|=
name|gimp_image_pick_layer
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
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|gimp_image_get_floating_selection
argument_list|(
name|image
argument_list|)
operator|&&
operator|!
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
block|{
comment|/*  If there is a floating selection, and this aint it,                    *  use the move tool to anchor it.                    */
name|move
operator|->
name|floating_layer
operator|=
name|gimp_image_get_floating_selection
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
return|return;
block|}
else|else
block|{
name|move
operator|->
name|old_active_layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_set_active_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/*  no guide and no layer picked  */
return|return;
block|}
block|}
block|}
switch|switch
condition|(
name|options
operator|->
name|move_type
condition|)
block|{
case|case
name|GIMP_TRANSFORM_TYPE_PATH
case|:
block|{
name|active_item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|null_message
operator|=
name|_
argument_list|(
literal|"There is no path to move."
argument_list|)
expr_stmt|;
name|locked_message
operator|=
name|_
argument_list|(
literal|"The active path's position is locked."
argument_list|)
expr_stmt|;
if|if
condition|(
name|active_item
operator|&&
operator|!
name|gimp_item_is_position_locked
argument_list|(
name|active_item
argument_list|)
condition|)
block|{
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_edit_selection_tool_start
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|coords
argument_list|,
name|GIMP_TRANSLATE_MODE_VECTORS
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_SELECTION
case|:
block|{
name|active_item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
comment|/* cannot happen, so don't translate these messages */
name|null_message
operator|=
literal|"There is no selection to move."
expr_stmt|;
name|locked_message
operator|=
literal|"The selection's position is locked."
expr_stmt|;
if|if
condition|(
name|active_item
operator|&&
operator|!
name|gimp_item_is_position_locked
argument_list|(
name|active_item
argument_list|)
condition|)
block|{
if|if
condition|(
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
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_edit_selection_tool_start
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|coords
argument_list|,
name|GIMP_TRANSLATE_MODE_MASK
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return;
block|}
else|else
name|locked_message
operator|=
name|_
argument_list|(
literal|"The selection is empty."
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_LAYER
case|:
block|{
name|active_item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|null_message
operator|=
name|_
argument_list|(
literal|"There is no layer to move."
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|active_item
argument_list|)
condition|)
block|{
name|locked_message
operator|=
name|_
argument_list|(
literal|"The active layer's position is locked."
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_is_position_locked
argument_list|(
name|active_item
argument_list|)
condition|)
block|{
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_edit_selection_tool_start
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|coords
argument_list|,
name|GIMP_TRANSLATE_MODE_LAYER_MASK
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|active_item
argument_list|)
condition|)
block|{
name|locked_message
operator|=
name|_
argument_list|(
literal|"The active channel's position is locked."
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_is_position_locked
argument_list|(
name|active_item
argument_list|)
condition|)
block|{
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_edit_selection_tool_start
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|coords
argument_list|,
name|GIMP_TRANSLATE_MODE_CHANNEL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|active_item
argument_list|)
condition|)
block|{
name|locked_message
operator|=
name|_
argument_list|(
literal|"The active layer's position is locked."
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_is_position_locked
argument_list|(
name|active_item
argument_list|)
condition|)
block|{
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_edit_selection_tool_start
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|coords
argument_list|,
name|GIMP_TRANSLATE_MODE_LAYER
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
block|}
break|break;
block|}
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
name|null_message
argument_list|)
expr_stmt|;
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_tool_message_literal
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|locked_message
argument_list|)
expr_stmt|;
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_move_tool_button_release
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
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
init|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|config
init|=
name|GIMP_GUI_CONFIG
argument_list|(
name|display
operator|->
name|gimp
operator|->
name|config
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
name|gboolean
name|flush
init|=
name|FALSE
decl_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|config
operator|->
name|move_tool_changes_active
operator|||
operator|(
name|release_type
operator|==
name|GIMP_BUTTON_RELEASE_CANCEL
operator|)
condition|)
block|{
if|if
condition|(
name|move
operator|->
name|old_active_layer
condition|)
block|{
name|gimp_image_set_active_layer
argument_list|(
name|image
argument_list|,
name|move
operator|->
name|old_active_layer
argument_list|)
expr_stmt|;
name|move
operator|->
name|old_active_layer
operator|=
name|NULL
expr_stmt|;
name|flush
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|move
operator|->
name|old_active_vectors
condition|)
block|{
name|gimp_image_set_active_vectors
argument_list|(
name|image
argument_list|,
name|move
operator|->
name|old_active_vectors
argument_list|)
expr_stmt|;
name|move
operator|->
name|old_active_vectors
operator|=
name|NULL
expr_stmt|;
name|flush
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|release_type
operator|!=
name|GIMP_BUTTON_RELEASE_CANCEL
condition|)
block|{
if|if
condition|(
name|move
operator|->
name|floating_layer
condition|)
block|{
name|floating_sel_anchor
argument_list|(
name|move
operator|->
name|floating_layer
argument_list|)
expr_stmt|;
name|flush
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|flush
condition|)
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_move_tool_key_press (GimpTool * tool,GdkEventKey * kevent,GimpDisplay * display)
name|gimp_move_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpMoveOptions
modifier|*
name|options
init|=
name|GIMP_MOVE_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
return|return
name|gimp_edit_selection_tool_translate
argument_list|(
name|tool
argument_list|,
name|kevent
argument_list|,
name|options
operator|->
name|move_type
argument_list|,
name|display
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_move_tool_modifier_key
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
name|GimpMoveTool
modifier|*
name|move
init|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpMoveOptions
modifier|*
name|options
init|=
name|GIMP_MOVE_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|key
operator|==
name|gimp_get_extend_selection_mask
argument_list|()
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"move-current"
argument_list|,
operator|!
name|options
operator|->
name|move_current
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|key
operator|==
name|GDK_MOD1_MASK
operator|||
name|key
operator|==
name|gimp_get_toggle_behavior_mask
argument_list|()
condition|)
block|{
name|GimpTransformType
name|button_type
decl_stmt|;
name|button_type
operator|=
name|options
operator|->
name|move_type
expr_stmt|;
if|if
condition|(
name|press
condition|)
block|{
if|if
condition|(
name|key
operator|==
operator|(
name|state
operator|&
operator|(
name|GDK_MOD1_MASK
operator||
name|gimp_get_toggle_behavior_mask
argument_list|()
operator|)
operator|)
condition|)
block|{
comment|/*  first modifier pressed  */
name|move
operator|->
name|saved_type
operator|=
name|options
operator|->
name|move_type
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
operator|!
operator|(
name|state
operator|&
operator|(
name|GDK_MOD1_MASK
operator||
name|gimp_get_toggle_behavior_mask
argument_list|()
operator|)
operator|)
condition|)
block|{
comment|/*  last modifier released  */
name|button_type
operator|=
name|move
operator|->
name|saved_type
expr_stmt|;
block|}
block|}
if|if
condition|(
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
block|{
name|button_type
operator|=
name|GIMP_TRANSFORM_TYPE_SELECTION
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|gimp_get_toggle_behavior_mask
argument_list|()
condition|)
block|{
name|button_type
operator|=
name|GIMP_TRANSFORM_TYPE_PATH
expr_stmt|;
block|}
if|if
condition|(
name|button_type
operator|!=
name|options
operator|->
name|move_type
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"move-type"
argument_list|,
name|button_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_oper_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_move_tool_oper_update
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
name|GimpMoveTool
modifier|*
name|move
init|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpMoveOptions
modifier|*
name|options
init|=
name|GIMP_MOVE_TOOL_GET_OPTIONS
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
name|options
operator|->
name|move_type
operator|==
name|GIMP_TRANSFORM_TYPE_LAYER
operator|&&
operator|!
name|options
operator|->
name|move_current
operator|&&
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
name|gimp_image_find_guide
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
name|move
operator|->
name|guide
operator|!=
name|guide
condition|)
block|{
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
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
name|move
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_move_tool_cursor_update
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
name|GimpMoveOptions
modifier|*
name|options
init|=
name|GIMP_MOVE_TOOL_GET_OPTIONS
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
name|GimpCursorType
name|cursor
init|=
name|GIMP_CURSOR_MOUSE
decl_stmt|;
name|GimpToolCursorType
name|tool_cursor
init|=
name|GIMP_TOOL_CURSOR_MOVE
decl_stmt|;
name|GimpCursorModifier
name|modifier
init|=
name|GIMP_CURSOR_MODIFIER_NONE
decl_stmt|;
if|if
condition|(
name|options
operator|->
name|move_type
operator|==
name|GIMP_TRANSFORM_TYPE_PATH
condition|)
block|{
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_PATHS
expr_stmt|;
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_MOVE
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|move_current
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|item
operator|||
name|gimp_item_is_position_locked
argument_list|(
name|item
argument_list|)
condition|)
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BAD
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gimp_draw_tool_on_vectors
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|display
argument_list|,
name|coords
argument_list|,
literal|7
argument_list|,
literal|7
argument_list|,
name|NULL
argument_list|,
name|NULL
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
block|{
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_HAND
expr_stmt|;
block|}
else|else
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BAD
expr_stmt|;
block|}
block|}
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|move_type
operator|==
name|GIMP_TRANSFORM_TYPE_SELECTION
condition|)
block|{
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_RECT_SELECT
expr_stmt|;
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_MOVE
expr_stmt|;
if|if
condition|(
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
condition|)
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BAD
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|move_current
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|item
operator|||
name|gimp_item_is_position_locked
argument_list|(
name|item
argument_list|)
condition|)
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BAD
expr_stmt|;
block|}
else|else
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
specifier|const
name|gint
name|snap_distance
init|=
name|display
operator|->
name|config
operator|->
name|snap_distance
decl_stmt|;
if|if
condition|(
name|gimp_display_shell_get_show_guides
argument_list|(
name|shell
argument_list|)
operator|&&
name|gimp_image_find_guide
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
condition|)
block|{
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_HAND
expr_stmt|;
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_MOVE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|layer
operator|=
name|gimp_image_pick_layer
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
argument_list|)
operator|)
condition|)
block|{
comment|/*  if there is a floating selection, and this aint it...  */
if|if
condition|(
name|gimp_image_get_floating_selection
argument_list|(
name|image
argument_list|)
operator|&&
operator|!
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_MOVE
expr_stmt|;
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_ANCHOR
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_item_is_position_locked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BAD
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|layer
operator|!=
name|gimp_image_get_active_layer
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_HAND
expr_stmt|;
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_MOVE
expr_stmt|;
block|}
block|}
else|else
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BAD
expr_stmt|;
block|}
block|}
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|tool_cursor
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|modifier
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
DECL|function|gimp_move_tool_draw (GimpDrawTool * draw_tool)
name|gimp_move_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
init|=
name|GIMP_MOVE_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|move
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
name|move
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
name|move
operator|->
name|guide
argument_list|)
argument_list|,
name|gimp_guide_get_position
argument_list|(
name|move
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

end_unit

