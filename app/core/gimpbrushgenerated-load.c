begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp_brush_generated module Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
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
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated-load.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GList
modifier|*
DECL|function|gimp_brush_generated_load (GimpContext * context,const gchar * filename,GError ** error)
name|gimp_brush_generated_load
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
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|gchar
name|string
index|[
literal|256
index|]
decl_stmt|;
name|gint
name|linenum
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|GimpBrushGeneratedShape
name|shape
init|=
name|GIMP_BRUSH_GENERATED_CIRCLE
decl_stmt|;
name|gboolean
name|have_shape
init|=
name|FALSE
decl_stmt|;
name|gint
name|spikes
init|=
literal|2
decl_stmt|;
name|gdouble
name|spacing
decl_stmt|;
name|gdouble
name|radius
decl_stmt|;
name|gdouble
name|hardness
decl_stmt|;
name|gdouble
name|aspect_ratio
decl_stmt|;
name|gdouble
name|angle
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
name|g_fopen
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
comment|/* make sure the file we are reading is the right type */
name|errno
operator|=
literal|0
expr_stmt|;
name|linenum
operator|=
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|string
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|failed
goto|;
if|if
condition|(
operator|!
name|g_str_has_prefix
argument_list|(
name|string
argument_list|,
literal|"GIMP-VBR"
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
literal|"Fatal parse error in brush file '%s': "
literal|"Not a GIMP brush file."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
comment|/* make sure we are reading a compatible version */
name|errno
operator|=
literal|0
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|string
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|failed
goto|;
if|if
condition|(
operator|!
name|g_str_has_prefix
argument_list|(
name|string
argument_list|,
literal|"1.0"
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|g_str_has_prefix
argument_list|(
name|string
argument_list|,
literal|"1.5"
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
literal|"Fatal parse error in brush file '%s': "
literal|"Unknown GIMP brush version in line %d."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
else|else
block|{
name|have_shape
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
comment|/* read name */
name|errno
operator|=
literal|0
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|string
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|failed
goto|;
name|g_strstrip
argument_list|(
name|string
argument_list|)
expr_stmt|;
comment|/* the empty string is not an allowed name */
if|if
condition|(
name|strlen
argument_list|(
name|string
argument_list|)
operator|<
literal|1
condition|)
name|g_strlcpy
argument_list|(
name|string
argument_list|,
name|_
argument_list|(
literal|"Untitled"
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_any_to_utf8
argument_list|(
name|string
argument_list|,
operator|-
literal|1
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
expr_stmt|;
if|if
condition|(
name|have_shape
condition|)
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|shape_val
decl_stmt|;
name|enum_class
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_BRUSH_GENERATED_SHAPE
argument_list|)
expr_stmt|;
comment|/* read shape */
name|errno
operator|=
literal|0
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|string
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|failed
goto|;
name|g_strstrip
argument_list|(
name|string
argument_list|)
expr_stmt|;
name|shape_val
operator|=
name|g_enum_get_value_by_nick
argument_list|(
name|enum_class
argument_list|,
name|string
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|shape_val
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
literal|"Unknown GIMP brush shape in line %d."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
name|shape
operator|=
name|shape_val
operator|->
name|value
expr_stmt|;
block|}
comment|/* read brush spacing */
name|errno
operator|=
literal|0
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|string
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|failed
goto|;
name|spacing
operator|=
name|g_ascii_strtod
argument_list|(
name|string
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* read brush radius */
name|errno
operator|=
literal|0
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|string
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|failed
goto|;
name|radius
operator|=
name|g_ascii_strtod
argument_list|(
name|string
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|have_shape
condition|)
block|{
comment|/* read number of spikes */
name|errno
operator|=
literal|0
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|string
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|failed
goto|;
name|spikes
operator|=
name|CLAMP
argument_list|(
name|atoi
argument_list|(
name|string
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|20
argument_list|)
expr_stmt|;
block|}
comment|/* read brush hardness */
name|errno
operator|=
literal|0
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|string
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|failed
goto|;
name|hardness
operator|=
name|g_ascii_strtod
argument_list|(
name|string
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* read brush aspect_ratio */
name|errno
operator|=
literal|0
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|string
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|failed
goto|;
name|aspect_ratio
operator|=
name|g_ascii_strtod
argument_list|(
name|string
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* read brush angle */
name|errno
operator|=
literal|0
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|string
argument_list|,
sizeof|sizeof
argument_list|(
name|string
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|failed
goto|;
name|angle
operator|=
name|g_ascii_strtod
argument_list|(
name|string
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|gimp_brush_generated_new
argument_list|(
name|name
argument_list|,
name|shape
argument_list|,
name|radius
argument_list|,
name|spikes
argument_list|,
name|hardness
argument_list|,
name|aspect_ratio
argument_list|,
name|angle
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|brush
operator|->
name|spacing
operator|=
name|spacing
expr_stmt|;
return|return
name|g_list_prepend
argument_list|(
name|NULL
argument_list|,
name|brush
argument_list|)
return|;
name|failed
label|:
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
condition|)
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
block|{
name|gchar
modifier|*
name|msg
decl_stmt|;
if|if
condition|(
name|errno
condition|)
name|msg
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Line %d: %s"
argument_list|)
argument_list|,
name|linenum
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|msg
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"File is truncated in line %d"
argument_list|)
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
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
literal|"Error while reading brush file '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|msg
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|msg
argument_list|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

