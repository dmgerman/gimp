begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1999 Andy Thomas (alt@picnic.demon.co.uk)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"cursorutil.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_decl_stmt
DECL|variable|active_dialogs
specifier|static
name|GSList
modifier|*
name|active_dialogs
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|active_dialogs
comment|/* List of dialogs that have  					  been created and are on  					  screen (may be hidden already). 				       */
end_comment

begin_decl_stmt
DECL|variable|doing_update
specifier|static
name|gint
name|doing_update
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|doing_update
comment|/* Prevent multiple keypresses  				      from unsetting me. 				   */
end_comment

begin_comment
comment|/* State of individual dialogs */
end_comment

begin_typedef
DECL|typedef|DIALOGSTATE
DECL|typedef|DIALOGSTATEP
typedef|typedef
name|struct
name|_dialog_state
name|DIALOGSTATE
typedef|,
modifier|*
name|DIALOGSTATEP
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon27cba7c10103
typedef|typedef
enum|enum
block|{
DECL|enumerator|WAS_HIDDEN
name|WAS_HIDDEN
block|,
DECL|enumerator|WAS_SHOWING
name|WAS_SHOWING
block|,
DECL|enumerator|UNKNOWN
name|UNKNOWN
block|, }
DECL|typedef|dialogstate
name|dialogstate
typedef|;
end_typedef

begin_struct
DECL|struct|_dialog_state
struct|struct
name|_dialog_state
block|{
DECL|member|d
name|GtkWidget
modifier|*
name|d
decl_stmt|;
DECL|member|state
name|dialogstate
name|state
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* This keeps track of the state the dialogs are in */
end_comment

begin_comment
comment|/* ie how many times we have pressed the tab key */
end_comment

begin_typedef
DECL|enum|__anon27cba7c10203
typedef|typedef
enum|enum
block|{
DECL|enumerator|SHOW_ALL
name|SHOW_ALL
block|,
DECL|enumerator|HIDE_ALL
name|HIDE_ALL
block|,
DECL|enumerator|SHOW_TOOLBOX
name|SHOW_TOOLBOX
block|,
DECL|enumerator|LAST_SHOW_STATE
name|LAST_SHOW_STATE
block|, }
DECL|typedef|ShowState
name|ShowState
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|dialogs_showing
specifier|static
name|ShowState
name|dialogs_showing
init|=
name|SHOW_ALL
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|dialogs_showing
comment|/* Start off with all  						dialogs showing  					     */
end_comment

begin_decl_stmt
DECL|variable|toolbox_shell
specifier|static
name|DIALOGSTATEP
name|toolbox_shell
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|toolbox_shell
comment|/* Copy of the shell for the tool  					      box - this has special behaviour  					      so is not on the normal list. 					   */
end_comment

begin_comment
comment|/* Private */
end_comment

begin_comment
comment|/* Hide all currently registered dialogs */
end_comment

begin_function
specifier|static
name|void
DECL|function|dialog_hide_all ()
name|dialog_hide_all
parameter_list|()
block|{
name|GSList
modifier|*
name|list
init|=
name|active_dialogs
decl_stmt|;
name|DIALOGSTATEP
name|dstate
decl_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|dstate
operator|=
operator|(
name|DIALOGSTATEP
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|dstate
operator|->
name|d
argument_list|)
condition|)
block|{
name|dstate
operator|->
name|state
operator|=
name|WAS_SHOWING
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|dstate
operator|->
name|d
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|dstate
operator|->
name|state
operator|=
name|WAS_HIDDEN
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/* Show all currently registered dialogs */
end_comment

begin_function
specifier|static
name|void
DECL|function|dialog_show_all ()
name|dialog_show_all
parameter_list|()
block|{
name|GSList
modifier|*
name|list
init|=
name|active_dialogs
decl_stmt|;
name|DIALOGSTATEP
name|dstate
decl_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|dstate
operator|=
operator|(
name|DIALOGSTATEP
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|dstate
operator|->
name|state
operator|==
name|WAS_SHOWING
operator|&&
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|dstate
operator|->
name|d
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|dstate
operator|->
name|d
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* Handle the tool box in a special way */
end_comment

begin_function
specifier|static
name|void
DECL|function|dialog_hide_toolbox ()
name|dialog_hide_toolbox
parameter_list|()
block|{
if|if
condition|(
name|toolbox_shell
operator|&&
name|GTK_WIDGET_VISIBLE
argument_list|(
name|toolbox_shell
operator|->
name|d
argument_list|)
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|toolbox_shell
operator|->
name|d
argument_list|)
expr_stmt|;
name|toolbox_shell
operator|->
name|state
operator|=
name|WAS_SHOWING
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* public */
end_comment

begin_function
name|void
DECL|function|dialog_show_toolbox ()
name|dialog_show_toolbox
parameter_list|()
block|{
if|if
condition|(
name|toolbox_shell
operator|&&
name|toolbox_shell
operator|->
name|state
operator|==
name|WAS_SHOWING
operator|&&
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|toolbox_shell
operator|->
name|d
argument_list|)
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|toolbox_shell
operator|->
name|d
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* Set hourglass cursor on all currently registered dialogs */
end_comment

begin_function
name|void
DECL|function|dialog_idle_all ()
name|dialog_idle_all
parameter_list|()
block|{
name|GSList
modifier|*
name|list
init|=
name|active_dialogs
decl_stmt|;
name|DIALOGSTATEP
name|dstate
decl_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|dstate
operator|=
operator|(
name|DIALOGSTATEP
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|dstate
operator|->
name|d
argument_list|)
condition|)
block|{
name|change_win_cursor
argument_list|(
name|dstate
operator|->
name|d
operator|->
name|window
argument_list|,
name|GDK_WATCH
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|toolbox_shell
operator|&&
name|GTK_WIDGET_VISIBLE
argument_list|(
name|toolbox_shell
operator|->
name|d
argument_list|)
condition|)
block|{
name|change_win_cursor
argument_list|(
name|toolbox_shell
operator|->
name|d
operator|->
name|window
argument_list|,
name|GDK_WATCH
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* And remove the hourglass again. */
end_comment

begin_function
name|void
DECL|function|dialog_unidle_all ()
name|dialog_unidle_all
parameter_list|()
block|{
name|GSList
modifier|*
name|list
init|=
name|active_dialogs
decl_stmt|;
name|DIALOGSTATEP
name|dstate
decl_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|dstate
operator|=
operator|(
name|DIALOGSTATEP
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|dstate
operator|->
name|d
argument_list|)
condition|)
block|{
name|unset_win_cursor
argument_list|(
name|dstate
operator|->
name|d
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|toolbox_shell
operator|&&
name|GTK_WIDGET_VISIBLE
argument_list|(
name|toolbox_shell
operator|->
name|d
argument_list|)
condition|)
block|{
name|unset_win_cursor
argument_list|(
name|toolbox_shell
operator|->
name|d
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* Register a dialog that we can handle */
end_comment

begin_function
name|void
DECL|function|dialog_register (GtkWidget * dialog)
name|dialog_register
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|DIALOGSTATEP
name|dstatep
init|=
name|g_new
argument_list|(
name|DIALOGSTATE
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|dstatep
operator|->
name|d
operator|=
name|dialog
expr_stmt|;
name|dstatep
operator|->
name|state
operator|=
name|UNKNOWN
expr_stmt|;
name|active_dialogs
operator|=
name|g_slist_append
argument_list|(
name|active_dialogs
argument_list|,
name|dstatep
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dialog_register_toolbox (GtkWidget * dialog)
name|dialog_register_toolbox
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|DIALOGSTATEP
name|dstatep
init|=
name|g_new
argument_list|(
name|DIALOGSTATE
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|dstatep
operator|->
name|d
operator|=
name|dialog
expr_stmt|;
name|dstatep
operator|->
name|state
operator|=
name|UNKNOWN
expr_stmt|;
name|toolbox_shell
operator|=
name|dstatep
expr_stmt|;
block|}
end_function

begin_comment
comment|/* unregister dialog */
end_comment

begin_function
name|void
DECL|function|dialog_unregister (GtkWidget * dialog)
name|dialog_unregister
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|GSList
modifier|*
name|list
init|=
name|active_dialogs
decl_stmt|;
name|DIALOGSTATEP
name|dstate
init|=
name|NULL
decl_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|dstate
operator|=
operator|(
name|DIALOGSTATEP
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|dstate
operator|->
name|d
operator|==
name|dialog
condition|)
break|break;
block|}
if|if
condition|(
name|dstate
operator|!=
name|NULL
condition|)
name|active_dialogs
operator|=
name|g_slist_remove
argument_list|(
name|active_dialogs
argument_list|,
name|dstate
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Toggle showing of dialogs */
end_comment

begin_comment
comment|/* States:-  * SHOW_ALL -> HIDE_ALL -> SHOW_TOOLBOX -> SHOW_ALL ....  */
end_comment

begin_function
name|void
DECL|function|dialog_toggle (void)
name|dialog_toggle
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|doing_update
operator|==
name|FALSE
condition|)
name|doing_update
operator|=
name|TRUE
expr_stmt|;
else|else
return|return;
switch|switch
condition|(
name|dialogs_showing
condition|)
block|{
case|case
name|SHOW_ALL
case|:
name|dialogs_showing
operator|=
name|HIDE_ALL
expr_stmt|;
name|dialog_hide_all
argument_list|()
expr_stmt|;
name|dialog_hide_toolbox
argument_list|()
expr_stmt|;
break|break;
case|case
name|HIDE_ALL
case|:
name|dialogs_showing
operator|=
name|SHOW_TOOLBOX
expr_stmt|;
name|dialog_show_toolbox
argument_list|()
expr_stmt|;
break|break;
case|case
name|SHOW_TOOLBOX
case|:
name|dialogs_showing
operator|=
name|SHOW_ALL
expr_stmt|;
name|dialog_show_all
argument_list|()
expr_stmt|;
default|default:
break|break;
block|}
name|gdk_flush
argument_list|()
expr_stmt|;
while|while
condition|(
name|gtk_events_pending
argument_list|()
condition|)
block|{
name|gtk_main_iteration
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
name|doing_update
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

