begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpoldwidgets.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  These functions are deprecated and should not be used in newly  *  written code.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

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
name|__GIMP_OLD_WIDGETS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OLD_WIDGETS_H__
define|#
directive|define
name|__GIMP_OLD_WIDGETS_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/*  *  Widget Constructors  */
name|GtkWidget
modifier|*
name|gimp_int_option_menu_new
argument_list|(
name|gboolean
name|menu_only
argument_list|,
name|GCallback
name|menu_item_callback
argument_list|,
name|gpointer
name|menu_item_callback_data
argument_list|,
name|gint
name|initial
argument_list|,
comment|/* item_data */
comment|/* specify menu items as va_list:                                                *  gchar      *label,                                                *  gint        item_data,                                                *  GtkWidget **widget_ptr,                                                */
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_int_option_menu_set_history
parameter_list|(
name|GtkOptionMenu
modifier|*
name|option_menu
parameter_list|,
name|gint
name|item_data
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|GimpIntOptionMenuSensitivityCallback
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpIntOptionMenuSensitivityCallback
function_decl|)
parameter_list|(
name|gint
name|item_data
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_int_option_menu_set_sensitive
parameter_list|(
name|GtkOptionMenu
modifier|*
name|option_menu
parameter_list|,
name|GimpIntOptionMenuSensitivityCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GtkWidget
modifier|*
name|gimp_option_menu_new
argument_list|(
name|gboolean
name|menu_only
argument_list|,
comment|/* specify menu items as va_list:                                        *  gchar       *label,                                        *  GCallback    callback,                                        *  gpointer     callback_data,                                        *  gpointer     item_data,                                        *  GtkWidget  **widget_ptr,                                        *  gboolean     active                                        */
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GtkWidget
modifier|*
name|gimp_option_menu_new2
argument_list|(
name|gboolean
name|menu_only
argument_list|,
name|GCallback
name|menu_item_callback
argument_list|,
name|gpointer
name|menu_item_callback_data
argument_list|,
name|gpointer
name|initial
argument_list|,
comment|/* item_data */
comment|/* specify menu items as va_list:                                        *  gchar        *label,                                        *  gpointer      item_data,                                        *  GtkWidget   **widget_ptr,                                        */
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_option_menu_set_history
parameter_list|(
name|GtkOptionMenu
modifier|*
name|option_menu
parameter_list|,
name|gpointer
name|item_data
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|GimpOptionMenuSensitivityCallback
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpOptionMenuSensitivityCallback
function_decl|)
parameter_list|(
name|gpointer
name|item_data
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_option_menu_set_sensitive
parameter_list|(
name|GtkOptionMenu
modifier|*
name|option_menu
parameter_list|,
name|GimpOptionMenuSensitivityCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_menu_item_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
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
comment|/* __GIMP_OLD_WIDGETS_H__ */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  GIMP_DISABLE_DEPRECATED  */
end_comment

end_unit

