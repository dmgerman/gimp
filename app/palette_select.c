begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1998 Andy Thomas (alt@picnic.demon.co.uk)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"palette_entries.h"
end_include

begin_include
include|#
directive|include
file|"palette_select.h"
end_include

begin_include
include|#
directive|include
file|"paletteP.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  List of active dialogs  */
end_comment

begin_decl_stmt
DECL|variable|active_dialogs
specifier|static
name|GSList
modifier|*
name|active_dialogs
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gint
name|palette_select_button_press
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|palette_select_close_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|palette_select_edit_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|PaletteSelect
modifier|*
DECL|function|palette_select_new (gchar * title,gchar * initial_palette)
name|palette_select_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
name|initial_palette
parameter_list|)
block|{
name|PaletteEntries
modifier|*
name|p_entries
init|=
name|NULL
decl_stmt|;
name|PaletteSelect
modifier|*
name|psp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|;
name|gchar
modifier|*
name|titles
index|[
literal|3
index|]
decl_stmt|;
name|gint
name|select_pos
decl_stmt|;
name|palette_select_palette_init
argument_list|()
expr_stmt|;
name|psp
operator|=
name|g_new
argument_list|(
name|PaletteSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|psp
operator|->
name|callback_name
operator|=
name|NULL
expr_stmt|;
comment|/*  The shell and main vbox  */
name|psp
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|title
condition|?
name|title
else|:
name|_
argument_list|(
literal|"Palette Selection"
argument_list|)
argument_list|,
literal|"palette_selection"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/palette_selection.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Edit"
argument_list|)
argument_list|,
name|palette_select_edit_callback
argument_list|,
name|psp
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Close"
argument_list|)
argument_list|,
name|palette_select_close_callback
argument_list|,
name|psp
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|8
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
comment|/* clist preview of gradients */
name|scrolled_win
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
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
name|GTK_POLICY_ALWAYS
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
name|gtk_widget_show
argument_list|(
name|scrolled_win
argument_list|)
expr_stmt|;
name|titles
index|[
literal|0
index|]
operator|=
name|_
argument_list|(
literal|"Palette"
argument_list|)
expr_stmt|;
name|titles
index|[
literal|1
index|]
operator|=
name|_
argument_list|(
literal|"Ncols"
argument_list|)
expr_stmt|;
name|titles
index|[
literal|2
index|]
operator|=
name|_
argument_list|(
literal|"Name"
argument_list|)
expr_stmt|;
name|psp
operator|->
name|clist
operator|=
name|gtk_clist_new_with_titles
argument_list|(
literal|3
argument_list|,
name|titles
argument_list|)
expr_stmt|;
name|gtk_clist_set_shadow_type
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_clist_set_row_height
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
name|SM_PREVIEW_HEIGHT
operator|+
literal|2
argument_list|)
expr_stmt|;
name|gtk_clist_set_use_drag_icons
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_clist_column_titles_passive
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|psp
operator|->
name|clist
argument_list|,
literal|203
argument_list|,
literal|200
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_width
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
literal|0
argument_list|,
name|SM_PREVIEW_WIDTH
operator|+
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|psp
operator|->
name|clist
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
expr_stmt|;
name|select_pos
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|initial_palette
operator|&&
name|strlen
argument_list|(
name|initial_palette
argument_list|)
condition|)
block|{
for|for
control|(
name|list
operator|=
name|palette_entries_list
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|p_entries
operator|=
operator|(
name|PaletteEntries
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|p_entries
operator|->
name|name
argument_list|,
name|initial_palette
argument_list|)
operator|>
literal|0
condition|)
break|break;
name|select_pos
operator|++
expr_stmt|;
block|}
block|}
name|gtk_widget_realize
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|psp
operator|->
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|psp
operator|->
name|shell
operator|->
name|window
argument_list|)
expr_stmt|;
name|palette_clist_init
argument_list|(
name|psp
operator|->
name|clist
argument_list|,
name|psp
operator|->
name|shell
argument_list|,
name|psp
operator|->
name|gc
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|palette_select_button_press
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|psp
argument_list|)
expr_stmt|;
comment|/* Now show the dialog */
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|select_pos
operator|!=
operator|-
literal|1
condition|)
block|{
name|gtk_clist_select_row
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
name|select_pos
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_clist_moveto
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
name|select_pos
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
else|else
name|gtk_clist_select_row
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|active_dialogs
operator|=
name|g_slist_append
argument_list|(
name|active_dialogs
argument_list|,
name|psp
argument_list|)
expr_stmt|;
return|return
name|psp
return|;
block|}
end_function

begin_function
name|void
DECL|function|palette_select_clist_insert_all (PaletteEntries * p_entries)
name|palette_select_clist_insert_all
parameter_list|(
name|PaletteEntries
modifier|*
name|p_entries
parameter_list|)
block|{
name|PaletteEntries
modifier|*
name|chk_entries
decl_stmt|;
name|PaletteSelect
modifier|*
name|psp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gint
name|pos
init|=
literal|0
decl_stmt|;
for|for
control|(
name|list
operator|=
name|palette_entries_list
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|chk_entries
operator|=
operator|(
name|PaletteEntries
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
comment|/*  to make sure we get something!  */
if|if
condition|(
name|chk_entries
operator|==
name|NULL
condition|)
return|return;
if|if
condition|(
name|strcmp
argument_list|(
name|p_entries
operator|->
name|name
argument_list|,
name|chk_entries
operator|->
name|name
argument_list|)
operator|==
literal|0
condition|)
break|break;
name|pos
operator|++
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|active_dialogs
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|psp
operator|=
operator|(
name|PaletteSelect
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gtk_clist_freeze
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
name|palette_clist_insert
argument_list|(
name|psp
operator|->
name|clist
argument_list|,
name|psp
operator|->
name|shell
argument_list|,
name|psp
operator|->
name|gc
argument_list|,
name|p_entries
argument_list|,
name|pos
argument_list|)
expr_stmt|;
name|gtk_clist_thaw
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|palette_select_set_text_all (PaletteEntries * entries)
name|palette_select_set_text_all
parameter_list|(
name|PaletteEntries
modifier|*
name|entries
parameter_list|)
block|{
name|PaletteEntries
modifier|*
name|p_entries
init|=
name|NULL
decl_stmt|;
name|PaletteSelect
modifier|*
name|psp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|num_buf
decl_stmt|;
name|gint
name|pos
init|=
literal|0
decl_stmt|;
for|for
control|(
name|list
operator|=
name|palette_entries_list
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|p_entries
operator|=
operator|(
name|PaletteEntries
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|p_entries
operator|==
name|entries
condition|)
break|break;
name|pos
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|p_entries
operator|==
name|NULL
condition|)
return|return;
comment|/* This is actually an error */
name|num_buf
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|p_entries
operator|->
name|n_colors
argument_list|)
expr_stmt|;
empty_stmt|;
for|for
control|(
name|list
operator|=
name|active_dialogs
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|psp
operator|=
operator|(
name|PaletteSelect
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gtk_clist_set_text
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
name|pos
argument_list|,
literal|1
argument_list|,
name|num_buf
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|num_buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palette_select_refresh_all ()
name|palette_select_refresh_all
parameter_list|()
block|{
name|PaletteSelect
modifier|*
name|psp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|active_dialogs
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|psp
operator|=
operator|(
name|PaletteSelect
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gtk_clist_freeze
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_clist_clear
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
name|palette_clist_init
argument_list|(
name|psp
operator|->
name|clist
argument_list|,
name|psp
operator|->
name|shell
argument_list|,
name|psp
operator|->
name|gc
argument_list|)
expr_stmt|;
name|gtk_clist_thaw
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  local functions  */
end_comment

begin_function
specifier|static
name|gint
DECL|function|palette_select_button_press (GtkWidget * widget,GdkEventButton * bevent,gpointer data)
name|palette_select_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PaletteSelect
modifier|*
name|psp
decl_stmt|;
name|psp
operator|=
operator|(
name|PaletteSelect
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
operator|&&
name|bevent
operator|->
name|type
operator|==
name|GDK_2BUTTON_PRESS
condition|)
block|{
name|palette_select_edit_callback
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|palette_select_edit_callback (GtkWidget * widget,gpointer data)
name|palette_select_edit_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PaletteEntries
modifier|*
name|p_entries
init|=
name|NULL
decl_stmt|;
name|PaletteSelect
modifier|*
name|psp
init|=
operator|(
name|PaletteSelect
operator|*
operator|)
name|data
decl_stmt|;
name|GList
modifier|*
name|sel_list
decl_stmt|;
name|sel_list
operator|=
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
operator|->
name|selection
expr_stmt|;
while|while
condition|(
name|sel_list
condition|)
block|{
name|gint
name|row
decl_stmt|;
name|row
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|sel_list
operator|->
name|data
argument_list|)
expr_stmt|;
name|p_entries
operator|=
operator|(
name|PaletteEntries
operator|*
operator|)
name|gtk_clist_get_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|palette_create_edit
argument_list|(
name|p_entries
argument_list|)
expr_stmt|;
comment|/* One only */
return|return;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|palette_select_free (PaletteSelect * psp)
name|palette_select_free
parameter_list|(
name|PaletteSelect
modifier|*
name|psp
parameter_list|)
block|{
if|if
condition|(
name|psp
condition|)
block|{
comment|/*       if(psp->callback_name) 	g_free (gsp->callback_name);       */
comment|/* remove from active list */
name|active_dialogs
operator|=
name|g_slist_remove
argument_list|(
name|active_dialogs
argument_list|,
name|psp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|psp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|palette_select_close_callback (GtkWidget * widget,gpointer data)
name|palette_select_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PaletteSelect
modifier|*
name|psp
decl_stmt|;
name|psp
operator|=
operator|(
name|PaletteSelect
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|palette_select_free
argument_list|(
name|psp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

