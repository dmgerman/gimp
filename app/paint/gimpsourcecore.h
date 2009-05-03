begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SOURCE_CORE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SOURCE_CORE_H__
define|#
directive|define
name|__GIMP_SOURCE_CORE_H__
end_define

begin_include
include|#
directive|include
file|"gimpbrushcore.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SOURCE_CORE
define|#
directive|define
name|GIMP_TYPE_SOURCE_CORE
value|(gimp_source_core_get_type ())
end_define

begin_define
DECL|macro|GIMP_SOURCE_CORE (obj)
define|#
directive|define
name|GIMP_SOURCE_CORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SOURCE_CORE, GimpSourceCore))
end_define

begin_define
DECL|macro|GIMP_SOURCE_CORE_CLASS (klass)
define|#
directive|define
name|GIMP_SOURCE_CORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SOURCE_CORE, GimpSourceCoreClass))
end_define

begin_define
DECL|macro|GIMP_IS_SOURCE_CORE (obj)
define|#
directive|define
name|GIMP_IS_SOURCE_CORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SOURCE_CORE))
end_define

begin_define
DECL|macro|GIMP_IS_SOURCE_CORE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SOURCE_CORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SOURCE_CORE))
end_define

begin_define
DECL|macro|GIMP_SOURCE_CORE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SOURCE_CORE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SOURCE_CORE, GimpSourceCoreClass))
end_define

begin_typedef
DECL|typedef|GimpSourceCoreClass
typedef|typedef
name|struct
name|_GimpSourceCoreClass
name|GimpSourceCoreClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSourceCore
struct|struct
name|_GimpSourceCore
block|{
DECL|member|parent_instance
name|GimpBrushCore
name|parent_instance
decl_stmt|;
DECL|member|set_source
name|gboolean
name|set_source
decl_stmt|;
DECL|member|src_drawable
name|GimpDrawable
modifier|*
name|src_drawable
decl_stmt|;
DECL|member|src_x
name|gdouble
name|src_x
decl_stmt|;
DECL|member|src_y
name|gdouble
name|src_y
decl_stmt|;
DECL|member|orig_src_x
name|gdouble
name|orig_src_x
decl_stmt|;
DECL|member|orig_src_y
name|gdouble
name|orig_src_y
decl_stmt|;
DECL|member|offset_x
name|gdouble
name|offset_x
decl_stmt|;
DECL|member|offset_y
name|gdouble
name|offset_y
decl_stmt|;
DECL|member|first_stroke
name|gboolean
name|first_stroke
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSourceCoreClass
struct|struct
name|_GimpSourceCoreClass
block|{
DECL|member|parent_class
name|GimpBrushCoreClass
name|parent_class
decl_stmt|;
DECL|member|get_source
name|gboolean
function_decl|(
modifier|*
name|get_source
function_decl|)
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|TempBuf
modifier|*
name|paint_area
parameter_list|,
name|gint
modifier|*
name|paint_area_offset_x
parameter_list|,
name|gint
modifier|*
name|paint_area_offset_y
parameter_list|,
name|gint
modifier|*
name|paint_area_width
parameter_list|,
name|gint
modifier|*
name|paint_area_height
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|)
function_decl|;
DECL|member|motion
name|void
function_decl|(
modifier|*
name|motion
function_decl|)
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|TempBuf
modifier|*
name|paint_area
parameter_list|,
name|gint
name|paint_area_offset_x
parameter_list|,
name|gint
name|paint_area_offset_y
parameter_list|,
name|gint
name|paint_area_width
parameter_list|,
name|gint
name|paint_area_height
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_source_core_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* TEMP HACK */
end_comment

begin_function_decl
name|void
name|gimp_source_core_motion
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SOURCE_CORE_H__  */
end_comment

end_unit

