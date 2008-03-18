begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpdisplayshell-cursor.h"
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
name|GimpDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|image
operator|&&
name|display
operator|->
name|image
operator|->
name|dirty
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
specifier|static
name|void
DECL|function|gimp_displays_image_dirty_callback (GimpImage * image,GimpDirtyMask dirty_mask,GimpContainer * container)
name|gimp_displays_image_dirty_callback
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
if|if
condition|(
name|image
operator|->
name|dirty
operator|&&
name|image
operator|->
name|disp_count
operator|>
literal|0
operator|&&
operator|!
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
condition|)
name|gimp_container_add
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_displays_dirty_images_disconnect (GimpContainer * dirty_container,GimpContainer * global_container)
name|gimp_displays_dirty_images_disconnect
parameter_list|(
name|GimpContainer
modifier|*
name|dirty_container
parameter_list|,
name|GimpContainer
modifier|*
name|global_container
parameter_list|)
block|{
name|GQuark
name|handler
decl_stmt|;
name|handler
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dirty_container
argument_list|)
argument_list|,
literal|"clean-handler"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|global_container
argument_list|,
name|handler
argument_list|)
expr_stmt|;
name|handler
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dirty_container
argument_list|)
argument_list|,
literal|"dirty-handler"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|global_container
argument_list|,
name|handler
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_displays_image_clean_callback (GimpImage * image,GimpDirtyMask dirty_mask,GimpContainer * container)
name|gimp_displays_image_clean_callback
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
if|if
condition|(
operator|!
name|image
operator|->
name|dirty
condition|)
name|gimp_container_remove
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_displays_get_dirty_images (Gimp * gimp)
name|gimp_displays_get_dirty_images
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
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
if|if
condition|(
name|gimp_displays_dirty
argument_list|(
name|gimp
argument_list|)
condition|)
block|{
name|GimpContainer
modifier|*
name|container
init|=
name|gimp_list_new_weak
argument_list|(
name|GIMP_TYPE_IMAGE
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GQuark
name|handler
decl_stmt|;
name|handler
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"clean"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_displays_image_dirty_callback
argument_list|)
argument_list|,
name|container
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|container
argument_list|)
argument_list|,
literal|"clean-handler"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|handler
argument_list|)
argument_list|)
expr_stmt|;
name|handler
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"dirty"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_displays_image_dirty_callback
argument_list|)
argument_list|,
name|container
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|container
argument_list|)
argument_list|,
literal|"dirty-handler"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|handler
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|container
argument_list|,
literal|"disconnect"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_displays_dirty_images_disconnect
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|images
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_container_add_handler
argument_list|(
name|container
argument_list|,
literal|"clean"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_displays_image_clean_callback
argument_list|)
argument_list|,
name|container
argument_list|)
expr_stmt|;
name|gimp_container_add_handler
argument_list|(
name|container
argument_list|,
literal|"dirty"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_displays_image_clean_callback
argument_list|)
argument_list|,
name|container
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
name|images
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
name|GimpImage
modifier|*
name|image
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|image
operator|->
name|dirty
operator|&&
name|image
operator|->
name|disp_count
operator|>
literal|0
condition|)
name|gimp_container_add
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|container
return|;
block|}
return|return
name|NULL
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
name|GimpDisplay
modifier|*
name|display
init|=
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
decl_stmt|;
name|gimp_display_delete
argument_list|(
name|display
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
name|contexts
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
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
comment|/*  remember which contexts refer to old_image  */
for|for
control|(
name|list
operator|=
name|gimp
operator|->
name|context_list
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
name|GimpContext
modifier|*
name|context
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
operator|==
name|old
condition|)
name|contexts
operator|=
name|g_list_prepend
argument_list|(
name|contexts
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
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
name|GimpDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|image
operator|==
name|old
condition|)
name|gimp_display_set_image
argument_list|(
name|display
argument_list|,
name|new
argument_list|)
expr_stmt|;
block|}
comment|/*  set the new_image on the remembered contexts (in reverse    *  order, since older contexts are usually the parents of    *  newer ones)    */
name|g_list_foreach
argument_list|(
name|contexts
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_context_set_image
argument_list|,
name|new
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|contexts
argument_list|)
expr_stmt|;
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
name|GimpDisplayShell
modifier|*
name|shell
init|=
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
decl_stmt|;
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
name|GimpDisplayShell
modifier|*
name|shell
init|=
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
decl_stmt|;
name|gimp_display_shell_unset_override_cursor
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

