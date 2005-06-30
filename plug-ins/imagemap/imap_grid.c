begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
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
file|"imap_grid.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"imap_menu.h"
end_include

begin_include
include|#
directive|include
file|"imap_preview.h"
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
DECL|enum|__anon2a04d4790103
DECL|enumerator|GRID_HIDDEN
DECL|enumerator|GRID_LINES
DECL|enumerator|GRID_CROSSES
DECL|typedef|GridType_t
typedef|typedef
enum|enum
block|{
name|GRID_HIDDEN
block|,
name|GRID_LINES
block|,
name|GRID_CROSSES
block|}
name|GridType_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a04d4790208
typedef|typedef
struct|struct
block|{
DECL|member|dialog
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
DECL|member|type_frame
name|GtkWidget
modifier|*
name|type_frame
decl_stmt|;
DECL|member|granularity_frame
name|GtkWidget
modifier|*
name|granularity_frame
decl_stmt|;
DECL|member|offset_frame
name|GtkWidget
modifier|*
name|offset_frame
decl_stmt|;
DECL|member|snap
name|GtkWidget
modifier|*
name|snap
decl_stmt|;
DECL|member|width
name|GtkWidget
modifier|*
name|width
decl_stmt|;
DECL|member|height
name|GtkWidget
modifier|*
name|height
decl_stmt|;
DECL|member|chain_width_height
name|GtkWidget
modifier|*
name|chain_width_height
decl_stmt|;
DECL|member|left
name|GtkWidget
modifier|*
name|left
decl_stmt|;
DECL|member|top
name|GtkWidget
modifier|*
name|top
decl_stmt|;
DECL|member|chain_left_top
name|GtkWidget
modifier|*
name|chain_left_top
decl_stmt|;
DECL|member|hidden
name|GtkWidget
modifier|*
name|hidden
decl_stmt|;
DECL|member|lines
name|GtkWidget
modifier|*
name|lines
decl_stmt|;
DECL|member|crosses
name|GtkWidget
modifier|*
name|crosses
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|enable_preview
name|gboolean
name|enable_preview
decl_stmt|;
DECL|typedef|GridDialog_t
block|}
name|GridDialog_t
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|grid_gc
specifier|static
name|GdkGC
modifier|*
name|grid_gc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|grid_snap
specifier|static
name|gboolean
name|grid_snap
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|grid_width
specifier|static
name|gint
name|grid_width
init|=
literal|15
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|grid_height
specifier|static
name|gint
name|grid_height
init|=
literal|15
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|grid_left
specifier|static
name|gint
name|grid_left
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|grid_top
specifier|static
name|gint
name|grid_top
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|grid_type
specifier|static
name|GridType_t
name|grid_type
init|=
name|GRID_LINES
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|grid_settings_ok_cb (gpointer data)
name|grid_settings_ok_cb
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GridDialog_t
modifier|*
name|param
init|=
operator|(
name|GridDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|gboolean
name|new_snap
decl_stmt|;
name|new_snap
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|param
operator|->
name|snap
argument_list|)
argument_list|)
expr_stmt|;
name|grid_width
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|width
argument_list|)
argument_list|)
expr_stmt|;
name|grid_height
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|height
argument_list|)
argument_list|)
expr_stmt|;
name|grid_left
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|left
argument_list|)
argument_list|)
expr_stmt|;
name|grid_top
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|top
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|grid_snap
operator|!=
name|new_snap
condition|)
block|{
name|grid_snap
operator|=
name|new_snap
expr_stmt|;
name|menu_check_grid
argument_list|(
name|grid_snap
argument_list|)
expr_stmt|;
block|}
name|redraw_preview
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|snap_toggled_cb (GtkWidget * widget,gpointer data)
name|snap_toggled_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GridDialog_t
modifier|*
name|param
init|=
operator|(
name|GridDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|sensitive
init|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|param
operator|->
name|type_frame
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|param
operator|->
name|granularity_frame
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|param
operator|->
name|offset_frame
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|param
operator|->
name|preview
argument_list|,
name|sensitive
argument_list|)
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
block|{
name|grid_type
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|redraw_preview
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|toggle_preview_cb (GtkWidget * widget,GridDialog_t * param)
name|toggle_preview_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GridDialog_t
modifier|*
name|param
parameter_list|)
block|{
name|param
operator|->
name|enable_preview
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|redraw_preview
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|grid_assign_value (GtkWidget * widget,gpointer data,gint * value)
name|grid_assign_value
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint
modifier|*
name|value
parameter_list|)
block|{
name|GridDialog_t
modifier|*
name|dialog
init|=
operator|(
name|GridDialog_t
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|enable_preview
condition|)
block|{
operator|*
name|value
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|redraw_preview
argument_list|()
expr_stmt|;
comment|/* Fix me! */
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|width_changed_cb (GtkWidget * widget,gpointer data)
name|width_changed_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GridDialog_t
modifier|*
name|dialog
init|=
operator|(
name|GridDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|grid_assign_value
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
operator|&
name|grid_width
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_chain_button_get_active
argument_list|(
name|GIMP_CHAIN_BUTTON
argument_list|(
name|dialog
operator|->
name|chain_width_height
argument_list|)
argument_list|)
condition|)
block|{
name|gint
name|value
init|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|dialog
operator|->
name|height
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|height_changed_cb (GtkWidget * widget,gpointer data)
name|height_changed_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GridDialog_t
modifier|*
name|dialog
init|=
operator|(
name|GridDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|grid_assign_value
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
operator|&
name|grid_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_chain_button_get_active
argument_list|(
name|GIMP_CHAIN_BUTTON
argument_list|(
name|dialog
operator|->
name|chain_width_height
argument_list|)
argument_list|)
condition|)
block|{
name|gint
name|value
init|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|dialog
operator|->
name|width
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|left_changed_cb (GtkWidget * widget,gpointer data)
name|left_changed_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GridDialog_t
modifier|*
name|dialog
init|=
operator|(
name|GridDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|grid_assign_value
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
operator|&
name|grid_left
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_chain_button_get_active
argument_list|(
name|GIMP_CHAIN_BUTTON
argument_list|(
name|dialog
operator|->
name|chain_left_top
argument_list|)
argument_list|)
condition|)
block|{
name|gint
name|value
init|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|dialog
operator|->
name|top
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|top_changed_cb (GtkWidget * widget,gpointer data)
name|top_changed_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GridDialog_t
modifier|*
name|dialog
init|=
operator|(
name|GridDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|grid_assign_value
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
operator|&
name|grid_top
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_chain_button_get_active
argument_list|(
name|GIMP_CHAIN_BUTTON
argument_list|(
name|dialog
operator|->
name|chain_left_top
argument_list|)
argument_list|)
condition|)
block|{
name|gint
name|value
init|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|dialog
operator|->
name|left
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GridDialog_t
modifier|*
DECL|function|create_grid_settings_dialog (void)
name|create_grid_settings_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GridDialog_t
modifier|*
name|data
init|=
name|g_new
argument_list|(
name|GridDialog_t
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
name|main_table
decl_stmt|,
modifier|*
name|table
decl_stmt|,
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|chain_button
decl_stmt|;
name|data
operator|->
name|dialog
operator|=
name|dialog
operator|=
name|make_default_dialog
argument_list|(
name|_
argument_list|(
literal|"Grid Settings"
argument_list|)
argument_list|)
expr_stmt|;
name|default_dialog_set_ok_cb
argument_list|(
name|dialog
argument_list|,
name|grid_settings_ok_cb
argument_list|,
operator|(
name|gpointer
operator|)
name|data
argument_list|)
expr_stmt|;
name|main_table
operator|=
name|default_dialog_add_table
argument_list|(
name|dialog
argument_list|,
literal|4
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|data
operator|->
name|snap
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Snap-To Grid Enabled"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|snap
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|snap_toggled_cb
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|main_table
argument_list|)
argument_list|,
name|data
operator|->
name|snap
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|data
operator|->
name|snap
argument_list|)
expr_stmt|;
name|data
operator|->
name|type_frame
operator|=
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Grid Visibility and Type"
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
name|main_table
argument_list|)
argument_list|,
name|frame
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
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
name|button
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"_Hidden"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|hidden
operator|=
name|button
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
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
name|GRID_HIDDEN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Lines"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|lines
operator|=
name|button
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
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
name|GRID_LINES
argument_list|)
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"C_rosses"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|crosses
operator|=
name|button
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
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
name|GRID_CROSSES
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|data
operator|->
name|granularity_frame
operator|=
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Grid Granularity"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|main_table
argument_list|)
argument_list|,
name|frame
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|table
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|label
operator|=
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
literal|"_Width"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|width
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|15
argument_list|,
literal|1
argument_list|,
literal|100
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|width
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|width_changed_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|data
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
name|_
argument_list|(
literal|"pixels"
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
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
literal|"_Height"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|height
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|15
argument_list|,
literal|1
argument_list|,
literal|100
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|height
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|height_changed_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|data
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
name|_
argument_list|(
literal|"pixels"
argument_list|)
argument_list|)
expr_stmt|;
name|chain_button
operator|=
name|gimp_chain_button_new
argument_list|(
name|GIMP_CHAIN_RIGHT
argument_list|)
expr_stmt|;
name|data
operator|->
name|chain_width_height
operator|=
name|chain_button
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|chain_button
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|chain_button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|data
operator|->
name|offset_frame
operator|=
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Grid Offset"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|main_table
argument_list|)
argument_list|,
name|frame
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|label
operator|=
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"pixels from l_eft"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|left
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|100
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|left
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|left_changed_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|data
argument_list|)
expr_stmt|;
name|label
operator|=
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"pixels from _top"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|top
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|100
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|top
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|top_changed_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|data
argument_list|)
expr_stmt|;
name|chain_button
operator|=
name|gimp_chain_button_new
argument_list|(
name|GIMP_CHAIN_RIGHT
argument_list|)
expr_stmt|;
name|data
operator|->
name|chain_left_top
operator|=
name|chain_button
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|chain_button
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|chain_button
argument_list|)
expr_stmt|;
name|data
operator|->
name|preview
operator|=
name|create_check_button_in_table
argument_list|(
name|main_table
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|preview
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|toggle_preview_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|data
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|data
operator|->
name|preview
argument_list|)
expr_stmt|;
name|snap_toggled_cb
argument_list|(
name|data
operator|->
name|snap
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

begin_function
name|void
DECL|function|do_grid_settings_dialog (void)
name|do_grid_settings_dialog
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GridDialog_t
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|type
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
name|dialog
operator|=
name|create_grid_settings_dialog
argument_list|()
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|dialog
operator|->
name|snap
argument_list|)
argument_list|,
name|grid_snap
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|dialog
operator|->
name|width
argument_list|)
argument_list|,
name|grid_width
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|dialog
operator|->
name|height
argument_list|)
argument_list|,
name|grid_height
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|dialog
operator|->
name|left
argument_list|)
argument_list|,
name|grid_left
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|dialog
operator|->
name|top
argument_list|)
argument_list|,
name|grid_top
argument_list|)
expr_stmt|;
if|if
condition|(
name|grid_type
operator|==
name|GRID_HIDDEN
condition|)
name|type
operator|=
name|dialog
operator|->
name|hidden
expr_stmt|;
elseif|else
if|if
condition|(
name|grid_type
operator|==
name|GRID_LINES
condition|)
name|type
operator|=
name|dialog
operator|->
name|lines
expr_stmt|;
else|else
name|type
operator|=
name|dialog
operator|->
name|crosses
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|type
argument_list|)
argument_list|,
name|TRUE
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

begin_function
specifier|static
name|void
DECL|function|draw_lines (GdkWindow * window,GdkGC * gc,gint width,gint height)
name|draw_lines
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
for|for
control|(
name|x
operator|=
name|grid_left
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|+=
name|grid_width
control|)
name|draw_line
argument_list|(
name|window
argument_list|,
name|grid_gc
argument_list|,
name|x
argument_list|,
literal|1
argument_list|,
name|x
argument_list|,
name|height
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
name|grid_top
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|+=
name|grid_height
control|)
name|draw_line
argument_list|(
name|window
argument_list|,
name|grid_gc
argument_list|,
literal|1
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_crosses (GdkWindow * window,GdkGC * gc,gint width,gint height)
name|draw_crosses
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
for|for
control|(
name|x
operator|=
name|grid_left
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|+=
name|grid_width
control|)
block|{
for|for
control|(
name|y
operator|=
name|grid_top
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|+=
name|grid_height
control|)
block|{
name|draw_line
argument_list|(
name|window
argument_list|,
name|gc
argument_list|,
name|x
operator|-
literal|3
argument_list|,
name|y
argument_list|,
name|x
operator|+
literal|3
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|draw_line
argument_list|(
name|window
argument_list|,
name|gc
argument_list|,
name|x
argument_list|,
name|y
operator|-
literal|3
argument_list|,
name|x
argument_list|,
name|y
operator|+
literal|3
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|draw_grid (GtkWidget * preview)
name|draw_grid
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
if|if
condition|(
name|grid_snap
operator|&&
name|grid_type
operator|!=
name|GRID_HIDDEN
condition|)
block|{
name|gint
name|width
init|=
name|preview_get_width
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|preview_get_height
argument_list|(
name|preview
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|grid_gc
condition|)
block|{
name|grid_gc
operator|=
name|gdk_gc_new
argument_list|(
name|preview
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_gc_set_line_attributes
argument_list|(
name|grid_gc
argument_list|,
literal|1
argument_list|,
name|GDK_LINE_ON_OFF_DASH
argument_list|,
name|GDK_CAP_BUTT
argument_list|,
name|GDK_JOIN_BEVEL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|grid_type
operator|==
name|GRID_LINES
condition|)
name|draw_lines
argument_list|(
name|preview
operator|->
name|window
argument_list|,
name|grid_gc
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
else|else
name|draw_crosses
argument_list|(
name|preview
operator|->
name|window
argument_list|,
name|preview
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|toggle_grid (void)
name|toggle_grid
parameter_list|(
name|void
parameter_list|)
block|{
name|grid_snap
operator|=
operator|!
name|grid_snap
expr_stmt|;
name|redraw_preview
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|grid_nearest_x (gint x)
name|grid_nearest_x
parameter_list|(
name|gint
name|x
parameter_list|)
block|{
return|return
name|grid_left
operator|+
operator|(
name|x
operator|-
name|grid_left
operator|+
name|grid_width
operator|/
literal|2
operator|)
operator|/
name|grid_width
operator|*
name|grid_width
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|grid_nearest_y (gint y)
name|grid_nearest_y
parameter_list|(
name|gint
name|y
parameter_list|)
block|{
return|return
name|grid_top
operator|+
operator|(
name|y
operator|-
name|grid_top
operator|+
name|grid_height
operator|/
literal|2
operator|)
operator|/
name|grid_height
operator|*
name|grid_height
return|;
block|}
end_function

begin_function
name|void
DECL|function|round_to_grid (gint * x,gint * y)
name|round_to_grid
parameter_list|(
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
block|{
if|if
condition|(
name|grid_snap
condition|)
block|{
operator|*
name|x
operator|=
name|grid_nearest_x
argument_list|(
operator|*
name|x
argument_list|)
expr_stmt|;
operator|*
name|y
operator|=
name|grid_nearest_y
argument_list|(
operator|*
name|y
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|grid_near_x (gint x)
name|grid_near_x
parameter_list|(
name|gint
name|x
parameter_list|)
block|{
return|return
name|grid_snap
operator|&&
name|grid_type
operator|!=
name|GRID_HIDDEN
operator|&&
name|abs
argument_list|(
name|grid_nearest_x
argument_list|(
name|x
argument_list|)
operator|-
name|x
argument_list|)
operator|<=
literal|1
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|grid_near_y (gint y)
name|grid_near_y
parameter_list|(
name|gint
name|y
parameter_list|)
block|{
return|return
name|grid_snap
operator|&&
name|grid_type
operator|!=
name|GRID_HIDDEN
operator|&&
name|abs
argument_list|(
name|grid_nearest_x
argument_list|(
name|y
argument_list|)
operator|-
name|y
argument_list|)
operator|<=
literal|1
return|;
block|}
end_function

end_unit

