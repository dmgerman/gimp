begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program Copyright (C) 1995  * Spencer Kimball and Peter Mattis  *  * gimpcanvasboundary.h  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CANVAS_BOUNDARY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CANVAS_BOUNDARY_H__
define|#
directive|define
name|__GIMP_CANVAS_BOUNDARY_H__
end_define

begin_include
include|#
directive|include
file|"gimpcanvasitem.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CANVAS_BOUNDARY
define|#
directive|define
name|GIMP_TYPE_CANVAS_BOUNDARY
value|(gimp_canvas_boundary_get_type ())
end_define

begin_define
DECL|macro|GIMP_CANVAS_BOUNDARY (obj)
define|#
directive|define
name|GIMP_CANVAS_BOUNDARY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CANVAS_BOUNDARY, GimpCanvasBoundary))
end_define

begin_define
DECL|macro|GIMP_CANVAS_BOUNDARY_CLASS (klass)
define|#
directive|define
name|GIMP_CANVAS_BOUNDARY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CANVAS_BOUNDARY, GimpCanvasBoundaryClass))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_BOUNDARY (obj)
define|#
directive|define
name|GIMP_IS_CANVAS_BOUNDARY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CANVAS_BOUNDARY))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_BOUNDARY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CANVAS_BOUNDARY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CANVAS_BOUNDARY))
end_define

begin_define
DECL|macro|GIMP_CANVAS_BOUNDARY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CANVAS_BOUNDARY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CANVAS_BOUNDARY, GimpCanvasBoundaryClass))
end_define

begin_typedef
DECL|typedef|GimpCanvasBoundary
typedef|typedef
name|struct
name|_GimpCanvasBoundary
name|GimpCanvasBoundary
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCanvasBoundaryClass
typedef|typedef
name|struct
name|_GimpCanvasBoundaryClass
name|GimpCanvasBoundaryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasBoundary
struct|struct
name|_GimpCanvasBoundary
block|{
DECL|member|parent_instance
name|GimpCanvasItem
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCanvasBoundaryClass
struct|struct
name|_GimpCanvasBoundaryClass
block|{
DECL|member|parent_class
name|GimpCanvasItemClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_canvas_boundary_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_canvas_boundary_new
parameter_list|(
specifier|const
name|BoundSeg
modifier|*
name|segs
parameter_list|,
name|gint
name|n_segs
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CANVAS_BOUNDARY_H__ */
end_comment

end_unit

