begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpwidgets-utils.c  * Copyright (C) 1999-2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
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
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
DECL|member|repeat_label
name|GtkWidget
modifier|*
name|repeat_label
decl_stmt|;
DECL|member|domain
name|gchar
modifier|*
name|domain
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
comment|/*  the maximum number of concurrent dialog boxes */
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
DECL|function|gimp_message_box (const gchar * stock_id,const gchar * domain,const gchar * message,GtkCallback callback,gpointer data)
name|gimp_message_box
parameter_list|(
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
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
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|PangoAttrList
modifier|*
name|attrs
decl_stmt|;
name|PangoAttribute
modifier|*
name|attr
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|stock_id
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|message
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|domain
condition|)
name|domain
operator|=
name|_
argument_list|(
literal|"GIMP"
argument_list|)
expr_stmt|;
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
name|domain
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
operator|&&
name|strcmp
argument_list|(
name|msg_box
operator|->
name|domain
argument_list|,
name|domain
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
literal|"Message repeated %d times."
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
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|attrs
operator|=
name|pango_attr_list_new
argument_list|()
expr_stmt|;
name|attr
operator|=
name|pango_attr_style_new
argument_list|(
name|PANGO_STYLE_OBLIQUE
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
literal|0
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
operator|-
literal|1
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrs
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Message repeated once."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|attrs
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|msg_box
operator|->
name|vbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|pango_attr_list_unref
argument_list|(
name|attrs
argument_list|)
expr_stmt|;
name|msg_box
operator|->
name|repeat_label
operator|=
name|label
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|msg_box
operator|->
name|mbox
argument_list|)
argument_list|)
expr_stmt|;
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
name|domain
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
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|mbox
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_dialog_set_has_separator
argument_list|(
name|GTK_DIALOG
argument_list|(
name|mbox
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|10
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
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|stock_id
argument_list|,
name|GTK_ICON_SIZE_DIALOG
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|image
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|image
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
name|image
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|attrs
operator|=
name|pango_attr_list_new
argument_list|()
expr_stmt|;
name|attr
operator|=
name|pango_attr_scale_new
argument_list|(
name|PANGO_SCALE_LARGE
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
literal|0
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
operator|-
literal|1
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrs
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|attr
operator|=
name|pango_attr_weight_new
argument_list|(
name|PANGO_WEIGHT_BOLD
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
literal|0
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
operator|-
literal|1
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrs
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s Message"
argument_list|)
argument_list|,
name|domain
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|attrs
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
name|FALSE
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
name|pango_attr_list_unref
argument_list|(
name|attrs
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|gtk_label_set_selectable
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
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
name|FALSE
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
name|vbox
operator|=
name|vbox
expr_stmt|;
name|msg_box
operator|->
name|domain
operator|=
name|g_strdup
argument_list|(
name|domain
argument_list|)
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
name|g_list_prepend
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
name|domain
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

begin_function
name|void
DECL|function|gimp_table_attach_stock (GtkTable * table,gint row,const gchar * label_text,gdouble yalign,GtkWidget * widget,gint colspan,const gchar * stock_id)
name|gimp_table_attach_stock
parameter_list|(
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label_text
parameter_list|,
name|gdouble
name|yalign
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|colspan
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_TABLE
argument_list|(
name|table
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|label_text
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|label_text
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|yalign
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_RIGHT
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
condition|)
block|{
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|table
argument_list|,
name|widget
argument_list|,
literal|1
argument_list|,
literal|1
operator|+
name|colspan
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
block|}
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|stock_id
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|image
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|table
argument_list|,
name|image
argument_list|,
literal|1
operator|+
name|colspan
argument_list|,
literal|2
operator|+
name|colspan
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GtkIconSize
DECL|function|gimp_get_icon_size (GtkWidget * widget,const gchar * stock_id,GtkIconSize max_size,gint width,gint height)
name|gimp_get_icon_size
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
name|GtkIconSize
name|max_size
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GtkIconSet
modifier|*
name|icon_set
decl_stmt|;
name|GtkIconSize
modifier|*
name|sizes
decl_stmt|;
name|gint
name|n_sizes
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|width_diff
init|=
literal|1024
decl_stmt|;
name|gint
name|height_diff
init|=
literal|1024
decl_stmt|;
name|gint
name|max_width
decl_stmt|;
name|gint
name|max_height
decl_stmt|;
name|GtkIconSize
name|icon_size
init|=
name|GTK_ICON_SIZE_MENU
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|icon_size
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|stock_id
operator|!=
name|NULL
argument_list|,
name|icon_size
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
argument_list|,
name|icon_size
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
argument_list|,
name|icon_size
argument_list|)
expr_stmt|;
name|icon_set
operator|=
name|gtk_style_lookup_icon_set
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|stock_id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|icon_set
condition|)
return|return
name|GTK_ICON_SIZE_INVALID
return|;
if|if
condition|(
operator|!
name|gtk_icon_size_lookup
argument_list|(
name|max_size
argument_list|,
operator|&
name|max_width
argument_list|,
operator|&
name|max_height
argument_list|)
condition|)
block|{
name|max_width
operator|=
literal|1024
expr_stmt|;
name|max_height
operator|=
literal|1024
expr_stmt|;
block|}
name|gtk_icon_set_get_sizes
argument_list|(
name|icon_set
argument_list|,
operator|&
name|sizes
argument_list|,
operator|&
name|n_sizes
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_sizes
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|icon_width
decl_stmt|;
name|gint
name|icon_height
decl_stmt|;
if|if
condition|(
name|gtk_icon_size_lookup
argument_list|(
name|sizes
index|[
name|i
index|]
argument_list|,
operator|&
name|icon_width
argument_list|,
operator|&
name|icon_height
argument_list|)
condition|)
block|{
if|if
condition|(
name|icon_width
operator|<=
name|width
operator|&&
name|icon_height
operator|<=
name|height
operator|&&
name|icon_width
operator|<=
name|max_width
operator|&&
name|icon_height
operator|<=
name|max_height
operator|&&
operator|(
operator|(
name|width
operator|-
name|icon_width
operator|)
operator|<
name|width_diff
operator|||
operator|(
name|height
operator|-
name|icon_height
operator|)
operator|<
name|height_diff
operator|)
condition|)
block|{
name|width_diff
operator|=
name|width
operator|-
name|icon_width
expr_stmt|;
name|height_diff
operator|=
name|height
operator|-
name|icon_height
expr_stmt|;
name|icon_size
operator|=
name|sizes
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|sizes
argument_list|)
expr_stmt|;
return|return
name|icon_size
return|;
block|}
end_function

begin_comment
comment|/*  The format string which is used to display modifier names  *<Shift>,<Ctrl> and<Alt>  */
end_comment

begin_define
DECL|macro|GIMP_MOD_NAME_FORMAT_STRING
define|#
directive|define
name|GIMP_MOD_NAME_FORMAT_STRING
value|N_("<%s>")
end_define

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_get_mod_name_shift (void)
name|gimp_get_mod_name_shift
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|mod_name_shift
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|mod_name_shift
condition|)
block|{
name|GtkAccelLabelClass
modifier|*
name|accel_label_class
decl_stmt|;
name|accel_label_class
operator|=
name|g_type_class_ref
argument_list|(
name|GTK_TYPE_ACCEL_LABEL
argument_list|)
expr_stmt|;
name|mod_name_shift
operator|=
name|g_strdup_printf
argument_list|(
name|gettext
argument_list|(
name|GIMP_MOD_NAME_FORMAT_STRING
argument_list|)
argument_list|,
name|accel_label_class
operator|->
name|mod_name_shift
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|accel_label_class
argument_list|)
expr_stmt|;
block|}
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|mod_name_shift
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_get_mod_name_control (void)
name|gimp_get_mod_name_control
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|mod_name_control
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|mod_name_control
condition|)
block|{
name|GtkAccelLabelClass
modifier|*
name|accel_label_class
decl_stmt|;
name|accel_label_class
operator|=
name|g_type_class_ref
argument_list|(
name|GTK_TYPE_ACCEL_LABEL
argument_list|)
expr_stmt|;
name|mod_name_control
operator|=
name|g_strdup_printf
argument_list|(
name|gettext
argument_list|(
name|GIMP_MOD_NAME_FORMAT_STRING
argument_list|)
argument_list|,
name|accel_label_class
operator|->
name|mod_name_control
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|accel_label_class
argument_list|)
expr_stmt|;
block|}
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|mod_name_control
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_get_mod_name_alt (void)
name|gimp_get_mod_name_alt
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|mod_name_alt
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|mod_name_alt
condition|)
block|{
name|GtkAccelLabelClass
modifier|*
name|accel_label_class
decl_stmt|;
name|accel_label_class
operator|=
name|g_type_class_ref
argument_list|(
name|GTK_TYPE_ACCEL_LABEL
argument_list|)
expr_stmt|;
name|mod_name_alt
operator|=
name|g_strdup_printf
argument_list|(
name|gettext
argument_list|(
name|GIMP_MOD_NAME_FORMAT_STRING
argument_list|)
argument_list|,
name|accel_label_class
operator|->
name|mod_name_alt
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|accel_label_class
argument_list|)
expr_stmt|;
block|}
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|mod_name_alt
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_get_mod_separator (void)
name|gimp_get_mod_separator
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|mod_separator
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|mod_separator
condition|)
block|{
name|GtkAccelLabelClass
modifier|*
name|accel_label_class
decl_stmt|;
name|accel_label_class
operator|=
name|g_type_class_ref
argument_list|(
name|GTK_TYPE_ACCEL_LABEL
argument_list|)
expr_stmt|;
name|mod_separator
operator|=
name|g_strdup
argument_list|(
name|accel_label_class
operator|->
name|mod_separator
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|accel_label_class
argument_list|)
expr_stmt|;
block|}
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|mod_separator
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_get_screen_resolution:  * @screen: a #GdkScreen or %NULL  * @xres: returns the horizontal screen resolution (in dpi)  * @yres: returns the vertical screen resolution (in dpi)  *   * Retrieves the screen resolution from GDK. If @screen is %NULL, the  * default screen is used.  **/
end_comment

begin_function
name|void
DECL|function|gimp_get_screen_resolution (GdkScreen * screen,gdouble * xres,gdouble * yres)
name|gimp_get_screen_resolution
parameter_list|(
name|GdkScreen
modifier|*
name|screen
parameter_list|,
name|gdouble
modifier|*
name|xres
parameter_list|,
name|gdouble
modifier|*
name|yres
parameter_list|)
block|{
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|width_mm
decl_stmt|,
name|height_mm
decl_stmt|;
name|gdouble
name|x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|y
init|=
literal|0.0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|screen
operator|==
name|NULL
operator|||
name|GDK_IS_SCREEN
argument_list|(
name|screen
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|xres
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|yres
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|screen
condition|)
name|screen
operator|=
name|gdk_screen_get_default
argument_list|()
expr_stmt|;
name|width
operator|=
name|gdk_screen_get_width
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|height
operator|=
name|gdk_screen_get_height
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|width_mm
operator|=
name|gdk_screen_get_width_mm
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|height_mm
operator|=
name|gdk_screen_get_height_mm
argument_list|(
name|screen
argument_list|)
expr_stmt|;
comment|/*    * From xdpyinfo.c:    *    * there are 2.54 centimeters to an inch; so there are 25.4 millimeters.    *    *     dpi = N pixels / (M millimeters / (25.4 millimeters / 1 inch))    *         = N pixels / (M inch / 25.4)    *         = N * 25.4 pixels / M inch    */
if|if
condition|(
name|width_mm
operator|>
literal|0
operator|&&
name|height_mm
operator|>
literal|0
condition|)
block|{
name|x
operator|=
operator|(
name|width
operator|*
literal|25.4
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|width_mm
expr_stmt|;
name|y
operator|=
operator|(
name|height
operator|*
literal|25.4
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|height_mm
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|<
name|GIMP_MIN_RESOLUTION
operator|||
name|x
operator|>
name|GIMP_MAX_RESOLUTION
operator|||
name|y
operator|<
name|GIMP_MIN_RESOLUTION
operator|||
name|y
operator|>
name|GIMP_MAX_RESOLUTION
condition|)
block|{
name|g_warning
argument_list|(
literal|"GDK returned bogus values for the screen resolution, "
literal|"using 75 dpi instead."
argument_list|)
expr_stmt|;
name|x
operator|=
literal|75.0
expr_stmt|;
name|y
operator|=
literal|75.0
expr_stmt|;
block|}
comment|/*  round the value to full integers to give more pleasant results  */
operator|*
name|xres
operator|=
name|ROUND
argument_list|(
name|x
argument_list|)
expr_stmt|;
operator|*
name|yres
operator|=
name|ROUND
argument_list|(
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_get_gdk_color:  * @color: the source color as #GimpRGB  * @gdk_color: pointer to a #GdkColor  *   * Initializes @gdk_color from a #GimpRGB. This function does not  * allocate the color for you. Depending on how you want to use it,  * you may have to call gdk_colormap_alloc_color().  **/
end_comment

begin_function
name|void
DECL|function|gimp_rgb_get_gdk_color (const GimpRGB * color,GdkColor * gdk_color)
name|gimp_rgb_get_gdk_color
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GdkColor
modifier|*
name|gdk_color
parameter_list|)
block|{
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gdk_color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|gdk_color
operator|->
name|red
operator|=
operator|(
name|r
operator|<<
literal|8
operator|)
operator||
name|r
expr_stmt|;
name|gdk_color
operator|->
name|green
operator|=
operator|(
name|g
operator|<<
literal|8
operator|)
operator||
name|g
expr_stmt|;
name|gdk_color
operator|->
name|blue
operator|=
operator|(
name|b
operator|<<
literal|8
operator|)
operator||
name|b
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_menu_path_strip_uline (const gchar * menu_path)
name|gimp_menu_path_strip_uline
parameter_list|(
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
block|{
name|gchar
modifier|*
name|escaped
decl_stmt|;
name|gchar
modifier|*
name|p
decl_stmt|;
if|if
condition|(
operator|!
name|menu_path
condition|)
return|return
name|NULL
return|;
name|p
operator|=
name|escaped
operator|=
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|menu_path
condition|)
block|{
if|if
condition|(
operator|*
name|menu_path
operator|==
literal|'_'
condition|)
block|{
comment|/*  "__" means a literal "_" in the menu path  */
if|if
condition|(
name|menu_path
index|[
literal|1
index|]
operator|==
literal|'_'
condition|)
operator|*
name|p
operator|++
operator|=
operator|*
name|menu_path
operator|++
expr_stmt|;
name|menu_path
operator|++
expr_stmt|;
block|}
else|else
block|{
operator|*
name|p
operator|++
operator|=
operator|*
name|menu_path
operator|++
expr_stmt|;
block|}
block|}
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
return|return
name|escaped
return|;
block|}
end_function

end_unit

