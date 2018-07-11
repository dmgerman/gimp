begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpnpointdeformationoptions.c  * Copyright (C) 2013 Marek Dvoroznak<dvoromar@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpnpointdeformationoptions.h"
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
DECL|enum|__anon2bf7d9c30103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SQUARE_SIZE
name|PROP_SQUARE_SIZE
block|,
DECL|enumerator|PROP_RIGIDITY
name|PROP_RIGIDITY
block|,
DECL|enumerator|PROP_ASAP_DEFORMATION
name|PROP_ASAP_DEFORMATION
block|,
DECL|enumerator|PROP_MLS_WEIGHTS
name|PROP_MLS_WEIGHTS
block|,
DECL|enumerator|PROP_MLS_WEIGHTS_ALPHA
name|PROP_MLS_WEIGHTS_ALPHA
block|,
DECL|enumerator|PROP_MESH_VISIBLE
name|PROP_MESH_VISIBLE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_n_point_deformation_options_set_property
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
name|gimp_n_point_deformation_options_get_property
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
DECL|function|G_DEFINE_TYPE (GimpNPointDeformationOptions,gimp_n_point_deformation_options,GIMP_TYPE_TOOL_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpNPointDeformationOptions
argument_list|,
argument|gimp_n_point_deformation_options
argument_list|,
argument|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_n_point_deformation_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_n_point_deformation_options_class_init
parameter_list|(
name|GimpNPointDeformationOptionsClass
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
name|gimp_n_point_deformation_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_n_point_deformation_options_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_SQUARE_SIZE
argument_list|,
literal|"square-size"
argument_list|,
name|_
argument_list|(
literal|"Density"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Density"
argument_list|)
argument_list|,
literal|5.0
argument_list|,
literal|1000.0
argument_list|,
literal|20.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_RIGIDITY
argument_list|,
literal|"rigidity"
argument_list|,
name|_
argument_list|(
literal|"Rigidity"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Rigidity"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|10000.0
argument_list|,
literal|100.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ASAP_DEFORMATION
argument_list|,
literal|"asap-deformation"
argument_list|,
name|_
argument_list|(
literal|"Deformation mode"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Deformation mode"
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
name|PROP_MLS_WEIGHTS
argument_list|,
literal|"mls-weights"
argument_list|,
name|_
argument_list|(
literal|"Use weights"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Use weights"
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
name|PROP_MLS_WEIGHTS_ALPHA
argument_list|,
literal|"mls-weights-alpha"
argument_list|,
name|_
argument_list|(
literal|"Control points influence"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Amount of control points' influence"
argument_list|)
argument_list|,
literal|0.1
argument_list|,
literal|2.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_MESH_VISIBLE
argument_list|,
literal|"mesh-visible"
argument_list|,
name|_
argument_list|(
literal|"Show lattice"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Show lattice"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_options_init (GimpNPointDeformationOptions * options)
name|gimp_n_point_deformation_options_init
parameter_list|(
name|GimpNPointDeformationOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_n_point_deformation_options_set_property
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
name|GimpNPointDeformationOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_N_POINT_DEFORMATION_OPTIONS
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SQUARE_SIZE
case|:
name|options
operator|->
name|square_size
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RIGIDITY
case|:
name|options
operator|->
name|rigidity
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ASAP_DEFORMATION
case|:
name|options
operator|->
name|asap_deformation
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MLS_WEIGHTS
case|:
name|options
operator|->
name|mls_weights
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MLS_WEIGHTS_ALPHA
case|:
name|options
operator|->
name|mls_weights_alpha
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MESH_VISIBLE
case|:
name|options
operator|->
name|mesh_visible
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
DECL|function|gimp_n_point_deformation_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_n_point_deformation_options_get_property
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
name|GimpNPointDeformationOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_N_POINT_DEFORMATION_OPTIONS
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SQUARE_SIZE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|square_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RIGIDITY
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|rigidity
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ASAP_DEFORMATION
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|asap_deformation
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MLS_WEIGHTS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|mls_weights
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MLS_WEIGHTS_ALPHA
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|mls_weights_alpha
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MESH_VISIBLE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|mesh_visible
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
DECL|function|gimp_n_point_deformation_options_gui (GimpToolOptions * tool_options)
name|gimp_n_point_deformation_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GimpNPointDeformationOptions
modifier|*
name|npd_options
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
name|widget
decl_stmt|;
name|npd_options
operator|=
name|GIMP_N_POINT_DEFORMATION_OPTIONS
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"mesh-visible"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|npd_options
operator|->
name|check_mesh_visible
operator|=
name|widget
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|widget
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|widget
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"square-size"
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
name|npd_options
operator|->
name|scale_square_size
operator|=
name|widget
expr_stmt|;
name|gimp_spin_scale_set_scale_limits
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|10.0
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
name|widget
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|widget
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"rigidity"
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
name|widget
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|2000.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|widget
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|widget
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gimp_prop_boolean_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"asap-deformation"
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Scale"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Rigid (Rubber)"
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
name|widget
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|widget
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"mls-weights"
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
name|widget
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|widget
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"mls-weights-alpha"
argument_list|,
name|NULL
argument_list|,
literal|0.1
argument_list|,
literal|0.1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_spin_scale_set_scale_limits
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0.1
argument_list|,
literal|2.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|widget
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|widget
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|g_object_bind_property
argument_list|(
name|config
argument_list|,
literal|"mls-weights"
argument_list|,
name|widget
argument_list|,
literal|"sensitive"
argument_list|,
name|G_BINDING_DEFAULT
operator||
name|G_BINDING_SYNC_CREATE
argument_list|)
expr_stmt|;
name|gimp_n_point_deformation_options_set_sensitivity
argument_list|(
name|npd_options
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_n_point_deformation_options_set_sensitivity (GimpNPointDeformationOptions * npd_options,gboolean tool_active)
name|gimp_n_point_deformation_options_set_sensitivity
parameter_list|(
name|GimpNPointDeformationOptions
modifier|*
name|npd_options
parameter_list|,
name|gboolean
name|tool_active
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|npd_options
operator|->
name|scale_square_size
argument_list|,
operator|!
name|tool_active
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|npd_options
operator|->
name|check_mesh_visible
argument_list|,
name|tool_active
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

