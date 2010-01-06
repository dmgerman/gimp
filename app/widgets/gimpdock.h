begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdock.h  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DOCK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DOCK_H__
define|#
directive|define
name|__GIMP_DOCK_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_DOCK
define|#
directive|define
name|GIMP_TYPE_DOCK
value|(gimp_dock_get_type ())
end_define

begin_define
DECL|macro|GIMP_DOCK (obj)
define|#
directive|define
name|GIMP_DOCK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DOCK, GimpDock))
end_define

begin_define
DECL|macro|GIMP_DOCK_CLASS (klass)
define|#
directive|define
name|GIMP_DOCK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DOCK, GimpDockClass))
end_define

begin_define
DECL|macro|GIMP_IS_DOCK (obj)
define|#
directive|define
name|GIMP_IS_DOCK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DOCK))
end_define

begin_define
DECL|macro|GIMP_IS_DOCK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DOCK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DOCK))
end_define

begin_define
DECL|macro|GIMP_DOCK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DOCK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DOCK, GimpDockClass))
end_define

begin_typedef
DECL|typedef|GimpDockClass
typedef|typedef
name|struct
name|_GimpDockClass
name|GimpDockClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDockPrivate
typedef|typedef
name|struct
name|_GimpDockPrivate
name|GimpDockPrivate
typedef|;
end_typedef

begin_comment
comment|/**  * GimpDock:  *  * Contains a column of GimpDockbooks.  */
end_comment

begin_struct
DECL|struct|_GimpDock
struct|struct
name|_GimpDock
block|{
DECL|member|parent_instance
name|GtkVBox
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpDockPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDockClass
struct|struct
name|_GimpDockClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|get_title
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_title
function_decl|)
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
DECL|member|set_host_geometry_hints
name|void
function_decl|(
modifier|*
name|set_host_geometry_hints
function_decl|)
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GtkWindow
modifier|*
name|window
parameter_list|)
function_decl|;
comment|/*  signals  */
DECL|member|book_added
name|void
function_decl|(
modifier|*
name|book_added
function_decl|)
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
DECL|member|book_removed
name|void
function_decl|(
modifier|*
name|book_removed
function_decl|)
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
DECL|member|title_invalidated
name|void
function_decl|(
modifier|*
name|title_invalidated
function_decl|)
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
DECL|member|geometry_invalidated
name|void
function_decl|(
modifier|*
name|geometry_invalidated
function_decl|)
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dock_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gchar
modifier|*
name|gimp_dock_get_title
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_invalidate_title
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_set_host_geometry_hints
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GtkWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_invalidate_geometry
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_update_with_context
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_dock_get_context
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDialogFactory
modifier|*
name|gimp_dock_get_dialog_factory
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUIManager
modifier|*
name|gimp_dock_get_ui_manager
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_dock_get_dockbooks
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_dock_get_n_dockables
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dock_get_main_vbox
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dock_get_vbox
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_dock_get_id
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_add
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|gint
name|book
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_remove
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_add_book
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_remove_book
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DOCK_H__ */
end_comment

end_unit

