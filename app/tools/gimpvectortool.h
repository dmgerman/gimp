begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Vector tool  * Copyright (C) 2003 Simon Budig<simon@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpdrawtool.h"
end_include

begin_comment
comment|/*  possible vector functions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2922b9120103
block|{
DECL|enumerator|VECTORS_SELECT_VECTOR
name|VECTORS_SELECT_VECTOR
block|,
DECL|enumerator|VECTORS_CREATE_VECTOR
name|VECTORS_CREATE_VECTOR
block|,
DECL|enumerator|VECTORS_CREATE_STROKE
name|VECTORS_CREATE_STROKE
block|,
DECL|enumerator|VECTORS_ADD_ANCHOR
name|VECTORS_ADD_ANCHOR
block|,
DECL|enumerator|VECTORS_MOVE_ANCHOR
name|VECTORS_MOVE_ANCHOR
block|,
DECL|enumerator|VECTORS_MOVE_ANCHORSET
name|VECTORS_MOVE_ANCHORSET
block|,
DECL|enumerator|VECTORS_MOVE_HANDLE
name|VECTORS_MOVE_HANDLE
block|,
DECL|enumerator|VECTORS_MOVE_CURVE
name|VECTORS_MOVE_CURVE
block|,
DECL|enumerator|VECTORS_MOVE_STROKE
name|VECTORS_MOVE_STROKE
block|,
DECL|enumerator|VECTORS_MOVE_VECTORS
name|VECTORS_MOVE_VECTORS
block|,
DECL|enumerator|VECTORS_INSERT_ANCHOR
name|VECTORS_INSERT_ANCHOR
block|,
DECL|enumerator|VECTORS_DELETE_ANCHOR
name|VECTORS_DELETE_ANCHOR
block|,
DECL|enumerator|VECTORS_CONNECT_STROKES
name|VECTORS_CONNECT_STROKES
block|,
DECL|enumerator|VECTORS_DELETE_SEGMENT
name|VECTORS_DELETE_SEGMENT
block|,
DECL|enumerator|VECTORS_CONVERT_EDGE
name|VECTORS_CONVERT_EDGE
block|,
DECL|enumerator|VECTORS_FINISHED
name|VECTORS_FINISHED
DECL|typedef|GimpVectorFunction
block|}
name|GimpVectorFunction
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

begin_define
DECL|macro|GIMP_VECTOR_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_VECTOR_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_VECTOR_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
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
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|function
name|GimpVectorFunction
name|function
decl_stmt|;
comment|/* function we're performing         */
DECL|member|restriction
name|GimpAnchorFeatureType
name|restriction
decl_stmt|;
comment|/* movement restriction              */
DECL|member|modifier_lock
name|gboolean
name|modifier_lock
decl_stmt|;
comment|/* can we toggle the Shift key?      */
DECL|member|saved_state
name|GdkModifierType
name|saved_state
decl_stmt|;
comment|/* modifier state at button_press    */
DECL|member|last_x
name|gdouble
name|last_x
decl_stmt|;
comment|/* last x coordinate                 */
DECL|member|last_y
name|gdouble
name|last_y
decl_stmt|;
comment|/* last y coordinate                 */
DECL|member|undo_motion
name|gboolean
name|undo_motion
decl_stmt|;
comment|/* we need a motion to have an undo  */
DECL|member|have_undo
name|gboolean
name|have_undo
decl_stmt|;
comment|/* did we push an undo at            */
comment|/* ..._button_press?                 */
DECL|member|cur_anchor
name|GimpAnchor
modifier|*
name|cur_anchor
decl_stmt|;
comment|/* the current Anchor                */
DECL|member|cur_anchor2
name|GimpAnchor
modifier|*
name|cur_anchor2
decl_stmt|;
comment|/* secondary Anchor (end on_curve)   */
DECL|member|cur_stroke
name|GimpStroke
modifier|*
name|cur_stroke
decl_stmt|;
comment|/* the current Stroke                */
DECL|member|cur_position
name|gdouble
name|cur_position
decl_stmt|;
comment|/* the current Position on a segment */
DECL|member|cur_vectors
name|GimpVectors
modifier|*
name|cur_vectors
decl_stmt|;
comment|/* the vectors the tool is hovering  */
comment|/* over (if different from ->vectors */
DECL|member|vectors
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
comment|/* the current Vector data           */
DECL|member|sel_count
name|gint
name|sel_count
decl_stmt|;
comment|/* number of selected anchors        */
DECL|member|sel_anchor
name|GimpAnchor
modifier|*
name|sel_anchor
decl_stmt|;
comment|/* currently selected anchor, NULL   */
comment|/* if multiple anchors are selected  */
DECL|member|sel_stroke
name|GimpStroke
modifier|*
name|sel_stroke
decl_stmt|;
comment|/* selected stroke                   */
DECL|member|saved_mode
name|GimpVectorMode
name|saved_mode
decl_stmt|;
comment|/* used by modifier_key()            */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpVectorToolClass
struct|struct
name|_GimpVectorToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_VECTOR_TOOL_H__  */
end_comment

end_unit

