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
file|<stdlib.h>
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
file|"gimpsheartool.h"
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
DECL|macro|HORZ_OR_VERT
define|#
directive|define
name|HORZ_OR_VERT
value|0
end_define

begin_define
DECL|macro|XSHEAR
define|#
directive|define
name|XSHEAR
value|1
end_define

begin_define
DECL|macro|YSHEAR
define|#
directive|define
name|YSHEAR
value|2
end_define

begin_comment
comment|/*  the minimum movement before direction of shear can be determined (pixels) */
end_comment

begin_define
DECL|macro|MIN_MOVE
define|#
directive|define
name|MIN_MOVE
value|5
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
name|void
name|gimp_shear_tool_dialog
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
name|gimp_shear_tool_dialog_update
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
name|gimp_shear_tool_prepare
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
name|gimp_shear_tool_motion
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
name|gimp_shear_tool_recalc
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
name|shear_x_mag_changed
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
name|shear_y_mag_changed
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpShearTool,gimp_shear_tool,GIMP_TYPE_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpShearTool
argument_list|,
argument|gimp_shear_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_TOOL
argument_list|)
end_macro

begin_function
name|void
name|gimp_shear_tool_register
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
name|GIMP_TYPE_SHEAR_TOOL
argument_list|,
name|GIMP_TYPE_TRANSFORM_OPTIONS
argument_list|,
name|gimp_transform_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-shear-tool"
argument_list|,
name|_
argument_list|(
literal|"Shear"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Shear Tool: Shear the layer or selection"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"S_hear"
argument_list|)
argument_list|,
literal|"<shift>S"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_SHEAR
argument_list|,
name|GIMP_STOCK_TOOL_SHEAR
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_shear_tool_class_init (GimpShearToolClass * klass)
name|gimp_shear_tool_class_init
parameter_list|(
name|GimpShearToolClass
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
name|gimp_shear_tool_dialog
expr_stmt|;
name|trans_class
operator|->
name|dialog_update
operator|=
name|gimp_shear_tool_dialog_update
expr_stmt|;
name|trans_class
operator|->
name|prepare
operator|=
name|gimp_shear_tool_prepare
expr_stmt|;
name|trans_class
operator|->
name|motion
operator|=
name|gimp_shear_tool_motion
expr_stmt|;
name|trans_class
operator|->
name|recalc
operator|=
name|gimp_shear_tool_recalc
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_shear_tool_init (GimpShearTool * shear_tool)
name|gimp_shear_tool_init
parameter_list|(
name|GimpShearTool
modifier|*
name|shear_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|shear_tool
argument_list|)
decl_stmt|;
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|shear_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_SHEAR
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|undo_desc
operator|=
name|Q_
argument_list|(
literal|"command|Shear"
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|shell_desc
operator|=
name|_
argument_list|(
literal|"Shearing Information"
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Shearing"
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|use_grid
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_shear_tool_dialog (GimpTransformTool * tr_tool)
name|gimp_shear_tool_dialog
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpShearTool
modifier|*
name|shear
init|=
name|GIMP_SHEAR_TOOL
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
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
name|shear
operator|->
name|x_adj
argument_list|,
literal|0
argument_list|,
operator|-
literal|65536
argument_list|,
literal|65536
argument_list|,
literal|1
argument_list|,
literal|15
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
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
literal|"Shear magnitude X:"
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
name|g_signal_connect
argument_list|(
name|shear
operator|->
name|x_adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|shear_x_mag_changed
argument_list|)
argument_list|,
name|tr_tool
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|shear
operator|->
name|y_adj
argument_list|,
literal|0
argument_list|,
operator|-
literal|65536
argument_list|,
literal|65536
argument_list|,
literal|1
argument_list|,
literal|15
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
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
literal|1
argument_list|,
name|_
argument_list|(
literal|"Shear magnitude Y:"
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
name|g_signal_connect
argument_list|(
name|shear
operator|->
name|y_adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|shear_y_mag_changed
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
DECL|function|gimp_shear_tool_dialog_update (GimpTransformTool * tr_tool)
name|gimp_shear_tool_dialog_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpShearTool
modifier|*
name|shear
init|=
name|GIMP_SHEAR_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|shear
operator|->
name|x_adj
argument_list|)
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|shear
operator|->
name|y_adj
argument_list|)
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_shear_tool_prepare (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_shear_tool_prepare
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
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|=
name|GIMP_ORIENTATION_UNKNOWN
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|=
literal|0.0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_shear_tool_motion (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_shear_tool_motion
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
name|gdouble
name|diffx
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
name|diffy
init|=
name|tr_tool
operator|->
name|cury
operator|-
name|tr_tool
operator|->
name|lasty
decl_stmt|;
comment|/*  If we haven't yet decided on which way to control shearing    *  decide using the maximum differential    */
if|if
condition|(
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|==
name|GIMP_ORIENTATION_UNKNOWN
condition|)
block|{
if|if
condition|(
name|abs
argument_list|(
name|diffx
argument_list|)
operator|>
name|MIN_MOVE
operator|||
name|abs
argument_list|(
name|diffy
argument_list|)
operator|>
name|MIN_MOVE
condition|)
block|{
if|if
condition|(
name|abs
argument_list|(
name|diffx
argument_list|)
operator|>
name|abs
argument_list|(
name|diffy
argument_list|)
condition|)
block|{
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|=
name|GIMP_ORIENTATION_HORIZONTAL
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
else|else
block|{
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|=
name|GIMP_ORIENTATION_VERTICAL
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
block|}
comment|/*  set the current coords to the last ones  */
else|else
block|{
name|tr_tool
operator|->
name|curx
operator|=
name|tr_tool
operator|->
name|lastx
expr_stmt|;
name|tr_tool
operator|->
name|cury
operator|=
name|tr_tool
operator|->
name|lasty
expr_stmt|;
block|}
block|}
comment|/*  if the direction is known, keep track of the magnitude  */
if|if
condition|(
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
block|{
if|if
condition|(
name|tr_tool
operator|->
name|cury
operator|>
operator|(
name|tr_tool
operator|->
name|ty1
operator|+
name|tr_tool
operator|->
name|ty3
operator|)
operator|/
literal|2
condition|)
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|+=
name|diffx
expr_stmt|;
else|else
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|-=
name|diffx
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|==
name|GIMP_ORIENTATION_VERTICAL
condition|)
block|{
if|if
condition|(
name|tr_tool
operator|->
name|curx
operator|>
operator|(
name|tr_tool
operator|->
name|tx1
operator|+
name|tr_tool
operator|->
name|tx2
operator|)
operator|/
literal|2
condition|)
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
operator|+=
name|diffy
expr_stmt|;
else|else
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
operator|-=
name|diffy
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_shear_tool_recalc (GimpTransformTool * tr_tool,GimpDisplay * display)
name|gimp_shear_tool_recalc
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
name|gdouble
name|amount
decl_stmt|;
if|if
condition|(
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|==
literal|0.0
operator|&&
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
operator|==
literal|0.0
condition|)
block|{
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|=
name|GIMP_ORIENTATION_UNKNOWN
expr_stmt|;
block|}
if|if
condition|(
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|amount
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
expr_stmt|;
else|else
name|amount
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
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
name|gimp_transform_matrix_shear
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
name|HORZ_OR_VERT
index|]
argument_list|,
name|amount
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shear_x_mag_changed (GtkAdjustment * adj,GimpTransformTool * tr_tool)
name|shear_x_mag_changed
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
name|gtk_adjustment_get_value
argument_list|(
name|adj
argument_list|)
decl_stmt|;
if|if
condition|(
name|value
operator|!=
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
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
if|if
condition|(
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|==
name|GIMP_ORIENTATION_UNKNOWN
condition|)
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|=
name|GIMP_ORIENTATION_HORIZONTAL
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shear_y_mag_changed (GtkAdjustment * adj,GimpTransformTool * tr_tool)
name|shear_y_mag_changed
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
name|gtk_adjustment_get_value
argument_list|(
name|adj
argument_list|)
decl_stmt|;
if|if
condition|(
name|value
operator|!=
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
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
if|if
condition|(
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|==
name|GIMP_ORIENTATION_UNKNOWN
condition|)
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|=
name|GIMP_ORIENTATION_VERTICAL
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
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
block|}
end_function

end_unit

