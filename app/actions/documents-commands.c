begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpthumb/gimpthumb.h"
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
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-documents.h"
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
file|"core/gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpclipboard.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdocumentview.h"
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"documents-commands.h"
end_include

begin_include
include|#
directive|include
file|"file-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|RaiseClosure
typedef|typedef
name|struct
name|_RaiseClosure
name|RaiseClosure
typedef|;
end_typedef

begin_struct
DECL|struct|_RaiseClosure
struct|struct
name|_RaiseClosure
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|found
name|gboolean
name|found
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|documents_open_image
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|documents_raise_display
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions */
end_comment

begin_function
name|void
DECL|function|documents_open_cmd_callback (GtkAction * action,gpointer data)
name|documents_open_cmd_callback
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
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
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
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_context_get_imagefile
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
condition|)
block|{
name|documents_open_image
argument_list|(
name|context
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|file_file_open_dialog
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|documents_raise_or_open_cmd_callback (GtkAction * action,gpointer data)
name|documents_raise_or_open_cmd_callback
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
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
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
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_context_get_imagefile
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
condition|)
block|{
name|RaiseClosure
name|closure
decl_stmt|;
name|closure
operator|.
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|closure
operator|.
name|found
operator|=
name|FALSE
expr_stmt|;
name|gimp_container_foreach
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|displays
argument_list|,
name|documents_raise_display
argument_list|,
operator|&
name|closure
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|closure
operator|.
name|found
condition|)
name|documents_open_image
argument_list|(
name|context
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|documents_file_open_dialog_cmd_callback (GtkAction * action,gpointer data)
name|documents_file_open_dialog_cmd_callback
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
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
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
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_context_get_imagefile
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
condition|)
block|{
name|file_file_open_dialog
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|documents_copy_location_cmd_callback (GtkAction * action,gpointer data)
name|documents_copy_location_cmd_callback
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
name|GimpImagefile
modifier|*
name|imagefile
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
name|imagefile
operator|=
name|gimp_context_get_imagefile
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
condition|)
name|gimp_clipboard_set_text
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|documents_remove_cmd_callback (GtkAction * action,gpointer data)
name|documents_remove_cmd_callback
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
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
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
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_context_get_imagefile
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_container_remove
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|documents_clear_cmd_callback (GtkAction * action,gpointer data)
name|documents_clear_cmd_callback
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
name|GtkWidget
modifier|*
name|dialog
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
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Clear Document History"
argument_list|)
argument_list|,
name|GIMP_STOCK_QUESTION
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_DIALOG_MODAL
operator||
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_CLEAR
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
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
name|g_signal_connect_object
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|,
literal|"unmap"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|dialog
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Remove all entries from the "
literal|"document history?"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Clearing the document history will permanently "
literal|"remove all currently listed entries."
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|gimp_container_clear
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|documents
argument_list|)
expr_stmt|;
name|gimp_documents_save
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|documents_recreate_preview_cmd_callback (GtkAction * action,gpointer data)
name|documents_recreate_preview_cmd_callback
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
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
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
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_context_get_imagefile
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_imagefile_create_thumbnail
argument_list|(
name|imagefile
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|,
name|imagefile
operator|->
name|gimp
operator|->
name|config
operator|->
name|thumbnail_size
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|documents_reload_previews_cmd_callback (GtkAction * action,gpointer data)
name|documents_reload_previews_cmd_callback
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
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gimp_container_foreach
argument_list|(
name|container
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_imagefile_update
argument_list|,
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|documents_remove_dangling_foreach (GimpImagefile * imagefile,GimpContainer * container)
name|documents_remove_dangling_foreach
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
if|if
condition|(
name|gimp_thumbnail_peek_image
argument_list|(
name|imagefile
operator|->
name|thumbnail
argument_list|)
operator|==
name|GIMP_THUMB_STATE_NOT_FOUND
condition|)
block|{
name|gimp_container_remove
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|documents_remove_dangling_cmd_callback (GtkAction * action,gpointer data)
name|documents_remove_dangling_cmd_callback
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
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gimp_container_foreach
argument_list|(
name|container
argument_list|,
operator|(
name|GFunc
operator|)
name|documents_remove_dangling_foreach
argument_list|,
name|container
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
DECL|function|documents_open_image (GimpContext * context,GimpImagefile * imagefile)
name|documents_open_image
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|file_open_with_display
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|,
name|uri
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|file_utils_uri_display_name
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|gimp_message
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Opening '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|documents_raise_display (gpointer data,gpointer user_data)
name|documents_raise_display
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|data
decl_stmt|;
name|RaiseClosure
modifier|*
name|closure
init|=
name|user_data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
operator|&&
operator|!
name|strcmp
argument_list|(
name|closure
operator|->
name|name
argument_list|,
name|uri
argument_list|)
condition|)
block|{
name|closure
operator|->
name|found
operator|=
name|TRUE
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

