begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BLEND_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BLEND_OPTIONS_H__
define|#
directive|define
name|__GIMP_BLEND_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BLEND_OPTIONS
define|#
directive|define
name|GIMP_TYPE_BLEND_OPTIONS
value|(gimp_blend_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_BLEND_OPTIONS (obj)
define|#
directive|define
name|GIMP_BLEND_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BLEND_OPTIONS, GimpBlendOptions))
end_define

begin_define
DECL|macro|GIMP_BLEND_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_BLEND_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BLEND_OPTIONS, GimpBlendOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_BLEND_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_BLEND_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BLEND_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_BLEND_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BLEND_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BLEND_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_BLEND_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BLEND_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BLEND_OPTIONS, GimpBlendOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpBlendOptions
typedef|typedef
name|struct
name|_GimpBlendOptions
name|GimpBlendOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBlendOptionsClass
typedef|typedef
name|struct
name|_GimpPaintOptionsClass
name|GimpBlendOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBlendOptions
struct|struct
name|_GimpBlendOptions
block|{
DECL|member|paint_options
name|GimpPaintOptions
name|paint_options
decl_stmt|;
DECL|member|offset
name|gdouble
name|offset
decl_stmt|;
DECL|member|gradient_type
name|GimpGradientType
name|gradient_type
decl_stmt|;
DECL|member|distance_metric
name|GeglDistanceMetric
name|distance_metric
decl_stmt|;
DECL|member|supersample
name|gboolean
name|supersample
decl_stmt|;
DECL|member|supersample_depth
name|gint
name|supersample_depth
decl_stmt|;
DECL|member|supersample_threshold
name|gdouble
name|supersample_threshold
decl_stmt|;
DECL|member|dither
name|gboolean
name|dither
decl_stmt|;
DECL|member|instant
name|gboolean
name|instant
decl_stmt|;
DECL|member|modify_active
name|gboolean
name|modify_active
decl_stmt|;
comment|/*  options gui  */
DECL|member|instant_toggle
name|GtkWidget
modifier|*
name|instant_toggle
decl_stmt|;
DECL|member|modify_active_frame
name|GtkWidget
modifier|*
name|modify_active_frame
decl_stmt|;
DECL|member|modify_active_hint
name|GtkWidget
modifier|*
name|modify_active_hint
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_blend_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_blend_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BLEND_OPTIONS_H__  */
end_comment

end_unit

