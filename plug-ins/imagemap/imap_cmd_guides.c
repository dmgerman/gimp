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
file|"imap_commands.h"
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

begin_include
include|#
directive|include
file|"imap_rectangle.h"
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
DECL|struct|__anon2c06ff870108
typedef|typedef
struct|struct
block|{
DECL|member|dialog
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
DECL|member|image_dimensions
name|GtkWidget
modifier|*
name|image_dimensions
decl_stmt|;
DECL|member|guide_bounds
name|GtkWidget
modifier|*
name|guide_bounds
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
DECL|member|horz_spacing
name|GtkWidget
modifier|*
name|horz_spacing
decl_stmt|;
DECL|member|vert_spacing
name|GtkWidget
modifier|*
name|vert_spacing
decl_stmt|;
DECL|member|no_across
name|GtkWidget
modifier|*
name|no_across
decl_stmt|;
DECL|member|no_down
name|GtkWidget
modifier|*
name|no_down
decl_stmt|;
DECL|member|base_url
name|GtkWidget
modifier|*
name|base_url
decl_stmt|;
DECL|member|list
name|ObjectList_t
modifier|*
name|list
decl_stmt|;
DECL|typedef|GuidesDialog_t
block|}
name|GuidesDialog_t
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|guides_ok_cb (gpointer data)
name|guides_ok_cb
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GuidesDialog_t
modifier|*
name|param
init|=
operator|(
name|GuidesDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|,
name|left
decl_stmt|,
name|top
decl_stmt|,
name|hspace
decl_stmt|,
name|vspace
decl_stmt|,
name|rows
decl_stmt|,
name|cols
decl_stmt|;
name|width
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
name|height
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
name|left
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
name|top
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
name|hspace
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|horz_spacing
argument_list|)
argument_list|)
expr_stmt|;
name|vspace
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|vert_spacing
argument_list|)
argument_list|)
expr_stmt|;
name|rows
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|no_down
argument_list|)
argument_list|)
expr_stmt|;
name|cols
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|no_across
argument_list|)
argument_list|)
expr_stmt|;
name|subcommand_start
argument_list|(
name|_
argument_list|(
literal|"Create Guides"
argument_list|)
argument_list|)
expr_stmt|;
name|y
operator|=
name|top
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|rows
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|x
init|=
name|left
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|cols
condition|;
name|j
operator|++
control|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|create_rectangle
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
decl_stmt|;
name|Command_t
modifier|*
name|command
init|=
name|create_command_new
argument_list|(
name|param
operator|->
name|list
argument_list|,
name|obj
argument_list|)
decl_stmt|;
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
name|base_url
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|command_execute
argument_list|(
name|command
argument_list|)
expr_stmt|;
name|x
operator|+=
name|width
operator|+
name|hspace
expr_stmt|;
block|}
name|y
operator|+=
name|height
operator|+
name|vspace
expr_stmt|;
block|}
name|subcommand_end
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|recalc_bounds (GtkWidget * widget,gpointer data)
name|recalc_bounds
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GuidesDialog_t
modifier|*
name|param
init|=
operator|(
name|GuidesDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|,
name|left
decl_stmt|,
name|top
decl_stmt|,
name|hspace
decl_stmt|,
name|vspace
decl_stmt|,
name|rows
decl_stmt|,
name|cols
decl_stmt|;
name|gint
name|bound_w
decl_stmt|,
name|bound_h
decl_stmt|;
name|gchar
modifier|*
name|bounds
decl_stmt|;
name|width
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
name|height
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
name|left
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
name|top
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
name|hspace
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|horz_spacing
argument_list|)
argument_list|)
expr_stmt|;
name|vspace
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|vert_spacing
argument_list|)
argument_list|)
expr_stmt|;
name|rows
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|no_down
argument_list|)
argument_list|)
expr_stmt|;
name|cols
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|param
operator|->
name|no_across
argument_list|)
argument_list|)
expr_stmt|;
name|bound_w
operator|=
operator|(
name|width
operator|+
name|hspace
operator|)
operator|*
name|cols
operator|-
name|hspace
expr_stmt|;
name|bound_h
operator|=
operator|(
name|height
operator|+
name|vspace
operator|)
operator|*
name|rows
operator|-
name|vspace
expr_stmt|;
name|bounds
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Resulting Guide Bounds: %d,%d to %d,%d (%d areas)"
argument_list|)
argument_list|,
name|left
argument_list|,
name|top
argument_list|,
name|left
operator|+
name|bound_w
argument_list|,
name|top
operator|+
name|bound_h
argument_list|,
name|rows
operator|*
name|cols
argument_list|)
expr_stmt|;
if|if
condition|(
name|left
operator|+
name|bound_w
operator|>
name|get_image_width
argument_list|()
operator|||
name|top
operator|+
name|bound_h
operator|>
name|get_image_height
argument_list|()
condition|)
block|{
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|param
operator|->
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|param
operator|->
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|param
operator|->
name|guide_bounds
argument_list|)
argument_list|,
name|bounds
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bounds
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GuidesDialog_t
modifier|*
DECL|function|make_guides_dialog (void)
name|make_guides_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GuidesDialog_t
modifier|*
name|data
init|=
name|g_new
argument_list|(
name|GuidesDialog_t
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
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
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
literal|"Create Guides"
argument_list|)
argument_list|)
expr_stmt|;
name|default_dialog_set_ok_cb
argument_list|(
name|dialog
argument_list|,
name|guides_ok_cb
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gimp_hint_box_new
argument_list|(
name|_
argument_list|(
literal|"Guides are pre-defined rectangles covering the image. You define "
literal|"them by their width, height, and spacing from each other. This "
literal|"allows you to rapidly create the most common image map type - "
literal|"image collection of \"thumbnails\", suitable for navigation bars."
argument_list|)
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
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|data
operator|->
name|image_dimensions
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
name|data
operator|->
name|image_dimensions
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
name|dialog
operator|->
name|vbox
argument_list|)
argument_list|,
name|data
operator|->
name|image_dimensions
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
name|image_dimensions
argument_list|)
expr_stmt|;
name|data
operator|->
name|guide_bounds
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
name|data
operator|->
name|guide_bounds
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
name|dialog
operator|->
name|vbox
argument_list|)
argument_list|,
name|data
operator|->
name|guide_bounds
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
name|guide_bounds
argument_list|)
expr_stmt|;
name|table
operator|=
name|default_dialog_add_table
argument_list|(
name|dialog
argument_list|,
literal|4
argument_list|,
literal|4
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
literal|"_Width:"
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
literal|32
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
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|recalc_bounds
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
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"_Left start at:"
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
literal|3
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
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|recalc_bounds
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
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Height:"
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
literal|32
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
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|recalc_bounds
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
literal|"_Top start at:"
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
literal|3
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
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|recalc_bounds
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
literal|2
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Horz. spacing:"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|horz_spacing
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|2
argument_list|,
literal|1
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
name|horz_spacing
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|recalc_bounds
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
literal|2
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"_No. across:"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|no_across
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|2
argument_list|,
literal|3
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
name|no_across
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|recalc_bounds
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
literal|3
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Vert. spacing:"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|vert_spacing
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|3
argument_list|,
literal|1
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
name|vert_spacing
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|recalc_bounds
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
literal|3
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"No. _down:"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|no_down
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|3
argument_list|,
literal|3
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
name|no_down
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|recalc_bounds
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|data
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
name|dialog
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
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Base _URL:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|data
operator|->
name|base_url
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|data
operator|->
name|base_url
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|data
operator|->
name|base_url
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|data
operator|->
name|base_url
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|init_guides_dialog (GuidesDialog_t * dialog,ObjectList_t * list)
name|init_guides_dialog
parameter_list|(
name|GuidesDialog_t
modifier|*
name|dialog
parameter_list|,
name|ObjectList_t
modifier|*
name|list
parameter_list|)
block|{
name|gchar
modifier|*
name|dimension
decl_stmt|;
name|dialog
operator|->
name|list
operator|=
name|list
expr_stmt|;
name|dimension
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Image dimensions: %d Ã %d"
argument_list|)
argument_list|,
name|get_image_width
argument_list|()
argument_list|,
name|get_image_height
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|image_dimensions
argument_list|)
argument_list|,
name|dimension
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dimension
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|guide_bounds
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Resulting Guide Bounds: 0,0 to 0,0 (0 areas)"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|dialog
operator|->
name|width
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|do_create_guides_dialog_local (ObjectList_t * list)
name|do_create_guides_dialog_local
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
block|{
specifier|static
name|GuidesDialog_t
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
name|dialog
operator|=
name|make_guides_dialog
argument_list|()
expr_stmt|;
name|init_guides_dialog
argument_list|(
name|dialog
argument_list|,
name|list
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

begin_function_decl
specifier|static
name|CmdExecuteValue_t
name|guides_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|guides_command_class
specifier|static
name|CommandClass_t
name|guides_command_class
init|=
block|{
name|NULL
block|,
comment|/* guides_command_destruct */
name|guides_command_execute
block|,
name|NULL
block|,
comment|/* guides_command_undo */
name|NULL
comment|/* guides_command_redo */
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|struct|__anon2c06ff870208
typedef|typedef
struct|struct
block|{
DECL|member|parent
name|Command_t
name|parent
decl_stmt|;
DECL|member|list
name|ObjectList_t
modifier|*
name|list
decl_stmt|;
DECL|typedef|GuidesCommand_t
block|}
name|GuidesCommand_t
typedef|;
end_typedef

begin_function
name|Command_t
modifier|*
DECL|function|guides_command_new (ObjectList_t * list)
name|guides_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
block|{
name|GuidesCommand_t
modifier|*
name|command
init|=
name|g_new
argument_list|(
name|GuidesCommand_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|command
operator|->
name|list
operator|=
name|list
expr_stmt|;
return|return
name|command_init
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|,
name|_
argument_list|(
literal|"Guides"
argument_list|)
argument_list|,
operator|&
name|guides_command_class
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|CmdExecuteValue_t
DECL|function|guides_command_execute (Command_t * parent)
name|guides_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|GuidesCommand_t
modifier|*
name|command
init|=
operator|(
name|GuidesCommand_t
operator|*
operator|)
name|parent
decl_stmt|;
name|do_create_guides_dialog_local
argument_list|(
name|command
operator|->
name|list
argument_list|)
expr_stmt|;
return|return
name|CMD_DESTRUCT
return|;
block|}
end_function

end_unit

