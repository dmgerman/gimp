begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockbook.h  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|<gtk/gtknotebook.h>
end_include

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

begin_struct
DECL|struct|_GimpDockbook
struct|struct
name|_GimpDockbook
block|{
DECL|member|parent_instance
name|GtkNotebook
name|parent_instance
decl_stmt|;
DECL|member|dock
name|GimpDock
modifier|*
name|dock
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
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|gimp_dockbook_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dockbook_new
parameter_list|(
name|void
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DOCKBOOK_H__ */
end_comment

end_unit

