begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VECTOR_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VECTOR_TOOL_H__
define|#
directive|define
name|__GIMP_VECTOR_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_comment
comment|/*  possible vector functions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29b474f60103
block|{
DECL|enumerator|VECTORS_CREATING
name|VECTORS_CREATING
block|,
DECL|enumerator|VECTORS_ADDING
name|VECTORS_ADDING
block|,
DECL|enumerator|VECTORS_MOVING
name|VECTORS_MOVING
block|,
DECL|enumerator|VECTORS_MOVING_ALL
name|VECTORS_MOVING_ALL
block|,
DECL|enumerator|VECTORS_GUIDING
name|VECTORS_GUIDING
block|,
DECL|enumerator|VECTORS_FINISHED
name|VECTORS_FINISHED
DECL|typedef|VectorFunction
block|}
name|VectorFunction
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_VECTOR_TOOL
define|#
directive|define
name|GIMP_TYPE_VECTOR_TOOL
value|(gimp_vector_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_VECTOR_TOOL (obj)
define|#
directive|define
name|GIMP_VECTOR_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VECTOR_TOOL, GimpVectorTool))
end_define

begin_define
DECL|macro|GIMP_VECTOR_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_VECTOR_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VECTOR_TOOL, GimpVectorToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_VECTOR_TOOL (obj)
define|#
directive|define
name|GIMP_IS_VECTOR_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_VECTOR_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_VECTOR_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VECTOR_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VECTOR_TOOL))
end_define

begin_define
DECL|macro|GIMP_VECTOR_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VECTOR_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VECTOR_TOOL, GimpVectorToolClass))
end_define

begin_typedef
DECL|typedef|GimpVectorTool
typedef|typedef
name|struct
name|_GimpVectorTool
name|GimpVectorTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVectorToolClass
typedef|typedef
name|struct
name|_GimpVectorToolClass
name|GimpVectorToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpVectorTool
struct|struct
name|_GimpVectorTool
block|{
DECL|member|parent_instance
name|GimpSelectionTool
name|parent_instance
decl_stmt|;
DECL|member|function
name|VectorFunction
name|function
decl_stmt|;
comment|/*  function we're performing     */
DECL|member|restriction
name|GimpAnchorFeatureType
name|restriction
decl_stmt|;
comment|/*  movement restriction          */
DECL|member|last_x
name|gint
name|last_x
decl_stmt|;
comment|/*  last x coordinate             */
DECL|member|last_y
name|gint
name|last_y
decl_stmt|;
comment|/*  last y coordinate             */
DECL|member|cur_anchor
name|GimpAnchor
modifier|*
name|cur_anchor
decl_stmt|;
comment|/*  The current Anchor            */
DECL|member|cur_stroke
name|GimpStroke
modifier|*
name|cur_stroke
decl_stmt|;
comment|/*  The current Stroke            */
DECL|member|vectors
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
comment|/*  The current Vector data       */
DECL|member|active_anchors
name|GList
modifier|*
name|active_anchors
decl_stmt|;
comment|/*  The currently active anchors  */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpVectorToolClass
struct|struct
name|_GimpVectorToolClass
block|{
DECL|member|parent_class
name|GimpSelectionToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_vector_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_vector_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_vector_tool_set_vectors
parameter_list|(
name|GimpVectorTool
modifier|*
name|vector_tool
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector_tool_clear_vectors
parameter_list|(
name|GimpVectorTool
modifier|*
name|vector_tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_VECTOR_TOOL_H__  */
end_comment

end_unit

