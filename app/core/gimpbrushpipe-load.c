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
file|<errno.h>
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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|_O_BINARY
end_ifndef

begin_define
DECL|macro|_O_BINARY
define|#
directive|define
name|_O_BINARY
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush-header.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpipe.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern-header.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_comment
comment|/*  this needs to go away  */
end_comment

begin_include
include|#
directive|include
file|"tools/gimppainttool.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpparasiteio.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|GimpBrush
modifier|*
name|gimp_brush_pipe_select_brush
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_pipe_want_null_motion
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_pipe_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpBrushClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpBrush
modifier|*
DECL|function|gimp_brush_pipe_select_brush (GimpPaintTool * paint_tool)
name|gimp_brush_pipe_select_brush
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|brushix
decl_stmt|,
name|ix
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|paint_tool
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_PIPE
argument_list|(
name|paint_tool
operator|->
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pipe
operator|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|paint_tool
operator|->
name|brush
argument_list|)
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
name|paint_tool
operator|->
name|cury
operator|-
name|paint_tool
operator|->
name|lasty
argument_list|,
name|paint_tool
operator|->
name|curx
operator|-
name|paint_tool
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
literal|2.0
operator|*
name|G_PI
expr_stmt|;
elseif|else
if|if
condition|(
name|angle
operator|>
literal|2.0
operator|*
name|G_PI
condition|)
name|angle
operator|-=
literal|2.0
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
literal|2.0
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
name|paint_tool
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
name|paint_tool
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
name|paint_tool
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
DECL|function|gimp_brush_pipe_want_null_motion (GimpPaintTool * paint_tool)
name|gimp_brush_pipe_want_null_motion
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|paint_tool
operator|!=
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_PIPE
argument_list|(
name|paint_tool
operator|->
name|brush
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pipe
operator|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|paint_tool
operator|->
name|brush
argument_list|)
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
if|if
condition|(
name|pipe
operator|->
name|brushes
index|[
name|i
index|]
condition|)
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
name|GimpBrushClass
modifier|*
name|brush_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|brush_class
operator|=
operator|(
name|GimpBrushClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_BRUSH
argument_list|)
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
name|nbrushes
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
name|GimpData
modifier|*
DECL|function|gimp_brush_pipe_load (const gchar * filename)
name|gimp_brush_pipe_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpBrushPipe
modifier|*
name|pipe
init|=
name|NULL
decl_stmt|;
name|GimpPixPipeParams
name|params
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|num_of_brushes
init|=
literal|0
decl_stmt|;
name|gint
name|totalcells
decl_stmt|;
name|gchar
modifier|*
name|paramstring
decl_stmt|;
name|GString
modifier|*
name|buffer
decl_stmt|;
name|gchar
name|c
decl_stmt|;
name|gint
name|fd
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
operator||
name|_O_BINARY
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
literal|"Couldn't open file '%s'"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/* The file format starts with a painfully simple text header */
comment|/*  get the name  */
name|buffer
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
while|while
condition|(
name|read
argument_list|(
name|fd
argument_list|,
operator|&
name|c
argument_list|,
literal|1
argument_list|)
operator|==
literal|1
operator|&&
name|c
operator|!=
literal|'\n'
operator|&&
name|buffer
operator|->
name|len
operator|<
literal|1024
condition|)
name|g_string_append_c
argument_list|(
name|buffer
argument_list|,
name|c
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
operator|->
name|len
operator|>
literal|0
operator|&&
name|buffer
operator|->
name|len
operator|<
literal|1024
condition|)
block|{
name|pipe
operator|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_BRUSH_PIPE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|pipe
argument_list|)
argument_list|,
name|buffer
operator|->
name|str
argument_list|)
expr_stmt|;
block|}
name|g_string_free
argument_list|(
name|buffer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pipe
condition|)
block|{
name|g_message
argument_list|(
literal|"Couldn't read name for brush pipe from file '%s'\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/*  get the number of brushes  */
name|buffer
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
while|while
condition|(
name|read
argument_list|(
name|fd
argument_list|,
operator|&
name|c
argument_list|,
literal|1
argument_list|)
operator|==
literal|1
operator|&&
name|c
operator|!=
literal|'\n'
operator|&&
name|buffer
operator|->
name|len
operator|<
literal|1024
condition|)
name|g_string_append_c
argument_list|(
name|buffer
argument_list|,
name|c
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
operator|->
name|len
operator|>
literal|0
operator|&&
name|buffer
operator|->
name|len
operator|<
literal|1024
condition|)
block|{
name|num_of_brushes
operator|=
name|strtol
argument_list|(
name|buffer
operator|->
name|str
argument_list|,
operator|&
name|paramstring
argument_list|,
literal|10
argument_list|)
expr_stmt|;
block|}
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
literal|"Brush pipes should have at least one brush:\n\"%s\""
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pipe
argument_list|)
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|buffer
argument_list|,
name|TRUE
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
name|gimp_pixpipe_params_init
argument_list|(
operator|&
name|params
argument_list|)
expr_stmt|;
name|gimp_pixpipe_params_parse
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
name|g_new0
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
name|g_new0
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
name|g_new0
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
name|g_string_free
argument_list|(
name|buffer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
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
name|g_new0
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
name|pipe
operator|->
name|brushes
operator|=
name|g_new0
argument_list|(
name|GimpBrush
operator|*
argument_list|,
name|num_of_brushes
argument_list|)
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
name|pipe
operator|->
name|brushes
index|[
name|pipe
operator|->
name|nbrushes
index|]
operator|=
name|gimp_brush_load_brush
argument_list|(
name|fd
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|pipe
operator|->
name|brushes
index|[
name|pipe
operator|->
name|nbrushes
index|]
condition|)
block|{
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
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
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
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
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
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
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Failed to load one of the brushes in the brush pipe\n\"%s\""
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pipe
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|pipe
operator|->
name|nbrushes
operator|++
expr_stmt|;
block|}
comment|/* Current brush is the first one. */
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
name|gimp_data_set_filename
argument_list|(
name|GIMP_DATA
argument_list|(
name|pipe
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
comment|/*  just to satisfy the code that relies on this crap  */
name|GIMP_BRUSH
argument_list|(
name|pipe
argument_list|)
operator|->
name|spacing
operator|=
name|pipe
operator|->
name|current
operator|->
name|spacing
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|pipe
argument_list|)
operator|->
name|x_axis
operator|=
name|pipe
operator|->
name|current
operator|->
name|x_axis
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|pipe
argument_list|)
operator|->
name|y_axis
operator|=
name|pipe
operator|->
name|current
operator|->
name|y_axis
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|pipe
argument_list|)
operator|->
name|mask
operator|=
name|pipe
operator|->
name|current
operator|->
name|mask
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|pipe
argument_list|)
operator|->
name|pixmap
operator|=
name|pipe
operator|->
name|current
operator|->
name|pixmap
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|GIMP_DATA
argument_list|(
name|pipe
argument_list|)
return|;
block|}
end_function

end_unit

