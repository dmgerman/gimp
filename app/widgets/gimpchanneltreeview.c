begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpchannellistview.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

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
file|"core/gimpimage-mask-select.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannellistview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcomponentlistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagepreview.h"
end_include

begin_include
include|#
directive|include
file|"gimplistitem.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_view_class_init
parameter_list|(
name|GimpChannelListViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_view_init
parameter_list|(
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_view_set_image
parameter_list|(
name|GimpItemListView
modifier|*
name|item_view
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
name|gimp_channel_list_view_select_item
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
name|gimp_channel_list_view_set_preview_size
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
name|gimp_channel_list_view_toselection_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_view_toselection_extended_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|state
parameter_list|,
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_view_create_components
parameter_list|(
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_view_clear_components
parameter_list|(
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_view_mode_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_view_alpha_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_view_component_toggle
parameter_list|(
name|GtkList
modifier|*
name|list
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDrawableListViewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_channel_list_view_get_type (void)
name|gimp_channel_list_view_get_type
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
name|GimpChannelListViewClass
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
name|gimp_channel_list_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpChannelListView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_channel_list_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DRAWABLE_LIST_VIEW
argument_list|,
literal|"GimpChannelListView"
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
DECL|function|gimp_channel_list_view_class_init (GimpChannelListViewClass * klass)
name|gimp_channel_list_view_class_init
parameter_list|(
name|GimpChannelListViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpContainerViewClass
modifier|*
name|container_view_class
decl_stmt|;
name|GimpItemListViewClass
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
name|GIMP_ITEM_LIST_VIEW_CLASS
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
name|gimp_channel_list_view_select_item
expr_stmt|;
name|container_view_class
operator|->
name|set_preview_size
operator|=
name|gimp_channel_list_view_set_preview_size
expr_stmt|;
name|item_view_class
operator|->
name|set_image
operator|=
name|gimp_channel_list_view_set_image
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_init (GimpChannelListView * view)
name|gimp_channel_list_view_init
parameter_list|(
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpDrawableListView
modifier|*
name|drawable_view
decl_stmt|;
name|GimpContainerView
modifier|*
name|container_view
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|container_view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
comment|/*  component frame  */
name|view
operator|->
name|component_frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|view
operator|->
name|component_frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
operator|->
name|component_frame
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
name|view
argument_list|)
argument_list|,
name|view
operator|->
name|component_frame
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* don't show */
name|view
operator|->
name|component_list
operator|=
name|gtk_list_new
argument_list|()
expr_stmt|;
name|gtk_list_set_selection_mode
argument_list|(
name|GTK_LIST
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
name|GTK_SELECTION_MULTIPLE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|view
operator|->
name|component_frame
argument_list|)
argument_list|,
name|view
operator|->
name|component_list
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
literal|"select_child"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_channel_list_view_component_toggle
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
literal|"unselect_child"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_channel_list_view_component_toggle
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
comment|/*  To Selection button  */
name|view
operator|->
name|toselection_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|container_view
argument_list|)
argument_list|,
name|GIMP_STOCK_SELECTION_REPLACE
argument_list|,
name|_
argument_list|(
literal|"Channel to Selection\n"
literal|"<Shift> Add\n"
literal|"<Ctrl> Subtract\n"
literal|"<Shift><Ctrl> Intersect"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_channel_list_view_toselection_clicked
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_channel_list_view_toselection_extended_clicked
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|container_view
argument_list|)
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
name|gimp_container_view_enable_dnd
argument_list|(
name|container_view
argument_list|,
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|)
argument_list|,
name|GIMP_TYPE_CHANNEL
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
block|}
end_function

begin_comment
comment|/*  GimpChannelListView methods  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_set_image (GimpItemListView * item_view,GimpImage * gimage)
name|gimp_channel_list_view_set_image
parameter_list|(
name|GimpItemListView
modifier|*
name|item_view
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpChannelListView
modifier|*
name|channel_view
decl_stmt|;
name|channel_view
operator|=
name|GIMP_CHANNEL_LIST_VIEW
argument_list|(
name|item_view
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_view
operator|->
name|gimage
condition|)
block|{
if|if
condition|(
operator|!
name|gimage
condition|)
name|gtk_widget_hide
argument_list|(
name|channel_view
operator|->
name|component_frame
argument_list|)
expr_stmt|;
name|gimp_channel_list_view_clear_components
argument_list|(
name|channel_view
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|)
argument_list|,
name|gimp_channel_list_view_mode_changed
argument_list|,
name|channel_view
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|)
argument_list|,
name|gimp_channel_list_view_alpha_changed
argument_list|,
name|channel_view
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_ITEM_LIST_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
condition|)
name|GIMP_ITEM_LIST_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
argument_list|(
name|item_view
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_view
operator|->
name|gimage
condition|)
block|{
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|channel_view
operator|->
name|component_frame
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|channel_view
operator|->
name|component_frame
argument_list|)
expr_stmt|;
name|gimp_channel_list_view_create_components
argument_list|(
name|channel_view
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"mode_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_channel_list_view_mode_changed
argument_list|)
argument_list|,
name|channel_view
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"alpha_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_channel_list_view_alpha_changed
argument_list|)
argument_list|,
name|channel_view
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  GimpContainerView methods  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_select_item (GimpContainerView * view,GimpViewable * item,gpointer insert_data)
name|gimp_channel_list_view_select_item
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
name|GimpItemListView
modifier|*
name|item_view
decl_stmt|;
name|GimpChannelListView
modifier|*
name|list_view
decl_stmt|;
name|item_view
operator|=
name|GIMP_ITEM_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|list_view
operator|=
name|GIMP_CHANNEL_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
condition|)
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
if|if
condition|(
name|item_view
operator|->
name|gimage
condition|)
block|{
name|gboolean
name|floating_sel
decl_stmt|;
name|floating_sel
operator|=
operator|(
name|gimp_image_floating_sel
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|button_box
argument_list|,
operator|!
name|floating_sel
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|list_view
operator|->
name|toselection_button
argument_list|,
name|item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_set_preview_size (GimpContainerView * view)
name|gimp_channel_list_view_set_preview_size
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GimpChannelListView
modifier|*
name|channel_view
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_preview_size
condition|)
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_preview_size
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|channel_view
operator|=
name|GIMP_CHANNEL_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GTK_LIST
argument_list|(
name|channel_view
operator|->
name|component_list
argument_list|)
operator|->
name|children
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gimp_list_item_set_preview_size
argument_list|(
name|GIMP_LIST_ITEM
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
name|view
operator|->
name|preview_size
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_queue_resize
argument_list|(
name|channel_view
operator|->
name|component_frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_toselection_clicked (GtkWidget * widget,GimpChannelListView * view)
name|gimp_channel_list_view_toselection_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_channel_list_view_toselection_extended_clicked
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
DECL|function|gimp_channel_list_view_toselection_extended_clicked (GtkWidget * widget,guint state,GimpChannelListView * view)
name|gimp_channel_list_view_toselection_extended_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|state
parameter_list|,
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpItemListView
modifier|*
name|item_view
decl_stmt|;
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
name|item_view
operator|=
name|GIMP_ITEM_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|viewable
operator|=
name|item_view
operator|->
name|get_item_func
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
condition|)
block|{
name|GimpChannelOps
name|operation
init|=
name|GIMP_CHANNEL_OP_REPLACE
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
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
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_mask_select_channel
argument_list|(
name|gimage
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|viewable
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|operation
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
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
DECL|function|gimp_channel_list_view_create_components (GimpChannelListView * view)
name|gimp_channel_list_view_create_components
parameter_list|(
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GtkWidget
modifier|*
name|list_item
decl_stmt|;
name|gint
name|n_components
init|=
literal|0
decl_stmt|;
name|GimpChannelType
name|components
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimage
operator|=
name|GIMP_ITEM_LIST_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|gimage
expr_stmt|;
switch|switch
condition|(
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB
case|:
name|n_components
operator|=
literal|3
expr_stmt|;
name|components
index|[
literal|0
index|]
operator|=
name|GIMP_RED_CHANNEL
expr_stmt|;
name|components
index|[
literal|1
index|]
operator|=
name|GIMP_GREEN_CHANNEL
expr_stmt|;
name|components
index|[
literal|2
index|]
operator|=
name|GIMP_BLUE_CHANNEL
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY
case|:
name|n_components
operator|=
literal|1
expr_stmt|;
name|components
index|[
literal|0
index|]
operator|=
name|GIMP_GRAY_CHANNEL
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED
case|:
name|n_components
operator|=
literal|1
expr_stmt|;
name|components
index|[
literal|0
index|]
operator|=
name|GIMP_INDEXED_CHANNEL
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|gimp_image_has_alpha
argument_list|(
name|gimage
argument_list|)
condition|)
block|{
name|components
index|[
name|n_components
operator|++
index|]
operator|=
name|GIMP_ALPHA_CHANNEL
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_components
condition|;
name|i
operator|++
control|)
block|{
name|list_item
operator|=
name|gimp_component_list_item_new
argument_list|(
name|gimage
argument_list|,
name|GIMP_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|preview_size
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list_item
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
block|}
name|gtk_list_insert_items
argument_list|(
name|GTK_LIST
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
name|list
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_queue_resize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
operator|->
name|component_frame
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_clear_components (GimpChannelListView * view)
name|gimp_channel_list_view_clear_components
parameter_list|(
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
name|gimp_channel_list_view_component_toggle
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_list_clear_items
argument_list|(
name|GTK_LIST
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
name|gimp_channel_list_view_component_toggle
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_mode_changed (GimpImage * gimage,GimpChannelListView * view)
name|gimp_channel_list_view_mode_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_channel_list_view_clear_components
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|gimp_channel_list_view_create_components
argument_list|(
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_alpha_changed (GimpImage * gimage,GimpChannelListView * view)
name|gimp_channel_list_view_alpha_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_channel_list_view_clear_components
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|gimp_channel_list_view_create_components
argument_list|(
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_component_toggle (GtkList * list,GtkWidget * child,GimpChannelListView * view)
name|gimp_channel_list_view_component_toggle
parameter_list|(
name|GtkList
modifier|*
name|list
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|GimpChannelListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpComponentListItem
modifier|*
name|component_item
decl_stmt|;
name|component_item
operator|=
name|GIMP_COMPONENT_LIST_ITEM
argument_list|(
name|child
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
name|gimp_channel_list_view_component_toggle
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gimp_image_set_component_active
argument_list|(
name|GIMP_ITEM_LIST_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|gimage
argument_list|,
name|component_item
operator|->
name|channel
argument_list|,
name|child
operator|->
name|state
operator|==
name|GTK_STATE_SELECTED
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
name|gimp_channel_list_view_component_toggle
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

