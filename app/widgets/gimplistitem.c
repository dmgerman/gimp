begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplistitem.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannellistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawablelistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimplayerlistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimplistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_list_item_class_init
parameter_list|(
name|GimpListItemClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_list_item_init
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_list_item_real_set_viewable
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_list_item_real_set_preview_size
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_list_item_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_list_item_drag_leave
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_list_item_drag_motion
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_list_item_drag_drop
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_list_item_name_changed
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpListItem
modifier|*
name|list_item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpViewable
modifier|*
name|gimp_list_item_drag_viewable
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkListItemClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_list_item_get_type (void)
name|gimp_list_item_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|list_item_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|list_item_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|list_item_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpListItemClass
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
name|gimp_list_item_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpListItem
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_list_item_init
block|,       }
decl_stmt|;
name|list_item_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_LIST_ITEM
argument_list|,
literal|"GimpListItem"
argument_list|,
operator|&
name|list_item_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|list_item_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_item_class_init (GimpListItemClass * klass)
name|gimp_list_item_class_init
parameter_list|(
name|GimpListItemClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|widget_class
operator|=
name|GTK_WIDGET_CLASS
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
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_list_item_expose_event
expr_stmt|;
name|widget_class
operator|->
name|drag_leave
operator|=
name|gimp_list_item_drag_leave
expr_stmt|;
name|widget_class
operator|->
name|drag_motion
operator|=
name|gimp_list_item_drag_motion
expr_stmt|;
name|widget_class
operator|->
name|drag_drop
operator|=
name|gimp_list_item_drag_drop
expr_stmt|;
name|klass
operator|->
name|set_viewable
operator|=
name|gimp_list_item_real_set_viewable
expr_stmt|;
name|klass
operator|->
name|set_preview_size
operator|=
name|gimp_list_item_real_set_preview_size
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_item_init (GimpListItem * list_item)
name|gimp_list_item_init
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|)
block|{
name|list_item
operator|->
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|list_item
operator|->
name|hbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|list_item
argument_list|)
argument_list|,
name|list_item
operator|->
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list_item
operator|->
name|hbox
argument_list|)
expr_stmt|;
name|list_item
operator|->
name|preview
operator|=
name|NULL
expr_stmt|;
name|list_item
operator|->
name|name_label
operator|=
name|NULL
expr_stmt|;
name|list_item
operator|->
name|preview_size
operator|=
literal|0
expr_stmt|;
name|list_item
operator|->
name|reorderable
operator|=
name|FALSE
expr_stmt|;
name|list_item
operator|->
name|drop_type
operator|=
name|GIMP_DROP_NONE
expr_stmt|;
name|list_item
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
name|list_item
operator|->
name|get_name_func
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_list_item_expose_event (GtkWidget * widget,GdkEventExpose * eevent)
name|gimp_list_item_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|)
block|{
name|GimpListItem
modifier|*
name|list_item
decl_stmt|;
name|list_item
operator|=
name|GIMP_LIST_ITEM
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|expose_event
argument_list|(
name|widget
argument_list|,
name|eevent
argument_list|)
expr_stmt|;
if|if
condition|(
name|list_item
operator|->
name|drop_type
operator|!=
name|GIMP_DROP_NONE
condition|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|x
operator|=
name|list_item
operator|->
name|name_label
operator|->
name|allocation
operator|.
name|x
expr_stmt|;
name|y
operator|=
operator|(
operator|(
name|list_item
operator|->
name|drop_type
operator|==
name|GIMP_DROP_ABOVE
operator|)
condition|?
literal|3
else|:
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
literal|4
operator|)
expr_stmt|;
name|gdk_gc_set_line_attributes
argument_list|(
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
literal|5
argument_list|,
name|GDK_LINE_SOLID
argument_list|,
name|GDK_CAP_BUTT
argument_list|,
name|GDK_JOIN_MITER
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_rectangle
argument_list|(
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
operator|&
name|eevent
operator|->
name|area
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|3
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_rectangle
argument_list|(
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_gc_set_line_attributes
argument_list|(
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
literal|0
argument_list|,
name|GDK_LINE_SOLID
argument_list|,
name|GDK_CAP_BUTT
argument_list|,
name|GDK_JOIN_MITER
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_item_drag_leave (GtkWidget * widget,GdkDragContext * context,guint time)
name|gimp_list_item_drag_leave
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
parameter_list|)
block|{
name|GimpListItem
modifier|*
name|list_item
decl_stmt|;
name|list_item
operator|=
name|GIMP_LIST_ITEM
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|list_item
operator|->
name|drop_type
operator|=
name|GIMP_DROP_NONE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_list_item_drag_motion (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time)
name|gimp_list_item_drag_motion
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
parameter_list|)
block|{
name|GimpListItem
modifier|*
name|list_item
decl_stmt|;
name|GimpViewable
modifier|*
name|src_viewable
decl_stmt|;
name|gint
name|dest_index
decl_stmt|;
name|GdkDragAction
name|drag_action
decl_stmt|;
name|GimpDropType
name|drop_type
decl_stmt|;
name|gboolean
name|return_val
decl_stmt|;
name|list_item
operator|=
name|GIMP_LIST_ITEM
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|return_val
operator|=
name|gimp_list_item_check_drag
argument_list|(
name|list_item
argument_list|,
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|src_viewable
argument_list|,
operator|&
name|dest_index
argument_list|,
operator|&
name|drag_action
argument_list|,
operator|&
name|drop_type
argument_list|)
expr_stmt|;
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
name|list_item
operator|->
name|drop_type
operator|!=
name|drop_type
condition|)
block|{
name|list_item
operator|->
name|drop_type
operator|=
name|drop_type
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
return|return
name|return_val
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_list_item_drag_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time)
name|gimp_list_item_drag_drop
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
parameter_list|)
block|{
name|GimpListItem
modifier|*
name|list_item
decl_stmt|;
name|GimpViewable
modifier|*
name|src_viewable
decl_stmt|;
name|gint
name|dest_index
decl_stmt|;
name|GdkDragAction
name|drag_action
decl_stmt|;
name|GimpDropType
name|drop_type
decl_stmt|;
name|gboolean
name|return_val
decl_stmt|;
name|list_item
operator|=
name|GIMP_LIST_ITEM
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|return_val
operator|=
name|gimp_list_item_check_drag
argument_list|(
name|list_item
argument_list|,
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|src_viewable
argument_list|,
operator|&
name|dest_index
argument_list|,
operator|&
name|drag_action
argument_list|,
operator|&
name|drop_type
argument_list|)
expr_stmt|;
name|gtk_drag_finish
argument_list|(
name|context
argument_list|,
name|return_val
argument_list|,
name|FALSE
argument_list|,
name|time
argument_list|)
expr_stmt|;
name|list_item
operator|->
name|drop_type
operator|=
name|GIMP_DROP_NONE
expr_stmt|;
if|if
condition|(
name|return_val
condition|)
block|{
name|gimp_container_reorder
argument_list|(
name|list_item
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|src_viewable
argument_list|)
argument_list|,
name|dest_index
argument_list|)
expr_stmt|;
block|}
return|return
name|return_val
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_list_item_new (GimpViewable * viewable,gint preview_size)
name|gimp_list_item_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|preview_size
parameter_list|)
block|{
name|GimpListItem
modifier|*
name|list_item
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|preview_size
operator|>
literal|0
operator|&&
name|preview_size
operator|<=
literal|256
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|list_item
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_LAYER_LIST_ITEM
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|list_item
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CHANNEL_LIST_ITEM
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|list_item
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DRAWABLE_LIST_ITEM
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|list_item
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_LIST_ITEM
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|list_item
operator|->
name|preview_size
operator|=
name|preview_size
expr_stmt|;
name|gimp_list_item_set_viewable
argument_list|(
name|list_item
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|list_item
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_list_item_set_viewable (GimpListItem * list_item,GimpViewable * viewable)
name|gimp_list_item_set_viewable
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LIST_ITEM
argument_list|(
name|list_item
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_LIST_ITEM_GET_CLASS
argument_list|(
name|list_item
argument_list|)
operator|->
name|set_viewable
argument_list|(
name|list_item
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_item_real_set_viewable (GimpListItem * list_item,GimpViewable * viewable)
name|gimp_list_item_real_set_viewable
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|list_item
operator|->
name|preview
operator|=
name|gimp_preview_new
argument_list|(
name|viewable
argument_list|,
name|list_item
operator|->
name|preview_size
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|list_item
operator|->
name|hbox
argument_list|)
argument_list|,
name|list_item
operator|->
name|preview
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list_item
operator|->
name|preview
argument_list|)
expr_stmt|;
name|list_item
operator|->
name|name_label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|list_item
operator|->
name|hbox
argument_list|)
argument_list|,
name|list_item
operator|->
name|name_label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list_item
operator|->
name|name_label
argument_list|)
expr_stmt|;
name|gimp_list_item_name_changed
argument_list|(
name|viewable
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
literal|"name_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_list_item_name_changed
argument_list|)
argument_list|,
name|list_item
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_gtk_drag_source_set_by_type
argument_list|(
name|GTK_WIDGET
argument_list|(
name|list_item
argument_list|)
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|GDK_ACTION_MOVE
operator||
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_source_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|list_item
argument_list|)
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|gimp_list_item_drag_viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_list_item_set_preview_size (GimpListItem * list_item,gint preview_size)
name|gimp_list_item_set_preview_size
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|gint
name|preview_size
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LIST_ITEM
argument_list|(
name|list_item
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|preview_size
operator|>
literal|0
operator|&&
name|preview_size
operator|<=
literal|256
comment|/* FIXME: 64 */
argument_list|)
expr_stmt|;
name|list_item
operator|->
name|preview_size
operator|=
name|preview_size
expr_stmt|;
name|GIMP_LIST_ITEM_GET_CLASS
argument_list|(
name|list_item
argument_list|)
operator|->
name|set_preview_size
argument_list|(
name|list_item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_item_real_set_preview_size (GimpListItem * list_item)
name|gimp_list_item_real_set_preview_size
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|preview
decl_stmt|;
name|preview
operator|=
name|GIMP_PREVIEW
argument_list|(
name|list_item
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gimp_preview_set_size
argument_list|(
name|preview
argument_list|,
name|list_item
operator|->
name|preview_size
argument_list|,
name|preview
operator|->
name|border_width
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_list_item_set_reorderable (GimpListItem * list_item,gboolean reorderable,GimpContainer * container)
name|gimp_list_item_set_reorderable
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|gboolean
name|reorderable
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|list_item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LIST_ITEM
argument_list|(
name|list_item
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|reorderable
operator|||
name|container
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|container
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|)
expr_stmt|;
name|list_item
operator|->
name|reorderable
operator|=
name|reorderable
expr_stmt|;
if|if
condition|(
name|reorderable
condition|)
block|{
name|list_item
operator|->
name|container
operator|=
name|container
expr_stmt|;
name|gimp_gtk_drag_dest_set_by_type
argument_list|(
name|GTK_WIDGET
argument_list|(
name|list_item
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|container
operator|->
name|children_type
argument_list|,
name|GDK_ACTION_MOVE
operator||
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|list_item
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
name|gtk_drag_dest_unset
argument_list|(
name|GTK_WIDGET
argument_list|(
name|list_item
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_list_item_set_name_func (GimpListItem * list_item,GimpItemGetNameFunc get_name_func)
name|gimp_list_item_set_name_func
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|GimpItemGetNameFunc
name|get_name_func
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|list_item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LIST_ITEM
argument_list|(
name|list_item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|list_item
operator|->
name|get_name_func
operator|!=
name|get_name_func
condition|)
block|{
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
name|list_item
operator|->
name|get_name_func
operator|=
name|get_name_func
expr_stmt|;
name|viewable
operator|=
name|GIMP_PREVIEW
argument_list|(
name|list_item
operator|->
name|preview
argument_list|)
operator|->
name|viewable
expr_stmt|;
if|if
condition|(
name|viewable
condition|)
name|gimp_list_item_name_changed
argument_list|(
name|viewable
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_list_item_check_drag (GimpListItem * list_item,GdkDragContext * context,gint x,gint y,GimpViewable ** src_viewable,gint * dest_index,GdkDragAction * drag_action,GimpDropType * drop_type)
name|gimp_list_item_check_drag
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
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
name|GimpViewable
modifier|*
modifier|*
name|src_viewable
parameter_list|,
name|gint
modifier|*
name|dest_index
parameter_list|,
name|GdkDragAction
modifier|*
name|drag_action
parameter_list|,
name|GimpDropType
modifier|*
name|drop_type
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|src_widget
decl_stmt|;
name|GimpViewable
modifier|*
name|my_src_viewable
init|=
name|NULL
decl_stmt|;
name|GimpViewable
modifier|*
name|my_dest_viewable
init|=
name|NULL
decl_stmt|;
name|gint
name|my_src_index
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|my_dest_index
init|=
operator|-
literal|1
decl_stmt|;
name|GdkDragAction
name|my_drag_action
init|=
name|GDK_ACTION_DEFAULT
decl_stmt|;
name|GimpDropType
name|my_drop_type
init|=
name|GIMP_DROP_NONE
decl_stmt|;
name|gboolean
name|return_val
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|list_item
operator|->
name|reorderable
operator|&&
name|list_item
operator|->
name|container
operator|&&
operator|(
name|src_widget
operator|=
name|gtk_drag_get_source_widget
argument_list|(
name|context
argument_list|)
operator|)
operator|&&
name|src_widget
operator|!=
name|GTK_WIDGET
argument_list|(
name|list_item
argument_list|)
condition|)
block|{
name|my_src_viewable
operator|=
name|gimp_dnd_get_drag_data
argument_list|(
name|src_widget
argument_list|)
expr_stmt|;
name|my_dest_viewable
operator|=
name|GIMP_PREVIEW
argument_list|(
name|list_item
operator|->
name|preview
argument_list|)
operator|->
name|viewable
expr_stmt|;
if|if
condition|(
name|my_src_viewable
operator|&&
name|my_dest_viewable
condition|)
block|{
name|my_src_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|list_item
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|my_src_viewable
argument_list|)
argument_list|)
expr_stmt|;
name|my_dest_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|list_item
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|my_dest_viewable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|my_src_viewable
operator|&&
name|my_src_index
operator|!=
operator|-
literal|1
operator|&&
name|my_dest_viewable
operator|&&
name|my_dest_index
operator|!=
operator|-
literal|1
condition|)
block|{
name|gint
name|difference
decl_stmt|;
name|difference
operator|=
name|my_dest_index
operator|-
name|my_src_index
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|GTK_WIDGET
argument_list|(
name|list_item
argument_list|)
operator|->
name|allocation
operator|.
name|height
operator|/
literal|2
condition|)
name|my_drop_type
operator|=
name|GIMP_DROP_ABOVE
expr_stmt|;
else|else
name|my_drop_type
operator|=
name|GIMP_DROP_BELOW
expr_stmt|;
if|if
condition|(
name|difference
operator|<
literal|0
operator|&&
name|my_drop_type
operator|==
name|GIMP_DROP_BELOW
condition|)
block|{
name|my_dest_index
operator|++
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|difference
operator|>
literal|0
operator|&&
name|my_drop_type
operator|==
name|GIMP_DROP_ABOVE
condition|)
block|{
name|my_dest_index
operator|--
expr_stmt|;
block|}
if|if
condition|(
name|my_src_index
operator|!=
name|my_dest_index
condition|)
block|{
name|my_drag_action
operator|=
name|GDK_ACTION_MOVE
expr_stmt|;
name|return_val
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|my_drop_type
operator|=
name|GIMP_DROP_NONE
expr_stmt|;
block|}
block|}
block|}
block|}
operator|*
name|src_viewable
operator|=
name|my_src_viewable
expr_stmt|;
operator|*
name|dest_index
operator|=
name|my_dest_index
expr_stmt|;
operator|*
name|drag_action
operator|=
name|my_drag_action
expr_stmt|;
operator|*
name|drop_type
operator|=
name|my_drop_type
expr_stmt|;
return|return
name|return_val
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_list_item_button_realize (GtkWidget * widget,gpointer data)
name|gimp_list_item_button_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gdk_window_set_back_pixmap
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_list_item_button_state_changed (GtkWidget * widget,GtkStateType previous_state,gpointer data)
name|gimp_list_item_button_state_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStateType
name|previous_state
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|list_item
decl_stmt|;
name|list_item
operator|=
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
operator|->
name|state
operator|!=
name|list_item
operator|->
name|state
condition|)
block|{
switch|switch
condition|(
name|widget
operator|->
name|state
condition|)
block|{
case|case
name|GTK_STATE_NORMAL
case|:
case|case
name|GTK_STATE_ACTIVE
case|:
comment|/*  beware: recursion  */
name|gtk_widget_set_state
argument_list|(
name|widget
argument_list|,
name|list_item
operator|->
name|state
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
elseif|else
if|if
condition|(
name|list_item
operator|->
name|state
operator|==
name|GTK_STATE_INSENSITIVE
condition|)
block|{
comment|/*  Don't look here, no, please...        *         *  I said NO ...        */
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|list_item
argument_list|)
condition|)
block|{
name|GdkRectangle
name|rect
decl_stmt|;
name|rect
operator|.
name|x
operator|=
name|widget
operator|->
name|allocation
operator|.
name|x
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|widget
operator|->
name|allocation
operator|.
name|y
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|widget
operator|->
name|allocation
operator|.
name|height
expr_stmt|;
name|gdk_window_invalidate_rect
argument_list|(
name|list_item
operator|->
name|window
argument_list|,
operator|&
name|rect
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gdk_window_process_updates
argument_list|(
name|list_item
operator|->
name|window
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_item_name_changed (GimpViewable * viewable,GimpListItem * list_item)
name|gimp_list_item_name_changed
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpListItem
modifier|*
name|list_item
parameter_list|)
block|{
if|if
condition|(
name|list_item
operator|->
name|get_name_func
condition|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|name
operator|=
name|list_item
operator|->
name|get_name_func
argument_list|(
name|GTK_WIDGET
argument_list|(
name|list_item
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|list_item
operator|->
name|name_label
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|list_item
operator|->
name|name_label
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GimpViewable
modifier|*
DECL|function|gimp_list_item_drag_viewable (GtkWidget * widget,gpointer data)
name|gimp_list_item_drag_viewable
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
name|GIMP_PREVIEW
argument_list|(
name|GIMP_LIST_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|preview
argument_list|)
operator|->
name|viewable
return|;
block|}
end_function

end_unit

