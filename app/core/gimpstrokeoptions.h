begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpstrokeoptions.h  * Copyright (C) 2003 Simon Budig  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpcontext.h"
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
name|GimpContext
name|parent_instance
decl_stmt|;
DECL|member|style
name|GimpStrokeStyle
name|style
decl_stmt|;
DECL|member|width
name|gdouble
name|width
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|cap_style
name|GimpCapStyle
name|cap_style
decl_stmt|;
DECL|member|join_style
name|GimpJoinStyle
name|join_style
decl_stmt|;
DECL|member|miter
name|gdouble
name|miter
decl_stmt|;
DECL|member|antialias
name|gboolean
name|antialias
decl_stmt|;
DECL|member|dash_offset
name|gdouble
name|dash_offset
decl_stmt|;
DECL|member|dash_info
name|GArray
modifier|*
name|dash_info
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
name|GimpContextClass
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
name|void
name|gimp_stroke_options_set_dash_pattern
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_STROKE_OPTIONS_H__  */
end_comment

end_unit

