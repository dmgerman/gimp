begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpcolorpickeroptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c261acc0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SAMPLE_AVERAGE
name|PROP_SAMPLE_AVERAGE
block|,
comment|/* overrides a GimpColorOptions property */
DECL|enumerator|PROP_PICK_TARGET
name|PROP_PICK_TARGET
block|,
DECL|enumerator|PROP_USE_INFO_WINDOW
name|PROP_USE_INFO_WINDOW
block|,
DECL|enumerator|PROP_FRAME1_MODE
name|PROP_FRAME1_MODE
block|,
DECL|enumerator|PROP_FRAME2_MODE
name|PROP_FRAME2_MODE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_options_set_property
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
name|gimp_color_picker_options_get_property
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
DECL|function|G_DEFINE_TYPE (GimpColorPickerOptions,gimp_color_picker_options,GIMP_TYPE_COLOR_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorPickerOptions
argument_list|,
argument|gimp_color_picker_options
argument_list|,
argument|GIMP_TYPE_COLOR_OPTIONS
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_color_picker_options_class_init
parameter_list|(
name|GimpColorPickerOptionsClass
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
name|gimp_color_picker_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_color_picker_options_get_property
expr_stmt|;
comment|/* override a GimpColorOptions property to get a different default value */
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SAMPLE_AVERAGE
argument_list|,
literal|"sample-average"
argument_list|,
name|_
argument_list|(
literal|"Sample average"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Use averaged color value from "
literal|"nearby pixels"
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
name|PROP_PICK_TARGET
argument_list|,
literal|"pick-target"
argument_list|,
name|_
argument_list|(
literal|"Pick Target"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Choose what the color picker will do"
argument_list|)
argument_list|,
name|GIMP_TYPE_COLOR_PICK_TARGET
argument_list|,
name|GIMP_COLOR_PICK_TARGET_FOREGROUND
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_INFO_WINDOW
argument_list|,
literal|"use-info-window"
argument_list|,
name|_
argument_list|(
literal|"Use info window"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Open a floating dialog to view picked "
literal|"color values in various color models"
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
name|PROP_FRAME1_MODE
argument_list|,
literal|"frame1-mode"
argument_list|,
literal|"Frame 1 Mode"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_COLOR_PICK_MODE
argument_list|,
name|GIMP_COLOR_PICK_MODE_PIXEL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_FRAME2_MODE
argument_list|,
literal|"frame2-mode"
argument_list|,
literal|"Frame 2 Mode"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_COLOR_PICK_MODE
argument_list|,
name|GIMP_COLOR_PICK_MODE_RGB_PERCENT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_options_init (GimpColorPickerOptions * options)
name|gimp_color_picker_options_init
parameter_list|(
name|GimpColorPickerOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_color_picker_options_set_property
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
name|GimpColorPickerOptions
modifier|*
name|options
init|=
name|GIMP_COLOR_PICKER_OPTIONS
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
name|PROP_SAMPLE_AVERAGE
case|:
name|GIMP_COLOR_OPTIONS
argument_list|(
name|options
argument_list|)
operator|->
name|sample_average
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PICK_TARGET
case|:
name|options
operator|->
name|pick_target
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_INFO_WINDOW
case|:
name|options
operator|->
name|use_info_window
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FRAME1_MODE
case|:
name|options
operator|->
name|frame1_mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FRAME2_MODE
case|:
name|options
operator|->
name|frame2_mode
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
DECL|function|gimp_color_picker_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_color_picker_options_get_property
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
name|GimpColorPickerOptions
modifier|*
name|options
init|=
name|GIMP_COLOR_PICKER_OPTIONS
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
name|PROP_SAMPLE_AVERAGE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|GIMP_COLOR_OPTIONS
argument_list|(
name|options
argument_list|)
operator|->
name|sample_average
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PICK_TARGET
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|pick_target
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_INFO_WINDOW
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|use_info_window
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FRAME1_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|frame1_mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FRAME2_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|frame2_mode
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
DECL|function|gimp_color_picker_options_gui (GimpToolOptions * tool_options)
name|gimp_color_picker_options_gui
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
name|gimp_color_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|GdkModifierType
name|extend_mask
init|=
name|gimp_get_extend_selection_mask
argument_list|()
decl_stmt|;
name|GdkModifierType
name|toggle_mask
init|=
name|gimp_get_toggle_behavior_mask
argument_list|()
decl_stmt|;
comment|/*  the sample merged toggle button  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"sample-merged"
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
comment|/*  the pick FG/BG frame  */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Pick Target  (%s)"
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|toggle_mask
argument_list|)
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"pick-target"
argument_list|,
name|str
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
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
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
comment|/*  the use_info_window toggle button  */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Use info window  (%s)"
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|extend_mask
argument_list|)
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"use-info-window"
argument_list|,
name|str
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
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

