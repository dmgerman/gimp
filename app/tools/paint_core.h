begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_CORE_H__
end_ifndef

begin_define
DECL|macro|__PAINT_CORE_H__
define|#
directive|define
name|__PAINT_CORE_H__
end_define

begin_comment
comment|/* the different states that the painting function can be called with  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon279d03370103
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
DECL|enum|__anon279d03370203
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

begin_typedef
DECL|typedef|PaintFunc
typedef|typedef
name|gpointer
function_decl|(
modifier|*
name|PaintFunc
function_decl|)
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PaintState
name|paint_state
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|_PaintCore
struct|struct
name|_PaintCore
block|{
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/*  Core select object         */
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
ifdef|#
directive|ifdef
name|GTK_HAVE_SIX_VALUATORS
DECL|member|startwheel
name|gdouble
name|startwheel
decl_stmt|;
comment|/*  starting wheel             */
endif|#
directive|endif
comment|/* GTK_HAVE_SIX_VALUATORS */
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
ifdef|#
directive|ifdef
name|GTK_HAVE_SIX_VALUATORS
DECL|member|curwheel
name|gdouble
name|curwheel
decl_stmt|;
comment|/*  current wheel              */
endif|#
directive|endif
comment|/* GTK_HAVE_SIX_VALUATORS */
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
ifdef|#
directive|ifdef
name|GTK_HAVE_SIX_VALUATORS
DECL|member|lastwheel
name|gdouble
name|lastwheel
decl_stmt|;
comment|/*  last wheel                 */
endif|#
directive|endif
comment|/* GTK_HAVE_SIX_VALUATORS */
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
DECL|member|paint_func
name|PaintFunc
name|paint_func
decl_stmt|;
comment|/*  painting function          */
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

begin_decl_stmt
specifier|extern
name|PaintCore
name|non_gui_paint_core
decl_stmt|;
end_decl_stmt

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
ifdef|#
directive|ifdef
name|GTK_HAVE_SIX_VALUATORS
DECL|member|lastwheel
name|gdouble
name|lastwheel
decl_stmt|;
endif|#
directive|endif
comment|/* GTK_HAVE_SIX_VALUATORS */
block|}
struct|;
end_struct

begin_comment
comment|/*  paint tool action functions  */
end_comment

begin_function_decl
name|void
name|paint_core_button_press
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_button_release
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_cursor_update
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_control
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  paint tool functions  */
end_comment

begin_function_decl
name|void
name|paint_core_no_draw
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tool
modifier|*
name|paint_core_new
parameter_list|(
name|ToolType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_free
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|paint_core_init
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
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
name|paint_core_interpolate
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_finish
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|tool_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_cleanup
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_get_color_from_gradient
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|gdouble
name|gradient_length
parameter_list|,
name|gdouble
modifier|*
name|r
parameter_list|,
name|gdouble
modifier|*
name|g
parameter_list|,
name|gdouble
modifier|*
name|b
parameter_list|,
name|gdouble
modifier|*
name|a
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
name|paint_core_get_paint_area
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
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
name|paint_core_get_orig_image
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
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
name|paint_core_paste_canvas
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
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
name|paint_core_replace_canvas
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
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
name|paint_core_color_area_with_pixmap
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
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
comment|/*  __PAINT_CORE_H__  */
end_comment

end_unit

