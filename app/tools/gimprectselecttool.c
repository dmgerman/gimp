begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|"gdk/gdkkeysyms.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"edit_selection.h"
end_include

begin_include
include|#
directive|include
file|"floating_sel.h"
end_include

begin_include
include|#
directive|include
file|"rect_select.h"
end_include

begin_include
include|#
directive|include
file|"rect_selectP.h"
end_include

begin_include
include|#
directive|include
file|"selection_options.h"
end_include

begin_include
include|#
directive|include
file|"cursorutil.h"
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpunitmenu.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|STATUSBAR_SIZE
define|#
directive|define
name|STATUSBAR_SIZE
value|128
end_define

begin_comment
comment|/*  the rectangular selection tool options  */
end_comment

begin_decl_stmt
DECL|variable|rect_options
specifier|static
name|SelectionOptions
modifier|*
name|rect_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  in gimp, ellipses are rectangular, too ;)  */
end_comment

begin_decl_stmt
specifier|extern
name|SelectionOptions
modifier|*
name|ellipse_options
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|extern
name|void
name|ellipse_select
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|selection_tool_update_op_state
parameter_list|(
name|RectSelect
modifier|*
name|rect_sel
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|state
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*************************************/
end_comment

begin_comment
comment|/*  Rectangular selection apparatus  */
end_comment

begin_function
name|void
DECL|function|rect_select (GimpImage * gimage,int x,int y,int w,int h,int op,int feather,double feather_radius)
name|rect_select
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|,
name|int
name|op
parameter_list|,
name|int
name|feather
parameter_list|,
name|double
name|feather_radius
parameter_list|)
block|{
name|Channel
modifier|*
name|new_mask
decl_stmt|;
comment|/*  if applicable, replace the current selection  */
if|if
condition|(
name|op
operator|==
name|SELECTION_REPLACE
condition|)
name|gimage_mask_clear
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
else|else
name|gimage_mask_undo
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  if feathering for rect, make a new mask with the    *  rectangle and feather that with the old mask    */
if|if
condition|(
name|feather
condition|)
block|{
name|new_mask
operator|=
name|channel_new_mask
argument_list|(
name|gimage
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|channel_combine_rect
argument_list|(
name|new_mask
argument_list|,
name|ADD
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
name|channel_feather
argument_list|(
name|new_mask
argument_list|,
name|gimage_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|feather_radius
argument_list|,
name|feather_radius
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|channel_delete
argument_list|(
name|new_mask
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|op
operator|==
name|SELECTION_INTERSECT
condition|)
block|{
name|new_mask
operator|=
name|channel_new_mask
argument_list|(
name|gimage
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|channel_combine_rect
argument_list|(
name|new_mask
argument_list|,
name|ADD
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
name|channel_combine_mask
argument_list|(
name|gimage_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|new_mask
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|channel_delete
argument_list|(
name|new_mask
argument_list|)
expr_stmt|;
block|}
else|else
name|channel_combine_rect
argument_list|(
name|gimage_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|op
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
name|void
DECL|function|rect_select_button_press (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|rect_select_button_press
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|RectSelect
modifier|*
name|rect_sel
decl_stmt|;
name|gchar
name|select_mode
index|[
name|STATUSBAR_SIZE
index|]
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|GUnit
name|unit
init|=
name|UNIT_PIXEL
decl_stmt|;
name|float
name|unit_factor
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|rect_sel
operator|=
operator|(
name|RectSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|rect_sel
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|=
name|y
expr_stmt|;
switch|switch
condition|(
name|tool
operator|->
name|type
condition|)
block|{
case|case
name|RECT_SELECT
case|:
name|rect_sel
operator|->
name|fixed_size
operator|=
name|rect_options
operator|->
name|fixed_size
expr_stmt|;
name|rect_sel
operator|->
name|fixed_width
operator|=
name|rect_options
operator|->
name|fixed_width
expr_stmt|;
name|rect_sel
operator|->
name|fixed_height
operator|=
name|rect_options
operator|->
name|fixed_height
expr_stmt|;
name|unit
operator|=
name|rect_options
operator|->
name|fixed_unit
expr_stmt|;
break|break;
case|case
name|ELLIPSE_SELECT
case|:
name|rect_sel
operator|->
name|fixed_size
operator|=
name|ellipse_options
operator|->
name|fixed_size
expr_stmt|;
name|rect_sel
operator|->
name|fixed_width
operator|=
name|ellipse_options
operator|->
name|fixed_width
expr_stmt|;
name|rect_sel
operator|->
name|fixed_height
operator|=
name|ellipse_options
operator|->
name|fixed_height
expr_stmt|;
name|unit
operator|=
name|ellipse_options
operator|->
name|fixed_unit
expr_stmt|;
break|break;
default|default:
break|break;
block|}
switch|switch
condition|(
name|unit
condition|)
block|{
case|case
name|UNIT_PIXEL
case|:
break|break;
case|case
name|UNIT_PERCENT
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
name|gimp_unit_get_factor
argument_list|(
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
name|center
operator|=
name|FALSE
expr_stmt|;
name|gdk_pointer_grab
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
name|GDK_POINTER_MOTION_HINT_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|tool
operator|->
name|gdisp_ptr
operator|=
name|gdisp_ptr
expr_stmt|;
switch|switch
condition|(
name|rect_sel
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
name|gdisp_ptr
argument_list|,
name|bevent
argument_list|,
name|MaskTranslate
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
name|gdisp_ptr
argument_list|,
name|bevent
argument_list|,
name|MaskToLayerTranslate
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* initialize the statusbar display */
name|rect_sel
operator|->
name|context_id
operator|=
name|gtk_statusbar_get_context_id
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|gdisp
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"selection"
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|rect_sel
operator|->
name|op
condition|)
block|{
case|case
name|SELECTION_ADD
case|:
name|g_snprintf
argument_list|(
name|select_mode
argument_list|,
name|STATUSBAR_SIZE
argument_list|,
name|_
argument_list|(
literal|"Selection: ADD"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_SUB
case|:
name|g_snprintf
argument_list|(
name|select_mode
argument_list|,
name|STATUSBAR_SIZE
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
name|g_snprintf
argument_list|(
name|select_mode
argument_list|,
name|STATUSBAR_SIZE
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
name|g_snprintf
argument_list|(
name|select_mode
argument_list|,
name|STATUSBAR_SIZE
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
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|gdisp
operator|->
name|statusbar
argument_list|)
argument_list|,
name|rect_sel
operator|->
name|context_id
argument_list|,
name|select_mode
argument_list|)
expr_stmt|;
name|draw_core_start
argument_list|(
name|rect_sel
operator|->
name|core
argument_list|,
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|rect_select_button_release (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|rect_select_button_release
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|RectSelect
modifier|*
name|rect_sel
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|rect_sel
operator|=
operator|(
name|RectSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|gdk_pointer_ungrab
argument_list|(
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
name|gtk_statusbar_pop
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|gdisp
operator|->
name|statusbar
argument_list|)
argument_list|,
name|rect_sel
operator|->
name|context_id
argument_list|)
expr_stmt|;
name|draw_core_stop
argument_list|(
name|rect_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
comment|/*  First take care of the case where the user "cancels" the action  */
if|if
condition|(
operator|!
operator|(
name|bevent
operator|->
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
operator|!
name|rect_sel
operator|->
name|fixed_size
condition|)
block|{
comment|/*  If there is a floating selection, anchor it  */
if|if
condition|(
name|gimage_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
name|floating_sel_anchor
argument_list|(
name|gimage_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Otherwise, clear the selection mask  */
else|else
name|gimage_mask_clear
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
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
switch|switch
condition|(
name|tool
operator|->
name|type
condition|)
block|{
case|case
name|RECT_SELECT
case|:
name|rect_select
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|rect_sel
operator|->
name|op
argument_list|,
name|rect_options
operator|->
name|feather
argument_list|,
name|rect_options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
break|break;
case|case
name|ELLIPSE_SELECT
case|:
name|ellipse_select
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|rect_sel
operator|->
name|op
argument_list|,
name|ellipse_options
operator|->
name|antialias
argument_list|,
name|ellipse_options
operator|->
name|feather
argument_list|,
name|ellipse_options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
comment|/*  show selection on all views  */
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|rect_select_motion (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|rect_select_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|RectSelect
modifier|*
name|rect_sel
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gchar
name|size
index|[
name|STATUSBAR_SIZE
index|]
decl_stmt|;
name|int
name|ox
decl_stmt|,
name|oy
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|int
name|w
decl_stmt|,
name|h
decl_stmt|,
name|s
decl_stmt|;
name|int
name|tw
decl_stmt|,
name|th
decl_stmt|;
name|double
name|ratio
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|state
operator|!=
name|ACTIVE
condition|)
return|return;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|rect_sel
operator|=
operator|(
name|RectSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|draw_core_pause
argument_list|(
name|rect_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
comment|/* Calculate starting point */
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
literal|2
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
literal|2
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
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|rect_sel
operator|->
name|fixed_size
condition|)
block|{
if|if
condition|(
name|mevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
name|ratio
operator|=
call|(
name|double
call|)
argument_list|(
name|rect_sel
operator|->
name|fixed_height
operator|/
operator|(
name|double
operator|)
name|rect_sel
operator|->
name|fixed_width
argument_list|)
expr_stmt|;
name|tw
operator|=
name|x
operator|-
name|ox
expr_stmt|;
name|th
operator|=
name|y
operator|-
name|oy
expr_stmt|;
comment|/*          * This is probably an inefficient way to do it, but it gives         * nicer, more predictable results than the original agorithm         */
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
call|(
name|int
call|)
argument_list|(
name|tw
operator|*
name|ratio
argument_list|)
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
call|(
name|int
call|)
argument_list|(
name|th
operator|/
name|ratio
argument_list|)
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
block|}
else|else
block|{
name|w
operator|=
operator|(
name|x
operator|-
name|ox
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
name|y
operator|-
name|oy
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
block|}
block|}
else|else
block|{
name|w
operator|=
operator|(
name|x
operator|-
name|ox
operator|)
expr_stmt|;
name|h
operator|=
operator|(
name|y
operator|-
name|oy
operator|)
expr_stmt|;
block|}
comment|/*  If the shift key is down, then make the rectangle square (or ellipse circular) */
if|if
condition|(
operator|(
name|mevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
operator|&&
operator|!
name|rect_sel
operator|->
name|fixed_size
condition|)
block|{
name|s
operator|=
name|MAXIMUM
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
expr_stmt|;
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
comment|/*  If the control key is down, create the selection from the center out */
if|if
condition|(
name|mevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
if|if
condition|(
name|rect_sel
operator|->
name|fixed_size
condition|)
block|{
if|if
condition|(
name|mevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
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
literal|2
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
name|h
operator|*
literal|2
expr_stmt|;
block|}
else|else
block|{
name|rect_sel
operator|->
name|x
operator|=
name|ox
operator|-
name|w
operator|/
literal|2
expr_stmt|;
name|rect_sel
operator|->
name|y
operator|=
name|oy
operator|-
name|h
operator|/
literal|2
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
else|else
block|{
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
literal|2
operator|*
name|w
operator|+
literal|1
expr_stmt|;
name|rect_sel
operator|->
name|h
operator|=
literal|2
operator|*
name|h
operator|+
literal|1
expr_stmt|;
block|}
name|rect_sel
operator|->
name|center
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
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
name|rect_sel
operator|->
name|center
operator|=
name|FALSE
expr_stmt|;
block|}
name|gtk_statusbar_pop
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|gdisp
operator|->
name|statusbar
argument_list|)
argument_list|,
name|rect_sel
operator|->
name|context_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|dot_for_dot
condition|)
block|{
name|g_snprintf
argument_list|(
name|size
argument_list|,
name|STATUSBAR_SIZE
argument_list|,
name|gdisp
operator|->
name|cursor_format_str
argument_list|,
name|_
argument_list|(
literal|"Selection: "
argument_list|)
argument_list|,
name|abs
argument_list|(
name|rect_sel
operator|->
name|w
argument_list|)
argument_list|,
literal|" x "
argument_list|,
name|abs
argument_list|(
name|rect_sel
operator|->
name|h
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* show real world units */
block|{
name|float
name|unit_factor
init|=
name|gimp_unit_get_factor
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|)
decl_stmt|;
name|g_snprintf
argument_list|(
name|size
argument_list|,
name|STATUSBAR_SIZE
argument_list|,
name|gdisp
operator|->
name|cursor_format_str
argument_list|,
name|_
argument_list|(
literal|"Selection: "
argument_list|)
argument_list|,
operator|(
name|float
operator|)
name|abs
argument_list|(
name|rect_sel
operator|->
name|w
argument_list|)
operator|*
name|unit_factor
operator|/
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
literal|" x "
argument_list|,
operator|(
name|float
operator|)
name|abs
argument_list|(
name|rect_sel
operator|->
name|h
argument_list|)
operator|*
name|unit_factor
operator|/
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|)
expr_stmt|;
block|}
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|gdisp
operator|->
name|statusbar
argument_list|)
argument_list|,
name|rect_sel
operator|->
name|context_id
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|draw_core_resume
argument_list|(
name|rect_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|rect_select_draw (Tool * tool)
name|rect_select_draw
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|RectSelect
modifier|*
name|rect_sel
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|tool
operator|->
name|gdisp_ptr
expr_stmt|;
name|rect_sel
operator|=
operator|(
name|RectSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|x1
operator|=
name|MINIMUM
argument_list|(
name|rect_sel
operator|->
name|x
argument_list|,
name|rect_sel
operator|->
name|x
operator|+
name|rect_sel
operator|->
name|w
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MINIMUM
argument_list|(
name|rect_sel
operator|->
name|y
argument_list|,
name|rect_sel
operator|->
name|y
operator|+
name|rect_sel
operator|->
name|h
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MAXIMUM
argument_list|(
name|rect_sel
operator|->
name|x
argument_list|,
name|rect_sel
operator|->
name|x
operator|+
name|rect_sel
operator|->
name|w
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MAXIMUM
argument_list|(
name|rect_sel
operator|->
name|y
argument_list|,
name|rect_sel
operator|->
name|y
operator|+
name|rect_sel
operator|->
name|h
argument_list|)
expr_stmt|;
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|rect_sel
operator|->
name|core
operator|->
name|win
argument_list|,
name|rect_sel
operator|->
name|core
operator|->
name|gc
argument_list|,
literal|0
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|selection_tool_update_op_state (RectSelect * rect_sel,int x,int y,int state,GDisplay * gdisp)
specifier|static
name|selection_tool_update_op_state
parameter_list|(
name|RectSelect
modifier|*
name|rect_sel
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|state
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
if|if
condition|(
name|active_tool
operator|->
name|state
operator|==
name|ACTIVE
condition|)
return|return;
if|if
condition|(
name|state
operator|&
name|GDK_MOD1_MASK
operator|&&
operator|!
operator|(
name|layer_is_floating_sel
argument_list|(
name|gimage_get_active_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
operator|)
condition|)
name|rect_sel
operator|->
name|op
operator|=
name|SELECTION_MOVE_MASK
expr_stmt|;
comment|/* move just the selection mask */
elseif|else
if|if
condition|(
name|layer_is_floating_sel
argument_list|(
name|gimage_get_active_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
operator|||
operator|(
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
name|gdisplay_mask_value
argument_list|(
name|gdisp
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
operator|)
condition|)
name|rect_sel
operator|->
name|op
operator|=
name|SELECTION_MOVE
expr_stmt|;
comment|/* move the selection */
elseif|else
if|if
condition|(
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
operator|&&
operator|!
operator|(
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
condition|)
name|rect_sel
operator|->
name|op
operator|=
name|SELECTION_ADD
expr_stmt|;
comment|/* add to the selection */
elseif|else
if|if
condition|(
operator|(
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
operator|&&
operator|!
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
condition|)
name|rect_sel
operator|->
name|op
operator|=
name|SELECTION_SUB
expr_stmt|;
comment|/* subtract from the selection */
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
name|rect_sel
operator|->
name|op
operator|=
name|SELECTION_INTERSECT
expr_stmt|;
comment|/* intersect with selection */
else|else
name|rect_sel
operator|->
name|op
operator|=
name|SELECTION_REPLACE
expr_stmt|;
comment|/* replace the selection */
block|}
end_function

begin_function
name|void
DECL|function|rect_select_cursor_update (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|rect_select_cursor_update
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|int
name|active
decl_stmt|;
name|RectSelect
modifier|*
name|rect_sel
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|active
operator|=
operator|(
name|active_tool
operator|->
name|state
operator|==
name|ACTIVE
operator|)
expr_stmt|;
name|rect_sel
operator|=
operator|(
name|RectSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|selection_tool_update_op_state
argument_list|(
name|rect_sel
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|,
name|mevent
operator|->
name|state
argument_list|,
name|gdisp_ptr
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|rect_sel
operator|->
name|op
condition|)
block|{
case|case
name|SELECTION_ADD
case|:
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GIMP_MOUSE1P_CURSOR
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_SUB
case|:
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GIMP_MOUSE1M_CURSOR
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_INTERSECT
case|:
comment|/* need a real cursor for this one */
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GIMP_BIGCIRC_CURSOR
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_REPLACE
case|:
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_TCROSS
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_MOVE_MASK
case|:
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_DIAMOND_CROSS
argument_list|)
expr_stmt|;
break|break;
case|case
name|SELECTION_MOVE
case|:
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_FLEUR
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|rect_select_control (Tool * tool,int action,gpointer gdisp_ptr)
name|rect_select_control
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|int
name|action
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|RectSelect
modifier|*
name|rect_sel
decl_stmt|;
name|rect_sel
operator|=
operator|(
name|RectSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
name|draw_core_pause
argument_list|(
name|rect_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|RESUME
case|:
name|draw_core_resume
argument_list|(
name|rect_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|HALT
case|:
name|draw_core_stop
argument_list|(
name|rect_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rect_select_options_reset ()
name|rect_select_options_reset
parameter_list|()
block|{
name|selection_options_reset
argument_list|(
name|rect_options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_rect_select ()
name|tools_new_rect_select
parameter_list|()
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|RectSelect
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|rect_options
condition|)
block|{
name|rect_options
operator|=
name|selection_options_new
argument_list|(
name|RECT_SELECT
argument_list|,
name|rect_select_options_reset
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|RECT_SELECT
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|rect_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|=
operator|(
name|Tool
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Tool
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
operator|(
name|RectSelect
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|RectSelect
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|core
operator|=
name|draw_core_new
argument_list|(
name|rect_select_draw
argument_list|)
expr_stmt|;
name|private
operator|->
name|x
operator|=
name|private
operator|->
name|y
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|w
operator|=
name|private
operator|->
name|h
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|op
operator|=
name|SELECTION_REPLACE
expr_stmt|;
name|tool
operator|->
name|type
operator|=
name|RECT_SELECT
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
literal|0
expr_stmt|;
comment|/*  Allow scrolling  */
name|tool
operator|->
name|auto_snap_to
operator|=
name|TRUE
expr_stmt|;
name|tool
operator|->
name|private
operator|=
operator|(
name|void
operator|*
operator|)
name|private
expr_stmt|;
name|tool
operator|->
name|button_press_func
operator|=
name|rect_select_button_press
expr_stmt|;
name|tool
operator|->
name|button_release_func
operator|=
name|rect_select_button_release
expr_stmt|;
name|tool
operator|->
name|motion_func
operator|=
name|rect_select_motion
expr_stmt|;
name|tool
operator|->
name|arrow_keys_func
operator|=
name|standard_arrow_keys_func
expr_stmt|;
name|tool
operator|->
name|modifier_key_func
operator|=
name|standard_modifier_key_func
expr_stmt|;
name|tool
operator|->
name|cursor_update_func
operator|=
name|rect_select_cursor_update
expr_stmt|;
name|tool
operator|->
name|control_func
operator|=
name|rect_select_control
expr_stmt|;
name|tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_rect_select (Tool * tool)
name|tools_free_rect_select
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|RectSelect
modifier|*
name|rect_sel
decl_stmt|;
name|rect_sel
operator|=
operator|(
name|RectSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|draw_core_free
argument_list|(
name|rect_sel
operator|->
name|core
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rect_sel
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

