begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-save.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager-file.h"
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
file|"internal-procs.h"
end_include

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|file_load_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|file_load_invoker
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|new_args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GimpProcedure
modifier|*
name|proc
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|file
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|FALSE
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
name|file_proc
operator|=
name|gimp_plug_in_manager_file_procedure_find
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|GIMP_FILE_PROCEDURE_GROUP_OPEN
argument_list|,
name|file
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|FALSE
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
name|proc
operator|=
name|GIMP_PROCEDURE
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
name|new_args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|proc
argument_list|)
expr_stmt|;
name|g_value_transform
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|gimp_value_array_index
argument_list|(
name|new_args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_take_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|new_args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|2
init|;
name|i
operator|<
name|proc
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|G_IS_PARAM_SPEC_STRING
argument_list|(
name|proc
operator|->
name|args
index|[
name|i
index|]
argument_list|)
condition|)
name|g_value_set_static_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|new_args
argument_list|,
name|i
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name_args
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
name|gimp_object_get_name
argument_list|(
name|proc
argument_list|)
argument_list|,
name|new_args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|new_args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
if|if
condition|(
name|gimp_value_array_length
argument_list|(
name|return_vals
argument_list|)
operator|>
literal|1
operator|&&
name|GIMP_VALUE_HOLDS_IMAGE
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_image_set_load_proc
argument_list|(
name|image
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|file_load_layer_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|file_load_layer_invoker
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|run_mode
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
init|=
name|NULL
decl_stmt|;
name|run_mode
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GList
modifier|*
name|layers
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|layers
operator|=
name|file_open_layers
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|image
argument_list|,
name|FALSE
argument_list|,
name|file
argument_list|,
name|run_mode
argument_list|,
name|NULL
argument_list|,
operator|&
name|status
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|layers
condition|)
block|{
name|layer
operator|=
name|layers
operator|->
name|data
expr_stmt|;
name|g_list_free
argument_list|(
name|layers
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
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|layer
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|file_load_layers_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|file_load_layers_invoker
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|run_mode
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|gint
name|num_layers
init|=
literal|0
decl_stmt|;
name|GimpLayer
modifier|*
modifier|*
name|layers
init|=
name|NULL
decl_stmt|;
name|run_mode
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GList
modifier|*
name|layer_list
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|layer_list
operator|=
name|file_open_layers
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|image
argument_list|,
name|FALSE
argument_list|,
name|file
argument_list|,
name|run_mode
argument_list|,
name|NULL
argument_list|,
operator|&
name|status
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|layers
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|num_layers
operator|=
name|g_list_length
argument_list|(
name|layer_list
argument_list|)
expr_stmt|;
name|layers
operator|=
name|g_new
argument_list|(
name|GimpLayer
operator|*
argument_list|,
name|num_layers
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|list
operator|=
name|layer_list
init|;
name|i
operator|<
name|num_layers
condition|;
name|i
operator|++
operator|,
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|layers
index|[
name|i
index|]
operator|=
name|g_object_ref
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|layer_list
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
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|num_layers
argument_list|)
expr_stmt|;
name|gimp_value_take_object_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|,
operator|(
name|GObject
operator|*
operator|*
operator|)
name|layers
argument_list|,
name|num_layers
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
name|GimpValueArray
modifier|*
DECL|function|file_save_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|file_save_invoker
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|new_args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GimpProcedure
modifier|*
name|proc
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|file
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
name|file_proc
operator|=
name|gimp_plug_in_manager_file_procedure_find
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|GIMP_FILE_PROCEDURE_GROUP_SAVE
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
name|file_proc
operator|=
name|gimp_plug_in_manager_file_procedure_find
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|GIMP_FILE_PROCEDURE_GROUP_EXPORT
argument_list|,
name|file
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|FALSE
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
name|proc
operator|=
name|GIMP_PROCEDURE
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
name|new_args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|proc
argument_list|)
expr_stmt|;
name|g_value_transform
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|gimp_value_array_index
argument_list|(
name|new_args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_transform
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|gimp_value_array_index
argument_list|(
name|new_args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_transform
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|gimp_value_array_index
argument_list|(
name|new_args
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_transform
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|gimp_value_array_index
argument_list|(
name|new_args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|4
init|;
name|i
operator|<
name|proc
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|G_IS_PARAM_SPEC_STRING
argument_list|(
name|proc
operator|->
name|args
index|[
name|i
index|]
argument_list|)
condition|)
name|g_value_set_static_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|new_args
argument_list|,
name|i
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name_args
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
name|gimp_object_get_name
argument_list|(
name|proc
argument_list|)
argument_list|,
name|new_args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|new_args
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|file_load_thumbnail_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|file_load_thumbnail_invoker
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|gint
name|width
init|=
literal|0
decl_stmt|;
name|gint
name|height
init|=
literal|0
decl_stmt|;
name|gint
name|thumb_data_count
init|=
literal|0
decl_stmt|;
name|guint8
modifier|*
name|thumb_data
init|=
name|NULL
decl_stmt|;
name|file
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|file_utils_load_thumbnail
argument_list|(
name|file
argument_list|)
decl_stmt|;
if|if
condition|(
name|pixbuf
condition|)
block|{
name|width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|thumb_data_count
operator|=
literal|3
operator|*
name|width
operator|*
name|height
expr_stmt|;
name|thumb_data
operator|=
name|g_memdup
argument_list|(
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|thumb_data_count
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
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
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|3
argument_list|)
argument_list|,
name|thumb_data_count
argument_list|)
expr_stmt|;
name|gimp_value_take_uint8_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|4
argument_list|)
argument_list|,
name|thumb_data
argument_list|,
name|thumb_data_count
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
name|GimpValueArray
modifier|*
DECL|function|file_save_thumbnail_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|file_save_thumbnail_invoker
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|image
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|success
operator|=
name|file_utils_save_thumbnail
argument_list|(
name|image
argument_list|,
name|file
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_file_procs (GimpPDB * pdb)
name|register_file_procs
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
comment|/*    * gimp-file-load    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|file_load_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-file-load"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_help
argument_list|(
name|procedure
argument_list|,
literal|"Loads an image file by invoking the right load handler."
argument_list|,
literal|"This procedure invokes the correct file load handler using magic if possible, and falling back on the file's extension and/or prefix if not. The name of the file to load is typically a full pathname, and the name entered is what the user actually typed before prepending a directory path. The reason for this is that if the user types https://www.gimp.org/foo.png he wants to fetch a URL, and the full pathname will not look like a URL."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Josh MacDonald"
argument_list|,
literal|"Josh MacDonald"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"run-mode"
argument_list|,
literal|"run mode"
argument_list|,
literal|"The run mode"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_param_spec_enum_exclude_value
argument_list|(
name|GIMP_PARAM_SPEC_ENUM
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|GIMP_RUN_WITH_LAST_VALS
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"file"
argument_list|,
literal|"file"
argument_list|,
literal|"The file to load"
argument_list|,
name|G_TYPE_FILE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The output image"
argument_list|,
name|FALSE
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
comment|/*    * gimp-file-load-layer    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|file_load_layer_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-file-load-layer"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_help
argument_list|(
name|procedure
argument_list|,
literal|"Loads an image file as a layer for an existing image."
argument_list|,
literal|"This procedure behaves like the file-load procedure but opens the specified image as a layer for an existing image. The returned layer needs to be added to the existing image with 'gimp-image-insert-layer'."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2005"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"run-mode"
argument_list|,
literal|"run mode"
argument_list|,
literal|"The run mode"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_param_spec_enum_exclude_value
argument_list|(
name|GIMP_PARAM_SPEC_ENUM
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|GIMP_RUN_WITH_LAST_VALS
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"Destination image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"file"
argument_list|,
literal|"file"
argument_list|,
literal|"The file to load"
argument_list|,
name|G_TYPE_FILE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_layer
argument_list|(
literal|"layer"
argument_list|,
literal|"layer"
argument_list|,
literal|"The layer created when loading the image file"
argument_list|,
name|FALSE
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
comment|/*    * gimp-file-load-layers    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|file_load_layers_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-file-load-layers"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_help
argument_list|(
name|procedure
argument_list|,
literal|"Loads an image file as layers for an existing image."
argument_list|,
literal|"This procedure behaves like the file-load procedure but opens the specified image as layers for an existing image. The returned layers needs to be added to the existing image with 'gimp-image-insert-layer'."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2006"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"run-mode"
argument_list|,
literal|"run mode"
argument_list|,
literal|"The run mode"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_param_spec_enum_exclude_value
argument_list|(
name|GIMP_PARAM_SPEC_ENUM
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|GIMP_RUN_WITH_LAST_VALS
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"Destination image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"file"
argument_list|,
literal|"file"
argument_list|,
literal|"The file to load"
argument_list|,
name|G_TYPE_FILE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-layers"
argument_list|,
literal|"num layers"
argument_list|,
literal|"The number of loaded layers"
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
name|gimp_param_spec_object_array
argument_list|(
literal|"layers"
argument_list|,
literal|"layers"
argument_list|,
literal|"The list of loaded layers"
argument_list|,
name|GIMP_TYPE_LAYER
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
comment|/*    * gimp-file-save    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|file_save_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-file-save"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_help
argument_list|(
name|procedure
argument_list|,
literal|"Saves a file by extension."
argument_list|,
literal|"This procedure invokes the correct file save handler according to the file's extension and/or prefix. The name of the file to save is typically a full pathname, and the name entered is what the user actually typed before prepending a directory path. The reason for this is that if the user types https://www.gimp.org/foo.png she wants to fetch a URL, and the full pathname will not look like a URL."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Josh MacDonald"
argument_list|,
literal|"Josh MacDonald"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"run-mode"
argument_list|,
literal|"run mode"
argument_list|,
literal|"The run mode"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"Input image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_drawable
argument_list|(
literal|"drawable"
argument_list|,
literal|"drawable"
argument_list|,
literal|"Drawable to save"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"file"
argument_list|,
literal|"file"
argument_list|,
literal|"The file to save the image in"
argument_list|,
name|G_TYPE_FILE
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
comment|/*    * gimp-file-load-thumbnail    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|file_load_thumbnail_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-file-load-thumbnail"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_help
argument_list|(
name|procedure
argument_list|,
literal|"Loads the thumbnail for a file."
argument_list|,
literal|"This procedure tries to load a thumbnail that belongs to the file with the given file. This name is a full pathname. The returned data is an array of colordepth 3 (RGB), regardless of the image type. Width and height of the thumbnail are also returned. Don't use this function if you need a thumbnail of an already opened image, use 'gimp-image-thumbnail' instead."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Adam D. Moss, Sven Neumann"
argument_list|,
literal|"Adam D. Moss, Sven Neumann"
argument_list|,
literal|"1999-2003"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"file"
argument_list|,
literal|"file"
argument_list|,
literal|"The file that owns the thumbnail to load"
argument_list|,
name|G_TYPE_FILE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"width"
argument_list|,
literal|"width"
argument_list|,
literal|"The width of the thumbnail"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"height"
argument_list|,
literal|"height"
argument_list|,
literal|"The height of the thumbnail"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"thumb-data-count"
argument_list|,
literal|"thumb data count"
argument_list|,
literal|"The number of bytes in thumbnail data"
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
name|gimp_param_spec_uint8_array
argument_list|(
literal|"thumb-data"
argument_list|,
literal|"thumb data"
argument_list|,
literal|"The thumbnail data"
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
comment|/*    * gimp-file-save-thumbnail    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|file_save_thumbnail_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-file-save-thumbnail"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_help
argument_list|(
name|procedure
argument_list|,
literal|"Saves a thumbnail for the given image"
argument_list|,
literal|"This procedure saves a thumbnail for the given image according to the Free Desktop Thumbnail Managing Standard. The thumbnail is saved so that it belongs to the file with the given filen. This means you have to save the image under this name first, otherwise this procedure will fail. This procedure may become useful if you want to explicitly save a thumbnail with a file."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Josh MacDonald"
argument_list|,
literal|"Josh MacDonald"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"file"
argument_list|,
literal|"file"
argument_list|,
literal|"The file the thumbnail belongs to"
argument_list|,
name|G_TYPE_FILE
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

