begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockcolumns.h  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DOCK_COLUMNS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DOCK_COLUMNS_H__
define|#
directive|define
name|__GIMP_DOCK_COLUMNS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_DOCK_COLUMNS
define|#
directive|define
name|GIMP_TYPE_DOCK_COLUMNS
value|(gimp_dock_columns_get_type ())
end_define

begin_define
DECL|macro|GIMP_DOCK_COLUMNS (obj)
define|#
directive|define
name|GIMP_DOCK_COLUMNS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DOCK_COLUMNS, GimpDockColumns))
end_define

begin_define
DECL|macro|GIMP_DOCK_COLUMNS_CLASS (klass)
define|#
directive|define
name|GIMP_DOCK_COLUMNS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DOCK_COLUMNS, GimpDockColumnsClass))
end_define

begin_define
DECL|macro|GIMP_IS_DOCK_COLUMNS (obj)
define|#
directive|define
name|GIMP_IS_DOCK_COLUMNS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DOCK_COLUMNS))
end_define

begin_define
DECL|macro|GIMP_IS_DOCK_COLUMNS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DOCK_COLUMNS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DOCK_COLUMNS))
end_define

begin_define
DECL|macro|GIMP_DOCK_COLUMNS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DOCK_COLUMNS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DOCK_COLUMNS, GimpDockColumnsClass))
end_define

begin_typedef
DECL|typedef|GimpDockColumnsClass
typedef|typedef
name|struct
name|_GimpDockColumnsClass
name|GimpDockColumnsClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDockColumnsPrivate
typedef|typedef
name|struct
name|_GimpDockColumnsPrivate
name|GimpDockColumnsPrivate
typedef|;
end_typedef

begin_comment
comment|/**  * GimpDockColumns:  *  * A widget containing GimpDocks so that dockables are arranged in  * columns.  */
end_comment

begin_struct
DECL|struct|_GimpDockColumns
struct|struct
name|_GimpDockColumns
block|{
DECL|member|parent_instance
name|GtkHBox
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpDockColumnsPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDockColumnsClass
struct|struct
name|_GimpDockColumnsClass
block|{
DECL|member|parent_class
name|GtkHBoxClass
name|parent_class
decl_stmt|;
DECL|member|dock_added
name|void
function_decl|(
modifier|*
name|dock_added
function_decl|)
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
DECL|member|dock_removed
name|void
function_decl|(
modifier|*
name|dock_removed
function_decl|)
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
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
name|gimp_dock_columns_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dock_columns_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_columns_add_dock
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
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
name|gimp_dock_columns_remove_dock
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_dock_columns_get_docks
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_dock_columns_get_context
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_columns_set_context
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DOCK_COLUMNS_H__ */
end_comment

end_unit

