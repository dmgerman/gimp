begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorselection.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_COLOR_SELECTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_SELECTION_H__
define|#
directive|define
name|__GIMP_COLOR_SELECTION_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look at the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_COLOR_SELECTION
define|#
directive|define
name|GIMP_TYPE_COLOR_SELECTION
value|(gimp_color_selection_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_SELECTION (obj)
define|#
directive|define
name|GIMP_COLOR_SELECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_SELECTION, GimpColorSelection))
end_define

begin_define
DECL|macro|GIMP_COLOR_SELECTION_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_SELECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_SELECTION, GimpColorSelectionClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_SELECTION (obj)
define|#
directive|define
name|GIMP_IS_COLOR_SELECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_SELECTION))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_SELECTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_SELECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_SELECTION))
end_define

begin_define
DECL|macro|GIMP_COLOR_SELECTION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_SELECTION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_SELECTION, GimpColorSelectionClass))
end_define

begin_typedef
DECL|typedef|GimpColorSelectionClass
typedef|typedef
name|struct
name|_GimpColorSelectionClass
name|GimpColorSelectionClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorSelection
struct|struct
name|_GimpColorSelection
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|show_alpha
name|gboolean
name|show_alpha
decl_stmt|;
DECL|member|hsv
name|GimpHSV
name|hsv
decl_stmt|;
DECL|member|rgb
name|GimpRGB
name|rgb
decl_stmt|;
DECL|member|channel
name|GimpColorSelectorChannel
name|channel
decl_stmt|;
DECL|member|left_vbox
name|GtkWidget
modifier|*
name|left_vbox
decl_stmt|;
DECL|member|right_vbox
name|GtkWidget
modifier|*
name|right_vbox
decl_stmt|;
DECL|member|notebook
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
DECL|member|scales
name|GtkWidget
modifier|*
name|scales
decl_stmt|;
DECL|member|new_color
name|GtkWidget
modifier|*
name|new_color
decl_stmt|;
DECL|member|old_color
name|GtkWidget
modifier|*
name|old_color
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorSelectionClass
struct|struct
name|_GimpColorSelectionClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
DECL|member|color_changed
name|void
function_decl|(
modifier|*
name|color_changed
function_decl|)
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_selection_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_selection_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selection_set_show_alpha
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_color_selection_get_show_alpha
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selection_set_color
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selection_get_color
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selection_set_old_color
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selection_get_old_color
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selection_reset
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selection_color_changed
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selection_set_config
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
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
comment|/* __GIMP_COLOR_SELECTION_H__ */
end_comment

end_unit

