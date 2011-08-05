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
file|"gimpunifiedtransformtool.h"
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
comment|/*  index into trans_info array  */
end_comment

begin_enum
enum|enum
DECL|enum|__anon2c7fb5740103
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
name|void
name|gimp_unified_transform_tool_motion
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpUnifiedTransformationTool,gimp_unified_transform_tool,GIMP_TYPE_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpUnifiedTransformationTool
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
name|GIMP_CONTEXT_BACKGROUND_MASK
argument_list|,
literal|"gimp-unified-transform-tool"
argument_list|,
name|_
argument_list|(
literal|"Unified Transformation"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Unified Transformation Tool: "
literal|"Transform the layer, selection or path"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Unified Transformation"
argument_list|)
argument_list|,
literal|"<shift>U"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_UNIFIED_TRANSFORM
argument_list|,
name|GIMP_STOCK_TOOL_UNIFIED_TRANSFORM
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unified_transform_tool_class_init (GimpUnifiedTransformationToolClass * klass)
name|gimp_unified_transform_tool_class_init
parameter_list|(
name|GimpUnifiedTransformationToolClass
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
name|motion
operator|=
name|gimp_unified_transform_tool_motion
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
DECL|function|gimp_unified_transform_tool_init (GimpUnifiedTransformationTool * unified_tool)
name|gimp_unified_transform_tool_init
parameter_list|(
name|GimpUnifiedTransformationTool
modifier|*
name|unified_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|unified_tool
argument_list|)
decl_stmt|;
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|unified_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_UNIFIED_TRANSFORM
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Unified transform"
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
name|tr_tool
operator|->
name|use_mid_handles
operator|=
name|TRUE
expr_stmt|;
name|tr_tool
operator|->
name|use_pivot
operator|=
name|TRUE
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
name|GimpUnifiedTransformationTool
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
name|content_area
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
name|content_area
operator|=
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|tr_tool
operator|->
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
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
name|content_area
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
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.0
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
name|GimpUnifiedTransformationTool
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
DECL|function|dotprod (GimpVector2 a,GimpVector2 b)
specifier|static
specifier|inline
name|gdouble
name|dotprod
parameter_list|(
name|GimpVector2
name|a
parameter_list|,
name|GimpVector2
name|b
parameter_list|)
block|{
return|return
name|a
operator|.
name|x
operator|*
name|b
operator|.
name|x
operator|+
name|a
operator|.
name|y
operator|*
name|b
operator|.
name|y
return|;
block|}
end_function

begin_function
DECL|function|norm (GimpVector2 a)
specifier|static
specifier|inline
name|gdouble
name|norm
parameter_list|(
name|GimpVector2
name|a
parameter_list|)
block|{
return|return
name|sqrt
argument_list|(
name|dotprod
argument_list|(
name|a
argument_list|,
name|a
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|vectorsubtract (GimpVector2 a,GimpVector2 b)
specifier|static
specifier|inline
name|GimpVector2
name|vectorsubtract
parameter_list|(
name|GimpVector2
name|a
parameter_list|,
name|GimpVector2
name|b
parameter_list|)
block|{
name|GimpVector2
name|c
decl_stmt|;
name|c
operator|.
name|x
operator|=
name|a
operator|.
name|x
operator|-
name|b
operator|.
name|x
expr_stmt|;
name|c
operator|.
name|y
operator|=
name|a
operator|.
name|y
operator|-
name|b
operator|.
name|y
expr_stmt|;
return|return
name|c
return|;
block|}
end_function

begin_function
DECL|function|vectoradd (GimpVector2 a,GimpVector2 b)
specifier|static
specifier|inline
name|GimpVector2
name|vectoradd
parameter_list|(
name|GimpVector2
name|a
parameter_list|,
name|GimpVector2
name|b
parameter_list|)
block|{
name|GimpVector2
name|c
decl_stmt|;
name|c
operator|.
name|x
operator|=
name|a
operator|.
name|x
operator|+
name|b
operator|.
name|x
expr_stmt|;
name|c
operator|.
name|y
operator|=
name|a
operator|.
name|y
operator|+
name|b
operator|.
name|y
expr_stmt|;
return|return
name|c
return|;
block|}
end_function

begin_function
DECL|function|scalemult (GimpVector2 a,gdouble b)
specifier|static
specifier|inline
name|GimpVector2
name|scalemult
parameter_list|(
name|GimpVector2
name|a
parameter_list|,
name|gdouble
name|b
parameter_list|)
block|{
name|GimpVector2
name|c
decl_stmt|;
name|c
operator|.
name|x
operator|=
name|a
operator|.
name|x
operator|*
name|b
expr_stmt|;
name|c
operator|.
name|y
operator|=
name|a
operator|.
name|y
operator|*
name|b
expr_stmt|;
return|return
name|c
return|;
block|}
end_function

begin_comment
comment|/* finds the clockwise angle between the vectors given, 0-2Ï */
end_comment

begin_function
DECL|function|calcangle (GimpVector2 a,GimpVector2 b)
specifier|static
specifier|inline
name|gdouble
name|calcangle
parameter_list|(
name|GimpVector2
name|a
parameter_list|,
name|GimpVector2
name|b
parameter_list|)
block|{
name|gdouble
name|angle
decl_stmt|,
name|angle2
decl_stmt|,
name|length
init|=
name|norm
argument_list|(
name|a
argument_list|)
operator|*
name|norm
argument_list|(
name|b
argument_list|)
decl_stmt|;
name|angle
operator|=
name|acos
argument_list|(
name|dotprod
argument_list|(
name|a
argument_list|,
name|b
argument_list|)
operator|/
name|length
argument_list|)
expr_stmt|;
name|angle2
operator|=
name|b
operator|.
name|y
expr_stmt|;
name|b
operator|.
name|y
operator|=
operator|-
name|b
operator|.
name|x
expr_stmt|;
name|b
operator|.
name|x
operator|=
name|angle2
expr_stmt|;
name|angle2
operator|=
name|acos
argument_list|(
name|dotprod
argument_list|(
name|a
argument_list|,
name|b
argument_list|)
operator|/
name|length
argument_list|)
expr_stmt|;
return|return
operator|-
operator|(
operator|(
name|angle2
operator|>
name|G_PI
operator|/
literal|2.
operator|)
condition|?
literal|2
operator|*
name|G_PI
operator|-
name|angle
else|:
name|angle
operator|)
return|;
block|}
end_function

begin_function
DECL|function|rotate2d (GimpVector2 p,gdouble angle)
specifier|static
specifier|inline
name|GimpVector2
name|rotate2d
parameter_list|(
name|GimpVector2
name|p
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
name|GimpVector2
name|ret
decl_stmt|;
name|ret
operator|.
name|x
operator|=
name|cos
argument_list|(
name|angle
argument_list|)
operator|*
name|p
operator|.
name|x
operator|-
name|sin
argument_list|(
name|angle
argument_list|)
operator|*
name|p
operator|.
name|y
expr_stmt|;
name|ret
operator|.
name|y
operator|=
name|sin
argument_list|(
name|angle
argument_list|)
operator|*
name|p
operator|.
name|x
operator|+
name|cos
argument_list|(
name|angle
argument_list|)
operator|*
name|p
operator|.
name|y
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
DECL|function|shearvector (GimpVector2 p,gdouble factor)
specifier|static
specifier|inline
name|GimpVector2
name|shearvector
parameter_list|(
name|GimpVector2
name|p
parameter_list|,
name|gdouble
name|factor
parameter_list|)
block|{
name|GimpVector2
name|ret
decl_stmt|;
name|ret
operator|.
name|x
operator|=
name|p
operator|.
name|x
operator|+
name|p
operator|.
name|y
operator|*
name|factor
expr_stmt|;
name|ret
operator|.
name|y
operator|=
name|p
operator|.
name|y
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unified_transform_tool_motion (GimpTransformTool * transform_tool)
name|gimp_unified_transform_tool_motion
parameter_list|(
name|GimpTransformTool
modifier|*
name|transform_tool
parameter_list|)
block|{
name|gdouble
name|diff_x
init|=
name|transform_tool
operator|->
name|curx
operator|-
name|transform_tool
operator|->
name|lastx
decl_stmt|,
name|diff_y
init|=
name|transform_tool
operator|->
name|cury
operator|-
name|transform_tool
operator|->
name|lasty
decl_stmt|;
name|gdouble
modifier|*
name|x
index|[
literal|4
index|]
decl_stmt|,
modifier|*
name|y
index|[
literal|4
index|]
decl_stmt|,
name|px
index|[
literal|4
index|]
decl_stmt|,
name|py
index|[
literal|4
index|]
decl_stmt|,
modifier|*
name|pivot_x
decl_stmt|,
modifier|*
name|pivot_y
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gboolean
name|horizontal
init|=
name|FALSE
decl_stmt|;
name|GimpTransformOptions
modifier|*
name|options
init|=
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
argument_list|(
name|transform_tool
argument_list|)
decl_stmt|;
name|x
index|[
literal|0
index|]
operator|=
operator|&
name|transform_tool
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|x
index|[
literal|1
index|]
operator|=
operator|&
name|transform_tool
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|x
index|[
literal|2
index|]
operator|=
operator|&
name|transform_tool
operator|->
name|trans_info
index|[
name|X2
index|]
expr_stmt|;
name|x
index|[
literal|3
index|]
operator|=
operator|&
name|transform_tool
operator|->
name|trans_info
index|[
name|X3
index|]
expr_stmt|;
name|y
index|[
literal|0
index|]
operator|=
operator|&
name|transform_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
expr_stmt|;
name|y
index|[
literal|1
index|]
operator|=
operator|&
name|transform_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
expr_stmt|;
name|y
index|[
literal|2
index|]
operator|=
operator|&
name|transform_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
expr_stmt|;
name|y
index|[
literal|3
index|]
operator|=
operator|&
name|transform_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
expr_stmt|;
name|px
index|[
literal|0
index|]
operator|=
operator|(
operator|*
name|transform_tool
operator|->
name|prev_trans_info
operator|)
index|[
name|X0
index|]
expr_stmt|;
name|px
index|[
literal|1
index|]
operator|=
operator|(
operator|*
name|transform_tool
operator|->
name|prev_trans_info
operator|)
index|[
name|X1
index|]
expr_stmt|;
name|px
index|[
literal|2
index|]
operator|=
operator|(
operator|*
name|transform_tool
operator|->
name|prev_trans_info
operator|)
index|[
name|X2
index|]
expr_stmt|;
name|px
index|[
literal|3
index|]
operator|=
operator|(
operator|*
name|transform_tool
operator|->
name|prev_trans_info
operator|)
index|[
name|X3
index|]
expr_stmt|;
name|py
index|[
literal|0
index|]
operator|=
operator|(
operator|*
name|transform_tool
operator|->
name|prev_trans_info
operator|)
index|[
name|Y0
index|]
expr_stmt|;
name|py
index|[
literal|1
index|]
operator|=
operator|(
operator|*
name|transform_tool
operator|->
name|prev_trans_info
operator|)
index|[
name|Y1
index|]
expr_stmt|;
name|py
index|[
literal|2
index|]
operator|=
operator|(
operator|*
name|transform_tool
operator|->
name|prev_trans_info
operator|)
index|[
name|Y2
index|]
expr_stmt|;
name|py
index|[
literal|3
index|]
operator|=
operator|(
operator|*
name|transform_tool
operator|->
name|prev_trans_info
operator|)
index|[
name|Y3
index|]
expr_stmt|;
name|pivot_x
operator|=
operator|&
name|transform_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
expr_stmt|;
name|pivot_y
operator|=
operator|&
name|transform_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|alternate
condition|)
block|{
name|gdouble
modifier|*
name|x0
decl_stmt|,
modifier|*
name|x1
decl_stmt|,
modifier|*
name|y0
decl_stmt|,
modifier|*
name|y1
decl_stmt|;
name|gboolean
name|moveedge
init|=
name|FALSE
decl_stmt|;
switch|switch
condition|(
name|transform_tool
operator|->
name|function
condition|)
block|{
case|case
name|TRANSFORM_HANDLE_W
case|:
name|x0
operator|=
name|x
index|[
literal|0
index|]
expr_stmt|;
name|y0
operator|=
name|y
index|[
literal|0
index|]
expr_stmt|;
name|x1
operator|=
name|x
index|[
literal|2
index|]
expr_stmt|;
name|y1
operator|=
name|y
index|[
literal|2
index|]
expr_stmt|;
name|moveedge
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_S
case|:
name|x0
operator|=
name|x
index|[
literal|2
index|]
expr_stmt|;
name|y0
operator|=
name|y
index|[
literal|2
index|]
expr_stmt|;
name|x1
operator|=
name|x
index|[
literal|3
index|]
expr_stmt|;
name|y1
operator|=
name|y
index|[
literal|3
index|]
expr_stmt|;
name|moveedge
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_N
case|:
name|x0
operator|=
name|x
index|[
literal|0
index|]
expr_stmt|;
name|y0
operator|=
name|y
index|[
literal|0
index|]
expr_stmt|;
name|x1
operator|=
name|x
index|[
literal|1
index|]
expr_stmt|;
name|y1
operator|=
name|y
index|[
literal|1
index|]
expr_stmt|;
name|moveedge
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_E
case|:
name|x0
operator|=
name|x
index|[
literal|1
index|]
expr_stmt|;
name|y0
operator|=
name|y
index|[
literal|1
index|]
expr_stmt|;
name|x1
operator|=
name|x
index|[
literal|3
index|]
expr_stmt|;
name|y1
operator|=
name|y
index|[
literal|3
index|]
expr_stmt|;
name|moveedge
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_NW
case|:
operator|*
name|x
index|[
literal|0
index|]
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|y
index|[
literal|0
index|]
operator|+=
name|diff_y
expr_stmt|;
return|return;
case|case
name|TRANSFORM_HANDLE_NE
case|:
operator|*
name|x
index|[
literal|1
index|]
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|y
index|[
literal|1
index|]
operator|+=
name|diff_y
expr_stmt|;
return|return;
case|case
name|TRANSFORM_HANDLE_SW
case|:
operator|*
name|x
index|[
literal|2
index|]
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|y
index|[
literal|2
index|]
operator|+=
name|diff_y
expr_stmt|;
return|return;
case|case
name|TRANSFORM_HANDLE_SE
case|:
operator|*
name|x
index|[
literal|3
index|]
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|y
index|[
literal|3
index|]
operator|+=
name|diff_y
expr_stmt|;
return|return;
default|default:
break|break;
block|}
if|if
condition|(
name|moveedge
condition|)
block|{
operator|*
name|x0
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|x1
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|y0
operator|+=
name|diff_y
expr_stmt|;
operator|*
name|y1
operator|+=
name|diff_y
expr_stmt|;
return|return;
block|}
block|}
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
case|case
name|TRANSFORM_HANDLE_NE
case|:
case|case
name|TRANSFORM_HANDLE_SW
case|:
case|case
name|TRANSFORM_HANDLE_SE
case|:
block|{
name|GimpVector2
name|m
init|=
block|{
operator|.
name|x
operator|=
name|transform_tool
operator|->
name|curx
block|,
operator|.
name|y
operator|=
name|transform_tool
operator|->
name|cury
block|}
decl_stmt|;
name|GimpVector2
name|p
init|=
block|{
operator|.
name|x
operator|=
name|transform_tool
operator|->
name|mousex
block|,
operator|.
name|y
operator|=
name|transform_tool
operator|->
name|mousey
block|}
decl_stmt|;
name|GimpVector2
name|c
init|=
block|{
operator|.
name|x
operator|=
operator|*
name|pivot_x
block|,
operator|.
name|y
operator|=
operator|*
name|pivot_y
block|}
decl_stmt|;
name|gdouble
name|angle
init|=
name|calcangle
argument_list|(
name|vectorsubtract
argument_list|(
name|m
argument_list|,
name|c
argument_list|)
argument_list|,
name|vectorsubtract
argument_list|(
name|p
argument_list|,
name|c
argument_list|)
argument_list|)
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
name|p
operator|.
name|x
operator|=
name|px
index|[
name|i
index|]
expr_stmt|;
name|p
operator|.
name|y
operator|=
name|py
index|[
name|i
index|]
expr_stmt|;
name|m
operator|=
name|vectoradd
argument_list|(
name|c
argument_list|,
name|rotate2d
argument_list|(
name|vectorsubtract
argument_list|(
name|p
argument_list|,
name|c
argument_list|)
argument_list|,
name|angle
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|x
index|[
name|i
index|]
operator|=
name|m
operator|.
name|x
expr_stmt|;
operator|*
name|y
index|[
name|i
index|]
operator|=
name|m
operator|.
name|y
expr_stmt|;
block|}
return|return;
block|}
case|case
name|TRANSFORM_HANDLE_CENTER
case|:
operator|*
name|x
index|[
literal|0
index|]
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|y
index|[
literal|0
index|]
operator|+=
name|diff_y
expr_stmt|;
operator|*
name|x
index|[
literal|1
index|]
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|y
index|[
literal|1
index|]
operator|+=
name|diff_y
expr_stmt|;
operator|*
name|x
index|[
literal|2
index|]
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|y
index|[
literal|2
index|]
operator|+=
name|diff_y
expr_stmt|;
operator|*
name|x
index|[
literal|3
index|]
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|y
index|[
literal|3
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_PIVOT
case|:
operator|*
name|pivot_x
operator|+=
name|diff_x
expr_stmt|;
operator|*
name|pivot_y
operator|+=
name|diff_y
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_E
case|:
case|case
name|TRANSFORM_HANDLE_W
case|:
name|horizontal
operator|=
name|TRUE
expr_stmt|;
case|case
name|TRANSFORM_HANDLE_N
case|:
case|case
name|TRANSFORM_HANDLE_S
case|:
if|if
condition|(
operator|!
name|options
operator|->
name|constrain
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|horizontal
condition|)
operator|*
name|x
index|[
name|i
index|]
operator|=
operator|*
name|pivot_x
operator|+
operator|(
operator|*
name|pivot_x
operator|-
name|transform_tool
operator|->
name|curx
operator|)
operator|/
operator|(
operator|*
name|pivot_x
operator|-
name|transform_tool
operator|->
name|mousex
operator|)
operator|*
operator|(
name|px
index|[
name|i
index|]
operator|-
operator|*
name|pivot_x
operator|)
expr_stmt|;
else|else
operator|*
name|y
index|[
name|i
index|]
operator|=
operator|*
name|pivot_y
operator|+
operator|(
operator|*
name|pivot_y
operator|-
name|transform_tool
operator|->
name|cury
operator|)
operator|/
operator|(
operator|*
name|pivot_y
operator|-
name|transform_tool
operator|->
name|mousey
operator|)
operator|*
operator|(
name|py
index|[
name|i
index|]
operator|-
operator|*
name|pivot_y
operator|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|GimpVector2
name|m
init|=
block|{
operator|.
name|x
operator|=
name|transform_tool
operator|->
name|curx
block|,
operator|.
name|y
operator|=
name|transform_tool
operator|->
name|cury
block|}
decl_stmt|;
name|GimpVector2
name|p
init|=
block|{
operator|.
name|x
operator|=
name|transform_tool
operator|->
name|mousex
block|,
operator|.
name|y
operator|=
name|transform_tool
operator|->
name|mousey
block|}
decl_stmt|;
name|GimpVector2
name|c
init|=
block|{
operator|.
name|x
operator|=
operator|*
name|pivot_x
block|,
operator|.
name|y
operator|=
operator|*
name|pivot_y
block|}
decl_stmt|;
name|gdouble
name|onorm
init|=
literal|1.
operator|/
name|norm
argument_list|(
name|vectorsubtract
argument_list|(
name|c
argument_list|,
name|p
argument_list|)
argument_list|)
decl_stmt|;
name|gdouble
name|distance
init|=
name|norm
argument_list|(
name|vectorsubtract
argument_list|(
name|c
argument_list|,
name|m
argument_list|)
argument_list|)
operator|*
name|onorm
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
name|p
operator|.
name|x
operator|=
name|px
index|[
name|i
index|]
expr_stmt|;
name|p
operator|.
name|y
operator|=
name|py
index|[
name|i
index|]
expr_stmt|;
name|m
operator|=
name|vectoradd
argument_list|(
name|c
argument_list|,
name|scalemult
argument_list|(
name|vectorsubtract
argument_list|(
name|p
argument_list|,
name|c
argument_list|)
argument_list|,
name|distance
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|x
index|[
name|i
index|]
operator|=
name|m
operator|.
name|x
expr_stmt|;
operator|*
name|y
index|[
name|i
index|]
operator|=
name|m
operator|.
name|y
expr_stmt|;
block|}
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unified_transform_tool_recalc_matrix (GimpTransformTool * tr_tool)
name|gimp_unified_transform_tool_recalc_matrix
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|tr_tool
operator|->
name|px
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
expr_stmt|;
name|tr_tool
operator|->
name|py
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
expr_stmt|;
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

end_unit

