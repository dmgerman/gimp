begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROJECTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROJECTION_H__
define|#
directive|define
name|__GIMP_PROJECTION_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_typedef
DECL|typedef|GimpProjectionIdleRender
typedef|typedef
name|struct
name|_GimpProjectionIdleRender
name|GimpProjectionIdleRender
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProjectionIdleRender
struct|struct
name|_GimpProjectionIdleRender
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|base_x
name|gint
name|base_x
decl_stmt|;
DECL|member|base_y
name|gint
name|base_y
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
DECL|member|update_areas
name|GSList
modifier|*
name|update_areas
decl_stmt|;
comment|/*  flushed update areas */
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_PROJECTION
define|#
directive|define
name|GIMP_TYPE_PROJECTION
value|(gimp_projection_get_type ())
end_define

begin_define
DECL|macro|GIMP_PROJECTION (obj)
define|#
directive|define
name|GIMP_PROJECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PROJECTION, GimpProjection))
end_define

begin_define
DECL|macro|GIMP_PROJECTION_CLASS (klass)
define|#
directive|define
name|GIMP_PROJECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PROJECTION, GimpProjectionClass))
end_define

begin_define
DECL|macro|GIMP_IS_PROJECTION (obj)
define|#
directive|define
name|GIMP_IS_PROJECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PROJECTION))
end_define

begin_define
DECL|macro|GIMP_IS_PROJECTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PROJECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PROJECTION))
end_define

begin_define
DECL|macro|GIMP_PROJECTION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PROJECTION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PROJECTION, GimpProjectionClass))
end_define

begin_typedef
DECL|typedef|GimpProjectionClass
typedef|typedef
name|struct
name|_GimpProjectionClass
name|GimpProjectionClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProjection
struct|struct
name|_GimpProjection
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|projectable
name|GimpProjectable
modifier|*
name|projectable
decl_stmt|;
DECL|member|pyramid
name|TilePyramid
modifier|*
name|pyramid
decl_stmt|;
DECL|member|buffer
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
DECL|member|graph
name|GeglNode
modifier|*
name|graph
decl_stmt|;
DECL|member|sink_node
name|GeglNode
modifier|*
name|sink_node
decl_stmt|;
DECL|member|processor
name|GeglProcessor
modifier|*
name|processor
decl_stmt|;
DECL|member|update_areas
name|GSList
modifier|*
name|update_areas
decl_stmt|;
DECL|member|idle_render
name|GimpProjectionIdleRender
name|idle_render
decl_stmt|;
DECL|member|invalidate_preview
name|gboolean
name|invalidate_preview
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpProjectionClass
struct|struct
name|_GimpProjectionClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|update
name|void
function_decl|(
modifier|*
name|update
function_decl|)
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gboolean
name|now
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_projection_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpProjection
modifier|*
name|gimp_projection_new
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglNode
modifier|*
name|gimp_projection_get_sink_node
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_projection_get_tiles_at_level
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gint
name|level
parameter_list|,
name|gboolean
modifier|*
name|is_premult
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_projection_get_level
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_projection_flush
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_projection_flush_now
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_projection_finish_draw
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_projection_estimate_memsize
parameter_list|(
name|GimpImageBaseType
name|type
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PROJECTION_H__  */
end_comment

end_unit

