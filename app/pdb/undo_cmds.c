begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
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
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
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
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_decl_stmt
DECL|variable|image_undo_group_start_proc
specifier|static
name|ProcRecord
name|image_undo_group_start_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_undo_group_end_proc
specifier|static
name|ProcRecord
name|image_undo_group_end_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_undo_is_enabled_proc
specifier|static
name|ProcRecord
name|image_undo_is_enabled_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_undo_disable_proc
specifier|static
name|ProcRecord
name|image_undo_disable_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_undo_enable_proc
specifier|static
name|ProcRecord
name|image_undo_enable_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_undo_freeze_proc
specifier|static
name|ProcRecord
name|image_undo_freeze_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_undo_thaw_proc
specifier|static
name|ProcRecord
name|image_undo_thaw_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_undo_procs (Gimp * gimp)
name|register_undo_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|procedure
decl_stmt|;
comment|/*    * image_undo_group_start    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|image_undo_group_start_proc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The ID of the image in which to open an undo group"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * image_undo_group_end    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|image_undo_group_end_proc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The ID of the image in which to close an undo group"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * image_undo_is_enabled    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|image_undo_is_enabled_proc
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"enabled"
argument_list|,
literal|"enabled"
argument_list|,
literal|"TRUE if undo is enabled for this image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * image_undo_disable    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|image_undo_disable_proc
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"disabled"
argument_list|,
literal|"disabled"
argument_list|,
literal|"TRUE if the image undo has been disabled"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * image_undo_enable    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|image_undo_enable_proc
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"enabled"
argument_list|,
literal|"enabled"
argument_list|,
literal|"TRUE if the image undo has been enabled"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * image_undo_freeze    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|image_undo_freeze_proc
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"frozen"
argument_list|,
literal|"frozen"
argument_list|,
literal|"TRUE if the image undo has been frozen"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * image_undo_thaw    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|image_undo_thaw_proc
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"thawed"
argument_list|,
literal|"thawed"
argument_list|,
literal|"TRUE if the image undo has been thawed"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_undo_group_start_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_undo_group_start_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
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
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|gchar
modifier|*
name|undo_desc
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
condition|)
name|undo_desc
operator|=
name|plug_in_get_undo_desc
argument_list|(
name|gimp
operator|->
name|current_plug_in
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_MISC
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo_desc
condition|)
name|g_free
argument_list|(
name|undo_desc
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_undo_group_start_proc
specifier|static
name|ProcRecord
name|image_undo_group_start_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-image-undo-group-start"
block|,
literal|"gimp-image-undo-group-start"
block|,
literal|"Starts a group undo."
block|,
literal|"This function is used to start a group undo--necessary for logically combining two or more undo operations into a single operation. This call must be used in conjunction with a 'gimp-image-undo-group-end' call."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1997"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_undo_group_start_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_undo_group_end_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_undo_group_end_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
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
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_undo_group_end_proc
specifier|static
name|ProcRecord
name|image_undo_group_end_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-image-undo-group-end"
block|,
literal|"gimp-image-undo-group-end"
block|,
literal|"Finish a group undo."
block|,
literal|"This function must be called once for each 'gimp-image-undo-group-start' call that is made."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1997"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_undo_group_end_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_undo_is_enabled_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_undo_is_enabled_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gboolean
name|enabled
init|=
name|FALSE
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|enabled
operator|=
name|gimp_image_undo_is_enabled
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_boolean
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|enabled
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_undo_is_enabled_proc
specifier|static
name|ProcRecord
name|image_undo_is_enabled_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-image-undo-is-enabled"
block|,
literal|"gimp-image-undo-is-enabled"
block|,
literal|"Check if the image's undo stack is enabled."
block|,
literal|"This procedure checks if the image's undo stack is currently enabled or disabled. This is useful when several plugins or scripts call each other and want to check if their caller has already used 'gimp_image_undo_disable' or 'gimp_image_undo_freeze'."
block|,
literal|"Raphael Quinet"
block|,
literal|"Raphael Quinet"
block|,
literal|"1999"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_undo_is_enabled_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_undo_disable_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_undo_disable_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gboolean
name|disabled
init|=
name|FALSE
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|disabled
operator|=
name|gimp_image_undo_disable
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_boolean
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|disabled
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_undo_disable_proc
specifier|static
name|ProcRecord
name|image_undo_disable_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-image-undo-disable"
block|,
literal|"gimp-image-undo-disable"
block|,
literal|"Disable the image's undo stack."
block|,
literal|"This procedure disables the image's undo stack, allowing subsequent operations to ignore their undo steps. This is generally called in conjunction with 'gimp_image_undo_enable' to temporarily disable an image undo stack. This is advantageous because saving undo steps can be time and memory intensive."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_undo_disable_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_undo_enable_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_undo_enable_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gboolean
name|enabled
init|=
name|FALSE
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|enabled
operator|=
name|gimp_image_undo_enable
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_boolean
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|enabled
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_undo_enable_proc
specifier|static
name|ProcRecord
name|image_undo_enable_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-image-undo-enable"
block|,
literal|"gimp-image-undo-enable"
block|,
literal|"Enable the image's undo stack."
block|,
literal|"This procedure enables the image's undo stack, allowing subsequent operations to store their undo steps. This is generally called in conjunction with 'gimp_image_undo_disable' to temporarily disable an image undo stack."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_undo_enable_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_undo_freeze_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_undo_freeze_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gboolean
name|frozen
init|=
name|FALSE
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|frozen
operator|=
name|gimp_image_undo_freeze
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_boolean
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|frozen
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_undo_freeze_proc
specifier|static
name|ProcRecord
name|image_undo_freeze_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-image-undo-freeze"
block|,
literal|"gimp-image-undo-freeze"
block|,
literal|"Freeze the image's undo stack."
block|,
literal|"This procedure freezes the image's undo stack, allowing subsequent operations to ignore their undo steps. This is generally called in conjunction with 'gimp_image_undo_thaw' to temporarily disable an image undo stack. This is advantageous because saving undo steps can be time and memory intensive. 'gimp_image_undo_{freeze,thaw}' and 'gimp_image_undo_{disable,enable}' differ in that the former does not free up all undo steps when undo is thawed, so is more suited to interactive in-situ previews. It is important in this case that the image is back to the same state it was frozen in before thawing, else 'undo' behaviour is undefined."
block|,
literal|"Adam D. Moss"
block|,
literal|"Adam D. Moss"
block|,
literal|"1999"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_undo_freeze_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_undo_thaw_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_undo_thaw_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gboolean
name|thawed
init|=
name|FALSE
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|thawed
operator|=
name|gimp_image_undo_thaw
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_boolean
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|thawed
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_undo_thaw_proc
specifier|static
name|ProcRecord
name|image_undo_thaw_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-image-undo-thaw"
block|,
literal|"gimp-image-undo-thaw"
block|,
literal|"Thaw the image's undo stack."
block|,
literal|"This procedure thaws the image's undo stack, allowing subsequent operations to store their undo steps. This is generally called in conjunction with 'gimp_image_undo_freeze' to temporarily freeze an image undo stack. 'gimp_image_undo_thaw' does NOT free the undo stack as 'gimp_image_undo_enable' does, so is suited for situations where one wishes to leave the undo stack in the same state in which one found it despite non-destructively playing with the image in the meantime. An example would be in-situ plugin previews. Balancing freezes and thaws and ensuring image consistancy is the responsibility of the caller."
block|,
literal|"Adam D. Moss"
block|,
literal|"Adam D. Moss"
block|,
literal|"1999"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_undo_thaw_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

