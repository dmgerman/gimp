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
file|<stdlib.h>
end_include

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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"actionarea.h"
end_include

begin_include
include|#
directive|include
file|"buildmenu.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"color_area.h"
end_include

begin_include
include|#
directive|include
file|"color_select.h"
end_include

begin_include
include|#
directive|include
file|"datafiles.h"
end_include

begin_include
include|#
directive|include
file|"devices.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gradient_header.h"
end_include

begin_include
include|#
directive|include
file|"gradient.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_include
include|#
directive|include
file|"palette_entries.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"palette_select.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

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
DECL|variable|active_dialogs
comment|/* List of active dialogs */
end_comment

begin_function_decl
specifier|static
name|void
name|palette_select_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
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
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|action_items
specifier|static
name|ActionAreaItem
name|action_items
index|[
literal|2
index|]
init|=
block|{
block|{
name|N_
argument_list|(
literal|"Close"
argument_list|)
block|,
name|palette_select_close_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Edit"
argument_list|)
block|,
name|palette_select_edit_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|palette_select_set_text_all (PaletteEntriesP entries)
name|palette_select_set_text_all
parameter_list|(
name|PaletteEntriesP
name|entries
parameter_list|)
block|{
name|gint
name|pos
init|=
literal|0
decl_stmt|;
name|char
modifier|*
name|num_buf
decl_stmt|;
name|GSList
modifier|*
name|aclist
init|=
name|active_dialogs
decl_stmt|;
name|GSList
modifier|*
name|plist
decl_stmt|;
name|PaletteSelectP
name|psp
decl_stmt|;
name|PaletteEntriesP
name|p_entries
init|=
name|NULL
decl_stmt|;
name|plist
operator|=
name|palette_entries_list
expr_stmt|;
while|while
condition|(
name|plist
condition|)
block|{
name|p_entries
operator|=
operator|(
name|PaletteEntriesP
operator|)
name|plist
operator|->
name|data
expr_stmt|;
name|plist
operator|=
name|g_slist_next
argument_list|(
name|plist
argument_list|)
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
comment|/* This is actually and error */
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
while|while
condition|(
name|aclist
condition|)
block|{
name|char
modifier|*
name|num_copy
init|=
name|g_strdup
argument_list|(
name|num_buf
argument_list|)
decl_stmt|;
name|psp
operator|=
operator|(
name|PaletteSelectP
operator|)
name|aclist
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
name|num_copy
argument_list|)
expr_stmt|;
name|aclist
operator|=
name|g_slist_next
argument_list|(
name|aclist
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|palette_select_refresh_all ()
name|palette_select_refresh_all
parameter_list|()
block|{
name|GSList
modifier|*
name|list
init|=
name|active_dialogs
decl_stmt|;
name|PaletteSelectP
name|psp
decl_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|psp
operator|=
operator|(
name|PaletteSelectP
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
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|palette_select_clist_insert_all (PaletteEntriesP p_entries)
name|palette_select_clist_insert_all
parameter_list|(
name|PaletteEntriesP
name|p_entries
parameter_list|)
block|{
name|GSList
modifier|*
name|aclist
init|=
name|active_dialogs
decl_stmt|;
name|PaletteEntriesP
name|chk_entries
decl_stmt|;
name|PaletteSelectP
name|psp
decl_stmt|;
name|GSList
modifier|*
name|plist
decl_stmt|;
name|gint
name|pos
init|=
literal|0
decl_stmt|;
name|plist
operator|=
name|palette_entries_list
expr_stmt|;
while|while
condition|(
name|plist
condition|)
block|{
name|chk_entries
operator|=
operator|(
name|PaletteEntriesP
operator|)
name|plist
operator|->
name|data
expr_stmt|;
name|plist
operator|=
name|g_slist_next
argument_list|(
name|plist
argument_list|)
expr_stmt|;
comment|/*  to make sure we get something!  */
if|if
condition|(
name|chk_entries
operator|==
name|NULL
condition|)
block|{
return|return;
block|}
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
while|while
condition|(
name|aclist
condition|)
block|{
name|psp
operator|=
operator|(
name|PaletteSelectP
operator|)
name|aclist
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
name|palette_insert_clist
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
name|aclist
operator|=
name|g_slist_next
argument_list|(
name|aclist
argument_list|)
expr_stmt|;
block|}
comment|/*   if(gradient_select_dialog) */
comment|/*     { */
comment|/*       gtk_clist_set_text(GTK_CLIST(gradient_select_dialog->clist),n,1,grad->name);   */
comment|/*     } */
block|}
end_function

begin_function
name|void
DECL|function|palette_select_free (PaletteSelectP psp)
name|palette_select_free
parameter_list|(
name|PaletteSelectP
name|psp
parameter_list|)
block|{
if|if
condition|(
name|psp
condition|)
block|{
comment|/*       if(psp->callback_name) */
comment|/* 	g_free(gsp->callback_name); */
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
DECL|function|palette_select_edit_callback (GtkWidget * w,gpointer client_data)
name|palette_select_edit_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|PaletteEntriesP
name|p_entries
init|=
name|NULL
decl_stmt|;
name|PaletteSelectP
name|psp
init|=
operator|(
name|PaletteSelectP
operator|)
name|client_data
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
if|if
condition|(
name|sel_list
condition|)
block|{
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
name|PaletteEntriesP
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|palette_select_close_callback (GtkWidget * w,gpointer client_data)
name|palette_select_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|PaletteSelectP
name|psp
decl_stmt|;
name|psp
operator|=
operator|(
name|PaletteSelectP
operator|)
name|client_data
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
comment|/* Free memory if poping down dialog which is not the main one */
comment|/*   if(gsp != gradient_select_dialog) */
comment|/*     { */
comment|/*       grad_change_callbacks(gsp,1); */
comment|/*       gtk_widget_destroy(gsp->shell);  */
comment|/*       grad_select_free(gsp);  */
comment|/*     } */
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|palette_select_delete_callback (GtkWidget * w,GdkEvent * e,gpointer client_data)
name|palette_select_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|GdkEvent
modifier|*
name|e
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|palette_select_close_callback
argument_list|(
name|w
argument_list|,
name|client_data
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|PaletteSelectP
DECL|function|palette_new_selection (gchar * title,gchar * initial_palette)
name|palette_new_selection
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
name|PaletteSelectP
name|psp
decl_stmt|;
comment|/*   gradient_t *grad = NULL; */
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
name|PaletteEntriesP
name|p_entries
init|=
name|NULL
decl_stmt|;
name|int
name|select_pos
decl_stmt|;
name|palette_select_palette_init
argument_list|()
expr_stmt|;
name|psp
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|_PaletteSelect
argument_list|)
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
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
argument_list|,
literal|"paletteselection"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
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
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
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
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* handle the wm close event */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|palette_select_delete_callback
argument_list|)
argument_list|,
name|psp
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
name|psp
operator|->
name|clist
operator|=
name|gtk_clist_new
argument_list|(
literal|3
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
name|gtk_clist_set_column_title
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
name|_
argument_list|(
literal|"Palette"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_title
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Ncols"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_title
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"Name"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_clist_column_titles_show
argument_list|(
name|GTK_CLIST
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
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
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|0
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
name|gtk_widget_show
argument_list|(
name|scrolled_win
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|psp
operator|->
name|clist
argument_list|)
expr_stmt|;
comment|/*   gtk_signal_connect(GTK_OBJECT(gsp->clist), "select_row", */
comment|/* 		     GTK_SIGNAL_FUNC(sel_list_item_update), */
comment|/* 		     (gpointer) gsp); */
name|action_items
index|[
literal|0
index|]
operator|.
name|user_data
operator|=
name|psp
expr_stmt|;
name|action_items
index|[
literal|1
index|]
operator|.
name|user_data
operator|=
name|psp
expr_stmt|;
name|build_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
argument_list|,
name|action_items
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|title
condition|)
block|{
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Palette Selection"
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
block|}
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
name|list
operator|=
name|palette_entries_list
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|p_entries
operator|=
operator|(
name|PaletteEntriesP
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
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

end_unit

