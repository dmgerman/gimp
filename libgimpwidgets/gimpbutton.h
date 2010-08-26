begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbutton.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BUTTON_H__
define|#
directive|define
name|__GIMP_BUTTON_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_BUTTON
define|#
directive|define
name|GIMP_TYPE_BUTTON
value|(gimp_button_get_type ())
end_define

begin_define
DECL|macro|GIMP_BUTTON (obj)
define|#
directive|define
name|GIMP_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BUTTON, GimpButton))
end_define

begin_define
DECL|macro|GIMP_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BUTTON, GimpButtonClass))
end_define

begin_define
DECL|macro|GIMP_IS_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BUTTON))
end_define

begin_define
DECL|macro|GIMP_IS_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BUTTON))
end_define

begin_define
DECL|macro|GIMP_BUTTON_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BUTTON_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BUTTON, GimpButtonClass))
end_define

begin_typedef
DECL|typedef|GimpButtonClass
typedef|typedef
name|struct
name|_GimpButtonClass
name|GimpButtonClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpButton
struct|struct
name|_GimpButton
block|{
DECL|member|parent_instance
name|GtkButton
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|press_state
name|GdkModifierType
name|press_state
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpButtonClass
struct|struct
name|_GimpButtonClass
block|{
DECL|member|parent_class
name|GtkButtonClass
name|parent_class
decl_stmt|;
DECL|member|extended_clicked
name|void
function_decl|(
modifier|*
name|extended_clicked
function_decl|)
parameter_list|(
name|GimpButton
modifier|*
name|button
parameter_list|,
name|GdkModifierType
name|modifier_state
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
name|gimp_button_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_button_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_button_extended_clicked
parameter_list|(
name|GimpButton
modifier|*
name|button
parameter_list|,
name|GdkModifierType
name|state
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
comment|/* __GIMP_BUTTON_H__ */
end_comment

end_unit

