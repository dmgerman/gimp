begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* Session-managment stuff   Copyright (C) 1998 Sven Neumann<sven@gimp.org>     I include a short description here on what is done and what problems     are left:     Since everything saved in sessionrc changes often (with each session?)     the whole file is rewritten each time the gimp exits. I don't see any    use in implementing a more flexible scheme like it is used for gimprc.     Right now session-managment is limited to window geometry. Restoring     openend images is planned, but I'm still not sure how to deal with dirty    images.     Dialogs are now reopened if the gimp is called with the command-line-option    --restore-session or if the related entry is set in gimprc.    Probably there should alternatively be a list of dialogs in the preferences     that should always be opened on start-up.      Please point me into the right direction to make this work with Gnome-SM.  */
end_comment

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
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"commands.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|sessionrc_write_info
parameter_list|(
name|SessionInfo
modifier|*
parameter_list|,
name|FILE
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|session_open_dialog
parameter_list|(
name|SessionInfo
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|session_reset_open_state
parameter_list|(
name|SessionInfo
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|session_info_updates
name|GList
modifier|*
name|session_info_updates
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* global session variables */
end_comment

begin_decl_stmt
DECL|variable|toolbox_session_info
name|SessionInfo
name|toolbox_session_info
init|=
block|{
literal|"toolbox"
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|lc_dialog_session_info
name|SessionInfo
name|lc_dialog_session_info
init|=
block|{
literal|"lc-dialog"
block|,
operator|(
name|GtkItemFactoryCallback
operator|)
name|dialogs_lc_cmd_callback
block|,
literal|0
block|,
literal|400
block|,
literal|0
block|,
literal|0
block|,
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|info_dialog_session_info
name|SessionInfo
name|info_dialog_session_info
init|=
block|{
literal|"info-dialog"
block|,
name|NULL
block|,
literal|165
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tool_options_session_info
name|SessionInfo
name|tool_options_session_info
init|=
block|{
literal|"tool-options"
block|,
operator|(
name|GtkItemFactoryCallback
operator|)
name|dialogs_tools_options_cmd_callback
block|,
literal|0
block|,
literal|345
block|,
literal|0
block|,
literal|0
block|,
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_session_info
name|SessionInfo
name|palette_session_info
init|=
block|{
literal|"palette"
block|,
operator|(
name|GtkItemFactoryCallback
operator|)
name|dialogs_palette_cmd_callback
block|,
literal|140
block|,
literal|180
block|,
literal|0
block|,
literal|0
block|,
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brush_select_session_info
name|SessionInfo
name|brush_select_session_info
init|=
block|{
literal|"brush-select"
block|,
operator|(
name|GtkItemFactoryCallback
operator|)
name|dialogs_brushes_cmd_callback
block|,
literal|150
block|,
literal|180
block|,
literal|0
block|,
literal|0
block|,
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pattern_select_session_info
name|SessionInfo
name|pattern_select_session_info
init|=
block|{
literal|"pattern-select"
block|,
operator|(
name|GtkItemFactoryCallback
operator|)
name|dialogs_patterns_cmd_callback
block|,
literal|160
block|,
literal|180
block|,
literal|0
block|,
literal|0
block|,
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradient_select_session_info
name|SessionInfo
name|gradient_select_session_info
init|=
block|{
literal|"gradient-editor"
block|,
operator|(
name|GtkItemFactoryCallback
operator|)
name|dialogs_gradient_editor_cmd_callback
block|,
literal|170
block|,
literal|180
block|,
literal|0
block|,
literal|0
block|,
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|device_status_session_info
name|SessionInfo
name|device_status_session_info
init|=
block|{
literal|"device-status"
block|,
operator|(
name|GtkItemFactoryCallback
operator|)
name|dialogs_device_status_cmd_callback
block|,
literal|0
block|,
literal|600
block|,
literal|0
block|,
literal|0
block|,
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_console_session_info
name|SessionInfo
name|error_console_session_info
init|=
block|{
literal|"error-console"
block|,
operator|(
name|GtkItemFactoryCallback
operator|)
name|dialogs_error_console_cmd_callback
block|,
literal|400
block|,
literal|0
block|,
literal|250
block|,
literal|300
block|,
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* public functions */
end_comment

begin_function
name|void
DECL|function|session_get_window_info (GtkWidget * window,SessionInfo * info)
name|session_get_window_info
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|,
name|SessionInfo
modifier|*
name|info
parameter_list|)
block|{
if|if
condition|(
operator|!
name|save_session_info
operator|||
name|info
operator|==
name|NULL
operator|||
name|window
operator|->
name|window
operator|==
name|NULL
condition|)
return|return;
name|gdk_window_get_root_origin
argument_list|(
name|window
operator|->
name|window
argument_list|,
operator|&
name|info
operator|->
name|x
argument_list|,
operator|&
name|info
operator|->
name|y
argument_list|)
expr_stmt|;
name|gdk_window_get_size
argument_list|(
name|window
operator|->
name|window
argument_list|,
operator|&
name|info
operator|->
name|width
argument_list|,
operator|&
name|info
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|we_are_exiting
condition|)
name|info
operator|->
name|open
operator|=
name|GTK_WIDGET_VISIBLE
argument_list|(
name|window
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_list_find
argument_list|(
name|session_info_updates
argument_list|,
name|info
argument_list|)
operator|==
name|NULL
condition|)
name|session_info_updates
operator|=
name|g_list_append
argument_list|(
name|session_info_updates
argument_list|,
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|session_set_window_geometry (GtkWidget * window,SessionInfo * info,int set_size)
name|session_set_window_geometry
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|,
name|SessionInfo
modifier|*
name|info
parameter_list|,
name|int
name|set_size
parameter_list|)
block|{
if|if
condition|(
name|window
operator|==
name|NULL
operator|||
name|info
operator|==
name|NULL
condition|)
return|return;
name|gtk_widget_set_uposition
argument_list|(
name|window
argument_list|,
name|info
operator|->
name|x
argument_list|,
name|info
operator|->
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|set_size
operator|)
operator|&&
operator|(
name|info
operator|->
name|width
operator|>
literal|0
operator|)
operator|&&
operator|(
name|info
operator|->
name|height
operator|>
literal|0
operator|)
condition|)
name|gtk_window_set_default_size
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|info
operator|->
name|width
argument_list|,
name|info
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|save_sessionrc (void)
name|save_sessionrc
parameter_list|(
name|void
parameter_list|)
block|{
name|char
modifier|*
name|gimp_dir
decl_stmt|;
name|char
name|filename
index|[
literal|512
index|]
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gimp_dir
operator|=
name|gimp_directory
argument_list|()
expr_stmt|;
if|if
condition|(
literal|'\000'
operator|!=
name|gimp_dir
index|[
literal|0
index|]
condition|)
block|{
name|sprintf
argument_list|(
name|filename
argument_list|,
literal|"%s/sessionrc"
argument_list|,
name|gimp_dir
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fp
condition|)
return|return;
name|fprintf
argument_list|(
name|fp
argument_list|,
name|_
argument_list|(
literal|"# GIMP sessionrc\n"
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
name|_
argument_list|(
literal|"# This file takes session-specific info (that is info,\n"
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
name|_
argument_list|(
literal|"# you want to keep between two gimp-sessions). You are\n"
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
name|_
argument_list|(
literal|"# not supposed to edit it manually, but of course you\n"
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
name|_
argument_list|(
literal|"# can do. This file will be entirely rewritten every time\n"
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
name|_
argument_list|(
literal|"# you quit the gimp. If this file isn't found, defaults\n"
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
name|_
argument_list|(
literal|"# are used.\n\n"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* save window geometries */
name|g_list_foreach
argument_list|(
name|session_info_updates
argument_list|,
operator|(
name|GFunc
operator|)
name|sessionrc_write_info
argument_list|,
name|fp
argument_list|)
expr_stmt|;
comment|/* save last tip shown */
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"(last-tip-shown %d)\n\n"
argument_list|,
name|last_tip
operator|+
literal|1
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|session_init (void)
name|session_init
parameter_list|(
name|void
parameter_list|)
block|{
name|char
modifier|*
name|gimp_dir
decl_stmt|;
name|char
name|filename
index|[
literal|512
index|]
decl_stmt|;
name|gimp_dir
operator|=
name|gimp_directory
argument_list|()
expr_stmt|;
if|if
condition|(
name|gimp_dir
condition|)
block|{
name|sprintf
argument_list|(
name|filename
argument_list|,
literal|"%s/sessionrc"
argument_list|,
name|gimp_dir
argument_list|)
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|filename
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|parse_gimprc_file
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|session_restore (void)
name|session_restore
parameter_list|(
name|void
parameter_list|)
block|{
comment|/* open dialogs */
if|if
condition|(
name|restore_session
condition|)
name|g_list_foreach
argument_list|(
name|session_info_updates
argument_list|,
operator|(
name|GFunc
operator|)
name|session_open_dialog
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* reset the open state in the session_infos */
name|g_list_foreach
argument_list|(
name|session_info_updates
argument_list|,
operator|(
name|GFunc
operator|)
name|session_reset_open_state
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* internal function */
end_comment

begin_function
specifier|static
name|void
DECL|function|sessionrc_write_info (SessionInfo * info,FILE * fp)
name|sessionrc_write_info
parameter_list|(
name|SessionInfo
modifier|*
name|info
parameter_list|,
name|FILE
modifier|*
name|fp
parameter_list|)
block|{
if|if
condition|(
name|fp
operator|==
name|NULL
operator|||
name|info
operator|==
name|NULL
condition|)
return|return;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"(session-info \"%s\"\n"
argument_list|,
name|info
operator|->
name|name
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"   (position %d %d)\n"
argument_list|,
name|info
operator|->
name|x
argument_list|,
name|info
operator|->
name|y
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"   (size %d %d)"
argument_list|,
name|info
operator|->
name|width
argument_list|,
name|info
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|open
condition|)
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"\n   (open-on-exit)"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|")\n\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|session_open_dialog (SessionInfo * info)
name|session_open_dialog
parameter_list|(
name|SessionInfo
modifier|*
name|info
parameter_list|)
block|{
if|if
condition|(
name|info
operator|==
name|NULL
operator|||
name|info
operator|->
name|open
operator|==
name|FALSE
condition|)
return|return;
call|(
name|info
operator|->
name|open_callback
call|)
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|session_reset_open_state (SessionInfo * info)
name|session_reset_open_state
parameter_list|(
name|SessionInfo
modifier|*
name|info
parameter_list|)
block|{
if|if
condition|(
name|info
operator|==
name|NULL
condition|)
return|return;
name|info
operator|->
name|open
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

