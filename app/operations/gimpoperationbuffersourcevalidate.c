begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationbuffersourcevalidate.c  * Copyright (C) 2017 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimptilehandlervalidate.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationbuffersourcevalidate.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a0e62d20103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_BUFFER
name|PROP_BUFFER
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_buffer_source_validate_dispose
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
name|gimp_operation_buffer_source_validate_get_property
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
name|gimp_operation_buffer_source_validate_set_property
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
name|GeglRectangle
name|gimp_operation_buffer_source_validate_get_bounding_box
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_operation_buffer_source_validate_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_buffer_source_validate_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglOperationContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|output_pad
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_operation_buffer_source_validate_buffer_changed
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_operation_buffer_source_validate_buffer_validate
parameter_list|(
name|GimpOperationBufferSourceValidate
modifier|*
name|buffer_source_validate
parameter_list|,
specifier|const
name|cairo_rectangle_int_t
modifier|*
name|rect
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationBufferSourceValidate,gimp_operation_buffer_source_validate,GEGL_TYPE_OPERATION_SOURCE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationBufferSourceValidate
argument_list|,
argument|gimp_operation_buffer_source_validate
argument_list|,
argument|GEGL_TYPE_OPERATION_SOURCE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_buffer_source_validate_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_buffer_source_validate_class_init
parameter_list|(
name|GimpOperationBufferSourceValidateClass
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
name|GeglOperationClass
modifier|*
name|operation_class
init|=
name|GEGL_OPERATION_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_operation_buffer_source_validate_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_buffer_source_validate_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_buffer_source_validate_get_property
expr_stmt|;
name|operation_class
operator|->
name|get_bounding_box
operator|=
name|gimp_operation_buffer_source_validate_get_bounding_box
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_buffer_source_validate_prepare
expr_stmt|;
name|operation_class
operator|->
name|process
operator|=
name|gimp_operation_buffer_source_validate_process
expr_stmt|;
name|operation_class
operator|->
name|threaded
operator|=
name|FALSE
expr_stmt|;
name|operation_class
operator|->
name|no_cache
operator|=
name|TRUE
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:buffer-source-validate"
argument_list|,
literal|"categories"
argument_list|,
literal|"gimp"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP Buffer-Source Validate operation"
argument_list|,
name|NULL
argument_list|)
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
literal|"Buffer"
argument_list|,
literal|"Input buffer"
argument_list|,
name|GEGL_TYPE_BUFFER
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_buffer_source_validate_init (GimpOperationBufferSourceValidate * self)
name|gimp_operation_buffer_source_validate_init
parameter_list|(
name|GimpOperationBufferSourceValidate
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_buffer_source_validate_dispose (GObject * object)
name|gimp_operation_buffer_source_validate_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOperationBufferSourceValidate
modifier|*
name|buffer_source_validate
init|=
name|GIMP_OPERATION_BUFFER_SOURCE_VALIDATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|buffer_source_validate
operator|->
name|buffer
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|,
name|gimp_operation_buffer_source_validate_buffer_changed
argument_list|,
name|buffer_source_validate
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|buffer_source_validate
operator|->
name|buffer
argument_list|)
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_buffer_source_validate_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_buffer_source_validate_get_property
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
name|GimpOperationBufferSourceValidate
modifier|*
name|buffer_source_validate
init|=
name|GIMP_OPERATION_BUFFER_SOURCE_VALIDATE
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
name|buffer_source_validate
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
DECL|function|gimp_operation_buffer_source_validate_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_buffer_source_validate_set_property
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
name|GimpOperationBufferSourceValidate
modifier|*
name|buffer_source_validate
init|=
name|GIMP_OPERATION_BUFFER_SOURCE_VALIDATE
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
block|{
if|if
condition|(
name|buffer_source_validate
operator|->
name|buffer
condition|)
block|{
name|gimp_operation_buffer_source_validate_buffer_changed
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|,
name|gegl_buffer_get_extent
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|)
argument_list|,
name|buffer_source_validate
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_operation_buffer_source_validate_buffer_changed
argument_list|)
argument_list|,
name|buffer_source_validate
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|buffer_source_validate
operator|->
name|buffer
argument_list|)
expr_stmt|;
block|}
name|buffer_source_validate
operator|->
name|buffer
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer_source_validate
operator|->
name|buffer
condition|)
block|{
name|g_signal_connect
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_operation_buffer_source_validate_buffer_changed
argument_list|)
argument_list|,
name|buffer_source_validate
argument_list|)
expr_stmt|;
name|gimp_operation_buffer_source_validate_buffer_changed
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|,
name|gegl_buffer_get_extent
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|)
argument_list|,
name|buffer_source_validate
argument_list|)
expr_stmt|;
block|}
block|}
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
name|GeglRectangle
DECL|function|gimp_operation_buffer_source_validate_get_bounding_box (GeglOperation * operation)
name|gimp_operation_buffer_source_validate_get_bounding_box
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|GimpOperationBufferSourceValidate
modifier|*
name|buffer_source_validate
init|=
name|GIMP_OPERATION_BUFFER_SOURCE_VALIDATE
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GeglRectangle
name|result
init|=
block|{}
decl_stmt|;
if|if
condition|(
name|buffer_source_validate
operator|->
name|buffer
condition|)
name|result
operator|=
operator|*
name|gegl_buffer_get_extent
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_buffer_source_validate_prepare (GeglOperation * operation)
name|gimp_operation_buffer_source_validate_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|GimpOperationBufferSourceValidate
modifier|*
name|buffer_source_validate
init|=
name|GIMP_OPERATION_BUFFER_SOURCE_VALIDATE
argument_list|(
name|operation
argument_list|)
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|buffer_source_validate
operator|->
name|buffer
condition|)
name|format
operator|=
name|gegl_buffer_get_format
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|)
expr_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"output"
argument_list|,
name|format
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_buffer_source_validate_process (GeglOperation * operation,GeglOperationContext * context,const gchar * output_pad,const GeglRectangle * result,gint level)
name|gimp_operation_buffer_source_validate_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglOperationContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|output_pad
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result
parameter_list|,
name|gint
name|level
parameter_list|)
block|{
name|GimpOperationBufferSourceValidate
modifier|*
name|buffer_source_validate
init|=
name|GIMP_OPERATION_BUFFER_SOURCE_VALIDATE
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
init|=
name|buffer_source_validate
operator|->
name|buffer
decl_stmt|;
if|if
condition|(
name|buffer
condition|)
block|{
name|GimpTileHandlerValidate
modifier|*
name|validate_handler
decl_stmt|;
name|validate_handler
operator|=
name|gimp_tile_handler_validate_get_assigned
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|validate_handler
condition|)
block|{
name|gint
name|n_threads
decl_stmt|;
name|g_object_get
argument_list|(
name|gegl_config
argument_list|()
argument_list|,
literal|"threads"
argument_list|,
operator|&
name|n_threads
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* the main reason to validate the buffer during processing is to            * avoid threading issues.  skip validation if not using            * multithreading.            */
if|if
condition|(
name|n_threads
operator|>
literal|1
condition|)
block|{
name|cairo_rectangle_int_t
name|rect
decl_stmt|;
name|cairo_region_overlap_t
name|overlap
decl_stmt|;
name|rect
operator|.
name|x
operator|=
name|result
operator|->
name|x
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|result
operator|->
name|y
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|result
operator|->
name|width
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|result
operator|->
name|height
expr_stmt|;
name|overlap
operator|=
name|cairo_region_contains_rectangle
argument_list|(
name|validate_handler
operator|->
name|dirty_region
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|overlap
operator|==
name|CAIRO_REGION_OVERLAP_IN
condition|)
block|{
name|gimp_operation_buffer_source_validate_buffer_validate
argument_list|(
name|buffer_source_validate
argument_list|,
operator|&
name|rect
argument_list|,
name|level
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|overlap
operator|==
name|CAIRO_REGION_OVERLAP_PART
condition|)
block|{
name|cairo_region_t
modifier|*
name|region
decl_stmt|;
name|gint
name|n_rectangles
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|region
operator|=
name|cairo_region_copy
argument_list|(
name|validate_handler
operator|->
name|dirty_region
argument_list|)
expr_stmt|;
name|cairo_region_intersect_rectangle
argument_list|(
name|region
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
name|n_rectangles
operator|=
name|cairo_region_num_rectangles
argument_list|(
name|region
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_rectangles
condition|;
name|i
operator|++
control|)
block|{
name|cairo_region_get_rectangle
argument_list|(
name|region
argument_list|,
name|i
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
name|gimp_operation_buffer_source_validate_buffer_validate
argument_list|(
name|buffer_source_validate
argument_list|,
operator|&
name|rect
argument_list|,
name|level
argument_list|)
expr_stmt|;
block|}
name|cairo_region_destroy
argument_list|(
name|region
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|gegl_operation_context_set_object
argument_list|(
name|context
argument_list|,
literal|"output"
argument_list|,
name|G_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_object_set_has_forked
argument_list|(
name|G_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_buffer_source_validate_buffer_changed (GeglBuffer * buffer,const GeglRectangle * rect,gpointer data)
name|gimp_operation_buffer_source_validate_buffer_changed
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpOperationBufferSourceValidate
modifier|*
name|buffer_source_validate
init|=
name|GIMP_OPERATION_BUFFER_SOURCE_VALIDATE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gegl_operation_invalidate
argument_list|(
name|GEGL_OPERATION
argument_list|(
name|buffer_source_validate
argument_list|)
argument_list|,
name|rect
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_buffer_source_validate_buffer_validate (GimpOperationBufferSourceValidate * buffer_source_validate,const cairo_rectangle_int_t * rect,gint level)
name|gimp_operation_buffer_source_validate_buffer_validate
parameter_list|(
name|GimpOperationBufferSourceValidate
modifier|*
name|buffer_source_validate
parameter_list|,
specifier|const
name|cairo_rectangle_int_t
modifier|*
name|rect
parameter_list|,
name|gint
name|level
parameter_list|)
block|{
name|gint
name|shift_x
decl_stmt|;
name|gint
name|shift_y
decl_stmt|;
name|gint
name|tile_width
decl_stmt|;
name|gint
name|tile_height
decl_stmt|;
name|GeglRectangle
name|roi
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|g_object_get
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|,
literal|"shift-x"
argument_list|,
operator|&
name|shift_x
argument_list|,
literal|"shift-y"
argument_list|,
operator|&
name|shift_y
argument_list|,
literal|"tile-width"
argument_list|,
operator|&
name|tile_width
argument_list|,
literal|"tile-height"
argument_list|,
operator|&
name|tile_height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* align rectangle to tile grid */
name|roi
operator|.
name|x
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
call|(
name|gdouble
call|)
argument_list|(
name|rect
operator|->
name|x
operator|+
name|shift_x
argument_list|)
operator|/
name|tile_width
argument_list|)
operator|*
name|tile_width
expr_stmt|;
name|roi
operator|.
name|y
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
call|(
name|gdouble
call|)
argument_list|(
name|rect
operator|->
name|y
operator|+
name|shift_y
argument_list|)
operator|/
name|tile_height
argument_list|)
operator|*
name|tile_height
expr_stmt|;
name|roi
operator|.
name|width
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
call|(
name|gdouble
call|)
argument_list|(
name|rect
operator|->
name|x
operator|+
name|rect
operator|->
name|width
operator|+
name|shift_x
argument_list|)
operator|/
name|tile_width
argument_list|)
operator|*
name|tile_width
operator|-
name|roi
operator|.
name|x
expr_stmt|;
name|roi
operator|.
name|height
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
call|(
name|gdouble
call|)
argument_list|(
name|rect
operator|->
name|y
operator|+
name|rect
operator|->
name|height
operator|+
name|shift_y
argument_list|)
operator|/
name|tile_height
argument_list|)
operator|*
name|tile_height
operator|-
name|roi
operator|.
name|y
expr_stmt|;
name|roi
operator|.
name|x
operator|-=
name|shift_x
expr_stmt|;
name|roi
operator|.
name|y
operator|-=
name|shift_y
expr_stmt|;
comment|/* intersect rectangle with abyss */
name|gegl_rectangle_intersect
argument_list|(
operator|&
name|roi
argument_list|,
operator|&
name|roi
argument_list|,
name|gegl_buffer_get_abyss
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
comment|/* iterate over rectangle -- this implicitly causes validation */
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|buffer_source_validate
operator|->
name|buffer
argument_list|,
operator|&
name|roi
argument_list|,
name|level
argument_list|,
name|NULL
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
empty_stmt|;
block|}
end_function

end_unit

