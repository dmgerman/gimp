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
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-types.h"
end_include

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
name|GParamSpecUInt
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
name|G_TYPE_PARAM_UINT
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
DECL|function|gimp_param_spec_memsize (const gchar * name,const gchar * nick,const gchar * blurb,guint minimum,guint maximum,guint default_value,GParamFlags flags)
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
name|guint
name|minimum
parameter_list|,
name|guint
name|maximum
parameter_list|,
name|guint
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GParamSpecUInt
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
name|GParamSpecString
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
DECL|function|gimp_param_spec_path (const gchar * name,const gchar * nick,const gchar * blurb,gchar * default_value,GParamFlags flags)
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
return|return
name|G_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
return|;
block|}
end_function

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
name|GParamSpecInt
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
DECL|function|gimp_param_spec_unit (const gchar * name,const gchar * nick,const gchar * blurb,GimpUnit default_value,GParamFlags flags)
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
name|GimpUnit
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GParamSpecInt
modifier|*
name|pspec
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
name|pspec
operator|->
name|default_value
operator|=
name|default_value
expr_stmt|;
name|pspec
operator|->
name|minimum
operator|=
name|GIMP_UNIT_INCH
expr_stmt|;
name|pspec
operator|->
name|maximum
operator|=
name|G_MAXINT
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

