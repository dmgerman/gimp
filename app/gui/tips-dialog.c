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
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/wilber3.xpm"
end_include

begin_define
DECL|macro|TIPS_DIR_NAME
define|#
directive|define
name|TIPS_DIR_NAME
value|"tips"
end_define

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

begin_function_decl
specifier|static
name|void
name|read_tips_file
parameter_list|(
name|gchar
modifier|*
name|filename
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
DECL|variable|tips_label
specifier|static
name|GtkWidget
modifier|*
name|tips_label
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tips_text
specifier|static
name|gchar
modifier|*
modifier|*
name|tips_text
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|pixmap
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
if|if
condition|(
name|tips_count
operator|==
literal|0
condition|)
block|{
name|gchar
modifier|*
name|temp
decl_stmt|;
name|temp
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s"
argument|G_DIR_SEPARATOR_S TIPS_DIR_NAME                               G_DIR_SEPARATOR_S
literal|"%s"
argument_list|,
argument|gimp_data_directory ()
argument_list|,
argument|_(
literal|"gimp_tips.txt"
argument|)
argument_list|)
expr_stmt|;
name|read_tips_file
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
block|}
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
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
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
literal|5
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
name|tips_label
operator|=
name|gtk_label_new
argument_list|(
name|tips_text
index|[
name|gimprc
operator|.
name|last_tip
index|]
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|tips_label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|tips_label
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
name|hbox
argument_list|)
argument_list|,
name|tips_label
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tips_label
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
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|gimp_pixmap_new
argument_list|(
name|wilber3_xpm
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|pixmap
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
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
name|gtk_check_button_new_with_label
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|GTK_SIGNAL_FUNC
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
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Close"
argument_list|)
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
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|tips_dialog
argument_list|)
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
name|gtk_button_box_set_spacing
argument_list|(
name|GTK_BUTTON_BOX
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
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Previous Tip"
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|tips_show_previous
argument_list|)
argument_list|,
name|NULL
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
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Next Tip"
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|tips_show_next
argument_list|)
argument_list|,
name|NULL
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
comment|/*  Connect the "F1" help key  */
name|gimp_help_connect_help_accel
argument_list|(
name|tips_dialog
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/tip_of_the_day.html"
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
comment|/* the last-shown-tip is now saved in sessionrc */
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
name|gimprc
operator|.
name|last_tip
operator|--
expr_stmt|;
if|if
condition|(
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
name|tips_count
operator|-
literal|1
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|tips_label
argument_list|)
argument_list|,
name|tips_text
index|[
name|gimprc
operator|.
name|last_tip
index|]
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
name|gimprc
operator|.
name|last_tip
operator|++
expr_stmt|;
if|if
condition|(
name|gimprc
operator|.
name|last_tip
operator|>=
name|tips_count
condition|)
name|gimprc
operator|.
name|last_tip
operator|=
literal|0
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|tips_label
argument_list|)
argument_list|,
name|tips_text
index|[
name|gimprc
operator|.
name|last_tip
index|]
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

begin_function
specifier|static
name|void
DECL|function|store_tip (gchar * str)
name|store_tip
parameter_list|(
name|gchar
modifier|*
name|str
parameter_list|)
block|{
name|tips_count
operator|++
expr_stmt|;
name|tips_text
operator|=
name|g_realloc
argument_list|(
name|tips_text
argument_list|,
sizeof|sizeof
argument_list|(
name|gchar
operator|*
argument_list|)
operator|*
name|tips_count
argument_list|)
expr_stmt|;
name|tips_text
index|[
name|tips_count
operator|-
literal|1
index|]
operator|=
name|str
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|read_tips_file (gchar * filename)
name|read_tips_file
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gchar
modifier|*
name|tip
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|str
init|=
name|NULL
decl_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rt"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fp
condition|)
block|{
name|store_tip
argument_list|(
name|_
argument_list|(
literal|"Your GIMP tips file appears to be missing!\n"
literal|"There should be a file called gimp_tips.txt in\n"
literal|"the tips subdirectory of the GIMP data directory.\n"
literal|"Please check your installation."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|str
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
literal|1024
argument_list|)
expr_stmt|;
while|while
condition|(
operator|!
name|feof
argument_list|(
name|fp
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|str
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
condition|)
continue|continue;
if|if
condition|(
name|str
index|[
literal|0
index|]
operator|==
literal|'#'
operator|||
name|str
index|[
literal|0
index|]
operator|==
literal|'\n'
condition|)
block|{
if|if
condition|(
name|tip
operator|!=
name|NULL
condition|)
block|{
name|tip
index|[
name|strlen
argument_list|(
name|tip
argument_list|)
operator|-
literal|1
index|]
operator|=
literal|'\000'
expr_stmt|;
name|store_tip
argument_list|(
name|tip
argument_list|)
expr_stmt|;
name|tip
operator|=
name|NULL
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|tip
operator|==
name|NULL
condition|)
block|{
name|tip
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|strcpy
argument_list|(
name|tip
argument_list|,
name|str
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tip
operator|=
name|g_realloc
argument_list|(
name|tip
argument_list|,
name|strlen
argument_list|(
name|tip
argument_list|)
operator|+
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|strcat
argument_list|(
name|tip
argument_list|,
name|str
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|tip
operator|!=
name|NULL
condition|)
name|store_tip
argument_list|(
name|tip
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

