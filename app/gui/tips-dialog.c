begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"tips-dialog.h"
end_include

begin_include
include|#
directive|include
file|"tips-parser.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|tips_set_labels
parameter_list|(
name|GimpTip
modifier|*
name|tip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_dialog_destroy
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

begin_function_decl
specifier|static
name|void
name|tips_show_previous
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

begin_function_decl
specifier|static
name|void
name|tips_show_next
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

begin_function_decl
specifier|static
name|void
name|tips_toggle_update
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

begin_decl_stmt
DECL|variable|tips_dialog
specifier|static
name|GtkWidget
modifier|*
name|tips_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|welcome_label
specifier|static
name|GtkWidget
modifier|*
name|welcome_label
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thetip_label
specifier|static
name|GtkWidget
modifier|*
name|thetip_label
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tips
specifier|static
name|GList
modifier|*
name|tips
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|current_tip
specifier|static
name|GList
modifier|*
name|current_tip
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tips_count
specifier|static
name|gint
name|tips_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|old_show_tips
specifier|static
name|gint
name|old_show_tips
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
name|GtkWidget
modifier|*
DECL|function|tips_dialog_create (void)
name|tips_dialog_create
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox2
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|bbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GdkPixbuf
modifier|*
name|wilber
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
if|if
condition|(
operator|!
name|tips
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"tips"
argument_list|,
literal|"gimp-tips.xml"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tips
operator|=
name|gimp_tips_from_file
argument_list|(
name|filename
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|tips
operator|=
name|g_list_prepend
argument_list|(
name|tips
argument_list|,
name|gimp_tip_new
argument_list|(
name|_
argument_list|(
literal|"<b>The GIMP tips file could not be parsed correctly!</b>"
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
block|}
name|tips_count
operator|=
name|g_list_length
argument_list|(
name|tips
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimprc
operator|.
name|last_tip
operator|>=
name|tips_count
operator|||
name|gimprc
operator|.
name|last_tip
operator|<
literal|0
condition|)
name|gimprc
operator|.
name|last_tip
operator|=
literal|0
expr_stmt|;
name|current_tip
operator|=
name|g_list_nth
argument_list|(
name|tips
argument_list|,
name|gimprc
operator|.
name|last_tip
argument_list|)
expr_stmt|;
if|if
condition|(
name|tips_dialog
condition|)
return|return
name|tips_dialog
return|;
name|tips_dialog
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_TOPLEVEL
argument_list|)
expr_stmt|;
name|gtk_window_set_type_hint
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|GDK_WINDOW_TYPE_HINT_DIALOG
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
literal|"tip_of_the_day"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"GIMP Tip of the Day"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_CENTER
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tips_dialog_destroy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* destroy the tips window if the mainlevel gtk_main() function is left */
name|gtk_quit_add_destroy
argument_list|(
literal|1
argument_list|,
name|GTK_OBJECT
argument_list|(
name|tips_dialog
argument_list|)
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|tips_dialog
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
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|vbox2
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
name|vbox2
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
name|vbox2
argument_list|)
expr_stmt|;
name|welcome_label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|welcome_label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|welcome_label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|welcome_label
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|welcome_label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|thetip_label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|thetip_label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|thetip_label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|thetip_label
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|thetip_label
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
name|thetip_label
argument_list|)
expr_stmt|;
name|vbox2
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox2
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
name|vbox2
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"images"
argument_list|,
literal|"wilber-tips.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|wilber
operator|=
name|gdk_pixbuf_new_from_file
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|wilber
condition|)
block|{
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|image
operator|=
name|gtk_image_new_from_pixbuf
argument_list|(
name|wilber
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|wilber
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|image
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
name|image
argument_list|)
expr_stmt|;
block|}
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|15
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
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
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
name|button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Show tip next time GIMP starts"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|gimprc
operator|.
name|show_tips
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
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tips_toggle_update
argument_list|)
argument_list|,
operator|&
name|gimprc
operator|.
name|show_tips
argument_list|)
expr_stmt|;
name|old_show_tips
operator|=
name|gimprc
operator|.
name|show_tips
expr_stmt|;
name|bbox
operator|=
name|gtk_hbutton_box_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|bbox
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
name|bbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_from_stock
argument_list|(
name|GTK_STOCK_CLOSE
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_window_set_default
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|bbox
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|tips_dialog
argument_list|)
expr_stmt|;
name|bbox
operator|=
name|gtk_hbutton_box_new
argument_list|()
expr_stmt|;
name|gtk_button_box_set_layout
argument_list|(
name|GTK_BUTTON_BOX
argument_list|(
name|bbox
argument_list|)
argument_list|,
name|GTK_BUTTONBOX_END
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|bbox
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|bbox
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
name|bbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Previous Tip"
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WIDGET_UNSET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_RECEIVES_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
operator|(
name|tips_count
operator|>
literal|1
operator|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|bbox
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tips_show_previous
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Next Tip"
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WIDGET_UNSET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_RECEIVES_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
operator|(
name|tips_count
operator|>
literal|1
operator|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|bbox
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tips_show_next
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Connect the "F1" help key  */
name|gimp_help_connect
argument_list|(
name|tips_dialog
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/tip_of_the_day.html"
argument_list|)
expr_stmt|;
name|tips_set_labels
argument_list|(
name|current_tip
operator|->
name|data
argument_list|)
expr_stmt|;
return|return
name|tips_dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_dialog_destroy (GtkWidget * widget,gpointer data)
name|tips_dialog_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GList
modifier|*
name|update
init|=
name|NULL
decl_stmt|;
comment|/* options that should be updated in .gimprc */
name|GList
modifier|*
name|remove
init|=
name|NULL
decl_stmt|;
comment|/* options that should be commented out */
name|tips_dialog
operator|=
name|NULL
expr_stmt|;
name|current_tip
operator|=
name|NULL
expr_stmt|;
name|gimp_tips_free
argument_list|(
name|tips
argument_list|)
expr_stmt|;
name|tips
operator|=
name|NULL
expr_stmt|;
comment|/* the last-shown-tip is now saved in sessionrc */
name|gimprc
operator|.
name|last_tip
operator|=
name|g_list_position
argument_list|(
name|tips
argument_list|,
name|current_tip
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimprc
operator|.
name|show_tips
operator|!=
name|old_show_tips
condition|)
block|{
name|update
operator|=
name|g_list_append
argument_list|(
name|update
argument_list|,
literal|"show-tips"
argument_list|)
expr_stmt|;
name|remove
operator|=
name|g_list_append
argument_list|(
name|remove
argument_list|,
literal|"dont-show-tips"
argument_list|)
expr_stmt|;
name|old_show_tips
operator|=
name|gimprc
operator|.
name|show_tips
expr_stmt|;
name|gimprc_save
argument_list|(
operator|&
name|update
argument_list|,
operator|&
name|remove
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|update
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|remove
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_set_labels (GimpTip * tip)
name|tips_set_labels
parameter_list|(
name|GimpTip
modifier|*
name|tip
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tip
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|tip
operator|->
name|welcome
condition|)
name|gtk_widget_show
argument_list|(
name|welcome_label
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_hide
argument_list|(
name|welcome_label
argument_list|)
expr_stmt|;
name|gtk_label_set_markup
argument_list|(
name|GTK_LABEL
argument_list|(
name|welcome_label
argument_list|)
argument_list|,
name|tip
operator|->
name|welcome
argument_list|)
expr_stmt|;
name|gtk_label_set_markup
argument_list|(
name|GTK_LABEL
argument_list|(
name|thetip_label
argument_list|)
argument_list|,
name|tip
operator|->
name|thetip
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_show_previous (GtkWidget * widget,gpointer data)
name|tips_show_previous
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|current_tip
operator|=
name|current_tip
operator|->
name|prev
condition|?
name|current_tip
operator|->
name|prev
else|:
name|g_list_last
argument_list|(
name|tips
argument_list|)
expr_stmt|;
name|tips_set_labels
argument_list|(
name|current_tip
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_show_next (GtkWidget * widget,gpointer data)
name|tips_show_next
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|current_tip
operator|=
name|current_tip
operator|->
name|next
condition|?
name|current_tip
operator|->
name|next
else|:
name|tips
expr_stmt|;
name|tips_set_labels
argument_list|(
name|current_tip
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_toggle_update (GtkWidget * widget,gpointer data)
name|tips_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
modifier|*
name|toggle_val
decl_stmt|;
name|toggle_val
operator|=
operator|(
name|gint
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
operator|*
name|toggle_val
operator|=
name|TRUE
expr_stmt|;
else|else
operator|*
name|toggle_val
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

