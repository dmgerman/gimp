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
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
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
file|"gimpbucketfilloptions.h"
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
DECL|enum|__anon2b7320c30103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_FILL_MODE
name|PROP_FILL_MODE
block|,
DECL|enumerator|PROP_FILL_SELECTION
name|PROP_FILL_SELECTION
block|,
DECL|enumerator|PROP_FILL_TRANSPARENT
name|PROP_FILL_TRANSPARENT
block|,
DECL|enumerator|PROP_SAMPLE_MERGED
name|PROP_SAMPLE_MERGED
block|,
DECL|enumerator|PROP_DIAGONAL_NEIGHBORS
name|PROP_DIAGONAL_NEIGHBORS
block|,
DECL|enumerator|PROP_THRESHOLD
name|PROP_THRESHOLD
block|,
DECL|enumerator|PROP_FILL_CRITERION
name|PROP_FILL_CRITERION
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_options_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|config_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_options_set_property
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
name|gimp_bucket_fill_options_get_property
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
name|gimp_bucket_fill_options_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpBucketFillOptions
argument_list|,
argument|gimp_bucket_fill_options
argument_list|,
argument|GIMP_TYPE_PAINT_OPTIONS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_bucket_fill_options_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_bucket_fill_options_parent_class
end_define

begin_decl_stmt
specifier|static
name|GimpConfigInterface
modifier|*
name|parent_config_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_options_class_init (GimpBucketFillOptionsClass * klass)
name|gimp_bucket_fill_options_class_init
parameter_list|(
name|GimpBucketFillOptionsClass
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
name|gimp_bucket_fill_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_bucket_fill_options_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_FILL_MODE
argument_list|,
literal|"fill-mode"
argument_list|,
name|_
argument_list|(
literal|"Fill type"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_BUCKET_FILL_MODE
argument_list|,
name|GIMP_BUCKET_FILL_FG
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_FILL_SELECTION
argument_list|,
literal|"fill-selection"
argument_list|,
name|_
argument_list|(
literal|"Fill selection"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Which area will be filled"
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
name|PROP_FILL_TRANSPARENT
argument_list|,
literal|"fill-transparent"
argument_list|,
name|_
argument_list|(
literal|"Fill transparent areas"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Allow completely transparent regions "
literal|"to be filled"
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
name|PROP_SAMPLE_MERGED
argument_list|,
literal|"sample-merged"
argument_list|,
name|_
argument_list|(
literal|"Sample merged"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Base filled area on all visible layers"
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
name|PROP_DIAGONAL_NEIGHBORS
argument_list|,
literal|"diagonal-neighbors"
argument_list|,
name|_
argument_list|(
literal|"Diagonal neighbors"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Treat diagonally neighboring pixels as "
literal|"connected"
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
name|PROP_THRESHOLD
argument_list|,
literal|"threshold"
argument_list|,
name|_
argument_list|(
literal|"Threshold"
argument_list|)
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
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_FILL_CRITERION
argument_list|,
literal|"fill-criterion"
argument_list|,
name|_
argument_list|(
literal|"Fill by"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Criterion used for determining color similarity"
argument_list|)
argument_list|,
name|GIMP_TYPE_SELECT_CRITERION
argument_list|,
name|GIMP_SELECT_CRITERION_COMPOSITE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_options_config_iface_init (GimpConfigInterface * config_iface)
name|gimp_bucket_fill_options_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|config_iface
parameter_list|)
block|{
name|parent_config_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|config_iface
argument_list|)
expr_stmt|;
name|config_iface
operator|->
name|reset
operator|=
name|gimp_bucket_fill_options_reset
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_options_init (GimpBucketFillOptions * options)
name|gimp_bucket_fill_options_init
parameter_list|(
name|GimpBucketFillOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_bucket_fill_options_set_property
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
name|GimpBucketFillOptions
modifier|*
name|options
init|=
name|GIMP_BUCKET_FILL_OPTIONS
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
name|PROP_FILL_MODE
case|:
name|options
operator|->
name|fill_mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILL_SELECTION
case|:
name|options
operator|->
name|fill_selection
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILL_TRANSPARENT
case|:
name|options
operator|->
name|fill_transparent
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
name|PROP_DIAGONAL_NEIGHBORS
case|:
name|options
operator|->
name|diagonal_neighbors
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
name|PROP_FILL_CRITERION
case|:
name|options
operator|->
name|fill_criterion
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
DECL|function|gimp_bucket_fill_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_bucket_fill_options_get_property
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
name|GimpBucketFillOptions
modifier|*
name|options
init|=
name|GIMP_BUCKET_FILL_OPTIONS
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
name|PROP_FILL_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|fill_mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILL_SELECTION
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|fill_selection
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILL_TRANSPARENT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|fill_transparent
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
name|PROP_DIAGONAL_NEIGHBORS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|diagonal_neighbors
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
name|PROP_FILL_CRITERION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|fill_criterion
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
DECL|function|gimp_bucket_fill_options_reset (GimpConfig * config)
name|gimp_bucket_fill_options_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpToolOptions
modifier|*
name|tool_options
init|=
name|GIMP_TOOL_OPTIONS
argument_list|(
name|config
argument_list|)
decl_stmt|;
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
name|config
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
name|parent_config_iface
operator|->
name|reset
argument_list|(
name|config
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_bucket_fill_options_gui (GimpToolOptions * tool_options)
name|gimp_bucket_fill_options_gui
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
name|hbox
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
comment|/*  fill type  */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Fill Type  (%s)"
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|toggle_mask
argument_list|)
argument_list|)
operator|,
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"fill-mode"
argument_list|,
name|str
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
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
name|gimp_prop_pattern_box_new
argument_list|(
name|NULL
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|tool_options
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|2
argument_list|,
literal|"pattern-view-type"
argument_list|,
literal|"pattern-view-size"
argument_list|)
expr_stmt|;
name|gimp_enum_radio_frame_add
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|GIMP_BUCKET_FILL_PATTERN
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  fill selection  */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Affected Area  (%s)"
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|extend_mask
argument_list|)
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_boolean_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"fill-selection"
argument_list|,
name|str
argument_list|,
name|_
argument_list|(
literal|"Fill whole selection"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Fill similar colors"
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|frame
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|"radio-button"
argument_list|)
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
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Finding Similar Colors"
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
name|g_object_bind_property
argument_list|(
name|config
argument_list|,
literal|"fill-selection"
argument_list|,
name|frame
argument_list|,
literal|"sensitive"
argument_list|,
name|G_BINDING_SYNC_CREATE
operator||
name|G_BINDING_INVERT_BOOLEAN
argument_list|)
expr_stmt|;
name|vbox2
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
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
name|vbox2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox2
argument_list|)
expr_stmt|;
comment|/*  the fill transparent areas toggle  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"fill-transparent"
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
comment|/*  the sample merged toggle  */
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
comment|/*  the diagonal neighbors toggle  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"diagonal-neighbors"
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
comment|/*  the threshold scale  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"threshold"
argument_list|,
name|NULL
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
comment|/*  the fill criterion combo  */
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"fill-criterion"
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
literal|"Fill by"
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
return|return
name|vbox
return|;
block|}
end_function

end_unit

