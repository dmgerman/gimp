begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpwarpoptions.c  * Copyright (C) 2011 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"widgets/gimpspinscale.h"
end_include

begin_include
include|#
directive|include
file|"gimpwarpoptions.h"
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
DECL|enum|__anon2b4fce7f0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_BEHAVIOR
name|PROP_BEHAVIOR
block|,
DECL|enumerator|PROP_EFFECT_SIZE
name|PROP_EFFECT_SIZE
block|,
DECL|enumerator|PROP_EFFECT_HARDNESS
name|PROP_EFFECT_HARDNESS
block|,
DECL|enumerator|PROP_EFFECT_STRENGTH
name|PROP_EFFECT_STRENGTH
block|,
DECL|enumerator|PROP_STROKE_SPACING
name|PROP_STROKE_SPACING
block|,
DECL|enumerator|PROP_INTERPOLATION
name|PROP_INTERPOLATION
block|,
DECL|enumerator|PROP_ABYSS_POLICY
name|PROP_ABYSS_POLICY
block|,
DECL|enumerator|PROP_HIGH_QUALITY_PREVIEW
name|PROP_HIGH_QUALITY_PREVIEW
block|,
DECL|enumerator|PROP_STROKE_DURING_MOTION
name|PROP_STROKE_DURING_MOTION
block|,
DECL|enumerator|PROP_STROKE_PERIODICALLY
name|PROP_STROKE_PERIODICALLY
block|,
DECL|enumerator|PROP_STROKE_PERIODICALLY_RATE
name|PROP_STROKE_PERIODICALLY_RATE
block|,
DECL|enumerator|PROP_N_ANIMATION_FRAMES
name|PROP_N_ANIMATION_FRAMES
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_warp_options_set_property
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
name|gimp_warp_options_get_property
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
DECL|function|G_DEFINE_TYPE (GimpWarpOptions,gimp_warp_options,GIMP_TYPE_TOOL_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpWarpOptions
argument_list|,
argument|gimp_warp_options
argument_list|,
argument|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_warp_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_warp_options_class_init
parameter_list|(
name|GimpWarpOptionsClass
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
name|gimp_warp_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_warp_options_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_BEHAVIOR
argument_list|,
literal|"behavior"
argument_list|,
name|_
argument_list|(
literal|"Behavior"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Behavior"
argument_list|)
argument_list|,
name|GIMP_TYPE_WARP_BEHAVIOR
argument_list|,
name|GIMP_WARP_BEHAVIOR_MOVE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_EFFECT_SIZE
argument_list|,
literal|"effect-size"
argument_list|,
name|_
argument_list|(
literal|"Size"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Effect Size"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|10000.0
argument_list|,
literal|40.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_EFFECT_HARDNESS
argument_list|,
literal|"effect-hardness"
argument_list|,
name|_
argument_list|(
literal|"Hardness"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Effect Hardness"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|50.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_EFFECT_STRENGTH
argument_list|,
literal|"effect-strength"
argument_list|,
name|_
argument_list|(
literal|"Strength"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Effect Strength"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|100.0
argument_list|,
literal|50.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_STROKE_SPACING
argument_list|,
literal|"stroke-spacing"
argument_list|,
name|_
argument_list|(
literal|"Spacing"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Stroke Spacing"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|100.0
argument_list|,
literal|20.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_INTERPOLATION
argument_list|,
literal|"interpolation"
argument_list|,
name|_
argument_list|(
literal|"Interpolation"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Interpolation method"
argument_list|)
argument_list|,
name|GIMP_TYPE_INTERPOLATION_TYPE
argument_list|,
name|GIMP_INTERPOLATION_CUBIC
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_ABYSS_POLICY
argument_list|,
literal|"abyss-policy"
argument_list|,
name|_
argument_list|(
literal|"Abyss policy"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Out-of-bounds sampling behavior"
argument_list|)
argument_list|,
name|GEGL_TYPE_ABYSS_POLICY
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_HIGH_QUALITY_PREVIEW
argument_list|,
literal|"high-quality-preview"
argument_list|,
name|_
argument_list|(
literal|"High quality preview"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Use an accurate but slower preview"
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
name|PROP_STROKE_DURING_MOTION
argument_list|,
literal|"stroke-during-motion"
argument_list|,
name|_
argument_list|(
literal|"During motion"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Apply effect during motion"
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
name|PROP_STROKE_PERIODICALLY
argument_list|,
literal|"stroke-periodically"
argument_list|,
name|_
argument_list|(
literal|"Periodically"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Apply effect periodically"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_STROKE_PERIODICALLY_RATE
argument_list|,
literal|"stroke-periodically-rate"
argument_list|,
name|_
argument_list|(
literal|"Rate"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Periodic stroke rate"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|50.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_N_ANIMATION_FRAMES
argument_list|,
literal|"n-animation-frames"
argument_list|,
name|_
argument_list|(
literal|"Frames"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Number of animation frames"
argument_list|)
argument_list|,
literal|3
argument_list|,
literal|1000
argument_list|,
literal|10
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_options_init (GimpWarpOptions * options)
name|gimp_warp_options_init
parameter_list|(
name|GimpWarpOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_warp_options_set_property
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
name|GimpWarpOptions
modifier|*
name|options
init|=
name|GIMP_WARP_OPTIONS
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
name|PROP_BEHAVIOR
case|:
name|options
operator|->
name|behavior
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EFFECT_SIZE
case|:
name|options
operator|->
name|effect_size
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EFFECT_HARDNESS
case|:
name|options
operator|->
name|effect_hardness
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EFFECT_STRENGTH
case|:
name|options
operator|->
name|effect_strength
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_SPACING
case|:
name|options
operator|->
name|stroke_spacing
operator|=
name|g_value_get_double
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
name|PROP_ABYSS_POLICY
case|:
name|options
operator|->
name|abyss_policy
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGH_QUALITY_PREVIEW
case|:
name|options
operator|->
name|high_quality_preview
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_DURING_MOTION
case|:
name|options
operator|->
name|stroke_during_motion
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_PERIODICALLY
case|:
name|options
operator|->
name|stroke_periodically
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_PERIODICALLY_RATE
case|:
name|options
operator|->
name|stroke_periodically_rate
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_N_ANIMATION_FRAMES
case|:
name|options
operator|->
name|n_animation_frames
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
specifier|static
name|void
DECL|function|gimp_warp_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_warp_options_get_property
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
name|GimpWarpOptions
modifier|*
name|options
init|=
name|GIMP_WARP_OPTIONS
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
name|PROP_BEHAVIOR
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|behavior
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EFFECT_SIZE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|effect_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EFFECT_HARDNESS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|effect_hardness
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EFFECT_STRENGTH
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|effect_strength
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_SPACING
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|stroke_spacing
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
name|PROP_ABYSS_POLICY
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|abyss_policy
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGH_QUALITY_PREVIEW
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|high_quality_preview
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_DURING_MOTION
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|stroke_during_motion
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_PERIODICALLY
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|stroke_periodically
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_PERIODICALLY_RATE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|stroke_periodically_rate
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_N_ANIMATION_FRAMES
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|n_animation_frames
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
DECL|function|gimp_warp_options_gui (GimpToolOptions * tool_options)
name|gimp_warp_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GimpWarpOptions
modifier|*
name|options
init|=
name|GIMP_WARP_OPTIONS
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
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
name|vbox2
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
name|scale
decl_stmt|;
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"behavior"
argument_list|,
literal|0
argument_list|,
literal|0
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
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"effect-size"
argument_list|,
name|NULL
argument_list|,
literal|0.01
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_spin_scale_set_scale_limits
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1000.0
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
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"effect-hardness"
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_spin_scale_set_scale_limits
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|100.0
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
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"effect-strength"
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_spin_scale_set_scale_limits
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|100.0
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
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"stroke-spacing"
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_spin_scale_set_scale_limits
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|100.0
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
name|gimp_int_combo_box_set_label
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Interpolation"
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
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"abyss-policy"
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|GEGL_ABYSS_LOOP
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
literal|"Abyss policy"
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
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"high-quality-preview"
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
comment|/*  the stroke frame  */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Stroke"
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
name|options
operator|->
name|stroke_frame
operator|=
name|frame
expr_stmt|;
name|vbox2
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
name|vbox2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox2
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"stroke-during-motion"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
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
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"stroke-periodically-rate"
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_spin_scale_set_scale_limits
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_expanding_frame_new
argument_list|(
name|config
argument_list|,
literal|"stroke-periodically"
argument_list|,
name|NULL
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
name|vbox2
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
comment|/*  the animation frame  */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Animate"
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
name|vbox2
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
name|vbox2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox2
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"n-animation-frames"
argument_list|,
name|NULL
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_spin_scale_set_scale_limits
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|3.0
argument_list|,
literal|100.0
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
name|options
operator|->
name|animate_button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Create Animation"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|options
operator|->
name|animate_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|options
operator|->
name|animate_button
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
name|options
operator|->
name|animate_button
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|animate_button
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|options
operator|->
name|animate_button
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

