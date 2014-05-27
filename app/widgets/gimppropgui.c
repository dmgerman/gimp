begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropgui.c  * Copyright (C) 2002-2014  Michael Natterer<mitch@gimp.org>  *                          Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gegl-paramspecs.h>
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
file|"libgimpbase/gimpbase.h"
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpanel.h"
end_include

begin_include
include|#
directive|include
file|"gimpspinscale.h"
end_include

begin_include
include|#
directive|include
file|"gimppropgui.h"
end_include

begin_include
include|#
directive|include
file|"gimppropgui-constructors.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|HAS_KEY (p,k,v)
define|#
directive|define
name|HAS_KEY
parameter_list|(
name|p
parameter_list|,
name|k
parameter_list|,
name|v
parameter_list|)
value|gimp_gegl_param_spec_has_key (p, k, v)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_prop_widget_new_seed_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GtkAdjustment
modifier|*
name|adj
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_widget_new (GObject * config,GParamSpec * pspec,GimpContext * context,GimpCreatePickerFunc create_picker_func,gpointer picker_creator,const gchar ** label)
name|gimp_prop_widget_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpCreatePickerFunc
name|create_picker_func
parameter_list|,
name|gpointer
name|picker_creator
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|label
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|G_OBJECT_TYPE
argument_list|(
name|config
argument_list|)
argument_list|,
name|pspec
operator|->
name|owner_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|label
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|label
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_SEED
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|GtkWidget
modifier|*
name|spin
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|widget
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|spin
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|config
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
name|spin
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
name|spin
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"New Seed"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|widget
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
name|adj
operator|=
name|gtk_spin_button_get_adjustment
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spin
argument_list|)
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
name|gimp_prop_widget_new_seed_clicked
argument_list|)
argument_list|,
name|adj
argument_list|)
expr_stmt|;
operator|*
name|label
operator|=
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
operator|||
name|G_IS_PARAM_SPEC_UINT
argument_list|(
name|pspec
argument_list|)
operator|||
name|G_IS_PARAM_SPEC_FLOAT
argument_list|(
name|pspec
argument_list|)
operator|||
name|G_IS_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|gdouble
name|lower
decl_stmt|;
name|gdouble
name|upper
decl_stmt|;
name|gdouble
name|step
decl_stmt|;
name|gdouble
name|page
decl_stmt|;
name|gint
name|digits
decl_stmt|;
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GeglParamSpecDouble
modifier|*
name|gspec
init|=
name|GEGL_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|lower
operator|=
name|gspec
operator|->
name|ui_minimum
expr_stmt|;
name|upper
operator|=
name|gspec
operator|->
name|ui_maximum
expr_stmt|;
name|step
operator|=
name|gspec
operator|->
name|ui_step_small
expr_stmt|;
name|page
operator|=
name|gspec
operator|->
name|ui_step_big
expr_stmt|;
name|digits
operator|=
name|gspec
operator|->
name|ui_digits
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GeglParamSpecInt
modifier|*
name|gspec
init|=
name|GEGL_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|lower
operator|=
name|gspec
operator|->
name|ui_minimum
expr_stmt|;
name|upper
operator|=
name|gspec
operator|->
name|ui_maximum
expr_stmt|;
name|step
operator|=
name|gspec
operator|->
name|ui_step_small
expr_stmt|;
name|page
operator|=
name|gspec
operator|->
name|ui_step_big
expr_stmt|;
name|digits
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|value
decl_stmt|;
name|_gimp_prop_widgets_get_numeric_values
argument_list|(
name|config
argument_list|,
name|pspec
argument_list|,
operator|&
name|value
argument_list|,
operator|&
name|lower
argument_list|,
operator|&
name|upper
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|upper
operator|-
name|lower
operator|<=
literal|1.0
operator|)
operator|&&
operator|(
name|G_IS_PARAM_SPEC_FLOAT
argument_list|(
name|pspec
argument_list|)
operator|||
name|G_IS_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
operator|)
condition|)
block|{
name|step
operator|=
literal|0.01
expr_stmt|;
name|page
operator|=
literal|0.1
expr_stmt|;
name|digits
operator|=
literal|4
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|upper
operator|-
name|lower
operator|<=
literal|10.0
operator|)
operator|&&
operator|(
name|G_IS_PARAM_SPEC_FLOAT
argument_list|(
name|pspec
argument_list|)
operator|||
name|G_IS_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
operator|)
condition|)
block|{
name|step
operator|=
literal|0.1
expr_stmt|;
name|page
operator|=
literal|1.0
expr_stmt|;
name|digits
operator|=
literal|3
expr_stmt|;
block|}
else|else
block|{
name|step
operator|=
literal|1.0
expr_stmt|;
name|page
operator|=
literal|10.0
expr_stmt|;
name|digits
operator|=
operator|(
name|G_IS_PARAM_SPEC_FLOAT
argument_list|(
name|pspec
argument_list|)
operator|||
name|G_IS_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
operator|)
condition|?
literal|2
else|:
literal|0
expr_stmt|;
block|}
block|}
name|widget
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|step
argument_list|,
name|page
argument_list|,
name|digits
argument_list|)
expr_stmt|;
if|if
condition|(
name|HAS_KEY
argument_list|(
name|pspec
argument_list|,
literal|"unit"
argument_list|,
literal|"degree"
argument_list|)
operator|&&
operator|(
name|upper
operator|-
name|lower
operator|)
operator|==
literal|360.0
condition|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|dial
decl_stmt|;
name|gtk_spin_button_set_wrap
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|widget
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
name|widget
argument_list|)
expr_stmt|;
name|dial
operator|=
name|gimp_prop_angle_dial_new
argument_list|(
name|config
argument_list|,
name|pspec
operator|->
name|name
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|dial
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
name|dial
argument_list|)
expr_stmt|;
name|widget
operator|=
name|hbox
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_STRING
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
specifier|static
name|GQuark
name|multiline_quark
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|multiline_quark
condition|)
name|multiline_quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"multiline"
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_CONFIG_PATH
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|widget
operator|=
name|gimp_prop_file_chooser_button_new
argument_list|(
name|config
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_OPEN
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_param_spec_get_qdata
argument_list|(
name|pspec
argument_list|,
name|multiline_quark
argument_list|)
condition|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|buffer
operator|=
name|gimp_prop_text_buffer_new
argument_list|(
name|config
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|view
operator|=
name|gtk_text_view_new_with_buffer
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_shadow_type
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|widget
operator|=
name|gimp_prop_entry_new
argument_list|(
name|config
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
operator|*
name|label
operator|=
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_BOOLEAN
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|widget
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|widget
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
name|pspec
operator|->
name|name
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
name|widget
argument_list|)
argument_list|,
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_RGB
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|widget
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_color_button_new
argument_list|(
name|config
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
argument_list|,
literal|128
argument_list|,
literal|24
argument_list|,
name|GIMP_COLOR_AREA_SMALL_CHECKS
argument_list|)
expr_stmt|;
name|gimp_color_button_set_update
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_color_panel_set_context
argument_list|(
name|GIMP_COLOR_PANEL
argument_list|(
name|button
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
if|if
condition|(
name|create_picker_func
condition|)
block|{
name|button
operator|=
name|create_picker_func
argument_list|(
name|picker_creator
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|GIMP_STOCK_COLOR_PICKER_GRAY
argument_list|,
name|_
argument_list|(
literal|"Pick color from the image"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|widget
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
block|}
operator|*
name|label
operator|=
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: not supported: %s (%s)\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|pspec
argument_list|)
argument_list|)
argument_list|,
name|pspec
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|widget
return|;
block|}
end_function

begin_typedef
DECL|typedef|GimpPropGuiNewFunc
typedef|typedef
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|GimpPropGuiNewFunc
function_decl|)
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|param_specs
parameter_list|,
name|guint
name|n_param_specs
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpCreatePickerFunc
name|create_picker_func
parameter_list|,
name|gpointer
name|picker_creator
parameter_list|)
function_decl|;
end_typedef

begin_struct
specifier|static
specifier|const
struct|struct
DECL|struct|__anon2770d5f60108
block|{
DECL|member|config_type
specifier|const
name|gchar
modifier|*
name|config_type
decl_stmt|;
DECL|member|gui_new_func
name|GimpPropGuiNewFunc
name|gui_new_func
decl_stmt|;
block|}
DECL|variable|gui_new_funcs
name|gui_new_funcs
index|[]
init|=
block|{
block|{
literal|"GimpGegl-gegl-color-rotate-config"
block|,
name|_gimp_prop_gui_new_generic
block|}
block|,
block|{
literal|"GimpGegl-gegl-convolution-matrix-config"
block|,
name|_gimp_prop_gui_new_generic
block|}
block|,
block|{
name|NULL
block|,
name|_gimp_prop_gui_new_generic
block|}
block|}
struct|;
end_struct

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_gui_new (GObject * config,GType owner_type,GimpContext * context,GimpCreatePickerFunc create_picker_func,gpointer picker_creator)
name|gimp_prop_gui_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GType
name|owner_type
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpCreatePickerFunc
name|create_picker_func
parameter_list|,
name|gpointer
name|picker_creator
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|gui
init|=
name|NULL
decl_stmt|;
name|GParamSpec
modifier|*
modifier|*
name|param_specs
decl_stmt|;
name|guint
name|n_param_specs
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|config_type_name
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|param_specs
operator|=
name|g_object_class_list_properties
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|config
argument_list|)
argument_list|,
operator|&
name|n_param_specs
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|j
operator|=
literal|0
init|;
name|i
operator|<
name|n_param_specs
condition|;
name|i
operator|++
control|)
block|{
name|GParamSpec
modifier|*
name|pspec
init|=
name|param_specs
index|[
name|i
index|]
decl_stmt|;
comment|/*  ignore properties of parent classes of owner_type  */
if|if
condition|(
operator|!
name|g_type_is_a
argument_list|(
name|pspec
operator|->
name|owner_type
argument_list|,
name|owner_type
argument_list|)
condition|)
continue|continue;
if|if
condition|(
name|HAS_KEY
argument_list|(
name|pspec
argument_list|,
literal|"role"
argument_list|,
literal|"output-extent"
argument_list|)
condition|)
continue|continue;
name|param_specs
index|[
name|j
index|]
operator|=
name|param_specs
index|[
name|i
index|]
expr_stmt|;
name|j
operator|++
expr_stmt|;
block|}
name|n_param_specs
operator|=
name|j
expr_stmt|;
name|config_type_name
operator|=
name|G_OBJECT_TYPE_NAME
argument_list|(
name|config
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|gui_new_funcs
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|gui_new_funcs
index|[
name|i
index|]
operator|.
name|config_type
operator|||
operator|!
name|strcmp
argument_list|(
name|gui_new_funcs
index|[
name|i
index|]
operator|.
name|config_type
argument_list|,
name|config_type_name
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"GUI new func match: %s\n"
argument_list|,
name|gui_new_funcs
index|[
name|i
index|]
operator|.
name|config_type
condition|?
name|gui_new_funcs
index|[
name|i
index|]
operator|.
name|config_type
else|:
literal|"generic fallback"
argument_list|)
expr_stmt|;
name|gui
operator|=
name|gui_new_funcs
index|[
name|i
index|]
operator|.
name|gui_new_func
argument_list|(
name|config
argument_list|,
name|param_specs
argument_list|,
name|n_param_specs
argument_list|,
name|context
argument_list|,
name|create_picker_func
argument_list|,
name|picker_creator
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|g_free
argument_list|(
name|param_specs
argument_list|)
expr_stmt|;
return|return
name|gui
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_prop_widget_new_seed_clicked (GtkButton * button,GtkAdjustment * adj)
name|gimp_prop_widget_new_seed_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GtkAdjustment
modifier|*
name|adj
parameter_list|)
block|{
name|guint32
name|value
init|=
name|g_random_int_range
argument_list|(
name|gtk_adjustment_get_lower
argument_list|(
name|adj
argument_list|)
argument_list|,
name|gtk_adjustment_get_upper
argument_list|(
name|adj
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|adj
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

