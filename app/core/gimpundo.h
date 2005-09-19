begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UNDO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UNDO_H__
define|#
directive|define
name|__GIMP_UNDO_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_struct
DECL|struct|_GimpUndoAccumulator
struct|struct
name|_GimpUndoAccumulator
block|{
DECL|member|mode_changed
name|gboolean
name|mode_changed
decl_stmt|;
DECL|member|size_changed
name|gboolean
name|size_changed
decl_stmt|;
DECL|member|resolution_changed
name|gboolean
name|resolution_changed
decl_stmt|;
DECL|member|unit_changed
name|gboolean
name|unit_changed
decl_stmt|;
DECL|member|quick_mask_changed
name|gboolean
name|quick_mask_changed
decl_stmt|;
DECL|member|alpha_changed
name|gboolean
name|alpha_changed
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_UNDO
define|#
directive|define
name|GIMP_TYPE_UNDO
value|(gimp_undo_get_type ())
end_define

begin_define
DECL|macro|GIMP_UNDO (obj)
define|#
directive|define
name|GIMP_UNDO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_UNDO, GimpUndo))
end_define

begin_define
DECL|macro|GIMP_UNDO_CLASS (klass)
define|#
directive|define
name|GIMP_UNDO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_UNDO, GimpUndoClass))
end_define

begin_define
DECL|macro|GIMP_IS_UNDO (obj)
define|#
directive|define
name|GIMP_IS_UNDO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_UNDO))
end_define

begin_define
DECL|macro|GIMP_IS_UNDO_CLASS (klass)
define|#
directive|define
name|GIMP_IS_UNDO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_UNDO))
end_define

begin_define
DECL|macro|GIMP_UNDO_GET_CLASS (obj)
define|#
directive|define
name|GIMP_UNDO_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_UNDO, GimpUndoClass))
end_define

begin_typedef
DECL|typedef|GimpUndoClass
typedef|typedef
name|struct
name|_GimpUndoClass
name|GimpUndoClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUndo
struct|struct
name|_GimpUndo
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
comment|/* the image this undo is part of     */
DECL|member|time
name|guint
name|time
decl_stmt|;
comment|/* time of undo step construction     */
DECL|member|undo_type
name|GimpUndoType
name|undo_type
decl_stmt|;
comment|/* undo type                          */
DECL|member|data
name|gpointer
name|data
decl_stmt|;
comment|/* data to implement the undo         */
DECL|member|size
name|gint64
name|size
decl_stmt|;
comment|/* size of undo item                  */
DECL|member|dirty_mask
name|GimpDirtyMask
name|dirty_mask
decl_stmt|;
comment|/* affected parts of the image        */
DECL|member|pop_func
name|GimpUndoPopFunc
name|pop_func
decl_stmt|;
comment|/* function pointer to undo pop proc  */
DECL|member|free_func
name|GimpUndoFreeFunc
name|free_func
decl_stmt|;
comment|/* function pointer to free undo data */
DECL|member|preview
name|TempBuf
modifier|*
name|preview
decl_stmt|;
DECL|member|preview_idle_id
name|guint
name|preview_idle_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpUndoClass
struct|struct
name|_GimpUndoClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
DECL|member|pop
name|void
function_decl|(
modifier|*
name|pop
function_decl|)
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
DECL|member|free
name|void
function_decl|(
modifier|*
name|free
function_decl|)
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_undo_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_undo_pop
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
name|void
name|gimp_undo_free
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

begin_function_decl
name|void
name|gimp_undo_create_preview
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|gboolean
name|create_now
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_undo_refresh_preview
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_undo_type_to_name
parameter_list|(
name|GimpUndoType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UNDO_H__ */
end_comment

end_unit

