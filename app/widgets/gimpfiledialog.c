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
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrendererimagefile.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
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
name|GtkFileChooser
modifier|*
name|chooser
parameter_list|,
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_dialog_update_preview
parameter_list|(
name|GtkFileChooser
modifier|*
name|chooser
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
name|GtkFileChooserDialogClass
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
name|GTK_TYPE_FILE_CHOOSER_DIALOG
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
block|{ }
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
name|manager
condition|)
block|{
name|g_object_unref
argument_list|(
name|dialog
operator|->
name|manager
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|manager
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
DECL|function|gimp_file_dialog_new (Gimp * gimp,GSList * file_procs,GtkFileChooserAction action,GimpMenuFactory * menu_factory,const gchar * menu_identifier,const gchar * ui_path,const gchar * title,const gchar * role,const gchar * stock_id,const gchar * help_id)
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
name|GtkFileChooserAction
name|action
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
name|ui_path
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
name|GtkFileFilter
modifier|*
name|filter
decl_stmt|;
name|GSList
modifier|*
name|list
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
name|ui_path
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
literal|"role"
argument_list|,
name|role
argument_list|,
literal|"action"
argument_list|,
name|action
argument_list|,
name|NULL
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
name|stock_id
argument_list|,
name|GTK_RESPONSE_OK
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
name|GTK_RESPONSE_OK
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
name|manager
operator|=
name|gimp_menu_factory_manager_new
argument_list|(
name|menu_factory
argument_list|,
name|menu_identifier
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_extra_widget
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|hbox
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
name|gimp_ui_manager_ui_get
argument_list|(
name|dialog
operator|->
name|manager
argument_list|,
name|ui_path
argument_list|)
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
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"selection-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_dialog_selection_changed
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"update-preview"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_dialog_update_preview
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
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
name|gtk_file_chooser_set_preview_widget
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|dialog
operator|->
name|thumb_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|thumb_box
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_FILE_SYSTEM_ICONS
name|GIMP_PREVIEW_RENDERER_IMAGEFILE
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|GIMP_THUMB_BOX
argument_list|(
name|dialog
operator|->
name|thumb_box
argument_list|)
operator|->
name|preview
argument_list|)
operator|->
name|renderer
argument_list|)
operator|->
name|file_system
operator|=
name|_gtk_file_chooser_get_file_system
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gtk_file_chooser_set_use_preview_label
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|filter
operator|=
name|gtk_file_filter_new
argument_list|()
expr_stmt|;
name|gtk_file_filter_set_name
argument_list|(
name|filter
argument_list|,
name|_
argument_list|(
literal|"All Files"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_file_filter_add_pattern
argument_list|(
name|filter
argument_list|,
literal|"*"
argument_list|)
expr_stmt|;
name|gtk_file_chooser_add_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|file_procs
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
name|PlugInProcDef
modifier|*
name|file_proc
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|file_proc
operator|->
name|menu_paths
operator|&&
name|file_proc
operator|->
name|extensions_list
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|GSList
modifier|*
name|ext
decl_stmt|;
if|if
condition|(
name|file_proc
operator|->
name|menu_label
condition|)
name|name
operator|=
name|file_proc
operator|->
name|menu_label
expr_stmt|;
else|else
name|name
operator|=
name|strrchr
argument_list|(
name|file_proc
operator|->
name|menu_paths
operator|->
name|data
argument_list|,
literal|'/'
argument_list|)
operator|+
literal|1
expr_stmt|;
name|filter
operator|=
name|gtk_file_filter_new
argument_list|()
expr_stmt|;
name|gtk_file_filter_set_name
argument_list|(
name|filter
argument_list|,
name|name
argument_list|)
expr_stmt|;
for|for
control|(
name|ext
operator|=
name|file_proc
operator|->
name|extensions_list
init|;
name|ext
condition|;
name|ext
operator|=
name|g_slist_next
argument_list|(
name|ext
argument_list|)
control|)
block|{
name|gchar
modifier|*
name|pattern
init|=
name|g_strdup_printf
argument_list|(
literal|"*.%s"
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|ext
operator|->
name|data
argument_list|)
decl_stmt|;
name|gtk_file_filter_add_pattern
argument_list|(
name|filter
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
block|}
name|gtk_file_chooser_add_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
block|}
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
name|GtkFileChooser
modifier|*
name|chooser
decl_stmt|;
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
name|chooser
operator|=
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_proc
operator|&&
name|file_proc
operator|->
name|extensions_list
operator|&&
name|gtk_file_chooser_get_action
argument_list|(
name|chooser
argument_list|)
operator|==
name|GTK_FILE_CHOOSER_ACTION_SAVE
condition|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|gtk_file_chooser_get_uri
argument_list|(
name|chooser
argument_list|)
decl_stmt|;
if|if
condition|(
name|uri
operator|&&
name|strlen
argument_list|(
name|uri
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|last_dot
init|=
name|strrchr
argument_list|(
name|uri
argument_list|,
literal|'.'
argument_list|)
decl_stmt|;
if|if
condition|(
name|last_dot
operator|!=
name|uri
condition|)
block|{
name|GString
modifier|*
name|s
init|=
name|g_string_new
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
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
name|uri
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
name|gtk_file_chooser_set_uri
argument_list|(
name|chooser
argument_list|,
name|s
operator|->
name|str
argument_list|)
expr_stmt|;
name|basename
operator|=
name|file_utils_uri_to_utf8_basename
argument_list|(
name|s
operator|->
name|str
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_current_name
argument_list|(
name|chooser
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
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
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_file_dialog_set_uri (GimpFileDialog * dialog,GimpImage * gimage,const gchar * uri)
name|gimp_file_dialog_set_uri
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|gchar
modifier|*
name|real_uri
init|=
name|NULL
decl_stmt|;
name|gboolean
name|is_folder
init|=
name|FALSE
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
name|gimage
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|gimp_image_get_filename
argument_list|(
name|gimage
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|gchar
modifier|*
name|dirname
init|=
name|g_path_get_dirname
argument_list|(
name|filename
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|real_uri
operator|=
name|g_filename_to_uri
argument_list|(
name|dirname
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
name|is_folder
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|uri
condition|)
block|{
name|real_uri
operator|=
name|g_strdup
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|current
init|=
name|g_get_current_dir
argument_list|()
decl_stmt|;
name|real_uri
operator|=
name|g_filename_to_uri
argument_list|(
name|current
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|current
argument_list|)
expr_stmt|;
name|is_folder
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|is_folder
condition|)
name|gtk_file_chooser_set_current_folder_uri
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|real_uri
argument_list|)
expr_stmt|;
else|else
name|gtk_file_chooser_set_uri
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|real_uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|real_uri
argument_list|)
expr_stmt|;
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
specifier|const
name|gchar
modifier|*
name|uri
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
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
name|gtk_file_chooser_set_uri
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
else|else
name|gtk_file_chooser_set_current_name
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_ui_manager_update
argument_list|(
name|dialog
operator|->
name|manager
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
DECL|function|gimp_file_dialog_selection_changed (GtkFileChooser * chooser,GimpFileDialog * dialog)
name|gimp_file_dialog_selection_changed
parameter_list|(
name|GtkFileChooser
modifier|*
name|chooser
parameter_list|,
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gimp_thumb_box_take_uris
argument_list|(
name|GIMP_THUMB_BOX
argument_list|(
name|dialog
operator|->
name|thumb_box
argument_list|)
argument_list|,
name|gtk_file_chooser_get_uris
argument_list|(
name|chooser
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_dialog_update_preview (GtkFileChooser * chooser,GimpFileDialog * dialog)
name|gimp_file_dialog_update_preview
parameter_list|(
name|GtkFileChooser
modifier|*
name|chooser
parameter_list|,
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|gtk_file_chooser_get_preview_uri
argument_list|(
name|chooser
argument_list|)
decl_stmt|;
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
end_function

end_unit

