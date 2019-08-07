begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpplugin-private.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpprotocol.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpwire.h"
end_include

begin_include
include|#
directive|include
file|"gimp-private.h"
end_include

begin_include
include|#
directive|include
file|"gimp-shm.h"
end_include

begin_include
include|#
directive|include
file|"gimpgpparams.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin_pdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure-private.h"
end_include

begin_comment
comment|/*  local function prototpes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_register
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GList
modifier|*
name|procedures
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_loop
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_process_message
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpWireMessage
modifier|*
name|msg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_proc_run
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GPProcRun
modifier|*
name|proc_run
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_temp_proc_run
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GPProcRun
modifier|*
name|proc_run
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_proc_run_internal
parameter_list|(
name|GPProcRun
modifier|*
name|proc_run
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GPProcReturn
modifier|*
name|proc_return
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_plug_in_io_error_handler
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GIOCondition
name|cond
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|_gimp_plug_in_query (GimpPlugIn * plug_in)
name|_gimp_plug_in_query
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|init_procedures
condition|)
name|gp_has_init_write
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|write_channel
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|query_procedures
condition|)
block|{
name|GList
modifier|*
name|procedures
init|=
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|query_procedures
argument_list|(
name|plug_in
argument_list|)
decl_stmt|;
name|gimp_plug_in_register
argument_list|(
name|plug_in
argument_list|,
name|procedures
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|_gimp_plug_in_init (GimpPlugIn * plug_in)
name|_gimp_plug_in_init
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|init_procedures
condition|)
block|{
name|GList
modifier|*
name|procedures
init|=
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|init_procedures
argument_list|(
name|plug_in
argument_list|)
decl_stmt|;
name|gimp_plug_in_register
argument_list|(
name|plug_in
argument_list|,
name|procedures
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|_gimp_plug_in_run (GimpPlugIn * plug_in)
name|_gimp_plug_in_run
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|g_io_add_watch
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|read_channel
argument_list|,
name|G_IO_ERR
operator||
name|G_IO_HUP
argument_list|,
name|gimp_plug_in_io_error_handler
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_loop
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_plug_in_quit (GimpPlugIn * plug_in)
name|_gimp_plug_in_quit
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|quit
condition|)
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|quit
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|_gimp_shm_close
argument_list|()
expr_stmt|;
name|gp_quit_write
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|write_channel
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GIOChannel
modifier|*
DECL|function|_gimp_plug_in_get_read_channel (GimpPlugIn * plug_in)
name|_gimp_plug_in_get_read_channel
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|plug_in
operator|->
name|priv
operator|->
name|read_channel
return|;
block|}
end_function

begin_function
name|GIOChannel
modifier|*
DECL|function|_gimp_plug_in_get_write_channel (GimpPlugIn * plug_in)
name|_gimp_plug_in_get_write_channel
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|plug_in
operator|->
name|priv
operator|->
name|write_channel
return|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_plug_in_read_expect_msg (GimpPlugIn * plug_in,GimpWireMessage * msg,gint type)
name|_gimp_plug_in_read_expect_msg
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpWireMessage
modifier|*
name|msg
parameter_list|,
name|gint
name|type
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|TRUE
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_wire_read_msg
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|read_channel
argument_list|,
name|msg
argument_list|,
name|NULL
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
if|if
condition|(
name|msg
operator|->
name|type
operator|==
name|type
condition|)
return|return;
comment|/* up to the caller to call wire_destroy() */
if|if
condition|(
name|msg
operator|->
name|type
operator|==
name|GP_TEMP_PROC_RUN
operator|||
name|msg
operator|->
name|type
operator|==
name|GP_QUIT
condition|)
block|{
name|gimp_plug_in_process_message
argument_list|(
name|plug_in
argument_list|,
name|msg
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_error
argument_list|(
literal|"unexpected message: %d"
argument_list|,
name|msg
operator|->
name|type
argument_list|)
expr_stmt|;
block|}
name|gimp_wire_destroy
argument_list|(
name|msg
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|_gimp_plug_in_extension_read (GIOChannel * channel,GIOCondition condition,gpointer data)
name|_gimp_plug_in_extension_read
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GIOCondition
name|condition
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|data
decl_stmt|;
name|_gimp_plug_in_single_message
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
return|return
name|G_SOURCE_CONTINUE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_register (GimpPlugIn * plug_in,GList * procedures)
name|gimp_plug_in_register
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GList
modifier|*
name|procedures
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|procedures
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|procedure
operator|=
name|gimp_plug_in_create_procedure
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
condition|)
block|{
name|_gimp_procedure_register
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"Plug-in failed to create procedure '%s'\n"
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
block|}
name|g_list_free_full
argument_list|(
name|procedures
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
operator|->
name|priv
operator|->
name|translation_domain_name
condition|)
block|{
name|gchar
modifier|*
name|path
init|=
name|g_file_get_path
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|translation_domain_path
argument_list|)
decl_stmt|;
name|_gimp_plugin_domain_register
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|translation_domain_name
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|plug_in
operator|->
name|priv
operator|->
name|help_domain_name
condition|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|g_file_get_uri
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|help_domain_uri
argument_list|)
decl_stmt|;
name|_gimp_plugin_help_register
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|help_domain_name
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|plug_in
operator|->
name|priv
operator|->
name|menu_branches
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInMenuBranch
modifier|*
name|branch
init|=
name|list
operator|->
name|data
decl_stmt|;
name|_gimp_plugin_menu_branch_register
argument_list|(
name|branch
operator|->
name|menu_path
argument_list|,
name|branch
operator|->
name|menu_label
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_loop (GimpPlugIn * plug_in)
name|gimp_plug_in_loop
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
while|while
condition|(
name|TRUE
condition|)
block|{
name|GimpWireMessage
name|msg
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_wire_read_msg
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|read_channel
argument_list|,
operator|&
name|msg
argument_list|,
name|NULL
argument_list|)
condition|)
return|return;
switch|switch
condition|(
name|msg
operator|.
name|type
condition|)
block|{
case|case
name|GP_QUIT
case|:
name|gimp_wire_destroy
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
return|return;
case|case
name|GP_CONFIG
case|:
name|_gimp_config
argument_list|(
name|msg
operator|.
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_TILE_REQ
case|:
case|case
name|GP_TILE_ACK
case|:
case|case
name|GP_TILE_DATA
case|:
name|g_warning
argument_list|(
literal|"unexpected tile message received (should not happen)"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_PROC_RUN
case|:
name|gimp_plug_in_proc_run
argument_list|(
name|plug_in
argument_list|,
name|msg
operator|.
name|data
argument_list|)
expr_stmt|;
name|gimp_wire_destroy
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
return|return;
case|case
name|GP_PROC_RETURN
case|:
name|g_warning
argument_list|(
literal|"unexpected proc return message received (should not happen)"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_TEMP_PROC_RUN
case|:
name|g_warning
argument_list|(
literal|"unexpected temp proc run message received (should not happen"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_TEMP_PROC_RETURN
case|:
name|g_warning
argument_list|(
literal|"unexpected temp proc return message received (should not happen"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_PROC_INSTALL
case|:
name|g_warning
argument_list|(
literal|"unexpected proc install message received (should not happen)"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_HAS_INIT
case|:
name|g_warning
argument_list|(
literal|"unexpected has init message received (should not happen)"
argument_list|)
expr_stmt|;
break|break;
block|}
name|gimp_wire_destroy
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|_gimp_plug_in_single_message (GimpPlugIn * plug_in)
name|_gimp_plug_in_single_message
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GimpWireMessage
name|msg
decl_stmt|;
comment|/* Run a temp function */
if|if
condition|(
operator|!
name|gimp_wire_read_msg
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|read_channel
argument_list|,
operator|&
name|msg
argument_list|,
name|NULL
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|gimp_plug_in_process_message
argument_list|(
name|plug_in
argument_list|,
operator|&
name|msg
argument_list|)
expr_stmt|;
name|gimp_wire_destroy
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_process_message (GimpPlugIn * plug_in,GimpWireMessage * msg)
name|gimp_plug_in_process_message
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpWireMessage
modifier|*
name|msg
parameter_list|)
block|{
switch|switch
condition|(
name|msg
operator|->
name|type
condition|)
block|{
case|case
name|GP_QUIT
case|:
name|gimp_quit
argument_list|()
expr_stmt|;
break|break;
case|case
name|GP_CONFIG
case|:
name|_gimp_config
argument_list|(
name|msg
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_TILE_REQ
case|:
case|case
name|GP_TILE_ACK
case|:
case|case
name|GP_TILE_DATA
case|:
name|g_warning
argument_list|(
literal|"unexpected tile message received (should not happen)"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_PROC_RUN
case|:
name|g_warning
argument_list|(
literal|"unexpected proc run message received (should not happen)"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_PROC_RETURN
case|:
name|g_warning
argument_list|(
literal|"unexpected proc return message received (should not happen)"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_TEMP_PROC_RUN
case|:
name|gimp_plug_in_temp_proc_run
argument_list|(
name|plug_in
argument_list|,
name|msg
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_TEMP_PROC_RETURN
case|:
name|g_warning
argument_list|(
literal|"unexpected temp proc return message received (should not happen)"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_PROC_INSTALL
case|:
name|g_warning
argument_list|(
literal|"unexpected proc install message received (should not happen)"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GP_HAS_INIT
case|:
name|g_warning
argument_list|(
literal|"unexpected has init message received (should not happen)"
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_proc_run (GimpPlugIn * plug_in,GPProcRun * proc_run)
name|gimp_plug_in_proc_run
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GPProcRun
modifier|*
name|proc_run
parameter_list|)
block|{
name|GPProcReturn
name|proc_return
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|procedure
operator|=
name|gimp_plug_in_create_procedure
argument_list|(
name|plug_in
argument_list|,
name|proc_run
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
condition|)
block|{
name|gimp_plug_in_proc_run_internal
argument_list|(
name|proc_run
argument_list|,
name|procedure
argument_list|,
operator|&
name|proc_return
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gp_proc_return_write
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|write_channel
argument_list|,
operator|&
name|proc_return
argument_list|,
name|plug_in
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_temp_proc_run (GimpPlugIn * plug_in,GPProcRun * proc_run)
name|gimp_plug_in_temp_proc_run
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GPProcRun
modifier|*
name|proc_run
parameter_list|)
block|{
name|GPProcReturn
name|proc_return
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|procedure
operator|=
name|gimp_plug_in_get_temp_procedure
argument_list|(
name|plug_in
argument_list|,
name|proc_run
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
condition|)
block|{
name|gimp_plug_in_proc_run_internal
argument_list|(
name|proc_run
argument_list|,
name|procedure
argument_list|,
operator|&
name|proc_return
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gp_temp_proc_return_write
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|write_channel
argument_list|,
operator|&
name|proc_return
argument_list|,
name|plug_in
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_proc_run_internal (GPProcRun * proc_run,GimpProcedure * procedure,GPProcReturn * proc_return)
name|gimp_plug_in_proc_run_internal
parameter_list|(
name|GPProcRun
modifier|*
name|proc_run
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GPProcReturn
modifier|*
name|proc_return
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|arguments
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_values
init|=
name|NULL
decl_stmt|;
name|arguments
operator|=
name|_gimp_gp_params_to_value_array
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|proc_run
operator|->
name|params
argument_list|,
name|proc_run
operator|->
name|nparams
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|return_values
operator|=
name|gimp_procedure_run
argument_list|(
name|procedure
argument_list|,
name|arguments
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|arguments
argument_list|)
expr_stmt|;
name|proc_return
operator|->
name|name
operator|=
name|proc_run
operator|->
name|name
expr_stmt|;
name|proc_return
operator|->
name|nparams
operator|=
name|gimp_value_array_length
argument_list|(
name|return_values
argument_list|)
expr_stmt|;
name|proc_return
operator|->
name|params
operator|=
name|_gimp_value_array_to_gp_params
argument_list|(
name|return_values
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_values
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_plug_in_io_error_handler (GIOChannel * channel,GIOCondition cond,gpointer data)
name|gimp_plug_in_io_error_handler
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GIOCondition
name|cond
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_printerr
argument_list|(
literal|"%s: fatal error: GIMP crashed\n"
argument_list|,
name|gimp_get_progname
argument_list|()
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
comment|/* never reached */
return|return
name|TRUE
return|;
block|}
end_function

end_unit

