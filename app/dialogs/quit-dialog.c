begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainertreeview.h"
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
file|"quit-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|quit_dialog_response
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
name|quit_dialog_container_changed
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
name|GimpContainer
modifier|*
name|images
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|rows
decl_stmt|;
name|gint
name|preview_size
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
name|images
operator|=
name|gimp_displays_get_dirty_images
argument_list|(
name|gimp
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
for|for
control|(
name|list
operator|=
name|gimp_action_groups_from_name
argument_list|(
literal|"file"
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
name|gimp_action_group_set_action_sensitive
argument_list|(
name|list
operator|->
name|data
argument_list|,
literal|"file-quit"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Quit The GIMP?"
argument_list|)
argument_list|,
literal|"gimp-quit"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_FILE_QUIT_CONFIRM
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_QUIT
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
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
name|quit_dialog_response
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|box
operator|=
name|gimp_message_box_new
argument_list|(
name|GIMP_STOCK_WILBER_EEK
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|box
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
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
name|quit_dialog_container_changed
argument_list|)
argument_list|,
name|box
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|quit_dialog_container_changed
argument_list|(
name|images
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|preview_size
operator|=
name|gimp
operator|->
name|config
operator|->
name|layer_preview_size
expr_stmt|;
name|view
operator|=
name|gimp_container_tree_view_new
argument_list|(
name|images
argument_list|,
name|NULL
argument_list|,
name|preview_size
argument_list|,
literal|1
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
name|rows
operator|=
name|CLAMP
argument_list|(
name|gimp_container_num_children
argument_list|(
name|images
argument_list|)
argument_list|,
literal|3
argument_list|,
literal|6
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
name|preview_size
operator|+
literal|2
operator|)
argument_list|)
expr_stmt|;
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
return|return
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|quit_dialog_response (GtkWidget * dialog,gint response_id,Gimp * gimp)
name|quit_dialog_response
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
name|GList
modifier|*
name|list
decl_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_action_groups_from_name
argument_list|(
literal|"file"
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
name|gimp_action_group_set_action_sensitive
argument_list|(
name|list
operator|->
name|data
argument_list|,
literal|"file-quit"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|quit_dialog_container_changed (GimpContainer * images,GimpObject * image,GimpMessageBox * box)
name|quit_dialog_container_changed
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
name|gimp_container_num_children
argument_list|(
name|images
argument_list|)
decl_stmt|;
if|if
condition|(
name|num_images
operator|==
literal|1
condition|)
name|gimp_message_box_set_primary_text
argument_list|(
name|box
argument_list|,
name|_
argument_list|(
literal|"There is one image with unsaved changes:"
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_message_box_set_primary_text
argument_list|(
name|box
argument_list|,
name|_
argument_list|(
literal|"There are %d images with unsaved changes:"
argument_list|)
argument_list|,
name|num_images
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

