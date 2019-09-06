begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprojection.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintcore.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimppainttool.h"
end_include

begin_include
include|#
directive|include
file|"gimppainttool-paint.h"
end_include

begin_define
DECL|macro|DISPLAY_UPDATE_INTERVAL
define|#
directive|define
name|DISPLAY_UPDATE_INTERVAL
value|10000
end_define

begin_comment
DECL|macro|DISPLAY_UPDATE_INTERVAL
comment|/* microseconds */
end_comment

begin_define
DECL|macro|PAINT_FINISH
define|#
directive|define
name|PAINT_FINISH
value|NULL
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29bf37e80108
block|{
DECL|member|paint_tool
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
DECL|member|func
name|GimpPaintToolPaintFunc
name|func
decl_stmt|;
union|union
DECL|union|__anon29bf37e8020a
block|{
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|member|finished
name|gboolean
modifier|*
name|finished
decl_stmt|;
block|}
union|;
DECL|typedef|PaintItem
block|}
name|PaintItem
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29bf37e80308
block|{
DECL|member|coords
name|GimpCoords
name|coords
decl_stmt|;
DECL|member|time
name|guint32
name|time
decl_stmt|;
DECL|typedef|InterpolateData
block|}
name|InterpolateData
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_paint_tool_paint_use_thread
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|gimp_paint_tool_paint_thread
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_paint_tool_paint_timeout
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paint_tool_paint_interpolate
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|,
name|InterpolateData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  static variables  */
end_comment

begin_decl_stmt
DECL|variable|paint_thread
specifier|static
name|GThread
modifier|*
name|paint_thread
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paint_mutex
specifier|static
name|GMutex
name|paint_mutex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paint_cond
specifier|static
name|GCond
name|paint_cond
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paint_queue
specifier|static
name|GQueue
name|paint_queue
init|=
name|G_QUEUE_INIT
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paint_queue_mutex
specifier|static
name|GMutex
name|paint_queue_mutex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paint_queue_cond
specifier|static
name|GCond
name|paint_queue_cond
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paint_timeout_id
specifier|static
name|guint
name|paint_timeout_id
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paint_timeout_pending
specifier|static
specifier|volatile
name|gboolean
name|paint_timeout_pending
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_paint_tool_paint_use_thread (GimpPaintTool * paint_tool)
name|gimp_paint_tool_paint_use_thread
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|)
block|{
if|if
condition|(
operator|!
name|paint_tool
operator|->
name|draw_line
condition|)
block|{
if|if
condition|(
operator|!
name|paint_thread
condition|)
block|{
specifier|static
name|gint
name|use_paint_thread
init|=
operator|-
literal|1
decl_stmt|;
if|if
condition|(
name|use_paint_thread
operator|<
literal|0
condition|)
name|use_paint_thread
operator|=
name|g_getenv
argument_list|(
literal|"GIMP_NO_PAINT_THREAD"
argument_list|)
operator|==
name|NULL
expr_stmt|;
if|if
condition|(
name|use_paint_thread
condition|)
block|{
name|paint_thread
operator|=
name|g_thread_new
argument_list|(
literal|"paint"
argument_list|,
name|gimp_paint_tool_paint_thread
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|paint_thread
operator|!=
name|NULL
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gpointer
DECL|function|gimp_paint_tool_paint_thread (gpointer data)
name|gimp_paint_tool_paint_thread
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|g_mutex_lock
argument_list|(
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
while|while
condition|(
name|TRUE
condition|)
block|{
name|PaintItem
modifier|*
name|item
decl_stmt|;
while|while
condition|(
operator|!
operator|(
name|item
operator|=
name|g_queue_pop_head
argument_list|(
operator|&
name|paint_queue
argument_list|)
operator|)
condition|)
name|g_cond_wait
argument_list|(
operator|&
name|paint_queue_cond
argument_list|,
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
operator|->
name|func
operator|==
name|PAINT_FINISH
condition|)
block|{
operator|*
name|item
operator|->
name|finished
operator|=
name|TRUE
expr_stmt|;
name|g_cond_signal
argument_list|(
operator|&
name|paint_queue_cond
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_mutex_unlock
argument_list|(
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|paint_mutex
argument_list|)
expr_stmt|;
while|while
condition|(
name|paint_timeout_pending
condition|)
name|g_cond_wait
argument_list|(
operator|&
name|paint_cond
argument_list|,
operator|&
name|paint_mutex
argument_list|)
expr_stmt|;
name|item
operator|->
name|func
argument_list|(
name|item
operator|->
name|paint_tool
argument_list|,
name|item
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|paint_mutex
argument_list|)
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
block|}
name|g_slice_free
argument_list|(
name|PaintItem
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
name|g_mutex_unlock
argument_list|(
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_paint_tool_paint_timeout (GimpPaintTool * paint_tool)
name|gimp_paint_tool_paint_timeout
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|)
block|{
name|GimpPaintCore
modifier|*
name|core
init|=
name|paint_tool
operator|->
name|core
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|paint_tool
operator|->
name|drawable
decl_stmt|;
name|gboolean
name|update
decl_stmt|;
name|paint_timeout_pending
operator|=
name|TRUE
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|paint_mutex
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|paint_x
operator|=
name|core
operator|->
name|cur_coords
operator|.
name|x
expr_stmt|;
name|paint_tool
operator|->
name|paint_y
operator|=
name|core
operator|->
name|cur_coords
operator|.
name|y
expr_stmt|;
name|update
operator|=
name|gimp_drawable_flush_paint
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|update
operator|&&
name|GIMP_PAINT_TOOL_GET_CLASS
argument_list|(
name|paint_tool
argument_list|)
operator|->
name|paint_flush
condition|)
name|GIMP_PAINT_TOOL_GET_CLASS
argument_list|(
name|paint_tool
argument_list|)
operator|->
name|paint_flush
argument_list|(
name|paint_tool
argument_list|)
expr_stmt|;
name|paint_timeout_pending
operator|=
name|FALSE
expr_stmt|;
name|g_cond_signal
argument_list|(
operator|&
name|paint_cond
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|paint_mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|update
condition|)
block|{
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|paint_tool
argument_list|)
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
init|=
name|paint_tool
operator|->
name|display
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
name|gimp_projection_flush_now
argument_list|(
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_display_flush_now
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
return|return
name|G_SOURCE_CONTINUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paint_tool_paint_interpolate (GimpPaintTool * paint_tool,InterpolateData * data)
name|gimp_paint_tool_paint_interpolate
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|,
name|InterpolateData
modifier|*
name|data
parameter_list|)
block|{
name|GimpPaintOptions
modifier|*
name|paint_options
init|=
name|GIMP_PAINT_TOOL_GET_OPTIONS
argument_list|(
name|paint_tool
argument_list|)
decl_stmt|;
name|GimpPaintCore
modifier|*
name|core
init|=
name|paint_tool
operator|->
name|core
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|paint_tool
operator|->
name|drawable
decl_stmt|;
name|gimp_paint_core_interpolate
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
operator|&
name|data
operator|->
name|coords
argument_list|,
name|data
operator|->
name|time
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|InterpolateData
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_paint_tool_paint_start (GimpPaintTool * paint_tool,GimpDisplay * display,const GimpCoords * coords,guint32 time,gboolean constrain,GError ** error)
name|gimp_paint_tool_paint_start
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|gboolean
name|constrain
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpPaintOptions
modifier|*
name|paint_options
decl_stmt|;
name|GimpPaintCore
modifier|*
name|core
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpCoords
name|curr_coords
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_TOOL
argument_list|(
name|paint_tool
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|coords
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|paint_tool
operator|->
name|display
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|paint_tool
argument_list|)
expr_stmt|;
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|paint_tool
argument_list|)
expr_stmt|;
name|paint_options
operator|=
name|GIMP_PAINT_TOOL_GET_OPTIONS
argument_list|(
name|paint_tool
argument_list|)
expr_stmt|;
name|core
operator|=
name|paint_tool
operator|->
name|core
expr_stmt|;
name|shell
operator|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|curr_coords
operator|=
operator|*
name|coords
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|curr_coords
operator|.
name|x
operator|-=
name|off_x
expr_stmt|;
name|curr_coords
operator|.
name|y
operator|-=
name|off_y
expr_stmt|;
name|paint_tool
operator|->
name|paint_x
operator|=
name|curr_coords
operator|.
name|x
expr_stmt|;
name|paint_tool
operator|->
name|paint_y
operator|=
name|curr_coords
operator|.
name|y
expr_stmt|;
comment|/*  If we use a separate paint thread, enter paint mode before starting the    *  paint core    */
if|if
condition|(
name|gimp_paint_tool_paint_use_thread
argument_list|(
name|paint_tool
argument_list|)
condition|)
name|gimp_drawable_start_paint
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_paint_core_set_show_all
argument_list|(
name|core
argument_list|,
name|shell
operator|->
name|show_all
argument_list|)
expr_stmt|;
comment|/*  Start the paint core  */
if|if
condition|(
operator|!
name|gimp_paint_core_start
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
operator|&
name|curr_coords
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|gimp_drawable_end_paint
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|paint_tool
operator|->
name|display
operator|=
name|display
expr_stmt|;
name|paint_tool
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
if|if
condition|(
operator|(
name|display
operator|!=
name|tool
operator|->
name|display
operator|)
operator|||
operator|!
name|paint_tool
operator|->
name|draw_line
condition|)
block|{
comment|/*  If this is a new display, reset the "last stroke's endpoint"        *  because there is none        */
if|if
condition|(
name|display
operator|!=
name|tool
operator|->
name|display
condition|)
name|core
operator|->
name|start_coords
operator|=
name|core
operator|->
name|cur_coords
expr_stmt|;
name|core
operator|->
name|last_coords
operator|=
name|core
operator|->
name|cur_coords
expr_stmt|;
name|core
operator|->
name|distance
operator|=
literal|0.0
expr_stmt|;
name|core
operator|->
name|pixel_dist
operator|=
literal|0.0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|paint_tool
operator|->
name|draw_line
condition|)
block|{
name|gdouble
name|offset_angle
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|gimp_display_shell_get_constrained_line_params
argument_list|(
name|shell
argument_list|,
operator|&
name|offset_angle
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
comment|/*  If shift is down and this is not the first paint        *  stroke, then draw a line from the last coords to the pointer        */
name|gimp_paint_core_round_line
argument_list|(
name|core
argument_list|,
name|paint_options
argument_list|,
name|constrain
argument_list|,
name|offset_angle
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
block|}
comment|/*  Notify subclasses  */
if|if
condition|(
name|gimp_paint_tool_paint_use_thread
argument_list|(
name|paint_tool
argument_list|)
operator|&&
name|GIMP_PAINT_TOOL_GET_CLASS
argument_list|(
name|paint_tool
argument_list|)
operator|->
name|paint_start
condition|)
block|{
name|GIMP_PAINT_TOOL_GET_CLASS
argument_list|(
name|paint_tool
argument_list|)
operator|->
name|paint_start
argument_list|(
name|paint_tool
argument_list|)
expr_stmt|;
block|}
comment|/*  Let the specific painting function initialize itself  */
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_INIT
argument_list|,
name|time
argument_list|)
expr_stmt|;
comment|/*  Paint to the image  */
if|if
condition|(
name|paint_tool
operator|->
name|draw_line
condition|)
block|{
name|gimp_paint_core_interpolate
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
operator|&
name|core
operator|->
name|cur_coords
argument_list|,
name|time
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_MOTION
argument_list|,
name|time
argument_list|)
expr_stmt|;
block|}
name|gimp_projection_flush_now
argument_list|(
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_display_flush_now
argument_list|(
name|display
argument_list|)
expr_stmt|;
comment|/*  Start the display update timeout  */
if|if
condition|(
name|gimp_paint_tool_paint_use_thread
argument_list|(
name|paint_tool
argument_list|)
condition|)
block|{
name|paint_timeout_id
operator|=
name|g_timeout_add_full
argument_list|(
name|G_PRIORITY_HIGH_IDLE
argument_list|,
name|DISPLAY_UPDATE_INTERVAL
operator|/
literal|1000
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gimp_paint_tool_paint_timeout
argument_list|,
name|paint_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_paint_tool_paint_end (GimpPaintTool * paint_tool,guint32 time,gboolean cancel)
name|gimp_paint_tool_paint_end
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|,
name|guint32
name|time
parameter_list|,
name|gboolean
name|cancel
parameter_list|)
block|{
name|GimpPaintOptions
modifier|*
name|paint_options
decl_stmt|;
name|GimpPaintCore
modifier|*
name|core
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PAINT_TOOL
argument_list|(
name|paint_tool
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|paint_tool
operator|->
name|display
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|paint_options
operator|=
name|GIMP_PAINT_TOOL_GET_OPTIONS
argument_list|(
name|paint_tool
argument_list|)
expr_stmt|;
name|core
operator|=
name|paint_tool
operator|->
name|core
expr_stmt|;
name|drawable
operator|=
name|paint_tool
operator|->
name|drawable
expr_stmt|;
comment|/*  Process remaining paint items  */
if|if
condition|(
name|gimp_paint_tool_paint_use_thread
argument_list|(
name|paint_tool
argument_list|)
condition|)
block|{
name|PaintItem
modifier|*
name|item
decl_stmt|;
name|gboolean
name|finished
init|=
name|FALSE
decl_stmt|;
name|guint64
name|end_time
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_paint_tool_paint_is_active
argument_list|(
name|paint_tool
argument_list|)
argument_list|)
expr_stmt|;
name|g_source_remove
argument_list|(
name|paint_timeout_id
argument_list|)
expr_stmt|;
name|paint_timeout_id
operator|=
literal|0
expr_stmt|;
name|item
operator|=
name|g_slice_new
argument_list|(
name|PaintItem
argument_list|)
expr_stmt|;
name|item
operator|->
name|paint_tool
operator|=
name|paint_tool
expr_stmt|;
name|item
operator|->
name|func
operator|=
name|PAINT_FINISH
expr_stmt|;
name|item
operator|->
name|finished
operator|=
operator|&
name|finished
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
operator|&
name|paint_queue
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|g_cond_signal
argument_list|(
operator|&
name|paint_queue_cond
argument_list|)
expr_stmt|;
name|end_time
operator|=
name|g_get_monotonic_time
argument_list|()
operator|+
name|DISPLAY_UPDATE_INTERVAL
expr_stmt|;
while|while
condition|(
operator|!
name|finished
condition|)
block|{
if|if
condition|(
operator|!
name|g_cond_wait_until
argument_list|(
operator|&
name|paint_queue_cond
argument_list|,
operator|&
name|paint_queue_mutex
argument_list|,
name|end_time
argument_list|)
condition|)
block|{
name|g_mutex_unlock
argument_list|(
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
name|gimp_paint_tool_paint_timeout
argument_list|(
name|paint_tool
argument_list|)
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
name|end_time
operator|=
name|g_get_monotonic_time
argument_list|()
operator|+
name|DISPLAY_UPDATE_INTERVAL
expr_stmt|;
block|}
block|}
name|g_mutex_unlock
argument_list|(
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
block|}
comment|/*  Let the specific painting function finish up  */
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_FINISH
argument_list|,
name|time
argument_list|)
expr_stmt|;
if|if
condition|(
name|cancel
condition|)
name|gimp_paint_core_cancel
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
else|else
name|gimp_paint_core_finish
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Notify subclasses  */
if|if
condition|(
name|gimp_paint_tool_paint_use_thread
argument_list|(
name|paint_tool
argument_list|)
operator|&&
name|GIMP_PAINT_TOOL_GET_CLASS
argument_list|(
name|paint_tool
argument_list|)
operator|->
name|paint_end
condition|)
block|{
name|GIMP_PAINT_TOOL_GET_CLASS
argument_list|(
name|paint_tool
argument_list|)
operator|->
name|paint_end
argument_list|(
name|paint_tool
argument_list|)
expr_stmt|;
block|}
comment|/*  Exit paint mode  */
if|if
condition|(
name|gimp_paint_tool_paint_use_thread
argument_list|(
name|paint_tool
argument_list|)
condition|)
name|gimp_drawable_end_paint
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|display
operator|=
name|NULL
expr_stmt|;
name|paint_tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_paint_tool_paint_is_active (GimpPaintTool * paint_tool)
name|gimp_paint_tool_paint_is_active
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_TOOL
argument_list|(
name|paint_tool
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|paint_tool
operator|->
name|drawable
operator|!=
name|NULL
operator|&&
name|gimp_drawable_is_painting
argument_list|(
name|paint_tool
operator|->
name|drawable
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_paint_tool_paint_push (GimpPaintTool * paint_tool,GimpPaintToolPaintFunc func,gpointer data)
name|gimp_paint_tool_paint_push
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|,
name|GimpPaintToolPaintFunc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PAINT_TOOL
argument_list|(
name|paint_tool
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_paint_tool_paint_use_thread
argument_list|(
name|paint_tool
argument_list|)
condition|)
block|{
name|PaintItem
modifier|*
name|item
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_paint_tool_paint_is_active
argument_list|(
name|paint_tool
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Push an item to the queue, to be processed by the paint thread  */
name|item
operator|=
name|g_slice_new
argument_list|(
name|PaintItem
argument_list|)
expr_stmt|;
name|item
operator|->
name|paint_tool
operator|=
name|paint_tool
expr_stmt|;
name|item
operator|->
name|func
operator|=
name|func
expr_stmt|;
name|item
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
operator|&
name|paint_queue
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|g_cond_signal
argument_list|(
operator|&
name|paint_queue_cond
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|paint_queue_mutex
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|paint_tool
argument_list|)
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
init|=
name|paint_tool
operator|->
name|display
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
comment|/*  Paint directly  */
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
name|func
argument_list|(
name|paint_tool
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_projection_flush_now
argument_list|(
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_display_flush_now
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_paint_tool_paint_motion (GimpPaintTool * paint_tool,const GimpCoords * coords,guint32 time)
name|gimp_paint_tool_paint_motion
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|GimpPaintOptions
modifier|*
name|paint_options
decl_stmt|;
name|GimpPaintCore
modifier|*
name|core
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|InterpolateData
modifier|*
name|data
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PAINT_TOOL
argument_list|(
name|paint_tool
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|coords
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|paint_tool
operator|->
name|display
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|paint_options
operator|=
name|GIMP_PAINT_TOOL_GET_OPTIONS
argument_list|(
name|paint_tool
argument_list|)
expr_stmt|;
name|core
operator|=
name|paint_tool
operator|->
name|core
expr_stmt|;
name|drawable
operator|=
name|paint_tool
operator|->
name|drawable
expr_stmt|;
name|data
operator|=
name|g_slice_new
argument_list|(
name|InterpolateData
argument_list|)
expr_stmt|;
name|data
operator|->
name|coords
operator|=
operator|*
name|coords
expr_stmt|;
name|data
operator|->
name|time
operator|=
name|time
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|data
operator|->
name|coords
operator|.
name|x
operator|-=
name|off_x
expr_stmt|;
name|data
operator|->
name|coords
operator|.
name|y
operator|-=
name|off_y
expr_stmt|;
name|gimp_paint_core_smooth_coords
argument_list|(
name|core
argument_list|,
name|paint_options
argument_list|,
operator|&
name|data
operator|->
name|coords
argument_list|)
expr_stmt|;
comment|/*  Don't paint while the Shift key is pressed for line drawing  */
if|if
condition|(
name|paint_tool
operator|->
name|draw_line
condition|)
block|{
name|gimp_paint_core_set_current_coords
argument_list|(
name|core
argument_list|,
operator|&
name|data
operator|->
name|coords
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|InterpolateData
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_paint_tool_paint_push
argument_list|(
name|paint_tool
argument_list|,
operator|(
name|GimpPaintToolPaintFunc
operator|)
name|gimp_paint_tool_paint_interpolate
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

