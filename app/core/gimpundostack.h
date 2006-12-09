begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UNDO_STACK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UNDO_STACK_H__
define|#
directive|define
name|__GIMP_UNDO_STACK_H__
end_define

begin_include
include|#
directive|include
file|"gimpundo.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_UNDO_STACK
define|#
directive|define
name|GIMP_TYPE_UNDO_STACK
value|(gimp_undo_stack_get_type ())
end_define

begin_define
DECL|macro|GIMP_UNDO_STACK (obj)
define|#
directive|define
name|GIMP_UNDO_STACK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_UNDO_STACK, GimpUndoStack))
end_define

begin_define
DECL|macro|GIMP_UNDO_STACK_CLASS (klass)
define|#
directive|define
name|GIMP_UNDO_STACK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_UNDO_STACK, GimpUndoStackClass))
end_define

begin_define
DECL|macro|GIMP_IS_UNDO_STACK (obj)
define|#
directive|define
name|GIMP_IS_UNDO_STACK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_UNDO_STACK))
end_define

begin_define
DECL|macro|GIMP_IS_UNDO_STACK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_UNDO_STACK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_UNDO_STACK))
end_define

begin_define
DECL|macro|GIMP_UNDO_STACK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_UNDO_STACK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_UNDO_STACK, GimpUndoStackClass))
end_define

begin_typedef
DECL|typedef|GimpUndoStackClass
typedef|typedef
name|struct
name|_GimpUndoStackClass
name|GimpUndoStackClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUndoStack
struct|struct
name|_GimpUndoStack
block|{
DECL|member|parent_instance
name|GimpUndo
name|parent_instance
decl_stmt|;
DECL|member|undos
name|GimpContainer
modifier|*
name|undos
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpUndoStackClass
struct|struct
name|_GimpUndoStackClass
block|{
DECL|member|parent_class
name|GimpUndoClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_undo_stack_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpUndoStack
modifier|*
name|gimp_undo_stack_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_undo_stack_push_undo
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUndo
modifier|*
name|gimp_undo_stack_pop_undo
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
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
name|GimpUndo
modifier|*
name|gimp_undo_stack_free_bottom
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUndo
modifier|*
name|gimp_undo_stack_peek
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_undo_stack_get_depth
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UNDO_STACK_H__ */
end_comment

end_unit

