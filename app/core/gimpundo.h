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
DECL|typedef|GimpUndoPopFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpUndoPopFunc
function_decl|)
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
end_typedef

begin_typedef
DECL|typedef|GimpUndoFreeFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpUndoFreeFunc
function_decl|)
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|)
function_decl|;
end_typedef

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
DECL|member|data
name|gpointer
name|data
decl_stmt|;
comment|/* data to implement the undo */
DECL|member|size
name|glong
name|size
decl_stmt|;
comment|/* size of undo item          */
DECL|member|dirties_image
name|gboolean
name|dirties_image
decl_stmt|;
comment|/* TRUE if undo mutates image */
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
DECL|member|push
name|void
function_decl|(
modifier|*
name|push
function_decl|)
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
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|gimp_undo_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUndo
modifier|*
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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

