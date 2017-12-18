begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdashboard.h  * Copyright (C) 2017 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DASHBOARD_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DASHBOARD_H__
define|#
directive|define
name|__GIMP_DASHBOARD_H__
end_define

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DASHBOARD
define|#
directive|define
name|GIMP_TYPE_DASHBOARD
value|(gimp_dashboard_get_type ())
end_define

begin_define
DECL|macro|GIMP_DASHBOARD (obj)
define|#
directive|define
name|GIMP_DASHBOARD
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DASHBOARD, GimpDashboard))
end_define

begin_define
DECL|macro|GIMP_DASHBOARD_CLASS (klass)
define|#
directive|define
name|GIMP_DASHBOARD_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DASHBOARD, GimpDashboardClass))
end_define

begin_define
DECL|macro|GIMP_IS_DASHBOARD (obj)
define|#
directive|define
name|GIMP_IS_DASHBOARD
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DASHBOARD))
end_define

begin_define
DECL|macro|GIMP_IS_DASHBOARD_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DASHBOARD_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DASHBOARD))
end_define

begin_define
DECL|macro|GIMP_DASHBOARD_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DASHBOARD_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DASHBOARD, GimpDashboardClass))
end_define

begin_typedef
DECL|typedef|GimpDashboardClass
typedef|typedef
name|struct
name|_GimpDashboardClass
name|GimpDashboardClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDashboard
struct|struct
name|_GimpDashboard
block|{
DECL|member|parent_instance
name|GimpEditor
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|box
name|GtkWidget
modifier|*
name|box
decl_stmt|;
DECL|member|cache_meter
name|GtkWidget
modifier|*
name|cache_meter
decl_stmt|;
DECL|member|cache_occupied_label
name|GtkWidget
modifier|*
name|cache_occupied_label
decl_stmt|;
DECL|member|cache_occupied_pct_label
name|GtkWidget
modifier|*
name|cache_occupied_pct_label
decl_stmt|;
DECL|member|cache_limit_label
name|GtkWidget
modifier|*
name|cache_limit_label
decl_stmt|;
DECL|member|swap_meter
name|GtkWidget
modifier|*
name|swap_meter
decl_stmt|;
DECL|member|swap_occupied_label
name|GtkWidget
modifier|*
name|swap_occupied_label
decl_stmt|;
DECL|member|swap_occupied_pct_label
name|GtkWidget
modifier|*
name|swap_occupied_pct_label
decl_stmt|;
DECL|member|swap_size_label
name|GtkWidget
modifier|*
name|swap_size_label
decl_stmt|;
DECL|member|swap_size_pct_label
name|GtkWidget
modifier|*
name|swap_size_pct_label
decl_stmt|;
DECL|member|swap_limit_label
name|GtkWidget
modifier|*
name|swap_limit_label
decl_stmt|;
DECL|member|timeout_id
name|gint
name|timeout_id
decl_stmt|;
DECL|member|low_swap_space_idle_id
name|gint
name|low_swap_space_idle_id
decl_stmt|;
DECL|member|thread
name|GThread
modifier|*
name|thread
decl_stmt|;
DECL|member|mutex
name|GMutex
name|mutex
decl_stmt|;
DECL|member|cond
name|GCond
name|cond
decl_stmt|;
DECL|member|quit
name|gboolean
name|quit
decl_stmt|;
DECL|member|update_interval
name|GimpDashboardUpdateInteval
name|update_interval
decl_stmt|;
DECL|member|history_duration
name|GimpDashboardHistoryDuration
name|history_duration
decl_stmt|;
DECL|member|low_swap_space_warning
name|gboolean
name|low_swap_space_warning
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDashboardClass
struct|struct
name|_GimpDashboardClass
block|{
DECL|member|parent_class
name|GimpEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dashboard_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dashboard_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dashboard_set_update_interval
parameter_list|(
name|GimpDashboard
modifier|*
name|dashboard
parameter_list|,
name|GimpDashboardUpdateInteval
name|update_interval
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dashboard_set_history_duration
parameter_list|(
name|GimpDashboard
modifier|*
name|dashboard
parameter_list|,
name|GimpDashboardHistoryDuration
name|history_duration
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dashboard_set_low_swap_space_warning
parameter_list|(
name|GimpDashboard
modifier|*
name|dashboard
parameter_list|,
name|gboolean
name|low_swap_space_warning
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DASHBOARD_H__  */
end_comment

end_unit

