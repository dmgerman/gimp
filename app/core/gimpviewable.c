begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpviewable.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29e0cc360103
block|{
DECL|enumerator|INVALIDATE_PREVIEW
name|INVALIDATE_PREVIEW
block|,
DECL|enumerator|SIZE_CHANGED
name|SIZE_CHANGED
block|,
DECL|enumerator|GET_PREVIEW
name|GET_PREVIEW
block|,
DECL|enumerator|GET_NEW_PREVIEW
name|GET_NEW_PREVIEW
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_viewable_class_init
parameter_list|(
name|GimpViewableClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_viewable_init
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_viewable_real_invalidate_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|viewable_signals
specifier|static
name|guint
name|viewable_signals
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
name|GimpObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_viewable_get_type (void)
name|gimp_viewable_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|viewable_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|viewable_type
condition|)
block|{
name|GtkTypeInfo
name|viewable_info
init|=
block|{
literal|"GimpViewable"
block|,
sizeof|sizeof
argument_list|(
name|GimpViewable
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpViewableClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_viewable_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_viewable_init
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
block|,       }
decl_stmt|;
name|viewable_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
operator|&
name|viewable_info
argument_list|)
expr_stmt|;
block|}
return|return
name|viewable_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_class_init (GimpViewableClass * klass)
name|gimp_viewable_class_init
parameter_list|(
name|GimpViewableClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
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
name|viewable_signals
index|[
name|INVALIDATE_PREVIEW
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"invalidate_preview"
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
name|GimpViewableClass
argument_list|,
name|invalidate_preview
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|viewable_signals
index|[
name|SIZE_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"size_changed"
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
name|GimpViewableClass
argument_list|,
name|size_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|viewable_signals
index|[
name|GET_PREVIEW
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"get_preview"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpViewableClass
argument_list|,
name|get_preview
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_POINTER__INT_INT
argument_list|,
name|G_TYPE_POINTER
argument_list|,
literal|2
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|viewable_signals
index|[
name|GET_NEW_PREVIEW
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"get_new_preview"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpViewableClass
argument_list|,
name|get_new_preview
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_POINTER__INT_INT
argument_list|,
name|G_TYPE_POINTER
argument_list|,
literal|2
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|klass
operator|->
name|invalidate_preview
operator|=
name|gimp_viewable_real_invalidate_preview
expr_stmt|;
name|klass
operator|->
name|size_changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|get_preview
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|get_new_preview
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_init (GimpViewable * viewable)
name|gimp_viewable_init
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{ }
end_function

begin_function
name|void
DECL|function|gimp_viewable_invalidate_preview (GimpViewable * viewable)
name|gimp_viewable_invalidate_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|viewable_signals
index|[
name|INVALIDATE_PREVIEW
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_viewable_size_changed (GimpViewable * viewable)
name|gimp_viewable_size_changed
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|viewable_signals
index|[
name|SIZE_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_real_invalidate_preview (GimpViewable * viewable)
name|gimp_viewable_real_invalidate_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
literal|"static-viewable-preview"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_viewable_get_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_viewable_get_preview
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
name|TempBuf
modifier|*
name|temp_buf
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|viewable_signals
index|[
name|GET_PREVIEW
index|]
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|temp_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|temp_buf
condition|)
return|return
name|temp_buf
return|;
name|temp_buf
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
literal|"static-viewable-preview"
argument_list|)
expr_stmt|;
if|if
condition|(
name|temp_buf
operator|&&
name|temp_buf
operator|->
name|width
operator|==
name|width
operator|&&
name|temp_buf
operator|->
name|height
operator|==
name|height
condition|)
return|return
name|temp_buf
return|;
name|temp_buf
operator|=
name|NULL
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|viewable_signals
index|[
name|GET_NEW_PREVIEW
index|]
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|temp_buf
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
literal|"static-viewable-preview"
argument_list|,
name|temp_buf
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|temp_buf_free
argument_list|)
expr_stmt|;
return|return
name|temp_buf
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_viewable_get_new_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_viewable_get_new_preview
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
name|TempBuf
modifier|*
name|temp_buf
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|viewable_signals
index|[
name|GET_NEW_PREVIEW
index|]
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|temp_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|temp_buf
condition|)
return|return
name|temp_buf
return|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|viewable_signals
index|[
name|GET_PREVIEW
index|]
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|temp_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|temp_buf
condition|)
return|return
name|temp_buf_copy
argument_list|(
name|temp_buf
argument_list|,
name|NULL
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

