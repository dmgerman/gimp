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
file|<string.h>
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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"draw_core.h"
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
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"scan_convert.h"
end_include

begin_include
include|#
directive|include
file|"edit_selection.h"
end_include

begin_include
include|#
directive|include
file|"free_select.h"
end_include

begin_include
include|#
directive|include
file|"rect_select.h"
end_include

begin_include
include|#
directive|include
file|"selection_options.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_define
DECL|macro|DEFAULT_MAX_INC
define|#
directive|define
name|DEFAULT_MAX_INC
value|1024
end_define

begin_define
DECL|macro|SUPERSAMPLE
define|#
directive|define
name|SUPERSAMPLE
value|3
end_define

begin_define
DECL|macro|SUPERSAMPLE2
define|#
directive|define
name|SUPERSAMPLE2
value|9
end_define

begin_comment
comment|/*  the free selection structures  */
end_comment

begin_typedef
DECL|typedef|FreeSelect
typedef|typedef
name|struct
name|_FreeSelect
name|FreeSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_FreeSelect
struct|struct
name|_FreeSelect
block|{
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/*  Core select object                      */
DECL|member|op
name|SelectOps
name|op
decl_stmt|;
comment|/*  selection operation (ADD, SUB, etc)     */
DECL|member|current_x
name|gint
name|current_x
decl_stmt|;
comment|/*  these values are updated on every motion event  */
DECL|member|current_y
name|gint
name|current_y
decl_stmt|;
comment|/*  (enables immediate cursor updating on modifier 			 *   key events).  */
DECL|member|num_pts
name|gint
name|num_pts
decl_stmt|;
comment|/*  Number of points in the polygon         */
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|free_select_button_press
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|free_select_button_release
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|free_select_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  the free selection tool options  */
end_comment

begin_decl_stmt
DECL|variable|free_options
specifier|static
name|SelectionOptions
modifier|*
name|free_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  The global array of XPoints for drawing the polygon...  */
end_comment

begin_decl_stmt
DECL|variable|global_pts
specifier|static
name|GdkPoint
modifier|*
name|global_pts
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|max_segs
specifier|static
name|gint
name|max_segs
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  functions  */
end_comment

begin_function
specifier|static
name|gint
DECL|function|add_point (gint num_pts,gint x,gint y)
name|add_point
parameter_list|(
name|gint
name|num_pts
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
if|if
condition|(
name|num_pts
operator|>=
name|max_segs
condition|)
block|{
name|max_segs
operator|+=
name|DEFAULT_MAX_INC
expr_stmt|;
name|global_pts
operator|=
operator|(
name|GdkPoint
operator|*
operator|)
name|g_realloc
argument_list|(
operator|(
name|void
operator|*
operator|)
name|global_pts
argument_list|,
sizeof|sizeof
argument_list|(
name|GdkPoint
argument_list|)
operator|*
name|max_segs
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|global_pts
condition|)
name|gimp_fatal_error
argument_list|(
literal|"add_point(): Unable to reallocate points array in free_select."
argument_list|)
expr_stmt|;
block|}
name|global_pts
index|[
name|num_pts
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|global_pts
index|[
name|num_pts
index|]
operator|.
name|y
operator|=
name|y
expr_stmt|;
return|return
literal|1
return|;
block|}
end_function

begin_function
specifier|static
name|GimpChannel
modifier|*
DECL|function|scan_convert (GimpImage * gimage,gint num_pts,ScanConvertPoint * pts,gint width,gint height,gboolean antialias)
name|scan_convert
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|num_pts
parameter_list|,
name|ScanConvertPoint
modifier|*
name|pts
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|ScanConverter
modifier|*
name|sc
decl_stmt|;
name|sc
operator|=
name|scan_converter_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|antialias
condition|?
name|SUPERSAMPLE
else|:
literal|1
argument_list|)
expr_stmt|;
name|scan_converter_add_points
argument_list|(
name|sc
argument_list|,
name|num_pts
argument_list|,
name|pts
argument_list|)
expr_stmt|;
name|mask
operator|=
name|scan_converter_to_channel
argument_list|(
name|sc
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|scan_converter_free
argument_list|(
name|sc
argument_list|)
expr_stmt|;
return|return
name|mask
return|;
block|}
end_function

begin_comment
comment|/*************************************/
end_comment

begin_comment
comment|/*  Polygonal selection apparatus    */
end_comment

begin_function
name|void
DECL|function|free_select (GImage * gimage,gint num_pts,ScanConvertPoint * pts,SelectOps op,gboolean antialias,gboolean feather,gdouble feather_radius)
name|free_select
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|num_pts
parameter_list|,
name|ScanConvertPoint
modifier|*
name|pts
parameter_list|,
name|SelectOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
comment|/*  if applicable, replace the current selection  */
comment|/*  or insure that a floating selection is anchored down...  */
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
name|mask
operator|=
name|scan_convert
argument_list|(
name|gimage
argument_list|,
name|num_pts
argument_list|,
name|pts
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
if|if
condition|(
name|feather
condition|)
name|gimp_channel_feather
argument_list|(
name|mask
argument_list|,
name|gimp_image_get_mask
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
else|else
name|gimp_channel_combine_mask
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|mask
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|free_select_button_press (Tool * tool,GdkEventButton * bevent,GDisplay * gdisp)
name|free_select_button_press
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|tool
operator|->
name|private
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
name|gdisp
operator|=
name|gdisp
expr_stmt|;
switch|switch
condition|(
name|free_sel
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
name|bevent
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
name|bevent
argument_list|,
name|EDIT_MASK_TO_LAYER_TRANSLATE
argument_list|)
expr_stmt|;
return|return;
default|default:
break|break;
block|}
name|add_point
argument_list|(
literal|0
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
expr_stmt|;
name|free_sel
operator|->
name|num_pts
operator|=
literal|1
expr_stmt|;
name|draw_core_start
argument_list|(
name|free_sel
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
specifier|static
name|void
DECL|function|free_select_button_release (Tool * tool,GdkEventButton * bevent,GDisplay * gdisp)
name|free_select_button_release
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|ScanConvertPoint
modifier|*
name|pts
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
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
name|draw_core_stop
argument_list|(
name|free_sel
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
if|if
condition|(
name|free_sel
operator|->
name|op
operator|==
name|SELECTION_ANCHOR
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
name|pts
operator|=
name|g_new
argument_list|(
name|ScanConvertPoint
argument_list|,
name|free_sel
operator|->
name|num_pts
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|free_sel
operator|->
name|num_pts
condition|;
name|i
operator|++
control|)
block|{
name|gdisplay_untransform_coords_f
argument_list|(
name|gdisp
argument_list|,
name|global_pts
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|global_pts
index|[
name|i
index|]
operator|.
name|y
argument_list|,
operator|&
name|pts
index|[
name|i
index|]
operator|.
name|x
argument_list|,
operator|&
name|pts
index|[
name|i
index|]
operator|.
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|free_select
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|free_sel
operator|->
name|num_pts
argument_list|,
name|pts
argument_list|,
name|free_sel
operator|->
name|op
argument_list|,
name|free_options
operator|->
name|antialias
argument_list|,
name|free_options
operator|->
name|feather
argument_list|,
name|free_options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pts
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|free_select_motion (Tool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|free_select_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
comment|/*  needed for immediate cursor update on modifier event  */
name|free_sel
operator|->
name|current_x
operator|=
name|mevent
operator|->
name|x
expr_stmt|;
name|free_sel
operator|->
name|current_y
operator|=
name|mevent
operator|->
name|y
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|state
operator|!=
name|ACTIVE
condition|)
return|return;
if|if
condition|(
name|free_sel
operator|->
name|op
operator|==
name|SELECTION_ANCHOR
condition|)
block|{
name|free_sel
operator|->
name|op
operator|=
name|SELECTION_REPLACE
expr_stmt|;
name|rect_select_cursor_update
argument_list|(
name|tool
argument_list|,
name|mevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|add_point
argument_list|(
name|free_sel
operator|->
name|num_pts
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|)
condition|)
block|{
name|gdk_draw_line
argument_list|(
name|free_sel
operator|->
name|core
operator|->
name|win
argument_list|,
name|free_sel
operator|->
name|core
operator|->
name|gc
argument_list|,
name|global_pts
index|[
name|free_sel
operator|->
name|num_pts
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
name|global_pts
index|[
name|free_sel
operator|->
name|num_pts
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
name|global_pts
index|[
name|free_sel
operator|->
name|num_pts
index|]
operator|.
name|x
argument_list|,
name|global_pts
index|[
name|free_sel
operator|->
name|num_pts
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
name|free_sel
operator|->
name|num_pts
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|free_select_control (Tool * tool,ToolAction action,GDisplay * gdisp)
name|free_select_control
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
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
name|free_sel
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
name|free_sel
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
name|free_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|free_select_draw (Tool * tool)
name|free_select_draw
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|free_sel
operator|->
name|num_pts
condition|;
name|i
operator|++
control|)
name|gdk_draw_line
argument_list|(
name|free_sel
operator|->
name|core
operator|->
name|win
argument_list|,
name|free_sel
operator|->
name|core
operator|->
name|gc
argument_list|,
name|global_pts
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
name|global_pts
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
name|global_pts
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|global_pts
index|[
name|i
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|free_select_options_reset (void)
name|free_select_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|selection_options_reset
argument_list|(
name|free_options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_free_select (void)
name|tools_new_free_select
parameter_list|(
name|void
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|FreeSelect
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|free_options
condition|)
block|{
name|free_options
operator|=
name|selection_options_new
argument_list|(
name|FREE_SELECT
argument_list|,
name|free_select_options_reset
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|FREE_SELECT
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|free_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|=
name|tools_new_tool
argument_list|(
name|FREE_SELECT
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_new0
argument_list|(
name|FreeSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|private
operator|->
name|core
operator|=
name|draw_core_new
argument_list|(
name|free_select_draw
argument_list|)
expr_stmt|;
name|private
operator|->
name|num_pts
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
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
comment|/*  Do not allow scrolling  */
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
name|free_select_button_press
expr_stmt|;
name|tool
operator|->
name|button_release_func
operator|=
name|free_select_button_release
expr_stmt|;
name|tool
operator|->
name|motion_func
operator|=
name|free_select_motion
expr_stmt|;
name|tool
operator|->
name|modifier_key_func
operator|=
name|rect_select_modifier_update
expr_stmt|;
name|tool
operator|->
name|cursor_update_func
operator|=
name|rect_select_cursor_update
expr_stmt|;
name|tool
operator|->
name|oper_update_func
operator|=
name|rect_select_oper_update
expr_stmt|;
name|tool
operator|->
name|control_func
operator|=
name|free_select_control
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_free_select (Tool * tool)
name|tools_free_free_select
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|draw_core_free
argument_list|(
name|free_sel
operator|->
name|core
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|free_sel
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

