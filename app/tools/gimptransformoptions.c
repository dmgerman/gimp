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
file|"gimpunifiedtransformtool.h"
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
DECL|enum|__anon293617720103
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
DECL|enumerator|PROP_SHOW_PREVIEW
name|PROP_SHOW_PREVIEW
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
block|,
DECL|enumerator|PROP_KEEPASPECT
name|PROP_KEEPASPECT
block|,
DECL|enumerator|PROP_FROMPIVOT
name|PROP_FROMPIVOT
block|,
DECL|enumerator|PROP_FREESHEAR
name|PROP_FREESHEAR
block|,
DECL|enumerator|PROP_CORNERSNAP
name|PROP_CORNERSNAP
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
name|gboolean
name|gimp_transform_options_sync_grid
parameter_list|(
name|GBinding
modifier|*
name|binding
parameter_list|,
specifier|const
name|GValue
modifier|*
name|source_value
parameter_list|,
name|GValue
modifier|*
name|target_value
parameter_list|,
name|gpointer
name|user_data
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
name|N_
argument_list|(
literal|"Direction of transformation"
argument_list|)
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
name|N_
argument_list|(
literal|"Interpolation method"
argument_list|)
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
name|N_
argument_list|(
literal|"How to clip"
argument_list|)
argument_list|,
name|GIMP_TYPE_TRANSFORM_RESIZE
argument_list|,
name|GIMP_TRANSFORM_RESIZE_ADJUST
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_PREVIEW
argument_list|,
literal|"show-preview"
argument_list|,
name|N_
argument_list|(
literal|"Show a preview of the transformed image"
argument_list|)
argument_list|,
name|TRUE
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
name|N_
argument_list|(
literal|"Opacity of the preview image"
argument_list|)
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
name|N_
argument_list|(
literal|"Composition guides such as rule of thirds"
argument_list|)
argument_list|,
name|GIMP_TYPE_GUIDES_TYPE
argument_list|,
name|GIMP_GUIDES_N_LINES
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
name|N_
argument_list|(
literal|"Size of a grid cell for variable number of composition guides"
argument_list|)
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
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_KEEPASPECT
argument_list|,
literal|"keepaspect"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_FROMPIVOT
argument_list|,
literal|"frompivot"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_FREESHEAR
argument_list|,
literal|"freeshear"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_CORNERSNAP
argument_list|,
literal|"cornersnap"
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
name|PROP_SHOW_PREVIEW
case|:
name|options
operator|->
name|show_preview
operator|=
name|g_value_get_boolean
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
case|case
name|PROP_KEEPASPECT
case|:
name|options
operator|->
name|keepaspect
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FROMPIVOT
case|:
name|options
operator|->
name|frompivot
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FREESHEAR
case|:
name|options
operator|->
name|freeshear
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CORNERSNAP
case|:
name|options
operator|->
name|cornersnap
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
name|PROP_SHOW_PREVIEW
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|show_preview
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
case|case
name|PROP_KEEPASPECT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|keepaspect
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FROMPIVOT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|frompivot
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FREESHEAR
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|freeshear
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CORNERSNAP
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|cornersnap
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
name|grid_box
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|constrain_label
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|constrain_tip
init|=
name|NULL
decl_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
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
literal|"Image opacity"
argument_list|)
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_expanding_frame_new
argument_list|(
name|config
argument_list|,
literal|"show-preview"
argument_list|,
name|_
argument_list|(
literal|"Show image preview"
argument_list|)
argument_list|,
name|scale
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
comment|/*  the guides frame  */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Guides"
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
name|grid_box
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
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
name|grid_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|grid_box
argument_list|)
expr_stmt|;
comment|/*  the guides type menu  */
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
name|grid_box
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
name|grid_box
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
name|g_object_bind_property_full
argument_list|(
name|config
argument_list|,
literal|"grid-type"
argument_list|,
name|scale
argument_list|,
literal|"visible"
argument_list|,
name|G_BINDING_SYNC_CREATE
argument_list|,
name|gimp_transform_options_sync_grid
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|constrain_label
operator|=
name|_
argument_list|(
literal|"15 degrees  (%s)"
argument_list|)
expr_stmt|;
name|constrain_tip
operator|=
name|_
argument_list|(
literal|"Limit rotation steps to 15 degrees"
argument_list|)
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
name|constrain_label
operator|=
name|_
argument_list|(
literal|"Keep aspect  (%s)"
argument_list|)
expr_stmt|;
name|constrain_tip
operator|=
name|_
argument_list|(
literal|"Keep the original aspect ratio"
argument_list|)
expr_stmt|;
block|}
comment|/* The constrain behaviour is not what is in the spec, it would make the help labels essays */
comment|/* spec:    * constrain move,rotate,perspective = ctrl    * from centre scale,shear = ctrl    * centre/corner rotate = ctrl    * keep aspect scale = shift    * free shear = shift    * real life:    * constrain move,rotate,perspective,scale(aspect),shear,rotation axis = ctrl    * from centre scale, shear = shift    */
comment|//TODO: check that the selection tools use the gimp_get_*_mask() functions for constrain/etc or change to what they use
elseif|else
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_UNIFIED_TRANSFORM_TOOL
condition|)
block|{
DECL|struct|__anon293617720208
struct|struct
block|{
DECL|member|shift
name|gboolean
name|shift
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|desc
name|gchar
modifier|*
name|desc
decl_stmt|;
block|}
name|opt_list
index|[]
init|=
block|{
block|{
name|TRUE
block|,
literal|"keepaspect"
block|,
literal|"Keep aspect (%s)"
block|}
block|,
block|{
name|TRUE
block|,
literal|"freeshear"
block|,
literal|"Move edge freely in shearing (%s)"
block|}
block|,
block|{
name|FALSE
block|,
literal|"frompivot"
block|,
literal|"Scale from pivot / Symmetric shearing (%s)"
block|}
block|,
block|{
name|FALSE
block|,
literal|"cornersnap"
block|,
literal|"Snap pivot point to corners/center (%s)"
block|}
block|,
block|{
name|FALSE
block|,
literal|"constrain"
block|,
literal|"Constrain movement (%s)"
block|}
block|,       }
struct|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|5
condition|;
name|i
operator|++
control|)
block|{
name|label
operator|=
name|g_strdup_printf
argument_list|(
name|opt_list
index|[
name|i
index|]
operator|.
name|desc
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|opt_list
index|[
name|i
index|]
operator|.
name|shift
condition|?
name|gimp_get_extend_selection_mask
argument_list|()
else|:
name|gimp_get_constrain_behavior_mask
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
name|opt_list
index|[
name|i
index|]
operator|.
name|name
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
block|}
if|if
condition|(
name|constrain_label
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
name|GdkModifierType
name|constrain_mask
decl_stmt|;
name|constrain_mask
operator|=
name|gimp_get_constrain_behavior_mask
argument_list|()
expr_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
name|constrain_label
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|constrain_mask
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
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|constrain_tip
argument_list|,
name|NULL
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
name|options
operator|->
name|show_preview
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
name|gboolean
DECL|function|gimp_transform_options_sync_grid (GBinding * binding,const GValue * source_value,GValue * target_value,gpointer user_data)
name|gimp_transform_options_sync_grid
parameter_list|(
name|GBinding
modifier|*
name|binding
parameter_list|,
specifier|const
name|GValue
modifier|*
name|source_value
parameter_list|,
name|GValue
modifier|*
name|target_value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpGuidesType
name|type
init|=
name|g_value_get_enum
argument_list|(
name|source_value
argument_list|)
decl_stmt|;
name|g_value_set_boolean
argument_list|(
name|target_value
argument_list|,
name|type
operator|==
name|GIMP_GUIDES_N_LINES
operator|||
name|type
operator|==
name|GIMP_GUIDES_SPACING
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

