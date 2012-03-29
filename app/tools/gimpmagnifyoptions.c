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
file|"config/gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpmagnifyoptions.h"
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
DECL|enum|__anon2ac08ab20103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_AUTO_RESIZE
name|PROP_AUTO_RESIZE
block|,
DECL|enumerator|PROP_ZOOM_TYPE
name|PROP_ZOOM_TYPE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_magnify_options_set_property
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
name|gimp_magnify_options_get_property
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
name|gimp_magnify_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpMagnifyOptions,gimp_magnify_options,GIMP_TYPE_TOOL_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMagnifyOptions
argument_list|,
argument|gimp_magnify_options
argument_list|,
argument|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_magnify_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_magnify_options_class_init
parameter_list|(
name|GimpMagnifyOptionsClass
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
name|GimpToolOptionsClass
modifier|*
name|options_class
init|=
name|GIMP_TOOL_OPTIONS_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_magnify_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_magnify_options_get_property
expr_stmt|;
name|options_class
operator|->
name|reset
operator|=
name|gimp_magnify_options_reset
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_AUTO_RESIZE
argument_list|,
literal|"auto-resize"
argument_list|,
name|N_
argument_list|(
literal|"Resize image window to accommodate "
literal|"new zoom level"
argument_list|)
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
name|PROP_ZOOM_TYPE
argument_list|,
literal|"zoom-type"
argument_list|,
name|N_
argument_list|(
literal|"Direction of magnification"
argument_list|)
argument_list|,
name|GIMP_TYPE_ZOOM_TYPE
argument_list|,
name|GIMP_ZOOM_IN
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_options_init (GimpMagnifyOptions * options)
name|gimp_magnify_options_init
parameter_list|(
name|GimpMagnifyOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_magnify_options_set_property
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
name|GimpMagnifyOptions
modifier|*
name|options
init|=
name|GIMP_MAGNIFY_OPTIONS
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
name|PROP_AUTO_RESIZE
case|:
name|options
operator|->
name|auto_resize
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ZOOM_TYPE
case|:
name|options
operator|->
name|zoom_type
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
DECL|function|gimp_magnify_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_magnify_options_get_property
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
name|GimpMagnifyOptions
modifier|*
name|options
init|=
name|GIMP_MAGNIFY_OPTIONS
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
name|PROP_AUTO_RESIZE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|auto_resize
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ZOOM_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|zoom_type
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
DECL|function|gimp_magnify_options_reset (GimpToolOptions * tool_options)
name|gimp_magnify_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|tool_options
argument_list|)
argument_list|,
literal|"auto-resize"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pspec
condition|)
name|G_PARAM_SPEC_BOOLEAN
argument_list|(
name|pspec
argument_list|)
operator|->
name|default_value
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|tool_options
operator|->
name|tool_info
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|resize_windows_on_zoom
expr_stmt|;
name|GIMP_TOOL_OPTIONS_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|reset
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_magnify_options_gui (GimpToolOptions * tool_options)
name|gimp_magnify_options_gui
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
name|GdkModifierType
name|toggle_mask
decl_stmt|;
name|toggle_mask
operator|=
name|gimp_get_toggle_behavior_mask
argument_list|()
expr_stmt|;
comment|/*  the auto_resize toggle button  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"auto-resize"
argument_list|,
name|_
argument_list|(
literal|"Auto-resize window"
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
comment|/*  tool toggle  */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Direction  (%s)"
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
literal|"zoom-type"
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
return|return
name|vbox
return|;
block|}
end_function

end_unit

