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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
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
file|"info_dialog.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_include
include|#
directive|include
file|"rotate_tool.h"
end_include

begin_include
include|#
directive|include
file|"selection.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"transform_core.h"
end_include

begin_include
include|#
directive|include
file|"transform_tool.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager_pvt.h"
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|M_PI
end_ifndef

begin_define
DECL|macro|M_PI
define|#
directive|define
name|M_PI
value|3.14159265358979323846
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* M_PI */
end_comment

begin_comment
comment|/*  index into trans_info array  */
end_comment

begin_define
DECL|macro|ANGLE
define|#
directive|define
name|ANGLE
value|0
end_define

begin_define
DECL|macro|REAL_ANGLE
define|#
directive|define
name|REAL_ANGLE
value|1
end_define

begin_define
DECL|macro|CENTER_X
define|#
directive|define
name|CENTER_X
value|2
end_define

begin_define
DECL|macro|CENTER_Y
define|#
directive|define
name|CENTER_Y
value|3
end_define

begin_define
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|0.018
end_define

begin_comment
DECL|macro|EPSILON
comment|/*  ~ 1 degree  */
end_comment

begin_define
DECL|macro|FIFTEEN_DEG
define|#
directive|define
name|FIFTEEN_DEG
value|(M_PI / 12.0)
end_define

begin_comment
comment|/*  variables local to this file  */
end_comment

begin_decl_stmt
DECL|variable|angle_buf
specifier|static
name|char
name|angle_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|center_x_buf
specifier|static
name|char
name|center_x_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|center_y_buf
specifier|static
name|char
name|center_y_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
modifier|*
name|rotate_tool_rotate
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|double
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|int
parameter_list|,
name|GimpMatrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|rotate_tool_recalc
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|rotate_tool_motion
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|rotate_info_update
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Argument
modifier|*
name|rotate_invoker
parameter_list|(
name|Argument
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  callback functions for the info dialog entries  */
end_comment

begin_function_decl
specifier|static
name|void
name|rotate_angle_changed
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|rotate_center_x_changed
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|rotate_center_y_changed
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
modifier|*
DECL|function|rotate_tool_transform (tool,gdisp_ptr,state)
name|rotate_tool_transform
parameter_list|(
name|tool
parameter_list|,
name|gdisp_ptr
parameter_list|,
name|state
parameter_list|)
name|Tool
modifier|*
name|tool
decl_stmt|;
name|gpointer
name|gdisp_ptr
decl_stmt|;
name|int
name|state
decl_stmt|;
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
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
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|INIT
case|:
if|if
condition|(
operator|!
name|transform_info
condition|)
block|{
name|transform_info
operator|=
name|info_dialog_new
argument_list|(
literal|"Rotation Information"
argument_list|)
expr_stmt|;
name|info_dialog_add_field
argument_list|(
name|transform_info
argument_list|,
literal|"Angle: "
argument_list|,
name|angle_buf
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|rotate_angle_changed
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|info_dialog_add_field
argument_list|(
name|transform_info
argument_list|,
literal|"Center X: "
argument_list|,
name|center_x_buf
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|rotate_center_x_changed
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|info_dialog_add_field
argument_list|(
name|transform_info
argument_list|,
literal|"Center Y: "
argument_list|,
name|center_y_buf
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|rotate_center_y_changed
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
name|transform_core
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
literal|0.0
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|=
literal|0.0
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
operator|=
operator|(
name|transform_core
operator|->
name|x1
operator|+
name|transform_core
operator|->
name|x2
operator|)
operator|/
literal|2
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
operator|=
operator|(
name|transform_core
operator|->
name|y1
operator|+
name|transform_core
operator|->
name|y2
operator|)
operator|/
literal|2
expr_stmt|;
return|return
name|NULL
return|;
break|break;
case|case
name|MOTION
case|:
name|rotate_tool_motion
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|)
expr_stmt|;
return|return
operator|(
name|rotate_tool_recalc
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|)
operator|)
return|;
break|break;
case|case
name|RECALC
case|:
return|return
operator|(
name|rotate_tool_recalc
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|)
operator|)
return|;
break|break;
case|case
name|FINISH
case|:
return|return
name|rotate_tool_rotate
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gimage_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|transform_core
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|,
name|transform_core
operator|->
name|original
argument_list|,
name|transform_tool_smoothing
argument_list|()
argument_list|,
name|transform_core
operator|->
name|transform
argument_list|)
return|;
break|break;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_rotate_tool ()
name|tools_new_rotate_tool
parameter_list|()
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|TransformCore
modifier|*
name|private
decl_stmt|;
name|tool
operator|=
name|transform_core_new
argument_list|(
name|ROTATE
argument_list|,
name|INTERACTIVE
argument_list|)
expr_stmt|;
name|private
operator|=
name|tool
operator|->
name|private
expr_stmt|;
comment|/*  set the rotation specific transformation attributes  */
name|private
operator|->
name|trans_func
operator|=
name|rotate_tool_transform
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
literal|0.0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|=
literal|0.0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
operator|=
operator|(
name|private
operator|->
name|x1
operator|+
name|private
operator|->
name|x2
operator|)
operator|/
literal|2
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
operator|=
operator|(
name|private
operator|->
name|y1
operator|+
name|private
operator|->
name|y2
operator|)
operator|/
literal|2
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|gimp_matrix_identity
argument_list|(
name|private
operator|->
name|transform
argument_list|)
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_rotate_tool (tool)
name|tools_free_rotate_tool
parameter_list|(
name|tool
parameter_list|)
name|Tool
modifier|*
name|tool
decl_stmt|;
block|{
name|transform_core_free
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_info_update (tool)
name|rotate_info_update
parameter_list|(
name|tool
parameter_list|)
name|Tool
modifier|*
name|tool
decl_stmt|;
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|double
name|angle
decl_stmt|;
name|int
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|angle
operator|=
operator|(
name|transform_core
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|*
literal|180.0
operator|)
operator|/
name|M_PI
expr_stmt|;
name|cx
operator|=
name|transform_core
operator|->
name|cx
expr_stmt|;
name|cy
operator|=
name|transform_core
operator|->
name|cy
expr_stmt|;
name|sprintf
argument_list|(
name|angle_buf
argument_list|,
literal|"%0.2f"
argument_list|,
name|angle
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|center_x_buf
argument_list|,
literal|"%d"
argument_list|,
name|cx
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|center_y_buf
argument_list|,
literal|"%d"
argument_list|,
name|cy
argument_list|)
expr_stmt|;
name|info_dialog_update
argument_list|(
name|transform_info
argument_list|)
expr_stmt|;
name|info_dialog_popup
argument_list|(
name|transform_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_angle_changed (GtkWidget * w,gpointer data)
name|rotate_angle_changed
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|double
name|value
decl_stmt|;
name|tool
operator|=
operator|(
name|Tool
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
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
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|str
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|w
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|value
operator|=
operator|(
name|atof
argument_list|(
name|str
argument_list|)
operator|*
name|M_PI
operator|)
operator|/
literal|180.0
expr_stmt|;
if|if
condition|(
name|value
operator|!=
name|transform_core
operator|->
name|trans_info
index|[
name|ANGLE
index|]
condition|)
block|{
name|draw_core_pause
argument_list|(
name|transform_core
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|value
expr_stmt|;
name|rotate_tool_recalc
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|draw_core_resume
argument_list|(
name|transform_core
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_center_x_changed (GtkWidget * w,gpointer data)
name|rotate_center_x_changed
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|int
name|value
decl_stmt|;
name|tool
operator|=
operator|(
name|Tool
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
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
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|str
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|w
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|value
operator|=
operator|(
name|int
operator|)
name|atof
argument_list|(
name|str
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|!=
name|transform_core
operator|->
name|cx
condition|)
block|{
name|draw_core_pause
argument_list|(
name|transform_core
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|transform_core
operator|->
name|cx
operator|=
name|value
expr_stmt|;
name|rotate_tool_recalc
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|draw_core_resume
argument_list|(
name|transform_core
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_center_y_changed (GtkWidget * w,gpointer data)
name|rotate_center_y_changed
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|int
name|value
decl_stmt|;
name|tool
operator|=
operator|(
name|Tool
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
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
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|str
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|w
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|value
operator|=
operator|(
name|int
operator|)
name|atof
argument_list|(
name|str
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|!=
name|transform_core
operator|->
name|cy
condition|)
block|{
name|draw_core_pause
argument_list|(
name|transform_core
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|transform_core
operator|->
name|cy
operator|=
name|value
expr_stmt|;
name|rotate_tool_recalc
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|draw_core_resume
argument_list|(
name|transform_core
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_tool_motion (tool,gdisp_ptr)
name|rotate_tool_motion
parameter_list|(
name|tool
parameter_list|,
name|gdisp_ptr
parameter_list|)
name|Tool
modifier|*
name|tool
decl_stmt|;
name|void
modifier|*
name|gdisp_ptr
decl_stmt|;
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|double
name|angle1
decl_stmt|,
name|angle2
decl_stmt|,
name|angle
decl_stmt|;
name|double
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|double
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
if|if
condition|(
name|transform_core
operator|->
name|function
operator|==
name|HANDLE_CENTER
condition|)
block|{
name|transform_core
operator|->
name|cx
operator|=
name|transform_core
operator|->
name|curx
expr_stmt|;
name|transform_core
operator|->
name|cy
operator|=
name|transform_core
operator|->
name|cury
expr_stmt|;
return|return;
block|}
name|cx
operator|=
name|transform_core
operator|->
name|cx
expr_stmt|;
name|cy
operator|=
name|transform_core
operator|->
name|cy
expr_stmt|;
name|x1
operator|=
name|transform_core
operator|->
name|curx
operator|-
name|cx
expr_stmt|;
name|x2
operator|=
name|transform_core
operator|->
name|lastx
operator|-
name|cx
expr_stmt|;
name|y1
operator|=
name|cy
operator|-
name|transform_core
operator|->
name|cury
expr_stmt|;
name|y2
operator|=
name|cy
operator|-
name|transform_core
operator|->
name|lasty
expr_stmt|;
comment|/*  find the first angle  */
name|angle1
operator|=
name|atan2
argument_list|(
name|y1
argument_list|,
name|x1
argument_list|)
expr_stmt|;
comment|/*  find the angle  */
name|angle2
operator|=
name|atan2
argument_list|(
name|y2
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|angle
operator|=
name|angle2
operator|-
name|angle1
expr_stmt|;
if|if
condition|(
name|angle
operator|>
name|M_PI
operator|||
name|angle
operator|<
operator|-
name|M_PI
condition|)
name|angle
operator|=
name|angle2
operator|-
operator|(
operator|(
name|angle1
operator|<
literal|0
operator|)
condition|?
literal|2
operator|*
name|M_PI
operator|+
name|angle1
else|:
name|angle1
operator|-
literal|2
operator|*
name|M_PI
operator|)
expr_stmt|;
comment|/*  increment the transform tool's angle  */
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|+=
name|angle
expr_stmt|;
comment|/*  limit the angle to between 0 and 360 degrees  */
if|if
condition|(
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|<
operator|-
name|M_PI
condition|)
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|=
literal|2
operator|*
name|M_PI
operator|-
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
expr_stmt|;
elseif|else
if|if
condition|(
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|>
name|M_PI
condition|)
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|=
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|-
literal|2
operator|*
name|M_PI
expr_stmt|;
comment|/* constrain the angle to 15-degree multiples if ctrl is held down */
if|if
condition|(
name|transform_core
operator|->
name|state
operator|&
name|ControlMask
condition|)
name|transform_core
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|FIFTEEN_DEG
operator|*
call|(
name|int
call|)
argument_list|(
operator|(
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|+
name|FIFTEEN_DEG
operator|/
literal|2.0
operator|)
operator|/
name|FIFTEEN_DEG
argument_list|)
expr_stmt|;
else|else
name|transform_core
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|rotate_tool_recalc (tool,gdisp_ptr)
name|rotate_tool_recalc
parameter_list|(
name|tool
parameter_list|,
name|gdisp_ptr
parameter_list|)
name|Tool
modifier|*
name|tool
decl_stmt|;
name|void
modifier|*
name|gdisp_ptr
decl_stmt|;
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|double
name|cx
decl_stmt|,
name|cy
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
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|cx
operator|=
name|transform_core
operator|->
name|cx
expr_stmt|;
name|cy
operator|=
name|transform_core
operator|->
name|cy
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|gimp_matrix_identity
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|)
expr_stmt|;
name|gimp_matrix_translate
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|,
operator|-
name|cx
argument_list|,
operator|-
name|cy
argument_list|)
expr_stmt|;
name|gimp_matrix_rotate
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|,
name|transform_core
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
expr_stmt|;
name|gimp_matrix_translate
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|,
operator|+
name|cx
argument_list|,
operator|+
name|cy
argument_list|)
expr_stmt|;
comment|/*  transform the bounding box  */
name|transform_bounding_box
argument_list|(
name|tool
argument_list|)
expr_stmt|;
comment|/*  update the information dialog  */
name|rotate_info_update
argument_list|(
name|tool
argument_list|)
expr_stmt|;
return|return
operator|(
name|void
operator|*
operator|)
literal|1
return|;
block|}
end_function

begin_comment
comment|/*  This procedure returns a valid pointer to a new selection if the  *  requested angle is a multiple of 90 degrees...  */
end_comment

begin_function
specifier|static
name|void
modifier|*
DECL|function|rotate_tool_rotate (gimage,drawable,angle,float_tiles,interpolation,matrix)
name|rotate_tool_rotate
parameter_list|(
name|gimage
parameter_list|,
name|drawable
parameter_list|,
name|angle
parameter_list|,
name|float_tiles
parameter_list|,
name|interpolation
parameter_list|,
name|matrix
parameter_list|)
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|double
name|angle
decl_stmt|;
name|TileManager
modifier|*
name|float_tiles
decl_stmt|;
name|int
name|interpolation
decl_stmt|;
name|GimpMatrix
name|matrix
decl_stmt|;
block|{
return|return
name|transform_core_do
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|float_tiles
argument_list|,
name|interpolation
argument_list|,
name|matrix
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The rotate procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|rotate_args
name|ProcArg
name|rotate_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|,
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the affected drawable"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"interpolation"
block|,
literal|"whether to use interpolation"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"angle"
block|,
literal|"the angle of rotation (radians)"
block|,   }
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rotate_out_args
name|ProcArg
name|rotate_out_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the rotated drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rotate_proc
name|ProcRecord
name|rotate_proc
init|=
block|{
literal|"gimp_rotate"
block|,
literal|"Rotate the specified drawable about its center through the specified angle"
block|,
literal|"This tool rotates the specified drawable if no selection exists.  If a selection exists, the portion of the drawable which lies under the selection is cut from the drawable and made into a floating selection which is then rotated by the specified amount.  The interpolation parameter can be set to TRUE to indicate that either linear or cubic interpolation should be used to smooth the resulting rotated drawable.  The return value is the ID of the rotated drawable.  If there was no selection, this will be equal to the drawable ID supplied as input.  Otherwise, this will be the newly created and rotated drawable."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|4
block|,
name|rotate_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|rotate_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|rotate_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|rotate_invoker (args)
name|rotate_invoker
parameter_list|(
name|args
parameter_list|)
name|Argument
modifier|*
name|args
decl_stmt|;
block|{
name|int
name|success
init|=
name|TRUE
decl_stmt|;
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|interpolation
decl_stmt|;
name|double
name|angle
decl_stmt|;
name|int
name|int_value
decl_stmt|;
name|TileManager
modifier|*
name|float_tiles
decl_stmt|;
name|TileManager
modifier|*
name|new_tiles
decl_stmt|;
name|GimpMatrix
name|matrix
decl_stmt|;
name|int
name|new_layer
decl_stmt|;
name|Layer
modifier|*
name|layer
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|drawable
operator|=
name|NULL
expr_stmt|;
name|layer
operator|=
name|NULL
expr_stmt|;
comment|/*  the gimage  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
comment|/*  the drawable  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|drawable
operator|=
name|drawable_get_ID
argument_list|(
name|int_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|==
name|NULL
operator|||
name|gimage
operator|!=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
comment|/*  interpolation  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|interpolation
operator|=
operator|(
name|int_value
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
comment|/*  angle of rotation  */
if|if
condition|(
name|success
condition|)
name|angle
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
comment|/*  call the rotate procedure  */
if|if
condition|(
name|success
condition|)
block|{
name|double
name|cx
decl_stmt|,
name|cy
decl_stmt|;
comment|/*  Start a transform undo group  */
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|TRANSFORM_CORE_UNDO
argument_list|)
expr_stmt|;
comment|/*  Cut/Copy from the specified drawable  */
name|float_tiles
operator|=
name|transform_core_cut
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
operator|&
name|new_layer
argument_list|)
expr_stmt|;
name|cx
operator|=
name|float_tiles
operator|->
name|x
operator|+
name|float_tiles
operator|->
name|width
operator|/
literal|2.0
expr_stmt|;
name|cy
operator|=
name|float_tiles
operator|->
name|y
operator|+
name|float_tiles
operator|->
name|height
operator|/
literal|2.0
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|gimp_matrix_identity
argument_list|(
name|matrix
argument_list|)
expr_stmt|;
name|gimp_matrix_translate
argument_list|(
name|matrix
argument_list|,
operator|-
name|cx
argument_list|,
operator|-
name|cy
argument_list|)
expr_stmt|;
name|gimp_matrix_rotate
argument_list|(
name|matrix
argument_list|,
name|angle
argument_list|)
expr_stmt|;
name|gimp_matrix_translate
argument_list|(
name|matrix
argument_list|,
operator|+
name|cx
argument_list|,
operator|+
name|cy
argument_list|)
expr_stmt|;
comment|/*  rotate the buffer  */
name|new_tiles
operator|=
name|rotate_tool_rotate
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|angle
argument_list|,
name|float_tiles
argument_list|,
name|interpolation
argument_list|,
name|matrix
argument_list|)
expr_stmt|;
comment|/*  free the cut/copied buffer  */
name|tile_manager_destroy
argument_list|(
name|float_tiles
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_tiles
condition|)
name|success
operator|=
operator|(
name|layer
operator|=
name|transform_core_paste
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|new_tiles
argument_list|,
name|new_layer
argument_list|)
operator|)
operator|!=
name|NULL
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
comment|/*  push the undo group end  */
name|undo_push_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|rotate_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|drawable_ID
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

end_unit

