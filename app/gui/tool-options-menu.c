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

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|tool_options_menu_update_presets
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|gint
name|keep_n
parameter_list|,
name|gboolean
name|has_none
parameter_list|,
name|GtkItemFactoryCallback
name|callback
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
parameter_list|,
name|GimpContainer
modifier|*
name|presets
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  global variables  */
end_comment

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
literal|"/Rename Saved Options/(None)"
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

begin_comment
comment|/*  public functions  */
end_comment

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
literal|"/Rename Saved Options/(None)"
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

begin_define
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
end_define

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
literal|"/Rename Saved Options"
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
name|SET_VISIBLE
argument_list|(
literal|"/Save Options to/new-separator"
argument_list|,
name|gimp_container_num_children
argument_list|(
name|tool_info
operator|->
name|options_presets
argument_list|)
operator|>
literal|0
argument_list|)
expr_stmt|;
name|tool_options_menu_update_presets
argument_list|(
name|factory
argument_list|,
literal|"/Save Options to"
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|,
name|tool_options_save_to_cmd_callback
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_SAVE
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
name|tool_options_menu_update_presets
argument_list|(
name|factory
argument_list|,
literal|"/Restore Options from"
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
name|tool_options_restore_from_cmd_callback
argument_list|,
name|GTK_STOCK_REVERT_TO_SAVED
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_RESTORE
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
name|tool_options_menu_update_presets
argument_list|(
name|factory
argument_list|,
literal|"/Rename Saved Options"
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
name|tool_options_rename_saved_cmd_callback
argument_list|,
name|GIMP_STOCK_EDIT
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_RENAME
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
name|tool_options_menu_update_presets
argument_list|(
name|factory
argument_list|,
literal|"/Delete Saved Options"
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
name|tool_options_delete_saved_cmd_callback
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DELETE
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  privat function  */
end_comment

begin_function
specifier|static
name|void
DECL|function|tool_options_menu_update_presets (GtkItemFactory * factory,const gchar * menu_path,gint keep_n,gboolean has_none,GtkItemFactoryCallback callback,const gchar * stock_id,const gchar * help_id,GimpContainer * presets)
name|tool_options_menu_update_presets
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|gint
name|keep_n
parameter_list|,
name|gboolean
name|has_none
parameter_list|,
name|GtkItemFactoryCallback
name|callback
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
parameter_list|,
name|GimpContainer
modifier|*
name|presets
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|menu
operator|=
name|gtk_item_factory_get_widget
argument_list|(
name|factory
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|num_children
decl_stmt|;
name|list
operator|=
name|g_list_nth
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
argument_list|,
name|keep_n
operator|-
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
name|num_children
operator|=
name|gimp_container_num_children
argument_list|(
name|presets
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_none
condition|)
block|{
name|gchar
modifier|*
name|none
decl_stmt|;
name|none
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/(None)"
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
name|none
argument_list|,
name|num_children
operator|==
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|none
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|num_children
operator|>
literal|0
condition|)
block|{
name|GimpItemFactoryEntry
name|entry
decl_stmt|;
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
name|callback
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
name|stock_id
condition|?
literal|"<StockItem>"
else|:
literal|"<Item>"
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|extra_data
operator|=
name|stock_id
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
name|help_id
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
name|presets
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
name|GimpToolOptions
modifier|*
name|options
init|=
name|list
operator|->
name|data
decl_stmt|;
name|entry
operator|.
name|entry
operator|.
name|path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/%s"
argument_list|,
name|menu_path
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
block|}
block|}
end_function

begin_undef
undef|#
directive|undef
name|SET_VISIBLE
end_undef

end_unit

