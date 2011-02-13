begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* Author: Josh MacDonald. */
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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"uri-backend.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-uri-load"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-uri-save"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-uri"
end_define

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

begin_function_decl
specifier|static
name|gint32
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpPDBStatusType
name|save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|get_temp_name
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
modifier|*
name|name_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|valid_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
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
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
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
literal|"The name of the file to load"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name entered"
block|}
block|}
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
specifier|static
specifier|const
name|GimpParamDef
name|save_args
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
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to save"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|}
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|uri_backend_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"%s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|uri_backend_get_load_protocols
argument_list|()
condition|)
block|{
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"loads files given an URI"
argument_list|,
name|uri_backend_get_load_help
argument_list|()
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-2008"
argument_list|,
name|N_
argument_list|(
literal|"URI"
argument_list|)
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
name|gimp_plugin_icon_register
argument_list|(
name|LOAD_PROC
argument_list|,
name|GIMP_ICON_TYPE_STOCK_ID
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
name|GIMP_STOCK_WEB
argument_list|)
expr_stmt|;
name|gimp_register_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|""
argument_list|,
name|uri_backend_get_load_protocols
argument_list|()
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|uri_backend_get_save_protocols
argument_list|()
condition|)
block|{
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"saves files given an URI"
argument_list|,
name|uri_backend_get_save_help
argument_list|()
argument_list|,
literal|"Michael Natterer, Sven Neumann"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2005-2008"
argument_list|,
name|N_
argument_list|(
literal|"URI"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|save_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|save_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_icon_register
argument_list|(
name|SAVE_PROC
argument_list|,
name|GIMP_ICON_TYPE_STOCK_ID
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
name|GIMP_STOCK_WEB
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
argument_list|,
literal|""
argument_list|,
name|uri_backend_get_save_protocols
argument_list|()
argument_list|)
expr_stmt|;
block|}
name|uri_backend_shutdown
argument_list|()
expr_stmt|;
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
literal|2
index|]
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_EXECUTION_ERROR
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
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
name|status
expr_stmt|;
if|if
condition|(
operator|!
name|uri_backend_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|TRUE
argument_list|,
name|run_mode
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
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
return|return;
block|}
comment|/*  We handle PDB errors by forwarding them to the caller in    *  our return values.    */
name|gimp_plugin_set_pdb_error_handler
argument_list|(
name|GIMP_PDB_ERROR_HANDLER_PLUGIN
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|LOAD_PROC
argument_list|)
operator|&&
name|uri_backend_get_load_protocols
argument_list|()
condition|)
block|{
name|image_ID
operator|=
name|load_image
argument_list|(
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|run_mode
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
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
name|GIMP_PDB_IMAGE
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image_ID
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|SAVE_PROC
argument_list|)
operator|&&
name|uri_backend_get_save_protocols
argument_list|()
condition|)
block|{
name|status
operator|=
name|save_image
argument_list|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|run_mode
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
name|uri_backend_shutdown
argument_list|()
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

begin_function
specifier|static
name|gint32
DECL|function|load_image (const gchar * uri,GimpRunMode run_mode,GError ** error)
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
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
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|gboolean
name|name_image
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|tmpname
decl_stmt|;
name|gboolean
name|mapped
init|=
name|FALSE
decl_stmt|;
name|tmpname
operator|=
name|uri_backend_map_image
argument_list|(
name|uri
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
if|if
condition|(
name|tmpname
condition|)
block|{
name|mapped
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|tmpname
operator|=
name|get_temp_name
argument_list|(
name|uri
argument_list|,
operator|&
name|name_image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|uri_backend_load_image
argument_list|(
name|uri
argument_list|,
name|tmpname
argument_list|,
name|run_mode
argument_list|,
name|error
argument_list|)
condition|)
return|return
operator|-
literal|1
return|;
block|}
name|image_ID
operator|=
name|gimp_file_load
argument_list|(
name|run_mode
argument_list|,
name|tmpname
argument_list|,
name|tmpname
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
if|if
condition|(
name|mapped
operator|||
name|name_image
condition|)
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|uri
argument_list|)
expr_stmt|;
else|else
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
literal|"%s"
argument_list|,
name|gimp_get_pdb_error
argument_list|()
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|mapped
condition|)
name|g_unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_function
specifier|static
name|GimpPDBStatusType
DECL|function|save_image (const gchar * uri,gint32 image_ID,gint32 drawable_ID,gint32 run_mode,GError ** error)
name|save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_EXECUTION_ERROR
decl_stmt|;
name|gchar
modifier|*
name|tmpname
decl_stmt|;
name|gboolean
name|mapped
init|=
name|FALSE
decl_stmt|;
name|tmpname
operator|=
name|uri_backend_map_image
argument_list|(
name|uri
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
if|if
condition|(
name|tmpname
condition|)
name|mapped
operator|=
name|TRUE
expr_stmt|;
else|else
name|tmpname
operator|=
name|get_temp_name
argument_list|(
name|uri
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_file_save
argument_list|(
name|run_mode
argument_list|,
name|image_ID
argument_list|,
name|drawable_ID
argument_list|,
name|tmpname
argument_list|,
name|tmpname
argument_list|)
operator|&&
name|valid_file
argument_list|(
name|tmpname
argument_list|)
condition|)
block|{
if|if
condition|(
name|mapped
operator|||
name|uri_backend_save_image
argument_list|(
name|uri
argument_list|,
name|tmpname
argument_list|,
name|run_mode
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
literal|"%s"
argument_list|,
name|gimp_get_pdb_error
argument_list|()
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|mapped
condition|)
name|g_unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|status
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|get_temp_name (const gchar * uri,gboolean * name_image)
name|get_temp_name
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
modifier|*
name|name_image
parameter_list|)
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|tmpname
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|name_image
condition|)
operator|*
name|name_image
operator|=
name|FALSE
expr_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|basename
condition|)
block|{
name|gchar
modifier|*
name|ext
init|=
name|strchr
argument_list|(
name|basename
argument_list|,
literal|'.'
argument_list|)
decl_stmt|;
if|if
condition|(
name|ext
operator|&&
name|strlen
argument_list|(
name|ext
argument_list|)
condition|)
block|{
name|tmpname
operator|=
name|gimp_temp_name
argument_list|(
name|ext
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|name_image
condition|)
operator|*
name|name_image
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|tmpname
condition|)
name|tmpname
operator|=
name|gimp_temp_name
argument_list|(
literal|"xxx"
argument_list|)
expr_stmt|;
return|return
name|tmpname
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|valid_file (const gchar * filename)
name|valid_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|struct
name|stat
name|buf
decl_stmt|;
return|return
name|g_stat
argument_list|(
name|filename
argument_list|,
operator|&
name|buf
argument_list|)
operator|==
literal|0
operator|&&
name|buf
operator|.
name|st_size
operator|>
literal|0
return|;
block|}
end_function

end_unit

