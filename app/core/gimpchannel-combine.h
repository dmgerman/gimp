begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CHANNEL_H__
end_ifndef

begin_define
DECL|macro|__CHANNEL_H__
define|#
directive|define
name|__CHANNEL_H__
end_define

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"boundary.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_comment
comment|/* OPERATIONS */
end_comment

begin_define
DECL|macro|ADD
define|#
directive|define
name|ADD
value|0
end_define

begin_define
DECL|macro|SUB
define|#
directive|define
name|SUB
value|1
end_define

begin_define
DECL|macro|REPLACE
define|#
directive|define
name|REPLACE
value|2
end_define

begin_define
DECL|macro|INTERSECT
define|#
directive|define
name|INTERSECT
value|3
end_define

begin_comment
comment|/*  Half way point where a region is no longer visible in a selection  */
end_comment

begin_define
DECL|macro|HALF_WAY
define|#
directive|define
name|HALF_WAY
value|127
end_define

begin_comment
comment|/* structure declarations */
end_comment

begin_define
DECL|macro|GIMP_CHANNEL (obj)
define|#
directive|define
name|GIMP_CHANNEL
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST (obj, gimp_channel_get_type (), GimpChannel)
end_define

begin_define
DECL|macro|GIMP_CHANNEL_CLASS (klass)
define|#
directive|define
name|GIMP_CHANNEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST (klass, gimp_channel_get_type(), GimpChannelClass)
end_define

begin_define
DECL|macro|GIMP_IS_CHANNEL (obj)
define|#
directive|define
name|GIMP_IS_CHANNEL
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, gimp_channel_get_type())
end_define

begin_typedef
DECL|typedef|GimpChannel
typedef|typedef
name|struct
name|_GimpChannel
name|GimpChannel
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChannelClass
typedef|typedef
name|struct
name|_GimpChannelClass
name|GimpChannelClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|Channel
typedef|typedef
name|GimpChannel
name|Channel
typedef|;
end_typedef

begin_comment
DECL|typedef|Channel
comment|/* convenience */
end_comment

begin_function_decl
name|guint
name|gimp_channel_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Special undo type  */
end_comment

begin_typedef
DECL|typedef|ChannelUndo
typedef|typedef
name|struct
name|_channel_undo
name|ChannelUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_channel_undo
struct|struct
name|_channel_undo
block|{
DECL|member|channel
name|Channel
modifier|*
name|channel
decl_stmt|;
comment|/*  the actual channel         */
DECL|member|prev_position
name|int
name|prev_position
decl_stmt|;
comment|/*  former position in list    */
DECL|member|prev_channel
name|Channel
modifier|*
name|prev_channel
decl_stmt|;
comment|/*  previous active channel    */
DECL|member|undo_type
name|int
name|undo_type
decl_stmt|;
comment|/*  is this a new channel undo */
comment|/*  or a remove channel undo?  */
block|}
struct|;
end_struct

begin_comment
comment|/*  Special undo type  */
end_comment

begin_typedef
DECL|typedef|MaskUndo
typedef|typedef
name|struct
name|_mask_undo
name|MaskUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_mask_undo
struct|struct
name|_mask_undo
block|{
DECL|member|tiles
name|TileManager
modifier|*
name|tiles
decl_stmt|;
comment|/*  the actual mask  */
DECL|member|x
DECL|member|y
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  offsets          */
block|}
struct|;
end_struct

begin_comment
comment|/* function declarations */
end_comment

begin_function_decl
name|Channel
modifier|*
name|channel_new
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|channel_copy
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|channel_get_ID
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_delete
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_scale
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_resize
parameter_list|(
name|Channel
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

begin_comment
comment|/* access functions */
end_comment

begin_function_decl
name|unsigned
name|char
modifier|*
name|channel_data
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|channel_toggle_visibility
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|channel_preview
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_invalidate_previews
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* selection mask functions  */
end_comment

begin_function_decl
name|Channel
modifier|*
name|channel_new_mask
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|channel_boundary
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
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
name|int
name|channel_bounds
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|channel_value
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|channel_is_empty
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_add_segment
parameter_list|(
name|Channel
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
name|channel_sub_segment
parameter_list|(
name|Channel
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
name|channel_inter_segment
parameter_list|(
name|Channel
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
name|channel_combine_rect
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|int
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
name|channel_combine_ellipse
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
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
name|channel_combine_mask
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|Channel
modifier|*
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
name|channel_feather
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|,
name|double
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
name|channel_push_undo
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_clear
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_invert
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_sharpen
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_all
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_border
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_grow
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_shrink
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_translate
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_load
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_invalidate_bounds
parameter_list|(
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|int
name|channel_get_count
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* from drawable.c */
end_comment

begin_function_decl
name|Channel
modifier|*
name|drawable_channel
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CHANNEL_H__ */
end_comment

end_unit

