begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainertreeview-dnd.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainertreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainertreeview-dnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrenderer.h"
end_include

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_tree_view_drop_status (GimpContainerTreeView * tree_view,GdkDragContext * context,gint x,gint y,guint time,GtkTreePath ** return_path,GimpViewable ** return_src,GimpViewable ** return_dest,GtkTreeViewDropPosition * return_pos)
name|gimp_container_tree_view_drop_status
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|tree_view
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
name|GtkTreePath
modifier|*
modifier|*
name|return_path
parameter_list|,
name|GimpViewable
modifier|*
modifier|*
name|return_src
parameter_list|,
name|GimpViewable
modifier|*
modifier|*
name|return_dest
parameter_list|,
name|GtkTreeViewDropPosition
modifier|*
name|return_pos
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|src_widget
decl_stmt|;
name|GimpViewable
modifier|*
name|src_viewable
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_container_view_get_reorderable
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|tree_view
argument_list|)
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|src_widget
operator|=
name|gtk_drag_get_source_widget
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|src_widget
condition|)
return|return
name|FALSE
return|;
name|src_viewable
operator|=
name|gimp_dnd_get_drag_data
argument_list|(
name|src_widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_VIEWABLE
argument_list|(
name|src_viewable
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|gtk_tree_view_get_path_at_pos
argument_list|(
name|tree_view
operator|->
name|view
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|path
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GimpPreviewRenderer
modifier|*
name|renderer
decl_stmt|;
name|GimpViewable
modifier|*
name|dest_viewable
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|GdkRectangle
name|cell_area
decl_stmt|;
name|GtkTreeViewDropPosition
name|drop_pos
decl_stmt|;
name|GdkDragAction
name|drag_action
decl_stmt|;
name|gtk_tree_model_get_iter
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|tree_view
operator|->
name|model_column_renderer
argument_list|,
operator|&
name|renderer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|dest_viewable
operator|=
name|renderer
operator|->
name|viewable
expr_stmt|;
name|gtk_tree_view_get_cell_area
argument_list|(
name|tree_view
operator|->
name|view
argument_list|,
name|path
argument_list|,
name|NULL
argument_list|,
operator|&
name|cell_area
argument_list|)
expr_stmt|;
if|if
condition|(
name|y
operator|>=
operator|(
name|cell_area
operator|.
name|y
operator|+
name|cell_area
operator|.
name|height
operator|/
literal|2
operator|)
condition|)
name|drop_pos
operator|=
name|GTK_TREE_VIEW_DROP_AFTER
expr_stmt|;
else|else
name|drop_pos
operator|=
name|GTK_TREE_VIEW_DROP_BEFORE
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_CONTAINER_TREE_VIEW_GET_CLASS
argument_list|(
name|tree_view
argument_list|)
operator|->
name|drop_possible
argument_list|(
name|tree_view
argument_list|,
name|src_viewable
argument_list|,
name|dest_viewable
argument_list|,
name|drop_pos
argument_list|,
operator|&
name|drag_action
argument_list|)
condition|)
block|{
name|gdk_drag_status
argument_list|(
name|context
argument_list|,
name|drag_action
argument_list|,
name|time
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_path
condition|)
operator|*
name|return_path
operator|=
name|path
expr_stmt|;
else|else
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_src
condition|)
operator|*
name|return_src
operator|=
name|src_viewable
expr_stmt|;
if|if
condition|(
name|return_dest
condition|)
operator|*
name|return_dest
operator|=
name|dest_viewable
expr_stmt|;
if|if
condition|(
name|return_pos
condition|)
operator|*
name|return_pos
operator|=
name|drop_pos
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|gdk_drag_status
argument_list|(
name|context
argument_list|,
literal|0
argument_list|,
name|time
argument_list|)
expr_stmt|;
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_define
DECL|macro|SCROLL_DISTANCE
define|#
directive|define
name|SCROLL_DISTANCE
value|30
end_define

begin_define
DECL|macro|SCROLL_STEP
define|#
directive|define
name|SCROLL_STEP
value|10
end_define

begin_define
DECL|macro|SCROLL_INTERVAL
define|#
directive|define
name|SCROLL_INTERVAL
value|5
end_define

begin_comment
comment|/* #define SCROLL_DEBUG 1 */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_tree_view_scroll_timeout (gpointer data)
name|gimp_container_tree_view_scroll_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
init|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|gdouble
name|new_value
decl_stmt|;
name|adj
operator|=
name|gtk_tree_view_get_vadjustment
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|tree_view
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|SCROLL_DEBUG
name|g_print
argument_list|(
literal|"scroll_timeout: scrolling by %d\n"
argument_list|,
name|SCROLL_STEP
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|tree_view
operator|->
name|scroll_dir
operator|==
name|GDK_SCROLL_UP
condition|)
name|new_value
operator|=
name|adj
operator|->
name|value
operator|-
name|SCROLL_STEP
expr_stmt|;
else|else
name|new_value
operator|=
name|adj
operator|->
name|value
operator|+
name|SCROLL_STEP
expr_stmt|;
name|new_value
operator|=
name|CLAMP
argument_list|(
name|new_value
argument_list|,
name|adj
operator|->
name|lower
argument_list|,
name|adj
operator|->
name|upper
operator|-
name|adj
operator|->
name|page_size
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|adj
argument_list|,
name|new_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|tree_view
operator|->
name|scroll_timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|tree_view
operator|->
name|scroll_timeout_id
argument_list|)
expr_stmt|;
name|tree_view
operator|->
name|scroll_timeout_id
operator|=
name|g_timeout_add
argument_list|(
name|tree_view
operator|->
name|scroll_timeout_interval
argument_list|,
name|gimp_container_tree_view_scroll_timeout
argument_list|,
name|tree_view
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_tree_view_drag_leave (GtkWidget * widget,GdkDragContext * context,guint time,GimpContainerTreeView * tree_view)
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
name|tree_view
parameter_list|)
block|{
if|if
condition|(
name|tree_view
operator|->
name|scroll_timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|tree_view
operator|->
name|scroll_timeout_id
argument_list|)
expr_stmt|;
name|tree_view
operator|->
name|scroll_timeout_id
operator|=
literal|0
expr_stmt|;
block|}
name|gtk_tree_view_unset_rows_drag_dest
argument_list|(
name|tree_view
operator|->
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_container_tree_view_drag_motion (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time,GimpContainerTreeView * tree_view)
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
name|tree_view
parameter_list|)
block|{
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GtkTreeViewDropPosition
name|drop_pos
decl_stmt|;
if|if
condition|(
name|y
operator|<
name|SCROLL_DISTANCE
operator|||
name|y
operator|>
operator|(
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
name|SCROLL_DISTANCE
operator|)
condition|)
block|{
name|gint
name|distance
decl_stmt|;
if|if
condition|(
name|y
operator|<
name|SCROLL_DISTANCE
condition|)
block|{
name|tree_view
operator|->
name|scroll_dir
operator|=
name|GDK_SCROLL_UP
expr_stmt|;
name|distance
operator|=
name|MIN
argument_list|(
operator|-
name|y
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tree_view
operator|->
name|scroll_dir
operator|=
name|GDK_SCROLL_DOWN
expr_stmt|;
name|distance
operator|=
name|MAX
argument_list|(
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
name|y
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
name|tree_view
operator|->
name|scroll_timeout_interval
operator|=
name|SCROLL_INTERVAL
operator|*
name|ABS
argument_list|(
name|distance
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|SCROLL_DEBUG
name|g_print
argument_list|(
literal|"drag_motion: scroll_distance = %d  scroll_interval = %d\n"
argument_list|,
name|distance
argument_list|,
name|tree_view
operator|->
name|scroll_timeout_interval
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|tree_view
operator|->
name|scroll_timeout_id
condition|)
name|tree_view
operator|->
name|scroll_timeout_id
operator|=
name|g_timeout_add
argument_list|(
name|tree_view
operator|->
name|scroll_timeout_interval
argument_list|,
name|gimp_container_tree_view_scroll_timeout
argument_list|,
name|tree_view
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tree_view
operator|->
name|scroll_timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|tree_view
operator|->
name|scroll_timeout_id
argument_list|)
expr_stmt|;
name|tree_view
operator|->
name|scroll_timeout_id
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|gimp_container_tree_view_drop_status
argument_list|(
name|tree_view
argument_list|,
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|time
argument_list|,
operator|&
name|path
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|drop_pos
argument_list|)
condition|)
block|{
name|gtk_tree_view_set_drag_dest_row
argument_list|(
name|tree_view
operator|->
name|view
argument_list|,
name|path
argument_list|,
name|drop_pos
argument_list|)
expr_stmt|;
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|gtk_tree_view_unset_rows_drag_dest
argument_list|(
name|tree_view
operator|->
name|view
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_container_tree_view_drag_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time,GimpContainerTreeView * tree_view)
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
name|tree_view
parameter_list|)
block|{
name|GimpViewable
modifier|*
name|src_viewable
decl_stmt|;
name|GimpViewable
modifier|*
name|dest_viewable
decl_stmt|;
name|GtkTreeViewDropPosition
name|drop_pos
decl_stmt|;
if|if
condition|(
name|tree_view
operator|->
name|scroll_timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|tree_view
operator|->
name|scroll_timeout_id
argument_list|)
expr_stmt|;
name|tree_view
operator|->
name|scroll_timeout_id
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|gimp_container_tree_view_drop_status
argument_list|(
name|tree_view
argument_list|,
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|time
argument_list|,
name|NULL
argument_list|,
operator|&
name|src_viewable
argument_list|,
operator|&
name|dest_viewable
argument_list|,
operator|&
name|drop_pos
argument_list|)
condition|)
block|{
name|GIMP_CONTAINER_TREE_VIEW_GET_CLASS
argument_list|(
name|tree_view
argument_list|)
operator|->
name|drop
argument_list|(
name|tree_view
argument_list|,
name|src_viewable
argument_list|,
name|dest_viewable
argument_list|,
name|drop_pos
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_container_tree_view_real_drop_possible (GimpContainerTreeView * tree_view,GimpViewable * src_viewable,GimpViewable * dest_viewable,GtkTreeViewDropPosition drop_pos,GdkDragAction * drag_action)
name|gimp_container_tree_view_real_drop_possible
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
block|{
name|GimpContainerView
modifier|*
name|view
init|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|tree_view
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
init|=
name|gimp_container_view_get_container
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GimpObject
modifier|*
name|src_object
decl_stmt|;
name|GimpObject
modifier|*
name|dest_object
decl_stmt|;
name|gint
name|src_index
decl_stmt|;
name|gint
name|dest_index
decl_stmt|;
if|if
condition|(
name|src_viewable
operator|==
name|dest_viewable
condition|)
return|return
name|FALSE
return|;
name|src_object
operator|=
name|GIMP_OBJECT
argument_list|(
name|src_viewable
argument_list|)
expr_stmt|;
name|dest_object
operator|=
name|GIMP_OBJECT
argument_list|(
name|dest_viewable
argument_list|)
expr_stmt|;
name|src_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|src_object
argument_list|)
expr_stmt|;
name|dest_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|dest_object
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_index
operator|==
operator|-
literal|1
operator|||
name|dest_index
operator|==
operator|-
literal|1
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|drop_pos
operator|==
name|GTK_TREE_VIEW_DROP_BEFORE
condition|)
block|{
if|if
condition|(
name|dest_index
operator|==
operator|(
name|src_index
operator|+
literal|1
operator|)
condition|)
return|return
name|FALSE
return|;
block|}
else|else
block|{
if|if
condition|(
name|dest_index
operator|==
operator|(
name|src_index
operator|-
literal|1
operator|)
condition|)
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|drag_action
condition|)
operator|*
name|drag_action
operator|=
name|GDK_ACTION_MOVE
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_tree_view_real_drop (GimpContainerTreeView * tree_view,GimpViewable * src_viewable,GimpViewable * dest_viewable,GtkTreeViewDropPosition drop_pos)
name|gimp_container_tree_view_real_drop
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
block|{
name|GimpContainerView
modifier|*
name|view
init|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|tree_view
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
init|=
name|gimp_container_view_get_container
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GimpObject
modifier|*
name|src_object
decl_stmt|;
name|GimpObject
modifier|*
name|dest_object
decl_stmt|;
name|gint
name|src_index
decl_stmt|;
name|gint
name|dest_index
decl_stmt|;
name|src_object
operator|=
name|GIMP_OBJECT
argument_list|(
name|src_viewable
argument_list|)
expr_stmt|;
name|dest_object
operator|=
name|GIMP_OBJECT
argument_list|(
name|dest_viewable
argument_list|)
expr_stmt|;
name|src_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|src_object
argument_list|)
expr_stmt|;
name|dest_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|dest_object
argument_list|)
expr_stmt|;
if|if
condition|(
name|drop_pos
operator|==
name|GTK_TREE_VIEW_DROP_AFTER
operator|&&
name|src_index
operator|>
name|dest_index
condition|)
block|{
name|dest_index
operator|++
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|drop_pos
operator|==
name|GTK_TREE_VIEW_DROP_BEFORE
operator|&&
name|src_index
operator|<
name|dest_index
condition|)
block|{
name|dest_index
operator|--
expr_stmt|;
block|}
name|gimp_container_reorder
argument_list|(
name|container
argument_list|,
name|src_object
argument_list|,
name|dest_index
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

