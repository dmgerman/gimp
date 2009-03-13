begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDisplayConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_CONFIG_H__
define|#
directive|define
name|__GIMP_DISPLAY_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"display/display-enums.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_define
DECL|macro|GIMP_CONFIG_DEFAULT_IMAGE_TITLE_FORMAT
define|#
directive|define
name|GIMP_CONFIG_DEFAULT_IMAGE_TITLE_FORMAT
value|"%D*%f-%p.%i (%t, %L) %wx%h"
end_define

begin_define
DECL|macro|GIMP_CONFIG_DEFAULT_IMAGE_STATUS_FORMAT
define|#
directive|define
name|GIMP_CONFIG_DEFAULT_IMAGE_STATUS_FORMAT
value|"%n (%m)"
end_define

begin_define
DECL|macro|GIMP_TYPE_DISPLAY_CONFIG
define|#
directive|define
name|GIMP_TYPE_DISPLAY_CONFIG
value|(gimp_display_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_DISPLAY_CONFIG (obj)
define|#
directive|define
name|GIMP_DISPLAY_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DISPLAY_CONFIG, GimpDisplayConfig))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_DISPLAY_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DISPLAY_CONFIG, GimpDisplayConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_DISPLAY_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DISPLAY_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DISPLAY_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DISPLAY_CONFIG))
end_define

begin_typedef
DECL|typedef|GimpDisplayConfigClass
typedef|typedef
name|struct
name|_GimpDisplayConfigClass
name|GimpDisplayConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDisplayConfig
struct|struct
name|_GimpDisplayConfig
block|{
DECL|member|parent_instance
name|GimpCoreConfig
name|parent_instance
decl_stmt|;
DECL|member|transparency_size
name|GimpCheckSize
name|transparency_size
decl_stmt|;
DECL|member|transparency_type
name|GimpCheckType
name|transparency_type
decl_stmt|;
DECL|member|snap_distance
name|gint
name|snap_distance
decl_stmt|;
DECL|member|marching_ants_speed
name|gint
name|marching_ants_speed
decl_stmt|;
DECL|member|resize_windows_on_zoom
name|gboolean
name|resize_windows_on_zoom
decl_stmt|;
DECL|member|resize_windows_on_resize
name|gboolean
name|resize_windows_on_resize
decl_stmt|;
DECL|member|default_dot_for_dot
name|gboolean
name|default_dot_for_dot
decl_stmt|;
DECL|member|initial_zoom_to_fit
name|gboolean
name|initial_zoom_to_fit
decl_stmt|;
DECL|member|perfect_mouse
name|gboolean
name|perfect_mouse
decl_stmt|;
DECL|member|cursor_mode
name|GimpCursorMode
name|cursor_mode
decl_stmt|;
DECL|member|cursor_updating
name|gboolean
name|cursor_updating
decl_stmt|;
DECL|member|show_brush_outline
name|gboolean
name|show_brush_outline
decl_stmt|;
DECL|member|show_paint_tool_cursor
name|gboolean
name|show_paint_tool_cursor
decl_stmt|;
DECL|member|image_title_format
name|gchar
modifier|*
name|image_title_format
decl_stmt|;
DECL|member|image_status_format
name|gchar
modifier|*
name|image_status_format
decl_stmt|;
DECL|member|confirm_on_close
name|gboolean
name|confirm_on_close
decl_stmt|;
DECL|member|monitor_xres
name|gdouble
name|monitor_xres
decl_stmt|;
DECL|member|monitor_yres
name|gdouble
name|monitor_yres
decl_stmt|;
DECL|member|monitor_res_from_gdk
name|gboolean
name|monitor_res_from_gdk
decl_stmt|;
DECL|member|nav_preview_size
name|GimpViewSize
name|nav_preview_size
decl_stmt|;
DECL|member|default_view
name|GimpDisplayOptions
modifier|*
name|default_view
decl_stmt|;
DECL|member|default_fullscreen_view
name|GimpDisplayOptions
modifier|*
name|default_fullscreen_view
decl_stmt|;
DECL|member|default_snap_to_guides
name|gboolean
name|default_snap_to_guides
decl_stmt|;
DECL|member|default_snap_to_grid
name|gboolean
name|default_snap_to_grid
decl_stmt|;
DECL|member|default_snap_to_canvas
name|gboolean
name|default_snap_to_canvas
decl_stmt|;
DECL|member|default_snap_to_path
name|gboolean
name|default_snap_to_path
decl_stmt|;
DECL|member|activate_on_focus
name|gboolean
name|activate_on_focus
decl_stmt|;
DECL|member|space_bar_action
name|GimpSpaceBarAction
name|space_bar_action
decl_stmt|;
DECL|member|xor_color
name|GimpRGB
name|xor_color
decl_stmt|;
DECL|member|zoom_quality
name|GimpZoomQuality
name|zoom_quality
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDisplayConfigClass
struct|struct
name|_GimpDisplayConfigClass
block|{
DECL|member|parent_class
name|GimpCoreConfigClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_display_config_get_type
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
comment|/* GIMP_DISPLAY_CONFIG_H__ */
end_comment

end_unit

