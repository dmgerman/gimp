begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * extension-dialog.c  * Copyright (C) 2018 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo-gobject.h>
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpextensionmanager.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpextension.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpextensiondetails.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpextensionlist.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpprefsbox.h"
end_include

begin_include
include|#
directive|include
file|"extensions-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GIMP_EXTENSION_LIST_STACK_CHILD
define|#
directive|define
name|GIMP_EXTENSION_LIST_STACK_CHILD
value|"extension-list"
end_define

begin_define
DECL|macro|GIMP_EXTENSION_DETAILS_STACK_CHILD
define|#
directive|define
name|GIMP_EXTENSION_DETAILS_STACK_CHILD
value|"extension-details"
end_define

begin_function_decl
specifier|static
name|void
name|extensions_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|extensions_dialog_search_activate
parameter_list|(
name|GtkEntry
modifier|*
name|entry
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|extensions_dialog_search_icon_pressed
parameter_list|(
name|GtkEntry
modifier|*
name|entry
parameter_list|,
name|GtkEntryIconPosition
name|icon_pos
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|extensions_dialog_extension_activated
parameter_list|(
name|GimpExtensionList
modifier|*
name|list
parameter_list|,
name|GimpExtension
modifier|*
name|extension
parameter_list|,
name|GtkStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|extensions_dialog_back_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GtkStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public function  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|extensions_dialog_new (Gimp * gimp)
name|extensions_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|stack
decl_stmt|;
name|GtkWidget
modifier|*
name|stacked
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|list
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkTreeIter
name|top_iter
decl_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Extensions"
argument_list|)
argument_list|,
literal|"gimp-extensions"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_EXTENSIONS_DIALOG
argument_list|,
name|_
argument_list|(
literal|"_OK"
argument_list|)
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
name|extensions_dialog_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|stack
operator|=
name|gtk_stack_new
argument_list|()
expr_stmt|;
name|gtk_stack_set_transition_type
argument_list|(
name|GTK_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|GTK_STACK_TRANSITION_TYPE_SLIDE_RIGHT
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|stack
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
name|stack
argument_list|)
expr_stmt|;
comment|/* The extension lists. */
name|stacked
operator|=
name|gimp_prefs_box_new
argument_list|()
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|stacked
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_stack_add_named
argument_list|(
name|GTK_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|stacked
argument_list|,
name|GIMP_EXTENSION_LIST_STACK_CHILD
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|stacked
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_prefs_box_add_page
argument_list|(
name|GIMP_PREFS_BOX
argument_list|(
name|stacked
argument_list|)
argument_list|,
literal|"system-software-install"
argument_list|,
comment|/*"gimp-extensions-installed",*/
name|_
argument_list|(
literal|"Installed Extensions"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Installed Extensions"
argument_list|)
argument_list|,
name|GIMP_HELP_EXTENSIONS_INSTALLED
argument_list|,
name|NULL
argument_list|,
operator|&
name|top_iter
argument_list|)
expr_stmt|;
name|list
operator|=
name|gimp_extension_list_new
argument_list|(
name|gimp
operator|->
name|extension_manager
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|list
argument_list|,
literal|"extension-activated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|extensions_dialog_extension_activated
argument_list|)
argument_list|,
name|stack
argument_list|)
expr_stmt|;
name|gimp_extension_list_show_user
argument_list|(
name|GIMP_EXTENSION_LIST
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|list
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_prefs_box_add_page
argument_list|(
name|GIMP_PREFS_BOX
argument_list|(
name|stacked
argument_list|)
argument_list|,
literal|"system-software-install"
argument_list|,
name|_
argument_list|(
literal|"System Extensions"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"System Extensions"
argument_list|)
argument_list|,
name|GIMP_HELP_EXTENSIONS_SYSTEM
argument_list|,
name|NULL
argument_list|,
operator|&
name|top_iter
argument_list|)
expr_stmt|;
name|list
operator|=
name|gimp_extension_list_new
argument_list|(
name|gimp
operator|->
name|extension_manager
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|list
argument_list|,
literal|"extension-activated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|extensions_dialog_extension_activated
argument_list|)
argument_list|,
name|stack
argument_list|)
expr_stmt|;
name|gimp_extension_list_show_system
argument_list|(
name|GIMP_EXTENSION_LIST
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|list
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_prefs_box_add_page
argument_list|(
name|GIMP_PREFS_BOX
argument_list|(
name|stacked
argument_list|)
argument_list|,
literal|"system-software-install"
argument_list|,
name|_
argument_list|(
literal|"Install Extensions"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Install Extensions"
argument_list|)
argument_list|,
name|GIMP_HELP_EXTENSIONS_INSTALL
argument_list|,
name|NULL
argument_list|,
operator|&
name|top_iter
argument_list|)
expr_stmt|;
name|list
operator|=
name|gimp_extension_list_new
argument_list|(
name|gimp
operator|->
name|extension_manager
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|list
argument_list|,
literal|"extension-activated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|extensions_dialog_extension_activated
argument_list|)
argument_list|,
name|stack
argument_list|)
expr_stmt|;
name|gimp_extension_list_show_search
argument_list|(
name|GIMP_EXTENSION_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|list
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Search extension:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|widget
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_entry_set_icon_from_icon_name
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
literal|"edit-find"
argument_list|)
expr_stmt|;
name|gtk_entry_set_icon_activatable
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_icon_sensitive
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_icon_tooltip_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
name|_
argument_list|(
literal|"Search extensions matching these keywords"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|extensions_dialog_search_activate
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"icon-press"
argument_list|,
name|G_CALLBACK
argument_list|(
name|extensions_dialog_search_icon_pressed
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|widget
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
comment|/* The extension details. */
name|stacked
operator|=
name|gimp_extension_details_new
argument_list|()
expr_stmt|;
name|gtk_stack_add_named
argument_list|(
name|GTK_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|stacked
argument_list|,
name|GIMP_EXTENSION_DETAILS_STACK_CHILD
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|stacked
argument_list|)
expr_stmt|;
name|gtk_stack_set_visible_child_name
argument_list|(
name|GTK_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|GIMP_EXTENSION_LIST_STACK_CHILD
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
DECL|function|extensions_dialog_response (GtkWidget * widget,gint response_id,GtkWidget * dialog)
name|extensions_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|extensions_dialog_search_activate (GtkEntry * entry,gpointer user_data)
name|extensions_dialog_search_activate
parameter_list|(
name|GtkEntry
modifier|*
name|entry
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpExtensionList
modifier|*
name|list
init|=
name|user_data
decl_stmt|;
name|gimp_extension_list_show_search
argument_list|(
name|list
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|extensions_dialog_search_icon_pressed (GtkEntry * entry,GtkEntryIconPosition icon_pos,GdkEvent * event,gpointer user_data)
name|extensions_dialog_search_icon_pressed
parameter_list|(
name|GtkEntry
modifier|*
name|entry
parameter_list|,
name|GtkEntryIconPosition
name|icon_pos
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|extensions_dialog_search_activate
argument_list|(
name|entry
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|extensions_dialog_extension_activated (GimpExtensionList * list,GimpExtension * extension,GtkStack * stack)
name|extensions_dialog_extension_activated
parameter_list|(
name|GimpExtensionList
modifier|*
name|list
parameter_list|,
name|GimpExtension
modifier|*
name|extension
parameter_list|,
name|GtkStack
modifier|*
name|stack
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
init|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|stack
argument_list|)
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|header_bar
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
comment|/* Add a back button to the header bar. */
name|header_bar
operator|=
name|gtk_window_get_titlebar
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gtk_button_new_from_icon_name
argument_list|(
literal|"go-previous"
argument_list|,
name|GTK_ICON_SIZE_SMALL_TOOLBAR
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|extensions_dialog_back_button_clicked
argument_list|)
argument_list|,
name|stack
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_header_bar_pack_start
argument_list|(
name|GTK_HEADER_BAR
argument_list|(
name|header_bar
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
comment|/* Show the details of the extension. */
name|widget
operator|=
name|gtk_stack_get_child_by_name
argument_list|(
name|stack
argument_list|,
name|GIMP_EXTENSION_DETAILS_STACK_CHILD
argument_list|)
expr_stmt|;
name|gimp_extension_details_set
argument_list|(
name|GIMP_EXTENSION_DETAILS
argument_list|(
name|widget
argument_list|)
argument_list|,
name|extension
argument_list|)
expr_stmt|;
name|gtk_stack_set_visible_child_name
argument_list|(
name|stack
argument_list|,
name|GIMP_EXTENSION_DETAILS_STACK_CHILD
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|extensions_dialog_back_button_clicked (GtkButton * button,GtkStack * stack)
name|extensions_dialog_back_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GtkStack
modifier|*
name|stack
parameter_list|)
block|{
name|gtk_stack_set_visible_child_name
argument_list|(
name|stack
argument_list|,
name|GIMP_EXTENSION_LIST_STACK_CHILD
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

