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
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

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
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient-load.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GimpData
modifier|*
DECL|function|gimp_gradient_load (const gchar * filename,gboolean stingy_memory_use,GError ** error)
name|gimp_gradient_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|stingy_memory_use
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|seg
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|prev
decl_stmt|;
name|gint
name|num_segments
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|type
decl_stmt|,
name|color
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|gchar
name|line
index|[
literal|1024
index|]
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
name|file
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
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
name|fgets
argument_list|(
name|line
argument_list|,
literal|1024
argument_list|,
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|line
argument_list|,
literal|"GIMP Gradient\n"
argument_list|)
operator|!=
literal|0
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
literal|"Fatal parse error in gradient file '%s': "
literal|"Not a GIMP gradient file."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|gradient
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRADIENT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fgets
argument_list|(
name|line
argument_list|,
literal|1024
argument_list|,
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strncmp
argument_list|(
name|line
argument_list|,
literal|"Name: "
argument_list|,
name|strlen
argument_list|(
literal|"Name: "
argument_list|)
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|utf8
operator|=
name|gimp_any_to_utf8
argument_list|(
operator|&
name|line
index|[
name|strlen
argument_list|(
literal|"Name: "
argument_list|)
index|]
argument_list|,
operator|-
literal|1
argument_list|,
name|_
argument_list|(
literal|"Invalid UTF-8 string in gradient file '%s'."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|g_strstrip
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gradient
argument_list|)
argument_list|,
name|utf8
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
name|fgets
argument_list|(
name|line
argument_list|,
literal|1024
argument_list|,
name|file
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* old gradient format */
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|utf8
operator|=
name|g_filename_to_utf8
argument_list|(
name|basename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gradient
argument_list|)
argument_list|,
name|utf8
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
block|}
name|num_segments
operator|=
name|atoi
argument_list|(
name|line
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_segments
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
literal|"Fatal parse error in gradient file '%s': "
literal|"File is corrupt."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|prev
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_segments
condition|;
name|i
operator|++
control|)
block|{
name|gchar
modifier|*
name|end
decl_stmt|;
name|seg
operator|=
name|gimp_gradient_segment_new
argument_list|()
expr_stmt|;
name|seg
operator|->
name|prev
operator|=
name|prev
expr_stmt|;
if|if
condition|(
name|prev
condition|)
name|prev
operator|->
name|next
operator|=
name|seg
expr_stmt|;
else|else
name|gradient
operator|->
name|segments
operator|=
name|seg
expr_stmt|;
name|fgets
argument_list|(
name|line
argument_list|,
literal|1024
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|seg
operator|->
name|left
operator|=
name|g_ascii_strtod
argument_list|(
name|line
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|middle
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|right
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|left_color
operator|.
name|r
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|left_color
operator|.
name|g
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|left_color
operator|.
name|b
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|left_color
operator|.
name|a
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|right_color
operator|.
name|r
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|right_color
operator|.
name|g
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|right_color
operator|.
name|b
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|right_color
operator|.
name|a
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|errno
operator|!=
name|ERANGE
operator|&&
name|sscanf
argument_list|(
name|end
argument_list|,
literal|"%d %d"
argument_list|,
operator|&
name|type
argument_list|,
operator|&
name|color
argument_list|)
operator|==
literal|2
condition|)
block|{
name|seg
operator|->
name|type
operator|=
operator|(
name|GimpGradientSegmentType
operator|)
name|type
expr_stmt|;
name|seg
operator|->
name|color
operator|=
operator|(
name|GimpGradientSegmentColor
operator|)
name|color
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Corrupt segment %d in gradient file '%s'."
argument_list|)
argument_list|,
name|i
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|prev
operator|=
name|seg
expr_stmt|;
block|}
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|GIMP_DATA
argument_list|(
name|gradient
argument_list|)
return|;
block|}
end_function

end_unit

