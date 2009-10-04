begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockcolumns.c  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockcolumns.h"
end_include

begin_struct
DECL|struct|_GimpDockColumnsPrivate
struct|struct
name|_GimpDockColumnsPrivate
block|{
DECL|member|dummy
name|int
name|dummy
decl_stmt|;
block|}
struct|;
end_struct

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDockColumns,gimp_dock_columns,GTK_TYPE_HBOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDockColumns
argument_list|,
argument|gimp_dock_columns
argument_list|,
argument|GTK_TYPE_HBOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dock_columns_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_dock_columns_class_init
parameter_list|(
name|GimpDockColumnsClass
modifier|*
name|klass
parameter_list|)
block|{
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDockColumnsPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_columns_init (GimpDockColumns * dock_columns)
name|gimp_dock_columns_init
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|)
block|{
name|dock_columns
operator|->
name|p
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|dock_columns
argument_list|,
name|GIMP_TYPE_DOCK_COLUMNS
argument_list|,
name|GimpDockColumnsPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_columns_add_dock (GimpDockColumns * dock_columns,GimpDock * dock)
name|gimp_dock_columns_add_dock
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK_COLUMNS
argument_list|(
name|dock_columns
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dock_columns
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

