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
file|<gegl.h>
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
file|"gegl/gimp-gegl-utils.h"
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
file|"core/gimpdynamics.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdynamicsoutput.h"
end_include

begin_include
include|#
directive|include
file|"core/gimperror.h"
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
specifier|const
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
specifier|const
name|GimpCoords
modifier|*
name|coords
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
name|gimp_clone_line_pattern
parameter_list|(
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
specifier|const
name|Babl
modifier|*
name|fish
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
DECL|function|gimp_clone_start (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GError ** error)
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
specifier|const
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
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
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
DECL|function|gimp_clone_motion (GimpSourceCore * source_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,gdouble opacity,GimpPickable * src_pickable,PixelRegion * srcPR,gint src_offset_x,gint src_offset_y,TempBuf * paint_area,gint paint_area_offset_x,gint paint_area_offset_y,gint paint_area_width,gint paint_area_height)
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
specifier|const
name|GimpCoords
modifier|*
name|coords
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
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|GimpDynamicsOutput
modifier|*
name|force_output
decl_stmt|;
name|gdouble
name|fade_point
decl_stmt|;
name|gdouble
name|force
decl_stmt|;
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
block|{
specifier|const
name|Babl
modifier|*
name|fish
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|fish
operator|=
name|babl_fish
argument_list|(
name|gimp_pickable_get_babl_format_with_alpha
argument_list|(
name|src_pickable
argument_list|)
argument_list|,
name|gimp_drawable_get_babl_format_with_alpha
argument_list|(
name|drawable
argument_list|)
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
name|gint
name|y
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
name|babl_process
argument_list|(
name|fish
argument_list|,
name|s
argument_list|,
name|d
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
name|d
operator|+=
name|destPR
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
block|}
break|break;
case|case
name|GIMP_PATTERN_CLONE
case|:
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|fish
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|fish
operator|=
name|babl_fish
argument_list|(
name|gimp_bpp_to_babl_format
argument_list|(
name|pattern
operator|->
name|mask
operator|->
name|bytes
argument_list|,
name|TRUE
argument_list|)
argument_list|,
name|gimp_drawable_get_babl_format_with_alpha
argument_list|(
name|drawable
argument_list|)
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
name|d
init|=
name|destPR
operator|.
name|data
decl_stmt|;
name|gint
name|y
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
name|gimp_clone_line_pattern
argument_list|(
name|image
argument_list|,
name|fish
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
name|d
operator|+=
name|destPR
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
block|}
break|break;
block|}
name|force_output
operator|=
name|gimp_dynamics_get_output
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
operator|->
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FORCE
argument_list|)
expr_stmt|;
name|fade_point
operator|=
name|gimp_paint_options_get_fade
argument_list|(
name|paint_options
argument_list|,
name|image
argument_list|,
name|paint_core
operator|->
name|pixel_dist
argument_list|)
expr_stmt|;
name|force
operator|=
name|gimp_dynamics_output_get_linear_value
argument_list|(
name|force_output
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
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
name|coords
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
name|force
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
DECL|function|gimp_clone_line_pattern (GimpImage * dest_image,const Babl * fish,GimpPattern * pattern,guchar * d,gint x,gint y,gint dest_bytes,gint width)
name|gimp_clone_line_pattern
parameter_list|(
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
specifier|const
name|Babl
modifier|*
name|fish
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
name|gint
name|pat_bytes
init|=
name|pattern
operator|->
name|mask
operator|->
name|bytes
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
name|temp_buf_get_data
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
name|babl_process
argument_list|(
name|fish
argument_list|,
name|p
argument_list|,
name|d
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|d
operator|+=
name|dest_bytes
expr_stmt|;
block|}
block|}
end_function

end_unit

