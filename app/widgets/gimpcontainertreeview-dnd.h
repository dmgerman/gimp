begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainertreeview-dnd.h  * Copyright (C) 2003-2009 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_TREE_VIEW_DND_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_TREE_VIEW_DND_H__
define|#
directive|define
name|__GIMP_CONTAINER_TREE_VIEW_DND_H__
end_define

begin_function_decl
name|void
name|gimp_container_tree_view_drag_failed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GtkDragResult
name|result
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_tree_view_drag_leave
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|guint
name|time
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_tree_view_drag_motion
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_tree_view_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_tree_view_drag_data_received
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection_data
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_tree_view_real_drop_possible
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|,
name|GimpDndType
name|src_type
parameter_list|,
name|GimpViewable
modifier|*
name|src_viewable
parameter_list|,
name|GimpViewable
modifier|*
name|dest_viewable
parameter_list|,
name|GtkTreePath
modifier|*
name|drop_path
parameter_list|,
name|GtkTreeViewDropPosition
name|drop_pos
parameter_list|,
name|GtkTreeViewDropPosition
modifier|*
name|return_drop_pos
parameter_list|,
name|GdkDragAction
modifier|*
name|return_drag_action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_tree_view_real_drop_viewable
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
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_TREE_VIEW_DND_H__  */
end_comment

end_unit

