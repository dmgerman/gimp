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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpmaskundo.h"
end_include

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_mask_undo_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_mask_undo_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mask_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mask_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpMaskUndo,gimp_mask_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMaskUndo
argument_list|,
argument|gimp_mask_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_mask_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_mask_undo_class_init
parameter_list|(
name|GimpMaskUndoClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpUndoClass
modifier|*
name|undo_class
init|=
name|GIMP_UNDO_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_mask_undo_constructor
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_mask_undo_get_memsize
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_mask_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_mask_undo_free
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mask_undo_init (GimpMaskUndo * undo)
name|gimp_mask_undo_init
parameter_list|(
name|GimpMaskUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_mask_undo_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_mask_undo_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpMaskUndo
modifier|*
name|mask_undo
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|mask_undo
operator|=
name|GIMP_MASK_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|channel
operator|=
name|GIMP_CHANNEL
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_channel_bounds
argument_list|(
name|channel
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
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|mask_undo
operator|->
name|tiles
operator|=
name|tile_manager_new
argument_list|(
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|mask_undo
operator|->
name|x
operator|=
name|x1
expr_stmt|;
name|mask_undo
operator|->
name|y
operator|=
name|y1
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|mask_undo
operator|->
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
block|}
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|gint64
DECL|function|gimp_mask_undo_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_mask_undo_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpMaskUndo
modifier|*
name|mask_undo
init|=
name|GIMP_MASK_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|tile_manager_get_memsize
argument_list|(
name|mask_undo
operator|->
name|tiles
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mask_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_mask_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
block|{
name|GimpMaskUndo
modifier|*
name|mask_undo
init|=
name|GIMP_MASK_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
init|=
name|GIMP_CHANNEL
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
argument_list|)
decl_stmt|;
name|TileManager
modifier|*
name|new_tiles
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|width
init|=
literal|0
decl_stmt|;
name|gint
name|height
init|=
literal|0
decl_stmt|;
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|pop
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|,
name|accum
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_channel_bounds
argument_list|(
name|channel
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
name|new_tiles
operator|=
name|tile_manager_new
argument_list|(
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|clear_region
argument_list|(
operator|&
name|srcPR
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new_tiles
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|mask_undo
operator|->
name|tiles
condition|)
block|{
name|width
operator|=
name|tile_manager_width
argument_list|(
name|mask_undo
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|height
operator|=
name|tile_manager_height
argument_list|(
name|mask_undo
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|mask_undo
operator|->
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
argument_list|,
name|mask_undo
operator|->
name|x
argument_list|,
name|mask_undo
operator|->
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|mask_undo
operator|->
name|tiles
argument_list|)
expr_stmt|;
block|}
comment|/* invalidate the current bounds and boundary of the mask */
name|gimp_drawable_invalidate_boundary
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask_undo
operator|->
name|tiles
condition|)
block|{
name|channel
operator|->
name|empty
operator|=
name|FALSE
expr_stmt|;
name|channel
operator|->
name|x1
operator|=
name|mask_undo
operator|->
name|x
expr_stmt|;
name|channel
operator|->
name|y1
operator|=
name|mask_undo
operator|->
name|y
expr_stmt|;
name|channel
operator|->
name|x2
operator|=
name|mask_undo
operator|->
name|x
operator|+
name|width
expr_stmt|;
name|channel
operator|->
name|y2
operator|=
name|mask_undo
operator|->
name|y
operator|+
name|height
expr_stmt|;
block|}
else|else
block|{
name|channel
operator|->
name|empty
operator|=
name|TRUE
expr_stmt|;
name|channel
operator|->
name|x1
operator|=
literal|0
expr_stmt|;
name|channel
operator|->
name|y1
operator|=
literal|0
expr_stmt|;
name|channel
operator|->
name|x2
operator|=
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|channel
operator|->
name|y2
operator|=
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/* we know the bounds */
name|channel
operator|->
name|bounds_known
operator|=
name|TRUE
expr_stmt|;
comment|/*  set the new mask undo parameters  */
name|mask_undo
operator|->
name|tiles
operator|=
name|new_tiles
expr_stmt|;
name|mask_undo
operator|->
name|x
operator|=
name|x1
expr_stmt|;
name|mask_undo
operator|->
name|y
operator|=
name|y1
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mask_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_mask_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpMaskUndo
modifier|*
name|mask_undo
init|=
name|GIMP_MASK_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
if|if
condition|(
name|mask_undo
operator|->
name|tiles
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|mask_undo
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|mask_undo
operator|->
name|tiles
operator|=
name|NULL
expr_stmt|;
block|}
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|free
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

