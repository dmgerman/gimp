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
file|<stdio.h>
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

begin_include
include|#
directive|include
file|<glib.h>
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
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern-header.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern-load.h"
end_include

begin_include
include|#
directive|include
file|"gimptempbuf.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GList
modifier|*
DECL|function|gimp_pattern_load (GimpContext * context,const gchar * filename,GError ** error)
name|gimp_pattern_load
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
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
name|GimpPattern
modifier|*
name|pattern
init|=
name|NULL
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
init|=
name|NULL
decl_stmt|;
name|gint
name|fd
decl_stmt|;
name|PatternHeader
name|header
decl_stmt|;
name|gint
name|bn_size
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
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
comment|/*  Read in the header size  */
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
operator|&
name|header
argument_list|,
sizeof|sizeof
argument_list|(
name|header
argument_list|)
argument_list|)
operator|!=
sizeof|sizeof
argument_list|(
name|header
argument_list|)
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
literal|"Fatal parse error in pattern file '%s': "
literal|"File appears truncated."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|error
goto|;
block|}
comment|/*  rearrange the bytes in each unsigned int  */
name|header
operator|.
name|header_size
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|header_size
argument_list|)
expr_stmt|;
name|header
operator|.
name|version
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|version
argument_list|)
expr_stmt|;
name|header
operator|.
name|width
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|width
argument_list|)
expr_stmt|;
name|header
operator|.
name|height
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|height
argument_list|)
expr_stmt|;
name|header
operator|.
name|bytes
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|bytes
argument_list|)
expr_stmt|;
name|header
operator|.
name|magic_number
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|magic_number
argument_list|)
expr_stmt|;
comment|/*  Check for correct file format */
if|if
condition|(
name|header
operator|.
name|magic_number
operator|!=
name|GPATTERN_MAGIC
operator|||
name|header
operator|.
name|version
operator|!=
literal|1
operator|||
name|header
operator|.
name|header_size
operator|<=
sizeof|sizeof
argument_list|(
name|header
argument_list|)
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
literal|"Fatal parse error in pattern file '%s': "
literal|"Unknown pattern format version %d."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|header
operator|.
name|version
argument_list|)
expr_stmt|;
goto|goto
name|error
goto|;
block|}
comment|/*  Check for supported bit depths  */
if|if
condition|(
name|header
operator|.
name|bytes
operator|<
literal|1
operator|||
name|header
operator|.
name|bytes
operator|>
literal|4
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
literal|"Fatal parse error in pattern file '%s: "
literal|"Unsupported pattern depth %d.\n"
literal|"GIMP Patterns must be GRAY or RGB."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|header
operator|.
name|bytes
argument_list|)
expr_stmt|;
goto|goto
name|error
goto|;
block|}
comment|/*  Read in the pattern name  */
if|if
condition|(
operator|(
name|bn_size
operator|=
operator|(
name|header
operator|.
name|header_size
operator|-
sizeof|sizeof
argument_list|(
name|header
argument_list|)
operator|)
operator|)
condition|)
block|{
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|name
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|bn_size
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|read
argument_list|(
name|fd
argument_list|,
name|name
argument_list|,
name|bn_size
argument_list|)
operator|)
operator|<
name|bn_size
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
literal|"Fatal parse error in pattern file '%s': "
literal|"File appears truncated."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
goto|goto
name|error
goto|;
block|}
name|utf8
operator|=
name|gimp_any_to_utf8
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|,
name|_
argument_list|(
literal|"Invalid UTF-8 string in pattern file '%s'."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|name
operator|=
name|utf8
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Unnamed"
argument_list|)
argument_list|)
expr_stmt|;
name|pattern
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"mime-type"
argument_list|,
literal|"image/x-gimp-pat"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|header
operator|.
name|bytes
condition|)
block|{
case|case
literal|1
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
break|break;
block|}
name|pattern
operator|->
name|mask
operator|=
name|gimp_temp_buf_new
argument_list|(
name|header
operator|.
name|width
argument_list|,
name|header
operator|.
name|height
argument_list|,
name|format
argument_list|)
expr_stmt|;
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
name|gimp_temp_buf_get_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
argument_list|,
name|header
operator|.
name|width
operator|*
name|header
operator|.
name|height
operator|*
name|header
operator|.
name|bytes
argument_list|)
operator|<
name|header
operator|.
name|width
operator|*
name|header
operator|.
name|height
operator|*
name|header
operator|.
name|bytes
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
literal|"Fatal parse error in pattern file '%s': "
literal|"File appears truncated."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|error
goto|;
block|}
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|g_list_prepend
argument_list|(
name|NULL
argument_list|,
name|pattern
argument_list|)
return|;
name|error
label|:
if|if
condition|(
name|pattern
condition|)
name|g_object_unref
argument_list|(
name|pattern
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
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_pattern_load_pixbuf (GimpContext * context,const gchar * filename,GError ** error)
name|gimp_pattern_load_pixbuf
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
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
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|gchar
modifier|*
name|name
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
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_file
argument_list|(
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pixbuf
condition|)
return|return
name|NULL
return|;
name|name
operator|=
name|g_strdup
argument_list|(
name|gdk_pixbuf_get_option
argument_list|(
name|pixbuf
argument_list|,
literal|"tEXt::Title"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|gdk_pixbuf_get_option
argument_list|(
name|pixbuf
argument_list|,
literal|"tEXt::Comment"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
name|g_filename_display_basename
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|pattern
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"mime-type"
argument_list|,
name|NULL
argument_list|,
comment|/* FIXME!! */
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|pattern
operator|->
name|mask
operator|=
name|gimp_temp_buf_new
argument_list|(
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gimp_pixbuf_get_format
argument_list|(
name|pixbuf
argument_list|)
argument_list|)
expr_stmt|;
name|src_buffer
operator|=
name|gimp_pixbuf_create_buffer
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|dest_buffer
operator|=
name|gimp_temp_buf_create_buffer
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|src_buffer
argument_list|,
name|NULL
argument_list|,
name|dest_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
return|return
name|g_list_prepend
argument_list|(
name|NULL
argument_list|,
name|pattern
argument_list|)
return|;
block|}
end_function

end_unit

