begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpstroke.h  * Copyright (C) 2002 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_STROKE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_STROKE_H__
define|#
directive|define
name|__GIMP_STROKE_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_STROKE
define|#
directive|define
name|GIMP_TYPE_STROKE
value|(gimp_stroke_get_type ())
end_define

begin_define
DECL|macro|GIMP_STROKE (obj)
define|#
directive|define
name|GIMP_STROKE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_STROKE, GimpStroke))
end_define

begin_define
DECL|macro|GIMP_STROKE_CLASS (klass)
define|#
directive|define
name|GIMP_STROKE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_STROKE, GimpStrokeClass))
end_define

begin_define
DECL|macro|GIMP_IS_STROKE (obj)
define|#
directive|define
name|GIMP_IS_STROKE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_STROKE))
end_define

begin_define
DECL|macro|GIMP_IS_STROKE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_STROKE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_STROKE))
end_define

begin_define
DECL|macro|GIMP_STROKE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_STROKE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_STROKE, GimpStrokeClass))
end_define

begin_struct
DECL|struct|_GimpStroke
struct|struct
name|_GimpStroke
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|anchors
name|GList
modifier|*
name|anchors
decl_stmt|;
DECL|member|closed
name|gboolean
name|closed
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpStrokeClass
struct|struct
name|_GimpStrokeClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|changed
name|void
function_decl|(
modifier|*
name|changed
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
DECL|member|removed
name|void
function_decl|(
modifier|*
name|removed
function_decl|)
parameter_list|(
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
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
function_decl|;
DECL|member|nearest_point_get
name|gdouble
function_decl|(
modifier|*
name|nearest_point_get
function_decl|)
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
specifier|const
name|gdouble
name|precision
parameter_list|,
name|GimpCoords
modifier|*
name|ret_point
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_segment_start
parameter_list|,
name|gdouble
modifier|*
name|ret_pos
parameter_list|)
function_decl|;
DECL|member|anchor_get_next
name|GimpAnchor
modifier|*
function_decl|(
modifier|*
name|anchor_get_next
function_decl|)
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpAnchor
modifier|*
name|prev
parameter_list|)
function_decl|;
DECL|member|anchor_select
name|void
function_decl|(
modifier|*
name|anchor_select
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|,
name|gboolean
name|exclusive
parameter_list|)
function_decl|;
DECL|member|anchor_move_relative
name|void
function_decl|(
modifier|*
name|anchor_move_relative
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
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
name|GimpAnchorFeatureType
name|feature
parameter_list|)
function_decl|;
DECL|member|anchor_move_absolute
name|void
function_decl|(
modifier|*
name|anchor_move_absolute
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
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
name|GimpAnchorFeatureType
name|feature
parameter_list|)
function_decl|;
DECL|member|anchor_convert
name|void
function_decl|(
modifier|*
name|anchor_convert
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|,
name|GimpAnchorFeatureType
name|feature
parameter_list|)
function_decl|;
DECL|member|anchor_delete
name|void
function_decl|(
modifier|*
name|anchor_delete
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|)
function_decl|;
DECL|member|point_is_movable
name|gboolean
function_decl|(
modifier|*
name|point_is_movable
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|predec
parameter_list|,
name|gdouble
name|position
parameter_list|)
function_decl|;
DECL|member|point_move_relative
name|void
function_decl|(
modifier|*
name|point_move_relative
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|predec
parameter_list|,
name|gdouble
name|position
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|deltacoord
parameter_list|,
name|GimpAnchorFeatureType
name|feature
parameter_list|)
function_decl|;
DECL|member|point_move_absolute
name|void
function_decl|(
modifier|*
name|point_move_absolute
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|predec
parameter_list|,
name|gdouble
name|position
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
name|GimpAnchorFeatureType
name|feature
parameter_list|)
function_decl|;
DECL|member|open
name|GimpStroke
modifier|*
function_decl|(
modifier|*
name|open
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|end_anchor
parameter_list|)
function_decl|;
DECL|member|anchor_is_insertable
name|gboolean
function_decl|(
modifier|*
name|anchor_is_insertable
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|predec
parameter_list|,
name|gdouble
name|position
parameter_list|)
function_decl|;
DECL|member|anchor_insert
name|GimpAnchor
modifier|*
function_decl|(
modifier|*
name|anchor_insert
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|predec
parameter_list|,
name|gdouble
name|position
parameter_list|)
function_decl|;
DECL|member|is_extendable
name|gboolean
function_decl|(
modifier|*
name|is_extendable
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|neighbor
parameter_list|)
function_decl|;
DECL|member|extend
name|GimpAnchor
modifier|*
function_decl|(
modifier|*
name|extend
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpAnchor
modifier|*
name|neighbor
parameter_list|,
name|GimpVectorExtendMode
name|extend_mode
parameter_list|)
function_decl|;
DECL|member|is_empty
name|gboolean
function_decl|(
modifier|*
name|is_empty
function_decl|)
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
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
name|GimpStroke
modifier|*
name|stroke
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
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
function_decl|;
DECL|member|interpolate
name|GArray
modifier|*
function_decl|(
modifier|*
name|interpolate
function_decl|)
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|gdouble
name|precision
parameter_list|,
name|gboolean
modifier|*
name|ret_closed
parameter_list|)
function_decl|;
DECL|member|duplicate
name|GimpStroke
modifier|*
function_decl|(
modifier|*
name|duplicate
function_decl|)
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
DECL|member|make_bezier
name|GimpStroke
modifier|*
function_decl|(
modifier|*
name|make_bezier
function_decl|)
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
DECL|member|translate
name|void
function_decl|(
modifier|*
name|translate
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|)
function_decl|;
DECL|member|scale
name|void
function_decl|(
modifier|*
name|scale
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
DECL|member|resize
name|void
function_decl|(
modifier|*
name|resize
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_heigth
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
DECL|member|flip
name|void
function_decl|(
modifier|*
name|flip
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gdouble
name|axis
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
DECL|member|rotate
name|void
function_decl|(
modifier|*
name|rotate
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
DECL|member|transform
name|void
function_decl|(
modifier|*
name|transform
function_decl|)
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|GimpTransformDirection
name|direction
parameter_list|,
name|GimpInterpolationType
name|interp_type
parameter_list|,
name|gboolean
name|clip_result
parameter_list|,
name|GimpProgressFunc
name|progress_callback
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
DECL|member|get_draw_anchors
name|GList
modifier|*
function_decl|(
modifier|*
name|get_draw_anchors
function_decl|)
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
DECL|member|get_draw_controls
name|GList
modifier|*
function_decl|(
modifier|*
name|get_draw_controls
function_decl|)
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
DECL|member|get_draw_lines
name|GArray
modifier|*
function_decl|(
modifier|*
name|get_draw_lines
function_decl|)
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_stroke_get_type
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
name|gimp_stroke_anchor_get
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_stroke_nearest_point_get
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
specifier|const
name|gdouble
name|precision
parameter_list|,
name|GimpCoords
modifier|*
name|ret_point
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_segment_start
parameter_list|,
name|gdouble
modifier|*
name|ret_pos
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* prev == NULL: "first" anchor */
end_comment

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_stroke_anchor_get_next
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpAnchor
modifier|*
name|prev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_anchor_select
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|,
name|gboolean
name|exclusive
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* type will be an xorable enum:  * VECTORS_NONE, VECTORS_FIX_ANGLE, VECTORS_FIX_RATIO, VECTORS_RESTRICT_ANGLE  *  or so.  */
end_comment

begin_function_decl
name|void
name|gimp_stroke_anchor_move_relative
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|delta
parameter_list|,
name|GimpAnchorFeatureType
name|feature
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_anchor_move_absolute
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
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
name|GimpAnchorFeatureType
name|feature
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_stroke_point_is_movable
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|predec
parameter_list|,
name|gdouble
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_point_move_relative
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|predec
parameter_list|,
name|gdouble
name|position
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|deltacoord
parameter_list|,
name|GimpAnchorFeatureType
name|feature
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_point_move_absolute
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|predec
parameter_list|,
name|gdouble
name|position
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
name|GimpAnchorFeatureType
name|feature
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_close
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_anchor_convert
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|,
name|GimpAnchorFeatureType
name|feature
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_anchor_delete
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|anchor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpStroke
modifier|*
name|gimp_stroke_open
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|end_anchor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_stroke_anchor_is_insertable
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|predec
parameter_list|,
name|gdouble
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_stroke_anchor_insert
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|predec
parameter_list|,
name|gdouble
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_stroke_is_extendable
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpAnchor
modifier|*
name|neighbor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_stroke_extend
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpAnchor
modifier|*
name|neighbor
parameter_list|,
name|GimpVectorExtendMode
name|extend_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_stroke_is_empty
parameter_list|(
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
name|gimp_stroke_get_length
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_stroke_get_distance
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* returns an array of valid coordinates */
end_comment

begin_function_decl
name|GArray
modifier|*
name|gimp_stroke_interpolate
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|gdouble
name|precision
parameter_list|,
name|gboolean
modifier|*
name|closed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpStroke
modifier|*
name|gimp_stroke_duplicate
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* creates a bezier approximation. */
end_comment

begin_function_decl
name|GimpStroke
modifier|*
name|gimp_stroke_make_bezier
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_translate
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_scale
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_resize
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_flip
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gdouble
name|axis
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_rotate
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_transform
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|GimpTransformDirection
name|direction
parameter_list|,
name|GimpInterpolationType
name|interp_type
parameter_list|,
name|gboolean
name|clip_result
parameter_list|,
name|GimpProgressFunc
name|progress_callback
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_stroke_get_draw_anchors
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_stroke_get_draw_controls
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GArray
modifier|*
name|gimp_stroke_get_draw_lines
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_STROKE_H__ */
end_comment

end_unit

