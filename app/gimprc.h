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

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_comment
comment|/*  global gimprc variables  */
end_comment

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|plug_in_path
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|temp_path
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|swap_path
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|brush_path
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|brush_vbr_path
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|default_brush
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|pattern_path
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|default_pattern
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|palette_path
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|default_palette
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|gradient_path
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|default_gradient
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|pluginrc_path
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|module_path
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|tile_cache_size
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|marching_speed
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|last_opened_size
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gdouble
name|gamma_val
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|transparency_type
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|perfectmouse
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|transparency_size
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|levels_of_undo
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|color_cube_shades
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|install_cmap
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|cycled_marching_ants
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|default_threshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|stingy_memory_use
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|allow_resize_windows
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|no_cursor_updating
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|preview_size
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|nav_preview_size
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|show_rulers
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpUnit
name|default_units
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|show_statusbar
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|auto_save
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|InterpolationType
name|interpolation_type
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|confirm_on_close
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|default_width
decl_stmt|,
name|default_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|default_type
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpUnit
name|default_resolution_units
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gdouble
name|default_xresolution
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gdouble
name|default_yresolution
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|default_comment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|default_dot_for_dot
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|save_session_info
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|save_device_status
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|always_restore_session
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|show_tips
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|last_tip
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|show_tool_tips
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gdouble
name|monitor_xres
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gdouble
name|monitor_yres
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|using_xserver_resolution
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|num_processors
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|image_title_format
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|global_paint_options
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|show_indicators
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|max_new_image_size
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|thumbnail_mode
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|trust_dirty_flag
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|use_help
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|nav_window_per_display
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|info_window_follows_mouse
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|help_browser
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  function prototypes  */
end_comment

begin_function_decl
name|gboolean
name|parse_buffers_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* this has to be called before any file 					 * is parsed 					 */
end_comment

begin_function_decl
name|void
name|parse_gimprc
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|parse_gimprc_file
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|save_gimprc
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
name|gchar
modifier|*
name|gimprc_find_token
parameter_list|(
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
name|gchar
modifier|*
name|token
parameter_list|,
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

