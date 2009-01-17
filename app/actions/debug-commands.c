begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"base/tile.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprojection.h"
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
name|gboolean
name|debug_benchmark_projection
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

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

begin_function_decl
specifier|static
name|void
name|debug_print_qdata
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|debug_print_qdata_foreach
parameter_list|(
name|GQuark
name|key_id
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
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
DECL|function|debug_benchmark_projection_cmd_callback (GtkAction * action,gpointer data)
name|debug_benchmark_projection_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|debug_benchmark_projection
argument_list|,
name|g_object_ref
argument_list|(
name|image
argument_list|)
argument_list|)
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
name|GimpUIManager
modifier|*
name|manager
init|=
name|managers
operator|->
name|data
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|registered_uis
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
name|GimpUIManagerUIEntry
modifier|*
name|ui_entry
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|GTK_IS_MENU_SHELL
argument_list|(
name|ui_entry
operator|->
name|widget
argument_list|)
condition|)
block|{
name|g_print
argument_list|(
literal|"\n\n"
literal|"========================================\n"
literal|"Menu: %s%s\n"
literal|"========================================\n\n"
argument_list|,
name|entry
operator|->
name|identifier
argument_list|,
name|ui_entry
operator|->
name|ui_path
argument_list|)
expr_stmt|;
name|debug_dump_menus_recurse_menu
argument_list|(
name|ui_entry
operator|->
name|widget
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
literal|"\n\n"
literal|"========================================\n"
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
literal|"%s\n"
argument_list|,
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

begin_function
name|void
DECL|function|debug_dump_attached_data_cmd_callback (GtkAction * action,gpointer data)
name|debug_dump_attached_data_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|action_data_get_gimp
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|user_context
init|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|debug_print_qdata
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|debug_print_qdata
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|user_context
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
name|gboolean
DECL|function|debug_benchmark_projection (GimpImage * image)
name|debug_benchmark_projection
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpProjection
modifier|*
name|projection
init|=
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|GTimer
modifier|*
name|timer
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gimp_image_update
argument_list|(
name|image
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_projection_flush_now
argument_list|(
name|projection
argument_list|)
expr_stmt|;
name|tiles
operator|=
name|gimp_pickable_get_tiles
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|projection
argument_list|)
argument_list|)
expr_stmt|;
name|timer
operator|=
name|g_timer_new
argument_list|()
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
condition|;
name|x
operator|+=
name|TILE_WIDTH
control|)
block|{
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
condition|;
name|y
operator|+=
name|TILE_HEIGHT
control|)
block|{
name|Tile
modifier|*
name|tile
init|=
name|tile_manager_get_tile
argument_list|(
name|tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|tile_release
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
name|g_print
argument_list|(
literal|"Validation of the entire projection took %.0f ms\n"
argument_list|,
literal|1000
operator|*
name|g_timer_elapsed
argument_list|(
name|timer
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_timer_destroy
argument_list|(
name|timer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

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
name|GList
modifier|*
name|list
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
name|GtkWidget
modifier|*
name|menu_item
init|=
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|child
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|menu_item
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|child
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|full_path
decl_stmt|;
name|gchar
modifier|*
name|help_page
decl_stmt|;
name|gchar
modifier|*
name|format_str
decl_stmt|;
name|label
operator|=
name|gtk_label_get_text
argument_list|(
name|GTK_LABEL
argument_list|(
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
name|help_page
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|,
literal|"gimp-help-id"
argument_list|)
expr_stmt|;
name|help_page
operator|=
name|g_strdup
argument_list|(
name|help_page
argument_list|)
expr_stmt|;
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

begin_function
specifier|static
name|void
DECL|function|debug_print_qdata (GimpObject * object)
name|debug_print_qdata
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|g_print
argument_list|(
literal|"\nData attached to '%s':\n\n"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|g_datalist_foreach
argument_list|(
operator|&
name|G_OBJECT
argument_list|(
name|object
argument_list|)
operator|->
name|qdata
argument_list|,
name|debug_print_qdata_foreach
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|debug_print_qdata_foreach (GQuark key_id,gpointer data,gpointer user_data)
name|debug_print_qdata_foreach
parameter_list|(
name|GQuark
name|key_id
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|g_print
argument_list|(
literal|"%s: %p\n"
argument_list|,
name|g_quark_to_string
argument_list|(
name|key_id
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
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

