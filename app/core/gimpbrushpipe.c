begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1999 Adrian Likins and Tor Lillqvist  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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
file|<ctype.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"brush_header.h"
end_include

begin_include
include|#
directive|include
file|"pattern_header.h"
end_include

begin_include
include|#
directive|include
file|"patterns.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpipe.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpipeP.h"
end_include

begin_include
include|#
directive|include
file|"paint_core.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/parasiteio.h"
end_include

begin_decl_stmt
DECL|variable|gimp_brush_class
specifier|static
name|GimpBrushClass
modifier|*
name|gimp_brush_class
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_brush_pixmap_class
specifier|static
name|GimpBrushPixmapClass
modifier|*
name|gimp_brush_pixmap_class
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|GimpBrush
modifier|*
name|gimp_brush_pixmap_select_brush
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_pixmap_want_null_motion
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|gimp_brush_pixmap_destroy (GtkObject * object)
name|gimp_brush_pixmap_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrushPixmap
modifier|*
name|pixmap
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH_PIXMAP
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|GIMP_BRUSH_PIXMAP
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|pixmap
operator|->
name|pixmap_mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|gimp_brush_class
argument_list|)
operator|->
name|destroy
condition|)
operator|(
operator|*
name|GTK_OBJECT_CLASS
argument_list|(
name|gimp_brush_class
argument_list|)
operator|->
name|destroy
operator|)
operator|(
name|object
operator|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_pixmap_class_init (GimpBrushPixmapClass * klass)
name|gimp_brush_pixmap_class_init
parameter_list|(
name|GimpBrushPixmapClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpBrushClass
modifier|*
name|brush_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|brush_class
operator|=
name|GIMP_BRUSH_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_brush_class
operator|=
name|gtk_type_class
argument_list|(
name|gimp_brush_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_brush_pixmap_destroy
expr_stmt|;
name|brush_class
operator|->
name|select_brush
operator|=
name|gimp_brush_pixmap_select_brush
expr_stmt|;
name|brush_class
operator|->
name|want_null_motion
operator|=
name|gimp_brush_pixmap_want_null_motion
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_pixmap_init (GimpBrushPixmap * brush)
name|gimp_brush_pixmap_init
parameter_list|(
name|GimpBrushPixmap
modifier|*
name|brush
parameter_list|)
block|{
name|brush
operator|->
name|pixmap_mask
operator|=
name|NULL
expr_stmt|;
name|brush
operator|->
name|pipe
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_brush_pixmap_get_type (void)
name|gimp_brush_pixmap_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
name|GtkTypeInfo
name|info
init|=
block|{
literal|"GimpBrushPixmap"
block|,
sizeof|sizeof
argument_list|(
name|GimpBrushPixmap
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpBrushPixmapClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_brush_pixmap_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_brush_pixmap_init
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
block|}
decl_stmt|;
name|type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_BRUSH
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|GimpBrush
modifier|*
DECL|function|gimp_brush_pixmap_select_brush (PaintCore * paint_core)
name|gimp_brush_pixmap_select_brush
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
decl_stmt|;
name|int
name|i
decl_stmt|,
name|brushix
decl_stmt|,
name|ix
decl_stmt|;
name|double
name|angle
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_PIXMAP
argument_list|(
name|paint_core
operator|->
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pipe
operator|=
name|GIMP_BRUSH_PIXMAP
argument_list|(
name|paint_core
operator|->
name|brush
argument_list|)
operator|->
name|pipe
expr_stmt|;
if|if
condition|(
name|pipe
operator|->
name|nbrushes
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
name|angle
operator|=
name|atan2
argument_list|(
name|paint_core
operator|->
name|cury
operator|-
name|paint_core
operator|->
name|lasty
argument_list|,
name|paint_core
operator|->
name|curx
operator|-
name|paint_core
operator|->
name|lastx
argument_list|)
expr_stmt|;
comment|/* Offset angle to be compatible with PSP tubes */
name|angle
operator|+=
name|G_PI_2
expr_stmt|;
comment|/* Map it to the [0..2*G_PI) interval */
if|if
condition|(
name|angle
operator|<
literal|0
condition|)
name|angle
operator|+=
literal|2.
operator|*
name|G_PI
expr_stmt|;
elseif|else
if|if
condition|(
name|angle
operator|>
literal|2.
operator|*
name|G_PI
condition|)
name|angle
operator|-=
literal|2.
operator|*
name|G_PI
expr_stmt|;
name|ix
operator|=
name|RINT
argument_list|(
name|angle
operator|/
operator|(
literal|2.
operator|*
name|G_PI
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
name|rand
argument_list|()
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
name|PIPE_SELECT_PRESSURE
case|:
name|ix
operator|=
name|RINT
argument_list|(
name|paint_core
operator|->
name|curpressure
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
name|paint_core
operator|->
name|curxtilt
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
name|paint_core
operator|->
name|curytilt
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
comment|/* g_print ("ix at %d: %d, brushix: %d\n", i, ix, brushix); */
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
name|nbrushes
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
DECL|function|gimp_brush_pixmap_want_null_motion (PaintCore * paint_core)
name|gimp_brush_pixmap_want_null_motion
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
decl_stmt|;
name|int
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_PIXMAP
argument_list|(
name|paint_core
operator|->
name|brush
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pipe
operator|=
name|GIMP_BRUSH_PIXMAP
argument_list|(
name|paint_core
operator|->
name|brush
argument_list|)
operator|->
name|pipe
expr_stmt|;
if|if
condition|(
name|pipe
operator|->
name|nbrushes
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

begin_function
specifier|static
name|void
DECL|function|gimp_brush_pipe_destroy (GtkObject * object)
name|gimp_brush_pipe_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|object
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH_PIPE
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|pipe
operator|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pipe
operator|->
name|rank
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pipe
operator|->
name|stride
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|pipe
operator|->
name|nbrushes
condition|;
name|i
operator|++
control|)
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pipe
operator|->
name|brushes
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pipe
operator|->
name|brushes
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pipe
operator|->
name|select
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pipe
operator|->
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|gimp_brush_pixmap_class
argument_list|)
operator|->
name|destroy
condition|)
operator|(
operator|*
name|GTK_OBJECT_CLASS
argument_list|(
name|gimp_brush_pixmap_class
argument_list|)
operator|->
name|destroy
operator|)
operator|(
name|object
operator|)
expr_stmt|;
block|}
end_function

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
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_brush_pixmap_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_BRUSH_PIXMAP
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_brush_pipe_destroy
expr_stmt|;
block|}
end_function

begin_function
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
name|nbrushes
operator|=
literal|0
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
name|GtkType
DECL|function|gimp_brush_pipe_get_type (void)
name|gimp_brush_pipe_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
name|GtkTypeInfo
name|info
init|=
block|{
literal|"GimpBrushPipe"
block|,
sizeof|sizeof
argument_list|(
name|GimpBrushPipe
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpBrushPipeClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_brush_pipe_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_brush_pipe_init
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
block|}
decl_stmt|;
name|type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_BRUSH_PIXMAP
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GimpBrushPipe
modifier|*
DECL|function|gimp_brush_pipe_load (gchar * filename)
name|gimp_brush_pipe_load
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
decl_stmt|;
name|GPattern
modifier|*
name|pattern
decl_stmt|;
name|PixPipeParams
name|params
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gchar
name|buf
index|[
literal|1024
index|]
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|num_of_brushes
decl_stmt|;
name|gint
name|totalcells
decl_stmt|;
name|gchar
modifier|*
name|paramstring
decl_stmt|;
if|if
condition|(
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
operator|)
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
comment|/* The file format starts with a painfully simple text header    * and we use a painfully simple way to read it    */
if|if
condition|(
name|fgets
argument_list|(
name|buf
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
operator|==
name|NULL
condition|)
block|{
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|buf
index|[
name|strlen
argument_list|(
name|buf
argument_list|)
operator|-
literal|1
index|]
operator|=
literal|0
expr_stmt|;
name|pipe
operator|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|gimp_type_new
argument_list|(
name|GIMP_TYPE_BRUSH_PIPE
argument_list|)
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup
argument_list|(
name|buf
argument_list|)
expr_stmt|;
comment|/* get the number of brushes */
if|if
condition|(
name|fgets
argument_list|(
name|buf
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
operator|==
name|NULL
condition|)
block|{
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|gimp_object_destroy
argument_list|(
name|pipe
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|num_of_brushes
operator|=
name|strtol
argument_list|(
name|buf
argument_list|,
operator|&
name|paramstring
argument_list|,
literal|10
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_of_brushes
operator|<
literal|1
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Brush pipes should have at least one brush."
argument_list|)
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|gimp_object_destroy
argument_list|(
name|pipe
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
while|while
condition|(
operator|*
name|paramstring
operator|&&
name|isspace
argument_list|(
operator|*
name|paramstring
argument_list|)
condition|)
name|paramstring
operator|++
expr_stmt|;
if|if
condition|(
operator|*
name|paramstring
condition|)
block|{
name|pixpipeparams_init
argument_list|(
operator|&
name|params
argument_list|)
expr_stmt|;
name|pixpipeparams_parse
argument_list|(
name|paramstring
argument_list|,
operator|&
name|params
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|dimension
operator|=
name|params
operator|.
name|dim
expr_stmt|;
name|pipe
operator|->
name|rank
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|pipe
operator|->
name|dimension
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|select
operator|=
name|g_new
argument_list|(
name|PipeSelectModes
argument_list|,
name|pipe
operator|->
name|dimension
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|index
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|pipe
operator|->
name|dimension
argument_list|)
expr_stmt|;
comment|/* placement is not used at all ?? */
if|if
condition|(
name|params
operator|.
name|free_placement_string
condition|)
name|g_free
argument_list|(
name|params
operator|.
name|placement
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
name|dimension
condition|;
name|i
operator|++
control|)
block|{
name|pipe
operator|->
name|rank
index|[
name|i
index|]
operator|=
name|params
operator|.
name|rank
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|params
operator|.
name|selection
index|[
name|i
index|]
argument_list|,
literal|"incremental"
argument_list|)
operator|==
literal|0
condition|)
name|pipe
operator|->
name|select
index|[
name|i
index|]
operator|=
name|PIPE_SELECT_INCREMENTAL
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|params
operator|.
name|selection
index|[
name|i
index|]
argument_list|,
literal|"angular"
argument_list|)
operator|==
literal|0
condition|)
name|pipe
operator|->
name|select
index|[
name|i
index|]
operator|=
name|PIPE_SELECT_ANGULAR
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|params
operator|.
name|selection
index|[
name|i
index|]
argument_list|,
literal|"velocity"
argument_list|)
operator|==
literal|0
condition|)
name|pipe
operator|->
name|select
index|[
name|i
index|]
operator|=
name|PIPE_SELECT_VELOCITY
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|params
operator|.
name|selection
index|[
name|i
index|]
argument_list|,
literal|"random"
argument_list|)
operator|==
literal|0
condition|)
name|pipe
operator|->
name|select
index|[
name|i
index|]
operator|=
name|PIPE_SELECT_RANDOM
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|params
operator|.
name|selection
index|[
name|i
index|]
argument_list|,
literal|"pressure"
argument_list|)
operator|==
literal|0
condition|)
name|pipe
operator|->
name|select
index|[
name|i
index|]
operator|=
name|PIPE_SELECT_PRESSURE
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|params
operator|.
name|selection
index|[
name|i
index|]
argument_list|,
literal|"xtilt"
argument_list|)
operator|==
literal|0
condition|)
name|pipe
operator|->
name|select
index|[
name|i
index|]
operator|=
name|PIPE_SELECT_TILT_X
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|params
operator|.
name|selection
index|[
name|i
index|]
argument_list|,
literal|"ytilt"
argument_list|)
operator|==
literal|0
condition|)
name|pipe
operator|->
name|select
index|[
name|i
index|]
operator|=
name|PIPE_SELECT_TILT_Y
expr_stmt|;
else|else
name|pipe
operator|->
name|select
index|[
name|i
index|]
operator|=
name|PIPE_SELECT_CONSTANT
expr_stmt|;
if|if
condition|(
name|params
operator|.
name|free_selection_string
condition|)
name|g_free
argument_list|(
name|params
operator|.
name|selection
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|index
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
block|}
block|}
else|else
block|{
name|pipe
operator|->
name|dimension
operator|=
literal|1
expr_stmt|;
name|pipe
operator|->
name|rank
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|rank
index|[
literal|0
index|]
operator|=
name|num_of_brushes
expr_stmt|;
name|pipe
operator|->
name|select
operator|=
name|g_new
argument_list|(
name|PipeSelectModes
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|select
index|[
literal|0
index|]
operator|=
name|PIPE_SELECT_INCREMENTAL
expr_stmt|;
name|pipe
operator|->
name|index
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|index
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
block|}
name|totalcells
operator|=
literal|1
expr_stmt|;
comment|/* Not all necessarily present, maybe */
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
name|totalcells
operator|*=
name|pipe
operator|->
name|rank
index|[
name|i
index|]
expr_stmt|;
name|pipe
operator|->
name|stride
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|pipe
operator|->
name|dimension
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
name|dimension
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|==
literal|0
condition|)
name|pipe
operator|->
name|stride
index|[
name|i
index|]
operator|=
name|totalcells
operator|/
name|pipe
operator|->
name|rank
index|[
name|i
index|]
expr_stmt|;
else|else
name|pipe
operator|->
name|stride
index|[
name|i
index|]
operator|=
name|pipe
operator|->
name|stride
index|[
name|i
operator|-
literal|1
index|]
operator|/
name|pipe
operator|->
name|rank
index|[
name|i
index|]
expr_stmt|;
block|}
name|g_assert
argument_list|(
name|pipe
operator|->
name|stride
index|[
name|pipe
operator|->
name|dimension
operator|-
literal|1
index|]
operator|==
literal|1
argument_list|)
expr_stmt|;
name|pattern
operator|=
name|g_new0
argument_list|(
name|GPattern
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|brushes
operator|=
name|g_new0
argument_list|(
name|GimpBrushPixmap
operator|*
argument_list|,
name|num_of_brushes
argument_list|)
expr_stmt|;
comment|/* First pixmap brush in the list is the pipe itself */
name|pipe
operator|->
name|brushes
index|[
literal|0
index|]
operator|=
name|GIMP_BRUSH_PIXMAP
argument_list|(
name|pipe
argument_list|)
expr_stmt|;
comment|/* Current pixmap brush is the first one. */
name|pipe
operator|->
name|current
operator|=
name|pipe
operator|->
name|brushes
index|[
literal|0
index|]
expr_stmt|;
while|while
condition|(
name|pipe
operator|->
name|nbrushes
operator|<
name|num_of_brushes
condition|)
block|{
if|if
condition|(
name|pipe
operator|->
name|nbrushes
operator|>
literal|0
condition|)
block|{
name|pipe
operator|->
name|brushes
index|[
name|pipe
operator|->
name|nbrushes
index|]
operator|=
name|GIMP_BRUSH_PIXMAP
argument_list|(
name|gimp_type_new
argument_list|(
name|GIMP_TYPE_BRUSH_PIXMAP
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|GIMP_BRUSH
argument_list|(
name|pipe
operator|->
name|brushes
index|[
name|pipe
operator|->
name|nbrushes
index|]
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|pipe
operator|->
name|brushes
index|[
name|pipe
operator|->
name|nbrushes
index|]
argument_list|)
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
block|}
name|pipe
operator|->
name|brushes
index|[
name|pipe
operator|->
name|nbrushes
index|]
operator|->
name|pipe
operator|=
name|pipe
expr_stmt|;
comment|/* load the brush */
if|if
condition|(
operator|!
name|gimp_brush_load_brush
argument_list|(
name|GIMP_BRUSH
argument_list|(
name|pipe
operator|->
name|brushes
index|[
name|pipe
operator|->
name|nbrushes
index|]
argument_list|)
argument_list|,
name|fp
argument_list|,
name|filename
argument_list|)
operator|||
operator|!
name|pattern_load
argument_list|(
name|pattern
argument_list|,
name|fp
argument_list|,
name|filename
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Failed to load one of the\n"
literal|"brushes in the brush pipe."
argument_list|)
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|pattern_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
name|gimp_object_destroy
argument_list|(
name|pipe
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|pipe
operator|->
name|nbrushes
operator|==
literal|0
condition|)
block|{
comment|/* Replace name with the whole pipe's name */
name|g_free
argument_list|(
name|GIMP_BRUSH
argument_list|(
name|pipe
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|pipe
argument_list|)
operator|->
name|name
operator|=
name|name
expr_stmt|;
block|}
name|pipe
operator|->
name|brushes
index|[
name|pipe
operator|->
name|nbrushes
index|]
operator|->
name|pixmap_mask
operator|=
name|pattern
operator|->
name|mask
expr_stmt|;
name|g_free
argument_list|(
name|pattern
operator|->
name|name
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|nbrushes
operator|++
expr_stmt|;
block|}
comment|/*  Clean up  */
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return
name|pipe
return|;
block|}
end_function

begin_function
name|GimpBrushPipe
modifier|*
DECL|function|gimp_brush_pixmap_load (gchar * filename)
name|gimp_brush_pixmap_load
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
decl_stmt|;
name|GPattern
modifier|*
name|pattern
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
if|if
condition|(
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
operator|)
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
name|pipe
operator|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|gimp_type_new
argument_list|(
name|GIMP_TYPE_BRUSH_PIPE
argument_list|)
argument_list|)
expr_stmt|;
comment|/* A (single) pixmap brush is a pixmap pipe brush with just one pixmap */
name|pipe
operator|->
name|dimension
operator|=
literal|1
expr_stmt|;
name|pipe
operator|->
name|rank
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|rank
index|[
literal|0
index|]
operator|=
literal|1
expr_stmt|;
name|pipe
operator|->
name|select
operator|=
name|g_new
argument_list|(
name|PipeSelectModes
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|select
index|[
literal|0
index|]
operator|=
name|PIPE_SELECT_INCREMENTAL
expr_stmt|;
name|pipe
operator|->
name|index
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|index
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|pattern
operator|=
name|g_new0
argument_list|(
name|GPattern
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|brushes
operator|=
name|g_new
argument_list|(
name|GimpBrushPixmap
operator|*
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pipe
operator|->
name|brushes
index|[
literal|0
index|]
operator|=
name|GIMP_BRUSH_PIXMAP
argument_list|(
name|pipe
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
literal|0
index|]
expr_stmt|;
name|pipe
operator|->
name|brushes
index|[
literal|0
index|]
operator|->
name|pipe
operator|=
name|pipe
expr_stmt|;
comment|/* load the brush */
if|if
condition|(
operator|!
name|gimp_brush_load_brush
argument_list|(
name|GIMP_BRUSH
argument_list|(
name|pipe
operator|->
name|brushes
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|fp
argument_list|,
name|filename
argument_list|)
operator|||
operator|!
name|pattern_load
argument_list|(
name|pattern
argument_list|,
name|fp
argument_list|,
name|filename
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Failed to load pixmap brush."
argument_list|)
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|pattern_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
name|gimp_object_destroy
argument_list|(
name|pipe
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|pipe
operator|->
name|brushes
index|[
literal|0
index|]
operator|->
name|pixmap_mask
operator|=
name|pattern
operator|->
name|mask
expr_stmt|;
name|pipe
operator|->
name|nbrushes
operator|=
literal|1
expr_stmt|;
comment|/*  Clean up  */
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return
name|pipe
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_pixmap_pixmap (GimpBrushPixmap * brush)
name|gimp_brush_pixmap_pixmap
parameter_list|(
name|GimpBrushPixmap
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|brush
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_PIXMAP
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|pixmap_mask
return|;
block|}
end_function

end_unit

