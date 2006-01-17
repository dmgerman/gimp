begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainergridview.h  * Copyright (C) 2001-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_GRID_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_GRID_VIEW_H__
define|#
directive|define
name|__GIMP_CONTAINER_GRID_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontainerbox.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_GRID_VIEW
define|#
directive|define
name|GIMP_TYPE_CONTAINER_GRID_VIEW
value|(gimp_container_grid_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_GRID_VIEW (obj)
define|#
directive|define
name|GIMP_CONTAINER_GRID_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_GRID_VIEW, GimpContainerGridView))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_GRID_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_GRID_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER_GRID_VIEW, GimpContainerGridViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_GRID_VIEW (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_GRID_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_GRID_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_GRID_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_GRID_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER_GRID_VIEW))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_GRID_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_GRID_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER_GRID_VIEW, GimpContainerGridViewClass))
end_define

begin_typedef
DECL|typedef|GimpContainerGridViewClass
typedef|typedef
name|struct
name|_GimpContainerGridViewClass
name|GimpContainerGridViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerGridView
struct|struct
name|_GimpContainerGridView
block|{
DECL|member|parent_instance
name|GimpContainerBox
name|parent_instance
decl_stmt|;
DECL|member|wrap_box
name|GtkWidget
modifier|*
name|wrap_box
decl_stmt|;
DECL|member|rows
name|gint
name|rows
decl_stmt|;
DECL|member|columns
name|gint
name|columns
decl_stmt|;
DECL|member|visible_rows
name|gint
name|visible_rows
decl_stmt|;
DECL|member|selected_item
name|GimpView
modifier|*
name|selected_item
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerGridViewClass
struct|struct
name|_GimpContainerGridViewClass
block|{
DECL|member|parent_class
name|GimpContainerBoxClass
name|parent_class
decl_stmt|;
DECL|member|move_cursor
name|gboolean
function_decl|(
modifier|*
name|move_cursor
function_decl|)
parameter_list|(
name|GimpContainerGridView
modifier|*
name|grid_view
parameter_list|,
name|GtkMovementStep
name|step
parameter_list|,
name|gint
name|count
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_grid_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_container_grid_view_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_GRID_VIEW_H__  */
end_comment

end_unit

