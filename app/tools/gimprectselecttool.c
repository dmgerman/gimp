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
file|<stdlib.h>
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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-crop.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-unit.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
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
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpeditselectiontool.h"
end_include

begin_include
include|#
directive|include
file|"gimprectselecttool.h"
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
name|gimp_rect_select_tool_class_init
parameter_list|(
name|GimpRectSelectToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rect_select_tool_init
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rect_select_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rect_select_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rect_select_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rect_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rect_select_tool_real_rect_select
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rect_select_tool_update_options
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpSelectionToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_rect_select_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_rect_select_tool_register
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
name|GIMP_TYPE_RECT_SELECT_TOOL
argument_list|,
name|GIMP_TYPE_SELECTION_OPTIONS
argument_list|,
name|gimp_selection_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-rect-select-tool"
argument_list|,
name|_
argument_list|(
literal|"Rect Select"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Select rectangular regions"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Selection Tools/_Rect Select"
argument_list|)
argument_list|,
literal|"R"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_RECT_SELECT
argument_list|,
name|GIMP_STOCK_TOOL_RECT_SELECT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_rect_select_tool_get_type (void)
name|gimp_rect_select_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
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
name|GimpRectSelectToolClass
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
name|gimp_rect_select_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpRectSelectTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_rect_select_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_SELECTION_TOOL
argument_list|,
literal|"GimpRectSelectTool"
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_tool_class_init (GimpRectSelectToolClass * klass)
name|gimp_rect_select_tool_class_init
parameter_list|(
name|GimpRectSelectToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|draw_tool_class
operator|=
name|GIMP_DRAW_TOOL_CLASS
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
name|button_press
operator|=
name|gimp_rect_select_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_rect_select_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_rect_select_tool_motion
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_rect_select_tool_draw
expr_stmt|;
name|klass
operator|->
name|rect_select
operator|=
name|gimp_rect_select_tool_real_rect_select
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_tool_init (GimpRectSelectTool * rect_select)
name|gimp_rect_select_tool_init
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_select
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|rect_select
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_RECT_SELECT_TOOL_CURSOR
argument_list|)
expr_stmt|;
name|rect_select
operator|->
name|x
operator|=
name|rect_select
operator|->
name|y
operator|=
literal|0.0
expr_stmt|;
name|rect_select
operator|->
name|w
operator|=
name|rect_select
operator|->
name|h
operator|=
literal|0.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_rect_select_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpRectSelectTool
modifier|*
name|rect_sel
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|GimpUnit
name|unit
init|=
name|GIMP_UNIT_PIXEL
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
name|rect_sel
operator|=
name|GIMP_RECT_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|sel_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|rect_sel
operator|->
name|w
operator|=
literal|0.0
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
literal|0.0
expr_stmt|;
name|rect_sel
operator|->
name|center
operator|=
name|FALSE
expr_stmt|;
name|rect_sel
operator|->
name|last_coords
operator|=
operator|*
name|coords
expr_stmt|;
name|rect_sel
operator|->
name|fixed_mode
operator|=
name|options
operator|->
name|fixed_mode
expr_stmt|;
name|rect_sel
operator|->
name|fixed_width
operator|=
name|options
operator|->
name|fixed_width
expr_stmt|;
name|rect_sel
operator|->
name|fixed_height
operator|=
name|options
operator|->
name|fixed_height
expr_stmt|;
name|unit
operator|=
name|options
operator|->
name|fixed_unit
expr_stmt|;
switch|switch
condition|(
name|unit
condition|)
block|{
case|case
name|GIMP_UNIT_PIXEL
case|:
break|break;
case|case
name|GIMP_UNIT_PERCENT
case|:
name|rect_sel
operator|->
name|fixed_width
operator|=
name|gdisp
operator|->
name|gimage
operator|->
name|width
operator|*
name|rect_sel
operator|->
name|fixed_width
operator|/
literal|100
expr_stmt|;
name|rect_sel
operator|->
name|fixed_height
operator|=
name|gdisp
operator|->
name|gimage
operator|->
name|height
operator|*
name|rect_sel
operator|->
name|fixed_height
operator|/
literal|100
expr_stmt|;
break|break;
default|default:
name|unit_factor
operator|=
name|_gimp_unit_get_factor
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|fixed_width
operator|=
name|rect_sel
operator|->
name|fixed_width
operator|*
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
operator|/
name|unit_factor
expr_stmt|;
name|rect_sel
operator|->
name|fixed_height
operator|=
name|rect_sel
operator|->
name|fixed_height
operator|*
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
operator|/
name|unit_factor
expr_stmt|;
break|break;
block|}
name|rect_sel
operator|->
name|fixed_width
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|rect_sel
operator|->
name|fixed_width
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|fixed_height
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|rect_sel
operator|->
name|fixed_height
argument_list|)
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
switch|switch
condition|(
name|sel_tool
operator|->
name|op
condition|)
block|{
case|case
name|SELECTION_MOVE_MASK
case|:
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|coords
argument_list|,
name|EDIT_MASK_TRANSLATE
argument_list|)
expr_stmt|;
return|return;
case|case
name|SELECTION_MOVE
case|:
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|coords
argument_list|,
name|EDIT_MASK_TO_LAYER_TRANSLATE
argument_list|)
expr_stmt|;
return|return;
case|case
name|SELECTION_MOVE_COPY
case|:
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|coords
argument_list|,
name|EDIT_MASK_COPY_TO_LAYER_TRANSLATE
argument_list|)
expr_stmt|;
return|return;
default|default:
break|break;
block|}
switch|switch
condition|(
name|sel_tool
operator|->
name|op
condition|)
block|{
case|case
name|SELECTION_ADD
case|:
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|_
argument_list|(
literal|"Selection: ADD"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_SUBTRACT
case|:
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|_
argument_list|(
literal|"Selection: SUBTRACT"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_INTERSECT
case|:
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|_
argument_list|(
literal|"Selection: INTERSECT"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_REPLACE
case|:
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|_
argument_list|(
literal|"Selection: REPLACE"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_rect_select_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpRectSelectTool
modifier|*
name|rect_sel
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
decl_stmt|;
name|gdouble
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gdouble
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gdouble
name|w
decl_stmt|,
name|h
decl_stmt|;
name|rect_sel
operator|=
name|GIMP_RECT_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|sel_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
comment|/*  First take care of the case where the user "cancels" the action  */
if|if
condition|(
operator|!
operator|(
name|state
operator|&
name|GDK_BUTTON3_MASK
operator|)
condition|)
block|{
name|x1
operator|=
operator|(
name|rect_sel
operator|->
name|w
operator|<
literal|0
operator|)
condition|?
name|rect_sel
operator|->
name|x
operator|+
name|rect_sel
operator|->
name|w
else|:
name|rect_sel
operator|->
name|x
expr_stmt|;
name|y1
operator|=
operator|(
name|rect_sel
operator|->
name|h
operator|<
literal|0
operator|)
condition|?
name|rect_sel
operator|->
name|y
operator|+
name|rect_sel
operator|->
name|h
else|:
name|rect_sel
operator|->
name|y
expr_stmt|;
name|w
operator|=
operator|(
name|rect_sel
operator|->
name|w
operator|<
literal|0
operator|)
condition|?
operator|-
name|rect_sel
operator|->
name|w
else|:
name|rect_sel
operator|->
name|w
expr_stmt|;
name|h
operator|=
operator|(
name|rect_sel
operator|->
name|h
operator|<
literal|0
operator|)
condition|?
operator|-
name|rect_sel
operator|->
name|h
else|:
name|rect_sel
operator|->
name|h
expr_stmt|;
if|if
condition|(
operator|(
operator|!
name|w
operator|||
operator|!
name|h
operator|)
operator|&&
name|rect_sel
operator|->
name|fixed_mode
operator|==
name|GIMP_RECT_SELECT_MODE_FREE
condition|)
block|{
comment|/*  If there is a floating selection, anchor it  */
if|if
condition|(
name|gimp_image_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
name|floating_sel_anchor
argument_list|(
name|gimp_image_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Otherwise, clear the selection mask  */
else|else
name|gimp_channel_clear
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
return|return;
block|}
name|x2
operator|=
name|x1
operator|+
name|w
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|h
expr_stmt|;
name|gimp_rect_select_tool_rect_select
argument_list|(
name|rect_sel
argument_list|,
name|RINT
argument_list|(
name|x1
argument_list|)
argument_list|,
name|RINT
argument_list|(
name|y1
argument_list|)
argument_list|,
name|RINT
argument_list|(
name|w
argument_list|)
argument_list|,
name|RINT
argument_list|(
name|h
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  show selection on all views  */
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_rect_select_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpRectSelectTool
modifier|*
name|rect_sel
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
decl_stmt|;
name|gdouble
name|ox
decl_stmt|,
name|oy
decl_stmt|;
name|gdouble
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gdouble
name|tw
decl_stmt|,
name|th
decl_stmt|;
name|gdouble
name|ratio
decl_stmt|;
name|rect_sel
operator|=
name|GIMP_RECT_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|sel_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|sel_tool
operator|->
name|op
operator|==
name|SELECTION_ANCHOR
condition|)
block|{
name|sel_tool
operator|->
name|op
operator|=
name|SELECTION_REPLACE
expr_stmt|;
name|gimp_tool_cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
block|{
comment|/*  Just move the selection rectangle around  */
name|rect_sel
operator|->
name|x
operator|+=
name|coords
operator|->
name|x
operator|-
name|rect_sel
operator|->
name|last_coords
operator|.
name|x
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|+=
name|coords
operator|->
name|y
operator|-
name|rect_sel
operator|->
name|last_coords
operator|.
name|y
expr_stmt|;
block|}
else|else
block|{
comment|/*  Change the selection rectangle's size  */
comment|/*  Calculate starting point  */
if|if
condition|(
name|rect_sel
operator|->
name|center
condition|)
block|{
name|ox
operator|=
name|rect_sel
operator|->
name|x
operator|+
name|rect_sel
operator|->
name|w
operator|/
literal|2.0
expr_stmt|;
name|oy
operator|=
name|rect_sel
operator|->
name|y
operator|+
name|rect_sel
operator|->
name|h
operator|/
literal|2.0
expr_stmt|;
block|}
else|else
block|{
name|ox
operator|=
name|rect_sel
operator|->
name|x
expr_stmt|;
name|oy
operator|=
name|rect_sel
operator|->
name|y
expr_stmt|;
block|}
switch|switch
condition|(
name|rect_sel
operator|->
name|fixed_mode
condition|)
block|{
case|case
name|GIMP_RECT_SELECT_MODE_FIXED_SIZE
case|:
name|w
operator|=
operator|(
operator|(
name|coords
operator|->
name|x
operator|-
name|ox
operator|)
operator|>
literal|0
condition|?
name|rect_sel
operator|->
name|fixed_width
else|:
operator|-
name|rect_sel
operator|->
name|fixed_width
operator|)
expr_stmt|;
name|h
operator|=
operator|(
operator|(
name|coords
operator|->
name|y
operator|-
name|oy
operator|)
operator|>
literal|0
condition|?
name|rect_sel
operator|->
name|fixed_height
else|:
operator|-
name|rect_sel
operator|->
name|fixed_height
operator|)
expr_stmt|;
break|break;
case|case
name|GIMP_RECT_SELECT_MODE_FIXED_RATIO
case|:
name|ratio
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|rect_sel
operator|->
name|fixed_height
operator|/
operator|(
name|gdouble
operator|)
name|rect_sel
operator|->
name|fixed_width
operator|)
expr_stmt|;
name|tw
operator|=
operator|(
name|coords
operator|->
name|x
operator|-
name|ox
operator|)
expr_stmt|;
name|th
operator|=
operator|(
name|coords
operator|->
name|y
operator|-
name|oy
operator|)
expr_stmt|;
comment|/* This is probably an inefficient way to do it, but it gives            * nicer, more predictable results than the original agorithm            */
if|if
condition|(
operator|(
name|abs
argument_list|(
name|th
argument_list|)
operator|<
operator|(
name|ratio
operator|*
name|abs
argument_list|(
name|tw
argument_list|)
operator|)
operator|)
operator|&&
operator|(
name|abs
argument_list|(
name|tw
argument_list|)
operator|>
operator|(
name|abs
argument_list|(
name|th
argument_list|)
operator|/
name|ratio
operator|)
operator|)
condition|)
block|{
name|w
operator|=
name|tw
expr_stmt|;
name|h
operator|=
operator|(
name|tw
operator|*
name|ratio
operator|)
expr_stmt|;
comment|/* h should have the sign of th */
if|if
condition|(
operator|(
name|th
operator|<
literal|0
operator|&&
name|h
operator|>
literal|0
operator|)
operator|||
operator|(
name|th
operator|>
literal|0
operator|&&
name|h
operator|<
literal|0
operator|)
condition|)
name|h
operator|=
operator|-
name|h
expr_stmt|;
block|}
else|else
block|{
name|h
operator|=
name|th
expr_stmt|;
name|w
operator|=
operator|(
name|th
operator|/
name|ratio
operator|)
expr_stmt|;
comment|/* w should have the sign of tw */
if|if
condition|(
operator|(
name|tw
operator|<
literal|0
operator|&&
name|w
operator|>
literal|0
operator|)
operator|||
operator|(
name|tw
operator|>
literal|0
operator|&&
name|w
operator|<
literal|0
operator|)
condition|)
name|w
operator|=
operator|-
name|w
expr_stmt|;
block|}
break|break;
default|default:
name|w
operator|=
operator|(
name|coords
operator|->
name|x
operator|-
name|ox
operator|)
expr_stmt|;
name|h
operator|=
operator|(
name|coords
operator|->
name|y
operator|-
name|oy
operator|)
expr_stmt|;
break|break;
block|}
comment|/* If the shift key is down, then make the rectangle square (or        * ellipse circular)        */
if|if
condition|(
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
operator|&&
name|rect_sel
operator|->
name|fixed_mode
operator|==
name|GIMP_RECT_SELECT_MODE_FREE
condition|)
block|{
name|gint
name|s
init|=
name|MAX
argument_list|(
name|abs
argument_list|(
name|w
argument_list|)
argument_list|,
name|abs
argument_list|(
name|h
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|w
operator|<
literal|0
condition|)
name|w
operator|=
operator|-
name|s
expr_stmt|;
else|else
name|w
operator|=
name|s
expr_stmt|;
if|if
condition|(
name|h
operator|<
literal|0
condition|)
name|h
operator|=
operator|-
name|s
expr_stmt|;
else|else
name|h
operator|=
name|s
expr_stmt|;
block|}
comment|/*  If the control key is down, create the selection from the center out        */
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|rect_sel
operator|->
name|center
operator|=
name|TRUE
expr_stmt|;
switch|switch
condition|(
name|rect_sel
operator|->
name|fixed_mode
condition|)
block|{
case|case
name|GIMP_RECT_SELECT_MODE_FIXED_SIZE
case|:
name|rect_sel
operator|->
name|x
operator|=
name|ox
operator|-
name|w
operator|/
literal|2.0
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|=
name|oy
operator|-
name|h
operator|/
literal|2.0
expr_stmt|;
name|rect_sel
operator|->
name|w
operator|=
name|w
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
name|h
expr_stmt|;
break|break;
case|case
name|GIMP_RECT_SELECT_MODE_FIXED_RATIO
case|:
name|rect_sel
operator|->
name|x
operator|=
name|ox
operator|-
name|w
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|=
name|oy
operator|-
name|h
expr_stmt|;
name|rect_sel
operator|->
name|w
operator|=
name|w
operator|*
literal|2.0
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
name|h
operator|*
literal|2.0
expr_stmt|;
break|break;
default|default:
name|w
operator|=
name|abs
argument_list|(
name|w
argument_list|)
expr_stmt|;
name|h
operator|=
name|abs
argument_list|(
name|h
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|x
operator|=
name|ox
operator|-
name|w
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|=
name|oy
operator|-
name|h
expr_stmt|;
name|rect_sel
operator|->
name|w
operator|=
literal|2.0
operator|*
name|w
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
literal|2.0
operator|*
name|h
expr_stmt|;
break|break;
block|}
block|}
else|else
block|{
name|rect_sel
operator|->
name|center
operator|=
name|FALSE
expr_stmt|;
name|rect_sel
operator|->
name|x
operator|=
name|ox
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|=
name|oy
expr_stmt|;
name|rect_sel
operator|->
name|w
operator|=
name|w
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
name|h
expr_stmt|;
block|}
block|}
name|rect_sel
operator|->
name|last_coords
operator|=
operator|*
name|coords
expr_stmt|;
name|gimp_rect_select_tool_update_options
argument_list|(
name|rect_sel
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_tool_push_status_coords
argument_list|(
name|tool
argument_list|,
name|_
argument_list|(
literal|"Selection: "
argument_list|)
argument_list|,
name|abs
argument_list|(
name|RINT
argument_list|(
name|rect_sel
operator|->
name|w
argument_list|)
argument_list|)
argument_list|,
literal|" x "
argument_list|,
name|abs
argument_list|(
name|RINT
argument_list|(
name|rect_sel
operator|->
name|h
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_tool_draw (GimpDrawTool * draw_tool)
name|gimp_rect_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpRectSelectTool
modifier|*
name|rect_sel
init|=
name|GIMP_RECT_SELECT_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_draw_rectangle
argument_list|(
name|draw_tool
argument_list|,
name|FALSE
argument_list|,
name|RINT
argument_list|(
name|rect_sel
operator|->
name|x
argument_list|)
argument_list|,
name|RINT
argument_list|(
name|rect_sel
operator|->
name|y
argument_list|)
argument_list|,
name|RINT
argument_list|(
name|rect_sel
operator|->
name|w
argument_list|)
argument_list|,
name|RINT
argument_list|(
name|rect_sel
operator|->
name|h
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_tool_real_rect_select (GimpRectSelectTool * rect_tool,gint x,gint y,gint w,gint h)
name|gimp_rect_select_tool_real_rect_select
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|rect_tool
argument_list|)
expr_stmt|;
name|sel_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|rect_tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|gimp_channel_select_rectangle
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|sel_tool
operator|->
name|op
argument_list|,
name|options
operator|->
name|feather
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rect_select_tool_rect_select (GimpRectSelectTool * rect_tool,gint x,gint y,gint w,gint h)
name|gimp_rect_select_tool_rect_select
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RECT_SELECT_TOOL
argument_list|(
name|rect_tool
argument_list|)
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|rect_tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|auto_shrink
condition|)
block|{
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|x
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|tool
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|y
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
name|tool
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|w
operator|=
name|CLAMP
argument_list|(
name|w
argument_list|,
literal|0
argument_list|,
name|tool
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|width
operator|-
name|x
argument_list|)
expr_stmt|;
name|h
operator|=
name|CLAMP
argument_list|(
name|h
argument_list|,
literal|0
argument_list|,
name|tool
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
operator|-
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|w
operator|<
literal|1
operator|||
name|h
operator|<
literal|1
condition|)
return|return;
if|if
condition|(
operator|!
name|options
operator|->
name|shrink_merged
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_item_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|x
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
name|off_x
argument_list|,
name|off_x
operator|+
name|width
argument_list|)
expr_stmt|;
name|y
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
name|off_y
argument_list|,
name|off_y
operator|+
name|height
argument_list|)
expr_stmt|;
name|w
operator|=
name|CLAMP
argument_list|(
name|w
argument_list|,
literal|0
argument_list|,
name|off_x
operator|+
name|width
operator|-
name|x
argument_list|)
expr_stmt|;
name|h
operator|=
name|CLAMP
argument_list|(
name|h
argument_list|,
literal|0
argument_list|,
name|off_y
operator|+
name|height
operator|-
name|y
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_image_crop_auto_shrink
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|gimage
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|x
operator|+
name|w
argument_list|,
name|y
operator|+
name|h
argument_list|,
operator|!
name|options
operator|->
name|shrink_merged
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
condition|)
block|{
name|w
operator|=
name|x2
operator|-
name|x
expr_stmt|;
name|h
operator|=
name|y2
operator|-
name|y
expr_stmt|;
block|}
block|}
name|GIMP_RECT_SELECT_TOOL_GET_CLASS
argument_list|(
name|rect_tool
argument_list|)
operator|->
name|rect_select
argument_list|(
name|rect_tool
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_tool_update_options (GimpRectSelectTool * rect_sel,GimpDisplay * gdisp)
name|gimp_rect_select_tool_update_options
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpUnit
name|unit
decl_stmt|;
name|gdouble
name|width
decl_stmt|;
name|gdouble
name|height
decl_stmt|;
if|if
condition|(
name|rect_sel
operator|->
name|fixed_mode
operator|!=
name|GIMP_RECT_SELECT_MODE_FREE
condition|)
return|return;
if|if
condition|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|dot_for_dot
condition|)
block|{
name|width
operator|=
name|fabs
argument_list|(
name|rect_sel
operator|->
name|w
argument_list|)
expr_stmt|;
name|height
operator|=
name|fabs
argument_list|(
name|rect_sel
operator|->
name|h
argument_list|)
expr_stmt|;
name|unit
operator|=
name|GIMP_UNIT_PIXEL
expr_stmt|;
block|}
else|else
block|{
name|GimpImage
modifier|*
name|gimage
init|=
name|gdisp
operator|->
name|gimage
decl_stmt|;
name|unit
operator|=
name|gimage
operator|->
name|unit
expr_stmt|;
name|width
operator|=
operator|(
name|fabs
argument_list|(
name|rect_sel
operator|->
name|w
argument_list|)
operator|*
name|gimp_image_unit_get_factor
argument_list|(
name|gimage
argument_list|)
operator|/
name|gimage
operator|->
name|xresolution
operator|)
expr_stmt|;
name|height
operator|=
operator|(
name|fabs
argument_list|(
name|rect_sel
operator|->
name|h
argument_list|)
operator|*
name|gimp_image_unit_get_factor
argument_list|(
name|gimage
argument_list|)
operator|/
name|gimage
operator|->
name|yresolution
operator|)
expr_stmt|;
block|}
name|g_object_set
argument_list|(
name|GIMP_TOOL
argument_list|(
name|rect_sel
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|,
literal|"fixed-width"
argument_list|,
name|width
argument_list|,
literal|"fixed-height"
argument_list|,
name|height
argument_list|,
literal|"fixed-unit"
argument_list|,
name|unit
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

