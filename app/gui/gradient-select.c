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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerbox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"menus/menus.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-constructors.h"
end_include

begin_include
include|#
directive|include
file|"gradient-select.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

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
name|gradient_select_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GradientSelect
modifier|*
name|gsp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  list of active dialogs   */
end_comment

begin_decl_stmt
DECL|variable|gradient_active_dialogs
specifier|static
name|GSList
modifier|*
name|gradient_active_dialogs
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GradientSelect
modifier|*
DECL|function|gradient_select_new (Gimp * gimp,GimpContext * context,const gchar * title,const gchar * initial_gradient,const gchar * callback_name,gint sample_size)
name|gradient_select_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|initial_gradient
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
name|gint
name|sample_size
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gsp
decl_stmt|;
name|GimpGradient
modifier|*
name|active
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|no_data
condition|)
block|{
specifier|static
name|gboolean
name|first_call
init|=
name|TRUE
decl_stmt|;
if|if
condition|(
name|first_call
condition|)
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|first_call
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
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
name|gimp
operator|->
name|gradient_factory
operator|->
name|container
argument_list|,
name|initial_gradient
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
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|active
condition|)
return|return
name|NULL
return|;
name|gsp
operator|=
name|g_new0
argument_list|(
name|GradientSelect
argument_list|,
literal|1
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
name|gsp
operator|->
name|context
operator|=
name|gimp_context_new
argument_list|(
name|gimp
argument_list|,
name|title
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gsp
operator|->
name|callback_name
operator|=
name|g_strdup
argument_list|(
name|callback_name
argument_list|)
expr_stmt|;
name|gsp
operator|->
name|sample_size
operator|=
name|sample_size
expr_stmt|;
name|gimp_context_set_gradient
argument_list|(
name|gsp
operator|->
name|context
argument_list|,
name|active
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gsp
operator|->
name|context
argument_list|,
literal|"gradient_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gradient_select_gradient_changed
argument_list|)
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
comment|/*  the shell  */
name|gsp
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|title
argument_list|,
literal|"gradient_selection"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_GRADIENT_DIALOG
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gsp
operator|->
name|shell
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gradient_select_response
argument_list|)
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
comment|/*  the gradient list  */
name|gsp
operator|->
name|view
operator|=
name|gimp_data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|gimp
operator|->
name|gradient_factory
argument_list|,
name|dialogs_edit_gradient_func
argument_list|,
name|gsp
operator|->
name|context
argument_list|,
name|GIMP_PREVIEW_SIZE_MEDIUM
argument_list|,
literal|1
argument_list|,
name|global_menu_factory
argument_list|,
literal|"<Gradients>"
argument_list|,
literal|"/gradients-popup"
argument_list|)
expr_stmt|;
name|gimp_container_box_set_size_request
argument_list|(
name|GIMP_CONTAINER_BOX
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|gsp
operator|->
name|view
argument_list|)
operator|->
name|view
argument_list|)
argument_list|,
literal|6
operator|*
operator|(
name|GIMP_PREVIEW_SIZE_MEDIUM
operator|+
literal|2
operator|)
argument_list|,
literal|6
operator|*
operator|(
name|GIMP_PREVIEW_SIZE_MEDIUM
operator|+
literal|2
operator|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|gsp
operator|->
name|view
argument_list|)
argument_list|,
literal|6
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
name|gsp
operator|->
name|view
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
name|gsp
operator|->
name|shell
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
name|g_return_if_fail
argument_list|(
name|gsp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|gsp
operator|->
name|shell
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|gsp
operator|->
name|callback_name
condition|)
name|g_free
argument_list|(
name|gsp
operator|->
name|callback_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gsp
operator|->
name|context
condition|)
name|g_object_unref
argument_list|(
name|gsp
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gsp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GradientSelect
modifier|*
DECL|function|gradient_select_get_by_callback (const gchar * callback_name)
name|gradient_select_get_by_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|callback_name
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
if|if
condition|(
name|gsp
operator|->
name|callback_name
operator|&&
operator|!
name|strcmp
argument_list|(
name|callback_name
argument_list|,
name|gsp
operator|->
name|callback_name
argument_list|)
condition|)
return|return
name|gsp
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

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
if|if
condition|(
name|gsp
operator|->
name|callback_name
condition|)
block|{
if|if
condition|(
operator|!
name|procedural_db_lookup
argument_list|(
name|gsp
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|gsp
operator|->
name|callback_name
argument_list|)
condition|)
name|gradient_select_response
argument_list|(
name|NULL
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|gsp
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

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
name|ProcRecord
modifier|*
name|proc
init|=
name|NULL
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
specifier|static
name|gboolean
name|busy
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gsp
operator|&&
name|gsp
operator|->
name|callback_name
operator|)
operator|||
name|busy
condition|)
return|return;
name|busy
operator|=
name|TRUE
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
name|proc
operator|=
name|procedural_db_lookup
argument_list|(
name|gsp
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|gsp
operator|->
name|callback_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc
operator|&&
name|gradient
condition|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
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
name|FALSE
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
name|gsp
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|gsp
operator|->
name|context
argument_list|,
name|gsp
operator|->
name|callback_name
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|gradient
argument_list|)
operator|->
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|gsp
operator|->
name|sample_size
operator|*
literal|4
argument_list|,
name|GIMP_PDB_FLOATARRAY
argument_list|,
name|values
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
operator|(
name|gint
operator|)
name|closing
argument_list|,
name|GIMP_PDB_END
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
name|GIMP_PDB_SUCCESS
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unable to run gradient callback. "
literal|"The corresponding plug-in may have crashed."
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
condition|)
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
name|gradient_select_change_callbacks
argument_list|(
name|gsp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_select_response (GtkWidget * widget,gint response_id,GradientSelect * gsp)
name|gradient_select_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GradientSelect
modifier|*
name|gsp
parameter_list|)
block|{
name|gradient_select_change_callbacks
argument_list|(
name|gsp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gradient_select_free
argument_list|(
name|gsp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

