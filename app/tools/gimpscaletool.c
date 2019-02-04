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
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsizebox.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
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
file|"gimpscaletool.h"
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

begin_define
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|1e-6
end_define

begin_comment
comment|/*  index into trans_info array  */
end_comment

begin_enum
enum|enum
DECL|enum|__anon2c4e361c0103
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
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_scale_tool_recalc_matrix
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
name|gimp_scale_tool_get_undo_desc
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
name|gimp_scale_tool_dialog
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
name|gimp_scale_tool_dialog_update
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
name|gimp_scale_tool_prepare
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
name|gimp_scale_tool_get_widget
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
name|gimp_scale_tool_update_widget
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
name|gimp_scale_tool_widget_changed
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
name|gimp_scale_tool_size_notify
parameter_list|(
name|GtkWidget
modifier|*
name|box
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpScaleTool,gimp_scale_tool,GIMP_TYPE_TRANSFORM_GRID_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpScaleTool
argument_list|,
argument|gimp_scale_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_GRID_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_scale_tool_parent_class
end_define

begin_function
name|void
name|gimp_scale_tool_register
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
name|GIMP_TYPE_SCALE_TOOL
argument_list|,
name|GIMP_TYPE_TRANSFORM_GRID_OPTIONS
argument_list|,
name|gimp_transform_grid_options_gui
argument_list|,
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
argument_list|,
literal|"gimp-scale-tool"
argument_list|,
name|_
argument_list|(
literal|"Scale"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Scale Tool: Scale the layer, selection or path"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Scale"
argument_list|)
argument_list|,
literal|"<shift>S"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_SCALE
argument_list|,
name|GIMP_ICON_TOOL_SCALE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_class_init (GimpScaleToolClass * klass)
name|gimp_scale_tool_class_init
parameter_list|(
name|GimpScaleToolClass
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
name|tr_class
operator|->
name|recalc_matrix
operator|=
name|gimp_scale_tool_recalc_matrix
expr_stmt|;
name|tr_class
operator|->
name|get_undo_desc
operator|=
name|gimp_scale_tool_get_undo_desc
expr_stmt|;
name|tg_class
operator|->
name|dialog
operator|=
name|gimp_scale_tool_dialog
expr_stmt|;
name|tg_class
operator|->
name|dialog_update
operator|=
name|gimp_scale_tool_dialog_update
expr_stmt|;
name|tg_class
operator|->
name|prepare
operator|=
name|gimp_scale_tool_prepare
expr_stmt|;
name|tg_class
operator|->
name|get_widget
operator|=
name|gimp_scale_tool_get_widget
expr_stmt|;
name|tg_class
operator|->
name|update_widget
operator|=
name|gimp_scale_tool_update_widget
expr_stmt|;
name|tg_class
operator|->
name|widget_changed
operator|=
name|gimp_scale_tool_widget_changed
expr_stmt|;
name|tr_class
operator|->
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Scale"
argument_list|)
expr_stmt|;
name|tr_class
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Scaling"
argument_list|)
expr_stmt|;
name|tg_class
operator|->
name|ok_button_label
operator|=
name|_
argument_list|(
literal|"_Scale"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_init (GimpScaleTool * scale_tool)
name|gimp_scale_tool_init
parameter_list|(
name|GimpScaleTool
modifier|*
name|scale_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|scale_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_RESIZE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_recalc_matrix (GimpTransformTool * tr_tool)
name|gimp_scale_tool_recalc_matrix
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpTransformGridTool
modifier|*
name|tg_tool
init|=
name|GIMP_TRANSFORM_GRID_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|gimp_matrix3_identity
argument_list|(
operator|&
name|tr_tool
operator|->
name|transform
argument_list|)
expr_stmt|;
name|gimp_transform_matrix_scale
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
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|)
expr_stmt|;
name|GIMP_TRANSFORM_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|recalc_matrix
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_scale_tool_get_undo_desc (GimpTransformTool * tr_tool)
name|gimp_scale_tool_get_undo_desc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpTransformGridTool
modifier|*
name|tg_tool
init|=
name|GIMP_TRANSFORM_GRID_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|width
operator|=
name|ROUND
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|)
expr_stmt|;
name|height
operator|=
name|ROUND
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|)
expr_stmt|;
return|return
name|g_strdup_printf
argument_list|(
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Scale to %d x %d"
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_dialog (GimpTransformGridTool * tg_tool)
name|gimp_scale_tool_dialog
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_dialog_update (GimpTransformGridTool * tg_tool)
name|gimp_scale_tool_dialog_update
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|GimpTransformGridOptions
modifier|*
name|options
init|=
name|GIMP_TRANSFORM_GRID_TOOL_GET_OPTIONS
argument_list|(
name|tg_tool
argument_list|)
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|width
operator|=
name|ROUND
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|)
expr_stmt|;
name|height
operator|=
name|ROUND
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_SCALE_TOOL
argument_list|(
name|tg_tool
argument_list|)
operator|->
name|box
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
literal|"keep-aspect"
argument_list|,
name|options
operator|->
name|constrain_scale
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_prepare (GimpTransformGridTool * tg_tool)
name|gimp_scale_tool_prepare
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|GimpScaleTool
modifier|*
name|scale
init|=
name|GIMP_SCALE_TOOL
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
name|GimpTransformGridOptions
modifier|*
name|options
init|=
name|GIMP_TRANSFORM_GRID_TOOL_GET_OPTIONS
argument_list|(
name|tg_tool
argument_list|)
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_TOOL
argument_list|(
name|tg_tool
argument_list|)
operator|->
name|display
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
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
name|y2
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
if|if
condition|(
name|scale
operator|->
name|box
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|scale
operator|->
name|box
argument_list|,
name|gimp_scale_tool_size_notify
argument_list|,
name|tg_tool
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|scale
operator|->
name|box
argument_list|)
expr_stmt|;
block|}
comment|/*  Need to create a new GimpSizeBox widget because the initial    *  width and height is what counts as 100%.    */
name|scale
operator|->
name|box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_SIZE_BOX
argument_list|,
literal|"width"
argument_list|,
name|tr_tool
operator|->
name|x2
operator|-
name|tr_tool
operator|->
name|x1
argument_list|,
literal|"height"
argument_list|,
name|tr_tool
operator|->
name|y2
operator|-
name|tr_tool
operator|->
name|y1
argument_list|,
literal|"keep-aspect"
argument_list|,
name|options
operator|->
name|constrain_scale
argument_list|,
literal|"unit"
argument_list|,
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
operator|->
name|unit
argument_list|,
literal|"xresolution"
argument_list|,
name|xres
argument_list|,
literal|"yresolution"
argument_list|,
name|yres
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gimp_tool_gui_get_vbox
argument_list|(
name|tg_tool
operator|->
name|gui
argument_list|)
argument_list|)
argument_list|,
name|scale
operator|->
name|box
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
name|scale
operator|->
name|box
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|scale
operator|->
name|box
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_scale_tool_size_notify
argument_list|)
argument_list|,
name|tg_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpToolWidget
modifier|*
DECL|function|gimp_scale_tool_get_widget (GimpTransformGridTool * tg_tool)
name|gimp_scale_tool_get_widget
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
name|GIMP_TRANSFORM_FUNCTION_SCALE
argument_list|,
literal|"outside-function"
argument_list|,
name|GIMP_TRANSFORM_FUNCTION_SCALE
argument_list|,
literal|"use-corner-handles"
argument_list|,
name|TRUE
argument_list|,
literal|"use-side-handles"
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
DECL|function|gimp_scale_tool_update_widget (GimpTransformGridTool * tg_tool)
name|gimp_scale_tool_update_widget
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
literal|"pivot-x"
argument_list|,
operator|(
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|)
operator|/
literal|2.0
argument_list|,
literal|"pivot-y"
argument_list|,
operator|(
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|+
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|)
operator|/
literal|2.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_widget_changed (GimpTransformGridTool * tg_tool)
name|gimp_scale_tool_widget_changed
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
name|GimpMatrix3
modifier|*
name|transform
decl_stmt|;
name|gdouble
name|x0
decl_stmt|,
name|y0
decl_stmt|;
name|gdouble
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
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
name|x0
argument_list|,
operator|&
name|y0
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
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|transform
argument_list|)
expr_stmt|;
name|width
operator|=
name|ROUND
argument_list|(
name|x1
operator|-
name|x0
argument_list|)
expr_stmt|;
name|height
operator|=
name|ROUND
argument_list|(
name|y1
operator|-
name|y0
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|>
literal|0
condition|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
name|x0
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
name|x1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|fabs
argument_list|(
name|x0
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|)
operator|<
name|EPSILON
condition|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+
literal|1.0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|fabs
argument_list|(
name|x1
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
argument_list|)
operator|<
name|EPSILON
condition|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|-
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
operator|(
name|x0
operator|+
name|x1
operator|)
operator|/
literal|2.0
operator|-
literal|0.5
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
operator|(
name|x0
operator|+
name|x1
operator|)
operator|/
literal|2.0
operator|+
literal|0.5
expr_stmt|;
block|}
if|if
condition|(
name|height
operator|>
literal|0
condition|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
name|y0
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
name|y1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|fabs
argument_list|(
name|y0
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|)
operator|<
name|EPSILON
condition|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|+
literal|1.0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|fabs
argument_list|(
name|y1
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
argument_list|)
operator|<
name|EPSILON
condition|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|-
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
operator|(
name|y0
operator|+
name|y1
operator|)
operator|/
literal|2.0
operator|-
literal|0.5
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
operator|(
name|y0
operator|+
name|y1
operator|)
operator|/
literal|2.0
operator|+
literal|0.5
expr_stmt|;
block|}
if|if
condition|(
name|width
operator|<=
literal|0
operator|||
name|height
operator|<=
literal|0
condition|)
name|gimp_transform_tool_recalc_matrix
argument_list|(
name|tr_tool
argument_list|,
name|tool
operator|->
name|display
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
DECL|function|gimp_scale_tool_size_notify (GtkWidget * box,GParamSpec * pspec,GimpTransformGridTool * tg_tool)
name|gimp_scale_tool_size_notify
parameter_list|(
name|GtkWidget
modifier|*
name|box
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|GimpTransformGridOptions
modifier|*
name|options
init|=
name|GIMP_TRANSFORM_GRID_TOOL_GET_OPTIONS
argument_list|(
name|tg_tool
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"width"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"height"
argument_list|)
condition|)
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|old_width
decl_stmt|;
name|gint
name|old_height
decl_stmt|;
name|g_object_get
argument_list|(
name|box
argument_list|,
literal|"width"
argument_list|,
operator|&
name|width
argument_list|,
literal|"height"
argument_list|,
operator|&
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|old_width
operator|=
name|ROUND
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|)
expr_stmt|;
name|old_height
operator|=
name|ROUND
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|width
operator|!=
name|old_width
operator|)
operator|||
operator|(
name|height
operator|!=
name|old_height
operator|)
condition|)
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
if|if
condition|(
name|options
operator|->
name|frompivot_scale
condition|)
block|{
name|gdouble
name|center_x
decl_stmt|;
name|gdouble
name|center_y
decl_stmt|;
name|center_x
operator|=
operator|(
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|)
operator|/
literal|2.0
expr_stmt|;
name|center_y
operator|=
operator|(
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|+
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|)
operator|/
literal|2.0
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
name|center_x
operator|-
name|width
operator|/
literal|2.0
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
name|center_y
operator|-
name|height
operator|/
literal|2.0
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
name|center_x
operator|+
name|width
operator|/
literal|2.0
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
name|center_y
operator|+
name|height
operator|/
literal|2.0
expr_stmt|;
block|}
else|else
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
name|tg_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+
name|width
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
name|tg_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|+
name|height
expr_stmt|;
block|}
name|gimp_transform_grid_tool_push_internal_undo
argument_list|(
name|tg_tool
argument_list|)
expr_stmt|;
name|gimp_transform_tool_recalc_matrix
argument_list|(
name|tr_tool
argument_list|,
name|tool
operator|->
name|display
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"keep-aspect"
argument_list|)
condition|)
block|{
name|gboolean
name|constrain
decl_stmt|;
name|g_object_get
argument_list|(
name|box
argument_list|,
literal|"keep-aspect"
argument_list|,
operator|&
name|constrain
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|constrain
operator|!=
name|options
operator|->
name|constrain_scale
condition|)
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|g_object_get
argument_list|(
name|box
argument_list|,
literal|"width"
argument_list|,
operator|&
name|width
argument_list|,
literal|"height"
argument_list|,
operator|&
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"constrain-scale"
argument_list|,
name|constrain
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

