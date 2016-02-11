begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGuide  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"gimpmarshal.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a30e0c00103
block|{
DECL|enumerator|REMOVED
name|REMOVED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a30e0c00203
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
block|,
DECL|enumerator|PROP_STYLE
name|PROP_STYLE
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpGuidePrivate
struct|struct
name|_GimpGuidePrivate
block|{
DECL|member|guide_ID
name|guint32
name|guide_ID
decl_stmt|;
DECL|member|orientation
name|GimpOrientationType
name|orientation
decl_stmt|;
DECL|member|position
name|gint
name|position
decl_stmt|;
DECL|member|style
name|GimpGuideStyle
name|style
decl_stmt|;
block|}
struct|;
end_struct

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
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGuide
argument_list|,
argument|gimp_guide
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|guint
name|gimp_guide_signals
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
DECL|function|gimp_guide_class_init (GimpGuideClass * klass)
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
name|gimp_guide_signals
index|[
name|REMOVED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"removed"
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
name|GimpGuideClass
argument_list|,
name|removed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
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
name|klass
operator|->
name|removed
operator|=
name|NULL
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ID
argument_list|,
name|g_param_spec_uint
argument_list|(
literal|"id"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXUINT32
argument_list|,
literal|0
argument_list|,
name|G_PARAM_CONSTRUCT_ONLY
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_ORIENTATION
argument_list|,
literal|"orientation"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_ORIENTATION_TYPE
argument_list|,
name|GIMP_ORIENTATION_UNKNOWN
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_POSITION
argument_list|,
literal|"position"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_GUIDE_POSITION_UNDEFINED
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_GUIDE_POSITION_UNDEFINED
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_STYLE
argument_list|,
literal|"style"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GUIDE_STYLE
argument_list|,
name|GIMP_GUIDE_STYLE_NONE
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
name|GimpGuidePrivate
argument_list|)
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
block|{
name|guide
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|guide
argument_list|,
name|GIMP_TYPE_GUIDE
argument_list|,
name|GimpGuidePrivate
argument_list|)
expr_stmt|;
block|}
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
name|g_value_set_uint
argument_list|(
name|value
argument_list|,
name|guide
operator|->
name|priv
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
name|priv
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
name|priv
operator|->
name|position
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|guide
operator|->
name|priv
operator|->
name|style
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
name|priv
operator|->
name|guide_ID
operator|=
name|g_value_get_uint
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
name|priv
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
name|priv
operator|->
name|position
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STYLE
case|:
name|guide
operator|->
name|priv
operator|->
name|style
operator|=
name|g_value_get_enum
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
literal|"style"
argument_list|,
name|GIMP_GUIDE_STYLE_NORMAL
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_guide_custom_new:  * @orientation:       the #GimpOrientationType  * @guide_ID:          the unique guide ID  * @guide_style:       the #GimpGuideStyle  *  * This function returns a new guide and will flag it as "custom".  * Custom guides are used for purpose "other" than the basic guides  * a user can create oneself, for instance as symmetry guides, to  * drive GEGL ops, etc.  * They are not saved in the XCF file. If an op, a symmetry or a plugin  * wishes to save its state, it has to do it internally.  * Moreover they don't follow guide snapping settings and never snap.  *  * Returns: the custom #GimpGuide.  **/
end_comment

begin_function
name|GimpGuide
modifier|*
DECL|function|gimp_guide_custom_new (GimpOrientationType orientation,guint32 guide_ID,GimpGuideStyle guide_style)
name|gimp_guide_custom_new
parameter_list|(
name|GimpOrientationType
name|orientation
parameter_list|,
name|guint32
name|guide_ID
parameter_list|,
name|GimpGuideStyle
name|guide_style
parameter_list|)
block|{
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|guide
operator|=
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
literal|"style"
argument_list|,
name|guide_style
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|guide
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
name|priv
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
name|priv
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
name|priv
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
name|GIMP_GUIDE_POSITION_UNDEFINED
argument_list|)
expr_stmt|;
return|return
name|guide
operator|->
name|priv
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
name|priv
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

begin_function
name|void
DECL|function|gimp_guide_removed (GimpGuide * guide)
name|gimp_guide_removed
parameter_list|(
name|GimpGuide
modifier|*
name|guide
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
name|g_signal_emit
argument_list|(
name|guide
argument_list|,
name|gimp_guide_signals
index|[
name|REMOVED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpGuideStyle
DECL|function|gimp_guide_get_style (GimpGuide * guide)
name|gimp_guide_get_style
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
block|{
return|return
name|guide
operator|->
name|priv
operator|->
name|style
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_guide_is_custom (GimpGuide * guide)
name|gimp_guide_is_custom
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
block|{
return|return
operator|(
name|guide
operator|->
name|priv
operator|->
name|style
operator|!=
name|GIMP_GUIDE_STYLE_NORMAL
operator|)
return|;
block|}
end_function

end_unit

