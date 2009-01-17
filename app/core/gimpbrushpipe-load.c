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
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpparasiteio.h"
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
file|"gimpbrush-load.h"
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

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GList
modifier|*
DECL|function|gimp_brush_pipe_load (const gchar * filename,GError ** error)
name|gimp_brush_pipe_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|g_return_val_if_fail
argument_list|(
name|g_path_is_absolute
argument_list|(
name|filename
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fd
operator|=
name|g_open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
operator||
name|_O_BINARY
argument_list|,
literal|0
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
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_OPEN
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
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
name|gchar
modifier|*
name|utf8
init|=
name|gimp_any_to_utf8
argument_list|(
name|buffer
operator|->
name|str
argument_list|,
name|buffer
operator|->
name|len
argument_list|,
name|_
argument_list|(
literal|"Invalid UTF-8 string in brush file '%s'."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
decl_stmt|;
name|pipe
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BRUSH_PIPE
argument_list|,
literal|"name"
argument_list|,
name|utf8
argument_list|,
literal|"mime-type"
argument_list|,
literal|"image/x-gimp-gih"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
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
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in brush file '%s': "
literal|"File is corrupt."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
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
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in brush file '%s': "
literal|"File is corrupt."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pipe
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
name|g_ascii_isspace
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
name|MAX
argument_list|(
literal|1
argument_list|,
name|params
operator|.
name|rank
index|[
name|i
index|]
argument_list|)
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
argument_list|,
name|NULL
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
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in brush file '%s': "
literal|"File is corrupt."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|g_object_unref
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
name|nbrushes
operator|++
expr_stmt|;
block|}
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
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
return|return
name|g_list_prepend
argument_list|(
name|NULL
argument_list|,
name|pipe
argument_list|)
return|;
block|}
end_function

end_unit

