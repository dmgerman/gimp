begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Manish Singh  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbsse.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"color_area.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay_color.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay_color_ui.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageP.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_typedef
DECL|typedef|ColorDisplayDialog
typedef|typedef
name|struct
name|_ColorDisplayDialog
name|ColorDisplayDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_ColorDisplayDialog
struct|struct
name|_ColorDisplayDialog
block|{
DECL|member|gdisp
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|src
name|GtkWidget
modifier|*
name|src
decl_stmt|;
DECL|member|dest
name|GtkWidget
modifier|*
name|dest
decl_stmt|;
DECL|member|src_row
name|gint
name|src_row
decl_stmt|;
DECL|member|dest_row
name|gint
name|dest_row
decl_stmt|;
DECL|member|modified
name|gboolean
name|modified
decl_stmt|;
DECL|member|old_nodes
name|GList
modifier|*
name|old_nodes
decl_stmt|;
DECL|member|conf_nodes
name|GList
modifier|*
name|conf_nodes
decl_stmt|;
DECL|member|buttons
name|GtkWidget
modifier|*
name|buttons
index|[
literal|5
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_enum
enum|enum
DECL|enum|__anon29bbea910103
block|{
DECL|enumerator|BUTTON_ADD
name|BUTTON_ADD
block|,
DECL|enumerator|BUTTON_REMOVE
name|BUTTON_REMOVE
block|,
DECL|enumerator|BUTTON_UP
name|BUTTON_UP
block|,
DECL|enumerator|BUTTON_DOWN
name|BUTTON_DOWN
block|,
DECL|enumerator|BUTTON_CONFIGURE
name|BUTTON_CONFIGURE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|ButtonCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|ButtonCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ButtonInfo
typedef|typedef
name|struct
name|_ButtonInfo
name|ButtonInfo
typedef|;
end_typedef

begin_struct
DECL|struct|_ButtonInfo
struct|struct
name|_ButtonInfo
block|{
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|callback
name|ButtonCallback
name|callback
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|make_dialog
parameter_list|(
name|ColorDisplayDialog
modifier|*
name|cdd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_display_ok_callback
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
name|color_display_cancel_callback
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
name|color_display_add_callback
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
name|color_display_remove_callback
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
name|color_display_up_callback
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
name|color_display_down_callback
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
name|color_display_configure_callback
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
name|src_list_populate
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dest_list_populate
parameter_list|(
name|GList
modifier|*
name|node_list
parameter_list|,
name|GtkWidget
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|select_src
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|unselect_src
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|select_dest
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|unselect_dest
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_display_update_up_and_down
parameter_list|(
name|ColorDisplayDialog
modifier|*
name|cdd
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|LIST_WIDTH
define|#
directive|define
name|LIST_WIDTH
value|180
end_define

begin_define
DECL|macro|LIST_HEIGHT
define|#
directive|define
name|LIST_HEIGHT
value|180
end_define

begin_define
DECL|macro|UPDATE_DISPLAY (gdisp)
define|#
directive|define
name|UPDATE_DISPLAY
parameter_list|(
name|gdisp
parameter_list|)
value|G_STMT_START {	\   if (gdisp != color_area_gdisp)		\     {						\       gdisplay_expose_full (gdisp);		\       gdisplay_flush (gdisp);			\     }						\ } G_STMT_END
end_define

begin_function
specifier|static
name|void
DECL|function|make_dialog (ColorDisplayDialog * cdd)
name|make_dialog
parameter_list|(
name|ColorDisplayDialog
modifier|*
name|cdd
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|;
name|GtkWidget
modifier|*
name|vbbox
decl_stmt|;
name|gchar
modifier|*
name|titles
index|[
literal|2
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
specifier|static
name|ButtonInfo
name|buttons
index|[]
init|=
block|{
block|{
name|N_
argument_list|(
literal|"Add"
argument_list|)
block|,
name|color_display_add_callback
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Remove"
argument_list|)
block|,
name|color_display_remove_callback
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Up"
argument_list|)
block|,
name|color_display_up_callback
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Down"
argument_list|)
block|,
name|color_display_down_callback
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Configure"
argument_list|)
block|,
name|color_display_configure_callback
block|}
block|}
decl_stmt|;
name|cdd
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Color Display Filters"
argument_list|)
argument_list|,
literal|"display_color"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/display_filters/display_filters.html"
argument_list|,
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|color_display_ok_callback
argument_list|,
name|cdd
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|color_display_cancel_callback
argument_list|,
name|cdd
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog_register
argument_list|(
name|cdd
operator|->
name|shell
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|cdd
operator|->
name|shell
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
literal|4
argument_list|)
expr_stmt|;
name|scrolled_win
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|scrolled_win
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|titles
index|[
literal|0
index|]
operator|=
name|_
argument_list|(
literal|"Available Filters"
argument_list|)
expr_stmt|;
name|titles
index|[
literal|1
index|]
operator|=
name|NULL
expr_stmt|;
name|cdd
operator|->
name|src
operator|=
name|gtk_clist_new_with_titles
argument_list|(
literal|1
argument_list|,
name|titles
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|cdd
operator|->
name|src
argument_list|,
name|LIST_WIDTH
argument_list|,
name|LIST_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_clist_column_titles_passive
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|src
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_clist_set_auto_sort
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|src
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|cdd
operator|->
name|src
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|cdd
operator|->
name|src
argument_list|)
argument_list|,
literal|"select_row"
argument_list|,
name|G_CALLBACK
argument_list|(
name|select_src
argument_list|)
argument_list|,
name|cdd
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|cdd
operator|->
name|src
argument_list|)
argument_list|,
literal|"unselect_row"
argument_list|,
name|G_CALLBACK
argument_list|(
name|unselect_src
argument_list|)
argument_list|,
name|cdd
argument_list|)
expr_stmt|;
name|vbbox
operator|=
name|gtk_vbutton_box_new
argument_list|()
expr_stmt|;
name|gtk_vbutton_box_set_layout_default
argument_list|(
name|GTK_BUTTONBOX_START
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|scrolled_win
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|scrolled_win
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|titles
index|[
literal|0
index|]
operator|=
name|_
argument_list|(
literal|"Active Filters"
argument_list|)
expr_stmt|;
name|titles
index|[
literal|1
index|]
operator|=
name|NULL
expr_stmt|;
name|cdd
operator|->
name|dest
operator|=
name|gtk_clist_new_with_titles
argument_list|(
literal|1
argument_list|,
name|titles
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|cdd
operator|->
name|dest
argument_list|,
name|LIST_WIDTH
argument_list|,
name|LIST_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_clist_column_titles_passive
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|cdd
operator|->
name|dest
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
literal|"select_row"
argument_list|,
name|G_CALLBACK
argument_list|(
name|select_dest
argument_list|)
argument_list|,
name|cdd
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
literal|"unselect_row"
argument_list|,
name|G_CALLBACK
argument_list|(
name|unselect_dest
argument_list|)
argument_list|,
name|cdd
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
literal|5
condition|;
name|i
operator|++
control|)
block|{
name|cdd
operator|->
name|buttons
index|[
name|i
index|]
operator|=
name|gtk_button_new_with_label
argument_list|(
name|gettext
argument_list|(
name|buttons
index|[
name|i
index|]
operator|.
name|label
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbbox
argument_list|)
argument_list|,
name|cdd
operator|->
name|buttons
index|[
name|i
index|]
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|cdd
operator|->
name|buttons
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|buttons
index|[
name|i
index|]
operator|.
name|callback
argument_list|)
argument_list|,
name|cdd
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|cdd
operator|->
name|buttons
index|[
name|i
index|]
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show_all
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_display_ok_callback (GtkWidget * widget,gpointer data)
name|color_display_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
init|=
name|cdd
operator|->
name|gdisp
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|dialog_unregister
argument_list|(
name|cdd
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|cdd
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|cd_ui
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|cdd
operator|->
name|modified
condition|)
block|{
name|list
operator|=
name|cdd
operator|->
name|old_nodes
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
if|if
condition|(
operator|!
name|g_list_find
argument_list|(
name|gdisp
operator|->
name|cd_list
argument_list|,
name|list
operator|->
name|data
argument_list|)
condition|)
name|gdisplay_color_detach_destroy
argument_list|(
name|gdisp
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|list
operator|->
name|next
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|cdd
operator|->
name|old_nodes
argument_list|)
expr_stmt|;
name|UPDATE_DISPLAY
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_display_cancel_callback (GtkWidget * widget,gpointer data)
name|color_display_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
init|=
name|cdd
operator|->
name|gdisp
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|next
decl_stmt|;
name|dialog_unregister
argument_list|(
name|cdd
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|cdd
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|cd_ui
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|cdd
operator|->
name|modified
condition|)
block|{
name|list
operator|=
name|gdisp
operator|->
name|cd_list
expr_stmt|;
name|gdisp
operator|->
name|cd_list
operator|=
name|cdd
operator|->
name|old_nodes
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|next
operator|=
name|list
operator|->
name|next
expr_stmt|;
if|if
condition|(
operator|!
name|g_list_find
argument_list|(
name|cdd
operator|->
name|old_nodes
argument_list|,
name|list
operator|->
name|data
argument_list|)
condition|)
name|gdisplay_color_detach_destroy
argument_list|(
name|gdisp
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|next
expr_stmt|;
block|}
name|UPDATE_DISPLAY
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_display_update_up_and_down (ColorDisplayDialog * cdd)
name|color_display_update_up_and_down
parameter_list|(
name|ColorDisplayDialog
modifier|*
name|cdd
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|cdd
operator|->
name|buttons
index|[
name|BUTTON_UP
index|]
argument_list|,
name|cdd
operator|->
name|dest_row
operator|>
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|cdd
operator|->
name|buttons
index|[
name|BUTTON_DOWN
index|]
argument_list|,
name|cdd
operator|->
name|dest_row
operator|>=
literal|0
operator|&&
name|cdd
operator|->
name|dest_row
operator|<
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
operator|->
name|rows
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_display_add_callback (GtkWidget * widget,gpointer data)
name|color_display_add_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
init|=
name|cdd
operator|->
name|gdisp
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|ColorDisplayNode
modifier|*
name|node
decl_stmt|;
name|gint
name|row
decl_stmt|;
if|if
condition|(
name|cdd
operator|->
name|src_row
operator|<
literal|0
condition|)
return|return;
name|gtk_clist_get_text
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|src
argument_list|)
argument_list|,
name|cdd
operator|->
name|src_row
argument_list|,
literal|0
argument_list|,
operator|&
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
return|return;
name|cdd
operator|->
name|modified
operator|=
name|TRUE
expr_stmt|;
name|node
operator|=
name|gdisplay_color_attach
argument_list|(
name|gdisp
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|row
operator|=
name|gtk_clist_append
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
operator|&
name|name
argument_list|)
expr_stmt|;
name|gtk_clist_set_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
name|row
argument_list|,
name|node
argument_list|)
expr_stmt|;
name|color_display_update_up_and_down
argument_list|(
name|cdd
argument_list|)
expr_stmt|;
name|UPDATE_DISPLAY
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_display_remove_callback (GtkWidget * widget,gpointer data)
name|color_display_remove_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
init|=
name|cdd
operator|->
name|gdisp
decl_stmt|;
name|ColorDisplayNode
modifier|*
name|node
decl_stmt|;
if|if
condition|(
name|cdd
operator|->
name|dest_row
operator|<
literal|0
condition|)
return|return;
name|node
operator|=
name|gtk_clist_get_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
name|cdd
operator|->
name|dest_row
argument_list|)
expr_stmt|;
name|gtk_clist_remove
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
name|cdd
operator|->
name|dest_row
argument_list|)
expr_stmt|;
name|cdd
operator|->
name|modified
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|g_list_find
argument_list|(
name|cdd
operator|->
name|old_nodes
argument_list|,
name|node
argument_list|)
condition|)
name|gdisplay_color_detach
argument_list|(
name|gdisp
argument_list|,
name|node
argument_list|)
expr_stmt|;
else|else
name|gdisplay_color_detach_destroy
argument_list|(
name|gdisp
argument_list|,
name|node
argument_list|)
expr_stmt|;
name|cdd
operator|->
name|dest_row
operator|=
operator|-
literal|1
expr_stmt|;
name|color_display_update_up_and_down
argument_list|(
name|cdd
argument_list|)
expr_stmt|;
name|UPDATE_DISPLAY
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_display_up_callback (GtkWidget * widget,gpointer data)
name|color_display_up_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
init|=
name|cdd
operator|->
name|gdisp
decl_stmt|;
name|ColorDisplayNode
modifier|*
name|node
decl_stmt|;
if|if
condition|(
name|cdd
operator|->
name|dest_row
operator|<
literal|1
condition|)
return|return;
name|node
operator|=
name|gtk_clist_get_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
name|cdd
operator|->
name|dest_row
argument_list|)
expr_stmt|;
name|gtk_clist_row_move
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
name|cdd
operator|->
name|dest_row
argument_list|,
name|cdd
operator|->
name|dest_row
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gdisplay_color_reorder_up
argument_list|(
name|gdisp
argument_list|,
name|node
argument_list|)
expr_stmt|;
name|cdd
operator|->
name|modified
operator|=
name|TRUE
expr_stmt|;
name|cdd
operator|->
name|dest_row
operator|--
expr_stmt|;
name|color_display_update_up_and_down
argument_list|(
name|cdd
argument_list|)
expr_stmt|;
name|UPDATE_DISPLAY
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_display_down_callback (GtkWidget * widget,gpointer data)
name|color_display_down_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
init|=
name|cdd
operator|->
name|gdisp
decl_stmt|;
name|ColorDisplayNode
modifier|*
name|node
decl_stmt|;
if|if
condition|(
name|cdd
operator|->
name|dest_row
operator|<
literal|0
condition|)
return|return;
if|if
condition|(
name|cdd
operator|->
name|dest_row
operator|>=
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
operator|->
name|rows
operator|-
literal|1
condition|)
return|return;
name|node
operator|=
name|gtk_clist_get_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
name|cdd
operator|->
name|dest_row
argument_list|)
expr_stmt|;
name|gtk_clist_row_move
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
name|cdd
operator|->
name|dest_row
argument_list|,
name|cdd
operator|->
name|dest_row
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gdisplay_color_reorder_down
argument_list|(
name|gdisp
argument_list|,
name|node
argument_list|)
expr_stmt|;
name|cdd
operator|->
name|modified
operator|=
name|TRUE
expr_stmt|;
name|cdd
operator|->
name|dest_row
operator|++
expr_stmt|;
name|color_display_update_up_and_down
argument_list|(
name|cdd
argument_list|)
expr_stmt|;
name|UPDATE_DISPLAY
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_display_configure_callback (GtkWidget * widget,gpointer data)
name|color_display_configure_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
init|=
name|cdd
operator|->
name|gdisp
decl_stmt|;
name|ColorDisplayNode
modifier|*
name|node
decl_stmt|;
if|if
condition|(
name|cdd
operator|->
name|dest_row
operator|<
literal|0
condition|)
return|return;
name|node
operator|=
name|gtk_clist_get_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|,
name|cdd
operator|->
name|dest_row
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_list_find
argument_list|(
name|cdd
operator|->
name|conf_nodes
argument_list|,
name|node
argument_list|)
condition|)
name|cdd
operator|->
name|conf_nodes
operator|=
name|g_list_append
argument_list|(
name|cdd
operator|->
name|conf_nodes
argument_list|,
name|node
argument_list|)
expr_stmt|;
name|gdisplay_color_configure
argument_list|(
name|node
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cdd
operator|->
name|modified
operator|=
name|TRUE
expr_stmt|;
name|UPDATE_DISPLAY
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gdisplay_color_ui_new (GDisplay * gdisp)
name|gdisplay_color_ui_new
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
decl_stmt|;
name|cdd
operator|=
name|g_new0
argument_list|(
name|ColorDisplayDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|make_dialog
argument_list|(
name|cdd
argument_list|)
expr_stmt|;
name|gtk_clist_clear
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|src
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_clist_clear
argument_list|(
name|GTK_CLIST
argument_list|(
name|cdd
operator|->
name|dest
argument_list|)
argument_list|)
expr_stmt|;
name|color_display_foreach
argument_list|(
name|src_list_populate
argument_list|,
name|cdd
operator|->
name|src
argument_list|)
expr_stmt|;
name|cdd
operator|->
name|old_nodes
operator|=
name|gdisp
operator|->
name|cd_list
expr_stmt|;
name|dest_list_populate
argument_list|(
name|gdisp
operator|->
name|cd_list
argument_list|,
name|cdd
operator|->
name|dest
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|cd_list
operator|=
name|g_list_copy
argument_list|(
name|cdd
operator|->
name|old_nodes
argument_list|)
expr_stmt|;
name|cdd
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|cdd
operator|->
name|src_row
operator|=
operator|-
literal|1
expr_stmt|;
name|cdd
operator|->
name|dest_row
operator|=
operator|-
literal|1
expr_stmt|;
name|gdisp
operator|->
name|cd_ui
operator|=
name|cdd
operator|->
name|shell
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|src_list_populate (const char * name,gpointer data)
name|src_list_populate
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
name|gtk_clist_append
argument_list|(
name|GTK_CLIST
argument_list|(
name|data
argument_list|)
argument_list|,
operator|(
name|gchar
operator|*
operator|*
operator|)
operator|&
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dest_list_populate (GList * node_list,GtkWidget * dest)
name|dest_list_populate
parameter_list|(
name|GList
modifier|*
name|node_list
parameter_list|,
name|GtkWidget
modifier|*
name|dest
parameter_list|)
block|{
name|ColorDisplayNode
modifier|*
name|node
decl_stmt|;
name|int
name|row
decl_stmt|;
while|while
condition|(
name|node_list
condition|)
block|{
name|node
operator|=
name|node_list
operator|->
name|data
expr_stmt|;
name|row
operator|=
name|gtk_clist_append
argument_list|(
name|GTK_CLIST
argument_list|(
name|dest
argument_list|)
argument_list|,
operator|&
name|node
operator|->
name|cd_name
argument_list|)
expr_stmt|;
name|gtk_clist_set_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|dest
argument_list|)
argument_list|,
name|row
argument_list|,
name|node
argument_list|)
expr_stmt|;
name|node_list
operator|=
name|node_list
operator|->
name|next
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_src (GtkWidget * widget,gint row,gint column,GdkEventButton * event,gpointer data)
name|select_src
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|cdd
operator|->
name|src_row
operator|=
name|row
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|cdd
operator|->
name|buttons
index|[
name|BUTTON_ADD
index|]
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|unselect_src (GtkWidget * widget,gint row,gint column,GdkEventButton * event,gpointer data)
name|unselect_src
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|cdd
operator|->
name|src_row
operator|=
operator|-
literal|1
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|cdd
operator|->
name|buttons
index|[
name|BUTTON_ADD
index|]
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_dest (GtkWidget * widget,gint row,gint column,GdkEventButton * event,gpointer data)
name|select_dest
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|cdd
operator|->
name|dest_row
operator|=
name|row
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|cdd
operator|->
name|buttons
index|[
name|BUTTON_REMOVE
index|]
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|cdd
operator|->
name|buttons
index|[
name|BUTTON_CONFIGURE
index|]
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_display_update_up_and_down
argument_list|(
name|cdd
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|unselect_dest (GtkWidget * widget,gint row,gint column,GdkEventButton * event,gpointer data)
name|unselect_dest
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorDisplayDialog
modifier|*
name|cdd
init|=
name|data
decl_stmt|;
name|cdd
operator|->
name|dest_row
operator|=
operator|-
literal|1
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|cdd
operator|->
name|buttons
index|[
name|BUTTON_REMOVE
index|]
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|cdd
operator|->
name|buttons
index|[
name|BUTTON_CONFIGURE
index|]
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|color_display_update_up_and_down
argument_list|(
name|cdd
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

