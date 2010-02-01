begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGuiConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GUI_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GUI_CONFIG_H__
define|#
directive|define
name|__GIMP_GUI_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"config/gimpdisplayconfig.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_GUI_CONFIG
define|#
directive|define
name|GIMP_TYPE_GUI_CONFIG
value|(gimp_gui_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_GUI_CONFIG (obj)
define|#
directive|define
name|GIMP_GUI_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_GUI_CONFIG, GimpGuiConfig))
end_define

begin_define
DECL|macro|GIMP_GUI_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_GUI_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_GUI_CONFIG, GimpGuiConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_GUI_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_GUI_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_GUI_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_GUI_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_GUI_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_GUI_CONFIG))
end_define

begin_typedef
DECL|typedef|GimpGuiConfigClass
typedef|typedef
name|struct
name|_GimpGuiConfigClass
name|GimpGuiConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGuiConfig
struct|struct
name|_GimpGuiConfig
block|{
DECL|member|parent_instance
name|GimpDisplayConfig
name|parent_instance
decl_stmt|;
DECL|member|default_threshold
name|gint
name|default_threshold
decl_stmt|;
DECL|member|move_tool_changes_active
name|gboolean
name|move_tool_changes_active
decl_stmt|;
DECL|member|image_map_tool_max_recent
name|gint
name|image_map_tool_max_recent
decl_stmt|;
DECL|member|trust_dirty_flag
name|gboolean
name|trust_dirty_flag
decl_stmt|;
DECL|member|save_device_status
name|gboolean
name|save_device_status
decl_stmt|;
DECL|member|save_session_info
name|gboolean
name|save_session_info
decl_stmt|;
DECL|member|restore_session
name|gboolean
name|restore_session
decl_stmt|;
DECL|member|save_tool_options
name|gboolean
name|save_tool_options
decl_stmt|;
DECL|member|show_tooltips
name|gboolean
name|show_tooltips
decl_stmt|;
DECL|member|single_window_mode
name|gboolean
name|single_window_mode
decl_stmt|;
DECL|member|tearoff_menus
name|gboolean
name|tearoff_menus
decl_stmt|;
DECL|member|can_change_accels
name|gboolean
name|can_change_accels
decl_stmt|;
DECL|member|save_accels
name|gboolean
name|save_accels
decl_stmt|;
DECL|member|restore_accels
name|gboolean
name|restore_accels
decl_stmt|;
DECL|member|last_opened_size
name|gint
name|last_opened_size
decl_stmt|;
DECL|member|max_new_image_size
name|guint64
name|max_new_image_size
decl_stmt|;
DECL|member|toolbox_color_area
name|gboolean
name|toolbox_color_area
decl_stmt|;
DECL|member|toolbox_foo_area
name|gboolean
name|toolbox_foo_area
decl_stmt|;
DECL|member|toolbox_image_area
name|gboolean
name|toolbox_image_area
decl_stmt|;
DECL|member|toolbox_wilber
name|gboolean
name|toolbox_wilber
decl_stmt|;
DECL|member|theme_path
name|gchar
modifier|*
name|theme_path
decl_stmt|;
DECL|member|theme
name|gchar
modifier|*
name|theme
decl_stmt|;
DECL|member|use_help
name|gboolean
name|use_help
decl_stmt|;
DECL|member|show_help_button
name|gboolean
name|show_help_button
decl_stmt|;
DECL|member|help_locales
name|gchar
modifier|*
name|help_locales
decl_stmt|;
DECL|member|help_browser
name|GimpHelpBrowserType
name|help_browser
decl_stmt|;
DECL|member|web_browser
name|gchar
modifier|*
name|web_browser
decl_stmt|;
DECL|member|user_manual_online
name|gboolean
name|user_manual_online
decl_stmt|;
DECL|member|user_manual_online_uri
name|gchar
modifier|*
name|user_manual_online_uri
decl_stmt|;
DECL|member|dock_window_hint
name|GimpWindowHint
name|dock_window_hint
decl_stmt|;
DECL|member|cursor_format
name|GimpCursorFormat
name|cursor_format
decl_stmt|;
DECL|member|last_tip
name|gint
name|last_tip
decl_stmt|;
comment|/* saved in sessionrc */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpGuiConfigClass
struct|struct
name|_GimpGuiConfigClass
block|{
DECL|member|parent_class
name|GimpDisplayConfigClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_gui_config_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_GUI_CONFIG_H__ */
end_comment

end_unit

