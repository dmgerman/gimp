begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_mov_dialog.h  * 1997.11.06 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * Dialog Window for gap_mov  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_MOV_DIALOG_H
end_ifndef

begin_define
DECL|macro|_GAP_MOV_DIALOG_H
define|#
directive|define
name|_GAP_MOV_DIALOG_H
end_define

begin_comment
comment|/* revision history:  * version 0.96.02; 1998.07.25  hof: added clip_to_img  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b9a90210103
block|{
DECL|enumerator|GAP_STEP_LOOP
name|GAP_STEP_LOOP
init|=
literal|0
block|,
DECL|enumerator|GAP_STEP_LOOP_REV
name|GAP_STEP_LOOP_REV
init|=
literal|1
block|,
DECL|enumerator|GAP_STEP_ONCE
name|GAP_STEP_ONCE
init|=
literal|2
block|,
DECL|enumerator|GAP_STEP_ONCE_REV
name|GAP_STEP_ONCE_REV
init|=
literal|3
block|,
DECL|enumerator|GAP_STEP_PING_PONG
name|GAP_STEP_PING_PONG
init|=
literal|4
block|,
DECL|enumerator|GAP_STEP_NONE
name|GAP_STEP_NONE
init|=
literal|5
DECL|typedef|t_mov_stepmodes
block|}
name|t_mov_stepmodes
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b9a90210203
block|{
DECL|enumerator|GAP_HANDLE_LEFT_TOP
name|GAP_HANDLE_LEFT_TOP
init|=
literal|0
block|,
DECL|enumerator|GAP_HANDLE_LEFT_BOT
name|GAP_HANDLE_LEFT_BOT
init|=
literal|1
block|,
DECL|enumerator|GAP_HANDLE_RIGHT_TOP
name|GAP_HANDLE_RIGHT_TOP
init|=
literal|2
block|,
DECL|enumerator|GAP_HANDLE_RIGHT_BOT
name|GAP_HANDLE_RIGHT_BOT
init|=
literal|3
block|,
DECL|enumerator|GAP_HANDLE_CENTER
name|GAP_HANDLE_CENTER
init|=
literal|4
DECL|typedef|t_mov_handle
block|}
name|t_mov_handle
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b9a90210308
typedef|typedef
struct|struct
block|{
DECL|member|dst_frame_nr
name|long
name|dst_frame_nr
decl_stmt|;
comment|/* current destination frame_nr */
DECL|member|src_layer_idx
name|long
name|src_layer_idx
decl_stmt|;
comment|/* index of current layer */
DECL|member|src_layers
name|gint32
modifier|*
name|src_layers
decl_stmt|;
comment|/* array of source images layer id's */
DECL|member|src_last_layer
name|long
name|src_last_layer
decl_stmt|;
comment|/* index of last layer 0 upto n-1 */
DECL|member|currX
DECL|member|currY
name|gdouble
name|currX
decl_stmt|,
name|currY
decl_stmt|;
DECL|member|deltaX
DECL|member|deltaY
name|gdouble
name|deltaX
decl_stmt|,
name|deltaY
decl_stmt|;
DECL|member|l_handleX
name|gint
name|l_handleX
decl_stmt|;
DECL|member|l_handleY
name|gint
name|l_handleY
decl_stmt|;
DECL|member|currOpacity
name|gdouble
name|currOpacity
decl_stmt|;
DECL|member|deltaOpacity
name|gdouble
name|deltaOpacity
decl_stmt|;
DECL|member|currWidth
name|gdouble
name|currWidth
decl_stmt|;
DECL|member|deltaWidth
name|gdouble
name|deltaWidth
decl_stmt|;
DECL|member|currHeight
name|gdouble
name|currHeight
decl_stmt|;
DECL|member|deltaHeight
name|gdouble
name|deltaHeight
decl_stmt|;
DECL|member|currRotation
name|gdouble
name|currRotation
decl_stmt|;
DECL|member|deltaRotation
name|gdouble
name|deltaRotation
decl_stmt|;
DECL|typedef|t_mov_current
block|}
name|t_mov_current
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b9a90210408
typedef|typedef
struct|struct
block|{
DECL|member|p_x
DECL|member|p_y
name|gint
name|p_x
decl_stmt|,
name|p_y
decl_stmt|;
comment|/* +- koordinates */
DECL|member|opacity
name|gint
name|opacity
decl_stmt|;
comment|/* 0  upto 100% */
DECL|member|w_resize
name|gint
name|w_resize
decl_stmt|;
comment|/* width resize 10 upto 300% */
DECL|member|h_resize
name|gint
name|h_resize
decl_stmt|;
comment|/* height resize 10 upto 300% */
DECL|member|rotation
name|gint
name|rotation
decl_stmt|;
comment|/* rotatation +- degrees */
DECL|typedef|t_mov_point
block|}
name|t_mov_point
typedef|;
end_typedef

begin_define
DECL|macro|GAP_MOV_MAX_POINT
define|#
directive|define
name|GAP_MOV_MAX_POINT
value|256
end_define

begin_comment
comment|/*  * Notes:  * - exchange of frames (load replace)  *   keeps an images id, but all its  *   layers were allocated new.  *   this results in new layer_id's  *   For this reason the source image MUST NOT be one of the Frames  *   of the destination Animation !!  * - Rotation is now supported (since gap 0.95) (data structs are prepared for)  */
end_comment

begin_typedef
DECL|struct|__anon2b9a90210508
typedef|typedef
struct|struct
block|{
DECL|member|src_image_id
name|gint32
name|src_image_id
decl_stmt|;
comment|/* source image */
DECL|member|src_layer_id
name|gint32
name|src_layer_id
decl_stmt|;
comment|/* id of layer (to begin with) */
DECL|member|src_handle
name|int
name|src_handle
decl_stmt|;
DECL|member|src_stepmode
name|int
name|src_stepmode
decl_stmt|;
DECL|member|src_paintmode
name|int
name|src_paintmode
decl_stmt|;
DECL|member|src_only_visible
name|gint
name|src_only_visible
decl_stmt|;
comment|/* TRUE FALSE */
DECL|member|clip_to_img
name|gint
name|clip_to_img
decl_stmt|;
comment|/* TRUE FALSE */
DECL|member|point_idx
name|gint
name|point_idx
decl_stmt|;
comment|/* 0 upto MAX_POINT -1 */
DECL|member|point_idx_max
name|gint
name|point_idx_max
decl_stmt|;
comment|/* 0 upto MAX_POINT -1 */
DECL|member|point
name|t_mov_point
name|point
index|[
name|GAP_MOV_MAX_POINT
index|]
decl_stmt|;
DECL|member|dst_range_start
name|gint
name|dst_range_start
decl_stmt|;
comment|/* use current frame as default */
DECL|member|dst_range_end
name|gint
name|dst_range_end
decl_stmt|;
DECL|member|dst_layerstack
name|gint
name|dst_layerstack
decl_stmt|;
DECL|member|dst_combination_mode
name|gint
name|dst_combination_mode
decl_stmt|;
comment|/* GLayerMode */
comment|/* for dialog only */
DECL|member|dst_image_id
name|gint32
name|dst_image_id
decl_stmt|;
comment|/* frame image */
DECL|member|tmp_image_id
name|gint32
name|tmp_image_id
decl_stmt|;
comment|/* temp. flattened preview image */
DECL|typedef|t_mov_values
block|}
name|t_mov_values
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b9a90210608
typedef|typedef
struct|struct
block|{
DECL|member|dst_ainfo_ptr
name|t_anim_info
modifier|*
name|dst_ainfo_ptr
decl_stmt|;
comment|/* destination frames */
DECL|member|val_ptr
name|t_mov_values
modifier|*
name|val_ptr
decl_stmt|;
DECL|typedef|t_mov_data
block|}
name|t_mov_data
typedef|;
end_typedef

begin_function_decl
name|long
name|p_move_dialog
parameter_list|(
name|t_mov_data
modifier|*
name|mov_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|p_set_handle_offsets
parameter_list|(
name|t_mov_values
modifier|*
name|val_ptr
parameter_list|,
name|t_mov_current
modifier|*
name|cur_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_mov_render
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|t_mov_values
modifier|*
name|val_ptr
parameter_list|,
name|t_mov_current
modifier|*
name|cur_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

