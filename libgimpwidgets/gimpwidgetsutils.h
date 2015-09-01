begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwidgetsutils.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_WIDGETS_UTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WIDGETS_UTILS_H__
define|#
directive|define
name|__GIMP_WIDGETS_UTILS_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|GtkWidget
modifier|*
name|gimp_table_attach_aligned
parameter_list|(
name|GtkTable
modifier|*
name|table
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
name|label_text
parameter_list|,
name|gfloat
name|xalign
parameter_list|,
name|gfloat
name|yalign
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
name|gimp_label_set_attributes
parameter_list|(
name|GtkLabel
modifier|*
name|label
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_widget_get_monitor
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_get_monitor_at_pointer
parameter_list|(
name|GdkScreen
modifier|*
modifier|*
name|screen
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_widget_get_color_profile
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorTransform
name|gimp_widget_get_color_transform
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|,
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
specifier|const
name|Babl
modifier|*
modifier|*
name|src_format
parameter_list|,
specifier|const
name|Babl
modifier|*
modifier|*
name|dest_format
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
comment|/* __GIMP_WIDGETS_UTILS_H__ */
end_comment

end_unit

