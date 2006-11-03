begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpImageParasiteView  * Copyright (C) 2006  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageparasiteview.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2961e7920103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PARASITE
name|PROP_PARASITE
block|,
DECL|enumerator|PROP_IMAGE
name|PROP_IMAGE
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2961e7920203
block|{
DECL|enumerator|UPDATE
name|UPDATE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_image_parasite_view_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_parasite_view_set_property
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
name|gimp_image_parasite_view_get_property
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
name|gimp_image_parasite_view_finalize
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
name|gimp_image_parasite_view_parasite_changed
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_parasite_view_update
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpImageParasiteView
argument_list|,
argument|gimp_image_parasite_view
argument_list|,
argument|GTK_TYPE_VBOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_parasite_view_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|view_signals
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
specifier|static
name|void
DECL|function|gimp_image_parasite_view_class_init (GimpImageParasiteViewClass * klass)
name|gimp_image_parasite_view_class_init
parameter_list|(
name|GimpImageParasiteViewClass
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
name|view_signals
index|[
name|UPDATE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"update"
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
name|GimpImageParasiteViewClass
argument_list|,
name|update
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
name|constructor
operator|=
name|gimp_image_parasite_view_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_image_parasite_view_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_image_parasite_view_get_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_image_parasite_view_finalize
expr_stmt|;
name|klass
operator|->
name|update
operator|=
name|NULL
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PARASITE
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"parasite"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"image"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
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
DECL|function|gimp_image_parasite_view_init (GimpImageParasiteView * view)
name|gimp_image_parasite_view_init
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|parasite
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_parasite_view_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_image_parasite_view_set_property
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
name|GimpImageParasiteView
modifier|*
name|view
init|=
name|GIMP_IMAGE_PARASITE_VIEW
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
name|PROP_PARASITE
case|:
name|view
operator|->
name|parasite
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE
case|:
name|view
operator|->
name|image
operator|=
name|GIMP_IMAGE
argument_list|(
name|g_value_get_object
argument_list|(
name|value
argument_list|)
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
DECL|function|gimp_image_parasite_view_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_image_parasite_view_get_property
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
name|GimpImageParasiteView
modifier|*
name|view
init|=
name|GIMP_IMAGE_PARASITE_VIEW
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
name|PROP_PARASITE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|view
operator|->
name|parasite
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|view
operator|->
name|image
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
name|GObject
modifier|*
DECL|function|gimp_image_parasite_view_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_image_parasite_view_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GimpImageParasiteView
modifier|*
name|view
decl_stmt|;
name|GObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_IMAGE_PARASITE_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|view
operator|->
name|parasite
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|view
operator|->
name|image
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|view
operator|->
name|image
argument_list|,
literal|"parasite-attached"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_parasite_view_parasite_changed
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|view
operator|->
name|image
argument_list|,
literal|"parasite-detached"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_parasite_view_parasite_changed
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|gimp_image_parasite_view_update
argument_list|(
name|view
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_parasite_view_finalize (GObject * object)
name|gimp_image_parasite_view_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageParasiteView
modifier|*
name|view
init|=
name|GIMP_IMAGE_PARASITE_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|view
operator|->
name|parasite
condition|)
block|{
name|g_free
argument_list|(
name|view
operator|->
name|parasite
argument_list|)
expr_stmt|;
name|view
operator|->
name|parasite
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
name|GimpImage
modifier|*
DECL|function|gimp_image_parasite_view_get_image (GimpImageParasiteView * view)
name|gimp_image_parasite_view_get_image
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE_PARASITE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|view
operator|->
name|image
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_image_parasite_view_parasite_changed (GimpImageParasiteView * view,const gchar * name)
name|gimp_image_parasite_view_parasite_changed
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
if|if
condition|(
name|name
operator|&&
name|view
operator|->
name|parasite
operator|&&
name|strcmp
argument_list|(
name|name
argument_list|,
name|view
operator|->
name|parasite
argument_list|)
operator|==
literal|0
condition|)
name|gimp_image_parasite_view_update
argument_list|(
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_parasite_view_update (GimpImageParasiteView * view)
name|gimp_image_parasite_view_update
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
block|{
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|view_signals
index|[
name|UPDATE
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

