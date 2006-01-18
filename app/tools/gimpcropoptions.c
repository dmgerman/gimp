begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangleoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpcropoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2ab145e60103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_HIGHLIGHT
name|PROP_HIGHLIGHT
block|,
DECL|enumerator|PROP_FIXED_WIDTH
name|PROP_FIXED_WIDTH
block|,
DECL|enumerator|PROP_WIDTH
name|PROP_WIDTH
block|,
DECL|enumerator|PROP_FIXED_HEIGHT
name|PROP_FIXED_HEIGHT
block|,
DECL|enumerator|PROP_HEIGHT
name|PROP_HEIGHT
block|,
DECL|enumerator|PROP_FIXED_ASPECT
name|PROP_FIXED_ASPECT
block|,
DECL|enumerator|PROP_ASPECT
name|PROP_ASPECT
block|,
DECL|enumerator|PROP_FIXED_CENTER
name|PROP_FIXED_CENTER
block|,
DECL|enumerator|PROP_CENTER_X
name|PROP_CENTER_X
block|,
DECL|enumerator|PROP_CENTER_Y
name|PROP_CENTER_Y
block|,
DECL|enumerator|PROP_UNIT
name|PROP_UNIT
block|,
DECL|enumerator|PROP_LAYER_ONLY
name|PROP_LAYER_ONLY
block|,
DECL|enumerator|PROP_CROP_MODE
name|PROP_CROP_MODE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_crop_options_rectangle_options_iface_init
parameter_list|(
name|GimpRectangleOptionsInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_options_set_property
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
name|gimp_crop_options_get_property
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

begin_expr_stmt
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
name|GimpCropOptions
argument_list|,
name|gimp_crop_options
argument_list|,
name|GIMP_TYPE_TOOL_OPTIONS
argument_list|,
name|G_IMPLEMENT_INTERFACE
argument_list|(
name|GIMP_TYPE_RECTANGLE_OPTIONS
argument_list|,
name|gimp_crop_options_rectangle_options_iface_init
argument_list|)
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_crop_options_class_init (GimpCropOptionsClass * klass)
name|gimp_crop_options_class_init
parameter_list|(
name|GimpCropOptionsClass
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
name|gimp_crop_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_crop_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_LAYER_ONLY
argument_list|,
literal|"layer-only"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_CROP_MODE
argument_list|,
literal|"crop-mode"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CROP_MODE
argument_list|,
name|GIMP_CROP_MODE_CROP
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|gimp_rectangle_options_install_properties
argument_list|(
name|object_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_options_init (GimpCropOptions * options)
name|gimp_crop_options_init
parameter_list|(
name|GimpCropOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_options_rectangle_options_iface_init (GimpRectangleOptionsInterface * iface)
name|gimp_crop_options_rectangle_options_iface_init
parameter_list|(
name|GimpRectangleOptionsInterface
modifier|*
name|iface
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_crop_options_set_property
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
name|GimpCropOptions
modifier|*
name|options
init|=
name|GIMP_CROP_OPTIONS
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
name|GIMP_RECTANGLE_OPTIONS_PROP_HIGHLIGHT
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_WIDTH
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_WIDTH
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_HEIGHT
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_HEIGHT
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_ASPECT
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_ASPECT
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_CENTER
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_CENTER_X
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_CENTER_Y
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_UNIT
case|:
name|gimp_rectangle_options_set_property
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|value
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LAYER_ONLY
case|:
name|options
operator|->
name|layer_only
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CROP_MODE
case|:
name|options
operator|->
name|crop_mode
operator|=
name|g_value_get_enum
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
DECL|function|gimp_crop_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_crop_options_get_property
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
name|GimpCropOptions
modifier|*
name|options
init|=
name|GIMP_CROP_OPTIONS
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
name|GIMP_RECTANGLE_OPTIONS_PROP_HIGHLIGHT
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_WIDTH
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_WIDTH
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_HEIGHT
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_HEIGHT
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_ASPECT
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_ASPECT
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_CENTER
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_CENTER_X
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_CENTER_Y
case|:
case|case
name|GIMP_RECTANGLE_OPTIONS_PROP_UNIT
case|:
name|gimp_rectangle_options_get_property
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|value
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LAYER_ONLY
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|layer_only
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CROP_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|crop_mode
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
name|GtkWidget
modifier|*
DECL|function|gimp_crop_options_gui (GimpToolOptions * tool_options)
name|gimp_crop_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox_rectangle
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|vbox
operator|=
name|gimp_tool_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
comment|/*  tool toggle  */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Tool Toggle  (%s)"
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|GDK_CONTROL_MASK
argument_list|)
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"crop-mode"
argument_list|,
name|str
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
comment|/*  layer toggle  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"layer-only"
argument_list|,
name|_
argument_list|(
literal|"Current layer only"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
comment|/*  rectangle options  */
name|vbox_rectangle
operator|=
name|gimp_rectangle_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|vbox_rectangle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox_rectangle
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

