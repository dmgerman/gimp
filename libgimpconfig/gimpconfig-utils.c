begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Utitility functions for GimpConfig.  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpenv.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-utils.h"
end_include

begin_function
name|GList
modifier|*
DECL|function|gimp_config_diff (GObject * a,GObject * b,GParamFlags flags)
name|gimp_config_diff
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GParamSpec
modifier|*
modifier|*
name|param_specs
decl_stmt|;
name|guint
name|n_param_specs
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|a
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|b
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|a
argument_list|)
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|b
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|param_specs
operator|=
name|g_object_class_list_properties
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|a
argument_list|)
argument_list|,
operator|&
name|n_param_specs
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_param_specs
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|flags
operator|||
operator|(
operator|(
name|param_specs
index|[
name|i
index|]
operator|->
name|flags
operator|&
name|flags
operator|)
operator|==
name|flags
operator|)
condition|)
block|{
name|GValue
name|a_value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|GValue
name|b_value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|a_value
argument_list|,
name|param_specs
index|[
name|i
index|]
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|b_value
argument_list|,
name|param_specs
index|[
name|i
index|]
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|a
argument_list|,
name|param_specs
index|[
name|i
index|]
operator|->
name|name
argument_list|,
operator|&
name|a_value
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|b
argument_list|,
name|param_specs
index|[
name|i
index|]
operator|->
name|name
argument_list|,
operator|&
name|b_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_param_values_cmp
argument_list|(
name|param_specs
index|[
name|i
index|]
argument_list|,
operator|&
name|a_value
argument_list|,
operator|&
name|b_value
argument_list|)
condition|)
name|list
operator|=
name|g_list_prepend
argument_list|(
name|list
argument_list|,
name|param_specs
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|a_value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|b_value
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|param_specs
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
DECL|function|gimp_config_copy_properties (GObject * src,GObject * dest)
name|gimp_config_copy_properties
parameter_list|(
name|GObject
modifier|*
name|src
parameter_list|,
name|GObject
modifier|*
name|dest
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|klass
decl_stmt|;
name|GParamSpec
modifier|*
modifier|*
name|property_specs
decl_stmt|;
name|guint
name|n_property_specs
decl_stmt|;
name|guint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|src
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|src
argument_list|)
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|dest
argument_list|)
argument_list|)
expr_stmt|;
name|klass
operator|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|property_specs
operator|=
name|g_object_class_list_properties
argument_list|(
name|klass
argument_list|,
operator|&
name|n_property_specs
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|property_specs
condition|)
return|return;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_property_specs
condition|;
name|i
operator|++
control|)
block|{
name|GParamSpec
modifier|*
name|prop_spec
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|prop_spec
operator|=
name|property_specs
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|G_PARAM_READWRITE
operator|)
condition|)
continue|continue;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|src
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|dest
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_config_build_data_path (const gchar * name)
name|gimp_config_build_data_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
name|gimp_data_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_config_build_plug_in_path (const gchar * name)
name|gimp_config_build_plug_in_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
name|gimp_plug_in_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

