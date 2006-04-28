begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-in-run.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"base/tile.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimptemporaryprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_define
DECL|macro|__YES_I_NEED_GIMP_PLUG_IN_MANAGER_RUN__
define|#
directive|define
name|__YES_I_NEED_GIMP_PLUG_IN_MANAGER_RUN__
end_define

begin_include
include|#
directive|include
file|"gimppluginmanager-run.h"
end_include

begin_include
include|#
directive|include
file|"plug-in.h"
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GValueArray
modifier|*
DECL|function|gimp_plug_in_manager_run (GimpPlugInManager * manager,GimpContext * context,GimpProgress * progress,GimpPlugInProcedure * procedure,GValueArray * args,gboolean synchronous,gboolean destroy_return_vals,gint display_ID)
name|gimp_plug_in_manager_run
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
name|GValueArray
modifier|*
name|args
parameter_list|,
name|gboolean
name|synchronous
parameter_list|,
name|gboolean
name|destroy_return_vals
parameter_list|,
name|gint
name|display_ID
parameter_list|)
block|{
name|GValueArray
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|PlugIn
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
name|GIMP_IS_CONTEXT
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
name|plug_in
operator|=
name|plug_in_new
argument_list|(
name|manager
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|procedure
operator|->
name|prog
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
name|monitor
decl_stmt|;
if|if
condition|(
operator|!
name|plug_in_open
argument_list|(
name|plug_in
argument_list|)
condition|)
block|{
name|plug_in_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
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
name|TILE_WIDTH
expr_stmt|;
name|config
operator|.
name|tile_height
operator|=
name|TILE_HEIGHT
expr_stmt|;
name|config
operator|.
name|shm_ID
operator|=
name|gimp_plug_in_manager_get_shm_ID
argument_list|(
name|manager
argument_list|)
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
name|gimp_reserved_4
operator|=
literal|0
expr_stmt|;
name|config
operator|.
name|gimp_reserved_5
operator|=
literal|0
expr_stmt|;
name|config
operator|.
name|gimp_reserved_6
operator|=
literal|0
expr_stmt|;
name|config
operator|.
name|gimp_reserved_7
operator|=
literal|0
expr_stmt|;
name|config
operator|.
name|gimp_reserved_8
operator|=
literal|0
expr_stmt|;
name|config
operator|.
name|install_cmap
operator|=
name|core_config
operator|->
name|install_cmap
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
name|CLAMP
argument_list|(
name|core_config
operator|->
name|min_colors
argument_list|,
literal|27
argument_list|,
literal|256
argument_list|)
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
argument_list|)
expr_stmt|;
name|config
operator|.
name|monitor_number
operator|=
name|monitor
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
name|args
operator|->
name|n_values
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
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
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
name|plug_in_ref
argument_list|(
name|plug_in
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
name|gimp_threads_leave
argument_list|(
name|manager
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|plug_in
operator|->
name|ext_main_loop
argument_list|)
expr_stmt|;
name|gimp_threads_enter
argument_list|(
name|manager
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/*  main_loop is quit in plug_in_handle_extension_ack()  */
name|g_main_loop_unref
argument_list|(
name|plug_in
operator|->
name|ext_main_loop
argument_list|)
expr_stmt|;
name|plug_in
operator|->
name|ext_main_loop
operator|=
name|NULL
expr_stmt|;
block|}
comment|/* If this plug-in is requested to run synchronously,        * wait for its return values        */
if|if
condition|(
name|synchronous
condition|)
block|{
name|PlugInProcFrame
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
name|gimp_threads_leave
argument_list|(
name|manager
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|proc_frame
operator|->
name|main_loop
argument_list|)
expr_stmt|;
name|gimp_threads_enter
argument_list|(
name|manager
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/*  main_loop is quit in plug_in_handle_proc_return()  */
name|g_main_loop_unref
argument_list|(
name|proc_frame
operator|->
name|main_loop
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|main_loop
operator|=
name|NULL
expr_stmt|;
name|return_vals
operator|=
name|plug_in_proc_frame_get_return_vals
argument_list|(
name|proc_frame
argument_list|)
expr_stmt|;
block|}
name|plug_in_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
name|done
label|:
if|if
condition|(
name|return_vals
operator|&&
name|destroy_return_vals
condition|)
block|{
name|g_value_array_free
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|NULL
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|GValueArray
modifier|*
DECL|function|gimp_plug_in_manager_run_temp (GimpPlugInManager * manager,GimpContext * context,GimpProgress * progress,GimpTemporaryProcedure * procedure,GValueArray * args)
name|gimp_plug_in_manager_run_temp
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
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|GValueArray
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|PlugIn
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
name|GIMP_IS_CONTEXT
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
name|PlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|GPProcRun
name|proc_run
decl_stmt|;
name|proc_frame
operator|=
name|plug_in_proc_frame_push
argument_list|(
name|plug_in
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
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
name|args
operator|->
name|n_values
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
name|g_free
argument_list|(
name|proc_run
operator|.
name|params
argument_list|)
expr_stmt|;
name|plug_in_proc_frame_pop
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
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
name|g_free
argument_list|(
name|proc_run
operator|.
name|params
argument_list|)
expr_stmt|;
name|plug_in_ref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|plug_in_proc_frame_ref
argument_list|(
name|proc_frame
argument_list|)
expr_stmt|;
name|plug_in_main_loop
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
comment|/*  main_loop is quit and proc_frame is popped in        *  plug_in_handle_temp_proc_return()        */
name|return_vals
operator|=
name|plug_in_proc_frame_get_return_vals
argument_list|(
name|proc_frame
argument_list|)
expr_stmt|;
name|plug_in_proc_frame_unref
argument_list|(
name|proc_frame
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
name|plug_in_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
name|done
label|:
return|return
name|return_vals
return|;
block|}
end_function

end_unit

