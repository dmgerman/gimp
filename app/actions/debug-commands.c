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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpobject.h"
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
file|"debug-commands.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_DEBUG_ENTRIES
end_ifdef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|debug_dump_menus_recurse_menu
parameter_list|(
name|GtkWidget
modifier|*
name|menu
parameter_list|,
name|gint
name|depth
parameter_list|,
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|debug_dump_menus_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|debug_dump_menus_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
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
name|global_menu_factory
operator|->
name|registered_menus
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
name|GimpMenuFactoryEntry
modifier|*
name|entry
decl_stmt|;
name|GimpItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|entry
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|item_factory
operator|=
name|gimp_item_factory_from_path
argument_list|(
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_factory
condition|)
block|{
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|menu_item
operator|=
name|gtk_item_factory_get_item
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
name|entry
operator|->
name|entries
index|[
literal|0
index|]
operator|.
name|entry
operator|.
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu_item
operator|&&
name|menu_item
operator|->
name|parent
operator|&&
name|GTK_IS_MENU
argument_list|(
name|menu_item
operator|->
name|parent
argument_list|)
condition|)
name|debug_dump_menus_recurse_menu
argument_list|(
name|menu_item
operator|->
name|parent
argument_list|,
literal|1
argument_list|,
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|debug_mem_profile_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|debug_mem_profile_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
specifier|extern
name|gboolean
name|gimp_debug_memsize
decl_stmt|;
name|gimp_debug_memsize
operator|=
name|TRUE
expr_stmt|;
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_debug_memsize
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|debug_dump_menus_recurse_menu (GtkWidget * menu,gint depth,gchar * path)
name|debug_dump_menus_recurse_menu
parameter_list|(
name|GtkWidget
modifier|*
name|menu
parameter_list|,
name|gint
name|depth
parameter_list|,
name|gchar
modifier|*
name|path
parameter_list|)
block|{
name|GtkItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|help_page
decl_stmt|;
name|gchar
modifier|*
name|help_path
decl_stmt|;
name|gchar
modifier|*
name|factory_path
decl_stmt|;
name|gchar
modifier|*
name|hash
decl_stmt|;
name|gchar
modifier|*
name|full_path
decl_stmt|;
name|gchar
modifier|*
name|format_str
decl_stmt|;
for|for
control|(
name|list
operator|=
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
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
name|menu_item
operator|=
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|menu_item
argument_list|)
operator|->
name|child
argument_list|)
condition|)
block|{
name|label
operator|=
name|gtk_label_get_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|menu_item
argument_list|)
operator|->
name|child
argument_list|)
argument_list|)
expr_stmt|;
name|full_path
operator|=
name|g_strconcat
argument_list|(
name|path
argument_list|,
literal|"/"
argument_list|,
name|label
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item_factory
operator|=
name|GTK_ITEM_FACTORY
argument_list|(
name|gimp_item_factory_from_path
argument_list|(
name|path
argument_list|)
argument_list|)
expr_stmt|;
name|help_page
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|,
literal|"help_page"
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_factory
condition|)
block|{
name|factory_path
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"factory_path"
argument_list|)
expr_stmt|;
if|if
condition|(
name|factory_path
condition|)
block|{
name|help_page
operator|=
name|g_build_filename
argument_list|(
name|factory_path
argument_list|,
name|help_page
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|help_page
operator|=
name|g_strdup
argument_list|(
name|help_page
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|help_page
operator|=
name|g_strdup
argument_list|(
name|help_page
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|help_page
condition|)
block|{
name|help_path
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"help"
argument_list|,
literal|"C"
argument_list|,
name|help_page
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|hash
operator|=
name|strchr
argument_list|(
name|help_path
argument_list|,
literal|'#'
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
operator|*
name|hash
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|help_path
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|help_path
argument_list|)
expr_stmt|;
name|help_path
operator|=
name|g_strconcat
argument_list|(
literal|"! "
argument_list|,
name|help_page
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help_page
argument_list|)
expr_stmt|;
name|help_page
operator|=
name|help_path
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|help_path
argument_list|)
expr_stmt|;
block|}
block|}
name|format_str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%%%ds%%%ds %%-20s %%s\n"
argument_list|,
name|depth
operator|*
literal|2
argument_list|,
name|depth
operator|*
literal|2
operator|-
literal|40
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|format_str
argument_list|,
literal|""
argument_list|,
name|label
argument_list|,
literal|""
argument_list|,
name|help_page
condition|?
name|help_page
else|:
literal|""
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|format_str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help_page
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_MENU_ITEM
argument_list|(
name|menu_item
argument_list|)
operator|->
name|submenu
condition|)
name|debug_dump_menus_recurse_menu
argument_list|(
name|GTK_MENU_ITEM
argument_list|(
name|menu_item
argument_list|)
operator|->
name|submenu
argument_list|,
name|depth
operator|+
literal|1
argument_list|,
name|full_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|full_path
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  ENABLE_DEBUG_ENTRIES  */
end_comment

end_unit

