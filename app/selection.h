begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SELECTION_H__
end_ifndef

begin_define
DECL|macro|__SELECTION_H__
define|#
directive|define
name|__SELECTION_H__
end_define

begin_typedef
DECL|typedef|Selection
typedef|typedef
name|struct
name|_selection
name|Selection
typedef|;
end_typedef

begin_struct
DECL|struct|_selection
struct|struct
name|_selection
block|{
comment|/*  This information is for maintaining the selection's appearance  */
DECL|member|win
name|GdkWindow
modifier|*
name|win
decl_stmt|;
comment|/*  Window to draw to                 */
DECL|member|gdisp
name|void
modifier|*
name|gdisp
decl_stmt|;
comment|/*  GDisplay that owns the selection  */
DECL|member|gc_in
name|GdkGC
modifier|*
name|gc_in
decl_stmt|;
comment|/*  GC for drawing selection outline  */
DECL|member|gc_out
name|GdkGC
modifier|*
name|gc_out
decl_stmt|;
comment|/*  GC for selected regions outside current layer */
DECL|member|gc_layer
name|GdkGC
modifier|*
name|gc_layer
decl_stmt|;
comment|/*  GC for current layer outline      */
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
name|int
name|num_segs_in
decl_stmt|;
comment|/*  number of segments in segs1       */
DECL|member|num_segs_out
name|int
name|num_segs_out
decl_stmt|;
comment|/*  number of segments in segs2       */
DECL|member|num_segs_layer
name|int
name|num_segs_layer
decl_stmt|;
comment|/*  number of segments in segs3       */
DECL|member|index_in
name|int
name|index_in
decl_stmt|;
comment|/*  index of current stipple pattern  */
DECL|member|index_out
name|int
name|index_out
decl_stmt|;
comment|/*  index of current stipple pattern  */
DECL|member|index_layer
name|int
name|index_layer
decl_stmt|;
comment|/*  index of current stipple pattern  */
DECL|member|state
name|int
name|state
decl_stmt|;
comment|/*  internal drawing state            */
DECL|member|paused
name|int
name|paused
decl_stmt|;
comment|/*  count of pause requests           */
DECL|member|recalc
name|int
name|recalc
decl_stmt|;
comment|/*  flag to recalculate the selection */
DECL|member|speed
name|int
name|speed
decl_stmt|;
comment|/*  speed of marching ants            */
DECL|member|hidden
name|int
name|hidden
decl_stmt|;
comment|/*  is the selection hidden?          */
DECL|member|timer
name|gint
name|timer
decl_stmt|;
comment|/*  timer for successive draws        */
DECL|member|cycle
name|int
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
name|int
name|num_points_in
index|[
literal|8
index|]
decl_stmt|;
comment|/* number of points in points_in     */
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

begin_comment
comment|/*  Function declarations  */
end_comment

begin_function_decl
name|Selection
modifier|*
name|selection_create
parameter_list|(
name|GdkWindow
modifier|*
parameter_list|,
name|gpointer
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
name|selection_pause
parameter_list|(
name|Selection
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|selection_resume
parameter_list|(
name|Selection
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|selection_start
parameter_list|(
name|Selection
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|selection_invis
parameter_list|(
name|Selection
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|selection_layer_invis
parameter_list|(
name|Selection
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|selection_hide
parameter_list|(
name|Selection
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|selection_free
parameter_list|(
name|Selection
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __SELECTION_H__  */
end_comment

end_unit

