begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
file|"dialog_handler.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_comment
comment|/* for gdisplay_*_override_cursor() */
end_comment

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|display_list
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* It's in gdisplay.c, FYI */
end_comment

begin_decl_stmt
DECL|variable|pending_removebusy
specifier|static
name|gboolean
name|pending_removebusy
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|change_win_cursor (win,cursortype)
name|change_win_cursor
parameter_list|(
name|win
parameter_list|,
name|cursortype
parameter_list|)
name|GdkWindow
modifier|*
name|win
decl_stmt|;
name|GdkCursorType
name|cursortype
decl_stmt|;
block|{
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|cursor
operator|=
name|gdk_cursor_new
argument_list|(
name|cursortype
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|win
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|gdk_cursor_destroy
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|unset_win_cursor (win)
name|unset_win_cursor
parameter_list|(
name|win
parameter_list|)
name|GdkWindow
modifier|*
name|win
decl_stmt|;
block|{
name|gdk_window_set_cursor
argument_list|(
name|win
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_add_busy_cursors_until_idle (void)
name|gimp_add_busy_cursors_until_idle
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|pending_removebusy
condition|)
block|{
name|gimp_add_busy_cursors
argument_list|()
expr_stmt|;
name|gtk_idle_add_priority
argument_list|(
name|GTK_PRIORITY_HIGH
argument_list|,
name|gimp_remove_busy_cursors
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pending_removebusy
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_add_busy_cursors (void)
name|gimp_add_busy_cursors
parameter_list|(
name|void
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GSList
modifier|*
name|list
init|=
name|display_list
decl_stmt|;
comment|/* Canvases */
while|while
condition|(
name|list
condition|)
block|{
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gdisplay_install_override_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_WATCH
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
comment|/* Dialogs */
name|dialog_idle_all
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_remove_busy_cursors (gpointer data)
name|gimp_remove_busy_cursors
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GSList
modifier|*
name|list
init|=
name|display_list
decl_stmt|;
comment|/* Canvases */
while|while
condition|(
name|list
condition|)
block|{
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gdisplay_remove_override_cursor
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
comment|/* Dialogs */
name|dialog_unidle_all
argument_list|()
expr_stmt|;
name|pending_removebusy
operator|=
name|FALSE
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

end_unit

