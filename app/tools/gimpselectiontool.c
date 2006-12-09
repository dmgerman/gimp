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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpeditselectiontool.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectionoptions.h"
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

begin_function_decl
specifier|static
name|void
name|gimp_selection_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
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
name|gimp_selection_tool_modifier_key
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
name|gimp_selection_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|gimp_selection_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSelectionTool,gimp_selection_tool,GIMP_TYPE_DRAW_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSelectionTool
argument_list|,
argument|gimp_selection_tool
argument_list|,
argument|GIMP_TYPE_DRAW_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_selection_tool_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_selection_tool_class_init
parameter_list|(
name|GimpSelectionToolClass
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
name|tool_class
operator|->
name|control
operator|=
name|gimp_selection_tool_control
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_selection_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|key_press
operator|=
name|gimp_edit_selection_tool_key_press
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_selection_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_selection_tool_cursor_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_tool_init (GimpSelectionTool * selection_tool)
name|gimp_selection_tool_init
parameter_list|(
name|GimpSelectionTool
modifier|*
name|selection_tool
parameter_list|)
block|{
name|selection_tool
operator|->
name|function
operator|=
name|SELECTION_SELECT
expr_stmt|;
name|selection_tool
operator|->
name|saved_operation
operator|=
name|GIMP_CHANNEL_OP_REPLACE
expr_stmt|;
name|selection_tool
operator|->
name|allow_move
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * display)
name|gimp_selection_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|GIMP_TOOL_ACTION_PAUSE
case|:
case|case
name|GIMP_TOOL_ACTION_RESUME
case|:
break|break;
case|case
name|GIMP_TOOL_ACTION_HALT
case|:
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
break|break;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_selection_tool_modifier_key
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
name|GimpSelectionTool
modifier|*
name|selection_tool
init|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_SELECTION_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|key
operator|==
name|GDK_SHIFT_MASK
operator|||
name|key
operator|==
name|GDK_CONTROL_MASK
operator|||
name|key
operator|==
name|GDK_MOD1_MASK
condition|)
block|{
name|GimpChannelOps
name|button_op
init|=
name|options
operator|->
name|operation
decl_stmt|;
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
name|GDK_SHIFT_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_MOD1_MASK
operator|)
operator|)
condition|)
block|{
comment|/*  first modifier pressed  */
name|selection_tool
operator|->
name|saved_operation
operator|=
name|options
operator|->
name|operation
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
name|GDK_SHIFT_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_MOD1_MASK
operator|)
operator|)
condition|)
block|{
comment|/*  last modifier released  */
name|button_op
operator|=
name|selection_tool
operator|->
name|saved_operation
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
comment|/*  if alt is down, pretend that neither            *  shift nor control are down            */
name|button_op
operator|=
name|selection_tool
operator|->
name|saved_operation
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
operator|&&
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
condition|)
block|{
name|button_op
operator|=
name|GIMP_CHANNEL_OP_INTERSECT
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
name|button_op
operator|=
name|GIMP_CHANNEL_OP_ADD
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|button_op
operator|=
name|GIMP_CHANNEL_OP_SUBTRACT
expr_stmt|;
block|}
if|if
condition|(
name|button_op
operator|!=
name|options
operator|->
name|operation
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"operation"
argument_list|,
name|button_op
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
DECL|function|gimp_selection_tool_oper_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_selection_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|GimpSelectionTool
modifier|*
name|selection_tool
init|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|GimpChannel
modifier|*
name|selection
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
name|gboolean
name|move_layer
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|move_floating_sel
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|selection_empty
decl_stmt|;
name|options
operator|=
name|GIMP_SELECTION_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|selection
operator|=
name|gimp_image_get_mask
argument_list|(
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_image_pick_correlate_layer
argument_list|(
name|display
operator|->
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
expr_stmt|;
name|floating_sel
operator|=
name|gimp_image_floating_sel
argument_list|(
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
if|if
condition|(
name|floating_sel
condition|)
block|{
if|if
condition|(
name|layer
operator|==
name|floating_sel
condition|)
name|move_floating_sel
operator|=
name|TRUE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable
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
name|move_layer
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|selection_empty
operator|=
name|gimp_channel_is_empty
argument_list|(
name|selection
argument_list|)
expr_stmt|;
name|selection_tool
operator|->
name|function
operator|=
name|SELECTION_SELECT
expr_stmt|;
if|if
condition|(
name|selection_tool
operator|->
name|allow_move
operator|&&
operator|(
name|state
operator|&
name|GDK_MOD1_MASK
operator|)
operator|&&
operator|(
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
operator|&&
name|move_layer
condition|)
block|{
comment|/* move the selection */
name|selection_tool
operator|->
name|function
operator|=
name|SELECTION_MOVE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|selection_tool
operator|->
name|allow_move
operator|&&
operator|(
name|state
operator|&
name|GDK_MOD1_MASK
operator|)
operator|&&
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
operator|&&
name|move_layer
condition|)
block|{
comment|/* move a copy of the selection */
name|selection_tool
operator|->
name|function
operator|=
name|SELECTION_MOVE_COPY
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|selection_tool
operator|->
name|allow_move
operator|&&
operator|(
name|state
operator|&
name|GDK_MOD1_MASK
operator|)
operator|&&
operator|!
name|selection_empty
condition|)
block|{
comment|/* move the selection mask */
name|selection_tool
operator|->
name|function
operator|=
name|SELECTION_MOVE_MASK
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|selection_tool
operator|->
name|allow_move
operator|&&
operator|!
operator|(
name|state
operator|&
operator|(
name|GDK_SHIFT_MASK
operator||
name|GDK_CONTROL_MASK
operator|)
operator|)
operator|&&
name|move_floating_sel
condition|)
block|{
comment|/* move the selection */
name|selection_tool
operator|->
name|function
operator|=
name|SELECTION_MOVE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
operator|||
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
condition|)
block|{
comment|/* select */
name|selection_tool
operator|->
name|function
operator|=
name|SELECTION_SELECT
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|floating_sel
condition|)
block|{
comment|/* anchor the selection */
name|selection_tool
operator|->
name|function
operator|=
name|SELECTION_ANCHOR
expr_stmt|;
block|}
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|proximity
condition|)
block|{
name|gchar
modifier|*
name|status
init|=
name|NULL
decl_stmt|;
name|gboolean
name|free_status
init|=
name|FALSE
decl_stmt|;
name|GdkModifierType
name|modifiers
init|=
operator|(
name|GDK_SHIFT_MASK
operator||
name|GDK_CONTROL_MASK
operator|)
decl_stmt|;
if|if
condition|(
operator|!
name|selection_empty
condition|)
name|modifiers
operator||=
name|GDK_MOD1_MASK
expr_stmt|;
switch|switch
condition|(
name|selection_tool
operator|->
name|function
condition|)
block|{
case|case
name|SELECTION_SELECT
case|:
switch|switch
condition|(
name|options
operator|->
name|operation
condition|)
block|{
case|case
name|GIMP_CHANNEL_OP_REPLACE
case|:
if|if
condition|(
operator|!
name|selection_empty
condition|)
block|{
name|status
operator|=
name|gimp_suggest_modifiers
argument_list|(
name|_
argument_list|(
literal|"Click-Drag to replace the "
literal|"current selection"
argument_list|)
argument_list|,
name|modifiers
operator|&
operator|~
name|state
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|free_status
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|_
argument_list|(
literal|"Click-Drag to create a new selection"
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_CHANNEL_OP_ADD
case|:
name|status
operator|=
name|gimp_suggest_modifiers
argument_list|(
name|_
argument_list|(
literal|"Click-Drag to add to the "
literal|"current selection"
argument_list|)
argument_list|,
name|modifiers
operator|&
operator|~
operator|(
name|state
operator||
name|GDK_SHIFT_MASK
operator|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|free_status
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_OP_SUBTRACT
case|:
name|status
operator|=
name|gimp_suggest_modifiers
argument_list|(
name|_
argument_list|(
literal|"Click-Drag to subtract from the "
literal|"current selection"
argument_list|)
argument_list|,
name|modifiers
operator|&
operator|~
operator|(
name|state
operator||
name|GDK_CONTROL_MASK
operator|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|free_status
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_OP_INTERSECT
case|:
name|status
operator|=
name|gimp_suggest_modifiers
argument_list|(
name|_
argument_list|(
literal|"Click-Drag to intersect with "
literal|"the current selection"
argument_list|)
argument_list|,
name|modifiers
operator|&
operator|~
name|state
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|free_status
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
break|break;
case|case
name|SELECTION_MOVE_MASK
case|:
name|status
operator|=
name|gimp_suggest_modifiers
argument_list|(
name|_
argument_list|(
literal|"Click-Drag to move the "
literal|"selection mask"
argument_list|)
argument_list|,
name|modifiers
operator|&
operator|~
name|state
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|free_status
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|SELECTION_MOVE
case|:
name|status
operator|=
name|_
argument_list|(
literal|"Click-Drag to move the selected pixels"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_MOVE_COPY
case|:
name|status
operator|=
name|_
argument_list|(
literal|"Click-Drag to move a copy of the selected pixels"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_ANCHOR
case|:
name|status
operator|=
name|_
argument_list|(
literal|"Click to anchor the floating selection"
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|status
condition|)
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|status
argument_list|)
expr_stmt|;
if|if
condition|(
name|free_status
condition|)
name|g_free
argument_list|(
name|status
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_selection_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|GimpSelectionTool
modifier|*
name|selection_tool
init|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|GimpToolCursorType
name|tool_cursor
decl_stmt|;
name|GimpCursorModifier
name|modifier
decl_stmt|;
name|options
operator|=
name|GIMP_SELECTION_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|tool_cursor
operator|=
name|gimp_tool_control_get_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_NONE
expr_stmt|;
switch|switch
condition|(
name|selection_tool
operator|->
name|function
condition|)
block|{
case|case
name|SELECTION_SELECT
case|:
switch|switch
condition|(
name|options
operator|->
name|operation
condition|)
block|{
case|case
name|GIMP_CHANNEL_OP_REPLACE
case|:
break|break;
case|case
name|GIMP_CHANNEL_OP_ADD
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_PLUS
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_OP_SUBTRACT
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_MINUS
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_OP_INTERSECT
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_INTERSECT
expr_stmt|;
break|break;
block|}
break|break;
case|case
name|SELECTION_MOVE_MASK
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_MOVE
expr_stmt|;
break|break;
case|case
name|SELECTION_MOVE
case|:
case|case
name|SELECTION_MOVE_COPY
case|:
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_MOVE
expr_stmt|;
break|break;
case|case
name|SELECTION_ANCHOR
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_ANCHOR
expr_stmt|;
break|break;
block|}
comment|/*  we don't set the bad modifier ourselves, so a subclass has set    *  it, always leave it there since it's more important than what we    *  have to say.    */
if|if
condition|(
name|gimp_tool_control_get_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|)
operator|==
name|GIMP_CURSOR_MODIFIER_BAD
condition|)
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BAD
expr_stmt|;
block|}
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
name|tool_cursor
argument_list|,
name|modifier
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_tool_start_edit (GimpSelectionTool * sel_tool,GimpCoords * coords)
name|gimp_selection_tool_start_edit
parameter_list|(
name|GimpSelectionTool
modifier|*
name|sel_tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SELECTION_TOOL
argument_list|(
name|sel_tool
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|coords
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|sel_tool
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|tool
operator|->
name|display
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|sel_tool
operator|->
name|function
condition|)
block|{
case|case
name|SELECTION_MOVE_MASK
case|:
name|gimp_edit_selection_tool_start
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|display
argument_list|,
name|coords
argument_list|,
name|GIMP_TRANSLATE_MODE_MASK
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
case|case
name|SELECTION_MOVE
case|:
name|gimp_edit_selection_tool_start
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|display
argument_list|,
name|coords
argument_list|,
name|GIMP_TRANSLATE_MODE_MASK_TO_LAYER
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
case|case
name|SELECTION_MOVE_COPY
case|:
name|gimp_edit_selection_tool_start
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|display
argument_list|,
name|coords
argument_list|,
name|GIMP_TRANSLATE_MODE_MASK_COPY_TO_LAYER
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

