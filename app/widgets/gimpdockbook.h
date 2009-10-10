begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockbook.h  * Copyright (C) 2001-2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DOCKBOOK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DOCKBOOK_H__
define|#
directive|define
name|__GIMP_DOCKBOOK_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_DOCKBOOK
define|#
directive|define
name|GIMP_TYPE_DOCKBOOK
value|(gimp_dockbook_get_type ())
end_define

begin_define
DECL|macro|GIMP_DOCKBOOK (obj)
define|#
directive|define
name|GIMP_DOCKBOOK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DOCKBOOK, GimpDockbook))
end_define

begin_define
DECL|macro|GIMP_DOCKBOOK_CLASS (klass)
define|#
directive|define
name|GIMP_DOCKBOOK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DOCKBOOK, GimpDockbookClass))
end_define

begin_define
DECL|macro|GIMP_IS_DOCKBOOK (obj)
define|#
directive|define
name|GIMP_IS_DOCKBOOK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DOCKBOOK))
end_define

begin_define
DECL|macro|GIMP_IS_DOCKBOOK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DOCKBOOK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DOCKBOOK))
end_define

begin_define
DECL|macro|GIMP_DOCKBOOK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DOCKBOOK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DOCKBOOK, GimpDockbookClass))
end_define

begin_typedef
DECL|typedef|GimpDockbookClass
typedef|typedef
name|struct
name|_GimpDockbookClass
name|GimpDockbookClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDockbookPrivate
typedef|typedef
name|struct
name|_GimpDockbookPrivate
name|GimpDockbookPrivate
typedef|;
end_typedef

begin_comment
comment|/**  * GimpDockbook:  *  * Holds GimpDockables which are presented on different tabs using  * GtkNotebook.  */
end_comment

begin_struct
DECL|struct|_GimpDockbook
struct|struct
name|_GimpDockbook
block|{
DECL|member|parent_instance
name|GtkNotebook
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpDockbookPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDockbookClass
struct|struct
name|_GimpDockbookClass
block|{
DECL|member|parent_class
name|GtkNotebookClass
name|parent_class
decl_stmt|;
DECL|member|dockable_added
name|void
function_decl|(
modifier|*
name|dockable_added
function_decl|)
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
DECL|member|dockable_removed
name|void
function_decl|(
modifier|*
name|dockable_removed
function_decl|)
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
DECL|member|dockable_reordered
name|void
function_decl|(
modifier|*
name|dockable_reordered
function_decl|)
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dockbook_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dockbook_new
parameter_list|(
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDock
modifier|*
name|gimp_dockbook_get_dock
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dockbook_set_dock
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
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
name|gimp_dockbook_get_ui_manager
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dockbook_add
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dockbook_remove
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dockbook_create_tab_widget
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dockbook_drop_dockable
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GtkWidget
modifier|*
name|drag_source
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DOCKBOOK_H__ */
end_comment

end_unit

