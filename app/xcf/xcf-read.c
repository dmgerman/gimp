begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"xcf-private.h"
end_include

begin_include
include|#
directive|include
file|"xcf-read.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|MAX_XCF_STRING_LEN
define|#
directive|define
name|MAX_XCF_STRING_LEN
value|(16L * 1024 * 1024)
end_define

begin_function
name|guint
DECL|function|xcf_read_int8 (XcfInfo * info,guint8 * data,gint count)
name|xcf_read_int8
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
name|gsize
name|bytes_read
init|=
literal|0
decl_stmt|;
comment|/* we allow for 'data == NULL&& count == 0', which g_input_stream_read_all()    * rejects.    */
if|if
condition|(
name|count
operator|>
literal|0
condition|)
block|{
name|g_input_stream_read_all
argument_list|(
name|info
operator|->
name|input
argument_list|,
name|data
argument_list|,
name|count
argument_list|,
operator|&
name|bytes_read
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|info
operator|->
name|cp
operator|+=
name|bytes_read
expr_stmt|;
block|}
return|return
name|bytes_read
return|;
block|}
end_function

begin_function
name|guint
DECL|function|xcf_read_int16 (XcfInfo * info,guint16 * data,gint count)
name|xcf_read_int16
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|guint16
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
name|guint
name|total
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|count
operator|>
literal|0
condition|)
block|{
name|total
operator|+=
name|xcf_read_int8
argument_list|(
name|info
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|data
argument_list|,
name|count
operator|*
literal|2
argument_list|)
expr_stmt|;
while|while
condition|(
name|count
operator|--
condition|)
block|{
operator|*
name|data
operator|=
name|g_ntohs
argument_list|(
operator|*
name|data
argument_list|)
expr_stmt|;
name|data
operator|++
expr_stmt|;
block|}
block|}
return|return
name|total
return|;
block|}
end_function

begin_function
name|guint
DECL|function|xcf_read_int32 (XcfInfo * info,guint32 * data,gint count)
name|xcf_read_int32
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|guint32
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
name|guint
name|total
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|count
operator|>
literal|0
condition|)
block|{
name|total
operator|+=
name|xcf_read_int8
argument_list|(
name|info
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|data
argument_list|,
name|count
operator|*
literal|4
argument_list|)
expr_stmt|;
while|while
condition|(
name|count
operator|--
condition|)
block|{
operator|*
name|data
operator|=
name|g_ntohl
argument_list|(
operator|*
name|data
argument_list|)
expr_stmt|;
name|data
operator|++
expr_stmt|;
block|}
block|}
return|return
name|total
return|;
block|}
end_function

begin_function
name|guint
DECL|function|xcf_read_int64 (XcfInfo * info,guint64 * data,gint count)
name|xcf_read_int64
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|guint64
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
name|guint
name|total
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|count
operator|>
literal|0
condition|)
block|{
name|total
operator|+=
name|xcf_read_int8
argument_list|(
name|info
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|data
argument_list|,
name|count
operator|*
literal|8
argument_list|)
expr_stmt|;
while|while
condition|(
name|count
operator|--
condition|)
block|{
operator|*
name|data
operator|=
name|GINT64_FROM_BE
argument_list|(
operator|*
name|data
argument_list|)
expr_stmt|;
name|data
operator|++
expr_stmt|;
block|}
block|}
return|return
name|total
return|;
block|}
end_function

begin_function
name|guint
DECL|function|xcf_read_offset (XcfInfo * info,goffset * data,gint count)
name|xcf_read_offset
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|goffset
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
name|guint
name|total
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|count
operator|>
literal|0
condition|)
block|{
if|if
condition|(
name|info
operator|->
name|bytes_per_offset
operator|==
literal|4
condition|)
block|{
name|gint32
modifier|*
name|int_offsets
init|=
name|g_alloca
argument_list|(
name|count
operator|*
sizeof|sizeof
argument_list|(
name|gint32
argument_list|)
argument_list|)
decl_stmt|;
name|total
operator|+=
name|xcf_read_int8
argument_list|(
name|info
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|int_offsets
argument_list|,
name|count
operator|*
literal|4
argument_list|)
expr_stmt|;
while|while
condition|(
name|count
operator|--
condition|)
block|{
operator|*
name|data
operator|=
name|g_ntohl
argument_list|(
operator|*
name|int_offsets
argument_list|)
expr_stmt|;
name|int_offsets
operator|++
expr_stmt|;
name|data
operator|++
expr_stmt|;
block|}
block|}
else|else
block|{
name|total
operator|+=
name|xcf_read_int8
argument_list|(
name|info
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|data
argument_list|,
name|count
operator|*
literal|8
argument_list|)
expr_stmt|;
while|while
condition|(
name|count
operator|--
condition|)
block|{
operator|*
name|data
operator|=
name|GINT64_FROM_BE
argument_list|(
operator|*
name|data
argument_list|)
expr_stmt|;
name|data
operator|++
expr_stmt|;
block|}
block|}
block|}
return|return
name|total
return|;
block|}
end_function

begin_function
name|guint
DECL|function|xcf_read_float (XcfInfo * info,gfloat * data,gint count)
name|xcf_read_float
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|gfloat
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
return|return
name|xcf_read_int32
argument_list|(
name|info
argument_list|,
operator|(
name|guint32
operator|*
operator|)
operator|(
operator|(
name|void
operator|*
operator|)
name|data
operator|)
argument_list|,
name|count
argument_list|)
return|;
block|}
end_function

begin_function
name|guint
DECL|function|xcf_read_string (XcfInfo * info,gchar ** data,gint count)
name|xcf_read_string
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|gchar
modifier|*
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
name|guint
name|total
init|=
literal|0
decl_stmt|;
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
name|count
condition|;
name|i
operator|++
control|)
block|{
name|guint32
name|tmp
decl_stmt|;
name|total
operator|+=
name|xcf_read_int32
argument_list|(
name|info
argument_list|,
operator|&
name|tmp
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|tmp
operator|>
name|MAX_XCF_STRING_LEN
condition|)
block|{
name|g_warning
argument_list|(
literal|"Maximum string length (%ld bytes) exceeded. "
literal|"Possibly corrupt XCF file."
argument_list|,
name|MAX_XCF_STRING_LEN
argument_list|)
expr_stmt|;
name|data
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tmp
operator|>
literal|0
condition|)
block|{
name|gchar
modifier|*
name|str
decl_stmt|;
name|str
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|total
operator|+=
name|xcf_read_int8
argument_list|(
name|info
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|str
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
if|if
condition|(
name|str
index|[
name|tmp
operator|-
literal|1
index|]
operator|!=
literal|'\0'
condition|)
name|str
index|[
name|tmp
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
name|data
index|[
name|i
index|]
operator|=
name|gimp_any_to_utf8
argument_list|(
name|str
argument_list|,
operator|-
literal|1
argument_list|,
name|_
argument_list|(
literal|"Invalid UTF-8 string in XCF file"
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|data
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
block|}
return|return
name|total
return|;
block|}
end_function

begin_function
name|guint
DECL|function|xcf_read_component (XcfInfo * info,gint bpc,guint8 * data,gint count)
name|xcf_read_component
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|gint
name|bpc
parameter_list|,
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
switch|switch
condition|(
name|bpc
condition|)
block|{
case|case
literal|1
case|:
return|return
name|xcf_read_int8
argument_list|(
name|info
argument_list|,
name|data
argument_list|,
name|count
argument_list|)
return|;
case|case
literal|2
case|:
return|return
name|xcf_read_int16
argument_list|(
name|info
argument_list|,
operator|(
name|guint16
operator|*
operator|)
name|data
argument_list|,
name|count
argument_list|)
return|;
case|case
literal|4
case|:
return|return
name|xcf_read_int32
argument_list|(
name|info
argument_list|,
operator|(
name|guint32
operator|*
operator|)
name|data
argument_list|,
name|count
argument_list|)
return|;
case|case
literal|8
case|:
return|return
name|xcf_read_int64
argument_list|(
name|info
argument_list|,
operator|(
name|guint64
operator|*
operator|)
name|data
argument_list|,
name|count
argument_list|)
return|;
default|default:
break|break;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_function
name|void
DECL|function|xcf_read_from_be (gint bpc,guint8 * data,gint count)
name|xcf_read_from_be
parameter_list|(
name|gint
name|bpc
parameter_list|,
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
switch|switch
condition|(
name|bpc
condition|)
block|{
case|case
literal|1
case|:
break|break;
case|case
literal|2
case|:
block|{
name|guint16
modifier|*
name|d
init|=
operator|(
name|guint16
operator|*
operator|)
name|data
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|count
condition|;
name|i
operator|++
control|)
name|d
index|[
name|i
index|]
operator|=
name|g_ntohs
argument_list|(
name|d
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|4
case|:
block|{
name|guint32
modifier|*
name|d
init|=
operator|(
name|guint32
operator|*
operator|)
name|data
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|count
condition|;
name|i
operator|++
control|)
name|d
index|[
name|i
index|]
operator|=
name|g_ntohl
argument_list|(
name|d
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|8
case|:
block|{
name|guint64
modifier|*
name|d
init|=
operator|(
name|guint64
operator|*
operator|)
name|data
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|count
condition|;
name|i
operator|++
control|)
name|d
index|[
name|i
index|]
operator|=
name|GINT64_FROM_BE
argument_list|(
name|d
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
block|}
end_function

end_unit

