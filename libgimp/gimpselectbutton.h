begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpselectbutton.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_SELECT_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SELECT_BUTTON_H__
define|#
directive|define
name|__GIMP_SELECT_BUTTON_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_SELECT_BUTTON
define|#
directive|define
name|GIMP_TYPE_SELECT_BUTTON
value|(gimp_select_button_get_type ())
end_define

begin_define
DECL|macro|GIMP_SELECT_BUTTON (obj)
define|#
directive|define
name|GIMP_SELECT_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SELECT_BUTTON, GimpSelectButton))
end_define

begin_define
DECL|macro|GIMP_SELECT_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_SELECT_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SELECT_BUTTON, GimpSelectButtonClass))
end_define

begin_define
DECL|macro|GIMP_IS_SELECT_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_SELECT_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SELECT_BUTTON))
end_define

begin_define
DECL|macro|GIMP_IS_SELECT_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SELECT_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SELECT_BUTTON))
end_define

begin_define
DECL|macro|GIMP_SELECT_BUTTON_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SELECT_BUTTON_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SELECT_BUTTON, GimpSelectButtonClass))
end_define

begin_typedef
DECL|typedef|GimpSelectButtonClass
typedef|typedef
name|struct
name|_GimpSelectButtonClass
name|GimpSelectButtonClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSelectButton
struct|struct
name|_GimpSelectButton
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|temp_callback
specifier|const
name|gchar
modifier|*
name|temp_callback
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSelectButtonClass
struct|struct
name|_GimpSelectButtonClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
DECL|member|default_title
name|gchar
modifier|*
name|default_title
decl_stmt|;
DECL|member|select_destroy
name|void
function_decl|(
modifier|*
name|select_destroy
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|callback
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
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_select_button_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_select_button_close_popup
parameter_list|(
name|GimpSelectButton
modifier|*
name|button
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
comment|/* __GIMP_SELECT_BUTTON_H__ */
end_comment

end_unit

