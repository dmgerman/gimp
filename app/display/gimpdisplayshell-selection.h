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
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
comment|/*  shell that owns the selection     */
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
DECL|member|index
name|guint
name|index
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
DECL|member|cycle_pix
name|GdkPixmap
modifier|*
name|cycle_pix
decl_stmt|;
comment|/*  cycling pixmap                    */
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
block|}
struct|;
end_struct

begin_function_decl
name|Selection
modifier|*
name|gimp_display_shell_selection_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
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
name|gimp_display_shell_selection_set_hidden
parameter_list|(
name|Selection
modifier|*
name|select
parameter_list|,
name|gboolean
name|hidden
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_selection_layer_set_hidden
parameter_list|(
name|Selection
modifier|*
name|select
parameter_list|,
name|gboolean
name|hidden
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

