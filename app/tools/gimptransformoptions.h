begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TRANSFORM_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TRANSFORM_OPTIONS_H_
define|#
directive|define
name|__GIMP_TRANSFORM_OPTIONS_H_
end_define

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_OPTIONS
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_OPTIONS
value|(gimp_transform_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_OPTIONS (obj)
define|#
directive|define
name|GIMP_TRANSFORM_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TRANSFORM_OPTIONS, GimpTransformOptions))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_TRANSFORM_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TRANSFORM_OPTIONS, GimpTransformOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_TRANSFORM_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TRANSFORM_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TRANSFORM_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TRANSFORM_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TRANSFORM_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TRANSFORM_OPTIONS, GimpTransformOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpTransformOptions
typedef|typedef
name|struct
name|_GimpTransformOptions
name|GimpTransformOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTransformOptionsClass
typedef|typedef
name|struct
name|_GimpToolOptionsClass
name|GimpTransformOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTransformOptions
struct|struct
name|_GimpTransformOptions
block|{
DECL|member|parent_instance
name|GimpToolOptions
name|parent_instance
decl_stmt|;
DECL|member|type
name|GimpTransformType
name|type
decl_stmt|;
DECL|member|direction
name|GimpTransformDirection
name|direction
decl_stmt|;
DECL|member|interpolation
name|GimpInterpolationType
name|interpolation
decl_stmt|;
DECL|member|supersample
name|gboolean
name|supersample
decl_stmt|;
DECL|member|recursion_level
name|gint
name|recursion_level
decl_stmt|;
DECL|member|clip
name|gboolean
name|clip
decl_stmt|;
DECL|member|preview_type
name|GimpTransformPreviewType
name|preview_type
decl_stmt|;
DECL|member|grid_type
name|GimpTransformGridType
name|grid_type
decl_stmt|;
DECL|member|grid_size
name|gint
name|grid_size
decl_stmt|;
DECL|member|constrain_1
name|gboolean
name|constrain_1
decl_stmt|;
DECL|member|constrain_2
name|gboolean
name|constrain_2
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_transform_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_transform_options_gui
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
comment|/* __GIMP_TRANSFORM_OPTIONS_H__ */
end_comment

end_unit

