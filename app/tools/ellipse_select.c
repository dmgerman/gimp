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
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"edit_selection.h"
end_include

begin_include
include|#
directive|include
file|"ellipse_select.h"
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
file|"rect_select.h"
end_include

begin_comment
comment|/*  private header file for rect_select data structure  */
end_comment

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

begin_comment
comment|/*  the ellipse selection tool options  */
end_comment

begin_decl_stmt
DECL|variable|ellipse_options
name|SelectionOptions
modifier|*
name|ellipse_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*************************************/
end_comment

begin_comment
comment|/*  Ellipsoidal selection apparatus  */
end_comment

begin_function
name|void
DECL|function|ellipse_select (GimpImage * gimage,gint x,gint y,gint w,gint h,SelectOps op,gboolean antialias,gboolean feather,gdouble feather_radius)
name|ellipse_select
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|channel_combine_ellipse
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
argument_list|,
name|antialias
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
name|channel_combine_ellipse
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
argument_list|,
name|antialias
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
name|channel_combine_ellipse
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
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ellipse_select_draw (Tool * tool)
name|ellipse_select_draw
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
name|EllipseSelect
modifier|*
name|ellipse_sel
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
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
name|ellipse_sel
operator|=
operator|(
name|EllipseSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|x1
operator|=
name|MIN
argument_list|(
name|ellipse_sel
operator|->
name|x
argument_list|,
name|ellipse_sel
operator|->
name|x
operator|+
name|ellipse_sel
operator|->
name|w
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MIN
argument_list|(
name|ellipse_sel
operator|->
name|y
argument_list|,
name|ellipse_sel
operator|->
name|y
operator|+
name|ellipse_sel
operator|->
name|h
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MAX
argument_list|(
name|ellipse_sel
operator|->
name|x
argument_list|,
name|ellipse_sel
operator|->
name|x
operator|+
name|ellipse_sel
operator|->
name|w
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MAX
argument_list|(
name|ellipse_sel
operator|->
name|y
argument_list|,
name|ellipse_sel
operator|->
name|y
operator|+
name|ellipse_sel
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
name|gdk_draw_arc
argument_list|(
name|ellipse_sel
operator|->
name|core
operator|->
name|win
argument_list|,
name|ellipse_sel
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
argument_list|,
literal|0
argument_list|,
literal|23040
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ellipse_select_options_reset (void)
name|ellipse_select_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|selection_options_reset
argument_list|(
name|ellipse_options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_ellipse_select (void)
name|tools_new_ellipse_select
parameter_list|(
name|void
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|EllipseSelect
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|ellipse_options
condition|)
block|{
name|ellipse_options
operator|=
name|selection_options_new
argument_list|(
name|ELLIPSE_SELECT
argument_list|,
name|ellipse_select_options_reset
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|ELLIPSE_SELECT
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|ellipse_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|=
name|tools_new_tool
argument_list|(
name|ELLIPSE_SELECT
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_new0
argument_list|(
name|EllipseSelect
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
name|ellipse_select_draw
argument_list|)
expr_stmt|;
comment|/*  Make the selection static, not blinking  */
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
name|rect_select_control
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_ellipse_select (Tool * tool)
name|tools_free_ellipse_select
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|EllipseSelect
modifier|*
name|ellipse_sel
decl_stmt|;
name|ellipse_sel
operator|=
operator|(
name|EllipseSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|draw_core_free
argument_list|(
name|ellipse_sel
operator|->
name|core
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ellipse_sel
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

