begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpui.h  * Copyright (C) 1999 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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

begin_typedef
DECL|typedef|GimpGetAccelContextFunc
typedef|typedef
name|gpointer
function_decl|(
modifier|*
name|GimpGetAccelContextFunc
function_decl|)
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_message_box
parameter_list|(
name|gchar
modifier|*
name|message
parameter_list|,
name|GtkCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_menu_position
parameter_list|(
name|GtkMenu
modifier|*
name|menu
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|guint
modifier|*
name|button
parameter_list|,
name|guint32
modifier|*
name|activate_time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_window_add_accel_group
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|GtkItemFactory
modifier|*
name|item_factory
parameter_list|,
name|GimpGetAccelContextFunc
name|get_context_func
parameter_list|,
name|gpointer
name|get_context_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_window_remove_accel_group
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|GtkItemFactory
modifier|*
name|item_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|gimp_widget_get_callback_context
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_WIDGETS_UTILS_H__ */
end_comment

end_unit

