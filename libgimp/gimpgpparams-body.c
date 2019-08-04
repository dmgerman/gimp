begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpgpparams-body.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  this file is included by both  *  *  libgimp/gimpgpparams.c  *  app/plug-in/gimpgpparams.c  */
end_comment

begin_function
name|void
DECL|function|_gimp_param_spec_to_gp_param_def (GParamSpec * pspec,GPParamDef * param_def)
name|_gimp_param_spec_to_gp_param_def
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GPParamDef
modifier|*
name|param_def
parameter_list|)
block|{
name|GType
name|pspec_type
decl_stmt|;
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_DEFAULT
expr_stmt|;
name|param_def
operator|->
name|type_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|G_PARAM_SPEC_TYPE_NAME
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|param_def
operator|->
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|param_def
operator|->
name|nick
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|param_def
operator|->
name|blurb
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_param_spec_get_blurb
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|pspec_type
operator|=
name|G_PARAM_SPEC_TYPE
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
if|if
condition|(
name|pspec_type
operator|==
name|G_TYPE_PARAM_INT
operator|||
name|pspec_type
operator|==
name|GIMP_TYPE_PARAM_INT32
operator|||
name|pspec_type
operator|==
name|GIMP_TYPE_PARAM_INT16
condition|)
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
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_INT
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|min_val
operator|=
name|ispec
operator|->
name|minimum
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|max_val
operator|=
name|ispec
operator|->
name|maximum
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|default_val
operator|=
name|ispec
operator|->
name|default_value
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pspec_type
operator|==
name|GIMP_TYPE_PARAM_INT8
condition|)
block|{
name|GParamSpecUInt
modifier|*
name|uspec
init|=
name|G_PARAM_SPEC_UINT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_INT
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|min_val
operator|=
name|uspec
operator|->
name|minimum
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|max_val
operator|=
name|uspec
operator|->
name|maximum
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|default_val
operator|=
name|uspec
operator|->
name|default_value
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pspec_type
operator|==
name|GIMP_TYPE_PARAM_UNIT
condition|)
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
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_UNIT
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_unit
operator|.
name|allow_pixels
operator|=
operator|(
name|ispec
operator|->
name|minimum
operator|<
name|GIMP_UNIT_INCH
operator|)
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_unit
operator|.
name|allow_percent
operator|=
name|uspec
operator|->
name|allow_percent
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_unit
operator|.
name|default_val
operator|=
name|ispec
operator|->
name|default_value
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pspec_type
operator|==
name|G_TYPE_PARAM_ENUM
condition|)
block|{
name|GParamSpecEnum
modifier|*
name|espec
init|=
name|G_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|GType
name|enum_type
init|=
name|pspec
operator|->
name|value_type
decl_stmt|;
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_ENUM
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_enum
operator|.
name|type_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_type_name
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_enum
operator|.
name|default_val
operator|=
name|espec
operator|->
name|default_value
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pspec_type
operator|==
name|G_TYPE_PARAM_BOOLEAN
condition|)
block|{
name|GParamSpecBoolean
modifier|*
name|bspec
init|=
name|G_PARAM_SPEC_BOOLEAN
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_BOOLEAN
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_boolean
operator|.
name|default_val
operator|=
name|bspec
operator|->
name|default_value
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pspec_type
operator|==
name|G_TYPE_PARAM_DOUBLE
condition|)
block|{
name|GParamSpecDouble
modifier|*
name|dspec
init|=
name|G_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_FLOAT
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_float
operator|.
name|min_val
operator|=
name|dspec
operator|->
name|minimum
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_float
operator|.
name|max_val
operator|=
name|dspec
operator|->
name|maximum
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_float
operator|.
name|default_val
operator|=
name|dspec
operator|->
name|default_value
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pspec_type
operator|==
name|GIMP_TYPE_PARAM_STRING
operator|||
name|pspec_type
operator|==
name|G_TYPE_PARAM_STRING
condition|)
block|{
name|GParamSpecString
modifier|*
name|gsspec
init|=
name|G_PARAM_SPEC_STRING
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_STRING
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_string
operator|.
name|null_ok
operator|=
operator|!
name|gsspec
operator|->
name|ensure_non_null
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_string
operator|.
name|default_val
operator|=
name|gsspec
operator|->
name|default_value
expr_stmt|;
if|if
condition|(
name|pspec_type
operator|==
name|GIMP_TYPE_PARAM_STRING
condition|)
block|{
name|GimpParamSpecString
modifier|*
name|sspec
init|=
name|GIMP_PARAM_SPEC_STRING
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_string
operator|.
name|allow_non_utf8
operator|=
name|sspec
operator|->
name|allow_non_utf8
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_string
operator|.
name|non_empty
operator|=
name|sspec
operator|->
name|non_empty
expr_stmt|;
block|}
else|else
block|{
name|param_def
operator|->
name|meta
operator|.
name|m_string
operator|.
name|allow_non_utf8
operator|=
name|FALSE
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_string
operator|.
name|non_empty
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|pspec_type
operator|==
name|GIMP_TYPE_PARAM_RGB
condition|)
block|{
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_COLOR
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_color
operator|.
name|has_alpha
operator|=
name|gimp_param_spec_rgb_has_alpha
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|gimp_param_spec_rgb_get_default
argument_list|(
name|pspec
argument_list|,
operator|&
name|param_def
operator|->
name|meta
operator|.
name|m_color
operator|.
name|default_val
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pspec_type
operator|==
name|GIMP_TYPE_PARAM_DISPLAY_ID
condition|)
block|{
name|GimpParamSpecDisplayID
modifier|*
name|ispec
init|=
name|GIMP_PARAM_SPEC_DISPLAY_ID
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_ID
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
operator|=
name|ispec
operator|->
name|none_ok
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pspec_type
operator|==
name|GIMP_TYPE_PARAM_IMAGE_ID
condition|)
block|{
name|GimpParamSpecImageID
modifier|*
name|ispec
init|=
name|GIMP_PARAM_SPEC_IMAGE_ID
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_ID
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
operator|=
name|ispec
operator|->
name|none_ok
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_ITEM_ID
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GimpParamSpecItemID
modifier|*
name|ispec
init|=
name|GIMP_PARAM_SPEC_ITEM_ID
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|param_def
operator|->
name|param_def_type
operator|=
name|GP_PARAM_DEF_TYPE_ID
expr_stmt|;
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
operator|=
name|ispec
operator|->
name|none_ok
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|_gimp_gp_param_to_value (gpointer gimp,GPParam * param,GType type,GValue * value,gboolean full_copy)
name|_gimp_gp_param_to_value
parameter_list|(
name|gpointer
name|gimp
parameter_list|,
name|GPParam
modifier|*
name|param
parameter_list|,
name|GType
name|type
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|gboolean
name|full_copy
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|param
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|value
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|==
name|G_TYPE_NONE
condition|)
name|type
operator|=
name|g_type_from_name
argument_list|(
name|param
operator|->
name|type_name
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
name|value
argument_list|,
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|==
name|G_TYPE_INT
operator|||
name|type
operator|==
name|GIMP_TYPE_INT32
operator|||
name|type
operator|==
name|GIMP_TYPE_INT16
operator|||
name|type
operator|==
name|GIMP_TYPE_UNIT
condition|)
block|{
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_int
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_UINT
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|g_value_set_uint
argument_list|(
name|value
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_int
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_ENUM
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_int
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_BOOLEAN
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_int
condition|?
name|TRUE
else|:
name|FALSE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_DOUBLE
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_float
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_STRING
argument_list|(
name|value
argument_list|)
condition|)
block|{
if|if
condition|(
name|full_copy
condition|)
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
else|else
name|g_value_set_static_string
argument_list|(
name|value
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_RGB
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|gimp_value_set_rgb
argument_list|(
name|value
argument_list|,
operator|&
name|param
operator|->
name|data
operator|.
name|d_color
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_PARASITE
argument_list|(
name|value
argument_list|)
condition|)
block|{
if|if
condition|(
name|full_copy
condition|)
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|param
operator|->
name|data
operator|.
name|d_parasite
argument_list|)
expr_stmt|;
else|else
name|g_value_set_static_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|param
operator|->
name|data
operator|.
name|d_parasite
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_INT32_ARRAY
argument_list|(
name|value
argument_list|)
condition|)
block|{
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_int32_array
argument_list|(
name|value
argument_list|,
operator|(
name|gint32
operator|*
operator|)
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|/
sizeof|sizeof
argument_list|(
name|gint32
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_int32_array
argument_list|(
name|value
argument_list|,
operator|(
name|gint32
operator|*
operator|)
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|/
sizeof|sizeof
argument_list|(
name|gint32
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_INT16_ARRAY
argument_list|(
name|value
argument_list|)
condition|)
block|{
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_int16_array
argument_list|(
name|value
argument_list|,
operator|(
name|gint16
operator|*
operator|)
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|/
sizeof|sizeof
argument_list|(
name|gint16
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_int16_array
argument_list|(
name|value
argument_list|,
operator|(
name|gint16
operator|*
operator|)
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|/
sizeof|sizeof
argument_list|(
name|gint16
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_INT8_ARRAY
argument_list|(
name|value
argument_list|)
condition|)
block|{
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_int8_array
argument_list|(
name|value
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|/
sizeof|sizeof
argument_list|(
name|guint8
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_int8_array
argument_list|(
name|value
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|/
sizeof|sizeof
argument_list|(
name|guint8
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_FLOAT_ARRAY
argument_list|(
name|value
argument_list|)
condition|)
block|{
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_float_array
argument_list|(
name|value
argument_list|,
operator|(
specifier|const
name|gdouble
operator|*
operator|)
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|/
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_float_array
argument_list|(
name|value
argument_list|,
operator|(
specifier|const
name|gdouble
operator|*
operator|)
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|/
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_STRING_ARRAY
argument_list|(
name|value
argument_list|)
condition|)
block|{
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_string_array
argument_list|(
name|value
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|param
operator|->
name|data
operator|.
name|d_string_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_string_array
operator|.
name|size
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_string_array
argument_list|(
name|value
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|param
operator|->
name|data
operator|.
name|d_string_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_string_array
operator|.
name|size
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_RGB_ARRAY
argument_list|(
name|value
argument_list|)
condition|)
block|{
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_rgb_array
argument_list|(
name|value
argument_list|,
operator|(
name|GimpRGB
operator|*
operator|)
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|/
sizeof|sizeof
argument_list|(
name|GimpRGB
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_rgb_array
argument_list|(
name|value
argument_list|,
operator|(
name|GimpRGB
operator|*
operator|)
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|/
sizeof|sizeof
argument_list|(
name|GimpRGB
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_DISPLAY_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_IMAGE_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_ITEM_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_DRAWABLE_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_LAYER_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_CHANNEL_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_LAYER_MASK_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_SELECTION_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_VECTORS_ID
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|param
operator|->
name|data
operator|.
name|d_int
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_PARAM
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|GParamSpec
modifier|*
name|pspec
init|=
name|_gimp_gp_param_def_to_param_spec
argument_list|(
name|gimp
argument_list|,
operator|&
name|param
operator|->
name|data
operator|.
name|d_param_def
argument_list|)
decl_stmt|;
name|g_value_take_param
argument_list|(
name|value
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpValueArray
modifier|*
DECL|function|_gimp_gp_params_to_value_array (gpointer gimp,GParamSpec ** pspecs,gint n_pspecs,GPParam * params,gint n_params,gboolean return_values,gboolean full_copy)
name|_gimp_gp_params_to_value_array
parameter_list|(
name|gpointer
name|gimp
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|,
name|gint
name|n_pspecs
parameter_list|,
name|GPParam
modifier|*
name|params
parameter_list|,
name|gint
name|n_params
parameter_list|,
name|gboolean
name|return_values
parameter_list|,
name|gboolean
name|full_copy
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|(
name|params
operator|!=
name|NULL
operator|&&
name|n_params
operator|>
literal|0
operator|)
operator|||
operator|(
name|params
operator|==
name|NULL
operator|&&
name|n_params
operator|==
literal|0
operator|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|args
operator|=
name|gimp_value_array_new
argument_list|(
name|n_params
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
name|n_params
condition|;
name|i
operator|++
control|)
block|{
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|GType
name|type
decl_stmt|;
comment|/*  first get the GType from the passed GPParam  */
name|type
operator|=
name|g_type_from_name
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|type_name
argument_list|)
expr_stmt|;
comment|/*  then try to try to be more specific by looking at the param        *  spec (return values have one additional value (the status),        *  skip that, it's not in the array of param specs)        */
if|if
condition|(
name|i
operator|>
literal|0
operator|||
operator|!
name|return_values
condition|)
block|{
name|gint
name|pspec_index
init|=
name|i
decl_stmt|;
if|if
condition|(
name|return_values
condition|)
name|pspec_index
operator|--
expr_stmt|;
comment|/*  are there param specs left?  */
if|if
condition|(
name|pspec_index
operator|<
name|n_pspecs
condition|)
block|{
name|GType
name|pspec_type
init|=
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|pspecs
index|[
name|pspec_index
index|]
argument_list|)
decl_stmt|;
if|if
condition|(
name|type
operator|!=
name|pspec_type
condition|)
block|{
if|if
condition|(
name|g_type_is_a
argument_list|(
name|pspec_type
argument_list|,
name|type
argument_list|)
condition|)
block|{
comment|/*  if the param spec's GType is more specific                        *  than the one from the GPParam, use the param                        *  spec's GType.                        */
name|type
operator|=
name|pspec_type
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|type
operator|==
name|GIMP_TYPE_INT32
condition|)
block|{
if|if
condition|(
name|g_type_is_a
argument_list|(
name|pspec_type
argument_list|,
name|G_TYPE_ENUM
argument_list|)
condition|)
block|{
comment|/*  if the param spec's type is enum, but an                            *  int32 was passed, use the enum type.                            */
name|type
operator|=
name|pspec_type
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|pspec_type
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|)
condition|)
block|{
comment|/*  if the param spec's type is boolean, but                            *  an int32 was passed, use the boolean                            *  type.                            */
name|type
operator|=
name|pspec_type
expr_stmt|;
block|}
block|}
block|}
block|}
block|}
name|_gimp_gp_param_to_value
argument_list|(
name|gimp
argument_list|,
operator|&
name|params
index|[
name|i
index|]
argument_list|,
name|type
argument_list|,
operator|&
name|value
argument_list|,
name|full_copy
argument_list|)
expr_stmt|;
name|gimp_value_array_append
argument_list|(
name|args
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|args
return|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_value_to_gp_param (const GValue * value,GPParam * param,gboolean full_copy)
name|_gimp_value_to_gp_param
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GPParam
modifier|*
name|param
parameter_list|,
name|gboolean
name|full_copy
parameter_list|)
block|{
name|GType
name|type
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|value
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|param
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|type
operator|=
name|G_VALUE_TYPE
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|param
operator|->
name|param_type
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
name|param
operator|->
name|type_name
operator|=
name|g_strdup
argument_list|(
name|g_type_name
argument_list|(
name|type
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|param
operator|->
name|type_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_type_name
argument_list|(
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|==
name|G_TYPE_INT
operator|||
name|type
operator|==
name|GIMP_TYPE_INT32
operator|||
name|type
operator|==
name|GIMP_TYPE_INT16
operator|||
name|type
operator|==
name|GIMP_TYPE_UNIT
condition|)
block|{
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_INT
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_int
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|type
operator|==
name|G_TYPE_UINT
operator|||
name|type
operator|==
name|GIMP_TYPE_INT8
condition|)
block|{
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_INT
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_int
operator|=
name|g_value_get_uint
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_ENUM
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_INT
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_int
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_BOOLEAN
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_INT
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_int
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_DOUBLE
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_FLOAT
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_float
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_STRING
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_STRING
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
name|param
operator|->
name|data
operator|.
name|d_string
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|param
operator|->
name|data
operator|.
name|d_string
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_RGB
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_COLOR
expr_stmt|;
name|gimp_value_get_rgb
argument_list|(
name|value
argument_list|,
operator|&
name|param
operator|->
name|data
operator|.
name|d_color
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_PARASITE
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
init|=
operator|(
name|full_copy
condition|?
name|g_value_dup_boxed
argument_list|(
name|value
argument_list|)
else|:
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
operator|)
decl_stmt|;
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_PARASITE
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|param
operator|->
name|data
operator|.
name|d_parasite
operator|.
name|name
operator|=
name|parasite
operator|->
name|name
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_parasite
operator|.
name|flags
operator|=
name|parasite
operator|->
name|flags
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_parasite
operator|.
name|size
operator|=
name|parasite
operator|->
name|size
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_parasite
operator|.
name|data
operator|=
name|parasite
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
block|{
name|parasite
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|parasite
operator|->
name|flags
operator|=
literal|0
expr_stmt|;
name|parasite
operator|->
name|size
operator|=
literal|0
expr_stmt|;
name|parasite
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|param
operator|->
name|data
operator|.
name|d_parasite
operator|.
name|name
operator|=
name|NULL
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_parasite
operator|.
name|flags
operator|=
literal|0
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_parasite
operator|.
name|size
operator|=
literal|0
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_parasite
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_INT32_ARRAY
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_INT16_ARRAY
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_INT8_ARRAY
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_FLOAT_ARRAY
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_RGB_ARRAY
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|GimpArray
modifier|*
name|array
init|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_ARRAY
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|size
operator|=
name|array
operator|->
name|length
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
operator|=
name|g_memdup
argument_list|(
name|array
operator|->
name|data
argument_list|,
name|array
operator|->
name|length
argument_list|)
expr_stmt|;
else|else
name|param
operator|->
name|data
operator|.
name|d_array
operator|.
name|data
operator|=
name|array
operator|->
name|data
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_STRING_ARRAY
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|GimpArray
modifier|*
name|array
init|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_STRING_ARRAY
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_string_array
operator|.
name|size
operator|=
name|array
operator|->
name|length
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
name|param
operator|->
name|data
operator|.
name|d_string_array
operator|.
name|data
operator|=
name|gimp_value_dup_string_array
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|param
operator|->
name|data
operator|.
name|d_string_array
operator|.
name|data
operator|=
operator|(
name|gchar
operator|*
operator|*
operator|)
name|gimp_value_get_string_array
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_DISPLAY_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_IMAGE_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_ITEM_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_DRAWABLE_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_LAYER_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_CHANNEL_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_LAYER_MASK_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_SELECTION_ID
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_VECTORS_ID
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_INT
expr_stmt|;
name|param
operator|->
name|data
operator|.
name|d_int
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_PARAM
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|param
operator|->
name|param_type
operator|=
name|GP_PARAM_TYPE_PARAM_DEF
expr_stmt|;
name|_gimp_param_spec_to_gp_param_def
argument_list|(
name|g_value_get_param
argument_list|(
name|value
argument_list|)
argument_list|,
operator|&
name|param
operator|->
name|data
operator|.
name|d_param_def
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|param
operator|->
name|param_type
operator|==
operator|-
literal|1
condition|)
name|g_printerr
argument_list|(
literal|"%s: GValue contains unsupported type '%s'\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|param
operator|->
name|type_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GPParam
modifier|*
DECL|function|_gimp_value_array_to_gp_params (GimpValueArray * args,gboolean full_copy)
name|_gimp_value_array_to_gp_params
parameter_list|(
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gboolean
name|full_copy
parameter_list|)
block|{
name|GPParam
modifier|*
name|params
decl_stmt|;
name|gint
name|length
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|args
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|length
operator|=
name|gimp_value_array_length
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|params
operator|=
name|g_new0
argument_list|(
name|GPParam
argument_list|,
name|length
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
name|length
condition|;
name|i
operator|++
control|)
block|{
name|GValue
modifier|*
name|value
init|=
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|_gimp_value_to_gp_param
argument_list|(
name|value
argument_list|,
operator|&
name|params
index|[
name|i
index|]
argument_list|,
name|full_copy
argument_list|)
expr_stmt|;
block|}
return|return
name|params
return|;
block|}
end_function

end_unit

