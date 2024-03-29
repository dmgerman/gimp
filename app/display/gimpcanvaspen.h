begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program Copyright (C) 1995  * Spencer Kimball and Peter Mattis  *  * gimpcanvaspen.h  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CANVAS_PEN_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CANVAS_PEN_H__
define|#
directive|define
name|__GIMP_CANVAS_PEN_H__
end_define

begin_include
include|#
directive|include
file|"gimpcanvaspolygon.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CANVAS_PEN
define|#
directive|define
name|GIMP_TYPE_CANVAS_PEN
value|(gimp_canvas_pen_get_type ())
end_define

begin_define
DECL|macro|GIMP_CANVAS_PEN (obj)
define|#
directive|define
name|GIMP_CANVAS_PEN
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CANVAS_PEN, GimpCanvasPen))
end_define

begin_define
DECL|macro|GIMP_CANVAS_PEN_CLASS (klass)
define|#
directive|define
name|GIMP_CANVAS_PEN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CANVAS_PEN, GimpCanvasPenClass))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_PEN (obj)
define|#
directive|define
name|GIMP_IS_CANVAS_PEN
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CANVAS_PEN))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_PEN_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CANVAS_PEN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CANVAS_PEN))
end_define

begin_define
DECL|macro|GIMP_CANVAS_PEN_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CANVAS_PEN_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CANVAS_PEN, GimpCanvasPenClass))
end_define

begin_typedef
DECL|typedef|GimpCanvasPen
typedef|typedef
name|struct
name|_GimpCanvasPen
name|GimpCanvasPen
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCanvasPenClass
typedef|typedef
name|struct
name|_GimpCanvasPenClass
name|GimpCanvasPenClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasPen
struct|struct
name|_GimpCanvasPen
block|{
DECL|member|parent_instance
name|GimpCanvasPolygon
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCanvasPenClass
struct|struct
name|_GimpCanvasPenClass
block|{
DECL|member|parent_class
name|GimpCanvasPolygonClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_canvas_pen_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_canvas_pen_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpActiveColor
name|color
parameter_list|,
name|gint
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CANVAS_PEN_H__ */
end_comment

end_unit

