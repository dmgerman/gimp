begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropwidgets.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_APP_PROP_WIDGETS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_APP_PROP_WIDGETS_H__
define|#
directive|define
name|__GIMP_APP_PROP_WIDGETS_H__
end_define

begin_comment
comment|/*  GParamBoolean  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_expanding_frame_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|button_label
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GParamEnum  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_paint_mode_menu_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|gboolean
name|with_behind_mode
parameter_list|,
name|gboolean
name|with_replace_modes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GimpParamColor  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_color_button_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GParamDouble  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_scale_button_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_spin_scale_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|gdouble
name|step_increment
parameter_list|,
name|gdouble
name|page_increment
parameter_list|,
name|gint
name|digits
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GParamObject (GimpViewable)  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_view_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GParamDouble, GParamDouble, GParamDouble, GParamDouble, GParamBoolean  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_number_pair_entry_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|left_number_property
parameter_list|,
specifier|const
name|gchar
modifier|*
name|right_number_property
parameter_list|,
specifier|const
name|gchar
modifier|*
name|default_left_number_property
parameter_list|,
specifier|const
name|gchar
modifier|*
name|default_right_number_property
parameter_list|,
specifier|const
name|gchar
modifier|*
name|user_override_property
parameter_list|,
name|gboolean
name|connect_numbers_changed
parameter_list|,
name|gboolean
name|connect_ratio_changed
parameter_list|,
specifier|const
name|gchar
modifier|*
name|separators
parameter_list|,
name|gboolean
name|allow_simplification
parameter_list|,
name|gdouble
name|min_valid_value
parameter_list|,
name|gdouble
name|max_valid_value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GParamString  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_language_combo_box_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_language_entry_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  A view on all of an object's properties  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_table_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GType
name|owner_type
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_APP_PROP_WIDGETS_H__ */
end_comment

end_unit

