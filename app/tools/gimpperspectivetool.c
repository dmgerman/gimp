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
file|"perspective_tool.h"
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

begin_define
DECL|macro|X0
define|#
directive|define
name|X0
value|0
end_define

begin_define
DECL|macro|Y0
define|#
directive|define
name|Y0
value|1
end_define

begin_define
DECL|macro|X1
define|#
directive|define
name|X1
value|2
end_define

begin_define
DECL|macro|Y1
define|#
directive|define
name|Y1
value|3
end_define

begin_define
DECL|macro|X2
define|#
directive|define
name|X2
value|4
end_define

begin_define
DECL|macro|Y2
define|#
directive|define
name|Y2
value|5
end_define

begin_define
DECL|macro|X3
define|#
directive|define
name|X3
value|6
end_define

begin_define
DECL|macro|Y3
define|#
directive|define
name|Y3
value|7
end_define

begin_comment
comment|/*  storage for information dialog fields  */
end_comment

begin_decl_stmt
DECL|variable|matrix_row_buf
specifier|static
name|char
name|matrix_row_buf
index|[
literal|3
index|]
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
name|perspective_tool_perspective
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|int
parameter_list|,
name|Matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|perspective_find_transform
parameter_list|(
name|double
modifier|*
parameter_list|,
name|Matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|perspective_tool_recalc
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
name|perspective_tool_motion
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
name|perspective_info_update
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
name|perspective_invoker
parameter_list|(
name|Argument
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
modifier|*
DECL|function|perspective_tool_transform (tool,gdisp_ptr,state)
name|perspective_tool_transform
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
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
literal|"Perspective Transform Information"
argument_list|)
expr_stmt|;
name|info_dialog_add_field
argument_list|(
name|transform_info
argument_list|,
literal|"Matrix: "
argument_list|,
name|matrix_row_buf
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|info_dialog_add_field
argument_list|(
name|transform_info
argument_list|,
literal|"        "
argument_list|,
name|matrix_row_buf
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|info_dialog_add_field
argument_list|(
name|transform_info
argument_list|,
literal|"        "
argument_list|,
name|matrix_row_buf
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
block|}
name|transform_core
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
operator|(
name|double
operator|)
name|transform_core
operator|->
name|x1
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
operator|(
name|double
operator|)
name|transform_core
operator|->
name|y1
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
operator|(
name|double
operator|)
name|transform_core
operator|->
name|x2
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
operator|(
name|double
operator|)
name|transform_core
operator|->
name|y1
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|X2
index|]
operator|=
operator|(
name|double
operator|)
name|transform_core
operator|->
name|x1
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|Y2
index|]
operator|=
operator|(
name|double
operator|)
name|transform_core
operator|->
name|y2
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|X3
index|]
operator|=
operator|(
name|double
operator|)
name|transform_core
operator|->
name|x2
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|=
operator|(
name|double
operator|)
name|transform_core
operator|->
name|y2
expr_stmt|;
return|return
name|NULL
return|;
break|break;
case|case
name|MOTION
case|:
name|perspective_tool_motion
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|)
expr_stmt|;
return|return
operator|(
name|perspective_tool_recalc
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
name|perspective_tool_recalc
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
comment|/*  Let the transform core handle the inverse mapping  */
return|return
name|perspective_tool_perspective
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
DECL|function|tools_new_perspective_tool ()
name|tools_new_perspective_tool
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
name|PERSPECTIVE
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
name|perspective_tool_transform
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|X2
index|]
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|Y2
index|]
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|X3
index|]
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|=
literal|0
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|identity_matrix
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
DECL|function|tools_free_perspective_tool (tool)
name|tools_free_perspective_tool
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
DECL|function|perspective_info_update (tool)
name|perspective_info_update
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
name|int
name|i
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
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
block|{
name|char
modifier|*
name|p
init|=
name|matrix_row_buf
index|[
name|i
index|]
decl_stmt|;
name|int
name|j
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
block|{
name|p
operator|+=
name|sprintf
argument_list|(
name|p
argument_list|,
literal|"%10.3g"
argument_list|,
name|transform_core
operator|->
name|transform
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|)
expr_stmt|;
block|}
block|}
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
return|return;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|perspective_tool_motion (tool,gdisp_ptr)
name|perspective_tool_motion
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|int
name|diff_x
decl_stmt|,
name|diff_y
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
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
name|diff_x
operator|=
name|transform_core
operator|->
name|curx
operator|-
name|transform_core
operator|->
name|lastx
expr_stmt|;
name|diff_y
operator|=
name|transform_core
operator|->
name|cury
operator|-
name|transform_core
operator|->
name|lasty
expr_stmt|;
switch|switch
condition|(
name|transform_core
operator|->
name|function
condition|)
block|{
case|case
name|HANDLE_1
case|:
name|transform_core
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
case|case
name|HANDLE_2
case|:
name|transform_core
operator|->
name|trans_info
index|[
name|X1
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
case|case
name|HANDLE_3
case|:
name|transform_core
operator|->
name|trans_info
index|[
name|X2
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|Y2
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
case|case
name|HANDLE_4
case|:
name|transform_core
operator|->
name|trans_info
index|[
name|X3
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
default|default :
return|return;
block|}
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|perspective_tool_recalc (tool,gdisp_ptr)
name|perspective_tool_recalc
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
name|Matrix
name|m
decl_stmt|;
name|double
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|double
name|scalex
decl_stmt|,
name|scaley
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
comment|/*  determine the perspective transform that maps from    *  the unit cube to the trans_info coordinates    */
name|perspective_find_transform
argument_list|(
name|transform_core
operator|->
name|trans_info
argument_list|,
name|m
argument_list|)
expr_stmt|;
name|cx
operator|=
name|transform_core
operator|->
name|x1
expr_stmt|;
name|cy
operator|=
name|transform_core
operator|->
name|y1
expr_stmt|;
name|scalex
operator|=
literal|1.0
expr_stmt|;
name|scaley
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|transform_core
operator|->
name|x2
operator|-
name|transform_core
operator|->
name|x1
condition|)
name|scalex
operator|=
literal|1.0
operator|/
operator|(
name|transform_core
operator|->
name|x2
operator|-
name|transform_core
operator|->
name|x1
operator|)
expr_stmt|;
if|if
condition|(
name|transform_core
operator|->
name|y2
operator|-
name|transform_core
operator|->
name|y1
condition|)
name|scaley
operator|=
literal|1.0
operator|/
operator|(
name|transform_core
operator|->
name|y2
operator|-
name|transform_core
operator|->
name|y1
operator|)
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|identity_matrix
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|)
expr_stmt|;
name|translate_matrix
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
name|scale_matrix
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|,
name|scalex
argument_list|,
name|scaley
argument_list|)
expr_stmt|;
name|mult_matrix
argument_list|(
name|m
argument_list|,
name|transform_core
operator|->
name|transform
argument_list|)
expr_stmt|;
comment|/*  transform the bounding box  */
name|transform_bounding_box
argument_list|(
name|tool
argument_list|)
expr_stmt|;
comment|/*  update the information dialog  */
name|perspective_info_update
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

begin_function
specifier|static
name|void
DECL|function|perspective_find_transform (coords,m)
name|perspective_find_transform
parameter_list|(
name|coords
parameter_list|,
name|m
parameter_list|)
name|double
modifier|*
name|coords
decl_stmt|;
name|Matrix
name|m
decl_stmt|;
block|{
name|double
name|dx1
decl_stmt|,
name|dx2
decl_stmt|,
name|dx3
decl_stmt|,
name|dy1
decl_stmt|,
name|dy2
decl_stmt|,
name|dy3
decl_stmt|;
name|double
name|det1
decl_stmt|,
name|det2
decl_stmt|;
name|dx1
operator|=
name|coords
index|[
name|X1
index|]
operator|-
name|coords
index|[
name|X3
index|]
expr_stmt|;
name|dx2
operator|=
name|coords
index|[
name|X2
index|]
operator|-
name|coords
index|[
name|X3
index|]
expr_stmt|;
name|dx3
operator|=
name|coords
index|[
name|X0
index|]
operator|-
name|coords
index|[
name|X1
index|]
operator|+
name|coords
index|[
name|X3
index|]
operator|-
name|coords
index|[
name|X2
index|]
expr_stmt|;
name|dy1
operator|=
name|coords
index|[
name|Y1
index|]
operator|-
name|coords
index|[
name|Y3
index|]
expr_stmt|;
name|dy2
operator|=
name|coords
index|[
name|Y2
index|]
operator|-
name|coords
index|[
name|Y3
index|]
expr_stmt|;
name|dy3
operator|=
name|coords
index|[
name|Y0
index|]
operator|-
name|coords
index|[
name|Y1
index|]
operator|+
name|coords
index|[
name|Y3
index|]
operator|-
name|coords
index|[
name|Y2
index|]
expr_stmt|;
comment|/*  Is the mapping affine?  */
if|if
condition|(
operator|(
name|dx3
operator|==
literal|0.0
operator|)
operator|&&
operator|(
name|dy3
operator|==
literal|0.0
operator|)
condition|)
block|{
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
name|coords
index|[
name|X1
index|]
operator|-
name|coords
index|[
name|X0
index|]
expr_stmt|;
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
name|coords
index|[
name|X3
index|]
operator|-
name|coords
index|[
name|X1
index|]
expr_stmt|;
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
name|coords
index|[
name|X0
index|]
expr_stmt|;
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|=
name|coords
index|[
name|Y1
index|]
operator|-
name|coords
index|[
name|Y0
index|]
expr_stmt|;
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
name|coords
index|[
name|Y3
index|]
operator|-
name|coords
index|[
name|Y1
index|]
expr_stmt|;
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
name|coords
index|[
name|Y0
index|]
expr_stmt|;
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|=
literal|0.0
expr_stmt|;
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
else|else
block|{
name|det1
operator|=
name|dx3
operator|*
name|dy2
operator|-
name|dy3
operator|*
name|dx2
expr_stmt|;
name|det2
operator|=
name|dx1
operator|*
name|dy2
operator|-
name|dy1
operator|*
name|dx2
expr_stmt|;
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|=
name|det1
operator|/
name|det2
expr_stmt|;
name|det1
operator|=
name|dx1
operator|*
name|dy3
operator|-
name|dy1
operator|*
name|dx3
expr_stmt|;
name|det2
operator|=
name|dx1
operator|*
name|dy2
operator|-
name|dy1
operator|*
name|dx2
expr_stmt|;
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|=
name|det1
operator|/
name|det2
expr_stmt|;
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
name|coords
index|[
name|X1
index|]
operator|-
name|coords
index|[
name|X0
index|]
operator|+
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|*
name|coords
index|[
name|X1
index|]
expr_stmt|;
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
name|coords
index|[
name|X2
index|]
operator|-
name|coords
index|[
name|X0
index|]
operator|+
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|*
name|coords
index|[
name|X2
index|]
expr_stmt|;
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
name|coords
index|[
name|X0
index|]
expr_stmt|;
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|=
name|coords
index|[
name|Y1
index|]
operator|-
name|coords
index|[
name|Y0
index|]
operator|+
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|*
name|coords
index|[
name|Y1
index|]
expr_stmt|;
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
name|coords
index|[
name|Y2
index|]
operator|-
name|coords
index|[
name|Y0
index|]
operator|+
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|*
name|coords
index|[
name|Y2
index|]
expr_stmt|;
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
name|coords
index|[
name|Y0
index|]
expr_stmt|;
block|}
name|m
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|=
literal|1.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|perspective_tool_perspective (gimage,drawable,float_tiles,interpolation,matrix)
name|perspective_tool_perspective
parameter_list|(
name|gimage
parameter_list|,
name|drawable
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
name|TileManager
modifier|*
name|float_tiles
decl_stmt|;
name|int
name|interpolation
decl_stmt|;
name|Matrix
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
comment|/*  The perspective procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|perspective_args
name|ProcArg
name|perspective_args
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
literal|"x0"
block|,
literal|"the new x coordinate of upper-left corner of original bounding box"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"y0"
block|,
literal|"the new y coordinate of upper-left corner of original bounding box"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"x1"
block|,
literal|"the new x coordinate of upper-right corner of original bounding box"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"y1"
block|,
literal|"the new y coordinate of upper-right corner of original bounding box"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"x2"
block|,
literal|"the new x coordinate of lower-left corner of original bounding box"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"y2"
block|,
literal|"the new y coordinate of lower-left corner of original bounding box"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"x3"
block|,
literal|"the new x coordinate of lower-right corner of original bounding box"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"y3"
block|,
literal|"the new y coordinate of lower-right corner of original bounding box"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|perspective_out_args
name|ProcArg
name|perspective_out_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the newly mapped drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|perspective_proc
name|ProcRecord
name|perspective_proc
init|=
block|{
literal|"gimp_perspective"
block|,
literal|"Perform a possibly non-affine transformation on the specified drawable"
block|,
literal|"This tool performs a possibly non-affine transformation on the specified drawable by allowing the corners of the original bounding box to be arbitrarily remapped to any values.  The specified drawable is remapped if no selection exists.  However, if a selection exists, the portion of the drawable which lies under the selection is cut from the drawable and made into a floating selection which is then remapped as specified.  The interpolation parameter can be set to TRUE to indicate that either linear or cubic interpolation should be used to smooth the resulting remapped drawable.  The return value is the ID of the remapped drawable.  If there was no selection, this will be equal to the drawable ID supplied as input.  Otherwise, this will be the newly created and remapped drawable.  The 4 coordinates specify the new locations of each corner of the original bounding box.  By specifying these values, any affine transformation (rotation, scaling, translation) can be affected.  Additionally, these values can be specified such that the resulting transformed drawable will appear to have been projected via a perspective transform."
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
literal|11
block|,
name|perspective_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|perspective_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|perspective_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|perspective_invoker (args)
name|perspective_invoker
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
name|trans_info
index|[
literal|8
index|]
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
name|Matrix
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
comment|/*  perspective extents  */
if|if
condition|(
name|success
condition|)
block|{
name|trans_info
index|[
name|X0
index|]
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
name|trans_info
index|[
name|Y0
index|]
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|trans_info
index|[
name|X1
index|]
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|trans_info
index|[
name|Y1
index|]
operator|=
name|args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|trans_info
index|[
name|X2
index|]
operator|=
name|args
index|[
literal|7
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|trans_info
index|[
name|Y2
index|]
operator|=
name|args
index|[
literal|8
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|trans_info
index|[
name|X3
index|]
operator|=
name|args
index|[
literal|9
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|trans_info
index|[
name|Y3
index|]
operator|=
name|args
index|[
literal|10
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
block|}
comment|/*  call the perspective procedure  */
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
name|double
name|scalex
decl_stmt|,
name|scaley
decl_stmt|;
name|Matrix
name|m
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
comment|/*  determine the perspective transform that maps from        *  the unit cube to the trans_info coordinates        */
name|perspective_find_transform
argument_list|(
name|trans_info
argument_list|,
name|m
argument_list|)
expr_stmt|;
name|cx
operator|=
name|float_tiles
operator|->
name|x
expr_stmt|;
name|cy
operator|=
name|float_tiles
operator|->
name|y
expr_stmt|;
name|scalex
operator|=
literal|1.0
expr_stmt|;
name|scaley
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|float_tiles
operator|->
name|levels
index|[
literal|0
index|]
operator|.
name|width
condition|)
name|scalex
operator|=
literal|1.0
operator|/
name|float_tiles
operator|->
name|levels
index|[
literal|0
index|]
operator|.
name|width
expr_stmt|;
if|if
condition|(
name|float_tiles
operator|->
name|levels
index|[
literal|0
index|]
operator|.
name|height
condition|)
name|scaley
operator|=
literal|1.0
operator|/
name|float_tiles
operator|->
name|levels
index|[
literal|0
index|]
operator|.
name|height
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|identity_matrix
argument_list|(
name|matrix
argument_list|)
expr_stmt|;
name|translate_matrix
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
name|scale_matrix
argument_list|(
name|matrix
argument_list|,
name|scalex
argument_list|,
name|scaley
argument_list|)
expr_stmt|;
name|mult_matrix
argument_list|(
name|m
argument_list|,
name|matrix
argument_list|)
expr_stmt|;
comment|/*  perspective the buffer  */
name|new_tiles
operator|=
name|perspective_tool_perspective
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
name|perspective_proc
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

