begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpdisplayconfig.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagedialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-close.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagewindow.h"
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
name|gimp_display_shell_close_dialog
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_close_name_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpMessageBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_close_exported
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpMessageBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_display_shell_close_time_changed
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_close_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|close
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_close_accel_marshal
parameter_list|(
name|GClosure
modifier|*
name|closure
parameter_list|,
name|GValue
modifier|*
name|return_value
parameter_list|,
name|guint
name|n_param_values
parameter_list|,
specifier|const
name|GValue
modifier|*
name|param_values
parameter_list|,
name|gpointer
name|invocation_hint
parameter_list|,
name|gpointer
name|marshal_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_time_since
parameter_list|(
name|gint64
name|then
parameter_list|,
name|gint
modifier|*
name|hours
parameter_list|,
name|gint
modifier|*
name|minutes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_close (GimpDisplayShell * shell,gboolean kill_it)
name|gimp_display_shell_close
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|kill_it
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
comment|/*  FIXME: gimp_busy HACK not really appropriate here because we only    *  want to prevent the busy image and display to be closed.  --Mitch    */
if|if
condition|(
name|shell
operator|->
name|display
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
comment|/*  If the image has been modified, give the user a chance to save    *  it before nuking it--this only applies if its the last view    *  to an image canvas.  (a image with disp_count = 1)    */
if|if
condition|(
operator|!
name|kill_it
operator|&&
name|image
operator|&&
name|gimp_image_get_display_count
argument_list|(
name|image
argument_list|)
operator|==
literal|1
operator|&&
name|gimp_image_is_dirty
argument_list|(
name|image
argument_list|)
condition|)
block|{
comment|/*  If there's a save dialog active for this image, then raise it.        *  (see bug #511965)        */
name|GtkWidget
modifier|*
name|dialog
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"gimp-file-save-dialog"
argument_list|)
decl_stmt|;
if|if
condition|(
name|dialog
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_display_shell_close_dialog
argument_list|(
name|shell
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|image
condition|)
block|{
name|gimp_display_close
argument_list|(
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpImageWindow
modifier|*
name|window
init|=
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
decl_stmt|;
if|if
condition|(
name|window
condition|)
block|{
name|GimpUIManager
modifier|*
name|manager
init|=
name|gimp_image_window_get_ui_manager
argument_list|(
name|window
argument_list|)
decl_stmt|;
comment|/* Activate the action instead of simply calling gimp_exit(), so            * the quit action's sensitivity is taken into account.            */
name|gimp_ui_manager_activate_action
argument_list|(
name|manager
argument_list|,
literal|"file"
argument_list|,
literal|"file-quit"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_define
DECL|macro|RESPONSE_SAVE
define|#
directive|define
name|RESPONSE_SAVE
value|1
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_close_dialog (GimpDisplayShell * shell,GimpImage * image)
name|gimp_display_shell_close_dialog
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GimpMessageBox
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkAccelGroup
modifier|*
name|accel_group
decl_stmt|;
name|GClosure
modifier|*
name|closure
decl_stmt|;
name|GSource
modifier|*
name|source
decl_stmt|;
name|guint
name|accel_key
decl_stmt|;
name|GdkModifierType
name|accel_mods
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|gchar
modifier|*
name|accel_string
decl_stmt|;
name|gchar
modifier|*
name|hint
decl_stmt|;
name|gchar
modifier|*
name|markup
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
if|if
condition|(
name|shell
operator|->
name|close_dialog
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|close_dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|file
operator|=
name|gimp_image_get_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|title
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Close %s"
argument_list|)
argument_list|,
name|gimp_image_get_display_name
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|close_dialog
operator|=
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|title
argument_list|,
name|GIMP_ICON_DOCUMENT_SAVE
argument_list|,
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|file
condition|?
name|_
argument_list|(
literal|"_Save"
argument_list|)
else|:
name|_
argument_list|(
literal|"Save _As"
argument_list|)
argument_list|,
name|RESPONSE_SAVE
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_Discard Changes"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|)
expr_stmt|;
name|gimp_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|RESPONSE_SAVE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|shell
operator|->
name|close_dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_close_response
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
comment|/* connect<Primary>D to the quit/close button */
name|accel_group
operator|=
name|gtk_accel_group_new
argument_list|()
expr_stmt|;
name|gtk_window_add_accel_group
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|close_dialog
argument_list|)
argument_list|,
name|accel_group
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|accel_group
argument_list|)
expr_stmt|;
name|closure
operator|=
name|g_closure_new_object
argument_list|(
sizeof|sizeof
argument_list|(
name|GClosure
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|close_dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_closure_set_marshal
argument_list|(
name|closure
argument_list|,
name|gimp_display_shell_close_accel_marshal
argument_list|)
expr_stmt|;
name|gtk_accelerator_parse
argument_list|(
literal|"<Primary>D"
argument_list|,
operator|&
name|accel_key
argument_list|,
operator|&
name|accel_mods
argument_list|)
expr_stmt|;
name|gtk_accel_group_connect
argument_list|(
name|accel_group
argument_list|,
name|accel_key
argument_list|,
name|accel_mods
argument_list|,
literal|0
argument_list|,
name|closure
argument_list|)
expr_stmt|;
name|box
operator|=
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
expr_stmt|;
name|accel_string
operator|=
name|gtk_accelerator_get_label
argument_list|(
name|accel_key
argument_list|,
name|accel_mods
argument_list|)
expr_stmt|;
name|hint
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Press %s to discard all changes and close the image."
argument_list|)
argument_list|,
name|accel_string
argument_list|)
expr_stmt|;
name|markup
operator|=
name|g_strdup_printf
argument_list|(
literal|"<i><small>%s</small></i>"
argument_list|,
name|hint
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_label_set_markup
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|markup
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
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
name|g_free
argument_list|(
name|markup
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|hint
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|accel_string
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|image
argument_list|,
literal|"name-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_close_name_changed
argument_list|)
argument_list|,
name|box
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|image
argument_list|,
literal|"exported"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_close_exported
argument_list|)
argument_list|,
name|box
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_display_shell_close_name_changed
argument_list|(
name|image
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|closure
operator|=
name|g_cclosure_new_object
argument_list|(
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_close_time_changed
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  update every 10 seconds  */
name|source
operator|=
name|g_timeout_source_new_seconds
argument_list|(
literal|10
argument_list|)
expr_stmt|;
name|g_source_set_closure
argument_list|(
name|source
argument_list|,
name|closure
argument_list|)
expr_stmt|;
name|g_source_attach
argument_list|(
name|source
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_source_unref
argument_list|(
name|source
argument_list|)
expr_stmt|;
comment|/*  The dialog is destroyed with the shell, so it should be safe    *  to hold an image pointer for the lifetime of the dialog.    */
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"gimp-image"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gimp_display_shell_close_time_changed
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_close_name_changed (GimpImage * image,GimpMessageBox * box)
name|gimp_display_shell_close_name_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpMessageBox
modifier|*
name|box
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|window
init|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_IS_WINDOW
argument_list|(
name|window
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|title
init|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Close %s"
argument_list|)
argument_list|,
name|gimp_image_get_display_name
argument_list|(
name|image
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
block|}
name|gimp_message_box_set_primary_text
argument_list|(
name|box
argument_list|,
name|_
argument_list|(
literal|"Save the changes to image '%s' "
literal|"before closing?"
argument_list|)
argument_list|,
name|gimp_image_get_display_name
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_close_exported (GimpImage * image,GFile * file,GimpMessageBox * box)
name|gimp_display_shell_close_exported
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpMessageBox
modifier|*
name|box
parameter_list|)
block|{
name|gimp_display_shell_close_time_changed
argument_list|(
name|box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_close_time_changed (GimpMessageBox * box)
name|gimp_display_shell_close_time_changed
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"gimp-image"
argument_list|)
decl_stmt|;
name|gint64
name|dirty_time
init|=
name|gimp_image_get_dirty_time
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|time_text
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|export_text
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|dirty_time
condition|)
block|{
name|gint
name|hours
init|=
literal|0
decl_stmt|;
name|gint
name|minutes
init|=
literal|0
decl_stmt|;
name|gimp_time_since
argument_list|(
name|dirty_time
argument_list|,
operator|&
name|hours
argument_list|,
operator|&
name|minutes
argument_list|)
expr_stmt|;
if|if
condition|(
name|hours
operator|>
literal|0
condition|)
block|{
if|if
condition|(
name|hours
operator|>
literal|1
operator|||
name|minutes
operator|==
literal|0
condition|)
block|{
name|time_text
operator|=
name|g_strdup_printf
argument_list|(
name|ngettext
argument_list|(
literal|"If you don't save the image, "
literal|"changes from the last hour "
literal|"will be lost."
argument_list|,
literal|"If you don't save the image, "
literal|"changes from the last %d "
literal|"hours will be lost."
argument_list|,
name|hours
argument_list|)
argument_list|,
name|hours
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|time_text
operator|=
name|g_strdup_printf
argument_list|(
name|ngettext
argument_list|(
literal|"If you don't save the image, "
literal|"changes from the last hour "
literal|"and %d minute will be lost."
argument_list|,
literal|"If you don't save the image, "
literal|"changes from the last hour "
literal|"and %d minutes will be lost."
argument_list|,
name|minutes
argument_list|)
argument_list|,
name|minutes
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|time_text
operator|=
name|g_strdup_printf
argument_list|(
name|ngettext
argument_list|(
literal|"If you don't save the image, "
literal|"changes from the last minute "
literal|"will be lost."
argument_list|,
literal|"If you don't save the image, "
literal|"changes from the last %d "
literal|"minutes will be lost."
argument_list|,
name|minutes
argument_list|)
argument_list|,
name|minutes
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|gimp_image_is_export_dirty
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|file
operator|=
name|gimp_image_get_exported_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
name|file
operator|=
name|gimp_image_get_imported_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|export_text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"The image has been exported to '%s'."
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|time_text
operator|&&
name|export_text
condition|)
name|gimp_message_box_set_text
argument_list|(
name|box
argument_list|,
literal|"%s\n\n%s"
argument_list|,
name|time_text
argument_list|,
name|export_text
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|time_text
operator|||
name|export_text
condition|)
name|gimp_message_box_set_text
argument_list|(
name|box
argument_list|,
literal|"%s"
argument_list|,
name|time_text
condition|?
name|time_text
else|:
name|export_text
argument_list|)
expr_stmt|;
else|else
name|gimp_message_box_set_text
argument_list|(
name|box
argument_list|,
literal|"%s"
argument_list|,
name|time_text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|time_text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|export_text
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_close_response (GtkWidget * widget,gint response_id,GimpDisplayShell * shell)
name|gimp_display_shell_close_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|GTK_RESPONSE_CLOSE
case|:
name|gimp_display_close
argument_list|(
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
break|break;
case|case
name|RESPONSE_SAVE
case|:
block|{
name|GimpImageWindow
modifier|*
name|window
init|=
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
decl_stmt|;
if|if
condition|(
name|window
condition|)
block|{
name|GimpUIManager
modifier|*
name|manager
init|=
name|gimp_image_window_get_ui_manager
argument_list|(
name|window
argument_list|)
decl_stmt|;
name|gimp_image_window_set_active_shell
argument_list|(
name|window
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_ui_manager_activate_action
argument_list|(
name|manager
argument_list|,
literal|"file"
argument_list|,
literal|"file-save-and-close"
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_close_accel_marshal (GClosure * closure,GValue * return_value,guint n_param_values,const GValue * param_values,gpointer invocation_hint,gpointer marshal_data)
name|gimp_display_shell_close_accel_marshal
parameter_list|(
name|GClosure
modifier|*
name|closure
parameter_list|,
name|GValue
modifier|*
name|return_value
parameter_list|,
name|guint
name|n_param_values
parameter_list|,
specifier|const
name|GValue
modifier|*
name|param_values
parameter_list|,
name|gpointer
name|invocation_hint
parameter_list|,
name|gpointer
name|marshal_data
parameter_list|)
block|{
name|gtk_dialog_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|closure
operator|->
name|data
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|)
expr_stmt|;
comment|/* we handled the accelerator */
name|g_value_set_boolean
argument_list|(
name|return_value
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_time_since (gint64 then,gint * hours,gint * minutes)
name|gimp_time_since
parameter_list|(
name|gint64
name|then
parameter_list|,
name|gint
modifier|*
name|hours
parameter_list|,
name|gint
modifier|*
name|minutes
parameter_list|)
block|{
name|gint64
name|now
init|=
name|time
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|gint64
name|diff
init|=
literal|1
operator|+
name|now
operator|-
name|then
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|now
operator|>=
name|then
argument_list|)
expr_stmt|;
comment|/*  first round up to the nearest minute  */
name|diff
operator|=
operator|(
name|diff
operator|+
literal|59
operator|)
operator|/
literal|60
expr_stmt|;
comment|/*  then optionally round minutes to multiples of 5 or 10  */
if|if
condition|(
name|diff
operator|>
literal|50
condition|)
name|diff
operator|=
operator|(
operator|(
name|diff
operator|+
literal|8
operator|)
operator|/
literal|10
operator|)
operator|*
literal|10
expr_stmt|;
elseif|else
if|if
condition|(
name|diff
operator|>
literal|20
condition|)
name|diff
operator|=
operator|(
operator|(
name|diff
operator|+
literal|3
operator|)
operator|/
literal|5
operator|)
operator|*
literal|5
expr_stmt|;
comment|/*  determine full hours  */
if|if
condition|(
name|diff
operator|>=
literal|60
condition|)
block|{
operator|*
name|hours
operator|=
name|diff
operator|/
literal|60
expr_stmt|;
name|diff
operator|=
operator|(
name|diff
operator|%
literal|60
operator|)
expr_stmt|;
block|}
comment|/*  round up to full hours for 2 and more  */
if|if
condition|(
operator|*
name|hours
operator|>
literal|1
operator|&&
name|diff
operator|>
literal|0
condition|)
block|{
operator|*
name|hours
operator|+=
literal|1
expr_stmt|;
name|diff
operator|=
literal|0
expr_stmt|;
block|}
operator|*
name|minutes
operator|=
name|diff
expr_stmt|;
block|}
end_function

end_unit

