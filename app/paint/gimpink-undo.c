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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpundo.h"
end_include

begin_include
include|#
directive|include
file|"gimpink.h"
end_include

begin_include
include|#
directive|include
file|"gimpink-blob.h"
end_include

begin_include
include|#
directive|include
file|"gimpink-undo.h"
end_include

begin_comment
comment|/**************/
end_comment

begin_comment
comment|/*  Ink Undo  */
end_comment

begin_comment
comment|/**************/
end_comment

begin_typedef
DECL|typedef|InkUndo
typedef|typedef
name|struct
name|_InkUndo
name|InkUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_InkUndo
struct|struct
name|_InkUndo
block|{
DECL|member|ink
name|GimpInk
modifier|*
name|ink
decl_stmt|;
DECL|member|last_blob
name|Blob
modifier|*
name|last_blob
decl_stmt|;
DECL|member|dt_buffer
name|gdouble
name|dt_buffer
index|[
name|DIST_SMOOTHER_BUFFER
index|]
decl_stmt|;
DECL|member|dt_index
name|gint
name|dt_index
decl_stmt|;
DECL|member|ts_buffer
name|guint32
name|ts_buffer
index|[
name|TIME_SMOOTHER_BUFFER
index|]
decl_stmt|;
DECL|member|ts_index
name|gint
name|ts_index
decl_stmt|;
DECL|member|last_time
name|gdouble
name|last_time
decl_stmt|;
DECL|member|init_velocity
name|gboolean
name|init_velocity
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|gboolean
name|undo_pop_ink
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|undo_free_ink
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|gboolean
DECL|function|gimp_ink_push_undo (GimpPaintCore * core,GimpImage * gimage,const gchar * undo_desc)
name|gimp_ink_push_undo
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|new
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_INK
argument_list|(
name|core
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|g_type_class_peek_parent
argument_list|(
name|GIMP_INK_GET_CLASS
argument_list|(
name|core
argument_list|)
argument_list|)
argument_list|)
operator|->
name|push_undo
argument_list|(
name|core
argument_list|,
name|gimage
argument_list|,
name|undo_desc
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|(
name|new
operator|=
name|gimp_image_undo_push
argument_list|(
name|gimage
argument_list|,
name|GIMP_TYPE_UNDO
argument_list|,
sizeof|sizeof
argument_list|(
name|InkUndo
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|InkUndo
argument_list|)
argument_list|,
name|GIMP_UNDO_INK
argument_list|,
name|undo_desc
argument_list|,
name|FALSE
argument_list|,
name|undo_pop_ink
argument_list|,
name|undo_free_ink
argument_list|,
name|NULL
argument_list|)
operator|)
condition|)
block|{
name|GimpInk
modifier|*
name|ink
init|=
name|GIMP_INK
argument_list|(
name|core
argument_list|)
decl_stmt|;
name|InkUndo
modifier|*
name|ink_undo
init|=
name|new
operator|->
name|data
decl_stmt|;
name|ink_undo
operator|->
name|ink
operator|=
name|ink
expr_stmt|;
if|if
condition|(
name|ink
operator|->
name|start_blob
condition|)
name|ink_undo
operator|->
name|last_blob
operator|=
name|blob_duplicate
argument_list|(
name|ink
operator|->
name|start_blob
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|ink_undo
operator|->
name|dt_buffer
argument_list|,
name|ink
operator|->
name|dt_buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|ink_undo
operator|->
name|dt_buffer
argument_list|)
argument_list|)
expr_stmt|;
name|ink_undo
operator|->
name|dt_index
operator|=
name|ink
operator|->
name|dt_index
expr_stmt|;
name|memcpy
argument_list|(
name|ink_undo
operator|->
name|ts_buffer
argument_list|,
name|ink
operator|->
name|ts_buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|ink_undo
operator|->
name|ts_buffer
argument_list|)
argument_list|)
expr_stmt|;
name|ink_undo
operator|->
name|ts_index
operator|=
name|ink
operator|->
name|ts_index
expr_stmt|;
name|ink_undo
operator|->
name|last_time
operator|=
name|ink
operator|->
name|last_time
expr_stmt|;
name|ink_undo
operator|->
name|init_velocity
operator|=
name|ink
operator|->
name|init_velocity
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|ink
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|ink_undo
operator|->
name|ink
argument_list|)
expr_stmt|;
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
name|gboolean
DECL|function|undo_pop_ink (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|undo_pop_ink
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
block|{
name|InkUndo
modifier|*
name|ink_undo
init|=
name|undo
operator|->
name|data
decl_stmt|;
comment|/*  only pop if the core still exists  */
if|if
condition|(
name|ink_undo
operator|->
name|ink
condition|)
block|{
name|Blob
modifier|*
name|tmp_blob
decl_stmt|;
name|gint
name|tmp_int
decl_stmt|;
name|gdouble
name|tmp_double
decl_stmt|;
name|guint32
name|tmp_int_buf
index|[
name|DIST_SMOOTHER_BUFFER
index|]
decl_stmt|;
name|gdouble
name|tmp_double_buf
index|[
name|DIST_SMOOTHER_BUFFER
index|]
decl_stmt|;
name|tmp_blob
operator|=
name|ink_undo
operator|->
name|ink
operator|->
name|last_blob
expr_stmt|;
name|ink_undo
operator|->
name|ink
operator|->
name|last_blob
operator|=
name|ink_undo
operator|->
name|last_blob
expr_stmt|;
name|ink_undo
operator|->
name|last_blob
operator|=
name|tmp_blob
expr_stmt|;
name|memcpy
argument_list|(
name|tmp_double_buf
argument_list|,
name|ink_undo
operator|->
name|ink
operator|->
name|dt_buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|tmp_double_buf
argument_list|)
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|ink_undo
operator|->
name|ink
operator|->
name|dt_buffer
argument_list|,
name|ink_undo
operator|->
name|dt_buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|tmp_double_buf
argument_list|)
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|ink_undo
operator|->
name|dt_buffer
argument_list|,
name|tmp_double_buf
argument_list|,
sizeof|sizeof
argument_list|(
name|tmp_double_buf
argument_list|)
argument_list|)
expr_stmt|;
name|tmp_int
operator|=
name|ink_undo
operator|->
name|ink
operator|->
name|dt_index
expr_stmt|;
name|ink_undo
operator|->
name|ink
operator|->
name|dt_index
operator|=
name|ink_undo
operator|->
name|dt_index
expr_stmt|;
name|ink_undo
operator|->
name|dt_index
operator|=
name|tmp_int
expr_stmt|;
name|memcpy
argument_list|(
name|tmp_int_buf
argument_list|,
name|ink_undo
operator|->
name|ink
operator|->
name|ts_buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|tmp_int_buf
argument_list|)
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|ink_undo
operator|->
name|ink
operator|->
name|ts_buffer
argument_list|,
name|ink_undo
operator|->
name|ts_buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|tmp_int_buf
argument_list|)
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|ink_undo
operator|->
name|ts_buffer
argument_list|,
name|tmp_int_buf
argument_list|,
sizeof|sizeof
argument_list|(
name|tmp_int_buf
argument_list|)
argument_list|)
expr_stmt|;
name|tmp_int
operator|=
name|ink_undo
operator|->
name|ink
operator|->
name|ts_index
expr_stmt|;
name|ink_undo
operator|->
name|ink
operator|->
name|ts_index
operator|=
name|ink_undo
operator|->
name|ts_index
expr_stmt|;
name|ink_undo
operator|->
name|ts_index
operator|=
name|tmp_int
expr_stmt|;
name|tmp_double
operator|=
name|ink_undo
operator|->
name|ink
operator|->
name|last_time
expr_stmt|;
name|ink_undo
operator|->
name|ink
operator|->
name|last_time
operator|=
name|ink_undo
operator|->
name|last_time
expr_stmt|;
name|ink_undo
operator|->
name|last_time
operator|=
name|tmp_double
expr_stmt|;
name|tmp_int
operator|=
name|ink_undo
operator|->
name|ink
operator|->
name|init_velocity
expr_stmt|;
name|ink_undo
operator|->
name|ink
operator|->
name|init_velocity
operator|=
name|ink_undo
operator|->
name|init_velocity
expr_stmt|;
name|ink_undo
operator|->
name|init_velocity
operator|=
name|tmp_int
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|undo_free_ink (GimpUndo * undo,GimpUndoMode undo_mode)
name|undo_free_ink
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|InkUndo
modifier|*
name|ink_undo
init|=
name|undo
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|ink_undo
operator|->
name|ink
condition|)
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|ink_undo
operator|->
name|ink
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|ink_undo
operator|->
name|ink
argument_list|)
expr_stmt|;
if|if
condition|(
name|ink_undo
operator|->
name|last_blob
condition|)
name|g_free
argument_list|(
name|ink_undo
operator|->
name|last_blob
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ink_undo
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

