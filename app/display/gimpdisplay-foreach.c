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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
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
file|"app_procs.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_displays_dirty (Gimp * gimp)
name|gimp_displays_dirty
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|the_gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
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
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_displays_delete (Gimp * gimp)
name|gimp_displays_delete
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  this removes the GimpDisplay from the list, so do a while loop    *  "around" the first element to get them all    */
while|while
condition|(
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
condition|)
block|{
name|gdisp
operator|=
operator|(
name|GimpDisplay
operator|*
operator|)
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
operator|->
name|data
expr_stmt|;
name|gimp_display_delete
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
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|the_gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
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
DECL|function|gimp_displays_flush (Gimp * gimp)
name|gimp_displays_flush
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
specifier|static
name|gboolean
name|flushing
init|=
name|FALSE
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
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
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
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
name|gimp_display_flush
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

begin_comment
comment|/* Force all gdisplays to finish their idlerender projection */
end_comment

begin_function
name|void
DECL|function|gimp_displays_finish_draw (Gimp * gimp)
name|gimp_displays_finish_draw
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
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
name|gimp_display_finish_draw
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_displays_reconnect (Gimp * gimp,GimpImage * old,GimpImage * new)
name|gimp_displays_reconnect
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|old
parameter_list|,
name|GimpImage
modifier|*
name|new
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|old
argument_list|)
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
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
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
name|gimp_display_reconnect
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
DECL|function|gimp_displays_set_busy (Gimp * gimp)
name|gimp_displays_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
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
name|gimp_display_shell_set_override_cursor
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
DECL|function|gimp_displays_unset_busy (Gimp * gimp)
name|gimp_displays_unset_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
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
name|gimp_display_shell_unset_override_cursor
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

