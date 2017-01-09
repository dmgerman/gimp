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
file|"libgimpcolor/gimpcolor.h"
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
file|"widgets/gimpwidgets-constructors.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpforegroundselectoptions.h"
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

begin_comment
comment|/*  * for matting-global: iterations int  * for matting-levin:  levels int, active levels int  */
end_comment

begin_enum
enum|enum
DECL|enum|__anon2bb10c3e0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DRAW_MODE
name|PROP_DRAW_MODE
block|,
DECL|enumerator|PROP_STROKE_WIDTH
name|PROP_STROKE_WIDTH
block|,
DECL|enumerator|PROP_MASK_COLOR
name|PROP_MASK_COLOR
block|,
DECL|enumerator|PROP_ENGINE
name|PROP_ENGINE
block|,
DECL|enumerator|PROP_ITERATIONS
name|PROP_ITERATIONS
block|,
DECL|enumerator|PROP_LEVELS
name|PROP_LEVELS
block|,
DECL|enumerator|PROP_ACTIVE_LEVELS
name|PROP_ACTIVE_LEVELS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_foreground_select_options_set_property
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
name|gimp_foreground_select_options_get_property
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
DECL|function|G_DEFINE_TYPE (GimpForegroundSelectOptions,gimp_foreground_select_options,GIMP_TYPE_SELECTION_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpForegroundSelectOptions
argument_list|,
argument|gimp_foreground_select_options
argument_list|,
argument|GIMP_TYPE_SELECTION_OPTIONS
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_foreground_select_options_class_init
parameter_list|(
name|GimpForegroundSelectOptionsClass
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
name|gimp_foreground_select_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_foreground_select_options_get_property
expr_stmt|;
comment|/*  override the antialias default value from GimpSelectionOptions  */
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_DRAW_MODE
argument_list|,
literal|"draw-mode"
argument_list|,
name|_
argument_list|(
literal|"Draw Mode"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Paint over areas to mark color values for "
literal|"inclusion or exclusion from selection"
argument_list|)
argument_list|,
name|GIMP_TYPE_MATTING_DRAW_MODE
argument_list|,
name|GIMP_MATTING_DRAW_MODE_FOREGROUND
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_STROKE_WIDTH
argument_list|,
literal|"stroke-width"
argument_list|,
name|_
argument_list|(
literal|"Stroke width"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Size of the brush used for refinements"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|6000
argument_list|,
literal|10
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_MASK_COLOR
argument_list|,
literal|"mask-color"
argument_list|,
name|_
argument_list|(
literal|"Preview color"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Color of selection preview mask"
argument_list|)
argument_list|,
name|GIMP_TYPE_CHANNEL_TYPE
argument_list|,
name|GIMP_CHANNEL_BLUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_ENGINE
argument_list|,
literal|"engine"
argument_list|,
name|_
argument_list|(
literal|"Engine"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Matting engine to use"
argument_list|)
argument_list|,
name|GIMP_TYPE_MATTING_ENGINE
argument_list|,
name|GIMP_MATTING_ENGINE_GLOBAL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_LEVELS
argument_list|,
literal|"levels"
argument_list|,
name|_
argument_list|(
literal|"Levels"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Number of downsampled levels to use"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|2
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_ACTIVE_LEVELS
argument_list|,
literal|"active-levels"
argument_list|,
name|_
argument_list|(
literal|"Active levels"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Number of levels to perform solving"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|2
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_ITERATIONS
argument_list|,
literal|"iterations"
argument_list|,
name|_
argument_list|(
literal|"Iterations"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Number of iterations to perform"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|2
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_foreground_select_options_init (GimpForegroundSelectOptions * options)
name|gimp_foreground_select_options_init
parameter_list|(
name|GimpForegroundSelectOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_foreground_select_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_foreground_select_options_set_property
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
name|GimpForegroundSelectOptions
modifier|*
name|options
init|=
name|GIMP_FOREGROUND_SELECT_OPTIONS
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
name|PROP_DRAW_MODE
case|:
name|options
operator|->
name|draw_mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_WIDTH
case|:
name|options
operator|->
name|stroke_width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MASK_COLOR
case|:
name|options
operator|->
name|mask_color
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ENGINE
case|:
name|options
operator|->
name|engine
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|options
operator|->
name|engine
operator|==
name|GIMP_MATTING_ENGINE_LEVIN
operator|)
operator|&&
operator|!
operator|(
name|gegl_has_operation
argument_list|(
literal|"gegl:matting-levin"
argument_list|)
operator|)
condition|)
block|{
name|options
operator|->
name|engine
operator|=
name|GIMP_MATTING_ENGINE_GLOBAL
expr_stmt|;
block|}
break|break;
case|case
name|PROP_LEVELS
case|:
name|options
operator|->
name|levels
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ACTIVE_LEVELS
case|:
name|options
operator|->
name|active_levels
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ITERATIONS
case|:
name|options
operator|->
name|iterations
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
DECL|function|gimp_foreground_select_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_foreground_select_options_get_property
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
name|GimpForegroundSelectOptions
modifier|*
name|options
init|=
name|GIMP_FOREGROUND_SELECT_OPTIONS
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
name|PROP_DRAW_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|draw_mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|stroke_width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MASK_COLOR
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|mask_color
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ENGINE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|engine
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LEVELS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|levels
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ACTIVE_LEVELS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|active_levels
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ITERATIONS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|iterations
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
DECL|function|gimp_foreground_select_options_reset_stroke_width (GtkWidget * button,GimpToolOptions * tool_options)
name|gimp_foreground_select_options_reset_stroke_width
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|tool_options
argument_list|,
literal|"stroke-width"
argument_list|,
literal|10
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_foreground_select_options_sync_engine (GBinding * binding,const GValue * source_value,GValue * target_value,gpointer user_data)
name|gimp_foreground_select_options_sync_engine
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
name|gint
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
name|GPOINTER_TO_INT
argument_list|(
name|user_data
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_foreground_select_options_gui (GimpToolOptions * tool_options)
name|gimp_foreground_select_options_gui
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
name|gimp_selection_options_gui
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
name|button
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
name|inner_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|antialias_toggle
decl_stmt|;
name|antialias_toggle
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool_options
argument_list|)
operator|->
name|antialias_toggle
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|antialias_toggle
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"draw-mode"
argument_list|,
name|NULL
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
comment|/* stroke width */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"stroke-width"
argument_list|,
name|NULL
argument_list|,
literal|1.0
argument_list|,
literal|10.0
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
name|gimp_spin_scale_set_gamma
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|1.7
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_icon_button_new
argument_list|(
name|GIMP_STOCK_RESET
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_button_set_relief
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|GTK_RELIEF_NONE
argument_list|)
expr_stmt|;
name|gtk_image_set_from_icon_name
argument_list|(
name|GTK_IMAGE
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|button
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_foreground_select_options_reset_stroke_width
argument_list|)
argument_list|,
name|tool_options
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|_
argument_list|(
literal|"Reset stroke width native size"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  mask color */
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"mask-color"
argument_list|,
name|GIMP_CHANNEL_RED
argument_list|,
name|GIMP_CHANNEL_GRAY
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
literal|"Preview color"
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
comment|/* engine */
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
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"engine"
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
literal|"Engine"
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
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gegl_has_operation
argument_list|(
literal|"gegl:matting-levin"
argument_list|)
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|combo
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|combo
argument_list|)
expr_stmt|;
name|inner_vbox
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
name|inner_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|inner_vbox
argument_list|)
expr_stmt|;
comment|/*  engine parameters  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"levels"
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
name|inner_vbox
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
name|g_object_bind_property_full
argument_list|(
name|config
argument_list|,
literal|"engine"
argument_list|,
name|scale
argument_list|,
literal|"visible"
argument_list|,
name|G_BINDING_SYNC_CREATE
argument_list|,
name|gimp_foreground_select_options_sync_engine
argument_list|,
name|NULL
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_MATTING_ENGINE_LEVIN
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"active-levels"
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
name|inner_vbox
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
name|g_object_bind_property_full
argument_list|(
name|config
argument_list|,
literal|"engine"
argument_list|,
name|scale
argument_list|,
literal|"visible"
argument_list|,
name|G_BINDING_SYNC_CREATE
argument_list|,
name|gimp_foreground_select_options_sync_engine
argument_list|,
name|NULL
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_MATTING_ENGINE_LEVIN
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"iterations"
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
name|inner_vbox
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
name|g_object_bind_property_full
argument_list|(
name|config
argument_list|,
literal|"engine"
argument_list|,
name|scale
argument_list|,
literal|"visible"
argument_list|,
name|G_BINDING_SYNC_CREATE
argument_list|,
name|gimp_foreground_select_options_sync_engine
argument_list|,
name|NULL
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_MATTING_ENGINE_GLOBAL
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_foreground_select_options_get_mask_color (GimpForegroundSelectOptions * options,GimpRGB * color)
name|gimp_foreground_select_options_get_mask_color
parameter_list|(
name|GimpForegroundSelectOptions
modifier|*
name|options
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FOREGROUND_SELECT_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|mask_color
condition|)
block|{
case|case
name|GIMP_CHANNEL_RED
case|:
name|gimp_rgba_set
argument_list|(
name|color
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0.7
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_GREEN
case|:
name|gimp_rgba_set
argument_list|(
name|color
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0.7
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_BLUE
case|:
name|gimp_rgba_set
argument_list|(
name|color
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0.7
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_GRAY
case|:
name|gimp_rgba_set
argument_list|(
name|color
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0.7
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warn_if_reached
argument_list|()
expr_stmt|;
break|break;
block|}
block|}
end_function

end_unit

