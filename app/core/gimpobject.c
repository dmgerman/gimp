begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29d86cf60103
block|{
DECL|enumerator|NAME_CHANGED
name|NAME_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29d86cf60203
block|{
DECL|enumerator|ARG_0
name|ARG_0
block|,
DECL|enumerator|ARG_NAME
name|ARG_NAME
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_object_class_init
parameter_list|(
name|GimpObjectClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_object_init
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_object_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_object_set_arg
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkArg
modifier|*
name|arg
parameter_list|,
name|guint
name|arg_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_object_get_arg
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkArg
modifier|*
name|arg
parameter_list|,
name|guint
name|arg_id
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|object_signals
specifier|static
name|guint
name|object_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_object_get_type (void)
name|gimp_object_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|object_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|object_type
condition|)
block|{
name|GtkTypeInfo
name|object_info
init|=
block|{
literal|"GimpObject"
block|,
sizeof|sizeof
argument_list|(
name|GimpObject
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpObjectClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_object_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_object_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|object_type
operator|=
name|gtk_type_unique
argument_list|(
name|GTK_TYPE_OBJECT
argument_list|,
operator|&
name|object_info
argument_list|)
expr_stmt|;
block|}
return|return
name|object_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_object_class_init (GimpObjectClass * klass)
name|gimp_object_class_init
parameter_list|(
name|GimpObjectClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GTK_TYPE_OBJECT
argument_list|)
expr_stmt|;
name|gtk_object_add_arg_type
argument_list|(
literal|"GimpObject::name"
argument_list|,
name|GTK_TYPE_STRING
argument_list|,
name|GTK_ARG_READWRITE
argument_list|,
name|ARG_NAME
argument_list|)
expr_stmt|;
name|object_signals
index|[
name|NAME_CHANGED
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"name_changed"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpObjectClass
argument_list|,
name|name_changed
argument_list|)
argument_list|,
name|gtk_signal_default_marshaller
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|object_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_object_destroy
expr_stmt|;
name|object_class
operator|->
name|set_arg
operator|=
name|gimp_object_set_arg
expr_stmt|;
name|object_class
operator|->
name|get_arg
operator|=
name|gimp_object_get_arg
expr_stmt|;
name|klass
operator|->
name|name_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_object_init (GimpObject * object)
name|gimp_object_init
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|object
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_object_destroy (GtkObject * object)
name|gimp_object_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpObject
modifier|*
name|gimp_object
decl_stmt|;
name|gimp_object
operator|=
name|GIMP_OBJECT
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gimp_object
operator|->
name|name
argument_list|)
expr_stmt|;
name|gimp_object
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_object_set_arg (GtkObject * object,GtkArg * arg,guint arg_id)
name|gimp_object_set_arg
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkArg
modifier|*
name|arg
parameter_list|,
name|guint
name|arg_id
parameter_list|)
block|{
name|GimpObject
modifier|*
name|gimp_object
decl_stmt|;
name|gimp_object
operator|=
name|GIMP_OBJECT
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|arg_id
condition|)
block|{
case|case
name|ARG_NAME
case|:
name|gimp_object_set_name
argument_list|(
name|gimp_object
argument_list|,
name|GTK_VALUE_STRING
argument_list|(
operator|*
name|arg
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_object_get_arg (GtkObject * object,GtkArg * arg,guint arg_id)
name|gimp_object_get_arg
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkArg
modifier|*
name|arg
parameter_list|,
name|guint
name|arg_id
parameter_list|)
block|{
name|GimpObject
modifier|*
name|gimp_object
decl_stmt|;
name|gimp_object
operator|=
name|GIMP_OBJECT
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|arg_id
condition|)
block|{
case|case
name|ARG_NAME
case|:
name|GTK_VALUE_STRING
argument_list|(
operator|*
name|arg
argument_list|)
operator|=
name|g_strdup
argument_list|(
name|gimp_object
operator|->
name|name
argument_list|)
expr_stmt|;
break|break;
default|default:
name|arg
operator|->
name|type
operator|=
name|GTK_TYPE_INVALID
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_object_set_name (GimpObject * object,const gchar * name)
name|gimp_object_set_name
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|!
name|object
operator|->
name|name
operator|&&
operator|!
name|name
operator|)
operator|||
operator|(
name|object
operator|->
name|name
operator|&&
name|name
operator|&&
operator|!
name|strcmp
argument_list|(
name|object
operator|->
name|name
argument_list|,
name|name
argument_list|)
operator|)
condition|)
return|return;
name|g_free
argument_list|(
name|object
operator|->
name|name
argument_list|)
expr_stmt|;
name|object
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gimp_object_name_changed
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_object_get_name (const GimpObject * object)
name|gimp_object_get_name
parameter_list|(
specifier|const
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|object
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|object
operator|->
name|name
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_object_name_changed (GimpObject * object)
name|gimp_object_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|object_signals
index|[
name|NAME_CHANGED
index|]
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

