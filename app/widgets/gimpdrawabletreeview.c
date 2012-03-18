begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdrawabletreeview.c  * Copyright (C) 2001-2009 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-edit.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
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
file|"gimpdrawabletreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_drawable_tree_view_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_drawable_tree_view_drop_possible
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|view
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
specifier|static
name|void
name|gimp_drawable_tree_view_drop_viewable
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|view
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

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_drop_color
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|view
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
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

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_set_image
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_floating_selection_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_new_pattern_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_new_color_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpDrawableTreeView
argument_list|,
argument|gimp_drawable_tree_view
argument_list|,
argument|GIMP_TYPE_ITEM_TREE_VIEW
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONTAINER_VIEW,                                                 gimp_drawable_tree_view_view_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_drawable_tree_view_parent_class
end_define

begin_decl_stmt
specifier|static
name|GimpContainerViewInterface
modifier|*
name|parent_view_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_class_init (GimpDrawableTreeViewClass * klass)
name|gimp_drawable_tree_view_class_init
parameter_list|(
name|GimpDrawableTreeViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpContainerTreeViewClass
modifier|*
name|tree_view_class
decl_stmt|;
name|GimpItemTreeViewClass
modifier|*
name|item_view_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|tree_view_class
operator|=
name|GIMP_CONTAINER_TREE_VIEW_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|item_view_class
operator|=
name|GIMP_ITEM_TREE_VIEW_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_drawable_tree_view_constructed
expr_stmt|;
name|tree_view_class
operator|->
name|drop_possible
operator|=
name|gimp_drawable_tree_view_drop_possible
expr_stmt|;
name|tree_view_class
operator|->
name|drop_viewable
operator|=
name|gimp_drawable_tree_view_drop_viewable
expr_stmt|;
name|tree_view_class
operator|->
name|drop_color
operator|=
name|gimp_drawable_tree_view_drop_color
expr_stmt|;
name|item_view_class
operator|->
name|set_image
operator|=
name|gimp_drawable_tree_view_set_image
expr_stmt|;
name|item_view_class
operator|->
name|lock_content_stock_id
operator|=
name|GIMP_STOCK_TOOL_PAINTBRUSH
expr_stmt|;
name|item_view_class
operator|->
name|lock_content_tooltip
operator|=
name|_
argument_list|(
literal|"Lock pixels"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_view_iface_init (GimpContainerViewInterface * iface)
name|gimp_drawable_tree_view_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|iface
parameter_list|)
block|{
name|parent_view_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|iface
argument_list|)
expr_stmt|;
name|iface
operator|->
name|select_item
operator|=
name|gimp_drawable_tree_view_select_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_init (GimpDrawableTreeView * view)
name|gimp_drawable_tree_view_init
parameter_list|(
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_constructed (GObject * object)
name|gimp_drawable_tree_view_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
init|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpItemTreeView
modifier|*
name|item_view
init|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
condition|)
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|gimp_item_tree_view_get_new_button
argument_list|(
name|item_view
argument_list|)
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
name|gimp_drawable_tree_view_new_pattern_dropped
argument_list|,
name|item_view
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_add
argument_list|(
name|gimp_item_tree_view_get_new_button
argument_list|(
name|item_view
argument_list|)
argument_list|,
name|gimp_drawable_tree_view_new_color_dropped
argument_list|,
name|item_view
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tree_view
operator|->
name|view
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|tree_view
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tree_view
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
name|NULL
argument_list|,
name|tree_view
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  GimpContainerView methods  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_drawable_tree_view_select_item (GimpContainerView * view,GimpViewable * item,gpointer insert_data)
name|gimp_drawable_tree_view_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
block|{
name|GimpItemTreeView
modifier|*
name|item_view
init|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
if|if
condition|(
name|gimp_item_tree_view_get_image
argument_list|(
name|item_view
argument_list|)
condition|)
block|{
name|GimpLayer
modifier|*
name|floating_sel
init|=
name|gimp_image_get_floating_selection
argument_list|(
name|gimp_item_tree_view_get_image
argument_list|(
name|item_view
argument_list|)
argument_list|)
decl_stmt|;
name|success
operator|=
operator|(
name|item
operator|==
name|NULL
operator|||
name|floating_sel
operator|==
name|NULL
operator|||
name|item
operator|==
name|GIMP_VIEWABLE
argument_list|(
name|floating_sel
argument_list|)
operator|)
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|success
operator|=
name|parent_view_iface
operator|->
name|select_item
argument_list|(
name|view
argument_list|,
name|item
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/*  GimpContainerTreeView methods  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_drawable_tree_view_drop_possible (GimpContainerTreeView * tree_view,GimpDndType src_type,GimpViewable * src_viewable,GimpViewable * dest_viewable,GtkTreePath * drop_path,GtkTreeViewDropPosition drop_pos,GtkTreeViewDropPosition * return_drop_pos,GdkDragAction * return_drag_action)
name|gimp_drawable_tree_view_drop_possible
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
block|{
if|if
condition|(
name|GIMP_CONTAINER_TREE_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|drop_possible
argument_list|(
name|tree_view
argument_list|,
name|src_type
argument_list|,
name|src_viewable
argument_list|,
name|dest_viewable
argument_list|,
name|drop_path
argument_list|,
name|drop_pos
argument_list|,
name|return_drop_pos
argument_list|,
name|return_drag_action
argument_list|)
condition|)
block|{
if|if
condition|(
name|src_type
operator|==
name|GIMP_DND_TYPE_COLOR
operator|||
name|src_type
operator|==
name|GIMP_DND_TYPE_PATTERN
condition|)
block|{
if|if
condition|(
operator|!
name|dest_viewable
operator|||
name|gimp_item_is_content_locked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|dest_viewable
argument_list|)
argument_list|)
operator|||
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|dest_viewable
argument_list|)
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|return_drop_pos
condition|)
block|{
operator|*
name|return_drop_pos
operator|=
name|GTK_TREE_VIEW_DROP_INTO_OR_AFTER
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_drop_viewable (GimpContainerTreeView * view,GimpViewable * src_viewable,GimpViewable * dest_viewable,GtkTreeViewDropPosition drop_pos)
name|gimp_drawable_tree_view_drop_viewable
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|view
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
if|if
condition|(
name|dest_viewable
operator|&&
name|GIMP_IS_PATTERN
argument_list|(
name|src_viewable
argument_list|)
condition|)
block|{
name|gimp_edit_fill_full
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|dest_viewable
argument_list|)
argument_list|)
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|dest_viewable
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_PATTERN
argument_list|(
name|src_viewable
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Drop pattern to layer"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|dest_viewable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|GIMP_CONTAINER_TREE_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|drop_viewable
argument_list|(
name|view
argument_list|,
name|src_viewable
argument_list|,
name|dest_viewable
argument_list|,
name|drop_pos
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_drop_color (GimpContainerTreeView * view,const GimpRGB * color,GimpViewable * dest_viewable,GtkTreeViewDropPosition drop_pos)
name|gimp_drawable_tree_view_drop_color
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|view
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpViewable
modifier|*
name|dest_viewable
parameter_list|,
name|GtkTreeViewDropPosition
name|drop_pos
parameter_list|)
block|{
if|if
condition|(
name|dest_viewable
condition|)
block|{
name|gimp_edit_fill_full
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|dest_viewable
argument_list|)
argument_list|)
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|dest_viewable
argument_list|)
argument_list|,
name|color
argument_list|,
name|NULL
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Drop color to layer"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|dest_viewable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  GimpItemTreeView methods  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_set_image (GimpItemTreeView * view,GimpImage * image)
name|gimp_drawable_tree_view_set_image
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
if|if
condition|(
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
condition|)
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
argument_list|,
name|gimp_drawable_tree_view_floating_selection_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|GIMP_ITEM_TREE_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
argument_list|(
name|view
argument_list|,
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
condition|)
name|g_signal_connect
argument_list|(
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
argument_list|,
literal|"floating-selection-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_tree_view_floating_selection_changed
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  callbacks  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_floating_selection_changed (GimpImage * image,GimpDrawableTreeView * view)
name|gimp_drawable_tree_view_floating_selection_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM_TREE_VIEW_GET_CLASS
argument_list|(
name|view
argument_list|)
operator|->
name|get_active_item
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/*  update button states  */
name|gimp_container_view_select_item
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
operator|(
name|GimpViewable
operator|*
operator|)
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_new_dropped (GimpItemTreeView * view,gint x,gint y,const GimpRGB * color,GimpPattern * pattern)
name|gimp_drawable_tree_view_new_dropped
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"New Layer"
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM_TREE_VIEW_GET_CLASS
argument_list|(
name|view
argument_list|)
operator|->
name|new_item
argument_list|(
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
condition|)
block|{
name|gimp_edit_fill_full
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|item
argument_list|)
argument_list|,
name|color
argument_list|,
name|pattern
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|pattern
condition|?
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Drop pattern to layer"
argument_list|)
else|:
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Drop color to layer"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_group_end
argument_list|(
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_new_pattern_dropped (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|gimp_drawable_tree_view_new_pattern_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_drawable_tree_view_new_dropped
argument_list|(
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|NULL
argument_list|,
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_new_color_dropped (GtkWidget * widget,gint x,gint y,const GimpRGB * color,gpointer data)
name|gimp_drawable_tree_view_new_color_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_drawable_tree_view_new_dropped
argument_list|(
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

