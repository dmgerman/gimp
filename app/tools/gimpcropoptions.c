begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets/gimppropwidgets.h"
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
DECL|enum|__anon2a096ab00103
block|{
DECL|enumerator|PROP_LAYER_ONLY
name|PROP_LAYER_ONLY
init|=
name|GIMP_RECTANGLE_OPTIONS_PROP_LAST
operator|+
literal|1
block|,
DECL|enumerator|PROP_ALLOW_GROWING
name|PROP_ALLOW_GROWING
block|,
DECL|enumerator|PROP_FILL_TYPE
name|PROP_FILL_TYPE
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

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpCropOptions,gimp_crop_options,GIMP_TYPE_TOOL_OPTIONS,G_IMPLEMENT_INTERFACE (GIMP_TYPE_RECTANGLE_OPTIONS,gimp_crop_options_rectangle_options_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpCropOptions
argument_list|,
argument|gimp_crop_options
argument_list|,
argument|GIMP_TYPE_TOOL_OPTIONS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_RECTANGLE_OPTIONS,                                                 gimp_crop_options_rectangle_options_iface_init)
argument_list|)
end_macro

begin_function
specifier|static
name|void
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
comment|/* The 'highlight' property is defined here because we want different    * default values for the Crop and the Rectangle Select tools.    */
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|GIMP_RECTANGLE_OPTIONS_PROP_HIGHLIGHT
argument_list|,
literal|"highlight"
argument_list|,
name|_
argument_list|(
literal|"Highlight"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Dim everything outside selection"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_LAYER_ONLY
argument_list|,
literal|"layer-only"
argument_list|,
name|_
argument_list|(
literal|"Current layer only"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Crop only currently selected layer"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ALLOW_GROWING
argument_list|,
literal|"allow-growing"
argument_list|,
name|_
argument_list|(
literal|"Allow growing"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Allow resizing canvas by dragging cropping frame "
literal|"beyond image boundary"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_FILL_TYPE
argument_list|,
literal|"fill-type"
argument_list|,
name|_
argument_list|(
literal|"Fill with"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"How to fill new areas created by 'Allow growing'"
argument_list|)
argument_list|,
name|GIMP_TYPE_FILL_TYPE
argument_list|,
name|GIMP_FILL_TRANSPARENT
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
name|PROP_ALLOW_GROWING
case|:
name|options
operator|->
name|allow_growing
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILL_TYPE
case|:
name|options
operator|->
name|fill_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
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
name|PROP_ALLOW_GROWING
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|allow_growing
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILL_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|fill_type
argument_list|)
expr_stmt|;
break|break;
default|default:
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
init|=
name|gimp_tool_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox_rectangle
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
comment|/*  layer toggle  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"layer-only"
argument_list|,
name|NULL
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
comment|/*  fill type combo  */
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"fill-type"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_label
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Fill with"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  allow growing toggle/frame  */
name|frame
operator|=
name|gimp_prop_expanding_frame_new
argument_list|(
name|config
argument_list|,
literal|"allow-growing"
argument_list|,
name|NULL
argument_list|,
name|combo
argument_list|,
name|NULL
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

