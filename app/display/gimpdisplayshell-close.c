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
file|<time.h>
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
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
name|gimage
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
name|gchar
modifier|*
name|gimp_time_since
parameter_list|(
name|guint
name|then
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
name|gimage
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|shell
operator|->
name|gdisp
operator|->
name|gimage
expr_stmt|;
comment|/*  FIXME: gimp_busy HACK not really appropriate here because we only    *  want to prevent the busy image and display to be closed.  --Mitch    */
if|if
condition|(
name|gimage
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
comment|/*  If the image has been modified, give the user a chance to save    *  it before nuking it--this only applies if its the last view    *  to an image canvas.  (a gimage with disp_count = 1)    */
if|if
condition|(
operator|!
name|kill_it
operator|&&
name|gimage
operator|->
name|disp_count
operator|==
literal|1
operator|&&
name|gimage
operator|->
name|dirty
operator|&&
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|confirm_on_close
condition|)
block|{
name|gimp_display_shell_close_dialog
argument_list|(
name|shell
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_display_delete
argument_list|(
name|shell
operator|->
name|gdisp
argument_list|)
expr_stmt|;
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
DECL|function|gimp_display_shell_close_dialog (GimpDisplayShell * shell,GimpImage * gimage)
name|gimp_display_shell_close_dialog
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GimpMessageBox
modifier|*
name|box
decl_stmt|;
name|GClosure
modifier|*
name|closure
decl_stmt|;
name|GSource
modifier|*
name|source
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|title
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
name|name
operator|=
name|file_utils_uri_display_basename
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|gimage
argument_list|)
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
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
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
name|GIMP_STOCK_WARNING
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
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Do_n't Save"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|)
expr_stmt|;
name|gtk_button_set_image
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|gtk_image_new_from_stock
argument_list|(
name|GTK_STOCK_DELETE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_dialog_add_buttons
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
name|RESPONSE_SAVE
argument_list|,
name|NULL
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
name|gtk_dialog_set_alternative_button_order
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
name|box
operator|=
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimage
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
name|gimp_display_shell_close_name_changed
argument_list|(
name|gimage
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
name|source
operator|=
name|g_timeout_source_new
argument_list|(
literal|1000
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
name|gimage
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
name|gchar
modifier|*
name|name
decl_stmt|;
name|name
operator|=
name|file_utils_uri_display_basename
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|window
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
name|name
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
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
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
if|if
condition|(
name|image
operator|->
name|dirty_time
condition|)
block|{
name|gchar
modifier|*
name|period
init|=
name|gimp_time_since
argument_list|(
name|image
operator|->
name|dirty_time
argument_list|)
decl_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|box
argument_list|,
name|_
argument_list|(
literal|"If you don't save the image, "
literal|"changes from the last %s will be lost."
argument_list|)
argument_list|,
name|period
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|period
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_message_box_set_text
argument_list|(
name|box
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
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
name|gimp_display_delete
argument_list|(
name|shell
operator|->
name|gdisp
argument_list|)
expr_stmt|;
break|break;
case|case
name|RESPONSE_SAVE
case|:
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|action
operator|=
name|gimp_ui_manager_find_action
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"file"
argument_list|,
literal|"file-save"
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|action
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_action_activate
argument_list|(
name|action
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|dirty
condition|)
name|gimp_display_delete
argument_list|(
name|shell
operator|->
name|gdisp
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_time_since (guint then)
name|gimp_time_since
parameter_list|(
name|guint
name|then
parameter_list|)
block|{
name|guint
name|now
init|=
name|time
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|guint
name|diff
init|=
literal|1
operator|+
name|now
operator|-
name|then
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|now
operator|>=
name|then
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* one second, the time period  */
if|if
condition|(
name|diff
operator|<
literal|60
condition|)
return|return
name|g_strdup_printf
argument_list|(
name|ngettext
argument_list|(
literal|"second"
argument_list|,
literal|"%d seconds"
argument_list|,
name|diff
argument_list|)
argument_list|,
name|diff
argument_list|)
return|;
comment|/*  round to the nearest minute  */
name|diff
operator|=
operator|(
name|diff
operator|+
literal|30
operator|)
operator|/
literal|60
expr_stmt|;
return|return
name|g_strdup_printf
argument_list|(
name|ngettext
argument_list|(
literal|"minute"
argument_list|,
literal|"%d minutes"
argument_list|,
name|diff
argument_list|)
argument_list|,
name|diff
argument_list|)
return|;
block|}
end_function

end_unit

