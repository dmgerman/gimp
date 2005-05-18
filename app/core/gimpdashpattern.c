begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpdashpattern.c  * Copyright (C) 2003 Simon Budig  * Copyright (C) 2005 Sven Neumann  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"gimpdashpattern.h"
end_include

begin_function
name|GArray
modifier|*
DECL|function|gimp_dash_pattern_from_preset (GimpDashPreset preset)
name|gimp_dash_pattern_from_preset
parameter_list|(
name|GimpDashPreset
name|preset
parameter_list|)
block|{
name|GArray
modifier|*
name|pattern
decl_stmt|;
name|gdouble
name|dash
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|pattern
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|preset
condition|)
block|{
case|case
name|GIMP_DASH_LINE
case|:
break|break;
case|case
name|GIMP_DASH_LONG_DASH
case|:
name|dash
operator|=
literal|9.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
name|dash
operator|=
literal|3.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_DASH_MEDIUM_DASH
case|:
name|dash
operator|=
literal|6.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
name|dash
operator|=
literal|6.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_DASH_SHORT_DASH
case|:
name|dash
operator|=
literal|3.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
name|dash
operator|=
literal|9.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_DASH_SPARSE_DOTS
case|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
block|{
name|dash
operator|=
literal|1.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
name|dash
operator|=
literal|5.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_DASH_NORMAL_DOTS
case|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
block|{
name|dash
operator|=
literal|1.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
name|dash
operator|=
literal|3.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_DASH_DENSE_DOTS
case|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|12
condition|;
name|i
operator|++
control|)
block|{
name|dash
operator|=
literal|1.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_DASH_STIPPLES
case|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|24
condition|;
name|i
operator|++
control|)
block|{
name|dash
operator|=
literal|0.5
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_DASH_DASH_DOT
case|:
name|dash
operator|=
literal|7.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
name|dash
operator|=
literal|2.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
name|dash
operator|=
literal|1.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
name|dash
operator|=
literal|2.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_DASH_DASH_DOT_DOT
case|:
name|dash
operator|=
literal|7.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
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
literal|5
condition|;
name|i
operator|++
control|)
block|{
name|dash
operator|=
literal|1.0
expr_stmt|;
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|dash
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_DASH_CUSTOM
case|:
name|g_warning
argument_list|(
literal|"GIMP_DASH_CUSTOM passed to gimp_dash_pattern_from_preset()"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pattern
operator|->
name|len
operator|<
literal|2
condition|)
block|{
name|g_array_free
argument_list|(
name|pattern
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|pattern
return|;
block|}
end_function

begin_function
name|GArray
modifier|*
DECL|function|gimp_dash_pattern_from_value (const GValue * value)
name|gimp_dash_pattern_from_value
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GValueArray
modifier|*
name|val_array
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_VALUE_HOLDS_BOXED
argument_list|(
name|value
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|val_array
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|val_array
operator|==
name|NULL
operator|||
name|val_array
operator|->
name|n_values
operator|==
literal|0
condition|)
block|{
return|return
name|NULL
return|;
block|}
else|else
block|{
name|GArray
modifier|*
name|pattern
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|pattern
operator|=
name|g_array_sized_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|,
name|val_array
operator|->
name|n_values
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
name|val_array
operator|->
name|n_values
condition|;
name|i
operator|++
control|)
block|{
name|GValue
modifier|*
name|item
init|=
name|g_value_array_get_nth
argument_list|(
name|val_array
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|gdouble
name|val
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_VALUE_HOLDS_DOUBLE
argument_list|(
name|item
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|val
operator|=
name|g_value_get_double
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|pattern
operator|=
name|g_array_append_val
argument_list|(
name|pattern
argument_list|,
name|val
argument_list|)
expr_stmt|;
block|}
return|return
name|pattern
return|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_dash_pattern_value_set (GArray * pattern,GValue * value)
name|gimp_dash_pattern_value_set
parameter_list|(
name|GArray
modifier|*
name|pattern
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|G_VALUE_HOLDS_BOXED
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern
operator|==
name|NULL
operator|||
name|pattern
operator|->
name|len
operator|==
literal|0
condition|)
block|{
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GValueArray
modifier|*
name|val_array
init|=
name|g_value_array_new
argument_list|(
name|pattern
operator|->
name|len
argument_list|)
decl_stmt|;
name|GValue
name|item
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|item
argument_list|,
name|G_TYPE_DOUBLE
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
name|pattern
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|g_value_set_double
argument_list|(
operator|&
name|item
argument_list|,
name|g_array_index
argument_list|(
name|pattern
argument_list|,
name|gdouble
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_array_append
argument_list|(
name|val_array
argument_list|,
operator|&
name|item
argument_list|)
expr_stmt|;
block|}
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
name|val_array
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

