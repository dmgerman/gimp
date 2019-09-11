begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpplugin-proc.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimpbase/gimpbase.h"
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
file|"pdb/gimppdberror.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-proc.h"
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
file|"gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpPlugInProcedure
modifier|*
name|gimp_plug_in_proc_find
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_plug_in_set_proc_image_types (GimpPlugIn * plug_in,const gchar * proc_name,const gchar * image_types,GError ** error)
name|gimp_plug_in_set_proc_image_types
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|image_types
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register images types "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_plug_in_procedure_set_image_types
argument_list|(
name|proc
argument_list|,
name|image_types
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_set_proc_menu_label (GimpPlugIn * plug_in,const gchar * proc_name,const gchar * menu_label,GError ** error)
name|gimp_plug_in_set_proc_menu_label
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_label
operator|!=
name|NULL
operator|&&
name|strlen
argument_list|(
name|menu_label
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register the menu label \"%s\" "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|menu_label
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|gimp_plug_in_procedure_set_menu_label
argument_list|(
name|proc
argument_list|,
name|menu_label
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_add_proc_menu_path (GimpPlugIn * plug_in,const gchar * proc_name,const gchar * menu_path,GError ** error)
name|gimp_plug_in_add_proc_menu_path
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
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
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register the menu item \"%s\" "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|menu_path
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|gimp_plug_in_procedure_add_menu_path
argument_list|(
name|proc
argument_list|,
name|menu_path
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_set_proc_icon (GimpPlugIn * plug_in,const gchar * proc_name,GimpIconType type,const guint8 * data,gint data_length,GError ** error)
name|gimp_plug_in_set_proc_icon
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|GimpIconType
name|type
parameter_list|,
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|data_length
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to set the icon "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|type
argument_list|,
name|data
argument_list|,
name|data_length
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_set_proc_help (GimpPlugIn * plug_in,const gchar * proc_name,const gchar * blurb,const gchar * help,const gchar * help_id,GError ** error)
name|gimp_plug_in_set_proc_help
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register help "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_procedure_set_help
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|,
name|blurb
argument_list|,
name|help
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_set_proc_attribution (GimpPlugIn * plug_in,const gchar * proc_name,const gchar * authors,const gchar * copyright,const gchar * date,GError ** error)
name|gimp_plug_in_set_proc_attribution
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|authors
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register the attribution "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_procedure_set_attribution
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|,
name|authors
argument_list|,
name|copyright
argument_list|,
name|date
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|gboolean
DECL|function|GIMP_IS_PARAM_SPEC_RUN_MODE (GParamSpec * pspec)
name|GIMP_IS_PARAM_SPEC_RUN_MODE
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
return|return
operator|(
name|G_IS_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
operator|&&
name|pspec
operator|->
name|value_type
operator|==
name|GIMP_TYPE_RUN_MODE
operator|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|gboolean
DECL|function|GIMP_IS_PARAM_SPEC_FILE (GParamSpec * pspec)
name|GIMP_IS_PARAM_SPEC_FILE
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
return|return
operator|(
name|G_IS_PARAM_SPEC_OBJECT
argument_list|(
name|pspec
argument_list|)
operator|&&
name|pspec
operator|->
name|value_type
operator|==
name|G_TYPE_FILE
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_set_file_proc_load_handler (GimpPlugIn * plug_in,const gchar * proc_name,const gchar * extensions,const gchar * prefixes,const gchar * magics,GError ** error)
name|gimp_plug_in_set_file_proc_load_handler
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register procedure \"%s\" "
literal|"as load handler.\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
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
name|proc
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
literal|2
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
name|GIMP_IS_PARAM_SPEC_RUN_MODE
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
name|GIMP_IS_PARAM_SPEC_FILE
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|1
index|]
argument_list|)
operator|||
operator|(
operator|!
name|proc
operator|->
name|generic_file_proc
operator|&&
operator|!
name|GIMP_IS_PARAM_SPEC_IMAGE
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
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_FAILED
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register procedure \"%s\" "
literal|"as load handler which does not take the standard "
literal|"load procedure arguments: "
literal|"(GimpRunMode, GFile) -> (GimpImage)"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_plug_in_procedure_set_file_proc
argument_list|(
name|proc
argument_list|,
name|extensions
argument_list|,
name|prefixes
argument_list|,
name|magics
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_load_procedure
argument_list|(
name|plug_in
operator|->
name|manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_set_file_proc_save_handler (GimpPlugIn * plug_in,const gchar * proc_name,const gchar * extensions,const gchar * prefixes,GError ** error)
name|gimp_plug_in_set_file_proc_save_handler
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
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
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register procedure \"%s\" "
literal|"as save handler.\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
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
name|proc
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|procedure
operator|->
name|num_args
operator|<
literal|4
operator|)
operator|||
operator|!
name|GIMP_IS_PARAM_SPEC_RUN_MODE
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
name|GIMP_IS_PARAM_SPEC_IMAGE
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
name|GIMP_IS_PARAM_SPEC_DRAWABLE
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
name|GIMP_IS_PARAM_SPEC_FILE
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|3
index|]
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_FAILED
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register procedure \"%s\" "
literal|"as save handler which does not take the standard "
literal|"save procedure arguments: "
literal|"(GimpRunMode, GimpImage, GimpDrawable, GFile)"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_plug_in_procedure_set_file_proc
argument_list|(
name|proc
argument_list|,
name|extensions
argument_list|,
name|prefixes
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_save_procedure
argument_list|(
name|plug_in
operator|->
name|manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_set_file_proc_priority (GimpPlugIn * plug_in,const gchar * proc_name,gint priority,GError ** error)
name|gimp_plug_in_set_file_proc_priority
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|gint
name|priority
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register the priority "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_plug_in_procedure_set_priority
argument_list|(
name|proc
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
DECL|function|gimp_plug_in_set_file_proc_mime_types (GimpPlugIn * plug_in,const gchar * proc_name,const gchar * mime_types,GError ** error)
name|gimp_plug_in_set_file_proc_mime_types
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_types
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register mime types "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_plug_in_procedure_set_mime_types
argument_list|(
name|proc
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
DECL|function|gimp_plug_in_set_file_proc_handles_remote (GimpPlugIn * plug_in,const gchar * proc_name,GError ** error)
name|gimp_plug_in_set_file_proc_handles_remote
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register 'handles remote' "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_plug_in_procedure_set_handles_remote
argument_list|(
name|proc
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_set_file_proc_handles_raw (GimpPlugIn * plug_in,const gchar * proc_name,GError ** error)
name|gimp_plug_in_set_file_proc_handles_raw
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register 'handles raw' "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_plug_in_procedure_set_handles_raw
argument_list|(
name|proc
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_set_file_proc_thumb_loader (GimpPlugIn * plug_in,const gchar * proc_name,const gchar * thumb_proc_name,GError ** error)
name|gimp_plug_in_set_file_proc_thumb_loader
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|thumb_proc_name
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|GimpPlugInProcedure
modifier|*
name|thumb_proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|thumb_proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
name|thumb_proc
operator|=
name|gimp_plug_in_proc_find
argument_list|(
name|plug_in
argument_list|,
name|thumb_proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register a thumbnail loader "
literal|"for procedure \"%s\".\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
operator|!
name|thumb_proc
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
literal|"Plug-in \"%s\"\n(%s)\n"
literal|"attempted to register a procedure \"%s\" "
literal|"as thumbnail loader.\n"
literal|"It has however not installed that procedure. "
literal|"This is not allowed."
argument_list|,
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|plug_in
operator|->
name|file
argument_list|)
argument_list|,
name|thumb_proc_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_plug_in_procedure_set_thumb_loader
argument_list|(
name|proc
argument_list|,
name|thumb_proc_name
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpPlugInProcedure
modifier|*
DECL|function|gimp_plug_in_proc_find (GimpPlugIn * plug_in,const gchar * proc_name)
name|gimp_plug_in_proc_find
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|plug_in
operator|->
name|plug_in_def
condition|)
name|proc
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|plug_in
operator|->
name|plug_in_def
operator|->
name|procedures
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
name|proc
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|plug_in
operator|->
name|temp_procedures
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
return|return
name|proc
return|;
block|}
end_function

end_unit

