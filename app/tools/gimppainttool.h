begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PAINT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PAINT_TOOL_H__
define|#
directive|define
name|__GIMP_PAINT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_comment
comment|/* the different states that the painting function can be called with  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2796d6970103
block|{
DECL|enumerator|INIT_PAINT
name|INIT_PAINT
block|,
comment|/* Setup PaintFunc internals */
DECL|enumerator|MOTION_PAINT
name|MOTION_PAINT
block|,
comment|/* PaintFunc performs motion-related rendering */
DECL|enumerator|PAUSE_PAINT
name|PAUSE_PAINT
block|,
comment|/* Unused. Reserved */
DECL|enumerator|RESUME_PAINT
name|RESUME_PAINT
block|,
comment|/* Unused. Reserved */
DECL|enumerator|FINISH_PAINT
name|FINISH_PAINT
block|,
comment|/* Cleanup and/or reset PaintFunc operation */
DECL|enumerator|PRETRACE_PAINT
name|PRETRACE_PAINT
block|,
comment|/* PaintFunc performs window tracing activity prior to rendering */
DECL|enumerator|POSTTRACE_PAINT
name|POSTTRACE_PAINT
comment|/* PaintFunc performs window tracing activity following rendering */
DECL|typedef|PaintState
block|}
name|PaintState
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2796d6970203
block|{
DECL|enumerator|TOOL_CAN_HANDLE_CHANGING_BRUSH
name|TOOL_CAN_HANDLE_CHANGING_BRUSH
init|=
literal|0x0001
block|,
comment|/* Set for tools that don't mind 					    * if the brush changes while 					    * painting. 					    */
DECL|enumerator|TOOL_TRACES_ON_WINDOW
name|TOOL_TRACES_ON_WINDOW
comment|/* Set for tools that perform temporary                                             * rendering directly to the window. These                                             * require sequencing with gdisplay_flush()                                             * routines. See clone.c for example.                                             */
DECL|typedef|ToolFlags
block|}
name|ToolFlags
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PAINT_TOOL
define|#
directive|define
name|GIMP_TYPE_PAINT_TOOL
value|(gimp_paint_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_PAINT_TOOL (obj)
define|#
directive|define
name|GIMP_PAINT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PAINT_TOOL, GimpPaintTool))
end_define

begin_define
DECL|macro|GIMP_PAINT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_PAINT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PAINT_TOOL, GimpPaintToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_PAINT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_PAINT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PAINT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_PAINT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PAINT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PAINT_TOOL))
end_define

begin_define
DECL|macro|GIMP_PAINT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PAINT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PAINT_TOOL, GimpPaintToolClass))
end_define

begin_typedef
DECL|typedef|GimpPaintToolClass
typedef|typedef
name|struct
name|_GimpPaintToolClass
name|GimpPaintToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPaintTool
struct|struct
name|_GimpPaintTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|startx
name|gdouble
name|startx
decl_stmt|;
comment|/*  starting x coord           */
DECL|member|starty
name|gdouble
name|starty
decl_stmt|;
comment|/*  starting y coord           */
DECL|member|startpressure
name|gdouble
name|startpressure
decl_stmt|;
comment|/*  starting pressure          */
DECL|member|startxtilt
name|gdouble
name|startxtilt
decl_stmt|;
comment|/*  starting xtilt             */
DECL|member|startytilt
name|gdouble
name|startytilt
decl_stmt|;
comment|/*  starting ytilt             */
DECL|member|curx
name|gdouble
name|curx
decl_stmt|;
comment|/*  current x coord            */
DECL|member|cury
name|gdouble
name|cury
decl_stmt|;
comment|/*  current y coord            */
DECL|member|curpressure
name|gdouble
name|curpressure
decl_stmt|;
comment|/*  current pressure           */
DECL|member|curxtilt
name|gdouble
name|curxtilt
decl_stmt|;
comment|/*  current xtilt              */
DECL|member|curytilt
name|gdouble
name|curytilt
decl_stmt|;
comment|/*  current ytilt              */
DECL|member|lastx
name|gdouble
name|lastx
decl_stmt|;
comment|/*  last x coord               */
DECL|member|lasty
name|gdouble
name|lasty
decl_stmt|;
comment|/*  last y coord               */
DECL|member|lastpressure
name|gdouble
name|lastpressure
decl_stmt|;
comment|/*  last pressure              */
DECL|member|lastxtilt
name|gdouble
name|lastxtilt
decl_stmt|;
comment|/*  last xtilt                 */
DECL|member|lastytilt
name|gdouble
name|lastytilt
decl_stmt|;
comment|/*  last ytilt                 */
DECL|member|state
name|gint
name|state
decl_stmt|;
comment|/*  state of buttons and keys  */
DECL|member|distance
name|gdouble
name|distance
decl_stmt|;
comment|/*  distance traveled by brush */
DECL|member|pixel_dist
name|gdouble
name|pixel_dist
decl_stmt|;
comment|/*  distance in pixels         */
DECL|member|spacing
name|gdouble
name|spacing
decl_stmt|;
comment|/*  spacing                    */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  image space coordinate     */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  image space coords         */
DECL|member|brush
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
comment|/*  current brush	        */
DECL|member|pick_colors
name|gboolean
name|pick_colors
decl_stmt|;
comment|/*  pick color if ctrl or alt is pressed  */
DECL|member|pick_state
name|gboolean
name|pick_state
decl_stmt|;
comment|/*  was ctrl or alt pressed when clicked? */
DECL|member|flags
name|ToolFlags
name|flags
decl_stmt|;
comment|/*  tool flags, see ToolFlags above       */
DECL|member|context_id
name|guint
name|context_id
decl_stmt|;
comment|/*  for the statusbar          */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPaintToolClass
struct|struct
name|_GimpPaintToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
DECL|member|paint
name|void
function_decl|(
modifier|*
name|paint
function_decl|)
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PaintState
name|paint_state
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Special undo type  */
end_comment

begin_typedef
DECL|typedef|PaintUndo
typedef|typedef
name|struct
name|_PaintUndo
name|PaintUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_PaintUndo
struct|struct
name|_PaintUndo
block|{
DECL|member|tool_ID
name|gint
name|tool_ID
decl_stmt|;
DECL|member|tool_type
name|GType
name|tool_type
decl_stmt|;
DECL|member|lastx
name|gdouble
name|lastx
decl_stmt|;
DECL|member|lasty
name|gdouble
name|lasty
decl_stmt|;
DECL|member|lastpressure
name|gdouble
name|lastpressure
decl_stmt|;
DECL|member|lastxtilt
name|gdouble
name|lastxtilt
decl_stmt|;
DECL|member|lastytilt
name|gdouble
name|lastytilt
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|gimp_paint_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_tool_paint
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PaintState
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_tool_no_draw
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimp_paint_tool_start
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
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
name|gimp_paint_tool_interpolate
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_tool_finish
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_tool_cleanup
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_tool_get_color_from_gradient
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|,
name|gdouble
name|gradient_length
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GradientPaintMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  paint tool painting functions  */
end_comment

begin_function_decl
name|TempBuf
modifier|*
name|gimp_paint_tool_get_paint_area
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_paint_tool_get_orig_image
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
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
name|gimp_paint_tool_paste_canvas
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|brush_opacity
parameter_list|,
name|gint
name|image_opacity
parameter_list|,
name|LayerModeEffects
name|paint_mode
parameter_list|,
name|BrushApplicationMode
name|brush_hardness
parameter_list|,
name|gdouble
name|brush_scale
parameter_list|,
name|PaintApplicationMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_tool_replace_canvas
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|brush_opacity
parameter_list|,
name|gint
name|image_opacity
parameter_list|,
name|BrushApplicationMode
name|brush_hardness
parameter_list|,
name|gdouble
name|brush_scale
parameter_list|,
name|PaintApplicationMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_tool_color_area_with_pixmap
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|TempBuf
modifier|*
name|area
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|BrushApplicationMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PAINT_TOOL_H__  */
end_comment

end_unit

