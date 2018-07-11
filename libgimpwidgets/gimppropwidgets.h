begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppropwidgets.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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

begin_function_decl
name|G_BEGIN_DECLS
comment|/*  GParamBoolean  */
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
name|gimp_prop_boolean_combo_box_new
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

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_boolean_radio_frame_new
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

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_expander_new
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

begin_comment
comment|/*  GParamInt  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_int_combo_box_new
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
name|GimpIntStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GParamGType  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_pointer_combo_box_new
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
name|GimpIntStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GParamEnum  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_enum_combo_box_new
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

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_enum_check_button_new
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
name|gint
name|false_value
parameter_list|,
name|gint
name|true_value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_enum_radio_frame_new
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
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_enum_radio_box_new
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

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_enum_icon_box_new
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
name|icon_prefix
parameter_list|,
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_enum_label_new
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

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_hscale_new
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

begin_function_decl
name|GtkAdjustment
modifier|*
name|gimp_prop_scale_entry_new
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
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|column
parameter_list|,
name|gint
name|row
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
parameter_list|,
name|gboolean
name|limit_scale
parameter_list|,
name|gdouble
name|lower_limit
parameter_list|,
name|gdouble
name|upper_limit
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  special form of gimp_prop_scale_entry_new() for GParamDouble  */
end_comment

begin_function_decl
name|GtkAdjustment
modifier|*
name|gimp_prop_opacity_entry_new
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
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|column
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
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
name|gimp_prop_label_new
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
name|gimp_prop_string_combo_box_new
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
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|gint
name|id_column
parameter_list|,
name|gint
name|label_column
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GimpParamPath  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_file_chooser_button_new
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
name|GtkFileChooserAction
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_file_chooser_button_new_with_dialog
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
name|GtkWidget
modifier|*
name|dialog
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
name|path_property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|writable_property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filesel_title
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GParamInt, GParamUInt, GParamDouble   unit: GimpParamUnit  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_size_entry_new
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
name|property_is_pixel
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
name|resolution
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

begin_function_decl
name|gboolean
name|gimp_prop_coordinates_connect
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
name|GtkWidget
modifier|*
name|sizeentry
parameter_list|,
name|GtkWidget
modifier|*
name|chainbutton
parameter_list|,
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GimpParamColor  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_color_area_new
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
name|gimp_prop_unit_combo_box_new
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
comment|/*  GParamString (icon name)  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_icon_image_new
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
name|GtkIconSize
name|icon_size
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROP_WIDGETS_H__ */
end_comment

end_unit

