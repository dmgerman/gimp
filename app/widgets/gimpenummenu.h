begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpenummenu.h  * Copyright (C) 2002  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ENUM_MENU_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ENUM_MENU_H__
define|#
directive|define
name|__GIMP_ENUM_MENU_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkmenu.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_ENUM_MENU
define|#
directive|define
name|GIMP_TYPE_ENUM_MENU
value|(gimp_enum_menu_get_type ())
end_define

begin_define
DECL|macro|GIMP_ENUM_MENU (obj)
define|#
directive|define
name|GIMP_ENUM_MENU
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ENUM_MENU, GimpEnumMenu))
end_define

begin_define
DECL|macro|GIMP_ENUM_MENU_CLASS (klass)
define|#
directive|define
name|GIMP_ENUM_MENU_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ENUM_MENU, GimpEnumMenuClass))
end_define

begin_define
DECL|macro|GIMP_IS_ENUM_MENU (obj)
define|#
directive|define
name|GIMP_IS_ENUM_MENU
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ENUM_MENU))
end_define

begin_define
DECL|macro|GIMP_IS_ENUM_MENU_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ENUM_MENU_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ENUM_MENU))
end_define

begin_define
DECL|macro|GIMP_ENUM_MENU_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ENUM_MENU_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ENUM_MENU, GimpEnumMenuClass))
end_define

begin_typedef
DECL|typedef|GimpEnumMenuClass
typedef|typedef
name|struct
name|_GimpEnumMenuClass
name|GimpEnumMenuClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEnumMenuClass
struct|struct
name|_GimpEnumMenuClass
block|{
DECL|member|parent_instance
name|GtkMenuClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpEnumMenu
struct|struct
name|_GimpEnumMenu
block|{
DECL|member|parent_instance
name|GtkMenu
name|parent_instance
decl_stmt|;
DECL|member|enum_class
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_enum_menu_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_enum_menu_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_enum_option_menu_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_enum_radio_box_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|first_button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_enum_radio_frame_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GtkWidget
modifier|*
name|label_widget
parameter_list|,
name|gint
name|border_width
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|first_button
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ENUM_MENU_H__ */
end_comment

end_unit

