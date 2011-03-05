begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpstrokeoptions.h  * Copyright (C) 2003 Simon Budig  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_STROKE_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_STROKE_OPTIONS_H__
define|#
directive|define
name|__GIMP_STROKE_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"gimpfilloptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_STROKE_OPTIONS
define|#
directive|define
name|GIMP_TYPE_STROKE_OPTIONS
value|(gimp_stroke_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_STROKE_OPTIONS (obj)
define|#
directive|define
name|GIMP_STROKE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_STROKE_OPTIONS, GimpStrokeOptions))
end_define

begin_define
DECL|macro|GIMP_STROKE_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_STROKE_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_STROKE_OPTIONS, GimpStrokeOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_STROKE_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_STROKE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_STROKE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_STROKE_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_STROKE_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_STROKE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_STROKE_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_STROKE_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_STROKE_OPTIONS, GimpStrokeOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpStrokeOptionsClass
typedef|typedef
name|struct
name|_GimpStrokeOptionsClass
name|GimpStrokeOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpStrokeOptions
struct|struct
name|_GimpStrokeOptions
block|{
DECL|member|parent_instance
name|GimpFillOptions
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpStrokeOptionsClass
struct|struct
name|_GimpStrokeOptionsClass
block|{
DECL|member|parent_class
name|GimpFillOptionsClass
name|parent_class
decl_stmt|;
DECL|member|dash_info_changed
name|void
function_decl|(
modifier|*
name|dash_info_changed
function_decl|)
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|stroke_options
parameter_list|,
name|GimpDashPreset
name|preset
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_stroke_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpStrokeOptions
modifier|*
name|gimp_stroke_options_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|use_context_color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpStrokeMethod
name|gimp_stroke_options_get_method
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_stroke_options_get_width
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|gimp_stroke_options_get_unit
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCapStyle
name|gimp_stroke_options_get_cap_style
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpJoinStyle
name|gimp_stroke_options_get_join_style
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_stroke_options_get_miter_limit
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_stroke_options_get_dash_offset
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GArray
modifier|*
name|gimp_stroke_options_get_dash_info
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPaintOptions
modifier|*
name|gimp_stroke_options_get_paint_options
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_stroke_options_get_emulate_dynamics
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_options_take_dash_pattern
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
name|GimpDashPreset
name|preset
parameter_list|,
name|GArray
modifier|*
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_options_prepare
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|use_default_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_options_finish
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_STROKE_OPTIONS_H__ */
end_comment

end_unit

