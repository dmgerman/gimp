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
file|"base/tile.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemap.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b2646810103
block|{
DECL|enumerator|FLUSH
name|FLUSH
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpImageMap
struct|struct
name|_GimpImageMap
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|undo_desc
name|gchar
modifier|*
name|undo_desc
decl_stmt|;
DECL|member|undo_tiles
name|TileManager
modifier|*
name|undo_tiles
decl_stmt|;
DECL|member|undo_offset_x
name|gint
name|undo_offset_x
decl_stmt|;
DECL|member|undo_offset_y
name|gint
name|undo_offset_y
decl_stmt|;
DECL|member|apply_func
name|GimpImageMapApplyFunc
name|apply_func
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|srcPR
name|PixelRegion
name|srcPR
decl_stmt|;
DECL|member|destPR
name|PixelRegion
name|destPR
decl_stmt|;
DECL|member|PRI
name|PixelRegionIterator
modifier|*
name|PRI
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_image_map_class_init
parameter_list|(
name|GimpImageMapClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_init
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_pickable_iface_init
parameter_list|(
name|GimpPickableInterface
modifier|*
name|pickable_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpImage
modifier|*
name|gimp_image_map_get_image
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpImageType
name|gimp_image_map_get_image_type
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TileManager
modifier|*
name|gimp_image_map_get_tiles
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guchar
modifier|*
name|gimp_image_map_get_color_at
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
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
name|gboolean
name|gimp_image_map_do
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|image_map_signals
specifier|static
name|guint
name|image_map_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_image_map_get_type (void)
name|gimp_image_map_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|image_map_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|image_map_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|image_map_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpImageMapClass
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
name|gimp_image_map_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpImageMap
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_image_map_init
block|,       }
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|pickable_iface_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_image_map_pickable_iface_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|image_map_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
literal|"GimpImageMap"
argument_list|,
operator|&
name|image_map_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|image_map_type
argument_list|,
name|GIMP_TYPE_PICKABLE
argument_list|,
operator|&
name|pickable_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|image_map_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_class_init (GimpImageMapClass * klass)
name|gimp_image_map_class_init
parameter_list|(
name|GimpImageMapClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|image_map_signals
index|[
name|FLUSH
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"flush"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpImageMapClass
argument_list|,
name|flush
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_image_map_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_init (GimpImageMap * image_map)
name|gimp_image_map_init
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
name|image_map
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
name|image_map
operator|->
name|undo_tiles
operator|=
name|NULL
expr_stmt|;
name|image_map
operator|->
name|undo_offset_x
operator|=
literal|0
expr_stmt|;
name|image_map
operator|->
name|undo_offset_y
operator|=
literal|0
expr_stmt|;
name|image_map
operator|->
name|apply_func
operator|=
name|NULL
expr_stmt|;
name|image_map
operator|->
name|user_data
operator|=
name|NULL
expr_stmt|;
name|image_map
operator|->
name|PRI
operator|=
name|NULL
expr_stmt|;
name|image_map
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_pickable_iface_init (GimpPickableInterface * pickable_iface)
name|gimp_image_map_pickable_iface_init
parameter_list|(
name|GimpPickableInterface
modifier|*
name|pickable_iface
parameter_list|)
block|{
name|pickable_iface
operator|->
name|get_image
operator|=
name|gimp_image_map_get_image
expr_stmt|;
name|pickable_iface
operator|->
name|get_image_type
operator|=
name|gimp_image_map_get_image_type
expr_stmt|;
name|pickable_iface
operator|->
name|get_tiles
operator|=
name|gimp_image_map_get_tiles
expr_stmt|;
name|pickable_iface
operator|->
name|get_color_at
operator|=
name|gimp_image_map_get_color_at
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_finalize (GObject * object)
name|gimp_image_map_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|image_map
operator|->
name|undo_desc
condition|)
block|{
name|g_free
argument_list|(
name|image_map
operator|->
name|undo_desc
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|undo_desc
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpImage
modifier|*
DECL|function|gimp_image_map_get_image (GimpPickable * pickable)
name|gimp_image_map_get_image
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|pickable
argument_list|)
decl_stmt|;
return|return
name|gimp_pickable_get_image
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpImageType
DECL|function|gimp_image_map_get_image_type (GimpPickable * pickable)
name|gimp_image_map_get_image_type
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|pickable
argument_list|)
decl_stmt|;
return|return
name|gimp_pickable_get_image_type
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|TileManager
modifier|*
DECL|function|gimp_image_map_get_tiles (GimpPickable * pickable)
name|gimp_image_map_get_tiles
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|pickable
argument_list|)
decl_stmt|;
if|if
condition|(
name|image_map
operator|->
name|undo_tiles
condition|)
return|return
name|image_map
operator|->
name|undo_tiles
return|;
else|else
return|return
name|gimp_pickable_get_tiles
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|guchar
modifier|*
DECL|function|gimp_image_map_get_color_at (GimpPickable * pickable,gint x,gint y)
name|gimp_image_map_get_color_at
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|pickable
argument_list|)
decl_stmt|;
name|guchar
name|src
index|[
literal|5
index|]
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
if|if
condition|(
name|x
operator|>=
literal|0
operator|&&
name|x
operator|<
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
operator|&&
name|y
operator|>=
literal|0
operator|&&
name|y
operator|<
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
comment|/* Check if done damage to original image */
if|if
condition|(
operator|!
name|image_map
operator|->
name|undo_tiles
condition|)
return|return
name|gimp_pickable_get_color_at
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
return|;
if|if
condition|(
operator|(
operator|!
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
operator|&&
name|gimp_drawable_is_indexed
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
operator|)
operator|||
name|x
operator|<
literal|0
operator|||
name|y
operator|<
literal|0
operator|||
name|x
operator|>=
name|tile_manager_width
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
operator|||
name|y
operator|>=
name|tile_manager_height
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|read_pixel_data_1
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|src
argument_list|)
expr_stmt|;
name|gimp_image_get_color
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_drawable_type
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|src
argument_list|,
name|dest
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
condition|)
name|dest
index|[
literal|4
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
else|else
name|dest
index|[
literal|4
index|]
operator|=
literal|0
expr_stmt|;
return|return
name|dest
return|;
block|}
else|else
comment|/* out of bounds error */
block|{
return|return
name|NULL
return|;
block|}
block|}
end_function

begin_function
name|GimpImageMap
modifier|*
DECL|function|gimp_image_map_new (GimpDrawable * drawable,const gchar * undo_desc)
name|gimp_image_map_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
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
name|image_map
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_IMAGE_MAP
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|image_map
operator|->
name|undo_desc
operator|=
name|g_strdup
argument_list|(
name|undo_desc
argument_list|)
expr_stmt|;
return|return
name|image_map
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_apply (GimpImageMap * image_map,GimpImageMapApplyFunc apply_func,gpointer apply_data)
name|gimp_image_map_apply
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
name|GimpImageMapApplyFunc
name|apply_func
parameter_list|,
name|gpointer
name|apply_data
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|undo_offset_x
decl_stmt|,
name|undo_offset_y
decl_stmt|;
name|gint
name|undo_width
decl_stmt|,
name|undo_height
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP
argument_list|(
name|image_map
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|apply_func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|apply_func
operator|=
name|apply_func
expr_stmt|;
name|image_map
operator|->
name|user_data
operator|=
name|apply_data
expr_stmt|;
comment|/*  If we're still working, remove the timer  */
if|if
condition|(
name|image_map
operator|->
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|image_map
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
name|pixel_regions_process_stop
argument_list|(
name|image_map
operator|->
name|PRI
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|PRI
operator|=
name|NULL
expr_stmt|;
block|}
comment|/*  Make sure the drawable is still valid  */
if|if
condition|(
operator|!
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
condition|)
return|return;
comment|/*  The application should occur only within selection bounds  */
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
return|return;
comment|/*  If undo tiles don't exist, or change size, (re)allocate  */
if|if
condition|(
name|image_map
operator|->
name|undo_tiles
condition|)
block|{
name|undo_offset_x
operator|=
name|image_map
operator|->
name|undo_offset_x
expr_stmt|;
name|undo_offset_y
operator|=
name|image_map
operator|->
name|undo_offset_y
expr_stmt|;
name|undo_width
operator|=
name|tile_manager_width
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
name|undo_height
operator|=
name|tile_manager_height
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|undo_offset_x
operator|=
literal|0
expr_stmt|;
name|undo_offset_y
operator|=
literal|0
expr_stmt|;
name|undo_width
operator|=
literal|0
expr_stmt|;
name|undo_height
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|image_map
operator|->
name|undo_tiles
operator|||
name|undo_offset_x
operator|!=
name|x
operator|||
name|undo_offset_y
operator|!=
name|y
operator|||
name|undo_width
operator|!=
name|width
operator|||
name|undo_height
operator|!=
name|height
condition|)
block|{
comment|/* If either the extents changed or the tiles don't exist,        * allocate new        */
if|if
condition|(
operator|!
name|image_map
operator|->
name|undo_tiles
operator|||
name|undo_width
operator|!=
name|width
operator|||
name|undo_height
operator|!=
name|height
condition|)
block|{
comment|/*  Destroy old tiles  */
if|if
condition|(
name|image_map
operator|->
name|undo_tiles
condition|)
name|tile_manager_unref
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
comment|/*  Allocate new tiles  */
name|image_map
operator|->
name|undo_tiles
operator|=
name|tile_manager_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  Copy from the image to the new tiles  */
name|pixel_region_init
argument_list|(
operator|&
name|image_map
operator|->
name|srcPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
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
name|image_map
operator|->
name|destPR
argument_list|,
name|image_map
operator|->
name|undo_tiles
argument_list|,
literal|0
argument_list|,
literal|0
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
name|image_map
operator|->
name|srcPR
argument_list|,
operator|&
name|image_map
operator|->
name|destPR
argument_list|)
expr_stmt|;
comment|/*  Set the offsets  */
name|image_map
operator|->
name|undo_offset_x
operator|=
name|x
expr_stmt|;
name|image_map
operator|->
name|undo_offset_y
operator|=
name|y
expr_stmt|;
block|}
else|else
comment|/* image_map->undo_tiles exist AND drawable dimensions have not changed         */
block|{
comment|/* Reset to initial drawable conditions.            */
comment|/* Copy from the backup undo tiles to the drawable  */
name|pixel_region_init
argument_list|(
operator|&
name|image_map
operator|->
name|srcPR
argument_list|,
name|image_map
operator|->
name|undo_tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|undo_width
argument_list|,
name|undo_height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|image_map
operator|->
name|destPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|undo_offset_x
argument_list|,
name|undo_offset_y
argument_list|,
name|undo_width
argument_list|,
name|undo_height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|image_map
operator|->
name|srcPR
argument_list|,
operator|&
name|image_map
operator|->
name|destPR
argument_list|)
expr_stmt|;
block|}
comment|/*  Configure the src from the drawable data  */
name|pixel_region_init
argument_list|(
operator|&
name|image_map
operator|->
name|srcPR
argument_list|,
name|image_map
operator|->
name|undo_tiles
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
comment|/*  Configure the dest as the shadow buffer  */
name|pixel_region_init
argument_list|(
operator|&
name|image_map
operator|->
name|destPR
argument_list|,
name|gimp_drawable_shadow
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Apply the image transformation to the pixels  */
name|image_map
operator|->
name|PRI
operator|=
name|pixel_regions_register
argument_list|(
literal|2
argument_list|,
operator|&
name|image_map
operator|->
name|srcPR
argument_list|,
operator|&
name|image_map
operator|->
name|destPR
argument_list|)
expr_stmt|;
comment|/*  Start the intermittant work procedure  */
name|image_map
operator|->
name|idle_id
operator|=
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|gimp_image_map_do
argument_list|,
name|image_map
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_commit (GimpImageMap * image_map)
name|gimp_image_map_commit
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP
argument_list|(
name|image_map
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_map
operator|->
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|image_map
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
comment|/*  Finish the changes  */
while|while
condition|(
name|gimp_image_map_do
argument_list|(
name|image_map
argument_list|)
condition|)
empty_stmt|;
block|}
comment|/*  Make sure the drawable is still valid  */
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
condition|)
return|return;
comment|/*  Register an undo step  */
if|if
condition|(
name|image_map
operator|->
name|undo_tiles
condition|)
block|{
name|x1
operator|=
name|image_map
operator|->
name|undo_offset_x
expr_stmt|;
name|y1
operator|=
name|image_map
operator|->
name|undo_offset_y
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
name|tile_manager_width
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|tile_manager_height
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
name|gimp_drawable_push_undo
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
name|image_map
operator|->
name|undo_desc
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|image_map
operator|->
name|undo_tiles
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|undo_tiles
operator|=
name|NULL
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_clear (GimpImageMap * image_map)
name|gimp_image_map_clear
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP
argument_list|(
name|image_map
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_map
operator|->
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|image_map
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
name|pixel_regions_process_stop
argument_list|(
name|image_map
operator|->
name|PRI
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|PRI
operator|=
name|NULL
expr_stmt|;
block|}
comment|/*  Make sure the drawable is still valid  */
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
condition|)
return|return;
comment|/*  restore the original image  */
if|if
condition|(
name|image_map
operator|->
name|undo_tiles
condition|)
block|{
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|offset_x
operator|=
name|image_map
operator|->
name|undo_offset_x
expr_stmt|;
name|offset_y
operator|=
name|image_map
operator|->
name|undo_offset_y
expr_stmt|;
name|width
operator|=
name|tile_manager_width
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
name|height
operator|=
name|tile_manager_height
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
operator|,
comment|/*  Copy from the drawable to the tiles  */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|image_map
operator|->
name|undo_tiles
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
name|gimp_drawable_data
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* if the user has changed the image depth get out quickly */
if|if
condition|(
name|destPR
operator|.
name|bytes
operator|!=
name|srcPR
operator|.
name|bytes
condition|)
block|{
name|g_message
argument_list|(
literal|"image depth change, unable to restore original image"
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|undo_tiles
operator|=
name|NULL
expr_stmt|;
name|g_object_unref
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
return|return;
block|}
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
comment|/*  Update the area  */
name|gimp_drawable_update
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
comment|/*  Free the undo_tiles tile manager  */
name|tile_manager_unref
argument_list|(
name|image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|undo_tiles
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_abort (GimpImageMap * image_map)
name|gimp_image_map_abort
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP
argument_list|(
name|image_map
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
condition|)
return|return;
name|gimp_image_map_clear
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_map_do (GimpImageMap * image_map)
name|gimp_image_map_do
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|PixelRegion
name|shadowPR
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
condition|)
block|{
name|image_map
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/*  Process up to 16 tiles in one go. This reduces the overhead    *  caused by updating the display while the imagemap is being    *  applied and gives us a tiny speedup.    */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|16
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|image_map
operator|->
name|apply_func
argument_list|(
operator|&
name|image_map
operator|->
name|srcPR
argument_list|,
operator|&
name|image_map
operator|->
name|destPR
argument_list|,
name|image_map
operator|->
name|user_data
argument_list|)
expr_stmt|;
name|x
operator|=
name|image_map
operator|->
name|destPR
operator|.
name|x
expr_stmt|;
name|y
operator|=
name|image_map
operator|->
name|destPR
operator|.
name|y
expr_stmt|;
name|w
operator|=
name|image_map
operator|->
name|destPR
operator|.
name|w
expr_stmt|;
name|h
operator|=
name|image_map
operator|->
name|destPR
operator|.
name|h
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|shadowPR
argument_list|,
name|gimage
operator|->
name|shadow
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_region
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
operator|&
name|shadowPR
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_REPLACE_MODE
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|image_map
operator|->
name|drawable
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
name|image_map
operator|->
name|PRI
operator|=
name|pixel_regions_process
argument_list|(
name|image_map
operator|->
name|PRI
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_map
operator|->
name|PRI
operator|==
name|NULL
condition|)
block|{
name|image_map
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
name|g_signal_emit
argument_list|(
name|image_map
argument_list|,
name|image_map_signals
index|[
name|FLUSH
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

