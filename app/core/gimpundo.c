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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpundo.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2bc2b1ce0103
block|{
DECL|enumerator|PUSH
name|PUSH
block|,
DECL|enumerator|POP
name|POP
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_undo_class_init
parameter_list|(
name|GimpUndoClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_init
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_real_push
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_real_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_undo_get_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|undo_signals
specifier|static
name|guint
name|undo_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpViewableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_undo_get_type (void)
name|gimp_undo_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|undo_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|undo_type
condition|)
block|{
specifier|static
specifier|const
name|GtkTypeInfo
name|undo_info
init|=
block|{
literal|"GimpUndo"
block|,
sizeof|sizeof
argument_list|(
name|GimpUndo
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpUndoClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_undo_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_undo_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|undo_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_VIEWABLE
argument_list|,
operator|&
name|undo_info
argument_list|)
expr_stmt|;
block|}
return|return
name|undo_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_class_init (GimpUndoClass * klass)
name|gimp_undo_class_init
parameter_list|(
name|GimpUndoClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|viewable_class
operator|=
operator|(
name|GimpViewableClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|undo_signals
index|[
name|PUSH
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"push"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpUndoClass
argument_list|,
name|push
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|undo_signals
index|[
name|POP
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"pop"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpUndoClass
argument_list|,
name|pop
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_undo_destroy
expr_stmt|;
name|viewable_class
operator|->
name|get_preview
operator|=
name|gimp_undo_get_preview
expr_stmt|;
name|klass
operator|->
name|push
operator|=
name|gimp_undo_real_push
expr_stmt|;
name|klass
operator|->
name|pop
operator|=
name|gimp_undo_real_pop
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_init (GimpUndo * undo)
name|gimp_undo_init
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|)
block|{
name|undo
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|undo
operator|->
name|size
operator|=
literal|0
expr_stmt|;
name|undo
operator|->
name|dirties_image
operator|=
name|FALSE
expr_stmt|;
name|undo
operator|->
name|pop_func
operator|=
name|NULL
expr_stmt|;
name|undo
operator|->
name|free_func
operator|=
name|NULL
expr_stmt|;
name|undo
operator|->
name|preview
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_destroy (GtkObject * object)
name|gimp_undo_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|undo
operator|=
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|->
name|free_func
condition|)
name|undo
operator|->
name|free_func
argument_list|(
name|undo
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|->
name|preview
condition|)
name|temp_buf_free
argument_list|(
name|undo
operator|->
name|preview
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpUndo
modifier|*
DECL|function|gimp_undo_new (const gchar * name,gpointer data,glong size,gboolean dirties_image,GimpUndoPopFunc pop_func,GimpUndoFreeFunc free_func)
name|gimp_undo_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|glong
name|size
parameter_list|,
name|gboolean
name|dirties_image
parameter_list|,
name|GimpUndoPopFunc
name|pop_func
parameter_list|,
name|GimpUndoFreeFunc
name|free_func
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|undo
operator|=
name|GIMP_UNDO
argument_list|(
name|gtk_object_new
argument_list|(
name|GIMP_TYPE_UNDO
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|undo
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|undo
operator|->
name|size
operator|=
sizeof|sizeof
argument_list|(
name|GimpUndo
argument_list|)
operator|+
name|size
expr_stmt|;
name|undo
operator|->
name|pop_func
operator|=
name|pop_func
expr_stmt|;
name|undo
operator|->
name|free_func
operator|=
name|free_func
expr_stmt|;
return|return
name|undo
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_undo_push (GimpUndo * undo,GimpImage * gimage)
name|gimp_undo_push
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|undo
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNDO
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|,
name|undo_signals
index|[
name|PUSH
index|]
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_undo_pop (GimpUndo * undo,GimpImage * gimage)
name|gimp_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|undo
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNDO
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|,
name|undo_signals
index|[
name|POP
index|]
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_real_push (GimpUndo * undo,GimpImage * gimage)
name|gimp_undo_real_push
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
comment|/* FIXME: need core_config->undo_preview_size */
name|undo
operator|->
name|preview
operator|=
name|gimp_viewable_get_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|24
argument_list|,
literal|24
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_real_pop (GimpUndo * undo,GimpImage * gimage)
name|gimp_undo_real_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
if|if
condition|(
name|undo
operator|->
name|pop_func
condition|)
name|undo
operator|->
name|pop_func
argument_list|(
name|undo
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_undo_get_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_undo_get_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
return|return
operator|(
name|GIMP_UNDO
argument_list|(
name|viewable
argument_list|)
operator|->
name|preview
operator|)
return|;
block|}
end_function

end_unit

