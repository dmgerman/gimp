begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginmanager-file.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugindef.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-file.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-file-procedure.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginprocedure.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|file_procedure_in_group
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|file_proc
parameter_list|,
name|GimpFileProcedureGroup
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_plug_in_manager_register_load_handler (GimpPlugInManager * manager,const gchar * name,const gchar * extensions,const gchar * prefixes,const gchar * magics)
name|gimp_plug_in_manager_register_load_handler
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extensions
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefixes
parameter_list|,
specifier|const
name|gchar
modifier|*
name|magics
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|current_plug_in
operator|&&
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
condition|)
name|list
operator|=
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
operator|->
name|procedures
expr_stmt|;
else|else
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
expr_stmt|;
name|file_proc
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
block|{
name|gimp_message
argument_list|(
name|manager
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"attempt to register nonexistent load handler \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|procedure
operator|=
name|GIMP_PROCEDURE
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|procedure
operator|->
name|num_args
operator|<
literal|3
operator|)
operator|||
operator|(
name|procedure
operator|->
name|num_values
operator|<
literal|1
operator|)
operator|||
operator|!
name|GIMP_IS_PARAM_SPEC_INT32
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|0
index|]
argument_list|)
operator|||
operator|!
name|G_IS_PARAM_SPEC_STRING
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|1
index|]
argument_list|)
operator|||
operator|!
name|G_IS_PARAM_SPEC_STRING
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|2
index|]
argument_list|)
operator|||
operator|(
operator|!
name|file_proc
operator|->
name|generic_file_proc
operator|&&
operator|!
name|GIMP_IS_PARAM_SPEC_IMAGE_ID
argument_list|(
name|procedure
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
operator|)
operator|)
condition|)
block|{
name|gimp_message
argument_list|(
name|manager
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"load handler \"%s\" does not take the standard "
literal|"load handler args"
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_plug_in_procedure_set_file_proc
argument_list|(
name|file_proc
argument_list|,
name|extensions
argument_list|,
name|prefixes
argument_list|,
name|magics
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_slist_find
argument_list|(
name|manager
operator|->
name|load_procs
argument_list|,
name|file_proc
argument_list|)
condition|)
name|manager
operator|->
name|load_procs
operator|=
name|g_slist_prepend
argument_list|(
name|manager
operator|->
name|load_procs
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_manager_register_save_handler (GimpPlugInManager * manager,const gchar * name,const gchar * extensions,const gchar * prefixes)
name|gimp_plug_in_manager_register_save_handler
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extensions
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefixes
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|current_plug_in
operator|&&
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
condition|)
name|list
operator|=
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
operator|->
name|procedures
expr_stmt|;
else|else
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
expr_stmt|;
name|file_proc
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
block|{
name|gimp_message
argument_list|(
name|manager
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"attempt to register nonexistent save handler \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|procedure
operator|=
name|GIMP_PROCEDURE
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|procedure
operator|->
name|num_args
operator|<
literal|5
operator|)
operator|||
operator|!
name|GIMP_IS_PARAM_SPEC_INT32
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|0
index|]
argument_list|)
operator|||
operator|!
name|GIMP_IS_PARAM_SPEC_IMAGE_ID
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|1
index|]
argument_list|)
operator|||
operator|!
name|GIMP_IS_PARAM_SPEC_DRAWABLE_ID
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|2
index|]
argument_list|)
operator|||
operator|!
name|G_IS_PARAM_SPEC_STRING
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|3
index|]
argument_list|)
operator|||
operator|!
name|G_IS_PARAM_SPEC_STRING
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|4
index|]
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|manager
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"save handler \"%s\" does not take the standard "
literal|"save handler args"
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_plug_in_procedure_set_file_proc
argument_list|(
name|file_proc
argument_list|,
name|extensions
argument_list|,
name|prefixes
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_procedure_in_group
argument_list|(
name|file_proc
argument_list|,
name|GIMP_FILE_PROCEDURE_GROUP_SAVE
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|g_slist_find
argument_list|(
name|manager
operator|->
name|save_procs
argument_list|,
name|file_proc
argument_list|)
condition|)
name|manager
operator|->
name|save_procs
operator|=
name|g_slist_prepend
argument_list|(
name|manager
operator|->
name|save_procs
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|file_procedure_in_group
argument_list|(
name|file_proc
argument_list|,
name|GIMP_FILE_PROCEDURE_GROUP_EXPORT
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|g_slist_find
argument_list|(
name|manager
operator|->
name|export_procs
argument_list|,
name|file_proc
argument_list|)
condition|)
name|manager
operator|->
name|export_procs
operator|=
name|g_slist_prepend
argument_list|(
name|manager
operator|->
name|export_procs
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_manager_register_priority (GimpPlugInManager * manager,const gchar * name,gint priority)
name|gimp_plug_in_manager_register_priority
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|priority
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|current_plug_in
operator|&&
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
condition|)
name|list
operator|=
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
operator|->
name|procedures
expr_stmt|;
else|else
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
expr_stmt|;
name|file_proc
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
return|return
name|FALSE
return|;
name|gimp_plug_in_procedure_set_priority
argument_list|(
name|file_proc
argument_list|,
name|priority
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_manager_register_mime_types (GimpPlugInManager * manager,const gchar * name,const gchar * mime_types)
name|gimp_plug_in_manager_register_mime_types
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_types
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|mime_types
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|current_plug_in
operator|&&
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
condition|)
name|list
operator|=
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
operator|->
name|procedures
expr_stmt|;
else|else
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
expr_stmt|;
name|file_proc
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
return|return
name|FALSE
return|;
name|gimp_plug_in_procedure_set_mime_types
argument_list|(
name|file_proc
argument_list|,
name|mime_types
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_manager_register_handles_uri (GimpPlugInManager * manager,const gchar * name)
name|gimp_plug_in_manager_register_handles_uri
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|current_plug_in
operator|&&
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
condition|)
name|list
operator|=
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
operator|->
name|procedures
expr_stmt|;
else|else
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
expr_stmt|;
name|file_proc
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
return|return
name|FALSE
return|;
name|gimp_plug_in_procedure_set_handles_uri
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_manager_register_handles_raw (GimpPlugInManager * manager,const gchar * name)
name|gimp_plug_in_manager_register_handles_raw
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|current_plug_in
operator|&&
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
condition|)
name|list
operator|=
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
operator|->
name|procedures
expr_stmt|;
else|else
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
expr_stmt|;
name|file_proc
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
return|return
name|FALSE
return|;
name|gimp_plug_in_procedure_set_handles_raw
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_manager_register_thumb_loader (GimpPlugInManager * manager,const gchar * load_proc,const gchar * thumb_proc)
name|gimp_plug_in_manager_register_thumb_loader
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|load_proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|thumb_proc
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|load_proc
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|thumb_proc
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|current_plug_in
operator|&&
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
condition|)
name|list
operator|=
name|manager
operator|->
name|current_plug_in
operator|->
name|plug_in_def
operator|->
name|procedures
expr_stmt|;
else|else
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
expr_stmt|;
name|file_proc
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|list
argument_list|,
name|load_proc
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
return|return
name|FALSE
return|;
name|gimp_plug_in_procedure_set_thumb_loader
argument_list|(
name|file_proc
argument_list|,
name|thumb_proc
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GSList
modifier|*
DECL|function|gimp_plug_in_manager_get_file_procedures (GimpPlugInManager * manager,GimpFileProcedureGroup group)
name|gimp_plug_in_manager_get_file_procedures
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpFileProcedureGroup
name|group
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|group
condition|)
block|{
case|case
name|GIMP_FILE_PROCEDURE_GROUP_NONE
case|:
return|return
name|NULL
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_OPEN
case|:
return|return
name|manager
operator|->
name|display_load_procs
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_SAVE
case|:
return|return
name|manager
operator|->
name|display_save_procs
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_EXPORT
case|:
return|return
name|manager
operator|->
name|display_export_procs
return|;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|gimp_plug_in_manager_file_procedure_find (GimpPlugInManager * manager,GimpFileProcedureGroup group,GFile * file,GError ** error)
name|gimp_plug_in_manager_file_procedure_find
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpFileProcedureGroup
name|group
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|group
condition|)
block|{
case|case
name|GIMP_FILE_PROCEDURE_GROUP_OPEN
case|:
return|return
name|file_procedure_find
argument_list|(
name|manager
operator|->
name|load_procs
argument_list|,
name|file
argument_list|,
name|error
argument_list|)
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_SAVE
case|:
return|return
name|file_procedure_find
argument_list|(
name|manager
operator|->
name|save_procs
argument_list|,
name|file
argument_list|,
name|error
argument_list|)
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_EXPORT
case|:
return|return
name|file_procedure_find
argument_list|(
name|manager
operator|->
name|export_procs
argument_list|,
name|file
argument_list|,
name|error
argument_list|)
return|;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|gimp_plug_in_manager_file_procedure_find_by_prefix (GimpPlugInManager * manager,GimpFileProcedureGroup group,GFile * file)
name|gimp_plug_in_manager_file_procedure_find_by_prefix
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpFileProcedureGroup
name|group
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|group
condition|)
block|{
case|case
name|GIMP_FILE_PROCEDURE_GROUP_OPEN
case|:
return|return
name|file_procedure_find_by_prefix
argument_list|(
name|manager
operator|->
name|load_procs
argument_list|,
name|file
argument_list|)
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_SAVE
case|:
return|return
name|file_procedure_find_by_prefix
argument_list|(
name|manager
operator|->
name|save_procs
argument_list|,
name|file
argument_list|)
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_EXPORT
case|:
return|return
name|file_procedure_find_by_prefix
argument_list|(
name|manager
operator|->
name|export_procs
argument_list|,
name|file
argument_list|)
return|;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|gimp_plug_in_manager_file_procedure_find_by_extension (GimpPlugInManager * manager,GimpFileProcedureGroup group,GFile * file)
name|gimp_plug_in_manager_file_procedure_find_by_extension
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpFileProcedureGroup
name|group
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|group
condition|)
block|{
case|case
name|GIMP_FILE_PROCEDURE_GROUP_OPEN
case|:
return|return
name|file_procedure_find_by_extension
argument_list|(
name|manager
operator|->
name|load_procs
argument_list|,
name|file
argument_list|)
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_SAVE
case|:
return|return
name|file_procedure_find_by_extension
argument_list|(
name|manager
operator|->
name|save_procs
argument_list|,
name|file
argument_list|)
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_EXPORT
case|:
return|return
name|file_procedure_find_by_extension
argument_list|(
name|manager
operator|->
name|export_procs
argument_list|,
name|file
argument_list|)
return|;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|gimp_plug_in_manager_file_procedure_find_by_mime_type (GimpPlugInManager * manager,GimpFileProcedureGroup group,const gchar * mime_type)
name|gimp_plug_in_manager_file_procedure_find_by_mime_type
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpFileProcedureGroup
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|mime_type
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|group
condition|)
block|{
case|case
name|GIMP_FILE_PROCEDURE_GROUP_OPEN
case|:
return|return
name|file_procedure_find_by_mime_type
argument_list|(
name|manager
operator|->
name|load_procs
argument_list|,
name|mime_type
argument_list|)
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_SAVE
case|:
return|return
name|file_procedure_find_by_mime_type
argument_list|(
name|manager
operator|->
name|save_procs
argument_list|,
name|mime_type
argument_list|)
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_EXPORT
case|:
return|return
name|file_procedure_find_by_mime_type
argument_list|(
name|manager
operator|->
name|export_procs
argument_list|,
name|mime_type
argument_list|)
return|;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|file_procedure_in_group (GimpPlugInProcedure * file_proc,GimpFileProcedureGroup group)
name|file_procedure_in_group
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|file_proc
parameter_list|,
name|GimpFileProcedureGroup
name|group
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gimp_object_get_name
argument_list|(
name|file_proc
argument_list|)
decl_stmt|;
name|gboolean
name|is_xcf_save
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|is_filter
init|=
name|FALSE
decl_stmt|;
name|is_xcf_save
operator|=
operator|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"gimp-xcf-save"
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
name|is_filter
operator|=
operator|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file-gz-save"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file-bz2-save"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file-xz-save"
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
switch|switch
condition|(
name|group
condition|)
block|{
case|case
name|GIMP_FILE_PROCEDURE_GROUP_NONE
case|:
return|return
name|FALSE
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_SAVE
case|:
comment|/* Only .xcf shall pass */
return|return
name|is_xcf_save
operator|||
name|is_filter
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_EXPORT
case|:
comment|/* Anything but .xcf shall pass */
return|return
operator|!
name|is_xcf_save
return|;
case|case
name|GIMP_FILE_PROCEDURE_GROUP_OPEN
case|:
comment|/* No filter applied for Open */
return|return
name|TRUE
return|;
default|default:
case|case
name|GIMP_FILE_PROCEDURE_GROUP_ANY
case|:
return|return
name|TRUE
return|;
block|}
block|}
end_function

end_unit

