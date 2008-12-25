begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpvectorstreeview.c  * Copyright (C) 2001-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors-export.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors-import.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectorstreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_vectors_tree_view_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_vectors_tree_view_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_tree_view_set_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_tree_view_drop_svg
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|,
specifier|const
name|gchar
modifier|*
name|svg_data
parameter_list|,
name|gsize
name|svg_data_len
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
name|GimpItem
modifier|*
name|gimp_vectors_tree_view_item_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guchar
modifier|*
name|gimp_vectors_tree_view_drag_svg
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gsize
modifier|*
name|svg_data_len
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpVectorsTreeView
argument_list|,
argument|gimp_vectors_tree_view
argument_list|,
argument|GIMP_TYPE_ITEM_TREE_VIEW
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONTAINER_VIEW,                                                 gimp_vectors_tree_view_view_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_vectors_tree_view_parent_class
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
DECL|function|gimp_vectors_tree_view_class_init (GimpVectorsTreeViewClass * klass)
name|gimp_vectors_tree_view_class_init
parameter_list|(
name|GimpVectorsTreeViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpContainerTreeViewClass
modifier|*
name|view_class
init|=
name|GIMP_CONTAINER_TREE_VIEW_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpItemTreeViewClass
modifier|*
name|iv_class
init|=
name|GIMP_ITEM_TREE_VIEW_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_vectors_tree_view_constructor
expr_stmt|;
name|view_class
operator|->
name|drop_svg
operator|=
name|gimp_vectors_tree_view_drop_svg
expr_stmt|;
name|iv_class
operator|->
name|item_type
operator|=
name|GIMP_TYPE_VECTORS
expr_stmt|;
name|iv_class
operator|->
name|signal_name
operator|=
literal|"active-vectors-changed"
expr_stmt|;
name|iv_class
operator|->
name|get_container
operator|=
name|gimp_image_get_vectors
expr_stmt|;
name|iv_class
operator|->
name|get_active_item
operator|=
operator|(
name|GimpGetItemFunc
operator|)
name|gimp_image_get_active_vectors
expr_stmt|;
name|iv_class
operator|->
name|set_active_item
operator|=
operator|(
name|GimpSetItemFunc
operator|)
name|gimp_image_set_active_vectors
expr_stmt|;
name|iv_class
operator|->
name|reorder_item
operator|=
operator|(
name|GimpReorderItemFunc
operator|)
name|gimp_image_position_vectors
expr_stmt|;
name|iv_class
operator|->
name|add_item
operator|=
operator|(
name|GimpAddItemFunc
operator|)
name|gimp_image_add_vectors
expr_stmt|;
name|iv_class
operator|->
name|remove_item
operator|=
operator|(
name|GimpRemoveItemFunc
operator|)
name|gimp_image_remove_vectors
expr_stmt|;
name|iv_class
operator|->
name|new_item
operator|=
name|gimp_vectors_tree_view_item_new
expr_stmt|;
name|iv_class
operator|->
name|action_group
operator|=
literal|"vectors"
expr_stmt|;
name|iv_class
operator|->
name|activate_action
operator|=
literal|"vectors-path-tool"
expr_stmt|;
name|iv_class
operator|->
name|edit_action
operator|=
literal|"vectors-edit-attributes"
expr_stmt|;
name|iv_class
operator|->
name|new_action
operator|=
literal|"vectors-new"
expr_stmt|;
name|iv_class
operator|->
name|new_default_action
operator|=
literal|"vectors-new-last-values"
expr_stmt|;
name|iv_class
operator|->
name|raise_action
operator|=
literal|"vectors-raise"
expr_stmt|;
name|iv_class
operator|->
name|raise_top_action
operator|=
literal|"vectors-raise-to-top"
expr_stmt|;
name|iv_class
operator|->
name|lower_action
operator|=
literal|"vectors-lower"
expr_stmt|;
name|iv_class
operator|->
name|lower_bottom_action
operator|=
literal|"vectors-lower-to-bottom"
expr_stmt|;
name|iv_class
operator|->
name|duplicate_action
operator|=
literal|"vectors-duplicate"
expr_stmt|;
name|iv_class
operator|->
name|delete_action
operator|=
literal|"vectors-delete"
expr_stmt|;
name|iv_class
operator|->
name|reorder_desc
operator|=
name|_
argument_list|(
literal|"Reorder path"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_tree_view_view_iface_init (GimpContainerViewInterface * iface)
name|gimp_vectors_tree_view_view_iface_init
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
name|set_container
operator|=
name|gimp_vectors_tree_view_set_container
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_tree_view_init (GimpVectorsTreeView * view)
name|gimp_vectors_tree_view_init
parameter_list|(
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_vectors_tree_view_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_vectors_tree_view_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpEditor
modifier|*
name|editor
decl_stmt|;
name|GimpContainerTreeView
modifier|*
name|tree_view
decl_stmt|;
name|GimpVectorsTreeView
modifier|*
name|view
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|editor
operator|=
name|GIMP_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_VECTORS_TREE_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
comment|/*  hide basically useless edit button  */
name|gtk_widget_hide
argument_list|(
name|gimp_item_tree_view_get_edit_button
argument_list|(
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|toselection_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|editor
argument_list|,
literal|"vectors"
argument_list|,
literal|"vectors-selection-replace"
argument_list|,
literal|"vectors-selection-add"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
literal|"vectors-selection-subtract"
argument_list|,
name|GDK_CONTROL_MASK
argument_list|,
literal|"vectors-selection-intersect"
argument_list|,
name|GDK_SHIFT_MASK
operator||
name|GDK_CONTROL_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|)
argument_list|,
name|GIMP_TYPE_VECTORS
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|button_box
argument_list|)
argument_list|,
name|view
operator|->
name|toselection_button
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|view
operator|->
name|tovectors_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|editor
argument_list|,
literal|"vectors"
argument_list|,
literal|"vectors-selection-to-vectors"
argument_list|,
literal|"vectors-selection-to-vectors-advanced"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|button_box
argument_list|)
argument_list|,
name|view
operator|->
name|tovectors_button
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|view
operator|->
name|stroke_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|editor
argument_list|,
literal|"vectors"
argument_list|,
literal|"vectors-stroke"
argument_list|,
literal|"vectors-stroke-last-values"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|stroke_button
argument_list|)
argument_list|,
name|GIMP_TYPE_VECTORS
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|button_box
argument_list|)
argument_list|,
name|view
operator|->
name|stroke_button
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|gimp_dnd_svg_dest_add
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
name|view
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_tree_view_set_container (GimpContainerView * view,GimpContainer * container)
name|gimp_vectors_tree_view_set_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
init|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|old_container
decl_stmt|;
name|old_container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_container
operator|&&
operator|!
name|container
condition|)
block|{
name|gimp_dnd_svg_source_remove
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tree_view
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|parent_view_iface
operator|->
name|set_container
argument_list|(
name|view
argument_list|,
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|old_container
operator|&&
name|container
condition|)
block|{
name|gimp_dnd_svg_source_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tree_view
operator|->
name|view
argument_list|)
argument_list|,
name|gimp_vectors_tree_view_drag_svg
argument_list|,
name|tree_view
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_tree_view_drop_svg (GimpContainerTreeView * tree_view,const gchar * svg_data,gsize svg_data_len,GimpViewable * dest_viewable,GtkTreeViewDropPosition drop_pos)
name|gimp_vectors_tree_view_drop_svg
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|,
specifier|const
name|gchar
modifier|*
name|svg_data
parameter_list|,
name|gsize
name|svg_data_len
parameter_list|,
name|GimpViewable
modifier|*
name|dest_viewable
parameter_list|,
name|GtkTreeViewDropPosition
name|drop_pos
parameter_list|)
block|{
name|GimpItemTreeView
modifier|*
name|view
init|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|tree_view
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|gint
name|index
init|=
operator|-
literal|1
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|image
operator|->
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"%s: SVG dropped (len = %d)\n"
argument_list|,
name|G_STRFUNC
argument_list|,
operator|(
name|gint
operator|)
name|svg_data_len
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_viewable
condition|)
block|{
name|index
operator|=
name|gimp_image_get_vectors_index
argument_list|(
name|image
argument_list|,
name|GIMP_VECTORS
argument_list|(
name|dest_viewable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|drop_pos
operator|==
name|GTK_TREE_VIEW_DROP_AFTER
condition|)
name|index
operator|++
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gimp_vectors_import_buffer
argument_list|(
name|image
argument_list|,
name|svg_data
argument_list|,
name|svg_data_len
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|index
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|tree_view
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GimpItem
modifier|*
DECL|function|gimp_vectors_tree_view_item_new (GimpImage * image)
name|gimp_vectors_tree_view_item_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpVectors
modifier|*
name|new_vectors
decl_stmt|;
name|new_vectors
operator|=
name|gimp_vectors_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Empty Path"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|image
argument_list|,
name|new_vectors
argument_list|,
operator|-
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|GIMP_ITEM
argument_list|(
name|new_vectors
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|guchar
modifier|*
DECL|function|gimp_vectors_tree_view_drag_svg (GtkWidget * widget,gsize * svg_data_len,gpointer data)
name|gimp_vectors_tree_view_drag_svg
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gsize
modifier|*
name|svg_data_len
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpItemTreeView
modifier|*
name|view
init|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|gchar
modifier|*
name|svg_data
init|=
name|NULL
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
operator|*
name|svg_data_len
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|item
condition|)
block|{
name|svg_data
operator|=
name|gimp_vectors_export_string
argument_list|(
name|image
argument_list|,
name|GIMP_VECTORS
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|svg_data
condition|)
operator|*
name|svg_data_len
operator|=
name|strlen
argument_list|(
name|svg_data
argument_list|)
expr_stmt|;
block|}
return|return
operator|(
name|guchar
operator|*
operator|)
name|svg_data
return|;
block|}
end_function

end_unit

