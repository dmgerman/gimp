begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpboundary.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcairo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-appearance.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-draw.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-expose.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-selection.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_struct
DECL|struct|_Selection
struct|struct
name|_Selection
block|{
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
comment|/*  shell that owns the selection     */
DECL|member|segs_in
name|GimpSegment
modifier|*
name|segs_in
decl_stmt|;
comment|/*  gdk segments of area boundary     */
DECL|member|n_segs_in
name|gint
name|n_segs_in
decl_stmt|;
comment|/*  number of segments in segs_in     */
DECL|member|segs_out
name|GimpSegment
modifier|*
name|segs_out
decl_stmt|;
comment|/*  gdk segments of area boundary     */
DECL|member|n_segs_out
name|gint
name|n_segs_out
decl_stmt|;
comment|/*  number of segments in segs_out    */
DECL|member|index
name|guint
name|index
decl_stmt|;
comment|/*  index of current stipple pattern  */
DECL|member|paused
name|gint
name|paused
decl_stmt|;
comment|/*  count of pause requests           */
DECL|member|shell_visible
name|gboolean
name|shell_visible
decl_stmt|;
comment|/*  visility of the display shell     */
DECL|member|show_selection
name|gboolean
name|show_selection
decl_stmt|;
comment|/*  is the selection visible?         */
DECL|member|timeout
name|guint
name|timeout
decl_stmt|;
comment|/*  timer for successive draws        */
DECL|member|segs_in_mask
name|cairo_pattern_t
modifier|*
name|segs_in_mask
decl_stmt|;
comment|/*  cache for rendered segments       */
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|selection_start
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|selection_stop
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|selection_draw
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|selection_undraw
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|selection_render_mask
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|selection_transform_segs
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|,
specifier|const
name|BoundSeg
modifier|*
name|src_segs
parameter_list|,
name|GimpSegment
modifier|*
name|dest_segs
parameter_list|,
name|gint
name|n_segs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|selection_generate_segs
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|selection_free_segs
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|selection_start_timeout
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|selection_timeout
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|selection_window_state_event
parameter_list|(
name|GtkWidget
modifier|*
name|shell
parameter_list|,
name|GdkEventWindowState
modifier|*
name|event
parameter_list|,
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|selection_visibility_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|shell
parameter_list|,
name|GdkEventVisibility
modifier|*
name|event
parameter_list|,
name|Selection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_selection_init (GimpDisplayShell * shell)
name|gimp_display_shell_selection_init
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|Selection
modifier|*
name|selection
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|shell
operator|->
name|selection
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|selection
operator|=
name|g_slice_new0
argument_list|(
name|Selection
argument_list|)
expr_stmt|;
name|selection
operator|->
name|shell
operator|=
name|shell
expr_stmt|;
name|selection
operator|->
name|shell_visible
operator|=
name|TRUE
expr_stmt|;
name|selection
operator|->
name|show_selection
operator|=
name|gimp_display_shell_get_show_selection
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|shell
operator|->
name|selection
operator|=
name|selection
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
argument_list|,
literal|"window-state-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|selection_window_state_event
argument_list|)
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
argument_list|,
literal|"visibility-notify-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|selection_visibility_notify_event
argument_list|)
argument_list|,
name|selection
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_selection_free (GimpDisplayShell * shell)
name|gimp_display_shell_selection_free
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|selection
condition|)
block|{
name|Selection
modifier|*
name|selection
init|=
name|shell
operator|->
name|selection
decl_stmt|;
name|selection_stop
argument_list|(
name|selection
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|shell
argument_list|,
name|selection_window_state_event
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|shell
argument_list|,
name|selection_visibility_notify_event
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|selection_free_segs
argument_list|(
name|selection
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|Selection
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|shell
operator|->
name|selection
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_selection_undraw (GimpDisplayShell * shell)
name|gimp_display_shell_selection_undraw
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|selection
operator|&&
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
block|{
name|selection_undraw
argument_list|(
name|shell
operator|->
name|selection
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|selection_stop
argument_list|(
name|shell
operator|->
name|selection
argument_list|)
expr_stmt|;
name|selection_free_segs
argument_list|(
name|shell
operator|->
name|selection
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_selection_restart (GimpDisplayShell * shell)
name|gimp_display_shell_selection_restart
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|selection
operator|&&
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
block|{
name|selection_start
argument_list|(
name|shell
operator|->
name|selection
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_selection_pause (GimpDisplayShell * shell)
name|gimp_display_shell_selection_pause
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|selection
operator|&&
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
block|{
if|if
condition|(
name|shell
operator|->
name|selection
operator|->
name|paused
operator|==
literal|0
condition|)
name|selection_stop
argument_list|(
name|shell
operator|->
name|selection
argument_list|)
expr_stmt|;
name|shell
operator|->
name|selection
operator|->
name|paused
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_selection_resume (GimpDisplayShell * shell)
name|gimp_display_shell_selection_resume
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|selection
operator|&&
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
block|{
name|shell
operator|->
name|selection
operator|->
name|paused
operator|--
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|selection
operator|->
name|paused
operator|==
literal|0
condition|)
name|selection_start
argument_list|(
name|shell
operator|->
name|selection
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_selection_set_show (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_selection_set_show
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|selection
operator|&&
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
block|{
name|Selection
modifier|*
name|selection
init|=
name|shell
operator|->
name|selection
decl_stmt|;
if|if
condition|(
name|show
operator|!=
name|selection
operator|->
name|show_selection
condition|)
block|{
name|selection_undraw
argument_list|(
name|selection
argument_list|)
expr_stmt|;
name|selection
operator|->
name|show_selection
operator|=
name|show
expr_stmt|;
name|selection_start
argument_list|(
name|selection
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|selection_start (Selection * selection)
name|selection_start
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
name|selection_stop
argument_list|(
name|selection
argument_list|)
expr_stmt|;
comment|/*  If this selection is paused, do not start it  */
if|if
condition|(
name|selection
operator|->
name|paused
operator|==
literal|0
condition|)
block|{
name|selection
operator|->
name|timeout
operator|=
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|selection_start_timeout
argument_list|,
name|selection
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_stop (Selection * selection)
name|selection_stop
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
if|if
condition|(
name|selection
operator|->
name|timeout
condition|)
block|{
name|g_source_remove
argument_list|(
name|selection
operator|->
name|timeout
argument_list|)
expr_stmt|;
name|selection
operator|->
name|timeout
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_draw (Selection * selection)
name|selection_draw
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
if|if
condition|(
name|selection
operator|->
name|segs_in
condition|)
block|{
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|selection
operator|->
name|shell
operator|->
name|canvas
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_draw_selection_in
argument_list|(
name|selection
operator|->
name|shell
argument_list|,
name|cr
argument_list|,
name|selection
operator|->
name|segs_in_mask
argument_list|,
name|selection
operator|->
name|index
operator|%
literal|8
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_undraw (Selection * selection)
name|selection_undraw
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|selection_stop
argument_list|(
name|selection
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_display_shell_mask_bounds
argument_list|(
name|selection
operator|->
name|shell
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
condition|)
block|{
comment|/* expose will restart the selection */
name|gimp_display_shell_expose_area
argument_list|(
name|selection
operator|->
name|shell
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|selection_start
argument_list|(
name|selection
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_render_mask (Selection * selection)
name|selection_render_mask
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|window
operator|=
name|gtk_widget_get_window
argument_list|(
name|selection
operator|->
name|shell
operator|->
name|canvas
argument_list|)
expr_stmt|;
name|surface
operator|=
name|gdk_window_create_similar_surface
argument_list|(
name|window
argument_list|,
name|CAIRO_CONTENT_ALPHA
argument_list|,
name|gdk_window_get_width
argument_list|(
name|window
argument_list|)
argument_list|,
name|gdk_window_get_height
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
name|cr
operator|=
name|cairo_create
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|cairo_set_line_cap
argument_list|(
name|cr
argument_list|,
name|CAIRO_LINE_CAP_SQUARE
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_cairo_add_segments
argument_list|(
name|cr
argument_list|,
name|selection
operator|->
name|segs_in
argument_list|,
name|selection
operator|->
name|n_segs_in
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|selection
operator|->
name|segs_in_mask
operator|=
name|cairo_pattern_create_for_surface
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_transform_segs (Selection * selection,const BoundSeg * src_segs,GimpSegment * dest_segs,gint n_segs)
name|selection_transform_segs
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|,
specifier|const
name|BoundSeg
modifier|*
name|src_segs
parameter_list|,
name|GimpSegment
modifier|*
name|dest_segs
parameter_list|,
name|gint
name|n_segs
parameter_list|)
block|{
specifier|const
name|gint
name|xclamp
init|=
name|selection
operator|->
name|shell
operator|->
name|disp_width
operator|+
literal|1
decl_stmt|;
specifier|const
name|gint
name|yclamp
init|=
name|selection
operator|->
name|shell
operator|->
name|disp_height
operator|+
literal|1
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimp_display_shell_transform_segments
argument_list|(
name|selection
operator|->
name|shell
argument_list|,
name|src_segs
argument_list|,
name|dest_segs
argument_list|,
name|n_segs
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_segs
condition|;
name|i
operator|++
control|)
block|{
name|dest_segs
index|[
name|i
index|]
operator|.
name|x1
operator|=
name|CLAMP
argument_list|(
name|dest_segs
index|[
name|i
index|]
operator|.
name|x1
argument_list|,
operator|-
literal|1
argument_list|,
name|xclamp
argument_list|)
expr_stmt|;
name|dest_segs
index|[
name|i
index|]
operator|.
name|y1
operator|=
name|CLAMP
argument_list|(
name|dest_segs
index|[
name|i
index|]
operator|.
name|y1
argument_list|,
operator|-
literal|1
argument_list|,
name|yclamp
argument_list|)
expr_stmt|;
name|dest_segs
index|[
name|i
index|]
operator|.
name|x2
operator|=
name|CLAMP
argument_list|(
name|dest_segs
index|[
name|i
index|]
operator|.
name|x2
argument_list|,
operator|-
literal|1
argument_list|,
name|xclamp
argument_list|)
expr_stmt|;
name|dest_segs
index|[
name|i
index|]
operator|.
name|y2
operator|=
name|CLAMP
argument_list|(
name|dest_segs
index|[
name|i
index|]
operator|.
name|y2
argument_list|,
operator|-
literal|1
argument_list|,
name|yclamp
argument_list|)
expr_stmt|;
comment|/*  If this segment is a closing segment&& the segments lie inside        *  the region, OR if this is an opening segment and the segments        *  lie outside the region...        *  we need to transform it by one display pixel        */
if|if
condition|(
operator|!
name|src_segs
index|[
name|i
index|]
operator|.
name|open
condition|)
block|{
comment|/*  If it is vertical  */
if|if
condition|(
name|dest_segs
index|[
name|i
index|]
operator|.
name|x1
operator|==
name|dest_segs
index|[
name|i
index|]
operator|.
name|x2
condition|)
block|{
name|dest_segs
index|[
name|i
index|]
operator|.
name|x1
operator|-=
literal|1
expr_stmt|;
name|dest_segs
index|[
name|i
index|]
operator|.
name|x2
operator|-=
literal|1
expr_stmt|;
block|}
else|else
block|{
name|dest_segs
index|[
name|i
index|]
operator|.
name|y1
operator|-=
literal|1
expr_stmt|;
name|dest_segs
index|[
name|i
index|]
operator|.
name|y2
operator|-=
literal|1
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_generate_segs (Selection * selection)
name|selection_generate_segs
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|selection
operator|->
name|shell
operator|->
name|display
argument_list|)
decl_stmt|;
specifier|const
name|BoundSeg
modifier|*
name|segs_in
decl_stmt|;
specifier|const
name|BoundSeg
modifier|*
name|segs_out
decl_stmt|;
comment|/*  Ask the image for the boundary of its selected region...    *  Then transform that information into a new buffer of GimpSegments    */
name|gimp_channel_boundary
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
operator|&
name|segs_in
argument_list|,
operator|&
name|segs_out
argument_list|,
operator|&
name|selection
operator|->
name|n_segs_in
argument_list|,
operator|&
name|selection
operator|->
name|n_segs_out
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection
operator|->
name|n_segs_in
condition|)
block|{
name|selection
operator|->
name|segs_in
operator|=
name|g_new
argument_list|(
name|GimpSegment
argument_list|,
name|selection
operator|->
name|n_segs_in
argument_list|)
expr_stmt|;
name|selection_transform_segs
argument_list|(
name|selection
argument_list|,
name|segs_in
argument_list|,
name|selection
operator|->
name|segs_in
argument_list|,
name|selection
operator|->
name|n_segs_in
argument_list|)
expr_stmt|;
name|selection_render_mask
argument_list|(
name|selection
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|selection
operator|->
name|segs_in
operator|=
name|NULL
expr_stmt|;
block|}
comment|/*  Possible secondary boundary representation  */
if|if
condition|(
name|selection
operator|->
name|n_segs_out
condition|)
block|{
name|selection
operator|->
name|segs_out
operator|=
name|g_new
argument_list|(
name|GimpSegment
argument_list|,
name|selection
operator|->
name|n_segs_out
argument_list|)
expr_stmt|;
name|selection_transform_segs
argument_list|(
name|selection
argument_list|,
name|segs_out
argument_list|,
name|selection
operator|->
name|segs_out
argument_list|,
name|selection
operator|->
name|n_segs_out
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|selection
operator|->
name|segs_out
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_free_segs (Selection * selection)
name|selection_free_segs
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
if|if
condition|(
name|selection
operator|->
name|segs_in
condition|)
block|{
name|g_free
argument_list|(
name|selection
operator|->
name|segs_in
argument_list|)
expr_stmt|;
name|selection
operator|->
name|segs_in
operator|=
name|NULL
expr_stmt|;
name|selection
operator|->
name|n_segs_in
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|selection
operator|->
name|segs_out
condition|)
block|{
name|g_free
argument_list|(
name|selection
operator|->
name|segs_out
argument_list|)
expr_stmt|;
name|selection
operator|->
name|segs_out
operator|=
name|NULL
expr_stmt|;
name|selection
operator|->
name|n_segs_out
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|selection
operator|->
name|segs_in_mask
condition|)
block|{
name|cairo_pattern_destroy
argument_list|(
name|selection
operator|->
name|segs_in_mask
argument_list|)
expr_stmt|;
name|selection
operator|->
name|segs_in_mask
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|selection_start_timeout (Selection * selection)
name|selection_start_timeout
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
name|selection_free_segs
argument_list|(
name|selection
argument_list|)
expr_stmt|;
name|selection
operator|->
name|timeout
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_display_get_image
argument_list|(
name|selection
operator|->
name|shell
operator|->
name|display
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|selection_generate_segs
argument_list|(
name|selection
argument_list|)
expr_stmt|;
name|selection
operator|->
name|index
operator|=
literal|0
expr_stmt|;
comment|/*  Draw the ants  */
if|if
condition|(
name|selection
operator|->
name|show_selection
condition|)
block|{
name|GimpDisplayConfig
modifier|*
name|config
init|=
name|selection
operator|->
name|shell
operator|->
name|display
operator|->
name|config
decl_stmt|;
name|selection_draw
argument_list|(
name|selection
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection
operator|->
name|segs_out
condition|)
block|{
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|selection
operator|->
name|shell
operator|->
name|canvas
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_draw_selection_out
argument_list|(
name|selection
operator|->
name|shell
argument_list|,
name|cr
argument_list|,
name|selection
operator|->
name|segs_out
argument_list|,
name|selection
operator|->
name|n_segs_out
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|selection
operator|->
name|segs_in
operator|&&
name|selection
operator|->
name|shell_visible
condition|)
name|selection
operator|->
name|timeout
operator|=
name|g_timeout_add_full
argument_list|(
name|G_PRIORITY_DEFAULT_IDLE
argument_list|,
name|config
operator|->
name|marching_ants_speed
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|selection_timeout
argument_list|,
name|selection
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|selection_timeout (Selection * selection)
name|selection_timeout
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
name|selection
operator|->
name|index
operator|++
expr_stmt|;
name|selection_draw
argument_list|(
name|selection
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_set_shell_visible (Selection * selection,gboolean shell_visible)
name|selection_set_shell_visible
parameter_list|(
name|Selection
modifier|*
name|selection
parameter_list|,
name|gboolean
name|shell_visible
parameter_list|)
block|{
if|if
condition|(
name|selection
operator|->
name|shell_visible
operator|!=
name|shell_visible
condition|)
block|{
name|selection
operator|->
name|shell_visible
operator|=
name|shell_visible
expr_stmt|;
if|if
condition|(
name|shell_visible
condition|)
name|selection_start
argument_list|(
name|selection
argument_list|)
expr_stmt|;
else|else
name|selection_stop
argument_list|(
name|selection
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|selection_window_state_event (GtkWidget * shell,GdkEventWindowState * event,Selection * selection)
name|selection_window_state_event
parameter_list|(
name|GtkWidget
modifier|*
name|shell
parameter_list|,
name|GdkEventWindowState
modifier|*
name|event
parameter_list|,
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
name|selection_set_shell_visible
argument_list|(
name|selection
argument_list|,
operator|(
name|event
operator|->
name|new_window_state
operator|&
operator|(
name|GDK_WINDOW_STATE_WITHDRAWN
operator||
name|GDK_WINDOW_STATE_ICONIFIED
operator|)
operator|)
operator|==
literal|0
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|selection_visibility_notify_event (GtkWidget * shell,GdkEventVisibility * event,Selection * selection)
name|selection_visibility_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|shell
parameter_list|,
name|GdkEventVisibility
modifier|*
name|event
parameter_list|,
name|Selection
modifier|*
name|selection
parameter_list|)
block|{
name|selection_set_shell_visible
argument_list|(
name|selection
argument_list|,
name|event
operator|->
name|state
operator|!=
name|GDK_VISIBILITY_FULLY_OBSCURED
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

