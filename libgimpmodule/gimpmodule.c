begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmoduleinfo.c  * (C) 1999 Austin Donnelly<austin@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimp/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpmoduleinfo.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29c5b4280103
block|{
DECL|enumerator|MODIFIED
name|MODIFIED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_module_info_class_init
parameter_list|(
name|GimpModuleInfoObjClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_module_info_init
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|mod
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_module_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_module_info_load
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_module_info_unload
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_module_info_set_last_error
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|module_info
parameter_list|,
specifier|const
name|gchar
modifier|*
name|error_str
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|module_info_signals
specifier|static
name|guint
name|module_info_signals
index|[
name|LAST_SIGNAL
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GTypeModuleClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_module_info_get_type (void)
name|gimp_module_info_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|module_info_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|module_info_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|module_info_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpModuleInfoObjClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_module_info_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpModuleInfoObj
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_module_info_init
block|,       }
decl_stmt|;
name|module_info_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_TYPE_MODULE
argument_list|,
literal|"GimpModuleInfoObj"
argument_list|,
operator|&
name|module_info_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|module_info_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_module_info_class_init (GimpModuleInfoObjClass * klass)
name|gimp_module_info_class_init
parameter_list|(
name|GimpModuleInfoObjClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GTypeModuleClass
modifier|*
name|module_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|module_class
operator|=
name|G_TYPE_MODULE_CLASS
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
name|module_info_signals
index|[
name|MODIFIED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"modified"
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
name|GimpModuleInfoObjClass
argument_list|,
name|modified
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_module_info_finalize
expr_stmt|;
name|module_class
operator|->
name|load
operator|=
name|gimp_module_info_load
expr_stmt|;
name|module_class
operator|->
name|unload
operator|=
name|gimp_module_info_unload
expr_stmt|;
name|klass
operator|->
name|modified
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_module_info_init (GimpModuleInfoObj * module_info)
name|gimp_module_info_init
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|module_info
parameter_list|)
block|{
name|module_info
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
name|module_info
operator|->
name|verbose
operator|=
name|FALSE
expr_stmt|;
name|module_info
operator|->
name|state
operator|=
name|GIMP_MODULE_STATE_ERROR
expr_stmt|;
name|module_info
operator|->
name|on_disk
operator|=
name|FALSE
expr_stmt|;
name|module_info
operator|->
name|load_inhibit
operator|=
name|FALSE
expr_stmt|;
name|module_info
operator|->
name|module
operator|=
name|NULL
expr_stmt|;
name|module_info
operator|->
name|info
operator|=
name|NULL
expr_stmt|;
name|module_info
operator|->
name|last_module_error
operator|=
name|NULL
expr_stmt|;
name|module_info
operator|->
name|register_module
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_module_info_finalize (GObject * object)
name|gimp_module_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpModuleInfoObj
modifier|*
name|mod
decl_stmt|;
name|mod
operator|=
name|GIMP_MODULE_INFO
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|mod
operator|->
name|last_module_error
condition|)
block|{
name|g_free
argument_list|(
name|mod
operator|->
name|last_module_error
argument_list|)
expr_stmt|;
name|mod
operator|->
name|last_module_error
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|mod
operator|->
name|filename
condition|)
block|{
name|g_free
argument_list|(
name|mod
operator|->
name|filename
argument_list|)
expr_stmt|;
name|mod
operator|->
name|filename
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
name|gboolean
DECL|function|gimp_module_info_load (GTypeModule * module)
name|gimp_module_info_load
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
name|GimpModuleInfoObj
modifier|*
name|module_info
decl_stmt|;
name|gpointer
name|symbol
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MODULE_INFO
argument_list|(
name|module
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|module_info
operator|=
name|GIMP_MODULE_INFO
argument_list|(
name|module
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|module_info
operator|->
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|module_info
operator|->
name|module
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|module_info
operator|->
name|verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"loading module: '%s'\n"
argument_list|)
argument_list|,
name|module_info
operator|->
name|filename
argument_list|)
expr_stmt|;
name|module_info
operator|->
name|module
operator|=
name|g_module_open
argument_list|(
name|module_info
operator|->
name|filename
argument_list|,
name|G_MODULE_BIND_LAZY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|module_info
operator|->
name|module
condition|)
block|{
name|module_info
operator|->
name|state
operator|=
name|GIMP_MODULE_STATE_ERROR
expr_stmt|;
name|gimp_module_info_set_last_error
argument_list|(
name|module_info
argument_list|,
name|g_module_error
argument_list|()
argument_list|)
expr_stmt|;
if|if
condition|(
name|module_info
operator|->
name|verbose
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Module '%s' load error:\n%s"
argument_list|)
argument_list|,
name|module_info
operator|->
name|filename
argument_list|,
name|module_info
operator|->
name|last_module_error
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/* find the module_init symbol */
if|if
condition|(
operator|!
name|g_module_symbol
argument_list|(
name|module_info
operator|->
name|module
argument_list|,
literal|"gimp_module_register"
argument_list|,
operator|&
name|symbol
argument_list|)
condition|)
block|{
name|module_info
operator|->
name|state
operator|=
name|GIMP_MODULE_STATE_ERROR
expr_stmt|;
name|gimp_module_info_set_last_error
argument_list|(
name|module_info
argument_list|,
name|_
argument_list|(
literal|"Missing gimp_module_register() symbol"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|module_info
operator|->
name|verbose
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Module '%s' load error:\n%s"
argument_list|)
argument_list|,
name|module_info
operator|->
name|filename
argument_list|,
name|module_info
operator|->
name|last_module_error
argument_list|)
expr_stmt|;
name|g_module_close
argument_list|(
name|module_info
operator|->
name|module
argument_list|)
expr_stmt|;
name|module_info
operator|->
name|module
operator|=
name|NULL
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|module_info
operator|->
name|register_module
operator|=
name|symbol
expr_stmt|;
name|retval
operator|=
name|module_info
operator|->
name|register_module
argument_list|(
name|module
argument_list|,
operator|&
name|module_info
operator|->
name|info
argument_list|)
expr_stmt|;
if|if
condition|(
name|retval
condition|)
name|module_info
operator|->
name|state
operator|=
name|GIMP_MODULE_STATE_LOADED_OK
expr_stmt|;
else|else
name|module_info
operator|->
name|state
operator|=
name|GIMP_MODULE_STATE_LOAD_FAILED
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_module_info_unload (GTypeModule * module)
name|gimp_module_info_unload
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
name|GimpModuleInfoObj
modifier|*
name|module_info
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MODULE_INFO
argument_list|(
name|module
argument_list|)
argument_list|)
expr_stmt|;
name|module_info
operator|=
name|GIMP_MODULE_INFO
argument_list|(
name|module
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|module_info
operator|->
name|module
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_module_close
argument_list|(
name|module_info
operator|->
name|module
argument_list|)
expr_stmt|;
comment|/* FIXME: error handling */
name|module_info
operator|->
name|module
operator|=
name|NULL
expr_stmt|;
name|module_info
operator|->
name|info
operator|=
name|NULL
expr_stmt|;
name|module_info
operator|->
name|register_module
operator|=
name|NULL
expr_stmt|;
name|module_info
operator|->
name|state
operator|=
name|GIMP_MODULE_STATE_UNLOADED_OK
expr_stmt|;
block|}
end_function

begin_function
name|GimpModuleInfoObj
modifier|*
DECL|function|gimp_module_info_new (const gchar * filename,const gchar * inhibit_list,gboolean verbose)
name|gimp_module_info_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|inhibit_list
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
block|{
name|GimpModuleInfoObj
modifier|*
name|module_info
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|module_info
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_MODULE_INFO
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|module_info
operator|->
name|filename
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|module_info
operator|->
name|verbose
operator|=
name|verbose
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|module_info
operator|->
name|on_disk
operator|=
name|TRUE
expr_stmt|;
name|gimp_module_info_set_load_inhibit
argument_list|(
name|module_info
argument_list|,
name|inhibit_list
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|module_info
operator|->
name|load_inhibit
condition|)
block|{
if|if
condition|(
name|gimp_module_info_load
argument_list|(
name|G_TYPE_MODULE
argument_list|(
name|module_info
argument_list|)
argument_list|)
condition|)
name|gimp_module_info_unload
argument_list|(
name|G_TYPE_MODULE
argument_list|(
name|module_info
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"skipping module: '%s'\n"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|module_info
operator|->
name|state
operator|=
name|GIMP_MODULE_STATE_UNLOADED_OK
expr_stmt|;
block|}
return|return
name|module_info
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_module_info_modified (GimpModuleInfoObj * module_info)
name|gimp_module_info_modified
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|module_info
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MODULE_INFO
argument_list|(
name|module_info
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|module_info
argument_list|)
argument_list|,
name|module_info_signals
index|[
name|MODIFIED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_module_info_set_load_inhibit (GimpModuleInfoObj * module_info,const gchar * inhibit_list)
name|gimp_module_info_set_load_inhibit
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|module_info
parameter_list|,
specifier|const
name|gchar
modifier|*
name|inhibit_list
parameter_list|)
block|{
name|gchar
modifier|*
name|p
decl_stmt|;
name|gint
name|pathlen
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|start
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|end
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MODULE_INFO
argument_list|(
name|module_info
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|module_info
operator|->
name|filename
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|module_info
operator|->
name|load_inhibit
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|inhibit_list
operator|||
operator|!
name|strlen
argument_list|(
name|inhibit_list
argument_list|)
condition|)
return|return;
name|p
operator|=
name|strstr
argument_list|(
name|inhibit_list
argument_list|,
name|module_info
operator|->
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|p
condition|)
return|return;
comment|/* we have a substring, but check for colons either side */
name|start
operator|=
name|p
expr_stmt|;
while|while
condition|(
name|start
operator|!=
name|inhibit_list
operator|&&
operator|*
name|start
operator|!=
name|G_SEARCHPATH_SEPARATOR
condition|)
name|start
operator|--
expr_stmt|;
if|if
condition|(
operator|*
name|start
operator|==
name|G_SEARCHPATH_SEPARATOR
condition|)
name|start
operator|++
expr_stmt|;
name|end
operator|=
name|strchr
argument_list|(
name|p
argument_list|,
name|G_SEARCHPATH_SEPARATOR
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|end
condition|)
name|end
operator|=
name|inhibit_list
operator|+
name|strlen
argument_list|(
name|inhibit_list
argument_list|)
expr_stmt|;
name|pathlen
operator|=
name|strlen
argument_list|(
name|module_info
operator|->
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|end
operator|-
name|start
operator|)
operator|==
name|pathlen
condition|)
name|module_info
operator|->
name|load_inhibit
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_module_info_set_last_error (GimpModuleInfoObj * module_info,const gchar * error_str)
name|gimp_module_info_set_last_error
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|module_info
parameter_list|,
specifier|const
name|gchar
modifier|*
name|error_str
parameter_list|)
block|{
if|if
condition|(
name|module_info
operator|->
name|last_module_error
condition|)
name|g_free
argument_list|(
name|module_info
operator|->
name|last_module_error
argument_list|)
expr_stmt|;
name|module_info
operator|->
name|last_module_error
operator|=
name|g_strdup
argument_list|(
name|error_str
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

