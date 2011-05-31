begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpwidgets-utils.h  * Copyright (C) 1999-2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WIDGETS_UTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WIDGETS_UTILS_H__
define|#
directive|define
name|__GIMP_WIDGETS_UTILS_H__
end_define

begin_function_decl
name|void
name|gimp_menu_position
parameter_list|(
name|GtkMenu
modifier|*
name|menu
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_button_menu_position
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GtkMenu
modifier|*
name|menu
parameter_list|,
name|GtkPositionType
name|position
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_table_attach_stock
parameter_list|(
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|colspan
parameter_list|,
name|gboolean
name|left_align
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_enum_radio_box_add
parameter_list|(
name|GtkBox
modifier|*
name|box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|enum_value
parameter_list|,
name|gboolean
name|below
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_enum_radio_frame_add
parameter_list|(
name|GtkFrame
modifier|*
name|frame
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|enum_value
parameter_list|,
name|gboolean
name|below
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkIconSize
name|gimp_get_icon_size
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
name|GtkIconSize
name|max_size
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTabStyle
name|gimp_preview_tab_style_to_icon
parameter_list|(
name|GimpTabStyle
name|tab_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_get_mod_name_shift
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_get_mod_name_control
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_get_mod_name_alt
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_get_mod_separator
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_get_mod_string
parameter_list|(
name|GdkModifierType
name|modifiers
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_suggest_modifiers
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|GdkModifierType
name|modifiers
parameter_list|,
specifier|const
name|gchar
modifier|*
name|shift_format
parameter_list|,
specifier|const
name|gchar
modifier|*
name|control_format
parameter_list|,
specifier|const
name|gchar
modifier|*
name|alt_format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_get_screen_resolution
parameter_list|(
name|GdkScreen
modifier|*
name|screen
parameter_list|,
name|gdouble
modifier|*
name|xres
parameter_list|,
name|gdouble
modifier|*
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_get_gdk_color
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|GdkColor
modifier|*
name|gdk_color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_set_gdk_color
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GdkColor
modifier|*
name|gdk_color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_window_set_hint
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|GimpWindowHint
name|hint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint32
name|gimp_window_get_native_id
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_window_set_transient_for
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|guint32
name|parent_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_toggle_button_set_visible
parameter_list|(
name|GtkToggleButton
modifier|*
name|toggle
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_widget_set_accel_help
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_get_message_stock_id
parameter_list|(
name|GimpMessageSeverity
name|severity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pango_layout_set_scale
parameter_list|(
name|PangoLayout
modifier|*
name|layout
parameter_list|,
name|double
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pango_layout_set_weight
parameter_list|(
name|PangoLayout
modifier|*
name|layout
parameter_list|,
name|PangoWeight
name|weight
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_highlight_widget
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|highlight
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dock_with_window_new
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GdkScreen
modifier|*
name|screen
parameter_list|,
name|gboolean
name|toolbox
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_tools_get_tool_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tools_set_tool_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_widget_flush_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_print_event
parameter_list|(
specifier|const
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_write_position
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_WIDGETS_UTILS_H__ */
end_comment

end_unit

