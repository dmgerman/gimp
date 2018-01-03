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
file|"libgimpmath/gimpmath.h"
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
file|"display/gimptoolgui.h"
end_include

begin_include
include|#
directive|include
file|"display/gimptooltransformgrid.h"
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
file|"gimpunifiedtransformtool.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  index into trans_info array  */
end_comment

begin_enum
enum|enum
DECL|enum|__anon276ea1800103
block|{
DECL|enumerator|X0
name|X0
block|,
DECL|enumerator|Y0
name|Y0
block|,
DECL|enumerator|X1
name|X1
block|,
DECL|enumerator|Y1
name|Y1
block|,
DECL|enumerator|X2
name|X2
block|,
DECL|enumerator|Y2
name|Y2
block|,
DECL|enumerator|X3
name|X3
block|,
DECL|enumerator|Y3
name|Y3
block|,
DECL|enumerator|PIVOT_X
name|PIVOT_X
block|,
DECL|enumerator|PIVOT_Y
name|PIVOT_Y
block|, }
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_unified_transform_tool_dialog
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
name|gimp_unified_transform_tool_dialog_update
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
name|gimp_unified_transform_tool_prepare
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpToolWidget
modifier|*
name|gimp_unified_transform_tool_get_widget
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
name|gimp_unified_transform_tool_recalc_matrix
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_unified_transform_tool_get_undo_desc
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
name|gimp_unified_transform_tool_widget_changed
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpUnifiedTransformTool,gimp_unified_transform_tool,GIMP_TYPE_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpUnifiedTransformTool
argument_list|,
argument|gimp_unified_transform_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_TOOL
argument_list|)
end_macro

begin_function
name|void
name|gimp_unified_transform_tool_register
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
name|GIMP_TYPE_UNIFIED_TRANSFORM_TOOL
argument_list|,
name|GIMP_TYPE_TRANSFORM_OPTIONS
argument_list|,
name|gimp_transform_options_gui
argument_list|,
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
argument_list|,
literal|"gimp-unified-transform-tool"
argument_list|,
name|_
argument_list|(
literal|"Unified Transform"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Unified Transform Tool: "
literal|"Transform the layer, selection or path"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Unified Transform"
argument_list|)
argument_list|,
literal|"<shift>T"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_UNIFIED_TRANSFORM
argument_list|,
name|GIMP_ICON_TOOL_UNIFIED_TRANSFORM
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unified_transform_tool_class_init (GimpUnifiedTransformToolClass * klass)
name|gimp_unified_transform_tool_class_init
parameter_list|(
name|GimpUnifiedTransformToolClass
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
name|gimp_unified_transform_tool_dialog
expr_stmt|;
name|trans_class
operator|->
name|dialog_update
operator|=
name|gimp_unified_transform_tool_dialog_update
expr_stmt|;
name|trans_class
operator|->
name|prepare
operator|=
name|gimp_unified_transform_tool_prepare
expr_stmt|;
name|trans_class
operator|->
name|get_widget
operator|=
name|gimp_unified_transform_tool_get_widget
expr_stmt|;
name|trans_class
operator|->
name|recalc_matrix
operator|=
name|gimp_unified_transform_tool_recalc_matrix
expr_stmt|;
name|trans_class
operator|->
name|get_undo_desc
operator|=
name|gimp_unified_transform_tool_get_undo_desc
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unified_transform_tool_init (GimpUnifiedTransformTool * unified_tool)
name|gimp_unified_transform_tool_init
parameter_list|(
name|GimpUnifiedTransformTool
modifier|*
name|unified_tool
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|unified_tool
argument_list|)
decl_stmt|;
name|tr_tool
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Unified transform"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unified_transform_tool_dialog (GimpTransformTool * tr_tool)
name|gimp_unified_transform_tool_dialog
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpUnifiedTransformTool
modifier|*
name|unified
init|=
name|GIMP_UNIFIED_TRANSFORM_TOOL
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
literal|"Transform Matrix"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gimp_tool_gui_get_vbox
argument_list|(
name|tr_tool
operator|->
name|gui
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
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
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
name|unified
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
DECL|function|gimp_unified_transform_tool_dialog_update (GimpTransformTool * tr_tool)
name|gimp_unified_transform_tool_dialog_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpUnifiedTransformTool
modifier|*
name|unified
init|=
name|GIMP_UNIFIED_TRANSFORM_TOOL
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
name|unified
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
DECL|function|gimp_unified_transform_tool_prepare (GimpTransformTool * tr_tool)
name|gimp_unified_transform_tool_prepare
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
name|PIVOT_X
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|tr_tool
operator|->
name|x1
operator|+
name|tr_tool
operator|->
name|x2
argument_list|)
operator|/
literal|2.0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|tr_tool
operator|->
name|y1
operator|+
name|tr_tool
operator|->
name|y2
argument_list|)
operator|/
literal|2.0
expr_stmt|;
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
name|GimpToolWidget
modifier|*
DECL|function|gimp_unified_transform_tool_get_widget (GimpTransformTool * tr_tool)
name|gimp_unified_transform_tool_get_widget
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|tool
operator|->
name|display
argument_list|)
decl_stmt|;
name|GimpToolWidget
modifier|*
name|widget
decl_stmt|;
name|widget
operator|=
name|gimp_tool_transform_grid_new
argument_list|(
name|shell
argument_list|,
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
argument_list|,
name|tr_tool
operator|->
name|y2
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|widget
argument_list|,
literal|"pivot-x"
argument_list|,
operator|(
name|tr_tool
operator|->
name|x1
operator|+
name|tr_tool
operator|->
name|x2
operator|)
operator|/
literal|2.0
argument_list|,
literal|"pivot-y"
argument_list|,
operator|(
name|tr_tool
operator|->
name|y1
operator|+
name|tr_tool
operator|->
name|y2
operator|)
operator|/
literal|2.0
argument_list|,
literal|"inside-function"
argument_list|,
name|GIMP_TRANSFORM_FUNCTION_MOVE
argument_list|,
literal|"outside-function"
argument_list|,
name|GIMP_TRANSFORM_FUNCTION_ROTATE
argument_list|,
literal|"use-corner-handles"
argument_list|,
name|TRUE
argument_list|,
literal|"use-perspective-handles"
argument_list|,
name|TRUE
argument_list|,
literal|"use-side-handles"
argument_list|,
name|TRUE
argument_list|,
literal|"use-shear-handles"
argument_list|,
name|TRUE
argument_list|,
literal|"use-pivot-handle"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_unified_transform_tool_widget_changed
argument_list|)
argument_list|,
name|tr_tool
argument_list|)
expr_stmt|;
return|return
name|widget
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unified_transform_tool_recalc_matrix (GimpTransformTool * tr_tool,GimpToolWidget * widget)
name|gimp_unified_transform_tool_recalc_matrix
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpToolWidget
modifier|*
name|widget
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
if|if
condition|(
name|widget
condition|)
name|g_object_set
argument_list|(
name|widget
argument_list|,
literal|"transform"
argument_list|,
operator|&
name|tr_tool
operator|->
name|transform
argument_list|,
literal|"x1"
argument_list|,
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x1
argument_list|,
literal|"y1"
argument_list|,
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y1
argument_list|,
literal|"x2"
argument_list|,
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x2
argument_list|,
literal|"y2"
argument_list|,
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y2
argument_list|,
literal|"pivot-x"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|,
literal|"pivot-y"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_unified_transform_tool_get_undo_desc (GimpTransformTool * tr_tool)
name|gimp_unified_transform_tool_get_undo_desc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
return|return
name|g_strdup
argument_list|(
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Unified Transform"
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unified_transform_tool_widget_changed (GimpToolWidget * widget,GimpTransformTool * tr_tool)
name|gimp_unified_transform_tool_widget_changed
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpMatrix3
modifier|*
name|transform
decl_stmt|;
name|g_object_get
argument_list|(
name|widget
argument_list|,
literal|"transform"
argument_list|,
operator|&
name|transform
argument_list|,
literal|"pivot-x"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|,
literal|"pivot-y"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
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
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|transform
argument_list|,
name|tr_tool
operator|->
name|x2
argument_list|,
name|tr_tool
operator|->
name|y1
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|transform
argument_list|,
name|tr_tool
operator|->
name|x1
argument_list|,
name|tr_tool
operator|->
name|y2
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X2
index|]
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|transform
argument_list|,
name|tr_tool
operator|->
name|x2
argument_list|,
name|tr_tool
operator|->
name|y2
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X3
index|]
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|transform
argument_list|)
expr_stmt|;
name|gimp_transform_tool_recalc_matrix
argument_list|(
name|tr_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

