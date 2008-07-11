begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|macro|FIFTEEN_DEG
define|#
directive|define
name|FIFTEEN_DEG
value|(G_PI / 12.0)
end_define

begin_define
DECL|macro|SB_WIDTH
define|#
directive|define
name|SB_WIDTH
value|10
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
name|void
name|gimp_rotate_tool_dialog
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
name|gimp_rotate_tool_dialog_update
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
name|gimp_rotate_tool_prepare
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
name|gimp_rotate_tool_motion
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
name|gimp_rotate_tool_recalc
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
name|rotate_angle_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpTransformTool
modifier|*
name|tr_tool
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
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpRotateTool,gimp_rotate_tool,GIMP_TYPE_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpRotateTool
argument_list|,
argument|gimp_rotate_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_TOOL
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
name|GIMP_TYPE_TRANSFORM_OPTIONS
argument_list|,
name|gimp_transform_options_gui
argument_list|,
literal|0
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
name|GIMP_STOCK_TOOL_ROTATE
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
name|trans_class
init|=
name|GIMP_TRANSFORM_TOOL_CLASS
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
name|trans_class
operator|->
name|dialog
operator|=
name|gimp_rotate_tool_dialog
expr_stmt|;
name|trans_class
operator|->
name|dialog_update
operator|=
name|gimp_rotate_tool_dialog_update
expr_stmt|;
name|trans_class
operator|->
name|prepare
operator|=
name|gimp_rotate_tool_prepare
expr_stmt|;
name|trans_class
operator|->
name|motion
operator|=
name|gimp_rotate_tool_motion
expr_stmt|;
name|trans_class
operator|->
name|recalc
operator|=
name|gimp_rotate_tool_recalc
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
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
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
name|tr_tool
operator|->
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"command"
argument_list|,
literal|"Rotate"
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Rotating"
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
name|use_center
operator|=
name|TRUE
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
name|GDK_Up
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
name|GDK_Down
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
name|GDK_Left
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
name|GDK_Right
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
name|void
DECL|function|gimp_rotate_tool_dialog (GimpTransformTool * tr_tool)
name|gimp_rotate_tool_dialog
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpRotateTool
modifier|*
name|rotate
init|=
name|GIMP_ROTATE_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|4
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|1
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
name|table
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
name|table
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|rotate
operator|->
name|angle_adj
argument_list|,
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
argument_list|,
literal|2
argument_list|,
literal|2
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
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
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
argument_list|,
name|TRUE
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
name|tr_tool
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|rotate
operator|->
name|angle_adj
argument_list|)
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
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|scale
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adj
argument_list|,
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
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
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
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
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
argument_list|,
name|TRUE
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
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
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
argument_list|,
name|TRUE
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
name|tr_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_dialog_update (GimpTransformTool * tr_tool)
name|gimp_rotate_tool_dialog_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpRotateTool
modifier|*
name|rotate
init|=
name|GIMP_ROTATE_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|rotate
operator|->
name|angle_adj
argument_list|)
argument_list|,
name|gimp_rad_to_deg
argument_list|(
name|tr_tool
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
name|tr_tool
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
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_X
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
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
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
name|tr_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_prepare (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_rotate_tool_prepare
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
name|GimpRotateTool
modifier|*
name|rotate
init|=
name|GIMP_ROTATE_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
literal|0.0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|=
literal|0.0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
operator|=
name|tr_tool
operator|->
name|cx
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
operator|=
name|tr_tool
operator|->
name|cy
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|display
operator|->
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
name|tr_tool
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
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
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
name|display
operator|->
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
name|display
operator|->
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
name|tr_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_motion (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_rotate_tool_motion
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
init|=
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
argument_list|(
name|tr_tool
argument_list|)
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
if|if
condition|(
name|tr_tool
operator|->
name|function
operator|==
name|TRANSFORM_HANDLE_CENTER
condition|)
block|{
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
operator|=
name|tr_tool
operator|->
name|curx
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
operator|=
name|tr_tool
operator|->
name|cury
expr_stmt|;
name|tr_tool
operator|->
name|cx
operator|=
name|tr_tool
operator|->
name|curx
expr_stmt|;
name|tr_tool
operator|->
name|cy
operator|=
name|tr_tool
operator|->
name|cury
expr_stmt|;
return|return;
block|}
name|cx
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
expr_stmt|;
name|cy
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
expr_stmt|;
name|x1
operator|=
name|tr_tool
operator|->
name|curx
operator|-
name|cx
expr_stmt|;
name|x2
operator|=
name|tr_tool
operator|->
name|lastx
operator|-
name|cx
expr_stmt|;
name|y1
operator|=
name|cy
operator|-
name|tr_tool
operator|->
name|cury
expr_stmt|;
name|y2
operator|=
name|cy
operator|-
name|tr_tool
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
name|tr_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|+=
name|angle
expr_stmt|;
comment|/*  limit the angle to between -180 and 180 degrees  */
if|if
condition|(
name|tr_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|<
operator|-
name|G_PI
condition|)
block|{
name|tr_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|+=
literal|2.0
operator|*
name|G_PI
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tr_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|>
name|G_PI
condition|)
block|{
name|tr_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|-=
literal|2.0
operator|*
name|G_PI
expr_stmt|;
block|}
comment|/*  constrain the angle to 15-degree multiples if ctrl is held down  */
if|if
condition|(
name|options
operator|->
name|constrain
condition|)
block|{
name|tr_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|FIFTEEN_DEG
operator|*
call|(
name|gint
call|)
argument_list|(
operator|(
name|tr_tool
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
block|}
else|else
block|{
name|tr_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rotate_tool_recalc (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_rotate_tool_recalc
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
name|tr_tool
operator|->
name|cx
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
expr_stmt|;
name|tr_tool
operator|->
name|cy
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
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
name|gimp_transform_matrix_rotate_center
argument_list|(
operator|&
name|tr_tool
operator|->
name|transform
argument_list|,
name|tr_tool
operator|->
name|cx
argument_list|,
name|tr_tool
operator|->
name|cy
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_angle_changed (GtkAdjustment * adj,GimpTransformTool * tr_tool)
name|rotate_angle_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpTransformTool
modifier|*
name|tr_tool
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
DECL|macro|ANGLE_EPSILON
define|#
directive|define
name|ANGLE_EPSILON
value|0.0001
if|if
condition|(
name|ABS
argument_list|(
name|value
operator|-
name|tr_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
operator|>
name|ANGLE_EPSILON
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
name|REAL_ANGLE
index|]
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|value
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
undef|#
directive|undef
name|ANGLE_EPSILON
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_center_changed (GtkWidget * widget,GimpTransformTool * tr_tool)
name|rotate_center_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|gdouble
name|cx
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
name|cy
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
name|cx
operator|!=
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
operator|)
operator|||
operator|(
name|cy
operator|!=
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
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
name|CENTER_X
index|]
operator|=
name|cx
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
operator|=
name|cy
expr_stmt|;
name|tr_tool
operator|->
name|cx
operator|=
name|cx
expr_stmt|;
name|tr_tool
operator|->
name|cy
operator|=
name|cy
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
end_function

end_unit

