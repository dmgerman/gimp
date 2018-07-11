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
file|"core/gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-gradients.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewablebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradientoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2bfd02630103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_OFFSET
name|PROP_OFFSET
block|,
DECL|enumerator|PROP_GRADIENT_TYPE
name|PROP_GRADIENT_TYPE
block|,
DECL|enumerator|PROP_DISTANCE_METRIC
name|PROP_DISTANCE_METRIC
block|,
DECL|enumerator|PROP_GRADIENT_REPEAT
name|PROP_GRADIENT_REPEAT
block|,
comment|/*  overrides a GimpPaintOptions property  */
DECL|enumerator|PROP_SUPERSAMPLE
name|PROP_SUPERSAMPLE
block|,
DECL|enumerator|PROP_SUPERSAMPLE_DEPTH
name|PROP_SUPERSAMPLE_DEPTH
block|,
DECL|enumerator|PROP_SUPERSAMPLE_THRESHOLD
name|PROP_SUPERSAMPLE_THRESHOLD
block|,
DECL|enumerator|PROP_DITHER
name|PROP_DITHER
block|,
DECL|enumerator|PROP_INSTANT
name|PROP_INSTANT
block|,
DECL|enumerator|PROP_MODIFY_ACTIVE
name|PROP_MODIFY_ACTIVE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_gradient_options_set_property
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
name|gimp_gradient_options_get_property
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
name|gradient_options_repeat_gradient_type_notify
parameter_list|(
name|GimpGradientOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|repeat_combo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gradient_options_metric_gradient_type_notify
parameter_list|(
name|GimpGradientOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|repeat_combo
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpGradientOptions,gimp_gradient_options,GIMP_TYPE_PAINT_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGradientOptions
argument_list|,
argument|gimp_gradient_options
argument_list|,
argument|GIMP_TYPE_PAINT_OPTIONS
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_gradient_options_class_init
parameter_list|(
name|GimpGradientOptionsClass
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
name|gimp_gradient_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_gradient_options_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_OFFSET
argument_list|,
literal|"offset"
argument_list|,
name|_
argument_list|(
literal|"Offset"
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_TYPE
argument_list|,
literal|"gradient-type"
argument_list|,
name|_
argument_list|(
literal|"Shape"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GRADIENT_TYPE
argument_list|,
name|GIMP_GRADIENT_LINEAR
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_DISTANCE_METRIC
argument_list|,
literal|"distance-metric"
argument_list|,
name|_
argument_list|(
literal|"Metric"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Metric to use for the distance calculation"
argument_list|)
argument_list|,
name|GEGL_TYPE_DISTANCE_METRIC
argument_list|,
name|GEGL_DISTANCE_METRIC_EUCLIDEAN
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_REPEAT
argument_list|,
literal|"gradient-repeat"
argument_list|,
name|_
argument_list|(
literal|"Repeat"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_REPEAT_MODE
argument_list|,
name|GIMP_REPEAT_NONE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SUPERSAMPLE
argument_list|,
literal|"supersample"
argument_list|,
name|_
argument_list|(
literal|"Adaptive Supersampling"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_SUPERSAMPLE_DEPTH
argument_list|,
literal|"supersample-depth"
argument_list|,
name|_
argument_list|(
literal|"Max depth"
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
literal|9
argument_list|,
literal|3
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_SUPERSAMPLE_THRESHOLD
argument_list|,
literal|"supersample-threshold"
argument_list|,
name|_
argument_list|(
literal|"Threshold"
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|4.0
argument_list|,
literal|0.2
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DITHER
argument_list|,
literal|"dither"
argument_list|,
name|_
argument_list|(
literal|"Dithering"
argument_list|)
argument_list|,
name|NULL
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
name|PROP_INSTANT
argument_list|,
literal|"instant"
argument_list|,
name|_
argument_list|(
literal|"Instant mode"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Commit gradient instantly"
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
name|PROP_MODIFY_ACTIVE
argument_list|,
literal|"modify-active"
argument_list|,
name|_
argument_list|(
literal|"Modify active gradient"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Modify the active gradient in-place"
argument_list|)
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
DECL|function|gimp_gradient_options_init (GimpGradientOptions * options)
name|gimp_gradient_options_init
parameter_list|(
name|GimpGradientOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_gradient_options_set_property
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
name|GimpGradientOptions
modifier|*
name|options
init|=
name|GIMP_GRADIENT_OPTIONS
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
name|PROP_OFFSET
case|:
name|options
operator|->
name|offset
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_TYPE
case|:
name|options
operator|->
name|gradient_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISTANCE_METRIC
case|:
name|options
operator|->
name|distance_metric
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_REPEAT
case|:
name|GIMP_PAINT_OPTIONS
argument_list|(
name|options
argument_list|)
operator|->
name|gradient_options
operator|->
name|gradient_repeat
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE
case|:
name|options
operator|->
name|supersample
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE_DEPTH
case|:
name|options
operator|->
name|supersample_depth
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE_THRESHOLD
case|:
name|options
operator|->
name|supersample_threshold
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DITHER
case|:
name|options
operator|->
name|dither
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INSTANT
case|:
name|options
operator|->
name|instant
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MODIFY_ACTIVE
case|:
name|options
operator|->
name|modify_active
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
DECL|function|gimp_gradient_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_gradient_options_get_property
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
name|GimpGradientOptions
modifier|*
name|options
init|=
name|GIMP_GRADIENT_OPTIONS
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
name|PROP_OFFSET
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|offset
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|gradient_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISTANCE_METRIC
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|distance_metric
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_REPEAT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|GIMP_PAINT_OPTIONS
argument_list|(
name|options
argument_list|)
operator|->
name|gradient_options
operator|->
name|gradient_repeat
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|supersample
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE_DEPTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|supersample_depth
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE_THRESHOLD
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|supersample_threshold
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DITHER
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|dither
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INSTANT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|instant
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MODIFY_ACTIVE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|modify_active
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
DECL|function|gimp_gradient_options_gui (GimpToolOptions * tool_options)
name|gimp_gradient_options_gui
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
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GimpGradientOptions
modifier|*
name|options
init|=
name|GIMP_GRADIENT_OPTIONS
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
init|=
name|gimp_paint_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox2
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|GdkModifierType
name|extend_mask
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|extend_mask
operator|=
name|gimp_get_extend_selection_mask
argument_list|()
expr_stmt|;
comment|/*  the gradient  */
name|button
operator|=
name|gimp_prop_gradient_box_new
argument_list|(
name|NULL
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|tool_options
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Gradient"
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|"gradient-view-type"
argument_list|,
literal|"gradient-view-size"
argument_list|,
literal|"gradient-reverse"
argument_list|,
literal|"gradient-blend-color-space"
argument_list|,
literal|"gimp-gradient-editor"
argument_list|,
name|_
argument_list|(
literal|"Edit this gradient"
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
comment|/*  the blend color space  */
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"gradient-blend-color-space"
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
literal|"Blend Color Space"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|combo
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_END
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
comment|/*  the gradient type menu  */
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"gradient-type"
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
literal|"Shape"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|combo
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_enum_combo_box_set_icon_prefix
argument_list|(
name|GIMP_ENUM_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
literal|"gimp-gradient"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
comment|/*  the distance metric menu  */
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"distance-metric"
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
literal|"Metric"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|combo
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_END
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
literal|"notify::gradient-type"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gradient_options_metric_gradient_type_notify
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|gradient_options_metric_gradient_type_notify
argument_list|(
name|options
argument_list|,
name|NULL
argument_list|,
name|combo
argument_list|)
expr_stmt|;
comment|/*  the repeat option  */
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"gradient-repeat"
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
literal|"Repeat"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|combo
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_END
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
literal|"notify::gradient-type"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gradient_options_repeat_gradient_type_notify
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|gradient_options_repeat_gradient_type_notify
argument_list|(
name|options
argument_list|,
name|NULL
argument_list|,
name|combo
argument_list|)
expr_stmt|;
comment|/*  the offset scale  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"offset"
argument_list|,
name|NULL
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
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
comment|/*  the dither toggle  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"dither"
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
comment|/*  supersampling options  */
name|vbox2
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_expanding_frame_new
argument_list|(
name|config
argument_list|,
literal|"supersample"
argument_list|,
name|NULL
argument_list|,
name|vbox2
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
comment|/*  max depth scale  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"supersample-depth"
argument_list|,
name|NULL
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
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
comment|/*  threshold scale  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"supersample-threshold"
argument_list|,
name|NULL
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
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
comment|/* the instant toggle */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Instant mode  (%s)"
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
literal|"instant"
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
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|options
operator|->
name|instant_toggle
operator|=
name|button
expr_stmt|;
comment|/*  the modify active toggle  */
name|vbox2
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_expanding_frame_new
argument_list|(
name|config
argument_list|,
literal|"modify-active"
argument_list|,
name|NULL
argument_list|,
name|vbox2
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
name|options
operator|->
name|modify_active_frame
operator|=
name|frame
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"The active gradient is non-writable "
literal|"and cannot be edited directly. "
literal|"Uncheck this option "
literal|"to edit a copy of it."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_label_set_width_chars
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|24
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|options
operator|->
name|modify_active_hint
operator|=
name|label
expr_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|options
operator|->
name|modify_active_frame
argument_list|,
name|gradient
operator|!=
name|gimp_gradients_get_custom
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|options
operator|->
name|modify_active_hint
argument_list|,
name|gradient
operator|&&
operator|!
name|gimp_data_is_writable
argument_list|(
name|GIMP_DATA
argument_list|(
name|gradient
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_options_repeat_gradient_type_notify (GimpGradientOptions * options,GParamSpec * pspec,GtkWidget * repeat_combo)
name|gradient_options_repeat_gradient_type_notify
parameter_list|(
name|GimpGradientOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|repeat_combo
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|repeat_combo
argument_list|,
name|options
operator|->
name|gradient_type
operator|<
name|GIMP_GRADIENT_SHAPEBURST_ANGULAR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_options_metric_gradient_type_notify (GimpGradientOptions * options,GParamSpec * pspec,GtkWidget * repeat_combo)
name|gradient_options_metric_gradient_type_notify
parameter_list|(
name|GimpGradientOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|repeat_combo
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|repeat_combo
argument_list|,
name|options
operator|->
name|gradient_type
operator|>=
name|GIMP_GRADIENT_SHAPEBURST_ANGULAR
operator|&&
name|options
operator|->
name|gradient_type
operator|<=
name|GIMP_GRADIENT_SHAPEBURST_DIMPLED
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

