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
file|<math.h>
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

begin_decl_stmt
DECL|variable|gimp_brush_class
specifier|static
name|GimpBrushClass
modifier|*
name|gimp_brush_class
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_object_class
specifier|static
name|GtkObjectClass
modifier|*
name|gimp_object_class
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
name|void
name|paint_line_pixmap_mask
parameter_list|(
name|GImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpBrushPixmap
modifier|*
name|brush
parameter_list|,
name|guchar
modifier|*
name|d
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|bytes
parameter_list|,
name|int
name|width
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
operator|(
operator|*
name|GTK_OBJECT_CLASS
argument_list|(
name|gimp_object_class
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
name|GimpBrushPixmap
modifier|*
name|pixmap
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
name|pixmap
operator|=
name|GIMP_BRUSH_PIXMAP
argument_list|(
name|paint_core
operator|->
name|brush
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixmap
operator|->
name|pipe
operator|->
name|nbrushes
operator|==
literal|1
condition|)
return|return
name|GIMP_BRUSH
argument_list|(
name|pixmap
operator|->
name|pipe
operator|->
name|current
argument_list|)
return|;
comment|/* Just select the next one for now. This is the place where we    * will select the correct brush based on various parameters    * in paint_core.    */
name|pixmap
operator|->
name|pipe
operator|->
name|index
index|[
literal|0
index|]
operator|=
operator|(
name|pixmap
operator|->
name|pipe
operator|->
name|index
index|[
literal|0
index|]
operator|+
literal|1
operator|)
operator|%
name|pixmap
operator|->
name|pipe
operator|->
name|nbrushes
expr_stmt|;
name|pixmap
operator|->
name|pipe
operator|->
name|current
operator|=
name|pixmap
operator|->
name|pipe
operator|->
name|brushes
index|[
name|pixmap
operator|->
name|pipe
operator|->
name|index
index|[
literal|0
index|]
index|]
expr_stmt|;
return|return
name|GIMP_BRUSH
argument_list|(
name|pixmap
operator|->
name|pipe
operator|->
name|current
argument_list|)
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
name|int
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
name|gimp_object_destroy
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
name|gimp_object_class
argument_list|)
operator|->
name|destroy
condition|)
operator|(
operator|*
name|GTK_OBJECT_CLASS
argument_list|(
name|gimp_object_class
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
name|gimp_object_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_OBJECT
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
DECL|function|gimp_brush_pipe_load (char * filename)
name|gimp_brush_pipe_load
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
decl_stmt|;
name|GPatternP
name|pattern
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|guchar
name|buf
index|[
literal|1024
index|]
decl_stmt|;
name|guchar
modifier|*
name|name
decl_stmt|;
name|int
name|num_of_brushes
decl_stmt|;
name|guchar
modifier|*
name|params
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
name|params
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
literal|"pixmap brush pipe should have at least one brush"
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
comment|/* Here we should parse the params to get the dimension, ranks,    * placement options, etc. But just use defaults for now.    */
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
name|int
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
name|int
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
operator|(
name|GPatternP
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|GPattern
argument_list|)
argument_list|)
expr_stmt|;
name|pattern
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
name|pattern
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|pattern
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
name|pipe
operator|->
name|brushes
operator|=
operator|(
name|GimpBrushPixmap
operator|*
operator|*
operator|)
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
name|load_pattern_pattern
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
literal|"failed to load one of the pixmap brushes in the pipe"
argument_list|)
argument_list|)
expr_stmt|;
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
DECL|function|gimp_brush_pixmap_load (char * filename)
name|gimp_brush_pixmap_load
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
decl_stmt|;
name|GPatternP
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
name|int
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
name|int
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
operator|(
name|GPatternP
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|GPattern
argument_list|)
argument_list|)
expr_stmt|;
name|pattern
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
name|pattern
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|pattern
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
name|pipe
operator|->
name|brushes
operator|=
operator|(
name|GimpBrushPixmap
operator|*
operator|*
operator|)
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
name|load_pattern_pattern
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
literal|"failed to load pixmap brush"
argument_list|)
argument_list|)
expr_stmt|;
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

begin_function
name|void
DECL|function|color_area_with_pixmap (PaintCore * paint_core,GImage * dest,GimpDrawable * drawable,TempBuf * area)
name|color_area_with_pixmap
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|TempBuf
modifier|*
name|area
parameter_list|)
block|{
name|PixelRegion
name|destPR
decl_stmt|;
name|void
modifier|*
name|pr
decl_stmt|;
name|guchar
modifier|*
name|d
decl_stmt|;
name|int
name|ulx
decl_stmt|,
name|uly
decl_stmt|,
name|offsetx
decl_stmt|,
name|offsety
decl_stmt|,
name|y
decl_stmt|;
name|GimpBrushPixmap
modifier|*
name|pixmap
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH_PIXMAP
argument_list|(
name|paint_core
operator|->
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|GIMP_BRUSH_PIXMAP
argument_list|(
name|paint_core
operator|->
name|brush
argument_list|)
expr_stmt|;
name|destPR
operator|.
name|bytes
operator|=
name|area
operator|->
name|bytes
expr_stmt|;
name|destPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|destPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|destPR
operator|.
name|rowstride
operator|=
name|destPR
operator|.
name|bytes
operator|*
name|area
operator|->
name|width
expr_stmt|;
name|destPR
operator|.
name|data
operator|=
name|temp_buf_data
argument_list|(
name|area
argument_list|)
expr_stmt|;
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|1
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
comment|/* Calculate upper left corner of brush as in    * paint_core_get_paint_area.  Ugly to have to do this here, too.    */
name|ulx
operator|=
operator|(
name|int
operator|)
name|paint_core
operator|->
name|curx
operator|-
operator|(
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|width
operator|>>
literal|1
operator|)
expr_stmt|;
name|uly
operator|=
operator|(
name|int
operator|)
name|paint_core
operator|->
name|cury
operator|-
operator|(
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|height
operator|>>
literal|1
operator|)
expr_stmt|;
name|offsetx
operator|=
name|area
operator|->
name|x
operator|-
name|ulx
expr_stmt|;
name|offsety
operator|=
name|area
operator|->
name|y
operator|-
name|uly
expr_stmt|;
for|for
control|(
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|d
operator|=
name|destPR
operator|.
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|destPR
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|paint_line_pixmap_mask
argument_list|(
name|dest
argument_list|,
name|drawable
argument_list|,
name|pixmap
argument_list|,
name|d
argument_list|,
name|offsetx
argument_list|,
name|y
operator|+
name|offsety
argument_list|,
name|destPR
operator|.
name|bytes
argument_list|,
name|destPR
operator|.
name|w
argument_list|)
expr_stmt|;
name|d
operator|+=
name|destPR
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paint_line_pixmap_mask (GImage * dest,GimpDrawable * drawable,GimpBrushPixmap * brush,guchar * d,int x,int y,int bytes,int width)
name|paint_line_pixmap_mask
parameter_list|(
name|GImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpBrushPixmap
modifier|*
name|brush
parameter_list|,
name|guchar
modifier|*
name|d
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|bytes
parameter_list|,
name|int
name|width
parameter_list|)
block|{
name|guchar
modifier|*
name|b
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|int
name|x_index
decl_stmt|;
name|gdouble
name|alpha
decl_stmt|;
name|gdouble
name|factor
init|=
literal|0.00392156986
decl_stmt|;
comment|/* 1.0/255.0 */
name|gint
name|i
decl_stmt|;
name|gint
name|j
decl_stmt|;
name|guchar
modifier|*
name|mask
decl_stmt|;
comment|/*  Make sure x, y are positive  */
while|while
condition|(
name|x
operator|<
literal|0
condition|)
name|x
operator|+=
name|brush
operator|->
name|pixmap_mask
operator|->
name|width
expr_stmt|;
while|while
condition|(
name|y
operator|<
literal|0
condition|)
name|y
operator|+=
name|brush
operator|->
name|pixmap_mask
operator|->
name|height
expr_stmt|;
comment|/* Point to the approriate scanline */
name|b
operator|=
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|pixmap_mask
argument_list|)
operator|+
operator|(
name|y
operator|%
name|brush
operator|->
name|pixmap_mask
operator|->
name|height
operator|)
operator|*
name|brush
operator|->
name|pixmap_mask
operator|->
name|width
operator|*
name|brush
operator|->
name|pixmap_mask
operator|->
name|bytes
expr_stmt|;
comment|/* ditto, except for the brush mask, so we can pre-multiply the alpha value */
name|mask
operator|=
name|temp_buf_data
argument_list|(
operator|(
name|brush
operator|->
name|gbrush
operator|)
operator|.
name|mask
argument_list|)
operator|+
operator|(
name|y
operator|%
name|brush
operator|->
name|pixmap_mask
operator|->
name|height
operator|)
operator|*
name|brush
operator|->
name|pixmap_mask
operator|->
name|width
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
condition|;
name|i
operator|++
control|)
block|{
comment|/* attempt to avoid doing this calc twice in the loop */
name|x_index
operator|=
operator|(
operator|(
name|i
operator|+
name|x
operator|)
operator|%
name|brush
operator|->
name|pixmap_mask
operator|->
name|width
operator|)
expr_stmt|;
name|p
operator|=
name|b
operator|+
name|x_index
operator|*
name|brush
operator|->
name|pixmap_mask
operator|->
name|bytes
expr_stmt|;
name|d
index|[
name|bytes
operator|-
literal|1
index|]
operator|=
name|mask
index|[
name|x_index
index|]
expr_stmt|;
comment|/* multiply alpha into the pixmap data */
comment|/* maybe we could do this at tool creation or brush switch time? */
comment|/* and compute it for the whole brush at once and cache it?  */
name|alpha
operator|=
name|d
index|[
name|bytes
operator|-
literal|1
index|]
operator|*
name|factor
expr_stmt|;
name|d
index|[
literal|0
index|]
operator|*=
name|alpha
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|*=
name|alpha
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|*=
name|alpha
expr_stmt|;
comment|/* printf("i: %i d->r: %i d->g: %i d->b: %i d->a: %i\n",i,(int)d[0], (int)d[1], (int)d[2], (int)d[3]); */
name|gimage_transform_color
argument_list|(
name|dest
argument_list|,
name|drawable
argument_list|,
name|p
argument_list|,
name|d
argument_list|,
name|RGB
argument_list|)
expr_stmt|;
name|d
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
end_function

end_unit

