begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"plug-in/plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"file-dialog-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GtkWidget
modifier|*
DECL|function|file_dialog_new (Gimp * gimp,GimpDialogFactory * dialog_factory,const gchar * dialog_identifier,GimpMenuFactory * menu_factory,const gchar * menu_identifier,const gchar * title,const gchar * role,const gchar * help_id,GCallback ok_callback)
name|file_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_identifier
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
name|help_id
parameter_list|,
name|GCallback
name|ok_callback
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|filesel
decl_stmt|;
name|GtkFileSelection
modifier|*
name|fs
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
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|dialog_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dialog_identifier
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
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|ok_callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|filesel
operator|=
name|gtk_file_selection_new
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|fs
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|filesel
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|filesel
argument_list|)
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
name|role
argument_list|)
expr_stmt|;
name|gimp_help_connect
argument_list|(
name|filesel
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|help_id
argument_list|,
name|NULL
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
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|filesel
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|fs
operator|->
name|cancel_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_dialog_hide
argument_list|)
argument_list|,
name|filesel
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|filesel
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_dialog_hide
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|fs
operator|->
name|ok_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|ok_callback
argument_list|)
argument_list|,
name|filesel
argument_list|)
expr_stmt|;
comment|/*  The file type menu  */
block|{
name|GimpItemFactory
modifier|*
name|item_factory
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
name|fs
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
name|gimp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|filesel
argument_list|)
argument_list|,
literal|"gimp-item-factory"
argument_list|,
name|item_factory
argument_list|)
expr_stmt|;
name|option_menu
operator|=
name|gtk_option_menu_new
argument_list|()
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
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|option_menu
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_object_unref
argument_list|,
name|item_factory
argument_list|)
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
name|item_factory
argument_list|)
operator|->
name|widget
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
block|}
name|gimp_dialog_factory_add_foreign
argument_list|(
name|dialog_factory
argument_list|,
name|dialog_identifier
argument_list|,
name|filesel
argument_list|)
expr_stmt|;
return|return
name|filesel
return|;
block|}
end_function

begin_function
name|void
DECL|function|file_dialog_show (GtkWidget * filesel,GtkWidget * parent)
name|file_dialog_show
parameter_list|(
name|GtkWidget
modifier|*
name|filesel
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Toolbox>"
argument_list|,
literal|"/File/Open..."
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Open..."
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save as..."
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save a Copy..."
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesel
argument_list|)
operator|->
name|selection_entry
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|file_dialog_hide (GtkWidget * filesel)
name|file_dialog_hide
parameter_list|(
name|GtkWidget
modifier|*
name|filesel
parameter_list|)
block|{
name|gtk_widget_hide
argument_list|(
name|filesel
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Toolbox>"
argument_list|,
literal|"/File/Open..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Open..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save as..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save a Copy..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  return TRUE because we are used as "delete_event" handler  */
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|file_dialog_update_name (PlugInProcDef * proc,GtkFileSelection * filesel)
name|file_dialog_update_name
parameter_list|(
name|PlugInProcDef
modifier|*
name|proc
parameter_list|,
name|GtkFileSelection
modifier|*
name|filesel
parameter_list|)
block|{
if|if
condition|(
name|proc
operator|->
name|extensions_list
condition|)
block|{
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
name|filesel
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
name|proc
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
name|filesel
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

end_unit

