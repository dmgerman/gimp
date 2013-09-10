begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasbufferpreview.c  * Copyright (C) 2013 Marek Dvoroznak<dvoromar@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<cairo/cairo.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"display/display-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasbufferpreview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scroll.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b1d63510103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_BUFFER
name|PROP_BUFFER
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasBufferPreviewPrivate
typedef|typedef
name|struct
name|_GimpCanvasBufferPreviewPrivate
name|GimpCanvasBufferPreviewPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasBufferPreviewPrivate
struct|struct
name|_GimpCanvasBufferPreviewPrivate
block|{
DECL|member|buffer
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (transform_preview)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|transform_preview
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (transform_preview, \                                      GIMP_TYPE_CANVAS_BUFFER_PREVIEW, \                                      GimpCanvasBufferPreviewPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_buffer_preview_set_property
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
name|gimp_canvas_buffer_preview_get_property
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
name|gimp_canvas_buffer_preview_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|cairo_region_t
modifier|*
name|gimp_canvas_buffer_preview_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_buffer_preview_compute_bounds
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_rectangle_int_t
modifier|*
name|bounds
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCanvasBufferPreview,gimp_canvas_buffer_preview,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasBufferPreview
argument_list|,
argument|gimp_canvas_buffer_preview
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_buffer_preview_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_buffer_preview_class_init
parameter_list|(
name|GimpCanvasBufferPreviewClass
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
name|GimpCanvasItemClass
modifier|*
name|item_class
init|=
name|GIMP_CANVAS_ITEM_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_canvas_buffer_preview_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_buffer_preview_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_buffer_preview_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_buffer_preview_get_extents
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_BUFFER
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"buffer"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GEGL_TYPE_BUFFER
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCanvasBufferPreviewPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_buffer_preview_init (GimpCanvasBufferPreview * transform_preview)
name|gimp_canvas_buffer_preview_init
parameter_list|(
name|GimpCanvasBufferPreview
modifier|*
name|transform_preview
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_buffer_preview_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_buffer_preview_set_property
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
name|GimpCanvasBufferPreviewPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_BUFFER
case|:
name|private
operator|->
name|buffer
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't ref */
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
DECL|function|gimp_canvas_buffer_preview_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_buffer_preview_get_property
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
name|GimpCanvasBufferPreviewPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_BUFFER
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|buffer
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
DECL|function|gimp_canvas_buffer_preview_draw (GimpCanvasItem * item,cairo_t * cr)
name|gimp_canvas_buffer_preview_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_canvas_item_get_shell
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
operator|->
name|buffer
decl_stmt|;
name|cairo_surface_t
modifier|*
name|area
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|cairo_rectangle_int_t
name|rectangle
decl_stmt|;
name|gint
name|viewport_offset_x
decl_stmt|,
name|viewport_offset_y
decl_stmt|;
name|gint
name|viewport_width
decl_stmt|,
name|viewport_height
decl_stmt|;
name|gimp_display_shell_scroll_get_scaled_viewport
argument_list|(
name|shell
argument_list|,
operator|&
name|viewport_offset_x
argument_list|,
operator|&
name|viewport_offset_y
argument_list|,
operator|&
name|viewport_width
argument_list|,
operator|&
name|viewport_height
argument_list|)
expr_stmt|;
name|gimp_canvas_buffer_preview_compute_bounds
argument_list|(
name|item
argument_list|,
operator|&
name|rectangle
argument_list|)
expr_stmt|;
name|area
operator|=
name|cairo_image_surface_create
argument_list|(
name|CAIRO_FORMAT_ARGB32
argument_list|,
name|rectangle
operator|.
name|width
argument_list|,
name|rectangle
operator|.
name|height
argument_list|)
expr_stmt|;
name|data
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|area
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
operator|(
name|viewport_offset_x
operator|<
literal|0
condition|?
literal|0
else|:
name|viewport_offset_x
operator|)
argument_list|,
operator|(
name|viewport_offset_y
operator|<
literal|0
condition|?
literal|0
else|:
name|viewport_offset_y
operator|)
argument_list|,
name|rectangle
operator|.
name|width
argument_list|,
name|rectangle
operator|.
name|height
argument_list|)
argument_list|,
name|shell
operator|->
name|scale_x
argument_list|,
name|gegl_buffer_get_format
argument_list|(
name|buffer
argument_list|)
argument_list|,
comment|/* has to be cairo-ARGB32 */
name|data
argument_list|,
name|cairo_image_surface_get_stride
argument_list|(
name|area
argument_list|)
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|cairo_surface_flush
argument_list|(
name|area
argument_list|)
expr_stmt|;
name|cairo_surface_mark_dirty
argument_list|(
name|area
argument_list|)
expr_stmt|;
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|area
argument_list|,
name|rectangle
operator|.
name|x
argument_list|,
name|rectangle
operator|.
name|y
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|rectangle
operator|.
name|x
argument_list|,
name|rectangle
operator|.
name|y
argument_list|,
name|rectangle
operator|.
name|width
argument_list|,
name|rectangle
operator|.
name|height
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|area
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_buffer_preview_compute_bounds (GimpCanvasItem * item,cairo_rectangle_int_t * bounds)
name|gimp_canvas_buffer_preview_compute_bounds
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_rectangle_int_t
modifier|*
name|bounds
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_canvas_item_get_shell
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
operator|->
name|buffer
decl_stmt|;
name|gint
name|x_from
decl_stmt|,
name|x_to
decl_stmt|;
name|gint
name|y_from
decl_stmt|,
name|y_to
decl_stmt|;
name|gint
name|viewport_offset_x
decl_stmt|,
name|viewport_offset_y
decl_stmt|;
name|gint
name|viewport_width
decl_stmt|,
name|viewport_height
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|width
operator|=
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|height
operator|=
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_display_shell_scroll_get_scaled_viewport
argument_list|(
name|shell
argument_list|,
operator|&
name|viewport_offset_x
argument_list|,
operator|&
name|viewport_offset_y
argument_list|,
operator|&
name|viewport_width
argument_list|,
operator|&
name|viewport_height
argument_list|)
expr_stmt|;
name|x_from
operator|=
operator|(
name|viewport_offset_x
operator|<
literal|0
condition|?
operator|-
name|viewport_offset_x
else|:
literal|0
operator|)
expr_stmt|;
name|y_from
operator|=
operator|(
name|viewport_offset_y
operator|<
literal|0
condition|?
operator|-
name|viewport_offset_y
else|:
literal|0
operator|)
expr_stmt|;
name|x_to
operator|=
name|width
operator|*
name|shell
operator|->
name|scale_x
operator|-
name|viewport_offset_x
expr_stmt|;
if|if
condition|(
name|x_to
operator|>
name|viewport_width
condition|)
name|x_to
operator|=
name|viewport_width
expr_stmt|;
name|y_to
operator|=
name|height
operator|*
name|shell
operator|->
name|scale_y
operator|-
name|viewport_offset_y
expr_stmt|;
if|if
condition|(
name|y_to
operator|>
name|viewport_height
condition|)
name|y_to
operator|=
name|viewport_height
expr_stmt|;
name|bounds
operator|->
name|x
operator|=
name|x_from
expr_stmt|;
name|bounds
operator|->
name|y
operator|=
name|y_from
expr_stmt|;
name|bounds
operator|->
name|width
operator|=
name|x_to
operator|-
name|x_from
expr_stmt|;
name|bounds
operator|->
name|height
operator|=
name|y_to
operator|-
name|y_from
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|cairo_region_t
modifier|*
DECL|function|gimp_canvas_buffer_preview_get_extents (GimpCanvasItem * item)
name|gimp_canvas_buffer_preview_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
name|cairo_rectangle_int_t
name|rectangle
decl_stmt|;
name|gimp_canvas_buffer_preview_compute_bounds
argument_list|(
name|item
argument_list|,
operator|&
name|rectangle
argument_list|)
expr_stmt|;
return|return
name|cairo_region_create_rectangle
argument_list|(
operator|&
name|rectangle
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_buffer_preview_new (GimpDisplayShell * shell,GeglBuffer * buffer)
name|gimp_canvas_buffer_preview_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS_BUFFER_PREVIEW
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"buffer"
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

