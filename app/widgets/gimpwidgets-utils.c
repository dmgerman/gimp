begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpui.c  * Copyright (C) 1999 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|prog_name
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|gimp_message_box_close_callback
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

begin_comment
comment|/*  *  Message Boxes...  */
end_comment

begin_typedef
DECL|typedef|MessageBox
typedef|typedef
name|struct
name|_MessageBox
name|MessageBox
typedef|;
end_typedef

begin_struct
DECL|struct|_MessageBox
struct|struct
name|_MessageBox
block|{
DECL|member|mbox
name|GtkWidget
modifier|*
name|mbox
decl_stmt|;
DECL|member|repeat_label
name|GtkWidget
modifier|*
name|repeat_label
decl_stmt|;
DECL|member|message
name|gchar
modifier|*
name|message
decl_stmt|;
DECL|member|repeat_count
name|gint
name|repeat_count
decl_stmt|;
DECL|member|callback
name|GtkCallback
name|callback
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  the maximum number of concucrrent dialog boxes */
end_comment

begin_define
DECL|macro|MESSAGE_BOX_MAXIMUM
define|#
directive|define
name|MESSAGE_BOX_MAXIMUM
value|4
end_define

begin_decl_stmt
DECL|variable|message_boxes
specifier|static
name|GList
modifier|*
name|message_boxes
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_message_box (const gchar * message,GtkCallback callback,gpointer data)
name|gimp_message_box
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|GtkCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|MessageBox
modifier|*
name|msg_box
decl_stmt|;
name|GtkWidget
modifier|*
name|mbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
operator|!
name|message
condition|)
return|return;
if|if
condition|(
name|g_list_length
argument_list|(
name|message_boxes
argument_list|)
operator|>
name|MESSAGE_BOX_MAXIMUM
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: %s\n"
argument_list|,
name|prog_name
argument_list|,
name|message
argument_list|)
expr_stmt|;
return|return;
block|}
for|for
control|(
name|list
operator|=
name|message_boxes
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|msg_box
operator|=
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|msg_box
operator|->
name|message
argument_list|,
name|message
argument_list|)
operator|==
literal|0
condition|)
block|{
name|msg_box
operator|->
name|repeat_count
operator|++
expr_stmt|;
if|if
condition|(
name|msg_box
operator|->
name|repeat_count
operator|>
literal|1
condition|)
block|{
name|gchar
modifier|*
name|text
init|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Message repeated %d times"
argument_list|)
argument_list|,
name|msg_box
operator|->
name|repeat_count
argument_list|)
decl_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|msg_box
operator|->
name|repeat_label
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gdk_window_raise
argument_list|(
name|msg_box
operator|->
name|mbox
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|msg_box
operator|->
name|mbox
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|msg_box
operator|->
name|repeat_label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Message repeated once"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|msg_box
operator|->
name|repeat_label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|msg_box
operator|->
name|repeat_label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gdk_window_raise
argument_list|(
name|msg_box
operator|->
name|mbox
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
return|return;
block|}
block|}
if|if
condition|(
name|g_list_length
argument_list|(
name|message_boxes
argument_list|)
operator|==
name|MESSAGE_BOX_MAXIMUM
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: %s\n"
argument_list|,
name|prog_name
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|message
operator|=
name|_
argument_list|(
literal|"WARNING:\n"
literal|"Too many open message dialogs.\n"
literal|"Messages are redirected to stderr."
argument_list|)
expr_stmt|;
block|}
name|msg_box
operator|=
name|g_new0
argument_list|(
name|MessageBox
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|mbox
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"GIMP Message"
argument_list|)
argument_list|,
literal|"gimp-message"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|gimp_message_box_close_callback
argument_list|,
name|msg_box
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|mbox
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|msg_box
operator|->
name|mbox
operator|=
name|mbox
expr_stmt|;
name|msg_box
operator|->
name|message
operator|=
name|g_strdup
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|msg_box
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|msg_box
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|message_boxes
operator|=
name|g_list_append
argument_list|(
name|message_boxes
argument_list|,
name|msg_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|mbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_close_callback (GtkWidget * widget,gpointer data)
name|gimp_message_box_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|MessageBox
modifier|*
name|msg_box
decl_stmt|;
name|msg_box
operator|=
operator|(
name|MessageBox
operator|*
operator|)
name|data
expr_stmt|;
comment|/*  If there is a valid callback, invoke it  */
if|if
condition|(
name|msg_box
operator|->
name|callback
condition|)
call|(
modifier|*
name|msg_box
operator|->
name|callback
call|)
argument_list|(
name|widget
argument_list|,
name|msg_box
operator|->
name|data
argument_list|)
expr_stmt|;
comment|/*  Destroy the box  */
name|gtk_widget_destroy
argument_list|(
name|msg_box
operator|->
name|mbox
argument_list|)
expr_stmt|;
comment|/* make this box available again */
name|message_boxes
operator|=
name|g_list_remove
argument_list|(
name|message_boxes
argument_list|,
name|msg_box
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|msg_box
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|msg_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_menu_position (GtkMenu * menu,gint * x,gint * y,guint * button,guint32 * activate_time)
name|gimp_menu_position
parameter_list|(
name|GtkMenu
modifier|*
name|menu
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|guint
modifier|*
name|button
parameter_list|,
name|guint32
modifier|*
name|activate_time
parameter_list|)
block|{
name|GdkEvent
modifier|*
name|current_event
decl_stmt|;
name|GtkRequisition
name|requisition
decl_stmt|;
name|gint
name|pointer_x
decl_stmt|;
name|gint
name|pointer_y
decl_stmt|;
name|gint
name|screen_width
decl_stmt|;
name|gint
name|screen_height
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_MENU
argument_list|(
name|menu
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|x
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|y
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|button
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|activate_time
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gdk_window_get_pointer
argument_list|(
name|NULL
argument_list|,
operator|&
name|pointer_x
argument_list|,
operator|&
name|pointer_y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|menu
argument_list|)
argument_list|,
operator|&
name|requisition
argument_list|)
expr_stmt|;
name|screen_width
operator|=
name|gdk_screen_width
argument_list|()
operator|+
literal|2
expr_stmt|;
name|screen_height
operator|=
name|gdk_screen_height
argument_list|()
operator|+
literal|2
expr_stmt|;
operator|*
name|x
operator|=
name|CLAMP
argument_list|(
name|pointer_x
argument_list|,
literal|2
argument_list|,
name|MAX
argument_list|(
literal|0
argument_list|,
name|screen_width
operator|-
name|requisition
operator|.
name|width
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|y
operator|=
name|CLAMP
argument_list|(
name|pointer_y
argument_list|,
literal|2
argument_list|,
name|MAX
argument_list|(
literal|0
argument_list|,
name|screen_height
operator|-
name|requisition
operator|.
name|height
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|x
operator|+=
operator|(
name|pointer_x
operator|<=
operator|*
name|x
operator|)
condition|?
literal|2
else|:
operator|-
literal|2
expr_stmt|;
operator|*
name|y
operator|+=
operator|(
name|pointer_y
operator|<=
operator|*
name|y
operator|)
condition|?
literal|2
else|:
operator|-
literal|2
expr_stmt|;
operator|*
name|x
operator|=
name|MAX
argument_list|(
operator|*
name|x
argument_list|,
literal|0
argument_list|)
expr_stmt|;
operator|*
name|y
operator|=
name|MAX
argument_list|(
operator|*
name|y
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|current_event
operator|=
name|gtk_get_current_event
argument_list|()
expr_stmt|;
if|if
condition|(
name|current_event
operator|&&
name|current_event
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
block|{
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
name|bevent
operator|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|current_event
expr_stmt|;
operator|*
name|button
operator|=
name|bevent
operator|->
name|button
expr_stmt|;
operator|*
name|activate_time
operator|=
name|bevent
operator|->
name|time
expr_stmt|;
block|}
else|else
block|{
operator|*
name|button
operator|=
literal|0
expr_stmt|;
operator|*
name|activate_time
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_typedef
DECL|typedef|GimpAccelContextData
typedef|typedef
name|struct
name|_GimpAccelContextData
name|GimpAccelContextData
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpAccelContextData
struct|struct
name|_GimpAccelContextData
block|{
DECL|member|item_factory
name|GtkItemFactory
modifier|*
name|item_factory
decl_stmt|;
DECL|member|get_context_func
name|GimpGetAccelContextFunc
name|get_context_func
decl_stmt|;
DECL|member|get_context_data
name|gpointer
name|get_context_data
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|gboolean
DECL|function|gimp_window_accel_key_press (GtkWidget * widget,GdkEvent * event,GimpAccelContextData * context_data)
name|gimp_window_accel_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpAccelContextData
modifier|*
name|context_data
parameter_list|)
block|{
name|gpointer
name|accel_context
decl_stmt|;
name|accel_context
operator|=
name|context_data
operator|->
name|get_context_func
argument_list|(
name|context_data
operator|->
name|get_context_data
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|context_data
operator|->
name|item_factory
argument_list|)
argument_list|,
literal|"gimp-accel-context"
argument_list|,
name|accel_context
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_window_accel_key_release (GtkWidget * widget,GdkEvent * event,GimpAccelContextData * context_data)
name|gimp_window_accel_key_release
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpAccelContextData
modifier|*
name|context_data
parameter_list|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|context_data
operator|->
name|item_factory
argument_list|)
argument_list|,
literal|"gimp-accel-context"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_window_add_accel_group (GtkWindow * window,GtkItemFactory * item_factory,GimpGetAccelContextFunc get_context_func,gpointer get_context_data)
name|gimp_window_add_accel_group
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|GtkItemFactory
modifier|*
name|item_factory
parameter_list|,
name|GimpGetAccelContextFunc
name|get_context_func
parameter_list|,
name|gpointer
name|get_context_data
parameter_list|)
block|{
if|if
condition|(
name|get_context_func
condition|)
block|{
name|GimpAccelContextData
modifier|*
name|context_data
decl_stmt|;
name|context_data
operator|=
name|g_new0
argument_list|(
name|GimpAccelContextData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|context_data
operator|->
name|item_factory
operator|=
name|item_factory
expr_stmt|;
name|context_data
operator|->
name|get_context_func
operator|=
name|get_context_func
expr_stmt|;
name|context_data
operator|->
name|get_context_data
operator|=
name|get_context_data
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"gimp-accel-conext-data"
argument_list|,
name|context_data
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"key_press_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_window_accel_key_press
argument_list|)
argument_list|,
name|context_data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"key_release_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_window_accel_key_release
argument_list|)
argument_list|,
name|context_data
argument_list|)
expr_stmt|;
block|}
name|gtk_window_add_accel_group
argument_list|(
name|window
argument_list|,
name|item_factory
operator|->
name|accel_group
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_window_remove_accel_group (GtkWindow * window,GtkItemFactory * item_factory)
name|gimp_window_remove_accel_group
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|GtkItemFactory
modifier|*
name|item_factory
parameter_list|)
block|{
name|GimpAccelContextData
modifier|*
name|context_data
decl_stmt|;
name|context_data
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"gimp-accel-conext-data"
argument_list|)
expr_stmt|;
if|if
condition|(
name|context_data
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_window_accel_key_press
argument_list|)
argument_list|,
name|context_data
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_window_accel_key_release
argument_list|)
argument_list|,
name|context_data
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"gimp-accel-conext-data"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gtk_window_remove_accel_group
argument_list|(
name|window
argument_list|,
name|item_factory
operator|->
name|accel_group
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gpointer
DECL|function|gimp_widget_get_callback_context (GtkWidget * widget)
name|gimp_widget_get_callback_context
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GtkItemFactory
modifier|*
name|ifactory
decl_stmt|;
name|gpointer
name|popup_context
decl_stmt|;
name|gpointer
name|accel_context
init|=
name|NULL
decl_stmt|;
name|ifactory
operator|=
name|gtk_item_factory_from_widget
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|popup_context
operator|=
name|gtk_item_factory_popup_data_from_widget
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|ifactory
condition|)
name|accel_context
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|ifactory
argument_list|)
argument_list|,
literal|"gimp-accel-context"
argument_list|)
expr_stmt|;
if|if
condition|(
name|popup_context
condition|)
return|return
name|popup_context
return|;
return|return
name|accel_context
return|;
block|}
end_function

end_unit

