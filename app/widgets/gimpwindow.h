begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpwindow.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WINDOW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WINDOW_H__
define|#
directive|define
name|__GIMP_WINDOW_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_WINDOW
define|#
directive|define
name|GIMP_TYPE_WINDOW
value|(gimp_window_get_type ())
end_define

begin_define
DECL|macro|GIMP_WINDOW (obj)
define|#
directive|define
name|GIMP_WINDOW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_WINDOW, GimpWindow))
end_define

begin_define
DECL|macro|GIMP_WINDOW_CLASS (klass)
define|#
directive|define
name|GIMP_WINDOW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_WINDOW, GimpWindowClass))
end_define

begin_define
DECL|macro|GIMP_IS_WINDOW (obj)
define|#
directive|define
name|GIMP_IS_WINDOW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_WINDOW))
end_define

begin_define
DECL|macro|GIMP_IS_WINDOW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_WINDOW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_WINDOW))
end_define

begin_define
DECL|macro|GIMP_WINDOW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_WINDOW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_WINDOW, GimpWindowClass))
end_define

begin_typedef
DECL|typedef|GimpWindowClass
typedef|typedef
name|struct
name|_GimpWindowClass
name|GimpWindowClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpWindow
struct|struct
name|_GimpWindow
block|{
DECL|member|parent_instance
name|GtkWindow
name|parent_instance
decl_stmt|;
DECL|member|primary_focus_widget
name|GtkWidget
modifier|*
name|primary_focus_widget
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpWindowClass
struct|struct
name|_GimpWindowClass
block|{
DECL|member|parent_class
name|GtkWindowClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_window_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_window_set_primary_focus_widget
parameter_list|(
name|GimpWindow
modifier|*
name|window
parameter_list|,
name|GtkWidget
modifier|*
name|primary_focus
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_window_get_primary_focus_widget
parameter_list|(
name|GimpWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_WINDOW_H__ */
end_comment

end_unit

