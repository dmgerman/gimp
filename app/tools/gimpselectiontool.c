begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
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
file|"selection_options.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_selection_tool_class_init
parameter_list|(
name|GimpSelectionToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_tool_init
parameter_list|(
name|GimpSelectionTool
modifier|*
name|selection_tool
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
name|gdisp
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
name|GimpDisplay
modifier|*
name|gdisp
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
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDrawToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_selection_tool_get_type (void)
name|gimp_selection_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpSelectionToolClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_selection_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpSelectionTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_selection_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DRAW_TOOL
argument_list|,
literal|"GimpSelectionTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_tool_class_init (GimpSelectionToolClass * klass)
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
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_selection_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|arrow_key
operator|=
name|gimp_edit_selection_tool_arrow_key
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
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|selection_tool
argument_list|)
expr_stmt|;
name|selection_tool
operator|->
name|op
operator|=
name|SELECTION_REPLACE
expr_stmt|;
name|selection_tool
operator|->
name|saved_op
operator|=
name|SELECTION_REPLACE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * gdisp)
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
name|gdisp
parameter_list|)
block|{
name|GimpSelectionTool
modifier|*
name|selection_tool
decl_stmt|;
name|SelectionOptions
modifier|*
name|sel_options
decl_stmt|;
name|SelectOps
name|button_op
decl_stmt|;
name|selection_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|sel_options
operator|=
operator|(
name|SelectionOptions
operator|*
operator|)
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
name|button_op
operator|=
name|sel_options
operator|->
name|op
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
condition|)
block|{
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
operator|)
operator|)
condition|)
block|{
comment|/*  first modifier pressed  */
name|selection_tool
operator|->
name|saved_op
operator|=
name|sel_options
operator|->
name|op
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
operator|)
operator|)
condition|)
block|{
comment|/*  last modifier released  */
name|button_op
operator|=
name|selection_tool
operator|->
name|saved_op
expr_stmt|;
block|}
block|}
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
name|SELECTION_INTERSECT
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
name|SELECTION_ADD
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
name|SELECTION_SUBTRACT
expr_stmt|;
block|}
if|if
condition|(
name|button_op
operator|!=
name|sel_options
operator|->
name|op
condition|)
block|{
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|sel_options
operator|->
name|op_w
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|button_op
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_tool_oper_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
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
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpSelectionTool
modifier|*
name|selection_tool
decl_stmt|;
name|SelectionOptions
modifier|*
name|sel_options
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
name|selection_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|sel_options
operator|=
operator|(
name|SelectionOptions
operator|*
operator|)
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
name|layer
operator|=
name|gimp_image_pick_correlate_layer
argument_list|(
name|gdisp
operator|->
name|gimage
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
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|state
operator|&
name|GDK_MOD1_MASK
operator|)
operator|&&
operator|!
name|gimp_image_mask_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
block|{
name|selection_tool
operator|->
name|op
operator|=
name|SELECTION_MOVE_MASK
expr_stmt|;
comment|/* move the selection mask */
block|}
elseif|else
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
operator|)
operator|)
operator|&&
name|layer
operator|&&
operator|(
name|layer
operator|==
name|floating_sel
operator|||
operator|(
name|gimp_image_mask_value
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|)
operator|&&
name|floating_sel
operator|==
name|NULL
operator|)
operator|)
condition|)
block|{
name|selection_tool
operator|->
name|op
operator|=
name|SELECTION_MOVE
expr_stmt|;
comment|/* move the selection */
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
name|selection_tool
operator|->
name|op
operator|=
name|SELECTION_INTERSECT
expr_stmt|;
comment|/* intersect with selection */
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
name|selection_tool
operator|->
name|op
operator|=
name|SELECTION_ADD
expr_stmt|;
comment|/* add to the selection */
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|selection_tool
operator|->
name|op
operator|=
name|SELECTION_SUBTRACT
expr_stmt|;
comment|/* subtract from the selection */
block|}
elseif|else
if|if
condition|(
name|floating_sel
condition|)
block|{
name|selection_tool
operator|->
name|op
operator|=
name|SELECTION_ANCHOR
expr_stmt|;
comment|/* anchor the selection */
block|}
else|else
block|{
name|selection_tool
operator|->
name|op
operator|=
name|sel_options
operator|->
name|op
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
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
name|gdisp
parameter_list|)
block|{
name|GimpSelectionTool
modifier|*
name|selection_tool
decl_stmt|;
name|GimpToolCursorType
name|tool_cursor
decl_stmt|;
name|GimpCursorModifier
name|cmodifier
decl_stmt|;
name|selection_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|tool_cursor
operator|=
name|tool
operator|->
name|tool_cursor
expr_stmt|;
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_NONE
expr_stmt|;
switch|switch
condition|(
name|selection_tool
operator|->
name|op
condition|)
block|{
case|case
name|SELECTION_ADD
case|:
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_PLUS
expr_stmt|;
break|break;
case|case
name|SELECTION_SUBTRACT
case|:
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_MINUS
expr_stmt|;
break|break;
case|case
name|SELECTION_INTERSECT
case|:
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_INTERSECT
expr_stmt|;
break|break;
case|case
name|SELECTION_REPLACE
case|:
break|break;
case|case
name|SELECTION_MOVE_MASK
case|:
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_MOVE
expr_stmt|;
break|break;
case|case
name|SELECTION_MOVE
case|:
name|tool_cursor
operator|=
name|GIMP_MOVE_TOOL_CURSOR
expr_stmt|;
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_NONE
expr_stmt|;
break|break;
case|case
name|SELECTION_ANCHOR
case|:
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_ANCHOR
expr_stmt|;
break|break;
block|}
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|,
name|tool_cursor
argument_list|,
name|cmodifier
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

