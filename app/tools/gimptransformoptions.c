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
file|"config/gimpcoreconfig.h"
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
file|"gimprotatetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpscaletool.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimptransformoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a285a8b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TYPE
name|PROP_TYPE
block|,
DECL|enumerator|PROP_DIRECTION
name|PROP_DIRECTION
block|,
DECL|enumerator|PROP_INTERPOLATION
name|PROP_INTERPOLATION
block|,
DECL|enumerator|PROP_CLIP
name|PROP_CLIP
block|,
DECL|enumerator|PROP_PREVIEW_TYPE
name|PROP_PREVIEW_TYPE
block|,
DECL|enumerator|PROP_PREVIEW_OPACITY
name|PROP_PREVIEW_OPACITY
block|,
DECL|enumerator|PROP_GRID_TYPE
name|PROP_GRID_TYPE
block|,
DECL|enumerator|PROP_GRID_SIZE
name|PROP_GRID_SIZE
block|,
DECL|enumerator|PROP_CONSTRAIN
name|PROP_CONSTRAIN
block|, }
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_transform_options_set_property
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
name|gimp_transform_options_get_property
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
name|gimp_transform_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_transform_options_preview_notify
parameter_list|(
name|GimpTransformOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_transform_options_preview_opacity_notify
parameter_list|(
name|GimpTransformOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|table
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTransformOptions,gimp_transform_options,GIMP_TYPE_TOOL_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTransformOptions
argument_list|,
argument|gimp_transform_options
argument_list|,
argument|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_transform_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_transform_options_class_init
parameter_list|(
name|GimpTransformOptionsClass
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
name|gimp_transform_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_transform_options_get_property
expr_stmt|;
name|options_class
operator|->
name|reset
operator|=
name|gimp_transform_options_reset
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_TYPE
argument_list|,
literal|"type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TRANSFORM_TYPE
argument_list|,
name|GIMP_TRANSFORM_TYPE_LAYER
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_DIRECTION
argument_list|,
literal|"direction"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TRANSFORM_DIRECTION
argument_list|,
name|GIMP_TRANSFORM_FORWARD
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_INTERPOLATION
argument_list|,
literal|"interpolation"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_INTERPOLATION_TYPE
argument_list|,
name|GIMP_INTERPOLATION_LINEAR
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_CLIP
argument_list|,
literal|"clip"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TRANSFORM_RESIZE
argument_list|,
name|GIMP_TRANSFORM_RESIZE_ADJUST
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_PREVIEW_TYPE
argument_list|,
literal|"preview-type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TRANSFORM_PREVIEW_TYPE
argument_list|,
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_PREVIEW_OPACITY
argument_list|,
literal|"preview-opacity"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_GRID_TYPE
argument_list|,
literal|"grid-type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TRANSFORM_GRID_TYPE
argument_list|,
name|GIMP_TRANSFORM_GRID_TYPE_N_LINES
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_GRID_SIZE
argument_list|,
literal|"grid-size"
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
literal|128
argument_list|,
literal|15
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_CONSTRAIN
argument_list|,
literal|"constrain"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_options_init (GimpTransformOptions * options)
name|gimp_transform_options_init
parameter_list|(
name|GimpTransformOptions
modifier|*
name|options
parameter_list|)
block|{
name|options
operator|->
name|recursion_level
operator|=
literal|3
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_transform_options_set_property
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
name|GimpTransformOptions
modifier|*
name|options
init|=
name|GIMP_TRANSFORM_OPTIONS
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
name|PROP_TYPE
case|:
name|options
operator|->
name|type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DIRECTION
case|:
name|options
operator|->
name|direction
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INTERPOLATION
case|:
name|options
operator|->
name|interpolation
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CLIP
case|:
name|options
operator|->
name|clip
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_TYPE
case|:
name|options
operator|->
name|preview_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_OPACITY
case|:
name|options
operator|->
name|preview_opacity
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRID_TYPE
case|:
name|options
operator|->
name|grid_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRID_SIZE
case|:
name|options
operator|->
name|grid_size
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONSTRAIN
case|:
name|options
operator|->
name|constrain
operator|=
name|g_value_get_boolean
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
DECL|function|gimp_transform_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_transform_options_get_property
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
name|GimpTransformOptions
modifier|*
name|options
init|=
name|GIMP_TRANSFORM_OPTIONS
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
name|PROP_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DIRECTION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|direction
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INTERPOLATION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|interpolation
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CLIP
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|clip
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|preview_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_OPACITY
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|preview_opacity
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRID_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|grid_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRID_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|grid_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONSTRAIN
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|constrain
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
DECL|function|gimp_transform_options_reset (GimpToolOptions * tool_options)
name|gimp_transform_options_reset
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
literal|"interpolation"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pspec
condition|)
name|G_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
operator|->
name|default_value
operator|=
name|tool_options
operator|->
name|tool_info
operator|->
name|gimp
operator|->
name|config
operator|->
name|interpolation_type
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

begin_comment
comment|/**  * gimp_transform_options_gui:  * @tool_options: a #GimpToolOptions  *  * Build the Transform Tool Options.  *  * Return value: a container holding the transform tool options  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_transform_options_gui (GimpToolOptions * tool_options)
name|gimp_transform_options_gui
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
name|GimpTransformOptions
modifier|*
name|options
init|=
name|GIMP_TRANSFORM_OPTIONS
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
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|preview_box
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|constrain
init|=
name|NULL
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Transform:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|box
operator|=
name|gimp_prop_enum_stock_box_new
argument_list|(
name|config
argument_list|,
literal|"type"
argument_list|,
literal|"gimp"
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
name|hbox
argument_list|)
argument_list|,
name|box
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
name|box
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"direction"
argument_list|,
name|_
argument_list|(
literal|"Direction"
argument_list|)
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
comment|/*  the interpolation menu  */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Interpolation:"
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
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"interpolation"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|combo
argument_list|)
expr_stmt|;
comment|/*  the clipping menu  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Clipping:"
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
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"clip"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|combo
argument_list|)
expr_stmt|;
comment|/*  the preview frame  */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
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
comment|/*  the preview type menu  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Preview:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"preview-type"
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
name|hbox
argument_list|)
argument_list|,
name|combo
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|combo
argument_list|)
expr_stmt|;
name|preview_box
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|preview_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview_box
argument_list|)
expr_stmt|;
comment|/*  the preview opacity scale  */
name|scale
operator|=
name|gimp_prop_opacity_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"preview-opacity"
argument_list|,
name|_
argument_list|(
literal|"Opacity"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|preview_box
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify::preview-type"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_transform_options_preview_opacity_notify
argument_list|)
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|gimp_transform_options_preview_opacity_notify
argument_list|(
name|options
argument_list|,
name|NULL
argument_list|,
name|scale
argument_list|)
expr_stmt|;
comment|/*  the grid type menu  */
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"grid-type"
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
name|preview_box
argument_list|)
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify::preview-type"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_transform_options_preview_notify
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|gimp_transform_options_preview_notify
argument_list|(
name|options
argument_list|,
name|NULL
argument_list|,
name|combo
argument_list|)
expr_stmt|;
comment|/*  the grid density scale  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"grid-size"
argument_list|,
name|NULL
argument_list|,
literal|1.8
argument_list|,
literal|8.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|preview_box
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify::preview-type"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_transform_options_preview_notify
argument_list|)
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|gimp_transform_options_preview_notify
argument_list|(
name|options
argument_list|,
name|NULL
argument_list|,
name|scale
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_ROTATE_TOOL
condition|)
block|{
name|constrain
operator|=
operator|(
name|_
argument_list|(
literal|"15 degrees  (%s)"
argument_list|)
operator|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_SCALE_TOOL
condition|)
block|{
name|constrain
operator|=
operator|(
name|_
argument_list|(
literal|"Keep aspect  (%s)"
argument_list|)
operator|)
expr_stmt|;
block|}
if|if
condition|(
name|constrain
condition|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
name|constrain
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|GDK_CONTROL_MASK
argument_list|)
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"constrain"
argument_list|,
name|label
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
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
return|return
name|vbox
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_transform_options_show_preview (GimpTransformOptions * options)
name|gimp_transform_options_show_preview
parameter_list|(
name|GimpTransformOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TRANSFORM_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
operator|(
operator|(
name|options
operator|->
name|preview_type
operator|==
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE
operator|||
name|options
operator|->
name|preview_type
operator|==
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE_GRID
operator|)
operator|&&
name|options
operator|->
name|type
operator|==
name|GIMP_TRANSFORM_TYPE_LAYER
operator|&&
name|options
operator|->
name|direction
operator|==
name|GIMP_TRANSFORM_FORWARD
operator|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_transform_options_preview_notify (GimpTransformOptions * options,GParamSpec * pspec,GtkWidget * widget)
name|gimp_transform_options_preview_notify
parameter_list|(
name|GimpTransformOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|widget
argument_list|,
name|options
operator|->
name|preview_type
operator|==
name|GIMP_TRANSFORM_PREVIEW_TYPE_GRID
operator|||
name|options
operator|->
name|preview_type
operator|==
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE_GRID
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_options_preview_opacity_notify (GimpTransformOptions * options,GParamSpec * pspec,GtkWidget * widget)
name|gimp_transform_options_preview_opacity_notify
parameter_list|(
name|GimpTransformOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|widget
argument_list|,
name|options
operator|->
name|preview_type
operator|==
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE
operator|||
name|options
operator|->
name|preview_type
operator|==
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE_GRID
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

