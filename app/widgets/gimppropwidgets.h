begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropwidgets.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROP_WIDGETS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROP_WIDGETS_H__
define|#
directive|define
name|__GIMP_PROP_WIDGETS_H__
end_define

begin_comment
comment|/*  GParamBoolean  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_check_button_new
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_boolean_option_menu_new
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
name|true_text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|false_text
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GParamEnum  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_enum_option_menu_new
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
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GParamInt, GParamUInt, GParamLong, GParamULong, GParamDouble  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_spin_button_new
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
comment|/*  GimpParamMemsize  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_memsize_entry_new
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
comment|/*  GParamString  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_entry_new
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
name|gint
name|max_len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkTextBuffer
modifier|*
name|gimp_prop_text_buffer_new
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
name|gint
name|max_len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_font_selection_new
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
comment|/*  GimpParamPath  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_file_entry_new
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
name|filesel_title
parameter_list|,
name|gboolean
name|dir_only
parameter_list|,
name|gboolean
name|check_valid
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_path_editor_new
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
name|filesel_title
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  x,y: GParamInt, GParamDouble   unit: GimpParamUnit  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_coordinates_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|x_property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|y_property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|unit_property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|unit_format
parameter_list|,
name|GimpSizeEntryUpdatePolicy
name|update_policy
parameter_list|,
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|,
name|gboolean
name|has_chainbutton
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
comment|/*  GimpParamUnit  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_unit_menu_new
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
name|unit_format
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROP_WIDGETS_H__ */
end_comment

end_unit

