begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-nodes.h  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GEGL_NODES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GEGL_NODES_H__
define|#
directive|define
name|__GIMP_GEGL_NODES_H__
end_define

begin_function_decl
name|GeglNode
modifier|*
name|gimp_gegl_create_flatten_node
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|background
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglNode
modifier|*
name|gimp_gegl_create_apply_opacity_node
parameter_list|(
name|GeglBuffer
modifier|*
name|mask
parameter_list|,
name|gint
name|mask_offset_x
parameter_list|,
name|gint
name|mask_offset_y
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglNode
modifier|*
name|gimp_gegl_add_buffer_source
parameter_list|(
name|GeglNode
modifier|*
name|parent
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gegl_mode_node_set_mode
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|,
name|GimpLayerCompositeMode
name|composite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gegl_mode_node_set_opacity
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gegl_node_set_matrix
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gegl_node_set_color
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GEGL_NODES_H__ */
end_comment

end_unit

