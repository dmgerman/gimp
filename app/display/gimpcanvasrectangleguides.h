begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasrectangleguides.h  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CANVAS_RECTANGLE_GUIDES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CANVAS_RECTANGLE_GUIDES_H__
define|#
directive|define
name|__GIMP_CANVAS_RECTANGLE_GUIDES_H__
end_define

begin_include
include|#
directive|include
file|"gimpcanvasitem.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CANVAS_RECTANGLE_GUIDES
define|#
directive|define
name|GIMP_TYPE_CANVAS_RECTANGLE_GUIDES
value|(gimp_canvas_rectangle_guides_get_type ())
end_define

begin_define
DECL|macro|GIMP_CANVAS_RECTANGLE_GUIDES (obj)
define|#
directive|define
name|GIMP_CANVAS_RECTANGLE_GUIDES
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CANVAS_RECTANGLE_GUIDES, GimpCanvasRectangleGuides))
end_define

begin_define
DECL|macro|GIMP_CANVAS_RECTANGLE_GUIDES_CLASS (klass)
define|#
directive|define
name|GIMP_CANVAS_RECTANGLE_GUIDES_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CANVAS_RECTANGLE_GUIDES, GimpCanvasRectangleGuidesClass))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_RECTANGLE_GUIDES (obj)
define|#
directive|define
name|GIMP_IS_CANVAS_RECTANGLE_GUIDES
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CANVAS_RECTANGLE_GUIDES))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_RECTANGLE_GUIDES_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CANVAS_RECTANGLE_GUIDES_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CANVAS_RECTANGLE_GUIDES))
end_define

begin_define
DECL|macro|GIMP_CANVAS_RECTANGLE_GUIDES_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CANVAS_RECTANGLE_GUIDES_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CANVAS_RECTANGLE_GUIDES, GimpCanvasRectangleGuidesClass))
end_define

begin_typedef
DECL|typedef|GimpCanvasRectangleGuides
typedef|typedef
name|struct
name|_GimpCanvasRectangleGuides
name|GimpCanvasRectangleGuides
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCanvasRectangleGuidesClass
typedef|typedef
name|struct
name|_GimpCanvasRectangleGuidesClass
name|GimpCanvasRectangleGuidesClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasRectangleGuides
struct|struct
name|_GimpCanvasRectangleGuides
block|{
DECL|member|parent_instance
name|GimpCanvasItem
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCanvasRectangleGuidesClass
struct|struct
name|_GimpCanvasRectangleGuidesClass
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
name|gimp_canvas_rectangle_guides_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_canvas_rectangle_guides_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|GimpGuidesType
name|type
parameter_list|,
name|gint
name|n_guides
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_rectangle_guides_set
parameter_list|(
name|GimpCanvasItem
modifier|*
name|rectangle
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|GimpGuidesType
name|type
parameter_list|,
name|gint
name|n_guides
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CANVAS_RECTANGLE_GUIDES_H__ */
end_comment

end_unit

