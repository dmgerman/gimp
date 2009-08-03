begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpchanneltreeview.c  * Copyright (C) 2001-2009 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
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
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"gimpchanneltreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcomponenteditor.h"
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
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
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

begin_struct
DECL|struct|_GimpChannelTreeViewPriv
struct|struct
name|_GimpChannelTreeViewPriv
block|{
DECL|member|component_editor
name|GtkWidget
modifier|*
name|component_editor
decl_stmt|;
DECL|member|toselection_button
name|GtkWidget
modifier|*
name|toselection_button
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_channel_tree_view_view_iface_init
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
name|gimp_channel_tree_view_constructor
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
name|gimp_channel_tree_view_drop_viewable
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
name|gimp_channel_tree_view_drop_component
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|component
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
name|gimp_channel_tree_view_set_image
parameter_list|(
name|GimpItemTreeView
modifier|*
name|item_view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpItem
modifier|*
name|gimp_channel_tree_view_item_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_tree_view_set_context
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_tree_view_set_view_size
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_tree_view_channel_clicked
parameter_list|(
name|GimpCellRendererViewable
modifier|*
name|cell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_str
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpChannelTreeView
argument_list|,
argument|gimp_channel_tree_view
argument_list|,
argument|GIMP_TYPE_DRAWABLE_TREE_VIEW
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONTAINER_VIEW,                                                 gimp_channel_tree_view_view_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_channel_tree_view_parent_class
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
DECL|function|gimp_channel_tree_view_class_init (GimpChannelTreeViewClass * klass)
name|gimp_channel_tree_view_class_init
parameter_list|(
name|GimpChannelTreeViewClass
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
name|gimp_channel_tree_view_constructor
expr_stmt|;
name|view_class
operator|->
name|drop_viewable
operator|=
name|gimp_channel_tree_view_drop_viewable
expr_stmt|;
name|view_class
operator|->
name|drop_component
operator|=
name|gimp_channel_tree_view_drop_component
expr_stmt|;
name|iv_class
operator|->
name|set_image
operator|=
name|gimp_channel_tree_view_set_image
expr_stmt|;
name|iv_class
operator|->
name|item_type
operator|=
name|GIMP_TYPE_CHANNEL
expr_stmt|;
name|iv_class
operator|->
name|signal_name
operator|=
literal|"active-channel-changed"
expr_stmt|;
name|iv_class
operator|->
name|get_container
operator|=
name|gimp_image_get_channels
expr_stmt|;
name|iv_class
operator|->
name|get_active_item
operator|=
operator|(
name|GimpGetItemFunc
operator|)
name|gimp_image_get_active_channel
expr_stmt|;
name|iv_class
operator|->
name|set_active_item
operator|=
operator|(
name|GimpSetItemFunc
operator|)
name|gimp_image_set_active_channel
expr_stmt|;
name|iv_class
operator|->
name|reorder_item
operator|=
operator|(
name|GimpReorderItemFunc
operator|)
name|gimp_image_position_channel
expr_stmt|;
name|iv_class
operator|->
name|add_item
operator|=
operator|(
name|GimpAddItemFunc
operator|)
name|gimp_image_add_channel
expr_stmt|;
name|iv_class
operator|->
name|remove_item
operator|=
operator|(
name|GimpRemoveItemFunc
operator|)
name|gimp_image_remove_channel
expr_stmt|;
name|iv_class
operator|->
name|new_item
operator|=
name|gimp_channel_tree_view_item_new
expr_stmt|;
name|iv_class
operator|->
name|action_group
operator|=
literal|"channels"
expr_stmt|;
name|iv_class
operator|->
name|activate_action
operator|=
literal|"channels-edit-attributes"
expr_stmt|;
name|iv_class
operator|->
name|edit_action
operator|=
literal|"channels-edit-attributes"
expr_stmt|;
name|iv_class
operator|->
name|new_action
operator|=
literal|"channels-new"
expr_stmt|;
name|iv_class
operator|->
name|new_default_action
operator|=
literal|"channels-new-last-values"
expr_stmt|;
name|iv_class
operator|->
name|raise_action
operator|=
literal|"channels-raise"
expr_stmt|;
name|iv_class
operator|->
name|raise_top_action
operator|=
literal|"channels-raise-to-top"
expr_stmt|;
name|iv_class
operator|->
name|lower_action
operator|=
literal|"channels-lower"
expr_stmt|;
name|iv_class
operator|->
name|lower_bottom_action
operator|=
literal|"channels-lower-to-bottom"
expr_stmt|;
name|iv_class
operator|->
name|duplicate_action
operator|=
literal|"channels-duplicate"
expr_stmt|;
name|iv_class
operator|->
name|delete_action
operator|=
literal|"channels-delete"
expr_stmt|;
name|iv_class
operator|->
name|reorder_desc
operator|=
name|_
argument_list|(
literal|"Reorder Channel"
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpChannelTreeViewPriv
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_tree_view_view_iface_init (GimpContainerViewInterface * view_iface)
name|gimp_channel_tree_view_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|view_iface
parameter_list|)
block|{
name|parent_view_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|view_iface
argument_list|)
expr_stmt|;
name|view_iface
operator|->
name|set_context
operator|=
name|gimp_channel_tree_view_set_context
expr_stmt|;
name|view_iface
operator|->
name|set_view_size
operator|=
name|gimp_channel_tree_view_set_view_size
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_tree_view_init (GimpChannelTreeView * view)
name|gimp_channel_tree_view_init
parameter_list|(
name|GimpChannelTreeView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|view
argument_list|,
name|GIMP_TYPE_CHANNEL_TREE_VIEW
argument_list|,
name|GimpChannelTreeViewPriv
argument_list|)
expr_stmt|;
name|view
operator|->
name|priv
operator|->
name|component_editor
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|priv
operator|->
name|toselection_button
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_channel_tree_view_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_channel_tree_view_constructor
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
name|GimpChannelTreeView
modifier|*
name|view
decl_stmt|;
name|GimpContainerTreeView
modifier|*
name|tree_view
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
name|view
operator|=
name|GIMP_CHANNEL_TREE_VIEW
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
name|g_signal_connect
argument_list|(
name|tree_view
operator|->
name|renderer_cell
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_channel_tree_view_channel_clicked
argument_list|)
argument_list|,
name|view
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
name|GIMP_TYPE_LAYER
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
name|GIMP_TYPE_LAYER_MASK
argument_list|,
name|NULL
argument_list|,
name|tree_view
argument_list|)
expr_stmt|;
name|gimp_dnd_component_dest_add
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
name|view
operator|->
name|priv
operator|->
name|toselection_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|view
argument_list|)
argument_list|,
literal|"channels"
argument_list|,
literal|"channels-selection-replace"
argument_list|,
literal|"channels-selection-add"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
literal|"channels-selection-subtract"
argument_list|,
name|GDK_CONTROL_MASK
argument_list|,
literal|"channels-selection-intersect"
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
name|view
argument_list|)
argument_list|,
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|priv
operator|->
name|toselection_button
argument_list|)
argument_list|,
name|GIMP_TYPE_CHANNEL
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|button_box
argument_list|)
argument_list|,
name|view
operator|->
name|priv
operator|->
name|toselection_button
argument_list|,
literal|5
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_comment
comment|/*  GimpContainerTreeView methods  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_channel_tree_view_drop_viewable (GimpContainerTreeView * tree_view,GimpViewable * src_viewable,GimpViewable * dest_viewable,GtkTreeViewDropPosition drop_pos)
name|gimp_channel_tree_view_drop_viewable
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
name|GimpItemTreeView
modifier|*
name|item_view
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
name|item_view
argument_list|)
decl_stmt|;
name|GimpItemTreeViewClass
modifier|*
name|item_view_class
decl_stmt|;
name|item_view_class
operator|=
name|GIMP_ITEM_TREE_VIEW_GET_CLASS
argument_list|(
name|item_view
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|src_viewable
argument_list|)
operator|&&
operator|(
name|image
operator|!=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|src_viewable
argument_list|)
argument_list|)
operator|||
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|src_viewable
argument_list|)
operator|!=
name|item_view_class
operator|->
name|item_type
operator|)
condition|)
block|{
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
name|GimpItem
modifier|*
name|parent
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|index
operator|=
name|gimp_item_tree_view_get_drop_index
argument_list|(
name|item_view
argument_list|,
name|dest_viewable
argument_list|,
name|drop_pos
argument_list|,
operator|(
name|GimpViewable
operator|*
operator|*
operator|)
operator|&
name|parent
argument_list|)
expr_stmt|;
name|new_item
operator|=
name|gimp_item_convert
argument_list|(
name|GIMP_ITEM
argument_list|(
name|src_viewable
argument_list|)
argument_list|,
name|gimp_item_tree_view_get_image
argument_list|(
name|item_view
argument_list|)
argument_list|,
name|item_view_class
operator|->
name|item_type
argument_list|)
expr_stmt|;
name|gimp_item_set_linked
argument_list|(
name|new_item
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|item_view_class
operator|->
name|add_item
argument_list|(
name|image
argument_list|,
name|new_item
argument_list|,
name|parent
argument_list|,
name|index
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
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
name|tree_view
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
DECL|function|gimp_channel_tree_view_drop_component (GimpContainerTreeView * tree_view,GimpImage * src_image,GimpChannelType component,GimpViewable * dest_viewable,GtkTreeViewDropPosition drop_pos)
name|gimp_channel_tree_view_drop_component
parameter_list|(
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|,
name|GimpImage
modifier|*
name|src_image
parameter_list|,
name|GimpChannelType
name|component
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
name|item_view
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
name|item_view
argument_list|)
decl_stmt|;
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
name|GimpChannel
modifier|*
name|parent
decl_stmt|;
name|gint
name|index
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|index
operator|=
name|gimp_item_tree_view_get_drop_index
argument_list|(
name|item_view
argument_list|,
name|dest_viewable
argument_list|,
name|drop_pos
argument_list|,
operator|(
name|GimpViewable
operator|*
operator|*
operator|)
operator|&
name|parent
argument_list|)
expr_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_CHANNEL_TYPE
argument_list|,
name|component
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s Channel Copy"
argument_list|)
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|new_item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_channel_new_from_component
argument_list|(
name|src_image
argument_list|,
name|component
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  copied components are invisible by default so subsequent copies    *  of components don't affect each other    */
name|gimp_item_set_visible
argument_list|(
name|new_item
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_image
operator|!=
name|image
condition|)
name|GIMP_ITEM_GET_CLASS
argument_list|(
name|new_item
argument_list|)
operator|->
name|convert
argument_list|(
name|new_item
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|image
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|new_item
argument_list|)
argument_list|,
name|parent
argument_list|,
name|index
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  GimpItemTreeView methods  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_channel_tree_view_set_image (GimpItemTreeView * item_view,GimpImage * image)
name|gimp_channel_tree_view_set_image
parameter_list|(
name|GimpItemTreeView
modifier|*
name|item_view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpChannelTreeView
modifier|*
name|channel_view
init|=
name|GIMP_CHANNEL_TREE_VIEW
argument_list|(
name|item_view
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
condition|)
block|{
name|GimpContainerView
modifier|*
name|view
init|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|item_view
argument_list|)
decl_stmt|;
name|gint
name|view_size
decl_stmt|;
name|view_size
operator|=
name|gimp_container_view_get_view_size
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
operator|=
name|gimp_component_editor_new
argument_list|(
name|view_size
argument_list|,
name|GIMP_EDITOR
argument_list|(
name|item_view
argument_list|)
operator|->
name|menu_factory
argument_list|)
expr_stmt|;
name|gimp_docked_set_context
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
argument_list|)
argument_list|,
name|gimp_container_view_get_context
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|item_view
argument_list|)
argument_list|,
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|item_view
argument_list|)
argument_list|,
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|image
condition|)
name|gtk_widget_hide
argument_list|(
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
argument_list|)
expr_stmt|;
name|gimp_image_editor_set_image
argument_list|(
name|GIMP_IMAGE_EDITOR
argument_list|(
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|GIMP_ITEM_TREE_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
argument_list|(
name|item_view
argument_list|,
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_item_tree_view_get_image
argument_list|(
name|item_view
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpItem
modifier|*
DECL|function|gimp_channel_tree_view_item_new (GimpImage * image)
name|gimp_channel_tree_view_item_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|new_channel
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"New Channel"
argument_list|)
argument_list|)
expr_stmt|;
name|new_channel
operator|=
name|gimp_channel_new
argument_list|(
name|image
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Empty Channel"
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
comment|/* FIXME tree */
name|gimp_image_add_channel
argument_list|(
name|image
argument_list|,
name|new_channel
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|GIMP_ITEM
argument_list|(
name|new_channel
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  GimpContainerView methods  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_channel_tree_view_set_context (GimpContainerView * view,GimpContext * context)
name|gimp_channel_tree_view_set_context
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpChannelTreeView
modifier|*
name|channel_view
init|=
name|GIMP_CHANNEL_TREE_VIEW
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|parent_view_iface
operator|->
name|set_context
argument_list|(
name|view
argument_list|,
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
condition|)
name|gimp_docked_set_context
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_tree_view_set_view_size (GimpContainerView * view)
name|gimp_channel_tree_view_set_view_size
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GimpChannelTreeView
modifier|*
name|channel_view
init|=
name|GIMP_CHANNEL_TREE_VIEW
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|gint
name|view_size
decl_stmt|;
name|parent_view_iface
operator|->
name|set_view_size
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|view_size
operator|=
name|gimp_container_view_get_view_size
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
condition|)
name|gimp_component_editor_set_view_size
argument_list|(
name|GIMP_COMPONENT_EDITOR
argument_list|(
name|channel_view
operator|->
name|priv
operator|->
name|component_editor
argument_list|)
argument_list|,
name|view_size
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  signal handlers  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_channel_tree_view_channel_clicked (GimpCellRendererViewable * cell,const gchar * path_str,GdkModifierType state,GimpContainerTreeView * tree_view)
name|gimp_channel_tree_view_channel_clicked
parameter_list|(
name|GimpCellRendererViewable
modifier|*
name|cell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_str
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|)
block|{
if|if
condition|(
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
block|{
name|GimpUIManager
modifier|*
name|ui_manager
init|=
name|GIMP_EDITOR
argument_list|(
name|tree_view
argument_list|)
operator|->
name|ui_manager
decl_stmt|;
name|GimpActionGroup
modifier|*
name|group
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|action
init|=
literal|"channels-selection-replace"
decl_stmt|;
name|group
operator|=
name|gimp_ui_manager_get_action_group
argument_list|(
name|ui_manager
argument_list|,
literal|"channels"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
operator|&&
operator|(
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
condition|)
block|{
name|action
operator|=
literal|"channels-selection-intersect"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
name|action
operator|=
literal|"channels-selection-add"
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
name|action
operator|=
literal|"channels-selection-subtract"
expr_stmt|;
block|}
name|gimp_action_group_activate_action
argument_list|(
name|group
argument_list|,
name|action
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

