begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|"libgimpbase/gimpwin32-io.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpbaseconfig.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"composite/gimp-composite.h"
end_include

begin_include
include|#
directive|include
file|"base.h"
end_include

begin_include
include|#
directive|include
file|"pixel-processor.h"
end_include

begin_include
include|#
directive|include
file|"tile-cache.h"
end_include

begin_include
include|#
directive|include
file|"tile-swap.h"
end_include

begin_function_decl
specifier|static
name|void
name|base_toast_old_swap_files
parameter_list|(
specifier|const
name|gchar
modifier|*
name|swap_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|base_tile_cache_size_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|base_num_processors_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|base_config
specifier|static
name|GimpBaseConfig
modifier|*
name|base_config
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|base_init (GimpBaseConfig * config,gboolean be_verbose,gboolean use_cpu_accel)
name|base_init
parameter_list|(
name|GimpBaseConfig
modifier|*
name|config
parameter_list|,
name|gboolean
name|be_verbose
parameter_list|,
name|gboolean
name|use_cpu_accel
parameter_list|)
block|{
name|gboolean
name|swap_is_ok
decl_stmt|;
name|gchar
modifier|*
name|temp_dir
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BASE_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|base_config
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|base_config
operator|=
name|g_object_ref
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|tile_cache_init
argument_list|(
name|config
operator|->
name|tile_cache_size
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify::tile-cache-size"
argument_list|,
name|G_CALLBACK
argument_list|(
name|base_tile_cache_size_notify
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|config
operator|->
name|swap_path
operator|||
operator|!
operator|*
name|config
operator|->
name|swap_path
condition|)
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"swap-path"
argument_list|)
expr_stmt|;
name|base_toast_old_swap_files
argument_list|(
name|config
operator|->
name|swap_path
argument_list|)
expr_stmt|;
name|tile_swap_init
argument_list|(
name|config
operator|->
name|swap_path
argument_list|)
expr_stmt|;
name|swap_is_ok
operator|=
name|tile_swap_test
argument_list|()
expr_stmt|;
comment|/*  create the temp directory if it doesn't exist  */
if|if
condition|(
operator|!
name|config
operator|->
name|temp_path
operator|||
operator|!
operator|*
name|config
operator|->
name|temp_path
condition|)
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"temp-path"
argument_list|)
expr_stmt|;
name|temp_dir
operator|=
name|gimp_config_path_expand
argument_list|(
name|config
operator|->
name|temp_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_file_test
argument_list|(
name|temp_dir
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
name|g_mkdir_with_parents
argument_list|(
name|temp_dir
argument_list|,
name|S_IRUSR
operator||
name|S_IXUSR
operator||
name|S_IWUSR
operator||
name|S_IRGRP
operator||
name|S_IXGRP
operator||
name|S_IROTH
operator||
name|S_IXOTH
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp_dir
argument_list|)
expr_stmt|;
name|pixel_processor_init
argument_list|(
name|config
operator|->
name|num_processors
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify::num-processors"
argument_list|,
name|G_CALLBACK
argument_list|(
name|base_num_processors_notify
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_composite_init
argument_list|(
name|be_verbose
argument_list|,
name|use_cpu_accel
argument_list|)
expr_stmt|;
name|paint_funcs_setup
argument_list|()
expr_stmt|;
return|return
name|swap_is_ok
return|;
block|}
end_function

begin_function
name|void
DECL|function|base_exit (void)
name|base_exit
parameter_list|(
name|void
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|base_config
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|pixel_processor_exit
argument_list|()
expr_stmt|;
name|paint_funcs_free
argument_list|()
expr_stmt|;
name|tile_cache_exit
argument_list|()
expr_stmt|;
name|tile_swap_exit
argument_list|()
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|base_config
argument_list|,
name|base_tile_cache_size_notify
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|base_config
argument_list|)
expr_stmt|;
name|base_config
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|base_toast_old_swap_files (const gchar * swap_path)
name|base_toast_old_swap_files
parameter_list|(
specifier|const
name|gchar
modifier|*
name|swap_path
parameter_list|)
block|{
name|GDir
modifier|*
name|dir
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|dirname
decl_stmt|;
specifier|const
name|char
modifier|*
name|entry
decl_stmt|;
if|if
condition|(
operator|!
name|swap_path
condition|)
return|return;
name|dirname
operator|=
name|gimp_config_path_expand
argument_list|(
name|swap_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dirname
condition|)
return|return;
name|dir
operator|=
name|g_dir_open
argument_list|(
name|dirname
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
block|{
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
return|return;
block|}
while|while
condition|(
operator|(
name|entry
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|entry
argument_list|,
literal|"gimpswap."
argument_list|)
condition|)
block|{
comment|/* don't try to kill swap files of running processes          * yes, I know they might not all be gimp processes, and when you          * unlink, it's refcounted, but lets not confuse the user by          * "where did my disk space go?" cause the filename is gone          * if the kill succeeds, and there running process isn't gimp          * we'll probably get it the next time around          */
name|gint
name|pid
init|=
name|atoi
argument_list|(
name|entry
operator|+
literal|9
argument_list|)
decl_stmt|;
comment|/*  On Windows, you can't remove open files anyhow,          *  so no harm trying.          */
ifndef|#
directive|ifndef
name|G_OS_WIN32
if|if
condition|(
name|kill
argument_list|(
name|pid
argument_list|,
literal|0
argument_list|)
condition|)
endif|#
directive|endif
block|{
name|gchar
modifier|*
name|filename
init|=
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
name|entry
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_unlink
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|base_tile_cache_size_notify (GObject * config,GParamSpec * param_spec,gpointer data)
name|base_tile_cache_size_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|tile_cache_set_size
argument_list|(
name|GIMP_BASE_CONFIG
argument_list|(
name|config
argument_list|)
operator|->
name|tile_cache_size
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|base_num_processors_notify (GObject * config,GParamSpec * param_spec,gpointer data)
name|base_num_processors_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|pixel_processor_set_num_threads
argument_list|(
name|GIMP_BASE_CONFIG
argument_list|(
name|config
argument_list|)
operator|->
name|num_processors
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

