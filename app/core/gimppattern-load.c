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
file|<stdio.h>
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

begin_include
include|#
directive|include
file|<glib-object.h>
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpbaseconfig.h"
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
file|"libgimp/gimpintl.h"
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
name|gsize
name|gimp_pattern_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
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
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|GimpDataClass
modifier|*
name|data_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_object_class
operator|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|viewable_class
operator|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|data_class
operator|=
name|GIMP_DATA_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|get_new_preview
operator|=
name|gimp_pattern_get_new_preview
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
decl_stmt|;
name|pattern
operator|=
name|GIMP_PATTERN
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
name|gsize
DECL|function|gimp_pattern_get_memsize (GimpObject * object)
name|gimp_pattern_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|gsize
name|memsize
init|=
literal|0
decl_stmt|;
name|pattern
operator|=
name|GIMP_PATTERN
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
argument_list|)
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
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|guchar
name|white
index|[
name|MAX_CHANNELS
index|]
init|=
block|{
literal|255
block|,
literal|255
block|,
literal|255
block|,
literal|255
block|}
decl_stmt|;
name|gint
name|copy_width
decl_stmt|;
name|gint
name|copy_height
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|pattern
operator|=
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
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
name|x
operator|=
operator|(
name|copy_width
operator|==
name|width
operator|)
condition|?
literal|0
else|:
operator|(
name|width
operator|-
name|copy_width
operator|)
operator|/
literal|2
expr_stmt|;
name|y
operator|=
operator|(
name|copy_height
operator|==
name|height
operator|)
condition|?
literal|0
else|:
operator|(
name|height
operator|-
name|copy_height
operator|)
operator|/
literal|2
expr_stmt|;
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
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
name|white
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
name|x
argument_list|,
name|y
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
decl_stmt|;
name|pattern
operator|=
name|GIMP_PATTERN
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
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
comment|/*  Swap the pattern to disk (if we're being stingy with memory) */
if|if
condition|(
name|base_config
operator|->
name|stingy_memory_use
condition|)
name|temp_buf_swap
argument_list|(
name|pattern
operator|->
name|mask
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
name|GIMP_PATTERN
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|pattern
argument_list|)
argument_list|,
name|name
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
comment|/*  Swap the pattern to disk (if we're being stingy with memory) */
if|if
condition|(
name|base_config
operator|->
name|stingy_memory_use
condition|)
name|temp_buf_swap
argument_list|(
name|pattern
operator|->
name|mask
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
DECL|function|gimp_pattern_get_standard (void)
name|gimp_pattern_get_standard
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpPattern
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
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|standard_pattern
operator|=
name|GIMP_PATTERN
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|standard_pattern
argument_list|)
argument_list|,
literal|"Standard"
argument_list|)
expr_stmt|;
name|standard_pattern
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
name|standard_pattern
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
name|standard_pattern
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
name|standard_pattern
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
comment|/*  set ref_count to 2 --> never swap the standard pattern  */
name|g_object_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|standard_pattern
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_DATA
argument_list|(
name|standard_pattern
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_pattern_load (const gchar * filename)
name|gimp_pattern_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
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
return|return
name|NULL
return|;
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
goto|goto
name|error
goto|;
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unknown pattern format version %d in '%s'."
argument_list|)
argument_list|,
name|header
operator|.
name|version
argument_list|,
name|filename
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
operator|!=
literal|1
operator|&&
name|header
operator|.
name|bytes
operator|!=
literal|3
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unsupported pattern depth %d\n"
literal|"in file '%s'.\n"
literal|"GIMP Patterns must be GRAY or RGB.\n"
argument_list|)
argument_list|,
name|header
operator|.
name|bytes
argument_list|,
name|filename
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Error in GIMP pattern file '%s'."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
goto|goto
name|error
goto|;
block|}
if|if
condition|(
operator|!
name|g_utf8_validate
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Invalid UTF-8 string in pattern file '%s'."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|name
operator|=
name|NULL
expr_stmt|;
block|}
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
name|GIMP_PATTERN
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
name|NULL
argument_list|)
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Fatal parsing error: Pattern file '%s' appears truncated."
argument_list|)
argument_list|,
name|filename
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
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|pattern
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gimp_data_set_filename
argument_list|(
name|GIMP_DATA
argument_list|(
name|pattern
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
comment|/*  Swap the pattern to disk (if we're being stingy with memory) */
if|if
condition|(
name|base_config
operator|->
name|stingy_memory_use
condition|)
name|temp_buf_swap
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
return|return
name|GIMP_DATA
argument_list|(
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
name|G_OBJECT
argument_list|(
name|pattern
argument_list|)
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|name
condition|)
name|g_free
argument_list|(
name|name
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

