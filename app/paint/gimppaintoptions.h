begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PAINT_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PAINT_OPTIONS_H__
define|#
directive|define
name|__GIMP_PAINT_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_define
DECL|macro|GIMP_PAINT_OPTIONS_CONTEXT_MASK
define|#
directive|define
name|GIMP_PAINT_OPTIONS_CONTEXT_MASK
value|GIMP_CONTEXT_FOREGROUND_MASK | \                                         GIMP_CONTEXT_BACKGROUND_MASK | \                                         GIMP_CONTEXT_OPACITY_MASK    | \                                         GIMP_CONTEXT_PAINT_MODE_MASK | \                                         GIMP_CONTEXT_BRUSH_MASK
end_define

begin_typedef
DECL|typedef|GimpPressureOptions
typedef|typedef
name|struct
name|_GimpPressureOptions
name|GimpPressureOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFadeOptions
typedef|typedef
name|struct
name|_GimpFadeOptions
name|GimpFadeOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGradientOptions
typedef|typedef
name|struct
name|_GimpGradientOptions
name|GimpGradientOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPressureOptions
struct|struct
name|_GimpPressureOptions
block|{
DECL|member|opacity
name|gboolean
name|opacity
decl_stmt|;
DECL|member|hardness
name|gboolean
name|hardness
decl_stmt|;
DECL|member|rate
name|gboolean
name|rate
decl_stmt|;
DECL|member|size
name|gboolean
name|size
decl_stmt|;
DECL|member|color
name|gboolean
name|color
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFadeOptions
struct|struct
name|_GimpFadeOptions
block|{
DECL|member|use_fade
name|gboolean
name|use_fade
decl_stmt|;
DECL|member|fade_length
name|gdouble
name|fade_length
decl_stmt|;
DECL|member|fade_unit
name|GimpUnit
name|fade_unit
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpGradientOptions
struct|struct
name|_GimpGradientOptions
block|{
DECL|member|use_gradient
name|gboolean
name|use_gradient
decl_stmt|;
DECL|member|gradient_reverse
name|gboolean
name|gradient_reverse
decl_stmt|;
DECL|member|gradient_length
name|gdouble
name|gradient_length
decl_stmt|;
DECL|member|gradient_unit
name|GimpUnit
name|gradient_unit
decl_stmt|;
DECL|member|gradient_repeat
name|GimpRepeatMode
name|gradient_repeat
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_PAINT_OPTIONS
define|#
directive|define
name|GIMP_TYPE_PAINT_OPTIONS
value|(gimp_paint_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_PAINT_OPTIONS (obj)
define|#
directive|define
name|GIMP_PAINT_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PAINT_OPTIONS, GimpPaintOptions))
end_define

begin_define
DECL|macro|GIMP_PAINT_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_PAINT_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PAINT_OPTIONS, GimpPaintOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_PAINT_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_PAINT_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PAINT_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_PAINT_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PAINT_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PAINT_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_PAINT_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PAINT_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PAINT_OPTIONS, GimpPaintOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpPaintOptionsClass
typedef|typedef
name|struct
name|_GimpPaintOptionsClass
name|GimpPaintOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPaintOptions
struct|struct
name|_GimpPaintOptions
block|{
DECL|member|parent_instance
name|GimpToolOptions
name|parent_instance
decl_stmt|;
DECL|member|paint_info
name|GimpPaintInfo
modifier|*
name|paint_info
decl_stmt|;
DECL|member|application_mode
name|GimpPaintApplicationMode
name|application_mode
decl_stmt|;
DECL|member|application_mode_save
name|GimpPaintApplicationMode
name|application_mode_save
decl_stmt|;
DECL|member|hard
name|gboolean
name|hard
decl_stmt|;
DECL|member|pressure_options
name|GimpPressureOptions
modifier|*
name|pressure_options
decl_stmt|;
DECL|member|fade_options
name|GimpFadeOptions
modifier|*
name|fade_options
decl_stmt|;
DECL|member|gradient_options
name|GimpGradientOptions
modifier|*
name|gradient_options
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPaintOptionsClass
struct|struct
name|_GimpPaintOptionsClass
block|{
DECL|member|parent_instance
name|GimpToolOptionsClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_paint_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpPaintOptions
modifier|*
name|gimp_paint_options_new
parameter_list|(
name|GimpPaintInfo
modifier|*
name|paint_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_paint_options_get_fade
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|pixel_dist
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_paint_options_get_gradient_color
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|pressure
parameter_list|,
name|gdouble
name|pixel_dist
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrushApplicationMode
name|gimp_paint_options_get_brush_mode
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PAINT_OPTIONS_H__  */
end_comment

end_unit

