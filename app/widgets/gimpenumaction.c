begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpenumaction.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpenumaction.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29e7b5e50103
block|{
DECL|enumerator|SELECTED
name|SELECTED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29e7b5e50203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_VALUE
name|PROP_VALUE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_enum_action_init
parameter_list|(
name|GimpEnumAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_enum_action_class_init
parameter_list|(
name|GimpEnumActionClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkActionClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|action_signals
specifier|static
name|guint
name|action_signals
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
name|GType
DECL|function|gimp_enum_action_get_type (void)
name|gimp_enum_action_get_type
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
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpEnumActionClass
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
name|gimp_enum_action_class_init
block|,
operator|(
name|GClassFinalizeFunc
operator|)
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpEnumAction
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_enum_action_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_ACTION
argument_list|,
literal|"GimpEnumAction"
argument_list|,
operator|&
name|type_info
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
DECL|function|gimp_enum_action_class_init (GimpEnumActionClass * klass)
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
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|action_signals
index|[
name|SELECTED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"selected"
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
name|GimpEnumActionClass
argument_list|,
name|selected
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_INT
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
block|{
name|action
operator|->
name|value
operator|=
literal|0
expr_stmt|;
block|}
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
DECL|function|gimp_enum_action_new (const gchar * name,const gchar * label,const gchar * tooltip,const gchar * stock_id,gint value)
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
name|stock_id
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
return|return
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
literal|"stock_id"
argument_list|,
name|stock_id
argument_list|,
literal|"value"
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
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
name|gimp_enum_action_selected
argument_list|(
name|enum_action
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_enum_action_selected (GimpEnumAction * action)
name|gimp_enum_action_selected
parameter_list|(
name|GimpEnumAction
modifier|*
name|action
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENUM_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|action
argument_list|,
name|action_signals
index|[
name|SELECTED
index|]
argument_list|,
literal|0
argument_list|,
name|action
operator|->
name|value
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

