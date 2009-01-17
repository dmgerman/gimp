begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"dialogs-types.h"
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
file|"widgets/gimpcontainertreeview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdnd.h"
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
file|"quit-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|quit_close_all_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|do_quit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|quit_close_all_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|quit_close_all_dialog_container_changed
parameter_list|(
name|GimpContainer
modifier|*
name|images
parameter_list|,
name|GimpObject
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
name|quit_close_all_dialog_image_activated
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|quit_dialog_new (Gimp * gimp)
name|quit_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|quit_close_all_dialog_new
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|close_all_dialog_new (Gimp * gimp)
name|close_all_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|quit_close_all_dialog_new
argument_list|(
name|gimp
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|quit_close_all_dialog_new (Gimp * gimp,gboolean do_quit)
name|quit_close_all_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|do_quit
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|images
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpMessageBox
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|GtkWidget
modifier|*
name|dnd_widget
decl_stmt|;
name|gint
name|rows
decl_stmt|;
name|gint
name|view_size
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
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: need container of dirty images
endif|#
directive|endif
name|images
operator|=
name|gimp_displays_get_dirty_images
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_context_new
argument_list|(
name|gimp
argument_list|,
literal|"close-all-dialog"
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|images
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|do_quit
condition|?
name|_
argument_list|(
literal|"Quit GIMP"
argument_list|)
else|:
name|_
argument_list|(
literal|"Close All Images"
argument_list|)
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|do_quit
condition|?
name|GIMP_HELP_FILE_QUIT
else|:
name|GIMP_HELP_FILE_CLOSE_ALL
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"dirty-images"
argument_list|,
name|images
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"dirty-images-context"
argument_list|,
name|context
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
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
name|quit_close_all_dialog_response
argument_list|)
argument_list|,
name|gimp
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
name|button
operator|=
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|""
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"ok-button"
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"do-quit"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|do_quit
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|images
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|quit_close_all_dialog_container_changed
argument_list|)
argument_list|,
name|box
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|images
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|quit_close_all_dialog_container_changed
argument_list|)
argument_list|,
name|box
argument_list|,
literal|0
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
name|view_size
operator|=
name|gimp
operator|->
name|config
operator|->
name|layer_preview_size
expr_stmt|;
name|rows
operator|=
name|CLAMP
argument_list|(
name|gimp_container_get_n_children
argument_list|(
name|images
argument_list|)
argument_list|,
literal|3
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|view
operator|=
name|gimp_container_tree_view_new
argument_list|(
name|images
argument_list|,
name|context
argument_list|,
name|view_size
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_container_box_set_size_request
argument_list|(
name|GIMP_CONTAINER_BOX
argument_list|(
name|view
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|rows
operator|*
operator|(
name|view_size
operator|+
literal|2
operator|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
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
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|view
argument_list|,
literal|"activate-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|quit_close_all_dialog_image_activated
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|dnd_widget
operator|=
name|gimp_container_view_get_dnd_widget
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dnd_xds_source_add
argument_list|(
name|dnd_widget
argument_list|,
operator|(
name|GimpDndDragViewableFunc
operator|)
name|gimp_dnd_get_drag_data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|do_quit
condition|)
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"If you quit GIMP now, "
literal|"these changes will be lost."
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"If you close these images now, "
literal|"changes will be lost."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
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
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"lost-label"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|quit_close_all_dialog_container_changed
argument_list|(
name|images
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|quit_close_all_dialog_response (GtkWidget * dialog,gint response_id,Gimp * gimp)
name|quit_close_all_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpMessageBox
modifier|*
name|box
init|=
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
decl_stmt|;
name|gboolean
name|do_quit
init|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"do-quit"
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
if|if
condition|(
name|do_quit
condition|)
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|gimp_displays_close
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|quit_close_all_dialog_container_changed (GimpContainer * images,GimpObject * image,GimpMessageBox * box)
name|quit_close_all_dialog_container_changed
parameter_list|(
name|GimpContainer
modifier|*
name|images
parameter_list|,
name|GimpObject
modifier|*
name|image
parameter_list|,
name|GimpMessageBox
modifier|*
name|box
parameter_list|)
block|{
name|gint
name|num_images
init|=
name|gimp_container_get_n_children
argument_list|(
name|images
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|label
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"lost-label"
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|button
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"ok-button"
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
init|=
name|gtk_widget_get_toplevel
argument_list|(
name|button
argument_list|)
decl_stmt|;
name|gboolean
name|do_quit
init|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"do-quit"
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|box
argument_list|,
name|ngettext
argument_list|(
literal|"There is one image with "
literal|"unsaved changes:"
argument_list|,
literal|"There are %d images with "
literal|"unsaved changes:"
argument_list|,
name|num_images
argument_list|)
argument_list|,
name|num_images
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_images
operator|==
literal|0
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|button
argument_list|,
literal|"label"
argument_list|,
name|do_quit
condition|?
name|GTK_STOCK_QUIT
else|:
name|GTK_STOCK_CLOSE
argument_list|,
literal|"use-stock"
argument_list|,
name|TRUE
argument_list|,
literal|"image"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_grab_default
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|icon
init|=
name|gtk_image_new_from_stock
argument_list|(
name|GTK_STOCK_DELETE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
decl_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|button
argument_list|,
literal|"label"
argument_list|,
name|_
argument_list|(
literal|"_Discard Changes"
argument_list|)
argument_list|,
literal|"use-stock"
argument_list|,
name|FALSE
argument_list|,
literal|"image"
argument_list|,
name|icon
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
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|quit_close_all_dialog_image_activated (GimpContainerView * view,GimpImage * image,gpointer insert_data,Gimp * gimp)
name|quit_close_all_dialog_image_activated
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_display_iter
argument_list|(
name|gimp
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|image
operator|==
name|image
condition|)
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

