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
file|"dashboard-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functionss */
end_comment

begin_function
name|void
DECL|function|dashboard_update_interval_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|dashboard_update_interval_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkAction
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
name|gtk_radio_action_get_current_value
argument_list|(
name|GTK_RADIO_ACTION
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
DECL|function|dashboard_history_duration_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|dashboard_history_duration_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkAction
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
name|gtk_radio_action_get_current_value
argument_list|(
name|GTK_RADIO_ACTION
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
DECL|function|dashboard_low_swap_space_warning_cmd_callback (GtkAction * action,gpointer data)
name|dashboard_low_swap_space_warning_cmd_callback
parameter_list|(
name|GtkAction
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
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
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

end_unit

