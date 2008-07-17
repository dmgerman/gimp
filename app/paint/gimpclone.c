begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
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
name|gboolean
name|gimp_clone_start
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
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_motion
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|TempBuf
modifier|*
name|paint_area
parameter_list|,
name|gint
name|paint_area_offset_x
parameter_list|,
name|gint
name|paint_area_offset_y
parameter_list|,
name|gint
name|paint_area_width
parameter_list|,
name|gint
name|paint_area_height
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
name|dest_image
parameter_list|,
name|GimpImageType
name|dest_type
parameter_list|,
name|GimpImage
modifier|*
name|src_image
parameter_list|,
name|GimpImageType
name|src_type
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
name|dest_image
parameter_list|,
name|GimpImageType
name|dest_type
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
name|dest_bytes
parameter_list|,
name|gint
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpClone,gimp_clone,GIMP_TYPE_SOURCE_CORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpClone
argument_list|,
argument|gimp_clone
argument_list|,
argument|GIMP_TYPE_SOURCE_CORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_clone_parent_class
end_define

begin_function
name|void
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
literal|"gimp-clone"
argument_list|,
name|_
argument_list|(
literal|"Clone"
argument_list|)
argument_list|,
literal|"gimp-tool-clone"
argument_list|)
expr_stmt|;
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
name|GimpSourceCoreClass
modifier|*
name|source_core_class
init|=
name|GIMP_SOURCE_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|paint_core_class
operator|->
name|start
operator|=
name|gimp_clone_start
expr_stmt|;
name|source_core_class
operator|->
name|motion
operator|=
name|gimp_clone_motion
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
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_clone_start (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpCoords * coords,GError ** error)
name|gimp_clone_start
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
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpCloneOptions
modifier|*
name|options
init|=
name|GIMP_CLONE_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|start
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|,
name|error
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|options
operator|->
name|clone_type
operator|==
name|GIMP_PATTERN_CLONE
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_context_get_pattern
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"No patterns available for use with this tool."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_motion (GimpSourceCore * source_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,gdouble opacity,GimpPickable * src_pickable,PixelRegion * srcPR,gint src_offset_x,gint src_offset_y,TempBuf * paint_area,gint paint_area_offset_x,gint paint_area_offset_y,gint paint_area_width,gint paint_area_height)
name|gimp_clone_motion
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|TempBuf
modifier|*
name|paint_area
parameter_list|,
name|gint
name|paint_area_offset_x
parameter_list|,
name|gint
name|paint_area_offset_y
parameter_list|,
name|gint
name|paint_area_width
parameter_list|,
name|gint
name|paint_area_height
parameter_list|)
block|{
name|GimpPaintCore
modifier|*
name|paint_core
init|=
name|GIMP_PAINT_CORE
argument_list|(
name|source_core
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
name|GimpSourceOptions
modifier|*
name|source_options
init|=
name|GIMP_SOURCE_OPTIONS
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
name|GimpImage
modifier|*
name|src_image
init|=
name|NULL
decl_stmt|;
name|GimpImageType
name|src_type
init|=
literal|0
decl_stmt|;
name|GimpImageType
name|dest_type
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gpointer
name|pr
init|=
name|NULL
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|GimpPattern
modifier|*
name|pattern
init|=
name|NULL
decl_stmt|;
name|gdouble
name|hardness
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
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
name|src_image
operator|=
name|gimp_pickable_get_image
argument_list|(
name|src_pickable
argument_list|)
expr_stmt|;
name|src_type
operator|=
name|gimp_pickable_get_image_type
argument_list|(
name|src_pickable
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_pickable_get_bytes
argument_list|(
name|src_pickable
argument_list|)
operator|<
name|srcPR
operator|->
name|bytes
condition|)
name|src_type
operator|=
name|GIMP_IMAGE_TYPE_WITH_ALPHA
argument_list|(
name|src_type
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|destPR
argument_list|,
name|paint_area
argument_list|,
name|paint_area_offset_x
argument_list|,
name|paint_area_offset_y
argument_list|,
name|paint_area_width
argument_list|,
name|paint_area_height
argument_list|)
expr_stmt|;
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|2
argument_list|,
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
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|destPR
argument_list|,
name|paint_area
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|paint_area
operator|->
name|width
argument_list|,
name|paint_area
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
name|dest_type
operator|=
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
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
name|guchar
modifier|*
name|s
init|=
name|srcPR
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|destPR
operator|.
name|data
decl_stmt|;
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
name|image
argument_list|,
name|dest_type
argument_list|,
name|src_image
argument_list|,
name|src_type
argument_list|,
name|s
argument_list|,
name|d
argument_list|,
name|srcPR
operator|->
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
operator|->
name|rowstride
expr_stmt|;
break|break;
case|case
name|GIMP_PATTERN_CLONE
case|:
name|gimp_clone_line_pattern
argument_list|(
name|image
argument_list|,
name|dest_type
argument_list|,
name|pattern
argument_list|,
name|d
argument_list|,
name|paint_area
operator|->
name|x
operator|+
name|src_offset_x
argument_list|,
name|paint_area
operator|->
name|y
operator|+
name|y
operator|+
name|src_offset_y
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
name|opacity
operator|*=
name|gimp_paint_options_get_dynamic_opacity
argument_list|(
name|paint_options
argument_list|,
operator|&
name|paint_core
operator|->
name|cur_coords
argument_list|)
expr_stmt|;
name|hardness
operator|=
name|gimp_paint_options_get_dynamic_hardness
argument_list|(
name|paint_options
argument_list|,
operator|&
name|paint_core
operator|->
name|cur_coords
argument_list|)
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
name|hardness
argument_list|,
comment|/* In fixed mode, paint incremental so the                                  * individual brushes are properly applied                                  * on top of each other.                                  * Otherwise the stuff we paint is seamless                                  * and we don't need intermediate masking.                                  */
name|source_options
operator|->
name|align_mode
operator|==
name|GIMP_SOURCE_ALIGN_FIXED
condition|?
name|GIMP_PAINT_INCREMENTAL
else|:
name|GIMP_PAINT_CONSTANT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_line_image (GimpImage * dest_image,GimpImageType dest_type,GimpImage * src_image,GimpImageType src_type,guchar * s,guchar * d,gint src_bytes,gint dest_bytes,gint width)
name|gimp_clone_line_image
parameter_list|(
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|GimpImageType
name|dest_type
parameter_list|,
name|GimpImage
modifier|*
name|src_image
parameter_list|,
name|GimpImageType
name|src_type
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
name|src_image
argument_list|,
name|src_type
argument_list|,
name|s
argument_list|,
name|rgba
argument_list|)
expr_stmt|;
name|gimp_image_transform_color
argument_list|(
name|dest_image
argument_list|,
name|dest_type
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
DECL|function|gimp_clone_line_pattern (GimpImage * dest_image,GimpImageType dest_type,GimpPattern * pattern,guchar * d,gint x,gint y,gint dest_bytes,gint width)
name|gimp_clone_line_pattern
parameter_list|(
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|GimpImageType
name|dest_type
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
name|dest_bytes
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
name|dest_bytes
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
name|dest_image
argument_list|,
name|dest_type
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
name|dest_bytes
expr_stmt|;
block|}
block|}
end_function

end_unit

