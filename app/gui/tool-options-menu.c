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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-commands.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-menu.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|tool_options_menu_entries
name|GimpItemFactoryEntry
name|tool_options_menu_entries
index|[]
init|=
block|{
block|{
block|{
name|N_
argument_list|(
literal|"/Save Options to/New Entry..."
argument_list|)
block|,
literal|""
block|,
name|tool_options_save_new_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_NEW
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_TOOL_OPTIONS_SAVE
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Save Options to/new-separator"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
literal|0
block|,
literal|"<Separator>"
block|,
name|NULL
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Restore Options from/(None)"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
literal|0
block|,
literal|"<Item>"
block|,
name|NULL
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Delete Saved Options/(None)"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
literal|0
block|,
literal|"<Item>"
block|,
name|NULL
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
block|{
literal|"/reset-separator"
block|,
name|NULL
block|,
name|NULL
block|,
literal|0
block|,
literal|"<Separator>"
block|,
name|NULL
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Reset Tool Options"
argument_list|)
block|,
literal|""
block|,
name|tool_options_reset_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_RESET
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_TOOL_OPTIONS_RESET
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Reset all Tool Options..."
argument_list|)
block|,
literal|""
block|,
name|tool_options_reset_all_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_RESET
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_TOOL_OPTIONS_RESET
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_tool_options_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|tool_options_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|tool_options_menu_setup (GimpItemFactory * factory)
name|tool_options_menu_setup
parameter_list|(
name|GimpItemFactory
modifier|*
name|factory
parameter_list|)
block|{
name|gimp_item_factory_set_sensitive
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
literal|"/Restore Options from/(None)"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
literal|"/Delete Saved Options/(None)"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_menu_update (GtkItemFactory * factory,gpointer data)
name|tool_options_menu_update
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GtkWidget
modifier|*
name|save_menu
decl_stmt|;
name|GtkWidget
modifier|*
name|restore_menu
decl_stmt|;
name|GtkWidget
modifier|*
name|delete_menu
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|GIMP_ITEM_FACTORY
argument_list|(
name|factory
argument_list|)
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
DECL|macro|SET_VISIBLE (menu,condition)
define|#
directive|define
name|SET_VISIBLE
parameter_list|(
name|menu
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_item_factory_set_visible (factory, menu, (condition) != 0)
name|SET_VISIBLE
argument_list|(
literal|"/Save Options to"
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Restore Options from"
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Delete Saved Options"
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/reset-separator"
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
operator|->
name|options_presets
condition|)
return|return;
name|save_menu
operator|=
name|gtk_item_factory_get_widget
argument_list|(
name|factory
argument_list|,
literal|"/Save Options to"
argument_list|)
expr_stmt|;
name|restore_menu
operator|=
name|gtk_item_factory_get_widget
argument_list|(
name|factory
argument_list|,
literal|"/Restore Options from"
argument_list|)
expr_stmt|;
name|delete_menu
operator|=
name|gtk_item_factory_get_widget
argument_list|(
name|factory
argument_list|,
literal|"/Delete Saved Options"
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_nth
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|save_menu
argument_list|)
operator|->
name|children
argument_list|,
literal|1
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_list_next
argument_list|(
name|list
argument_list|)
condition|)
name|gtk_widget_destroy
argument_list|(
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_nth
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|restore_menu
argument_list|)
operator|->
name|children
argument_list|,
literal|0
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_list_next
argument_list|(
name|list
argument_list|)
condition|)
name|gtk_widget_destroy
argument_list|(
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_nth
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|delete_menu
argument_list|)
operator|->
name|children
argument_list|,
literal|0
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_list_next
argument_list|(
name|list
argument_list|)
condition|)
name|gtk_widget_destroy
argument_list|(
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_container_num_children
argument_list|(
name|tool_info
operator|->
name|options_presets
argument_list|)
condition|)
block|{
name|GimpItemFactoryEntry
name|entry
decl_stmt|;
name|GimpToolOptions
modifier|*
name|options
decl_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Save Options to/new-separator"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Restore Options from/(None)"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Delete Saved Options/(None)"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|path
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|accelerator
operator|=
literal|""
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|callback
operator|=
name|tool_options_save_to_cmd_callback
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|callback_action
operator|=
literal|0
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|item_type
operator|=
literal|"<StockItem>"
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|extra_data
operator|=
name|GTK_STOCK_SAVE
expr_stmt|;
name|entry
operator|.
name|quark_string
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|GIMP_HELP_TOOL_OPTIONS_SAVE
expr_stmt|;
name|entry
operator|.
name|description
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|tool_info
operator|->
name|options_presets
argument_list|)
operator|->
name|list
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
name|options
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|path
operator|=
name|g_strdup_printf
argument_list|(
literal|"/Save Options to/%s"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|gimp_item_factory_create_item
argument_list|(
name|GIMP_ITEM_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
operator|&
name|entry
argument_list|,
name|NULL
argument_list|,
name|options
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|entry
operator|.
name|entry
operator|.
name|path
argument_list|)
expr_stmt|;
block|}
name|entry
operator|.
name|entry
operator|.
name|callback
operator|=
name|tool_options_restore_from_cmd_callback
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|extra_data
operator|=
name|GTK_STOCK_REVERT_TO_SAVED
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|GIMP_HELP_TOOL_OPTIONS_RESTORE
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|tool_info
operator|->
name|options_presets
argument_list|)
operator|->
name|list
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
name|options
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|path
operator|=
name|g_strdup_printf
argument_list|(
literal|"/Restore Options from/%s"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|gimp_item_factory_create_item
argument_list|(
name|GIMP_ITEM_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
operator|&
name|entry
argument_list|,
name|NULL
argument_list|,
name|options
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|entry
operator|.
name|entry
operator|.
name|path
argument_list|)
expr_stmt|;
block|}
name|entry
operator|.
name|entry
operator|.
name|callback
operator|=
name|tool_options_delete_saved_cmd_callback
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|extra_data
operator|=
name|GTK_STOCK_DELETE
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|GIMP_HELP_TOOL_OPTIONS_DELETE
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|tool_info
operator|->
name|options_presets
argument_list|)
operator|->
name|list
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
name|options
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|path
operator|=
name|g_strdup_printf
argument_list|(
literal|"/Delete Saved Options/%s"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|gimp_item_factory_create_item
argument_list|(
name|GIMP_ITEM_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
operator|&
name|entry
argument_list|,
name|NULL
argument_list|,
name|options
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|entry
operator|.
name|entry
operator|.
name|path
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|SET_VISIBLE
argument_list|(
literal|"/Save Options to/new-separator"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Restore Options from/(None)"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Delete Saved Options/(None)"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
undef|#
directive|undef
name|SET_VISIBLE
block|}
end_function

end_unit

