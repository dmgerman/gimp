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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"draw_core.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"info_dialog.h"
end_include

begin_include
include|#
directive|include
file|"shear_tool.h"
end_include

begin_include
include|#
directive|include
file|"selection.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"transform_core.h"
end_include

begin_include
include|#
directive|include
file|"transform_tool.h"
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
name|TileManager
modifier|*
name|shear_tool_transform
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GDisplay
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
name|shear_tool_recalc
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|shear_tool_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GDisplay
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
name|Tool
modifier|*
name|tool
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
name|gpointer
name|data
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
name|gpointer
name|data
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

begin_function
specifier|static
name|TileManager
modifier|*
DECL|function|shear_tool_transform (Tool * tool,GDisplay * gdisp,TransformState state)
name|shear_tool_transform
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|TransformState
name|state
parameter_list|)
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|TRANSFORM_INIT
case|:
if|if
condition|(
operator|!
name|transform_info
condition|)
block|{
name|transform_info
operator|=
name|info_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Shear Information"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"tools/transform_shear.html"
argument_list|)
expr_stmt|;
name|info_dialog_add_spinbutton
argument_list|(
name|transform_info
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
name|shear_x_mag_changed
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|info_dialog_add_spinbutton
argument_list|(
name|transform_info
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
name|shear_y_mag_changed
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|transform_info
operator|->
name|shell
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|=
name|ORIENTATION_UNKNOWN
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|=
literal|0.0
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
operator|=
literal|0.0
expr_stmt|;
return|return
name|NULL
return|;
break|break;
case|case
name|TRANSFORM_MOTION
case|:
name|shear_tool_motion
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|shear_tool_recalc
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
break|break;
case|case
name|TRANSFORM_RECALC
case|:
name|shear_tool_recalc
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
break|break;
case|case
name|TRANSFORM_FINISH
case|:
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|transform_info
operator|->
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|shear_tool_shear
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|gdisp
argument_list|,
name|transform_core
operator|->
name|original
argument_list|,
name|transform_tool_smoothing
argument_list|()
argument_list|,
name|transform_core
operator|->
name|transform
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
name|Tool
modifier|*
DECL|function|tools_new_shear_tool (void)
name|tools_new_shear_tool
parameter_list|(
name|void
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|TransformCore
modifier|*
name|private
decl_stmt|;
name|tool
operator|=
name|transform_core_new
argument_list|(
name|SHEAR
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|private
operator|=
name|tool
operator|->
name|private
expr_stmt|;
comment|/*  set the rotation specific transformation attributes  */
name|private
operator|->
name|trans_func
operator|=
name|shear_tool_transform
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|gimp_matrix3_identity
argument_list|(
name|private
operator|->
name|transform
argument_list|)
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_shear_tool (Tool * tool)
name|tools_free_shear_tool
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|transform_core_free
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shear_info_update (Tool * tool)
name|shear_info_update
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|xshear_val
operator|=
name|transform_core
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
expr_stmt|;
name|yshear_val
operator|=
name|transform_core
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
expr_stmt|;
name|info_dialog_update
argument_list|(
name|transform_info
argument_list|)
expr_stmt|;
name|info_dialog_popup
argument_list|(
name|transform_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shear_x_mag_changed (GtkWidget * widget,gpointer data)
name|shear_x_mag_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|tool
operator|=
operator|(
name|Tool
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
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
name|transform_core
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
condition|)
block|{
name|draw_core_pause
argument_list|(
name|transform_core
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|=
name|value
expr_stmt|;
name|shear_tool_recalc
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|gdisp
argument_list|)
expr_stmt|;
name|draw_core_resume
argument_list|(
name|transform_core
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shear_y_mag_changed (GtkWidget * widget,gpointer data)
name|shear_y_mag_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|tool
operator|=
operator|(
name|Tool
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
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
name|transform_core
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
condition|)
block|{
name|draw_core_pause
argument_list|(
name|transform_core
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
operator|=
name|value
expr_stmt|;
name|shear_tool_recalc
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|gdisp
argument_list|)
expr_stmt|;
name|draw_core_resume
argument_list|(
name|transform_core
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shear_tool_motion (Tool * tool,GDisplay * gdisp)
name|shear_tool_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gint
name|diffx
decl_stmt|,
name|diffy
decl_stmt|;
name|gint
name|dir
decl_stmt|;
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|diffx
operator|=
name|transform_core
operator|->
name|curx
operator|-
name|transform_core
operator|->
name|lastx
expr_stmt|;
name|diffy
operator|=
name|transform_core
operator|->
name|cury
operator|-
name|transform_core
operator|->
name|lasty
expr_stmt|;
comment|/*  If we haven't yet decided on which way to control shearing    *  decide using the maximum differential    */
if|if
condition|(
name|transform_core
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|==
name|ORIENTATION_UNKNOWN
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
name|transform_core
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|=
name|ORIENTATION_HORIZONTAL
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|ORIENTATION_VERTICAL
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
else|else
block|{
name|transform_core
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|=
name|ORIENTATION_VERTICAL
expr_stmt|;
name|transform_core
operator|->
name|trans_info
index|[
name|ORIENTATION_HORIZONTAL
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
block|}
comment|/*  set the current coords to the last ones  */
else|else
block|{
name|transform_core
operator|->
name|curx
operator|=
name|transform_core
operator|->
name|lastx
expr_stmt|;
name|transform_core
operator|->
name|cury
operator|=
name|transform_core
operator|->
name|lasty
expr_stmt|;
block|}
block|}
comment|/*  if the direction is known, keep track of the magnitude  */
if|if
condition|(
name|transform_core
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|!=
name|ORIENTATION_UNKNOWN
condition|)
block|{
name|dir
operator|=
name|transform_core
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
expr_stmt|;
switch|switch
condition|(
name|transform_core
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
name|ORIENTATION_HORIZONTAL
condition|)
name|transform_core
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|-=
name|diffx
expr_stmt|;
else|else
name|transform_core
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
name|ORIENTATION_HORIZONTAL
condition|)
name|transform_core
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|-=
name|diffx
expr_stmt|;
else|else
name|transform_core
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
name|ORIENTATION_HORIZONTAL
condition|)
name|transform_core
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|+=
name|diffx
expr_stmt|;
else|else
name|transform_core
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
name|ORIENTATION_HORIZONTAL
condition|)
name|transform_core
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|+=
name|diffx
expr_stmt|;
else|else
name|transform_core
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
DECL|function|shear_tool_recalc (Tool * tool,GDisplay * gdisp)
name|shear_tool_recalc
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|gfloat
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gfloat
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|cx
operator|=
operator|(
name|transform_core
operator|->
name|x1
operator|+
name|transform_core
operator|->
name|x2
operator|)
operator|/
literal|2.0
expr_stmt|;
name|cy
operator|=
operator|(
name|transform_core
operator|->
name|y1
operator|+
name|transform_core
operator|->
name|y2
operator|)
operator|/
literal|2.0
expr_stmt|;
name|width
operator|=
name|transform_core
operator|->
name|x2
operator|-
name|transform_core
operator|->
name|x1
expr_stmt|;
name|height
operator|=
name|transform_core
operator|->
name|y2
operator|-
name|transform_core
operator|->
name|y1
expr_stmt|;
if|if
condition|(
name|width
operator|==
literal|0
condition|)
name|width
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|height
operator|==
literal|0
condition|)
name|height
operator|=
literal|1
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|gimp_matrix3_identity
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|,
operator|-
name|cx
argument_list|,
operator|-
name|cy
argument_list|)
expr_stmt|;
comment|/*  shear matrix  */
if|if
condition|(
name|transform_core
operator|->
name|trans_info
index|[
name|HORZ_OR_VERT
index|]
operator|==
name|ORIENTATION_HORIZONTAL
condition|)
name|gimp_matrix3_xshear
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|,
operator|(
name|float
operator|)
name|transform_core
operator|->
name|trans_info
index|[
name|XSHEAR
index|]
operator|/
name|height
argument_list|)
expr_stmt|;
else|else
name|gimp_matrix3_yshear
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|,
operator|(
name|float
operator|)
name|transform_core
operator|->
name|trans_info
index|[
name|YSHEAR
index|]
operator|/
name|width
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|transform_core
operator|->
name|transform
argument_list|,
operator|+
name|cx
argument_list|,
operator|+
name|cy
argument_list|)
expr_stmt|;
comment|/*  transform the bounding box  */
name|transform_core_transform_bounding_box
argument_list|(
name|tool
argument_list|)
expr_stmt|;
comment|/*  update the information dialog  */
name|shear_info_update
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|shear_tool_shear (GimpImage * gimage,GimpDrawable * drawable,GDisplay * gdisp,TileManager * float_tiles,gboolean interpolation,GimpMatrix3 matrix)
name|shear_tool_shear
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|TileManager
modifier|*
name|float_tiles
parameter_list|,
name|gboolean
name|interpolation
parameter_list|,
name|GimpMatrix3
name|matrix
parameter_list|)
block|{
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|TileManager
modifier|*
name|ret
decl_stmt|;
name|progress
operator|=
name|progress_start
argument_list|(
name|gdisp
argument_list|,
name|_
argument_list|(
literal|"Shearing..."
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ret
operator|=
name|transform_core_do
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|float_tiles
argument_list|,
name|interpolation
argument_list|,
name|matrix
argument_list|,
name|progress
condition|?
name|progress_update_and_flush
else|:
operator|(
name|GimpProgressFunc
operator|)
name|NULL
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

end_unit

