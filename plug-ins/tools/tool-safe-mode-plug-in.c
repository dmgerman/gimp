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
file|"tool-safe-mode.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

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
decl_stmt|;
name|gchar
modifier|*
name|freeme
decl_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
name|freeme
operator|=
name|tool_plug_in_path
operator|=
name|gimp_gimprc_query
argument_list|(
literal|"tool-plug-in-path"
argument_list|)
expr_stmt|;
comment|/* FIXME: why does it return the string with quotes around it?    * gflare-path does not    *    * It's a bug that will be fixed with the death of app/gimprc.c    * --mitch    */
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
name|tool_safe_mode_init
argument_list|(
name|tool_plug_in_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|freeme
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|safe_mode_init
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* query_proc */
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
name|MAIN
argument_list|()
end_macro

end_unit

