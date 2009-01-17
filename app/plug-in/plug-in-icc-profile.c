begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-in-icc-profile.c  * Copyright (C) 2006  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginerror.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-icc-profile.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|ICC_PROFILE_APPLY_RGB_PROC
define|#
directive|define
name|ICC_PROFILE_APPLY_RGB_PROC
value|"plug-in-icc-profile-apply-rgb"
end_define

begin_define
DECL|macro|ICC_PROFILE_INFO_PROC
define|#
directive|define
name|ICC_PROFILE_INFO_PROC
value|"plug-in-icc-profile-info"
end_define

begin_define
DECL|macro|ICC_PROFILE_FILE_INFO_PROC
define|#
directive|define
name|ICC_PROFILE_FILE_INFO_PROC
value|"plug-in-icc-profile-file-info"
end_define

begin_function_decl
specifier|static
name|void
name|plug_in_icc_profile_info_return
parameter_list|(
name|GValueArray
modifier|*
name|return_vals
parameter_list|,
name|gchar
modifier|*
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|desc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|gboolean
DECL|function|plug_in_icc_profile_apply_rgb (GimpImage * image,GimpContext * context,GimpProgress * progress,GimpRunMode run_mode,GError ** error)
name|plug_in_icc_profile_apply_rgb
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
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
name|gimp
operator|=
name|image
operator|->
name|gimp
expr_stmt|;
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
operator|==
name|GIMP_GRAY
condition|)
return|return
name|FALSE
return|;
name|procedure
operator|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|ICC_PROFILE_APPLY_RGB_PROC
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
operator|&&
name|procedure
operator|->
name|num_args
operator|>=
literal|2
operator|&&
name|GIMP_IS_PARAM_SPEC_INT32
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|0
index|]
argument_list|)
operator|&&
name|GIMP_IS_PARAM_SPEC_IMAGE_ID
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|1
index|]
argument_list|)
condition|)
block|{
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GimpColorProfilePolicy
name|policy
init|=
name|GIMP_COLOR_PROFILE_POLICY_ASK
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|error
argument_list|,
name|ICC_PROFILE_APPLY_RGB_PROC
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|run_mode
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|gimp_image_get_ID
argument_list|(
name|image
argument_list|)
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|status
operator|=
name|g_value_get_enum
argument_list|(
name|return_vals
operator|->
name|values
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|status
condition|)
block|{
case|case
name|GIMP_PDB_SUCCESS
case|:
name|policy
operator|=
name|GIMP_COLOR_PROFILE_POLICY_CONVERT
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_CANCEL
case|:
name|policy
operator|=
name|GIMP_COLOR_PROFILE_POLICY_KEEP
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PLUG_IN_ERROR
argument_list|,
name|GIMP_PLUG_IN_EXECUTION_FAILED
argument_list|,
name|_
argument_list|(
literal|"Error running '%s'"
argument_list|)
argument_list|,
name|ICC_PROFILE_APPLY_RGB_PROC
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|success
operator|&&
name|return_vals
operator|->
name|n_values
operator|>
literal|1
condition|)
block|{
name|GValue
modifier|*
name|value
init|=
name|g_value_array_get_nth
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_VALUE_HOLDS_INT32
argument_list|(
name|value
argument_list|)
operator|&&
name|g_value_get_int
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
argument_list|,
literal|"color-profile-policy"
argument_list|,
name|policy
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
name|g_value_array_free
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PLUG_IN_ERROR
argument_list|,
name|GIMP_PLUG_IN_NOT_FOUND
argument_list|,
name|_
argument_list|(
literal|"Plug-In missing (%s)"
argument_list|)
argument_list|,
name|ICC_PROFILE_APPLY_RGB_PROC
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|plug_in_icc_profile_info (GimpImage * image,GimpContext * context,GimpProgress * progress,gchar ** name,gchar ** desc,gchar ** info,GError ** error)
name|plug_in_icc_profile_info
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gchar
modifier|*
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|desc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|info
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
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
name|gimp
operator|=
name|image
operator|->
name|gimp
expr_stmt|;
name|procedure
operator|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|ICC_PROFILE_INFO_PROC
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
operator|&&
name|procedure
operator|->
name|num_args
operator|>=
literal|1
operator|&&
name|GIMP_IS_PARAM_SPEC_IMAGE_ID
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|0
index|]
argument_list|)
condition|)
block|{
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|error
argument_list|,
name|ICC_PROFILE_INFO_PROC
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|gimp_image_get_ID
argument_list|(
name|image
argument_list|)
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|status
operator|=
name|g_value_get_enum
argument_list|(
name|return_vals
operator|->
name|values
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|status
condition|)
block|{
case|case
name|GIMP_PDB_SUCCESS
case|:
name|plug_in_icc_profile_info_return
argument_list|(
name|return_vals
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|info
argument_list|)
expr_stmt|;
break|break;
default|default:
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PLUG_IN_ERROR
argument_list|,
name|GIMP_PLUG_IN_FAILED
argument_list|,
name|_
argument_list|(
literal|"Error running '%s'"
argument_list|)
argument_list|,
name|ICC_PROFILE_INFO_PROC
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_value_array_free
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
operator|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|)
return|;
block|}
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PLUG_IN_ERROR
argument_list|,
name|GIMP_PLUG_IN_FAILED
argument_list|,
name|_
argument_list|(
literal|"Plug-In missing (%s)"
argument_list|)
argument_list|,
name|ICC_PROFILE_INFO_PROC
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|plug_in_icc_profile_file_info (Gimp * gimp,GimpContext * context,GimpProgress * progress,const gchar * filename,gchar ** name,gchar ** desc,gchar ** info,GError ** error)
name|plug_in_icc_profile_file_info
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gchar
modifier|*
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|desc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|info
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
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
name|procedure
operator|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|ICC_PROFILE_FILE_INFO_PROC
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
operator|&&
name|procedure
operator|->
name|num_args
operator|>=
literal|1
operator|&&
name|GIMP_IS_PARAM_SPEC_STRING
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|0
index|]
argument_list|)
condition|)
block|{
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|error
argument_list|,
name|ICC_PROFILE_FILE_INFO_PROC
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|filename
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|status
operator|=
name|g_value_get_enum
argument_list|(
name|return_vals
operator|->
name|values
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|status
condition|)
block|{
case|case
name|GIMP_PDB_SUCCESS
case|:
name|plug_in_icc_profile_info_return
argument_list|(
name|return_vals
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|info
argument_list|)
expr_stmt|;
break|break;
default|default:
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PLUG_IN_ERROR
argument_list|,
name|GIMP_PLUG_IN_FAILED
argument_list|,
name|_
argument_list|(
literal|"Error running '%s'"
argument_list|)
argument_list|,
name|ICC_PROFILE_FILE_INFO_PROC
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_value_array_free
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
operator|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|)
return|;
block|}
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PLUG_IN_ERROR
argument_list|,
name|GIMP_PLUG_IN_FAILED
argument_list|,
name|_
argument_list|(
literal|"Plug-In missing (%s)"
argument_list|)
argument_list|,
name|ICC_PROFILE_FILE_INFO_PROC
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_icc_profile_info_return (GValueArray * return_vals,gchar ** name,gchar ** desc,gchar ** info)
name|plug_in_icc_profile_info_return
parameter_list|(
name|GValueArray
modifier|*
name|return_vals
parameter_list|,
name|gchar
modifier|*
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|desc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|info
parameter_list|)
block|{
if|if
condition|(
name|name
condition|)
block|{
name|GValue
modifier|*
name|value
init|=
name|g_value_array_get_nth
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
decl_stmt|;
operator|*
name|name
operator|=
name|G_VALUE_HOLDS_STRING
argument_list|(
name|value
argument_list|)
condition|?
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
else|:
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|desc
condition|)
block|{
name|GValue
modifier|*
name|value
init|=
name|g_value_array_get_nth
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
decl_stmt|;
operator|*
name|desc
operator|=
name|G_VALUE_HOLDS_STRING
argument_list|(
name|value
argument_list|)
condition|?
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
else|:
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|info
condition|)
block|{
name|GValue
modifier|*
name|value
init|=
name|g_value_array_get_nth
argument_list|(
name|return_vals
argument_list|,
literal|3
argument_list|)
decl_stmt|;
operator|*
name|info
operator|=
name|G_VALUE_HOLDS_STRING
argument_list|(
name|value
argument_list|)
condition|?
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
else|:
name|NULL
expr_stmt|;
block|}
block|}
end_function

end_unit

