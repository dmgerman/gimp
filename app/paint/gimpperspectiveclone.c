begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimperror.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-transform-region.h"
end_include

begin_include
include|#
directive|include
file|"gimpperspectiveclone.h"
end_include

begin_include
include|#
directive|include
file|"gimpperspectivecloneoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|MIN4 (a,b,c,d)
define|#
directive|define
name|MIN4
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|,
name|d
parameter_list|)
value|MIN(MIN(a,b),MIN(c,d))
end_define

begin_define
DECL|macro|MAX4 (a,b,c,d)
define|#
directive|define
name|MAX4
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|,
name|d
parameter_list|)
value|MAX(MAX(a,b),MAX(c,d))
end_define

begin_function_decl
specifier|static
name|void
name|gimp_perspective_clone_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_perspective_clone_start
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_clone_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_perspective_clone_get_source
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|TempBuf
modifier|*
name|paint_area
parameter_list|,
name|gint
modifier|*
name|paint_area_offset_x
parameter_list|,
name|gint
modifier|*
name|paint_area_offset_y
parameter_list|,
name|gint
modifier|*
name|paint_area_width
parameter_list|,
name|gint
modifier|*
name|paint_area_height
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_perspective_clone_get_matrix
parameter_list|(
name|GimpPerspectiveClone
modifier|*
name|clone
parameter_list|,
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPerspectiveClone,gimp_perspective_clone,GIMP_TYPE_CLONE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPerspectiveClone
argument_list|,
argument|gimp_perspective_clone
argument_list|,
argument|GIMP_TYPE_CLONE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_perspective_clone_parent_class
end_define

begin_function
name|void
name|gimp_perspective_clone_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_PERSPECTIVE_CLONE
argument_list|,
name|GIMP_TYPE_PERSPECTIVE_CLONE_OPTIONS
argument_list|,
literal|"gimp-perspective-clone"
argument_list|,
name|_
argument_list|(
literal|"Perspective Clone"
argument_list|)
argument_list|,
literal|"gimp-tool-perspective-clone"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_clone_class_init (GimpPerspectiveCloneClass * klass)
name|gimp_perspective_clone_class_init
parameter_list|(
name|GimpPerspectiveCloneClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
init|=
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpSourceCoreClass
modifier|*
name|source_core_class
init|=
name|GIMP_SOURCE_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_perspective_clone_finalize
expr_stmt|;
name|paint_core_class
operator|->
name|start
operator|=
name|gimp_perspective_clone_start
expr_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_perspective_clone_paint
expr_stmt|;
name|source_core_class
operator|->
name|get_source
operator|=
name|gimp_perspective_clone_get_source
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_clone_init (GimpPerspectiveClone * clone)
name|gimp_perspective_clone_init
parameter_list|(
name|GimpPerspectiveClone
modifier|*
name|clone
parameter_list|)
block|{
name|clone
operator|->
name|src_x_fv
operator|=
literal|0.0
expr_stmt|;
comment|/* source coords in front_view perspective */
name|clone
operator|->
name|src_y_fv
operator|=
literal|0.0
expr_stmt|;
name|clone
operator|->
name|dest_x_fv
operator|=
literal|0.0
expr_stmt|;
comment|/* destination coords in front_view perspective */
name|clone
operator|->
name|dest_y_fv
operator|=
literal|0.0
expr_stmt|;
name|gimp_matrix3_identity
argument_list|(
operator|&
name|clone
operator|->
name|transform
argument_list|)
expr_stmt|;
name|gimp_matrix3_identity
argument_list|(
operator|&
name|clone
operator|->
name|transform_inv
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_clone_finalize (GObject * object)
name|gimp_perspective_clone_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPerspectiveClone
modifier|*
name|clone
init|=
name|GIMP_PERSPECTIVE_CLONE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|clone
operator|->
name|src_area
condition|)
block|{
name|temp_buf_free
argument_list|(
name|clone
operator|->
name|src_area
argument_list|)
expr_stmt|;
name|clone
operator|->
name|src_area
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_perspective_clone_start (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GError ** error)
name|gimp_perspective_clone_start
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpSourceCore
modifier|*
name|source_core
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|start
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|,
name|error
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
if|if
condition|(
operator|!
name|source_core
operator|->
name|set_source
operator|&&
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Perspective Clone does not operate on "
literal|"indexed layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_clone_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GimpPaintState paint_state,guint32 time)
name|gimp_perspective_clone_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|GimpSourceCore
modifier|*
name|source_core
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpPerspectiveClone
modifier|*
name|clone
init|=
name|GIMP_PERSPECTIVE_CLONE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpSourceOptions
modifier|*
name|options
init|=
name|GIMP_SOURCE_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|GIMP_PAINT_STATE_INIT
case|:
if|if
condition|(
name|source_core
operator|->
name|set_source
condition|)
block|{
name|g_object_set
argument_list|(
name|source_core
argument_list|,
literal|"src-drawable"
argument_list|,
name|drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|source_core
operator|->
name|src_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|source_core
operator|->
name|src_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
comment|/* get source coordinates in front view perspective */
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|clone
operator|->
name|transform_inv
argument_list|,
name|source_core
operator|->
name|src_x
argument_list|,
name|source_core
operator|->
name|src_y
argument_list|,
operator|&
name|clone
operator|->
name|src_x_fv
argument_list|,
operator|&
name|clone
operator|->
name|src_y_fv
argument_list|)
expr_stmt|;
name|source_core
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|align_mode
operator|==
name|GIMP_SOURCE_ALIGN_NO
condition|)
block|{
name|source_core
operator|->
name|orig_src_x
operator|=
name|source_core
operator|->
name|src_x
expr_stmt|;
name|source_core
operator|->
name|orig_src_y
operator|=
name|source_core
operator|->
name|src_y
expr_stmt|;
name|source_core
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
if|if
condition|(
name|source_core
operator|->
name|set_source
condition|)
block|{
comment|/*  If the control key is down, move the src target and return */
name|source_core
operator|->
name|src_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|source_core
operator|->
name|src_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
comment|/* get source coordinates in front view perspective */
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|clone
operator|->
name|transform_inv
argument_list|,
name|source_core
operator|->
name|src_x
argument_list|,
name|source_core
operator|->
name|src_y
argument_list|,
operator|&
name|clone
operator|->
name|src_x_fv
argument_list|,
operator|&
name|clone
operator|->
name|src_y_fv
argument_list|)
expr_stmt|;
name|source_core
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
comment|/*  otherwise, update the target  */
name|gint
name|dest_x
decl_stmt|;
name|gint
name|dest_y
decl_stmt|;
name|dest_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|dest_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|align_mode
operator|==
name|GIMP_SOURCE_ALIGN_REGISTERED
condition|)
block|{
name|source_core
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|source_core
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|align_mode
operator|==
name|GIMP_SOURCE_ALIGN_FIXED
condition|)
block|{
name|source_core
operator|->
name|offset_x
operator|=
name|source_core
operator|->
name|src_x
operator|-
name|dest_x
expr_stmt|;
name|source_core
operator|->
name|offset_y
operator|=
name|source_core
operator|->
name|src_y
operator|-
name|dest_y
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|source_core
operator|->
name|first_stroke
condition|)
block|{
name|source_core
operator|->
name|offset_x
operator|=
name|source_core
operator|->
name|src_x
operator|-
name|dest_x
expr_stmt|;
name|source_core
operator|->
name|offset_y
operator|=
name|source_core
operator|->
name|src_y
operator|-
name|dest_y
expr_stmt|;
comment|/* get destination coordinates in front view perspective */
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|clone
operator|->
name|transform_inv
argument_list|,
name|dest_x
argument_list|,
name|dest_y
argument_list|,
operator|&
name|clone
operator|->
name|dest_x_fv
argument_list|,
operator|&
name|clone
operator|->
name|dest_y_fv
argument_list|)
expr_stmt|;
name|source_core
operator|->
name|first_stroke
operator|=
name|FALSE
expr_stmt|;
block|}
name|gimp_source_core_motion
argument_list|(
name|source_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PAINT_STATE_FINISH
case|:
break|break;
default|default:
break|break;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|clone
argument_list|)
argument_list|,
literal|"src-x"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|clone
argument_list|)
argument_list|,
literal|"src-y"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_perspective_clone_get_source (GimpSourceCore * source_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPickable * src_pickable,gint src_offset_x,gint src_offset_y,TempBuf * paint_area,gint * paint_area_offset_x,gint * paint_area_offset_y,gint * paint_area_width,gint * paint_area_height,PixelRegion * srcPR)
name|gimp_perspective_clone_get_source
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|TempBuf
modifier|*
name|paint_area
parameter_list|,
name|gint
modifier|*
name|paint_area_offset_x
parameter_list|,
name|gint
modifier|*
name|paint_area_offset_y
parameter_list|,
name|gint
modifier|*
name|paint_area_width
parameter_list|,
name|gint
modifier|*
name|paint_area_height
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|)
block|{
name|GimpPerspectiveClone
modifier|*
name|clone
init|=
name|GIMP_PERSPECTIVE_CLONE
argument_list|(
name|source_core
argument_list|)
decl_stmt|;
name|GimpPaintCore
modifier|*
name|paint_core
init|=
name|GIMP_PAINT_CORE
argument_list|(
name|source_core
argument_list|)
decl_stmt|;
name|GimpSourceOptions
modifier|*
name|options
init|=
name|GIMP_SOURCE_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|src_image
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpImageType
name|src_type
decl_stmt|;
name|gint
name|x1d
decl_stmt|,
name|y1d
decl_stmt|,
name|x2d
decl_stmt|,
name|y2d
decl_stmt|;
name|gdouble
name|x1s
decl_stmt|,
name|y1s
decl_stmt|,
name|x2s
decl_stmt|,
name|y2s
decl_stmt|,
name|x3s
decl_stmt|,
name|y3s
decl_stmt|,
name|x4s
decl_stmt|,
name|y4s
decl_stmt|;
name|gint
name|xmin
decl_stmt|,
name|ymin
decl_stmt|,
name|xmax
decl_stmt|,
name|ymax
decl_stmt|;
name|TileManager
modifier|*
name|src_tiles
decl_stmt|;
name|TileManager
modifier|*
name|orig_tiles
decl_stmt|;
name|PixelRegion
name|origPR
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|src_image
operator|=
name|gimp_pickable_get_image
argument_list|(
name|src_pickable
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|src_type
operator|=
name|gimp_pickable_get_image_type
argument_list|(
name|src_pickable
argument_list|)
expr_stmt|;
name|src_tiles
operator|=
name|gimp_pickable_get_tiles
argument_list|(
name|src_pickable
argument_list|)
expr_stmt|;
comment|/* Destination coordinates that will be painted */
name|x1d
operator|=
name|paint_area
operator|->
name|x
expr_stmt|;
name|y1d
operator|=
name|paint_area
operator|->
name|y
expr_stmt|;
name|x2d
operator|=
name|paint_area
operator|->
name|x
operator|+
name|paint_area
operator|->
name|width
expr_stmt|;
name|y2d
operator|=
name|paint_area
operator|->
name|y
operator|+
name|paint_area
operator|->
name|height
expr_stmt|;
comment|/* Boundary box for source pixels to copy: Convert all the vertex of    * the box to paint in destination area to its correspondent in    * source area bearing in mind perspective    */
name|gimp_perspective_clone_get_source_point
argument_list|(
name|clone
argument_list|,
name|x1d
argument_list|,
name|y1d
argument_list|,
operator|&
name|x1s
argument_list|,
operator|&
name|y1s
argument_list|)
expr_stmt|;
name|gimp_perspective_clone_get_source_point
argument_list|(
name|clone
argument_list|,
name|x1d
argument_list|,
name|y2d
argument_list|,
operator|&
name|x2s
argument_list|,
operator|&
name|y2s
argument_list|)
expr_stmt|;
name|gimp_perspective_clone_get_source_point
argument_list|(
name|clone
argument_list|,
name|x2d
argument_list|,
name|y1d
argument_list|,
operator|&
name|x3s
argument_list|,
operator|&
name|y3s
argument_list|)
expr_stmt|;
name|gimp_perspective_clone_get_source_point
argument_list|(
name|clone
argument_list|,
name|x2d
argument_list|,
name|y2d
argument_list|,
operator|&
name|x4s
argument_list|,
operator|&
name|y4s
argument_list|)
expr_stmt|;
name|xmin
operator|=
name|floor
argument_list|(
name|MIN4
argument_list|(
name|x1s
argument_list|,
name|x2s
argument_list|,
name|x3s
argument_list|,
name|x4s
argument_list|)
argument_list|)
expr_stmt|;
name|ymin
operator|=
name|floor
argument_list|(
name|MIN4
argument_list|(
name|y1s
argument_list|,
name|y2s
argument_list|,
name|y3s
argument_list|,
name|y4s
argument_list|)
argument_list|)
expr_stmt|;
name|xmax
operator|=
name|ceil
argument_list|(
name|MAX4
argument_list|(
name|x1s
argument_list|,
name|x2s
argument_list|,
name|x3s
argument_list|,
name|x4s
argument_list|)
argument_list|)
expr_stmt|;
name|ymax
operator|=
name|ceil
argument_list|(
name|MAX4
argument_list|(
name|y1s
argument_list|,
name|y2s
argument_list|,
name|y3s
argument_list|,
name|y4s
argument_list|)
argument_list|)
expr_stmt|;
name|xmin
operator|=
name|CLAMP
argument_list|(
name|xmin
operator|-
literal|1
argument_list|,
literal|0
argument_list|,
name|tile_manager_width
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
name|ymin
operator|=
name|CLAMP
argument_list|(
name|ymin
operator|-
literal|1
argument_list|,
literal|0
argument_list|,
name|tile_manager_height
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
name|xmax
operator|=
name|CLAMP
argument_list|(
name|xmax
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
name|tile_manager_width
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
name|ymax
operator|=
name|CLAMP
argument_list|(
name|ymax
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
name|tile_manager_height
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
comment|/* if the source area is completely out of the image */
if|if
condition|(
operator|!
operator|(
name|xmax
operator|-
name|xmin
operator|)
operator|||
operator|!
operator|(
name|ymax
operator|-
name|ymin
operator|)
condition|)
return|return
name|FALSE
return|;
comment|/*  If the source image is different from the destination,    *  then we should copy straight from the source image    *  to the canvas.    *  Otherwise, we need a call to get_orig_image to make sure    *  we get a copy of the unblemished (offset) image    */
if|if
condition|(
operator|(
name|options
operator|->
name|sample_merged
operator|&&
operator|(
name|src_image
operator|!=
name|image
operator|)
operator|)
operator|||
operator|(
operator|!
name|options
operator|->
name|sample_merged
operator|&&
operator|(
name|source_core
operator|->
name|src_drawable
operator|!=
name|drawable
operator|)
operator|)
condition|)
block|{
name|pixel_region_init
argument_list|(
operator|&
name|origPR
argument_list|,
name|src_tiles
argument_list|,
name|xmin
argument_list|,
name|ymin
argument_list|,
name|xmax
operator|-
name|xmin
argument_list|,
name|ymax
operator|-
name|ymin
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|TempBuf
modifier|*
name|orig
decl_stmt|;
comment|/*  get the original image  */
if|if
condition|(
name|options
operator|->
name|sample_merged
condition|)
name|orig
operator|=
name|gimp_paint_core_get_orig_proj
argument_list|(
name|paint_core
argument_list|,
name|src_pickable
argument_list|,
name|xmin
argument_list|,
name|ymin
argument_list|,
name|xmax
argument_list|,
name|ymax
argument_list|)
expr_stmt|;
else|else
name|orig
operator|=
name|gimp_paint_core_get_orig_image
argument_list|(
name|paint_core
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|src_pickable
argument_list|)
argument_list|,
name|xmin
argument_list|,
name|ymin
argument_list|,
name|xmax
argument_list|,
name|ymax
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|origPR
argument_list|,
name|orig
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|xmax
operator|-
name|xmin
argument_list|,
name|ymax
operator|-
name|ymin
argument_list|)
expr_stmt|;
block|}
comment|/*  copy the original image to a tile manager, adding alpha if needed  */
name|bytes
operator|=
name|GIMP_IMAGE_TYPE_BYTES
argument_list|(
name|GIMP_IMAGE_TYPE_WITH_ALPHA
argument_list|(
name|src_type
argument_list|)
argument_list|)
expr_stmt|;
name|orig_tiles
operator|=
name|tile_manager_new
argument_list|(
name|xmax
operator|-
name|xmin
argument_list|,
name|ymax
operator|-
name|ymin
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|tile_manager_set_offsets
argument_list|(
name|orig_tiles
argument_list|,
name|xmin
argument_list|,
name|ymin
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|orig_tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|xmax
operator|-
name|xmin
argument_list|,
name|ymax
operator|-
name|ymin
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|bytes
operator|>
name|origPR
operator|.
name|bytes
condition|)
name|add_alpha_region
argument_list|(
operator|&
name|origPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
else|else
name|copy_region
argument_list|(
operator|&
name|origPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|clone
operator|->
name|src_area
operator|=
name|temp_buf_resize
argument_list|(
name|clone
operator|->
name|src_area
argument_list|,
name|tile_manager_bpp
argument_list|(
name|orig_tiles
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2d
operator|-
name|x1d
argument_list|,
name|y2d
operator|-
name|y1d
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|destPR
argument_list|,
name|clone
operator|->
name|src_area
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2d
operator|-
name|x1d
argument_list|,
name|y2d
operator|-
name|y1d
argument_list|)
expr_stmt|;
name|gimp_perspective_clone_get_matrix
argument_list|(
name|clone
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|gimp_transform_region
argument_list|(
name|src_pickable
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|orig_tiles
argument_list|,
operator|&
name|destPR
argument_list|,
name|x1d
argument_list|,
name|y1d
argument_list|,
name|x2d
argument_list|,
name|y2d
argument_list|,
operator|&
name|matrix
argument_list|,
name|GIMP_INTERPOLATION_LINEAR
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|orig_tiles
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
name|srcPR
argument_list|,
name|clone
operator|->
name|src_area
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2d
operator|-
name|x1d
argument_list|,
name|y2d
operator|-
name|y1d
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_perspective_clone_set_transform (GimpPerspectiveClone * clone,GimpMatrix3 * transform)
name|gimp_perspective_clone_set_transform
parameter_list|(
name|GimpPerspectiveClone
modifier|*
name|clone
parameter_list|,
name|GimpMatrix3
modifier|*
name|transform
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PERSPECTIVE_CLONE
argument_list|(
name|clone
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|transform
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|clone
operator|->
name|transform
operator|=
operator|*
name|transform
expr_stmt|;
name|clone
operator|->
name|transform_inv
operator|=
name|clone
operator|->
name|transform
expr_stmt|;
name|gimp_matrix3_invert
argument_list|(
operator|&
name|clone
operator|->
name|transform_inv
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|g_printerr ("%f\t%f\t%f\n%f\t%f\t%f\n%f\t%f\t%f\n\n",               clone->transform.coeff[0][0],               clone->transform.coeff[0][1],               clone->transform.coeff[0][2],               clone->transform.coeff[1][0],               clone->transform.coeff[1][1],               clone->transform.coeff[1][2],               clone->transform.coeff[2][0],               clone->transform.coeff[2][1],               clone->transform.coeff[2][2]);
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|gimp_perspective_clone_get_source_point (GimpPerspectiveClone * clone,gdouble x,gdouble y,gdouble * newx,gdouble * newy)
name|gimp_perspective_clone_get_source_point
parameter_list|(
name|GimpPerspectiveClone
modifier|*
name|clone
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|newx
parameter_list|,
name|gdouble
modifier|*
name|newy
parameter_list|)
block|{
name|gdouble
name|temp_x
decl_stmt|,
name|temp_y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PERSPECTIVE_CLONE
argument_list|(
name|clone
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|newx
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|newy
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|clone
operator|->
name|transform_inv
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|temp_x
argument_list|,
operator|&
name|temp_y
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
comment|/* Get the offset of each pixel in destination area from the    * destination pixel in front view perspective    */
block|offset_x_fv = temp_x - clone->dest_x_fv;   offset_y_fv = temp_y - clone->dest_y_fv;
comment|/* Get the source pixel in front view perspective */
block|temp_x = offset_x_fv + clone->src_x_fv;   temp_y = offset_y_fv + clone->src_y_fv;
endif|#
directive|endif
name|temp_x
operator|+=
name|clone
operator|->
name|src_x_fv
operator|-
name|clone
operator|->
name|dest_x_fv
expr_stmt|;
name|temp_y
operator|+=
name|clone
operator|->
name|src_y_fv
operator|-
name|clone
operator|->
name|dest_y_fv
expr_stmt|;
comment|/* Convert the source pixel to perspective view */
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|clone
operator|->
name|transform
argument_list|,
name|temp_x
argument_list|,
name|temp_y
argument_list|,
name|newx
argument_list|,
name|newy
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_perspective_clone_get_matrix (GimpPerspectiveClone * clone,GimpMatrix3 * matrix)
name|gimp_perspective_clone_get_matrix
parameter_list|(
name|GimpPerspectiveClone
modifier|*
name|clone
parameter_list|,
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
name|GimpMatrix3
name|temp
decl_stmt|;
name|gimp_matrix3_identity
argument_list|(
operator|&
name|temp
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
operator|&
name|temp
argument_list|,
name|clone
operator|->
name|dest_x_fv
operator|-
name|clone
operator|->
name|src_x_fv
argument_list|,
name|clone
operator|->
name|dest_y_fv
operator|-
name|clone
operator|->
name|src_y_fv
argument_list|)
expr_stmt|;
operator|*
name|matrix
operator|=
name|clone
operator|->
name|transform_inv
expr_stmt|;
name|gimp_matrix3_mult
argument_list|(
operator|&
name|temp
argument_list|,
name|matrix
argument_list|)
expr_stmt|;
name|gimp_matrix3_mult
argument_list|(
operator|&
name|clone
operator|->
name|transform
argument_list|,
name|matrix
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

