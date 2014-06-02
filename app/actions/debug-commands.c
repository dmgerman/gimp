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
file|<glib/gprintf.h>
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
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
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprojectable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprojection.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpaction.h"
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpimagewindow.h"
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
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|debug_show_image_graph
parameter_list|(
name|GimpImage
modifier|*
name|source_image
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

begin_function_decl
specifier|static
name|gboolean
name|debug_accel_find_func
parameter_list|(
name|GtkAccelKey
modifier|*
name|key
parameter_list|,
name|GClosure
modifier|*
name|closure
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
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
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
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|debug_show_image_graph_cmd_callback (GtkAction * action,gpointer data)
name|debug_show_image_graph_cmd_callback
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
name|source_image
init|=
name|NULL
decl_stmt|;
name|return_if_no_image
argument_list|(
name|source_image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|debug_show_image_graph
argument_list|,
name|g_object_ref
argument_list|(
name|source_image
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
name|gimp_menu_factory_get_registered_menus
argument_list|(
name|global_menu_factory
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
name|gimp_menu_factory_get_registered_menus
argument_list|(
name|global_menu_factory
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
DECL|function|debug_dump_keyboard_shortcuts_cmd_callback (GtkAction * action,gpointer data)
name|debug_dump_keyboard_shortcuts_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GimpImageWindow
modifier|*
name|window
decl_stmt|;
name|GtkUIManager
modifier|*
name|manager
decl_stmt|;
name|GtkAccelGroup
modifier|*
name|accel_group
decl_stmt|;
name|GList
modifier|*
name|group_it
decl_stmt|;
name|GList
modifier|*
name|strings
init|=
name|NULL
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|window
operator|=
name|gimp_display_shell_get_window
argument_list|(
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|=
name|GTK_UI_MANAGER
argument_list|(
name|gimp_image_window_get_ui_manager
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
name|accel_group
operator|=
name|gtk_ui_manager_get_accel_group
argument_list|(
name|manager
argument_list|)
expr_stmt|;
comment|/* Gather formated strings of keyboard shortcuts */
for|for
control|(
name|group_it
operator|=
name|gtk_ui_manager_get_action_groups
argument_list|(
name|manager
argument_list|)
init|;
name|group_it
condition|;
name|group_it
operator|=
name|g_list_next
argument_list|(
name|group_it
argument_list|)
control|)
block|{
name|GimpActionGroup
modifier|*
name|group
init|=
name|group_it
operator|->
name|data
decl_stmt|;
name|GList
modifier|*
name|actions
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|action_it
init|=
name|NULL
decl_stmt|;
name|actions
operator|=
name|gtk_action_group_list_actions
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|actions
operator|=
name|g_list_sort
argument_list|(
name|actions
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_action_name_compare
argument_list|)
expr_stmt|;
for|for
control|(
name|action_it
operator|=
name|actions
init|;
name|action_it
condition|;
name|action_it
operator|=
name|g_list_next
argument_list|(
name|action_it
argument_list|)
control|)
block|{
name|GtkAction
modifier|*
name|action
init|=
name|action_it
operator|->
name|data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gtk_action_get_name
argument_list|(
name|action
argument_list|)
decl_stmt|;
name|GClosure
modifier|*
name|accel_closure
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|strstr
argument_list|(
name|name
argument_list|,
literal|"-menu"
argument_list|)
operator|||
name|strstr
argument_list|(
name|name
argument_list|,
literal|"-popup"
argument_list|)
operator|||
name|name
index|[
literal|0
index|]
operator|==
literal|'<'
condition|)
continue|continue;
name|accel_closure
operator|=
name|gtk_action_get_accel_closure
argument_list|(
name|action
argument_list|)
expr_stmt|;
if|if
condition|(
name|accel_closure
condition|)
block|{
name|GtkAccelKey
modifier|*
name|key
init|=
name|gtk_accel_group_find
argument_list|(
name|accel_group
argument_list|,
name|debug_accel_find_func
argument_list|,
name|accel_closure
argument_list|)
decl_stmt|;
if|if
condition|(
name|key
operator|&&
name|key
operator|->
name|accel_key
operator|&&
name|key
operator|->
name|accel_flags
operator|&
name|GTK_ACCEL_VISIBLE
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|label_tmp
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|key_string
decl_stmt|;
name|label_tmp
operator|=
name|gtk_action_get_label
argument_list|(
name|action
argument_list|)
expr_stmt|;
name|label
operator|=
name|gimp_strip_uline
argument_list|(
name|label_tmp
argument_list|)
expr_stmt|;
name|key_string
operator|=
name|gtk_accelerator_get_label
argument_list|(
name|key
operator|->
name|accel_key
argument_list|,
name|key
operator|->
name|accel_mods
argument_list|)
expr_stmt|;
name|strings
operator|=
name|g_list_prepend
argument_list|(
name|strings
argument_list|,
name|g_strdup_printf
argument_list|(
literal|"%-20s %s"
argument_list|,
name|key_string
argument_list|,
name|label
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|key_string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|g_list_free
argument_list|(
name|actions
argument_list|)
expr_stmt|;
block|}
comment|/* Sort and prints the strings */
block|{
name|GList
modifier|*
name|string_it
init|=
name|NULL
decl_stmt|;
name|strings
operator|=
name|g_list_sort
argument_list|(
name|strings
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|strcmp
argument_list|)
expr_stmt|;
for|for
control|(
name|string_it
operator|=
name|strings
init|;
name|string_it
condition|;
name|string_it
operator|=
name|g_list_next
argument_list|(
name|string_it
argument_list|)
control|)
block|{
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|string_it
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|string_it
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|strings
argument_list|)
expr_stmt|;
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
DECL|function|debug_benchmark_projection (GimpDisplay * display)
name|debug_benchmark_projection
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpProjection
modifier|*
name|projection
init|=
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GIMP_TIMER_START
argument_list|()
expr_stmt|;
name|gimp_image_invalidate
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
name|gimp_display_flush_now
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|GIMP_TIMER_END
argument_list|(
literal|"Validation of the entire projection"
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|display
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|debug_show_image_graph (GimpImage * source_image)
name|debug_show_image_graph
parameter_list|(
name|GimpImage
modifier|*
name|source_image
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|source_image
operator|->
name|gimp
decl_stmt|;
name|GimpProjectable
modifier|*
name|projectable
init|=
name|GIMP_PROJECTABLE
argument_list|(
name|source_image
argument_list|)
decl_stmt|;
name|GeglNode
modifier|*
name|image_graph
init|=
name|gimp_projectable_get_graph
argument_list|(
name|projectable
argument_list|)
decl_stmt|;
name|GeglNode
modifier|*
name|output_node
init|=
name|gegl_node_get_output_proxy
argument_list|(
name|image_graph
argument_list|,
literal|"output"
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|new_image
init|=
name|NULL
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
init|=
name|NULL
decl_stmt|;
name|GeglNode
modifier|*
name|introspect
init|=
name|NULL
decl_stmt|;
name|GeglNode
modifier|*
name|sink
init|=
name|NULL
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|new_name
init|=
name|NULL
decl_stmt|;
comment|/* Setup and process the introspection graph */
name|introspect
operator|=
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:introspect"
argument_list|,
literal|"node"
argument_list|,
name|output_node
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sink
operator|=
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-sink"
argument_list|,
literal|"buffer"
argument_list|,
operator|&
name|buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_link_many
argument_list|(
name|introspect
argument_list|,
name|sink
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|sink
argument_list|)
expr_stmt|;
comment|/* Create a new image of the result */
name|new_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s GEGL graph"
argument_list|,
name|gimp_image_get_display_name
argument_list|(
name|source_image
argument_list|)
argument_list|)
expr_stmt|;
name|new_image
operator|=
name|gimp_create_image
argument_list|(
name|gimp
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|GIMP_RGB
argument_list|,
name|GIMP_PRECISION_U8_GAMMA
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_set_uri
argument_list|(
name|new_image
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new_from_buffer
argument_list|(
name|buffer
argument_list|,
name|new_image
argument_list|,
name|gimp_image_get_layer_format
argument_list|(
name|new_image
argument_list|,
name|TRUE
argument_list|)
argument_list|,
name|new_name
argument_list|,
literal|1.0
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|new_image
argument_list|,
name|layer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gimp
argument_list|,
name|new_image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Cleanup */
name|g_object_unref
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|new_name
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|sink
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|introspect
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|source_image
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
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|menu
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
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
name|GtkWidget
modifier|*
name|submenu
decl_stmt|;
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
name|submenu
operator|=
name|gtk_menu_item_get_submenu
argument_list|(
name|GTK_MENU_ITEM
argument_list|(
name|menu_item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|submenu
condition|)
name|debug_dump_menus_recurse_menu
argument_list|(
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
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
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

begin_function
specifier|static
name|gboolean
DECL|function|debug_accel_find_func (GtkAccelKey * key,GClosure * closure,gpointer data)
name|debug_accel_find_func
parameter_list|(
name|GtkAccelKey
modifier|*
name|key
parameter_list|,
name|GClosure
modifier|*
name|closure
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
operator|(
name|GClosure
operator|*
operator|)
name|data
operator|==
name|closure
return|;
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

