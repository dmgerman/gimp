begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets/gimpoverlaybox.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b0d87e40103
block|{
DECL|enumerator|GIMP_CANVAS_STYLE_XOR
name|GIMP_CANVAS_STYLE_XOR
block|,
DECL|enumerator|GIMP_CANVAS_STYLE_XOR_DASHED
name|GIMP_CANVAS_STYLE_XOR_DASHED
block|,
DECL|enumerator|GIMP_CANVAS_STYLE_XOR_DOTTED
name|GIMP_CANVAS_STYLE_XOR_DOTTED
block|,
DECL|enumerator|GIMP_CANVAS_NUM_STYLES
name|GIMP_CANVAS_NUM_STYLES
DECL|typedef|GimpCanvasStyle
block|}
name|GimpCanvasStyle
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_CANVAS_NUM_STIPPLES
define|#
directive|define
name|GIMP_CANVAS_NUM_STIPPLES
value|8
end_define

begin_define
DECL|macro|GIMP_CANVAS_EVENT_MASK
define|#
directive|define
name|GIMP_CANVAS_EVENT_MASK
value|(GDK_EXPOSURE_MASK            | \                                   GDK_POINTER_MOTION_MASK      |  \                                   GDK_POINTER_MOTION_HINT_MASK |  \                                   GDK_BUTTON_PRESS_MASK        |  \                                   GDK_BUTTON_RELEASE_MASK      |  \                                   GDK_STRUCTURE_MASK           |  \                                   GDK_ENTER_NOTIFY_MASK        |  \                                   GDK_LEAVE_NOTIFY_MASK        |  \                                   GDK_FOCUS_CHANGE_MASK        |  \                                   GDK_KEY_PRESS_MASK           |  \                                   GDK_KEY_RELEASE_MASK         |  \                                   GDK_PROXIMITY_OUT_MASK)
end_define

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
name|GimpOverlayBox
name|parent_instance
decl_stmt|;
DECL|member|config
name|GimpDisplayConfig
modifier|*
name|config
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
index|[
name|GIMP_CANVAS_NUM_STYLES
index|]
decl_stmt|;
DECL|member|stipple
name|GdkBitmap
modifier|*
name|stipple
index|[
name|GIMP_CANVAS_NUM_STIPPLES
index|]
decl_stmt|;
DECL|member|layout
name|PangoLayout
modifier|*
name|layout
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
name|GimpOverlayBoxClass
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
name|GimpDisplayConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_draw_line
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_draw_lines
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|GdkPoint
modifier|*
name|points
parameter_list|,
name|gint
name|num_points
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_draw_rectangle
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|gboolean
name|filled
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_draw_arc
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|gboolean
name|filled
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|angle1
parameter_list|,
name|gint
name|angle2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_draw_polygon
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|gboolean
name|filled
parameter_list|,
name|GdkPoint
modifier|*
name|points
parameter_list|,
name|gint
name|num_points
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_draw_segments
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|GdkSegment
modifier|*
name|segments
parameter_list|,
name|gint
name|num_segments
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PangoLayout
modifier|*
name|gimp_canvas_get_layout
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|2
operator|,
function_decl|3
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_canvas_draw_drop_zone
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_set_clip_rect
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_set_clip_region
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
specifier|const
name|GdkRegion
modifier|*
name|region
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_canvas_set_bg_color
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
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
comment|/*  __GIMP_CANVAS_H__  */
end_comment

end_unit

