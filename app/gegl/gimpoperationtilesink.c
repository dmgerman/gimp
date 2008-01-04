begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationtilesink.c  * Copyright (C) 2007 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"gegl/gegl-types.h"
end_include

begin_include
include|#
directive|include
file|<gegl/buffer/gegl-buffer.h>
end_include

begin_include
include|#
directive|include
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"base/base-types.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationtilesink.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2933e8ff0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TILE_MANAGER
name|PROP_TILE_MANAGER
block|,
DECL|enumerator|PROP_LINEAR
name|PROP_LINEAR
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2933e8ff0203
block|{
DECL|enumerator|DATA_WRITTEN
name|DATA_WRITTEN
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_tile_sink_finalize
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
name|gimp_operation_tile_sink_get_property
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
name|gimp_operation_tile_sink_set_property
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
name|gboolean
name|gimp_operation_tile_sink_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationTileSink
argument_list|,
argument|gimp_operation_tile_sink
argument_list|,
argument|GEGL_TYPE_OPERATION_SINK
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_tile_sink_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|tile_sink_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_operation_tile_sink_class_init (GimpOperationTileSinkClass * klass)
name|gimp_operation_tile_sink_class_init
parameter_list|(
name|GimpOperationTileSinkClass
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
name|GeglOperationSinkClass
modifier|*
name|sink_class
init|=
name|GEGL_OPERATION_SINK_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tile_sink_signals
index|[
name|DATA_WRITTEN
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"data-written"
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
name|GimpOperationTileSinkClass
argument_list|,
name|data_written
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_operation_tile_sink_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_tile_sink_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_tile_sink_get_property
expr_stmt|;
name|sink_class
operator|->
name|process
operator|=
name|gimp_operation_tile_sink_process
expr_stmt|;
name|sink_class
operator|->
name|needs_full
operator|=
name|FALSE
expr_stmt|;
name|gegl_operation_class_set_name
argument_list|(
name|operation_class
argument_list|,
literal|"gimp-tilemanager-sink"
argument_list|)
expr_stmt|;
empty_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TILE_MANAGER
argument_list|,
name|g_param_spec_boxed
argument_list|(
literal|"tile-manager"
argument_list|,
literal|"Tile Manager"
argument_list|,
literal|"The tile manager to use as a destination"
argument_list|,
name|GIMP_TYPE_TILE_MANAGER
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_LINEAR
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"linear"
argument_list|,
literal|"Linear data"
argument_list|,
literal|"Should the data written to the tile-manager be linear or gamma-corrected?"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
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
DECL|function|gimp_operation_tile_sink_init (GimpOperationTileSink * self)
name|gimp_operation_tile_sink_init
parameter_list|(
name|GimpOperationTileSink
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_tile_sink_finalize (GObject * object)
name|gimp_operation_tile_sink_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOperationTileSink
modifier|*
name|self
init|=
name|GIMP_OPERATION_TILE_SINK
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|self
operator|->
name|tile_manager
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|self
operator|->
name|tile_manager
argument_list|)
expr_stmt|;
name|self
operator|->
name|tile_manager
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
name|void
DECL|function|gimp_operation_tile_sink_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_tile_sink_get_property
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
name|GimpOperationTileSink
modifier|*
name|self
init|=
name|GIMP_OPERATION_TILE_SINK
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
name|PROP_TILE_MANAGER
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|tile_manager
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LINEAR
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|linear
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
DECL|function|gimp_operation_tile_sink_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_tile_sink_set_property
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
name|GimpOperationTileSink
modifier|*
name|self
init|=
name|GIMP_OPERATION_TILE_SINK
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
name|PROP_TILE_MANAGER
case|:
if|if
condition|(
name|self
operator|->
name|tile_manager
condition|)
name|tile_manager_unref
argument_list|(
name|self
operator|->
name|tile_manager
argument_list|)
expr_stmt|;
name|self
operator|->
name|tile_manager
operator|=
name|g_value_dup_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LINEAR
case|:
name|self
operator|->
name|linear
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
name|gboolean
DECL|function|gimp_operation_tile_sink_process (GeglOperation * operation,gpointer context_id,const GeglRectangle * result)
name|gimp_operation_tile_sink_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result
parameter_list|)
block|{
name|GimpOperationTileSink
modifier|*
name|self
init|=
name|GIMP_OPERATION_TILE_SINK
argument_list|(
name|operation
argument_list|)
decl_stmt|;
if|if
condition|(
name|self
operator|->
name|tile_manager
condition|)
block|{
name|GeglBuffer
modifier|*
name|input
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
specifier|const
name|guint
name|bpp
init|=
name|tile_manager_bpp
argument_list|(
name|self
operator|->
name|tile_manager
argument_list|)
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
if|if
condition|(
name|self
operator|->
name|linear
condition|)
name|format
operator|=
name|gimp_bpp_to_babl_format_linear
argument_list|(
name|bpp
argument_list|)
expr_stmt|;
else|else
name|format
operator|=
name|gimp_bpp_to_babl_format
argument_list|(
name|bpp
argument_list|)
expr_stmt|;
name|input
operator|=
name|GEGL_BUFFER
argument_list|(
name|gegl_operation_get_data
argument_list|(
name|operation
argument_list|,
name|context_id
argument_list|,
literal|"input"
argument_list|)
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|self
operator|->
name|tile_manager
argument_list|,
name|result
operator|->
name|x
argument_list|,
name|result
operator|->
name|y
argument_list|,
name|result
operator|->
name|width
argument_list|,
name|result
operator|->
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|1
argument_list|,
operator|&
name|destPR
argument_list|)
init|;
name|pr
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|GeglRectangle
name|rect
init|=
block|{
name|destPR
operator|.
name|x
block|,
name|destPR
operator|.
name|y
block|,
name|destPR
operator|.
name|w
block|,
name|destPR
operator|.
name|h
block|}
decl_stmt|;
name|gegl_buffer_get
argument_list|(
name|input
argument_list|,
literal|1.0
argument_list|,
operator|&
name|rect
argument_list|,
name|format
argument_list|,
name|destPR
operator|.
name|data
argument_list|,
name|destPR
operator|.
name|rowstride
argument_list|)
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|operation
argument_list|,
name|tile_sink_signals
index|[
name|DATA_WRITTEN
index|]
argument_list|,
literal|0
argument_list|,
name|result
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"no tilemanager?"
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

