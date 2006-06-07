begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGuide  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_comment
comment|/* strcmp */
end_comment

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
file|"libgimpbase/gimplimits.h"
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
file|"gimpguide.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28b8d2ea0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ID
name|PROP_ID
block|,
DECL|enumerator|PROP_ORIENTATION
name|PROP_ORIENTATION
block|,
DECL|enumerator|PROP_POSITION
name|PROP_POSITION
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_guide_get_property
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
name|gimp_guide_set_property
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
DECL|function|G_DEFINE_TYPE (GimpGuide,gimp_guide,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGuide
argument_list|,
argument|gimp_guide
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_guide_class_init
parameter_list|(
name|GimpGuideClass
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
name|gimp_guide_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_guide_set_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_ID
argument_list|,
literal|"id"
argument_list|,
name|N_
argument_list|(
literal|"Identifying number for the guide."
argument_list|)
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|G_PARAM_CONSTRUCT_ONLY
operator||
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_ORIENTATION
argument_list|,
literal|"orientation"
argument_list|,
name|N_
argument_list|(
literal|"Orientation of the guide."
argument_list|)
argument_list|,
name|GIMP_TYPE_ORIENTATION_TYPE
argument_list|,
name|GIMP_ORIENTATION_UNKNOWN
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_POSITION
argument_list|,
literal|"position"
argument_list|,
name|N_
argument_list|(
literal|"Offset of the guide."
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
operator|-
literal|1
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_guide_init (GimpGuide * guide)
name|gimp_guide_init
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_guide_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_guide_get_property
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
name|GimpGuide
modifier|*
name|guide
init|=
name|GIMP_GUIDE
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
name|PROP_ID
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|guide
operator|->
name|guide_ID
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ORIENTATION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|guide
operator|->
name|orientation
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_POSITION
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|guide
operator|->
name|position
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
DECL|function|gimp_guide_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_guide_set_property
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
name|GimpGuide
modifier|*
name|guide
init|=
name|GIMP_GUIDE
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
name|PROP_ID
case|:
name|guide
operator|->
name|guide_ID
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ORIENTATION
case|:
name|guide
operator|->
name|orientation
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_POSITION
case|:
name|guide
operator|->
name|position
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
name|GimpGuide
modifier|*
DECL|function|gimp_guide_new (GimpOrientationType orientation,guint32 guide_ID)
name|gimp_guide_new
parameter_list|(
name|GimpOrientationType
name|orientation
parameter_list|,
name|guint32
name|guide_ID
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_GUIDE
argument_list|,
literal|"id"
argument_list|,
name|guide_ID
argument_list|,
literal|"orientation"
argument_list|,
name|orientation
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|guint32
DECL|function|gimp_guide_get_ID (GimpGuide * guide)
name|gimp_guide_get_ID
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GUIDE
argument_list|(
name|guide
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|guide
operator|->
name|guide_ID
return|;
block|}
end_function

begin_function
name|GimpOrientationType
DECL|function|gimp_guide_get_orientation (GimpGuide * guide)
name|gimp_guide_get_orientation
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GUIDE
argument_list|(
name|guide
argument_list|)
argument_list|,
name|GIMP_ORIENTATION_UNKNOWN
argument_list|)
expr_stmt|;
return|return
name|guide
operator|->
name|orientation
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_guide_set_orientation (GimpGuide * guide,GimpOrientationType orientation)
name|gimp_guide_set_orientation
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GUIDE
argument_list|(
name|guide
argument_list|)
argument_list|)
expr_stmt|;
name|guide
operator|->
name|orientation
operator|=
name|orientation
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|guide
argument_list|)
argument_list|,
literal|"orientation"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_guide_get_position (GimpGuide * guide)
name|gimp_guide_get_position
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GUIDE
argument_list|(
name|guide
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|guide
operator|->
name|position
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_guide_set_position (GimpGuide * guide,gint position)
name|gimp_guide_set_position
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|gint
name|position
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GUIDE
argument_list|(
name|guide
argument_list|)
argument_list|)
expr_stmt|;
name|guide
operator|->
name|position
operator|=
name|position
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|guide
argument_list|)
argument_list|,
literal|"position"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

