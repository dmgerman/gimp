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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimperrorconsole.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimperrordialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpprogressdialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gui_message_error_console
parameter_list|(
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gui_message_error_dialog
parameter_list|(
name|GimpProgress
modifier|*
name|progress
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_message_console
parameter_list|(
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
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gui_message (Gimp * gimp,GimpProgress * progress,const gchar * domain,const gchar * message)
name|gui_message
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
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
switch|switch
condition|(
name|gimp
operator|->
name|message_handler
condition|)
block|{
case|case
name|GIMP_ERROR_CONSOLE
case|:
if|if
condition|(
name|gui_message_error_console
argument_list|(
name|domain
argument_list|,
name|message
argument_list|)
condition|)
return|return;
name|gimp
operator|->
name|message_handler
operator|=
name|GIMP_MESSAGE_BOX
expr_stmt|;
comment|/*  fallthru  */
case|case
name|GIMP_MESSAGE_BOX
case|:
if|if
condition|(
name|gui_message_error_dialog
argument_list|(
name|progress
argument_list|,
name|domain
argument_list|,
name|message
argument_list|)
condition|)
return|return;
name|gimp
operator|->
name|message_handler
operator|=
name|GIMP_CONSOLE
expr_stmt|;
comment|/*  fallthru  */
case|case
name|GIMP_CONSOLE
case|:
name|gui_message_console
argument_list|(
name|domain
argument_list|,
name|message
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gui_message_error_console (const gchar * domain,const gchar * message)
name|gui_message_error_console
parameter_list|(
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
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
name|gdk_screen_get_default
argument_list|()
argument_list|,
literal|"gimp-error-console"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
block|{
name|gimp_error_console_add
argument_list|(
name|GIMP_ERROR_CONSOLE
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|GIMP_STOCK_WARNING
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
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|progress_error_dialog_unset (GimpProgress * progress)
name|progress_error_dialog_unset
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|"gimp-error-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|progress_error_dialog (GimpProgress * progress)
name|progress_error_dialog
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|"gimp-error-dialog"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
name|dialog
operator|=
name|gimp_error_dialog_new
argument_list|(
name|_
argument_list|(
literal|"GIMP Message"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|"gimp-error-dialog"
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|progress_error_dialog_unset
argument_list|)
argument_list|,
name|progress
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_WIDGET
argument_list|(
name|progress
argument_list|)
condition|)
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
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|toplevel
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|guint32
name|window
init|=
name|gimp_progress_get_window
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|window
condition|)
name|gimp_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|global_error_dialog (void)
name|global_error_dialog
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|gdk_screen_get_default
argument_list|()
argument_list|,
literal|"gimp-error-dialog"
argument_list|,
operator|-
literal|1
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gui_message_error_dialog (GimpProgress * progress,const gchar * domain,const gchar * message)
name|gui_message_error_dialog
parameter_list|(
name|GimpProgress
modifier|*
name|progress
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
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
name|progress
operator|&&
operator|!
name|GIMP_IS_PROGRESS_DIALOG
argument_list|(
name|progress
argument_list|)
condition|)
name|dialog
operator|=
name|progress_error_dialog
argument_list|(
name|progress
argument_list|)
expr_stmt|;
else|else
name|dialog
operator|=
name|global_error_dialog
argument_list|()
expr_stmt|;
if|if
condition|(
name|dialog
condition|)
block|{
name|gimp_error_dialog_add
argument_list|(
name|GIMP_ERROR_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|,
name|domain
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_message_console (const gchar * domain,const gchar * message)
name|gui_message_console
parameter_list|(
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
name|g_printerr
argument_list|(
literal|"%s: %s\n\n"
argument_list|,
name|domain
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

