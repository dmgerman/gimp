begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpobject.h"
end_include

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
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_BRUSH, GimpBrush))
end_define

begin_define
DECL|macro|GIMP_BRUSH_CLASS (klass)
define|#
directive|define
name|GIMP_BRUSH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BRUSH, GimpBrushClass))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH (obj)
define|#
directive|define
name|GIMP_IS_BRUSH
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_BRUSH))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRUSH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BRUSH))
end_define

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
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
comment|/*  actual filename--brush's location on disk  */
DECL|member|spacing
name|gint
name|spacing
decl_stmt|;
comment|/*  brush's spacing                            */
DECL|member|x_axis
name|GimpVector2
name|x_axis
decl_stmt|;
comment|/*  for calculating brush spacing              */
DECL|member|y_axis
name|GimpVector2
name|y_axis
decl_stmt|;
comment|/*  for calculating brush spacing              */
DECL|member|mask
name|TempBuf
modifier|*
name|mask
decl_stmt|;
comment|/*  the actual mask                            */
DECL|member|pixmap
name|TempBuf
modifier|*
name|pixmap
decl_stmt|;
comment|/*  optional pixmap data                       */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrushClass
struct|struct
name|_GimpBrushClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|dirty
name|void
function_decl|(
modifier|*
name|dirty
function_decl|)
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
comment|/* FIXME: these are no virtual function pointers but bad hacks: */
DECL|member|select_brush
name|GimpBrush
modifier|*
function_decl|(
modifier|*
name|select_brush
function_decl|)
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|)
function_decl|;
DECL|member|want_null_motion
name|gboolean
function_decl|(
modifier|*
name|want_null_motion
function_decl|)
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_brush_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrush
modifier|*
name|gimp_brush_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrush
modifier|*
name|gimp_brush_load_brush
parameter_list|(
name|gint
name|fd
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
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
name|TempBuf
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BRUSH_H__ */
end_comment

end_unit

