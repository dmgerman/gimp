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
file|"base/siox.h"
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

begin_enum
enum|enum
DECL|enum|__anon288b66460103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTIGUOUS
name|PROP_CONTIGUOUS
block|,
DECL|enumerator|PROP_BACKGROUND
name|PROP_BACKGROUND
block|,
DECL|enumerator|PROP_STROKE_WIDTH
name|PROP_STROKE_WIDTH
block|,
DECL|enumerator|PROP_SMOOTHNESS
name|PROP_SMOOTHNESS
block|,
DECL|enumerator|PROP_MASK_COLOR
name|PROP_MASK_COLOR
block|,
DECL|enumerator|PROP_EXPANDED
name|PROP_EXPANDED
block|,
DECL|enumerator|PROP_SENSITIVITY_L
name|PROP_SENSITIVITY_L
block|,
DECL|enumerator|PROP_SENSITIVITY_A
name|PROP_SENSITIVITY_A
block|,
DECL|enumerator|PROP_SENSITIVITY_B
name|PROP_SENSITIVITY_B
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
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTIGUOUS
argument_list|,
literal|"contiguous"
argument_list|,
name|_
argument_list|(
literal|"Select a single contiguous area"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_BACKGROUND
argument_list|,
literal|"background"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_STROKE_WIDTH
argument_list|,
literal|"stroke-width"
argument_list|,
name|_
argument_list|(
literal|"Size of the brush used for refinements"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|80
argument_list|,
literal|18
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_SMOOTHNESS
argument_list|,
literal|"smoothness"
argument_list|,
name|_
argument_list|(
literal|"Smaller values give a more accurate "
literal|"selection border but may introduce holes "
literal|"in the selection"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|8
argument_list|,
name|SIOX_DEFAULT_SMOOTHNESS
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_MASK_COLOR
argument_list|,
literal|"mask-color"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CHANNEL_TYPE
argument_list|,
name|GIMP_BLUE_CHANNEL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_EXPANDED
argument_list|,
literal|"expanded"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_SENSITIVITY_L
argument_list|,
literal|"sensitivity-l"
argument_list|,
name|_
argument_list|(
literal|"Sensitivity for brightness component"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|10.0
argument_list|,
name|SIOX_DEFAULT_SENSITIVITY_L
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_SENSITIVITY_A
argument_list|,
literal|"sensitivity-a"
argument_list|,
name|_
argument_list|(
literal|"Sensitivity for red/green component"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|10.0
argument_list|,
name|SIOX_DEFAULT_SENSITIVITY_A
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_SENSITIVITY_B
argument_list|,
literal|"sensitivity-b"
argument_list|,
name|_
argument_list|(
literal|"Sensitivity for yellow/blue component"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|10.0
argument_list|,
name|SIOX_DEFAULT_SENSITIVITY_B
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
name|PROP_CONTIGUOUS
case|:
name|options
operator|->
name|contiguous
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BACKGROUND
case|:
name|options
operator|->
name|background
operator|=
name|g_value_get_boolean
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
name|PROP_SMOOTHNESS
case|:
name|options
operator|->
name|smoothness
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
name|PROP_EXPANDED
case|:
name|options
operator|->
name|expanded
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SENSITIVITY_L
case|:
name|options
operator|->
name|sensitivity
index|[
literal|0
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SENSITIVITY_A
case|:
name|options
operator|->
name|sensitivity
index|[
literal|1
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SENSITIVITY_B
case|:
name|options
operator|->
name|sensitivity
index|[
literal|2
index|]
operator|=
name|g_value_get_double
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
name|PROP_CONTIGUOUS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|contiguous
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BACKGROUND
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|background
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
name|PROP_SMOOTHNESS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|smoothness
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
name|PROP_EXPANDED
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|expanded
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SENSITIVITY_L
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|sensitivity
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SENSITIVITY_A
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|sensitivity
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SENSITIVITY_B
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|sensitivity
index|[
literal|2
index|]
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
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|inner_frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|gint
name|row
init|=
literal|0
decl_stmt|;
comment|/*  single / multiple objects  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"contiguous"
argument_list|,
name|_
argument_list|(
literal|"Contiguous"
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
comment|/*  foreground / background  */
name|title
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Interactive refinement  (%s)"
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
name|gimp_prop_boolean_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"background"
argument_list|,
name|title
argument_list|,
name|_
argument_list|(
literal|"Mark background"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Mark foreground"
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
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
comment|/*  stroke width  */
name|inner_frame
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_BIN
argument_list|(
name|frame
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|inner_frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|inner_frame
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|inner_frame
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
literal|"Small brush"
argument_list|)
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
name|PANGO_ATTR_SCALE
argument_list|,
name|PANGO_SCALE_SMALL
argument_list|,
operator|-
literal|1
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Large brush"
argument_list|)
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
name|PANGO_ATTR_SCALE
argument_list|,
name|PANGO_SCALE_SMALL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
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
name|scale
operator|=
name|gimp_prop_hscale_new
argument_list|(
name|config
argument_list|,
literal|"stroke-width"
argument_list|,
literal|1.0
argument_list|,
literal|5.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_draw_value
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|inner_frame
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
comment|/*  smoothness  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
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
name|table
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
name|table
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_prop_hscale_new
argument_list|(
name|config
argument_list|,
literal|"smoothness"
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_POS_RIGHT
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Smoothing:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|scale
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  mask color */
name|menu
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"mask-color"
argument_list|,
name|GIMP_RED_CHANNEL
argument_list|,
name|GIMP_BLUE_CHANNEL
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Preview color:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|menu
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  granularity  */
name|frame
operator|=
name|gimp_prop_expander_new
argument_list|(
name|config
argument_list|,
literal|"expanded"
argument_list|,
name|_
argument_list|(
literal|"Color Sensitivity"
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
name|inner_frame
operator|=
name|gimp_frame_new
argument_list|(
literal|"<expander>"
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|inner_frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|inner_frame
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|inner_frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_prop_opacity_entry_new
argument_list|(
name|config
argument_list|,
literal|"sensitivity-l"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"L"
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|adj
argument_list|)
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_prop_opacity_entry_new
argument_list|(
name|config
argument_list|,
literal|"sensitivity-a"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"a"
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|adj
argument_list|)
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_prop_opacity_entry_new
argument_list|(
name|config
argument_list|,
literal|"sensitivity-b"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"b"
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|adj
argument_list|)
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

