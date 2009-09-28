begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo-aux.c  * Copyright (C) 2001-2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockwindow.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo-aux.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpSessionInfoAux
modifier|*
DECL|function|gimp_session_info_aux_new (const gchar * name,const gchar * value)
name|gimp_session_info_aux_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
block|{
name|GimpSessionInfoAux
modifier|*
name|aux
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|value
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|aux
operator|=
name|g_slice_new0
argument_list|(
name|GimpSessionInfoAux
argument_list|)
expr_stmt|;
name|aux
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|aux
operator|->
name|value
operator|=
name|g_strdup
argument_list|(
name|value
argument_list|)
expr_stmt|;
return|return
name|aux
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_aux_free (GimpSessionInfoAux * aux)
name|gimp_session_info_aux_free
parameter_list|(
name|GimpSessionInfoAux
modifier|*
name|aux
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|aux
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|aux
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|aux
operator|->
name|value
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpSessionInfoAux
argument_list|,
name|aux
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_session_info_aux_new_from_props (GObject * object,...)
name|gimp_session_info_aux_new_from_props
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|prop_name
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|object
argument_list|)
expr_stmt|;
for|for
control|(
name|prop_name
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
init|;
name|prop_name
condition|;
name|prop_name
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
control|)
block|{
name|GObjectClass
modifier|*
name|class
init|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GParamSpec
modifier|*
name|pspec
init|=
name|g_object_class_find_property
argument_list|(
name|class
argument_list|,
name|prop_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|pspec
condition|)
block|{
name|GString
modifier|*
name|str
init|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|object
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_param_value_defaults
argument_list|(
name|pspec
argument_list|,
operator|&
name|value
argument_list|)
operator|&&
name|gimp_config_serialize_value
argument_list|(
operator|&
name|value
argument_list|,
name|str
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
name|list
operator|=
name|g_list_prepend
argument_list|(
name|list
argument_list|,
name|gimp_session_info_aux_new
argument_list|(
name|prop_name
argument_list|,
name|str
operator|->
name|str
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|str
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: no property named '%s' for %s"
argument_list|,
name|G_STRFUNC
argument_list|,
name|prop_name
argument_list|,
name|G_OBJECT_CLASS_NAME
argument_list|(
name|class
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|g_list_reverse
argument_list|(
name|list
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_aux_set_props (GObject * object,GList * auxs,...)
name|gimp_session_info_aux_set_props
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GList
modifier|*
name|auxs
parameter_list|,
modifier|...
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|prop_name
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|auxs
argument_list|)
expr_stmt|;
for|for
control|(
name|prop_name
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
init|;
name|prop_name
condition|;
name|prop_name
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
control|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|auxs
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
name|GimpSessionInfoAux
modifier|*
name|aux
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|aux
operator|->
name|name
argument_list|,
name|prop_name
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GObjectClass
modifier|*
name|class
init|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GParamSpec
modifier|*
name|pspec
init|=
name|g_object_class_find_property
argument_list|(
name|class
argument_list|,
name|prop_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|pspec
condition|)
block|{
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_VALUE_HOLDS_ENUM
argument_list|(
operator|&
name|value
argument_list|)
condition|)
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|enum_class
operator|=
name|g_type_class_peek
argument_list|(
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value_by_nick
argument_list|(
name|enum_class
argument_list|,
name|aux
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_value
condition|)
block|{
name|g_value_set_enum
argument_list|(
operator|&
name|value
argument_list|,
name|enum_value
operator|->
name|value
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|object
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: unknown enum value in '%s' for %s"
argument_list|,
name|G_STRFUNC
argument_list|,
name|prop_name
argument_list|,
name|G_OBJECT_CLASS_NAME
argument_list|(
name|class
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|GValue
name|str_value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|str_value
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|g_value_set_static_string
argument_list|(
operator|&
name|str_value
argument_list|,
name|aux
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_transform
argument_list|(
operator|&
name|str_value
argument_list|,
operator|&
name|value
argument_list|)
condition|)
name|g_object_set_property
argument_list|(
name|object
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
else|else
name|g_warning
argument_list|(
literal|"%s: cannot convert property '%s' for %s"
argument_list|,
name|G_STRFUNC
argument_list|,
name|prop_name
argument_list|,
name|G_OBJECT_CLASS_NAME
argument_list|(
name|class
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|str_value
argument_list|)
expr_stmt|;
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: no property named '%s' for %s"
argument_list|,
name|G_STRFUNC
argument_list|,
name|prop_name
argument_list|,
name|G_OBJECT_CLASS_NAME
argument_list|(
name|class
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_aux_serialize (GimpConfigWriter * writer,GList * aux_info)
name|gimp_session_info_aux_serialize
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|aux_info
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"aux-info"
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|aux_info
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
name|GimpSessionInfoAux
modifier|*
name|aux
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
name|aux
operator|->
name|name
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|aux
operator|->
name|value
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GTokenType
DECL|function|gimp_session_info_aux_deserialize (GScanner * scanner,GList ** aux_list)
name|gimp_session_info_aux_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GList
modifier|*
modifier|*
name|aux_list
parameter_list|)
block|{
name|GimpSessionInfoAux
modifier|*
name|aux_info
init|=
name|NULL
decl_stmt|;
name|GTokenType
name|token
init|=
name|G_TOKEN_LEFT_PAREN
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|scanner
operator|!=
name|NULL
argument_list|,
name|G_TOKEN_LEFT_PAREN
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|aux_list
operator|!=
name|NULL
argument_list|,
name|G_TOKEN_LEFT_PAREN
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|token
condition|)
block|{
case|case
name|G_TOKEN_LEFT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_IDENTIFIER
expr_stmt|;
break|break;
case|case
name|G_TOKEN_IDENTIFIER
case|:
block|{
name|aux_info
operator|=
name|g_slice_new0
argument_list|(
name|GimpSessionInfoAux
argument_list|)
expr_stmt|;
name|aux_info
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|token
condition|)
goto|goto
name|error
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|aux_info
operator|->
name|value
argument_list|)
condition|)
goto|goto
name|error
goto|;
operator|*
name|aux_list
operator|=
name|g_list_append
argument_list|(
operator|*
name|aux_list
argument_list|,
name|aux_info
argument_list|)
expr_stmt|;
name|aux_info
operator|=
name|NULL
expr_stmt|;
block|}
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
break|break;
case|case
name|G_TOKEN_RIGHT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
return|return
name|token
return|;
name|error
label|:
if|if
condition|(
name|aux_info
condition|)
name|gimp_session_info_aux_free
argument_list|(
name|aux_info
argument_list|)
expr_stmt|;
return|return
name|token
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_aux_set_list (GtkWidget * dialog,GList * aux_list)
name|gimp_session_info_aux_set_list
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GList
modifier|*
name|aux_list
parameter_list|)
block|{
comment|/* FIXME: make the aux-info stuff generic */
if|if
condition|(
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|dialog
argument_list|)
condition|)
name|gimp_dock_set_aux_info
argument_list|(
name|gimp_dock_window_get_dock
argument_list|(
name|GIMP_DOCK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|,
name|aux_list
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dialog
argument_list|)
condition|)
name|gimp_dockable_set_aux_info
argument_list|(
name|GIMP_DOCKABLE
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|aux_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_session_info_aux_get_list (GtkWidget * dialog)
name|gimp_session_info_aux_get_list
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
comment|/* FIXME: make the aux-info stuff generic */
if|if
condition|(
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|dialog
argument_list|)
condition|)
return|return
name|gimp_dock_get_aux_info
argument_list|(
name|gimp_dock_window_get_dock
argument_list|(
name|GIMP_DOCK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dialog
argument_list|)
condition|)
return|return
name|gimp_dockable_get_aux_info
argument_list|(
name|GIMP_DOCKABLE
argument_list|(
name|dialog
argument_list|)
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

