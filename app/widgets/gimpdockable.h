begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockable.h  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DOCKABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DOCKABLE_H__
define|#
directive|define
name|__GIMP_DOCKABLE_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkvbox.h>
end_include

begin_typedef
DECL|typedef|GimpDockableGetTabFunc
typedef|typedef
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|GimpDockableGetTabFunc
function_decl|)
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DOCKABLE
define|#
directive|define
name|GIMP_TYPE_DOCKABLE
value|(gimp_dockable_get_type ())
end_define

begin_define
DECL|macro|GIMP_DOCKABLE (obj)
define|#
directive|define
name|GIMP_DOCKABLE
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_DOCKABLE, GimpDockable))
end_define

begin_define
DECL|macro|GIMP_DOCKABLE_CLASS (klass)
define|#
directive|define
name|GIMP_DOCKABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DOCKABLE, GimpDockableClass))
end_define

begin_define
DECL|macro|GIMP_IS_DOCKABLE (obj)
define|#
directive|define
name|GIMP_IS_DOCKABLE
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_DOCKABLE))
end_define

begin_define
DECL|macro|GIMP_IS_DOCKABLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DOCKABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DOCKABLE))
end_define

begin_typedef
DECL|typedef|GimpDockableClass
typedef|typedef
name|struct
name|_GimpDockableClass
name|GimpDockableClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDockable
struct|struct
name|_GimpDockable
block|{
DECL|member|parent_instance
name|GtkVBox
name|parent_instance
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|short_name
name|gchar
modifier|*
name|short_name
decl_stmt|;
DECL|member|dockbook
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
DECL|member|get_tab_func
name|GimpDockableGetTabFunc
name|get_tab_func
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDockableClass
struct|struct
name|_GimpDockableClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_dockable_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dockable_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|short_name
parameter_list|,
name|GimpDockableGetTabFunc
name|get_tab_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dockable_get_tab_widget
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DOCKABLE_H__ */
end_comment

end_unit

