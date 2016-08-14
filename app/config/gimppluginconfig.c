begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpPluginConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimppluginconfig.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2bf1d9dd0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_FRACTALEXPLORER_PATH
name|PROP_FRACTALEXPLORER_PATH
block|,
DECL|enumerator|PROP_GFIG_PATH
name|PROP_GFIG_PATH
block|,
DECL|enumerator|PROP_GFLARE_PATH
name|PROP_GFLARE_PATH
block|,
DECL|enumerator|PROP_GIMPRESSIONIST_PATH
name|PROP_GIMPRESSIONIST_PATH
block|,
DECL|enumerator|PROP_SCRIPT_FU_PATH
name|PROP_SCRIPT_FU_PATH
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_plugin_config_finalize
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
name|gimp_plugin_config_set_property
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
name|gimp_plugin_config_get_property
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
DECL|function|G_DEFINE_TYPE (GimpPluginConfig,gimp_plugin_config,GIMP_TYPE_DIALOG_CONFIG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPluginConfig
argument_list|,
argument|gimp_plugin_config
argument_list|,
argument|GIMP_TYPE_DIALOG_CONFIG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_plugin_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_plugin_config_class_init
parameter_list|(
name|GimpPluginConfigClass
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
name|gchar
modifier|*
name|path
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_plugin_config_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_plugin_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_plugin_config_get_property
expr_stmt|;
name|path
operator|=
name|gimp_config_build_data_path
argument_list|(
literal|"fractalexplorer"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_FRACTALEXPLORER_PATH
argument_list|,
literal|"fractalexplorer-path"
argument_list|,
literal|"Fractal Explorer path"
argument_list|,
name|FRACTALEXPLORER_PATH_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_DIR_LIST
argument_list|,
name|path
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_config_build_data_path
argument_list|(
literal|"gfig"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_GFIG_PATH
argument_list|,
literal|"gfig-path"
argument_list|,
literal|"GFig path"
argument_list|,
name|GFIG_PATH_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_DIR_LIST
argument_list|,
name|path
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_config_build_data_path
argument_list|(
literal|"gflare"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_GFLARE_PATH
argument_list|,
literal|"gflare-path"
argument_list|,
literal|"GFlare path"
argument_list|,
name|GFLARE_PATH_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_DIR_LIST
argument_list|,
name|path
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_config_build_data_path
argument_list|(
literal|"gimpressionist"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_GIMPRESSIONIST_PATH
argument_list|,
literal|"gimpressionist-path"
argument_list|,
literal|"GIMPressionist path"
argument_list|,
name|GIMPRESSIONIST_PATH_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_DIR_LIST
argument_list|,
name|path
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_config_build_data_path
argument_list|(
literal|"scripts"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_SCRIPT_FU_PATH
argument_list|,
literal|"script-fu-path"
argument_list|,
literal|"Script-Fu path"
argument_list|,
name|SCRIPT_FU_PATH_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_DIR_LIST
argument_list|,
name|path
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plugin_config_init (GimpPluginConfig * config)
name|gimp_plugin_config_init
parameter_list|(
name|GimpPluginConfig
modifier|*
name|config
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plugin_config_finalize (GObject * object)
name|gimp_plugin_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPluginConfig
modifier|*
name|plugin_config
init|=
name|GIMP_PLUGIN_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|plugin_config
operator|->
name|fractalexplorer_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|plugin_config
operator|->
name|gfig_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|plugin_config
operator|->
name|gflare_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|plugin_config
operator|->
name|gimpressionist_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|plugin_config
operator|->
name|script_fu_path
argument_list|)
expr_stmt|;
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
DECL|function|gimp_plugin_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_plugin_config_set_property
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
name|GimpPluginConfig
modifier|*
name|plugin_config
init|=
name|GIMP_PLUGIN_CONFIG
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
name|PROP_FRACTALEXPLORER_PATH
case|:
name|g_free
argument_list|(
name|plugin_config
operator|->
name|fractalexplorer_path
argument_list|)
expr_stmt|;
name|plugin_config
operator|->
name|fractalexplorer_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GFIG_PATH
case|:
name|g_free
argument_list|(
name|plugin_config
operator|->
name|gfig_path
argument_list|)
expr_stmt|;
name|plugin_config
operator|->
name|gfig_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GFLARE_PATH
case|:
name|g_free
argument_list|(
name|plugin_config
operator|->
name|gflare_path
argument_list|)
expr_stmt|;
name|plugin_config
operator|->
name|gflare_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GIMPRESSIONIST_PATH
case|:
name|g_free
argument_list|(
name|plugin_config
operator|->
name|gimpressionist_path
argument_list|)
expr_stmt|;
name|plugin_config
operator|->
name|gimpressionist_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SCRIPT_FU_PATH
case|:
name|g_free
argument_list|(
name|plugin_config
operator|->
name|script_fu_path
argument_list|)
expr_stmt|;
name|plugin_config
operator|->
name|script_fu_path
operator|=
name|g_value_dup_string
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
DECL|function|gimp_plugin_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_plugin_config_get_property
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
name|GimpPluginConfig
modifier|*
name|plugin_config
init|=
name|GIMP_PLUGIN_CONFIG
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
name|PROP_FRACTALEXPLORER_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|plugin_config
operator|->
name|fractalexplorer_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GFIG_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|plugin_config
operator|->
name|gfig_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GFLARE_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|plugin_config
operator|->
name|gflare_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GIMPRESSIONIST_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|plugin_config
operator|->
name|gimpressionist_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SCRIPT_FU_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|plugin_config
operator|->
name|script_fu_path
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

