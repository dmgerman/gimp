begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *   * gimpbezier.h  * Copyright (C) 2001 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BEZIER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BEZIER_H__
define|#
directive|define
name|__GIMP_BEZIER_H__
end_define

begin_comment
comment|/* Temporary implementation with straight lines. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"glib-object.h"
end_include

begin_include
include|#
directive|include
file|"vectors-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectors.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BEZIER
define|#
directive|define
name|GIMP_TYPE_BEZIER
value|(gimp_bezier_get_type ())
end_define

begin_define
DECL|macro|GIMP_BEZIER (obj)
define|#
directive|define
name|GIMP_BEZIER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BEZIER, GimpBezier))
end_define

begin_define
DECL|macro|GIMP_BEZIER_CLASS (klass)
define|#
directive|define
name|GIMP_BEZIER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BEZIER, GimpBezierClass))
end_define

begin_define
DECL|macro|GIMP_IS_BEZIER (obj)
define|#
directive|define
name|GIMP_IS_BEZIER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BEZIER))
end_define

begin_define
DECL|macro|GIMP_IS_BEZIER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BEZIER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BEZIER))
end_define

begin_define
DECL|macro|GIMP_BEZIER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BEZIER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BEZIER, GimpBezierClass))
end_define

begin_comment
comment|/* Bezier Data Structure */
end_comment

begin_struct
DECL|struct|_GimpBezier
struct|struct
name|_GimpBezier
block|{
DECL|member|parent_instance
name|GimpVectors
name|parent_instance
decl_stmt|;
DECL|member|anchors
name|GList
modifier|*
name|anchors
decl_stmt|;
DECL|member|strokes
name|GList
modifier|*
name|strokes
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBezierClass
struct|struct
name|_GimpBezierClass
block|{
DECL|member|parent_class
name|GimpVectorsClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_bezier_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* accessing / modifying the anchors */
end_comment

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_bezier_anchor_get
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
comment|/* prev == NULL: "first" anchor */
end_comment

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_bezier_anchor_get_next
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

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_bezier_anchor_set
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
specifier|const
name|gboolean
name|new_stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_anchor_move_relative
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
name|gimp_bezier_anchor_move_absolute
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
name|gimp_bezier_anchor_delete
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
comment|/* accessing the shape of the curve */
end_comment

begin_function_decl
name|gdouble
name|gimp_bezier_get_length
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

begin_comment
comment|/* returns the number of valid coordinates */
end_comment

begin_function_decl
name|gint
name|gimp_bezier_interpolate
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|start
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
name|gimp_bezier_temp_anchor_get
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
name|gimp_bezier_temp_anchor_set
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
name|gimp_bezier_temp_anchor_fix
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_temp_anchor_delete
parameter_list|(
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
comment|/* __GIMP_BEZIER_H__ */
end_comment

end_unit

