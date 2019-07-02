begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdashboard.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpradioaction.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptoggleaction.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dashboard-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|dashboard_log_record_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|int
name|response_id
parameter_list|,
name|GimpDashboard
modifier|*
name|dashboard
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dashboard_log_add_marker_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|description
parameter_list|,
name|GimpDashboard
modifier|*
name|dashboard
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions */
end_comment

begin_function
name|void
DECL|function|dashboard_update_interval_cmd_callback (GimpAction * action,GimpAction * current,gpointer data)
name|dashboard_update_interval_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GimpAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDashboard
modifier|*
name|dashboard
init|=
name|GIMP_DASHBOARD
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDashboardUpdateInteval
name|update_interval
decl_stmt|;
name|update_interval
operator|=
name|gimp_radio_action_get_current_value
argument_list|(
name|GIMP_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dashboard_set_update_interval
argument_list|(
name|dashboard
argument_list|,
name|update_interval
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dashboard_history_duration_cmd_callback (GimpAction * action,GimpAction * current,gpointer data)
name|dashboard_history_duration_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GimpAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDashboard
modifier|*
name|dashboard
init|=
name|GIMP_DASHBOARD
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDashboardHistoryDuration
name|history_duration
decl_stmt|;
name|history_duration
operator|=
name|gimp_radio_action_get_current_value
argument_list|(
name|GIMP_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dashboard_set_history_duration
argument_list|(
name|dashboard
argument_list|,
name|history_duration
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dashboard_log_record_cmd_callback (GimpAction * action,gpointer data)
name|dashboard_log_record_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDashboard
modifier|*
name|dashboard
init|=
name|GIMP_DASHBOARD
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_dashboard_log_is_recording
argument_list|(
name|dashboard
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|macro|LOG_RECORD_KEY
define|#
directive|define
name|LOG_RECORD_KEY
value|"gimp-dashboard-log-record-dialog"
name|dialog
operator|=
name|dialogs_get_dialog
argument_list|(
name|G_OBJECT
argument_list|(
name|dashboard
argument_list|)
argument_list|,
name|LOG_RECORD_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
name|GtkFileFilter
modifier|*
name|filter
decl_stmt|;
name|GFile
modifier|*
name|folder
decl_stmt|;
name|dialog
operator|=
name|gtk_file_chooser_dialog_new
argument_list|(
literal|"Record Performance Log"
argument_list|,
name|NULL
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_SAVE
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_Record"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
name|gimp_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dashboard
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-dashboard-log-record"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_do_overwrite_confirmation
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|filter
operator|=
name|gtk_file_filter_new
argument_list|()
expr_stmt|;
name|gtk_file_filter_set_name
argument_list|(
name|filter
argument_list|,
name|_
argument_list|(
literal|"All Files"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_file_filter_add_pattern
argument_list|(
name|filter
argument_list|,
literal|"*"
argument_list|)
expr_stmt|;
name|gtk_file_chooser_add_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|filter
operator|=
name|gtk_file_filter_new
argument_list|()
expr_stmt|;
name|gtk_file_filter_set_name
argument_list|(
name|filter
argument_list|,
name|_
argument_list|(
literal|"Log Files (*.log)"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_file_filter_add_pattern
argument_list|(
name|filter
argument_list|,
literal|"*.log"
argument_list|)
expr_stmt|;
name|gtk_file_chooser_add_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|folder
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dashboard
argument_list|)
argument_list|,
literal|"gimp-dashboard-log-record-folder"
argument_list|)
expr_stmt|;
if|if
condition|(
name|folder
condition|)
block|{
name|gtk_file_chooser_set_current_folder_file
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|folder
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gtk_file_chooser_set_current_name
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-performance.log"
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
name|dashboard_log_record_response
argument_list|)
argument_list|,
name|dashboard
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
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_connect
argument_list|(
name|dialog
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_DASHBOARD_LOG_RECORD
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialogs_attach_dialog
argument_list|(
name|G_OBJECT
argument_list|(
name|dashboard
argument_list|)
argument_list|,
name|LOG_RECORD_KEY
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dashboard
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|dialog
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|LOG_RECORD_KEY
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_dashboard_log_stop_recording
argument_list|(
name|dashboard
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|dashboard
argument_list|)
argument_list|)
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|dashboard_log_add_marker_cmd_callback (GimpAction * action,gpointer data)
name|dashboard_log_add_marker_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDashboard
modifier|*
name|dashboard
init|=
name|GIMP_DASHBOARD
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|macro|LOG_ADD_MARKER_KEY
define|#
directive|define
name|LOG_ADD_MARKER_KEY
value|"gimp-dashboard-log-add-marker-dialog"
name|dialog
operator|=
name|dialogs_get_dialog
argument_list|(
name|G_OBJECT
argument_list|(
name|dashboard
argument_list|)
argument_list|,
name|LOG_ADD_MARKER_KEY
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
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Add Marker"
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dashboard
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_DASHBOARD_LOG_ADD_MARKER
argument_list|,
name|_
argument_list|(
literal|"Enter a description for the marker"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_OBJECT
argument_list|(
name|dashboard
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
operator|(
name|GimpQueryStringCallback
operator|)
name|dashboard_log_add_marker_response
argument_list|,
name|dashboard
argument_list|)
expr_stmt|;
name|dialogs_attach_dialog
argument_list|(
name|G_OBJECT
argument_list|(
name|dashboard
argument_list|)
argument_list|,
name|LOG_ADD_MARKER_KEY
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|LOG_ADD_MARKER_KEY
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dashboard_log_add_empty_marker_cmd_callback (GimpAction * action,gpointer data)
name|dashboard_log_add_empty_marker_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDashboard
modifier|*
name|dashboard
init|=
name|GIMP_DASHBOARD
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_dashboard_log_add_marker
argument_list|(
name|dashboard
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dashboard_reset_cmd_callback (GimpAction * action,gpointer data)
name|dashboard_reset_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDashboard
modifier|*
name|dashboard
init|=
name|GIMP_DASHBOARD
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_dashboard_reset
argument_list|(
name|dashboard
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dashboard_low_swap_space_warning_cmd_callback (GimpAction * action,gpointer data)
name|dashboard_low_swap_space_warning_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDashboard
modifier|*
name|dashboard
init|=
name|GIMP_DASHBOARD
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|low_swap_space_warning
decl_stmt|;
name|low_swap_space_warning
operator|=
name|gimp_toggle_action_get_active
argument_list|(
name|GIMP_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dashboard_set_low_swap_space_warning
argument_list|(
name|dashboard
argument_list|,
name|low_swap_space_warning
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|dashboard_log_record_response (GtkWidget * dialog,int response_id,GimpDashboard * dashboard)
name|dashboard_log_record_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|int
name|response_id
parameter_list|,
name|GimpDashboard
modifier|*
name|dashboard
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GFile
modifier|*
name|file
init|=
name|gtk_file_chooser_get_file
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|dashboard
argument_list|)
argument_list|,
literal|"gimp-dashboard-log-record-folder"
argument_list|,
name|g_file_get_parent
argument_list|(
name|file
argument_list|)
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_dashboard_log_start_recording
argument_list|(
name|dashboard
argument_list|,
name|file
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|dashboard
argument_list|)
argument_list|)
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dashboard_log_add_marker_response (GtkWidget * dialog,const gchar * description,GimpDashboard * dashboard)
name|dashboard_log_add_marker_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|description
parameter_list|,
name|GimpDashboard
modifier|*
name|dashboard
parameter_list|)
block|{
name|gimp_dashboard_log_add_marker
argument_list|(
name|dashboard
argument_list|,
name|description
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

