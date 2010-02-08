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
file|"core/gimp-edit.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
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
file|"core/gimpimage-new.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpbufferview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview-utils.h"
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
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"buffers-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|buffers_paste
parameter_list|(
name|GimpBufferView
modifier|*
name|view
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functionss */
end_comment

begin_function
name|void
DECL|function|buffers_paste_cmd_callback (GtkAction * action,gpointer data)
name|buffers_paste_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|buffers_paste
argument_list|(
name|GIMP_BUFFER_VIEW
argument_list|(
name|data
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|buffers_paste_into_cmd_callback (GtkAction * action,gpointer data)
name|buffers_paste_into_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|buffers_paste
argument_list|(
name|GIMP_BUFFER_VIEW
argument_list|(
name|data
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|buffers_paste_as_new_cmd_callback (GtkAction * action,gpointer data)
name|buffers_paste_as_new_cmd_callback
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
name|GimpBuffer
modifier|*
name|buffer
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
name|buffer
operator|=
name|gimp_context_get_buffer
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
decl_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|new_image
operator|=
name|gimp_image_new_from_buffer
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|image
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|new_image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|buffers_delete_cmd_callback (GtkAction * action,gpointer data)
name|buffers_delete_cmd_callback
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
name|gimp_container_view_remove_active
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|buffers_paste (GimpBufferView * view,gboolean paste_into)
name|buffers_paste
parameter_list|(
name|GimpBufferView
modifier|*
name|view
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
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
name|GimpBuffer
modifier|*
name|buffer
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
name|buffer
operator|=
name|gimp_context_get_buffer
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
condition|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|gimp_context_get_display
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
name|gint
name|x
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|y
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|width
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|height
init|=
operator|-
literal|1
decl_stmt|;
if|if
condition|(
name|display
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|gimp_display_shell_untransform_viewport
argument_list|(
name|shell
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|image
operator|=
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|image
condition|)
block|{
name|gimp_edit_paste
argument_list|(
name|image
argument_list|,
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
argument_list|,
name|buffer
argument_list|,
name|paste_into
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

