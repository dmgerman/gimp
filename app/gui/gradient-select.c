begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1998 Andy Thomas.  *  * Gradient editor module copyight (C) 1996-1997 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURIGHTE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* This is the popup for the gradient selection stuff..  * idea is a cut down version of the gradient selection widget   * just a clist on which each gradient can be selected.   * Of course all the support functions for getting the slected gradient and  * setting the slection all need to be done as well.  */
end_comment

begin_comment
comment|/* Main structure for the dialog. There can be multiple of these   * so every thing has to go into the strcuture and we have to have a list   * the structures so we can find which one we are taking about.  */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"gradient_header.h"
end_include

begin_include
include|#
directive|include
file|"gradientP.h"
end_include

begin_include
include|#
directive|include
file|"gradient_select.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gradient_change_callbacks
parameter_list|(
name|GradientSelect
modifier|*
name|gsp
parameter_list|,
name|gboolean
name|closing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gradient_select_drop_gradient
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gradient_select_gradient_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|,
name|GradientSelect
modifier|*
name|gsp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gradient_select_select
parameter_list|(
name|GradientSelect
modifier|*
name|gsp
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gradient_select_list_item_update
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
name|gradient_select_close_callback
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
name|gradient_select_edit_callback
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

begin_comment
comment|/*  dnd stuff  */
end_comment

begin_decl_stmt
DECL|variable|clist_target_table
specifier|static
name|GtkTargetEntry
name|clist_target_table
index|[]
init|=
block|{
name|GIMP_TARGET_GRADIENT
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|clist_n_targets
specifier|static
name|guint
name|clist_n_targets
init|=
operator|(
sizeof|sizeof
argument_list|(
name|clist_target_table
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|clist_target_table
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  list of active dialogs   */
end_comment

begin_decl_stmt
DECL|variable|gradient_active_dialogs
name|GSList
modifier|*
name|gradient_active_dialogs
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  the main gradient selection dialog  */
end_comment

begin_decl_stmt
DECL|variable|gradient_select_dialog
name|GradientSelect
modifier|*
name|gradient_select_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gradient_dialog_create (void)
name|gradient_dialog_create
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gradient_select_dialog
condition|)
block|{
name|gradient_select_dialog
operator|=
name|gradient_select_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|gradient_select_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|gradient_select_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
else|else
name|gdk_window_raise
argument_list|(
name|gradient_select_dialog
operator|->
name|shell
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gradient_dialog_free (void)
name|gradient_dialog_free
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|gradient_select_dialog
condition|)
block|{
name|session_get_window_info
argument_list|(
name|gradient_select_dialog
operator|->
name|shell
argument_list|,
operator|&
name|gradient_select_session_info
argument_list|)
expr_stmt|;
name|gradient_select_free
argument_list|(
name|gradient_select_dialog
argument_list|)
expr_stmt|;
name|gradient_select_dialog
operator|=
name|NULL
expr_stmt|;
block|}
name|gradient_editor_free
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  If title == NULL then it is the main gradient select dialog  */
end_comment

begin_function
name|GradientSelect
modifier|*
DECL|function|gradient_select_new (gchar * title,gchar * initial_gradient)
name|gradient_select_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
name|initial_gradient
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|;
name|GdkColormap
modifier|*
name|colormap
decl_stmt|;
name|gint
name|select_pos
decl_stmt|;
name|gradient_t
modifier|*
name|active
init|=
name|NULL
decl_stmt|;
specifier|static
name|gboolean
name|first_call
init|=
name|TRUE
decl_stmt|;
name|gsp
operator|=
name|g_new
argument_list|(
name|GradientSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gsp
operator|->
name|callback_name
operator|=
name|NULL
expr_stmt|;
comment|/*  The shell  */
name|gsp
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
literal|"Gradient Selection"
argument_list|)
argument_list|,
literal|"gradient_selection"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/gradient_selection.html"
argument_list|,
name|GTK_WIN_POS_NONE
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
name|gradient_select_edit_callback
argument_list|,
name|gsp
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Close"
argument_list|)
argument_list|,
name|gradient_select_close_callback
argument_list|,
name|gsp
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|title
condition|)
block|{
name|gsp
operator|->
name|context
operator|=
name|gimp_context_new
argument_list|(
name|title
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gsp
operator|->
name|context
operator|=
name|gimp_context_get_user
argument_list|()
expr_stmt|;
name|session_set_window_geometry
argument_list|(
name|gsp
operator|->
name|shell
argument_list|,
operator|&
name|gradient_select_session_info
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dialog_register
argument_list|(
name|gsp
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|no_data
operator|&&
name|first_call
condition|)
name|gradients_init
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
name|first_call
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|title
operator|&&
name|initial_gradient
operator|&&
name|strlen
argument_list|(
name|initial_gradient
argument_list|)
condition|)
block|{
name|active
operator|=
name|gradient_list_get_gradient
argument_list|(
name|gradients_list
argument_list|,
name|initial_gradient
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active
operator|=
name|gimp_context_get_gradient
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|active
condition|)
block|{
name|active
operator|=
name|gimp_context_get_gradient
argument_list|(
name|gimp_context_get_standard
argument_list|()
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|title
condition|)
block|{
name|gimp_context_set_gradient
argument_list|(
name|gsp
operator|->
name|context
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|gsp
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
comment|/*  clist preview of gradients  */
name|scrolled_win
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gsp
operator|->
name|clist
operator|=
name|gtk_clist_new
argument_list|(
literal|2
argument_list|)
expr_stmt|;
name|gtk_clist_set_shadow_type
argument_list|(
name|GTK_CLIST
argument_list|(
name|gsp
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
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
literal|18
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_width
argument_list|(
name|GTK_CLIST
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|52
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_title
argument_list|(
name|GTK_CLIST
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Gradient"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_title
argument_list|(
name|GTK_CLIST
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
literal|1
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
name|gsp
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  dnd stuff  */
name|gtk_drag_dest_set
argument_list|(
name|gsp
operator|->
name|clist
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|clist_target_table
argument_list|,
name|clist_n_targets
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_gradient_dest_set
argument_list|(
name|gsp
operator|->
name|clist
argument_list|,
name|gradient_select_drop_gradient
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|scrolled_win
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|gsp
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
name|gsp
operator|->
name|clist
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|gsp
operator|->
name|clist
argument_list|,
literal|200
argument_list|,
literal|250
argument_list|)
expr_stmt|;
name|colormap
operator|=
name|gtk_widget_get_colormap
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
expr_stmt|;
name|gdk_color_parse
argument_list|(
literal|"black"
argument_list|,
operator|&
name|gsp
operator|->
name|black
argument_list|)
expr_stmt|;
name|gdk_color_alloc
argument_list|(
name|colormap
argument_list|,
operator|&
name|gsp
operator|->
name|black
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|gsp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gsp
operator|->
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|gsp
operator|->
name|shell
operator|->
name|window
argument_list|)
expr_stmt|;
name|select_pos
operator|=
name|gradient_clist_init
argument_list|(
name|gsp
operator|->
name|shell
argument_list|,
name|gsp
operator|->
name|gc
argument_list|,
name|gsp
operator|->
name|clist
argument_list|,
name|active
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
name|gsp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
literal|"select_row"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gradient_select_list_item_update
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|gsp
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
argument_list|,
literal|"gradient_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gradient_select_gradient_changed
argument_list|)
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
condition|)
name|gradient_select_select
argument_list|(
name|gsp
argument_list|,
name|active
argument_list|)
expr_stmt|;
comment|/*  Add to active gradient dialogs list  */
name|gradient_active_dialogs
operator|=
name|g_slist_append
argument_list|(
name|gradient_active_dialogs
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
return|return
name|gsp
return|;
block|}
end_function

begin_function
name|void
DECL|function|gradient_select_free (GradientSelect * gsp)
name|gradient_select_free
parameter_list|(
name|GradientSelect
modifier|*
name|gsp
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gsp
condition|)
return|return;
comment|/* remove from active list */
name|gradient_active_dialogs
operator|=
name|g_slist_remove
argument_list|(
name|gradient_active_dialogs
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
name|gtk_signal_disconnect_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gsp
operator|->
name|callback_name
condition|)
block|{
name|g_free
argument_list|(
name|gsp
operator|->
name|callback_name
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|gsp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Call this dialog's PDB callback  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gradient_change_callbacks (GradientSelect * gsp,gboolean closing)
name|gradient_change_callbacks
parameter_list|(
name|GradientSelect
modifier|*
name|gsp
parameter_list|,
name|gboolean
name|closing
parameter_list|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|ProcRecord
modifier|*
name|prec
init|=
name|NULL
decl_stmt|;
name|gradient_t
modifier|*
name|gradient
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
specifier|static
name|gboolean
name|busy
init|=
name|FALSE
decl_stmt|;
comment|/* Any procs registered to callback? */
name|Argument
modifier|*
name|return_vals
decl_stmt|;
if|if
condition|(
operator|!
name|gsp
operator|||
operator|!
name|gsp
operator|->
name|callback_name
operator|||
name|busy
operator|!=
literal|0
condition|)
return|return;
name|busy
operator|=
name|TRUE
expr_stmt|;
name|name
operator|=
name|gsp
operator|->
name|callback_name
expr_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
expr_stmt|;
comment|/*  If its still registered run it  */
name|prec
operator|=
name|procedural_db_lookup
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|prec
operator|&&
name|gradient
condition|)
block|{
name|gdouble
modifier|*
name|values
decl_stmt|,
modifier|*
name|pv
decl_stmt|;
name|double
name|pos
decl_stmt|,
name|delta
decl_stmt|;
name|double
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
name|int
name|i
init|=
name|gsp
operator|->
name|sample_size
decl_stmt|;
name|pos
operator|=
literal|0.0
expr_stmt|;
name|delta
operator|=
literal|1.0
operator|/
operator|(
name|i
operator|-
literal|1
operator|)
expr_stmt|;
name|values
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
literal|4
operator|*
name|i
argument_list|)
expr_stmt|;
name|pv
operator|=
name|values
expr_stmt|;
while|while
condition|(
name|i
operator|--
condition|)
block|{
name|gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|pos
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|,
operator|&
name|a
argument_list|)
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|r
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|g
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|b
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|a
expr_stmt|;
name|pos
operator|+=
name|delta
expr_stmt|;
block|}
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
name|name
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PDB_STRING
argument_list|,
name|gradient
operator|->
name|name
argument_list|,
name|PDB_INT32
argument_list|,
name|gsp
operator|->
name|sample_size
operator|*
literal|4
argument_list|,
name|PDB_FLOATARRAY
argument_list|,
name|values
argument_list|,
name|PDB_INT32
argument_list|,
operator|(
name|gint
operator|)
name|closing
argument_list|,
name|PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|return_vals
operator|||
name|return_vals
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|!=
name|PDB_SUCCESS
condition|)
name|g_message
argument_list|(
literal|"failed to run gradient callback function"
argument_list|)
expr_stmt|;
else|else
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
name|busy
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Close active dialogs that no longer have PDB registered for them  */
end_comment

begin_function
name|void
DECL|function|gradients_check_dialogs (void)
name|gradients_check_dialogs
parameter_list|(
name|void
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|ProcRecord
modifier|*
name|prec
init|=
name|NULL
decl_stmt|;
name|list
operator|=
name|gradient_active_dialogs
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|gsp
operator|=
operator|(
name|GradientSelect
operator|*
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
name|name
operator|=
name|gsp
operator|->
name|callback_name
expr_stmt|;
if|if
condition|(
name|name
condition|)
block|{
name|prec
operator|=
name|procedural_db_lookup
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|prec
condition|)
block|{
comment|/*  Can alter gradient_active_dialogs list  */
name|gradient_select_close_callback
argument_list|(
name|NULL
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gradient_select_rename_all (gint n,gradient_t * gradient)
name|gradient_select_rename_all
parameter_list|(
name|gint
name|n
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gradient_active_dialogs
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
name|gsp
operator|=
operator|(
name|GradientSelect
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
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
name|n
argument_list|,
literal|1
argument_list|,
name|gradient
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gradient_select_insert_all (gint pos,gradient_t * gradient)
name|gradient_select_insert_all
parameter_list|(
name|gint
name|pos
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gradient_active_dialogs
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
name|gsp
operator|=
operator|(
name|GradientSelect
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
name|gsp
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
name|gradient_clist_insert
argument_list|(
name|gsp
operator|->
name|shell
argument_list|,
name|gsp
operator|->
name|gc
argument_list|,
name|gsp
operator|->
name|clist
argument_list|,
name|gradient
argument_list|,
name|pos
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_clist_thaw
argument_list|(
name|GTK_CLIST
argument_list|(
name|gsp
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
DECL|function|gradient_select_delete_all (gint n)
name|gradient_select_delete_all
parameter_list|(
name|gint
name|n
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gradient_active_dialogs
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
name|gsp
operator|=
operator|(
name|GradientSelect
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gtk_clist_remove
argument_list|(
name|GTK_CLIST
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
name|n
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gradient_select_free_all (void)
name|gradient_select_free_all
parameter_list|(
name|void
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gradient_active_dialogs
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
name|gsp
operator|=
operator|(
name|GradientSelect
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
name|gsp
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_clist_clear
argument_list|(
name|GTK_CLIST
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_clist_thaw
argument_list|(
name|GTK_CLIST
argument_list|(
name|gsp
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
DECL|function|gradient_select_refill_all (void)
name|gradient_select_refill_all
parameter_list|(
name|void
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gint
name|index
init|=
operator|-
literal|1
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gradient_active_dialogs
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
name|gsp
operator|=
operator|(
name|GradientSelect
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|index
operator|=
name|gradient_clist_init
argument_list|(
name|gsp
operator|->
name|shell
argument_list|,
name|gsp
operator|->
name|gc
argument_list|,
name|gsp
operator|->
name|clist
argument_list|,
name|gimp_context_get_gradient
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|!=
operator|-
literal|1
condition|)
name|gradient_select_select
argument_list|(
name|gsp
argument_list|,
name|gimp_context_get_gradient
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gradient_select_update_all (gint row,gradient_t * gradient)
name|gradient_select_update_all
parameter_list|(
name|gint
name|row
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gradient_active_dialogs
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
name|gsp
operator|=
operator|(
name|GradientSelect
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
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
name|row
argument_list|,
literal|1
argument_list|,
name|gradient
operator|->
name|name
argument_list|)
expr_stmt|;
comment|/*  Are we updating one that is selected in a popup dialog?  */
if|if
condition|(
operator|(
name|gradient
operator|==
name|gimp_context_get_gradient
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
operator|)
operator|&&
operator|(
name|gsp
operator|!=
name|gradient_select_dialog
operator|)
condition|)
name|gradient_change_callbacks
argument_list|(
name|gsp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  *  Local functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gradient_select_drop_gradient (GtkWidget * widget,gradient_t * gradient,gpointer data)
name|gradient_select_drop_gradient
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|gsp
operator|=
operator|(
name|GradientSelect
operator|*
operator|)
name|data
expr_stmt|;
name|gimp_context_set_gradient
argument_list|(
name|gsp
operator|->
name|context
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_select_gradient_changed (GimpContext * context,gradient_t * gradient,GradientSelect * gsp)
name|gradient_select_gradient_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|,
name|GradientSelect
modifier|*
name|gsp
parameter_list|)
block|{
if|if
condition|(
name|gradient
condition|)
name|gradient_select_select
argument_list|(
name|gsp
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_select_select (GradientSelect * gsp,gradient_t * gradient)
name|gradient_select_select
parameter_list|(
name|GradientSelect
modifier|*
name|gsp
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|)
block|{
name|gint
name|index
decl_stmt|;
name|index
operator|=
name|gradient_list_get_gradient_index
argument_list|(
name|gradients_list
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|!=
operator|-
literal|1
condition|)
block|{
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
name|gtk_clist_select_row
argument_list|(
name|GTK_CLIST
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
name|index
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_clist_moveto
argument_list|(
name|GTK_CLIST
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
name|index
argument_list|,
literal|0
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gsp
operator|->
name|clist
argument_list|)
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_select_list_item_update (GtkWidget * widget,gint row,gint column,GdkEventButton * event,gpointer data)
name|gradient_select_list_item_update
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
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gsp
operator|=
operator|(
name|GradientSelect
operator|*
operator|)
name|data
expr_stmt|;
name|list
operator|=
name|g_slist_nth
argument_list|(
name|gradients_list
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
name|gimp_context_set_gradient
argument_list|(
name|gsp
operator|->
name|context
argument_list|,
operator|(
name|gradient_t
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gsp
operator|!=
name|gradient_select_dialog
condition|)
block|{
name|gradient_change_callbacks
argument_list|(
name|gsp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_select_edit_callback (GtkWidget * widget,gpointer data)
name|gradient_select_edit_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|gsp
operator|=
operator|(
name|GradientSelect
operator|*
operator|)
name|data
expr_stmt|;
name|gradient_editor_create
argument_list|()
expr_stmt|;
if|if
condition|(
name|gsp
condition|)
name|gradient_editor_set_gradient
argument_list|(
name|gimp_context_get_gradient
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_select_close_callback (GtkWidget * widget,gpointer data)
name|gradient_select_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|gsp
operator|=
operator|(
name|GradientSelect
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|gsp
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|gsp
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/* Free memory if poping down dialog which is not the main one */
if|if
condition|(
name|gsp
operator|!=
name|gradient_select_dialog
condition|)
block|{
name|gradient_change_callbacks
argument_list|(
name|gsp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|gsp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gradient_select_free
argument_list|(
name|gsp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

