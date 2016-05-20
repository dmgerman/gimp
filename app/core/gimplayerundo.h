begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LAYER_UNDO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LAYER_UNDO_H__
define|#
directive|define
name|__GIMP_LAYER_UNDO_H__
end_define

begin_include
include|#
directive|include
file|"gimpitemundo.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_LAYER_UNDO
define|#
directive|define
name|GIMP_TYPE_LAYER_UNDO
value|(gimp_layer_undo_get_type ())
end_define

begin_define
DECL|macro|GIMP_LAYER_UNDO (obj)
define|#
directive|define
name|GIMP_LAYER_UNDO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LAYER_UNDO, GimpLayerUndo))
end_define

begin_define
DECL|macro|GIMP_LAYER_UNDO_CLASS (klass)
define|#
directive|define
name|GIMP_LAYER_UNDO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LAYER_UNDO, GimpLayerUndoClass))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_UNDO (obj)
define|#
directive|define
name|GIMP_IS_LAYER_UNDO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LAYER_UNDO))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_UNDO_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LAYER_UNDO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LAYER_UNDO))
end_define

begin_define
DECL|macro|GIMP_LAYER_UNDO_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LAYER_UNDO_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LAYER_UNDO, GimpLayerUndoClass))
end_define

begin_typedef
DECL|typedef|GimpLayerUndo
typedef|typedef
name|struct
name|_GimpLayerUndo
name|GimpLayerUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerUndoClass
typedef|typedef
name|struct
name|_GimpLayerUndoClass
name|GimpLayerUndoClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLayerUndo
struct|struct
name|_GimpLayerUndo
block|{
DECL|member|parent_instance
name|GimpItemUndo
name|parent_instance
decl_stmt|;
DECL|member|prev_parent
name|GimpLayer
modifier|*
name|prev_parent
decl_stmt|;
DECL|member|prev_position
name|gint
name|prev_position
decl_stmt|;
comment|/*  former position in list  */
DECL|member|prev_layer
name|GimpLayer
modifier|*
name|prev_layer
decl_stmt|;
comment|/*  previous active layer    */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerUndoClass
struct|struct
name|_GimpLayerUndoClass
block|{
DECL|member|parent_class
name|GimpItemUndoClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_layer_undo_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LAYER_UNDO_H__ */
end_comment

end_unit

