begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * ParamSpecs for config objects  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-types.h"
end_include

begin_comment
comment|/*  * GIMP_TYPE_PARAM_COLOR  */
end_comment

begin_define
DECL|macro|GIMP_PARAM_SPEC_COLOR (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_COLOR
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_COLOR, GimpParamSpecColor))
end_define

begin_function_decl
specifier|static
name|void
name|gimp_param_color_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_param_color_init
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_param_color_set_default
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_param_color_validate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_param_color_values_cmp
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value1
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value2
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|GimpParamSpecColor
typedef|typedef
name|struct
name|_GimpParamSpecColor
name|GimpParamSpecColor
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecColor
struct|struct
name|_GimpParamSpecColor
block|{
DECL|member|parent_instance
name|GParamSpecBoxed
name|parent_instance
decl_stmt|;
DECL|member|default_value
name|GimpRGB
name|default_value
decl_stmt|;
block|}
struct|;
end_struct

begin_function
name|GType
DECL|function|gimp_param_color_get_type (void)
name|gimp_param_color_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|spec_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|spec_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GParamSpecClass
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_param_color_class_init
block|,
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpParamSpecColor
argument_list|)
block|,
literal|0
block|,
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_param_color_init
block|}
decl_stmt|;
name|spec_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_PARAM_BOXED
argument_list|,
literal|"GimpParamColor"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|spec_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_color_class_init (GParamSpecClass * class)
name|gimp_param_color_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
block|{
name|class
operator|->
name|value_type
operator|=
name|GIMP_TYPE_COLOR
expr_stmt|;
name|class
operator|->
name|value_set_default
operator|=
name|gimp_param_color_set_default
expr_stmt|;
name|class
operator|->
name|value_validate
operator|=
name|gimp_param_color_validate
expr_stmt|;
name|class
operator|->
name|values_cmp
operator|=
name|gimp_param_color_values_cmp
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_color_init (GParamSpec * pspec)
name|gimp_param_color_init
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpParamSpecColor
modifier|*
name|cspec
init|=
name|GIMP_PARAM_SPEC_COLOR
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|cspec
operator|->
name|default_value
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_color_set_default (GParamSpec * pspec,GValue * value)
name|gimp_param_color_set_default
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GimpParamSpecColor
modifier|*
name|cspec
init|=
name|GIMP_PARAM_SPEC_COLOR
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|g_value_set_static_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|cspec
operator|->
name|default_value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_param_color_validate (GParamSpec * pspec,GValue * value)
name|gimp_param_color_validate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GimpRGB
modifier|*
name|color
decl_stmt|;
name|color
operator|=
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
expr_stmt|;
if|if
condition|(
name|color
condition|)
block|{
name|GimpRGB
name|oval
decl_stmt|;
name|oval
operator|=
operator|*
name|color
expr_stmt|;
name|gimp_rgb_clamp
argument_list|(
name|color
argument_list|)
expr_stmt|;
return|return
operator|(
name|oval
operator|.
name|r
operator|!=
name|color
operator|->
name|r
operator|||
name|oval
operator|.
name|g
operator|!=
name|color
operator|->
name|g
operator|||
name|oval
operator|.
name|b
operator|!=
name|color
operator|->
name|b
operator|||
name|oval
operator|.
name|a
operator|!=
name|color
operator|->
name|a
operator|)
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_param_color_values_cmp (GParamSpec * pspec,const GValue * value1,const GValue * value2)
name|gimp_param_color_values_cmp
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value1
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value2
parameter_list|)
block|{
name|GimpRGB
modifier|*
name|color1
decl_stmt|;
name|GimpRGB
modifier|*
name|color2
decl_stmt|;
name|color1
operator|=
name|value1
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
expr_stmt|;
name|color2
operator|=
name|value2
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
expr_stmt|;
comment|/*  try to return at least *something*, it's useless anyway...  */
if|if
condition|(
operator|!
name|color1
condition|)
return|return
name|color2
operator|!=
name|NULL
condition|?
operator|-
literal|1
else|:
literal|0
return|;
elseif|else
if|if
condition|(
operator|!
name|color2
condition|)
return|return
name|color1
operator|!=
name|NULL
return|;
else|else
block|{
name|guint32
name|int1
decl_stmt|,
name|int2
decl_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|color1
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int1
operator|)
operator|+
literal|0
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int1
operator|)
operator|+
literal|1
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int1
operator|)
operator|+
literal|2
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int1
operator|)
operator|+
literal|3
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|color2
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int2
operator|)
operator|+
literal|0
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int2
operator|)
operator|+
literal|1
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int2
operator|)
operator|+
literal|2
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int2
operator|)
operator|+
literal|3
argument_list|)
expr_stmt|;
return|return
name|int1
operator|-
name|int2
return|;
block|}
block|}
end_function

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_param_spec_color (const gchar * name,const gchar * nick,const gchar * blurb,const GimpRGB * default_value,GParamFlags flags)
name|gimp_param_spec_color
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GimpParamSpecColor
modifier|*
name|cspec
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|default_value
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cspec
operator|=
name|g_param_spec_internal
argument_list|(
name|GIMP_TYPE_PARAM_COLOR
argument_list|,
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|cspec
operator|->
name|default_value
operator|=
operator|*
name|default_value
expr_stmt|;
return|return
name|G_PARAM_SPEC
argument_list|(
name|cspec
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * GIMP_TYPE_PARAM_MATRIX2  */
end_comment

begin_define
DECL|macro|GIMP_PARAM_SPEC_MATRIX2 (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_MATRIX2
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_MATRIX2, GimpParamSpecMatrix2))
end_define

begin_function_decl
specifier|static
name|void
name|gimp_param_matrix2_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_param_matrix2_init
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_param_matrix2_set_default
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_param_matrix2_values_cmp
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value1
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value2
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|GimpParamSpecMatrix2
typedef|typedef
name|struct
name|_GimpParamSpecMatrix2
name|GimpParamSpecMatrix2
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecMatrix2
struct|struct
name|_GimpParamSpecMatrix2
block|{
DECL|member|parent_instance
name|GParamSpecBoxed
name|parent_instance
decl_stmt|;
DECL|member|default_value
name|GimpMatrix2
name|default_value
decl_stmt|;
block|}
struct|;
end_struct

begin_function
name|GType
DECL|function|gimp_param_matrix2_get_type (void)
name|gimp_param_matrix2_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|spec_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|spec_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GParamSpecClass
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_param_matrix2_class_init
block|,
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpParamSpecMatrix2
argument_list|)
block|,
literal|0
block|,
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_param_matrix2_init
block|}
decl_stmt|;
name|spec_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_PARAM_BOXED
argument_list|,
literal|"GimpParamMatrix2"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|spec_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_matrix2_class_init (GParamSpecClass * class)
name|gimp_param_matrix2_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
block|{
name|class
operator|->
name|value_type
operator|=
name|GIMP_TYPE_MATRIX2
expr_stmt|;
name|class
operator|->
name|value_set_default
operator|=
name|gimp_param_matrix2_set_default
expr_stmt|;
name|class
operator|->
name|values_cmp
operator|=
name|gimp_param_matrix2_values_cmp
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_matrix2_init (GParamSpec * pspec)
name|gimp_param_matrix2_init
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpParamSpecMatrix2
modifier|*
name|cspec
init|=
name|GIMP_PARAM_SPEC_MATRIX2
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|gimp_matrix2_identity
argument_list|(
operator|&
name|cspec
operator|->
name|default_value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_matrix2_set_default (GParamSpec * pspec,GValue * value)
name|gimp_param_matrix2_set_default
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GimpParamSpecMatrix2
modifier|*
name|cspec
init|=
name|GIMP_PARAM_SPEC_MATRIX2
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|g_value_set_static_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|cspec
operator|->
name|default_value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_param_matrix2_values_cmp (GParamSpec * pspec,const GValue * value1,const GValue * value2)
name|gimp_param_matrix2_values_cmp
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value1
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value2
parameter_list|)
block|{
name|GimpMatrix2
modifier|*
name|matrix1
decl_stmt|;
name|GimpMatrix2
modifier|*
name|matrix2
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|matrix1
operator|=
name|value1
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
expr_stmt|;
name|matrix2
operator|=
name|value2
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
expr_stmt|;
comment|/*  try to return at least *something*, it's useless anyway...  */
if|if
condition|(
operator|!
name|matrix1
condition|)
return|return
name|matrix2
operator|!=
name|NULL
condition|?
operator|-
literal|1
else|:
literal|0
return|;
elseif|else
if|if
condition|(
operator|!
name|matrix2
condition|)
return|return
name|matrix1
operator|!=
name|NULL
return|;
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
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|2
condition|;
name|j
operator|++
control|)
if|if
condition|(
name|matrix1
operator|->
name|coeff
index|[
name|i
index|]
index|[
name|j
index|]
operator|!=
name|matrix2
operator|->
name|coeff
index|[
name|i
index|]
index|[
name|j
index|]
condition|)
return|return
literal|1
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_param_spec_matrix2 (const gchar * name,const gchar * nick,const gchar * blurb,const GimpMatrix2 * default_value,GParamFlags flags)
name|gimp_param_spec_matrix2
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|GimpMatrix2
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GimpParamSpecMatrix2
modifier|*
name|cspec
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|default_value
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cspec
operator|=
name|g_param_spec_internal
argument_list|(
name|GIMP_TYPE_PARAM_MATRIX2
argument_list|,
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|cspec
operator|->
name|default_value
operator|=
operator|*
name|default_value
expr_stmt|;
return|return
name|G_PARAM_SPEC
argument_list|(
name|cspec
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * GIMP_TYPE_PARAM_MEMSIZE  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_param_memsize_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_param_memsize_get_type (void)
name|gimp_param_memsize_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|spec_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|spec_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GParamSpecClass
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_param_memsize_class_init
block|,
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GParamSpecULong
argument_list|)
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|spec_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_PARAM_ULONG
argument_list|,
literal|"GimpParamMemsize"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|spec_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_memsize_class_init (GParamSpecClass * class)
name|gimp_param_memsize_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
block|{
name|class
operator|->
name|value_type
operator|=
name|GIMP_TYPE_MEMSIZE
expr_stmt|;
block|}
end_function

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_param_spec_memsize (const gchar * name,const gchar * nick,const gchar * blurb,gulong minimum,gulong maximum,gulong default_value,GParamFlags flags)
name|gimp_param_spec_memsize
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gulong
name|minimum
parameter_list|,
name|gulong
name|maximum
parameter_list|,
name|gulong
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GParamSpecULong
modifier|*
name|pspec
decl_stmt|;
name|pspec
operator|=
name|g_param_spec_internal
argument_list|(
name|GIMP_TYPE_PARAM_MEMSIZE
argument_list|,
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|pspec
operator|->
name|minimum
operator|=
name|minimum
expr_stmt|;
name|pspec
operator|->
name|maximum
operator|=
name|maximum
expr_stmt|;
name|pspec
operator|->
name|default_value
operator|=
name|default_value
expr_stmt|;
return|return
name|G_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * GIMP_TYPE_PARAM_PATH  */
end_comment

begin_define
DECL|macro|GIMP_PARAM_SPEC_PATH (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_PATH
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_PATH, GimpParamSpecPath))
end_define

begin_typedef
DECL|typedef|GimpParamSpecPath
typedef|typedef
name|struct
name|_GimpParamSpecPath
name|GimpParamSpecPath
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecPath
struct|struct
name|_GimpParamSpecPath
block|{
DECL|member|parent_instance
name|GParamSpecString
name|parent_instance
decl_stmt|;
DECL|member|type
name|GimpParamPathType
name|type
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_param_path_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_param_path_get_type (void)
name|gimp_param_path_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|spec_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|spec_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GParamSpecClass
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_param_path_class_init
block|,
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpParamSpecPath
argument_list|)
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|spec_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_PARAM_STRING
argument_list|,
literal|"GimpParamPath"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|spec_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_path_class_init (GParamSpecClass * class)
name|gimp_param_path_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
block|{
name|class
operator|->
name|value_type
operator|=
name|GIMP_TYPE_PATH
expr_stmt|;
block|}
end_function

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_param_spec_path (const gchar * name,const gchar * nick,const gchar * blurb,GimpParamPathType type,gchar * default_value,GParamFlags flags)
name|gimp_param_spec_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GimpParamPathType
name|type
parameter_list|,
name|gchar
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GParamSpecString
modifier|*
name|pspec
decl_stmt|;
name|pspec
operator|=
name|g_param_spec_internal
argument_list|(
name|GIMP_TYPE_PARAM_PATH
argument_list|,
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|pspec
operator|->
name|default_value
operator|=
name|default_value
expr_stmt|;
name|GIMP_PARAM_SPEC_PATH
argument_list|(
name|pspec
argument_list|)
operator|->
name|type
operator|=
name|type
expr_stmt|;
return|return
name|G_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpParamPathType
DECL|function|gimp_param_spec_path_type (GParamSpec * pspec)
name|gimp_param_spec_path_type
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PARAM_SPEC_PATH
argument_list|(
name|pspec
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GIMP_PARAM_SPEC_PATH
argument_list|(
name|pspec
argument_list|)
operator|->
name|type
return|;
block|}
end_function

begin_comment
comment|/*  * GIMP_TYPE_PARAM_UNIT  */
end_comment

begin_define
DECL|macro|GIMP_PARAM_SPEC_UNIT (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_UNIT
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_UNIT, GimpParamSpecUnit))
end_define

begin_typedef
DECL|typedef|GimpParamSpecUnit
typedef|typedef
name|struct
name|_GimpParamSpecUnit
name|GimpParamSpecUnit
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecUnit
struct|struct
name|_GimpParamSpecUnit
block|{
DECL|member|parent_instance
name|GParamSpecInt
name|parent_instance
decl_stmt|;
DECL|member|allow_percent
name|gboolean
name|allow_percent
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_param_unit_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_param_unit_value_validate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_param_unit_get_type (void)
name|gimp_param_unit_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|spec_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|spec_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GParamSpecClass
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_param_unit_class_init
block|,
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpParamSpecUnit
argument_list|)
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|spec_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_PARAM_INT
argument_list|,
literal|"GimpParamUnit"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|spec_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_unit_class_init (GParamSpecClass * class)
name|gimp_param_unit_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
block|{
name|class
operator|->
name|value_type
operator|=
name|GIMP_TYPE_UNIT
expr_stmt|;
name|class
operator|->
name|value_validate
operator|=
name|gimp_param_unit_value_validate
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_param_unit_value_validate (GParamSpec * pspec,GValue * value)
name|gimp_param_unit_value_validate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GParamSpecInt
modifier|*
name|ispec
init|=
name|G_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|GimpParamSpecUnit
modifier|*
name|uspec
init|=
name|GIMP_PARAM_SPEC_UNIT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|gint
name|oval
init|=
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
decl_stmt|;
if|if
condition|(
name|uspec
operator|->
name|allow_percent
operator|&&
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
operator|==
name|GIMP_UNIT_PERCENT
condition|)
block|{
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
operator|=
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
expr_stmt|;
block|}
else|else
block|{
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
operator|=
name|CLAMP
argument_list|(
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
argument_list|,
name|ispec
operator|->
name|minimum
argument_list|,
name|gimp_unit_get_number_of_units
argument_list|()
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
return|return
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
operator|!=
name|oval
return|;
block|}
end_function

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_param_spec_unit (const gchar * name,const gchar * nick,const gchar * blurb,gboolean allow_pixels,gboolean allow_percent,GimpUnit default_value,GParamFlags flags)
name|gimp_param_spec_unit
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gboolean
name|allow_pixels
parameter_list|,
name|gboolean
name|allow_percent
parameter_list|,
name|GimpUnit
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GimpParamSpecUnit
modifier|*
name|pspec
decl_stmt|;
name|GParamSpecInt
modifier|*
name|ispec
decl_stmt|;
name|pspec
operator|=
name|g_param_spec_internal
argument_list|(
name|GIMP_TYPE_PARAM_UNIT
argument_list|,
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|ispec
operator|=
name|G_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|ispec
operator|->
name|default_value
operator|=
name|default_value
expr_stmt|;
name|ispec
operator|->
name|minimum
operator|=
name|allow_pixels
condition|?
name|GIMP_UNIT_PIXEL
else|:
name|GIMP_UNIT_INCH
expr_stmt|;
name|ispec
operator|->
name|maximum
operator|=
name|GIMP_UNIT_PERCENT
operator|-
literal|1
expr_stmt|;
name|pspec
operator|->
name|allow_percent
operator|=
name|allow_percent
expr_stmt|;
return|return
name|G_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
return|;
block|}
end_function

end_unit

