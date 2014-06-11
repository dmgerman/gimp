begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpregionselectoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpregionselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2946093e0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SELECT_TRANSPARENT
name|PROP_SELECT_TRANSPARENT
block|,
DECL|enumerator|PROP_SAMPLE_MERGED
name|PROP_SAMPLE_MERGED
block|,
DECL|enumerator|PROP_THRESHOLD
name|PROP_THRESHOLD
block|,
DECL|enumerator|PROP_SELECT_CRITERION
name|PROP_SELECT_CRITERION
block|,
DECL|enumerator|PROP_DRAW_MASK
name|PROP_DRAW_MASK
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_region_select_options_set_property
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
name|gimp_region_select_options_get_property
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
name|gimp_region_select_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpRegionSelectOptions,gimp_region_select_options,GIMP_TYPE_SELECTION_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpRegionSelectOptions
argument_list|,
argument|gimp_region_select_options
argument_list|,
argument|GIMP_TYPE_SELECTION_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_region_select_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_region_select_options_class_init
parameter_list|(
name|GimpRegionSelectOptionsClass
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
name|gimp_region_select_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_region_select_options_get_property
expr_stmt|;
name|options_class
operator|->
name|reset
operator|=
name|gimp_region_select_options_reset
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SELECT_TRANSPARENT
argument_list|,
literal|"select-transparent"
argument_list|,
name|_
argument_list|(
literal|"Allow completely transparent regions "
literal|"to be selected"
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
name|PROP_SAMPLE_MERGED
argument_list|,
literal|"sample-merged"
argument_list|,
name|_
argument_list|(
literal|"Base selection on all visible layers"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_THRESHOLD
argument_list|,
literal|"threshold"
argument_list|,
name|_
argument_list|(
literal|"Maximum color difference"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|255.0
argument_list|,
literal|15.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_SELECT_CRITERION
argument_list|,
literal|"select-criterion"
argument_list|,
name|_
argument_list|(
literal|"Selection criterion"
argument_list|)
argument_list|,
name|GIMP_TYPE_SELECT_CRITERION
argument_list|,
name|GIMP_SELECT_CRITERION_COMPOSITE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DRAW_MASK
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"draw-mask"
argument_list|,
literal|"Draw mask"
argument_list|,
name|_
argument_list|(
literal|"Draw the selected region's mask"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
operator||
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_region_select_options_init (GimpRegionSelectOptions * options)
name|gimp_region_select_options_init
parameter_list|(
name|GimpRegionSelectOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_region_select_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_region_select_options_set_property
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
name|GimpRegionSelectOptions
modifier|*
name|options
init|=
name|GIMP_REGION_SELECT_OPTIONS
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
name|PROP_SELECT_TRANSPARENT
case|:
name|options
operator|->
name|select_transparent
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_MERGED
case|:
name|options
operator|->
name|sample_merged
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_THRESHOLD
case|:
name|options
operator|->
name|threshold
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SELECT_CRITERION
case|:
name|options
operator|->
name|select_criterion
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DRAW_MASK
case|:
name|options
operator|->
name|draw_mask
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
DECL|function|gimp_region_select_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_region_select_options_get_property
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
name|GimpRegionSelectOptions
modifier|*
name|options
init|=
name|GIMP_REGION_SELECT_OPTIONS
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
name|PROP_SELECT_TRANSPARENT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|select_transparent
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_MERGED
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_THRESHOLD
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|threshold
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SELECT_CRITERION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|select_criterion
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DRAW_MASK
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|draw_mask
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
DECL|function|gimp_region_select_options_reset (GimpToolOptions * tool_options)
name|gimp_region_select_options_reset
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
literal|"threshold"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pspec
condition|)
name|G_PARAM_SPEC_DOUBLE
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
name|default_threshold
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
DECL|function|gimp_region_select_options_gui (GimpToolOptions * tool_options)
name|gimp_region_select_options_gui
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
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
comment|/*  the select transparent areas toggle  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"select-transparent"
argument_list|,
name|_
argument_list|(
literal|"Select transparent areas"
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
comment|/*  the sample merged toggle  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"sample-merged"
argument_list|,
name|_
argument_list|(
literal|"Sample merged"
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
comment|/*  the threshold scale  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"threshold"
argument_list|,
name|_
argument_list|(
literal|"Threshold"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|16.0
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
comment|/*  the select criterion combo  */
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"select-criterion"
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
literal|"Select by"
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
comment|/*  the show mask toggle  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"draw-mask"
argument_list|,
name|_
argument_list|(
literal|"Draw Mask"
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
return|return
name|vbox
return|;
block|}
end_function

end_unit

