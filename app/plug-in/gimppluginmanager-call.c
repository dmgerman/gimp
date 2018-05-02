begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginmanager-call.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppdbcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-message.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugindef.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginerror.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_define
DECL|macro|__YES_I_NEED_GIMP_PLUG_IN_MANAGER_CALL__
define|#
directive|define
name|__YES_I_NEED_GIMP_PLUG_IN_MANAGER_CALL__
end_define

begin_include
include|#
directive|include
file|"gimppluginmanager-call.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginshm.h"
end_include

begin_include
include|#
directive|include
file|"gimptemporaryprocedure.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-params.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
specifier|static
name|void
DECL|function|gimp_allow_set_foreground_window (GimpPlugIn * plug_in)
name|gimp_allow_set_foreground_window
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|AllowSetForegroundWindow
argument_list|(
name|GetProcessId
argument_list|(
name|plug_in
operator|->
name|pid
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_plug_in_manager_call_query (GimpPlugInManager * manager,GimpContext * context,GimpPlugInDef * plug_in_def)
name|gimp_plug_in_manager_call_query
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PDB_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_DEF
argument_list|(
name|plug_in_def
argument_list|)
argument_list|)
expr_stmt|;
name|plug_in
operator|=
name|gimp_plug_in_new
argument_list|(
name|manager
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|plug_in_def
operator|->
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
name|plug_in
operator|->
name|plug_in_def
operator|=
name|plug_in_def
expr_stmt|;
if|if
condition|(
name|gimp_plug_in_open
argument_list|(
name|plug_in
argument_list|,
name|GIMP_PLUG_IN_CALL_QUERY
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
while|while
condition|(
name|plug_in
operator|->
name|open
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
name|my_read
argument_list|,
operator|&
name|msg
argument_list|,
name|plug_in
argument_list|)
condition|)
block|{
name|gimp_plug_in_close
argument_list|(
name|plug_in
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_plug_in_handle_message
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
block|}
block|}
name|g_object_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_call_init (GimpPlugInManager * manager,GimpContext * context,GimpPlugInDef * plug_in_def)
name|gimp_plug_in_manager_call_init
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PDB_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_DEF
argument_list|(
name|plug_in_def
argument_list|)
argument_list|)
expr_stmt|;
name|plug_in
operator|=
name|gimp_plug_in_new
argument_list|(
name|manager
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|plug_in_def
operator|->
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
name|plug_in
operator|->
name|plug_in_def
operator|=
name|plug_in_def
expr_stmt|;
if|if
condition|(
name|gimp_plug_in_open
argument_list|(
name|plug_in
argument_list|,
name|GIMP_PLUG_IN_CALL_INIT
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
while|while
condition|(
name|plug_in
operator|->
name|open
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
name|my_read
argument_list|,
operator|&
name|msg
argument_list|,
name|plug_in
argument_list|)
condition|)
block|{
name|gimp_plug_in_close
argument_list|(
name|plug_in
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_plug_in_handle_message
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
block|}
block|}
name|g_object_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_plug_in_manager_call_run (GimpPlugInManager * manager,GimpContext * context,GimpProgress * progress,GimpPlugInProcedure * procedure,GimpValueArray * args,gboolean synchronous,GimpObject * display)
name|gimp_plug_in_manager_call_run
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gboolean
name|synchronous
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|GimpPlugIn
modifier|*
name|plug_in
decl_stmt|;
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
name|GIMP_IS_PDB_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|args
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|display
operator|==
name|NULL
operator|||
name|GIMP_IS_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|plug_in
operator|=
name|gimp_plug_in_new
argument_list|(
name|manager
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|procedure
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
name|GimpCoreConfig
modifier|*
name|core_config
init|=
name|manager
operator|->
name|gimp
operator|->
name|config
decl_stmt|;
name|GimpGeglConfig
modifier|*
name|gegl_config
init|=
name|GIMP_GEGL_CONFIG
argument_list|(
name|core_config
argument_list|)
decl_stmt|;
name|GimpDisplayConfig
modifier|*
name|display_config
init|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|core_config
argument_list|)
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|gui_config
init|=
name|GIMP_GUI_CONFIG
argument_list|(
name|core_config
argument_list|)
decl_stmt|;
name|GPConfig
name|config
decl_stmt|;
name|GPProcRun
name|proc_run
decl_stmt|;
name|gint
name|display_ID
decl_stmt|;
name|GObject
modifier|*
name|monitor
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_plug_in_open
argument_list|(
name|plug_in
argument_list|,
name|GIMP_PLUG_IN_CALL_RUN
argument_list|,
name|FALSE
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|g_error_new
argument_list|(
name|GIMP_PLUG_IN_ERROR
argument_list|,
name|GIMP_PLUG_IN_EXECUTION_FAILED
argument_list|,
name|_
argument_list|(
literal|"Failed to run plug-in \"%s\""
argument_list|)
argument_list|,
name|name
argument_list|)
decl_stmt|;
name|g_object_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
name|display_ID
operator|=
name|display
condition|?
name|gimp_get_display_ID
argument_list|(
name|manager
operator|->
name|gimp
argument_list|,
name|display
argument_list|)
else|:
operator|-
literal|1
expr_stmt|;
name|config
operator|.
name|version
operator|=
name|GIMP_PROTOCOL_VERSION
expr_stmt|;
name|config
operator|.
name|tile_width
operator|=
name|GIMP_PLUG_IN_TILE_WIDTH
expr_stmt|;
name|config
operator|.
name|tile_height
operator|=
name|GIMP_PLUG_IN_TILE_HEIGHT
expr_stmt|;
name|config
operator|.
name|shm_ID
operator|=
operator|(
name|manager
operator|->
name|shm
condition|?
name|gimp_plug_in_shm_get_ID
argument_list|(
name|manager
operator|->
name|shm
argument_list|)
else|:
operator|-
literal|1
operator|)
expr_stmt|;
name|config
operator|.
name|check_size
operator|=
name|display_config
operator|->
name|transparency_size
expr_stmt|;
name|config
operator|.
name|check_type
operator|=
name|display_config
operator|->
name|transparency_type
expr_stmt|;
name|config
operator|.
name|show_help_button
operator|=
operator|(
name|gui_config
operator|->
name|use_help
operator|&&
name|gui_config
operator|->
name|show_help_button
operator|)
expr_stmt|;
name|config
operator|.
name|use_cpu_accel
operator|=
name|manager
operator|->
name|gimp
operator|->
name|use_cpu_accel
expr_stmt|;
name|config
operator|.
name|use_opencl
operator|=
name|gegl_config
operator|->
name|use_opencl
expr_stmt|;
name|config
operator|.
name|export_exif
operator|=
name|core_config
operator|->
name|export_metadata_exif
expr_stmt|;
name|config
operator|.
name|export_xmp
operator|=
name|core_config
operator|->
name|export_metadata_xmp
expr_stmt|;
name|config
operator|.
name|export_iptc
operator|=
name|core_config
operator|->
name|export_metadata_iptc
expr_stmt|;
name|config
operator|.
name|install_cmap
operator|=
name|FALSE
expr_stmt|;
name|config
operator|.
name|show_tooltips
operator|=
name|gui_config
operator|->
name|show_tooltips
expr_stmt|;
name|config
operator|.
name|min_colors
operator|=
literal|144
expr_stmt|;
name|config
operator|.
name|gdisp_ID
operator|=
name|display_ID
expr_stmt|;
name|config
operator|.
name|app_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_get_application_name
argument_list|()
expr_stmt|;
name|config
operator|.
name|wm_class
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_get_program_class
argument_list|(
name|manager
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|config
operator|.
name|display_name
operator|=
name|gimp_get_display_name
argument_list|(
name|manager
operator|->
name|gimp
argument_list|,
name|display_ID
argument_list|,
operator|&
name|monitor
argument_list|,
operator|&
name|config
operator|.
name|monitor_number
argument_list|)
expr_stmt|;
name|config
operator|.
name|timestamp
operator|=
name|gimp_get_user_time
argument_list|(
name|manager
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|proc_run
operator|.
name|name
operator|=
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
operator|->
name|original_name
expr_stmt|;
name|proc_run
operator|.
name|nparams
operator|=
name|gimp_value_array_length
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|proc_run
operator|.
name|params
operator|=
name|plug_in_args_to_params
argument_list|(
name|args
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gp_config_write
argument_list|(
name|plug_in
operator|->
name|my_write
argument_list|,
operator|&
name|config
argument_list|,
name|plug_in
argument_list|)
operator|||
operator|!
name|gp_proc_run_write
argument_list|(
name|plug_in
operator|->
name|my_write
argument_list|,
operator|&
name|proc_run
argument_list|,
name|plug_in
argument_list|)
operator|||
operator|!
name|gimp_wire_flush
argument_list|(
name|plug_in
operator|->
name|my_write
argument_list|,
name|plug_in
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|g_error_new
argument_list|(
name|GIMP_PLUG_IN_ERROR
argument_list|,
name|GIMP_PLUG_IN_EXECUTION_FAILED
argument_list|,
name|_
argument_list|(
literal|"Failed to run plug-in \"%s\""
argument_list|)
argument_list|,
name|name
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|config
operator|.
name|display_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_run
operator|.
name|params
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
name|g_free
argument_list|(
name|config
operator|.
name|display_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_run
operator|.
name|params
argument_list|)
expr_stmt|;
comment|/* If this is an extension,        * wait for an installation-confirmation message        */
if|if
condition|(
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
operator|->
name|proc_type
operator|==
name|GIMP_EXTENSION
condition|)
block|{
name|plug_in
operator|->
name|ext_main_loop
operator|=
name|g_main_loop_new
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|plug_in
operator|->
name|ext_main_loop
argument_list|)
expr_stmt|;
comment|/*  main_loop is quit in gimp_plug_in_handle_extension_ack()  */
name|g_clear_pointer
argument_list|(
operator|&
name|plug_in
operator|->
name|ext_main_loop
argument_list|,
name|g_main_loop_unref
argument_list|)
expr_stmt|;
block|}
comment|/* If this plug-in is requested to run synchronously,        * wait for its return values        */
if|if
condition|(
name|synchronous
condition|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
init|=
operator|&
name|plug_in
operator|->
name|main_proc_frame
decl_stmt|;
name|proc_frame
operator|->
name|main_loop
operator|=
name|g_main_loop_new
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|proc_frame
operator|->
name|main_loop
argument_list|)
expr_stmt|;
comment|/*  main_loop is quit in gimp_plug_in_handle_proc_return()  */
name|g_clear_pointer
argument_list|(
operator|&
name|proc_frame
operator|->
name|main_loop
argument_list|,
name|g_main_loop_unref
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_plug_in_proc_frame_get_return_values
argument_list|(
name|proc_frame
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_plug_in_manager_call_run_temp (GimpPlugInManager * manager,GimpContext * context,GimpProgress * progress,GimpTemporaryProcedure * procedure,GimpValueArray * args)
name|gimp_plug_in_manager_call_run_temp
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpTemporaryProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|GimpPlugIn
modifier|*
name|plug_in
decl_stmt|;
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
name|GIMP_IS_PDB_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPORARY_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|args
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|plug_in
operator|=
name|procedure
operator|->
name|plug_in
expr_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|GPProcRun
name|proc_run
decl_stmt|;
name|proc_frame
operator|=
name|gimp_plug_in_proc_frame_push
argument_list|(
name|plug_in
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|proc_run
operator|.
name|name
operator|=
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
operator|->
name|original_name
expr_stmt|;
name|proc_run
operator|.
name|nparams
operator|=
name|gimp_value_array_length
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|proc_run
operator|.
name|params
operator|=
name|plug_in_args_to_params
argument_list|(
name|args
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gp_temp_proc_run_write
argument_list|(
name|plug_in
operator|->
name|my_write
argument_list|,
operator|&
name|proc_run
argument_list|,
name|plug_in
argument_list|)
operator|||
operator|!
name|gimp_wire_flush
argument_list|(
name|plug_in
operator|->
name|my_write
argument_list|,
name|plug_in
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gimp_object_get_name
argument_list|(
name|plug_in
argument_list|)
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|g_error_new
argument_list|(
name|GIMP_PLUG_IN_ERROR
argument_list|,
name|GIMP_PLUG_IN_EXECUTION_FAILED
argument_list|,
name|_
argument_list|(
literal|"Failed to run plug-in \"%s\""
argument_list|)
argument_list|,
name|name
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|proc_run
operator|.
name|params
argument_list|)
expr_stmt|;
name|gimp_plug_in_proc_frame_pop
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
name|gimp_allow_set_foreground_window
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_run
operator|.
name|params
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|gimp_plug_in_proc_frame_ref
argument_list|(
name|proc_frame
argument_list|)
expr_stmt|;
name|gimp_plug_in_main_loop
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
comment|/*  main_loop is quit and proc_frame is popped in        *  gimp_plug_in_handle_temp_proc_return()        */
name|return_vals
operator|=
name|gimp_plug_in_proc_frame_get_return_values
argument_list|(
name|proc_frame
argument_list|)
expr_stmt|;
name|gimp_plug_in_proc_frame_unref
argument_list|(
name|proc_frame
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

end_unit

