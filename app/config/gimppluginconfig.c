begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpPluginConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

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
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-utils.h"
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

begin_function_decl
specifier|static
name|void
name|gimp_plugin_config_class_init
parameter_list|(
name|GimpPluginConfigClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

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

begin_enum
enum|enum
DECL|enum|__anon28b7a3290103
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
block|, }
enum|;
end_enum

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_plugin_config_get_type (void)
name|gimp_plugin_config_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|config_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|config_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|config_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPluginConfigClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
operator|(
name|GClassInitFunc
operator|)
name|gimp_plugin_config_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPluginConfig
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|config_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_GUI_CONFIG
argument_list|,
literal|"GimpPluginConfig"
argument_list|,
operator|&
name|config_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|config_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plugin_config_class_init (GimpPluginConfigClass * klass)
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
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_FRACTALEXPLORER_PATH
argument_list|,
literal|"fractalexplorer-path"
argument_list|,
name|FRACTALEXPLORER_PATH_BLURB
argument_list|,
name|gimp_config_build_data_path
argument_list|(
literal|"fractalexplorer"
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_GFIG_PATH
argument_list|,
literal|"gfig-path"
argument_list|,
name|GFIG_PATH_BLURB
argument_list|,
name|gimp_config_build_data_path
argument_list|(
literal|"gfig"
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_GFLARE_PATH
argument_list|,
literal|"gflare-path"
argument_list|,
name|GFLARE_PATH_BLURB
argument_list|,
name|gimp_config_build_data_path
argument_list|(
literal|"gflare"
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_GIMPRESSIONIST_PATH
argument_list|,
literal|"gimpressionist-path"
argument_list|,
name|GIMPRESSIONIST_PATH_BLURB
argument_list|,
name|gimp_config_build_data_path
argument_list|(
literal|"gimpressionist"
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
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
decl_stmt|;
name|plugin_config
operator|=
name|GIMP_PLUGIN_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|plugin_config
operator|=
name|GIMP_PLUGIN_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|plugin_config
operator|=
name|GIMP_PLUGIN_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
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

