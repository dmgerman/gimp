begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"imap_browse.h"
end_include

begin_include
include|#
directive|include
file|"imap_cmd_edit_object.h"
end_include

begin_include
include|#
directive|include
file|"imap_default_dialog.h"
end_include

begin_include
include|#
directive|include
file|"imap_edit_area_info.h"
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

begin_decl_stmt
DECL|variable|callback_lock
specifier|static
name|gint
name|callback_lock
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|relative_filter (const char * name,gpointer data)
name|relative_filter
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|AreaInfoDialog_t
modifier|*
name|param
init|=
operator|(
name|AreaInfoDialog_t
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|param
operator|->
name|relative_link
argument_list|)
argument_list|)
condition|)
return|return
name|g_basename
argument_list|(
name|name
argument_list|)
return|;
return|return
name|name
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|url_changed (GtkWidget * widget,gpointer data)
name|url_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|AreaInfoDialog_t
modifier|*
name|param
init|=
operator|(
name|AreaInfoDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|gchar
modifier|*
name|url
init|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|url
argument_list|)
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
if|if
condition|(
operator|!
name|g_strncasecmp
argument_list|(
name|url
argument_list|,
literal|"http://"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"http://"
argument_list|)
operator|-
literal|1
argument_list|)
condition|)
name|button
operator|=
name|param
operator|->
name|web_site
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|g_strncasecmp
argument_list|(
name|url
argument_list|,
literal|"ftp://"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"ftp://"
argument_list|)
operator|-
literal|1
argument_list|)
condition|)
name|button
operator|=
name|param
operator|->
name|ftp_site
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|g_strncasecmp
argument_list|(
name|url
argument_list|,
literal|"gopher://"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"gopher://"
argument_list|)
operator|-
literal|1
argument_list|)
condition|)
name|button
operator|=
name|param
operator|->
name|gopher
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|g_strncasecmp
argument_list|(
name|url
argument_list|,
literal|"file:/"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"file:/"
argument_list|)
operator|-
literal|1
argument_list|)
condition|)
name|button
operator|=
name|param
operator|->
name|file
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|g_strncasecmp
argument_list|(
name|url
argument_list|,
literal|"wais://"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"wais://"
argument_list|)
operator|-
literal|1
argument_list|)
condition|)
name|button
operator|=
name|param
operator|->
name|wais
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|g_strncasecmp
argument_list|(
name|url
argument_list|,
literal|"telnet://"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"telnet://"
argument_list|)
operator|-
literal|1
argument_list|)
condition|)
name|button
operator|=
name|param
operator|->
name|telnet
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|g_strncasecmp
argument_list|(
name|url
argument_list|,
literal|"mailto:"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"mailto:"
argument_list|)
operator|-
literal|1
argument_list|)
condition|)
name|button
operator|=
name|param
operator|->
name|email
expr_stmt|;
else|else
name|button
operator|=
name|param
operator|->
name|other
expr_stmt|;
name|callback_lock
operator|=
name|TRUE
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|set_url (GtkWidget * widget,AreaInfoDialog_t * param,const gchar * prefix)
name|set_url
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|AreaInfoDialog_t
modifier|*
name|param
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefix
parameter_list|)
block|{
if|if
condition|(
name|callback_lock
condition|)
block|{
name|callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|GTK_WIDGET_STATE
argument_list|(
name|widget
argument_list|)
operator|&
name|GTK_STATE_SELECTED
condition|)
block|{
name|char
modifier|*
name|p
decl_stmt|;
name|gchar
modifier|*
name|url
init|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|url
argument_list|)
argument_list|)
argument_list|)
decl_stmt|;
name|p
operator|=
name|strstr
argument_list|(
name|url
argument_list|,
literal|"//"
argument_list|)
expr_stmt|;
comment|/* 'http://' */
if|if
condition|(
name|p
condition|)
block|{
name|p
operator|+=
literal|2
expr_stmt|;
block|}
else|else
block|{
name|p
operator|=
name|strchr
argument_list|(
name|url
argument_list|,
literal|':'
argument_list|)
expr_stmt|;
comment|/* 'mailto:' */
if|if
condition|(
name|p
condition|)
block|{
name|p
operator|++
expr_stmt|;
if|if
condition|(
operator|*
name|p
operator|==
literal|'/'
condition|)
comment|/* 'file:/' */
name|p
operator|++
expr_stmt|;
block|}
else|else
block|{
name|p
operator|=
name|url
expr_stmt|;
block|}
block|}
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|url
argument_list|)
argument_list|,
name|prefix
argument_list|)
expr_stmt|;
name|gtk_entry_append_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|url
argument_list|)
argument_list|,
name|p
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|url
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_grab_focus
argument_list|(
name|param
operator|->
name|url
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_web_cb (GtkWidget * widget,AreaInfoDialog_t * param)
name|select_web_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|AreaInfoDialog_t
modifier|*
name|param
parameter_list|)
block|{
name|set_url
argument_list|(
name|widget
argument_list|,
name|param
argument_list|,
literal|"http://"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_ftp_cb (GtkWidget * widget,AreaInfoDialog_t * param)
name|select_ftp_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|AreaInfoDialog_t
modifier|*
name|param
parameter_list|)
block|{
name|set_url
argument_list|(
name|widget
argument_list|,
name|param
argument_list|,
literal|"ftp://"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_gopher_cb (GtkWidget * widget,AreaInfoDialog_t * param)
name|select_gopher_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|AreaInfoDialog_t
modifier|*
name|param
parameter_list|)
block|{
name|set_url
argument_list|(
name|widget
argument_list|,
name|param
argument_list|,
literal|"gopher://"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_other_cb (GtkWidget * widget,AreaInfoDialog_t * param)
name|select_other_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|AreaInfoDialog_t
modifier|*
name|param
parameter_list|)
block|{
name|set_url
argument_list|(
name|widget
argument_list|,
name|param
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_file_cb (GtkWidget * widget,AreaInfoDialog_t * param)
name|select_file_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|AreaInfoDialog_t
modifier|*
name|param
parameter_list|)
block|{
name|set_url
argument_list|(
name|widget
argument_list|,
name|param
argument_list|,
literal|"file:/"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_wais_cb (GtkWidget * widget,AreaInfoDialog_t * param)
name|select_wais_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|AreaInfoDialog_t
modifier|*
name|param
parameter_list|)
block|{
name|set_url
argument_list|(
name|widget
argument_list|,
name|param
argument_list|,
literal|"wais://"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_telnet_cb (GtkWidget * widget,AreaInfoDialog_t * param)
name|select_telnet_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|AreaInfoDialog_t
modifier|*
name|param
parameter_list|)
block|{
name|set_url
argument_list|(
name|widget
argument_list|,
name|param
argument_list|,
literal|"telnet://"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_email_cb (GtkWidget * widget,AreaInfoDialog_t * param)
name|select_email_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|AreaInfoDialog_t
modifier|*
name|param
parameter_list|)
block|{
name|set_url
argument_list|(
name|widget
argument_list|,
name|param
argument_list|,
literal|"mailto:"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|create_link_tab (AreaInfoDialog_t * dialog,GtkWidget * notebook)
name|create_link_tab
parameter_list|(
name|AreaInfoDialog_t
modifier|*
name|dialog
parameter_list|,
name|GtkWidget
modifier|*
name|notebook
parameter_list|)
block|{
name|BrowseWidget_t
modifier|*
name|browse
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|,
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|subtable
decl_stmt|,
modifier|*
name|frame
decl_stmt|;
name|GSList
modifier|*
name|group
decl_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|11
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
literal|"Link Type"
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|frame
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|subtable
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|4
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|subtable
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|subtable
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|web_site
operator|=
name|create_radio_button_in_table
argument_list|(
name|subtable
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Web Site"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
operator|->
name|web_site
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|select_web_cb
argument_list|,
operator|(
name|gpointer
operator|)
name|dialog
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|dialog
operator|->
name|web_site
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|ftp_site
operator|=
name|create_radio_button_in_table
argument_list|(
name|subtable
argument_list|,
name|group
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|"Ftp Site"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
operator|->
name|ftp_site
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|select_ftp_cb
argument_list|,
operator|(
name|gpointer
operator|)
name|dialog
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|dialog
operator|->
name|ftp_site
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|gopher
operator|=
name|create_radio_button_in_table
argument_list|(
name|subtable
argument_list|,
name|group
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|"Gopher"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
operator|->
name|gopher
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|select_gopher_cb
argument_list|,
operator|(
name|gpointer
operator|)
name|dialog
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|dialog
operator|->
name|gopher
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|other
operator|=
name|create_radio_button_in_table
argument_list|(
name|subtable
argument_list|,
name|group
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
literal|"Other"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
operator|->
name|other
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|select_other_cb
argument_list|,
operator|(
name|gpointer
operator|)
name|dialog
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|dialog
operator|->
name|other
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|file
operator|=
name|create_radio_button_in_table
argument_list|(
name|subtable
argument_list|,
name|group
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|"File"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
operator|->
name|file
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|select_file_cb
argument_list|,
operator|(
name|gpointer
operator|)
name|dialog
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|dialog
operator|->
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|wais
operator|=
name|create_radio_button_in_table
argument_list|(
name|subtable
argument_list|,
name|group
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|"WAIS"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
operator|->
name|wais
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|select_wais_cb
argument_list|,
operator|(
name|gpointer
operator|)
name|dialog
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|dialog
operator|->
name|wais
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|telnet
operator|=
name|create_radio_button_in_table
argument_list|(
name|subtable
argument_list|,
name|group
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|"Telnet"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
operator|->
name|telnet
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|select_telnet_cb
argument_list|,
operator|(
name|gpointer
operator|)
name|dialog
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|dialog
operator|->
name|telnet
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|email
operator|=
name|create_radio_button_in_table
argument_list|(
name|subtable
argument_list|,
name|group
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|"e-mail"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
operator|->
name|email
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|select_email_cb
argument_list|,
operator|(
name|gpointer
operator|)
name|dialog
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|"URL to activate when this area is clicked: (required)"
argument_list|)
expr_stmt|;
name|browse
operator|=
name|browse_widget_new
argument_list|(
literal|"Select HTML file"
argument_list|)
expr_stmt|;
name|browse_widget_set_filter
argument_list|(
name|browse
argument_list|,
name|relative_filter
argument_list|,
operator|(
name|gpointer
operator|)
name|dialog
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|browse
operator|->
name|hbox
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|url
operator|=
name|browse
operator|->
name|file
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
operator|->
name|url
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|url_changed
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|relative_link
operator|=
name|create_check_button_in_table
argument_list|(
name|table
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|,
literal|"Relative link"
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|dialog
operator|->
name|relative_link
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|6
argument_list|,
literal|0
argument_list|,
literal|"Target frame name/ID: (optional - used for FRAMES only)"
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|target
operator|=
name|create_entry_in_table
argument_list|(
name|table
argument_list|,
literal|7
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|9
argument_list|,
literal|0
argument_list|,
literal|"Comment about this area: (optional)"
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|comment
operator|=
name|create_entry_in_table
argument_list|(
name|table
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Link"
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|table
argument_list|,
name|label
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|create_java_script_tab (AreaInfoDialog_t * dialog,GtkWidget * notebook)
name|create_java_script_tab
parameter_list|(
name|AreaInfoDialog_t
modifier|*
name|dialog
parameter_list|,
name|GtkWidget
modifier|*
name|notebook
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|,
modifier|*
name|table
decl_stmt|,
modifier|*
name|label
decl_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|11
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
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"onMouseover:"
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|mouse_over
operator|=
name|create_entry_in_table
argument_list|(
name|table
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|"onMouseout:"
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|mouse_out
operator|=
name|create_entry_in_table
argument_list|(
name|table
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|6
argument_list|,
literal|0
argument_list|,
literal|"onFocus (HTML 4.0):"
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|focus
operator|=
name|create_entry_in_table
argument_list|(
name|table
argument_list|,
literal|7
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|9
argument_list|,
literal|0
argument_list|,
literal|"onBlur (HTML 4.0):"
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|blur
operator|=
name|create_entry_in_table
argument_list|(
name|table
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"JavaScript"
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|label
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|edit_area_ok_cb (gpointer data)
name|edit_area_ok_cb
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|AreaInfoDialog_t
modifier|*
name|param
init|=
operator|(
name|AreaInfoDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|Object_t
modifier|*
name|obj
init|=
name|param
operator|->
name|obj
decl_stmt|;
name|gint
name|old_x
decl_stmt|,
name|old_y
decl_stmt|,
name|old_width
decl_stmt|,
name|old_height
decl_stmt|;
name|gint
name|new_x
decl_stmt|,
name|new_y
decl_stmt|,
name|new_width
decl_stmt|,
name|new_height
decl_stmt|;
comment|/* Fix me: nasty hack */
if|if
condition|(
name|param
operator|->
name|add
condition|)
name|command_list_add
argument_list|(
name|edit_object_command_new
argument_list|(
name|obj
argument_list|)
argument_list|)
expr_stmt|;
name|object_get_dimensions
argument_list|(
name|obj
argument_list|,
operator|&
name|old_x
argument_list|,
operator|&
name|old_y
argument_list|,
operator|&
name|old_width
argument_list|,
operator|&
name|old_height
argument_list|)
expr_stmt|;
name|object_set_url
argument_list|(
name|obj
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|url
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|object_set_target
argument_list|(
name|obj
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|target
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|object_set_comment
argument_list|(
name|obj
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|comment
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|object_set_mouse_over
argument_list|(
name|obj
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|mouse_over
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|object_set_mouse_out
argument_list|(
name|obj
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|mouse_out
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|object_set_focus
argument_list|(
name|obj
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|focus
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|object_set_blur
argument_list|(
name|obj
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|blur
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|object_update
argument_list|(
name|obj
argument_list|,
name|param
operator|->
name|infotab
argument_list|)
expr_stmt|;
name|update_shape
argument_list|(
name|obj
argument_list|)
expr_stmt|;
name|object_unlock
argument_list|(
name|obj
argument_list|)
expr_stmt|;
name|object_get_dimensions
argument_list|(
name|obj
argument_list|,
operator|&
name|new_x
argument_list|,
operator|&
name|new_y
argument_list|,
operator|&
name|new_width
argument_list|,
operator|&
name|new_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_x
operator|!=
name|old_x
operator|||
name|new_y
operator|!=
name|old_y
operator|||
name|new_width
operator|!=
name|old_width
operator|||
name|new_height
operator|!=
name|old_height
condition|)
name|redraw_preview
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|edit_area_cancel_cb (gpointer data)
name|edit_area_cancel_cb
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
init|=
operator|(
operator|(
name|AreaInfoDialog_t
operator|*
operator|)
name|data
operator|)
operator|->
name|obj
decl_stmt|;
name|object_unlock
argument_list|(
name|obj
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|switch_page (GtkWidget * widget,GtkNotebookPage * page,gint page_num,gpointer data)
name|switch_page
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkNotebookPage
modifier|*
name|page
parameter_list|,
name|gint
name|page_num
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|AreaInfoDialog_t
modifier|*
name|param
init|=
operator|(
name|AreaInfoDialog_t
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|page_num
operator|==
literal|0
condition|)
block|{
name|gtk_widget_grab_focus
argument_list|(
name|param
operator|->
name|url
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|page_num
operator|==
literal|1
condition|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|param
operator|->
name|obj
decl_stmt|;
name|obj
operator|->
name|class
operator|->
name|set_initial_focus
argument_list|(
name|obj
argument_list|,
name|param
operator|->
name|infotab
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_grab_focus
argument_list|(
name|param
operator|->
name|mouse_over
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|AreaInfoDialog_t
modifier|*
DECL|function|create_edit_area_info_dialog (Object_t * obj)
name|create_edit_area_info_dialog
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
block|{
name|AreaInfoDialog_t
modifier|*
name|data
init|=
name|g_new
argument_list|(
name|AreaInfoDialog_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
name|data
operator|->
name|obj
operator|=
name|obj
expr_stmt|;
name|data
operator|->
name|browse
operator|=
name|NULL
expr_stmt|;
name|data
operator|->
name|dialog
operator|=
name|make_default_dialog
argument_list|(
literal|"Area Settings"
argument_list|)
expr_stmt|;
name|default_dialog_set_ok_cb
argument_list|(
name|data
operator|->
name|dialog
argument_list|,
name|edit_area_ok_cb
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|default_dialog_set_cancel_cb
argument_list|(
name|data
operator|->
name|dialog
argument_list|,
name|edit_area_cancel_cb
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|data
operator|->
name|notebook
operator|=
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|notebook
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_signal_connect_after
argument_list|(
name|GTK_OBJECT
argument_list|(
name|notebook
argument_list|)
argument_list|,
literal|"switch_page"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|switch_page
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|data
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|data
operator|->
name|dialog
operator|->
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|notebook
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|create_link_tab
argument_list|(
name|data
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|data
operator|->
name|infotab
operator|=
name|obj
operator|->
name|class
operator|->
name|create_info_tab
argument_list|(
name|notebook
argument_list|)
expr_stmt|;
name|create_java_script_tab
argument_list|(
name|data
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|notebook
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

begin_function
name|void
DECL|function|edit_area_info_dialog_show (AreaInfoDialog_t * dialog,Object_t * obj,gboolean add)
name|edit_area_info_dialog_show
parameter_list|(
name|AreaInfoDialog_t
modifier|*
name|dialog
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gboolean
name|add
parameter_list|)
block|{
name|char
name|title
index|[
literal|64
index|]
decl_stmt|;
name|object_unlock
argument_list|(
name|dialog
operator|->
name|obj
argument_list|)
expr_stmt|;
name|object_lock
argument_list|(
name|obj
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|obj
operator|=
name|obj
expr_stmt|;
name|dialog
operator|->
name|add
operator|=
name|add
expr_stmt|;
name|obj
operator|->
name|class
operator|->
name|fill_info_tab
argument_list|(
name|obj
argument_list|,
name|dialog
operator|->
name|infotab
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|dialog
operator|->
name|url
argument_list|)
argument_list|,
name|obj
operator|->
name|url
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|dialog
operator|->
name|target
argument_list|)
argument_list|,
name|obj
operator|->
name|target
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|dialog
operator|->
name|comment
argument_list|)
argument_list|,
name|obj
operator|->
name|comment
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|dialog
operator|->
name|mouse_over
argument_list|)
argument_list|,
name|obj
operator|->
name|mouse_over
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|dialog
operator|->
name|mouse_out
argument_list|)
argument_list|,
name|obj
operator|->
name|mouse_out
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|dialog
operator|->
name|focus
argument_list|)
argument_list|,
name|obj
operator|->
name|focus
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|dialog
operator|->
name|blur
argument_list|)
argument_list|,
name|obj
operator|->
name|blur
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|dialog
operator|->
name|url
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|title
argument_list|,
literal|"Area #%d Settings"
argument_list|,
name|object_get_position_in_list
argument_list|(
name|obj
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|default_dialog_set_title
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|default_dialog_show
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

