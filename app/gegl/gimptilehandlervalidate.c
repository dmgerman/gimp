begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptilehandlervalidate.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28be8f6b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_FORMAT
name|PROP_FORMAT
block|,
DECL|enumerator|PROP_TILE_WIDTH
name|PROP_TILE_WIDTH
block|,
DECL|enumerator|PROP_TILE_HEIGHT
name|PROP_TILE_HEIGHT
block|,
DECL|enumerator|PROP_WHOLE_TILE
name|PROP_WHOLE_TILE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_tile_handler_validate_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_handler_validate_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_handler_validate_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_handler_validate_real_begin_validate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_handler_validate_real_end_validate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_handler_validate_real_validate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gpointer
name|dest_buf
parameter_list|,
name|gint
name|dest_stride
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_handler_validate_real_validate_buffer
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|gimp_tile_handler_validate_command
parameter_list|(
name|GeglTileSource
modifier|*
name|source
parameter_list|,
name|GeglTileCommand
name|command
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|z
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTileHandlerValidate,gimp_tile_handler_validate,GEGL_TYPE_TILE_HANDLER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTileHandlerValidate
argument_list|,
argument|gimp_tile_handler_validate
argument_list|,
argument|GEGL_TYPE_TILE_HANDLER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tile_handler_validate_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tile_handler_validate_class_init
parameter_list|(
name|GimpTileHandlerValidateClass
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tile_handler_validate_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_tile_handler_validate_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_tile_handler_validate_get_property
expr_stmt|;
name|klass
operator|->
name|begin_validate
operator|=
name|gimp_tile_handler_validate_real_begin_validate
expr_stmt|;
name|klass
operator|->
name|end_validate
operator|=
name|gimp_tile_handler_validate_real_end_validate
expr_stmt|;
name|klass
operator|->
name|validate
operator|=
name|gimp_tile_handler_validate_real_validate
expr_stmt|;
name|klass
operator|->
name|validate_buffer
operator|=
name|gimp_tile_handler_validate_real_validate_buffer
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_FORMAT
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"format"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TILE_WIDTH
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"tile-width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|G_MAXINT
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TILE_HEIGHT
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"tile-height"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|G_MAXINT
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_WHOLE_TILE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"whole-tile"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_handler_validate_init (GimpTileHandlerValidate * validate)
name|gimp_tile_handler_validate_init
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|)
block|{
name|GeglTileSource
modifier|*
name|source
init|=
name|GEGL_TILE_SOURCE
argument_list|(
name|validate
argument_list|)
decl_stmt|;
name|source
operator|->
name|command
operator|=
name|gimp_tile_handler_validate_command
expr_stmt|;
name|validate
operator|->
name|dirty_region
operator|=
name|cairo_region_create
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_handler_validate_finalize (GObject * object)
name|gimp_tile_handler_validate_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTileHandlerValidate
modifier|*
name|validate
init|=
name|GIMP_TILE_HANDLER_VALIDATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|validate
operator|->
name|graph
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|validate
operator|->
name|dirty_region
argument_list|,
name|cairo_region_destroy
argument_list|)
expr_stmt|;
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
name|void
DECL|function|gimp_tile_handler_validate_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_tile_handler_validate_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpTileHandlerValidate
modifier|*
name|validate
init|=
name|GIMP_TILE_HANDLER_VALIDATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_FORMAT
case|:
name|validate
operator|->
name|format
operator|=
name|g_value_get_pointer
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILE_WIDTH
case|:
name|validate
operator|->
name|tile_width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILE_HEIGHT
case|:
name|validate
operator|->
name|tile_height
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WHOLE_TILE
case|:
name|validate
operator|->
name|whole_tile
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_handler_validate_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_tile_handler_validate_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpTileHandlerValidate
modifier|*
name|validate
init|=
name|GIMP_TILE_HANDLER_VALIDATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_FORMAT
case|:
name|g_value_set_pointer
argument_list|(
name|value
argument_list|,
operator|(
name|gpointer
operator|)
name|validate
operator|->
name|format
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILE_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|validate
operator|->
name|tile_width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILE_HEIGHT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|validate
operator|->
name|tile_height
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WHOLE_TILE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|validate
operator|->
name|whole_tile
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_handler_validate_real_begin_validate (GimpTileHandlerValidate * validate)
name|gimp_tile_handler_validate_real_begin_validate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|)
block|{
name|validate
operator|->
name|suspend_validate
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_handler_validate_real_end_validate (GimpTileHandlerValidate * validate)
name|gimp_tile_handler_validate_real_end_validate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|)
block|{
name|validate
operator|->
name|suspend_validate
operator|--
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_handler_validate_real_validate (GimpTileHandlerValidate * validate,const GeglRectangle * rect,const Babl * format,gpointer dest_buf,gint dest_stride)
name|gimp_tile_handler_validate_real_validate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gpointer
name|dest_buf
parameter_list|,
name|gint
name|dest_stride
parameter_list|)
block|{
if|#
directive|if
literal|0
block|g_printerr ("validating at %d %d %d %d\n",               rect.x,               rect.y,               rect.width,               rect.height);
endif|#
directive|endif
name|gegl_node_blit
argument_list|(
name|validate
operator|->
name|graph
argument_list|,
literal|1.0
argument_list|,
name|rect
argument_list|,
name|format
argument_list|,
name|dest_buf
argument_list|,
name|dest_stride
argument_list|,
name|GEGL_BLIT_DEFAULT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_handler_validate_real_validate_buffer (GimpTileHandlerValidate * validate,const GeglRectangle * rect,GeglBuffer * buffer)
name|gimp_tile_handler_validate_real_validate_buffer
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|GimpTileHandlerValidateClass
modifier|*
name|klass
decl_stmt|;
name|klass
operator|=
name|GIMP_TILE_HANDLER_VALIDATE_GET_CLASS
argument_list|(
name|validate
argument_list|)
expr_stmt|;
if|if
condition|(
name|klass
operator|->
name|validate
operator|==
name|gimp_tile_handler_validate_real_validate
condition|)
block|{
name|gegl_node_blit_buffer
argument_list|(
name|validate
operator|->
name|graph
argument_list|,
name|buffer
argument_list|,
name|rect
argument_list|,
literal|0
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|Babl
modifier|*
name|format
init|=
name|gegl_buffer_get_format
argument_list|(
name|buffer
argument_list|)
decl_stmt|;
name|gpointer
name|data
decl_stmt|;
name|gint
name|stride
decl_stmt|;
name|data
operator|=
name|gegl_buffer_linear_open
argument_list|(
name|buffer
argument_list|,
name|rect
argument_list|,
operator|&
name|stride
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|klass
operator|->
name|validate
argument_list|(
name|validate
argument_list|,
name|rect
argument_list|,
name|format
argument_list|,
name|data
argument_list|,
name|stride
argument_list|)
expr_stmt|;
name|gegl_buffer_linear_close
argument_list|(
name|buffer
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GeglTile
modifier|*
DECL|function|gimp_tile_handler_validate_validate (GeglTileSource * source,GeglTile * tile,gint x,gint y)
name|gimp_tile_handler_validate_validate
parameter_list|(
name|GeglTileSource
modifier|*
name|source
parameter_list|,
name|GeglTile
modifier|*
name|tile
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GimpTileHandlerValidate
modifier|*
name|validate
init|=
name|GIMP_TILE_HANDLER_VALIDATE
argument_list|(
name|source
argument_list|)
decl_stmt|;
name|cairo_rectangle_int_t
name|tile_rect
decl_stmt|;
if|if
condition|(
name|validate
operator|->
name|suspend_validate
operator|||
name|cairo_region_is_empty
argument_list|(
name|validate
operator|->
name|dirty_region
argument_list|)
condition|)
block|{
return|return
name|tile
return|;
block|}
name|tile_rect
operator|.
name|x
operator|=
name|x
operator|*
name|validate
operator|->
name|tile_width
expr_stmt|;
name|tile_rect
operator|.
name|y
operator|=
name|y
operator|*
name|validate
operator|->
name|tile_height
expr_stmt|;
name|tile_rect
operator|.
name|width
operator|=
name|validate
operator|->
name|tile_width
expr_stmt|;
name|tile_rect
operator|.
name|height
operator|=
name|validate
operator|->
name|tile_height
expr_stmt|;
if|if
condition|(
name|validate
operator|->
name|whole_tile
condition|)
block|{
if|if
condition|(
name|cairo_region_contains_rectangle
argument_list|(
name|validate
operator|->
name|dirty_region
argument_list|,
operator|&
name|tile_rect
argument_list|)
operator|!=
name|CAIRO_REGION_OVERLAP_OUT
condition|)
block|{
name|gint
name|tile_bpp
decl_stmt|;
name|gint
name|tile_stride
decl_stmt|;
if|if
condition|(
operator|!
name|tile
condition|)
name|tile
operator|=
name|gegl_tile_handler_create_tile
argument_list|(
name|GEGL_TILE_HANDLER
argument_list|(
name|source
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_region_subtract_rectangle
argument_list|(
name|validate
operator|->
name|dirty_region
argument_list|,
operator|&
name|tile_rect
argument_list|)
expr_stmt|;
name|tile_bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|validate
operator|->
name|format
argument_list|)
expr_stmt|;
name|tile_stride
operator|=
name|tile_bpp
operator|*
name|validate
operator|->
name|tile_width
expr_stmt|;
name|gimp_tile_handler_validate_begin_validate
argument_list|(
name|validate
argument_list|)
expr_stmt|;
name|gegl_tile_lock
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|GIMP_TILE_HANDLER_VALIDATE_GET_CLASS
argument_list|(
name|validate
argument_list|)
operator|->
name|validate
argument_list|(
name|validate
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|tile_rect
operator|.
name|x
argument_list|,
name|tile_rect
operator|.
name|y
argument_list|,
name|tile_rect
operator|.
name|width
argument_list|,
name|tile_rect
operator|.
name|height
argument_list|)
argument_list|,
name|validate
operator|->
name|format
argument_list|,
name|gegl_tile_get_data
argument_list|(
name|tile
argument_list|)
argument_list|,
name|tile_stride
argument_list|)
expr_stmt|;
name|gegl_tile_unlock
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|gimp_tile_handler_validate_end_validate
argument_list|(
name|validate
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|cairo_region_t
modifier|*
name|tile_region
init|=
name|cairo_region_copy
argument_list|(
name|validate
operator|->
name|dirty_region
argument_list|)
decl_stmt|;
name|cairo_region_intersect_rectangle
argument_list|(
name|tile_region
argument_list|,
operator|&
name|tile_rect
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|cairo_region_is_empty
argument_list|(
name|tile_region
argument_list|)
condition|)
block|{
name|gint
name|tile_bpp
decl_stmt|;
name|gint
name|tile_stride
decl_stmt|;
name|gint
name|n_rects
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|cairo_region_subtract_rectangle
argument_list|(
name|validate
operator|->
name|dirty_region
argument_list|,
operator|&
name|tile_rect
argument_list|)
expr_stmt|;
name|tile_bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|validate
operator|->
name|format
argument_list|)
expr_stmt|;
name|tile_stride
operator|=
name|tile_bpp
operator|*
name|validate
operator|->
name|tile_width
expr_stmt|;
if|if
condition|(
operator|!
name|tile
condition|)
block|{
name|tile
operator|=
name|gegl_tile_handler_create_tile
argument_list|(
name|GEGL_TILE_HANDLER
argument_list|(
name|source
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|gegl_tile_get_data
argument_list|(
name|tile
argument_list|)
argument_list|,
literal|0
argument_list|,
name|tile_stride
operator|*
name|validate
operator|->
name|tile_height
argument_list|)
expr_stmt|;
block|}
name|gimp_tile_handler_validate_begin_validate
argument_list|(
name|validate
argument_list|)
expr_stmt|;
name|gegl_tile_lock
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|n_rects
operator|=
name|cairo_region_num_rectangles
argument_list|(
name|tile_region
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|g_printerr ("%d chunks\n", n_rects);
endif|#
directive|endif
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_rects
condition|;
name|i
operator|++
control|)
block|{
name|cairo_rectangle_int_t
name|blit_rect
decl_stmt|;
name|cairo_region_get_rectangle
argument_list|(
name|tile_region
argument_list|,
name|i
argument_list|,
operator|&
name|blit_rect
argument_list|)
expr_stmt|;
name|GIMP_TILE_HANDLER_VALIDATE_GET_CLASS
argument_list|(
name|validate
argument_list|)
operator|->
name|validate
argument_list|(
name|validate
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|blit_rect
operator|.
name|x
argument_list|,
name|blit_rect
operator|.
name|y
argument_list|,
name|blit_rect
operator|.
name|width
argument_list|,
name|blit_rect
operator|.
name|height
argument_list|)
argument_list|,
name|validate
operator|->
name|format
argument_list|,
name|gegl_tile_get_data
argument_list|(
name|tile
argument_list|)
operator|+
operator|(
name|blit_rect
operator|.
name|y
operator|%
name|validate
operator|->
name|tile_height
operator|)
operator|*
name|tile_stride
operator|+
operator|(
name|blit_rect
operator|.
name|x
operator|%
name|validate
operator|->
name|tile_width
operator|)
operator|*
name|tile_bpp
argument_list|,
name|tile_stride
argument_list|)
expr_stmt|;
block|}
name|gegl_tile_unlock
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|gimp_tile_handler_validate_end_validate
argument_list|(
name|validate
argument_list|)
expr_stmt|;
block|}
name|cairo_region_destroy
argument_list|(
name|tile_region
argument_list|)
expr_stmt|;
block|}
return|return
name|tile
return|;
block|}
end_function

begin_function
specifier|static
name|gpointer
DECL|function|gimp_tile_handler_validate_command (GeglTileSource * source,GeglTileCommand command,gint x,gint y,gint z,gpointer data)
name|gimp_tile_handler_validate_command
parameter_list|(
name|GeglTileSource
modifier|*
name|source
parameter_list|,
name|GeglTileCommand
name|command
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|z
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gpointer
name|retval
decl_stmt|;
name|retval
operator|=
name|gegl_tile_handler_source_command
argument_list|(
name|source
argument_list|,
name|command
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|z
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|command
operator|==
name|GEGL_TILE_GET
operator|&&
name|z
operator|==
literal|0
condition|)
name|retval
operator|=
name|gimp_tile_handler_validate_validate
argument_list|(
name|source
argument_list|,
name|retval
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GeglTileHandler
modifier|*
DECL|function|gimp_tile_handler_validate_new (GeglNode * graph)
name|gimp_tile_handler_validate_new
parameter_list|(
name|GeglNode
modifier|*
name|graph
parameter_list|)
block|{
name|GimpTileHandlerValidate
modifier|*
name|validate
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_NODE
argument_list|(
name|graph
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|validate
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TILE_HANDLER_VALIDATE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|validate
operator|->
name|graph
operator|=
name|g_object_ref
argument_list|(
name|graph
argument_list|)
expr_stmt|;
return|return
name|GEGL_TILE_HANDLER
argument_list|(
name|validate
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_handler_validate_assign (GimpTileHandlerValidate * validate,GeglBuffer * buffer)
name|gimp_tile_handler_validate_assign
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TILE_HANDLER_VALIDATE
argument_list|(
name|validate
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_tile_handler_validate_get_assigned
argument_list|(
name|buffer
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|gegl_buffer_add_handler
argument_list|(
name|buffer
argument_list|,
name|validate
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|buffer
argument_list|,
literal|"format"
argument_list|,
operator|&
name|validate
operator|->
name|format
argument_list|,
literal|"tile-width"
argument_list|,
operator|&
name|validate
operator|->
name|tile_width
argument_list|,
literal|"tile-height"
argument_list|,
operator|&
name|validate
operator|->
name|tile_height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"gimp-tile-handler-validate"
argument_list|,
name|validate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_handler_validate_unassign (GimpTileHandlerValidate * validate,GeglBuffer * buffer)
name|gimp_tile_handler_validate_unassign
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TILE_HANDLER_VALIDATE
argument_list|(
name|validate
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_tile_handler_validate_get_assigned
argument_list|(
name|buffer
argument_list|)
operator|==
name|validate
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"gimp-tile-handler-validate"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_buffer_remove_handler
argument_list|(
name|buffer
argument_list|,
name|validate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpTileHandlerValidate
modifier|*
DECL|function|gimp_tile_handler_validate_get_assigned (GeglBuffer * buffer)
name|gimp_tile_handler_validate_get_assigned
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"gimp-tile-handler-validate"
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_handler_validate_invalidate (GimpTileHandlerValidate * validate,const GeglRectangle * rect)
name|gimp_tile_handler_validate_invalidate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TILE_HANDLER_VALIDATE
argument_list|(
name|validate
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cairo_region_union_rectangle
argument_list|(
name|validate
operator|->
name|dirty_region
argument_list|,
operator|(
name|cairo_rectangle_int_t
operator|*
operator|)
name|rect
argument_list|)
expr_stmt|;
name|gegl_tile_handler_damage_rect
argument_list|(
name|GEGL_TILE_HANDLER
argument_list|(
name|validate
argument_list|)
argument_list|,
name|rect
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_handler_validate_undo_invalidate (GimpTileHandlerValidate * validate,const GeglRectangle * rect)
name|gimp_tile_handler_validate_undo_invalidate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TILE_HANDLER_VALIDATE
argument_list|(
name|validate
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cairo_region_subtract_rectangle
argument_list|(
name|validate
operator|->
name|dirty_region
argument_list|,
operator|(
name|cairo_rectangle_int_t
operator|*
operator|)
name|rect
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_handler_validate_begin_validate (GimpTileHandlerValidate * validate)
name|gimp_tile_handler_validate_begin_validate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TILE_HANDLER_VALIDATE
argument_list|(
name|validate
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|validate
operator|->
name|validating
operator|++
operator|==
literal|0
condition|)
name|GIMP_TILE_HANDLER_VALIDATE_GET_CLASS
argument_list|(
name|validate
argument_list|)
operator|->
name|begin_validate
argument_list|(
name|validate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_handler_validate_end_validate (GimpTileHandlerValidate * validate)
name|gimp_tile_handler_validate_end_validate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TILE_HANDLER_VALIDATE
argument_list|(
name|validate
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|validate
operator|->
name|validating
operator|>
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|--
name|validate
operator|->
name|validating
operator|==
literal|0
condition|)
name|GIMP_TILE_HANDLER_VALIDATE_GET_CLASS
argument_list|(
name|validate
argument_list|)
operator|->
name|end_validate
argument_list|(
name|validate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_handler_validate_buffer_copy (GeglBuffer * src_buffer,const GeglRectangle * src_rect,GeglBuffer * dst_buffer,const GeglRectangle * dst_rect)
name|gimp_tile_handler_validate_buffer_copy
parameter_list|(
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|src_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|dst_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dst_rect
parameter_list|)
block|{
name|GimpTileHandlerValidate
modifier|*
name|src_validate
decl_stmt|;
name|GimpTileHandlerValidate
modifier|*
name|dst_validate
decl_stmt|;
name|GeglRectangle
name|real_src_rect
decl_stmt|;
name|GeglRectangle
name|real_dst_rect
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|src_buffer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|dst_buffer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|src_rect
operator|!=
name|dst_rect
argument_list|)
expr_stmt|;
name|src_validate
operator|=
name|gimp_tile_handler_validate_get_assigned
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
name|dst_validate
operator|=
name|gimp_tile_handler_validate_get_assigned
argument_list|(
name|dst_buffer
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dst_validate
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|src_rect
condition|)
name|src_rect
operator|=
name|gegl_buffer_get_extent
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dst_rect
condition|)
name|dst_rect
operator|=
name|src_rect
expr_stmt|;
name|real_src_rect
operator|=
operator|*
name|src_rect
expr_stmt|;
name|gegl_rectangle_intersect
argument_list|(
operator|&
name|real_dst_rect
argument_list|,
name|dst_rect
argument_list|,
name|gegl_buffer_get_extent
argument_list|(
name|dst_buffer
argument_list|)
argument_list|)
expr_stmt|;
name|real_src_rect
operator|.
name|x
operator|+=
name|real_dst_rect
operator|.
name|x
operator|-
name|dst_rect
operator|->
name|x
expr_stmt|;
name|real_src_rect
operator|.
name|y
operator|+=
name|real_dst_rect
operator|.
name|y
operator|-
name|dst_rect
operator|->
name|y
expr_stmt|;
name|real_src_rect
operator|.
name|width
operator|-=
name|real_dst_rect
operator|.
name|x
operator|-
name|dst_rect
operator|->
name|x
expr_stmt|;
name|real_src_rect
operator|.
name|height
operator|-=
name|real_dst_rect
operator|.
name|y
operator|-
name|dst_rect
operator|->
name|y
expr_stmt|;
name|real_src_rect
operator|.
name|width
operator|=
name|CLAMP
argument_list|(
name|real_src_rect
operator|.
name|width
argument_list|,
literal|0
argument_list|,
name|real_dst_rect
operator|.
name|width
argument_list|)
expr_stmt|;
name|real_src_rect
operator|.
name|height
operator|=
name|CLAMP
argument_list|(
name|real_src_rect
operator|.
name|height
argument_list|,
literal|0
argument_list|,
name|real_dst_rect
operator|.
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_validate
condition|)
name|src_validate
operator|->
name|suspend_validate
operator|++
expr_stmt|;
name|dst_validate
operator|->
name|suspend_validate
operator|++
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|src_buffer
argument_list|,
operator|&
name|real_src_rect
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|dst_buffer
argument_list|,
operator|&
name|real_dst_rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_validate
condition|)
name|src_validate
operator|->
name|suspend_validate
operator|--
expr_stmt|;
name|dst_validate
operator|->
name|suspend_validate
operator|--
expr_stmt|;
name|cairo_region_subtract_rectangle
argument_list|(
name|dst_validate
operator|->
name|dirty_region
argument_list|,
operator|(
name|cairo_rectangle_int_t
operator|*
operator|)
operator|&
name|real_dst_rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_validate
condition|)
block|{
if|if
condition|(
name|real_src_rect
operator|.
name|x
operator|==
name|real_dst_rect
operator|.
name|x
operator|&&
name|real_src_rect
operator|.
name|y
operator|==
name|real_dst_rect
operator|.
name|y
operator|&&
name|gegl_rectangle_equal
argument_list|(
operator|&
name|real_src_rect
argument_list|,
name|gegl_buffer_get_extent
argument_list|(
name|src_buffer
argument_list|)
argument_list|)
condition|)
block|{
name|cairo_region_union
argument_list|(
name|dst_validate
operator|->
name|dirty_region
argument_list|,
name|src_validate
operator|->
name|dirty_region
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|cairo_region_contains_rectangle
argument_list|(
name|src_validate
operator|->
name|dirty_region
argument_list|,
operator|(
name|cairo_rectangle_int_t
operator|*
operator|)
operator|&
name|real_src_rect
argument_list|)
operator|!=
name|CAIRO_REGION_OVERLAP_OUT
condition|)
block|{
name|cairo_region_t
modifier|*
name|region
decl_stmt|;
name|region
operator|=
name|cairo_region_copy
argument_list|(
name|src_validate
operator|->
name|dirty_region
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gegl_rectangle_equal
argument_list|(
operator|&
name|real_src_rect
argument_list|,
name|gegl_buffer_get_extent
argument_list|(
name|src_buffer
argument_list|)
argument_list|)
condition|)
block|{
name|cairo_region_intersect_rectangle
argument_list|(
name|region
argument_list|,
operator|(
name|cairo_rectangle_int_t
operator|*
operator|)
operator|&
name|real_src_rect
argument_list|)
expr_stmt|;
block|}
name|cairo_region_translate
argument_list|(
name|region
argument_list|,
name|real_dst_rect
operator|.
name|x
operator|-
name|real_src_rect
operator|.
name|x
argument_list|,
name|real_dst_rect
operator|.
name|y
operator|-
name|real_src_rect
operator|.
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|cairo_region_is_empty
argument_list|(
name|dst_validate
operator|->
name|dirty_region
argument_list|)
condition|)
block|{
name|cairo_region_destroy
argument_list|(
name|dst_validate
operator|->
name|dirty_region
argument_list|)
expr_stmt|;
name|dst_validate
operator|->
name|dirty_region
operator|=
name|region
expr_stmt|;
block|}
else|else
block|{
name|cairo_region_union
argument_list|(
name|dst_validate
operator|->
name|dirty_region
argument_list|,
name|region
argument_list|)
expr_stmt|;
name|cairo_region_destroy
argument_list|(
name|region
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

end_unit

