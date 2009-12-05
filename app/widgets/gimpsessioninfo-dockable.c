begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo-dockable.c  * Copyright (C) 2001-2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpcontainerview-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
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
file|"gimpsessioninfo-aux.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo-dockable.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2ba9f7e10103
block|{
DECL|enumerator|SESSION_INFO_DOCKABLE_LOCKED
name|SESSION_INFO_DOCKABLE_LOCKED
block|,
DECL|enumerator|SESSION_INFO_DOCKABLE_TAB_STYLE
name|SESSION_INFO_DOCKABLE_TAB_STYLE
block|,
DECL|enumerator|SESSION_INFO_DOCKABLE_VIEW_SIZE
name|SESSION_INFO_DOCKABLE_VIEW_SIZE
block|,
DECL|enumerator|SESSION_INFO_DOCKABLE_AUX
name|SESSION_INFO_DOCKABLE_AUX
block|}
enum|;
end_enum

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpSessionInfoDockable
modifier|*
DECL|function|gimp_session_info_dockable_new (void)
name|gimp_session_info_dockable_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_slice_new0
argument_list|(
name|GimpSessionInfoDockable
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_dockable_free (GimpSessionInfoDockable * info)
name|gimp_session_info_dockable_free
parameter_list|(
name|GimpSessionInfoDockable
modifier|*
name|info
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|info
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|identifier
condition|)
block|{
name|g_free
argument_list|(
name|info
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|info
operator|->
name|identifier
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|info
operator|->
name|aux_info
condition|)
block|{
name|g_list_foreach
argument_list|(
name|info
operator|->
name|aux_info
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_session_info_aux_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|info
operator|->
name|aux_info
argument_list|)
expr_stmt|;
name|info
operator|->
name|aux_info
operator|=
name|NULL
expr_stmt|;
block|}
name|g_slice_free
argument_list|(
name|GimpSessionInfoDockable
argument_list|,
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_dockable_serialize (GimpConfigWriter * writer,GimpSessionInfoDockable * info)
name|gimp_session_info_dockable_serialize
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GimpSessionInfoDockable
modifier|*
name|info
parameter_list|)
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|tab_style
init|=
literal|"icon"
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
name|info
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_TAB_STYLE
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"dockable"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|info
operator|->
name|identifier
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|locked
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"locked"
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
name|enum_value
operator|=
name|g_enum_get_value
argument_list|(
name|enum_class
argument_list|,
name|info
operator|->
name|tab_style
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_value
condition|)
name|tab_style
operator|=
name|enum_value
operator|->
name|value_nick
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"tab-style"
argument_list|)
expr_stmt|;
name|gimp_config_writer_print
argument_list|(
name|writer
argument_list|,
name|tab_style
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|view_size
operator|>
literal|0
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"preview-size"
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d"
argument_list|,
name|info
operator|->
name|view_size
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|info
operator|->
name|aux_info
condition|)
name|gimp_session_info_aux_serialize
argument_list|(
name|writer
argument_list|,
name|info
operator|->
name|aux_info
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GTokenType
DECL|function|gimp_session_info_dockable_deserialize (GScanner * scanner,gint scope,GimpSessionInfoDockable ** dockable)
name|gimp_session_info_dockable_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|scope
parameter_list|,
name|GimpSessionInfoDockable
modifier|*
modifier|*
name|dockable
parameter_list|)
block|{
name|GimpSessionInfoDockable
modifier|*
name|info
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|GTokenType
name|token
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
name|dockable
operator|!=
name|NULL
argument_list|,
name|G_TOKEN_LEFT_PAREN
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"locked"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_DOCKABLE_LOCKED
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"tab-style"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_DOCKABLE_TAB_STYLE
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"preview-size"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_DOCKABLE_VIEW_SIZE
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"aux-info"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_DOCKABLE_AUX
argument_list|)
argument_list|)
expr_stmt|;
name|info
operator|=
name|gimp_session_info_dockable_new
argument_list|()
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_TAB_STYLE
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|identifier
argument_list|)
condition|)
goto|goto
name|error
goto|;
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
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
name|G_TOKEN_SYMBOL
expr_stmt|;
break|break;
case|case
name|G_TOKEN_SYMBOL
case|:
switch|switch
condition|(
name|GPOINTER_TO_INT
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
argument_list|)
condition|)
block|{
case|case
name|SESSION_INFO_DOCKABLE_LOCKED
case|:
name|info
operator|->
name|locked
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|SESSION_INFO_DOCKABLE_TAB_STYLE
case|:
name|token
operator|=
name|G_TOKEN_IDENTIFIER
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
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value_by_nick
argument_list|(
name|enum_class
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|enum_value
condition|)
name|enum_value
operator|=
name|g_enum_get_value_by_name
argument_list|(
name|enum_class
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_value
condition|)
name|info
operator|->
name|tab_style
operator|=
name|enum_value
operator|->
name|value
expr_stmt|;
break|break;
case|case
name|SESSION_INFO_DOCKABLE_VIEW_SIZE
case|:
name|token
operator|=
name|G_TOKEN_INT
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|view_size
argument_list|)
condition|)
goto|goto
name|error
goto|;
break|break;
case|case
name|SESSION_INFO_DOCKABLE_AUX
case|:
name|token
operator|=
name|gimp_session_info_aux_deserialize
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|aux_info
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_LEFT_PAREN
condition|)
goto|goto
name|error
goto|;
break|break;
default|default:
goto|goto
name|error
goto|;
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
operator|*
name|dockable
operator|=
name|info
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"locked"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"tab-style"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"preview-size"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"aux-info"
argument_list|)
expr_stmt|;
return|return
name|token
return|;
name|error
label|:
operator|*
name|dockable
operator|=
name|NULL
expr_stmt|;
name|gimp_session_info_dockable_free
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
return|return
name|token
return|;
block|}
end_function

begin_function
name|GimpSessionInfoDockable
modifier|*
DECL|function|gimp_session_info_dockable_from_widget (GimpDockable * dockable)
name|gimp_session_info_dockable_from_widget
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|GimpSessionInfoDockable
modifier|*
name|info
decl_stmt|;
name|GimpDialogFactoryEntry
modifier|*
name|entry
decl_stmt|;
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
name|gint
name|view_size
init|=
operator|-
literal|1
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_from_widget
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|&
name|entry
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|entry
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|info
operator|=
name|gimp_session_info_dockable_new
argument_list|()
expr_stmt|;
name|info
operator|->
name|locked
operator|=
name|dockable
operator|->
name|locked
expr_stmt|;
name|info
operator|->
name|identifier
operator|=
name|g_strdup
argument_list|(
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|info
operator|->
name|tab_style
operator|=
name|dockable
operator|->
name|tab_style
expr_stmt|;
name|info
operator|->
name|view_size
operator|=
operator|-
literal|1
expr_stmt|;
name|view
operator|=
name|gimp_container_view_get_by_dockable
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
condition|)
name|view_size
operator|=
name|gimp_container_view_get_view_size
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|view_size
operator|>
literal|0
operator|&&
name|view_size
operator|!=
name|entry
operator|->
name|view_size
condition|)
name|info
operator|->
name|view_size
operator|=
name|view_size
expr_stmt|;
name|info
operator|->
name|aux_info
operator|=
name|gimp_session_info_aux_get_list
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|info
return|;
block|}
end_function

begin_function
name|GimpDockable
modifier|*
DECL|function|gimp_session_info_dockable_restore (GimpSessionInfoDockable * info,GimpDock * dock)
name|gimp_session_info_dockable_restore
parameter_list|(
name|GimpSessionInfoDockable
modifier|*
name|info
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|info
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|view_size
operator|<
name|GIMP_VIEW_SIZE_TINY
operator|||
name|info
operator|->
name|view_size
operator|>
name|GIMP_VIEW_SIZE_GIGANTIC
condition|)
name|info
operator|->
name|view_size
operator|=
operator|-
literal|1
expr_stmt|;
comment|/* FIXME: Merge global_dock_factory and global_toolbox_factory    * somehow so we don't need this hack    */
name|dockable
operator|=
name|gimp_dialog_factory_dockable_new
argument_list|(
operator|(
name|GIMP_IS_TOOLBOX
argument_list|(
name|dock
argument_list|)
condition|?
name|gimp_toolbox_get_dialog_factory
argument_list|(
name|GIMP_TOOLBOX
argument_list|(
name|dock
argument_list|)
argument_list|)
else|:
name|gimp_dock_get_dialog_factory
argument_list|(
name|dock
argument_list|)
operator|)
argument_list|,
name|dock
argument_list|,
name|info
operator|->
name|identifier
argument_list|,
name|info
operator|->
name|view_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
block|{
name|gimp_dockable_set_locked
argument_list|(
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|info
operator|->
name|locked
argument_list|)
expr_stmt|;
name|gimp_dockable_set_tab_style
argument_list|(
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|info
operator|->
name|tab_style
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|aux_info
condition|)
name|gimp_session_info_aux_set_list
argument_list|(
name|dockable
argument_list|,
name|info
operator|->
name|aux_info
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
return|;
block|}
end_function

end_unit

