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
file|"core/gimpdrawable-transform-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
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
file|"gui/info-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimprotatetool.h"
end_include

begin_include
include|#
directive|include
file|"transform_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
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
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|0.018
end_define

begin_comment
DECL|macro|EPSILON
comment|/*  ~ 1 degree  */
end_comment

begin_define
DECL|macro|FIFTEEN_DEG
define|#
directive|define
name|FIFTEEN_DEG
value|(G_PI / 12.0)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_rotate_tool_class_init
parameter_list|(
name|GimpRotateToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rotate_tool_init
parameter_list|(
name|GimpRotateTool
modifier|*
name|rotate_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TileManager
modifier|*
name|gimp_rotate_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|TransformState
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|rotate_tool_recalc
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
name|rotate_tool_motion
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
name|rotate_info_update
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
name|rotate_angle_changed
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
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
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  variables local to this file  */
end_comment

begin_decl_stmt
DECL|variable|angle_val
specifier|static
name|gdouble
name|angle_val
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|center_vals
specifier|static
name|gdouble
name|center_vals
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  needed for size update  */
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
DECL|function|gimp_rotate_tool_register (GimpToolRegisterCallback callback,gpointer data)
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
name|transform_options_new
argument_list|,
name|FALSE
argument_list|,
literal|"gimp-rotate-tool"
argument_list|,
name|_
argument_list|(
literal|"Rotate Tool"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Rotate the layer or selection"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Transform Tools/Rotate"
argument_list|)
argument_list|,
literal|"<shift>R"
argument_list|,
name|NULL
argument_list|,
literal|"tools/rotate.html"
argument_list|,
name|GIMP_STOCK_TOOL_ROTATE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_rotate_tool_get_type (void)
name|gimp_rotate_tool_get_type
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
name|GimpRotateToolClass
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
name|gimp_rotate_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpRotateTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_rotate_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_TRANSFORM_TOOL
argument_list|,
literal|"GimpRotateTool"
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
DECL|function|gimp_rotate_tool_class_init (GimpRotateToolClass * klass)
name|gimp_rotate_tool_class_init
parameter_list|(
name|GimpRotateToolClass
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
name|transform
operator|=
name|gimp_rotate_tool_transform
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
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|rotate_tool
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_ROTATE_TOOL_CURSOR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|TileManager
modifier|*
DECL|function|gimp_rotate_tool_transform (GimpTransformTool * transform_tool,GimpDisplay * gdisp,TransformState state)
name|gimp_rotate_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|transform_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|TransformState
name|state
parameter_list|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|TRANSFORM_INIT
case|:
name|angle_val
operator|=
literal|0.0
expr_stmt|;
name|center_vals
index|[
literal|0
index|]
operator|=
name|transform_tool
operator|->
name|cx
expr_stmt|;
name|center_vals
index|[
literal|1
index|]
operator|=
name|transform_tool
operator|->
name|cy
expr_stmt|;
if|if
condition|(
operator|!
name|transform_tool
operator|->
name|info_dialog
condition|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton2
decl_stmt|;
name|transform_tool
operator|->
name|info_dialog
operator|=
name|info_dialog_new
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Rotate"
argument_list|)
argument_list|,
literal|"rotate"
argument_list|,
name|GIMP_STOCK_TOOL_ROTATE
argument_list|,
name|_
argument_list|(
literal|"Rotation Information"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"tools/transform_rotate.html"
argument_list|)
expr_stmt|;
name|gimp_transform_tool_info_dialog_connect
argument_list|(
name|transform_tool
argument_list|,
name|GIMP_STOCK_TOOL_ROTATE
argument_list|)
expr_stmt|;
name|widget
operator|=
name|info_dialog_add_spinbutton
argument_list|(
name|transform_tool
operator|->
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Angle:"
argument_list|)
argument_list|,
operator|&
name|angle_val
argument_list|,
operator|-
literal|180
argument_list|,
literal|180
argument_list|,
literal|1
argument_list|,
literal|15
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|G_CALLBACK
argument_list|(
name|rotate_angle_changed
argument_list|)
argument_list|,
name|transform_tool
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_wrap
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  this looks strange (-180, 181), but it works  */
name|widget
operator|=
name|info_dialog_add_scale
argument_list|(
name|transform_tool
operator|->
name|info_dialog
argument_list|,
literal|""
argument_list|,
operator|&
name|angle_val
argument_list|,
operator|-
literal|180
argument_list|,
literal|181
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|1
argument_list|,
operator|-
literal|1
argument_list|,
name|G_CALLBACK
argument_list|(
name|rotate_angle_changed
argument_list|)
argument_list|,
name|transform_tool
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|widget
argument_list|,
literal|180
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|spinbutton2
operator|=
name|info_dialog_add_spinbutton
argument_list|(
name|transform_tool
operator|->
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Center X:"
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
name|transform_tool
operator|->
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Y:"
argument_list|)
argument_list|,
name|center_vals
argument_list|,
literal|1
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|unit
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
name|rotate_center_changed
argument_list|)
argument_list|,
name|transform_tool
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
name|spinbutton2
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|transform_tool
operator|->
name|info_dialog
operator|->
name|info_table
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|transform_tool
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
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|transform_tool
operator|->
name|info_dialog
operator|->
name|shell
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|rotate_center_changed
argument_list|,
name|transform_tool
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
operator|-
literal|65536
argument_list|,
literal|65536
operator|+
name|gdisp
operator|->
name|gimage
operator|->
name|width
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
operator|-
literal|65536
argument_list|,
literal|65536
operator|+
name|gdisp
operator|->
name|gimage
operator|->
name|height
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
name|transform_tool
operator|->
name|x1
argument_list|,
name|transform_tool
operator|->
name|x2
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
name|transform_tool
operator|->
name|y1
argument_list|,
name|transform_tool
operator|->
name|y2
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
name|center_vals
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
name|center_vals
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|rotate_center_changed
argument_list|,
name|transform_tool
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|transform_tool
operator|->
name|info_dialog
operator|->
name|shell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|angle_val
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|=
name|angle_val
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
operator|=
name|center_vals
index|[
literal|0
index|]
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
operator|=
name|center_vals
index|[
literal|1
index|]
expr_stmt|;
break|break;
case|case
name|TRANSFORM_MOTION
case|:
name|rotate_tool_motion
argument_list|(
name|transform_tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|rotate_tool_recalc
argument_list|(
name|transform_tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
break|break;
case|case
name|TRANSFORM_RECALC
case|:
name|rotate_tool_recalc
argument_list|(
name|transform_tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
break|break;
case|case
name|TRANSFORM_FINISH
case|:
return|return
name|gimp_transform_tool_transform_tiles
argument_list|(
name|transform_tool
argument_list|,
name|_
argument_list|(
literal|"Rotating..."
argument_list|)
argument_list|)
return|;
break|break;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_info_update (GimpTransformTool * transform_tool)
name|rotate_info_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|transform_tool
parameter_list|)
block|{
name|angle_val
operator|=
name|gimp_rad_to_deg
argument_list|(
name|transform_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|)
expr_stmt|;
name|center_vals
index|[
literal|0
index|]
operator|=
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
expr_stmt|;
name|center_vals
index|[
literal|1
index|]
operator|=
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
expr_stmt|;
name|info_dialog_update
argument_list|(
name|transform_tool
operator|->
name|info_dialog
argument_list|)
expr_stmt|;
name|info_dialog_popup
argument_list|(
name|transform_tool
operator|->
name|info_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_angle_changed (GtkWidget * widget,gpointer data)
name|rotate_angle_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpTransformTool
modifier|*
name|transform_tool
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|transform_tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|value
operator|=
name|gimp_deg_to_rad
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|widget
argument_list|)
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|!=
name|transform_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
condition|)
block|{
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|value
expr_stmt|;
name|rotate_tool_recalc
argument_list|(
name|transform_tool
argument_list|,
name|tool
operator|->
name|gdisp
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_center_changed (GtkWidget * widget,gpointer data)
name|rotate_center_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpTransformTool
modifier|*
name|transform_tool
decl_stmt|;
name|gdouble
name|cx
decl_stmt|;
name|gdouble
name|cy
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|transform_tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|cx
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cy
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|cx
operator|!=
name|transform_tool
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
name|transform_tool
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
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
operator|=
name|cx
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
operator|=
name|cy
expr_stmt|;
name|transform_tool
operator|->
name|cx
operator|=
name|cx
expr_stmt|;
name|transform_tool
operator|->
name|cy
operator|=
name|cy
expr_stmt|;
name|rotate_tool_recalc
argument_list|(
name|transform_tool
argument_list|,
name|tool
operator|->
name|gdisp
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_tool_motion (GimpTransformTool * transform_tool,GimpDisplay * gdisp)
name|rotate_tool_motion
parameter_list|(
name|GimpTransformTool
modifier|*
name|transform_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|TransformOptions
modifier|*
name|options
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
name|transform_tool
operator|->
name|function
operator|==
name|TRANSFORM_HANDLE_CENTER
condition|)
block|{
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
operator|=
name|transform_tool
operator|->
name|curx
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
operator|=
name|transform_tool
operator|->
name|cury
expr_stmt|;
name|transform_tool
operator|->
name|cx
operator|=
name|transform_tool
operator|->
name|curx
expr_stmt|;
name|transform_tool
operator|->
name|cy
operator|=
name|transform_tool
operator|->
name|cury
expr_stmt|;
return|return;
block|}
name|options
operator|=
operator|(
name|TransformOptions
operator|*
operator|)
name|GIMP_TOOL
argument_list|(
name|transform_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
name|cx
operator|=
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
expr_stmt|;
name|cy
operator|=
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
expr_stmt|;
name|x1
operator|=
name|transform_tool
operator|->
name|curx
operator|-
name|cx
expr_stmt|;
name|x2
operator|=
name|transform_tool
operator|->
name|lastx
operator|-
name|cx
expr_stmt|;
name|y1
operator|=
name|cy
operator|-
name|transform_tool
operator|->
name|cury
expr_stmt|;
name|y2
operator|=
name|cy
operator|-
name|transform_tool
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
name|transform_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|+=
name|angle
expr_stmt|;
comment|/*  limit the angle to between 0 and 360 degrees  */
if|if
condition|(
name|transform_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|<
operator|-
name|G_PI
condition|)
name|transform_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|=
literal|2.0
operator|*
name|G_PI
operator|-
name|transform_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
expr_stmt|;
elseif|else
if|if
condition|(
name|transform_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|>
name|G_PI
condition|)
name|transform_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|=
name|transform_tool
operator|->
name|trans_info
index|[
name|REAL_ANGLE
index|]
operator|-
literal|2.0
operator|*
name|G_PI
expr_stmt|;
comment|/*  constrain the angle to 15-degree multiples if ctrl is held down  */
if|if
condition|(
name|options
operator|->
name|constrain_1
condition|)
block|{
name|transform_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|FIFTEEN_DEG
operator|*
call|(
name|int
call|)
argument_list|(
operator|(
name|transform_tool
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
name|transform_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
operator|=
name|transform_tool
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
DECL|function|rotate_tool_recalc (GimpTransformTool * transform_tool,GimpDisplay * gdisp)
name|rotate_tool_recalc
parameter_list|(
name|GimpTransformTool
modifier|*
name|transform_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gdouble
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|cx
operator|=
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_X
index|]
expr_stmt|;
name|cy
operator|=
name|transform_tool
operator|->
name|trans_info
index|[
name|CENTER_Y
index|]
expr_stmt|;
name|transform_tool
operator|->
name|cx
operator|=
name|cx
expr_stmt|;
name|transform_tool
operator|->
name|cy
operator|=
name|cy
expr_stmt|;
name|gimp_drawable_transform_matrix_rotate_center
argument_list|(
name|transform_tool
operator|->
name|cx
argument_list|,
name|transform_tool
operator|->
name|cy
argument_list|,
name|transform_tool
operator|->
name|trans_info
index|[
name|ANGLE
index|]
argument_list|,
name|transform_tool
operator|->
name|transform
argument_list|)
expr_stmt|;
comment|/*  transform the bounding box  */
name|gimp_transform_tool_transform_bounding_box
argument_list|(
name|transform_tool
argument_list|)
expr_stmt|;
comment|/*  update the information dialog  */
name|rotate_info_update
argument_list|(
name|transform_tool
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

