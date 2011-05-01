begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1999 Adrian Likins and Tor Lillqvist  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpipe.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpipe-load.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_brush_pipe_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_brush_pipe_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_pipe_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_pipe_begin_use
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_pipe_end_use
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpBrush
modifier|*
name|gimp_brush_pipe_select_brush
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|current_coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_pipe_want_null_motion
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|current_coords
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpBrushPipe
argument_list|,
name|gimp_brush_pipe
argument_list|,
name|GIMP_TYPE_BRUSH
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_brush_pipe_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_brush_pipe_class_init (GimpBrushPipeClass * klass)
name|gimp_brush_pipe_class_init
parameter_list|(
name|GimpBrushPipeClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpBrushClass
modifier|*
name|brush_class
init|=
name|GIMP_BRUSH_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_brush_pipe_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_brush_pipe_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|get_popup_size
operator|=
name|gimp_brush_pipe_get_popup_size
expr_stmt|;
name|brush_class
operator|->
name|begin_use
operator|=
name|gimp_brush_pipe_begin_use
expr_stmt|;
name|brush_class
operator|->
name|end_use
operator|=
name|gimp_brush_pipe_end_use
expr_stmt|;
name|brush_class
operator|->
name|select_brush
operator|=
name|gimp_brush_pipe_select_brush
expr_stmt|;
name|brush_class
operator|->
name|want_null_motion
operator|=
name|gimp_brush_pipe_want_null_motion
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_pipe_init (GimpBrushPipe * pipe)
name|gimp_brush_pipe_init
parameter_list|(
name|GimpBrushPipe
modifier|*
name|pipe
parameter_list|)
block|{
name|pipe
operator|->
name|current
operator|=
name|NULL
expr_stmt|;
name|pipe
operator|->
name|dimension
operator|=
literal|0
expr_stmt|;
name|pipe
operator|->
name|rank
operator|=
name|NULL
expr_stmt|;
name|pipe
operator|->
name|stride
operator|=
name|NULL
expr_stmt|;
name|pipe
operator|->
name|n_brushes
operator|=
literal|0
expr_stmt|;
name|pipe
operator|->
name|brushes
operator|=
name|NULL
expr_stmt|;
name|pipe
operator|->
name|select
operator|=
name|NULL
expr_stmt|;
name|pipe
operator|->
name|index
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_pipe_finalize (GObject * object)
name|gimp_brush_pipe_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
init|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|pipe
operator|->
name|rank
condition|)
block|{
name|g_free
argument_list|(
name|pipe
operator|->
name|rank
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|rank
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|pipe
operator|->
name|stride
condition|)
block|{
name|g_free
argument_list|(
name|pipe
operator|->
name|stride
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|stride
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|pipe
operator|->
name|brushes
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pipe
operator|->
name|n_brushes
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|pipe
operator|->
name|brushes
index|[
name|i
index|]
condition|)
name|g_object_unref
argument_list|(
name|pipe
operator|->
name|brushes
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pipe
operator|->
name|brushes
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|brushes
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|pipe
operator|->
name|select
condition|)
block|{
name|g_free
argument_list|(
name|pipe
operator|->
name|select
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|select
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|pipe
operator|->
name|index
condition|)
block|{
name|g_free
argument_list|(
name|pipe
operator|->
name|index
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|index
operator|=
name|NULL
expr_stmt|;
block|}
name|GIMP_BRUSH
argument_list|(
name|pipe
argument_list|)
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|pipe
argument_list|)
operator|->
name|pixmap
operator|=
name|NULL
expr_stmt|;
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
name|gint64
DECL|function|gimp_brush_pipe_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_brush_pipe_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
init|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|memsize
operator|+=
name|pipe
operator|->
name|dimension
operator|*
operator|(
sizeof|sizeof
argument_list|(
name|gint
argument_list|)
comment|/* rank   */
operator|+
sizeof|sizeof
argument_list|(
name|gint
argument_list|)
comment|/* stride */
operator|+
sizeof|sizeof
argument_list|(
name|PipeSelectModes
argument_list|)
operator|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pipe
operator|->
name|n_brushes
condition|;
name|i
operator|++
control|)
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|pipe
operator|->
name|brushes
index|[
name|i
index|]
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_brush_pipe_get_popup_size (GimpViewable * viewable,gint width,gint height,gboolean dot_for_dot,gint * popup_width,gint * popup_height)
name|gimp_brush_pipe_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
block|{
return|return
name|gimp_viewable_get_size
argument_list|(
name|viewable
argument_list|,
name|popup_width
argument_list|,
name|popup_height
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_pipe_begin_use (GimpBrush * brush)
name|gimp_brush_pipe_begin_use
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
init|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|brush
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GIMP_BRUSH_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|begin_use
argument_list|(
name|brush
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
name|pipe
operator|->
name|n_brushes
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|pipe
operator|->
name|brushes
index|[
name|i
index|]
condition|)
name|gimp_brush_begin_use
argument_list|(
name|pipe
operator|->
name|brushes
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_pipe_end_use (GimpBrush * brush)
name|gimp_brush_pipe_end_use
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
init|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|brush
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GIMP_BRUSH_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|end_use
argument_list|(
name|brush
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
name|pipe
operator|->
name|n_brushes
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|pipe
operator|->
name|brushes
index|[
name|i
index|]
condition|)
name|gimp_brush_end_use
argument_list|(
name|pipe
operator|->
name|brushes
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpBrush
modifier|*
DECL|function|gimp_brush_pipe_select_brush (GimpBrush * brush,const GimpCoords * last_coords,const GimpCoords * current_coords)
name|gimp_brush_pipe_select_brush
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|current_coords
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
init|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|brush
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|brushix
decl_stmt|,
name|ix
decl_stmt|;
name|gdouble
name|velocity
decl_stmt|;
if|if
condition|(
name|pipe
operator|->
name|n_brushes
operator|==
literal|1
condition|)
return|return
name|GIMP_BRUSH
argument_list|(
name|pipe
operator|->
name|current
argument_list|)
return|;
name|brushix
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pipe
operator|->
name|dimension
condition|;
name|i
operator|++
control|)
block|{
switch|switch
condition|(
name|pipe
operator|->
name|select
index|[
name|i
index|]
condition|)
block|{
case|case
name|PIPE_SELECT_INCREMENTAL
case|:
name|ix
operator|=
operator|(
name|pipe
operator|->
name|index
index|[
name|i
index|]
operator|+
literal|1
operator|)
operator|%
name|pipe
operator|->
name|rank
index|[
name|i
index|]
expr_stmt|;
break|break;
case|case
name|PIPE_SELECT_ANGULAR
case|:
comment|/* Coords angle is already nomalized,            * offset by 90 degrees is still needed            * because hoses were made PS compatible*/
name|ix
operator|=
operator|(
name|gint
operator|)
name|RINT
argument_list|(
operator|(
literal|1.0
operator|-
name|current_coords
operator|->
name|direction
operator|+
literal|0.25
operator|)
operator|*
name|pipe
operator|->
name|rank
index|[
name|i
index|]
argument_list|)
operator|%
name|pipe
operator|->
name|rank
index|[
name|i
index|]
expr_stmt|;
break|break;
case|case
name|PIPE_SELECT_VELOCITY
case|:
name|velocity
operator|=
name|current_coords
operator|->
name|velocity
expr_stmt|;
comment|/* Max velocity is 3.0, picking stamp as a ratio*/
name|ix
operator|=
name|ROUND
argument_list|(
operator|(
literal|3.0
operator|/
name|velocity
operator|)
operator|*
name|pipe
operator|->
name|rank
index|[
name|i
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PIPE_SELECT_RANDOM
case|:
comment|/* This probably isn't the right way */
name|ix
operator|=
name|g_random_int_range
argument_list|(
literal|0
argument_list|,
name|pipe
operator|->
name|rank
index|[
name|i
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PIPE_SELECT_PRESSURE
case|:
name|ix
operator|=
name|RINT
argument_list|(
name|current_coords
operator|->
name|pressure
operator|*
operator|(
name|pipe
operator|->
name|rank
index|[
name|i
index|]
operator|-
literal|1
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PIPE_SELECT_TILT_X
case|:
name|ix
operator|=
name|RINT
argument_list|(
name|current_coords
operator|->
name|xtilt
operator|/
literal|2.0
operator|*
name|pipe
operator|->
name|rank
index|[
name|i
index|]
argument_list|)
operator|+
name|pipe
operator|->
name|rank
index|[
name|i
index|]
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|PIPE_SELECT_TILT_Y
case|:
name|ix
operator|=
name|RINT
argument_list|(
name|current_coords
operator|->
name|ytilt
operator|/
literal|2.0
operator|*
name|pipe
operator|->
name|rank
index|[
name|i
index|]
argument_list|)
operator|+
name|pipe
operator|->
name|rank
index|[
name|i
index|]
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|PIPE_SELECT_CONSTANT
case|:
default|default:
name|ix
operator|=
name|pipe
operator|->
name|index
index|[
name|i
index|]
expr_stmt|;
break|break;
block|}
name|pipe
operator|->
name|index
index|[
name|i
index|]
operator|=
name|CLAMP
argument_list|(
name|ix
argument_list|,
literal|0
argument_list|,
name|pipe
operator|->
name|rank
index|[
name|i
index|]
operator|-
literal|1
argument_list|)
expr_stmt|;
name|brushix
operator|+=
name|pipe
operator|->
name|stride
index|[
name|i
index|]
operator|*
name|pipe
operator|->
name|index
index|[
name|i
index|]
expr_stmt|;
block|}
comment|/* Make sure is inside bounds */
name|brushix
operator|=
name|CLAMP
argument_list|(
name|brushix
argument_list|,
literal|0
argument_list|,
name|pipe
operator|->
name|n_brushes
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|current
operator|=
name|pipe
operator|->
name|brushes
index|[
name|brushix
index|]
expr_stmt|;
return|return
name|GIMP_BRUSH
argument_list|(
name|pipe
operator|->
name|current
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_brush_pipe_want_null_motion (GimpBrush * brush,const GimpCoords * last_coords,const GimpCoords * current_coords)
name|gimp_brush_pipe_want_null_motion
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|current_coords
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
init|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|brush
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|pipe
operator|->
name|n_brushes
operator|==
literal|1
condition|)
return|return
name|TRUE
return|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pipe
operator|->
name|dimension
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|pipe
operator|->
name|select
index|[
name|i
index|]
operator|==
name|PIPE_SELECT_ANGULAR
condition|)
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

