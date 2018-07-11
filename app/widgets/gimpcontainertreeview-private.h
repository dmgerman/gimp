begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainertreeview-private.h  * Copyright (C) 2003-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_TREE_VIEW_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_TREE_VIEW_PRIVATE_H__
define|#
directive|define
name|__GIMP_CONTAINER_TREE_VIEW_PRIVATE_H__
end_define

begin_struct
DECL|struct|_GimpContainerTreeViewPriv
struct|struct
name|_GimpContainerTreeViewPriv
block|{
DECL|member|selection
name|GtkTreeSelection
modifier|*
name|selection
decl_stmt|;
DECL|member|name_cell
name|GtkCellRenderer
modifier|*
name|name_cell
decl_stmt|;
DECL|member|editable_cells
name|GList
modifier|*
name|editable_cells
decl_stmt|;
DECL|member|dnd_renderer
name|GimpViewRenderer
modifier|*
name|dnd_renderer
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
DECL|member|dnd_drop_to_empty
name|gboolean
name|dnd_drop_to_empty
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_TREE_VIEW_PRIVATE_H__  */
end_comment

end_unit

