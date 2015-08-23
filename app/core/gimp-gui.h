begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GUI_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GUI_H__
define|#
directive|define
name|__GIMP_GUI_H__
end_define

begin_typedef
DECL|typedef|GimpGui
typedef|typedef
name|struct
name|_GimpGui
name|GimpGui
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGui
struct|struct
name|_GimpGui
block|{
DECL|member|ungrab
name|void
function_decl|(
modifier|*
name|ungrab
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|threads_enter
name|void
function_decl|(
modifier|*
name|threads_enter
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|threads_leave
name|void
function_decl|(
modifier|*
name|threads_leave
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|set_busy
name|void
function_decl|(
modifier|*
name|set_busy
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|unset_busy
name|void
function_decl|(
modifier|*
name|unset_busy
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|show_message
name|void
function_decl|(
modifier|*
name|show_message
function_decl|)
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
DECL|member|help
name|void
function_decl|(
modifier|*
name|help
function_decl|)
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
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
DECL|member|get_program_class
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_program_class
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|get_display_name
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_display_name
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|display_ID
parameter_list|,
name|GObject
modifier|*
modifier|*
name|screen
parameter_list|,
name|gint
modifier|*
name|monitor
parameter_list|)
function_decl|;
DECL|member|get_user_time
name|guint32
function_decl|(
modifier|*
name|get_user_time
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|get_theme_dir
name|GFile
modifier|*
function_decl|(
modifier|*
name|get_theme_dir
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|get_window_strategy
name|GimpObject
modifier|*
function_decl|(
modifier|*
name|get_window_strategy
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|get_empty_display
name|GimpObject
modifier|*
function_decl|(
modifier|*
name|get_empty_display
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|display_get_by_id
name|GimpObject
modifier|*
function_decl|(
modifier|*
name|display_get_by_id
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|ID
parameter_list|)
function_decl|;
DECL|member|display_get_id
name|gint
function_decl|(
modifier|*
name|display_get_id
function_decl|)
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|display_get_window_id
name|guint32
function_decl|(
modifier|*
name|display_get_window_id
function_decl|)
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|display_create
name|GimpObject
modifier|*
function_decl|(
modifier|*
name|display_create
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|GObject
modifier|*
name|screen
parameter_list|,
name|gint
name|monitor
parameter_list|)
function_decl|;
DECL|member|display_delete
name|void
function_decl|(
modifier|*
name|display_delete
function_decl|)
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|displays_reconnect
name|void
function_decl|(
modifier|*
name|displays_reconnect
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|old_image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
DECL|member|progress_new
name|GimpProgress
modifier|*
function_decl|(
modifier|*
name|progress_new
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|progress_free
name|void
function_decl|(
modifier|*
name|progress_free
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
DECL|member|pdb_dialog_new
name|gboolean
function_decl|(
modifier|*
name|pdb_dialog_new
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
DECL|member|pdb_dialog_set
name|gboolean
function_decl|(
modifier|*
name|pdb_dialog_set
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
DECL|member|pdb_dialog_close
name|gboolean
function_decl|(
modifier|*
name|pdb_dialog_close
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|)
function_decl|;
DECL|member|recent_list_add_file
name|gboolean
function_decl|(
modifier|*
name|recent_list_add_file
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|)
function_decl|;
DECL|member|recent_list_load
name|void
function_decl|(
modifier|*
name|recent_list_load
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
name|GMountOperation
DECL|member|get_mount_operation
modifier|*
function_decl|(
modifier|*
name|get_mount_operation
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
name|GimpColorProfilePolicy
DECL|member|query_profile_policy
function_decl|(
modifier|*
name|query_profile_policy
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpColorProfile
modifier|*
modifier|*
name|dest_profile
parameter_list|,
name|gboolean
modifier|*
name|dont_ask
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_gui_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gui_ungrab
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_threads_enter
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_threads_leave
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_get_window_strategy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_get_empty_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_get_display_by_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_get_display_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint32
name|gimp_get_display_window_id
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_create_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|GObject
modifier|*
name|screen
parameter_list|,
name|gint
name|monitor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_delete_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_reconnect_displays
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|old_image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_busy_until_idle
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unset_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_show_message
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
name|void
name|gimp_help
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
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpProgress
modifier|*
name|gimp_new_progress
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_free_progress
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_get_program_class
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_get_display_name
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|display_ID
parameter_list|,
name|GObject
modifier|*
modifier|*
name|screen
parameter_list|,
name|gint
modifier|*
name|monitor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint32
name|gimp_get_user_time
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GFile
modifier|*
name|gimp_get_theme_dir
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|gboolean
name|gimp_pdb_dialog_new
argument_list|(
name|Gimp
operator|*
name|gimp
argument_list|,
name|GimpContext
operator|*
name|context
argument_list|,
name|GimpProgress
operator|*
name|progress
argument_list|,
name|GimpContainer
operator|*
name|container
argument_list|,
specifier|const
name|gchar
operator|*
name|title
argument_list|,
specifier|const
name|gchar
operator|*
name|callback_name
argument_list|,
specifier|const
name|gchar
operator|*
name|object_name
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gboolean
name|gimp_pdb_dialog_set
argument_list|(
name|Gimp
operator|*
name|gimp
argument_list|,
name|GimpContainer
operator|*
name|container
argument_list|,
specifier|const
name|gchar
operator|*
name|callback_name
argument_list|,
specifier|const
name|gchar
operator|*
name|object_name
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gimp_pdb_dialog_close
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_recent_list_add_file
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_recent_list_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GMountOperation
modifier|*
name|gimp_get_mount_operation
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfilePolicy
name|gimp_query_profile_policy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpColorProfile
modifier|*
modifier|*
name|dest_profile
parameter_list|,
name|gboolean
modifier|*
name|dont_ask
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GUI_H__ */
end_comment

end_unit

