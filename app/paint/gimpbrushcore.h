begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|member|brush
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
DECL|member|spacing
name|gdouble
name|spacing
decl_stmt|;
DECL|member|scale
name|gdouble
name|scale
decl_stmt|;
comment|/*  brush buffers  */
DECL|member|pressure_brush
name|MaskBuf
modifier|*
name|pressure_brush
decl_stmt|;
DECL|member|solid_brushes
name|MaskBuf
modifier|*
name|solid_brushes
index|[
name|BRUSH_CORE_SOLID_SUBSAMPLE
index|]
index|[
name|BRUSH_CORE_SOLID_SUBSAMPLE
index|]
decl_stmt|;
DECL|member|last_solid_brush
name|MaskBuf
modifier|*
name|last_solid_brush
decl_stmt|;
DECL|member|solid_cache_invalid
name|gboolean
name|solid_cache_invalid
decl_stmt|;
DECL|member|scale_brush
name|MaskBuf
modifier|*
name|scale_brush
decl_stmt|;
DECL|member|last_scale_brush
name|MaskBuf
modifier|*
name|last_scale_brush
decl_stmt|;
DECL|member|last_scale_width
name|gint
name|last_scale_width
decl_stmt|;
DECL|member|last_scale_height
name|gint
name|last_scale_height
decl_stmt|;
DECL|member|scale_pixmap
name|MaskBuf
modifier|*
name|scale_pixmap
decl_stmt|;
DECL|member|last_scale_pixmap
name|MaskBuf
modifier|*
name|last_scale_pixmap
decl_stmt|;
DECL|member|last_scale_pixmap_width
name|gint
name|last_scale_pixmap_width
decl_stmt|;
DECL|member|last_scale_pixmap_height
name|gint
name|last_scale_pixmap_height
decl_stmt|;
DECL|member|kernel_brushes
name|MaskBuf
modifier|*
name|kernel_brushes
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
DECL|member|last_brush_mask
name|MaskBuf
modifier|*
name|last_brush_mask
decl_stmt|;
DECL|member|cache_invalid
name|gboolean
name|cache_invalid
decl_stmt|;
comment|/*  don't use these...  */
DECL|member|grr_brush
name|GimpBrush
modifier|*
name|grr_brush
decl_stmt|;
DECL|member|brush_bound_segs
name|BoundSeg
modifier|*
name|brush_bound_segs
decl_stmt|;
DECL|member|n_brush_bound_segs
name|gint
name|n_brush_bound_segs
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
DECL|member|use_scale
name|gboolean
name|use_scale
decl_stmt|;
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
name|gdouble
name|brush_opacity
parameter_list|,
name|gdouble
name|image_opacity
parameter_list|,
name|GimpBrushApplicationMode
name|brush_hardness
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
name|GimpImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|TempBuf
modifier|*
name|area
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|GimpBrushApplicationMode
name|mode
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

