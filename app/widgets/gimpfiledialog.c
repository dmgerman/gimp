begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfiledialog.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
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
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"gimpfiledialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpthumbbox.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_file_dialog_class_init
parameter_list|(
name|GimpFileDialogClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_dialog_init
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_dialog_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_file_dialog_delete_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventAny
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_dialog_selection_changed
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkFileSelectionClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_file_dialog_get_type (void)
name|gimp_file_dialog_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|dialog_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|dialog_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|dialog_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpFileDialogClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_file_dialog_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpFileDialog
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_file_dialog_init
block|,       }
decl_stmt|;
name|dialog_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_FILE_SELECTION
argument_list|,
literal|"GimpFileDialog"
argument_list|,
operator|&
name|dialog_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|dialog_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_dialog_class_init (GimpFileDialogClass * klass)
name|gimp_file_dialog_class_init
parameter_list|(
name|GimpFileDialogClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_file_dialog_destroy
expr_stmt|;
name|widget_class
operator|->
name|delete_event
operator|=
name|gimp_file_dialog_delete_event
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_dialog_init (GimpFileDialog * dialog)
name|gimp_file_dialog_init
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkFileSelection
modifier|*
name|fs
init|=
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|fs
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|fs
operator|->
name|button_area
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_dialog_destroy (GtkObject * object)
name|gimp_file_dialog_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFileDialog
modifier|*
name|dialog
init|=
name|GIMP_FILE_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|item_factory
condition|)
block|{
name|g_object_unref
argument_list|(
name|dialog
operator|->
name|item_factory
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|item_factory
operator|=
name|NULL
expr_stmt|;
block|}
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_file_dialog_delete_event (GtkWidget * widget,GdkEventAny * event)
name|gimp_file_dialog_delete_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventAny
modifier|*
name|event
parameter_list|)
block|{
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_file_dialog_new (Gimp * gimp,GSList * file_procs,GimpMenuFactory * menu_factory,const gchar * menu_identifier,const gchar * title,const gchar * role,const gchar * stock_id,const gchar * help_id)
name|gimp_file_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GSList
modifier|*
name|file_procs
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|GimpFileDialog
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|option_menu
decl_stmt|;
name|GtkWidget
modifier|*
name|label
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
name|file_procs
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_identifier
operator|!=
name|NULL
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
name|g_return_val_if_fail
argument_list|(
name|role
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|stock_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FILE_DIALOG
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|role
argument_list|)
expr_stmt|;
name|gimp_help_connect
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|help_id
argument_list|,
name|NULL
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
name|item_factory
operator|=
name|gimp_menu_factory_menu_new
argument_list|(
name|menu_factory
argument_list|,
name|menu_identifier
argument_list|,
name|GTK_TYPE_MENU
argument_list|,
name|dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|option_menu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|,
name|GTK_ITEM_FACTORY
argument_list|(
name|dialog
operator|->
name|item_factory
argument_list|)
operator|->
name|widget
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|option_menu
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
name|option_menu
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Determine File _Type:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|option_menu
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
if|if
condition|(
name|gimp
operator|->
name|config
operator|->
name|thumbnail_size
operator|>
literal|0
condition|)
block|{
name|GtkFileSelection
modifier|*
name|fs
init|=
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|tree_sel
decl_stmt|;
name|tree_sel
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|fs
operator|->
name|file_list
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Catch file-list clicks so we can update the preview thumbnail */
name|g_signal_connect
argument_list|(
name|tree_sel
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_dialog_selection_changed
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
comment|/* EEK */
for|for
control|(
name|hbox
operator|=
name|fs
operator|->
name|dir_list
init|;
operator|!
name|GTK_IS_HBOX
argument_list|(
name|hbox
argument_list|)
condition|;
name|hbox
operator|=
name|hbox
operator|->
name|parent
control|)
empty_stmt|;
name|dialog
operator|->
name|thumb_box
operator|=
name|gimp_thumb_box_new
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
operator|->
name|thumb_box
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|thumb_box
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
name|thumb_box
argument_list|)
expr_stmt|;
block|}
return|return
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_file_dialog_set_file_proc (GimpFileDialog * dialog,PlugInProcDef * file_proc)
name|gimp_file_dialog_set_file_proc
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|,
name|PlugInProcDef
modifier|*
name|file_proc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_proc
operator|==
name|dialog
operator|->
name|file_proc
condition|)
return|return;
name|dialog
operator|->
name|file_proc
operator|=
name|file_proc
expr_stmt|;
if|if
condition|(
name|file_proc
operator|&&
name|file_proc
operator|->
name|extensions_list
operator|&&
name|dialog
operator|->
name|gimage
condition|)
block|{
name|GtkFileSelection
modifier|*
name|fs
init|=
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
decl_stmt|;
name|gchar
modifier|*
name|last_dot
decl_stmt|;
name|GString
modifier|*
name|s
decl_stmt|;
name|text
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|fs
operator|->
name|selection_entry
argument_list|)
argument_list|)
expr_stmt|;
name|last_dot
operator|=
name|strrchr
argument_list|(
name|text
argument_list|,
literal|'.'
argument_list|)
expr_stmt|;
if|if
condition|(
name|last_dot
operator|==
name|text
operator|||
operator|!
name|text
index|[
literal|0
index|]
condition|)
return|return;
name|s
operator|=
name|g_string_new
argument_list|(
name|text
argument_list|)
expr_stmt|;
if|if
condition|(
name|last_dot
condition|)
name|g_string_truncate
argument_list|(
name|s
argument_list|,
name|last_dot
operator|-
name|text
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|s
argument_list|,
literal|"."
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|s
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|file_proc
operator|->
name|extensions_list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|fs
operator|->
name|selection_entry
argument_list|)
argument_list|,
name|s
operator|->
name|str
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|s
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_file_dialog_set_image (GimpFileDialog * dialog,GimpImage * gimage,gboolean set_uri_and_proc,gboolean set_image_clean)
name|gimp_file_dialog_set_image
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gboolean
name|set_uri_and_proc
parameter_list|,
name|gboolean
name|set_image_clean
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|dialog
operator|->
name|set_uri_and_proc
operator|=
name|set_uri_and_proc
expr_stmt|;
name|dialog
operator|->
name|set_image_clean
operator|=
name|set_image_clean
expr_stmt|;
name|filename
operator|=
name|gimp_image_get_filename
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gtk_file_selection_set_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filename
condition|?
name|filename
else|:
literal|"."
name|G_DIR_SEPARATOR_S
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_item_factory_update
argument_list|(
name|dialog
operator|->
name|item_factory
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
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
DECL|function|selchanged_foreach (GtkTreeModel * model,GtkTreePath * path,GtkTreeIter * iter,gpointer data)
name|selchanged_foreach
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gboolean
modifier|*
name|selected
init|=
name|data
decl_stmt|;
operator|*
name|selected
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_dialog_selection_changed (GtkTreeSelection * sel,GimpFileDialog * dialog)
name|gimp_file_dialog_selection_changed
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkFileSelection
modifier|*
name|fs
init|=
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|fullfname
decl_stmt|;
name|gboolean
name|selected
init|=
name|FALSE
decl_stmt|;
name|gtk_tree_selection_selected_foreach
argument_list|(
name|sel
argument_list|,
name|selchanged_foreach
argument_list|,
operator|&
name|selected
argument_list|)
expr_stmt|;
if|if
condition|(
name|selected
condition|)
block|{
name|gchar
modifier|*
name|uri
decl_stmt|;
name|fullfname
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|fs
argument_list|)
expr_stmt|;
name|uri
operator|=
name|file_utils_filename_to_uri
argument_list|(
name|dialog
operator|->
name|gimp
operator|->
name|load_procs
argument_list|,
name|fullfname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_thumb_box_set_uri
argument_list|(
name|GIMP_THUMB_BOX
argument_list|(
name|dialog
operator|->
name|thumb_box
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_thumb_box_set_uri
argument_list|(
name|GIMP_THUMB_BOX
argument_list|(
name|dialog
operator|->
name|thumb_box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|{
name|gchar
modifier|*
modifier|*
name|selections
decl_stmt|;
name|GSList
modifier|*
name|uris
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|selections
operator|=
name|gtk_file_selection_get_selections
argument_list|(
name|fs
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|selections
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
name|uris
operator|=
name|g_slist_prepend
argument_list|(
name|uris
argument_list|,
name|g_filename_to_uri
argument_list|(
name|selections
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_strfreev
argument_list|(
name|selections
argument_list|)
expr_stmt|;
name|uris
operator|=
name|g_slist_reverse
argument_list|(
name|uris
argument_list|)
expr_stmt|;
name|gimp_thumb_box_set_uris
argument_list|(
name|GIMP_THUMB_BOX
argument_list|(
name|dialog
operator|->
name|thumb_box
argument_list|)
argument_list|,
name|uris
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

