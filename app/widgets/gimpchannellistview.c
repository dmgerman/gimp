begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpchannellistview.c  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewable.h"
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
file|"tools/paint_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/toselection.xpm"
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
name|gimp_channel_list_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_view_set_image
parameter_list|(
name|GimpDrawableListView
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
name|gimp_channel_list_view_to_selection
parameter_list|(
name|GimpChannelListView
modifier|*
name|view
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|ChannelOps
name|operation
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
name|gimp_channel_list_view_toselection_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|GtkType
DECL|function|gimp_channel_list_view_get_type (void)
name|gimp_channel_list_view_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
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
name|GtkTypeInfo
name|view_info
init|=
block|{
literal|"GimpChannelListView"
block|,
sizeof|sizeof
argument_list|(
name|GimpChannelListView
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpChannelListViewClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_channel_list_view_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_channel_list_view_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|view_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_DRAWABLE_LIST_VIEW
argument_list|,
operator|&
name|view_info
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
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpContainerViewClass
modifier|*
name|container_view_class
decl_stmt|;
name|GimpDrawableListViewClass
modifier|*
name|drawable_view_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|container_view_class
operator|=
operator|(
name|GimpContainerViewClass
operator|*
operator|)
name|klass
expr_stmt|;
name|drawable_view_class
operator|=
operator|(
name|GimpDrawableListViewClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_DRAWABLE_LIST_VIEW
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_channel_list_view_destroy
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
name|drawable_view_class
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
name|GtkWidget
modifier|*
name|pixmap
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
literal|"select_child"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_channel_list_view_component_toggle
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|component_list
argument_list|)
argument_list|,
literal|"unselect_child"
argument_list|,
name|GTK_SIGNAL_FUNC
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
name|gimp_button_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|drawable_view
operator|->
name|button_box
argument_list|)
argument_list|,
name|view
operator|->
name|toselection_button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|drawable_view
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
name|gtk_widget_show
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|,
name|_
argument_list|(
literal|"Channel to Selection \n"
literal|"<Shift> Add          "
literal|"<Ctrl> Subtract      "
literal|"<Shift><Ctrl> Intersect"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_channel_list_view_toselection_clicked
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|)
argument_list|,
literal|"extended_clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_channel_list_view_toselection_extended_clicked
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|gimp_pixmap_new
argument_list|(
name|toselection_xpm
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|)
argument_list|,
name|pixmap
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
name|gimp_gtk_drag_dest_set_by_type
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|GIMP_TYPE_CHANNEL
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|)
argument_list|,
name|GIMP_TYPE_CHANNEL
argument_list|,
name|gimp_channel_list_view_toselection_dropped
argument_list|,
name|view
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

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_destroy (GtkObject * object)
name|gimp_channel_list_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpChannelListView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
name|GIMP_CHANNEL_LIST_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
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
DECL|function|gimp_channel_list_view_set_image (GimpDrawableListView * view,GimpImage * gimage)
name|gimp_channel_list_view_set_image
parameter_list|(
name|GimpDrawableListView
modifier|*
name|view
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
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
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
name|gtk_signal_disconnect_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|gimage
argument_list|)
argument_list|,
name|gimp_channel_list_view_mode_changed
argument_list|,
name|channel_view
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_DRAWABLE_LIST_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
condition|)
name|GIMP_DRAWABLE_LIST_VIEW_CLASS
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
if|if
condition|(
name|view
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"mode_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_channel_list_view_mode_changed
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
name|GimpChannelListView
modifier|*
name|list_view
decl_stmt|;
name|gboolean
name|toselection_sensitive
init|=
name|FALSE
decl_stmt|;
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
name|item
condition|)
block|{
name|toselection_sensitive
operator|=
name|TRUE
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|list_view
operator|->
name|toselection_button
argument_list|,
name|toselection_sensitive
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

begin_comment
comment|/*  "To Selection" functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_to_selection (GimpChannelListView * view,GimpChannel * channel,ChannelOps operation)
name|gimp_channel_list_view_to_selection
parameter_list|(
name|GimpChannelListView
modifier|*
name|view
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|ChannelOps
name|operation
parameter_list|)
block|{
if|if
condition|(
name|channel
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpChannel
modifier|*
name|new_channel
decl_stmt|;
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|operation
operator|==
name|CHANNEL_OP_REPLACE
condition|)
block|{
name|new_channel
operator|=
name|channel
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new_channel
operator|=
name|gimp_channel_copy
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_channel_combine_mask
argument_list|(
name|new_channel
argument_list|,
name|channel
argument_list|,
name|operation
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gimage_mask_load
argument_list|(
name|gimage
argument_list|,
name|new_channel
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|new_channel
argument_list|)
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
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
name|GimpDrawableListView
modifier|*
name|drawable_view
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|drawable_view
operator|->
name|get_drawable_func
argument_list|(
name|drawable_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
name|gimp_channel_list_view_to_selection
argument_list|(
name|view
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|CHANNEL_OP_REPLACE
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
name|GimpDrawableListView
modifier|*
name|drawable_view
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|drawable_view
operator|->
name|get_drawable_func
argument_list|(
name|drawable_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
name|ChannelOps
name|operation
init|=
name|CHANNEL_OP_REPLACE
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
name|CHANNEL_OP_INTERSECT
expr_stmt|;
else|else
name|operation
operator|=
name|CHANNEL_OP_ADD
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
name|CHANNEL_OP_SUB
expr_stmt|;
block|}
name|gimp_channel_list_view_to_selection
argument_list|(
name|view
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|operation
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_view_toselection_dropped (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|gimp_channel_list_view_toselection_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpChannelListView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
operator|(
name|GimpChannelListView
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|viewable
operator|&&
name|gimp_container_have
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_channel_list_view_to_selection
argument_list|(
name|view
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|CHANNEL_OP_REPLACE
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
name|ChannelType
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
name|GIMP_DRAWABLE_LIST_VIEW
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
name|RGB
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
name|RED_CHANNEL
expr_stmt|;
name|components
index|[
literal|1
index|]
operator|=
name|GREEN_CHANNEL
expr_stmt|;
name|components
index|[
literal|2
index|]
operator|=
name|BLUE_CHANNEL
expr_stmt|;
break|break;
case|case
name|GRAY
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
name|GRAY_CHANNEL
expr_stmt|;
break|break;
case|case
name|INDEXED
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
name|INDEXED_CHANNEL
expr_stmt|;
break|break;
block|}
name|components
index|[
name|n_components
operator|++
index|]
operator|=
name|ALPHA_CHANNEL
expr_stmt|;
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
name|gtk_signal_handler_block_by_func
argument_list|(
name|GTK_OBJECT
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
name|gtk_signal_handler_unblock_by_func
argument_list|(
name|GTK_OBJECT
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
name|gtk_signal_handler_block_by_func
argument_list|(
name|GTK_OBJECT
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
name|GIMP_DRAWABLE_LIST_VIEW
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
name|gtk_signal_handler_unblock_by_func
argument_list|(
name|GTK_OBJECT
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

