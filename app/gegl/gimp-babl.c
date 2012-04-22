begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-babl.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_babl_init (void)
name|gimp_babl_init
parameter_list|(
name|void
parameter_list|)
block|{
name|babl_format_new
argument_list|(
literal|"name"
argument_list|,
literal|"R' u8"
argument_list|,
name|babl_model
argument_list|(
literal|"R'G'B'A"
argument_list|)
argument_list|,
name|babl_type
argument_list|(
literal|"u8"
argument_list|)
argument_list|,
name|babl_component
argument_list|(
literal|"R'"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|babl_format_new
argument_list|(
literal|"name"
argument_list|,
literal|"G' u8"
argument_list|,
name|babl_model
argument_list|(
literal|"R'G'B'A"
argument_list|)
argument_list|,
name|babl_type
argument_list|(
literal|"u8"
argument_list|)
argument_list|,
name|babl_component
argument_list|(
literal|"G'"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|babl_format_new
argument_list|(
literal|"name"
argument_list|,
literal|"B' u8"
argument_list|,
name|babl_model
argument_list|(
literal|"R'G'B'A"
argument_list|)
argument_list|,
name|babl_type
argument_list|(
literal|"u8"
argument_list|)
argument_list|,
name|babl_component
argument_list|(
literal|"B'"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|babl_format_new
argument_list|(
literal|"name"
argument_list|,
literal|"A u8"
argument_list|,
name|babl_model
argument_list|(
literal|"R'G'B'A"
argument_list|)
argument_list|,
name|babl_type
argument_list|(
literal|"u8"
argument_list|)
argument_list|,
name|babl_component
argument_list|(
literal|"A"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|babl_format_new
argument_list|(
literal|"name"
argument_list|,
literal|"A float"
argument_list|,
name|babl_model
argument_list|(
literal|"R'G'B'A"
argument_list|)
argument_list|,
name|babl_type
argument_list|(
literal|"float"
argument_list|)
argument_list|,
name|babl_component
argument_list|(
literal|"A"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|babl_format_new
argument_list|(
literal|"name"
argument_list|,
literal|"A double"
argument_list|,
name|babl_model
argument_list|(
literal|"R'G'B'A"
argument_list|)
argument_list|,
name|babl_type
argument_list|(
literal|"double"
argument_list|)
argument_list|,
name|babl_component
argument_list|(
literal|"A"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_struct
specifier|static
specifier|const
struct|struct
DECL|struct|__anon2ac0c7880108
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|description
specifier|const
name|gchar
modifier|*
name|description
decl_stmt|;
block|}
DECL|variable|babl_descriptions
name|babl_descriptions
index|[]
init|=
block|{
block|{
literal|"R'G'B' u8"
block|,
name|N_
argument_list|(
literal|"RGB"
argument_list|)
block|}
block|,
block|{
literal|"R'G'B'A u8"
block|,
name|N_
argument_list|(
literal|"RGB-alpha"
argument_list|)
block|}
block|,
block|{
literal|"Y' u8"
block|,
name|N_
argument_list|(
literal|"Grayscale"
argument_list|)
block|}
block|,
block|{
literal|"Y'A u8"
block|,
name|N_
argument_list|(
literal|"Grayscale-alpha"
argument_list|)
block|}
block|,
block|{
literal|"R' u8"
block|,
name|N_
argument_list|(
literal|"Red component"
argument_list|)
block|}
block|,
block|{
literal|"G' u8"
block|,
name|N_
argument_list|(
literal|"Green component"
argument_list|)
block|}
block|,
block|{
literal|"B' u8"
block|,
name|N_
argument_list|(
literal|"Blue component"
argument_list|)
block|}
block|,
block|{
literal|"A u8"
block|,
name|N_
argument_list|(
literal|"Alpha component"
argument_list|)
block|}
block|}
struct|;
end_struct

begin_decl_stmt
DECL|variable|babl_description_hash
specifier|static
name|GHashTable
modifier|*
name|babl_description_hash
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_babl_get_description (const Babl * babl)
name|gimp_babl_get_description
parameter_list|(
specifier|const
name|Babl
modifier|*
name|babl
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|description
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|babl
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|babl_description_hash
argument_list|)
condition|)
block|{
name|gint
name|i
decl_stmt|;
name|babl_description_hash
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
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
name|G_N_ELEMENTS
argument_list|(
name|babl_descriptions
argument_list|)
condition|;
name|i
operator|++
control|)
name|g_hash_table_insert
argument_list|(
name|babl_description_hash
argument_list|,
operator|(
name|gpointer
operator|)
name|babl_descriptions
index|[
name|i
index|]
operator|.
name|name
argument_list|,
name|gettext
argument_list|(
name|babl_descriptions
index|[
name|i
index|]
operator|.
name|description
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|babl_format_is_palette
argument_list|(
name|babl
argument_list|)
condition|)
block|{
if|if
condition|(
name|babl_format_has_alpha
argument_list|(
name|babl
argument_list|)
condition|)
return|return
name|_
argument_list|(
literal|"Indexed-alpha"
argument_list|)
return|;
else|else
return|return
name|_
argument_list|(
literal|"Indexed"
argument_list|)
return|;
block|}
name|description
operator|=
name|g_hash_table_lookup
argument_list|(
name|babl_description_hash
argument_list|,
name|babl_get_name
argument_list|(
name|babl
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|description
condition|)
return|return
name|description
return|;
return|return
name|g_strconcat
argument_list|(
literal|"ERROR: unknown Babl format "
argument_list|,
name|babl_get_name
argument_list|(
name|babl
argument_list|)
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpImageBaseType
DECL|function|gimp_babl_format_get_base_type (const Babl * format)
name|gimp_babl_format_get_base_type
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
condition|)
block|{
return|return
name|GIMP_GRAY
return|;
block|}
elseif|else
if|if
condition|(
name|format
operator|==
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
condition|)
block|{
return|return
name|GIMP_RGB
return|;
block|}
elseif|else
if|if
condition|(
name|babl_format_is_palette
argument_list|(
name|format
argument_list|)
condition|)
block|{
return|return
name|GIMP_INDEXED
return|;
block|}
name|g_return_val_if_reached
argument_list|(
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpPrecision
DECL|function|gimp_babl_format_get_precision (const Babl * format)
name|gimp_babl_format_get_precision
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|type
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|type
operator|=
name|babl_format_get_type
argument_list|(
name|format
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|==
name|babl_type
argument_list|(
literal|"u8"
argument_list|)
condition|)
return|return
name|GIMP_PRECISION_U8
return|;
name|g_return_val_if_reached
argument_list|(
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_babl_format (GimpImageBaseType base_type,GimpPrecision precision,gboolean with_alpha)
name|gimp_babl_format
parameter_list|(
name|GimpImageBaseType
name|base_type
parameter_list|,
name|GimpPrecision
name|precision
parameter_list|,
name|gboolean
name|with_alpha
parameter_list|)
block|{
switch|switch
condition|(
name|base_type
condition|)
block|{
case|case
name|GIMP_RGB
case|:
switch|switch
condition|(
name|precision
condition|)
block|{
case|case
name|GIMP_PRECISION_U8
case|:
if|if
condition|(
name|with_alpha
condition|)
return|return
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
return|;
else|else
return|return
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
return|;
default|default:
break|break;
block|}
break|break;
case|case
name|GIMP_GRAY
case|:
switch|switch
condition|(
name|precision
condition|)
block|{
case|case
name|GIMP_PRECISION_U8
case|:
if|if
condition|(
name|with_alpha
condition|)
return|return
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
return|;
else|else
return|return
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
return|;
default|default:
break|break;
block|}
break|break;
case|case
name|GIMP_INDEXED
case|:
comment|/* need to use the image's api for this */
break|break;
block|}
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

