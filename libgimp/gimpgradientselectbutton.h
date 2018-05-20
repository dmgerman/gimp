begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpgradientselectbutton.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_UI_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimpui.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GRADIENT_SELECT_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GRADIENT_SELECT_BUTTON_H__
define|#
directive|define
name|__GIMP_GRADIENT_SELECT_BUTTON_H__
end_define

begin_include
include|#
directive|include
file|<libgimp/gimpselectbutton.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_GRADIENT_SELECT_BUTTON
define|#
directive|define
name|GIMP_TYPE_GRADIENT_SELECT_BUTTON
value|(gimp_gradient_select_button_get_type ())
end_define

begin_define
DECL|macro|GIMP_GRADIENT_SELECT_BUTTON (obj)
define|#
directive|define
name|GIMP_GRADIENT_SELECT_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_GRADIENT_SELECT_BUTTON, GimpGradientSelectButton))
end_define

begin_define
DECL|macro|GIMP_GRADIENT_SELECT_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_GRADIENT_SELECT_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_GRADIENT_SELECT_BUTTON, GimpGradientSelectButtonClass))
end_define

begin_define
DECL|macro|GIMP_IS_GRADIENT_SELECT_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_GRADIENT_SELECT_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_GRADIENT_SELECT_BUTTON))
end_define

begin_define
DECL|macro|GIMP_IS_GRADIENT_SELECT_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_GRADIENT_SELECT_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_GRADIENT_SELECT_BUTTON))
end_define

begin_define
DECL|macro|GIMP_GRADIENT_SELECT_BUTTON_GET_CLASS (obj)
define|#
directive|define
name|GIMP_GRADIENT_SELECT_BUTTON_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_GRADIENT_SELECT_BUTTON, GimpGradientSelectButtonClass))
end_define

begin_typedef
DECL|typedef|GimpGradientSelectButtonPrivate
typedef|typedef
name|struct
name|_GimpGradientSelectButtonPrivate
name|GimpGradientSelectButtonPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGradientSelectButtonClass
typedef|typedef
name|struct
name|_GimpGradientSelectButtonClass
name|GimpGradientSelectButtonClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGradientSelectButton
struct|struct
name|_GimpGradientSelectButton
block|{
DECL|member|parent_instance
name|GimpSelectButton
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpGradientSelectButtonClass
struct|struct
name|_GimpGradientSelectButtonClass
block|{
DECL|member|parent_class
name|GimpSelectButtonClass
name|parent_class
decl_stmt|;
comment|/* gradient_set signal is emitted when gradient is chosen */
DECL|member|gradient_set
name|void
function_decl|(
modifier|*
name|gradient_set
function_decl|)
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|,
name|gint
name|width
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|gradient_data
parameter_list|,
name|gboolean
name|dialog_closing
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
DECL|member|_gimp_reserved5
name|void
function_decl|(
modifier|*
name|_gimp_reserved5
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved6
name|void
function_decl|(
modifier|*
name|_gimp_reserved6
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved7
name|void
function_decl|(
modifier|*
name|_gimp_reserved7
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved8
name|void
function_decl|(
modifier|*
name|_gimp_reserved8
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
name|gimp_gradient_select_button_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_gradient_select_button_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_gradient_select_button_get_gradient
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gradient_select_button_set_gradient
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
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
comment|/* __GIMP_GRADIENT_SELECT_BUTTON_H__ */
end_comment

end_unit

