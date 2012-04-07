begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_CORE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_CORE_H__
define|#
directive|define
name|__GIMP_BRUSH_CORE_H__
end_define

begin_include
include|#
directive|include
file|"gimppaintcore.h"
end_include

begin_define
DECL|macro|BRUSH_CORE_SUBSAMPLE
define|#
directive|define
name|BRUSH_CORE_SUBSAMPLE
value|4
end_define

begin_define
DECL|macro|BRUSH_CORE_SOLID_SUBSAMPLE
define|#
directive|define
name|BRUSH_CORE_SOLID_SUBSAMPLE
value|2
end_define

begin_define
DECL|macro|BRUSH_CORE_JITTER_LUTSIZE
define|#
directive|define
name|BRUSH_CORE_JITTER_LUTSIZE
value|360
end_define

begin_define
DECL|macro|GIMP_TYPE_BRUSH_CORE
define|#
directive|define
name|GIMP_TYPE_BRUSH_CORE
value|(gimp_brush_core_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH_CORE (obj)
define|#
directive|define
name|GIMP_BRUSH_CORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BRUSH_CORE, GimpBrushCore))
end_define

begin_define
DECL|macro|GIMP_BRUSH_CORE_CLASS (klass)
define|#
directive|define
name|GIMP_BRUSH_CORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BRUSH_CORE, GimpBrushCoreClass))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_CORE (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_CORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BRUSH_CORE))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_CORE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRUSH_CORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BRUSH_CORE))
end_define

begin_define
DECL|macro|GIMP_BRUSH_CORE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BRUSH_CORE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BRUSH_CORE, GimpBrushCoreClass))
end_define

begin_typedef
DECL|typedef|GimpBrushCoreClass
typedef|typedef
name|struct
name|_GimpBrushCoreClass
name|GimpBrushCoreClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrushCore
struct|struct
name|_GimpBrushCore
block|{
DECL|member|parent_instance
name|GimpPaintCore
name|parent_instance
decl_stmt|;
DECL|member|main_brush
name|GimpBrush
modifier|*
name|main_brush
decl_stmt|;
DECL|member|brush
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
DECL|member|dynamics
name|GimpDynamics
modifier|*
name|dynamics
decl_stmt|;
DECL|member|spacing
name|gdouble
name|spacing
decl_stmt|;
DECL|member|scale
name|gdouble
name|scale
decl_stmt|;
DECL|member|angle
name|gdouble
name|angle
decl_stmt|;
DECL|member|hardness
name|gdouble
name|hardness
decl_stmt|;
DECL|member|aspect_ratio
name|gdouble
name|aspect_ratio
decl_stmt|;
comment|/*  brush buffers  */
DECL|member|pressure_brush
name|TempBuf
modifier|*
name|pressure_brush
decl_stmt|;
DECL|member|solid_brushes
name|TempBuf
modifier|*
name|solid_brushes
index|[
name|BRUSH_CORE_SOLID_SUBSAMPLE
index|]
index|[
name|BRUSH_CORE_SOLID_SUBSAMPLE
index|]
decl_stmt|;
DECL|member|last_solid_brush_mask
specifier|const
name|TempBuf
modifier|*
name|last_solid_brush_mask
decl_stmt|;
DECL|member|solid_cache_invalid
name|gboolean
name|solid_cache_invalid
decl_stmt|;
DECL|member|transform_brush
specifier|const
name|TempBuf
modifier|*
name|transform_brush
decl_stmt|;
DECL|member|transform_pixmap
specifier|const
name|TempBuf
modifier|*
name|transform_pixmap
decl_stmt|;
DECL|member|subsample_brushes
name|TempBuf
modifier|*
name|subsample_brushes
index|[
name|BRUSH_CORE_SUBSAMPLE
operator|+
literal|1
index|]
index|[
name|BRUSH_CORE_SUBSAMPLE
operator|+
literal|1
index|]
decl_stmt|;
DECL|member|last_subsample_brush_mask
specifier|const
name|TempBuf
modifier|*
name|last_subsample_brush_mask
decl_stmt|;
DECL|member|subsample_cache_invalid
name|gboolean
name|subsample_cache_invalid
decl_stmt|;
DECL|member|jitter
name|gdouble
name|jitter
decl_stmt|;
DECL|member|jitter_lut_x
name|gdouble
name|jitter_lut_x
index|[
name|BRUSH_CORE_JITTER_LUTSIZE
index|]
decl_stmt|;
DECL|member|jitter_lut_y
name|gdouble
name|jitter_lut_y
index|[
name|BRUSH_CORE_JITTER_LUTSIZE
index|]
decl_stmt|;
DECL|member|rand
name|GRand
modifier|*
name|rand
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrushCoreClass
struct|struct
name|_GimpBrushCoreClass
block|{
DECL|member|parent_class
name|GimpPaintCoreClass
name|parent_class
decl_stmt|;
comment|/*  Set for tools that don't mind if the brush changes while painting  */
DECL|member|handles_changing_brush
name|gboolean
name|handles_changing_brush
decl_stmt|;
comment|/*  Set for tools that don't mind if the brush scales while painting  */
DECL|member|handles_transforming_brush
name|gboolean
name|handles_transforming_brush
decl_stmt|;
comment|/*  Set for tools that don't mind if the brush scales mid stroke  */
DECL|member|handles_dynamic_transforming_brush
name|gboolean
name|handles_dynamic_transforming_brush
decl_stmt|;
DECL|member|set_brush
name|void
function_decl|(
modifier|*
name|set_brush
function_decl|)
parameter_list|(
name|GimpBrushCore
modifier|*
name|core
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
DECL|member|set_dynamics
name|void
function_decl|(
modifier|*
name|set_dynamics
function_decl|)
parameter_list|(
name|GimpBrushCore
modifier|*
name|core
parameter_list|,
name|GimpDynamics
modifier|*
name|brush
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_brush_core_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_brush_core_set_brush
parameter_list|(
name|GimpBrushCore
modifier|*
name|core
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_core_set_dynamics
parameter_list|(
name|GimpBrushCore
modifier|*
name|core
parameter_list|,
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_core_paste_canvas
parameter_list|(
name|GimpBrushCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gdouble
name|brush_opacity
parameter_list|,
name|gdouble
name|image_opacity
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpBrushApplicationMode
name|brush_hardness
parameter_list|,
name|gdouble
name|dynamic_hardness
parameter_list|,
name|GimpPaintApplicationMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_core_replace_canvas
parameter_list|(
name|GimpBrushCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gdouble
name|brush_opacity
parameter_list|,
name|gdouble
name|image_opacity
parameter_list|,
name|GimpBrushApplicationMode
name|brush_hardness
parameter_list|,
name|gdouble
name|dynamic_hardness
parameter_list|,
name|GimpPaintApplicationMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_core_color_area_with_pixmap
parameter_list|(
name|GimpBrushCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|TempBuf
modifier|*
name|area
parameter_list|,
name|gint
name|area_x
parameter_list|,
name|gint
name|area_y
parameter_list|,
name|GimpBrushApplicationMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|TempBuf
modifier|*
name|gimp_brush_core_get_brush_mask
parameter_list|(
name|GimpBrushCore
modifier|*
name|core
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpBrushApplicationMode
name|brush_hardness
parameter_list|,
name|gdouble
name|dynamic_hardness
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_core_eval_transform_dynamics
parameter_list|(
name|GimpBrushCore
modifier|*
name|paint_core
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
comment|/*  __GIMP_BRUSH_CORE_H__  */
end_comment

end_unit

