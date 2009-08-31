begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagemapconfig.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpimagemapconfig.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2aa8977f0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TIME
name|PROP_TIME
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_image_map_config_get_property
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
name|gimp_image_map_config_set_property
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
DECL|function|G_DEFINE_TYPE (GimpImageMapConfig,gimp_image_map_config,GIMP_TYPE_VIEWABLE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpImageMapConfig
argument_list|,
argument|gimp_image_map_config
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_map_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_image_map_config_class_init
parameter_list|(
name|GimpImageMapConfigClass
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
name|set_property
operator|=
name|gimp_image_map_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_image_map_config_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UINT
argument_list|(
name|object_class
argument_list|,
name|PROP_TIME
argument_list|,
literal|"time"
argument_list|,
literal|"Time of settings creation"
argument_list|,
literal|0
argument_list|,
name|G_MAXUINT
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_config_init (GimpImageMapConfig * config)
name|gimp_image_map_config_init
parameter_list|(
name|GimpImageMapConfig
modifier|*
name|config
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_image_map_config_get_property
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
name|GimpImageMapConfig
modifier|*
name|config
init|=
name|GIMP_IMAGE_MAP_CONFIG
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
name|PROP_TIME
case|:
name|g_value_set_uint
argument_list|(
name|value
argument_list|,
name|config
operator|->
name|time
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
DECL|function|gimp_image_map_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_image_map_config_set_property
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
name|GimpImageMapConfig
modifier|*
name|config
init|=
name|GIMP_IMAGE_MAP_CONFIG
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
name|PROP_TIME
case|:
name|config
operator|->
name|time
operator|=
name|g_value_get_uint
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|time
operator|>
literal|0
condition|)
block|{
name|time_t
name|t
decl_stmt|;
name|struct
name|tm
name|tm
decl_stmt|;
name|gchar
name|buf
index|[
literal|64
index|]
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|t
operator|=
name|config
operator|->
name|time
expr_stmt|;
name|tm
operator|=
operator|*
name|localtime
argument_list|(
operator|&
name|t
argument_list|)
expr_stmt|;
name|strftime
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%Y-%m-%d %T"
argument_list|,
operator|&
name|tm
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_locale_to_utf8
argument_list|(
name|buf
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gint
DECL|function|gimp_image_map_config_compare (GimpImageMapConfig * a,GimpImageMapConfig * b)
name|gimp_image_map_config_compare
parameter_list|(
name|GimpImageMapConfig
modifier|*
name|a
parameter_list|,
name|GimpImageMapConfig
modifier|*
name|b
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name_a
init|=
name|gimp_object_get_name
argument_list|(
name|a
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name_b
init|=
name|gimp_object_get_name
argument_list|(
name|b
argument_list|)
decl_stmt|;
if|if
condition|(
name|a
operator|->
name|time
operator|>
literal|0
operator|&&
name|b
operator|->
name|time
operator|>
literal|0
condition|)
block|{
return|return
operator|-
name|strcmp
argument_list|(
name|name_a
argument_list|,
name|name_b
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|a
operator|->
name|time
operator|>
literal|0
condition|)
block|{
return|return
operator|-
literal|1
return|;
block|}
elseif|else
if|if
condition|(
name|b
operator|->
name|time
operator|>
literal|0
condition|)
block|{
return|return
literal|1
return|;
block|}
elseif|else
if|if
condition|(
name|name_a
operator|&&
name|name_b
condition|)
block|{
return|return
name|strcmp
argument_list|(
name|name_a
argument_list|,
name|name_b
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|name_a
condition|)
block|{
return|return
literal|1
return|;
block|}
elseif|else
if|if
condition|(
name|name_b
condition|)
block|{
return|return
operator|-
literal|1
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

end_unit

