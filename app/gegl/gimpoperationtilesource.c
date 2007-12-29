begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpops.c  * Copyright (C) 2007 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationtilesource.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2ac499020103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TILE_MANAGER
name|PROP_TILE_MANAGER
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_tile_source_finalize
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
name|gimp_operation_tile_source_get_property
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
name|gimp_operation_tile_source_set_property
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
name|gimp_operation_tile_source_get_defined_region
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
name|gimp_operation_tile_source_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationTileSource,gimp_operation_tile_source,GEGL_TYPE_OPERATION_SOURCE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationTileSource
argument_list|,
argument|gimp_operation_tile_source
argument_list|,
argument|GEGL_TYPE_OPERATION_SOURCE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_tile_source_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_tile_source_class_init
parameter_list|(
name|GimpOperationTileSourceClass
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
name|GeglOperationSourceClass
modifier|*
name|source_class
init|=
name|GEGL_OPERATION_SOURCE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_operation_tile_source_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_tile_source_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_tile_source_get_property
expr_stmt|;
name|operation_class
operator|->
name|get_defined_region
operator|=
name|gimp_operation_tile_source_get_defined_region
expr_stmt|;
name|source_class
operator|->
name|process
operator|=
name|gimp_operation_tile_source_process
expr_stmt|;
name|gegl_operation_class_set_name
argument_list|(
name|operation_class
argument_list|,
literal|"gimp-tilemanager-source"
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
literal|"The tile manager to use as source"
argument_list|,
name|GIMP_TYPE_TILE_MANAGER
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
DECL|function|gimp_operation_tile_source_init (GimpOperationTileSource * self)
name|gimp_operation_tile_source_init
parameter_list|(
name|GimpOperationTileSource
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_tile_source_finalize (GObject * object)
name|gimp_operation_tile_source_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOperationTileSource
modifier|*
name|self
init|=
name|GIMP_OPERATION_TILE_SOURCE
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
DECL|function|gimp_operation_tile_source_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_tile_source_get_property
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
name|GimpOperationTileSource
modifier|*
name|self
init|=
name|GIMP_OPERATION_TILE_SOURCE
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
DECL|function|gimp_operation_tile_source_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_tile_source_set_property
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
name|GimpOperationTileSource
modifier|*
name|self
init|=
name|GIMP_OPERATION_TILE_SOURCE
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
DECL|function|gimp_operation_tile_source_get_defined_region (GeglOperation * operation)
name|gimp_operation_tile_source_get_defined_region
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|GimpOperationTileSource
modifier|*
name|self
init|=
name|GIMP_OPERATION_TILE_SOURCE
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GeglRectangle
name|result
init|=
block|{
literal|0
block|, }
decl_stmt|;
if|if
condition|(
name|self
operator|->
name|tile_manager
condition|)
block|{
name|result
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|result
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|result
operator|.
name|width
operator|=
name|tile_manager_width
argument_list|(
name|self
operator|->
name|tile_manager
argument_list|)
expr_stmt|;
name|result
operator|.
name|height
operator|=
name|tile_manager_height
argument_list|(
name|self
operator|->
name|tile_manager
argument_list|)
expr_stmt|;
block|}
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_tile_source_process (GeglOperation * operation,gpointer context_id)
name|gimp_operation_tile_source_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|)
block|{
name|GimpOperationTileSource
modifier|*
name|self
init|=
name|GIMP_OPERATION_TILE_SOURCE
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
name|output
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|GeglRectangle
name|extent
init|=
block|{
literal|0
block|,
literal|0
block|,
name|tile_manager_width
argument_list|(
name|self
operator|->
name|tile_manager
argument_list|)
block|,
name|tile_manager_height
argument_list|(
argument|self->tile_manager
argument_list|)
block|}
decl_stmt|;
name|format
operator|=
name|gimp_bpp_to_babl_format
argument_list|(
name|tile_manager_bpp
argument_list|(
name|self
operator|->
name|tile_manager
argument_list|)
argument_list|)
expr_stmt|;
name|output
operator|=
name|gegl_buffer_new
argument_list|(
operator|&
name|extent
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|self
operator|->
name|tile_manager
argument_list|,
name|extent
operator|.
name|x
argument_list|,
name|extent
operator|.
name|y
argument_list|,
name|extent
operator|.
name|width
argument_list|,
name|extent
operator|.
name|height
argument_list|,
name|FALSE
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
name|srcPR
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
name|srcPR
operator|.
name|x
block|,
name|srcPR
operator|.
name|y
block|,
name|srcPR
operator|.
name|w
block|,
name|srcPR
operator|.
name|h
block|}
decl_stmt|;
name|gegl_buffer_set
argument_list|(
name|output
argument_list|,
operator|&
name|rect
argument_list|,
name|format
argument_list|,
name|srcPR
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
name|gegl_operation_set_data
argument_list|(
name|operation
argument_list|,
name|context_id
argument_list|,
literal|"output"
argument_list|,
name|G_OBJECT
argument_list|(
name|output
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

