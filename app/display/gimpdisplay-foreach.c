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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"nav_window.h"
end_include

begin_function
name|void
DECL|function|gdisplays_foreach (GFunc func,gpointer user_data)
name|gdisplays_foreach
parameter_list|(
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|g_slist_foreach
argument_list|(
name|display_list
argument_list|,
name|func
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gdisplays_expose_guide (GimpImage * gimage,GimpGuide * guide)
name|gdisplays_expose_guide
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|guide
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|display_list
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
name|gdisp
operator|=
operator|(
name|GimpDisplay
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|==
name|gimage
condition|)
name|gimp_display_shell_expose_guide
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
name|guide
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gdisplays_expose_full (void)
name|gdisplays_expose_full
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|display_list
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
name|gdisp
operator|=
operator|(
name|GimpDisplay
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gimp_display_shell_expose_full
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gdisplays_nav_preview_resized (void)
name|gdisplays_nav_preview_resized
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|display_list
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
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|GIMP_DISPLAY
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|nav_dialog
condition|)
name|nav_dialog_preview_resized
argument_list|(
name|shell
operator|->
name|nav_dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|nav_popup
condition|)
block|{
name|nav_dialog_free
argument_list|(
name|NULL
argument_list|,
name|shell
operator|->
name|nav_popup
argument_list|)
expr_stmt|;
name|shell
operator|->
name|nav_popup
operator|=
name|NULL
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gdisplays_dirty (void)
name|gdisplays_dirty
parameter_list|(
name|void
parameter_list|)
block|{
name|gboolean
name|dirty
init|=
name|FALSE
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|display_list
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
if|if
condition|(
operator|(
operator|(
name|GimpDisplay
operator|*
operator|)
name|list
operator|->
name|data
operator|)
operator|->
name|gimage
operator|->
name|dirty
operator|!=
literal|0
condition|)
name|dirty
operator|=
name|TRUE
expr_stmt|;
block|}
return|return
name|dirty
return|;
block|}
end_function

begin_function
name|void
DECL|function|gdisplays_delete (void)
name|gdisplays_delete
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
comment|/*  destroying the shell removes the GimpDisplay from the list, so    *  do a while loop "around" the first element to get them all    */
while|while
condition|(
name|display_list
condition|)
block|{
name|gdisp
operator|=
operator|(
name|GimpDisplay
operator|*
operator|)
name|display_list
operator|->
name|data
expr_stmt|;
name|gdisplay_delete
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpDisplay
modifier|*
DECL|function|gdisplays_check_valid (GimpDisplay * gtest,GimpImage * gimage)
name|gdisplays_check_valid
parameter_list|(
name|GimpDisplay
modifier|*
name|gtest
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
comment|/* Give a gdisp check that it is still valid and points to the required    * GimpImage. If not return the first gDisplay that does point to the     * gimage. If none found return NULL;    */
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp_found
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|display_list
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
name|gdisp
operator|=
operator|(
name|GimpDisplay
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gdisp
operator|==
name|gtest
condition|)
return|return
name|gtest
return|;
if|if
condition|(
operator|!
name|gdisp_found
operator|&&
name|gdisp
operator|->
name|gimage
operator|==
name|gimage
condition|)
name|gdisp_found
operator|=
name|gdisp
expr_stmt|;
block|}
return|return
name|gdisp_found
return|;
block|}
end_function

begin_function
name|void
DECL|function|gdisplays_flush (void)
name|gdisplays_flush
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gboolean
name|flushing
init|=
name|FALSE
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
comment|/*  this prevents multiple recursive calls to this procedure  */
if|if
condition|(
name|flushing
operator|==
name|TRUE
condition|)
block|{
name|g_warning
argument_list|(
literal|"gdisplays_flush() called recursively."
argument_list|)
expr_stmt|;
return|return;
block|}
name|flushing
operator|=
name|TRUE
expr_stmt|;
for|for
control|(
name|list
operator|=
name|display_list
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
name|gdisp
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|gdisplay_flush
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
name|flushing
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gdisplays_reconnect (GimpImage * old,GimpImage * new)
name|gdisplays_reconnect
parameter_list|(
name|GimpImage
modifier|*
name|old
parameter_list|,
name|GimpImage
modifier|*
name|new
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|old
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|new
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|display_list
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
name|gdisp
operator|=
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|==
name|old
condition|)
name|gdisplay_reconnect
argument_list|(
name|gdisp
argument_list|,
name|new
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gdisplays_set_busy (void)
name|gdisplays_set_busy
parameter_list|(
name|void
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
for|for
control|(
name|list
operator|=
name|display_list
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
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|GIMP_DISPLAY
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_install_override_cursor
argument_list|(
name|shell
argument_list|,
name|GDK_WATCH
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gdisplays_unset_busy (void)
name|gdisplays_unset_busy
parameter_list|(
name|void
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
for|for
control|(
name|list
operator|=
name|display_list
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
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|GIMP_DISPLAY
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_remove_override_cursor
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

