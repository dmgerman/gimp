begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-progress.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-title.h"
end_include

begin_include
include|#
directive|include
file|"gimpstatusbar.h"
end_include

begin_comment
comment|/*  Progress is shown in the status-bar. If the image window is iconified,  *  the progress messages are also shown in the window title so that they  *  appear in the task bar.  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_display_shell_is_iconified
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|GimpProgress
modifier|*
DECL|function|gimp_display_shell_progress_start (GimpProgress * progress,const gchar * message,gboolean cancelable)
name|gimp_display_shell_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
name|message
argument_list|,
name|cancelable
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|&&
name|gimp_display_shell_is_iconified
argument_list|(
name|shell
argument_list|)
condition|)
block|{
name|gdk_window_set_title
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
operator|->
name|window
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
return|return
name|progress
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_progress_end (GimpProgress * progress)
name|gimp_display_shell_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
name|gimp_progress_end
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_display_shell_is_iconified
argument_list|(
name|shell
argument_list|)
condition|)
name|gimp_display_shell_title_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_progress_is_active (GimpProgress * progress)
name|gimp_display_shell_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
return|return
name|gimp_progress_is_active
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_progress_set_text (GimpProgress * progress,const gchar * message)
name|gimp_display_shell_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
name|gimp_progress_set_text
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
name|message
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_progress_is_active
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
operator|&&
name|gimp_display_shell_is_iconified
argument_list|(
name|shell
argument_list|)
condition|)
block|{
name|gdk_window_set_title
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
operator|->
name|window
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_progress_set_value (GimpProgress * progress,gdouble percentage)
name|gimp_display_shell_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
name|gimp_progress_set_value
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_display_shell_progress_get_value (GimpProgress * progress)
name|gimp_display_shell_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
return|return
name|gimp_progress_get_value
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_progress_pulse (GimpProgress * progress)
name|gimp_display_shell_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
name|gimp_progress_pulse
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|gimp_display_shell_progress_get_window (GimpProgress * progress)
name|gimp_display_shell_progress_get_window
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
return|return
operator|(
name|guint32
operator|)
name|gimp_window_get_native
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_progress_message (GimpProgress * progress,Gimp * gimp,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gimp_display_shell_progress_message
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|severity
condition|)
block|{
case|case
name|GIMP_MESSAGE_ERROR
case|:
comment|/* error messages are never handled here */
break|break;
case|case
name|GIMP_MESSAGE_WARNING
case|:
comment|/* warning messages go to the statusbar, if it's visible */
if|if
condition|(
operator|!
name|gimp_statusbar_get_visible
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
condition|)
break|break;
comment|/* else fallthrough */
case|case
name|GIMP_MESSAGE_INFO
case|:
comment|/* info messages go to the statusbar, no matter if it's visible or not */
return|return
name|gimp_progress_message
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
name|gimp
argument_list|,
name|severity
argument_list|,
name|domain
argument_list|,
name|message
argument_list|)
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_is_iconified (GimpDisplayShell * shell)
name|gimp_display_shell_is_iconified
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
decl_stmt|;
return|return
operator|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|widget
argument_list|)
operator|&&
name|gdk_window_get_state
argument_list|(
name|widget
operator|->
name|window
argument_list|)
operator|==
name|GDK_WINDOW_STATE_ICONIFIED
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_progress_iface_init (GimpProgressInterface * iface)
name|gimp_display_shell_progress_iface_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|start
operator|=
name|gimp_display_shell_progress_start
expr_stmt|;
name|iface
operator|->
name|end
operator|=
name|gimp_display_shell_progress_end
expr_stmt|;
name|iface
operator|->
name|is_active
operator|=
name|gimp_display_shell_progress_is_active
expr_stmt|;
name|iface
operator|->
name|set_text
operator|=
name|gimp_display_shell_progress_set_text
expr_stmt|;
name|iface
operator|->
name|set_value
operator|=
name|gimp_display_shell_progress_set_value
expr_stmt|;
name|iface
operator|->
name|get_value
operator|=
name|gimp_display_shell_progress_get_value
expr_stmt|;
name|iface
operator|->
name|pulse
operator|=
name|gimp_display_shell_progress_pulse
expr_stmt|;
name|iface
operator|->
name|get_window
operator|=
name|gimp_display_shell_progress_get_window
expr_stmt|;
name|iface
operator|->
name|message
operator|=
name|gimp_display_shell_progress_message
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_progress_window_state_changed (GimpDisplayShell * shell)
name|gimp_display_shell_progress_window_state_changed
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gimp_progress_is_active
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|shell
argument_list|)
argument_list|)
condition|)
return|return;
if|if
condition|(
name|gimp_display_shell_is_iconified
argument_list|(
name|shell
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|msg
init|=
name|gimp_statusbar_peek
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"progress"
argument_list|)
decl_stmt|;
if|if
condition|(
name|msg
condition|)
block|{
name|gdk_window_set_title
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
operator|->
name|window
argument_list|,
name|msg
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|gimp_display_shell_title_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

