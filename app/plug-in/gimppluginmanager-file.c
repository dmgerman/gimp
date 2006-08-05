begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginmanager-file.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-def.h"
end_include

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
name|g_message
argument_list|(
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
condition|)
block|{
name|g_message
argument_list|(
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
name|g_message
argument_list|(
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
name|g_message
argument_list|(
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
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_manager_register_mime_type (GimpPlugInManager * manager,const gchar * name,const gchar * mime_type)
name|gimp_plug_in_manager_register_mime_type
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
name|mime_type
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
name|mime_type
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
name|gimp_plug_in_procedure_set_mime_type
argument_list|(
name|file_proc
argument_list|,
name|mime_type
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

end_unit

