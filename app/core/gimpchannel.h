begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CHANNEL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CHANNEL_H__
define|#
directive|define
name|__GIMP_CHANNEL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

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
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CHANNEL, GimpChannel))
end_define

begin_define
DECL|macro|GIMP_CHANNEL_CLASS (klass)
define|#
directive|define
name|GIMP_CHANNEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CHANNEL, GimpChannelClass))
end_define

begin_define
DECL|macro|GIMP_IS_CHANNEL (obj)
define|#
directive|define
name|GIMP_IS_CHANNEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CHANNEL))
end_define

begin_define
DECL|macro|GIMP_IS_CHANNEL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CHANNEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CHANNEL))
end_define

begin_define
DECL|macro|GIMP_CHANNEL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CHANNEL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CHANNEL, GimpChannelClass))
end_define

begin_typedef
DECL|typedef|GimpChannelClass
typedef|typedef
name|struct
name|_GimpChannelClass
name|GimpChannelClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpChannel
struct|struct
name|_GimpChannel
block|{
DECL|member|parent_instance
name|GimpDrawable
name|parent_instance
decl_stmt|;
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
comment|/*  Also stores the opacity        */
DECL|member|show_masked
name|gboolean
name|show_masked
decl_stmt|;
comment|/*  Show masked areas--as          */
comment|/*  opposed to selected areas      */
DECL|member|color_node
name|GeglNode
modifier|*
name|color_node
decl_stmt|;
DECL|member|invert_node
name|GeglNode
modifier|*
name|invert_node
decl_stmt|;
DECL|member|mask_node
name|GeglNode
modifier|*
name|mask_node
decl_stmt|;
comment|/*  Selection mask variables  */
DECL|member|boundary_known
name|gboolean
name|boundary_known
decl_stmt|;
comment|/*  is the current boundary valid  */
DECL|member|segs_in
name|BoundSeg
modifier|*
name|segs_in
decl_stmt|;
comment|/*  outline of selected region     */
DECL|member|segs_out
name|BoundSeg
modifier|*
name|segs_out
decl_stmt|;
comment|/*  outline of selected region     */
DECL|member|num_segs_in
name|gint
name|num_segs_in
decl_stmt|;
comment|/*  number of lines in boundary    */
DECL|member|num_segs_out
name|gint
name|num_segs_out
decl_stmt|;
comment|/*  number of lines in boundary    */
DECL|member|empty
name|gboolean
name|empty
decl_stmt|;
comment|/*  is the region empty?           */
DECL|member|bounds_known
name|gboolean
name|bounds_known
decl_stmt|;
comment|/*  recalculate the bounds?        */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  coordinates for bounding box   */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  lower right hand coordinate    */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpChannelClass
struct|struct
name|_GimpChannelClass
block|{
DECL|member|parent_class
name|GimpDrawableClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|color_changed
name|void
function_decl|(
modifier|*
name|color_changed
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|boundary
name|gboolean
function_decl|(
modifier|*
name|boundary
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
specifier|const
name|BoundSeg
modifier|*
modifier|*
name|segs_in
parameter_list|,
specifier|const
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
DECL|member|bounds
name|gboolean
function_decl|(
modifier|*
name|bounds
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
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
DECL|member|is_empty
name|gboolean
function_decl|(
modifier|*
name|is_empty
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
DECL|member|feather
name|void
function_decl|(
modifier|*
name|feather
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gdouble
name|radius_x
parameter_list|,
name|gdouble
name|radius_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
DECL|member|sharpen
name|void
function_decl|(
modifier|*
name|sharpen
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
DECL|member|clear
name|void
function_decl|(
modifier|*
name|clear
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
DECL|member|all
name|void
function_decl|(
modifier|*
name|all
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
DECL|member|invert
name|void
function_decl|(
modifier|*
name|invert
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
DECL|member|border
name|void
function_decl|(
modifier|*
name|border
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gint
name|radius_x
parameter_list|,
name|gint
name|radius_y
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gboolean
name|edge_lock
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
DECL|member|grow
name|void
function_decl|(
modifier|*
name|grow
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gint
name|radius_x
parameter_list|,
name|gint
name|radius_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
DECL|member|shrink
name|void
function_decl|(
modifier|*
name|shrink
function_decl|)
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gint
name|radius_x
parameter_list|,
name|gint
name|radius_y
parameter_list|,
name|gboolean
name|edge_lock
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
DECL|member|feather_desc
specifier|const
name|gchar
modifier|*
name|feather_desc
decl_stmt|;
DECL|member|sharpen_desc
specifier|const
name|gchar
modifier|*
name|sharpen_desc
decl_stmt|;
DECL|member|clear_desc
specifier|const
name|gchar
modifier|*
name|clear_desc
decl_stmt|;
DECL|member|all_desc
specifier|const
name|gchar
modifier|*
name|all_desc
decl_stmt|;
DECL|member|invert_desc
specifier|const
name|gchar
modifier|*
name|invert_desc
decl_stmt|;
DECL|member|border_desc
specifier|const
name|gchar
modifier|*
name|border_desc
decl_stmt|;
DECL|member|grow_desc
specifier|const
name|gchar
modifier|*
name|grow_desc
decl_stmt|;
DECL|member|shrink_desc
specifier|const
name|gchar
modifier|*
name|shrink_desc
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  function declarations  */
end_comment

begin_decl_stmt
name|GType
name|gimp_channel_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_channel_new
parameter_list|(
name|GimpImage
modifier|*
name|image
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
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_channel_new_from_alpha
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_channel_new_from_component
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_channel_get_opacity
parameter_list|(
specifier|const
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_set_opacity
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_get_color
parameter_list|(
specifier|const
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_set_color
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_channel_get_show_masked
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_set_show_masked
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|show_masked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_push_undo
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  selection mask functions  */
end_comment

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_channel_new_mask
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|gimp_channel_boundary
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
specifier|const
name|BoundSeg
modifier|*
modifier|*
name|segs_in
parameter_list|,
specifier|const
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
name|gimp_channel_bounds
parameter_list|(
name|GimpChannel
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
name|gboolean
name|gimp_channel_is_empty
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_feather
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|gdouble
name|radius_x
parameter_list|,
name|gdouble
name|radius_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_sharpen
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_clear
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_all
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_invert
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_border
parameter_list|(
name|GimpChannel
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
name|feather
parameter_list|,
name|gboolean
name|edge_lock
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_grow
parameter_list|(
name|GimpChannel
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
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_shrink
parameter_list|(
name|GimpChannel
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
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CHANNEL_H__ */
end_comment

end_unit

