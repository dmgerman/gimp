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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|FIXME #include "gui/gui-types.h"
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

begin_include
include|#
directive|include
file|"gui/info-dialog.h"
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
name|gimp_scale_tool_class_init
parameter_list|(
name|GimpScaleToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_scale_tool_init
parameter_list|(
name|GimpScaleTool
modifier|*
name|sc_tool
parameter_list|)
function_decl|;
end_function_decl

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
name|gimp_scale_tool_prepare
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
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
name|gdisp
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
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_scale_tool_info_update
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
name|gimp_scale_tool_size_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_scale_tool_unit_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

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
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpTransformToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_scale_tool_register (GimpToolRegisterCallback callback,gpointer data)
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
literal|"/Tools/Transform Tools/_Scale"
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
name|GType
DECL|function|gimp_scale_tool_get_type (void)
name|gimp_scale_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpScaleToolClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_scale_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpScaleTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_scale_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_TRANSFORM_TOOL
argument_list|,
literal|"GimpScaleTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

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
decl_stmt|;
name|trans_class
operator|=
name|GIMP_TRANSFORM_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|trans_class
operator|->
name|dialog
operator|=
name|gimp_scale_tool_dialog
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
name|GIMP_RESIZE_TOOL_CURSOR
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
literal|"Scaling..."
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
block|{
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|info_dialog_add_label
argument_list|(
name|tr_tool
operator|->
name|info_dialog
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
name|tr_tool
operator|->
name|info_dialog
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
name|tr_tool
operator|->
name|info_dialog
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
name|tr_tool
operator|->
name|info_dialog
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
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_scale_tool_size_changed
argument_list|)
argument_list|,
name|tr_tool
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|sizeentry
argument_list|,
literal|"unit_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_scale_tool_unit_changed
argument_list|)
argument_list|,
name|tr_tool
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
name|tr_tool
operator|->
name|info_dialog
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
name|tr_tool
operator|->
name|info_dialog
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
name|tr_tool
operator|->
name|info_dialog
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
name|tr_tool
operator|->
name|info_dialog
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
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_prepare (GimpTransformTool * tr_tool,GimpDisplay * gdisp)
name|gimp_scale_tool_prepare
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|size_vals
index|[
literal|0
index|]
operator|=
name|tr_tool
operator|->
name|x2
operator|-
name|tr_tool
operator|->
name|x1
expr_stmt|;
name|size_vals
index|[
literal|1
index|]
operator|=
name|tr_tool
operator|->
name|y2
operator|-
name|tr_tool
operator|->
name|y1
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|sizeentry
argument_list|,
name|gimp_scale_tool_size_changed
argument_list|,
name|tr_tool
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|sizeentry
argument_list|,
name|gimp_scale_tool_unit_changed
argument_list|,
name|tr_tool
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
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
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
name|g_signal_handlers_unblock_by_func
argument_list|(
name|sizeentry
argument_list|,
name|gimp_scale_tool_size_changed
argument_list|,
name|tr_tool
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|sizeentry
argument_list|,
name|gimp_scale_tool_unit_changed
argument_list|,
name|tr_tool
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_motion (GimpTransformTool * tr_tool,GimpDisplay * gdisp)
name|gimp_scale_tool_motion
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpTransformOptions
modifier|*
name|options
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
name|gdouble
name|diff_x
decl_stmt|,
name|diff_y
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
name|diff_x
operator|=
name|tr_tool
operator|->
name|curx
operator|-
name|tr_tool
operator|->
name|lastx
expr_stmt|;
name|diff_y
operator|=
name|tr_tool
operator|->
name|cury
operator|-
name|tr_tool
operator|->
name|lasty
expr_stmt|;
switch|switch
condition|(
name|tr_tool
operator|->
name|function
condition|)
block|{
case|case
name|TRANSFORM_HANDLE_1
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
name|TRANSFORM_HANDLE_2
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
name|TRANSFORM_HANDLE_3
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
name|TRANSFORM_HANDLE_4
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
comment|/*  if just the mod1 key is down, affect only the height  */
if|if
condition|(
name|options
operator|->
name|constrain_2
operator|&&
operator|!
name|options
operator|->
name|constrain_1
condition|)
block|{
name|diff_x
operator|=
literal|0
expr_stmt|;
block|}
comment|/*  if just the control key is down, affect only the width  */
elseif|else
if|if
condition|(
name|options
operator|->
name|constrain_1
operator|&&
operator|!
name|options
operator|->
name|constrain_2
condition|)
block|{
name|diff_y
operator|=
literal|0
expr_stmt|;
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
comment|/*  if both the control key& mod1 keys are down,    *  keep the aspect ratio intact    */
if|if
condition|(
name|options
operator|->
name|constrain_1
operator|&&
name|options
operator|->
name|constrain_2
condition|)
block|{
name|ratio
operator|=
operator|(
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
operator|/
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
operator|)
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
DECL|function|gimp_scale_tool_recalc (GimpTransformTool * tr_tool,GimpDisplay * gdisp)
name|gimp_scale_tool_recalc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gimp_transform_matrix_scale
argument_list|(
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
operator|&
name|tr_tool
operator|->
name|transform
argument_list|)
expr_stmt|;
comment|/*  transform the bounding box  */
name|gimp_transform_tool_transform_bounding_box
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
comment|/*  update the information dialog  */
name|gimp_scale_tool_info_update
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_info_update (GimpTransformTool * tr_tool)
name|gimp_scale_tool_info_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpTool
modifier|*
name|tool
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
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|tr_tool
argument_list|)
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
comment|/*  Find original sizes  */
name|x1
operator|=
name|tr_tool
operator|->
name|x1
expr_stmt|;
name|y1
operator|=
name|tr_tool
operator|->
name|y1
expr_stmt|;
name|x2
operator|=
name|tr_tool
operator|->
name|x2
expr_stmt|;
name|y2
operator|=
name|tr_tool
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
name|gimp
operator|=
name|tool
operator|->
name|tool_info
operator|->
name|gimp
expr_stmt|;
name|unit_factor
operator|=
name|_gimp_unit_get_factor
argument_list|(
name|gimp
argument_list|,
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
name|_gimp_unit_get_digits
argument_list|(
name|gimp
argument_list|,
name|label_unit
argument_list|)
operator|+
literal|1
argument_list|,
name|_gimp_unit_get_symbol
argument_list|(
name|gimp
argument_list|,
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
name|tool
operator|->
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
name|tool
operator|->
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
name|gint
operator|)
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
expr_stmt|;
name|y3
operator|=
operator|(
name|gint
operator|)
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
expr_stmt|;
name|x4
operator|=
operator|(
name|gint
operator|)
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
expr_stmt|;
name|y4
operator|=
operator|(
name|gint
operator|)
name|tr_tool
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
sizeof|sizeof
argument_list|(
name|x_ratio_buf
argument_list|)
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
sizeof|sizeof
argument_list|(
name|y_ratio_buf
argument_list|)
argument_list|,
literal|"%0.2f"
argument_list|,
name|ratio_y
argument_list|)
expr_stmt|;
name|info_dialog_update
argument_list|(
name|tr_tool
operator|->
name|info_dialog
argument_list|)
expr_stmt|;
name|info_dialog_show
argument_list|(
name|tr_tool
operator|->
name|info_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_tool_size_changed (GtkWidget * widget,GimpTransformTool * tr_tool)
name|gimp_scale_tool_size_changed
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
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|width
operator|=
name|RINT
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
argument_list|)
expr_stmt|;
name|height
operator|=
name|RINT
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
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|width
operator|!=
operator|(
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
operator|)
operator|)
operator|||
operator|(
name|height
operator|!=
operator|(
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
operator|)
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
name|gimp_scale_tool_recalc
argument_list|(
name|tr_tool
argument_list|,
name|GIMP_TOOL
argument_list|(
name|tr_tool
argument_list|)
operator|->
name|gdisp
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
DECL|function|gimp_scale_tool_unit_changed (GtkWidget * widget,GimpTransformTool * tr_tool)
name|gimp_scale_tool_unit_changed
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
name|gimp_scale_tool_info_update
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

