begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"core/gimp-transform-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-transform.h"
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
file|"gimpperspectivetool.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimptransformoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_dialog
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_dialog_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_prepare
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_motion
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_recalc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPerspectiveTool,gimp_perspective_tool,GIMP_TYPE_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPerspectiveTool
argument_list|,
argument|gimp_perspective_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_TOOL
argument_list|)
end_macro

begin_function
name|void
name|gimp_perspective_tool_register
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
name|GIMP_TYPE_PERSPECTIVE_TOOL
argument_list|,
name|GIMP_TYPE_TRANSFORM_OPTIONS
argument_list|,
name|gimp_transform_options_gui
argument_list|,
name|GIMP_CONTEXT_BACKGROUND_MASK
argument_list|,
literal|"gimp-perspective-tool"
argument_list|,
name|_
argument_list|(
literal|"Perspective"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Perspective Tool: "
literal|"Change perspective of the layer, selection or path"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Perspective"
argument_list|)
argument_list|,
literal|"<shift>P"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_PERSPECTIVE
argument_list|,
name|GIMP_STOCK_TOOL_PERSPECTIVE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_class_init (GimpPerspectiveToolClass * klass)
name|gimp_perspective_tool_class_init
parameter_list|(
name|GimpPerspectiveToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpTransformToolClass
modifier|*
name|trans_class
init|=
name|GIMP_TRANSFORM_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|trans_class
operator|->
name|dialog
operator|=
name|gimp_perspective_tool_dialog
expr_stmt|;
name|trans_class
operator|->
name|dialog_update
operator|=
name|gimp_perspective_tool_dialog_update
expr_stmt|;
name|trans_class
operator|->
name|prepare
operator|=
name|gimp_perspective_tool_prepare
expr_stmt|;
name|trans_class
operator|->
name|motion
operator|=
name|gimp_perspective_tool_motion
expr_stmt|;
name|trans_class
operator|->
name|recalc
operator|=
name|gimp_perspective_tool_recalc
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_init (GimpPerspectiveTool * perspective_tool)
name|gimp_perspective_tool_init
parameter_list|(
name|GimpPerspectiveTool
modifier|*
name|perspective_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|perspective_tool
argument_list|)
decl_stmt|;
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|perspective_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_PERSPECTIVE
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"command"
argument_list|,
literal|"Perspective"
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Perspective transformation"
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|use_grid
operator|=
name|TRUE
expr_stmt|;
name|tr_tool
operator|->
name|use_handles
operator|=
name|TRUE
expr_stmt|;
name|tr_tool
operator|->
name|use_center
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_dialog (GimpTransformTool * tr_tool)
name|gimp_perspective_tool_dialog
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpPerspectiveTool
modifier|*
name|perspective
init|=
name|GIMP_PERSPECTIVE_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Transformation Matrix"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|tr_tool
operator|->
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|3
condition|;
name|y
operator|++
control|)
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
literal|3
condition|;
name|x
operator|++
control|)
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|gtk_label_new
argument_list|(
literal|" "
argument_list|)
decl_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_RIGHT
argument_list|)
expr_stmt|;
name|gtk_label_set_width_chars
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
name|x
argument_list|,
name|x
operator|+
literal|1
argument_list|,
name|y
argument_list|,
name|y
operator|+
literal|1
argument_list|,
name|GTK_EXPAND
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|perspective
operator|->
name|label
index|[
name|y
index|]
index|[
name|x
index|]
operator|=
name|label
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_dialog_update (GimpTransformTool * tr_tool)
name|gimp_perspective_tool_dialog_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpPerspectiveTool
modifier|*
name|perspective
init|=
name|GIMP_PERSPECTIVE_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|3
condition|;
name|y
operator|++
control|)
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
literal|3
condition|;
name|x
operator|++
control|)
block|{
name|gchar
name|buf
index|[
literal|32
index|]
decl_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%10.5f"
argument_list|,
name|tr_tool
operator|->
name|transform
operator|.
name|coeff
index|[
name|y
index|]
index|[
name|x
index|]
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|perspective
operator|->
name|label
index|[
name|y
index|]
index|[
name|x
index|]
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_prepare (GimpTransformTool * tr_tool)
name|gimp_perspective_tool_prepare
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X2
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X3
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y2
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_motion (GimpTransformTool * transform_tool)
name|gimp_perspective_tool_motion
parameter_list|(
name|GimpTransformTool
modifier|*
name|transform_tool
parameter_list|)
block|{
name|gdouble
name|diff_x
decl_stmt|,
name|diff_y
decl_stmt|;
name|diff_x
operator|=
name|transform_tool
operator|->
name|curx
operator|-
name|transform_tool
operator|->
name|lastx
expr_stmt|;
name|diff_y
operator|=
name|transform_tool
operator|->
name|cury
operator|-
name|transform_tool
operator|->
name|lasty
expr_stmt|;
switch|switch
condition|(
name|transform_tool
operator|->
name|function
condition|)
block|{
case|case
name|TRANSFORM_HANDLE_NW
case|:
name|transform_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
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
name|TRANSFORM_HANDLE_NE
case|:
name|transform_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
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
name|TRANSFORM_HANDLE_SW
case|:
name|transform_tool
operator|->
name|trans_info
index|[
name|X2
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
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
name|TRANSFORM_HANDLE_SE
case|:
name|transform_tool
operator|->
name|trans_info
index|[
name|X3
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_CENTER
case|:
name|transform_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|+=
name|diff_y
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|+=
name|diff_y
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|X2
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
operator|+=
name|diff_y
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|X3
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_recalc (GimpTransformTool * tr_tool)
name|gimp_perspective_tool_recalc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|gimp_matrix3_identity
argument_list|(
operator|&
name|tr_tool
operator|->
name|transform
argument_list|)
expr_stmt|;
name|gimp_transform_matrix_perspective
argument_list|(
operator|&
name|tr_tool
operator|->
name|transform
argument_list|,
name|tr_tool
operator|->
name|x1
argument_list|,
name|tr_tool
operator|->
name|y1
argument_list|,
name|tr_tool
operator|->
name|x2
operator|-
name|tr_tool
operator|->
name|x1
argument_list|,
name|tr_tool
operator|->
name|y2
operator|-
name|tr_tool
operator|->
name|y1
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X2
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X3
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

