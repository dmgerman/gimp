begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
file|"scale_tool.h"
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
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimplimits.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  storage for information dialog fields  */
end_comment

begin_decl_stmt
DECL|variable|orig_width_buf
specifier|static
name|gchar
name|orig_width_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|orig_height_buf
specifier|static
name|gchar
name|orig_height_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|size_vals
specifier|static
name|gdouble
name|size_vals
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|x_ratio_buf
specifier|static
name|gchar
name|x_ratio_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|y_ratio_buf
specifier|static
name|gchar
name|y_ratio_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  needed for original size unit update  */
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
name|scale_tool_recalc
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
name|scale_tool_motion
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
name|scale_info_update
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  callback functions for the info dialog fields  */
end_comment

begin_function_decl
specifier|static
name|void
name|scale_size_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|scale_unit_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|TileManager
modifier|*
DECL|function|scale_tool_transform (Tool * tool,gpointer gdisp_ptr,TransformState state)
name|scale_tool_transform
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
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
name|size_vals
index|[
literal|0
index|]
operator|=
name|transform_core
operator|->
name|x2
operator|-
name|transform_core
operator|->
name|x1
expr_stmt|;
name|size_vals
index|[
literal|1
index|]
operator|=
name|transform_core
operator|->
name|y2
operator|-
name|transform_core
operator|->
name|y1
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
literal|"Scaling Information"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"tools/transform_scale.html"
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|transform_info
argument_list|,
name|_
argument_list|(
literal|"Original Width:"
argument_list|)
argument_list|,
name|orig_width_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|transform_info
argument_list|,
name|_
argument_list|(
literal|"Height:"
argument_list|)
argument_list|,
name|orig_height_buf
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|info_dialog_add_spinbutton
argument_list|(
name|transform_info
argument_list|,
name|_
argument_list|(
literal|"Current Width:"
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
literal|"Height:"
argument_list|)
argument_list|,
name|size_vals
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
name|scale_size_changed
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|"unit_changed"
argument_list|,
name|scale_unit_changed
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
name|spinbutton
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|transform_info
argument_list|,
name|_
argument_list|(
literal|"Scale Ratio X:"
argument_list|)
argument_list|,
name|x_ratio_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|transform_info
argument_list|,
name|_
argument_list|(
literal|"Y:"
argument_list|)
argument_list|,
name|y_ratio_buf
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
literal|4
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
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
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
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
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
literal|0
argument_list|,
name|size_vals
index|[
literal|0
index|]
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
literal|0
argument_list|,
name|size_vals
index|[
literal|1
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
literal|0
argument_list|,
name|size_vals
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
name|size_vals
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|transform_info
operator|->
name|shell
argument_list|)
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
name|y2
expr_stmt|;
return|return
name|NULL
return|;
break|break;
case|case
name|MOTION
case|:
name|scale_tool_motion
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|)
expr_stmt|;
name|scale_tool_recalc
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
name|scale_tool_recalc
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
name|scale_tool_scale
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
DECL|function|tools_new_scale_tool (void)
name|tools_new_scale_tool
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
name|SCALE
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
comment|/*  set the scale specific transformation attributes  */
name|private
operator|->
name|trans_func
operator|=
name|scale_tool_transform
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
literal|0.0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
literal|0.0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
literal|0.0
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|Y1
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
DECL|function|tools_free_scale_tool (Tool * tool)
name|tools_free_scale_tool
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
DECL|function|scale_info_update (Tool * tool)
name|scale_info_update
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
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gdouble
name|ratio_x
decl_stmt|,
name|ratio_y
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|,
name|x3
decl_stmt|,
name|y3
decl_stmt|,
name|x4
decl_stmt|,
name|y4
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
name|gchar
name|format_buf
index|[
literal|16
index|]
decl_stmt|;
specifier|static
name|GimpUnit
name|label_unit
init|=
name|GIMP_UNIT_PIXEL
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
name|unit
operator|=
name|gimp_size_entry_get_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|)
expr_stmt|;
empty_stmt|;
comment|/*  Find original sizes  */
name|x1
operator|=
name|transform_core
operator|->
name|x1
expr_stmt|;
name|y1
operator|=
name|transform_core
operator|->
name|y1
expr_stmt|;
name|x2
operator|=
name|transform_core
operator|->
name|x2
expr_stmt|;
name|y2
operator|=
name|transform_core
operator|->
name|y2
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PERCENT
condition|)
name|label_unit
operator|=
name|unit
expr_stmt|;
name|unit_factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|label_unit
argument_list|)
expr_stmt|;
if|if
condition|(
name|label_unit
condition|)
comment|/* unit != GIMP_UNIT_PIXEL */
block|{
name|g_snprintf
argument_list|(
name|format_buf
argument_list|,
sizeof|sizeof
argument_list|(
name|format_buf
argument_list|)
argument_list|,
literal|"%%.%df %s"
argument_list|,
name|gimp_unit_get_digits
argument_list|(
name|label_unit
argument_list|)
operator|+
literal|1
argument_list|,
name|gimp_unit_get_symbol
argument_list|(
name|label_unit
argument_list|)
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|orig_width_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
name|format_buf
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|unit_factor
operator|/
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|orig_height_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
name|format_buf
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
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
else|else
comment|/* unit == GIMP_UNIT_PIXEL */
block|{
name|g_snprintf
argument_list|(
name|orig_width_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
literal|"%d"
argument_list|,
name|x2
operator|-
name|x1
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|orig_height_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
literal|"%d"
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
block|}
comment|/*  Find current sizes  */
name|x3
operator|=
operator|(
name|int
operator|)
name|transform_core
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y3
operator|=
operator|(
name|int
operator|)
name|transform_core
operator|->
name|trans_info
index|[
name|Y0
index|]
expr_stmt|;
name|x4
operator|=
operator|(
name|int
operator|)
name|transform_core
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y4
operator|=
operator|(
name|int
operator|)
name|transform_core
operator|->
name|trans_info
index|[
name|Y1
index|]
expr_stmt|;
name|size_vals
index|[
literal|0
index|]
operator|=
name|x4
operator|-
name|x3
expr_stmt|;
name|size_vals
index|[
literal|1
index|]
operator|=
name|y4
operator|-
name|y3
expr_stmt|;
name|ratio_x
operator|=
name|ratio_y
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|x2
operator|-
name|x1
condition|)
name|ratio_x
operator|=
call|(
name|double
call|)
argument_list|(
name|x4
operator|-
name|x3
argument_list|)
operator|/
call|(
name|double
call|)
argument_list|(
name|x2
operator|-
name|x1
argument_list|)
expr_stmt|;
if|if
condition|(
name|y2
operator|-
name|y1
condition|)
name|ratio_y
operator|=
call|(
name|double
call|)
argument_list|(
name|y4
operator|-
name|y3
argument_list|)
operator|/
call|(
name|double
call|)
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|x_ratio_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
literal|"%0.2f"
argument_list|,
name|ratio_x
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|y_ratio_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
literal|"%0.2f"
argument_list|,
name|ratio_y
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
DECL|function|scale_size_changed (GtkWidget * widget,gpointer data)
name|scale_size_changed
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
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
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
name|width
operator|=
call|(
name|int
call|)
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
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|height
operator|=
call|(
name|int
call|)
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
operator|+
literal|0.5
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|width
operator|!=
operator|(
name|transform_core
operator|->
name|trans_info
index|[
name|X1
index|]
operator|-
name|transform_core
operator|->
name|trans_info
index|[
name|X0
index|]
operator|)
operator|)
operator|||
operator|(
name|height
operator|!=
operator|(
name|transform_core
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|-
name|transform_core
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|)
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
name|trans_info
index|[
name|X1
index|]
operator|=
name|transform_core
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+
name|width
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
name|transform_core
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|+
name|height
expr_stmt|;
name|scale_tool_recalc
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
DECL|function|scale_unit_changed (GtkWidget * widget,gpointer data)
name|scale_unit_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|scale_info_update
argument_list|(
operator|(
name|Tool
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|scale_tool_motion (Tool * tool,void * gdisp_ptr)
name|scale_tool_motion
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gdouble
name|ratio
decl_stmt|;
name|gdouble
modifier|*
name|x1
decl_stmt|;
name|gdouble
modifier|*
name|y1
decl_stmt|;
name|gdouble
modifier|*
name|x2
decl_stmt|;
name|gdouble
modifier|*
name|y2
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|dir_x
decl_stmt|,
name|dir_y
decl_stmt|;
name|gint
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
name|x1
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y1
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|Y0
index|]
expr_stmt|;
name|x2
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y2
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|Y1
index|]
expr_stmt|;
name|dir_x
operator|=
name|dir_y
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|HANDLE_2
case|:
name|x1
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y1
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|Y0
index|]
expr_stmt|;
name|x2
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y2
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|Y1
index|]
expr_stmt|;
name|dir_x
operator|=
operator|-
literal|1
expr_stmt|;
name|dir_y
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|HANDLE_3
case|:
name|x1
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y1
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|Y1
index|]
expr_stmt|;
name|x2
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y2
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|Y0
index|]
expr_stmt|;
name|dir_x
operator|=
literal|1
expr_stmt|;
name|dir_y
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|HANDLE_4
case|:
name|x1
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y1
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|Y1
index|]
expr_stmt|;
name|x2
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y2
operator|=
operator|&
name|transform_core
operator|->
name|trans_info
index|[
name|Y0
index|]
expr_stmt|;
name|dir_x
operator|=
name|dir_y
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
default|default :
return|return;
block|}
comment|/*  if just the mod1 key is down, affect only the height  */
if|if
condition|(
name|transform_core
operator|->
name|state
operator|&
name|GDK_MOD1_MASK
operator|&&
operator|!
operator|(
name|transform_core
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
condition|)
name|diff_x
operator|=
literal|0
expr_stmt|;
comment|/*  if just the control key is down, affect only the width  */
elseif|else
if|if
condition|(
name|transform_core
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
operator|&&
operator|!
operator|(
name|transform_core
operator|->
name|state
operator|&
name|GDK_MOD1_MASK
operator|)
condition|)
name|diff_y
operator|=
literal|0
expr_stmt|;
operator|*
name|x1
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|y1
operator|+=
name|diff_y
expr_stmt|;
if|if
condition|(
name|dir_x
operator|>
literal|0
condition|)
block|{
if|if
condition|(
operator|*
name|x1
operator|>=
operator|*
name|x2
condition|)
operator|*
name|x1
operator|=
operator|*
name|x2
operator|-
literal|1
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|*
name|x1
operator|<=
operator|*
name|x2
condition|)
operator|*
name|x1
operator|=
operator|*
name|x2
operator|+
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|dir_y
operator|>
literal|0
condition|)
block|{
if|if
condition|(
operator|*
name|y1
operator|>=
operator|*
name|y2
condition|)
operator|*
name|y1
operator|=
operator|*
name|y2
operator|-
literal|1
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|*
name|y1
operator|<=
operator|*
name|y2
condition|)
operator|*
name|y1
operator|=
operator|*
name|y2
operator|+
literal|1
expr_stmt|;
block|}
comment|/*  if both the control key& mod1 keys are down,    *  keep the aspect ratio intact     */
if|if
condition|(
name|transform_core
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
operator|&&
name|transform_core
operator|->
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
block|{
name|ratio
operator|=
call|(
name|double
call|)
argument_list|(
name|transform_core
operator|->
name|x2
operator|-
name|transform_core
operator|->
name|x1
argument_list|)
operator|/
call|(
name|double
call|)
argument_list|(
name|transform_core
operator|->
name|y2
operator|-
name|transform_core
operator|->
name|y1
argument_list|)
expr_stmt|;
name|w
operator|=
name|ABS
argument_list|(
operator|(
operator|*
name|x2
operator|-
operator|*
name|x1
operator|)
argument_list|)
expr_stmt|;
name|h
operator|=
name|ABS
argument_list|(
operator|(
operator|*
name|y2
operator|-
operator|*
name|y1
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|w
operator|>
name|h
operator|*
name|ratio
condition|)
name|h
operator|=
name|w
operator|/
name|ratio
expr_stmt|;
else|else
name|w
operator|=
name|h
operator|*
name|ratio
expr_stmt|;
operator|*
name|y1
operator|=
operator|*
name|y2
operator|-
name|dir_y
operator|*
name|h
expr_stmt|;
operator|*
name|x1
operator|=
operator|*
name|x2
operator|-
name|dir_x
operator|*
name|w
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|scale_tool_recalc (Tool * tool,void * gdisp_ptr)
name|scale_tool_recalc
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
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|diffx
decl_stmt|,
name|diffy
decl_stmt|;
name|gint
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|gdouble
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
name|x1
operator|=
operator|(
name|int
operator|)
name|transform_core
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y1
operator|=
operator|(
name|int
operator|)
name|transform_core
operator|->
name|trans_info
index|[
name|Y0
index|]
expr_stmt|;
name|x2
operator|=
operator|(
name|int
operator|)
name|transform_core
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y2
operator|=
operator|(
name|int
operator|)
name|transform_core
operator|->
name|trans_info
index|[
name|Y1
index|]
expr_stmt|;
name|scalex
operator|=
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
call|(
name|double
call|)
argument_list|(
name|x2
operator|-
name|x1
argument_list|)
operator|/
call|(
name|double
call|)
argument_list|(
name|transform_core
operator|->
name|x2
operator|-
name|transform_core
operator|->
name|x1
argument_list|)
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
call|(
name|double
call|)
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
operator|/
call|(
name|double
call|)
argument_list|(
name|transform_core
operator|->
name|y2
operator|-
name|transform_core
operator|->
name|y1
argument_list|)
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
name|cx
operator|=
name|x2
expr_stmt|;
name|cy
operator|=
name|y2
expr_stmt|;
name|diffx
operator|=
name|x2
operator|-
name|transform_core
operator|->
name|x2
expr_stmt|;
name|diffy
operator|=
name|y2
operator|-
name|transform_core
operator|->
name|y2
expr_stmt|;
break|break;
case|case
name|HANDLE_2
case|:
name|cx
operator|=
name|x1
expr_stmt|;
name|cy
operator|=
name|y2
expr_stmt|;
name|diffx
operator|=
name|x1
operator|-
name|transform_core
operator|->
name|x1
expr_stmt|;
name|diffy
operator|=
name|y2
operator|-
name|transform_core
operator|->
name|y2
expr_stmt|;
break|break;
case|case
name|HANDLE_3
case|:
name|cx
operator|=
name|x2
expr_stmt|;
name|cy
operator|=
name|y1
expr_stmt|;
name|diffx
operator|=
name|x2
operator|-
name|transform_core
operator|->
name|x2
expr_stmt|;
name|diffy
operator|=
name|y1
operator|-
name|transform_core
operator|->
name|y1
expr_stmt|;
break|break;
case|case
name|HANDLE_4
case|:
name|cx
operator|=
name|x1
expr_stmt|;
name|cy
operator|=
name|y1
expr_stmt|;
name|diffx
operator|=
name|x1
operator|-
name|transform_core
operator|->
name|x1
expr_stmt|;
name|diffy
operator|=
name|y1
operator|-
name|transform_core
operator|->
name|y1
expr_stmt|;
break|break;
default|default :
name|cx
operator|=
name|x1
expr_stmt|;
name|cy
operator|=
name|y1
expr_stmt|;
name|diffx
operator|=
name|diffy
operator|=
literal|0
expr_stmt|;
break|break;
block|}
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
operator|(
name|double
operator|)
operator|-
name|cx
operator|+
name|diffx
argument_list|,
operator|(
name|double
operator|)
operator|-
name|cy
operator|+
name|diffy
argument_list|)
expr_stmt|;
name|gimp_matrix3_scale
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
name|gimp_matrix3_translate
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|,
operator|(
name|double
operator|)
name|cx
argument_list|,
operator|(
name|double
operator|)
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
name|scale_info_update
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|scale_tool_scale (GImage * gimage,GimpDrawable * drawable,GDisplay * gdisp,gdouble * trans_info,TileManager * float_tiles,gboolean interpolation,GimpMatrix3 matrix)
name|scale_tool_scale
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
modifier|*
name|trans_info
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
literal|"Scaling..."
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

