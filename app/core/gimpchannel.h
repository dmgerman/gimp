begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"apptypes.h"
end_include

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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon275601050103
block|{
DECL|enumerator|ADD
name|ADD
block|,
DECL|enumerator|SUB
name|SUB
block|,
DECL|enumerator|REPLACE
name|REPLACE
block|,
DECL|enumerator|INTERSECT
name|INTERSECT
DECL|typedef|ChannelOps
block|}
name|ChannelOps
typedef|;
end_typedef

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
comment|/*  structure declarations  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_CHANNEL
define|#
directive|define
name|GIMP_TYPE_CHANNEL
value|(gimp_channel_get_type ())
end_define

begin_define
DECL|macro|GIMP_CHANNEL (obj)
define|#
directive|define
name|GIMP_CHANNEL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_CHANNEL, GimpChannel))
end_define

begin_define
DECL|macro|GIMP_CHANNEL_CLASS (klass)
define|#
directive|define
name|GIMP_CHANNEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CHANNEL, GimpChannelClass))
end_define

begin_define
DECL|macro|GIMP_IS_CHANNEL (obj)
define|#
directive|define
name|GIMP_IS_CHANNEL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_CHANNEL))
end_define

begin_define
DECL|macro|GIMP_IS_CHANNEL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CHANNEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CHANNEL))
end_define

begin_function_decl
name|GtkType
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
name|_ChannelUndo
name|ChannelUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_ChannelUndo
struct|struct
name|_ChannelUndo
block|{
DECL|member|channel
name|Channel
modifier|*
name|channel
decl_stmt|;
comment|/*  the actual channel          */
DECL|member|prev_position
name|gint
name|prev_position
decl_stmt|;
comment|/*  former position in list     */
DECL|member|prev_channel
name|Channel
modifier|*
name|prev_channel
decl_stmt|;
comment|/*  previous active channel     */
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
name|_MaskUndo
name|MaskUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_MaskUndo
struct|struct
name|_MaskUndo
block|{
DECL|member|tiles
name|TileManager
modifier|*
name|tiles
decl_stmt|;
comment|/*  the actual mask  */
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  offsets          */
block|}
struct|;
end_struct

begin_comment
comment|/*  function declarations  */
end_comment

begin_function_decl
name|Channel
modifier|*
name|channel_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|opacity
parameter_list|,
specifier|const
name|guchar
modifier|*
name|col
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|channel_copy
parameter_list|(
specifier|const
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|channel_get_name
parameter_list|(
specifier|const
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_set_name
parameter_list|(
name|Channel
modifier|*
name|channel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|channel_get_opacity
parameter_list|(
specifier|const
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_set_opacity
parameter_list|(
name|Channel
modifier|*
name|channel
parameter_list|,
name|gint
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|guchar
modifier|*
name|channel_get_color
parameter_list|(
specifier|const
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_set_color
parameter_list|(
name|Channel
modifier|*
name|channel
parameter_list|,
specifier|const
name|guchar
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|channel_get_ID
parameter_list|(
name|gint
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_delete
parameter_list|(
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_removed
parameter_list|(
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_scale
parameter_list|(
name|Channel
modifier|*
name|channel
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_resize
parameter_list|(
name|Channel
modifier|*
name|channel
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_update
parameter_list|(
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  access functions  */
end_comment

begin_function_decl
name|gboolean
name|channel_toggle_visibility
parameter_list|(
name|Channel
modifier|*
name|channel
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
name|channel
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_invalidate_previews
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tattoo
name|channel_get_tattoo
parameter_list|(
specifier|const
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_set_tattoo
parameter_list|(
name|Channel
modifier|*
name|channel
parameter_list|,
name|Tattoo
name|value
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
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|channel_boundary
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
name|segs_in
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
name|segs_out
parameter_list|,
name|gint
modifier|*
name|num_segs_in
parameter_list|,
name|gint
modifier|*
name|num_segs_out
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
name|gboolean
name|channel_bounds
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|channel_value
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|channel_is_empty
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_add_segment
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_sub_segment
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_combine_rect
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|ChannelOps
name|op
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_combine_ellipse
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|ChannelOps
name|op
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_combine_mask
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|Channel
modifier|*
name|add_on
parameter_list|,
name|ChannelOps
name|op
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_feather
parameter_list|(
name|Channel
modifier|*
name|input
parameter_list|,
name|Channel
modifier|*
name|output
parameter_list|,
name|gdouble
name|radius_x
parameter_list|,
name|gdouble
name|radius_y
parameter_list|,
name|ChannelOps
name|op
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_push_undo
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_clear
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_invert
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_sharpen
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_all
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_border
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|gint
name|radius_x
parameter_list|,
name|gint
name|radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_grow
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|gint
name|radius_x
parameter_list|,
name|gint
name|radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_shrink
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|gint
name|radius_x
parameter_list|,
name|gint
name|radius_y
parameter_list|,
name|gboolean
name|edge_lock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_translate
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_load
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_invalidate_bounds
parameter_list|(
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|drawable_channel
define|#
directive|define
name|drawable_channel
value|GIMP_IS_CHANNEL
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CHANNEL_H__ */
end_comment

end_unit

