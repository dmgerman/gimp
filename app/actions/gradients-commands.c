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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient-save.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainereditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gradients-commands.h"
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
name|gradients_save_as_pov_ray_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gradients_save_as_pov_ray_cmd_callback (GtkAction * action,gpointer data)
name|gradients_save_as_pov_ray_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|GtkFileChooser
modifier|*
name|chooser
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gradient
condition|)
return|return;
name|title
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Save '%s' as POV-Ray"
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|gradient
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|chooser
operator|=
name|GTK_FILE_CHOOSER
argument_list|(
name|gtk_file_chooser_dialog_new
argument_list|(
name|title
argument_list|,
name|NULL
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_SAVE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
literal|"gimp-gradient-save-pov"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|chooser
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gradients_save_as_pov_ray_response
argument_list|)
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|chooser
argument_list|,
literal|"delete-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|chooser
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|g_object_unref
argument_list|)
argument_list|,
name|gradient
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|gimp_help_connect
argument_list|(
name|GTK_WIDGET
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_GRADIENT_SAVE_AS_POV
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|chooser
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gradients_save_as_pov_ray_response (GtkWidget * dialog,gint response_id,GimpGradient * gradient)
name|gradients_save_as_pov_ray_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|filename
operator|=
name|gtk_file_chooser_get_filename
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_gradient_save_pov
argument_list|(
name|gradient
argument_list|,
name|filename
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

