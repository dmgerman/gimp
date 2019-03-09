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
file|<gdk/gdkkeysyms.h>
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
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"display/gimptoolgui.h"
end_include

begin_include
include|#
directive|include
file|"display/gimptoolrotategrid.h"
end_include

begin_include
include|#
directive|include
file|"gimprotatetool.h"
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
DECL|enum|__anon27e5ef320103
block|{
DECL|enumerator|ANGLE
name|ANGLE
block|,
DECL|enumerator|PIVOT_X
name|PIVOT_X
block|,
DECL|enumerator|PIVOT_Y
name|PIVOT_Y
block|}
enum|;
end_enum

begin_define
DECL|macro|SB_WIDTH
define|#
directive|define
name|SB_WIDTH
value|10
end_define

begin_define
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|1e-6
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_rotate_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_rotate_tool_info_to_matrix
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|,
name|GimpMatrix3
modifier|*
name|transform
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rotate_tool_matrix_to_info
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|transform
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_rotate_tool_get_undo_desc
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
name|gimp_rotate_tool_dialog
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
name|gimp_rotate_tool_dialog_update
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
name|gimp_rotate_tool_prepare
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
name|gimp_rotate_tool_readjust
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
name|gimp_rotate_tool_get_widget
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
name|gimp_rotate_tool_update_widget
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
name|gimp_rotate_tool_widget_changed
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
name|rotate_angle_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpTransformGridTool
modifier|*
name|tg_tool
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
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpRotateTool,gimp_rotate_tool,GIMP_TYPE_TRANSFORM_GRID_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpRotateTool
argument_list|,
argument|gimp_rotate_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_GRID_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_rotate_tool_parent_class
end_define

begin_function
name|void
name|gimp_rotate_tool_register
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
name|GIMP_TYPE_ROTATE_TOOL
argument_list|,
name|GIMP_TYPE_TRANSFORM_GRID_OPTIONS
argument_list|,
name|gimp_transform_grid_options_gui
argument_list|,
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
argument_list|,
literal|"gimp-rotate-tool"
argument_list|,
name|_
argument_list|(
literal|"Rotate"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Rotate Tool: Rotate the layer, selection or path"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Rotate"
argument_list|)
argument_list|,
literal|"<shift>R"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_ROTATE
argument_list|,
name|GIMP_ICON_TOOL_ROTATE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_class_init (GimpRotateToolClass * klass)
name|gimp_rotate_tool_class_init
parameter_list|(
name|GimpRotateToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
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
name|tool_class
operator|->
name|key_press
operator|=
name|gimp_rotate_tool_key_press
expr_stmt|;
name|tg_class
operator|->
name|info_to_matrix
operator|=
name|gimp_rotate_tool_info_to_matrix
expr_stmt|;
name|tg_class
operator|->
name|matrix_to_info
operator|=
name|gimp_rotate_tool_matrix_to_info
expr_stmt|;
name|tg_class
operator|->
name|get_undo_desc
operator|=
name|gimp_rotate_tool_get_undo_desc
expr_stmt|;
name|tg_class
operator|->
name|dialog
operator|=
name|gimp_rotate_tool_dialog
expr_stmt|;
name|tg_class
operator|->
name|dialog_update
operator|=
name|gimp_rotate_tool_dialog_update
expr_stmt|;
name|tg_class
operator|->
name|prepare
operator|=
name|gimp_rotate_tool_prepare
expr_stmt|;
name|tg_class
operator|->
name|readjust
operator|=
name|gimp_rotate_tool_readjust
expr_stmt|;
name|tg_class
operator|->
name|get_widget
operator|=
name|gimp_rotate_tool_get_widget
expr_stmt|;
name|tg_class
operator|->
name|update_widget
operator|=
name|gimp_rotate_tool_update_widget
expr_stmt|;
name|tg_class
operator|->
name|widget_changed
operator|=
name|gimp_rotate_tool_widget_changed
expr_stmt|;
name|tr_class
operator|->
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Rotate"
argument_list|)
expr_stmt|;
name|tr_class
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Rotating"
argument_list|)
expr_stmt|;
name|tg_class
operator|->
name|ok_button_label
operator|=
name|_
argument_list|(
literal|"R_otate"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_init (GimpRotateTool * rotate_tool)
name|gimp_rotate_tool_init
parameter_list|(
name|GimpRotateTool
modifier|*
name|rotate_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|rotate_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_ROTATE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rotate_tool_key_press (GimpTool * tool,GdkEventKey * kevent,GimpDisplay * display)
name|gimp_rotate_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|==
name|draw_tool
operator|->
name|display
condition|)
block|{
name|GimpRotateTool
modifier|*
name|rotate
init|=
name|GIMP_ROTATE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GtkSpinButton
modifier|*
name|angle_spin
init|=
name|GTK_SPIN_BUTTON
argument_list|(
name|rotate
operator|->
name|angle_spin_button
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_KEY_Up
case|:
name|gtk_spin_button_spin
argument_list|(
name|angle_spin
argument_list|,
name|GTK_SPIN_STEP_FORWARD
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
case|case
name|GDK_KEY_Down
case|:
name|gtk_spin_button_spin
argument_list|(
name|angle_spin
argument_list|,
name|GTK_SPIN_STEP_BACKWARD
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
case|case
name|GDK_KEY_Right
case|:
name|gtk_spin_button_spin
argument_list|(
name|angle_spin
argument_list|,
name|GTK_SPIN_PAGE_FORWARD
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
case|case
name|GDK_KEY_Left
case|:
name|gtk_spin_button_spin
argument_list|(
name|angle_spin
argument_list|,
name|GTK_SPIN_PAGE_BACKWARD
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
default|default:
break|break;
block|}
block|}
return|return
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|key_press
argument_list|(
name|tool
argument_list|,
name|kevent
argument_list|,
name|display
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rotate_tool_info_to_matrix (GimpTransformGridTool * tg_tool,GimpMatrix3 * transform)
name|gimp_rotate_tool_info_to_matrix
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|,
name|GimpMatrix3
modifier|*
name|transform
parameter_list|)
block|{
name|gimp_matrix3_identity
argument_list|(
name|transform
argument_list|)
expr_stmt|;
name|gimp_transform_matrix_rotate_center
argument_list|(
name|transform
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_matrix_to_info (GimpTransformGridTool * tg_tool,const GimpMatrix3 * transform)
name|gimp_rotate_tool_matrix_to_info
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|transform
parameter_list|)
block|{
name|gdouble
name|c
decl_stmt|;
name|gdouble
name|s
decl_stmt|;
name|gdouble
name|x
decl_stmt|;
name|gdouble
name|y
decl_stmt|;
name|gdouble
name|q
decl_stmt|;
name|c
operator|=
name|transform
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
expr_stmt|;
name|s
operator|=
name|transform
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
expr_stmt|;
name|x
operator|=
name|transform
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
expr_stmt|;
name|y
operator|=
name|transform
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|atan2
argument_list|(
name|s
argument_list|,
name|c
argument_list|)
expr_stmt|;
name|q
operator|=
literal|2.0
operator|*
operator|(
literal|1.0
operator|-
name|transform
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|)
expr_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|q
argument_list|)
operator|>
name|EPSILON
condition|)
block|{
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
operator|=
operator|(
operator|(
literal|1.0
operator|-
name|c
operator|)
operator|*
name|x
operator|-
name|s
operator|*
name|y
operator|)
operator|/
name|q
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
operator|=
operator|(
name|s
operator|*
name|x
operator|+
operator|(
literal|1.0
operator|-
name|c
operator|)
operator|*
name|y
operator|)
operator|/
name|q
expr_stmt|;
block|}
else|else
block|{
name|GimpMatrix3
name|transfer
decl_stmt|;
name|gimp_transform_grid_tool_info_to_matrix
argument_list|(
name|tg_tool
argument_list|,
operator|&
name|transfer
argument_list|)
expr_stmt|;
name|gimp_matrix3_invert
argument_list|(
operator|&
name|transfer
argument_list|)
expr_stmt|;
name|gimp_matrix3_mult
argument_list|(
name|transform
argument_list|,
operator|&
name|transfer
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|transfer
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
argument_list|,
operator|&
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|,
operator|&
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_rotate_tool_get_undo_desc (GimpTransformGridTool * tg_tool)
name|gimp_rotate_tool_get_undo_desc
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
name|gdouble
name|center_x
decl_stmt|;
name|gdouble
name|center_y
decl_stmt|;
name|center_x
operator|=
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
expr_stmt|;
name|center_y
operator|=
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
expr_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
operator|-
name|center_x
argument_list|)
operator|<=
name|EPSILON
operator|&&
name|fabs
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
operator|-
name|center_y
argument_list|)
operator|<=
name|EPSILON
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Rotate by %-3.3gÂ°"
argument_list|)
argument_list|,
name|gimp_rad_to_deg
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
argument_list|)
return|;
block|}
else|else
block|{
return|return
name|g_strdup_printf
argument_list|(
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Rotate by %-3.3gÂ° around (%g, %g)"
argument_list|)
argument_list|,
name|gimp_rad_to_deg
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
argument_list|)
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_dialog (GimpTransformGridTool * tg_tool)
name|gimp_rotate_tool_dialog
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|GimpRotateTool
modifier|*
name|rotate
init|=
name|GIMP_ROTATE_TOOL
argument_list|(
name|tg_tool
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|grid
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|grid
operator|=
name|gtk_grid_new
argument_list|()
expr_stmt|;
name|gtk_grid_set_row_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_grid_set_column_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|6
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
name|grid
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
name|grid
argument_list|)
expr_stmt|;
name|rotate
operator|->
name|angle_adj
operator|=
name|gtk_adjustment_new
argument_list|(
literal|0
argument_list|,
operator|-
literal|180
argument_list|,
literal|180
argument_list|,
literal|0.1
argument_list|,
literal|15
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_spin_button_new
argument_list|(
name|rotate
operator|->
name|angle_adj
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_wrap
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|button
argument_list|)
argument_list|,
name|SB_WIDTH
argument_list|)
expr_stmt|;
name|gtk_widget_set_halign
argument_list|(
name|button
argument_list|,
name|GTK_ALIGN_START
argument_list|)
expr_stmt|;
name|gimp_grid_attach_aligned
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Angle:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|button
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|rotate
operator|->
name|angle_spin_button
operator|=
name|button
expr_stmt|;
name|g_signal_connect
argument_list|(
name|rotate
operator|->
name|angle_adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|rotate_angle_changed
argument_list|)
argument_list|,
name|tg_tool
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_scale_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
name|rotate
operator|->
name|angle_adj
argument_list|)
expr_stmt|;
name|gtk_scale_set_draw_value
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_hexpand
argument_list|(
name|scale
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|scale
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gtk_adjustment_new
argument_list|(
literal|0
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
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_spin_button_new
argument_list|(
name|adj
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|button
argument_list|)
argument_list|,
name|SB_WIDTH
argument_list|)
expr_stmt|;
name|gtk_widget_set_halign
argument_list|(
name|button
argument_list|,
name|GTK_ALIGN_START
argument_list|)
expr_stmt|;
name|gimp_grid_attach_aligned
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"Center _X:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|button
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|rotate
operator|->
name|sizeentry
operator|=
name|gimp_size_entry_new
argument_list|(
literal|1
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|"%a"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|SB_WIDTH
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|)
expr_stmt|;
name|gimp_size_entry_add_field
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|)
argument_list|,
name|GTK_SPIN_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_pixel_digits
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_set_halign
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|,
name|GTK_ALIGN_START
argument_list|)
expr_stmt|;
name|gimp_grid_attach_aligned
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
name|_
argument_list|(
literal|"Center _Y:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|rotate
operator|->
name|sizeentry
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|rotate_center_changed
argument_list|)
argument_list|,
name|tg_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_dialog_update (GimpTransformGridTool * tg_tool)
name|gimp_rotate_tool_dialog_update
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|GimpRotateTool
modifier|*
name|rotate
init|=
name|GIMP_ROTATE_TOOL
argument_list|(
name|tg_tool
argument_list|)
decl_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|rotate
operator|->
name|angle_adj
argument_list|,
name|gimp_rad_to_deg
argument_list|(
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|,
name|rotate_center_changed
argument_list|,
name|tg_tool
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|,
name|rotate_center_changed
argument_list|,
name|tg_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_prepare (GimpTransformGridTool * tg_tool)
name|gimp_rotate_tool_prepare
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
name|GimpRotateTool
modifier|*
name|rotate
init|=
name|GIMP_ROTATE_TOOL
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
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
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
name|ANGLE
index|]
operator|=
literal|0.0
expr_stmt|;
name|tg_tool
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
name|tg_tool
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
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|,
name|rotate_center_changed
argument_list|,
name|tg_tool
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|)
argument_list|,
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
operator|->
name|unit
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|xres
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|yres
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
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
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
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
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|tr_tool
operator|->
name|x1
argument_list|,
name|tr_tool
operator|->
name|x2
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|tr_tool
operator|->
name|y1
argument_list|,
name|tr_tool
operator|->
name|y2
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|rotate
operator|->
name|sizeentry
argument_list|,
name|rotate_center_changed
argument_list|,
name|tg_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_readjust (GimpTransformGridTool * tg_tool)
name|gimp_rotate_tool_readjust
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
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
operator|-
name|gimp_deg_to_rad
argument_list|(
name|shell
operator|->
name|rotate_angle
argument_list|)
expr_stmt|;
if|if
condition|(
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|<=
operator|-
name|G_PI
condition|)
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|+=
literal|2.0
operator|*
name|G_PI
expr_stmt|;
name|gimp_display_shell_untransform_xy_f
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|disp_width
operator|/
literal|2.0
argument_list|,
name|shell
operator|->
name|disp_height
operator|/
literal|2.0
argument_list|,
operator|&
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|,
operator|&
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpToolWidget
modifier|*
DECL|function|gimp_rotate_tool_get_widget (GimpTransformGridTool * tg_tool)
name|gimp_rotate_tool_get_widget
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
name|gimp_tool_rotate_grid_new
argument_list|(
name|shell
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
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|widget
argument_list|,
literal|"inside-function"
argument_list|,
name|GIMP_TRANSFORM_FUNCTION_ROTATE
argument_list|,
literal|"outside-function"
argument_list|,
name|GIMP_TRANSFORM_FUNCTION_ROTATE
argument_list|,
literal|"use-pivot-handle"
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
DECL|function|gimp_rotate_tool_update_widget (GimpTransformGridTool * tg_tool)
name|gimp_rotate_tool_update_widget
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|GIMP_TRANSFORM_GRID_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|update_widget
argument_list|(
name|tg_tool
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|tg_tool
operator|->
name|widget
argument_list|,
literal|"angle"
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|,
literal|"pivot-x"
argument_list|,
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|,
literal|"pivot-y"
argument_list|,
name|tg_tool
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
name|void
DECL|function|gimp_rotate_tool_widget_changed (GimpTransformGridTool * tg_tool)
name|gimp_rotate_tool_widget_changed
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|g_object_get
argument_list|(
name|tg_tool
operator|->
name|widget
argument_list|,
literal|"angle"
argument_list|,
operator|&
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|,
literal|"pivot-x"
argument_list|,
operator|&
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
argument_list|,
literal|"pivot-y"
argument_list|,
operator|&
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
argument_list|,
name|NULL
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
DECL|function|rotate_angle_changed (GtkAdjustment * adj,GimpTransformGridTool * tg_tool)
name|rotate_angle_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|gdouble
name|value
init|=
name|gimp_deg_to_rad
argument_list|(
name|gtk_adjustment_get_value
argument_list|(
name|adj
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|value
operator|-
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
operator|>
name|EPSILON
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
name|tg_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|value
expr_stmt|;
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
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_center_changed (GtkWidget * widget,GimpTransformGridTool * tg_tool)
name|rotate_center_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
block|{
name|gdouble
name|px
init|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|)
decl_stmt|;
name|gdouble
name|py
init|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|1
argument_list|)
decl_stmt|;
if|if
condition|(
operator|(
name|px
operator|!=
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
operator|)
operator|||
operator|(
name|py
operator|!=
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
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
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_X
index|]
operator|=
name|px
expr_stmt|;
name|tg_tool
operator|->
name|trans_info
index|[
name|PIVOT_Y
index|]
operator|=
name|py
expr_stmt|;
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
end_function

end_unit

