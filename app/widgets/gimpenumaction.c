begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpenumaction.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"gimpaction-history.h"
end_include

begin_include
include|#
directive|include
file|"gimpenumaction.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c4b8d430103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_VALUE
name|PROP_VALUE
block|,
DECL|enumerator|PROP_VALUE_VARIABLE
name|PROP_VALUE_VARIABLE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_enum_action_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|gimp_enum_action_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|gimp_enum_action_activate
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpEnumAction,gimp_enum_action,GIMP_TYPE_ACTION_IMPL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpEnumAction
argument_list|,
argument|gimp_enum_action
argument_list|,
argument|GIMP_TYPE_ACTION_IMPL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_enum_action_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_enum_action_class_init
parameter_list|(
name|GimpEnumActionClass
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
name|GtkActionClass
modifier|*
name|action_class
init|=
name|GTK_ACTION_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_enum_action_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_enum_action_get_property
expr_stmt|;
name|action_class
operator|->
name|activate
operator|=
name|gimp_enum_action_activate
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VALUE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"value"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VALUE_VARIABLE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"value-variable"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_action_init (GimpEnumAction * action)
name|gimp_enum_action_init
parameter_list|(
name|GimpEnumAction
modifier|*
name|action
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_action_get_property (GObject * object,guint prop_id,GValue * value,GParamSpec * pspec)
name|gimp_enum_action_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GimpEnumAction
modifier|*
name|action
init|=
name|GIMP_ENUM_ACTION
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|prop_id
condition|)
block|{
case|case
name|PROP_VALUE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|action
operator|->
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VALUE_VARIABLE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|action
operator|->
name|value_variable
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|prop_id
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
DECL|function|gimp_enum_action_set_property (GObject * object,guint prop_id,const GValue * value,GParamSpec * pspec)
name|gimp_enum_action_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GimpEnumAction
modifier|*
name|action
init|=
name|GIMP_ENUM_ACTION
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|prop_id
condition|)
block|{
case|case
name|PROP_VALUE
case|:
name|action
operator|->
name|value
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VALUE_VARIABLE
case|:
name|action
operator|->
name|value_variable
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
name|prop_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|GimpEnumAction
modifier|*
DECL|function|gimp_enum_action_new (const gchar * name,const gchar * label,const gchar * tooltip,const gchar * icon_name,const gchar * help_id,gint value,gboolean value_variable)
name|gimp_enum_action_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gint
name|value
parameter_list|,
name|gboolean
name|value_variable
parameter_list|)
block|{
name|GimpEnumAction
modifier|*
name|action
decl_stmt|;
name|action
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_ACTION
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"label"
argument_list|,
name|label
argument_list|,
literal|"tooltip"
argument_list|,
name|tooltip
argument_list|,
literal|"icon-name"
argument_list|,
name|icon_name
argument_list|,
literal|"value"
argument_list|,
name|value
argument_list|,
literal|"value-variable"
argument_list|,
name|value_variable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_action_set_help_id
argument_list|(
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
return|return
name|action
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_action_activate (GtkAction * action)
name|gimp_enum_action_activate
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|)
block|{
name|GimpEnumAction
modifier|*
name|enum_action
init|=
name|GIMP_ENUM_ACTION
argument_list|(
name|action
argument_list|)
decl_stmt|;
name|gimp_action_emit_activate
argument_list|(
name|GIMP_ACTION
argument_list|(
name|enum_action
argument_list|)
argument_list|,
name|g_variant_new_int32
argument_list|(
name|enum_action
operator|->
name|value
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_history_action_activated
argument_list|(
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

