begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE__UNDO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE__UNDO_H__
define|#
directive|define
name|__GIMP_IMAGE__UNDO_H__
end_define

begin_function_decl
name|gboolean
name|gimp_image_undo
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_redo
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_strong_undo
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_strong_redo
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUndoStack
modifier|*
name|gimp_image_get_undo_stack
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUndoStack
modifier|*
name|gimp_image_get_redo_stack
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_undo_free
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_undo_group_count
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_group_start
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUndoType
name|undo_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_group_end
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GimpUndo
modifier|*
name|gimp_image_undo_push
argument_list|(
name|GimpImage
operator|*
name|image
argument_list|,
name|GType
name|object_type
argument_list|,
name|GimpUndoType
name|undo_type
argument_list|,
specifier|const
name|gchar
operator|*
name|name
argument_list|,
name|GimpDirtyMask
name|dirty_mask
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpUndo
modifier|*
name|gimp_image_undo_can_compress
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|object_type
parameter_list|,
name|GimpUndoType
name|undo_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUndo
modifier|*
name|gimp_image_undo_get_fadeable
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE__UNDO_H__ */
end_comment

end_unit

