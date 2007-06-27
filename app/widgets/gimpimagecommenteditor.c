begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpImageCommentEditor  * Copyright (C) 2007  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagecommenteditor.h"
end_include

begin_define
DECL|macro|GIMP_IMAGE_COMMENT_PARASITE
define|#
directive|define
name|GIMP_IMAGE_COMMENT_PARASITE
value|"gimp-comment"
end_define

begin_function_decl
specifier|static
name|void
name|gimp_image_comment_editor_update
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_comment_editor_buffer_changed
parameter_list|(
name|GtkTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpImageCommentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpImageCommentEditor,gimp_image_comment_editor,GIMP_TYPE_IMAGE_PARASITE_VIEW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpImageCommentEditor
argument_list|,
argument|gimp_image_comment_editor
argument_list|,
argument|GIMP_TYPE_IMAGE_PARASITE_VIEW
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_image_comment_editor_class_init
parameter_list|(
name|GimpImageCommentEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpImageParasiteViewClass
modifier|*
name|view_class
decl_stmt|;
name|view_class
operator|=
name|GIMP_IMAGE_PARASITE_VIEW_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|view_class
operator|->
name|update
operator|=
name|gimp_image_comment_editor_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_comment_editor_init (GimpImageCommentEditor * editor)
name|gimp_image_comment_editor_init
parameter_list|(
name|GimpImageCommentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|GtkWidget
modifier|*
name|text_view
decl_stmt|;
name|scrolled_window
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
argument_list|)
argument_list|,
name|scrolled_window
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_window
argument_list|)
expr_stmt|;
name|text_view
operator|=
name|gtk_text_view_new
argument_list|()
expr_stmt|;
name|gtk_text_view_set_editable
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_text_view_set_wrap_mode
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|,
name|GTK_WRAP_WORD
argument_list|)
expr_stmt|;
name|gtk_text_view_set_pixels_above_lines
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_text_view_set_left_margin
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_text_view_set_right_margin
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|text_view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|text_view
argument_list|)
expr_stmt|;
name|editor
operator|->
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|buffer
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_comment_editor_buffer_changed
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_image_comment_editor_new (GimpImage * image)
name|gimp_image_comment_editor_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_IMAGE_COMMENT_EDITOR
argument_list|,
literal|"image"
argument_list|,
name|image
argument_list|,
literal|"parasite"
argument_list|,
name|GIMP_IMAGE_COMMENT_PARASITE
argument_list|,
name|NULL
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
DECL|function|gimp_image_comment_editor_update (GimpImageParasiteView * view)
name|gimp_image_comment_editor_update
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
block|{
name|GimpImageCommentEditor
modifier|*
name|editor
init|=
name|GIMP_IMAGE_COMMENT_EDITOR
argument_list|(
name|view
argument_list|)
decl_stmt|;
specifier|const
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|recursing
condition|)
return|return;
name|g_signal_handlers_block_by_func
argument_list|(
name|editor
operator|->
name|buffer
argument_list|,
name|gimp_image_comment_editor_buffer_changed
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_image_parasite_view_get_parasite
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|gchar
modifier|*
name|text
init|=
name|g_strndup
argument_list|(
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|g_utf8_validate
argument_list|(
name|text
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|gimp_any_to_utf8
argument_list|(
name|text
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|text
operator|=
name|tmp
expr_stmt|;
block|}
name|gtk_text_buffer_set_text
argument_list|(
name|editor
operator|->
name|buffer
argument_list|,
name|text
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_text_buffer_set_text
argument_list|(
name|editor
operator|->
name|buffer
argument_list|,
literal|""
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|g_signal_handlers_unblock_by_func
argument_list|(
name|editor
operator|->
name|buffer
argument_list|,
name|gimp_image_comment_editor_buffer_changed
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_comment_editor_buffer_changed (GtkTextBuffer * buffer,GimpImageCommentEditor * editor)
name|gimp_image_comment_editor_buffer_changed
parameter_list|(
name|GtkTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpImageCommentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|gint
name|len
decl_stmt|;
name|GtkTextIter
name|start
decl_stmt|;
name|GtkTextIter
name|end
decl_stmt|;
name|image
operator|=
name|gimp_image_parasite_view_get_image
argument_list|(
name|GIMP_IMAGE_PARASITE_VIEW
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_bounds
argument_list|(
name|buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
name|text
operator|=
name|gtk_text_buffer_get_text
argument_list|(
name|buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|len
operator|=
name|text
condition|?
name|strlen
argument_list|(
name|text
argument_list|)
else|:
literal|0
expr_stmt|;
name|editor
operator|->
name|recursing
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|len
operator|>
literal|0
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
name|GIMP_IMAGE_COMMENT_PARASITE
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|len
operator|+
literal|1
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_parasite_detach
argument_list|(
name|image
argument_list|,
name|GIMP_IMAGE_COMMENT_PARASITE
argument_list|)
expr_stmt|;
block|}
name|editor
operator|->
name|recursing
operator|=
name|FALSE
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

