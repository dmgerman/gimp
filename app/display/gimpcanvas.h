begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CANVAS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CANVAS_H__
define|#
directive|define
name|__GIMP_CANVAS_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkdrawingarea.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_CANVAS
define|#
directive|define
name|GIMP_TYPE_CANVAS
value|(gimp_canvas_get_type ())
end_define

begin_define
DECL|macro|GIMP_CANVAS (obj)
define|#
directive|define
name|GIMP_CANVAS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CANVAS, GimpCanvas))
end_define

begin_define
DECL|macro|GIMP_CANVAS_CLASS (klass)
define|#
directive|define
name|GIMP_CANVAS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CANVAS, GimpCanvasClass))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS (obj)
define|#
directive|define
name|GIMP_IS_CANVAS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CANVAS))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CANVAS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CANVAS))
end_define

begin_define
DECL|macro|GIMP_CANVAS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CANVAS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CANVAS, GimpCanvasClass))
end_define

begin_typedef
DECL|typedef|GimpCanvasClass
typedef|typedef
name|struct
name|_GimpCanvasClass
name|GimpCanvasClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvas
struct|struct
name|_GimpCanvas
block|{
DECL|member|parent_instance
name|GtkDrawingArea
name|parent_instance
decl_stmt|;
comment|/*  GC for rendering the image  */
DECL|member|render_gc
name|GdkGC
modifier|*
name|render_gc
decl_stmt|;
comment|/*  GCs for rendering guides    */
struct|struct
DECL|struct|__anon278b85d10108
block|{
DECL|member|normal_hgc
name|GdkGC
modifier|*
name|normal_hgc
decl_stmt|;
DECL|member|active_hgc
name|GdkGC
modifier|*
name|active_hgc
decl_stmt|;
DECL|member|normal_vgc
name|GdkGC
modifier|*
name|normal_vgc
decl_stmt|;
DECL|member|active_vgc
name|GdkGC
modifier|*
name|active_vgc
decl_stmt|;
DECL|member|guides
block|}
name|guides
struct|;
comment|/*  GC for the grid             */
DECL|member|grid_gc
name|GdkGC
modifier|*
name|grid_gc
decl_stmt|;
comment|/*  GC for the vectors          */
DECL|member|vectors_gc
name|GdkGC
modifier|*
name|vectors_gc
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCanvasClass
struct|struct
name|_GimpCanvasClass
block|{
DECL|member|parent_class
name|GtkDrawingAreaClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_canvas_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_canvas_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkGC
modifier|*
name|gimp_canvas_grid_gc_new
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpGrid
modifier|*
name|grid
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_draw_cursor
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CANVAS_H__  */
end_comment

end_unit

