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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprojection.h"
end_include

begin_include
include|#
directive|include
file|"gimpclone.h"
end_include

begin_include
include|#
directive|include
file|"gimpcloneoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_clone_class_init
parameter_list|(
name|GimpCloneClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_init
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_line_image
parameter_list|(
name|GimpImage
modifier|*
name|dest
parameter_list|,
name|GimpImage
modifier|*
name|src
parameter_list|,
name|GimpDrawable
modifier|*
name|d_drawable
parameter_list|,
name|GimpPickable
modifier|*
name|s_pickable
parameter_list|,
name|guchar
modifier|*
name|s
parameter_list|,
name|guchar
modifier|*
name|d
parameter_list|,
name|gint
name|src_bytes
parameter_list|,
name|gint
name|dest_bytes
parameter_list|,
name|gint
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_line_pattern
parameter_list|(
name|GimpImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|,
name|guchar
modifier|*
name|d
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_set_src_drawable
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpBrushCoreClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_clone_register (Gimp * gimp,GimpPaintRegisterCallback callback)
name|gimp_clone_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_CLONE
argument_list|,
name|GIMP_TYPE_CLONE_OPTIONS
argument_list|,
name|_
argument_list|(
literal|"Clone"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_clone_get_type (void)
name|gimp_clone_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpCloneClass
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
name|gimp_clone_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpClone
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_clone_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_BRUSH_CORE
argument_list|,
literal|"GimpClone"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_class_init (GimpCloneClass * klass)
name|gimp_clone_class_init
parameter_list|(
name|GimpCloneClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
init|=
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpBrushCoreClass
modifier|*
name|brush_core_class
init|=
name|GIMP_BRUSH_CORE_CLASS
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
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_clone_paint
expr_stmt|;
name|brush_core_class
operator|->
name|handles_changing_brush
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_init (GimpClone * clone)
name|gimp_clone_init
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|)
block|{
name|clone
operator|->
name|set_source
operator|=
name|FALSE
expr_stmt|;
name|clone
operator|->
name|src_drawable
operator|=
name|NULL
expr_stmt|;
name|clone
operator|->
name|src_x
operator|=
literal|0.0
expr_stmt|;
name|clone
operator|->
name|src_y
operator|=
literal|0.0
expr_stmt|;
name|clone
operator|->
name|orig_src_x
operator|=
literal|0
expr_stmt|;
name|clone
operator|->
name|orig_src_y
operator|=
literal|0
expr_stmt|;
name|clone
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|clone
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
name|clone
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPaintState paint_state,guint32 time)
name|gimp_clone_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|GimpClone
modifier|*
name|clone
init|=
name|GIMP_CLONE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpCloneOptions
modifier|*
name|options
init|=
name|GIMP_CLONE_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|GIMP_PAINT_STATE_INIT
case|:
if|if
condition|(
name|clone
operator|->
name|set_source
condition|)
block|{
name|gimp_clone_set_src_drawable
argument_list|(
name|clone
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|clone
operator|->
name|src_x
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|x
expr_stmt|;
name|clone
operator|->
name|src_y
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|y
expr_stmt|;
name|clone
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|align_mode
operator|==
name|GIMP_CLONE_ALIGN_NO
condition|)
block|{
name|clone
operator|->
name|orig_src_x
operator|=
name|clone
operator|->
name|src_x
expr_stmt|;
name|clone
operator|->
name|orig_src_y
operator|=
name|clone
operator|->
name|src_y
expr_stmt|;
name|clone
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|clone_type
operator|==
name|GIMP_PATTERN_CLONE
condition|)
if|if
condition|(
operator|!
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"No patterns available for this operation."
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
if|if
condition|(
name|clone
operator|->
name|set_source
condition|)
block|{
comment|/*  If the control key is down, move the src target and return */
name|clone
operator|->
name|src_x
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|x
expr_stmt|;
name|clone
operator|->
name|src_y
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|y
expr_stmt|;
name|clone
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
comment|/*  otherwise, update the target  */
name|gint
name|dest_x
decl_stmt|;
name|gint
name|dest_y
decl_stmt|;
name|dest_x
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|x
expr_stmt|;
name|dest_y
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|align_mode
operator|==
name|GIMP_CLONE_ALIGN_REGISTERED
condition|)
block|{
name|clone
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|clone
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|clone
operator|->
name|first_stroke
condition|)
block|{
name|clone
operator|->
name|offset_x
operator|=
name|clone
operator|->
name|src_x
operator|-
name|dest_x
expr_stmt|;
name|clone
operator|->
name|offset_y
operator|=
name|clone
operator|->
name|src_y
operator|-
name|dest_y
expr_stmt|;
name|clone
operator|->
name|first_stroke
operator|=
name|FALSE
expr_stmt|;
block|}
name|clone
operator|->
name|src_x
operator|=
name|dest_x
operator|+
name|clone
operator|->
name|offset_x
expr_stmt|;
name|clone
operator|->
name|src_y
operator|=
name|dest_y
operator|+
name|clone
operator|->
name|offset_y
expr_stmt|;
name|gimp_clone_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PAINT_STATE_FINISH
case|:
if|if
condition|(
name|options
operator|->
name|align_mode
operator|==
name|GIMP_CLONE_ALIGN_NO
operator|&&
operator|!
name|clone
operator|->
name|first_stroke
condition|)
block|{
name|clone
operator|->
name|src_x
operator|=
name|clone
operator|->
name|orig_src_x
expr_stmt|;
name|clone
operator|->
name|src_y
operator|=
name|clone
operator|->
name|orig_src_y
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options)
name|gimp_clone_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
block|{
name|GimpClone
modifier|*
name|clone
init|=
name|GIMP_CLONE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpCloneOptions
modifier|*
name|options
init|=
name|GIMP_CLONE_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GimpPressureOptions
modifier|*
name|pressure_options
init|=
name|paint_options
operator|->
name|pressure_options
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpImage
modifier|*
name|src_gimage
init|=
name|NULL
decl_stmt|;
name|GimpPickable
modifier|*
name|src_pickable
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|s
decl_stmt|;
name|guchar
modifier|*
name|d
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|gpointer
name|pr
init|=
name|NULL
decl_stmt|;
name|gint
name|y
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
name|TileManager
modifier|*
name|src_tiles
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|GimpPattern
modifier|*
name|pattern
init|=
name|NULL
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
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
name|opacity
operator|=
name|gimp_paint_options_get_fade
argument_list|(
name|paint_options
argument_list|,
name|gimage
argument_list|,
name|paint_core
operator|->
name|pixel_dist
argument_list|)
expr_stmt|;
if|if
condition|(
name|opacity
operator|==
literal|0.0
condition|)
return|return;
comment|/*  make local copies because we change them  */
name|offset_x
operator|=
name|clone
operator|->
name|offset_x
expr_stmt|;
name|offset_y
operator|=
name|clone
operator|->
name|offset_y
expr_stmt|;
comment|/*  Make sure we still have a source if we are doing image cloning */
if|if
condition|(
name|options
operator|->
name|clone_type
operator|==
name|GIMP_IMAGE_CLONE
condition|)
block|{
if|if
condition|(
operator|!
name|clone
operator|->
name|src_drawable
condition|)
return|return;
name|src_pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|clone
operator|->
name|src_drawable
argument_list|)
expr_stmt|;
name|src_gimage
operator|=
name|gimp_pickable_get_image
argument_list|(
name|src_pickable
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|sample_merged
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|src_pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|src_gimage
operator|->
name|projection
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|clone
operator|->
name|src_drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|offset_x
operator|+=
name|off_x
expr_stmt|;
name|offset_y
operator|+=
name|off_y
expr_stmt|;
block|}
block|}
name|area
operator|=
name|gimp_paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|area
condition|)
return|return;
switch|switch
condition|(
name|options
operator|->
name|clone_type
condition|)
block|{
case|case
name|GIMP_IMAGE_CLONE
case|:
comment|/*  Set the paint area to transparent  */
name|temp_buf_data_clear
argument_list|(
name|area
argument_list|)
expr_stmt|;
name|src_tiles
operator|=
name|gimp_pickable_get_tiles
argument_list|(
name|src_pickable
argument_list|)
expr_stmt|;
name|x1
operator|=
name|CLAMP
argument_list|(
name|area
operator|->
name|x
operator|+
name|offset_x
argument_list|,
literal|0
argument_list|,
name|tile_manager_width
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|area
operator|->
name|y
operator|+
name|offset_y
argument_list|,
literal|0
argument_list|,
name|tile_manager_height
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|area
operator|->
name|x
operator|+
name|offset_x
operator|+
name|area
operator|->
name|width
argument_list|,
literal|0
argument_list|,
name|tile_manager_width
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|area
operator|->
name|y
operator|+
name|offset_y
operator|+
name|area
operator|->
name|height
argument_list|,
literal|0
argument_list|,
name|tile_manager_height
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|x2
operator|-
name|x1
operator|)
operator|||
operator|!
operator|(
name|y2
operator|-
name|y1
operator|)
condition|)
return|return;
comment|/*  If the source gimage is different from the destination,        *  then we should copy straight from the destination image        *  to the canvas.        *  Otherwise, we need a call to get_orig_image to make sure        *  we get a copy of the unblemished (offset) image        */
if|if
condition|(
operator|(
name|options
operator|->
name|sample_merged
operator|&&
operator|(
name|src_gimage
operator|!=
name|gimage
operator|)
operator|)
operator|||
operator|(
operator|!
name|options
operator|->
name|sample_merged
operator|&&
operator|(
name|clone
operator|->
name|src_drawable
operator|!=
name|drawable
operator|)
operator|)
condition|)
block|{
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|src_tiles
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
block|}
else|else
block|{
name|TempBuf
modifier|*
name|orig
decl_stmt|;
comment|/*  get the original image  */
if|if
condition|(
name|options
operator|->
name|sample_merged
condition|)
name|orig
operator|=
name|gimp_paint_core_get_orig_proj
argument_list|(
name|paint_core
argument_list|,
name|src_pickable
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
name|orig
operator|=
name|gimp_paint_core_get_orig_image
argument_list|(
name|paint_core
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|src_pickable
argument_list|)
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
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|srcPR
argument_list|,
name|orig
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
argument_list|)
expr_stmt|;
block|}
name|offset_x
operator|=
name|x1
operator|-
operator|(
name|area
operator|->
name|x
operator|+
name|offset_x
operator|)
expr_stmt|;
name|offset_y
operator|=
name|y1
operator|-
operator|(
name|area
operator|->
name|y
operator|+
name|offset_y
operator|)
expr_stmt|;
comment|/*  configure the destination  */
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|destPR
argument_list|,
name|area
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|srcPR
operator|.
name|w
argument_list|,
name|srcPR
operator|.
name|h
argument_list|)
expr_stmt|;
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PATTERN_CLONE
case|:
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pattern
condition|)
return|return;
comment|/*  configure the destination  */
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|destPR
argument_list|,
name|area
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|)
expr_stmt|;
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|1
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
break|break;
block|}
for|for
control|(
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|s
operator|=
name|srcPR
operator|.
name|data
expr_stmt|;
name|d
operator|=
name|destPR
operator|.
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|destPR
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
switch|switch
condition|(
name|options
operator|->
name|clone_type
condition|)
block|{
case|case
name|GIMP_IMAGE_CLONE
case|:
name|gimp_clone_line_image
argument_list|(
name|gimage
argument_list|,
name|src_gimage
argument_list|,
name|drawable
argument_list|,
name|src_pickable
argument_list|,
name|s
argument_list|,
name|d
argument_list|,
name|srcPR
operator|.
name|bytes
argument_list|,
name|destPR
operator|.
name|bytes
argument_list|,
name|destPR
operator|.
name|w
argument_list|)
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|.
name|rowstride
expr_stmt|;
break|break;
case|case
name|GIMP_PATTERN_CLONE
case|:
name|gimp_clone_line_pattern
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|pattern
argument_list|,
name|d
argument_list|,
name|area
operator|->
name|x
operator|+
name|offset_x
argument_list|,
name|area
operator|->
name|y
operator|+
name|y
operator|+
name|offset_y
argument_list|,
name|destPR
operator|.
name|bytes
argument_list|,
name|destPR
operator|.
name|w
argument_list|)
expr_stmt|;
break|break;
block|}
name|d
operator|+=
name|destPR
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
if|if
condition|(
name|pressure_options
operator|->
name|opacity
condition|)
name|opacity
operator|*=
name|PRESSURE_SCALE
operator|*
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
name|gimp_brush_core_paste_canvas
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|MIN
argument_list|(
name|opacity
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_paint_options_get_brush_mode
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|GIMP_PAINT_CONSTANT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_line_image (GimpImage * dest,GimpImage * src,GimpDrawable * d_drawable,GimpPickable * s_pickable,guchar * s,guchar * d,gint src_bytes,gint dest_bytes,gint width)
name|gimp_clone_line_image
parameter_list|(
name|GimpImage
modifier|*
name|dest
parameter_list|,
name|GimpImage
modifier|*
name|src
parameter_list|,
name|GimpDrawable
modifier|*
name|d_drawable
parameter_list|,
name|GimpPickable
modifier|*
name|s_pickable
parameter_list|,
name|guchar
modifier|*
name|s
parameter_list|,
name|guchar
modifier|*
name|d
parameter_list|,
name|gint
name|src_bytes
parameter_list|,
name|gint
name|dest_bytes
parameter_list|,
name|gint
name|width
parameter_list|)
block|{
name|guchar
name|rgba
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|gint
name|alpha
decl_stmt|;
name|alpha
operator|=
name|dest_bytes
operator|-
literal|1
expr_stmt|;
while|while
condition|(
name|width
operator|--
condition|)
block|{
name|gimp_image_get_color
argument_list|(
name|src
argument_list|,
name|gimp_pickable_get_image_type
argument_list|(
name|s_pickable
argument_list|)
argument_list|,
name|s
argument_list|,
name|rgba
argument_list|)
expr_stmt|;
name|gimp_image_transform_color
argument_list|(
name|dest
argument_list|,
name|d_drawable
argument_list|,
name|d
argument_list|,
name|GIMP_RGB
argument_list|,
name|rgba
argument_list|)
expr_stmt|;
name|d
index|[
name|alpha
index|]
operator|=
name|rgba
index|[
name|ALPHA_PIX
index|]
expr_stmt|;
name|s
operator|+=
name|src_bytes
expr_stmt|;
name|d
operator|+=
name|dest_bytes
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_line_pattern (GimpImage * dest,GimpDrawable * drawable,GimpPattern * pattern,guchar * d,gint x,gint y,gint bytes,gint width)
name|gimp_clone_line_pattern
parameter_list|(
name|GimpImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|,
name|guchar
modifier|*
name|d
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|width
parameter_list|)
block|{
name|guchar
modifier|*
name|pat
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|GimpImageBaseType
name|color_type
decl_stmt|;
name|gint
name|alpha
decl_stmt|;
name|gint
name|pat_bytes
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|pat_bytes
operator|=
name|pattern
operator|->
name|mask
operator|->
name|bytes
expr_stmt|;
comment|/*  Make sure x, y are positive  */
while|while
condition|(
name|x
operator|<
literal|0
condition|)
name|x
operator|+=
name|pattern
operator|->
name|mask
operator|->
name|width
expr_stmt|;
while|while
condition|(
name|y
operator|<
literal|0
condition|)
name|y
operator|+=
name|pattern
operator|->
name|mask
operator|->
name|height
expr_stmt|;
comment|/*  Get a pointer to the appropriate scanline of the pattern buffer  */
name|pat
operator|=
name|temp_buf_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
operator|+
operator|(
name|y
operator|%
name|pattern
operator|->
name|mask
operator|->
name|height
operator|)
operator|*
name|pattern
operator|->
name|mask
operator|->
name|width
operator|*
name|pat_bytes
expr_stmt|;
name|color_type
operator|=
operator|(
name|pat_bytes
operator|==
literal|3
operator|||
name|pat_bytes
operator|==
literal|4
operator|)
condition|?
name|GIMP_RGB
else|:
name|GIMP_GRAY
expr_stmt|;
name|alpha
operator|=
name|bytes
operator|-
literal|1
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
condition|;
name|i
operator|++
control|)
block|{
name|p
operator|=
name|pat
operator|+
operator|(
operator|(
name|i
operator|+
name|x
operator|)
operator|%
name|pattern
operator|->
name|mask
operator|->
name|width
operator|)
operator|*
name|pat_bytes
expr_stmt|;
name|gimp_image_transform_color
argument_list|(
name|dest
argument_list|,
name|drawable
argument_list|,
name|d
argument_list|,
name|color_type
argument_list|,
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|pat_bytes
operator|==
literal|2
operator|||
name|pat_bytes
operator|==
literal|4
condition|)
name|d
index|[
name|alpha
index|]
operator|=
name|p
index|[
name|pat_bytes
operator|-
literal|1
index|]
expr_stmt|;
else|else
name|d
index|[
name|alpha
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|d
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_src_drawable_removed (GimpDrawable * drawable,GimpClone * clone)
name|gimp_clone_src_drawable_removed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpClone
modifier|*
name|clone
parameter_list|)
block|{
if|if
condition|(
name|drawable
operator|==
name|clone
operator|->
name|src_drawable
condition|)
block|{
name|clone
operator|->
name|src_drawable
operator|=
name|NULL
expr_stmt|;
block|}
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|drawable
argument_list|,
name|gimp_clone_src_drawable_removed
argument_list|,
name|clone
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_set_src_drawable (GimpClone * clone,GimpDrawable * drawable)
name|gimp_clone_set_src_drawable
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|clone
operator|->
name|src_drawable
operator|==
name|drawable
condition|)
return|return;
if|if
condition|(
name|clone
operator|->
name|src_drawable
condition|)
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|clone
operator|->
name|src_drawable
argument_list|,
name|gimp_clone_src_drawable_removed
argument_list|,
name|clone
argument_list|)
expr_stmt|;
name|clone
operator|->
name|src_drawable
operator|=
name|drawable
expr_stmt|;
if|if
condition|(
name|clone
operator|->
name|src_drawable
condition|)
name|g_signal_connect
argument_list|(
name|clone
operator|->
name|src_drawable
argument_list|,
literal|"removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_clone_src_drawable_removed
argument_list|)
argument_list|,
name|clone
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

