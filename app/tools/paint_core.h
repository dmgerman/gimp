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

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"draw_core.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawableF.h"
end_include

begin_comment
comment|/* the different states that the painting function can be called with  */
end_comment

begin_define
DECL|macro|INIT_PAINT
define|#
directive|define
name|INIT_PAINT
value|0
end_define

begin_define
DECL|macro|MOTION_PAINT
define|#
directive|define
name|MOTION_PAINT
value|1
end_define

begin_define
DECL|macro|PAUSE_PAINT
define|#
directive|define
name|PAUSE_PAINT
value|2
end_define

begin_define
DECL|macro|RESUME_PAINT
define|#
directive|define
name|RESUME_PAINT
value|3
end_define

begin_define
DECL|macro|FINISH_PAINT
define|#
directive|define
name|FINISH_PAINT
value|4
end_define

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2a343c750103
block|{
DECL|enumerator|TOOL_CAN_HANDLE_CHANGING_BRUSH
name|TOOL_CAN_HANDLE_CHANGING_BRUSH
init|=
literal|0x0001
comment|/* Set for tools that don't mind 					   * if the brush changes while 					   * painting. 					   */
DECL|typedef|ToolFlags
block|}
name|ToolFlags
typedef|;
end_typedef

begin_typedef
DECL|typedef|PaintFunc
typedef|typedef
name|void
modifier|*
function_decl|(
modifier|*
name|PaintFunc
function_decl|)
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|_paint_core
struct|struct
name|_paint_core
block|{
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/*  Core select object         */
DECL|member|startx
name|double
name|startx
decl_stmt|;
comment|/*  starting x coord           */
DECL|member|starty
name|double
name|starty
decl_stmt|;
comment|/*  starting y coord           */
DECL|member|startpressure
name|double
name|startpressure
decl_stmt|;
comment|/*  starting pressure          */
DECL|member|startxtilt
name|double
name|startxtilt
decl_stmt|;
comment|/*  starting xtilt             */
DECL|member|startytilt
name|double
name|startytilt
decl_stmt|;
comment|/*  starting ytilt             */
ifdef|#
directive|ifdef
name|GTK_HAVE_SIX_VALUATORS
DECL|member|startwheel
name|double
name|startwheel
decl_stmt|;
comment|/*  starting wheel             */
endif|#
directive|endif
comment|/* GTK_HAVE_SIX_VALUATORS */
DECL|member|curx
name|double
name|curx
decl_stmt|;
comment|/*  current x coord            */
DECL|member|cury
name|double
name|cury
decl_stmt|;
comment|/*  current y coord            */
DECL|member|curpressure
name|double
name|curpressure
decl_stmt|;
comment|/*  current pressure           */
DECL|member|curxtilt
name|double
name|curxtilt
decl_stmt|;
comment|/*  current xtilt              */
DECL|member|curytilt
name|double
name|curytilt
decl_stmt|;
comment|/*  current ytilt              */
ifdef|#
directive|ifdef
name|GTK_HAVE_SIX_VALUATORS
DECL|member|curwheel
name|double
name|curwheel
decl_stmt|;
comment|/*  current wheel              */
endif|#
directive|endif
comment|/* GTK_HAVE_SIX_VALUATORS */
DECL|member|lastx
name|double
name|lastx
decl_stmt|;
comment|/*  last x coord               */
DECL|member|lasty
name|double
name|lasty
decl_stmt|;
comment|/*  last y coord               */
DECL|member|lastpressure
name|double
name|lastpressure
decl_stmt|;
comment|/*  last pressure              */
DECL|member|lastxtilt
name|double
name|lastxtilt
decl_stmt|;
comment|/*  last xtilt                 */
DECL|member|lastytilt
name|double
name|lastytilt
decl_stmt|;
comment|/*  last ytilt                 */
ifdef|#
directive|ifdef
name|GTK_HAVE_SIX_VALUATORS
DECL|member|lastwheel
name|double
name|lastwheel
decl_stmt|;
comment|/*  last wheel                 */
endif|#
directive|endif
comment|/* GTK_HAVE_SIX_VALUATORS */
DECL|member|state
name|int
name|state
decl_stmt|;
comment|/*  state of buttons and keys  */
DECL|member|distance
name|double
name|distance
decl_stmt|;
comment|/*  distance traveled by brush */
DECL|member|spacing
name|double
name|spacing
decl_stmt|;
comment|/*  distance traveled by brush */
DECL|member|x1
DECL|member|y1
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  image space coordinate     */
DECL|member|x2
DECL|member|y2
name|int
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
name|int
name|pick_colors
decl_stmt|;
comment|/*  pick color if ctrl or alt is pressed  */
DECL|member|pick_state
name|int
name|pick_state
decl_stmt|;
comment|/*  was ctrl or alt pressed when clicked? */
DECL|member|flags
name|int
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
name|_paint_undo
name|PaintUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_paint_undo
struct|struct
name|_paint_undo
block|{
DECL|member|tool_ID
name|int
name|tool_ID
decl_stmt|;
DECL|member|lastx
name|double
name|lastx
decl_stmt|;
DECL|member|lasty
name|double
name|lasty
decl_stmt|;
DECL|member|lastpressure
name|double
name|lastpressure
decl_stmt|;
DECL|member|lastxtilt
name|double
name|lastxtilt
decl_stmt|;
DECL|member|lastytilt
name|double
name|lastytilt
decl_stmt|;
ifdef|#
directive|ifdef
name|GTK_HAVE_SIX_VALUATORS
DECL|member|lastwheel
name|double
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
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_button_release
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_motion
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_cursor_update
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_control
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|ToolAction
parameter_list|,
name|gpointer
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tool
modifier|*
name|paint_core_new
parameter_list|(
name|ToolType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_free
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|paint_core_init
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_interpolate
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_get_color_from_gradient
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|double
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_finish
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|int
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
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|gdouble
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
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_paste_canvas
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|LayerModeEffects
parameter_list|,
name|BrushApplicationMode
parameter_list|,
name|gdouble
parameter_list|,
name|PaintApplicationMode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_replace_canvas
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|BrushApplicationMode
parameter_list|,
name|gdouble
parameter_list|,
name|PaintApplicationMode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_core_color_area_with_pixmap
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|TempBuf
modifier|*
parameter_list|,
name|gdouble
parameter_list|,
name|int
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

