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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"menus/menus.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"debug-commands.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_DEBUG_MENU
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
DECL|function|debug_mem_profile_cmd_callback (GtkAction * action,gpointer data)
name|debug_mem_profile_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|extern
name|gboolean
name|gimp_debug_memsize
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_debug_memsize
operator|=
name|TRUE
expr_stmt|;
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_debug_memsize
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|debug_dump_menus_cmd_callback (GtkAction * action,gpointer data)
name|debug_dump_menus_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
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
if|#
directive|if
literal|0
block|FIXME       GimpMenuFactoryEntry *entry = list->data;       GimpItemFactory      *item_factory;        item_factory = gimp_item_factory_from_path (entry->identifier);        if (item_factory)         {           GtkWidget *menu_item;            g_print ("%s\n", entry->identifier);            menu_item = gtk_item_factory_get_item (GTK_ITEM_FACTORY (item_factory),                                                  entry->entries[0].entry.path);            if (menu_item&&               menu_item->parent&&               GTK_IS_MENU (menu_item->parent))             debug_dump_menus_recurse_menu (menu_item->parent, 1,                                            entry->identifier);            g_print ("\n");         }
endif|#
directive|endif
block|}
block|}
end_function

begin_function
name|void
DECL|function|debug_dump_managers_cmd_callback (GtkAction * action,gpointer data)
name|debug_dump_managers_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
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
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GList
modifier|*
name|managers
decl_stmt|;
name|managers
operator|=
name|gimp_ui_managers_from_name
argument_list|(
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
if|if
condition|(
name|managers
condition|)
block|{
name|g_print
argument_list|(
literal|"\n\n========================================\n"
literal|"UI Manager: %s\n"
literal|"========================================\n\n"
argument_list|,
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|gtk_ui_manager_get_ui
argument_list|(
name|managers
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
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
if|#
directive|if
literal|0
block|GtkItemFactory *item_factory;   GtkWidget      *menu_item;   GList          *list;   const gchar    *label;   gchar          *help_page;   gchar          *full_path;   gchar          *format_str;    for (list = GTK_MENU_SHELL (menu)->children; list; list = g_list_next (list))     {       menu_item = GTK_WIDGET (list->data);        if (GTK_IS_LABEL (GTK_BIN (menu_item)->child)) 	{ 	  label = gtk_label_get_text (GTK_LABEL (GTK_BIN (menu_item)->child)); 	  full_path = g_strconcat (path, "/", label, NULL);  	  item_factory = GTK_ITEM_FACTORY (gimp_item_factory_from_path (path));           help_page    = g_object_get_data (G_OBJECT (menu_item),                                             "gimp-help-id");            help_page = g_strdup (help_page);  	  format_str = g_strdup_printf ("%%%ds%%%ds %%-20s %%s\n", 					depth * 2, depth * 2 - 40); 	  g_print (format_str, 		   "", label, "", help_page ? help_page : ""); 	  g_free (format_str); 	  g_free (help_page);  	  if (GTK_MENU_ITEM (menu_item)->submenu) 	    debug_dump_menus_recurse_menu (GTK_MENU_ITEM (menu_item)->submenu,                                            depth + 1, full_path);  	  g_free (full_path); 	}     }
endif|#
directive|endif
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ENABLE_DEBUG_MENU */
end_comment

end_unit

