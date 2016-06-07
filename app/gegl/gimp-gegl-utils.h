begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-utils.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GEGL_UTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GEGL_UTILS_H__
define|#
directive|define
name|__GIMP_GEGL_UTILS_H__
end_define

begin_function_decl
name|GType
name|gimp_gegl_get_op_enum_type
parameter_list|(
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglColor
modifier|*
name|gimp_gegl_color_new
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gegl_progress_connect
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_gegl_node_get_format
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pad_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gegl_param_spec_has_key
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GEGL_UTILS_H__ */
end_comment

end_unit

