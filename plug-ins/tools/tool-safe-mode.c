begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  *  * tool-safe-mode -- support plug-in for dynamically loaded tool modules  * Copyright (C) 2000 Nathan Summers  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* EEEEEEEK! */
end_comment

begin_typedef
DECL|typedef|GimpToolInfo
typedef|typedef
name|struct
name|_GimpToolInfo
name|GimpToolInfo
typedef|;
end_typedef

begin_include
include|#
directive|include
file|"libgimptool/gimptoolmodule.h"
end_include

begin_comment
comment|/* Declare local functions */
end_comment

begin_function_decl
specifier|static
name|void
name|safe_mode_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|safe_mode_init
block|,
comment|/* init_proc */
name|NULL
block|,
comment|/* query_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|NULL
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
name|safe_mode_register_tool
parameter_list|()
block|{ }
end_function

begin_comment
comment|/* much code borrowed from gimp_datafiles_read_directories --  * why isn't that function available in libgimp? It would be  * better than the ad-hoc stuff in gimpressionist, gflare, etc.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|safe_mode_init (void)
name|safe_mode_init
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|tool_plug_in_path
decl_stmt|,
modifier|*
name|free_me
decl_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
name|g_message
argument_list|(
literal|"tool-safe-mode init called"
argument_list|)
expr_stmt|;
name|free_me
operator|=
name|tool_plug_in_path
operator|=
name|gimp_gimprc_query
argument_list|(
literal|"tool-plug-in-path"
argument_list|)
expr_stmt|;
comment|/* FIXME: why does it return the string with quotes around it?    * gflare-path does not    */
name|tool_plug_in_path
operator|++
expr_stmt|;
name|tool_plug_in_path
index|[
name|strlen
argument_list|(
name|tool_plug_in_path
argument_list|)
operator|-
literal|1
index|]
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|g_module_supported
argument_list|()
operator|&&
name|tool_plug_in_path
condition|)
block|{
name|GList
modifier|*
name|path
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|err
decl_stmt|;
name|GDir
modifier|*
name|dir
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|dir_ent
decl_stmt|;
name|struct
name|stat
name|filestat
decl_stmt|;
ifdef|#
directive|ifdef
name|__EMX__
comment|/*    *  Change drive so opendir works.    */
if|if
condition|(
name|tool_plug_in_path
index|[
literal|1
index|]
operator|==
literal|':'
condition|)
block|{
name|_chdrive
argument_list|(
name|tool_plug_in_path
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|g_message
argument_list|(
literal|"%s"
argument_list|,
name|tool_plug_in_path
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_path_parse
argument_list|(
name|tool_plug_in_path
argument_list|,
literal|16
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"%p"
argument_list|,
name|path
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|path
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
name|g_message
argument_list|(
literal|"reading directory %s"
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
comment|/* Open directory */
name|dir
operator|=
name|g_dir_open
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
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
name|g_message
argument_list|(
literal|"error reading datafiles directory \"%s\""
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
while|while
condition|(
operator|(
name|dir_ent
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
operator|)
condition|)
block|{
name|filename
operator|=
name|g_build_filename
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|,
name|dir_ent
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Check the file and see that it is not a sub-directory */
name|err
operator|=
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|filestat
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|err
operator|&&
operator|!
name|S_ISDIR
argument_list|(
name|filestat
operator|.
name|st_mode
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"loading tool %s\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_tool_module_new
argument_list|(
name|filename
argument_list|,
name|safe_mode_register_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|free_me
argument_list|)
expr_stmt|;
block|}
name|g_message
argument_list|(
literal|"tool-safe-mode init done"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

