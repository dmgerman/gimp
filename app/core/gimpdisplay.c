begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a1196910103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ID
name|PROP_ID
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpDisplayPrivate
struct|struct
name|_GimpDisplayPrivate
block|{
DECL|member|id
name|gint
name|id
decl_stmt|;
comment|/* unique identifier for this display */
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_set_property
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
name|gimp_display_get_property
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
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpDisplay,gimp_display,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpDisplay
argument_list|,
argument|gimp_display
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_display_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_display_class_init
parameter_list|(
name|GimpDisplayClass
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
name|gimp_display_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_display_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ID
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"id"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GIMP
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GIMP
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_init (GimpDisplay * display)
name|gimp_display_init
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|display
operator|->
name|priv
operator|=
name|gimp_display_get_instance_private
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_display_set_property
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
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpDisplayPrivate
modifier|*
name|private
init|=
name|display
operator|->
name|priv
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_GIMP
case|:
block|{
name|gint
name|id
decl_stmt|;
name|display
operator|->
name|gimp
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't ref the gimp */
name|display
operator|->
name|config
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|display
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
do|do
block|{
name|id
operator|=
name|display
operator|->
name|gimp
operator|->
name|next_display_id
operator|++
expr_stmt|;
if|if
condition|(
name|display
operator|->
name|gimp
operator|->
name|next_display_id
operator|==
name|G_MAXINT
condition|)
name|display
operator|->
name|gimp
operator|->
name|next_display_id
operator|=
literal|1
expr_stmt|;
block|}
do|while
condition|(
name|gimp_display_get_by_id
argument_list|(
name|display
operator|->
name|gimp
argument_list|,
name|id
argument_list|)
condition|)
do|;
name|private
operator|->
name|id
operator|=
name|id
expr_stmt|;
block|}
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
DECL|function|gimp_display_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_display_get_property
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
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
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
name|PROP_ID
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|display
operator|->
name|priv
operator|->
name|id
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GIMP
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|display
operator|->
name|gimp
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gint
DECL|function|gimp_display_get_id (GimpDisplay * display)
name|gimp_display_get_id
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|display
operator|->
name|priv
operator|->
name|id
return|;
block|}
end_function

begin_function
name|GimpDisplay
modifier|*
DECL|function|gimp_display_get_by_id (Gimp * gimp,gint id)
name|gimp_display_get_by_id
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|id
parameter_list|)
block|{
name|GList
modifier|*
name|list
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
for|for
control|(
name|list
operator|=
name|gimp_get_display_iter
argument_list|(
name|gimp
argument_list|)
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
name|GimpDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_display_get_id
argument_list|(
name|display
argument_list|)
operator|==
name|id
condition|)
return|return
name|display
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|Gimp
modifier|*
DECL|function|gimp_display_get_gimp (GimpDisplay * display)
name|gimp_display_get_gimp
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|display
operator|->
name|gimp
return|;
block|}
end_function

end_unit

