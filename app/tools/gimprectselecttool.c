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
file|"core/gimp-utils.h"
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

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpRectSelectTool
argument_list|,
name|gimp_rect_select_tool
argument_list|,
name|GIMP_TYPE_SELECTION_TOOL
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_rect_select_tool_parent_class
end_define

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
literal|"Rectangle Select"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Select rectangular regions"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Rectangle Select"
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
name|GIMP_TOOL_CURSOR_RECT_SELECT
argument_list|)
expr_stmt|;
name|rect_select
operator|->
name|sx
operator|=
name|rect_select
operator|->
name|sy
operator|=
literal|0
expr_stmt|;
name|rect_select
operator|->
name|x
operator|=
name|rect_select
operator|->
name|y
operator|=
literal|0
expr_stmt|;
name|rect_select
operator|->
name|w
operator|=
name|rect_select
operator|->
name|h
operator|=
literal|0
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
init|=
name|GIMP_RECT_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
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
name|GimpUnit
name|unit
init|=
name|GIMP_UNIT_PIXEL
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
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
name|sx
operator|=
name|RINT
argument_list|(
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|sy
operator|=
name|RINT
argument_list|(
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|x
operator|=
literal|0
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|=
literal|0
expr_stmt|;
name|rect_sel
operator|->
name|w
operator|=
literal|0
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
literal|0
expr_stmt|;
name|rect_sel
operator|->
name|lx
operator|=
name|RINT
argument_list|(
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|ly
operator|=
name|RINT
argument_list|(
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|center
operator|=
name|FALSE
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
if|if
condition|(
name|gimp_selection_tool_start_edit
argument_list|(
name|sel_tool
argument_list|,
name|coords
argument_list|)
condition|)
return|return;
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
init|=
name|GIMP_RECT_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|gdisp
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
if|if
condition|(
name|rect_sel
operator|->
name|w
operator|==
literal|0
operator|||
name|rect_sel
operator|->
name|h
operator|==
literal|0
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
name|gimp_rect_select_tool_rect_select
argument_list|(
name|rect_sel
argument_list|,
name|rect_sel
operator|->
name|x
argument_list|,
name|rect_sel
operator|->
name|y
argument_list|,
name|rect_sel
operator|->
name|w
argument_list|,
name|rect_sel
operator|->
name|h
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
init|=
name|GIMP_RECT_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
init|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gint
name|mx
decl_stmt|,
name|my
decl_stmt|;
name|gdouble
name|ratio
decl_stmt|;
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
name|mx
operator|=
name|RINT
argument_list|(
name|coords
operator|->
name|x
argument_list|)
operator|-
name|rect_sel
operator|->
name|lx
expr_stmt|;
name|my
operator|=
name|RINT
argument_list|(
name|coords
operator|->
name|y
argument_list|)
operator|-
name|rect_sel
operator|->
name|ly
expr_stmt|;
name|rect_sel
operator|->
name|sx
operator|+=
name|mx
expr_stmt|;
name|rect_sel
operator|->
name|sy
operator|+=
name|my
expr_stmt|;
name|rect_sel
operator|->
name|x
operator|+=
name|mx
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|+=
name|my
expr_stmt|;
block|}
else|else
block|{
comment|/* Change the selection rectangle's size, first calculate absolute        * width and height, then take care of quadrants.        */
if|if
condition|(
name|rect_sel
operator|->
name|fixed_mode
operator|==
name|GIMP_RECT_SELECT_MODE_FIXED_SIZE
condition|)
block|{
name|rect_sel
operator|->
name|w
operator|=
name|RINT
argument_list|(
name|rect_sel
operator|->
name|fixed_width
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
name|RINT
argument_list|(
name|rect_sel
operator|->
name|fixed_height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|rect_sel
operator|->
name|w
operator|=
name|abs
argument_list|(
name|RINT
argument_list|(
name|coords
operator|->
name|x
argument_list|)
operator|-
name|rect_sel
operator|->
name|sx
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
name|abs
argument_list|(
name|RINT
argument_list|(
name|coords
operator|->
name|y
argument_list|)
operator|-
name|rect_sel
operator|->
name|sy
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|rect_sel
operator|->
name|fixed_mode
operator|==
name|GIMP_RECT_SELECT_MODE_FIXED_RATIO
condition|)
block|{
name|ratio
operator|=
name|rect_sel
operator|->
name|fixed_height
operator|/
name|rect_sel
operator|->
name|fixed_width
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|gdouble
operator|)
name|rect_sel
operator|->
name|h
operator|)
operator|/
operator|(
operator|(
name|gdouble
operator|)
name|rect_sel
operator|->
name|w
operator|)
operator|>
name|ratio
condition|)
block|{
name|rect_sel
operator|->
name|w
operator|=
name|RINT
argument_list|(
name|rect_sel
operator|->
name|h
operator|/
name|ratio
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|rect_sel
operator|->
name|h
operator|=
name|RINT
argument_list|(
name|rect_sel
operator|->
name|w
operator|*
name|ratio
argument_list|)
expr_stmt|;
block|}
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
if|if
condition|(
name|rect_sel
operator|->
name|w
operator|>
name|rect_sel
operator|->
name|h
condition|)
block|{
name|rect_sel
operator|->
name|h
operator|=
name|rect_sel
operator|->
name|w
expr_stmt|;
block|}
else|else
block|{
name|rect_sel
operator|->
name|w
operator|=
name|rect_sel
operator|->
name|h
expr_stmt|;
block|}
block|}
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
comment|/*  If the control key is down, create the selection from the center out  */
if|if
condition|(
name|rect_sel
operator|->
name|fixed_mode
operator|==
name|GIMP_RECT_SELECT_MODE_FIXED_SIZE
condition|)
block|{
comment|/*  Fixed size selection is simply centered over start point  */
name|rect_sel
operator|->
name|x
operator|=
name|RINT
argument_list|(
name|rect_sel
operator|->
name|sx
operator|-
name|rect_sel
operator|->
name|w
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|=
name|RINT
argument_list|(
name|rect_sel
operator|->
name|sy
operator|-
name|rect_sel
operator|->
name|h
operator|/
literal|2.0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  Non-fixed size is mirrored over starting point  */
name|rect_sel
operator|->
name|x
operator|=
name|rect_sel
operator|->
name|sx
operator|-
name|rect_sel
operator|->
name|w
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|=
name|rect_sel
operator|->
name|sy
operator|-
name|rect_sel
operator|->
name|h
expr_stmt|;
name|rect_sel
operator|->
name|w
operator|=
name|rect_sel
operator|->
name|w
operator|*
literal|2
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
name|rect_sel
operator|->
name|h
operator|*
literal|2
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/*  Make (rect->x, rect->y) upper left hand point of selection  */
if|if
condition|(
name|coords
operator|->
name|x
operator|>
name|rect_sel
operator|->
name|sx
condition|)
block|{
name|rect_sel
operator|->
name|x
operator|=
name|rect_sel
operator|->
name|sx
expr_stmt|;
block|}
else|else
block|{
name|rect_sel
operator|->
name|x
operator|=
name|rect_sel
operator|->
name|sx
operator|-
name|rect_sel
operator|->
name|w
expr_stmt|;
block|}
if|if
condition|(
name|coords
operator|->
name|y
operator|>
name|rect_sel
operator|->
name|sy
condition|)
block|{
name|rect_sel
operator|->
name|y
operator|=
name|rect_sel
operator|->
name|sy
expr_stmt|;
block|}
else|else
block|{
name|rect_sel
operator|->
name|y
operator|=
name|rect_sel
operator|->
name|sy
operator|-
name|rect_sel
operator|->
name|h
expr_stmt|;
block|}
block|}
block|}
name|rect_sel
operator|->
name|lx
operator|=
name|RINT
argument_list|(
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|ly
operator|=
name|RINT
argument_list|(
name|coords
operator|->
name|y
argument_list|)
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
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gimp_tool_push_status_coords
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|_
argument_list|(
literal|"Selection: "
argument_list|)
argument_list|,
name|rect_sel
operator|->
name|w
argument_list|,
literal|" Ã "
argument_list|,
name|rect_sel
operator|->
name|h
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
name|rect_sel
operator|->
name|x
argument_list|,
name|rect_sel
operator|->
name|y
argument_list|,
name|rect_sel
operator|->
name|w
argument_list|,
name|rect_sel
operator|->
name|h
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
init|=
name|GIMP_TOOL
argument_list|(
name|rect_tool
argument_list|)
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
init|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|rect_tool
argument_list|)
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
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
name|off_x
init|=
literal|0
decl_stmt|;
name|gint
name|off_y
init|=
literal|0
decl_stmt|;
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
literal|0
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
argument_list|,
name|tool
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
condition|)
block|{
return|return;
block|}
if|if
condition|(
operator|!
name|options
operator|->
name|shrink_merged
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
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
if|if
condition|(
operator|!
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
condition|)
block|{
return|return;
block|}
name|x
operator|-=
name|off_x
expr_stmt|;
name|y
operator|-=
name|off_y
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
name|x
operator|+=
name|off_x
expr_stmt|;
name|y
operator|+=
name|off_y
expr_stmt|;
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
name|GimpDisplayShell
modifier|*
name|shell
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
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|unit
operator|==
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|width
operator|=
name|rect_sel
operator|->
name|w
expr_stmt|;
name|height
operator|=
name|rect_sel
operator|->
name|h
expr_stmt|;
block|}
else|else
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gdisp
operator|->
name|gimage
decl_stmt|;
name|width
operator|=
operator|(
name|rect_sel
operator|->
name|w
operator|*
name|_gimp_unit_get_factor
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|shell
operator|->
name|unit
argument_list|)
operator|/
name|image
operator|->
name|xresolution
operator|)
expr_stmt|;
name|height
operator|=
operator|(
name|rect_sel
operator|->
name|h
operator|*
name|_gimp_unit_get_factor
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|shell
operator|->
name|unit
argument_list|)
operator|/
name|image
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
name|shell
operator|->
name|unit
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

