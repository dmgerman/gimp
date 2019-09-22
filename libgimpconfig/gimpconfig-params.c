begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpconfig-params.c  * Copyright (C) 2008-2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gegl-paramspecs.h>
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig.h"
end_include

begin_comment
comment|/**  * SECTION: gimpconfig-params  * @title: GimpConfig-params  * @short_description: Macros and defines to install config properties.  *  * Macros and defines to install config properties.  **/
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_gegl_param_spec_has_key (GParamSpec * pspec,const gchar * key,const gchar * value)
name|gimp_gegl_param_spec_has_key
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|v
init|=
name|gegl_param_spec_get_property_key
argument_list|(
name|pspec
argument_list|,
name|key
argument_list|)
decl_stmt|;
if|if
condition|(
name|v
operator|&&
operator|!
name|strcmp
argument_list|(
name|v
argument_list|,
name|value
argument_list|)
condition|)
return|return
name|TRUE
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_param_spec_duplicate:  * @pspec: the #GParamSpec to duplicate  *  * Creates an exact copy of @pspec, with all its properties, returns  * %NULL if @pspec is of an unknown type that can't be duplicated.  *  * Return: (transfer full): The new #GParamSpec, or %NULL.  *  * Since: 3.0  **/
end_comment

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_config_param_spec_duplicate (GParamSpec * pspec)
name|gimp_config_param_spec_duplicate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|copy
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|nick
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|blurb
decl_stmt|;
name|GParamFlags
name|flags
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|pspec
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|name
operator|=
name|pspec
operator|->
name|name
expr_stmt|;
name|nick
operator|=
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|blurb
operator|=
name|g_param_spec_get_blurb
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|flags
operator|=
name|pspec
operator|->
name|flags
expr_stmt|;
comment|/*  this special case exists for the GEGL tool, we don't want this    *  property serialized    */
if|if
condition|(
operator|!
name|gimp_gegl_param_spec_has_key
argument_list|(
name|pspec
argument_list|,
literal|"role"
argument_list|,
literal|"output-extent"
argument_list|)
condition|)
name|flags
operator||=
name|GIMP_CONFIG_PARAM_SERIALIZE
expr_stmt|;
if|if
condition|(
name|G_IS_PARAM_SPEC_STRING
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GParamSpecString
modifier|*
name|spec
init|=
name|G_PARAM_SPEC_STRING
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_FILE_PATH
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|copy
operator|=
name|gimp_param_spec_config_path
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|GIMP_CONFIG_PATH_FILE
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_CONFIG_PATH
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|copy
operator|=
name|gimp_param_spec_config_path
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp_param_spec_config_path_type
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|copy
operator|=
name|g_param_spec_string
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_BOOLEAN
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GParamSpecBoolean
modifier|*
name|spec
init|=
name|G_PARAM_SPEC_BOOLEAN
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|copy
operator|=
name|g_param_spec_boolean
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GParamSpecEnum
modifier|*
name|spec
init|=
name|G_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|copy
operator|=
name|g_param_spec_enum
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|spec
operator|->
name|enum_class
argument_list|)
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GParamSpecDouble
modifier|*
name|spec
init|=
name|G_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GeglParamSpecDouble
modifier|*
name|gspec
init|=
name|GEGL_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|copy
operator|=
name|gegl_param_spec_double
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|spec
operator|->
name|minimum
argument_list|,
name|spec
operator|->
name|maximum
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|gspec
operator|->
name|ui_minimum
argument_list|,
name|gspec
operator|->
name|ui_maximum
argument_list|,
name|gspec
operator|->
name|ui_gamma
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|gegl_param_spec_double_set_steps
argument_list|(
name|GEGL_PARAM_SPEC_DOUBLE
argument_list|(
name|copy
argument_list|)
argument_list|,
name|gspec
operator|->
name|ui_step_small
argument_list|,
name|gspec
operator|->
name|ui_step_big
argument_list|)
expr_stmt|;
name|gegl_param_spec_double_set_digits
argument_list|(
name|GEGL_PARAM_SPEC_DOUBLE
argument_list|(
name|copy
argument_list|)
argument_list|,
name|gspec
operator|->
name|ui_digits
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|copy
operator|=
name|g_param_spec_double
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|spec
operator|->
name|minimum
argument_list|,
name|spec
operator|->
name|maximum
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_FLOAT
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GParamSpecFloat
modifier|*
name|spec
init|=
name|G_PARAM_SPEC_FLOAT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|copy
operator|=
name|g_param_spec_float
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|spec
operator|->
name|minimum
argument_list|,
name|spec
operator|->
name|maximum
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GParamSpecInt
modifier|*
name|spec
init|=
name|G_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GeglParamSpecInt
modifier|*
name|gspec
init|=
name|GEGL_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|copy
operator|=
name|gegl_param_spec_int
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|spec
operator|->
name|minimum
argument_list|,
name|spec
operator|->
name|maximum
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|gspec
operator|->
name|ui_minimum
argument_list|,
name|gspec
operator|->
name|ui_maximum
argument_list|,
name|gspec
operator|->
name|ui_gamma
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|gegl_param_spec_int_set_steps
argument_list|(
name|GEGL_PARAM_SPEC_INT
argument_list|(
name|copy
argument_list|)
argument_list|,
name|gspec
operator|->
name|ui_step_small
argument_list|,
name|gspec
operator|->
name|ui_step_big
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_UNIT
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GimpParamSpecUnit
modifier|*
name|spec
init|=
name|GIMP_PARAM_SPEC_UNIT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|GParamSpecInt
modifier|*
name|ispec
init|=
name|G_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|copy
operator|=
name|gimp_param_spec_unit
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|ispec
operator|->
name|minimum
operator|==
name|GIMP_UNIT_PIXEL
argument_list|,
name|spec
operator|->
name|allow_percent
argument_list|,
name|ispec
operator|->
name|default_value
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|copy
operator|=
name|g_param_spec_int
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|spec
operator|->
name|minimum
argument_list|,
name|spec
operator|->
name|maximum
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_UINT
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GParamSpecUInt
modifier|*
name|spec
init|=
name|G_PARAM_SPEC_UINT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_SEED
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GeglParamSpecSeed
modifier|*
name|gspec
init|=
name|GEGL_PARAM_SPEC_SEED
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|copy
operator|=
name|gegl_param_spec_seed
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|G_PARAM_SPEC_UINT
argument_list|(
name|copy
argument_list|)
operator|->
name|minimum
operator|=
name|spec
operator|->
name|minimum
expr_stmt|;
name|G_PARAM_SPEC_UINT
argument_list|(
name|copy
argument_list|)
operator|->
name|maximum
operator|=
name|spec
operator|->
name|maximum
expr_stmt|;
name|G_PARAM_SPEC_UINT
argument_list|(
name|copy
argument_list|)
operator|->
name|default_value
operator|=
name|spec
operator|->
name|default_value
expr_stmt|;
name|GEGL_PARAM_SPEC_SEED
argument_list|(
name|copy
argument_list|)
operator|->
name|ui_minimum
operator|=
name|gspec
operator|->
name|ui_minimum
expr_stmt|;
name|GEGL_PARAM_SPEC_SEED
argument_list|(
name|copy
argument_list|)
operator|->
name|ui_maximum
operator|=
name|gspec
operator|->
name|ui_maximum
expr_stmt|;
block|}
else|else
block|{
name|copy
operator|=
name|g_param_spec_uint
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|spec
operator|->
name|minimum
argument_list|,
name|spec
operator|->
name|maximum
argument_list|,
name|spec
operator|->
name|default_value
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_RGB
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_param_spec_rgb_get_default
argument_list|(
name|pspec
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|copy
operator|=
name|gimp_param_spec_rgb
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp_param_spec_rgb_has_alpha
argument_list|(
name|pspec
argument_list|)
argument_list|,
operator|&
name|color
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_COLOR
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GeglColor
modifier|*
name|gegl_color
decl_stmt|;
name|GimpRGB
name|gimp_color
decl_stmt|;
name|gdouble
name|r
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|g
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|b
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|a
init|=
literal|1.0
decl_stmt|;
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|GEGL_TYPE_COLOR
argument_list|)
expr_stmt|;
name|g_param_value_set_default
argument_list|(
name|pspec
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|gegl_color
operator|=
name|g_value_get_object
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|gegl_color
condition|)
name|gegl_color_get_rgba
argument_list|(
name|gegl_color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|,
operator|&
name|a
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|gimp_color
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|a
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
name|copy
operator|=
name|gimp_param_spec_rgb
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|TRUE
argument_list|,
operator|&
name|gimp_color
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_PARAM
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|copy
operator|=
name|g_param_spec_param
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_PARASITE
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|copy
operator|=
name|gimp_param_spec_parasite
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_ARRAY
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_UINT8_ARRAY
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|copy
operator|=
name|gimp_param_spec_uint8_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_INT16_ARRAY
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|copy
operator|=
name|gimp_param_spec_int16_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_INT32_ARRAY
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|copy
operator|=
name|gimp_param_spec_int32_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_FLOAT_ARRAY
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|copy
operator|=
name|gimp_param_spec_float_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_STRING_ARRAY
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|copy
operator|=
name|gimp_param_spec_string_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_RGB_ARRAY
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|copy
operator|=
name|gimp_param_spec_rgb_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_OBJECT_ARRAY
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GimpParamSpecObjectArray
modifier|*
name|spec
init|=
name|GIMP_PARAM_SPEC_OBJECT_ARRAY
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|copy
operator|=
name|gimp_param_spec_object_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|spec
operator|->
name|object_type
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_OBJECT
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GType
name|value_type
init|=
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
if|if
condition|(
name|value_type
operator|==
name|G_TYPE_FILE
condition|)
block|{
name|copy
operator|=
name|g_param_spec_object
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|value_type
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|copy
condition|)
block|{
name|GQuark
name|quark
init|=
name|g_quark_from_static_string
argument_list|(
literal|"gegl-property-keys"
argument_list|)
decl_stmt|;
name|GHashTable
modifier|*
name|keys
init|=
name|g_param_spec_get_qdata
argument_list|(
name|pspec
argument_list|,
name|quark
argument_list|)
decl_stmt|;
if|if
condition|(
name|keys
condition|)
name|g_param_spec_set_qdata_full
argument_list|(
name|copy
argument_list|,
name|quark
argument_list|,
name|g_hash_table_ref
argument_list|(
name|keys
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_hash_table_unref
argument_list|)
expr_stmt|;
block|}
return|return
name|copy
return|;
block|}
end_function

end_unit
