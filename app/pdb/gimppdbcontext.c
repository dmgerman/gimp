begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimppdbcontext.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimppdbcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon292387cf0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ANTIALIAS
name|PROP_ANTIALIAS
block|,
DECL|enumerator|PROP_FEATHER
name|PROP_FEATHER
block|,
DECL|enumerator|PROP_FEATHER_RADIUS_X
name|PROP_FEATHER_RADIUS_X
block|,
DECL|enumerator|PROP_FEATHER_RADIUS_Y
name|PROP_FEATHER_RADIUS_Y
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_pdb_context_set_property
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
name|gimp_pdb_context_get_property
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
DECL|function|G_DEFINE_TYPE (GimpPDBContext,gimp_pdb_context,GIMP_TYPE_CONTEXT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPDBContext
argument_list|,
argument|gimp_pdb_context
argument_list|,
argument|GIMP_TYPE_CONTEXT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_pdb_context_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_pdb_context_class_init
parameter_list|(
name|GimpPDBContextClass
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
name|gimp_pdb_context_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_pdb_context_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ANTIALIAS
argument_list|,
literal|"antialias"
argument_list|,
name|N_
argument_list|(
literal|"Smooth edges"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_FEATHER
argument_list|,
literal|"feather"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_FEATHER_RADIUS_X
argument_list|,
literal|"feather-radius-x"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|10.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_FEATHER_RADIUS_Y
argument_list|,
literal|"feather-radius-y"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|10.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_context_init (GimpPDBContext * options)
name|gimp_pdb_context_init
parameter_list|(
name|GimpPDBContext
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_context_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_pdb_context_set_property
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
name|GimpPDBContext
modifier|*
name|options
init|=
name|GIMP_PDB_CONTEXT
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
name|PROP_ANTIALIAS
case|:
name|options
operator|->
name|antialias
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FEATHER
case|:
name|options
operator|->
name|feather
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FEATHER_RADIUS_X
case|:
name|options
operator|->
name|feather_radius_x
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FEATHER_RADIUS_Y
case|:
name|options
operator|->
name|feather_radius_y
operator|=
name|g_value_get_double
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
DECL|function|gimp_pdb_context_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_pdb_context_get_property
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
name|GimpPDBContext
modifier|*
name|options
init|=
name|GIMP_PDB_CONTEXT
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
name|PROP_ANTIALIAS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|antialias
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FEATHER
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|feather
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FEATHER_RADIUS_X
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|feather_radius_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FEATHER_RADIUS_Y
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|feather_radius_y
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
name|GimpContext
modifier|*
DECL|function|gimp_pdb_context_new (Gimp * gimp,GimpContext * parent,gboolean set_parent)
name|gimp_pdb_context_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|parent
parameter_list|,
name|gboolean
name|set_parent
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|context
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PDB_CONTEXT
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"name"
argument_list|,
literal|"PDB Context"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|parent
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|set_parent
condition|)
block|{
name|gimp_context_define_properties
argument_list|(
name|context
argument_list|,
name|GIMP_CONTEXT_ALL_PROPS_MASK
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|context
argument_list|,
name|parent
argument_list|)
expr_stmt|;
block|}
return|return
name|context
return|;
block|}
end_function

end_unit

