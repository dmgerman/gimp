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
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpimageview.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"images-commands.h"
end_include

begin_comment
comment|/*  public functionss */
end_comment

begin_function
name|void
DECL|function|images_raise_views_cmd_callback (GtkAction * action,gpointer data)
name|images_raise_views_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|&&
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
block|{
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
name|image
operator|->
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
name|image
condition|)
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|images_new_view_cmd_callback (GtkAction * action,gpointer data)
name|images_new_view_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|&&
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
block|{
name|gimp_create_display
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|images_delete_image_cmd_callback (GtkAction * action,gpointer data)
name|images_delete_image_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|&&
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
block|{
if|if
condition|(
name|image
operator|->
name|disp_count
operator|==
literal|0
condition|)
name|g_object_unref
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

