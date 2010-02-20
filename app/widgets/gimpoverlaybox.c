begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpOverlayBox  * Copyright (C) 2009 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_undef
undef|#
directive|undef
name|GSEAL_ENABLE
end_undef

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
file|"gimpoverlaybox.h"
end_include

begin_include
include|#
directive|include
file|"gimpoverlaychild.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_overlay_box_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_box_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_box_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_box_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_box_size_request
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkRequisition
modifier|*
name|requisition
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_box_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_overlay_box_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_overlay_box_damage
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_box_add
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_box_remove
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_box_forall
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|gboolean
name|include_internals
parameter_list|,
name|GtkCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GType
name|gimp_overlay_box_child_type
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkWindow
modifier|*
name|gimp_overlay_box_pick_embedded_child
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpOverlayBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOverlayBox,gimp_overlay_box,GTK_TYPE_CONTAINER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOverlayBox
argument_list|,
argument|gimp_overlay_box
argument_list|,
argument|GTK_TYPE_CONTAINER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_overlay_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_overlay_box_class_init
parameter_list|(
name|GimpOverlayBoxClass
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
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkContainerClass
modifier|*
name|container_class
init|=
name|GTK_CONTAINER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_overlay_box_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_overlay_box_get_property
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_overlay_box_realize
expr_stmt|;
name|widget_class
operator|->
name|unrealize
operator|=
name|gimp_overlay_box_unrealize
expr_stmt|;
name|widget_class
operator|->
name|size_request
operator|=
name|gimp_overlay_box_size_request
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_overlay_box_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_overlay_box_expose
expr_stmt|;
name|g_signal_override_class_handler
argument_list|(
literal|"damage-event"
argument_list|,
name|GIMP_TYPE_OVERLAY_BOX
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_overlay_box_damage
argument_list|)
argument_list|)
expr_stmt|;
name|container_class
operator|->
name|add
operator|=
name|gimp_overlay_box_add
expr_stmt|;
name|container_class
operator|->
name|remove
operator|=
name|gimp_overlay_box_remove
expr_stmt|;
name|container_class
operator|->
name|forall
operator|=
name|gimp_overlay_box_forall
expr_stmt|;
name|container_class
operator|->
name|child_type
operator|=
name|gimp_overlay_box_child_type
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_box_init (GimpOverlayBox * box)
name|gimp_overlay_box_init
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_box_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_overlay_box_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
switch|switch
condition|(
name|property_id
condition|)
block|{
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_box_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_overlay_box_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
switch|switch
condition|(
name|property_id
condition|)
block|{
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_box_realize (GtkWidget * widget)
name|gimp_overlay_box_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpOverlayBox
modifier|*
name|box
init|=
name|GIMP_OVERLAY_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|GdkWindowAttr
name|attributes
decl_stmt|;
name|gint
name|attributes_mask
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|widget
argument_list|,
name|GTK_REALIZED
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|attributes
operator|.
name|x
operator|=
name|allocation
operator|.
name|x
expr_stmt|;
name|attributes
operator|.
name|y
operator|=
name|allocation
operator|.
name|y
expr_stmt|;
name|attributes
operator|.
name|width
operator|=
name|allocation
operator|.
name|width
expr_stmt|;
name|attributes
operator|.
name|height
operator|=
name|allocation
operator|.
name|height
expr_stmt|;
name|attributes
operator|.
name|window_type
operator|=
name|GDK_WINDOW_CHILD
expr_stmt|;
name|attributes
operator|.
name|wclass
operator|=
name|GDK_INPUT_OUTPUT
expr_stmt|;
name|attributes
operator|.
name|visual
operator|=
name|gtk_widget_get_visual
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|attributes
operator|.
name|colormap
operator|=
name|gtk_widget_get_colormap
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|attributes
operator|.
name|event_mask
operator|=
name|gtk_widget_get_events
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|attributes_mask
operator|=
name|GDK_WA_X
operator||
name|GDK_WA_Y
operator||
name|GDK_WA_VISUAL
operator||
name|GDK_WA_COLORMAP
expr_stmt|;
name|gtk_widget_set_window
argument_list|(
name|widget
argument_list|,
name|gdk_window_new
argument_list|(
name|gtk_widget_get_parent_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|attributes
argument_list|,
name|attributes_mask
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_window_set_user_data
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"pick-embedded-child"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_overlay_box_pick_embedded_child
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|widget
operator|->
name|style
operator|=
name|gtk_style_attach
argument_list|(
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
argument_list|,
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_style_set_background
argument_list|(
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
argument_list|,
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_STATE_NORMAL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|box
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
name|gimp_overlay_child_realize
argument_list|(
name|box
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_box_unrealize (GtkWidget * widget)
name|gimp_overlay_box_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpOverlayBox
modifier|*
name|box
init|=
name|GIMP_OVERLAY_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|box
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
name|gimp_overlay_child_unrealize
argument_list|(
name|box
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|unrealize
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_box_size_request (GtkWidget * widget,GtkRequisition * requisition)
name|gimp_overlay_box_size_request
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkRequisition
modifier|*
name|requisition
parameter_list|)
block|{
name|GimpOverlayBox
modifier|*
name|box
init|=
name|GIMP_OVERLAY_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
name|border_width
operator|=
name|gtk_container_get_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|requisition
operator|->
name|width
operator|=
literal|1
operator|+
literal|2
operator|*
name|border_width
expr_stmt|;
name|requisition
operator|->
name|height
operator|=
literal|1
operator|+
literal|2
operator|*
name|border_width
expr_stmt|;
for|for
control|(
name|list
operator|=
name|box
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
name|gimp_overlay_child_size_request
argument_list|(
name|box
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_box_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_overlay_box_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
block|{
name|GimpOverlayBox
modifier|*
name|box
init|=
name|GIMP_OVERLAY_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gtk_widget_set_allocation
argument_list|(
name|widget
argument_list|,
name|allocation
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_REALIZED
argument_list|(
name|widget
argument_list|)
condition|)
name|gdk_window_move_resize
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|allocation
operator|->
name|x
argument_list|,
name|allocation
operator|->
name|y
argument_list|,
name|allocation
operator|->
name|width
argument_list|,
name|allocation
operator|->
name|height
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|box
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
name|gimp_overlay_child_size_allocate
argument_list|(
name|box
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_overlay_box_expose (GtkWidget * widget,GdkEventExpose * event)
name|gimp_overlay_box_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
block|{
if|if
condition|(
name|gtk_widget_is_drawable
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GimpOverlayBox
modifier|*
name|box
init|=
name|GIMP_OVERLAY_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|box
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
if|if
condition|(
name|gimp_overlay_child_expose
argument_list|(
name|box
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|event
argument_list|)
condition|)
return|return
name|TRUE
return|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_overlay_box_damage (GtkWidget * widget,GdkEventExpose * event)
name|gimp_overlay_box_damage
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
block|{
name|GimpOverlayBox
modifier|*
name|box
init|=
name|GIMP_OVERLAY_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|box
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
if|if
condition|(
name|gimp_overlay_child_damage
argument_list|(
name|box
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|event
argument_list|)
condition|)
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
DECL|function|gimp_overlay_box_add (GtkContainer * container,GtkWidget * widget)
name|gimp_overlay_box_add
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gimp_overlay_box_add_child
argument_list|(
name|GIMP_OVERLAY_BOX
argument_list|(
name|container
argument_list|)
argument_list|,
name|widget
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_box_remove (GtkContainer * container,GtkWidget * widget)
name|gimp_overlay_box_remove
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpOverlayBox
modifier|*
name|box
init|=
name|GIMP_OVERLAY_BOX
argument_list|(
name|container
argument_list|)
decl_stmt|;
name|GimpOverlayChild
modifier|*
name|child
init|=
name|gimp_overlay_child_find
argument_list|(
name|box
argument_list|,
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|child
condition|)
block|{
if|if
condition|(
name|gtk_widget_get_visible
argument_list|(
name|widget
argument_list|)
condition|)
name|gimp_overlay_child_invalidate
argument_list|(
name|box
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|box
operator|->
name|children
operator|=
name|g_list_remove
argument_list|(
name|box
operator|->
name|children
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|gimp_overlay_child_free
argument_list|(
name|box
argument_list|,
name|child
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_box_forall (GtkContainer * container,gboolean include_internals,GtkCallback callback,gpointer callback_data)
name|gimp_overlay_box_forall
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|gboolean
name|include_internals
parameter_list|,
name|GtkCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GimpOverlayBox
modifier|*
name|box
init|=
name|GIMP_OVERLAY_BOX
argument_list|(
name|container
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|box
operator|->
name|children
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|GimpOverlayChild
modifier|*
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
name|list
operator|=
name|list
operator|->
name|next
expr_stmt|;
call|(
modifier|*
name|callback
call|)
argument_list|(
name|child
operator|->
name|widget
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GType
DECL|function|gimp_overlay_box_child_type (GtkContainer * container)
name|gimp_overlay_box_child_type
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|)
block|{
return|return
name|GTK_TYPE_WIDGET
return|;
block|}
end_function

begin_function
specifier|static
name|GdkWindow
modifier|*
DECL|function|gimp_overlay_box_pick_embedded_child (GdkWindow * parent,gdouble parent_x,gdouble parent_y,GimpOverlayBox * box)
name|gimp_overlay_box_pick_embedded_child
parameter_list|(
name|GdkWindow
modifier|*
name|parent
parameter_list|,
name|gdouble
name|parent_x
parameter_list|,
name|gdouble
name|parent_y
parameter_list|,
name|GimpOverlayBox
modifier|*
name|box
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|box
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
name|GimpOverlayChild
modifier|*
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_overlay_child_pick
argument_list|(
name|box
argument_list|,
name|child
argument_list|,
name|parent_x
argument_list|,
name|parent_y
argument_list|)
condition|)
return|return
name|child
operator|->
name|window
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_overlay_box_new:  *  * Creates a new #GimpOverlayBox widget.  *  * Return value: a new #GimpOverlayBox widget  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_overlay_box_new (void)
name|gimp_overlay_box_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_OVERLAY_BOX
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_box_add_child (GimpOverlayBox * box,GtkWidget * widget,gdouble xalign,gdouble yalign)
name|gimp_overlay_box_add_child
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|xalign
parameter_list|,
name|gdouble
name|yalign
parameter_list|)
block|{
name|GimpOverlayChild
modifier|*
name|child
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|child
operator|=
name|gimp_overlay_child_new
argument_list|(
name|box
argument_list|,
name|widget
argument_list|,
name|xalign
argument_list|,
name|yalign
argument_list|,
literal|0.0
argument_list|,
literal|0.7
argument_list|)
expr_stmt|;
name|box
operator|->
name|children
operator|=
name|g_list_append
argument_list|(
name|box
operator|->
name|children
argument_list|,
name|child
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_box_set_child_alignment (GimpOverlayBox * box,GtkWidget * widget,gdouble xalign,gdouble yalign)
name|gimp_overlay_box_set_child_alignment
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|xalign
parameter_list|,
name|gdouble
name|yalign
parameter_list|)
block|{
name|GimpOverlayChild
modifier|*
name|child
init|=
name|gimp_overlay_child_find
argument_list|(
name|box
argument_list|,
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|child
condition|)
block|{
name|xalign
operator|=
name|CLAMP
argument_list|(
name|xalign
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|yalign
operator|=
name|CLAMP
argument_list|(
name|yalign
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
operator|->
name|has_position
operator|||
name|child
operator|->
name|xalign
operator|!=
name|xalign
operator|||
name|child
operator|->
name|yalign
operator|!=
name|yalign
condition|)
block|{
name|gimp_overlay_child_invalidate
argument_list|(
name|box
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|child
operator|->
name|has_position
operator|=
name|FALSE
expr_stmt|;
name|child
operator|->
name|xalign
operator|=
name|xalign
expr_stmt|;
name|child
operator|->
name|yalign
operator|=
name|yalign
expr_stmt|;
name|gtk_widget_queue_resize
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_box_set_child_position (GimpOverlayBox * box,GtkWidget * widget,gdouble x,gdouble y)
name|gimp_overlay_box_set_child_position
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpOverlayChild
modifier|*
name|child
init|=
name|gimp_overlay_child_find
argument_list|(
name|box
argument_list|,
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|child
condition|)
block|{
if|if
condition|(
operator|!
name|child
operator|->
name|has_position
operator|||
name|child
operator|->
name|x
operator|!=
name|x
operator|||
name|child
operator|->
name|y
operator|!=
name|y
condition|)
block|{
name|gimp_overlay_child_invalidate
argument_list|(
name|box
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|child
operator|->
name|has_position
operator|=
name|TRUE
expr_stmt|;
name|child
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|child
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|gtk_widget_queue_resize
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_box_set_child_angle (GimpOverlayBox * box,GtkWidget * widget,gdouble angle)
name|gimp_overlay_box_set_child_angle
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
name|GimpOverlayChild
modifier|*
name|child
init|=
name|gimp_overlay_child_find
argument_list|(
name|box
argument_list|,
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|child
condition|)
block|{
if|if
condition|(
name|child
operator|->
name|angle
operator|!=
name|angle
condition|)
block|{
name|gimp_overlay_child_invalidate
argument_list|(
name|box
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|child
operator|->
name|angle
operator|=
name|angle
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_box_set_child_opacity (GimpOverlayBox * box,GtkWidget * widget,gdouble opacity)
name|gimp_overlay_box_set_child_opacity
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
block|{
name|GimpOverlayChild
modifier|*
name|child
init|=
name|gimp_overlay_child_find
argument_list|(
name|box
argument_list|,
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|child
condition|)
block|{
name|opacity
operator|=
name|CLAMP
argument_list|(
name|opacity
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
operator|->
name|opacity
operator|!=
name|opacity
condition|)
block|{
name|child
operator|->
name|opacity
operator|=
name|opacity
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_overlay_box_scroll:  * @box: the #GimpOverlayBox widget to scroll.  * @offset_x: the x scroll amount.  * @offset_y: the y scroll amount.  *  * Scrolls the box using gdk_window_scroll() and makes sure the result  * is displayed immediately by calling gdk_window_process_updates().  **/
end_comment

begin_function
name|void
DECL|function|gimp_overlay_box_scroll (GimpOverlayBox * box,gint offset_x,gint offset_y)
name|gimp_overlay_box_scroll
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|widget
operator|=
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|window
operator|=
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
expr_stmt|;
comment|/*  Undraw all overlays  */
for|for
control|(
name|list
operator|=
name|box
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
name|GimpOverlayChild
modifier|*
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_overlay_child_invalidate
argument_list|(
name|box
argument_list|,
name|child
argument_list|)
expr_stmt|;
block|}
name|gdk_window_scroll
argument_list|(
name|window
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
comment|/*  Re-draw all overlays  */
for|for
control|(
name|list
operator|=
name|box
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
name|GimpOverlayChild
modifier|*
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_overlay_child_invalidate
argument_list|(
name|box
argument_list|,
name|child
argument_list|)
expr_stmt|;
block|}
comment|/*  Make sure expose events are processed before scrolling again  */
name|gdk_window_process_updates
argument_list|(
name|window
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

