begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2004 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"imap_browse.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"imap_settings.h"
end_include

begin_include
include|#
directive|include
file|"imap_string.h"
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

begin_typedef
DECL|struct|__anon2c6e42910108
typedef|typedef
struct|struct
block|{
DECL|member|dialog
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
DECL|member|imagename
name|BrowseWidget_t
modifier|*
name|imagename
decl_stmt|;
DECL|member|filename
name|GtkWidget
modifier|*
name|filename
decl_stmt|;
DECL|member|title
name|GtkWidget
modifier|*
name|title
decl_stmt|;
DECL|member|author
name|GtkWidget
modifier|*
name|author
decl_stmt|;
DECL|member|default_url
name|GtkWidget
modifier|*
name|default_url
decl_stmt|;
DECL|member|ncsa
name|GtkWidget
modifier|*
name|ncsa
decl_stmt|;
DECL|member|cern
name|GtkWidget
modifier|*
name|cern
decl_stmt|;
DECL|member|csim
name|GtkWidget
modifier|*
name|csim
decl_stmt|;
DECL|member|description
name|GtkTextBuffer
modifier|*
name|description
decl_stmt|;
DECL|typedef|SettingsDialog_t
block|}
name|SettingsDialog_t
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|_map_format
specifier|static
name|MapFormat_t
name|_map_format
init|=
name|CSIM
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|settings_ok_cb (gpointer data)
name|settings_ok_cb
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|SettingsDialog_t
modifier|*
name|param
init|=
operator|(
name|SettingsDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|MapInfo_t
modifier|*
name|info
init|=
name|get_map_info
argument_list|()
decl_stmt|;
name|gchar
modifier|*
name|description
decl_stmt|;
name|GtkTextIter
name|start
decl_stmt|,
name|end
decl_stmt|;
name|g_strreplace
argument_list|(
operator|&
name|info
operator|->
name|image_name
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|imagename
operator|->
name|file
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_strreplace
argument_list|(
operator|&
name|info
operator|->
name|title
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|title
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_strreplace
argument_list|(
operator|&
name|info
operator|->
name|author
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|author
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_strreplace
argument_list|(
operator|&
name|info
operator|->
name|default_url
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|default_url
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_bounds
argument_list|(
name|param
operator|->
name|description
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
name|description
operator|=
name|gtk_text_buffer_get_text
argument_list|(
name|param
operator|->
name|description
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_strreplace
argument_list|(
operator|&
name|info
operator|->
name|description
argument_list|,
name|description
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|description
argument_list|)
expr_stmt|;
name|info
operator|->
name|map_format
operator|=
name|_map_format
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|type_toggled_cb (GtkWidget * widget,gpointer data)
name|type_toggled_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
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
name|_map_format
operator|=
operator|(
name|MapFormat_t
operator|)
name|data
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|SettingsDialog_t
modifier|*
DECL|function|create_settings_dialog (void)
name|create_settings_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|SettingsDialog_t
modifier|*
name|data
init|=
name|g_new
argument_list|(
name|SettingsDialog_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|,
modifier|*
name|view
decl_stmt|,
modifier|*
name|frame
decl_stmt|,
modifier|*
name|hbox
decl_stmt|,
modifier|*
name|label
decl_stmt|,
modifier|*
name|swin
decl_stmt|;
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|data
operator|->
name|dialog
operator|=
name|make_default_dialog
argument_list|(
name|_
argument_list|(
literal|"Settings for this Mapfile"
argument_list|)
argument_list|)
expr_stmt|;
name|default_dialog_set_ok_cb
argument_list|(
name|dialog
argument_list|,
name|settings_ok_cb
argument_list|,
operator|(
name|gpointer
operator|)
name|data
argument_list|)
expr_stmt|;
name|table
operator|=
name|default_dialog_add_table
argument_list|(
name|dialog
argument_list|,
literal|9
argument_list|,
literal|2
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
name|_
argument_list|(
literal|"Filename:"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|filename
operator|=
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Image name:"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|imagename
operator|=
name|browse_widget_new
argument_list|(
name|_
argument_list|(
literal|"Select Image File"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|data
operator|->
name|imagename
operator|->
name|hbox
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|label
operator|=
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Title:"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|title
operator|=
name|create_entry_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|label
operator|=
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Aut_hor:"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|author
operator|=
name|create_entry_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|3
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|label
operator|=
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Default _URL:"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|default_url
operator|=
name|create_entry_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|4
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|label
operator|=
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|5
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Description:"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|description
operator|=
name|gtk_text_buffer_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|view
operator|=
name|gtk_text_view_new_with_buffer
argument_list|(
name|data
operator|->
name|description
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|view
argument_list|,
operator|-
literal|1
argument_list|,
literal|128
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|swin
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_shadow_type
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|swin
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|swin
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|5
argument_list|,
literal|8
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|swin
argument_list|)
argument_list|,
name|GTK_POLICY_NEVER
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|swin
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|swin
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Map File Format"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
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
literal|9
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
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
name|data
operator|->
name|ncsa
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|NULL
argument_list|,
literal|"_NCSA"
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|ncsa
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|type_toggled_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|NCSA
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|data
operator|->
name|ncsa
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
name|data
operator|->
name|ncsa
argument_list|)
expr_stmt|;
name|data
operator|->
name|cern
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|data
operator|->
name|ncsa
argument_list|)
argument_list|,
literal|"C_ERN"
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|cern
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|type_toggled_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|CERN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|data
operator|->
name|cern
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
name|data
operator|->
name|cern
argument_list|)
expr_stmt|;
name|data
operator|->
name|csim
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|data
operator|->
name|cern
argument_list|)
argument_list|,
literal|"C_SIM"
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|csim
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|type_toggled_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|CSIM
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|data
operator|->
name|csim
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
name|data
operator|->
name|csim
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

begin_function
name|void
DECL|function|do_settings_dialog (void)
name|do_settings_dialog
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|SettingsDialog_t
modifier|*
name|dialog
decl_stmt|;
specifier|const
name|char
modifier|*
name|filename
init|=
name|get_filename
argument_list|()
decl_stmt|;
name|MapInfo_t
modifier|*
name|info
init|=
name|get_map_info
argument_list|()
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
name|dialog
operator|=
name|create_settings_dialog
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|filename
condition|)
name|filename
operator|=
name|_
argument_list|(
literal|"<Untitled>"
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|filename
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|browse_widget_set_filename
argument_list|(
name|dialog
operator|->
name|imagename
argument_list|,
name|info
operator|->
name|image_name
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|dialog
operator|->
name|title
argument_list|)
argument_list|,
name|info
operator|->
name|title
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|dialog
operator|->
name|author
argument_list|)
argument_list|,
name|info
operator|->
name|author
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|dialog
operator|->
name|default_url
argument_list|)
argument_list|,
name|info
operator|->
name|default_url
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|map_format
operator|==
name|NCSA
condition|)
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|dialog
operator|->
name|ncsa
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|info
operator|->
name|map_format
operator|==
name|CERN
condition|)
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|dialog
operator|->
name|cern
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|dialog
operator|->
name|csim
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|dialog
operator|->
name|imagename
operator|->
name|file
argument_list|)
expr_stmt|;
name|default_dialog_show
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|gtk_text_buffer_set_text
argument_list|(
name|dialog
operator|->
name|description
argument_list|,
name|info
operator|->
name|description
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

