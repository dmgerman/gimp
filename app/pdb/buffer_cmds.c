begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl. */
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
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer-filter.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"internal_procs.h"
end_include

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|buffers_get_list_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|buffers_get_list_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filter
decl_stmt|;
name|gint32
name|num_buffers
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|buffer_list
init|=
name|NULL
decl_stmt|;
name|filter
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|buffer_list
operator|=
name|gimp_container_get_filtered_name_array
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|,
name|filter
argument_list|,
operator|&
name|num_buffers
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|num_buffers
argument_list|)
expr_stmt|;
name|gimp_value_take_stringarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|,
name|buffer_list
argument_list|,
name|num_buffers
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|buffer_rename_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|buffer_rename_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|buffer_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|new_name
decl_stmt|;
name|gchar
modifier|*
name|real_name
init|=
name|NULL
decl_stmt|;
name|buffer_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|new_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
operator|(
name|GimpBuffer
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|,
name|buffer_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|buffer
operator|&&
name|strlen
argument_list|(
name|new_name
argument_list|)
condition|)
block|{
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
name|real_name
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|real_name
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|buffer_delete_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|buffer_delete_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|buffer_name
decl_stmt|;
name|buffer_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
operator|(
name|GimpBuffer
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|,
name|buffer_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|buffer
condition|)
name|success
operator|=
name|gimp_container_remove
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|buffer_get_width_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|buffer_get_width_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|buffer_name
decl_stmt|;
name|gint32
name|width
init|=
literal|0
decl_stmt|;
name|buffer_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
operator|(
name|GimpBuffer
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|,
name|buffer_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|buffer
condition|)
name|width
operator|=
name|gimp_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|width
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|buffer_get_height_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|buffer_get_height_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|buffer_name
decl_stmt|;
name|gint32
name|height
init|=
literal|0
decl_stmt|;
name|buffer_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
operator|(
name|GimpBuffer
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|,
name|buffer_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|buffer
condition|)
name|height
operator|=
name|gimp_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|height
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|buffer_get_bytes_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|buffer_get_bytes_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|buffer_name
decl_stmt|;
name|gint32
name|bytes
init|=
literal|0
decl_stmt|;
name|buffer_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
operator|(
name|GimpBuffer
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|,
name|buffer_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|buffer
condition|)
name|bytes
operator|=
name|gimp_buffer_get_bytes
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|buffer_get_image_type_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|buffer_get_image_type_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|buffer_name
decl_stmt|;
name|gint32
name|image_type
init|=
literal|0
decl_stmt|;
name|buffer_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
operator|(
name|GimpBuffer
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|,
name|buffer_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|buffer
condition|)
name|image_type
operator|=
name|gimp_buffer_get_image_type
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_enum
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|image_type
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_buffer_procs (GimpPDB * pdb)
name|register_buffer_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * gimp-buffers-get-list    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|buffers_get_list_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-buffers-get-list"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-buffers-get-list"
argument_list|,
literal|"Retrieve a complete listing of the available buffers."
argument_list|,
literal|"This procedure returns a complete listing of available named buffers."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"filter"
argument_list|,
literal|"filter"
argument_list|,
literal|"An optional regular expression used to filter the list"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-buffers"
argument_list|,
literal|"num buffers"
argument_list|,
literal|"The number of buffers"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string_array
argument_list|(
literal|"buffer-list"
argument_list|,
literal|"buffer list"
argument_list|,
literal|"The list of buffer names"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-buffer-rename    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|buffer_rename_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-buffer-rename"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-buffer-rename"
argument_list|,
literal|"Renames a named buffer."
argument_list|,
literal|"This procedure renames a named buffer."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"buffer-name"
argument_list|,
literal|"buffer name"
argument_list|,
literal|"The buffer name"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"new-name"
argument_list|,
literal|"new name"
argument_list|,
literal|"The buffer's new name"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"real-name"
argument_list|,
literal|"real name"
argument_list|,
literal|"The real name given to the buffer"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-buffer-delete    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|buffer_delete_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-buffer-delete"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-buffer-delete"
argument_list|,
literal|"Deletes a named buffer."
argument_list|,
literal|"This procedure deletes a named buffer."
argument_list|,
literal|"David Gowers<neota@softhome.net>"
argument_list|,
literal|"David Gowers<neota@softhome.net>"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"buffer-name"
argument_list|,
literal|"buffer name"
argument_list|,
literal|"The buffer name"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-buffer-get-width    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|buffer_get_width_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-buffer-get-width"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-buffer-get-width"
argument_list|,
literal|"Retrieves the specified buffer's width."
argument_list|,
literal|"This procedure retrieves the specified named buffer's width."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"buffer-name"
argument_list|,
literal|"buffer name"
argument_list|,
literal|"The buffer name"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"width"
argument_list|,
literal|"width"
argument_list|,
literal|"The buffer width"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-buffer-get-height    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|buffer_get_height_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-buffer-get-height"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-buffer-get-height"
argument_list|,
literal|"Retrieves the specified buffer's height."
argument_list|,
literal|"This procedure retrieves the specified named buffer's height."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"buffer-name"
argument_list|,
literal|"buffer name"
argument_list|,
literal|"The buffer name"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"height"
argument_list|,
literal|"height"
argument_list|,
literal|"The buffer height"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-buffer-get-bytes    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|buffer_get_bytes_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-buffer-get-bytes"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-buffer-get-bytes"
argument_list|,
literal|"Retrieves the specified buffer's bytes."
argument_list|,
literal|"This procedure retrieves the specified named buffer's bytes."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"buffer-name"
argument_list|,
literal|"buffer name"
argument_list|,
literal|"The buffer name"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"bytes"
argument_list|,
literal|"bytes"
argument_list|,
literal|"The buffer bpp"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-buffer-get-image-type    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|buffer_get_image_type_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-buffer-get-image-type"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-buffer-get-image-type"
argument_list|,
literal|"Retrieves the specified buffer's image type."
argument_list|,
literal|"This procedure retrieves the specified named buffer's image type."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"buffer-name"
argument_list|,
literal|"buffer name"
argument_list|,
literal|"The buffer name"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"image-type"
argument_list|,
literal|"image type"
argument_list|,
literal|"The buffer image type"
argument_list|,
name|GIMP_TYPE_IMAGE_BASE_TYPE
argument_list|,
name|GIMP_RGB
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

