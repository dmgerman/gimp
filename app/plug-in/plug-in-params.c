begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"libgimpbase/gimpprotocol.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"plug-in.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-params.h"
end_include

begin_function
name|Argument
modifier|*
DECL|function|plug_in_params_to_args (GPParam * params,gint nparams,gboolean full_copy)
name|plug_in_params_to_args
parameter_list|(
name|GPParam
modifier|*
name|params
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|gboolean
name|full_copy
parameter_list|)
block|{
name|Argument
modifier|*
name|args
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|stringarray
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|params
operator|&&
name|nparams
operator|)
condition|)
return|return
name|NULL
return|;
name|args
operator|=
name|g_new0
argument_list|(
name|Argument
argument_list|,
name|nparams
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
name|nparams
condition|;
name|i
operator|++
control|)
block|{
name|args
index|[
name|i
index|]
operator|.
name|arg_type
operator|=
name|params
index|[
name|i
index|]
operator|.
name|type
expr_stmt|;
switch|switch
condition|(
name|args
index|[
name|i
index|]
operator|.
name|arg_type
condition|)
block|{
case|case
name|GIMP_PDB_INT32
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT16
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOAT
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_float
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRING
case|:
if|if
condition|(
name|full_copy
condition|)
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|g_strdup
argument_list|(
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT32ARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|count
operator|=
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|g_new
argument_list|(
name|gint32
argument_list|,
name|count
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
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
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32array
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_INT16ARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|count
operator|=
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|g_new
argument_list|(
name|gint16
argument_list|,
name|count
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
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
operator|*
literal|2
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16array
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_INT8ARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|count
operator|=
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|g_new
argument_list|(
name|gint8
argument_list|,
name|count
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
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
block|}
else|else
block|{
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8array
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_FLOATARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|count
operator|=
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|count
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
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
operator|*
literal|8
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_floatarray
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_STRINGARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
expr_stmt|;
name|stringarray
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
condition|;
name|j
operator|++
control|)
name|stringarray
index|[
name|j
index|]
operator|=
name|g_strdup
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_stringarray
index|[
name|j
index|]
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_stringarray
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_COLOR
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_color
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_color
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_REGION
case|:
name|g_message
argument_list|(
literal|"the \"region\" arg type is not currently supported"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_DISPLAY
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_display
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_IMAGE
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_LAYER
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_layer
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_CHANNEL
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_channel
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_DRAWABLE
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_SELECTION
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_selection
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_BOUNDARY
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_boundary
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_PATH
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_path
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_PARASITE
case|:
if|if
condition|(
name|full_copy
condition|)
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|gimp_parasite_copy
argument_list|(
operator|(
name|GimpParasite
operator|*
operator|)
operator|&
operator|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_parasite
operator|)
argument_list|)
expr_stmt|;
else|else
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
operator|(
name|gpointer
operator|)
operator|&
operator|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_parasite
operator|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STATUS
case|:
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_status
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_END
case|:
break|break;
block|}
block|}
return|return
name|args
return|;
block|}
end_function

begin_function
name|GPParam
modifier|*
DECL|function|plug_in_args_to_params (Argument * args,gint nargs,gboolean full_copy)
name|plug_in_args_to_params
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|,
name|gint
name|nargs
parameter_list|,
name|gboolean
name|full_copy
parameter_list|)
block|{
name|GPParam
modifier|*
name|params
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|stringarray
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|args
operator|&&
name|nargs
operator|)
condition|)
return|return
name|NULL
return|;
name|params
operator|=
name|g_new0
argument_list|(
name|GPParam
argument_list|,
name|nargs
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
name|nargs
condition|;
name|i
operator|++
control|)
block|{
name|params
index|[
name|i
index|]
operator|.
name|type
operator|=
name|args
index|[
name|i
index|]
operator|.
name|arg_type
expr_stmt|;
switch|switch
condition|(
name|args
index|[
name|i
index|]
operator|.
name|arg_type
condition|)
block|{
case|case
name|GIMP_PDB_INT32
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_float
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
name|g_strdup
argument_list|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT32ARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32array
operator|=
name|g_new
argument_list|(
name|gint32
argument_list|,
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32array
argument_list|,
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
argument_list|,
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
operator|*
literal|4
argument_list|)
expr_stmt|;
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
name|d_int32array
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_INT16ARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16array
operator|=
name|g_new
argument_list|(
name|gint16
argument_list|,
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16array
argument_list|,
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
argument_list|,
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
operator|*
literal|2
argument_list|)
expr_stmt|;
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
name|d_int16array
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_INT8ARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8array
operator|=
name|g_new
argument_list|(
name|gint8
argument_list|,
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|,
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
argument_list|,
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
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
name|d_int8array
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_FLOATARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_floatarray
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_floatarray
argument_list|,
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
argument_list|,
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
operator|*
literal|8
argument_list|)
expr_stmt|;
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
name|d_floatarray
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_STRINGARRAY
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_stringarray
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
name|stringarray
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
condition|;
name|j
operator|++
control|)
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_stringarray
index|[
name|j
index|]
operator|=
name|g_strdup
argument_list|(
name|stringarray
index|[
name|j
index|]
argument_list|)
expr_stmt|;
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
name|d_stringarray
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_COLOR
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_color
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_color
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_REGION
case|:
name|g_message
argument_list|(
literal|"the \"region\" arg type is not currently supported"
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_BOUNDARY
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_boundary
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_PATH
case|:
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_path
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_PARASITE
case|:
if|if
condition|(
name|full_copy
condition|)
block|{
name|GimpParasite
modifier|*
name|tmp
decl_stmt|;
name|tmp
operator|=
name|gimp_parasite_copy
argument_list|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
argument_list|)
expr_stmt|;
if|if
condition|(
name|tmp
operator|==
name|NULL
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
else|else
block|{
name|memcpy
argument_list|(
operator|&
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_parasite
argument_list|,
name|tmp
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpParasite
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|==
name|NULL
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
else|else
name|memcpy
argument_list|(
operator|&
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_parasite
argument_list|,
operator|(
name|GimpParasite
operator|*
operator|)
operator|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|)
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpParasite
argument_list|)
argument_list|)
expr_stmt|;
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
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
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

begin_function
name|void
DECL|function|plug_in_params_destroy (GPParam * params,gint nparams,gboolean full_destroy)
name|plug_in_params_destroy
parameter_list|(
name|GPParam
modifier|*
name|params
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|gboolean
name|full_destroy
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
if|if
condition|(
name|full_destroy
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nparams
condition|;
name|i
operator|++
control|)
block|{
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
case|case
name|GIMP_PDB_INT16
case|:
case|case
name|GIMP_PDB_INT8
case|:
case|case
name|GIMP_PDB_FLOAT
case|:
break|break;
case|case
name|GIMP_PDB_STRING
case|:
name|g_free
argument_list|(
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
name|g_free
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int32array
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT16ARRAY
case|:
name|g_free
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int16array
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8ARRAY
case|:
name|g_free
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOATARRAY
case|:
name|g_free
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_floatarray
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRINGARRAY
case|:
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|params
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
condition|;
name|j
operator|++
control|)
name|g_free
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_stringarray
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|data
operator|.
name|d_stringarray
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_COLOR
case|:
break|break;
case|case
name|GIMP_PDB_REGION
case|:
name|g_message
argument_list|(
literal|"the \"region\" arg type is not currently supported"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_DISPLAY
case|:
case|case
name|GIMP_PDB_IMAGE
case|:
case|case
name|GIMP_PDB_LAYER
case|:
case|case
name|GIMP_PDB_CHANNEL
case|:
case|case
name|GIMP_PDB_DRAWABLE
case|:
case|case
name|GIMP_PDB_SELECTION
case|:
case|case
name|GIMP_PDB_BOUNDARY
case|:
case|case
name|GIMP_PDB_PATH
case|:
break|break;
case|case
name|GIMP_PDB_PARASITE
case|:
if|if
condition|(
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
condition|)
block|{
name|g_free
argument_list|(
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
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
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
argument_list|)
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
name|data
operator|=
name|NULL
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_STATUS
case|:
break|break;
case|case
name|GIMP_PDB_END
case|:
break|break;
block|}
block|}
block|}
name|g_free
argument_list|(
name|params
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_args_destroy (Argument * args,gint nargs,gboolean full_destroy)
name|plug_in_args_destroy
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|,
name|gint
name|nargs
parameter_list|,
name|gboolean
name|full_destroy
parameter_list|)
block|{
if|if
condition|(
name|full_destroy
condition|)
name|procedural_db_destroy_args
argument_list|(
name|args
argument_list|,
name|nargs
argument_list|)
expr_stmt|;
else|else
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|plug_in_param_defs_check (const gchar * plug_in_name,const gchar * plug_in_prog,const gchar * procedure_name,const gchar * menu_path,GPParamDef * params,guint32 n_args,GPParamDef * return_vals,guint32 n_return_vals,GError ** error)
name|plug_in_param_defs_check
parameter_list|(
specifier|const
name|gchar
modifier|*
name|plug_in_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|plug_in_prog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|GPParamDef
modifier|*
name|params
parameter_list|,
name|guint32
name|n_args
parameter_list|,
name|GPParamDef
modifier|*
name|return_vals
parameter_list|,
name|guint32
name|n_return_vals
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
return|return
name|plug_in_proc_args_check
argument_list|(
name|plug_in_name
argument_list|,
name|plug_in_prog
argument_list|,
name|procedure_name
argument_list|,
name|menu_path
argument_list|,
operator|(
name|ProcArg
operator|*
operator|)
name|params
argument_list|,
name|n_args
argument_list|,
operator|(
name|ProcArg
operator|*
operator|)
name|return_vals
argument_list|,
name|n_return_vals
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|plug_in_proc_args_check (const gchar * plug_in_name,const gchar * plug_in_prog,const gchar * procedure_name,const gchar * menu_path,ProcArg * args,guint32 n_args,ProcArg * return_vals,guint32 n_return_vals,GError ** error)
name|plug_in_proc_args_check
parameter_list|(
specifier|const
name|gchar
modifier|*
name|plug_in_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|plug_in_prog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|ProcArg
modifier|*
name|args
parameter_list|,
name|guint32
name|n_args
parameter_list|,
name|ProcArg
modifier|*
name|return_vals
parameter_list|,
name|guint32
name|n_return_vals
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|p
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|plug_in_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|plug_in_prog
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|procedure_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_path
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|args
operator|==
name|NULL
operator|||
name|n_args
operator|>
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|return_vals
operator|==
name|NULL
operator|||
name|n_return_vals
operator|>
literal|0
argument_list|,
name|FALSE
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
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|strncmp
argument_list|(
name|menu_path
argument_list|,
literal|"<Toolbox>"
argument_list|,
literal|9
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|(
name|n_args
operator|<
literal|1
operator|)
operator|||
operator|(
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_INT32
operator|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Plug-In \"%s\"\n(%s)\n\n"
literal|"attempted to install<Toolbox> procedure \"%s\" "
literal|"which does not take the standard<Toolbox> Plug-In "
literal|"args.\n"
literal|"(INT32)"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_name
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_prog
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|menu_path
argument_list|,
literal|"<Image>"
argument_list|,
literal|7
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|(
name|n_args
operator|<
literal|3
operator|)
operator|||
operator|(
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_INT32
operator|)
operator|||
operator|(
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_IMAGE
operator|)
operator|||
operator|(
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_DRAWABLE
operator|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Plug-In \"%s\"\n(%s)\n\n"
literal|"attempted to install<Image> procedure \"%s\" "
literal|"which does not take the standard<Image> Plug-In "
literal|"args.\n"
literal|"(INT32, IMAGE, DRAWABLE)"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_name
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_prog
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|menu_path
argument_list|,
literal|"<Load>"
argument_list|,
literal|6
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|(
name|n_args
operator|<
literal|3
operator|)
operator|||
operator|(
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_INT32
operator|)
operator|||
operator|(
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_STRING
operator|)
operator|||
operator|(
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_STRING
operator|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Plug-In \"%s\"\n(%s)\n\n"
literal|"attempted to install<Load> procedure \"%s\" "
literal|"which does not take the standard<Load> Plug-In "
literal|"args.\n"
literal|"(INT32, STRING, STRING)"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_name
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_prog
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|menu_path
argument_list|,
literal|"<Save>"
argument_list|,
literal|6
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|(
name|n_args
operator|<
literal|5
operator|)
operator|||
operator|(
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_INT32
operator|)
operator|||
operator|(
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_IMAGE
operator|)
operator|||
operator|(
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_DRAWABLE
operator|)
operator|||
operator|(
name|args
index|[
literal|3
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_STRING
operator|)
operator|||
operator|(
name|args
index|[
literal|4
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_STRING
operator|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Plug-In \"%s\"\n(%s)\n\n"
literal|"attempted to install<Save> procedure \"%s\" "
literal|"which does not take the standard<Save> Plug-In "
literal|"args.\n"
literal|"(INT32, IMAGE, DRAWABLE, STRING, STRING)"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_name
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_prog
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Plug-In \"%s\"\n(%s)\n"
literal|"attempted to install procedure \"%s\" "
literal|"in the invalid menu location \"%s\".\n"
literal|"Use either \"<Toolbox>\", \"<Image>\", "
literal|"\"<Load>\", or \"<Save>\"."
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_name
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_prog
argument_list|)
argument_list|,
name|procedure_name
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|p
operator|=
name|strchr
argument_list|(
name|menu_path
argument_list|,
literal|'>'
argument_list|)
operator|+
literal|1
expr_stmt|;
if|if
condition|(
operator|*
name|p
operator|!=
literal|'/'
operator|&&
operator|*
name|p
operator|!=
literal|'\0'
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Plug-In \"%s\"\n(%s)\n"
literal|"attempted to install procedure \"%s\"\n"
literal|"in the invalid menu location \"%s\".\n"
literal|"The menu path must look like either \"<Prefix>\" "
literal|"or \"<Prefix>/path/to/item\"."
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_name
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|plug_in_prog
argument_list|)
argument_list|,
name|procedure_name
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

