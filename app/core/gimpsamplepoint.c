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
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpsamplepoint.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29e7b8830103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_POSITION_X
name|PROP_POSITION_X
block|,
DECL|enumerator|PROP_POSITION_Y
name|PROP_POSITION_Y
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpSamplePointPrivate
struct|struct
name|_GimpSamplePointPrivate
block|{
DECL|member|position_x
name|gint
name|position_x
decl_stmt|;
DECL|member|position_y
name|gint
name|position_y
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_get_property
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
name|gimp_sample_point_set_property
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSamplePoint,gimp_sample_point,GIMP_TYPE_AUX_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSamplePoint
argument_list|,
argument|gimp_sample_point
argument_list|,
argument|GIMP_TYPE_AUX_ITEM
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_sample_point_class_init
parameter_list|(
name|GimpSamplePointClass
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
name|get_property
operator|=
name|gimp_sample_point_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_sample_point_set_property
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_POSITION_X
argument_list|,
literal|"position-x"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_SAMPLE_POINT_POSITION_UNDEFINED
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_SAMPLE_POINT_POSITION_UNDEFINED
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_POSITION_Y
argument_list|,
literal|"position-y"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_SAMPLE_POINT_POSITION_UNDEFINED
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_SAMPLE_POINT_POSITION_UNDEFINED
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpSamplePointPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_init (GimpSamplePoint * sample_point)
name|gimp_sample_point_init
parameter_list|(
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
block|{
name|sample_point
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|sample_point
argument_list|,
name|GIMP_TYPE_SAMPLE_POINT
argument_list|,
name|GimpSamplePointPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_sample_point_get_property
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
name|GimpSamplePoint
modifier|*
name|sample_point
init|=
name|GIMP_SAMPLE_POINT
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
name|PROP_POSITION_X
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|sample_point
operator|->
name|priv
operator|->
name|position_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_POSITION_Y
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|sample_point
operator|->
name|priv
operator|->
name|position_y
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
DECL|function|gimp_sample_point_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_sample_point_set_property
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
name|GimpSamplePoint
modifier|*
name|sample_point
init|=
name|GIMP_SAMPLE_POINT
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
name|PROP_POSITION_X
case|:
name|sample_point
operator|->
name|priv
operator|->
name|position_x
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_POSITION_Y
case|:
name|sample_point
operator|->
name|priv
operator|->
name|position_y
operator|=
name|g_value_get_int
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
name|GimpSamplePoint
modifier|*
DECL|function|gimp_sample_point_new (guint32 sample_point_ID)
name|gimp_sample_point_new
parameter_list|(
name|guint32
name|sample_point_ID
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_SAMPLE_POINT
argument_list|,
literal|"id"
argument_list|,
name|sample_point_ID
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_sample_point_get_position (GimpSamplePoint * sample_point,gint * position_x,gint * position_y)
name|gimp_sample_point_get_position
parameter_list|(
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|gint
modifier|*
name|position_x
parameter_list|,
name|gint
modifier|*
name|position_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SAMPLE_POINT
argument_list|(
name|sample_point
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|position_x
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|position_y
operator|!=
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|position_x
operator|=
name|sample_point
operator|->
name|priv
operator|->
name|position_x
expr_stmt|;
operator|*
name|position_y
operator|=
name|sample_point
operator|->
name|priv
operator|->
name|position_y
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_sample_point_set_position (GimpSamplePoint * sample_point,gint position_x,gint position_y)
name|gimp_sample_point_set_position
parameter_list|(
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|gint
name|position_x
parameter_list|,
name|gint
name|position_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SAMPLE_POINT
argument_list|(
name|sample_point
argument_list|)
argument_list|)
expr_stmt|;
name|sample_point
operator|->
name|priv
operator|->
name|position_x
operator|=
name|position_x
expr_stmt|;
name|sample_point
operator|->
name|priv
operator|->
name|position_y
operator|=
name|position_y
expr_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|sample_point
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|sample_point
argument_list|)
argument_list|,
literal|"position-x"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|sample_point
argument_list|)
argument_list|,
literal|"position-y"
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|sample_point
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

