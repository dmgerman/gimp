begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpvectors.h  * Copyright (C) 2002 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VECTORS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VECTORS_H__
define|#
directive|define
name|__GIMP_VECTORS_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_VECTORS
define|#
directive|define
name|GIMP_TYPE_VECTORS
value|(gimp_vectors_get_type ())
end_define

begin_define
DECL|macro|GIMP_VECTORS (obj)
define|#
directive|define
name|GIMP_VECTORS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VECTORS, GimpVectors))
end_define

begin_define
DECL|macro|GIMP_VECTORS_CLASS (klass)
define|#
directive|define
name|GIMP_VECTORS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VECTORS, GimpVectorsClass))
end_define

begin_define
DECL|macro|GIMP_IS_VECTORS (obj)
define|#
directive|define
name|GIMP_IS_VECTORS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_VECTORS))
end_define

begin_define
DECL|macro|GIMP_IS_VECTORS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VECTORS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VECTORS))
end_define

begin_define
DECL|macro|GIMP_VECTORS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VECTORS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VECTORS, GimpVectorsClass))
end_define

begin_struct
DECL|struct|_GimpVectors
struct|struct
name|_GimpVectors
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
DECL|member|visible
name|gboolean
name|visible
decl_stmt|;
comment|/* controls visibility            */
DECL|member|locked
name|gboolean
name|locked
decl_stmt|;
comment|/* transformation locking         */
DECL|member|strokes
name|GimpStroke
modifier|*
name|strokes
decl_stmt|;
comment|/* The first stroke               */
comment|/* Stuff missing */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpVectorsClass
struct|struct
name|_GimpVectorsClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
DECL|member|changed
name|void
function_decl|(
modifier|*
name|changed
function_decl|)
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
DECL|member|removed
name|void
function_decl|(
modifier|*
name|removed
function_decl|)
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
DECL|member|stroke_add
name|void
function_decl|(
modifier|*
name|stroke_add
function_decl|)
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
DECL|member|stroke_get
name|GimpStroke
modifier|*
function_decl|(
modifier|*
name|stroke_get
function_decl|)
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
function_decl|;
DECL|member|stroke_get_next
name|GimpStroke
modifier|*
function_decl|(
modifier|*
name|stroke_get_next
function_decl|)
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|prev
parameter_list|)
function_decl|;
DECL|member|stroke_get_length
name|gdouble
function_decl|(
modifier|*
name|stroke_get_length
function_decl|)
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
DECL|member|anchor_get
name|GimpAnchor
modifier|*
function_decl|(
modifier|*
name|anchor_get
function_decl|)
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
name|GimpStroke
modifier|*
modifier|*
name|ret_stroke
parameter_list|)
function_decl|;
DECL|member|anchor_delete
name|void
function_decl|(
modifier|*
name|anchor_delete
function_decl|)
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|)
function_decl|;
DECL|member|get_length
name|gdouble
function_decl|(
modifier|*
name|get_length
function_decl|)
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpAnchor
modifier|*
name|start
parameter_list|)
function_decl|;
DECL|member|get_distance
name|gdouble
function_decl|(
modifier|*
name|get_distance
function_decl|)
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
function_decl|;
DECL|member|interpolate
name|gint
function_decl|(
modifier|*
name|interpolate
function_decl|)
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|gdouble
name|precision
parameter_list|,
specifier|const
name|gint
name|max_points
parameter_list|,
name|GimpCoords
modifier|*
name|ret_coords
parameter_list|)
function_decl|;
DECL|member|make_bezier
name|GimpVectors
modifier|*
function_decl|(
modifier|*
name|make_bezier
function_decl|)
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/*  vectors utility functions  */
end_comment

begin_decl_stmt
name|GType
name|gimp_vectors_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_vectors_set_image
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_vectors_get_image
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* accessing / modifying the anchors */
end_comment

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_vectors_anchor_get
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
name|GimpStroke
modifier|*
modifier|*
name|ret_stroke
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* prev == NULL: "first" anchor */
end_comment

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_vectors_anchor_get_next
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpAnchor
modifier|*
name|prev
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* type will be an xorable enum:  * VECTORS_NONE, VECTORS_FIX_ANGLE, VECTORS_FIX_RATIO, VECTORS_RESTRICT_ANGLE  *  or so.  */
end_comment

begin_function_decl
name|void
name|gimp_vectors_anchor_move_relative
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|deltacoord
parameter_list|,
specifier|const
name|gint
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vectors_anchor_move_absolute
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
specifier|const
name|gint
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vectors_anchor_delete
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* GimpStroke is a connected component of a GimpVectors object */
end_comment

begin_function_decl
name|void
name|gimp_vectors_stroke_add
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpStroke
modifier|*
name|gimp_vectors_stroke_get
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* prev == NULL: "first" stroke */
end_comment

begin_function_decl
name|GimpStroke
modifier|*
name|gimp_vectors_stroke_get_next
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|prev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vectors_stroke_get_length
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* accessing the shape of the curve */
end_comment

begin_function_decl
name|gdouble
name|gimp_vectors_get_length
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpAnchor
modifier|*
name|start
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vectors_get_distance
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* returns the number of valid coordinates */
end_comment

begin_function_decl
name|gint
name|gimp_vectors_interpolate
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|gdouble
name|precision
parameter_list|,
specifier|const
name|gint
name|max_points
parameter_list|,
name|GimpCoords
modifier|*
name|ret_coords
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Allow a singular temorary anchor (marking the "working point")? */
end_comment

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_vectors_temp_anchor_get
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_vectors_temp_anchor_set
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_temp_anchor_fix
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* usually overloaded */
end_comment

begin_comment
comment|/* creates a bezier approximation. */
end_comment

begin_function_decl
name|GimpVectors
modifier|*
name|gimp_vectors_make_bezier
parameter_list|(
specifier|const
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
comment|/* __GIMP_VECTORS_H__ */
end_comment

end_unit

