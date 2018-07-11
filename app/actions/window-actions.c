begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"window-actions.h"
end_include

begin_include
include|#
directive|include
file|"window-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  private functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|window_actions_display_opened
parameter_list|(
name|GdkDisplayManager
modifier|*
name|manager
parameter_list|,
name|GdkDisplay
modifier|*
name|display
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|window_actions_display_closed
parameter_list|(
name|GdkDisplay
modifier|*
name|display
parameter_list|,
name|gboolean
name|is_error
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|window_actions_setup (GimpActionGroup * group,const gchar * move_to_screen_help_id)
name|window_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|move_to_screen_help_id
parameter_list|)
block|{
name|GdkDisplayManager
modifier|*
name|manager
init|=
name|gdk_display_manager_get
argument_list|()
decl_stmt|;
name|GSList
modifier|*
name|displays
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"move-to-screen-help-id"
argument_list|,
name|g_strdup
argument_list|(
name|move_to_screen_help_id
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"display-table"
argument_list|,
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|NULL
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_hash_table_unref
argument_list|)
expr_stmt|;
name|displays
operator|=
name|gdk_display_manager_list_displays
argument_list|(
name|manager
argument_list|)
expr_stmt|;
comment|/*  present displays in the order in which they were opened  */
name|displays
operator|=
name|g_slist_reverse
argument_list|(
name|displays
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|displays
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
name|window_actions_display_opened
argument_list|(
name|manager
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|displays
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|manager
argument_list|,
literal|"display-opened"
argument_list|,
name|G_CALLBACK
argument_list|(
name|window_actions_display_opened
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|window_actions_update (GimpActionGroup * group,GtkWidget * window)
name|window_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|GtkWidget
modifier|*
name|window
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|group_name
decl_stmt|;
name|gint
name|show_menu
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|group_name
operator|=
name|gtk_action_group_get_name
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
DECL|macro|SET_ACTIVE (action,active)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|active
parameter_list|)
define|\
value|gimp_action_group_set_action_active (group, action, (active) != 0)
DECL|macro|SET_VISIBLE (action,active)
define|#
directive|define
name|SET_VISIBLE
parameter_list|(
name|action
parameter_list|,
name|active
parameter_list|)
define|\
value|gimp_action_group_set_action_visible (group, action, (active) != 0)
if|if
condition|(
name|GTK_IS_WINDOW
argument_list|(
name|window
argument_list|)
condition|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|gchar
modifier|*
name|screen_name
decl_stmt|;
ifndef|#
directive|ifndef
name|GIMP_UNSTABLE
block|{
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|display
operator|=
name|gtk_widget_get_display
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|show_menu
operator|=
operator|(
name|gdk_display_get_n_screens
argument_list|(
name|display
argument_list|)
operator|>
literal|1
operator|)
expr_stmt|;
block|}
else|#
directive|else
name|show_menu
operator|=
name|TRUE
expr_stmt|;
endif|#
directive|endif
comment|/* !GIMP_UNSTABLE */
if|if
condition|(
operator|!
name|show_menu
condition|)
block|{
name|GdkDisplayManager
modifier|*
name|manager
init|=
name|gdk_display_manager_get
argument_list|()
decl_stmt|;
name|GSList
modifier|*
name|displays
decl_stmt|;
name|displays
operator|=
name|gdk_display_manager_list_displays
argument_list|(
name|manager
argument_list|)
expr_stmt|;
name|show_menu
operator|=
operator|(
name|displays
operator|->
name|next
operator|!=
name|NULL
operator|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|displays
argument_list|)
expr_stmt|;
block|}
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|screen_name
operator|=
name|gdk_screen_make_display_name
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-move-to-screen-%s"
argument_list|,
name|group_name
argument_list|,
name|screen_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|screen_name
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|name
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-move-to-screen-menu"
argument_list|,
name|group_name
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
name|name
argument_list|,
name|show_menu
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_ACTIVE
undef|#
directive|undef
name|SET_VISIBLE
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|window_actions_display_opened (GdkDisplayManager * manager,GdkDisplay * display,GimpActionGroup * group)
name|window_actions_display_opened
parameter_list|(
name|GdkDisplayManager
modifier|*
name|manager
parameter_list|,
name|GdkDisplay
modifier|*
name|display
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GimpRadioActionEntry
modifier|*
name|entries
decl_stmt|;
name|GHashTable
modifier|*
name|displays
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|display_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|group_name
decl_stmt|;
name|GSList
modifier|*
name|radio_group
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|gint
name|n_screens
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|displays
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"display-table"
argument_list|)
expr_stmt|;
name|display_name
operator|=
name|gdk_display_get_name
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|count
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_hash_table_lookup
argument_list|(
name|displays
argument_list|,
name|display_name
argument_list|)
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|displays
argument_list|,
name|g_strdup
argument_list|(
name|display_name
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|count
operator|+
literal|1
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  don't add the same display twice  */
if|if
condition|(
name|count
operator|>
literal|0
condition|)
return|return;
name|help_id
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"change-to-screen-help-id"
argument_list|)
expr_stmt|;
name|group_name
operator|=
name|gtk_action_group_get_name
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|n_screens
operator|=
name|gdk_display_get_n_screens
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|entries
operator|=
name|g_new0
argument_list|(
name|GimpRadioActionEntry
argument_list|,
name|n_screens
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_screens
condition|;
name|i
operator|++
control|)
block|{
name|GdkScreen
modifier|*
name|screen
init|=
name|gdk_display_get_screen
argument_list|(
name|display
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|screen_name
decl_stmt|;
name|screen_name
operator|=
name|gdk_screen_make_display_name
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-move-to-screen-%s"
argument_list|,
name|group_name
argument_list|,
name|screen_name
argument_list|)
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|icon_name
operator|=
name|GIMP_ICON_WINDOW_MOVE_TO_SCREEN
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|label
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Screen %s"
argument_list|)
argument_list|,
name|screen_name
argument_list|)
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|accelerator
operator|=
name|NULL
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|tooltip
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Move this window to "
literal|"screen %s"
argument_list|)
argument_list|,
name|screen_name
argument_list|)
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|value
operator|=
name|g_quark_from_string
argument_list|(
name|screen_name
argument_list|)
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|help_id
operator|=
name|help_id
expr_stmt|;
name|g_free
argument_list|(
name|screen_name
argument_list|)
expr_stmt|;
block|}
name|radio_group
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"change-to-screen-radio-group"
argument_list|)
expr_stmt|;
name|radio_group
operator|=
name|gimp_action_group_add_radio_actions
argument_list|(
name|group
argument_list|,
name|NULL
argument_list|,
name|entries
argument_list|,
name|n_screens
argument_list|,
name|radio_group
argument_list|,
literal|0
argument_list|,
name|G_CALLBACK
argument_list|(
name|window_move_to_screen_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"change-to-screen-radio-group"
argument_list|,
name|radio_group
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_screens
condition|;
name|i
operator|++
control|)
block|{
name|GdkScreen
modifier|*
name|screen
init|=
name|gdk_display_get_screen
argument_list|(
name|display
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"screen"
argument_list|,
name|screen
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|entries
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|entries
index|[
name|i
index|]
operator|.
name|tooltip
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|entries
index|[
name|i
index|]
operator|.
name|label
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|entries
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|display
argument_list|,
literal|"closed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|window_actions_display_closed
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|window_actions_display_closed (GdkDisplay * display,gboolean is_error,GimpActionGroup * group)
name|window_actions_display_closed
parameter_list|(
name|GdkDisplay
modifier|*
name|display
parameter_list|,
name|gboolean
name|is_error
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GHashTable
modifier|*
name|displays
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|display_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|group_name
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|gint
name|n_screens
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|displays
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"display-table"
argument_list|)
expr_stmt|;
name|display_name
operator|=
name|gdk_display_get_name
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|count
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_hash_table_lookup
argument_list|(
name|displays
argument_list|,
name|display_name
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  don't remove the same display twice  */
if|if
condition|(
name|count
operator|>
literal|1
condition|)
block|{
name|g_hash_table_insert
argument_list|(
name|displays
argument_list|,
name|g_strdup
argument_list|(
name|display_name
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|count
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_hash_table_remove
argument_list|(
name|displays
argument_list|,
name|display_name
argument_list|)
expr_stmt|;
name|group_name
operator|=
name|gtk_action_group_get_name
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|n_screens
operator|=
name|gdk_display_get_n_screens
argument_list|(
name|display
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_screens
condition|;
name|i
operator|++
control|)
block|{
name|GdkScreen
modifier|*
name|screen
init|=
name|gdk_display_get_screen
argument_list|(
name|display
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gchar
modifier|*
name|screen_name
decl_stmt|;
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|screen_name
operator|=
name|gdk_screen_make_display_name
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|action_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-move-to-screen-%s"
argument_list|,
name|group_name
argument_list|,
name|screen_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|screen_name
argument_list|)
expr_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
block|{
name|GSList
modifier|*
name|radio_group
decl_stmt|;
name|radio_group
operator|=
name|gtk_radio_action_get_group
argument_list|(
name|GTK_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|radio_group
operator|->
name|data
operator|==
operator|(
name|gpointer
operator|)
name|action
condition|)
name|radio_group
operator|=
name|radio_group
operator|->
name|next
expr_stmt|;
name|gtk_action_group_remove_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"change-to-screen-radio-group"
argument_list|,
name|radio_group
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

