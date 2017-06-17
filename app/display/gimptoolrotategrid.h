begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolrotategrid.h  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_ROTATE_GRID_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_ROTATE_GRID_H__
define|#
directive|define
name|__GIMP_TOOL_ROTATE_GRID_H__
end_define

begin_include
include|#
directive|include
file|"gimptooltransformgrid.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_ROTATE_GRID
define|#
directive|define
name|GIMP_TYPE_TOOL_ROTATE_GRID
value|(gimp_tool_rotate_grid_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_ROTATE_GRID (obj)
define|#
directive|define
name|GIMP_TOOL_ROTATE_GRID
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_ROTATE_GRID, GimpToolRotateGrid))
end_define

begin_define
DECL|macro|GIMP_TOOL_ROTATE_GRID_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_ROTATE_GRID_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_ROTATE_GRID, GimpToolRotateGridClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_ROTATE_GRID (obj)
define|#
directive|define
name|GIMP_IS_TOOL_ROTATE_GRID
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_ROTATE_GRID))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_ROTATE_GRID_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_ROTATE_GRID_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_ROTATE_GRID))
end_define

begin_define
DECL|macro|GIMP_TOOL_ROTATE_GRID_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_ROTATE_GRID_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_ROTATE_GRID, GimpToolRotateGridClass))
end_define

begin_typedef
DECL|typedef|GimpToolRotateGrid
typedef|typedef
name|struct
name|_GimpToolRotateGrid
name|GimpToolRotateGrid
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolRotateGridPrivate
typedef|typedef
name|struct
name|_GimpToolRotateGridPrivate
name|GimpToolRotateGridPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolRotateGridClass
typedef|typedef
name|struct
name|_GimpToolRotateGridClass
name|GimpToolRotateGridClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolRotateGrid
struct|struct
name|_GimpToolRotateGrid
block|{
DECL|member|parent_instance
name|GimpToolTransformGrid
name|parent_instance
decl_stmt|;
DECL|member|private
name|GimpToolRotateGridPrivate
modifier|*
name|private
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolRotateGridClass
struct|struct
name|_GimpToolRotateGridClass
block|{
DECL|member|parent_class
name|GimpToolTransformGridClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_rotate_grid_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolWidget
modifier|*
name|gimp_tool_rotate_grid_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|gdouble
name|pivot_x
parameter_list|,
name|gdouble
name|pivot_y
parameter_list|,
name|gdouble
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_ROTATE_GRID_H__ */
end_comment

end_unit

