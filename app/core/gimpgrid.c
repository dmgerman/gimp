begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGrid  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_comment
comment|/* strcmp */
end_comment

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimplimits.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b9a733b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_STYLE
name|PROP_STYLE
block|,
DECL|enumerator|PROP_FGCOLOR
name|PROP_FGCOLOR
block|,
DECL|enumerator|PROP_BGCOLOR
name|PROP_BGCOLOR
block|,
DECL|enumerator|PROP_XSPACING
name|PROP_XSPACING
block|,
DECL|enumerator|PROP_YSPACING
name|PROP_YSPACING
block|,
DECL|enumerator|PROP_SPACING_UNIT
name|PROP_SPACING_UNIT
block|,
DECL|enumerator|PROP_XOFFSET
name|PROP_XOFFSET
block|,
DECL|enumerator|PROP_YOFFSET
name|PROP_YOFFSET
block|,
DECL|enumerator|PROP_OFFSET_UNIT
name|PROP_OFFSET_UNIT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_grid_class_init
parameter_list|(
name|GimpGridClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_grid_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_grid_get_property
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
name|gimp_grid_set_property
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_grid_get_type (void)
name|gimp_grid_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|grid_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|grid_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|grid_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpGridClass
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
name|gimp_grid_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpGrid
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|grid_iface_info
init|=
block|{
name|NULL
block|,
comment|/* iface_init     */
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|grid_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
literal|"GimpGrid"
argument_list|,
operator|&
name|grid_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|grid_type
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|,
operator|&
name|grid_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|grid_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_grid_class_init (GimpGridClass * klass)
name|gimp_grid_class_init
parameter_list|(
name|GimpGridClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpRGB
name|black
decl_stmt|;
name|GimpRGB
name|white
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
name|finalize
operator|=
name|gimp_grid_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_grid_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_grid_set_property
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|black
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|white
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_STYLE
argument_list|,
literal|"style"
argument_list|,
name|N_
argument_list|(
literal|"Line style used for the grid."
argument_list|)
argument_list|,
name|GIMP_TYPE_GRID_STYLE
argument_list|,
name|GIMP_GRID_INTERSECTIONS
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_COLOR
argument_list|(
name|object_class
argument_list|,
name|PROP_FGCOLOR
argument_list|,
literal|"fgcolor"
argument_list|,
name|N_
argument_list|(
literal|"The foreground color of the grid."
argument_list|)
argument_list|,
operator|&
name|black
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_COLOR
argument_list|(
name|object_class
argument_list|,
name|PROP_BGCOLOR
argument_list|,
literal|"bgcolor"
argument_list|,
name|N_
argument_list|(
literal|"The background color of the grid; "
literal|"only used in double dashed line style."
argument_list|)
argument_list|,
operator|&
name|white
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_XSPACING
argument_list|,
literal|"xspacing"
argument_list|,
name|N_
argument_list|(
literal|"Horizontal spacing of grid lines."
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_YSPACING
argument_list|,
literal|"yspacing"
argument_list|,
name|N_
argument_list|(
literal|"Vertical spacing of grid lines."
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_SPACING_UNIT
argument_list|,
literal|"spacing-unit"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_UNIT_INCH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_XOFFSET
argument_list|,
literal|"xoffset"
argument_list|,
name|N_
argument_list|(
literal|"Horizontal offset of the first grid "
literal|"line; this may be a negative number."
argument_list|)
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_YOFFSET
argument_list|,
literal|"yoffset"
argument_list|,
name|N_
argument_list|(
literal|"Vertical offset of the first grid "
literal|"line; this may be a negative number."
argument_list|)
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_OFFSET_UNIT
argument_list|,
literal|"offset-unit"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_UNIT_INCH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_grid_finalize (GObject * object)
name|gimp_grid_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
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
name|void
DECL|function|gimp_grid_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_grid_get_property
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
name|GimpGrid
modifier|*
name|grid
init|=
name|GIMP_GRID
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
name|PROP_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|grid
operator|->
name|style
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FGCOLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|grid
operator|->
name|fgcolor
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BGCOLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|grid
operator|->
name|bgcolor
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_XSPACING
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|grid
operator|->
name|xspacing
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YSPACING
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|grid
operator|->
name|yspacing
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SPACING_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|grid
operator|->
name|spacing_unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_XOFFSET
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|grid
operator|->
name|xoffset
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YOFFSET
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|grid
operator|->
name|yoffset
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|grid
operator|->
name|offset_unit
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
DECL|function|gimp_grid_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_grid_set_property
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
name|GimpGrid
modifier|*
name|grid
init|=
name|GIMP_GRID
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpRGB
modifier|*
name|color
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_STYLE
case|:
name|grid
operator|->
name|style
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FGCOLOR
case|:
name|color
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|grid
operator|->
name|fgcolor
operator|=
operator|*
name|color
expr_stmt|;
break|break;
case|case
name|PROP_BGCOLOR
case|:
name|color
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|grid
operator|->
name|bgcolor
operator|=
operator|*
name|color
expr_stmt|;
break|break;
case|case
name|PROP_XSPACING
case|:
name|grid
operator|->
name|xspacing
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YSPACING
case|:
name|grid
operator|->
name|yspacing
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SPACING_UNIT
case|:
name|grid
operator|->
name|spacing_unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_XOFFSET
case|:
name|grid
operator|->
name|xoffset
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YOFFSET
case|:
name|grid
operator|->
name|yoffset
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_UNIT
case|:
name|grid
operator|->
name|offset_unit
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
specifier|const
name|gchar
modifier|*
DECL|function|gimp_grid_parasite_name (void)
name|gimp_grid_parasite_name
parameter_list|(
name|void
parameter_list|)
block|{
return|return
literal|"gimp-image-grid"
return|;
block|}
end_function

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_grid_to_parasite (const GimpGrid * grid)
name|gimp_grid_to_parasite
parameter_list|(
specifier|const
name|GimpGrid
modifier|*
name|grid
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|str
operator|=
name|gimp_config_serialize_to_string
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|grid
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|str
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
name|gimp_grid_parasite_name
argument_list|()
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
return|return
name|parasite
return|;
block|}
end_function

begin_function
name|GimpGrid
modifier|*
DECL|function|gimp_grid_from_parasite (const GimpParasite * parasite)
name|gimp_grid_from_parasite
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parasite
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|strcmp
argument_list|(
name|gimp_parasite_name
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_grid_parasite_name
argument_list|()
argument_list|)
operator|==
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|str
operator|=
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|str
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|grid
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_string
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|grid
argument_list|)
argument_list|,
name|str
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"Failed to deserialize grid parasite: %s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
return|return
name|grid
return|;
block|}
end_function

end_unit

