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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
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
DECL|function|gimp_message_box (gchar * message,GtkCallback callback,gpointer data)
name|gimp_message_box
parameter_list|(
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
name|fprintf
argument_list|(
name|stderr
argument_list|,
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
name|fprintf
argument_list|(
name|stderr
argument_list|,
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
literal|"gimp_message"
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
name|_
argument_list|(
literal|"OK"
argument_list|)
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

begin_comment
comment|/*    * A workaround for what I think is a GTK+ bug:  *  If a dialog is hidden using gtk_widget_hide(),  *  and was iconified before, it is still present   *  in the window_list and can be deiconified by  *  the user later. All subsequent calls to   *  gtk_widget_hide() will then fail since the state  *  of the widget is still INVISIBLE.  *  Calling gdk_window_withdraw() seems to solve this.  *                                         --Sven  */
end_comment

begin_function
name|void
DECL|function|gimp_dialog_hide (GtkWidget * dialog)
name|gimp_dialog_hide
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|dialog
operator|!=
name|NULL
operator|&&
operator|!
name|GTK_WIDGET_NO_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gdk_window_withdraw
argument_list|(
name|dialog
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

