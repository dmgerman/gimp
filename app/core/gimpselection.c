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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/tile.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"gimpselection.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_selection_class_init
parameter_list|(
name|GimpSelectionClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_init
parameter_list|(
name|GimpSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_translate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_scale
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|new_offset_x
parameter_list|,
name|gint
name|new_offset_y
parameter_list|,
name|GimpInterpolationType
name|interp_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_resize
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
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
specifier|static
name|void
name|gimp_selection_flip
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gdouble
name|axis
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_rotate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpRotationType
name|rotation_type
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_selection_stroke
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintInfo
modifier|*
name|paint_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_invalidate_boundary
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_selection_boundary
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
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_selection_bounds
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
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_selection_is_empty
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_selection_value
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_feather
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
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_sharpen
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_clear
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
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_all
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_invert
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_border
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
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_grow
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
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_shrink
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
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_changed
parameter_list|(
name|GimpChannel
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_validate
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpChannelClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_selection_get_type (void)
name|gimp_selection_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|selection_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|selection_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|selection_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpSelectionClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_selection_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpSelection
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_selection_init
block|,       }
decl_stmt|;
name|selection_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_CHANNEL
argument_list|,
literal|"GimpSelection"
argument_list|,
operator|&
name|selection_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|selection_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_class_init (GimpSelectionClass * klass)
name|gimp_selection_class_init
parameter_list|(
name|GimpSelectionClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpItemClass
modifier|*
name|item_class
decl_stmt|;
name|GimpDrawableClass
modifier|*
name|drawable_class
decl_stmt|;
name|GimpChannelClass
modifier|*
name|channel_class
decl_stmt|;
name|item_class
operator|=
name|GIMP_ITEM_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|drawable_class
operator|=
name|GIMP_DRAWABLE_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|channel_class
operator|=
name|GIMP_CHANNEL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|translate
operator|=
name|gimp_selection_translate
expr_stmt|;
name|item_class
operator|->
name|scale
operator|=
name|gimp_selection_scale
expr_stmt|;
name|item_class
operator|->
name|resize
operator|=
name|gimp_selection_resize
expr_stmt|;
name|item_class
operator|->
name|flip
operator|=
name|gimp_selection_flip
expr_stmt|;
name|item_class
operator|->
name|rotate
operator|=
name|gimp_selection_rotate
expr_stmt|;
name|item_class
operator|->
name|stroke
operator|=
name|gimp_selection_stroke
expr_stmt|;
name|drawable_class
operator|->
name|invalidate_boundary
operator|=
name|gimp_selection_invalidate_boundary
expr_stmt|;
name|channel_class
operator|->
name|boundary
operator|=
name|gimp_selection_boundary
expr_stmt|;
name|channel_class
operator|->
name|bounds
operator|=
name|gimp_selection_bounds
expr_stmt|;
name|channel_class
operator|->
name|is_empty
operator|=
name|gimp_selection_is_empty
expr_stmt|;
name|channel_class
operator|->
name|value
operator|=
name|gimp_selection_value
expr_stmt|;
name|channel_class
operator|->
name|feather
operator|=
name|gimp_selection_feather
expr_stmt|;
name|channel_class
operator|->
name|sharpen
operator|=
name|gimp_selection_sharpen
expr_stmt|;
name|channel_class
operator|->
name|clear
operator|=
name|gimp_selection_clear
expr_stmt|;
name|channel_class
operator|->
name|all
operator|=
name|gimp_selection_all
expr_stmt|;
name|channel_class
operator|->
name|invert
operator|=
name|gimp_selection_invert
expr_stmt|;
name|channel_class
operator|->
name|border
operator|=
name|gimp_selection_border
expr_stmt|;
name|channel_class
operator|->
name|grow
operator|=
name|gimp_selection_grow
expr_stmt|;
name|channel_class
operator|->
name|shrink
operator|=
name|gimp_selection_shrink
expr_stmt|;
name|channel_class
operator|->
name|translate_desc
operator|=
name|_
argument_list|(
literal|"Move Selection"
argument_list|)
expr_stmt|;
name|channel_class
operator|->
name|feather_desc
operator|=
name|_
argument_list|(
literal|"Feather Selection"
argument_list|)
expr_stmt|;
name|channel_class
operator|->
name|sharpen_desc
operator|=
name|_
argument_list|(
literal|"Sharpen Selection"
argument_list|)
expr_stmt|;
name|channel_class
operator|->
name|clear_desc
operator|=
name|_
argument_list|(
literal|"Select None"
argument_list|)
expr_stmt|;
name|channel_class
operator|->
name|all_desc
operator|=
name|_
argument_list|(
literal|"Select All"
argument_list|)
expr_stmt|;
name|channel_class
operator|->
name|invert_desc
operator|=
name|_
argument_list|(
literal|"Invert Selection"
argument_list|)
expr_stmt|;
name|channel_class
operator|->
name|border_desc
operator|=
name|_
argument_list|(
literal|"Border Selection"
argument_list|)
expr_stmt|;
name|channel_class
operator|->
name|grow_desc
operator|=
name|_
argument_list|(
literal|"Grow Selection"
argument_list|)
expr_stmt|;
name|channel_class
operator|->
name|shrink_desc
operator|=
name|_
argument_list|(
literal|"Shrink Selection"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_init (GimpSelection * selection)
name|gimp_selection_init
parameter_list|(
name|GimpSelection
modifier|*
name|selection
parameter_list|)
block|{
name|selection
operator|->
name|stroking
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_translate (GimpItem * item,gint offset_x,gint offset_y,gboolean push_undo)
name|gimp_selection_translate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GIMP_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|translate
argument_list|(
name|item
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_scale (GimpItem * item,gint new_width,gint new_height,gint new_offset_x,gint new_offset_y,GimpInterpolationType interp_type)
name|gimp_selection_scale
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|new_offset_x
parameter_list|,
name|gint
name|new_offset_y
parameter_list|,
name|GimpInterpolationType
name|interp_type
parameter_list|)
block|{
name|GIMP_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|scale
argument_list|(
name|item
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
name|new_offset_x
argument_list|,
name|new_offset_y
argument_list|,
name|interp_type
argument_list|)
expr_stmt|;
name|item
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|item
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_resize (GimpItem * item,gint new_width,gint new_height,gint off_x,gint off_y)
name|gimp_selection_resize
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
block|{
name|GIMP_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|resize
argument_list|(
name|item
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|)
expr_stmt|;
name|item
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|item
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_flip (GimpItem * item,GimpOrientationType flip_type,gdouble axis,gboolean clip_result)
name|gimp_selection_flip
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gdouble
name|axis
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
block|{
name|GIMP_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|flip
argument_list|(
name|item
argument_list|,
name|flip_type
argument_list|,
name|axis
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_rotate (GimpItem * item,GimpRotationType rotation_type,gdouble center_x,gdouble center_y,gboolean clip_result)
name|gimp_selection_rotate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpRotationType
name|rotation_type
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
block|{
name|GIMP_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|rotate
argument_list|(
name|item
argument_list|,
name|rotation_type
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|clip_result
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_selection_stroke (GimpItem * item,GimpDrawable * drawable,GimpPaintInfo * paint_info)
name|gimp_selection_stroke
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintInfo
modifier|*
name|paint_info
parameter_list|)
block|{
name|GimpSelection
modifier|*
name|selection
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
specifier|const
name|BoundSeg
modifier|*
name|dummy_in
decl_stmt|;
specifier|const
name|BoundSeg
modifier|*
name|dummy_out
decl_stmt|;
name|gint
name|num_dummy_in
decl_stmt|;
name|gint
name|num_dummy_out
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|selection
operator|=
name|GIMP_SELECTION
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_channel_boundary
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|selection
argument_list|)
argument_list|,
operator|&
name|dummy_in
argument_list|,
operator|&
name|dummy_out
argument_list|,
operator|&
name|num_dummy_in
argument_list|,
operator|&
name|num_dummy_out
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"No selection to stroke."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|selection
operator|->
name|stroking
operator|=
name|TRUE
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_PAINT
argument_list|,
name|_
argument_list|(
literal|"Stroke Selection"
argument_list|)
argument_list|)
expr_stmt|;
name|retval
operator|=
name|GIMP_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|stroke
argument_list|(
name|item
argument_list|,
name|drawable
argument_list|,
name|paint_info
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|selection
operator|->
name|stroking
operator|=
name|FALSE
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_invalidate_boundary (GimpDrawable * drawable)
name|gimp_selection_invalidate_boundary
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|selection
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|selection
operator|=
name|GIMP_CHANNEL
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Turn the current selection off  */
name|gimp_image_selection_control
argument_list|(
name|gimage
argument_list|,
name|GIMP_SELECTION_OFF
argument_list|)
expr_stmt|;
name|GIMP_DRAWABLE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|invalidate_boundary
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
comment|/*  If there is a floating selection, update it's area...    *  we need to do this since this selection mask can act as an additional    *  mask in the composition of the floating selection    */
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
operator|&&
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*  invalidate the preview  */
name|drawable
operator|->
name|preview_valid
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_selection_boundary (GimpChannel * channel,const BoundSeg ** segs_in,const BoundSeg ** segs_out,gint * num_segs_in,gint * num_segs_out,gint unused1,gint unused2,gint unused3,gint unused4)
name|gimp_selection_boundary
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
name|unused1
parameter_list|,
name|gint
name|unused2
parameter_list|,
name|gint
name|unused3
parameter_list|,
name|gint
name|unused4
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|layer
operator|=
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
operator|)
condition|)
block|{
comment|/*  If there is a floating selection, then        *  we need to do some slightly different boundaries.        *  Instead of inside and outside boundaries being defined        *  by the extents of the layer, the inside boundary (the one        *  that actually marches and is black/white) is the boundary of        *  the floating selection.  The outside boundary (doesn't move,        *  is black/gray) is defined as the normal selection mask        */
comment|/*  Find the selection mask boundary  */
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|boundary
argument_list|(
name|channel
argument_list|,
name|segs_in
argument_list|,
name|segs_out
argument_list|,
name|num_segs_in
argument_list|,
name|num_segs_out
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
comment|/*  Find the floating selection boundary  */
operator|*
name|segs_in
operator|=
name|floating_sel_boundary
argument_list|(
name|layer
argument_list|,
name|num_segs_in
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
elseif|else
if|if
condition|(
operator|(
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
operator|)
operator|&&
name|GIMP_IS_CHANNEL
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
comment|/*  Otherwise, return the boundary...if a channel is active  */
return|return
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|boundary
argument_list|(
name|channel
argument_list|,
name|segs_in
argument_list|,
name|segs_out
argument_list|,
name|num_segs_in
argument_list|,
name|num_segs_out
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
operator|(
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|gimage
argument_list|)
operator|)
condition|)
block|{
comment|/*  If a layer is active, we return multiple boundaries based        *  on the extents        */
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
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
name|x1
operator|=
name|CLAMP
argument_list|(
name|off_x
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|off_y
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|off_x
operator|+
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|off_y
operator|+
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
return|return
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|boundary
argument_list|(
name|channel
argument_list|,
name|segs_in
argument_list|,
name|segs_out
argument_list|,
name|num_segs_in
argument_list|,
name|num_segs_out
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
return|;
block|}
operator|*
name|segs_in
operator|=
name|NULL
expr_stmt|;
operator|*
name|segs_out
operator|=
name|NULL
expr_stmt|;
operator|*
name|num_segs_in
operator|=
literal|0
expr_stmt|;
operator|*
name|num_segs_out
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_selection_bounds (GimpChannel * channel,gint * x1,gint * y1,gint * x2,gint * y2)
name|gimp_selection_bounds
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
block|{
return|return
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|bounds
argument_list|(
name|channel
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_selection_is_empty (GimpChannel * channel)
name|gimp_selection_is_empty
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|)
block|{
name|GimpSelection
modifier|*
name|selection
init|=
name|GIMP_SELECTION
argument_list|(
name|channel
argument_list|)
decl_stmt|;
comment|/*  in order to allow stroking of selections, we need to pretend here    *  that the selection mask is empty so that it doesn't mask the paint    *  during the stroke operation.    */
if|if
condition|(
name|selection
operator|->
name|stroking
condition|)
return|return
name|TRUE
return|;
return|return
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|is_empty
argument_list|(
name|channel
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_selection_value (GimpChannel * channel,gint x,gint y)
name|gimp_selection_value
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
parameter_list|)
block|{
return|return
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|value
argument_list|(
name|channel
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_feather (GimpChannel * channel,gdouble radius_x,gdouble radius_y,gboolean push_undo)
name|gimp_selection_feather
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
block|{
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|feather
argument_list|(
name|channel
argument_list|,
name|radius_x
argument_list|,
name|radius_y
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_sharpen (GimpChannel * channel,gboolean push_undo)
name|gimp_selection_sharpen
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|sharpen
argument_list|(
name|channel
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_clear (GimpChannel * channel,const gchar * undo_desc,gboolean push_undo)
name|gimp_selection_clear
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
block|{
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|clear
argument_list|(
name|channel
argument_list|,
name|undo_desc
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_all (GimpChannel * channel,gboolean push_undo)
name|gimp_selection_all
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|all
argument_list|(
name|channel
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_invert (GimpChannel * channel,gboolean push_undo)
name|gimp_selection_invert
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|invert
argument_list|(
name|channel
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_border (GimpChannel * channel,gint radius_x,gint radius_y,gboolean push_undo)
name|gimp_selection_border
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
block|{
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|border
argument_list|(
name|channel
argument_list|,
name|radius_x
argument_list|,
name|radius_y
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_grow (GimpChannel * channel,gint radius_x,gint radius_y,gboolean push_undo)
name|gimp_selection_grow
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
block|{
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|grow
argument_list|(
name|channel
argument_list|,
name|radius_x
argument_list|,
name|radius_y
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_shrink (GimpChannel * channel,gint radius_x,gint radius_y,gboolean edge_lock,gboolean push_undo)
name|gimp_selection_shrink
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
block|{
name|GIMP_CHANNEL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|shrink
argument_list|(
name|channel
argument_list|,
name|radius_x
argument_list|,
name|radius_y
argument_list|,
name|edge_lock
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_selection_changed
argument_list|(
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_changed (GimpChannel * selection)
name|gimp_selection_changed
parameter_list|(
name|GimpChannel
modifier|*
name|selection
parameter_list|)
block|{
name|gimp_image_mask_changed
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|selection
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_validate (TileManager * tm,Tile * tile)
name|gimp_selection_validate
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
comment|/*  Set the contents of the tile to empty  */
name|memset
argument_list|(
name|tile_data_pointer
argument_list|(
name|tile
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|,
name|TRANSPARENT_OPACITY
argument_list|,
name|tile_size
argument_list|(
name|tile
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpChannel
modifier|*
DECL|function|gimp_selection_new (GimpImage * gimage,gint width,gint height)
name|gimp_selection_new
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
block|{
name|GimpRGB
name|black
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.5
block|}
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|channel
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_SELECTION
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_configure
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|,
name|gimage
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_GRAY_IMAGE
argument_list|,
name|_
argument_list|(
literal|"Selection Mask"
argument_list|)
argument_list|)
expr_stmt|;
name|channel
operator|->
name|color
operator|=
name|black
expr_stmt|;
name|channel
operator|->
name|show_masked
operator|=
name|TRUE
expr_stmt|;
name|channel
operator|->
name|x2
operator|=
name|width
expr_stmt|;
name|channel
operator|->
name|y2
operator|=
name|height
expr_stmt|;
comment|/*  Set the validate procedure  */
name|tile_manager_set_validate_proc
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
operator|->
name|tiles
argument_list|,
name|gimp_selection_validate
argument_list|)
expr_stmt|;
return|return
name|channel
return|;
block|}
end_function

end_unit

