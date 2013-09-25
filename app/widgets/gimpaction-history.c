begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2013  Jehan<jehan at girinstud.io>  *  * gimpaction-history.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<ctype.h>
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"gimpaction-history.h"
end_include

begin_define
DECL|macro|GIMP_ACTION_HISTORY_FILENAME
define|#
directive|define
name|GIMP_ACTION_HISTORY_FILENAME
value|"action_history"
end_define

begin_typedef
DECL|struct|__anon28d9c5510108
typedef|typedef
struct|struct
block|{
DECL|member|action
name|GtkAction
modifier|*
name|action
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|count
name|gint
name|count
decl_stmt|;
DECL|typedef|GimpActionHistoryItem
block|}
name|GimpActionHistoryItem
typedef|;
end_typedef

begin_struct
DECL|struct|__anon28d9c5510208
specifier|static
struct|struct
block|{
DECL|member|config
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
DECL|member|items
name|GList
modifier|*
name|items
decl_stmt|;
DECL|variable|history
block|}
name|history
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_action_history_item_free
parameter_list|(
name|GimpActionHistoryItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_action_history_init_compare_func
parameter_list|(
name|GimpActionHistoryItem
modifier|*
name|a
parameter_list|,
name|GimpActionHistoryItem
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_action_history_compare_func
parameter_list|(
name|GimpActionHistoryItem
modifier|*
name|a
parameter_list|,
name|GimpActionHistoryItem
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_action_insert
parameter_list|(
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
name|gint
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_action_history_init (GimpGuiConfig * config)
name|gimp_action_history_init
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
block|{
name|gchar
modifier|*
name|history_file_path
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|history
operator|.
name|items
operator|!=
name|NULL
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: must be run only once."
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return;
block|}
name|history
operator|.
name|config
operator|=
name|config
expr_stmt|;
name|history_file_path
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|GIMP_ACTION_HISTORY_FILENAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|history_file_path
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|fp
operator|==
name|NULL
condition|)
comment|/* Probably a first use case. Not necessarily an error. */
return|return;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|config
operator|->
name|action_history_size
condition|;
name|i
operator|++
control|)
block|{
comment|/* Let's assume an action name will never be more than 256 character. */
name|gchar
name|action_name
index|[
literal|256
index|]
decl_stmt|;
if|if
condition|(
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"%s %d"
argument_list|,
name|action_name
argument_list|,
operator|&
name|count
argument_list|)
operator|==
name|EOF
condition|)
break|break;
name|gimp_action_insert
argument_list|(
name|action_name
argument_list|,
name|count
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|count
operator|>
literal|1
condition|)
block|{
name|GList
modifier|*
name|actions
init|=
name|history
operator|.
name|items
decl_stmt|;
for|for
control|(
init|;
name|actions
operator|&&
name|i
condition|;
name|actions
operator|=
name|g_list_next
argument_list|(
name|actions
argument_list|)
operator|,
name|i
operator|--
control|)
block|{
name|GimpActionHistoryItem
modifier|*
name|action
init|=
name|actions
operator|->
name|data
decl_stmt|;
name|action
operator|->
name|count
operator|-=
name|count
operator|-
literal|1
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|history_file_path
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_action_history_exit (GimpGuiConfig * config)
name|gimp_action_history_exit
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
block|{
name|GList
modifier|*
name|actions
init|=
name|history
operator|.
name|items
decl_stmt|;
name|gchar
modifier|*
name|history_file_path
decl_stmt|;
name|gint
name|min_count
init|=
literal|0
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gint
name|i
init|=
name|config
operator|->
name|action_history_size
decl_stmt|;
comment|/* If we have more items than current history size, trim the history      and move down all count so that 1 is lower. */
for|for
control|(
init|;
name|actions
operator|&&
name|i
condition|;
name|actions
operator|=
name|g_list_next
argument_list|(
name|actions
argument_list|)
operator|,
name|i
operator|--
control|)
empty_stmt|;
if|if
condition|(
name|actions
condition|)
block|{
name|GimpActionHistoryItem
modifier|*
name|action
init|=
name|actions
operator|->
name|data
decl_stmt|;
name|min_count
operator|=
name|action
operator|->
name|count
operator|-
literal|1
expr_stmt|;
block|}
name|actions
operator|=
name|history
operator|.
name|items
expr_stmt|;
name|i
operator|=
name|config
operator|->
name|action_history_size
expr_stmt|;
name|history_file_path
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|GIMP_ACTION_HISTORY_FILENAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|history_file_path
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
for|for
control|(
init|;
name|actions
operator|&&
name|i
condition|;
name|actions
operator|=
name|g_list_next
argument_list|(
name|actions
argument_list|)
operator|,
name|i
operator|--
control|)
block|{
name|GimpActionHistoryItem
modifier|*
name|action
init|=
name|actions
operator|->
name|data
decl_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"%s %d \n"
argument_list|,
name|action
operator|->
name|name
argument_list|,
name|action
operator|->
name|count
operator|-
name|min_count
argument_list|)
expr_stmt|;
block|}
name|gimp_action_history_empty
argument_list|()
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|history_file_path
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* gimp_action_history_excluded_action:  *  * Returns whether an action should be excluded from history.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_action_history_excluded_action (const gchar * action_name)
name|gimp_action_history_excluded_action
parameter_list|(
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|)
block|{
return|return
operator|(
name|g_str_has_suffix
argument_list|(
name|action_name
argument_list|,
literal|"-menu"
argument_list|)
operator|||
name|g_str_has_suffix
argument_list|(
name|action_name
argument_list|,
literal|"-popup"
argument_list|)
operator|||
name|g_str_has_suffix
argument_list|(
name|action_name
argument_list|,
literal|"-set"
argument_list|)
operator|||
name|g_str_has_suffix
argument_list|(
name|action_name
argument_list|,
literal|"-accel"
argument_list|)
operator|||
name|g_str_has_prefix
argument_list|(
name|action_name
argument_list|,
literal|"context-"
argument_list|)
operator|||
name|g_str_has_prefix
argument_list|(
name|action_name
argument_list|,
literal|"plug-in-recent-"
argument_list|)
operator|||
name|g_strcmp0
argument_list|(
name|action_name
argument_list|,
literal|"plug-in-repeat"
argument_list|)
operator|==
literal|0
operator|||
name|g_strcmp0
argument_list|(
name|action_name
argument_list|,
literal|"plug-in-reshow"
argument_list|)
operator|==
literal|0
operator|||
name|g_strcmp0
argument_list|(
name|action_name
argument_list|,
literal|"help-action-search"
argument_list|)
operator|==
literal|0
operator|)
return|;
block|}
end_function

begin_comment
comment|/* Callback run on the `activate` signal of an action.    It allows us to log all used action. */
end_comment

begin_function
name|void
DECL|function|gimp_action_history_activate_callback (GtkAction * action,gpointer user_data)
name|gimp_action_history_activate_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GList
modifier|*
name|actions
decl_stmt|;
name|GimpActionHistoryItem
modifier|*
name|history_item
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|gint
name|previous_count
init|=
literal|0
decl_stmt|;
name|action_name
operator|=
name|gtk_action_get_name
argument_list|(
name|action
argument_list|)
expr_stmt|;
comment|/* Some specific actions are of no log interest. */
if|if
condition|(
name|gimp_action_history_excluded_action
argument_list|(
name|action_name
argument_list|)
condition|)
return|return;
for|for
control|(
name|actions
operator|=
name|history
operator|.
name|items
init|;
name|actions
condition|;
name|actions
operator|=
name|g_list_next
argument_list|(
name|actions
argument_list|)
control|)
block|{
name|history_item
operator|=
name|actions
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|g_strcmp0
argument_list|(
name|action_name
argument_list|,
name|history_item
operator|->
name|name
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GimpActionHistoryItem
modifier|*
name|next_history_item
init|=
name|g_list_next
argument_list|(
name|actions
argument_list|)
condition|?
name|g_list_next
argument_list|(
name|actions
argument_list|)
operator|->
name|data
else|:
name|NULL
decl_stmt|;
comment|/* Is there any other item with the same count?              We don't want to leave any count gap to always accept new items.              This means that if we increment the only item with a given count,              we must decrement the next item.              Other consequence is that an item with higher count won't be              incremented at all if no other items have the same count. */
if|if
condition|(
name|previous_count
operator|==
name|history_item
operator|->
name|count
operator|||
operator|(
name|next_history_item
operator|&&
name|next_history_item
operator|->
name|count
operator|==
name|history_item
operator|->
name|count
operator|)
condition|)
block|{
name|history_item
operator|->
name|count
operator|++
expr_stmt|;
comment|/* Remove then reinsert to reorder. */
name|history
operator|.
name|items
operator|=
name|g_list_remove
argument_list|(
name|history
operator|.
name|items
argument_list|,
name|history_item
argument_list|)
expr_stmt|;
name|history
operator|.
name|items
operator|=
name|g_list_insert_sorted
argument_list|(
name|history
operator|.
name|items
argument_list|,
name|history_item
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_action_history_compare_func
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|previous_count
operator|!=
literal|0
operator|&&
name|previous_count
operator|!=
name|history_item
operator|->
name|count
condition|)
block|{
name|GimpActionHistoryItem
modifier|*
name|previous_history_item
init|=
name|g_list_previous
argument_list|(
name|actions
argument_list|)
operator|->
name|data
decl_stmt|;
name|history_item
operator|->
name|count
operator|++
expr_stmt|;
comment|/* Remove then reinsert to reorder. */
name|history
operator|.
name|items
operator|=
name|g_list_remove
argument_list|(
name|history
operator|.
name|items
argument_list|,
name|history_item
argument_list|)
expr_stmt|;
name|history
operator|.
name|items
operator|=
name|g_list_insert_sorted
argument_list|(
name|history
operator|.
name|items
argument_list|,
name|history_item
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_action_history_compare_func
argument_list|)
expr_stmt|;
name|previous_history_item
operator|->
name|count
operator|--
expr_stmt|;
comment|/* Remove then reinsert to reorder. */
name|history
operator|.
name|items
operator|=
name|g_list_remove
argument_list|(
name|history
operator|.
name|items
argument_list|,
name|previous_history_item
argument_list|)
expr_stmt|;
name|history
operator|.
name|items
operator|=
name|g_list_insert_sorted
argument_list|(
name|history
operator|.
name|items
argument_list|,
name|previous_history_item
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_action_history_compare_func
argument_list|)
expr_stmt|;
block|}
return|return;
block|}
name|previous_count
operator|=
name|history_item
operator|->
name|count
expr_stmt|;
block|}
comment|/* If we are here, this action is not logged yet. */
name|history_item
operator|=
name|g_malloc0
argument_list|(
sizeof|sizeof
argument_list|(
name|GimpActionHistoryItem
argument_list|)
argument_list|)
expr_stmt|;
name|history_item
operator|->
name|action
operator|=
name|g_object_ref
argument_list|(
name|action
argument_list|)
expr_stmt|;
name|history_item
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
name|history_item
operator|->
name|count
operator|=
literal|1
expr_stmt|;
name|history
operator|.
name|items
operator|=
name|g_list_insert_sorted
argument_list|(
name|history
operator|.
name|items
argument_list|,
name|history_item
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_action_history_compare_func
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_action_history_empty (void)
name|gimp_action_history_empty
parameter_list|(
name|void
parameter_list|)
block|{
name|g_list_free_full
argument_list|(
name|history
operator|.
name|items
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_action_history_item_free
argument_list|)
expr_stmt|;
name|history
operator|.
name|items
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Search all history actions which match "keyword"    with function match_func(action, keyword).     @return a list of GtkAction*, to free with:    g_list_free_full (result, (GDestroyNotify) g_object_unref);   */
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_action_history_search (const gchar * keyword,GimpActionMatchFunc match_func,GimpGuiConfig * config)
name|gimp_action_history_search
parameter_list|(
specifier|const
name|gchar
modifier|*
name|keyword
parameter_list|,
name|GimpActionMatchFunc
name|match_func
parameter_list|,
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
block|{
name|GList
modifier|*
name|actions
decl_stmt|;
name|GimpActionHistoryItem
modifier|*
name|history_item
decl_stmt|;
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|GList
modifier|*
name|search_result
init|=
name|NULL
decl_stmt|;
name|gint
name|i
init|=
name|config
operator|->
name|action_history_size
decl_stmt|;
for|for
control|(
name|actions
operator|=
name|history
operator|.
name|items
init|;
name|actions
operator|&&
name|i
condition|;
name|actions
operator|=
name|g_list_next
argument_list|(
name|actions
argument_list|)
operator|,
name|i
operator|--
control|)
block|{
name|history_item
operator|=
name|actions
operator|->
name|data
expr_stmt|;
name|action
operator|=
name|history_item
operator|->
name|action
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_action_get_sensitive
argument_list|(
name|action
argument_list|)
operator|&&
operator|!
name|config
operator|->
name|search_show_unavailable
condition|)
continue|continue;
if|if
condition|(
name|match_func
argument_list|(
name|action
argument_list|,
name|keyword
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
condition|)
name|search_result
operator|=
name|g_list_prepend
argument_list|(
name|search_result
argument_list|,
name|g_object_ref
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|g_list_reverse
argument_list|(
name|search_result
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_action_history_item_free (GimpActionHistoryItem * item)
name|gimp_action_history_item_free
parameter_list|(
name|GimpActionHistoryItem
modifier|*
name|item
parameter_list|)
block|{
name|g_object_unref
argument_list|(
name|item
operator|->
name|action
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|item
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Compare function used at list initialization.    We use a slightly different compare function as for runtime insert,    because we want to keep history file order for equal values. */
end_comment

begin_function
specifier|static
name|gint
DECL|function|gimp_action_history_init_compare_func (GimpActionHistoryItem * a,GimpActionHistoryItem * b)
name|gimp_action_history_init_compare_func
parameter_list|(
name|GimpActionHistoryItem
modifier|*
name|a
parameter_list|,
name|GimpActionHistoryItem
modifier|*
name|b
parameter_list|)
block|{
return|return
operator|(
name|a
operator|->
name|count
operator|<=
name|b
operator|->
name|count
operator|)
return|;
block|}
end_function

begin_comment
comment|/* Compare function used when updating the list.    There is no equality case. If they have the same count,    I ensure that the first action (last inserted) will be before. */
end_comment

begin_function
specifier|static
name|gint
DECL|function|gimp_action_history_compare_func (GimpActionHistoryItem * a,GimpActionHistoryItem * b)
name|gimp_action_history_compare_func
parameter_list|(
name|GimpActionHistoryItem
modifier|*
name|a
parameter_list|,
name|GimpActionHistoryItem
modifier|*
name|b
parameter_list|)
block|{
return|return
operator|(
name|a
operator|->
name|count
operator|<
name|b
operator|->
name|count
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_insert (const gchar * action_name,gint count)
name|gimp_action_insert
parameter_list|(
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
name|GList
modifier|*
name|action_groups
decl_stmt|;
name|GimpUIManager
modifier|*
name|manager
decl_stmt|;
comment|/* We do not insert some categories of actions. */
if|if
condition|(
name|gimp_action_history_excluded_action
argument_list|(
name|action_name
argument_list|)
condition|)
return|return;
name|manager
operator|=
name|gimp_ui_managers_from_name
argument_list|(
literal|"<Image>"
argument_list|)
operator|->
name|data
expr_stmt|;
for|for
control|(
name|action_groups
operator|=
name|gtk_ui_manager_get_action_groups
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
init|;
name|action_groups
condition|;
name|action_groups
operator|=
name|g_list_next
argument_list|(
name|action_groups
argument_list|)
control|)
block|{
name|GimpActionGroup
modifier|*
name|group
init|=
name|action_groups
operator|->
name|data
decl_stmt|;
name|GList
modifier|*
name|actions
decl_stmt|;
name|GList
modifier|*
name|list2
decl_stmt|;
name|gboolean
name|found
init|=
name|FALSE
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
name|list2
operator|=
name|actions
init|;
name|list2
condition|;
name|list2
operator|=
name|g_list_next
argument_list|(
name|list2
argument_list|)
control|)
block|{
name|GtkAction
modifier|*
name|action
init|=
name|list2
operator|->
name|data
decl_stmt|;
name|gint
name|unavailable_action
init|=
operator|-
literal|1
decl_stmt|;
name|unavailable_action
operator|=
name|strcmp
argument_list|(
name|action_name
argument_list|,
name|gtk_action_get_name
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unavailable_action
operator|==
literal|0
condition|)
block|{
comment|/* We found our action. */
name|GimpActionHistoryItem
modifier|*
name|new_action
init|=
name|g_malloc0
argument_list|(
sizeof|sizeof
argument_list|(
name|GimpActionHistoryItem
argument_list|)
argument_list|)
decl_stmt|;
name|new_action
operator|->
name|action
operator|=
name|g_object_ref
argument_list|(
name|action
argument_list|)
expr_stmt|;
name|new_action
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
name|new_action
operator|->
name|count
operator|=
name|count
expr_stmt|;
name|history
operator|.
name|items
operator|=
name|g_list_insert_sorted
argument_list|(
name|history
operator|.
name|items
argument_list|,
name|new_action
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_action_history_init_compare_func
argument_list|)
expr_stmt|;
name|found
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
elseif|else
if|if
condition|(
name|unavailable_action
operator|<
literal|0
condition|)
block|{
comment|/* Since the actions list is sorted, it means we passed                  all possible actions already and it is not in this group. */
break|break;
block|}
block|}
name|g_list_free
argument_list|(
name|actions
argument_list|)
expr_stmt|;
if|if
condition|(
name|found
condition|)
break|break;
block|}
block|}
end_function

end_unit

