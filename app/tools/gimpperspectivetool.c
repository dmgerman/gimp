begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimptransformgridoptions.h"
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
DECL|enum|__anon29099c430103
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
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_prepare
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpToolWidget
modifier|*
name|gimp_perspective_tool_get_widget
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_update_widget
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_widget_changed
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_recalc_points
parameter_list|(
name|GimpGenericTransformTool
modifier|*
name|generic
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPerspectiveTool,gimp_perspective_tool,GIMP_TYPE_GENERIC_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPerspectiveTool
argument_list|,
argument|gimp_perspective_tool
argument_list|,
argument|GIMP_TYPE_GENERIC_TRANSFORM_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_perspective_tool_parent_class
end_define

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
name|GIMP_TYPE_TRANSFORM_GRID_OPTIONS
argument_list|,
name|gimp_transform_grid_options_gui
argument_list|,
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
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
name|GIMP_ICON_TOOL_PERSPECTIVE
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
name|tr_class
init|=
name|GIMP_TRANSFORM_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpTransformGridToolClass
modifier|*
name|tg_class
init|=
name|GIMP_TRANSFORM_GRID_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpGenericTransformToolClass
modifier|*
name|generic_class
init|=
name|GIMP_GENERIC_TRANSFORM_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tg_class
operator|->
name|prepare
operator|=
name|gimp_perspective_tool_prepare
expr_stmt|;
name|tg_class
operator|->
name|get_widget
operator|=
name|gimp_perspective_tool_get_widget
expr_stmt|;
name|tg_class
operator|->
name|update_widget
operator|=
name|gimp_perspective_tool_update_widget
expr_stmt|;
name|tg_class
operator|->
name|widget_changed
operator|=
name|gimp_perspective_tool_widget_changed
expr_stmt|;
name|generic_class
operator|->
name|recalc_points
operator|=
name|gimp_perspective_tool_recalc_points
expr_stmt|;
name|tr_class
operator|->
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Perspective"
argument_list|)
expr_stmt|;
name|tr_class
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Perspective transformation"
argument_list|)
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
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_PERSPECTIVE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_prepare (GimpTransformGridTool * tg_tool)
name|gimp_perspective_tool_prepare
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|tg_tool
argument_list|)
decl_stmt|;
name|GIMP_TRANSFORM_GRID_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|prepare
argument_list|(
name|tg_tool
argument_list|)
expr_stmt|;
name|tg_tool
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
name|tg_tool
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
name|tg_tool
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
name|tg_tool
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
name|tg_tool
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
name|tg_tool
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
name|tg_tool
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
name|tg_tool
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
DECL|function|gimp_perspective_tool_get_widget (GimpTransformGridTool * tg_tool)
name|gimp_perspective_tool_get_widget
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|tg_tool
argument_list|)
decl_stmt|;
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|tg_tool
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
literal|"inside-function"
argument_list|,
name|GIMP_TRANSFORM_FUNCTION_PERSPECTIVE
argument_list|,
literal|"outside-function"
argument_list|,
name|GIMP_TRANSFORM_FUNCTION_PERSPECTIVE
argument_list|,
literal|"use-perspective-handles"
argument_list|,
name|TRUE
argument_list|,
literal|"use-center-handle"
argument_list|,
name|TRUE
argument_list|,
name|NULL
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
DECL|function|gimp_perspective_tool_update_widget (GimpTransformGridTool * tg_tool)
name|gimp_perspective_tool_update_widget
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|tg_tool
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|tg_tool
operator|->
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
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_widget_changed (GimpTransformGridTool * tg_tool)
name|gimp_perspective_tool_widget_changed
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|tg_tool
argument_list|)
decl_stmt|;
name|GimpMatrix3
modifier|*
name|transform
decl_stmt|;
name|g_object_get
argument_list|(
name|tg_tool
operator|->
name|widget
argument_list|,
literal|"transform"
argument_list|,
operator|&
name|transform
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
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|,
operator|&
name|tg_tool
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
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
argument_list|,
operator|&
name|tg_tool
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
name|tg_tool
operator|->
name|trans_info
index|[
name|X2
index|]
argument_list|,
operator|&
name|tg_tool
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
name|tg_tool
operator|->
name|trans_info
index|[
name|X3
index|]
argument_list|,
operator|&
name|tg_tool
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
name|GIMP_TRANSFORM_GRID_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|widget_changed
argument_list|(
name|tg_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_recalc_points (GimpGenericTransformTool * generic)
name|gimp_perspective_tool_recalc_points
parameter_list|(
name|GimpGenericTransformTool
modifier|*
name|generic
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|generic
argument_list|)
decl_stmt|;
name|GimpTransformGridTool
modifier|*
name|tg_tool
init|=
name|GIMP_TRANSFORM_GRID_TOOL
argument_list|(
name|generic
argument_list|)
decl_stmt|;
name|generic
operator|->
name|input_points
index|[
literal|0
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|tr_tool
operator|->
name|x1
block|,
name|tr_tool
operator|->
name|y1
block|}
expr_stmt|;
name|generic
operator|->
name|input_points
index|[
literal|1
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|tr_tool
operator|->
name|x2
block|,
name|tr_tool
operator|->
name|y1
block|}
expr_stmt|;
name|generic
operator|->
name|input_points
index|[
literal|2
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|tr_tool
operator|->
name|x1
block|,
name|tr_tool
operator|->
name|y2
block|}
expr_stmt|;
name|generic
operator|->
name|input_points
index|[
literal|3
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|tr_tool
operator|->
name|x2
block|,
name|tr_tool
operator|->
name|y2
block|}
expr_stmt|;
name|generic
operator|->
name|output_points
index|[
literal|0
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
block|,
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
block|}
expr_stmt|;
name|generic
operator|->
name|output_points
index|[
literal|1
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
block|,
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
block|}
expr_stmt|;
name|generic
operator|->
name|output_points
index|[
literal|2
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|X2
index|]
block|,
name|tg_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
block|}
expr_stmt|;
name|generic
operator|->
name|output_points
index|[
literal|3
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|X3
index|]
block|,
name|tg_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
block|}
expr_stmt|;
block|}
end_function

end_unit

