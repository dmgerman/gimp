begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimptoolmodule.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_tool_module_class_init
parameter_list|(
name|GimpToolModuleClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_module_init
parameter_list|(
name|GimpToolModule
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

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
specifier|static
name|gboolean
DECL|function|gimp_tool_module_load (GTypeModule * gmodule)
name|gimp_tool_module_load
parameter_list|(
name|GTypeModule
modifier|*
name|gmodule
parameter_list|)
block|{
name|GimpToolModule
modifier|*
name|module
init|=
name|GIMP_TOOL_MODULE
argument_list|(
name|gmodule
argument_list|)
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|module
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|module
operator|->
name|filename
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_module_supported
argument_list|()
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|module
operator|->
name|module
operator|=
name|g_module_open
argument_list|(
name|module
operator|->
name|filename
argument_list|,
name|G_MODULE_BIND_LAZY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|module
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|!
name|g_module_symbol
argument_list|(
name|module
operator|->
name|module
argument_list|,
literal|"gimp_tool_module_register_tool"
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|module
operator|->
name|register_tool
argument_list|)
operator|||
operator|!
name|g_module_symbol
argument_list|(
name|module
operator|->
name|module
argument_list|,
literal|"gimp_tool_module_register_type"
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|module
operator|->
name|register_type
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
name|g_module_error
argument_list|()
argument_list|)
expr_stmt|;
name|g_module_close
argument_list|(
name|module
operator|->
name|module
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|module
operator|->
name|register_type
argument_list|(
name|module
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_module_unload (GTypeModule * gmodule)
name|gimp_tool_module_unload
parameter_list|(
name|GTypeModule
modifier|*
name|gmodule
parameter_list|)
block|{
name|GimpToolModule
modifier|*
name|module
init|=
name|GIMP_TOOL_MODULE
argument_list|(
name|gmodule
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|module
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|module
operator|->
name|module
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_module_supported
argument_list|()
argument_list|)
expr_stmt|;
name|g_module_close
argument_list|(
name|module
operator|->
name|module
argument_list|)
expr_stmt|;
comment|/* FIXME: error handling */
name|module
operator|->
name|module
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_tool_module_get_type (void)
name|gimp_tool_module_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_module_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_module_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_module_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpToolModuleClass
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
name|gimp_tool_module_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpToolModule
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_tool_module_init
block|,       }
decl_stmt|;
name|tool_module_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_TYPE_MODULE
argument_list|,
literal|"GimpToolModule"
argument_list|,
operator|&
name|tool_module_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_module_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_module_class_init (GimpToolModuleClass * klass)
name|gimp_tool_module_class_init
parameter_list|(
name|GimpToolModuleClass
modifier|*
name|klass
parameter_list|)
block|{
name|GTypeModuleClass
modifier|*
name|g_type_module_class
init|=
name|G_TYPE_MODULE_CLASS
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
name|g_type_module_class
operator|->
name|load
operator|=
name|gimp_tool_module_load
expr_stmt|;
name|g_type_module_class
operator|->
name|unload
operator|=
name|gimp_tool_module_unload
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_module_init (GimpToolModule * module)
name|gimp_tool_module_init
parameter_list|(
name|GimpToolModule
modifier|*
name|module
parameter_list|)
block|{
name|module
operator|->
name|module
operator|=
name|NULL
expr_stmt|;
name|module
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
name|module
operator|->
name|register_tool
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GimpToolModule
modifier|*
DECL|function|gimp_tool_module_new (gchar * filename,Gimp * gimp,GimpToolRegisterCallback callback)
name|gimp_tool_module_new
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolRegisterCallback
name|callback
parameter_list|)
block|{
name|GimpToolModule
modifier|*
name|module
init|=
name|GIMP_TOOL_MODULE
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_MODULE
argument_list|,
name|NULL
argument_list|)
argument_list|)
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|module
operator|->
name|filename
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_tool_module_load
argument_list|(
name|G_TYPE_MODULE
argument_list|(
name|module
argument_list|)
argument_list|)
expr_stmt|;
comment|/* FIXME: check for errors! */
name|module
operator|->
name|register_tool
argument_list|(
name|gimp
argument_list|,
name|callback
argument_list|)
expr_stmt|;
name|gimp_tool_module_unload
argument_list|(
name|G_TYPE_MODULE
argument_list|(
name|module
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|module
return|;
block|}
end_function

end_unit

