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
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
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

begin_include
include|#
directive|include
file|"libgimp/gimpsizeentry.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpmath.h"
end_include

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
value|(G_PI / 12.0)
end_define

begin_comment
comment|/*  variables local to this file  */
end_comment

begin_decl_stmt
DECL|variable|angle_val
specifier|static
name|gdouble
name|angle_val
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|center_vals
specifier|static
name|gdouble
name|center_vals
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  needed for size update  */
end_comment

begin_decl_stmt
DECL|variable|sizeentry
specifier|static
name|GtkWidget
modifier|*
name|sizeentry
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
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

begin_comment
comment|/*  callback functions for the info dialog sizeentries  */
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
name|rotate_center_changed
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
name|TileManager
modifier|*
DECL|function|rotate_tool_transform (Tool * tool,gpointer gdisp_ptr,TransformState state)
name|rotate_tool_transform
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|,
name|TransformState
name|state
parameter_list|)
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton2
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
name|angle_val
operator|=
literal|0.0
expr_stmt|;
name|center_vals
index|[
literal|0
index|]
operator|=
name|transform_core
operator|->
name|cx
expr_stmt|;
name|center_vals
index|[
literal|1
index|]
operator|=
name|transform_core
operator|->
name|cy
expr_stmt|;
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
name|_
argument_list|(
literal|"Rotation Information"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"tools/transform_rotate.html"
argument_list|)
expr_stmt|;
name|widget
operator|=
name|info_dialog_add_spinbutton
argument_list|(
name|transform_info
argument_list|,
name|_
argument_list|(
literal|"Angle:"
argument_list|)
argument_list|,
operator|&
name|angle_val
argument_list|,
operator|-
literal|180
argument_list|,
literal|180
argument_list|,
literal|1
argument_list|,
literal|15
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|rotate_angle_changed
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_wrap
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  this looks strange (-180, 181), but it works  */
name|widget
operator|=
name|info_dialog_add_scale
argument_list|(
name|transform_info
argument_list|,
literal|""
argument_list|,
operator|&
name|angle_val
argument_list|,
operator|-
literal|180
argument_list|,
literal|181
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|1
argument_list|,
operator|-
literal|1
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|rotate_angle_changed
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|widget
argument_list|,
literal|180
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|spinbutton2
operator|=
name|info_dialog_add_spinbutton
argument_list|(
name|transform_info
argument_list|,
name|_
argument_list|(
literal|"Center X:"
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sizeentry
operator|=
name|info_dialog_add_sizeentry
argument_list|(
name|transform_info
argument_list|,
name|_
argument_list|(
literal|"Y:"
argument_list|)
argument_list|,
name|center_vals
argument_list|,
literal|1
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|,
literal|"%a"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|rotate_center_changed
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|gimp_size_entry_add_field
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|GTK_SPIN_BUTTON
argument_list|(
name|spinbutton2
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|transform_info
operator|->
name|info_table
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|transform_info
operator|->
name|info_table
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|dot_for_dot
condition|)
name|gimp_size_entry_set_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
literal|65536
argument_list|,
literal|65536
operator|+
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|,
operator|-
literal|65536
argument_list|,
literal|65536
operator|+
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|transform_core
operator|->
name|x1
argument_list|,
name|transform_core
operator|->
name|x2
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|transform_core
operator|->
name|y1
argument_list|,
name|transform_core
operator|->
name|y2
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|center_vals
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|center_vals
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|transform_info
operator|->
name|shell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|sizeentry
argument_list|)
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
name|angle_val
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|=
name|angle_val
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
operator|=
name|center_vals
index|[
literal|0
index|]
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
operator|=
name|center_vals
index|[
literal|1
index|]
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
name|rotate_tool_recalc
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|)
expr_stmt|;
break|break;
case|case
name|RECALC
case|:
name|rotate_tool_recalc
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|)
expr_stmt|;
break|break;
case|case
name|FINISH
case|:
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|transform_info
operator|->
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
name|gdisp
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
DECL|function|tools_new_rotate_tool (void)
name|tools_new_rotate_tool
parameter_list|(
name|void
parameter_list|)
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
name|TRUE
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
literal|0.0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
operator|=
literal|0.0
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|gimp_matrix3_identity
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
DECL|function|tools_free_rotate_tool (Tool * tool)
name|tools_free_rotate_tool
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
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
DECL|function|rotate_info_update (Tool * tool)
name|rotate_info_update
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|TransformCore
modifier|*
name|transform_core
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
name|angle_val
operator|=
name|gimp_rad_to_deg
argument_list|(
name|transform_core
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
expr_stmt|;
name|center_vals
index|[
literal|0
index|]
operator|=
name|transform_core
operator|->
name|cx
expr_stmt|;
name|center_vals
index|[
literal|1
index|]
operator|=
name|transform_core
operator|->
name|cy
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
DECL|function|rotate_angle_changed (GtkWidget * widget,gpointer data)
name|rotate_angle_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gdouble
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
name|value
operator|=
name|gimp_deg_to_rad
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|widget
argument_list|)
operator|->
name|value
argument_list|)
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
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_center_changed (GtkWidget * widget,gpointer data)
name|rotate_center_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gint
name|cx
decl_stmt|;
name|gint
name|cy
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
name|cx
operator|=
name|RINT
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|cy
operator|=
name|RINT
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|cx
operator|!=
name|transform_core
operator|->
name|cx
operator|)
operator|||
operator|(
name|cy
operator|!=
name|transform_core
operator|->
name|cy
operator|)
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
name|cx
expr_stmt|;
name|transform_core
operator|->
name|cy
operator|=
name|cy
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
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_tool_motion (Tool * tool,void * gdisp_ptr)
name|rotate_tool_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|void
modifier|*
name|gdisp_ptr
parameter_list|)
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gdouble
name|angle1
decl_stmt|,
name|angle2
decl_stmt|,
name|angle
decl_stmt|;
name|gdouble
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|gdouble
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
name|G_PI
operator|||
name|angle
operator|<
operator|-
name|G_PI
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
literal|2.0
operator|*
name|G_PI
operator|+
name|angle1
else|:
name|angle1
operator|-
literal|2.0
operator|*
name|G_PI
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
name|G_PI
condition|)
name|transform_core
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|=
literal|2.0
operator|*
name|G_PI
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
name|G_PI
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
literal|2.0
operator|*
name|G_PI
expr_stmt|;
comment|/*  constrain the angle to 15-degree multiples if ctrl is held down  */
if|if
condition|(
name|transform_core
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
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
DECL|function|rotate_tool_recalc (Tool * tool,void * gdisp_ptr)
name|rotate_tool_recalc
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|void
modifier|*
name|gdisp_ptr
parameter_list|)
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdouble
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
name|gimp_matrix3_identity
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
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
name|gimp_matrix3_rotate
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
name|gimp_matrix3_translate
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
name|transform_core_transform_bounding_box
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
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|rotate_tool_rotate (GImage * gimage,GimpDrawable * drawable,GDisplay * gdisp,gdouble angle,TileManager * float_tiles,gboolean interpolation,GimpMatrix3 matrix)
name|rotate_tool_rotate
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|TileManager
modifier|*
name|float_tiles
parameter_list|,
name|gboolean
name|interpolation
parameter_list|,
name|GimpMatrix3
name|matrix
parameter_list|)
block|{
name|gimp_progress
modifier|*
name|progress
decl_stmt|;
name|TileManager
modifier|*
name|ret
decl_stmt|;
name|progress
operator|=
name|progress_start
argument_list|(
name|gdisp
argument_list|,
name|_
argument_list|(
literal|"Rotating..."
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ret
operator|=
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
argument_list|,
name|progress
condition|?
name|progress_update_and_flush
else|:
operator|(
name|progress_func_t
operator|)
name|NULL
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

end_unit

