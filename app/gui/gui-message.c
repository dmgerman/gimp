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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"about.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwindowstrategy.h"
end_include

begin_include
include|#
directive|include
file|"gui-message.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b68ac770108
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|domain
name|gchar
modifier|*
name|domain
decl_stmt|;
DECL|member|message
name|gchar
modifier|*
name|message
decl_stmt|;
DECL|member|handler
name|GObject
modifier|*
name|handler
decl_stmt|;
DECL|member|severity
name|GimpMessageSeverity
name|severity
decl_stmt|;
DECL|typedef|GimpLogMessageData
block|}
name|GimpLogMessageData
typedef|;
end_typedef

begin_function_decl
specifier|static
name|gboolean
name|gui_message_idle
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gui_message_error_console
parameter_list|(
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gui_message_error_dialog
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GObject
modifier|*
name|handler
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_message_console
parameter_list|(
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
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gui_message (Gimp * gimp,GObject * handler,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gui_message
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GObject
modifier|*
name|handler
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
name|gimp
argument_list|,
name|severity
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
name|GIMP_MESSAGE_BOX
expr_stmt|;
comment|/*  fallthru  */
case|case
name|GIMP_MESSAGE_BOX
case|:
if|if
condition|(
name|g_strcmp0
argument_list|(
name|GIMP_ACRONYM
argument_list|,
name|domain
argument_list|)
operator|!=
literal|0
condition|)
block|{
comment|/* Handle non-GIMP messages in a multi-thread safe way,            * because we can't know for sure whether the log message may            * not have been called from a thread other than the main one.            */
name|GimpLogMessageData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
name|g_new0
argument_list|(
name|GimpLogMessageData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|data
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|data
operator|->
name|domain
operator|=
name|g_strdup
argument_list|(
name|domain
argument_list|)
expr_stmt|;
name|data
operator|->
name|message
operator|=
name|g_strdup
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|data
operator|->
name|handler
operator|=
name|handler
condition|?
name|g_object_ref
argument_list|(
name|handler
argument_list|)
else|:
name|NULL
expr_stmt|;
name|data
operator|->
name|severity
operator|=
name|severity
expr_stmt|;
name|gdk_threads_add_idle_full
argument_list|(
name|G_PRIORITY_DEFAULT_IDLE
argument_list|,
name|gui_message_idle
argument_list|,
name|data
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|gui_message_error_dialog
argument_list|(
name|gimp
argument_list|,
name|handler
argument_list|,
name|severity
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
name|severity
argument_list|,
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
DECL|function|gui_message_idle (gpointer user_data)
name|gui_message_idle
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpLogMessageData
modifier|*
name|data
init|=
operator|(
name|GimpLogMessageData
operator|*
operator|)
name|user_data
decl_stmt|;
if|if
condition|(
operator|!
name|gui_message_error_dialog
argument_list|(
name|data
operator|->
name|gimp
argument_list|,
name|data
operator|->
name|handler
argument_list|,
name|data
operator|->
name|severity
argument_list|,
name|data
operator|->
name|domain
argument_list|,
name|data
operator|->
name|message
argument_list|)
condition|)
block|{
name|gui_message_console
argument_list|(
name|data
operator|->
name|severity
argument_list|,
name|data
operator|->
name|domain
argument_list|,
name|data
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|data
operator|->
name|domain
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|message
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|handler
condition|)
name|g_object_unref
argument_list|(
name|data
operator|->
name|handler
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gui_message_error_console (Gimp * gimp,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gui_message_error_console
parameter_list|(
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
name|GtkWidget
modifier|*
name|dockable
init|=
name|NULL
decl_stmt|;
comment|/* try to avoid raising the error console for not so severe messages */
if|if
condition|(
name|severity
operator|<
name|GIMP_MESSAGE_ERROR
condition|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|gimp_dialog_factory_find_widget
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
literal|"gimp-error-console"
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|widget
argument_list|)
condition|)
name|dockable
operator|=
name|widget
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|dockable
condition|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|gint
name|monitor
decl_stmt|;
name|monitor
operator|=
name|gimp_get_monitor_at_pointer
argument_list|(
operator|&
name|screen
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|gimp_window_strategy_show_dockable_dialog
argument_list|(
name|GIMP_WINDOW_STRATEGY
argument_list|(
name|gimp_get_window_strategy
argument_list|(
name|gimp
argument_list|)
argument_list|)
argument_list|,
name|gimp
argument_list|,
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|screen
argument_list|,
name|monitor
argument_list|,
literal|"gimp-error-console"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|dockable
condition|)
block|{
name|GtkWidget
modifier|*
name|child
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_error_console_add
argument_list|(
name|GIMP_ERROR_CONSOLE
argument_list|(
name|child
argument_list|)
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
name|window_id
init|=
name|gimp_progress_get_window_id
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|window_id
condition|)
name|gimp_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|window_id
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
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|gint
name|monitor
decl_stmt|;
name|monitor
operator|=
name|gimp_get_monitor_at_pointer
argument_list|(
operator|&
name|screen
argument_list|)
expr_stmt|;
return|return
name|gimp_dialog_factory_dialog_new
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|screen
argument_list|,
name|monitor
argument_list|,
name|NULL
comment|/*ui_manager*/
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
DECL|function|gui_message_error_dialog (Gimp * gimp,GObject * handler,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gui_message_error_dialog
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GObject
modifier|*
name|handler
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
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
name|GIMP_IS_PROGRESS
argument_list|(
name|handler
argument_list|)
condition|)
block|{
comment|/* If there's already an error dialog associated with this        * progress, then continue without trying gimp_progress_message().        */
if|if
condition|(
operator|!
name|g_object_get_data
argument_list|(
name|handler
argument_list|,
literal|"gimp-error-dialog"
argument_list|)
operator|&&
name|gimp_progress_message
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|handler
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
condition|)
block|{
return|return
name|TRUE
return|;
block|}
block|}
elseif|else
if|if
condition|(
name|GTK_IS_WIDGET
argument_list|(
name|handler
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|parent
init|=
name|GTK_WIDGET
argument_list|(
name|handler
argument_list|)
decl_stmt|;
name|GtkMessageType
name|type
init|=
name|GTK_MESSAGE_ERROR
decl_stmt|;
switch|switch
condition|(
name|severity
condition|)
block|{
case|case
name|GIMP_MESSAGE_INFO
case|:
name|type
operator|=
name|GTK_MESSAGE_INFO
expr_stmt|;
break|break;
case|case
name|GIMP_MESSAGE_WARNING
case|:
name|type
operator|=
name|GTK_MESSAGE_WARNING
expr_stmt|;
break|break;
case|case
name|GIMP_MESSAGE_ERROR
case|:
name|type
operator|=
name|GTK_MESSAGE_ERROR
expr_stmt|;
break|break;
block|}
name|dialog
operator|=
name|gtk_message_dialog_new
argument_list|(
name|GTK_WINDOW
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|parent
argument_list|)
argument_list|)
argument_list|,
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|type
argument_list|,
name|GTK_BUTTONS_OK
argument_list|,
literal|"%s"
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
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
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|GIMP_IS_PROGRESS
argument_list|(
name|handler
argument_list|)
operator|&&
operator|!
name|GIMP_IS_PROGRESS_DIALOG
argument_list|(
name|handler
argument_list|)
condition|)
name|dialog
operator|=
name|progress_error_dialog
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|handler
argument_list|)
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
name|gimp_get_message_icon_name
argument_list|(
name|severity
argument_list|)
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
DECL|function|gui_message_console (GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gui_message_console
parameter_list|(
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
specifier|const
name|gchar
modifier|*
name|desc
init|=
literal|"Message"
decl_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_MESSAGE_SEVERITY
argument_list|,
name|severity
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"%s-%s: %s\n\n"
argument_list|,
name|domain
argument_list|,
name|desc
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

