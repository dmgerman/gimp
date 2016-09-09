begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationprofiletransform.c  * Copyright (C) 2016 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationprofiletransform.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c73c3710103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SRC_PROFILE
name|PROP_SRC_PROFILE
block|,
DECL|enumerator|PROP_DEST_PROFILE
name|PROP_DEST_PROFILE
block|,
DECL|enumerator|PROP_INTENT
name|PROP_INTENT
block|,
DECL|enumerator|PROP_BPC
name|PROP_BPC
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_profile_transform_finalize
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
name|gimp_operation_profile_transform_get_property
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
name|gimp_operation_profile_transform_set_property
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
name|gimp_operation_profile_transform_prepare
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
name|gimp_operation_profile_transform_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in_buf
parameter_list|,
name|void
modifier|*
name|out_buf
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationProfileTransform,gimp_operation_profile_transform,GEGL_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationProfileTransform
argument_list|,
argument|gimp_operation_profile_transform
argument_list|,
argument|GEGL_TYPE_OPERATION_POINT_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_profile_transform_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_profile_transform_class_init
parameter_list|(
name|GimpOperationProfileTransformClass
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
name|GeglOperationPointFilterClass
modifier|*
name|point_class
init|=
name|GEGL_OPERATION_POINT_FILTER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_operation_profile_transform_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_profile_transform_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_profile_transform_get_property
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:profile-transform"
argument_list|,
literal|"categories"
argument_list|,
literal|"color"
argument_list|,
literal|"description"
argument_list|,
literal|"Transform between two color profiles"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_profile_transform_prepare
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_profile_transform_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SRC_PROFILE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"src-profile"
argument_list|,
literal|"Source Profile"
argument_list|,
literal|"Source Profile"
argument_list|,
name|GIMP_TYPE_COLOR_PROFILE
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
name|PROP_DEST_PROFILE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"dest-profile"
argument_list|,
literal|"Destination Profile"
argument_list|,
literal|"Destination Profile"
argument_list|,
name|GIMP_TYPE_COLOR_PROFILE
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
name|PROP_INTENT
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"intent"
argument_list|,
literal|"Rendering Intent"
argument_list|,
literal|"Rendering Intent"
argument_list|,
name|GIMP_TYPE_COLOR_RENDERING_INTENT
argument_list|,
name|GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
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
name|PROP_BPC
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"blc"
argument_list|,
literal|"Black Point Compensation"
argument_list|,
literal|"Black Point Compensation"
argument_list|,
name|TRUE
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
DECL|function|gimp_operation_profile_transform_init (GimpOperationProfileTransform * self)
name|gimp_operation_profile_transform_init
parameter_list|(
name|GimpOperationProfileTransform
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_profile_transform_finalize (GObject * object)
name|gimp_operation_profile_transform_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOperationProfileTransform
modifier|*
name|self
init|=
name|GIMP_OPERATION_PROFILE_TRANSFORM
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|self
operator|->
name|src_profile
condition|)
block|{
name|g_object_unref
argument_list|(
name|self
operator|->
name|src_profile
argument_list|)
expr_stmt|;
name|self
operator|->
name|src_profile
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|self
operator|->
name|dest_profile
condition|)
block|{
name|g_object_unref
argument_list|(
name|self
operator|->
name|dest_profile
argument_list|)
expr_stmt|;
name|self
operator|->
name|dest_profile
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|self
operator|->
name|transform
condition|)
block|{
name|g_object_unref
argument_list|(
name|self
operator|->
name|transform
argument_list|)
expr_stmt|;
name|self
operator|->
name|transform
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
DECL|function|gimp_operation_profile_transform_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_profile_transform_get_property
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
name|GimpOperationProfileTransform
modifier|*
name|self
init|=
name|GIMP_OPERATION_PROFILE_TRANSFORM
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
name|PROP_SRC_PROFILE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|src_profile
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEST_PROFILE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|dest_profile
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INTENT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|intent
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BPC
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|bpc
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
DECL|function|gimp_operation_profile_transform_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_profile_transform_set_property
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
name|GimpOperationProfileTransform
modifier|*
name|self
init|=
name|GIMP_OPERATION_PROFILE_TRANSFORM
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
name|PROP_SRC_PROFILE
case|:
if|if
condition|(
name|self
operator|->
name|src_profile
condition|)
name|g_object_unref
argument_list|(
name|self
operator|->
name|src_profile
argument_list|)
expr_stmt|;
name|self
operator|->
name|src_profile
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEST_PROFILE
case|:
if|if
condition|(
name|self
operator|->
name|dest_profile
condition|)
name|g_object_unref
argument_list|(
name|self
operator|->
name|dest_profile
argument_list|)
expr_stmt|;
name|self
operator|->
name|dest_profile
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INTENT
case|:
name|self
operator|->
name|intent
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BPC
case|:
name|self
operator|->
name|bpc
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
DECL|function|gimp_operation_profile_transform_prepare (GeglOperation * operation)
name|gimp_operation_profile_transform_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|GimpOperationProfileTransform
modifier|*
name|self
init|=
name|GIMP_OPERATION_PROFILE_TRANSFORM
argument_list|(
name|operation
argument_list|)
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|format
operator|=
name|gegl_operation_get_source_format
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|format
condition|)
name|format
operator|=
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
expr_stmt|;
if|if
condition|(
name|self
operator|->
name|transform
condition|)
block|{
name|g_object_unref
argument_list|(
name|self
operator|->
name|transform
argument_list|)
expr_stmt|;
name|self
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
name|self
operator|->
name|src_format
operator|=
name|format
expr_stmt|;
name|self
operator|->
name|dest_format
operator|=
name|format
expr_stmt|;
if|if
condition|(
name|self
operator|->
name|src_profile
operator|&&
name|self
operator|->
name|dest_profile
condition|)
block|{
name|GimpColorTransformFlags
name|flags
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|self
operator|->
name|bpc
condition|)
name|flags
operator||=
name|GIMP_COLOR_TRANSFORM_FLAGS_BLACK_POINT_COMPENSATION
expr_stmt|;
name|flags
operator||=
name|GIMP_COLOR_TRANSFORM_FLAGS_NOOPTIMIZE
expr_stmt|;
name|self
operator|->
name|transform
operator|=
name|gimp_color_transform_new
argument_list|(
name|self
operator|->
name|src_profile
argument_list|,
name|format
argument_list|,
name|self
operator|->
name|dest_profile
argument_list|,
name|format
argument_list|,
name|self
operator|->
name|intent
argument_list|,
name|flags
argument_list|)
expr_stmt|;
block|}
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|,
name|self
operator|->
name|src_format
argument_list|)
expr_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"output"
argument_list|,
name|self
operator|->
name|dest_format
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_profile_transform_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_profile_transform_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in_buf
parameter_list|,
name|void
modifier|*
name|out_buf
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
block|{
name|GimpOperationProfileTransform
modifier|*
name|self
init|=
name|GIMP_OPERATION_PROFILE_TRANSFORM
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|gpointer
modifier|*
name|src
init|=
name|in_buf
decl_stmt|;
name|gpointer
modifier|*
name|dest
init|=
name|out_buf
decl_stmt|;
if|if
condition|(
name|self
operator|->
name|transform
condition|)
block|{
name|gimp_color_transform_process_pixels
argument_list|(
name|self
operator|->
name|transform
argument_list|,
name|self
operator|->
name|src_format
argument_list|,
name|src
argument_list|,
name|self
operator|->
name|dest_format
argument_list|,
name|dest
argument_list|,
name|samples
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
name|self
operator|->
name|src_format
argument_list|,
name|self
operator|->
name|dest_format
argument_list|)
argument_list|,
name|src
argument_list|,
name|dest
argument_list|,
name|samples
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

