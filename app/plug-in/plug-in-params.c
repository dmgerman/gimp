begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpprotocol.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimp-pdb-compat.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-params.h"
end_include

begin_function
name|GimpValueArray
modifier|*
DECL|function|plug_in_params_to_args (GParamSpec ** pspecs,gint n_pspecs,GPParam * params,gint n_params,gboolean return_values,gboolean full_copy)
name|plug_in_params_to_args
parameter_list|(
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
name|pspecs
operator|!=
name|NULL
operator|&&
name|n_pspecs
operator|>
literal|0
operator|)
operator|||
operator|(
name|pspecs
operator|==
name|NULL
operator|&&
name|n_pspecs
operator|==
literal|0
operator|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
block|{
literal|0
block|, }
decl_stmt|;
name|GType
name|type
decl_stmt|;
name|gint
name|count
decl_stmt|;
comment|/*  first get the fallback compat GType that matches the pdb type  */
name|type
operator|=
name|gimp_pdb_compat_arg_type_to_gtype
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|type
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
name|GimpPDBArgType
name|pspec_arg_type
decl_stmt|;
name|pspec_arg_type
operator|=
name|gimp_pdb_compat_arg_type_from_gtype
argument_list|(
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|pspecs
index|[
name|pspec_index
index|]
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  if the param spec's GType, mapped to a pdb type, matches                *  the passed pdb type, use the param spec's GType                */
if|if
condition|(
name|pspec_arg_type
operator|==
name|params
index|[
name|i
index|]
operator|.
name|type
condition|)
block|{
name|type
operator|=
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|pspecs
index|[
name|pspec_index
index|]
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|type
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_pdb_compat_arg_type_from_gtype
argument_list|(
name|type
argument_list|)
condition|)
block|{
case|case
name|GIMP_PDB_INT32
case|:
if|if
condition|(
name|G_VALUE_HOLDS_INT
argument_list|(
operator|&
name|value
argument_list|)
condition|)
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_UINT
argument_list|(
operator|&
name|value
argument_list|)
condition|)
name|g_value_set_uint
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_ENUM
argument_list|(
operator|&
name|value
argument_list|)
condition|)
name|g_value_set_enum
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_BOOLEAN
argument_list|(
operator|&
name|value
argument_list|)
condition|)
name|g_value_set_boolean
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32
condition|?
name|TRUE
else|:
name|FALSE
argument_list|)
expr_stmt|;
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s: unhandled GIMP_PDB_INT32 type: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|g_type_name
argument_list|(
name|G_VALUE_TYPE
argument_list|(
operator|&
name|value
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_reached
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_INT16
case|:
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8
case|:
name|g_value_set_uint
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOAT
case|:
name|g_value_set_double
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_float
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRING
case|:
if|if
condition|(
name|full_copy
condition|)
name|g_value_set_string
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
else|else
name|g_value_set_static_string
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT32ARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
name|i
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_int32array
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32array
argument_list|,
name|count
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_int32array
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32array
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT16ARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
name|i
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_int16array
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16array
argument_list|,
name|count
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_int16array
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16array
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8ARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
name|i
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_int8array
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|,
name|count
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_int8array
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOATARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
name|i
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_floatarray
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_floatarray
argument_list|,
name|count
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_floatarray
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_floatarray
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRINGARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
name|i
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_stringarray
argument_list|(
operator|&
name|value
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_stringarray
argument_list|,
name|count
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_stringarray
argument_list|(
operator|&
name|value
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_stringarray
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_COLOR
case|:
name|gimp_value_set_rgb
argument_list|(
operator|&
name|value
argument_list|,
operator|&
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_color
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_ITEM
case|:
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_item
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_DISPLAY
case|:
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_display
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_IMAGE
case|:
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_image
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_LAYER
case|:
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_layer
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_CHANNEL
case|:
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_channel
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_DRAWABLE
case|:
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_drawable
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_SELECTION
case|:
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_selection
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_COLORARRAY
case|:
name|count
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
name|i
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|full_copy
condition|)
name|gimp_value_set_colorarray
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_colorarray
argument_list|,
name|count
argument_list|)
expr_stmt|;
else|else
name|gimp_value_set_static_colorarray
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_colorarray
argument_list|,
name|count
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_VECTORS
case|:
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_vectors
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_PARASITE
case|:
if|if
condition|(
name|full_copy
condition|)
name|g_value_set_boxed
argument_list|(
operator|&
name|value
argument_list|,
operator|&
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_parasite
argument_list|)
expr_stmt|;
else|else
name|g_value_set_static_boxed
argument_list|(
operator|&
name|value
argument_list|,
operator|&
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_parasite
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STATUS
case|:
name|g_value_set_enum
argument_list|(
operator|&
name|value
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_status
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_END
case|:
break|break;
block|}
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
name|GPParam
modifier|*
DECL|function|plug_in_args_to_params (GimpValueArray * args,gboolean full_copy)
name|plug_in_args_to_params
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
name|params
operator|=
name|g_new0
argument_list|(
name|GPParam
argument_list|,
name|gimp_value_array_length
argument_list|(
name|args
argument_list|)
argument_list|)
expr_stmt|;
name|length
operator|=
name|gimp_value_array_length
argument_list|(
name|args
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
name|params
index|[
name|i
index|]
operator|.
name|type
operator|=
name|gimp_pdb_compat_arg_type_from_gtype
argument_list|(
name|G_VALUE_TYPE
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|params
index|[
name|i
index|]
operator|.
name|type
condition|)
block|{
case|case
name|GIMP_PDB_INT32
case|:
if|if
condition|(
name|G_VALUE_HOLDS_INT
argument_list|(
name|value
argument_list|)
condition|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_UINT
argument_list|(
name|value
argument_list|)
condition|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|g_value_get_uint
argument_list|(
name|value
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_ENUM
argument_list|(
name|value
argument_list|)
condition|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_BOOLEAN
argument_list|(
name|value
argument_list|)
condition|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s: unhandled GIMP_PDB_INT32 type: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|g_type_name
argument_list|(
name|G_VALUE_TYPE
argument_list|(
name|value
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_reached
argument_list|(
name|params
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_INT16
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8
operator|=
name|g_value_get_uint
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOAT
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_float
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRING
case|:
if|if
condition|(
name|full_copy
condition|)
name|params
index|[
name|i
index|]
operator|.
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
name|params
index|[
name|i
index|]
operator|.
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
break|break;
case|case
name|GIMP_PDB_INT32ARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32array
operator|=
name|gimp_value_dup_int32array
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32array
operator|=
operator|(
name|gint32
operator|*
operator|)
name|gimp_value_get_int32array
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT16ARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16array
operator|=
name|gimp_value_dup_int16array
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16array
operator|=
operator|(
name|gint16
operator|*
operator|)
name|gimp_value_get_int16array
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8ARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8array
operator|=
name|gimp_value_dup_int8array
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8array
operator|=
operator|(
name|guint8
operator|*
operator|)
name|gimp_value_get_int8array
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOATARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_floatarray
operator|=
name|gimp_value_dup_floatarray
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_floatarray
operator|=
operator|(
name|gdouble
operator|*
operator|)
name|gimp_value_get_floatarray
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRINGARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_stringarray
operator|=
name|gimp_value_dup_stringarray
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_stringarray
operator|=
operator|(
name|gchar
operator|*
operator|*
operator|)
name|gimp_value_get_stringarray
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_COLOR
case|:
name|gimp_value_get_rgb
argument_list|(
name|value
argument_list|,
operator|&
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_color
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_ITEM
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_item
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_DISPLAY
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_display
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_IMAGE
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_LAYER
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_layer
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_CHANNEL
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_channel
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_DRAWABLE
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_drawable
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_SELECTION
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_selection
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_COLORARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_colorarray
operator|=
name|gimp_value_dup_colorarray
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_colorarray
operator|=
operator|(
name|GimpRGB
operator|*
operator|)
name|gimp_value_get_colorarray
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_VECTORS
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_vectors
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_PARASITE
case|:
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
if|if
condition|(
name|parasite
condition|)
block|{
name|params
index|[
name|i
index|]
operator|.
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
name|params
index|[
name|i
index|]
operator|.
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
name|params
index|[
name|i
index|]
operator|.
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
name|params
index|[
name|i
index|]
operator|.
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
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_parasite
operator|.
name|name
operator|=
name|NULL
expr_stmt|;
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_parasite
operator|.
name|flags
operator|=
literal|0
expr_stmt|;
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_parasite
operator|.
name|size
operator|=
literal|0
expr_stmt|;
name|params
index|[
name|i
index|]
operator|.
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
break|break;
case|case
name|GIMP_PDB_STATUS
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_END
case|:
break|break;
block|}
block|}
return|return
name|params
return|;
block|}
end_function

end_unit

