begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPRC_H__
end_ifndef

begin_define
DECL|macro|__GIMPRC_H__
define|#
directive|define
name|__GIMPRC_H__
end_define

begin_typedef
DECL|typedef|GimpRc
typedef|typedef
name|struct
name|_GimpRc
name|GimpRc
typedef|;
end_typedef

begin_comment
comment|/*  global gimprc variables  - need some comments on this stuff */
end_comment

begin_struct
DECL|struct|_GimpRc
struct|struct
name|_GimpRc
block|{
DECL|member|marching_speed
name|gint
name|marching_speed
decl_stmt|;
DECL|member|last_opened_size
name|gint
name|last_opened_size
decl_stmt|;
DECL|member|gamma_val
name|gdouble
name|gamma_val
decl_stmt|;
DECL|member|transparency_type
name|gint
name|transparency_type
decl_stmt|;
DECL|member|perfectmouse
name|gboolean
name|perfectmouse
decl_stmt|;
DECL|member|transparency_size
name|gint
name|transparency_size
decl_stmt|;
DECL|member|min_colors
name|gint
name|min_colors
decl_stmt|;
DECL|member|install_cmap
name|gboolean
name|install_cmap
decl_stmt|;
DECL|member|cycled_marching_ants
name|gboolean
name|cycled_marching_ants
decl_stmt|;
DECL|member|default_threshold
name|gint
name|default_threshold
decl_stmt|;
DECL|member|resize_windows_on_zoom
name|gboolean
name|resize_windows_on_zoom
decl_stmt|;
DECL|member|resize_windows_on_resize
name|gboolean
name|resize_windows_on_resize
decl_stmt|;
DECL|member|no_cursor_updating
name|gboolean
name|no_cursor_updating
decl_stmt|;
DECL|member|preview_size
name|gint
name|preview_size
decl_stmt|;
DECL|member|nav_preview_size
name|gint
name|nav_preview_size
decl_stmt|;
DECL|member|show_rulers
name|gboolean
name|show_rulers
decl_stmt|;
DECL|member|show_statusbar
name|gboolean
name|show_statusbar
decl_stmt|;
DECL|member|auto_save
name|gboolean
name|auto_save
decl_stmt|;
DECL|member|confirm_on_close
name|gboolean
name|confirm_on_close
decl_stmt|;
DECL|member|default_dot_for_dot
name|gboolean
name|default_dot_for_dot
decl_stmt|;
DECL|member|save_session_info
name|gboolean
name|save_session_info
decl_stmt|;
DECL|member|save_device_status
name|gboolean
name|save_device_status
decl_stmt|;
DECL|member|always_restore_session
name|gboolean
name|always_restore_session
decl_stmt|;
DECL|member|show_tips
name|gboolean
name|show_tips
decl_stmt|;
DECL|member|last_tip
name|gint
name|last_tip
decl_stmt|;
DECL|member|show_tool_tips
name|gboolean
name|show_tool_tips
decl_stmt|;
DECL|member|monitor_xres
name|gdouble
name|monitor_xres
decl_stmt|;
DECL|member|monitor_yres
name|gdouble
name|monitor_yres
decl_stmt|;
DECL|member|using_xserver_resolution
name|gboolean
name|using_xserver_resolution
decl_stmt|;
DECL|member|image_title_format
name|gchar
modifier|*
name|image_title_format
decl_stmt|;
DECL|member|global_paint_options
name|gboolean
name|global_paint_options
decl_stmt|;
DECL|member|show_indicators
name|gboolean
name|show_indicators
decl_stmt|;
DECL|member|max_new_image_size
name|guint
name|max_new_image_size
decl_stmt|;
DECL|member|trust_dirty_flag
name|gboolean
name|trust_dirty_flag
decl_stmt|;
DECL|member|use_help
name|gboolean
name|use_help
decl_stmt|;
DECL|member|nav_window_per_display
name|gboolean
name|nav_window_per_display
decl_stmt|;
DECL|member|info_window_follows_mouse
name|gboolean
name|info_window_follows_mouse
decl_stmt|;
DECL|member|help_browser
name|gint
name|help_browser
decl_stmt|;
DECL|member|cursor_mode
name|gint
name|cursor_mode
decl_stmt|;
DECL|member|disable_tearoff_menus
name|gboolean
name|disable_tearoff_menus
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
block|}
struct|;
end_struct

begin_decl_stmt
specifier|extern
name|GimpRc
name|gimprc
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* this has to be called before any file is parsed  */
end_comment

begin_function_decl
name|gboolean
name|gimprc_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimprc_parse
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|cmdline_system_gimprc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|cmdline_gimprc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimprc_save
parameter_list|(
name|GList
modifier|*
modifier|*
name|updated_options
parameter_list|,
name|GList
modifier|*
modifier|*
name|conflicting_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimprc_parse_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimprc_find_token
parameter_list|(
specifier|const
name|gchar
modifier|*
name|token
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimprc_value_to_str
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|save_gimprc_strings
parameter_list|(
specifier|const
name|gchar
modifier|*
name|token
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMPRC_H__  */
end_comment

end_unit

