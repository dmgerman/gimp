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
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainertreestore.h"
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
file|"widgets/gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
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

begin_typedef
DECL|typedef|QuitDialog
typedef|typedef
name|struct
name|_QuitDialog
name|QuitDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_QuitDialog
struct|struct
name|_QuitDialog
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|images
name|GimpContainer
modifier|*
name|images
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|do_quit
name|gboolean
name|do_quit
decl_stmt|;
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|ok_button
name|GtkWidget
modifier|*
name|ok_button
decl_stmt|;
DECL|member|box
name|GimpMessageBox
modifier|*
name|box
decl_stmt|;
DECL|member|lost_label
name|GtkWidget
modifier|*
name|lost_label
decl_stmt|;
DECL|member|hint_label
name|GtkWidget
modifier|*
name|hint_label
decl_stmt|;
DECL|member|accel_key
name|guint
name|accel_key
decl_stmt|;
DECL|member|accel_mods
name|GdkModifierType
name|accel_mods
decl_stmt|;
block|}
struct|;
end_struct

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
name|quit_close_all_dialog_free
parameter_list|(
name|QuitDialog
modifier|*
name|dialog
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
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|QuitDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|quit_close_all_dialog_accel_marshal
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
name|GtkWidget
modifier|*
name|widget
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
name|QuitDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|quit_close_all_dialog_name_cell_func
parameter_list|(
name|GtkTreeViewColumn
modifier|*
name|tree_column
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
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
name|QuitDialog
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|GimpContainerTreeView
modifier|*
name|tree_view
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|renderer
decl_stmt|;
name|GtkWidget
modifier|*
name|dnd_widget
decl_stmt|;
name|GtkAccelGroup
modifier|*
name|accel_group
decl_stmt|;
name|GClosure
modifier|*
name|closure
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
name|dialog
operator|=
name|g_new0
argument_list|(
name|QuitDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|dialog
operator|->
name|do_quit
operator|=
name|do_quit
expr_stmt|;
name|dialog
operator|->
name|images
operator|=
name|gimp_displays_get_dirty_images
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|dialog
operator|->
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
name|dialog
operator|->
name|images
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|->
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
operator|->
name|dialog
argument_list|)
argument_list|,
literal|"quit-dialog"
argument_list|,
name|dialog
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|quit_close_all_dialog_free
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|ok_button
operator|=
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
literal|""
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
operator|->
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
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|quit_close_all_dialog_response
argument_list|)
argument_list|,
name|dialog
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
name|dialog
operator|->
name|dialog
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
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_closure_set_marshal
argument_list|(
name|closure
argument_list|,
name|quit_close_all_dialog_accel_marshal
argument_list|)
expr_stmt|;
name|gtk_accelerator_parse
argument_list|(
literal|"<Primary>D"
argument_list|,
operator|&
name|dialog
operator|->
name|accel_key
argument_list|,
operator|&
name|dialog
operator|->
name|accel_mods
argument_list|)
expr_stmt|;
name|gtk_accel_group_connect
argument_list|(
name|accel_group
argument_list|,
name|dialog
operator|->
name|accel_key
argument_list|,
name|dialog
operator|->
name|accel_mods
argument_list|,
literal|0
argument_list|,
name|closure
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|box
operator|=
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
operator|->
name|box
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
name|dialog
operator|->
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
name|dialog
operator|->
name|images
argument_list|,
name|dialog
operator|->
name|context
argument_list|,
name|view_size
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|gimp_container_tree_view_get_name_cell
argument_list|(
name|tree_view
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_cell_data_func
argument_list|(
name|tree_view
operator|->
name|main_column
argument_list|,
name|renderer
argument_list|,
name|quit_close_all_dialog_name_cell_func
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|dialog
operator|->
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
name|dialog
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
name|dialog
operator|->
name|lost_label
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
name|dialog
operator|->
name|lost_label
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
name|dialog
operator|->
name|lost_label
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
name|dialog
operator|->
name|lost_label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|,
name|dialog
operator|->
name|lost_label
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
name|dialog
operator|->
name|lost_label
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|hint_label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|dialog
operator|->
name|hint_label
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
name|dialog
operator|->
name|hint_label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|,
name|dialog
operator|->
name|hint_label
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
name|dialog
operator|->
name|hint_label
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dialog
operator|->
name|images
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|quit_close_all_dialog_container_changed
argument_list|)
argument_list|,
name|dialog
operator|->
name|dialog
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dialog
operator|->
name|images
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|quit_close_all_dialog_container_changed
argument_list|)
argument_list|,
name|dialog
operator|->
name|dialog
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|quit_close_all_dialog_container_changed
argument_list|(
name|dialog
operator|->
name|images
argument_list|,
name|NULL
argument_list|,
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
return|return
name|dialog
operator|->
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|quit_close_all_dialog_free (QuitDialog * dialog)
name|quit_close_all_dialog_free
parameter_list|(
name|QuitDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|g_object_unref
argument_list|(
name|dialog
operator|->
name|images
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dialog
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|quit_close_all_dialog_response (GtkWidget * widget,gint response_id,QuitDialog * dialog)
name|quit_close_all_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|QuitDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|dialog
operator|->
name|gimp
decl_stmt|;
name|gboolean
name|do_quit
init|=
name|dialog
operator|->
name|do_quit
decl_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
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
DECL|function|quit_close_all_dialog_accel_marshal (GClosure * closure,GValue * return_value,guint n_param_values,const GValue * param_values,gpointer invocation_hint,gpointer marshal_data)
name|quit_close_all_dialog_accel_marshal
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
name|GTK_RESPONSE_OK
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
DECL|function|quit_close_all_dialog_container_changed (GimpContainer * images,GimpObject * image,GtkWidget * widget)
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
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|QuitDialog
modifier|*
name|dialog
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"quit-dialog"
argument_list|)
decl_stmt|;
name|gint
name|num_images
init|=
name|gimp_container_get_n_children
argument_list|(
name|images
argument_list|)
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
name|accel_string
operator|=
name|gtk_accelerator_get_label
argument_list|(
name|dialog
operator|->
name|accel_key
argument_list|,
name|dialog
operator|->
name|accel_mods
argument_list|)
expr_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|dialog
operator|->
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
name|dialog
operator|->
name|lost_label
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|->
name|do_quit
condition|)
name|hint
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Press %s to quit."
argument_list|)
argument_list|,
name|accel_string
argument_list|)
expr_stmt|;
else|else
name|hint
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Press %s to close all images."
argument_list|)
argument_list|,
name|accel_string
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|dialog
operator|->
name|ok_button
argument_list|,
literal|"label"
argument_list|,
name|dialog
operator|->
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
name|dialog
operator|->
name|ok_button
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|icon
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|do_quit
condition|)
name|hint
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Press %s to discard all changes and quit."
argument_list|)
argument_list|,
name|accel_string
argument_list|)
expr_stmt|;
else|else
name|hint
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Press %s to discard all changes and close all images."
argument_list|)
argument_list|,
name|accel_string
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|lost_label
argument_list|)
expr_stmt|;
name|icon
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|GTK_STOCK_DELETE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|dialog
operator|->
name|ok_button
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
operator|->
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|)
expr_stmt|;
block|}
name|markup
operator|=
name|g_strdup_printf
argument_list|(
literal|"<i><small>%s</small></i>"
argument_list|,
name|hint
argument_list|)
expr_stmt|;
name|gtk_label_set_markup
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|hint_label
argument_list|)
argument_list|,
name|markup
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|quit_close_all_dialog_image_activated (GimpContainerView * view,GimpImage * image,gpointer insert_data,QuitDialog * dialog)
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
name|QuitDialog
modifier|*
name|dialog
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
name|dialog
operator|->
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
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
operator|==
name|image
condition|)
name|gimp_display_shell_present
argument_list|(
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|quit_close_all_dialog_name_cell_func (GtkTreeViewColumn * tree_column,GtkCellRenderer * cell,GtkTreeModel * tree_model,GtkTreeIter * iter,gpointer data)
name|quit_close_all_dialog_name_cell_func
parameter_list|(
name|GtkTreeViewColumn
modifier|*
name|tree_column
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpViewRenderer
modifier|*
name|renderer
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|tree_model
argument_list|,
name|iter
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_RENDERER
argument_list|,
operator|&
name|renderer
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME
argument_list|,
operator|&
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|image
operator|=
name|GIMP_IMAGE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_is_export_dirty
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"markup"
argument_list|,
name|NULL
argument_list|,
literal|"text"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|escaped_name
decl_stmt|;
name|gchar
modifier|*
name|escaped_filename
decl_stmt|;
name|gchar
modifier|*
name|exported
decl_stmt|;
name|gchar
modifier|*
name|markup
decl_stmt|;
name|uri
operator|=
name|gimp_image_get_exported_uri
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|uri
condition|)
name|uri
operator|=
name|gimp_image_get_imported_uri
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|escaped_name
operator|=
name|g_markup_escape_text
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|escaped_filename
operator|=
name|g_markup_escape_text
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|exported
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Exported to %s"
argument_list|)
argument_list|,
name|escaped_filename
argument_list|)
expr_stmt|;
name|markup
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s\n<i>%s</i>"
argument_list|,
name|escaped_name
argument_list|,
name|exported
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|exported
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|escaped_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|escaped_filename
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"text"
argument_list|,
name|NULL
argument_list|,
literal|"markup"
argument_list|,
name|markup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|markup
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

