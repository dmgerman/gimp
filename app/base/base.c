begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_DIRENT_H
end_ifdef

begin_include
include|#
directive|include
file|<dirent.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|<glib.h>
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
comment|/* For _getpid() */
end_comment

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_comment
comment|/* for _unlink() */
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
file|"base.h"
end_include

begin_include
include|#
directive|include
file|"base-config.h"
end_include

begin_include
include|#
directive|include
file|"detect-mmx.h"
end_include

begin_include
include|#
directive|include
file|"temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"tile-swap.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_function_decl
specifier|static
name|void
name|toast_old_temp_files
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|base_init (void)
name|base_init
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
ifdef|#
directive|ifdef
name|HAVE_ASM_MMX
name|use_mmx
operator|=
operator|(
name|intel_cpu_features
argument_list|()
operator|&
operator|(
literal|1
operator|<<
literal|23
operator|)
operator|)
condition|?
literal|1
else|:
literal|0
expr_stmt|;
name|g_print
argument_list|(
literal|"using MMX: %s\n"
argument_list|,
name|use_mmx
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|toast_old_temp_files
argument_list|()
expr_stmt|;
comment|/* Add the swap file  */
if|if
condition|(
name|base_config
operator|->
name|swap_path
operator|==
name|NULL
condition|)
name|base_config
operator|->
name|swap_path
operator|=
name|g_strdup
argument_list|(
name|g_get_tmp_dir
argument_list|()
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s"
name|G_DIR_SEPARATOR_S
literal|"gimpswap.%lu"
argument_list|,
name|base_config
operator|->
name|swap_path
argument_list|,
operator|(
name|unsigned
name|long
operator|)
name|getpid
argument_list|()
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
name|paint_funcs_setup
argument_list|()
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
name|swapping_free
argument_list|()
expr_stmt|;
name|paint_funcs_free
argument_list|()
expr_stmt|;
name|tile_swap_exit
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|toast_old_temp_files (void)
name|toast_old_temp_files
parameter_list|(
name|void
parameter_list|)
block|{
name|DIR
modifier|*
name|dir
decl_stmt|;
name|struct
name|dirent
modifier|*
name|entry
decl_stmt|;
name|GString
modifier|*
name|filename
init|=
name|g_string_new
argument_list|(
literal|""
argument_list|)
decl_stmt|;
name|dir
operator|=
name|opendir
argument_list|(
name|base_config
operator|->
name|swap_path
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
return|return;
while|while
condition|(
operator|(
name|entry
operator|=
name|readdir
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
operator|->
name|d_name
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
operator|->
name|d_name
operator|+
literal|9
argument_list|)
decl_stmt|;
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
comment|/*  On Windows, you can't remove open files anyhow, 	     *  so no harm trying. 	     */
name|g_string_printf
argument_list|(
name|filename
argument_list|,
literal|"%s"
name|G_DIR_SEPARATOR_S
literal|"%s"
argument_list|,
name|base_config
operator|->
name|swap_path
argument_list|,
name|entry
operator|->
name|d_name
argument_list|)
expr_stmt|;
name|unlink
argument_list|(
name|filename
operator|->
name|str
argument_list|)
expr_stmt|;
block|}
block|}
name|closedir
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|filename
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

