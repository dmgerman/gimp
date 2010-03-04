begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockwindow.h  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  * Copyright (C)      2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DOCK_WINDOW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DOCK_WINDOW_H__
define|#
directive|define
name|__GIMP_DOCK_WINDOW_H__
end_define

begin_include
include|#
directive|include
file|"widgets/gimpwindow.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DOCK_WINDOW
define|#
directive|define
name|GIMP_TYPE_DOCK_WINDOW
value|(gimp_dock_window_get_type ())
end_define

begin_define
DECL|macro|GIMP_DOCK_WINDOW (obj)
define|#
directive|define
name|GIMP_DOCK_WINDOW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DOCK_WINDOW, GimpDockWindow))
end_define

begin_define
DECL|macro|GIMP_DOCK_WINDOW_CLASS (klass)
define|#
directive|define
name|GIMP_DOCK_WINDOW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DOCK_WINDOW, GimpDockWindowClass))
end_define

begin_define
DECL|macro|GIMP_IS_DOCK_WINDOW (obj)
define|#
directive|define
name|GIMP_IS_DOCK_WINDOW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DOCK_WINDOW))
end_define

begin_define
DECL|macro|GIMP_IS_DOCK_WINDOW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DOCK_WINDOW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DOCK_WINDOW))
end_define

begin_define
DECL|macro|GIMP_DOCK_WINDOW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DOCK_WINDOW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DOCK_WINDOW, GimpDockWindowClass))
end_define

begin_typedef
DECL|typedef|GimpDockWindowClass
typedef|typedef
name|struct
name|_GimpDockWindowClass
name|GimpDockWindowClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDockWindowPrivate
typedef|typedef
name|struct
name|_GimpDockWindowPrivate
name|GimpDockWindowPrivate
typedef|;
end_typedef

begin_comment
comment|/**  * GimpDockWindow:  *  * A top-level window containing GimpDocks.  */
end_comment

begin_struct
DECL|struct|_GimpDockWindow
struct|struct
name|_GimpDockWindow
block|{
DECL|member|parent_instance
name|GimpWindow
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpDockWindowPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDockWindowClass
struct|struct
name|_GimpDockWindowClass
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
name|gimp_dock_window_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dock_window_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_manager_name
parameter_list|,
name|gboolean
name|allow_dockbook_absence
parameter_list|,
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_dock_window_get_id
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_window_add_dock
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_window_remove_dock
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUIManager
modifier|*
name|gimp_dock_window_get_ui_manager
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_dock_window_get_context
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDialogFactory
modifier|*
name|gimp_dock_window_get_dialog_factory
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_dock_window_get_docks
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dock_window_get_auto_follow_active
parameter_list|(
name|GimpDockWindow
modifier|*
name|menu_dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_window_set_auto_follow_active
parameter_list|(
name|GimpDockWindow
modifier|*
name|menu_dock
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dock_window_get_show_image_menu
parameter_list|(
name|GimpDockWindow
modifier|*
name|menu_dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_window_set_show_image_menu
parameter_list|(
name|GimpDockWindow
modifier|*
name|menu_dock
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_window_setup
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpDockWindow
modifier|*
name|template
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_window_set_aux_info
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_dock_window_get_aux_info
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dock_window_has_toolbox
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDockWindow
modifier|*
name|gimp_dock_window_from_dock
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DOCK_WINDOW_H__ */
end_comment

end_unit

