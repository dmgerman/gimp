begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"draw_core.h"
end_include

begin_include
include|#
directive|include
file|"edit_selection.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"floating_sel.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay_ops.h"
end_include

begin_include
include|#
directive|include
file|"move.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_typedef
DECL|typedef|MoveTool
typedef|typedef
name|struct
name|_MoveTool
name|MoveTool
typedef|;
end_typedef

begin_struct
DECL|struct|_MoveTool
struct|struct
name|_MoveTool
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
DECL|member|guide
name|Guide
modifier|*
name|guide
decl_stmt|;
DECL|member|guide_disp
name|int
name|guide_disp
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  move tool action functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|move_tool_button_press
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_tool_button_release
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_tool_motion
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_tool_cursor_update
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_tool_control
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|int
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_create_gc
parameter_list|(
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|move_options
specifier|static
name|void
modifier|*
name|move_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|move_gc
specifier|static
name|GdkGC
modifier|*
name|move_gc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  move action functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|move_tool_button_press (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|move_tool_button_press
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
name|MoveTool
modifier|*
name|move
decl_stmt|;
name|Layer
modifier|*
name|layer
decl_stmt|;
name|Guide
modifier|*
name|guide
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|move
operator|=
operator|(
name|MoveTool
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|tool
operator|->
name|gdisp_ptr
operator|=
name|gdisp_ptr
expr_stmt|;
name|move
operator|->
name|layer
operator|=
name|NULL
expr_stmt|;
name|move
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
name|move
operator|->
name|guide_disp
operator|=
operator|-
literal|1
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
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
block|{
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
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|,
name|bevent
argument_list|,
name|LayerTranslate
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gdisp
operator|->
name|draw_guides
operator|&&
operator|(
name|guide
operator|=
name|gdisplay_find_guide
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
argument_list|)
operator|)
condition|)
block|{
name|undo_push_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|move
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
name|gdisplays_expose_guide
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|ID
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimage_remove_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gdisplay_flush
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gimage_add_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|move
operator|->
name|guide
operator|=
name|guide
expr_stmt|;
name|move
operator|->
name|guide_disp
operator|=
name|gdisp
operator|->
name|ID
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|move_tool_motion
argument_list|(
name|tool
argument_list|,
name|NULL
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|layer
operator|=
name|gimage_pick_correlate_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
operator|)
condition|)
block|{
comment|/*  If there is a floating selection, and this aint it, use the move tool  */
if|if
condition|(
name|gimage_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|&&
operator|!
name|layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
name|move
operator|->
name|layer
operator|=
name|gimage_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
comment|/*  Otherwise, init the edit selection  */
else|else
block|{
name|gimage_set_active_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|layer
argument_list|)
expr_stmt|;
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|,
name|bevent
argument_list|,
name|LayerTranslate
argument_list|)
expr_stmt|;
block|}
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
block|}
block|}
comment|/* if we've got an active tool grab the pointer */
if|if
condition|(
name|tool
operator|->
name|state
operator|==
name|ACTIVE
condition|)
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_draw_guide (GDisplay * gdisp,Guide * guide)
name|move_draw_guide
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|Guide
modifier|*
name|guide
parameter_list|)
block|{
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|int
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|int
name|w
decl_stmt|,
name|h
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
if|if
condition|(
operator|!
name|move_gc
condition|)
name|move_create_gc
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
if|if
condition|(
name|guide
operator|->
name|position
operator|==
operator|-
literal|1
condition|)
return|return;
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gdk_window_get_size
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|guide
operator|->
name|orientation
condition|)
block|{
case|case
name|HORIZONTAL_GUIDE
case|:
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
name|guide
operator|->
name|position
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|x1
operator|<
literal|0
condition|)
name|x1
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|x2
operator|>
name|w
condition|)
name|x2
operator|=
name|w
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|move_gc
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
name|x2
argument_list|,
name|y
argument_list|)
expr_stmt|;
break|break;
case|case
name|VERTICAL_GUIDE
case|:
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
name|guide
operator|->
name|position
argument_list|,
literal|0
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|y1
operator|<
literal|0
condition|)
name|y1
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|y2
operator|>
name|h
condition|)
name|y2
operator|=
name|h
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|move_gc
argument_list|,
name|x
argument_list|,
name|y1
argument_list|,
name|x
argument_list|,
name|y2
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_tool_button_release (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|move_tool_button_release
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
name|MoveTool
modifier|*
name|move
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|int
name|remove_guide
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|int
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
name|gdisp_ptr
expr_stmt|;
name|move
operator|=
operator|(
name|MoveTool
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
name|gdk_pointer_ungrab
argument_list|(
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|guide
condition|)
block|{
name|tool
operator|->
name|scroll_lock
operator|=
name|FALSE
expr_stmt|;
name|remove_guide
operator|=
name|FALSE
expr_stmt|;
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
name|gdisp
operator|->
name|disp_width
argument_list|,
name|gdisp
operator|->
name|disp_height
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|x1
operator|<
literal|0
condition|)
name|x1
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|y1
operator|<
literal|0
condition|)
name|y1
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|x2
operator|>
name|gdisp
operator|->
name|gimage
operator|->
name|width
condition|)
name|x2
operator|=
name|gdisp
operator|->
name|gimage
operator|->
name|width
expr_stmt|;
if|if
condition|(
name|y2
operator|>
name|gdisp
operator|->
name|gimage
operator|->
name|height
condition|)
name|y2
operator|=
name|gdisp
operator|->
name|gimage
operator|->
name|height
expr_stmt|;
switch|switch
condition|(
name|move
operator|->
name|guide
operator|->
name|orientation
condition|)
block|{
case|case
name|HORIZONTAL_GUIDE
case|:
if|if
condition|(
operator|(
name|move
operator|->
name|guide
operator|->
name|position
operator|<
name|y1
operator|)
operator|||
operator|(
name|move
operator|->
name|guide
operator|->
name|position
operator|>
name|y2
operator|)
condition|)
name|remove_guide
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|VERTICAL_GUIDE
case|:
if|if
condition|(
operator|(
name|move
operator|->
name|guide
operator|->
name|position
operator|<
name|x1
operator|)
operator|||
operator|(
name|move
operator|->
name|guide
operator|->
name|position
operator|>
name|x2
operator|)
condition|)
name|remove_guide
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
name|gdisplays_expose_guide
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|ID
argument_list|,
name|move
operator|->
name|guide
argument_list|)
expr_stmt|;
if|if
condition|(
name|remove_guide
condition|)
block|{
name|move_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|move
operator|->
name|guide
argument_list|)
expr_stmt|;
name|move
operator|->
name|guide
operator|->
name|position
operator|=
operator|-
literal|1
expr_stmt|;
name|move
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
name|move
operator|->
name|guide_disp
operator|=
operator|-
literal|1
expr_stmt|;
block|}
else|else
block|{
name|move_tool_motion
argument_list|(
name|tool
argument_list|,
name|NULL
argument_list|,
name|gdisp_ptr
argument_list|)
expr_stmt|;
block|}
name|selection_resume
argument_list|(
name|gdisp
operator|->
name|select
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|guide
condition|)
name|gdisplay_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
if|if
condition|(
name|move
operator|->
name|layer
condition|)
block|{
name|floating_sel_anchor
argument_list|(
name|move
operator|->
name|layer
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_tool_motion (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|move_tool_motion
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|MoveTool
modifier|*
name|private
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdisp
operator|=
name|gdisp_ptr
expr_stmt|;
name|private
operator|=
name|tool
operator|->
name|private
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|guide
condition|)
block|{
name|move_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|private
operator|->
name|guide
argument_list|)
expr_stmt|;
if|if
condition|(
name|mevent
condition|)
block|{
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
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|guide
operator|->
name|orientation
operator|==
name|HORIZONTAL_GUIDE
condition|)
name|private
operator|->
name|guide
operator|->
name|position
operator|=
name|y
expr_stmt|;
else|else
name|private
operator|->
name|guide
operator|->
name|position
operator|=
name|x
expr_stmt|;
name|move_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|private
operator|->
name|guide
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_tool_cursor_update (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|move_tool_cursor_update
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
name|MoveTool
modifier|*
name|move
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|Guide
modifier|*
name|guide
decl_stmt|;
name|Layer
modifier|*
name|layer
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|move
operator|=
name|tool
operator|->
name|private
expr_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
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
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|mevent
operator|->
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_DIAMOND_CROSS
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|mevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_FLEUR
argument_list|)
expr_stmt|;
else|else
block|{
if|if
condition|(
name|gdisp
operator|->
name|draw_guides
operator|&&
operator|(
name|guide
operator|=
name|gdisplay_find_guide
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
argument_list|)
operator|)
condition|)
block|{
name|tool
operator|->
name|gdisp_ptr
operator|=
name|gdisp_ptr
expr_stmt|;
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_HAND2
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|state
operator|!=
name|ACTIVE
condition|)
block|{
if|if
condition|(
name|move
operator|->
name|guide
condition|)
block|{
name|gdisp
operator|=
name|gdisplay_get_ID
argument_list|(
name|move
operator|->
name|guide_disp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
condition|)
name|gdisplay_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gdisp
operator|=
name|gdisp_ptr
expr_stmt|;
name|gdisplay_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|move
operator|->
name|guide
operator|=
name|guide
expr_stmt|;
name|move
operator|->
name|guide_disp
operator|=
name|gdisp
operator|->
name|ID
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|(
name|layer
operator|=
name|gimage_pick_correlate_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
operator|)
condition|)
block|{
comment|/*  if there is a floating selection, and this aint it...  */
if|if
condition|(
name|gimage_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|&&
operator|!
name|layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_SB_DOWN_ARROW
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|layer
operator|==
name|gdisp
operator|->
name|gimage
operator|->
name|active_layer
condition|)
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_FLEUR
argument_list|)
expr_stmt|;
else|else
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_HAND2
argument_list|)
expr_stmt|;
block|}
else|else
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_TOP_LEFT_ARROW
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_tool_control (Tool * tool,int action,gpointer gdisp_ptr)
name|move_tool_control
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
name|MoveTool
modifier|*
name|move
decl_stmt|;
name|move
operator|=
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
break|break;
case|case
name|RESUME
case|:
if|if
condition|(
name|move
operator|->
name|guide
condition|)
name|gdisplay_draw_guide
argument_list|(
name|gdisp_ptr
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|HALT
case|:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_create_gc (GDisplay * gdisp)
name|move_create_gc
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
if|if
condition|(
operator|!
name|move_gc
condition|)
block|{
name|GdkGCValues
name|values
decl_stmt|;
name|values
operator|.
name|foreground
operator|.
name|pixel
operator|=
name|gdisplay_white_pixel
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|values
operator|.
name|function
operator|=
name|GDK_INVERT
expr_stmt|;
name|move_gc
operator|=
name|gdk_gc_new_with_values
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
operator|&
name|values
argument_list|,
name|GDK_GC_FUNCTION
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|move_tool_start_hguide (Tool * tool,void * data)
name|move_tool_start_hguide
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|MoveTool
modifier|*
name|private
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|data
expr_stmt|;
name|selection_pause
argument_list|(
name|gdisp
operator|->
name|select
argument_list|)
expr_stmt|;
name|tool
operator|->
name|gdisp_ptr
operator|=
name|gdisp
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
name|private
operator|=
name|tool
operator|->
name|private
expr_stmt|;
name|private
operator|->
name|guide
operator|=
name|gimage_add_hguide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|undo_push_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|private
operator|->
name|guide
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|move_tool_start_vguide (Tool * tool,void * data)
name|move_tool_start_vguide
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|MoveTool
modifier|*
name|private
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|data
expr_stmt|;
name|selection_pause
argument_list|(
name|gdisp
operator|->
name|select
argument_list|)
expr_stmt|;
name|tool
operator|->
name|gdisp_ptr
operator|=
name|gdisp
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
name|private
operator|=
name|tool
operator|->
name|private
expr_stmt|;
name|private
operator|->
name|guide
operator|=
name|gimage_add_vguide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|undo_push_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|private
operator|->
name|guide
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_move_tool ()
name|tools_new_move_tool
parameter_list|()
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|MoveTool
modifier|*
name|private
decl_stmt|;
if|if
condition|(
operator|!
name|move_options
condition|)
name|move_options
operator|=
name|tools_register_no_options
argument_list|(
name|MOVE
argument_list|,
literal|"Move Tool Options"
argument_list|)
expr_stmt|;
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
name|MoveTool
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|MoveTool
argument_list|)
argument_list|)
expr_stmt|;
name|tool
operator|->
name|type
operator|=
name|MOVE
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
name|FALSE
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
name|move_tool_button_press
expr_stmt|;
name|tool
operator|->
name|button_release_func
operator|=
name|move_tool_button_release
expr_stmt|;
name|tool
operator|->
name|motion_func
operator|=
name|move_tool_motion
expr_stmt|;
name|tool
operator|->
name|arrow_keys_func
operator|=
name|edit_sel_arrow_keys_func
expr_stmt|;
name|tool
operator|->
name|cursor_update_func
operator|=
name|move_tool_cursor_update
expr_stmt|;
name|tool
operator|->
name|control_func
operator|=
name|move_tool_control
expr_stmt|;
name|private
operator|->
name|layer
operator|=
name|NULL
expr_stmt|;
name|private
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_move_tool (Tool * tool)
name|tools_free_move_tool
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|MoveTool
modifier|*
name|move
decl_stmt|;
name|move
operator|=
operator|(
name|MoveTool
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|gdisp_ptr
condition|)
block|{
if|if
condition|(
name|move
operator|->
name|guide
condition|)
name|gdisplay_draw_guide
argument_list|(
name|tool
operator|->
name|gdisp_ptr
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|move
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

