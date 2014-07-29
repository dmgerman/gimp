begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpaction-history.c  * Copyright (C) 2013  Jehan<jehan at girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
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
file|"core/gimp.h"
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
value|"action-history"
end_define

begin_enum
enum|enum
DECL|enum|__anon287adf150103
block|{
DECL|enumerator|HISTORY_ITEM
name|HISTORY_ITEM
init|=
literal|1
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon287adf150208
block|{
DECL|member|action
name|GtkAction
modifier|*
name|action
decl_stmt|;
DECL|member|name
specifier|const
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
specifier|static
struct|struct
DECL|struct|__anon287adf150308
block|{
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
name|GimpActionHistoryItem
modifier|*
name|gimp_action_history_item_new
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|count
parameter_list|)
function_decl|;
end_function_decl

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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_action_history_init (Gimp * gimp)
name|gimp_action_history_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|GimpUIManager
modifier|*
name|manager
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|gint
name|n_items
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
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
name|file
operator|=
name|gimp_directory_file
argument_list|(
name|GIMP_ACTION_HISTORY_FILENAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|scanner
operator|=
name|gimp_scanner_new_gfile
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|scanner
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
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
literal|"history-item"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|HISTORY_ITEM
argument_list|)
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|token
condition|)
block|{
case|case
name|G_TOKEN_LEFT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_SYMBOL
expr_stmt|;
break|break;
case|case
name|G_TOKEN_SYMBOL
case|:
if|if
condition|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
operator|==
name|GINT_TO_POINTER
argument_list|(
name|HISTORY_ITEM
argument_list|)
condition|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|token
condition|)
break|break;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|name
argument_list|)
condition|)
break|break;
name|action
operator|=
name|gimp_ui_manager_find_action
argument_list|(
name|manager
argument_list|,
name|NULL
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_INT
expr_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|token
condition|)
break|break;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|count
argument_list|)
condition|)
break|break;
if|if
condition|(
name|action
condition|)
block|{
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
name|gimp_action_history_item_new
argument_list|(
name|action
argument_list|,
name|count
argument_list|)
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_action_history_init_compare_func
argument_list|)
expr_stmt|;
name|n_items
operator|++
expr_stmt|;
block|}
block|}
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
break|break;
case|case
name|G_TOKEN_RIGHT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
if|if
condition|(
name|n_items
operator|>=
name|config
operator|->
name|action_history_size
condition|)
goto|goto
name|done
goto|;
break|break;
default|default:
comment|/* do nothing */
break|break;
block|}
block|}
name|done
label|:
name|gimp_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|actions
operator|=
name|history
operator|.
name|items
operator|,
name|i
operator|=
literal|0
init|;
name|actions
operator|&&
name|i
operator|<
name|config
operator|->
name|action_history_size
condition|;
name|actions
operator|=
name|g_list_next
argument_list|(
name|actions
argument_list|)
operator|,
name|i
operator|++
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_action_history_exit (Gimp * gimp)
name|gimp_action_history_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|GimpActionHistoryItem
modifier|*
name|item
decl_stmt|;
name|GList
modifier|*
name|actions
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|gint
name|min_count
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
comment|/* If we have more items than current history size, trim the history    * and move down all count so that 1 is lower.    */
name|item
operator|=
name|g_list_nth_data
argument_list|(
name|history
operator|.
name|items
argument_list|,
name|config
operator|->
name|action_history_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
condition|)
name|min_count
operator|=
name|item
operator|->
name|count
operator|-
literal|1
expr_stmt|;
name|file
operator|=
name|gimp_directory_file
argument_list|(
name|GIMP_ACTION_HISTORY_FILENAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|writer
operator|=
name|gimp_config_writer_new_gfile
argument_list|(
name|file
argument_list|,
name|TRUE
argument_list|,
literal|"GIMP action-history"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
for|for
control|(
name|actions
operator|=
name|history
operator|.
name|items
operator|,
name|i
operator|=
literal|0
init|;
name|actions
operator|&&
name|i
operator|<
name|config
operator|->
name|action_history_size
condition|;
name|actions
operator|=
name|g_list_next
argument_list|(
name|actions
argument_list|)
operator|,
name|i
operator|++
control|)
block|{
name|item
operator|=
name|actions
operator|->
name|data
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"history-item"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|item
operator|->
name|name
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d"
argument_list|,
name|item
operator|->
name|count
operator|-
name|min_count
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
literal|"end of action-history"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_action_history_clear
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_action_history_clear (Gimp * gimp)
name|gimp_action_history_clear
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
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
comment|/* Search all history actions which match "keyword" with function  * match_func(action, keyword).  *  * @return a list of GtkAction*, to free with:  * g_list_free_full (result, (GDestroyNotify) g_object_unref);  */
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_action_history_search (Gimp * gimp,GimpActionMatchFunc match_func,const gchar * keyword)
name|gimp_action_history_search
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpActionMatchFunc
name|match_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|keyword
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|GList
modifier|*
name|actions
decl_stmt|;
name|GList
modifier|*
name|result
init|=
name|NULL
decl_stmt|;
name|gint
name|i
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
name|match_func
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
for|for
control|(
name|actions
operator|=
name|history
operator|.
name|items
operator|,
name|i
operator|=
literal|0
init|;
name|actions
operator|&&
name|i
operator|<
name|config
operator|->
name|action_history_size
condition|;
name|actions
operator|=
name|g_list_next
argument_list|(
name|actions
argument_list|)
operator|,
name|i
operator|++
control|)
block|{
name|GimpActionHistoryItem
modifier|*
name|item
init|=
name|actions
operator|->
name|data
decl_stmt|;
name|GtkAction
modifier|*
name|action
init|=
name|item
operator|->
name|action
decl_stmt|;
if|if
condition|(
operator|!
name|gtk_action_is_sensitive
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
name|result
operator|=
name|g_list_prepend
argument_list|(
name|result
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
name|result
argument_list|)
return|;
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
if|if
condition|(
name|gimp_action_is_gui_blacklisted
argument_list|(
name|action_name
argument_list|)
condition|)
return|return
name|TRUE
return|;
return|return
operator|(
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
comment|/* Callback run on the `activate` signal of an action.  * It allows us to log all used action.  */
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
name|GimpActionHistoryItem
modifier|*
name|item
init|=
name|actions
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|g_strcmp0
argument_list|(
name|action_name
argument_list|,
name|item
operator|->
name|name
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GimpActionHistoryItem
modifier|*
name|next_item
decl_stmt|;
name|next_item
operator|=
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
expr_stmt|;
comment|/* Is there any other item with the same count?  We don't            * want to leave any count gap to always accept new items.            * This means that if we increment the only item with a            * given count, we must decrement the next item.  Other            * consequence is that an item with higher count won't be            * incremented at all if no other items have the same count.            */
if|if
condition|(
name|previous_count
operator|==
name|item
operator|->
name|count
operator|||
operator|(
name|next_item
operator|&&
name|next_item
operator|->
name|count
operator|==
name|item
operator|->
name|count
operator|)
condition|)
block|{
name|item
operator|->
name|count
operator|++
expr_stmt|;
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
name|item
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
name|item
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
name|item
operator|->
name|count
condition|)
block|{
name|GimpActionHistoryItem
modifier|*
name|previous_item
init|=
name|g_list_previous
argument_list|(
name|actions
argument_list|)
operator|->
name|data
decl_stmt|;
name|item
operator|->
name|count
operator|++
expr_stmt|;
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
name|item
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
name|item
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_action_history_compare_func
argument_list|)
expr_stmt|;
name|previous_item
operator|->
name|count
operator|--
expr_stmt|;
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
name|previous_item
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
name|previous_item
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
name|item
operator|->
name|count
expr_stmt|;
block|}
comment|/* If we are here, this action is not logged yet. */
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
name|gimp_action_history_item_new
argument_list|(
name|action
argument_list|,
literal|1
argument_list|)
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_action_history_compare_func
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpActionHistoryItem
modifier|*
DECL|function|gimp_action_history_item_new (GtkAction * action,gint count)
name|gimp_action_history_item_new
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|count
parameter_list|)
block|{
name|GimpActionHistoryItem
modifier|*
name|item
init|=
name|g_new0
argument_list|(
name|GimpActionHistoryItem
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|item
operator|->
name|action
operator|=
name|g_object_ref
argument_list|(
name|action
argument_list|)
expr_stmt|;
name|item
operator|->
name|name
operator|=
name|gtk_action_get_name
argument_list|(
name|action
argument_list|)
expr_stmt|;
name|item
operator|->
name|count
operator|=
name|count
expr_stmt|;
return|return
name|item
return|;
block|}
end_function

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
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Compare function used at list initialization.  * We use a slightly different compare function as for runtime insert,  * because we want to keep history file order for equal values.  */
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
comment|/* Compare function used when updating the list.  * There is no equality case. If they have the same count,  * I ensure that the first action (last inserted) will be before.  */
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

end_unit

