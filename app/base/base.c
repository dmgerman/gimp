begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<process.h>
end_include

begin_comment
comment|/*  for _getpid()  */
end_comment

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_comment
comment|/*  for _unlink()  */
end_comment

begin_endif
endif|#
directive|endif
end_endif

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
file|"config/gimpconfig-path.h"
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
file|"temp-buf.h"
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

begin_decl_stmt
DECL|variable|base_config
name|GimpBaseConfig
modifier|*
name|base_config
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|base_toast_old_temp_files
parameter_list|(
name|GimpBaseConfig
modifier|*
name|config
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|base_init (GimpBaseConfig * config,gboolean use_cpu_accel)
name|base_init
parameter_list|(
name|GimpBaseConfig
modifier|*
name|config
parameter_list|,
name|gboolean
name|use_cpu_accel
parameter_list|)
block|{
name|gchar
modifier|*
name|swapfile
decl_stmt|;
name|gchar
modifier|*
name|swapdir
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BASE_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|base_config
operator|==
name|NULL
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
name|base_toast_old_temp_files
argument_list|(
name|config
argument_list|)
expr_stmt|;
comment|/* Add the swap file */
if|if
condition|(
operator|!
name|config
operator|->
name|swap_path
condition|)
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"swap_path"
argument_list|,
literal|"${gimp_dir}"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|swapdir
operator|=
name|gimp_config_path_expand
argument_list|(
name|config
operator|->
name|swap_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|swapfile
operator|=
name|g_strdup_printf
argument_list|(
literal|"gimpswap.%lu"
argument_list|,
operator|(
name|unsigned
name|long
operator|)
name|getpid
argument_list|()
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_build_filename
argument_list|(
name|swapdir
argument_list|,
name|swapfile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|swapfile
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|swapdir
argument_list|)
expr_stmt|;
name|tile_swap_add
argument_list|(
name|path
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
comment|/*  FIXME: pass use_cpu_accel to GimpComposite  */
name|gimp_composite_init
argument_list|(
name|use_cpu_accel
argument_list|)
expr_stmt|;
name|paint_funcs_setup
argument_list|(
name|use_cpu_accel
argument_list|)
expr_stmt|;
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
name|swapping_free
argument_list|()
expr_stmt|;
name|paint_funcs_free
argument_list|()
expr_stmt|;
name|tile_swap_exit
argument_list|()
expr_stmt|;
name|tile_cache_exit
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
DECL|function|base_toast_old_temp_files (GimpBaseConfig * config)
name|base_toast_old_temp_files
parameter_list|(
name|GimpBaseConfig
modifier|*
name|config
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
name|config
operator|->
name|swap_path
condition|)
return|return;
name|dirname
operator|=
name|gimp_config_path_expand
argument_list|(
name|config
operator|->
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
operator|!
name|strncmp
argument_list|(
name|entry
argument_list|,
literal|"gimpswap."
argument_list|,
literal|9
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
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
name|entry
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|unlink
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

end_unit

