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
file|"gimppaintcore.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/****************/
end_comment

begin_comment
comment|/*  Paint Undo  */
end_comment

begin_comment
comment|/****************/
end_comment

begin_typedef
DECL|typedef|PaintUndo
typedef|typedef
name|struct
name|_PaintUndo
name|PaintUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_PaintUndo
struct|struct
name|_PaintUndo
block|{
DECL|member|core
name|GimpPaintCore
modifier|*
name|core
decl_stmt|;
DECL|member|last_coords
name|GimpCoords
name|last_coords
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|gboolean
name|undo_pop_paint
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
name|undo_free_paint
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
DECL|function|gimp_paint_core_push_undo (GimpImage * gimage,const gchar * undo_desc,GimpPaintCore * core)
name|gimp_paint_core_push_undo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GimpPaintCore
modifier|*
name|core
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|new
decl_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_CORE
argument_list|(
name|core
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|new
operator|=
name|gimp_image_undo_push
argument_list|(
name|gimage
argument_list|,
sizeof|sizeof
argument_list|(
name|PaintUndo
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|PaintUndo
argument_list|)
argument_list|,
name|GIMP_UNDO_PAINT
argument_list|,
name|undo_desc
argument_list|,
name|FALSE
argument_list|,
name|undo_pop_paint
argument_list|,
name|undo_free_paint
argument_list|)
operator|)
condition|)
block|{
name|PaintUndo
modifier|*
name|pu
decl_stmt|;
name|pu
operator|=
name|new
operator|->
name|data
expr_stmt|;
name|pu
operator|->
name|core
operator|=
name|core
expr_stmt|;
name|pu
operator|->
name|last_coords
operator|=
name|core
operator|->
name|start_coords
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|core
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|pu
operator|->
name|core
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
DECL|function|undo_pop_paint (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|undo_pop_paint
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
name|PaintUndo
modifier|*
name|pu
decl_stmt|;
name|pu
operator|=
operator|(
name|PaintUndo
operator|*
operator|)
name|undo
operator|->
name|data
expr_stmt|;
comment|/*  only pop if the core still exists  */
if|if
condition|(
name|pu
operator|->
name|core
condition|)
block|{
name|GimpCoords
name|tmp_coords
decl_stmt|;
name|tmp_coords
operator|=
name|pu
operator|->
name|core
operator|->
name|last_coords
expr_stmt|;
name|pu
operator|->
name|core
operator|->
name|last_coords
operator|=
name|pu
operator|->
name|last_coords
expr_stmt|;
name|pu
operator|->
name|last_coords
operator|=
name|tmp_coords
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
DECL|function|undo_free_paint (GimpUndo * undo,GimpUndoMode undo_mode)
name|undo_free_paint
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|PaintUndo
modifier|*
name|pu
decl_stmt|;
name|pu
operator|=
operator|(
name|PaintUndo
operator|*
operator|)
name|undo
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|pu
operator|->
name|core
condition|)
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|pu
operator|->
name|core
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|pu
operator|->
name|core
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pu
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

