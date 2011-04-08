begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2002 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"imap_default_dialog.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_function
specifier|static
name|void
DECL|function|dialog_response (GtkWidget * widget,gint response_id,DefaultDialog_t * dialog)
name|dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|)
block|{
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|GTK_RESPONSE_APPLY
case|:
if|if
condition|(
name|dialog
operator|->
name|apply_cb
condition|)
name|dialog
operator|->
name|apply_cb
argument_list|(
name|dialog
operator|->
name|apply_cb_data
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|dialog
operator|->
name|ok_cb
condition|)
name|dialog
operator|->
name|ok_cb
argument_list|(
name|dialog
operator|->
name|ok_cb_data
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|->
name|ok_cb
condition|)
name|dialog
operator|->
name|ok_cb
argument_list|(
name|dialog
operator|->
name|ok_cb_data
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|->
name|cancel_cb
condition|)
name|dialog
operator|->
name|cancel_cb
argument_list|(
name|dialog
operator|->
name|cancel_cb_data
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|default_dialog_set_ok_cb (DefaultDialog_t * dialog,void (* ok_cb)(gpointer),gpointer ok_cb_data)
name|default_dialog_set_ok_cb
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
name|void
function_decl|(
modifier|*
name|ok_cb
function_decl|)
parameter_list|(
name|gpointer
parameter_list|)
parameter_list|,
name|gpointer
name|ok_cb_data
parameter_list|)
block|{
name|dialog
operator|->
name|ok_cb
operator|=
name|ok_cb
expr_stmt|;
name|dialog
operator|->
name|ok_cb_data
operator|=
name|ok_cb_data
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|default_dialog_set_apply_cb (DefaultDialog_t * dialog,void (* apply_cb)(gpointer),gpointer apply_cb_data)
name|default_dialog_set_apply_cb
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
name|void
function_decl|(
modifier|*
name|apply_cb
function_decl|)
parameter_list|(
name|gpointer
parameter_list|)
parameter_list|,
name|gpointer
name|apply_cb_data
parameter_list|)
block|{
name|dialog
operator|->
name|apply_cb
operator|=
name|apply_cb
expr_stmt|;
name|dialog
operator|->
name|apply_cb_data
operator|=
name|apply_cb_data
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|default_dialog_set_cancel_cb (DefaultDialog_t * dialog,void (* cancel_cb)(gpointer),gpointer cancel_cb_data)
name|default_dialog_set_cancel_cb
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
name|void
function_decl|(
modifier|*
name|cancel_cb
function_decl|)
parameter_list|(
name|gpointer
parameter_list|)
parameter_list|,
name|gpointer
name|cancel_cb_data
parameter_list|)
block|{
name|dialog
operator|->
name|cancel_cb
operator|=
name|cancel_cb
expr_stmt|;
name|dialog
operator|->
name|cancel_cb_data
operator|=
name|cancel_cb_data
expr_stmt|;
block|}
end_function

begin_function
name|DefaultDialog_t
modifier|*
DECL|function|make_default_dialog (const gchar * title)
name|make_default_dialog
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
block|{
name|DefaultDialog_t
modifier|*
name|data
init|=
name|g_new0
argument_list|(
name|DefaultDialog_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|data
operator|->
name|ok_cb
operator|=
name|NULL
expr_stmt|;
name|data
operator|->
name|apply_cb
operator|=
name|NULL
expr_stmt|;
name|data
operator|->
name|cancel_cb
operator|=
name|NULL
expr_stmt|;
name|data
operator|->
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|title
argument_list|,
name|PLUG_IN_ROLE
argument_list|,
name|get_dialog
argument_list|()
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|PLUG_IN_PROC
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|->
name|apply
operator|=
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|data
operator|->
name|dialog
argument_list|)
argument_list|,
name|GTK_STOCK_APPLY
argument_list|,
name|GTK_RESPONSE_APPLY
argument_list|)
expr_stmt|;
name|data
operator|->
name|cancel
operator|=
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|data
operator|->
name|dialog
argument_list|)
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|)
expr_stmt|;
name|data
operator|->
name|ok
operator|=
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|data
operator|->
name|dialog
argument_list|)
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|data
operator|->
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_APPLY
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dialog_response
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|data
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|data
operator|->
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|data
operator|->
name|vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|data
operator|->
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|data
operator|->
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|data
operator|->
name|vbox
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

begin_function
name|void
DECL|function|default_dialog_show (DefaultDialog_t * dialog)
name|default_dialog_show
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|)
block|{
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|default_dialog_hide_cancel_button (DefaultDialog_t * dialog)
name|default_dialog_hide_cancel_button
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|)
block|{
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|cancel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|default_dialog_hide_apply_button (DefaultDialog_t * dialog)
name|default_dialog_hide_apply_button
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|)
block|{
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|apply
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|default_dialog_hide_help_button (DefaultDialog_t * dialog)
name|default_dialog_hide_help_button
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|)
block|{
comment|/* gtk_widget_hide(dialog->help); */
block|}
end_function

begin_function
name|void
DECL|function|default_dialog_set_title (DefaultDialog_t * dialog,const gchar * title)
name|default_dialog_set_title
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
block|{
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|default_dialog_set_label (DefaultDialog_t * dialog,const gchar * text)
name|default_dialog_set_label
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|gtk_label_new
argument_list|(
name|text
argument_list|)
decl_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|default_dialog_add_table (DefaultDialog_t * dialog,gint rows,gint cols)
name|default_dialog_add_table
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
name|gint
name|rows
parameter_list|,
name|gint
name|cols
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|table
init|=
name|gtk_table_new
argument_list|(
name|rows
argument_list|,
name|cols
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
return|return
name|table
return|;
block|}
end_function

end_unit

