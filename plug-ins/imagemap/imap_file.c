begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2002 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
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
file|"imap_file.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"imap_table.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function
specifier|static
name|void
DECL|function|open_cb (GtkWidget * widget,gpointer data)
name|open_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|struct
name|stat
name|buf
decl_stmt|;
name|int
name|err
decl_stmt|;
name|filename
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|err
operator|=
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|err
operator|&&
operator|(
name|buf
operator|.
name|st_mode
operator|&
name|S_IFREG
operator|)
condition|)
block|{
name|gtk_widget_hide
argument_list|(
operator|(
name|GtkWidget
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
name|load
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|do_file_error_dialog
argument_list|(
name|_
argument_list|(
literal|"Error opening file"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|do_file_open_dialog (void)
name|do_file_open_dialog
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
name|dialog
operator|=
name|gtk_file_selection_new
argument_list|(
name|_
argument_list|(
literal|"Load Imagemap"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|G_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
operator|->
name|cancel_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
operator|->
name|ok_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|open_cb
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|really_overwrite (gpointer data)
name|really_overwrite
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_hide
argument_list|(
operator|(
name|GtkWidget
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
name|save_as
argument_list|(
name|gtk_file_selection_get_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|data
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|do_file_exists_dialog (gpointer data)
name|do_file_exists_dialog
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
specifier|static
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
name|dialog
operator|=
name|make_default_dialog
argument_list|(
name|_
argument_list|(
literal|"File exists!"
argument_list|)
argument_list|)
expr_stmt|;
name|default_dialog_hide_apply_button
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|default_dialog_set_ok_cb
argument_list|(
name|dialog
argument_list|,
name|really_overwrite
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|default_dialog_set_label
argument_list|(
name|dialog
argument_list|,
name|_
argument_list|(
literal|"File already exists.\n"
literal|"  Do you really want to overwrite?  "
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|default_dialog_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|save_cb (GtkWidget * widget,gpointer data)
name|save_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|struct
name|stat
name|buf
decl_stmt|;
name|int
name|err
decl_stmt|;
name|filename
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|err
operator|=
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
condition|)
block|{
name|gtk_widget_hide
argument_list|(
operator|(
name|GtkWidget
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
name|save_as
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* File exists */
if|if
condition|(
name|buf
operator|.
name|st_mode
operator|&
name|S_IFREG
condition|)
block|{
name|do_file_exists_dialog
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Fix me! */
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|do_file_save_as_dialog (void)
name|do_file_save_as_dialog
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
name|dialog
operator|=
name|gtk_file_selection_new
argument_list|(
name|_
argument_list|(
literal|"Save Imagemap"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|G_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
operator|->
name|cancel_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
operator|->
name|ok_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|save_cb
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_typedef
DECL|struct|__anon27396be00108
typedef|typedef
struct|struct
block|{
DECL|member|dialog
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
decl_stmt|;
DECL|typedef|Alert_t
block|}
name|Alert_t
typedef|;
end_typedef

begin_function
name|Alert_t
modifier|*
DECL|function|create_alert (const gchar * stock_id)
name|create_alert
parameter_list|(
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
name|Alert_t
modifier|*
name|alert
init|=
name|g_new
argument_list|(
name|Alert_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|alert
operator|->
name|dialog
operator|=
name|dialog
operator|=
name|make_default_dialog
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|default_dialog_hide_apply_button
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|default_dialog_hide_cancel_button
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
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
name|hbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|10
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|alert
operator|->
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|alert
operator|->
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|alert
operator|->
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|alert
operator|->
name|label
argument_list|)
expr_stmt|;
return|return
name|alert
return|;
block|}
end_function

begin_function
name|void
DECL|function|alert_set_text (Alert_t * alert,const char * primary_text,const char * secondary_text)
name|alert_set_text
parameter_list|(
name|Alert_t
modifier|*
name|alert
parameter_list|,
specifier|const
name|char
modifier|*
name|primary_text
parameter_list|,
specifier|const
name|char
modifier|*
name|secondary_text
parameter_list|)
block|{
name|gchar
modifier|*
name|text
decl_stmt|;
name|text
operator|=
name|g_strdup_printf
argument_list|(
literal|"<span weight=\"bold\" size=\"larger\">%s</span>\n\n%s"
argument_list|,
name|primary_text
argument_list|,
name|secondary_text
argument_list|)
expr_stmt|;
name|gtk_label_set_markup
argument_list|(
name|GTK_LABEL
argument_list|(
name|alert
operator|->
name|label
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
end_function

begin_function
name|void
DECL|function|do_file_error_dialog (const char * error,const char * filename)
name|do_file_error_dialog
parameter_list|(
specifier|const
name|char
modifier|*
name|error
parameter_list|,
specifier|const
name|char
modifier|*
name|filename
parameter_list|)
block|{
specifier|static
name|Alert_t
modifier|*
name|alert
decl_stmt|;
if|if
condition|(
operator|!
name|alert
condition|)
name|alert
operator|=
name|create_alert
argument_list|(
name|GTK_STOCK_DIALOG_ERROR
argument_list|)
expr_stmt|;
name|alert_set_text
argument_list|(
name|alert
argument_list|,
name|error
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|default_dialog_show
argument_list|(
name|alert
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

