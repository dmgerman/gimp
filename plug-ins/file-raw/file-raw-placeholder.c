begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-raw-placeholder.c -- raw file format plug-in that does nothing  *                           except warning that there is no raw plug-in  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  * Copyright (C) 2016 Tobias Ellinghaus<me@houz.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"file-raw-formats.h"
end_include

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc */
name|NULL
block|,
comment|/* quit_proc */
name|query
block|,
comment|/* query proc */
name|run
block|,
comment|/* run_proc */
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|load_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load."
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name entered"
block|}
block|,   }
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|load_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|}
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|file_formats
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
specifier|const
name|FileFormat
modifier|*
name|format
init|=
operator|&
name|file_formats
index|[
name|i
index|]
decl_stmt|;
name|gchar
modifier|*
name|load_proc
decl_stmt|;
name|gchar
modifier|*
name|load_blurb
decl_stmt|;
name|gchar
modifier|*
name|load_help
decl_stmt|;
name|load_proc
operator|=
name|g_strdup_printf
argument_list|(
name|format
operator|->
name|load_proc_format
argument_list|,
literal|"raw-placeholder"
argument_list|)
expr_stmt|;
name|load_blurb
operator|=
name|g_strdup_printf
argument_list|(
name|format
operator|->
name|load_blurb_format
argument_list|,
literal|"raw-placeholder"
argument_list|)
expr_stmt|;
name|load_help
operator|=
name|g_strdup_printf
argument_list|(
name|format
operator|->
name|load_help_format
argument_list|,
literal|"raw-placeholder"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|load_proc
argument_list|,
name|load_blurb
argument_list|,
name|load_help
argument_list|,
literal|"Tobias Ellinghaus"
argument_list|,
literal|"Tobias Ellinghaus"
argument_list|,
literal|"2016"
argument_list|,
name|format
operator|->
name|file_type
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_return_vals
argument_list|)
argument_list|,
name|load_args
argument_list|,
name|load_return_vals
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|load_proc
argument_list|,
name|format
operator|->
name|mime_type
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_raw
argument_list|(
name|load_proc
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|load_proc
argument_list|,
name|format
operator|->
name|extensions
argument_list|,
literal|""
argument_list|,
name|format
operator|->
name|magic
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|load_proc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|load_blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|load_help
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|6
index|]
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_EXECUTION_ERROR
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
comment|/* check if the format passed is actually supported& load */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|file_formats
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
specifier|const
name|FileFormat
modifier|*
name|format
init|=
operator|&
name|file_formats
index|[
name|i
index|]
decl_stmt|;
name|gchar
modifier|*
name|load_proc
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|format
operator|->
name|load_proc_format
condition|)
name|load_proc
operator|=
name|g_strdup_printf
argument_list|(
name|format
operator|->
name|load_proc_format
argument_list|,
literal|"raw-placeholder"
argument_list|)
expr_stmt|;
if|if
condition|(
name|load_proc
operator|&&
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|load_proc
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
operator|&
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"There is no RAW loader installed to open '%s' files.\n"
literal|"\n"
literal|"GIMP currently supports these RAW loaders:\n"
literal|"- darktable (http://www.darktable.org/), at least 1.7\n"
literal|"- RawTherapee (http://rawtherapee.com/), at least 5.2\n"
literal|"\n"
literal|"Please install one of them in order to "
literal|"load RAW files."
argument_list|)
argument_list|,
name|gettext
argument_list|(
name|format
operator|->
name|file_type
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|i
operator|==
name|G_N_ELEMENTS
argument_list|(
name|file_formats
argument_list|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_SUCCESS
operator|&&
name|error
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
operator|=
name|error
operator|->
name|message
expr_stmt|;
block|}
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

end_unit

