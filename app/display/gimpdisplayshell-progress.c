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
file|"gimpimagewindow.h"
end_include

begin_include
include|#
directive|include
file|"gimpstatusbar.h"
end_include

begin_comment
comment|/* FIXME: need to store the shell's progress state in the shell itself  * instead of simply dispatching to the statusbar. Otherwise it's  * impossible to switch an image window between two shells that both  * have active progress messages.  */
end_comment

begin_function
specifier|static
name|GimpProgress
modifier|*
DECL|function|gimp_display_shell_progress_get_real_progress (GimpProgress * progress)
name|gimp_display_shell_progress_get_real_progress
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
name|GimpImageWindow
modifier|*
name|window
init|=
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
decl_stmt|;
if|if
condition|(
name|window
operator|&&
name|gimp_image_window_get_active_shell
argument_list|(
name|window
argument_list|)
operator|==
name|shell
condition|)
return|return
name|GIMP_PROGRESS
argument_list|(
name|window
operator|->
name|statusbar
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

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
name|progress
operator|=
name|gimp_display_shell_progress_get_real_progress
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
return|return
name|gimp_progress_start
argument_list|(
name|progress
argument_list|,
name|message
argument_list|,
name|cancelable
argument_list|)
return|;
return|return
name|NULL
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
name|progress
operator|=
name|gimp_display_shell_progress_get_real_progress
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
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
name|progress
operator|=
name|gimp_display_shell_progress_get_real_progress
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
return|return
name|gimp_progress_is_active
argument_list|(
name|progress
argument_list|)
return|;
return|return
name|FALSE
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
name|progress
operator|=
name|gimp_display_shell_progress_get_real_progress
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_set_text
argument_list|(
name|progress
argument_list|,
name|message
argument_list|)
expr_stmt|;
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
name|progress
operator|=
name|gimp_display_shell_progress_get_real_progress
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_set_value
argument_list|(
name|progress
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
name|progress
operator|=
name|gimp_display_shell_progress_get_real_progress
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
return|return
name|gimp_progress_get_value
argument_list|(
name|progress
argument_list|)
return|;
return|return
literal|0.0
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
name|progress
operator|=
name|gimp_display_shell_progress_get_real_progress
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_pulse
argument_list|(
name|progress
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
name|GtkWidget
modifier|*
name|toplevel
init|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|progress
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_IS_WINDOW
argument_list|(
name|toplevel
argument_list|)
condition|)
return|return
operator|(
name|guint32
operator|)
name|gimp_window_get_native
argument_list|(
name|GTK_WINDOW
argument_list|(
name|toplevel
argument_list|)
argument_list|)
return|;
return|return
literal|0
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
name|progress
operator|=
name|gimp_display_shell_progress_get_real_progress
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
block|{
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
name|progress
argument_list|)
argument_list|)
condition|)
break|break;
else|else
return|return
name|gimp_progress_message
argument_list|(
name|progress
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
case|case
name|GIMP_MESSAGE_INFO
case|:
comment|/* info messages go to the statusbar;            * if they are not handled there, they are swallowed            */
name|gimp_progress_message
argument_list|(
name|progress
argument_list|,
name|gimp
argument_list|,
name|severity
argument_list|,
name|domain
argument_list|,
name|message
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
return|return
name|FALSE
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

end_unit

