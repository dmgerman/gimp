begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpdebug  * Copyright (C) 2018 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * GimpDebug simply displays a dialog with debug data (backtraces,  * version, etc.), proposing to create a bug report. The reason why it  * is a separate executable is simply that when the program crashed,  * even though some actions are possible before exit() by catching fatal  * errors and signals, it may not be possible to allocate memory  * anymore. Therefore creating a new dialog is an impossible action.  * So we call instead a separate program, then exit.  */
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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<glib/gi18n.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"app/widgets/gimpcriticaldialog.h"
end_include

begin_function
name|int
DECL|function|main (int argc,char ** argv)
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|program
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|pid
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|reason
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|message
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|bt_file
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|trace
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|error
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
name|argc
operator|!=
literal|6
condition|)
block|{
name|g_print
argument_list|(
literal|"Usage: gimp-debug-tool-2.0 [PROGRAM] [PID] [REASON] [MESSAGE] [BT_FILE]\n"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
block|}
name|program
operator|=
name|argv
index|[
literal|1
index|]
expr_stmt|;
name|pid
operator|=
name|argv
index|[
literal|2
index|]
expr_stmt|;
name|reason
operator|=
name|argv
index|[
literal|3
index|]
expr_stmt|;
name|message
operator|=
name|argv
index|[
literal|4
index|]
expr_stmt|;
name|error
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s: %s"
argument_list|,
name|reason
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|bt_file
operator|=
name|argv
index|[
literal|5
index|]
expr_stmt|;
name|g_file_get_contents
argument_list|(
name|bt_file
argument_list|,
operator|&
name|trace
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|trace
operator|==
name|NULL
operator|||
name|strlen
argument_list|(
name|trace
argument_list|)
operator|==
literal|0
condition|)
name|exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_critical_dialog_new
argument_list|(
name|_
argument_list|(
literal|"GIMP Crash Debug"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_critical_dialog_add
argument_list|(
name|dialog
argument_list|,
name|error
argument_list|,
name|trace
argument_list|,
name|TRUE
argument_list|,
name|program
argument_list|,
name|g_ascii_strtoull
argument_list|(
name|pid
argument_list|,
name|NULL
argument_list|,
literal|10
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|trace
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"delete-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

