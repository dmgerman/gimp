begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"xcf-read.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|guint
DECL|function|xcf_read_int32 (FILE * fp,guint32 * data,gint count)
name|xcf_read_int32
parameter_list|(
name|FILE
modifier|*
name|fp
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
name|fp
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
DECL|function|xcf_read_float (FILE * fp,gfloat * data,gint count)
name|xcf_read_float
parameter_list|(
name|FILE
modifier|*
name|fp
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
name|fp
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
DECL|function|xcf_read_int8 (FILE * fp,guint8 * data,gint count)
name|xcf_read_int8
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|,
name|guint8
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
while|while
condition|(
name|count
operator|>
literal|0
condition|)
block|{
name|gint
name|bytes
init|=
name|fread
argument_list|(
operator|(
name|char
operator|*
operator|)
name|data
argument_list|,
sizeof|sizeof
argument_list|(
name|char
argument_list|)
argument_list|,
name|count
argument_list|,
name|fp
argument_list|)
decl_stmt|;
if|if
condition|(
name|bytes
operator|<=
literal|0
condition|)
comment|/* something bad happened */
break|break;
name|total
operator|+=
name|bytes
expr_stmt|;
name|count
operator|-=
name|bytes
expr_stmt|;
name|data
operator|+=
name|bytes
expr_stmt|;
block|}
return|return
name|total
return|;
block|}
end_function

begin_function
name|guint
DECL|function|xcf_read_string (FILE * fp,gchar ** data,gint count)
name|xcf_read_string
parameter_list|(
name|FILE
modifier|*
name|fp
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
name|fp
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
name|fp
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

end_unit

