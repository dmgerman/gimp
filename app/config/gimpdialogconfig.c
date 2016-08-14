begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDialogConfig class  * Copyright (C) 2016  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimprc-blurbs.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b26f8450103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_COLOR_PROFILE_POLICY
name|PROP_COLOR_PROFILE_POLICY
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_dialog_config_set_property
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
name|gimp_dialog_config_get_property
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDialogConfig,gimp_dialog_config,GIMP_TYPE_GUI_CONFIG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDialogConfig
argument_list|,
argument|gimp_dialog_config
argument_list|,
argument|GIMP_TYPE_GUI_CONFIG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dialog_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_dialog_config_class_init
parameter_list|(
name|GimpDialogConfigClass
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
name|gimp_dialog_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dialog_config_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR_PROFILE_POLICY
argument_list|,
literal|"color-profile-policy"
argument_list|,
literal|"Color profile policy"
argument_list|,
name|COLOR_PROFILE_POLICY_BLURB
argument_list|,
name|GIMP_TYPE_COLOR_PROFILE_POLICY
argument_list|,
name|GIMP_COLOR_PROFILE_POLICY_ASK
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dialog_config_init (GimpDialogConfig * config)
name|gimp_dialog_config_init
parameter_list|(
name|GimpDialogConfig
modifier|*
name|config
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dialog_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dialog_config_set_property
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
name|GimpDialogConfig
modifier|*
name|dialog_config
init|=
name|GIMP_DIALOG_CONFIG
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
name|PROP_COLOR_PROFILE_POLICY
case|:
name|dialog_config
operator|->
name|color_profile_policy
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
specifier|static
name|void
DECL|function|gimp_dialog_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dialog_config_get_property
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
name|GimpDialogConfig
modifier|*
name|dialog_config
init|=
name|GIMP_DIALOG_CONFIG
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
name|PROP_COLOR_PROFILE_POLICY
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|dialog_config
operator|->
name|color_profile_policy
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

end_unit

