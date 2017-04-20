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
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"core/gimpsymmetry.h"
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
name|GeglNode
modifier|*
name|op
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|src_rect
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|GeglBuffer
modifier|*
name|paint_buffer
parameter_list|,
name|gint
name|paint_buffer_x
parameter_list|,
name|gint
name|paint_buffer_y
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
name|gboolean
name|gimp_clone_use_source
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpSourceOptions
modifier|*
name|options
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
name|use_source
operator|=
name|gimp_clone_use_source
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
name|GIMP_CLONE_PATTERN
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
DECL|function|gimp_clone_motion (GimpSourceCore * source_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GeglNode * op,gdouble opacity,GimpPickable * src_pickable,GeglBuffer * src_buffer,GeglRectangle * src_rect,gint src_offset_x,gint src_offset_y,GeglBuffer * paint_buffer,gint paint_buffer_x,gint paint_buffer_y,gint paint_area_offset_x,gint paint_area_offset_y,gint paint_area_width,gint paint_area_height)
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
name|GeglNode
modifier|*
name|op
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|src_rect
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|GeglBuffer
modifier|*
name|paint_buffer
parameter_list|,
name|gint
name|paint_buffer_x
parameter_list|,
name|gint
name|paint_buffer_y
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
name|GimpBrushCore
modifier|*
name|brush_core
init|=
name|GIMP_BRUSH_CORE
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
name|GimpDynamics
modifier|*
name|dynamics
init|=
name|brush_core
operator|->
name|dynamics
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
name|gdouble
name|fade_point
decl_stmt|;
name|gdouble
name|force
decl_stmt|;
if|if
condition|(
name|gimp_source_core_use_source
argument_list|(
name|source_core
argument_list|,
name|source_options
argument_list|)
condition|)
block|{
name|gegl_buffer_copy
argument_list|(
name|src_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|src_rect
operator|->
name|x
argument_list|,
name|src_rect
operator|->
name|y
argument_list|,
name|paint_area_width
argument_list|,
name|paint_area_height
argument_list|)
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|paint_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|paint_area_offset_x
argument_list|,
name|paint_area_offset_y
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|op
condition|)
block|{
name|GeglNode
modifier|*
name|graph
decl_stmt|,
modifier|*
name|source
decl_stmt|,
modifier|*
name|target
decl_stmt|;
name|graph
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|source
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|paint_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_add_child
argument_list|(
name|graph
argument_list|,
name|op
argument_list|)
expr_stmt|;
name|target
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:write-buffer"
argument_list|,
literal|"buffer"
argument_list|,
name|paint_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_link_many
argument_list|(
name|source
argument_list|,
name|op
argument_list|,
name|target
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|target
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|graph
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|clone_type
operator|==
name|GIMP_CLONE_PATTERN
condition|)
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
name|GeglBuffer
modifier|*
name|src_buffer
init|=
name|gimp_pattern_create_buffer
argument_list|(
name|pattern
argument_list|)
decl_stmt|;
name|src_offset_x
operator|+=
name|gegl_buffer_get_width
argument_list|(
name|src_buffer
argument_list|)
operator|/
literal|2
expr_stmt|;
name|src_offset_y
operator|+=
name|gegl_buffer_get_height
argument_list|(
name|src_buffer
argument_list|)
operator|/
literal|2
expr_stmt|;
name|gegl_buffer_set_pattern
argument_list|(
name|paint_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|paint_area_offset_x
argument_list|,
name|paint_area_offset_y
argument_list|,
name|paint_area_width
argument_list|,
name|paint_area_height
argument_list|)
argument_list|,
name|src_buffer
argument_list|,
operator|-
name|paint_buffer_x
operator|-
name|src_offset_x
argument_list|,
operator|-
name|paint_buffer_y
operator|-
name|src_offset_y
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
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
if|if
condition|(
name|gimp_dynamics_is_output_enabled
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FORCE
argument_list|)
condition|)
name|force
operator|=
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FORCE
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
expr_stmt|;
else|else
name|force
operator|=
name|paint_options
operator|->
name|brush_force
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
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_clone_use_source (GimpSourceCore * source_core,GimpSourceOptions * options)
name|gimp_clone_use_source
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpSourceOptions
modifier|*
name|options
parameter_list|)
block|{
return|return
name|GIMP_CLONE_OPTIONS
argument_list|(
name|options
argument_list|)
operator|->
name|clone_type
operator|==
name|GIMP_CLONE_IMAGE
return|;
block|}
end_function

end_unit

