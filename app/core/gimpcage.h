begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *   * gimpcage.h  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CAGE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CAGE_H__
define|#
directive|define
name|__GIMP_CAGE_H__
end_define

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmathtypes.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gegl-buffer.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_CAGE
define|#
directive|define
name|GIMP_TYPE_CAGE
value|(gimp_cage_get_type ())
end_define

begin_define
DECL|macro|GIMP_CAGE (obj)
define|#
directive|define
name|GIMP_CAGE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CAGE, GimpCage))
end_define

begin_define
DECL|macro|GIMP_CAGE_CLASS (klass)
define|#
directive|define
name|GIMP_CAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CAGE, GimpCageClass))
end_define

begin_define
DECL|macro|GIMP_IS_CAGE (obj)
define|#
directive|define
name|GIMP_IS_CAGE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CAGE))
end_define

begin_define
DECL|macro|GIMP_IS_CAGE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CAGE))
end_define

begin_define
DECL|macro|GIMP_CAGE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CAGE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CAGE, GimpCageClass))
end_define

begin_typedef
DECL|typedef|GimpCageClass
typedef|typedef
name|struct
name|_GimpCageClass
name|GimpCageClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCage
struct|struct
name|_GimpCage
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|cage_vertice_number
name|gint
name|cage_vertice_number
decl_stmt|;
comment|//number of vertices used by the cage
DECL|member|cage_vertices_max
name|gint
name|cage_vertices_max
decl_stmt|;
comment|//number of vertices allocated in memory
DECL|member|cage_vertices
name|GimpVector2
modifier|*
name|cage_vertices
decl_stmt|;
DECL|member|cage_vertices_coef
name|GeglBuffer
modifier|*
name|cage_vertices_coef
decl_stmt|;
DECL|member|cage_edges_coef
name|GeglBuffer
modifier|*
name|cage_edges_coef
decl_stmt|;
comment|//test data
DECL|member|extent
name|GeglRectangle
name|extent
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCageClass
struct|struct
name|_GimpCageClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_cage_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**  * gimp_cage_add_cage_point:  * @cage: the cage data structure  * @x: x value of the new point  * @y: y value of the new point  *   * Add a new point in the polygon of the cage, and make allocation if needed.  */
end_comment

begin_function_decl
name|void
name|gimp_cage_add_cage_point
parameter_list|(
name|GimpCage
modifier|*
name|cage
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_remove_last_cage_point
parameter_list|(
name|GimpCage
modifier|*
name|cage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_cage_is_on_handle
parameter_list|(
name|GimpCage
modifier|*
name|cage
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
name|handle_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_move_cage_point
parameter_list|(
name|GimpCage
modifier|*
name|cage
parameter_list|,
name|gint
name|point_number
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_compute_coefficient
parameter_list|(
name|GimpCage
modifier|*
name|gc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CAGE_H__ */
end_comment

end_unit

