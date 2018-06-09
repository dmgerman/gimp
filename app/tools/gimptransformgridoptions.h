begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TRANSFORM_GRID_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TRANSFORM_GRID_OPTIONS_H__
define|#
directive|define
name|__GIMP_TRANSFORM_GRID_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"gimptransformoptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_GRID_OPTIONS
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_GRID_OPTIONS
value|(gimp_transform_grid_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_GRID_OPTIONS (obj)
define|#
directive|define
name|GIMP_TRANSFORM_GRID_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TRANSFORM_GRID_OPTIONS, GimpTransformGridOptions))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_GRID_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_TRANSFORM_GRID_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TRANSFORM_GRID_OPTIONS, GimpTransformGridOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_GRID_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_TRANSFORM_GRID_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TRANSFORM_GRID_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_GRID_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TRANSFORM_GRID_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TRANSFORM_GRID_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_GRID_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TRANSFORM_GRID_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TRANSFORM_GRID_OPTIONS, GimpTransformGridOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpTransformGridOptions
typedef|typedef
name|struct
name|_GimpTransformGridOptions
name|GimpTransformGridOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTransformGridOptionsClass
typedef|typedef
name|struct
name|_GimpTransformGridOptionsClass
name|GimpTransformGridOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTransformGridOptions
struct|struct
name|_GimpTransformGridOptions
block|{
DECL|member|parent_instance
name|GimpTransformOptions
name|parent_instance
decl_stmt|;
DECL|member|show_preview
name|gboolean
name|show_preview
decl_stmt|;
DECL|member|preview_opacity
name|gdouble
name|preview_opacity
decl_stmt|;
DECL|member|grid_type
name|GimpGuidesType
name|grid_type
decl_stmt|;
DECL|member|grid_size
name|gint
name|grid_size
decl_stmt|;
DECL|member|constrain_move
name|gboolean
name|constrain_move
decl_stmt|;
DECL|member|constrain_scale
name|gboolean
name|constrain_scale
decl_stmt|;
DECL|member|constrain_rotate
name|gboolean
name|constrain_rotate
decl_stmt|;
DECL|member|constrain_shear
name|gboolean
name|constrain_shear
decl_stmt|;
DECL|member|constrain_perspective
name|gboolean
name|constrain_perspective
decl_stmt|;
DECL|member|frompivot_scale
name|gboolean
name|frompivot_scale
decl_stmt|;
DECL|member|frompivot_shear
name|gboolean
name|frompivot_shear
decl_stmt|;
DECL|member|frompivot_perspective
name|gboolean
name|frompivot_perspective
decl_stmt|;
DECL|member|cornersnap
name|gboolean
name|cornersnap
decl_stmt|;
DECL|member|fixedpivot
name|gboolean
name|fixedpivot
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTransformGridOptionsClass
struct|struct
name|_GimpTransformGridOptionsClass
block|{
DECL|member|parent_class
name|GimpTransformOptionsClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_transform_grid_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_transform_grid_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_transform_grid_options_show_preview
parameter_list|(
name|GimpTransformGridOptions
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
comment|/* __GIMP_TRANSFORM_GRID_OPTIONS_H__ */
end_comment

end_unit

