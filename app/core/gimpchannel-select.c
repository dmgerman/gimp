begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel-select.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel-combine.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-contiguous-region.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimpscanconvert.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpstroke.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_channel_select_rectangle (GimpChannel * channel,gint x,gint y,gint w,gint h,GimpChannelOps op,gboolean feather,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimp_channel_select_rectangle
parameter_list|(
name|GimpChannel
modifier|*
name|channel
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
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_push_undo
argument_list|(
name|channel
argument_list|,
name|_
argument_list|(
literal|"Rect Select"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  if applicable, replace the current selection  */
if|if
condition|(
name|op
operator|==
name|GIMP_CHANNEL_OP_REPLACE
condition|)
name|gimp_channel_clear
argument_list|(
name|channel
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  if feathering for rect, make a new mask with the    *  rectangle and feather that with the old mask    */
if|if
condition|(
name|feather
operator|||
name|op
operator|==
name|GIMP_CHANNEL_OP_INTERSECT
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpChannel
modifier|*
name|add_on
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|add_on
operator|=
name|gimp_channel_new_mask
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_combine_rect
argument_list|(
name|add_on
argument_list|,
name|GIMP_CHANNEL_OP_ADD
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
if|if
condition|(
name|feather
condition|)
name|gimp_channel_feather
argument_list|(
name|add_on
argument_list|,
name|feather_radius_x
argument_list|,
name|feather_radius_y
argument_list|,
name|FALSE
comment|/* no undo */
argument_list|)
expr_stmt|;
name|gimp_channel_combine_mask
argument_list|(
name|channel
argument_list|,
name|add_on
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|add_on
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_channel_combine_rect
argument_list|(
name|channel
argument_list|,
name|op
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_select_ellipse (GimpChannel * channel,gint x,gint y,gint w,gint h,GimpChannelOps op,gboolean antialias,gboolean feather,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimp_channel_select_ellipse
parameter_list|(
name|GimpChannel
modifier|*
name|channel
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
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_push_undo
argument_list|(
name|channel
argument_list|,
name|_
argument_list|(
literal|"Ellipse Select"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  if applicable, replace the current selection  */
if|if
condition|(
name|op
operator|==
name|GIMP_CHANNEL_OP_REPLACE
condition|)
name|gimp_channel_clear
argument_list|(
name|channel
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  if feathering for rect, make a new mask with the    *  rectangle and feather that with the old mask    */
if|if
condition|(
name|feather
operator|||
name|op
operator|==
name|GIMP_CHANNEL_OP_INTERSECT
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpChannel
modifier|*
name|add_on
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|add_on
operator|=
name|gimp_channel_new_mask
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_combine_ellipse
argument_list|(
name|add_on
argument_list|,
name|GIMP_CHANNEL_OP_ADD
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
if|if
condition|(
name|feather
condition|)
name|gimp_channel_feather
argument_list|(
name|add_on
argument_list|,
name|feather_radius_x
argument_list|,
name|feather_radius_y
argument_list|,
name|FALSE
comment|/* no undo */
argument_list|)
expr_stmt|;
name|gimp_channel_combine_mask
argument_list|(
name|channel
argument_list|,
name|add_on
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|add_on
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_channel_combine_ellipse
argument_list|(
name|channel
argument_list|,
name|op
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_select_polygon (GimpChannel * channel,const gchar * undo_desc,gint n_points,GimpVector2 * points,GimpChannelOps op,gboolean antialias,gboolean feather,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimp_channel_select_polygon
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
name|gint
name|n_points
parameter_list|,
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpScanConvert
modifier|*
name|scan_convert
decl_stmt|;
name|GimpChannel
modifier|*
name|add_on
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_push_undo
argument_list|(
name|channel
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
comment|/*  if applicable, replace the current selection  */
if|if
condition|(
name|op
operator|==
name|GIMP_CHANNEL_OP_REPLACE
condition|)
name|gimp_channel_clear
argument_list|(
name|channel
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|scan_convert
operator|=
name|gimp_scan_convert_new
argument_list|()
expr_stmt|;
name|gimp_scan_convert_add_polyline
argument_list|(
name|scan_convert
argument_list|,
name|n_points
argument_list|,
name|points
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|add_on
operator|=
name|gimp_channel_new_mask
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_scan_convert_render
argument_list|(
name|scan_convert
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|add_on
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
name|gimp_scan_convert_free
argument_list|(
name|scan_convert
argument_list|)
expr_stmt|;
if|if
condition|(
name|feather
condition|)
name|gimp_channel_feather
argument_list|(
name|add_on
argument_list|,
name|feather_radius_x
argument_list|,
name|feather_radius_y
argument_list|,
name|FALSE
comment|/* no undo */
argument_list|)
expr_stmt|;
name|gimp_channel_combine_mask
argument_list|(
name|channel
argument_list|,
name|add_on
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|add_on
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_select_vectors (GimpChannel * channel,const gchar * undo_desc,GimpVectors * vectors,GimpChannelOps op,gboolean antialias,gboolean feather,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimp_channel_select_vectors
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
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
name|GimpScanConvert
modifier|*
name|scan_convert
decl_stmt|;
name|GList
modifier|*
name|stroke
decl_stmt|;
name|gboolean
name|coords_added
init|=
name|FALSE
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|scan_convert
operator|=
name|gimp_scan_convert_new
argument_list|()
expr_stmt|;
for|for
control|(
name|stroke
operator|=
name|vectors
operator|->
name|strokes
init|;
name|stroke
condition|;
name|stroke
operator|=
name|stroke
operator|->
name|next
control|)
block|{
name|GArray
modifier|*
name|coords
decl_stmt|;
name|gboolean
name|closed
decl_stmt|;
name|coords
operator|=
name|gimp_stroke_interpolate
argument_list|(
name|GIMP_STROKE
argument_list|(
name|stroke
operator|->
name|data
argument_list|)
argument_list|,
literal|1.0
argument_list|,
operator|&
name|closed
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
operator|&&
name|coords
operator|->
name|len
condition|)
block|{
name|GimpVector2
modifier|*
name|points
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|points
operator|=
name|g_new0
argument_list|(
name|GimpVector2
argument_list|,
name|coords
operator|->
name|len
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
name|coords
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|points
index|[
name|i
index|]
operator|.
name|x
operator|=
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
operator|.
name|x
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|y
operator|=
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
operator|.
name|y
expr_stmt|;
block|}
name|gimp_scan_convert_add_polyline
argument_list|(
name|scan_convert
argument_list|,
name|coords
operator|->
name|len
argument_list|,
name|points
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|coords_added
operator|=
name|TRUE
expr_stmt|;
name|g_free
argument_list|(
name|points
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|coords
condition|)
name|g_array_free
argument_list|(
name|coords
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|coords_added
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpChannel
modifier|*
name|add_on
decl_stmt|;
name|gimp_channel_push_undo
argument_list|(
name|channel
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
comment|/*  if applicable, replace the current selection  */
if|if
condition|(
name|op
operator|==
name|GIMP_CHANNEL_OP_REPLACE
condition|)
name|gimp_channel_clear
argument_list|(
name|channel
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|add_on
operator|=
name|gimp_channel_new_mask
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_scan_convert_render
argument_list|(
name|scan_convert
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|add_on
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
if|if
condition|(
name|feather
condition|)
name|gimp_channel_feather
argument_list|(
name|add_on
argument_list|,
name|feather_radius_x
argument_list|,
name|feather_radius_y
argument_list|,
name|FALSE
comment|/* no undo */
argument_list|)
expr_stmt|;
name|gimp_channel_combine_mask
argument_list|(
name|channel
argument_list|,
name|add_on
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|add_on
argument_list|)
expr_stmt|;
block|}
name|gimp_scan_convert_free
argument_list|(
name|scan_convert
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_select_channel (GimpChannel * channel,const gchar * undo_desc,GimpChannel * add_on,gint offset_x,gint offset_y,GimpChannelOps op,gboolean feather,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimp_channel_select_channel
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
name|GimpChannel
modifier|*
name|add_on
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|add_on
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_push_undo
argument_list|(
name|channel
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
comment|/*  if applicable, replace the current selection  */
if|if
condition|(
name|op
operator|==
name|GIMP_CHANNEL_OP_REPLACE
condition|)
name|gimp_channel_clear
argument_list|(
name|channel
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|feather
operator|||
name|op
operator|==
name|GIMP_CHANNEL_OP_INTERSECT
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpChannel
modifier|*
name|add_on2
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|add_on2
operator|=
name|gimp_channel_new_mask
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_combine_mask
argument_list|(
name|add_on2
argument_list|,
name|add_on
argument_list|,
name|GIMP_CHANNEL_OP_ADD
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|feather
condition|)
name|gimp_channel_feather
argument_list|(
name|add_on2
argument_list|,
name|feather_radius_x
argument_list|,
name|feather_radius_y
argument_list|,
name|FALSE
comment|/* no undo */
argument_list|)
expr_stmt|;
name|gimp_channel_combine_mask
argument_list|(
name|channel
argument_list|,
name|add_on2
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|add_on2
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_channel_combine_mask
argument_list|(
name|channel
argument_list|,
name|add_on
argument_list|,
name|op
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_select_alpha (GimpChannel * channel,GimpLayer * layer,GimpChannelOps op,gboolean feather,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimp_channel_select_alpha
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpChannel
modifier|*
name|add_on
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|add_on
operator|=
name|gimp_channel_new_from_alpha
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|layer
argument_list|,
name|NULL
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
name|feather
condition|)
name|gimp_channel_feather
argument_list|(
name|add_on
argument_list|,
name|feather_radius_x
argument_list|,
name|feather_radius_y
argument_list|,
name|FALSE
comment|/* no undo */
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gimp_channel_select_channel
argument_list|(
name|channel
argument_list|,
name|_
argument_list|(
literal|"Alpha to Selection"
argument_list|)
argument_list|,
name|add_on
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|op
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|add_on
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_select_component (GimpChannel * channel,GimpChannelType component,GimpChannelOps op,gboolean feather,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimp_channel_select_component
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpChannel
modifier|*
name|add_on
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|add_on
operator|=
name|gimp_channel_new_from_component
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|component
argument_list|,
name|NULL
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
name|feather
condition|)
name|gimp_channel_feather
argument_list|(
name|add_on
argument_list|,
name|feather_radius_x
argument_list|,
name|feather_radius_y
argument_list|,
name|FALSE
comment|/* no undo */
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_CHANNEL_TYPE
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value
argument_list|(
name|enum_class
argument_list|,
name|component
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s Channel to Selection"
argument_list|)
argument_list|,
name|gettext
argument_list|(
name|enum_value
operator|->
name|value_name
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_select_channel
argument_list|(
name|channel
argument_list|,
name|name
argument_list|,
name|add_on
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|op
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|add_on
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_select_fuzzy (GimpChannel * channel,GimpDrawable * drawable,gboolean sample_merged,gint x,gint y,gint threshold,gboolean select_transparent,GimpChannelOps op,gboolean antialias,gboolean feather,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimp_channel_select_fuzzy
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpChannel
modifier|*
name|add_on
decl_stmt|;
name|gint
name|add_on_x
init|=
literal|0
decl_stmt|;
name|gint
name|add_on_y
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|add_on
operator|=
name|gimp_image_contiguous_region_by_seed
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|sample_merged
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|select_transparent
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sample_merged
condition|)
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|add_on_x
argument_list|,
operator|&
name|add_on_y
argument_list|)
expr_stmt|;
name|gimp_channel_select_channel
argument_list|(
name|channel
argument_list|,
name|_
argument_list|(
literal|"Fuzzy Select"
argument_list|)
argument_list|,
name|add_on
argument_list|,
name|add_on_x
argument_list|,
name|add_on_y
argument_list|,
name|op
argument_list|,
name|feather
argument_list|,
name|feather_radius_x
argument_list|,
name|feather_radius_y
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|add_on
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_select_by_color (GimpChannel * channel,GimpDrawable * drawable,gboolean sample_merged,const GimpRGB * color,gint threshold,gboolean select_transparent,GimpChannelOps op,gboolean antialias,gboolean feather,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimp_channel_select_by_color
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpChannel
modifier|*
name|add_on
decl_stmt|;
name|gint
name|add_on_x
init|=
literal|0
decl_stmt|;
name|gint
name|add_on_y
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|add_on
operator|=
name|gimp_image_contiguous_region_by_color
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|sample_merged
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|select_transparent
argument_list|,
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sample_merged
condition|)
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|add_on_x
argument_list|,
operator|&
name|add_on_y
argument_list|)
expr_stmt|;
name|gimp_channel_select_channel
argument_list|(
name|channel
argument_list|,
name|_
argument_list|(
literal|"Select by Color"
argument_list|)
argument_list|,
name|add_on
argument_list|,
name|add_on_x
argument_list|,
name|add_on_y
argument_list|,
name|op
argument_list|,
name|feather
argument_list|,
name|feather_radius_x
argument_list|,
name|feather_radius_y
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|add_on
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

