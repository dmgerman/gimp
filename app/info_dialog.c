begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"info_dialog.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_comment
comment|/*  static functions  */
end_comment

begin_function_decl
specifier|static
name|InfoField
modifier|*
name|info_field_new
parameter_list|(
name|InfoDialog
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|update_field
parameter_list|(
name|InfoField
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|info_dialog_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEvent
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|InfoField
modifier|*
DECL|function|info_field_new (InfoDialog * idialog,char * title,char * text_ptr)
name|info_field_new
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|char
modifier|*
name|title
parameter_list|,
name|char
modifier|*
name|text_ptr
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|InfoField
modifier|*
name|field
decl_stmt|;
name|field
operator|=
operator|(
name|InfoField
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|InfoField
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|title
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
name|idialog
operator|->
name|labels
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
name|field
operator|->
name|w
operator|=
name|gtk_label_new
argument_list|(
name|text_ptr
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|field
operator|->
name|w
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
name|idialog
operator|->
name|values
argument_list|)
argument_list|,
name|field
operator|->
name|w
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|field
operator|->
name|text_ptr
operator|=
name|text_ptr
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|field
operator|->
name|w
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
return|return
name|field
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|update_field (InfoField * field)
name|update_field
parameter_list|(
name|InfoField
modifier|*
name|field
parameter_list|)
block|{
name|gchar
modifier|*
name|old_text
decl_stmt|;
comment|/*  only update the field if its new value differs from the old  */
name|gtk_label_get
argument_list|(
name|GTK_LABEL
argument_list|(
name|field
operator|->
name|w
argument_list|)
argument_list|,
operator|&
name|old_text
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|old_text
argument_list|,
name|field
operator|->
name|text_ptr
argument_list|)
condition|)
block|{
comment|/* set the new value and update somehow */
name|gtk_label_set
argument_list|(
name|GTK_LABEL
argument_list|(
name|field
operator|->
name|w
argument_list|)
argument_list|,
name|field
operator|->
name|text_ptr
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  function definitions  */
end_comment

begin_function
name|InfoDialog
modifier|*
DECL|function|info_dialog_new (char * title)
name|info_dialog_new
parameter_list|(
name|char
modifier|*
name|title
parameter_list|)
block|{
name|InfoDialog
modifier|*
name|idialog
decl_stmt|;
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|labels
decl_stmt|,
modifier|*
name|values
decl_stmt|;
name|GtkWidget
modifier|*
name|info_area
decl_stmt|;
name|idialog
operator|=
operator|(
name|InfoDialog
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|InfoDialog
argument_list|)
argument_list|)
expr_stmt|;
name|idialog
operator|->
name|field_list
operator|=
name|NULL
expr_stmt|;
name|shell
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|gtk_widget_set_uposition
argument_list|(
name|shell
argument_list|,
name|info_x
argument_list|,
name|info_y
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|info_dialog_delete_callback
argument_list|)
argument_list|,
name|idialog
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|info_area
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|info_area
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|info_area
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|labels
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|info_area
argument_list|)
argument_list|,
name|labels
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|values
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|info_area
argument_list|)
argument_list|,
name|values
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|idialog
operator|->
name|shell
operator|=
name|shell
expr_stmt|;
name|idialog
operator|->
name|vbox
operator|=
name|vbox
expr_stmt|;
name|idialog
operator|->
name|info_area
operator|=
name|info_area
expr_stmt|;
name|idialog
operator|->
name|labels
operator|=
name|labels
expr_stmt|;
name|idialog
operator|->
name|values
operator|=
name|values
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|idialog
operator|->
name|labels
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|idialog
operator|->
name|values
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|idialog
operator|->
name|info_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|idialog
operator|->
name|vbox
argument_list|)
expr_stmt|;
return|return
name|idialog
return|;
block|}
end_function

begin_function
name|void
DECL|function|info_dialog_free (InfoDialog * idialog)
name|info_dialog_free
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
block|{
name|link_ptr
name|list
decl_stmt|;
if|if
condition|(
operator|!
name|idialog
condition|)
return|return;
comment|/*  Free each item in the field list  */
name|list
operator|=
name|idialog
operator|->
name|field_list
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|g_free
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|next_item
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
comment|/*  Free the actual field linked list  */
name|free_list
argument_list|(
name|idialog
operator|->
name|field_list
argument_list|)
expr_stmt|;
comment|/*  Destroy the associated widgets  */
name|gtk_widget_destroy
argument_list|(
name|idialog
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/*  Free the info dialog memory  */
name|g_free
argument_list|(
name|idialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|info_dialog_add_field (InfoDialog * idialog,char * title,char * text_ptr)
name|info_dialog_add_field
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|char
modifier|*
name|title
parameter_list|,
name|char
modifier|*
name|text_ptr
parameter_list|)
block|{
name|InfoField
modifier|*
name|new_field
decl_stmt|;
if|if
condition|(
operator|!
name|idialog
condition|)
return|return;
name|new_field
operator|=
name|info_field_new
argument_list|(
name|idialog
argument_list|,
name|title
argument_list|,
name|text_ptr
argument_list|)
expr_stmt|;
name|idialog
operator|->
name|field_list
operator|=
name|add_to_list
argument_list|(
name|idialog
operator|->
name|field_list
argument_list|,
operator|(
name|void
operator|*
operator|)
name|new_field
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|info_dialog_popup (InfoDialog * idialog)
name|info_dialog_popup
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
block|{
if|if
condition|(
operator|!
name|idialog
condition|)
return|return;
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|idialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|idialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|info_dialog_popdown (InfoDialog * idialog)
name|info_dialog_popdown
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
block|{
if|if
condition|(
operator|!
name|idialog
condition|)
return|return;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|idialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|idialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|info_dialog_update (InfoDialog * idialog)
name|info_dialog_update
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
block|{
name|link_ptr
name|list
decl_stmt|;
if|if
condition|(
operator|!
name|idialog
condition|)
return|return;
name|list
operator|=
name|idialog
operator|->
name|field_list
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|update_field
argument_list|(
operator|(
name|InfoField
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|next_item
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|info_dialog_delete_callback (GtkWidget * w,GdkEvent * e,gpointer client_data)
name|info_dialog_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|GdkEvent
modifier|*
name|e
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|info_dialog_popdown
argument_list|(
operator|(
name|InfoDialog
operator|*
operator|)
name|client_data
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

