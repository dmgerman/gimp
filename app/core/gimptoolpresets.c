begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolpresets.c  * Copyright (C) 2006 Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
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

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2af815e90103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TOOL_INFO
name|PROP_TOOL_INFO
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_tool_presets_finalize
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
name|gimp_tool_presets_set_property
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
name|gimp_tool_presets_get_property
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
DECL|function|G_DEFINE_TYPE (GimpToolPresets,gimp_tool_presets,GIMP_TYPE_LIST)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpToolPresets
argument_list|,
argument|gimp_tool_presets
argument_list|,
argument|GIMP_TYPE_LIST
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_presets_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tool_presets_class_init
parameter_list|(
name|GimpToolPresetsClass
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
name|gimp_tool_presets_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_tool_presets_get_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tool_presets_finalize
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TOOL_INFO
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"tool-info"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|G_PARAM_CONSTRUCT_ONLY
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_presets_init (GimpToolPresets * list)
name|gimp_tool_presets_init
parameter_list|(
name|GimpToolPresets
modifier|*
name|list
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_presets_finalize (GObject * object)
name|gimp_tool_presets_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolPresets
modifier|*
name|presets
init|=
name|GIMP_TOOL_PRESETS
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|presets
operator|->
name|tool_info
condition|)
block|{
name|g_object_unref
argument_list|(
name|presets
operator|->
name|tool_info
argument_list|)
expr_stmt|;
name|presets
operator|->
name|tool_info
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
DECL|function|gimp_tool_presets_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_tool_presets_set_property
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
name|GimpToolPresets
modifier|*
name|presets
init|=
name|GIMP_TOOL_PRESETS
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
name|PROP_TOOL_INFO
case|:
name|presets
operator|->
name|tool_info
operator|=
name|GIMP_TOOL_INFO
argument_list|(
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
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
DECL|function|gimp_tool_presets_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_tool_presets_get_property
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
name|GimpToolPresets
modifier|*
name|presets
init|=
name|GIMP_TOOL_PRESETS
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
name|PROP_TOOL_INFO
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|presets
operator|->
name|tool_info
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
name|GimpToolPresets
modifier|*
DECL|function|gimp_tool_presets_new (GimpToolInfo * tool_info)
name|gimp_tool_presets_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|GimpToolPresets
modifier|*
name|presets
decl_stmt|;
name|gchar
modifier|*
name|name
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
name|presets
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_PRESETS
argument_list|,
literal|"tool-info"
argument_list|,
name|tool_info
argument_list|,
literal|"children-type"
argument_list|,
name|tool_info
operator|->
name|tool_options_type
argument_list|,
literal|"policy"
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s options"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|presets
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|presets
return|;
block|}
end_function

begin_function
name|GimpToolOptions
modifier|*
DECL|function|gimp_tool_presets_get_options (GimpToolPresets * presets,gint index)
name|gimp_tool_presets_get_options
parameter_list|(
name|GimpToolPresets
modifier|*
name|presets
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_PRESETS
argument_list|(
name|presets
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
operator|(
name|GimpToolOptions
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|presets
argument_list|)
argument_list|,
name|index
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_presets_save (GimpToolPresets * presets,gboolean be_verbose,GError ** error)
name|gimp_tool_presets_save
parameter_list|(
name|GimpToolPresets
modifier|*
name|presets
parameter_list|,
name|gboolean
name|be_verbose
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gboolean
name|retval
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_PRESETS
argument_list|(
name|presets
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|presets
operator|->
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_tool_options_build_filename
argument_list|(
name|name
argument_list|,
literal|"presets"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_container_num_children
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|presets
argument_list|)
argument_list|)
operator|>
literal|0
condition|)
block|{
name|gchar
modifier|*
name|footer
decl_stmt|;
if|if
condition|(
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|footer
operator|=
name|g_strdup_printf
argument_list|(
literal|"end of %s"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|presets
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|presets
argument_list|)
argument_list|,
name|filename
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|presets
argument_list|)
operator|->
name|name
argument_list|,
name|footer
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|footer
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
if|if
condition|(
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Deleting '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_unlink
argument_list|(
name|filename
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|retval
operator|=
name|FALSE
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|g_file_error_from_errno
argument_list|(
name|errno
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Could not delete '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_presets_load (GimpToolPresets * presets,gboolean be_verbose,GError ** error)
name|gimp_tool_presets_load
parameter_list|(
name|GimpToolPresets
modifier|*
name|presets
parameter_list|,
name|gboolean
name|be_verbose
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gboolean
name|retval
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_PRESETS
argument_list|(
name|presets
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|presets
operator|->
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_tool_options_build_filename
argument_list|(
name|name
argument_list|,
literal|"presets"
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
if|if
condition|(
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|presets
argument_list|)
argument_list|,
name|filename
argument_list|,
name|presets
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|presets
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|presets
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|g_object_set
argument_list|(
name|list
operator|->
name|data
argument_list|,
literal|"tool-info"
argument_list|,
name|presets
operator|->
name|tool_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

end_unit

