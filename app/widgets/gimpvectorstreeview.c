begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpvectorstreeview.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpmath/gimpmath.h"
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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel-select.h"
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
file|"gimphelp-ids.h"
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
name|gimp_vectors_tree_view_class_init
parameter_list|(
name|GimpVectorsTreeViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_tree_view_init
parameter_list|(
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_vectors_tree_view_select_item
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
name|void
name|gimp_vectors_tree_view_set_image
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_tree_view_toselection_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_tree_view_toselection_extended_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|state
parameter_list|,
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_tree_view_tovectors_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_tree_view_tovectors_extended_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|state
parameter_list|,
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_tree_view_stroke_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpItemTreeViewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_vectors_tree_view_get_type (void)
name|gimp_vectors_tree_view_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpVectorsTreeViewClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_vectors_tree_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpVectorsTreeView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_vectors_tree_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_ITEM_TREE_VIEW
argument_list|,
literal|"GimpVectorsTreeView"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

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
name|GimpContainerViewClass
modifier|*
name|container_view_class
decl_stmt|;
name|GimpItemTreeViewClass
modifier|*
name|item_view_class
decl_stmt|;
name|container_view_class
operator|=
name|GIMP_CONTAINER_VIEW_CLASS
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|container_view_class
operator|->
name|select_item
operator|=
name|gimp_vectors_tree_view_select_item
expr_stmt|;
name|item_view_class
operator|->
name|set_image
operator|=
name|gimp_vectors_tree_view_set_image
expr_stmt|;
name|item_view_class
operator|->
name|get_container
operator|=
name|gimp_image_get_vectors
expr_stmt|;
name|item_view_class
operator|->
name|get_active_item
operator|=
operator|(
name|GimpGetItemFunc
operator|)
name|gimp_image_get_active_vectors
expr_stmt|;
name|item_view_class
operator|->
name|set_active_item
operator|=
operator|(
name|GimpSetItemFunc
operator|)
name|gimp_image_set_active_vectors
expr_stmt|;
name|item_view_class
operator|->
name|reorder_item
operator|=
operator|(
name|GimpReorderItemFunc
operator|)
name|gimp_image_position_vectors
expr_stmt|;
name|item_view_class
operator|->
name|add_item
operator|=
operator|(
name|GimpAddItemFunc
operator|)
name|gimp_image_add_vectors
expr_stmt|;
name|item_view_class
operator|->
name|remove_item
operator|=
operator|(
name|GimpRemoveItemFunc
operator|)
name|gimp_image_remove_vectors
expr_stmt|;
name|item_view_class
operator|->
name|edit_desc
operator|=
name|_
argument_list|(
literal|"Edit Path Attributes"
argument_list|)
expr_stmt|;
name|item_view_class
operator|->
name|edit_help_id
operator|=
name|GIMP_HELP_PATH_EDIT
expr_stmt|;
name|item_view_class
operator|->
name|new_desc
operator|=
name|_
argument_list|(
literal|"New Path"
argument_list|)
expr_stmt|;
name|item_view_class
operator|->
name|new_help_id
operator|=
name|GIMP_HELP_PATH_NEW
expr_stmt|;
name|item_view_class
operator|->
name|duplicate_desc
operator|=
name|_
argument_list|(
literal|"Duplicate Path"
argument_list|)
expr_stmt|;
name|item_view_class
operator|->
name|duplicate_help_id
operator|=
name|GIMP_HELP_PATH_DUPLICATE
expr_stmt|;
name|item_view_class
operator|->
name|delete_desc
operator|=
name|_
argument_list|(
literal|"Delete Path"
argument_list|)
expr_stmt|;
name|item_view_class
operator|->
name|delete_help_id
operator|=
name|GIMP_HELP_PATH_DELETE
expr_stmt|;
name|item_view_class
operator|->
name|raise_desc
operator|=
name|_
argument_list|(
literal|"Raise Path"
argument_list|)
expr_stmt|;
name|item_view_class
operator|->
name|raise_help_id
operator|=
name|GIMP_HELP_PATH_RAISE
expr_stmt|;
name|item_view_class
operator|->
name|raise_to_top_desc
operator|=
name|_
argument_list|(
literal|"Raise Path to Top"
argument_list|)
expr_stmt|;
name|item_view_class
operator|->
name|raise_to_top_help_id
operator|=
name|GIMP_HELP_PATH_RAISE_TO_TOP
expr_stmt|;
name|item_view_class
operator|->
name|lower_desc
operator|=
name|_
argument_list|(
literal|"Lower Path"
argument_list|)
expr_stmt|;
name|item_view_class
operator|->
name|lower_help_id
operator|=
name|GIMP_HELP_PATH_LOWER
expr_stmt|;
name|item_view_class
operator|->
name|lower_to_bottom_desc
operator|=
name|_
argument_list|(
literal|"Lower Path to Bottom"
argument_list|)
expr_stmt|;
name|item_view_class
operator|->
name|lower_to_bottom_help_id
operator|=
name|GIMP_HELP_PATH_LOWER_TO_BOTTOM
expr_stmt|;
name|item_view_class
operator|->
name|reorder_desc
operator|=
name|_
argument_list|(
literal|"Reorder Path"
argument_list|)
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
block|{
name|GimpEditor
modifier|*
name|editor
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|editor
operator|=
name|GIMP_EDITOR
argument_list|(
name|view
argument_list|)
expr_stmt|;
comment|/*  Hide basically useless Edit button  */
name|gtk_widget_hide
argument_list|(
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|edit_button
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Path to Selection\n"
literal|"%s  Add\n"
literal|"%s  Subtract\n"
literal|"%s%s%s  Intersect"
argument_list|)
argument_list|,
name|gimp_get_mod_name_shift
argument_list|()
argument_list|,
name|gimp_get_mod_name_control
argument_list|()
argument_list|,
name|gimp_get_mod_name_shift
argument_list|()
argument_list|,
name|gimp_get_mod_separator
argument_list|()
argument_list|,
name|gimp_get_mod_name_control
argument_list|()
argument_list|)
expr_stmt|;
name|view
operator|->
name|toselection_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|editor
argument_list|,
name|GIMP_STOCK_SELECTION_REPLACE
argument_list|,
name|str
argument_list|,
name|GIMP_HELP_PATH_SELECTION_REPLACE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_vectors_tree_view_toselection_clicked
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_vectors_tree_view_toselection_extended_clicked
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Selection to Path\n"
literal|"%s  Advanced Options"
argument_list|)
argument_list|,
name|gimp_get_mod_name_shift
argument_list|()
argument_list|)
expr_stmt|;
name|view
operator|->
name|tovectors_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|editor
argument_list|,
name|GIMP_STOCK_SELECTION_TO_PATH
argument_list|,
name|str
argument_list|,
name|GIMP_HELP_SELECTION_TO_PATH
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_vectors_tree_view_tovectors_clicked
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_vectors_tree_view_tovectors_extended_clicked
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|view
operator|->
name|stroke_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|editor
argument_list|,
name|GIMP_STOCK_PATH_STROKE
argument_list|,
name|_
argument_list|(
literal|"Stroke Path"
argument_list|)
argument_list|,
name|GIMP_HELP_PATH_STROKE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_vectors_tree_view_stroke_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|view
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
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|tovectors_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|stroke_button
argument_list|,
name|FALSE
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
DECL|function|gimp_vectors_tree_view_select_item (GimpContainerView * view,GimpViewable * item,gpointer insert_data)
name|gimp_vectors_tree_view_select_item
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
name|GimpVectorsTreeView
modifier|*
name|tree_view
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|tree_view
operator|=
name|GIMP_VECTORS_TREE_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|success
operator|=
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
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
name|gtk_widget_set_sensitive
argument_list|(
name|tree_view
operator|->
name|toselection_button
argument_list|,
name|item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|tree_view
operator|->
name|stroke_button
argument_list|,
name|item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_tree_view_set_image (GimpItemTreeView * view,GimpImage * gimage)
name|gimp_vectors_tree_view_set_image
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GIMP_ITEM_TREE_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
argument_list|(
name|view
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GIMP_VECTORS_TREE_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|tovectors_button
argument_list|,
name|gimage
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_tree_view_toselection_clicked (GtkWidget * widget,GimpVectorsTreeView * view)
name|gimp_vectors_tree_view_toselection_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_vectors_tree_view_toselection_extended_clicked
argument_list|(
name|widget
argument_list|,
literal|0
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_tree_view_toselection_extended_clicked (GtkWidget * widget,guint state,GimpVectorsTreeView * view)
name|gimp_vectors_tree_view_toselection_extended_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|state
parameter_list|,
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|gimage
operator|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|gimage
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM_TREE_VIEW_GET_CLASS
argument_list|(
name|view
argument_list|)
operator|->
name|get_active_item
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
condition|)
block|{
name|GimpChannelOps
name|operation
init|=
name|GIMP_CHANNEL_OP_REPLACE
decl_stmt|;
if|if
condition|(
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|operation
operator|=
name|GIMP_CHANNEL_OP_INTERSECT
expr_stmt|;
else|else
name|operation
operator|=
name|GIMP_CHANNEL_OP_ADD
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|operation
operator|=
name|GIMP_CHANNEL_OP_SUBTRACT
expr_stmt|;
block|}
name|gimp_channel_select_vectors
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Path to Selection"
argument_list|)
argument_list|,
name|GIMP_VECTORS
argument_list|(
name|item
argument_list|)
argument_list|,
name|operation
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_tree_view_tovectors_clicked (GtkWidget * widget,GimpVectorsTreeView * view)
name|gimp_vectors_tree_view_tovectors_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_vectors_tree_view_tovectors_extended_clicked
argument_list|(
name|widget
argument_list|,
literal|0
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_tree_view_tovectors_extended_clicked (GtkWidget * widget,guint state,GimpVectorsTreeView * view)
name|gimp_vectors_tree_view_tovectors_extended_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|state
parameter_list|,
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
block|{
if|if
condition|(
name|view
operator|->
name|selection_to_vectors_func
condition|)
name|view
operator|->
name|selection_to_vectors_func
argument_list|(
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|gimage
argument_list|,
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
operator|!=
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_tree_view_stroke_clicked (GtkWidget * widget,GimpVectorsTreeView * view)
name|gimp_vectors_tree_view_stroke_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpVectorsTreeView
modifier|*
name|view
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|gimage
operator|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|gimage
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM_TREE_VIEW_GET_CLASS
argument_list|(
name|view
argument_list|)
operator|->
name|get_active_item
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
operator|&&
name|view
operator|->
name|stroke_item_func
condition|)
name|view
operator|->
name|stroke_item_func
argument_list|(
name|item
argument_list|,
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

