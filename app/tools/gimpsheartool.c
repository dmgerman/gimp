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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gui/info-dialog.h"
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

begin_comment
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_shear_tool_class_init
parameter_list|(
name|GimpShearToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_shear_tool_init
parameter_list|(
name|GimpShearTool
modifier|*
name|shear_tool
parameter_list|)
function_decl|;
end_function_decl

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
name|gimp_shear_tool_prepare
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
name|gimp_shear_tool_motion
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
name|gimp_shear_tool_recalc
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
name|shear_info_update
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
name|shear_x_mag_changed
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
name|shear_y_mag_changed
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
comment|/*  variables local to this file  */
end_comment

begin_decl_stmt
DECL|variable|xshear_val
specifier|static
name|gdouble
name|xshear_val
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|yshear_val
specifier|static
name|gdouble
name|yshear_val
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
comment|/* Public functions */
end_comment

begin_function
name|void
DECL|function|gimp_shear_tool_register (GimpToolRegisterCallback callback,gpointer data)
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
name|FALSE
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
literal|"Shear the layer or selection"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Transform Tools/Shear"
argument_list|)
argument_list|,
literal|"<shift>S"
argument_list|,
name|NULL
argument_list|,
literal|"tools/shear.html"
argument_list|,
name|GIMP_STOCK_TOOL_SHEAR
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_shear_tool_get_type (void)
name|gimp_shear_tool_get_type
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
name|GimpShearToolClass
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
name|gimp_shear_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpShearTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_shear_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_TRANSFORM_TOOL
argument_list|,
literal|"GimpShearTool"
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
name|gimp_shear_tool_dialog
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
decl_stmt|;
name|GimpTransformTool
modifier|*
name|tr_tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|shear_tool
argument_list|)
expr_stmt|;
name|tr_tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|shear_tool
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_SHEAR_TOOL_CURSOR
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|use_center
operator|=
name|FALSE
expr_stmt|;
name|tr_tool
operator|->
name|shell_identifier
operator|=
literal|"gimp-shear-tool-dialog"
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
literal|"Shearing..."
argument_list|)
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
name|info_dialog_add_spinbutton
argument_list|(
name|tr_tool
operator|->
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Shear Magnitude X:"
argument_list|)
argument_list|,
operator|&
name|xshear_val
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
argument_list|,
name|G_CALLBACK
argument_list|(
name|shear_x_mag_changed
argument_list|)
argument_list|,
name|tr_tool
argument_list|)
expr_stmt|;
name|info_dialog_add_spinbutton
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
operator|&
name|yshear_val
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
DECL|function|gimp_shear_tool_prepare (GimpTransformTool * tr_tool,GimpDisplay * gdisp)
name|gimp_shear_tool_prepare
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
DECL|function|gimp_shear_tool_motion (GimpTransformTool * tr_tool,GimpDisplay * gdisp)
name|gimp_shear_tool_motion
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
name|gdouble
name|diffx
decl_stmt|,
name|diffy
decl_stmt|;
name|gint
name|dir
decl_stmt|;
name|diffx
operator|=
name|tr_tool
operator|->
name|curx
operator|-
name|tr_tool
operator|->
name|lastx
expr_stmt|;
name|diffy
operator|=
name|tr_tool
operator|->
name|cury
operator|-
name|tr_tool
operator|->
name|lasty
expr_stmt|;
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
operator|!=
name|GIMP_ORIENTATION_UNKNOWN
condition|)
block|{
name|dir
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
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
if|if
condition|(
name|dir
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|-=
name|diffx
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
break|break;
case|case
name|TRANSFORM_HANDLE_2
case|:
if|if
condition|(
name|dir
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|-=
name|diffx
expr_stmt|;
else|else
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
operator|+=
name|diffy
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_3
case|:
if|if
condition|(
name|dir
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
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
name|YSHEAR
index|]
operator|-=
name|diffy
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_4
case|:
if|if
condition|(
name|dir
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
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
name|YSHEAR
index|]
operator|+=
name|diffy
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_shear_tool_recalc (GimpTransformTool * tr_tool,GimpDisplay * gdisp)
name|gimp_shear_tool_recalc
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
name|gdouble
name|amount
decl_stmt|;
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
name|gimp_drawable_transform_matrix_shear
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
name|HORZ_OR_VERT
index|]
argument_list|,
name|amount
argument_list|,
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
name|shear_info_update
argument_list|(
name|tr_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shear_info_update (GimpTransformTool * tr_tool)
name|shear_info_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|xshear_val
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
expr_stmt|;
name|yshear_val
operator|=
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
expr_stmt|;
name|info_dialog_update
argument_list|(
name|tr_tool
operator|->
name|info_dialog
argument_list|)
expr_stmt|;
name|info_dialog_popup
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
DECL|function|shear_x_mag_changed (GtkWidget * widget,GimpTransformTool * tr_tool)
name|shear_x_mag_changed
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
name|value
decl_stmt|;
name|value
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|widget
argument_list|)
operator|->
name|value
expr_stmt|;
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
name|tr_tool
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|=
name|value
expr_stmt|;
name|gimp_shear_tool_recalc
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
DECL|function|shear_y_mag_changed (GtkWidget * widget,GimpTransformTool * tr_tool)
name|shear_y_mag_changed
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
name|value
decl_stmt|;
name|value
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|widget
argument_list|)
operator|->
name|value
expr_stmt|;
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
name|tr_tool
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
operator|=
name|value
expr_stmt|;
name|gimp_shear_tool_recalc
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

end_unit

