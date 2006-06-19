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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
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
name|gimp_scale_tool_dialog
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
name|gimp_scale_tool_dialog_update
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
name|gimp_scale_tool_prepare
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_scale_tool_motion
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_scale_tool_recalc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
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
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpScaleTool,gimp_scale_tool,GIMP_TYPE_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpScaleTool
argument_list|,
argument|gimp_scale_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_TOOL
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
name|GIMP_TYPE_TRANSFORM_OPTIONS
argument_list|,
name|gimp_transform_options_gui
argument_list|,
literal|0
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
literal|"Scale the layer or selection"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Scale"
argument_list|)
argument_list|,
literal|"<shift>T"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_SCALE
argument_list|,
name|GIMP_STOCK_TOOL_SCALE
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
name|gimp_scale_tool_dialog
expr_stmt|;
name|trans_class
operator|->
name|dialog_update
operator|=
name|gimp_scale_tool_dialog_update
expr_stmt|;
name|trans_class
operator|->
name|prepare
operator|=
name|gimp_scale_tool_prepare
expr_stmt|;
name|trans_class
operator|->
name|motion
operator|=
name|gimp_scale_tool_motion
expr_stmt|;
name|trans_class
operator|->
name|recalc
operator|=
name|gimp_scale_tool_recalc
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
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
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
name|tr_tool
operator|->
name|shell_desc
operator|=
name|_
argument_list|(
literal|"Scaling Information"
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Scaling"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_dialog (GimpTransformTool * tr_tool)
name|gimp_scale_tool_dialog
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_dialog_update (GimpTransformTool * tr_tool)
name|gimp_scale_tool_dialog_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpTransformOptions
modifier|*
name|options
decl_stmt|;
name|gint
name|width
init|=
name|ROUND
argument_list|(
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|-
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|ROUND
argument_list|(
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|-
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|)
decl_stmt|;
name|options
operator|=
name|GIMP_TRANSFORM_OPTIONS
argument_list|(
name|GIMP_TOOL
argument_list|(
name|tr_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_SCALE_TOOL
argument_list|(
name|tr_tool
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
name|constrain
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_prepare (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_scale_tool_prepare
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpScaleTool
modifier|*
name|scale
init|=
name|GIMP_SCALE_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GimpTransformOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_TRANSFORM_OPTIONS
argument_list|(
name|GIMP_TOOL
argument_list|(
name|scale
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
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
name|y2
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
name|tr_tool
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
name|constrain
argument_list|,
literal|"unit"
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
operator|->
name|unit
argument_list|,
literal|"xresolution"
argument_list|,
name|display
operator|->
name|image
operator|->
name|xresolution
argument_list|,
literal|"yresolution"
argument_list|,
name|display
operator|->
name|image
operator|->
name|yresolution
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scale
operator|->
name|box
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|tr_tool
operator|->
name|dialog
argument_list|)
operator|->
name|vbox
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
name|tr_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_motion (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_scale_tool_motion
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTransformOptions
modifier|*
name|options
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
name|dir_x
decl_stmt|;
name|gint
name|dir_y
decl_stmt|;
name|gdouble
name|diff_x
init|=
name|tr_tool
operator|->
name|curx
operator|-
name|tr_tool
operator|->
name|lastx
decl_stmt|;
name|gdouble
name|diff_y
init|=
name|tr_tool
operator|->
name|cury
operator|-
name|tr_tool
operator|->
name|lasty
decl_stmt|;
switch|switch
condition|(
name|tr_tool
operator|->
name|function
condition|)
block|{
case|case
name|TRANSFORM_HANDLE_NW
case|:
name|x1
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y1
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
expr_stmt|;
name|x2
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y2
operator|=
operator|&
name|tr_tool
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
name|TRANSFORM_HANDLE_NE
case|:
name|x1
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y1
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
expr_stmt|;
name|x2
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y2
operator|=
operator|&
name|tr_tool
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
name|TRANSFORM_HANDLE_SW
case|:
name|x1
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y1
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
expr_stmt|;
name|x2
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y2
operator|=
operator|&
name|tr_tool
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
name|TRANSFORM_HANDLE_SE
case|:
name|x1
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y1
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
expr_stmt|;
name|x2
operator|=
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y2
operator|=
operator|&
name|tr_tool
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
case|case
name|TRANSFORM_HANDLE_CENTER
case|:
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+=
name|diff_x
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|+=
name|diff_y
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|+=
name|diff_x
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|+=
name|diff_y
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X2
index|]
operator|+=
name|diff_x
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
operator|+=
name|diff_y
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X3
index|]
operator|+=
name|diff_x
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|+=
name|diff_y
expr_stmt|;
return|return;
default|default:
return|return;
block|}
comment|/*  if control is being held, constrain the aspect ratio  */
name|options
operator|=
name|GIMP_TRANSFORM_OPTIONS
argument_list|(
name|GIMP_TOOL
argument_list|(
name|tr_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|constrain
condition|)
block|{
name|gdouble
name|mag
decl_stmt|;
name|gdouble
name|dot
decl_stmt|;
name|mag
operator|=
name|hypot
argument_list|(
call|(
name|gdouble
call|)
argument_list|(
name|tr_tool
operator|->
name|x2
operator|-
name|tr_tool
operator|->
name|x1
argument_list|)
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|tr_tool
operator|->
name|y2
operator|-
name|tr_tool
operator|->
name|y1
argument_list|)
argument_list|)
expr_stmt|;
name|dot
operator|=
operator|(
name|dir_x
operator|*
name|diff_x
operator|*
operator|(
name|tr_tool
operator|->
name|x2
operator|-
name|tr_tool
operator|->
name|x1
operator|)
operator|+
name|dir_y
operator|*
name|diff_y
operator|*
operator|(
name|tr_tool
operator|->
name|y2
operator|-
name|tr_tool
operator|->
name|y1
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|mag
operator|>
literal|0.0
condition|)
block|{
name|diff_x
operator|=
name|dir_x
operator|*
operator|(
name|tr_tool
operator|->
name|x2
operator|-
name|tr_tool
operator|->
name|x1
operator|)
operator|*
name|dot
operator|/
operator|(
name|mag
operator|*
name|mag
operator|)
expr_stmt|;
name|diff_y
operator|=
name|dir_y
operator|*
operator|(
name|tr_tool
operator|->
name|y2
operator|-
name|tr_tool
operator|->
name|y1
operator|)
operator|*
name|dot
operator|/
operator|(
name|mag
operator|*
name|mag
operator|)
expr_stmt|;
block|}
else|else
block|{
name|diff_x
operator|=
name|diff_y
operator|=
literal|0
expr_stmt|;
block|}
block|}
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_recalc (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_scale_tool_recalc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
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
operator|-
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
name|Y1
index|]
operator|-
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_size_notify (GtkWidget * box,GParamSpec * pspec,GimpTransformTool * tr_tool)
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
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpTransformOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_TRANSFORM_OPTIONS
argument_list|(
name|GIMP_TOOL
argument_list|(
name|tr_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
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
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|-
name|tr_tool
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
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|-
name|tr_tool
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
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tr_tool
argument_list|)
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+
name|width
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|+
name|height
expr_stmt|;
name|gimp_transform_tool_recalc
argument_list|(
name|tr_tool
argument_list|,
name|GIMP_TOOL
argument_list|(
name|tr_tool
argument_list|)
operator|->
name|display
argument_list|)
expr_stmt|;
name|gimp_transform_tool_expose_preview
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tr_tool
argument_list|)
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
name|constrain
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"constrain"
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

