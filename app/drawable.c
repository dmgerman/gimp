begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"channel.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"floating_sel.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"layer.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"drawable_pvt.h"
end_include

begin_enum
DECL|enum|__anon2bc30b6d0103
enum|enum
block|{
DECL|enumerator|INVALIDATE_PREVIEW
name|INVALIDATE_PREVIEW
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_drawable_class_init
parameter_list|(
name|GimpDrawableClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_init
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|drawable_signals
specifier|static
name|gint
name|drawable_signals
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
name|GimpDrawableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_drawable_get_type ()
name|gimp_drawable_get_type
parameter_list|()
block|{
specifier|static
name|GtkType
name|drawable_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|drawable_type
condition|)
block|{
name|GtkTypeInfo
name|drawable_info
init|=
block|{
literal|"GimpDrawable"
block|,
sizeof|sizeof
argument_list|(
name|GimpDrawable
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpDrawableClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_drawable_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_drawable_init
block|,
comment|/* reversed_1 */
name|NULL
block|,
comment|/* reversed_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|drawable_type
operator|=
name|gtk_type_unique
argument_list|(
name|gtk_data_get_type
argument_list|()
argument_list|,
operator|&
name|drawable_info
argument_list|)
expr_stmt|;
block|}
return|return
name|drawable_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_class_init (GimpDrawableClass * class)
name|gimp_drawable_class_init
parameter_list|(
name|GimpDrawableClass
modifier|*
name|class
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|class
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|gtk_data_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|drawable_signals
index|[
name|INVALIDATE_PREVIEW
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"invalidate_preview"
argument_list|,
name|GTK_RUN_LAST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpDrawableClass
argument_list|,
name|invalidate_preview
argument_list|)
argument_list|,
name|gtk_signal_default_marshaller
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
operator|(
name|guint
operator|*
operator|)
name|drawable_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_drawable_destroy
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  *  Static variables  */
end_comment

begin_decl_stmt
DECL|variable|global_drawable_ID
name|int
name|global_drawable_ID
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_table
specifier|static
name|GHashTable
modifier|*
name|drawable_table
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**************************/
end_comment

begin_comment
comment|/*  Function definitions  */
end_comment

begin_function
name|GimpDrawable
modifier|*
DECL|function|drawable_get_ID (int drawable_id)
name|drawable_get_ID
parameter_list|(
name|int
name|drawable_id
parameter_list|)
block|{
if|if
condition|(
name|drawable_table
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
return|return
operator|(
name|GimpDrawable
operator|*
operator|)
name|g_hash_table_lookup
argument_list|(
name|drawable_table
argument_list|,
operator|(
name|gpointer
operator|)
name|drawable_id
argument_list|)
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_ID (GimpDrawable * drawable)
name|drawable_ID
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
return|return
name|drawable
operator|->
name|ID
return|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_apply_image (GimpDrawable * drawable,int x1,int y1,int x2,int y2,TileManager * tiles,int sparse)
name|drawable_apply_image
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|x1
parameter_list|,
name|int
name|y1
parameter_list|,
name|int
name|x2
parameter_list|,
name|int
name|y2
parameter_list|,
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|int
name|sparse
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
block|{
if|if
condition|(
operator|!
name|tiles
condition|)
name|undo_push_image
argument_list|(
name|gimage_get_ID
argument_list|(
name|drawable
operator|->
name|gimage_ID
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
else|else
name|undo_push_image_mod
argument_list|(
name|gimage_get_ID
argument_list|(
name|drawable
operator|->
name|gimage_ID
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|tiles
argument_list|,
name|sparse
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|drawable_merge_shadow (GimpDrawable * drawable,int undo)
name|drawable_merge_shadow
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|undo
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|PixelRegion
name|shadowPR
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return;
comment|/*  A useful optimization here is to limit the update to the    *  extents of the selection mask, as it cannot extend beyond    *  them.    */
name|drawable_mask_bounds
argument_list|(
name|drawable
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
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimage_apply_image
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
operator|&
name|shadowPR
argument_list|,
name|undo
argument_list|,
name|OPAQUE_OPACITY
argument_list|,
name|REPLACE_MODE
argument_list|,
name|NULL
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_fill (GimpDrawable * drawable,int fill_type)
name|drawable_fill
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|fill_type
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|unsigned
name|char
name|c
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|unsigned
name|char
name|i
decl_stmt|,
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return;
name|a
operator|=
literal|255
expr_stmt|;
comment|/*  a gimage_fill affects the active layer  */
switch|switch
condition|(
name|fill_type
condition|)
block|{
case|case
name|BACKGROUND_FILL
case|:
name|palette_get_background
argument_list|(
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|a
operator|=
literal|255
expr_stmt|;
break|break;
case|case
name|WHITE_FILL
case|:
name|a
operator|=
name|r
operator|=
name|g
operator|=
name|b
operator|=
literal|255
expr_stmt|;
break|break;
case|case
name|TRANSPARENT_FILL
case|:
name|r
operator|=
name|g
operator|=
name|b
operator|=
name|a
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|NO_FILL
case|:
return|return;
break|break;
block|}
switch|switch
condition|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
case|case
name|RGB_GIMAGE
case|:
case|case
name|RGBA_GIMAGE
case|:
name|c
index|[
name|RED_PIX
index|]
operator|=
name|r
expr_stmt|;
name|c
index|[
name|GREEN_PIX
index|]
operator|=
name|g
expr_stmt|;
name|c
index|[
name|BLUE_PIX
index|]
operator|=
name|b
expr_stmt|;
if|if
condition|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|RGBA_GIMAGE
condition|)
name|c
index|[
name|ALPHA_PIX
index|]
operator|=
name|a
expr_stmt|;
break|break;
case|case
name|GRAY_GIMAGE
case|:
case|case
name|GRAYA_GIMAGE
case|:
name|c
index|[
name|GRAY_PIX
index|]
operator|=
name|r
expr_stmt|;
if|if
condition|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|GRAYA_GIMAGE
condition|)
name|c
index|[
name|ALPHA_G_PIX
index|]
operator|=
name|a
expr_stmt|;
break|break;
case|case
name|INDEXED_GIMAGE
case|:
case|case
name|INDEXEDA_GIMAGE
case|:
name|c
index|[
name|RED_PIX
index|]
operator|=
name|r
expr_stmt|;
name|c
index|[
name|GREEN_PIX
index|]
operator|=
name|g
expr_stmt|;
name|c
index|[
name|BLUE_PIX
index|]
operator|=
name|b
expr_stmt|;
name|gimage_transform_color
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|c
argument_list|,
operator|&
name|i
argument_list|,
name|RGB
argument_list|)
expr_stmt|;
name|c
index|[
name|INDEXED_PIX
index|]
operator|=
name|i
expr_stmt|;
if|if
condition|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXEDA_GIMAGE
condition|)
name|c
index|[
name|ALPHA_I_PIX
index|]
operator|=
name|a
expr_stmt|;
break|break;
default|default:
name|g_message
argument_list|(
literal|"Can't fill unknown image type."
argument_list|)
expr_stmt|;
break|break;
block|}
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|destPR
argument_list|,
name|c
argument_list|)
expr_stmt|;
comment|/*  Update the filled area  */
name|drawable_update
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_update (GimpDrawable * drawable,int x,int y,int w,int h)
name|drawable_update
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return;
name|drawable_offsets
argument_list|(
name|drawable
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|x
operator|+=
name|offset_x
expr_stmt|;
name|y
operator|+=
name|offset_y
expr_stmt|;
name|gdisplays_update_area
argument_list|(
name|gimage
operator|->
name|ID
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
comment|/*  invalidate the preview  */
name|drawable_invalidate_preview
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_mask_bounds (GimpDrawable * drawable,int * x1,int * y1,int * x2,int * y2)
name|drawable_mask_bounds
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
modifier|*
name|x1
parameter_list|,
name|int
modifier|*
name|y1
parameter_list|,
name|int
modifier|*
name|x2
parameter_list|,
name|int
modifier|*
name|y2
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|gimage_mask_bounds
argument_list|(
name|gimage
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
condition|)
block|{
name|drawable_offsets
argument_list|(
name|drawable
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
operator|*
name|x1
operator|=
name|BOUNDS
argument_list|(
operator|*
name|x1
operator|-
name|off_x
argument_list|,
literal|0
argument_list|,
name|drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|y1
operator|=
name|BOUNDS
argument_list|(
operator|*
name|y1
operator|-
name|off_y
argument_list|,
literal|0
argument_list|,
name|drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|x2
operator|=
name|BOUNDS
argument_list|(
operator|*
name|x2
operator|-
name|off_x
argument_list|,
literal|0
argument_list|,
name|drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|y2
operator|=
name|BOUNDS
argument_list|(
operator|*
name|y2
operator|-
name|off_y
argument_list|,
literal|0
argument_list|,
name|drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
block|{
operator|*
name|x2
operator|=
name|drawable_width
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
operator|*
name|y2
operator|=
name|drawable_height
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|drawable_invalidate_preview (GimpDrawable * drawable)
name|drawable_invalidate_preview
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
name|drawable
operator|->
name|preview_valid
operator|=
name|FALSE
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|drawable_signals
index|[
name|INVALIDATE_PREVIEW
index|]
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|gimage
operator|->
name|comp_preview_valid
index|[
literal|0
index|]
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|->
name|comp_preview_valid
index|[
literal|1
index|]
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|->
name|comp_preview_valid
index|[
literal|2
index|]
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|int
DECL|function|drawable_dirty (GimpDrawable * drawable)
name|drawable_dirty
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|dirty
operator|=
operator|(
name|drawable
operator|->
name|dirty
operator|<
literal|0
operator|)
condition|?
literal|2
else|:
name|drawable
operator|->
name|dirty
operator|+
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_clean (GimpDrawable * drawable)
name|drawable_clean
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|dirty
operator|=
operator|(
name|drawable
operator|->
name|dirty
operator|<=
literal|0
operator|)
condition|?
literal|0
else|:
name|drawable
operator|->
name|dirty
operator|-
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|GImage
modifier|*
DECL|function|drawable_gimage (GimpDrawable * drawable)
name|drawable_gimage
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|gimage_get_ID
argument_list|(
name|drawable
operator|->
name|gimage_ID
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_type (GimpDrawable * drawable)
name|drawable_type
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|type
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_has_alpha (GimpDrawable * drawable)
name|drawable_has_alpha
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|has_alpha
return|;
else|else
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_visible (GimpDrawable * drawable)
name|drawable_visible
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
return|return
name|drawable
operator|->
name|visible
return|;
block|}
end_function

begin_function
name|char
modifier|*
DECL|function|drawable_name (GimpDrawable * drawable)
name|drawable_name
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
return|return
name|drawable
operator|->
name|name
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_type_with_alpha (GimpDrawable * drawable)
name|drawable_type_with_alpha
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|int
name|type
init|=
name|drawable_type
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|int
name|has_alpha
init|=
name|drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
if|if
condition|(
name|has_alpha
condition|)
return|return
name|type
return|;
else|else
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|RGB_GIMAGE
case|:
return|return
name|RGBA_GIMAGE
return|;
break|break;
case|case
name|GRAY_GIMAGE
case|:
return|return
name|GRAYA_GIMAGE
return|;
break|break;
case|case
name|INDEXED_GIMAGE
case|:
return|return
name|INDEXEDA_GIMAGE
return|;
break|break;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_color (GimpDrawable * drawable)
name|drawable_color
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|RGBA_GIMAGE
operator|||
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|RGB_GIMAGE
condition|)
return|return
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_gray (GimpDrawable * drawable)
name|drawable_gray
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|GRAYA_GIMAGE
operator|||
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|GRAY_GIMAGE
condition|)
return|return
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_indexed (GimpDrawable * drawable)
name|drawable_indexed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXEDA_GIMAGE
operator|||
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXED_GIMAGE
condition|)
return|return
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|drawable_data (GimpDrawable * drawable)
name|drawable_data
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|tiles
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|drawable_shadow (GimpDrawable * drawable)
name|drawable_shadow
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|drawable
condition|)
return|return
name|gimage_shadow
argument_list|(
name|gimage
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|drawable
operator|->
name|bytes
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_bytes (GimpDrawable * drawable)
name|drawable_bytes
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|bytes
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_width (GimpDrawable * drawable)
name|drawable_width
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|width
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|int
DECL|function|drawable_height (GimpDrawable * drawable)
name|drawable_height
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|height
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_offsets (GimpDrawable * drawable,int * off_x,int * off_y)
name|drawable_offsets
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
modifier|*
name|off_x
parameter_list|,
name|int
modifier|*
name|off_y
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
block|{
operator|*
name|off_x
operator|=
name|drawable
operator|->
name|offset_x
expr_stmt|;
operator|*
name|off_y
operator|=
name|drawable
operator|->
name|offset_y
expr_stmt|;
block|}
else|else
operator|*
name|off_x
operator|=
operator|*
name|off_y
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
name|unsigned
name|char
modifier|*
DECL|function|drawable_cmap (GimpDrawable * drawable)
name|drawable_cmap
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return
name|gimage
operator|->
name|cmap
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|Layer
modifier|*
DECL|function|drawable_layer (GimpDrawable * drawable)
name|drawable_layer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
operator|&&
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
return|return
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|LayerMask
modifier|*
DECL|function|drawable_layer_mask (GimpDrawable * drawable)
name|drawable_layer_mask
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
operator|&&
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
return|return
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|Channel
modifier|*
DECL|function|drawable_channel (GimpDrawable * drawable)
name|drawable_channel
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
operator|&&
name|GIMP_IS_CHANNEL
argument_list|(
name|drawable
argument_list|)
condition|)
return|return
name|GIMP_CHANNEL
argument_list|(
name|drawable
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_deallocate (GimpDrawable * drawable)
name|drawable_deallocate
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
operator|->
name|tiles
condition|)
name|tile_manager_destroy
argument_list|(
name|drawable
operator|->
name|tiles
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_init (GimpDrawable * drawable)
name|gimp_drawable_init
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|drawable
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|tiles
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|visible
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|->
name|width
operator|=
name|drawable
operator|->
name|height
operator|=
literal|0
expr_stmt|;
name|drawable
operator|->
name|offset_x
operator|=
name|drawable
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
name|drawable
operator|->
name|bytes
operator|=
literal|0
expr_stmt|;
name|drawable
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|->
name|gimage_ID
operator|=
operator|-
literal|1
expr_stmt|;
name|drawable
operator|->
name|type
operator|=
operator|-
literal|1
expr_stmt|;
name|drawable
operator|->
name|has_alpha
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|->
name|preview
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|preview_valid
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|->
name|ID
operator|=
name|global_drawable_ID
operator|++
expr_stmt|;
if|if
condition|(
name|drawable_table
operator|==
name|NULL
condition|)
name|drawable_table
operator|=
name|g_hash_table_new
argument_list|(
name|g_direct_hash
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|drawable_table
argument_list|,
operator|(
name|gpointer
operator|)
name|drawable
operator|->
name|ID
argument_list|,
operator|(
name|gpointer
operator|)
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_destroy (GtkObject * object)
name|gimp_drawable_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|object
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_hash_table_remove
argument_list|(
name|drawable_table
argument_list|,
operator|(
name|gpointer
operator|)
name|drawable
operator|->
name|ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|drawable
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|tiles
condition|)
name|tile_manager_destroy
argument_list|(
name|drawable
operator|->
name|tiles
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|preview
condition|)
name|temp_buf_free
argument_list|(
name|drawable
operator|->
name|preview
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
operator|(
operator|*
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
operator|)
operator|(
name|object
operator|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_configure (GimpDrawable * drawable,int gimage_ID,int width,int height,int type,char * name)
name|gimp_drawable_configure
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|gimage_ID
parameter_list|,
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|int
name|type
parameter_list|,
name|char
modifier|*
name|name
parameter_list|)
block|{
name|int
name|bpp
decl_stmt|;
name|int
name|alpha
decl_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
literal|"unnamed"
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|RGB_GIMAGE
case|:
name|bpp
operator|=
literal|3
expr_stmt|;
name|alpha
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|GRAY_GIMAGE
case|:
name|bpp
operator|=
literal|1
expr_stmt|;
name|alpha
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|RGBA_GIMAGE
case|:
name|bpp
operator|=
literal|4
expr_stmt|;
name|alpha
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GRAYA_GIMAGE
case|:
name|bpp
operator|=
literal|2
expr_stmt|;
name|alpha
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|INDEXED_GIMAGE
case|:
name|bpp
operator|=
literal|1
expr_stmt|;
name|alpha
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|INDEXEDA_GIMAGE
case|:
name|bpp
operator|=
literal|2
expr_stmt|;
name|alpha
operator|=
literal|1
expr_stmt|;
break|break;
default|default:
name|g_message
argument_list|(
literal|"Layer type %d not supported."
argument_list|,
name|type
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|drawable
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|drawable
operator|->
name|name
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|drawable
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|drawable
operator|->
name|bytes
operator|=
name|bpp
expr_stmt|;
name|drawable
operator|->
name|type
operator|=
name|type
expr_stmt|;
name|drawable
operator|->
name|has_alpha
operator|=
name|alpha
expr_stmt|;
name|drawable
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|drawable
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|tiles
condition|)
name|tile_manager_destroy
argument_list|(
name|drawable
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|tiles
operator|=
name|tile_manager_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|bpp
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|->
name|visible
operator|=
name|TRUE
expr_stmt|;
name|drawable
operator|->
name|gimage_ID
operator|=
name|gimage_ID
expr_stmt|;
comment|/*  preview variables  */
name|drawable
operator|->
name|preview
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|preview_valid
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

