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
file|"libgimpbase/gimpbase.h"
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
file|"gimpimage.h"
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
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_pattern_class_init
parameter_list|(
name|GimpPatternClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pattern_init
parameter_list|(
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pattern_finalize
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
name|gimp_pattern_get_memsize
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
name|gimp_pattern_get_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_pattern_get_new_preview
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_pattern_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_pattern_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpData
modifier|*
name|gimp_pattern_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDataClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_pattern_get_type (void)
name|gimp_pattern_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|pattern_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|pattern_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|pattern_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPatternClass
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
name|gimp_pattern_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPattern
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_pattern_init
block|,       }
decl_stmt|;
name|pattern_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DATA
argument_list|,
literal|"GimpPattern"
argument_list|,
operator|&
name|pattern_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|pattern_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_class_init (GimpPatternClass * klass)
name|gimp_pattern_class_init
parameter_list|(
name|GimpPatternClass
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
name|GimpDataClass
modifier|*
name|data_class
init|=
name|GIMP_DATA_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_pattern_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_pattern_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gimp-tool-bucket-fill"
expr_stmt|;
name|viewable_class
operator|->
name|get_size
operator|=
name|gimp_pattern_get_size
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_pattern_get_new_preview
expr_stmt|;
name|viewable_class
operator|->
name|get_description
operator|=
name|gimp_pattern_get_description
expr_stmt|;
name|data_class
operator|->
name|get_extension
operator|=
name|gimp_pattern_get_extension
expr_stmt|;
name|data_class
operator|->
name|duplicate
operator|=
name|gimp_pattern_duplicate
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_init (GimpPattern * pattern)
name|gimp_pattern_init
parameter_list|(
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
block|{
name|pattern
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_finalize (GObject * object)
name|gimp_pattern_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|pattern
operator|->
name|mask
condition|)
block|{
name|temp_buf_free
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
name|pattern
operator|->
name|mask
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
name|gint64
DECL|function|gimp_pattern_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_pattern_get_memsize
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
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|pattern
operator|->
name|mask
condition|)
name|memsize
operator|+=
name|temp_buf_get_memsize
argument_list|(
name|pattern
operator|->
name|mask
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
DECL|function|gimp_pattern_get_size (GimpViewable * viewable,gint * width,gint * height)
name|gimp_pattern_get_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
operator|*
name|width
operator|=
name|pattern
operator|->
name|mask
operator|->
name|width
expr_stmt|;
operator|*
name|height
operator|=
name|pattern
operator|->
name|mask
operator|->
name|height
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_pattern_get_new_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_pattern_get_new_preview
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
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|gint
name|copy_width
decl_stmt|;
name|gint
name|copy_height
decl_stmt|;
name|copy_width
operator|=
name|MIN
argument_list|(
name|width
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|width
argument_list|)
expr_stmt|;
name|copy_height
operator|=
name|MIN
argument_list|(
name|height
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|height
argument_list|)
expr_stmt|;
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|copy_width
argument_list|,
name|copy_height
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|temp_buf_copy_area
argument_list|(
name|pattern
operator|->
name|mask
argument_list|,
name|temp_buf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|copy_width
argument_list|,
name|copy_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|temp_buf
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_pattern_get_description (GimpViewable * viewable,gchar ** tooltip)
name|gimp_pattern_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%d x %d)"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|pattern
argument_list|)
operator|->
name|name
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|width
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|height
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_pattern_get_extension (GimpData * data)
name|gimp_pattern_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
return|return
name|GIMP_PATTERN_FILE_EXTENSION
return|;
block|}
end_function

begin_function
specifier|static
name|GimpData
modifier|*
DECL|function|gimp_pattern_duplicate (GimpData * data)
name|gimp_pattern_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|pattern
operator|->
name|mask
operator|=
name|temp_buf_copy
argument_list|(
name|GIMP_PATTERN
argument_list|(
name|data
argument_list|)
operator|->
name|mask
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_DATA
argument_list|(
name|pattern
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_pattern_new (const gchar * name)
name|gimp_pattern_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
name|pattern
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
literal|32
argument_list|,
literal|32
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|temp_buf_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|pattern
operator|->
name|mask
operator|->
name|height
condition|;
name|row
operator|++
control|)
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|pattern
operator|->
name|mask
operator|->
name|width
condition|;
name|col
operator|++
control|)
block|{
name|memset
argument_list|(
name|data
argument_list|,
operator|(
name|col
operator|%
literal|2
operator|)
operator|&&
operator|(
name|row
operator|%
literal|2
operator|)
condition|?
literal|255
else|:
literal|0
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|data
operator|+=
literal|3
expr_stmt|;
block|}
return|return
name|GIMP_DATA
argument_list|(
name|pattern
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_pattern_get_standard (void)
name|gimp_pattern_get_standard
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpData
modifier|*
name|standard_pattern
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|standard_pattern
condition|)
block|{
name|standard_pattern
operator|=
name|gimp_pattern_new
argument_list|(
literal|"Standard"
argument_list|)
expr_stmt|;
name|standard_pattern
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|gimp_data_make_internal
argument_list|(
name|standard_pattern
argument_list|)
expr_stmt|;
comment|/*  set ref_count to 2 --> never swap the standard pattern  */
name|g_object_ref
argument_list|(
name|standard_pattern
argument_list|)
expr_stmt|;
block|}
return|return
name|standard_pattern
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_pattern_load (const gchar * filename,GError ** error)
name|gimp_pattern_load
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
name|GimpPattern
modifier|*
name|pattern
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
name|pattern
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
name|header
operator|.
name|width
argument_list|,
name|header
operator|.
name|height
argument_list|,
name|header
operator|.
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
name|temp_buf_data
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
DECL|function|gimp_pattern_load_pixbuf (const gchar * filename,GError ** error)
name|gimp_pattern_load_pixbuf
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
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|guchar
modifier|*
name|pat_data
decl_stmt|;
name|guchar
modifier|*
name|buf_data
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
name|gint
name|i
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
name|width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|gdk_pixbuf_get_n_channels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|rowstride
operator|=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|pattern
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pat_data
operator|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|buf_data
operator|=
name|temp_buf_data
argument_list|(
name|pattern
operator|->
name|mask
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
name|height
condition|;
name|i
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|buf_data
operator|+
name|i
operator|*
name|width
operator|*
name|bytes
argument_list|,
name|pat_data
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|pat_data
operator|+=
name|rowstride
expr_stmt|;
block|}
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

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_pattern_get_mask (const GimpPattern * pattern)
name|gimp_pattern_get_mask
parameter_list|(
specifier|const
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PATTERN
argument_list|(
name|pattern
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|pattern
operator|->
name|mask
return|;
block|}
end_function

end_unit

