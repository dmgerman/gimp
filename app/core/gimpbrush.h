begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_H__
define|#
directive|define
name|__GIMP_BRUSH_H__
end_define

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_define
DECL|macro|GIMP_BRUSH_MAX_SIZE
define|#
directive|define
name|GIMP_BRUSH_MAX_SIZE
value|10000.0
end_define

begin_comment
DECL|macro|GIMP_BRUSH_MAX_SIZE
comment|/*Max size in either dimension in px*/
end_comment

begin_define
DECL|macro|GIMP_TYPE_BRUSH
define|#
directive|define
name|GIMP_TYPE_BRUSH
value|(gimp_brush_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH (obj)
define|#
directive|define
name|GIMP_BRUSH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BRUSH, GimpBrush))
end_define

begin_define
DECL|macro|GIMP_BRUSH_CLASS (klass)
define|#
directive|define
name|GIMP_BRUSH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BRUSH, GimpBrushClass))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH (obj)
define|#
directive|define
name|GIMP_IS_BRUSH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BRUSH))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRUSH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BRUSH))
end_define

begin_define
DECL|macro|GIMP_BRUSH_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BRUSH_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BRUSH, GimpBrushClass))
end_define

begin_typedef
DECL|typedef|GimpBrushPrivate
typedef|typedef
name|struct
name|_GimpBrushPrivate
name|GimpBrushPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrushClass
typedef|typedef
name|struct
name|_GimpBrushClass
name|GimpBrushClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrush
struct|struct
name|_GimpBrush
block|{
DECL|member|parent_instance
name|GimpData
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpBrushPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrushClass
struct|struct
name|_GimpBrushClass
block|{
DECL|member|parent_class
name|GimpDataClass
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|begin_use
name|void
function_decl|(
modifier|*
name|begin_use
function_decl|)
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
DECL|member|end_use
name|void
function_decl|(
modifier|*
name|end_use
function_decl|)
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
DECL|member|select_brush
name|GimpBrush
modifier|*
function_decl|(
modifier|*
name|select_brush
function_decl|)
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|current_coords
parameter_list|)
function_decl|;
DECL|member|want_null_motion
name|gboolean
function_decl|(
modifier|*
name|want_null_motion
function_decl|)
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|current_coords
parameter_list|)
function_decl|;
DECL|member|transform_size
name|void
function_decl|(
modifier|*
name|transform_size
function_decl|)
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
DECL|member|transform_mask
name|GimpTempBuf
modifier|*
function_decl|(
modifier|*
name|transform_mask
function_decl|)
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|)
function_decl|;
DECL|member|transform_pixmap
name|GimpTempBuf
modifier|*
function_decl|(
modifier|*
name|transform_pixmap
function_decl|)
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|)
function_decl|;
DECL|member|transform_boundary
name|GimpBezierDesc
modifier|*
function_decl|(
modifier|*
name|transform_boundary
function_decl|)
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
comment|/*  signals  */
DECL|member|spacing_changed
name|void
function_decl|(
modifier|*
name|spacing_changed
function_decl|)
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_brush_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpData
modifier|*
name|gimp_brush_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpData
modifier|*
name|gimp_brush_get_standard
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_begin_use
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_end_use
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrush
modifier|*
name|gimp_brush_select_brush
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|current_coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_brush_want_null_motion
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|current_coords
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Gets width and height of a transformed mask of the brush, for  * provided parameters.  */
end_comment

begin_function_decl
name|void
name|gimp_brush_transform_size
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpTempBuf
modifier|*
name|gimp_brush_transform_mask
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GeglNode
modifier|*
name|op
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpTempBuf
modifier|*
name|gimp_brush_transform_pixmap
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GeglNode
modifier|*
name|op
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpBezierDesc
modifier|*
name|gimp_brush_transform_boundary
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTempBuf
modifier|*
name|gimp_brush_get_mask
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTempBuf
modifier|*
name|gimp_brush_get_pixmap
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_brush_get_width
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_brush_get_height
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_brush_get_spacing
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_set_spacing
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gint
name|spacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_brush_get_x_axis
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_brush_get_y_axis
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BRUSH_H__ */
end_comment

end_unit

