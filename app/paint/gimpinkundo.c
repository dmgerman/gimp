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
file|"gimpinkundo.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_ink_undo_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ink_undo_pop
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
name|gimp_ink_undo_free
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpInkUndo,gimp_ink_undo,GIMP_TYPE_PAINT_CORE_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpInkUndo
argument_list|,
argument|gimp_ink_undo
argument_list|,
argument|GIMP_TYPE_PAINT_CORE_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_ink_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_ink_undo_class_init
parameter_list|(
name|GimpInkUndoClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpUndoClass
modifier|*
name|undo_class
init|=
name|GIMP_UNDO_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_ink_undo_constructed
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_ink_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_ink_undo_free
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ink_undo_init (GimpInkUndo * undo)
name|gimp_ink_undo_init
parameter_list|(
name|GimpInkUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ink_undo_constructed (GObject * object)
name|gimp_ink_undo_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpInkUndo
modifier|*
name|ink_undo
init|=
name|GIMP_INK_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpInk
modifier|*
name|ink
decl_stmt|;
if|if
condition|(
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
condition|)
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_INK
argument_list|(
name|GIMP_PAINT_CORE_UNDO
argument_list|(
name|ink_undo
argument_list|)
operator|->
name|paint_core
argument_list|)
argument_list|)
expr_stmt|;
name|ink
operator|=
name|GIMP_INK
argument_list|(
name|GIMP_PAINT_CORE_UNDO
argument_list|(
name|ink_undo
argument_list|)
operator|->
name|paint_core
argument_list|)
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
name|gimp_blob_duplicate
argument_list|(
name|ink
operator|->
name|start_blob
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ink_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_ink_undo_pop
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
name|GimpInkUndo
modifier|*
name|ink_undo
init|=
name|GIMP_INK_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|pop
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|,
name|accum
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_PAINT_CORE_UNDO
argument_list|(
name|ink_undo
argument_list|)
operator|->
name|paint_core
condition|)
block|{
name|GimpInk
modifier|*
name|ink
init|=
name|GIMP_INK
argument_list|(
name|GIMP_PAINT_CORE_UNDO
argument_list|(
name|ink_undo
argument_list|)
operator|->
name|paint_core
argument_list|)
decl_stmt|;
name|GimpBlob
modifier|*
name|tmp_blob
decl_stmt|;
name|tmp_blob
operator|=
name|ink
operator|->
name|last_blob
expr_stmt|;
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
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ink_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_ink_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpInkUndo
modifier|*
name|ink_undo
init|=
name|GIMP_INK_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
if|if
condition|(
name|ink_undo
operator|->
name|last_blob
condition|)
block|{
name|g_free
argument_list|(
name|ink_undo
operator|->
name|last_blob
argument_list|)
expr_stmt|;
name|ink_undo
operator|->
name|last_blob
operator|=
name|NULL
expr_stmt|;
block|}
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|free
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

