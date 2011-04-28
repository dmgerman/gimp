begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmenu.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_MENU_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MENU_H__
define|#
directive|define
name|__GIMP_MENU_H__
end_define

begin_comment
comment|/*  These functions are deprecated and should not be used in newly  *  written code.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|GimpConstraintFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpConstraintFunc
function_decl|)
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpMenuCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpMenuCallback
function_decl|)
parameter_list|(
name|gint32
name|any_id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_image_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_layer_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_channel_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_drawable_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_drawable
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
comment|/*  GIMP_DISABLE_DEPRECATED  */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MENU_H__ */
end_comment

end_unit

