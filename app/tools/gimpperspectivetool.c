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

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gui/info-dialog.h"
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
file|"gimpperspectivetool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
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

begin_define
DECL|macro|WANT_PERSPECTIVE_BITS
define|#
directive|define
name|WANT_PERSPECTIVE_BITS
end_define

begin_include
include|#
directive|include
file|"icons.h"
end_include

begin_comment
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_class_init
parameter_list|(
name|GimpPerspectiveToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_init
parameter_list|(
name|GimpPerspectiveTool
modifier|*
name|perspective_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_tool_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TileManager
modifier|*
name|gimp_perspective_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|transform_tool
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
name|perspective_tool_recalc
parameter_list|(
name|GimpTool
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
name|perspective_tool_motion
parameter_list|(
name|GimpTool
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
name|perspective_info_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  storage for information dialog fields  */
end_comment

begin_decl_stmt
DECL|variable|matrix_row_buf
specifier|static
name|gchar
name|matrix_row_buf
index|[
literal|3
index|]
index|[
name|MAX_INFO_BUF
index|]
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

begin_decl_stmt
DECL|variable|perspective_options
specifier|static
name|TransformOptions
modifier|*
name|perspective_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_perspective_tool_register (void)
name|gimp_perspective_tool_register
parameter_list|(
name|void
parameter_list|)
block|{
name|tool_manager_register_tool
argument_list|(
name|GIMP_TYPE_PERSPECTIVE_TOOL
argument_list|,
name|FALSE
argument_list|,
literal|"gimp:perspective_tool"
argument_list|,
name|_
argument_list|(
literal|"Perspective Tool"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Change perspective of the layer or selection"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Transform Tools/Perspective"
argument_list|)
argument_list|,
literal|"<shift>P"
argument_list|,
name|NULL
argument_list|,
literal|"tools/perspective.html"
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|perspective_bits
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_perspective_tool_get_type (void)
name|gimp_perspective_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
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
name|GtkTypeInfo
name|tool_info
init|=
block|{
literal|"GimpPerspectiveTool"
block|,
sizeof|sizeof
argument_list|(
name|GimpPerspectiveTool
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpPerspectiveToolClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_perspective_tool_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_perspective_tool_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_TRANSFORM_TOOL
argument_list|,
operator|&
name|tool_info
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|gimp_perspective_tool_perspective (GimpImage * gimage,GimpDrawable * drawable,GDisplay * gdisp,TileManager * float_tiles,gboolean interpolation,GimpMatrix3 matrix)
name|gimp_perspective_tool_perspective
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
literal|"Perspective..."
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
name|gimp_transform_tool_do
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

begin_function
name|void
DECL|function|gimp_perspective_tool_find_transform (gdouble * coords,GimpMatrix3 matrix)
name|gimp_perspective_tool_find_transform
parameter_list|(
name|gdouble
modifier|*
name|coords
parameter_list|,
name|GimpMatrix3
name|matrix
parameter_list|)
block|{
name|gdouble
name|dx1
decl_stmt|,
name|dx2
decl_stmt|,
name|dx3
decl_stmt|,
name|dy1
decl_stmt|,
name|dy2
decl_stmt|,
name|dy3
decl_stmt|;
name|gdouble
name|det1
decl_stmt|,
name|det2
decl_stmt|;
name|dx1
operator|=
name|coords
index|[
name|X1
index|]
operator|-
name|coords
index|[
name|X3
index|]
expr_stmt|;
name|dx2
operator|=
name|coords
index|[
name|X2
index|]
operator|-
name|coords
index|[
name|X3
index|]
expr_stmt|;
name|dx3
operator|=
name|coords
index|[
name|X0
index|]
operator|-
name|coords
index|[
name|X1
index|]
operator|+
name|coords
index|[
name|X3
index|]
operator|-
name|coords
index|[
name|X2
index|]
expr_stmt|;
name|dy1
operator|=
name|coords
index|[
name|Y1
index|]
operator|-
name|coords
index|[
name|Y3
index|]
expr_stmt|;
name|dy2
operator|=
name|coords
index|[
name|Y2
index|]
operator|-
name|coords
index|[
name|Y3
index|]
expr_stmt|;
name|dy3
operator|=
name|coords
index|[
name|Y0
index|]
operator|-
name|coords
index|[
name|Y1
index|]
operator|+
name|coords
index|[
name|Y3
index|]
operator|-
name|coords
index|[
name|Y2
index|]
expr_stmt|;
comment|/*  Is the mapping affine?  */
if|if
condition|(
operator|(
name|dx3
operator|==
literal|0.0
operator|)
operator|&&
operator|(
name|dy3
operator|==
literal|0.0
operator|)
condition|)
block|{
name|matrix
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
name|coords
index|[
name|X1
index|]
operator|-
name|coords
index|[
name|X0
index|]
expr_stmt|;
name|matrix
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
name|coords
index|[
name|X3
index|]
operator|-
name|coords
index|[
name|X1
index|]
expr_stmt|;
name|matrix
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
name|coords
index|[
name|X0
index|]
expr_stmt|;
name|matrix
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|=
name|coords
index|[
name|Y1
index|]
operator|-
name|coords
index|[
name|Y0
index|]
expr_stmt|;
name|matrix
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
name|coords
index|[
name|Y3
index|]
operator|-
name|coords
index|[
name|Y1
index|]
expr_stmt|;
name|matrix
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
name|coords
index|[
name|Y0
index|]
expr_stmt|;
name|matrix
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|=
literal|0.0
expr_stmt|;
name|matrix
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
else|else
block|{
name|det1
operator|=
name|dx3
operator|*
name|dy2
operator|-
name|dy3
operator|*
name|dx2
expr_stmt|;
name|det2
operator|=
name|dx1
operator|*
name|dy2
operator|-
name|dy1
operator|*
name|dx2
expr_stmt|;
name|matrix
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|=
name|det1
operator|/
name|det2
expr_stmt|;
name|det1
operator|=
name|dx1
operator|*
name|dy3
operator|-
name|dy1
operator|*
name|dx3
expr_stmt|;
name|det2
operator|=
name|dx1
operator|*
name|dy2
operator|-
name|dy1
operator|*
name|dx2
expr_stmt|;
name|matrix
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|=
name|det1
operator|/
name|det2
expr_stmt|;
name|matrix
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
name|coords
index|[
name|X1
index|]
operator|-
name|coords
index|[
name|X0
index|]
operator|+
name|matrix
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|*
name|coords
index|[
name|X1
index|]
expr_stmt|;
name|matrix
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
name|coords
index|[
name|X2
index|]
operator|-
name|coords
index|[
name|X0
index|]
operator|+
name|matrix
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|*
name|coords
index|[
name|X2
index|]
expr_stmt|;
name|matrix
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
name|coords
index|[
name|X0
index|]
expr_stmt|;
name|matrix
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|=
name|coords
index|[
name|Y1
index|]
operator|-
name|coords
index|[
name|Y0
index|]
operator|+
name|matrix
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|*
name|coords
index|[
name|Y1
index|]
expr_stmt|;
name|matrix
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
name|coords
index|[
name|Y2
index|]
operator|-
name|coords
index|[
name|Y0
index|]
operator|+
name|matrix
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|*
name|coords
index|[
name|Y2
index|]
expr_stmt|;
name|matrix
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
name|coords
index|[
name|Y0
index|]
expr_stmt|;
block|}
name|matrix
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|=
literal|1.0
expr_stmt|;
block|}
end_function

begin_comment
comment|/* private function definitions */
end_comment

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
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpTransformToolClass
modifier|*
name|trans_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|trans_class
operator|=
operator|(
name|GimpTransformToolClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_TRANSFORM_TOOL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_perspective_tool_destroy
expr_stmt|;
name|trans_class
operator|->
name|transform
operator|=
name|gimp_perspective_tool_transform
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
decl_stmt|;
name|GimpTransformTool
modifier|*
name|tr_tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|perspective_tool
argument_list|)
expr_stmt|;
name|tr_tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|perspective_tool
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|perspective_options
condition|)
block|{
name|perspective_options
operator|=
name|transform_options_new
argument_list|(
name|GIMP_TYPE_PERSPECTIVE_TOOL
argument_list|,
name|transform_options_reset
argument_list|)
expr_stmt|;
name|tool_manager_register_tool_options
argument_list|(
name|GIMP_TYPE_PERSPECTIVE_TOOL
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|perspective_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|->
name|tool_cursor
operator|=
name|GIMP_PERSPECTIVE_TOOL_CURSOR
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
literal|0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
literal|0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
literal|0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
literal|0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X2
index|]
operator|=
literal|0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
operator|=
literal|0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X3
index|]
operator|=
literal|0
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|=
literal|0
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|gimp_matrix3_identity
argument_list|(
name|tr_tool
operator|->
name|transform
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_tool_destroy (GtkObject * object)
name|gimp_perspective_tool_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|TileManager
modifier|*
DECL|function|gimp_perspective_tool_transform (GimpTransformTool * transform_tool,GDisplay * gdisp,TransformState state)
name|gimp_perspective_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|transform_tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|TransformState
name|state
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
name|transform_tool
argument_list|)
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
literal|"Perspective Transform Information"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"tools/transform_perspective.html"
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|transform_info
argument_list|,
name|_
argument_list|(
literal|"Matrix:"
argument_list|)
argument_list|,
name|matrix_row_buf
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|transform_info
argument_list|,
literal|""
argument_list|,
name|matrix_row_buf
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|transform_info
argument_list|,
literal|""
argument_list|,
name|matrix_row_buf
index|[
literal|2
index|]
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
name|transform_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
operator|(
name|double
operator|)
name|transform_tool
operator|->
name|x1
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
operator|(
name|double
operator|)
name|transform_tool
operator|->
name|y1
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
operator|(
name|double
operator|)
name|transform_tool
operator|->
name|x2
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
operator|(
name|double
operator|)
name|transform_tool
operator|->
name|y1
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|X2
index|]
operator|=
operator|(
name|double
operator|)
name|transform_tool
operator|->
name|x1
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
operator|=
operator|(
name|double
operator|)
name|transform_tool
operator|->
name|y2
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|X3
index|]
operator|=
operator|(
name|double
operator|)
name|transform_tool
operator|->
name|x2
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|=
operator|(
name|double
operator|)
name|transform_tool
operator|->
name|y2
expr_stmt|;
return|return
name|NULL
return|;
break|break;
case|case
name|TRANSFORM_MOTION
case|:
name|perspective_tool_motion
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|perspective_tool_recalc
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
name|perspective_tool_recalc
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
comment|/*  Let the transform tool handle the inverse mapping  */
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
name|gimp_perspective_tool_perspective
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
name|transform_tool
operator|->
name|original
argument_list|,
name|gimp_transform_tool_smoothing
argument_list|()
argument_list|,
name|transform_tool
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
specifier|static
name|void
DECL|function|perspective_info_update (GimpTool * tool)
name|perspective_info_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|transform_tool
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|transform_tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
block|{
name|gchar
modifier|*
name|p
init|=
name|matrix_row_buf
index|[
name|i
index|]
decl_stmt|;
name|gint
name|j
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
block|{
name|p
operator|+=
name|g_snprintf
argument_list|(
name|p
argument_list|,
name|MAX_INFO_BUF
operator|-
operator|(
name|p
operator|-
name|matrix_row_buf
index|[
name|i
index|]
operator|)
argument_list|,
literal|"%10.3g"
argument_list|,
name|transform_tool
operator|->
name|transform
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|)
expr_stmt|;
block|}
block|}
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
return|return;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|perspective_tool_motion (GimpTool * tool,GDisplay * gdisp)
name|perspective_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|transform_tool
decl_stmt|;
name|gint
name|diff_x
decl_stmt|,
name|diff_y
decl_stmt|;
name|transform_tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|diff_x
operator|=
name|transform_tool
operator|->
name|curx
operator|-
name|transform_tool
operator|->
name|lastx
expr_stmt|;
name|diff_y
operator|=
name|transform_tool
operator|->
name|cury
operator|-
name|transform_tool
operator|->
name|lasty
expr_stmt|;
switch|switch
condition|(
name|transform_tool
operator|->
name|function
condition|)
block|{
case|case
name|TRANSFORM_HANDLE_1
case|:
name|transform_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_2
case|:
name|transform_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_3
case|:
name|transform_tool
operator|->
name|trans_info
index|[
name|X2
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
case|case
name|TRANSFORM_HANDLE_4
case|:
name|transform_tool
operator|->
name|trans_info
index|[
name|X3
index|]
operator|+=
name|diff_x
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|+=
name|diff_y
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|perspective_tool_recalc (GimpTool * tool,GDisplay * gdisp)
name|perspective_tool_recalc
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|transform_tool
decl_stmt|;
name|GimpMatrix3
name|m
decl_stmt|;
name|gdouble
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|gdouble
name|scalex
decl_stmt|,
name|scaley
decl_stmt|;
name|transform_tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
comment|/*  determine the perspective transform that maps from    *  the unit cube to the trans_info coordinates    */
name|gimp_perspective_tool_find_transform
argument_list|(
name|transform_tool
operator|->
name|trans_info
argument_list|,
name|m
argument_list|)
expr_stmt|;
name|cx
operator|=
name|transform_tool
operator|->
name|x1
expr_stmt|;
name|cy
operator|=
name|transform_tool
operator|->
name|y1
expr_stmt|;
name|scalex
operator|=
literal|1.0
expr_stmt|;
name|scaley
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|transform_tool
operator|->
name|x2
operator|-
name|transform_tool
operator|->
name|x1
condition|)
name|scalex
operator|=
literal|1.0
operator|/
operator|(
name|transform_tool
operator|->
name|x2
operator|-
name|transform_tool
operator|->
name|x1
operator|)
expr_stmt|;
if|if
condition|(
name|transform_tool
operator|->
name|y2
operator|-
name|transform_tool
operator|->
name|y1
condition|)
name|scaley
operator|=
literal|1.0
operator|/
operator|(
name|transform_tool
operator|->
name|y2
operator|-
name|transform_tool
operator|->
name|y1
operator|)
expr_stmt|;
comment|/*  assemble the transformation matrix  */
name|gimp_matrix3_identity
argument_list|(
name|transform_tool
operator|->
name|transform
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|transform_tool
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
name|gimp_matrix3_scale
argument_list|(
name|transform_tool
operator|->
name|transform
argument_list|,
name|scalex
argument_list|,
name|scaley
argument_list|)
expr_stmt|;
name|gimp_matrix3_mult
argument_list|(
name|m
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
name|perspective_info_update
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

