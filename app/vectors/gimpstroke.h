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
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|anchors
name|GList
modifier|*
name|anchors
decl_stmt|;
DECL|member|next
name|GimpStroke
modifier|*
name|next
decl_stmt|;
DECL|member|temp_anchor
name|GimpAnchor
modifier|*
name|temp_anchor
decl_stmt|;
comment|/* Stuff missing? */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpStrokeClass
struct|struct
name|_GimpStrokeClass
block|{
DECL|member|parent_class
name|GObjectClass
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
specifier|const
name|gint
name|type
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
specifier|const
name|gint
name|type
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
DECL|member|temp_anchor_get
name|GimpAnchor
modifier|*
function_decl|(
modifier|*
name|temp_anchor_get
function_decl|)
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
DECL|member|temp_anchor_set
name|GimpAnchor
modifier|*
function_decl|(
modifier|*
name|temp_anchor_set
function_decl|)
parameter_list|(
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
DECL|member|temp_anchor_fix
name|gboolean
function_decl|(
modifier|*
name|temp_anchor_fix
function_decl|)
parameter_list|(
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
parameter_list|,
specifier|const
name|GimpAnchor
modifier|*
name|active
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
parameter_list|,
specifier|const
name|GimpAnchor
modifier|*
name|active
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/*  stroke utility functions  */
end_comment

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
specifier|const
name|gint
name|type
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
comment|/* returns the number of valid coordinates */
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
name|ret_closed
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Allow a singular temorary anchor (marking the "working point")? */
end_comment

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_stroke_temp_anchor_get
parameter_list|(
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_stroke_temp_anchor_set
parameter_list|(
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
name|gboolean
name|gimp_stroke_temp_anchor_fix
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
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
parameter_list|,
specifier|const
name|GimpAnchor
modifier|*
name|active
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
parameter_list|,
specifier|const
name|GimpAnchor
modifier|*
name|active
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

