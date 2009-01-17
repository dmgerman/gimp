begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolpresets.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b406aed0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_VISIBLE
name|PROP_VISIBLE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_tool_info_finalize
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
name|gimp_tool_info_get_property
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
name|gimp_tool_info_set_property
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
name|gchar
modifier|*
name|gimp_tool_info_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpToolInfo,gimp_tool_info,GIMP_TYPE_VIEWABLE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpToolInfo
argument_list|,
argument|gimp_tool_info
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_info_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tool_info_class_init
parameter_list|(
name|GimpToolInfoClass
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
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tool_info_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_tool_info_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_tool_info_set_property
expr_stmt|;
name|viewable_class
operator|->
name|get_description
operator|=
name|gimp_tool_info_get_description
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_VISIBLE
argument_list|,
literal|"visible"
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_info_init (GimpToolInfo * tool_info)
name|gimp_tool_info_init
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|tool_info
operator|->
name|gimp
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|tool_type
operator|=
name|G_TYPE_NONE
expr_stmt|;
name|tool_info
operator|->
name|tool_options_type
operator|=
name|G_TYPE_NONE
expr_stmt|;
name|tool_info
operator|->
name|context_props
operator|=
literal|0
expr_stmt|;
name|tool_info
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|help
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|menu_path
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|menu_accel
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|help_domain
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|help_id
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|visible
operator|=
name|TRUE
expr_stmt|;
name|tool_info
operator|->
name|tool_options
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|paint_info
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_info_finalize (GObject * object)
name|gimp_tool_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|GIMP_TOOL_INFO
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|blurb
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|help
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|help
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|menu_path
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|menu_path
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|menu_accel
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|menu_accel
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|menu_accel
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|help_domain
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|help_domain
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|help_domain
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|help_id
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|help_id
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|help_id
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|tool_options
condition|)
block|{
name|g_object_unref
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|tool_options
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|presets
condition|)
block|{
name|g_object_unref
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|presets
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
DECL|function|gimp_tool_info_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_tool_info_get_property
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
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|GIMP_TOOL_INFO
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
name|PROP_VISIBLE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|tool_info
operator|->
name|visible
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
DECL|function|gimp_tool_info_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_tool_info_set_property
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
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|GIMP_TOOL_INFO
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
name|PROP_VISIBLE
case|:
name|tool_info
operator|->
name|visible
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
name|gchar
modifier|*
DECL|function|gimp_tool_info_get_description (GimpViewable * viewable,gchar ** tooltip)
name|gimp_tool_info_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|GIMP_TOOL_INFO
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
return|return
name|g_strdup
argument_list|(
name|tool_info
operator|->
name|blurb
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpToolInfo
modifier|*
DECL|function|gimp_tool_info_new (Gimp * gimp,GType tool_type,GType tool_options_type,GimpContextPropMask context_props,const gchar * identifier,const gchar * blurb,const gchar * help,const gchar * menu_path,const gchar * menu_accel,const gchar * help_domain,const gchar * help_id,const gchar * paint_core_name,const gchar * stock_id)
name|gimp_tool_info_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|tool_type
parameter_list|,
name|GType
name|tool_options_type
parameter_list|,
name|GimpContextPropMask
name|context_props
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_accel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|paint_core_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|identifier
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|blurb
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|paint_core_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|stock_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|paint_info
operator|=
operator|(
name|GimpPaintInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|paint_info_list
argument_list|,
name|paint_core_name
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_INFO
argument_list|(
name|paint_info
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_INFO
argument_list|,
literal|"name"
argument_list|,
name|identifier
argument_list|,
literal|"stock-id"
argument_list|,
name|stock_id
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|tool_info
operator|->
name|tool_type
operator|=
name|tool_type
expr_stmt|;
name|tool_info
operator|->
name|tool_options_type
operator|=
name|tool_options_type
expr_stmt|;
name|tool_info
operator|->
name|context_props
operator|=
name|context_props
expr_stmt|;
name|tool_info
operator|->
name|blurb
operator|=
name|g_strdup
argument_list|(
name|blurb
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|help
operator|=
name|g_strdup
argument_list|(
name|help
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|menu_path
operator|=
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|menu_accel
operator|=
name|g_strdup
argument_list|(
name|menu_accel
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|help_domain
operator|=
name|g_strdup
argument_list|(
name|help_domain
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|help_id
operator|=
name|g_strdup
argument_list|(
name|help_id
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|paint_info
operator|=
name|paint_info
expr_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|tool_options_type
operator|==
name|paint_info
operator|->
name|paint_options_type
condition|)
block|{
name|tool_info
operator|->
name|tool_options
operator|=
name|g_object_ref
argument_list|(
name|paint_info
operator|->
name|paint_options
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tool_info
operator|->
name|tool_options
operator|=
name|g_object_new
argument_list|(
name|tool_info
operator|->
name|tool_options_type
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"name"
argument_list|,
name|identifier
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_object_set
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|,
literal|"tool-info"
argument_list|,
name|tool_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|context_props
condition|)
block|{
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|tool_info
operator|->
name|context_props
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gimp_context_set_serialize_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|tool_info
operator|->
name|context_props
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|tool_options_type
operator|!=
name|GIMP_TYPE_TOOL_OPTIONS
condition|)
block|{
name|tool_info
operator|->
name|presets
operator|=
name|gimp_tool_presets_new
argument_list|(
name|tool_info
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_info
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_info_set_standard (Gimp * gimp,GimpToolInfo * tool_info)
name|gimp_tool_info_set_standard
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|tool_info
operator|||
name|GIMP_IS_TOOL_INFO
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|!=
name|gimp
operator|->
name|standard_tool_info
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|standard_tool_info
condition|)
name|g_object_unref
argument_list|(
name|gimp
operator|->
name|standard_tool_info
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|standard_tool_info
operator|=
name|tool_info
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|standard_tool_info
condition|)
name|g_object_ref
argument_list|(
name|gimp
operator|->
name|standard_tool_info
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpToolInfo
modifier|*
DECL|function|gimp_tool_info_get_standard (Gimp * gimp)
name|gimp_tool_info_get_standard
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp
operator|->
name|standard_tool_info
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_tool_info_build_options_filename (GimpToolInfo * tool_info,const gchar * suffix)
name|gimp_tool_info_build_options_filename
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
specifier|const
name|gchar
modifier|*
name|suffix
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_INFO
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|suffix
condition|)
name|basename
operator|=
name|g_strconcat
argument_list|(
name|name
argument_list|,
name|suffix
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|basename
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
literal|"tool-options"
argument_list|,
name|basename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
return|return
name|filename
return|;
block|}
end_function

end_unit

