begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainertreeview.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_TREE_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_TREE_VIEW_H__
define|#
directive|define
name|__GIMP_CONTAINER_TREE_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontainerbox.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_TREE_VIEW
define|#
directive|define
name|GIMP_TYPE_CONTAINER_TREE_VIEW
value|(gimp_container_tree_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_TREE_VIEW (obj)
define|#
directive|define
name|GIMP_CONTAINER_TREE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_TREE_VIEW, GimpContainerTreeView))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_TREE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_TREE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER_TREE_VIEW, GimpContainerTreeViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_TREE_VIEW (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_TREE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_TREE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_TREE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_TREE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER_TREE_VIEW))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_TREE_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_TREE_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER_TREE_VIEW, GimpContainerTreeViewClass))
end_define

begin_typedef
DECL|typedef|GimpContainerTreeViewClass
typedef|typedef
name|struct
name|_GimpContainerTreeViewClass
name|GimpContainerTreeViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerTreeView
struct|struct
name|_GimpContainerTreeView
block|{
DECL|member|parent_instance
name|GimpContainerBox
name|parent_instance
decl_stmt|;
DECL|member|model
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
DECL|member|n_model_columns
name|gint
name|n_model_columns
decl_stmt|;
DECL|member|model_columns
name|GType
name|model_columns
index|[
literal|16
index|]
decl_stmt|;
DECL|member|model_column_renderer
name|gint
name|model_column_renderer
decl_stmt|;
DECL|member|model_column_name
name|gint
name|model_column_name
decl_stmt|;
DECL|member|model_column_name_attributes
name|gint
name|model_column_name_attributes
decl_stmt|;
DECL|member|view
name|GtkTreeView
modifier|*
name|view
decl_stmt|;
DECL|member|selection
name|GtkTreeSelection
modifier|*
name|selection
decl_stmt|;
DECL|member|main_column
name|GtkTreeViewColumn
modifier|*
name|main_column
decl_stmt|;
DECL|member|renderer_cell
name|GtkCellRenderer
modifier|*
name|renderer_cell
decl_stmt|;
DECL|member|name_cell
name|GtkCellRenderer
modifier|*
name|name_cell
decl_stmt|;
DECL|member|toggle_cells
name|GList
modifier|*
name|toggle_cells
decl_stmt|;
DECL|member|renderer_cells
name|GList
modifier|*
name|renderer_cells
decl_stmt|;
DECL|member|editable_cells
name|GList
modifier|*
name|editable_cells
decl_stmt|;
DECL|member|invalidate_preview_handler_id
name|GQuark
name|invalidate_preview_handler_id
decl_stmt|;
DECL|member|dnd_viewable
name|GimpViewable
modifier|*
name|dnd_viewable
decl_stmt|;
DECL|member|scroll_timeout_id
name|guint
name|scroll_timeout_id
decl_stmt|;
DECL|member|scroll_timeout_interval
name|guint
name|scroll_timeout_interval
decl_stmt|;
DECL|member|scroll_dir
name|GdkScrollDirection
name|scroll_dir
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerTreeViewClass
struct|struct
name|_GimpContainerTreeViewClass
block|{
DECL|member|parent_class
name|GimpContainerBoxClass
name|parent_class
decl_stmt|;
DECL|member|drop_possible
name|gboolean
function_decl|(
modifier|*
name|drop_possible
function_decl|)
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|,
name|GimpViewable
modifier|*
name|src_viewable
parameter_list|,
name|GimpViewable
modifier|*
name|dest_viewable
parameter_list|,
name|GtkTreeViewDropPosition
name|drop_pos
parameter_list|,
name|GdkDragAction
modifier|*
name|drag_action
parameter_list|)
function_decl|;
DECL|member|drop
name|void
function_decl|(
modifier|*
name|drop
function_decl|)
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|,
name|GimpViewable
modifier|*
name|src_viewable
parameter_list|,
name|GimpViewable
modifier|*
name|dest_viewable
parameter_list|,
name|GtkTreeViewDropPosition
name|drop_pos
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_tree_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_container_tree_view_new
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
name|preview_size
parameter_list|,
name|gint
name|preview_border_width
parameter_list|,
name|gboolean
name|reorderable
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_TREE_VIEW_H__  */
end_comment

end_unit

