begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1998 Andy Thomas.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURIGHTE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"context_manager.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gradient_editor.h"
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
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gradient_select_change_callbacks
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
name|gradient_select_gradient_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpGradient
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
name|gradient_select_edit_gradient
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

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

begin_comment
comment|/*  the main gradient editor dialog  */
end_comment

begin_decl_stmt
DECL|variable|gradient_editor_dialog
specifier|static
name|GradientEditor
modifier|*
name|gradient_editor_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

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
name|GimpGradient
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
name|g_new0
argument_list|(
name|GradientSelect
argument_list|,
literal|1
argument_list|)
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
name|title
condition|?
name|GTK_WIN_POS_MOUSE
else|:
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|"_delete_event_"
argument_list|,
name|gradient_select_close_callback
argument_list|,
name|gsp
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
name|gtk_widget_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|g_list_nth_data
argument_list|(
name|gtk_container_children
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
argument_list|)
argument_list|,
literal|0
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_DIALOG
argument_list|(
name|gsp
operator|->
name|shell
argument_list|)
operator|->
name|action_area
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
name|gimp_data_factory_data_init
argument_list|(
name|global_gradient_factory
argument_list|,
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
operator|(
name|GimpGradient
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|global_gradient_factory
operator|->
name|container
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
name|active
operator|=
name|gimp_context_get_gradient
argument_list|(
name|gimp_context_get_standard
argument_list|()
argument_list|)
expr_stmt|;
if|if
condition|(
name|title
condition|)
name|gimp_context_set_gradient
argument_list|(
name|gsp
operator|->
name|context
argument_list|,
name|active
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
comment|/*  The Gradient List  */
name|gsp
operator|->
name|view
operator|=
name|gimp_data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|global_gradient_factory
argument_list|,
name|gradient_select_edit_gradient
argument_list|,
name|gsp
operator|->
name|context
argument_list|,
literal|16
argument_list|,
literal|10
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
name|gsp
operator|->
name|view
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
name|gsp
operator|->
name|view
argument_list|)
expr_stmt|;
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
operator|(
name|gpointer
operator|)
name|gsp
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

begin_function
specifier|static
name|void
DECL|function|gradient_select_change_callbacks (GradientSelect * gsp,gboolean closing)
name|gradient_select_change_callbacks
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
name|GimpGradient
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
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|i
operator|=
name|gsp
operator|->
name|sample_size
expr_stmt|;
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
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|pos
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|r
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|g
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|b
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
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
name|GIMP_OBJECT
argument_list|(
name|gradient
argument_list|)
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
DECL|function|gradient_select_dialogs_check (void)
name|gradient_select_dialogs_check
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
specifier|static
name|void
DECL|function|gradient_select_gradient_changed (GimpContext * context,GimpGradient * gradient,GradientSelect * gsp)
name|gradient_select_gradient_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpGradient
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
block|{
if|if
condition|(
name|gsp
operator|->
name|callback_name
condition|)
name|gradient_select_change_callbacks
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
name|gradient_select_change_callbacks
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

begin_function
specifier|static
name|void
DECL|function|gradient_select_edit_gradient (GimpData * data)
name|gradient_select_edit_gradient
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|gradient
operator|=
name|GIMP_GRADIENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gradient_editor_dialog
condition|)
block|{
name|gradient_editor_dialog
operator|=
name|gradient_editor_new
argument_list|()
expr_stmt|;
block|}
name|gradient_editor_set_gradient
argument_list|(
name|gradient_editor_dialog
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

