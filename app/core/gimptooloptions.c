begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b1e146c0103
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
name|gimp_tool_options_init
parameter_list|(
name|GimpToolOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_class_init
parameter_list|(
name|GimpToolOptionsClass
modifier|*
name|options_class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_set_property
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
name|gimp_tool_options_get_property
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
name|gimp_tool_options_real_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpContextClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_tool_options_get_type (void)
name|gimp_tool_options_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpToolOptionsClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_tool_options_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpToolOptions
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_tool_options_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_CONTEXT
argument_list|,
literal|"GimpToolOptions"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_class_init (GimpToolOptionsClass * klass)
name|gimp_tool_options_class_init
parameter_list|(
name|GimpToolOptionsClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_tool_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_tool_options_get_property
expr_stmt|;
name|klass
operator|->
name|reset
operator|=
name|gimp_tool_options_real_reset
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
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_init (GimpToolOptions * options)
name|gimp_tool_options_init
parameter_list|(
name|GimpToolOptions
modifier|*
name|options
parameter_list|)
block|{
name|options
operator|->
name|tool_info
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_tool_options_set_property
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
name|GimpToolOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_TOOL_OPTIONS
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
name|PROP_TOOL_INFO
case|:
name|options
operator|->
name|tool_info
operator|=
name|g_value_get_object
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
DECL|function|gimp_tool_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_tool_options_get_property
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
name|GimpToolOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_TOOL_OPTIONS
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
name|PROP_TOOL_INFO
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|options
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
specifier|static
name|void
DECL|function|gimp_tool_options_real_reset (GimpToolOptions * tool_options)
name|gimp_tool_options_real_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|gimp_config_reset
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_options_reset (GimpToolOptions * tool_options)
name|gimp_tool_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_OPTIONS
argument_list|(
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_TOOL_OPTIONS_GET_CLASS
argument_list|(
name|tool_options
argument_list|)
operator|->
name|reset
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_tool_options_build_filename (GimpToolOptions * tool_options,const gchar * extension)
name|gimp_tool_options_build_filename
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|)
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
if|if
condition|(
name|extension
condition|)
block|{
name|basename
operator|=
name|g_strconcat
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|tool_options
operator|->
name|tool_info
argument_list|)
operator|->
name|name
argument_list|,
literal|"."
argument_list|,
name|extension
argument_list|,
name|NULL
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
block|}
else|else
block|{
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
literal|"tool-options"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_options
operator|->
name|tool_info
argument_list|)
operator|->
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|filename
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_options_serialize (GimpToolOptions * tool_options,const gchar * extension,GError ** error)
name|gimp_tool_options_serialize
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_OPTIONS
argument_list|(
name|tool_options
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
name|filename
operator|=
name|gimp_tool_options_build_filename
argument_list|(
name|tool_options
argument_list|,
name|extension
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp_config_serialize
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
argument_list|,
name|filename
argument_list|,
literal|"# tool options\n"
argument_list|,
literal|"# end tool options"
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
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
DECL|function|gimp_tool_options_deserialize (GimpToolOptions * tool_options,const gchar * extension,GError ** error)
name|gimp_tool_options_deserialize
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_OPTIONS
argument_list|(
name|tool_options
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
name|filename
operator|=
name|gimp_tool_options_build_filename
argument_list|(
name|tool_options
argument_list|,
name|extension
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp_config_deserialize
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
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
name|gpointer
DECL|function|gimp_tool_options_gui (GimpToolOptions * tool_options)
name|gimp_tool_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

