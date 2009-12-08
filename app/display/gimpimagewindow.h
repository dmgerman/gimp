begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_WINDOW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_WINDOW_H__
define|#
directive|define
name|__GIMP_IMAGE_WINDOW_H__
end_define

begin_include
include|#
directive|include
file|"widgets/gimpwindow.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGE_WINDOW
define|#
directive|define
name|GIMP_TYPE_IMAGE_WINDOW
value|(gimp_image_window_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE_WINDOW (obj)
define|#
directive|define
name|GIMP_IMAGE_WINDOW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE_WINDOW, GimpImageWindow))
end_define

begin_define
DECL|macro|GIMP_IMAGE_WINDOW_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_WINDOW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_WINDOW, GimpImageWindowClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_WINDOW (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_WINDOW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE_WINDOW))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_WINDOW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_WINDOW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_WINDOW))
end_define

begin_define
DECL|macro|GIMP_IMAGE_WINDOW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_WINDOW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE_WINDOW, GimpImageWindowClass))
end_define

begin_typedef
DECL|typedef|GimpImageWindowClass
typedef|typedef
name|struct
name|_GimpImageWindowClass
name|GimpImageWindowClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImageWindow
struct|struct
name|_GimpImageWindow
block|{
DECL|member|parent_instance
name|GimpWindow
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImageWindowClass
struct|struct
name|_GimpImageWindowClass
block|{
DECL|member|parent_class
name|GimpWindowClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_image_window_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpImageWindow
modifier|*
name|gimp_image_window_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
name|GimpDialogFactory
modifier|*
name|display_factory
parameter_list|,
name|GimpDialogFactory
modifier|*
name|dock_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_window_destroy
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUIManager
modifier|*
name|gimp_image_window_get_ui_manager
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDialogFactory
modifier|*
name|gimp_image_window_get_dock_factory
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDockColumns
modifier|*
name|gimp_image_window_get_left_docks
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDockColumns
modifier|*
name|gimp_image_window_get_right_docks
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_window_add_shell
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDisplayShell
modifier|*
name|gimp_image_window_get_shell
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_window_remove_shell
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_window_get_n_shells
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_window_set_active_shell
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDisplayShell
modifier|*
name|gimp_image_window_get_active_shell
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_window_set_fullscreen
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|gboolean
name|fullscreen
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_window_get_fullscreen
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_window_set_show_menubar
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_window_get_show_menubar
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_window_set_show_statusbar
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_window_get_show_statusbar
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_window_set_show_docks
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_window_get_show_docks
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_window_is_iconified
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_window_shrink_wrap
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|gboolean
name|grow_only
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_WINDOW_H__ */
end_comment

end_unit

