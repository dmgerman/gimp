begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_SHELL_SELECTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_SHELL_SELECTION_H__
define|#
directive|define
name|__GIMP_DISPLAY_SHELL_SELECTION_H__
end_define

begin_struct
DECL|struct|_Selection
struct|struct
name|_Selection
block|{
comment|/*  This information is for maintaining the selection's appearance  */
DECL|member|win
name|GdkWindow
modifier|*
name|win
decl_stmt|;
comment|/*  Window to draw to                    */
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
comment|/*  GimpDisplay that owns the selection  */
DECL|member|gc_in
name|GdkGC
modifier|*
name|gc_in
decl_stmt|;
comment|/*  GC for drawing selection outline     */
DECL|member|gc_out
name|GdkGC
modifier|*
name|gc_out
decl_stmt|;
comment|/*  GC for selected regions outside                                        *  current layer */
DECL|member|gc_layer
name|GdkGC
modifier|*
name|gc_layer
decl_stmt|;
comment|/*  GC for current layer outline         */
comment|/*  This information is for drawing the marching ants around the border  */
DECL|member|segs_in
name|GdkSegment
modifier|*
name|segs_in
decl_stmt|;
comment|/*  gdk segments of area boundary     */
DECL|member|segs_out
name|GdkSegment
modifier|*
name|segs_out
decl_stmt|;
comment|/*  gdk segments of area boundary     */
DECL|member|segs_layer
name|GdkSegment
modifier|*
name|segs_layer
decl_stmt|;
comment|/*  gdk segments of area boundary     */
DECL|member|num_segs_in
name|gint
name|num_segs_in
decl_stmt|;
comment|/*  number of segments in segs1       */
DECL|member|num_segs_out
name|gint
name|num_segs_out
decl_stmt|;
comment|/*  number of segments in segs2       */
DECL|member|num_segs_layer
name|gint
name|num_segs_layer
decl_stmt|;
comment|/*  number of segments in segs3       */
DECL|member|index_in
name|gint
name|index_in
decl_stmt|;
comment|/*  index of current stipple pattern  */
DECL|member|index_out
name|gint
name|index_out
decl_stmt|;
comment|/*  index of current stipple pattern  */
DECL|member|index_layer
name|gint
name|index_layer
decl_stmt|;
comment|/*  index of current stipple pattern  */
DECL|member|state
name|gint
name|state
decl_stmt|;
comment|/*  internal drawing state            */
DECL|member|paused
name|gint
name|paused
decl_stmt|;
comment|/*  count of pause requests           */
DECL|member|recalc
name|gboolean
name|recalc
decl_stmt|;
comment|/*  flag to recalculate the selection */
DECL|member|speed
name|gint
name|speed
decl_stmt|;
comment|/*  speed of marching ants            */
DECL|member|hidden
name|gboolean
name|hidden
decl_stmt|;
comment|/*  is the selection hidden?          */
DECL|member|layer_hidden
name|gboolean
name|layer_hidden
decl_stmt|;
comment|/*  is the layer boundary hidden?     */
DECL|member|timeout_id
name|guint
name|timeout_id
decl_stmt|;
comment|/*  timer for successive draws        */
DECL|member|cycle
name|gint
name|cycle
decl_stmt|;
comment|/*  color cycling turned on           */
DECL|member|cycle_pix
name|GdkPixmap
modifier|*
name|cycle_pix
decl_stmt|;
comment|/*  cycling pixmap                    */
comment|/* These are used only if USE_XDRAWPOINTS is defined. */
DECL|member|points_in
name|GdkPoint
modifier|*
name|points_in
index|[
literal|8
index|]
decl_stmt|;
comment|/*  points of segs_in for fast ants   */
DECL|member|num_points_in
name|gint
name|num_points_in
index|[
literal|8
index|]
decl_stmt|;
comment|/*  number of points in points_in     */
DECL|member|gc_white
name|GdkGC
modifier|*
name|gc_white
decl_stmt|;
comment|/*  gc for drawing white points       */
DECL|member|gc_black
name|GdkGC
modifier|*
name|gc_black
decl_stmt|;
comment|/*  gc for drawing black points       */
block|}
struct|;
end_struct

begin_function_decl
name|Selection
modifier|*
name|gimp_display_shell_selection_create
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GimpDisplayShell
modifier|*
name|gdisp
parameter_list|,
name|gint
name|size
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|speed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_selection_free
parameter_list|(
name|Selection
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_selection_pause
parameter_list|(
name|Selection
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_selection_resume
parameter_list|(
name|Selection
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_selection_start
parameter_list|(
name|Selection
modifier|*
name|select
parameter_list|,
name|gboolean
name|recalc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_selection_invis
parameter_list|(
name|Selection
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_selection_layer_invis
parameter_list|(
name|Selection
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_selection_toggle
parameter_list|(
name|Selection
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_selection_toggle_layer
parameter_list|(
name|Selection
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DISPLAY_SHELL_SELECTION_H__  */
end_comment

end_unit

