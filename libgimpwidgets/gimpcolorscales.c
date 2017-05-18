begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorscales.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on color_notebook module  * Copyright (C) 1998 Austin Donnelly<austin@greenend.org.uk>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorscale.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorscales.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcolorscales  * @title: GimpColorScales  * @short_description: A #GimpColorSelector implementation.  *  * The #GimpColorScales widget is an implementation of a  * #GimpColorSelector. It shows a group of #GimpColorScale widgets  * that allow to adjust the HSV, LCH, and RGB color channels.  **/
end_comment

begin_typedef
DECL|typedef|GimpLCH
typedef|typedef
name|struct
name|_GimpLCH
name|GimpLCH
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLCH
struct|struct
name|_GimpLCH
block|{
DECL|member|l
DECL|member|c
DECL|member|h
DECL|member|a
name|gdouble
name|l
decl_stmt|,
name|c
decl_stmt|,
name|h
decl_stmt|,
name|a
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_COLOR_SCALES_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_SCALES_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_SCALES, GimpColorScalesClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_SCALES_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_SCALES_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_SCALES))
end_define

begin_define
DECL|macro|GIMP_COLOR_SCALES_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_SCALES_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_SCALES, GimpColorScalesClass))
end_define

begin_typedef
DECL|typedef|GimpColorScalesClass
typedef|typedef
name|struct
name|_GimpColorScalesClass
name|GimpColorScalesClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorScales
struct|struct
name|_GimpColorScales
block|{
DECL|member|parent_instance
name|GimpColorSelector
name|parent_instance
decl_stmt|;
DECL|member|toggles
name|GtkWidget
modifier|*
name|toggles
index|[
literal|10
index|]
decl_stmt|;
DECL|member|sliders
name|GtkWidget
modifier|*
name|sliders
index|[
literal|10
index|]
decl_stmt|;
DECL|member|slider_data
name|GtkObject
modifier|*
name|slider_data
index|[
literal|10
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorScalesClass
struct|struct
name|_GimpColorScalesClass
block|{
DECL|member|parent_class
name|GimpColorSelectorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_color_scales_togg_sensitive
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_scales_togg_visible
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_scales_set_show_alpha
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_scales_set_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_scales_set_channel
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_scales_set_config
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_scales_update_scales
parameter_list|(
name|GimpColorScales
modifier|*
name|scales
parameter_list|,
name|gint
name|skip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_scales_toggle_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorScales
modifier|*
name|scales
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_scales_scale_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorScales
modifier|*
name|scales
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorScales
argument_list|,
argument|gimp_color_scales
argument_list|,
argument|GIMP_TYPE_COLOR_SELECTOR
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_scales_parent_class
end_define

begin_decl_stmt
specifier|static
specifier|const
name|Babl
modifier|*
name|fish_rgb_to_lch
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fish_lch_to_rgb
specifier|static
specifier|const
name|Babl
modifier|*
name|fish_lch_to_rgb
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_class_init (GimpColorScalesClass * klass)
name|gimp_color_scales_class_init
parameter_list|(
name|GimpColorScalesClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpColorSelectorClass
modifier|*
name|selector_class
init|=
name|GIMP_COLOR_SELECTOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|selector_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Scales"
argument_list|)
expr_stmt|;
name|selector_class
operator|->
name|help_id
operator|=
literal|"gimp-colorselector-scales"
expr_stmt|;
name|selector_class
operator|->
name|icon_name
operator|=
name|GIMP_ICON_DIALOG_TOOL_OPTIONS
expr_stmt|;
name|selector_class
operator|->
name|set_toggles_visible
operator|=
name|gimp_color_scales_togg_visible
expr_stmt|;
name|selector_class
operator|->
name|set_toggles_sensitive
operator|=
name|gimp_color_scales_togg_sensitive
expr_stmt|;
name|selector_class
operator|->
name|set_show_alpha
operator|=
name|gimp_color_scales_set_show_alpha
expr_stmt|;
name|selector_class
operator|->
name|set_color
operator|=
name|gimp_color_scales_set_color
expr_stmt|;
name|selector_class
operator|->
name|set_channel
operator|=
name|gimp_color_scales_set_channel
expr_stmt|;
name|selector_class
operator|->
name|set_config
operator|=
name|gimp_color_scales_set_config
expr_stmt|;
name|fish_rgb_to_lch
operator|=
name|babl_fish
argument_list|(
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"CIE LCH(ab) double"
argument_list|)
argument_list|)
expr_stmt|;
name|fish_lch_to_rgb
operator|=
name|babl_fish
argument_list|(
name|babl_format
argument_list|(
literal|"CIE LCH(ab) double"
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B' double"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_init (GimpColorScales * scales)
name|gimp_color_scales_init
parameter_list|(
name|GimpColorScales
modifier|*
name|scales
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|scales
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GSList
modifier|*
name|group
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/*{   H,   S,   V,      R,    G,    B,   A,     L,   C,   H }*/
specifier|static
specifier|const
name|gdouble
name|slider_initial_vals
index|[]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
specifier|static
specifier|const
name|gdouble
name|slider_min_vals
index|[]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
specifier|static
specifier|const
name|gdouble
name|slider_max_vals
index|[]
init|=
block|{
literal|360
block|,
literal|100
block|,
literal|100
block|,
literal|100
block|,
literal|100
block|,
literal|100
block|,
literal|100
block|,
literal|100
block|,
literal|100
block|,
literal|360
block|}
decl_stmt|;
specifier|static
specifier|const
name|gdouble
name|slider_incs
index|[]
init|=
block|{
literal|30
block|,
literal|10
block|,
literal|10
block|,
literal|16
block|,
literal|16
block|,
literal|16
block|,
literal|10
block|,
literal|10
block|,
literal|10
block|,
literal|30
block|}
decl_stmt|;
specifier|static
specifier|const
name|gdouble
name|spin_min_vals
index|[]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
operator|-
literal|500
block|,
operator|-
literal|500
block|,
operator|-
literal|500
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
specifier|static
specifier|const
name|gdouble
name|spin_max_vals
index|[]
init|=
block|{
literal|360
block|,
literal|500
block|,
literal|500
block|,
literal|500
block|,
literal|500
block|,
literal|500
block|,
literal|100
block|,
literal|300
block|,
literal|300
block|,
literal|360
block|}
decl_stmt|;
comment|/*  don't needs the toggles for our own operation  */
name|selector
operator|->
name|toggles_visible
operator|=
name|FALSE
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|11
argument_list|,
literal|4
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
literal|1
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|5
argument_list|)
expr_stmt|;
comment|/* hsv<-> rgb   */
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|5
argument_list|,
literal|5
argument_list|)
expr_stmt|;
comment|/* rgb<-> alpha */
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|,
literal|5
argument_list|)
expr_stmt|;
comment|/* alpha<-> lch   */
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
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
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
name|scales
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
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_COLOR_SELECTOR_CHANNEL
argument_list|)
expr_stmt|;
name|group
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|10
condition|;
name|i
operator|++
control|)
block|{
name|GimpEnumDesc
modifier|*
name|enum_desc
init|=
name|gimp_enum_get_desc
argument_list|(
name|enum_class
argument_list|,
name|i
argument_list|)
decl_stmt|;
if|if
condition|(
name|i
operator|==
name|GIMP_COLOR_SELECTOR_ALPHA
condition|)
block|{
name|scales
operator|->
name|toggles
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|scales
operator|->
name|toggles
index|[
name|i
index|]
operator|=
name|gtk_radio_button_new
argument_list|(
name|group
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|scales
operator|->
name|toggles
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|scales
operator|->
name|toggles
index|[
name|i
index|]
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_EXPAND
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|selector
operator|->
name|toggles_visible
condition|)
name|gtk_widget_show
argument_list|(
name|scales
operator|->
name|toggles
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|scales
operator|->
name|toggles
index|[
name|i
index|]
argument_list|,
name|gettext
argument_list|(
name|enum_desc
operator|->
name|value_help
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|scales
operator|->
name|toggles
index|[
name|i
index|]
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_scales_toggle_changed
argument_list|)
argument_list|,
name|scales
argument_list|)
expr_stmt|;
block|}
name|scales
operator|->
name|slider_data
index|[
name|i
index|]
operator|=
name|gimp_color_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|1
argument_list|,
name|i
argument_list|,
name|gettext
argument_list|(
name|enum_desc
operator|->
name|value_desc
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|,
name|slider_initial_vals
index|[
name|i
index|]
argument_list|,
name|slider_min_vals
index|[
name|i
index|]
argument_list|,
name|slider_max_vals
index|[
name|i
index|]
argument_list|,
literal|1.0
argument_list|,
name|slider_incs
index|[
name|i
index|]
argument_list|,
literal|1
argument_list|,
name|gettext
argument_list|(
name|enum_desc
operator|->
name|value_help
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_adjustment_configure
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|scales
operator|->
name|slider_data
index|[
name|i
index|]
argument_list|)
argument_list|,
name|slider_initial_vals
index|[
name|i
index|]
argument_list|,
name|spin_min_vals
index|[
name|i
index|]
argument_list|,
name|spin_max_vals
index|[
name|i
index|]
argument_list|,
literal|1.0
argument_list|,
name|slider_incs
index|[
name|i
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|scales
operator|->
name|sliders
index|[
name|i
index|]
operator|=
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|scales
operator|->
name|slider_data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|scales
operator|->
name|sliders
index|[
name|i
index|]
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|scales
operator|->
name|sliders
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gimp_color_scale_set_channel
argument_list|(
name|GIMP_COLOR_SCALE
argument_list|(
name|scales
operator|->
name|sliders
index|[
name|i
index|]
argument_list|)
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|scales
operator|->
name|slider_data
index|[
name|i
index|]
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_scales_scale_changed
argument_list|)
argument_list|,
name|scales
argument_list|)
expr_stmt|;
block|}
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_togg_sensitive (GimpColorSelector * selector,gboolean sensitive)
name|gimp_color_scales_togg_sensitive
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
block|{
name|GimpColorScales
modifier|*
name|scales
init|=
name|GIMP_COLOR_SCALES
argument_list|(
name|selector
argument_list|)
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
literal|10
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|scales
operator|->
name|toggles
index|[
name|i
index|]
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|scales
operator|->
name|toggles
index|[
name|i
index|]
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_togg_visible (GimpColorSelector * selector,gboolean visible)
name|gimp_color_scales_togg_visible
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|visible
parameter_list|)
block|{
name|GimpColorScales
modifier|*
name|scales
init|=
name|GIMP_COLOR_SCALES
argument_list|(
name|selector
argument_list|)
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
literal|10
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|scales
operator|->
name|toggles
index|[
name|i
index|]
condition|)
name|gtk_widget_set_visible
argument_list|(
name|scales
operator|->
name|toggles
index|[
name|i
index|]
argument_list|,
name|visible
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_set_show_alpha (GimpColorSelector * selector,gboolean show_alpha)
name|gimp_color_scales_set_show_alpha
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|)
block|{
name|GimpColorScales
modifier|*
name|scales
init|=
name|GIMP_COLOR_SCALES
argument_list|(
name|selector
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|spin
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|label
operator|=
name|GIMP_SCALE_ENTRY_LABEL
argument_list|(
name|scales
operator|->
name|slider_data
index|[
literal|6
index|]
argument_list|)
expr_stmt|;
name|scale
operator|=
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|scales
operator|->
name|slider_data
index|[
literal|6
index|]
argument_list|)
expr_stmt|;
name|spin
operator|=
name|GIMP_SCALE_ENTRY_SPINBUTTON
argument_list|(
name|scales
operator|->
name|slider_data
index|[
literal|6
index|]
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_widget_get_parent
argument_list|(
name|scale
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_TABLE
argument_list|(
name|table
argument_list|)
condition|)
block|{
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|5
argument_list|,
comment|/* rgb<-> alpha */
name|show_alpha
condition|?
literal|3
else|:
literal|0
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_visible
argument_list|(
name|label
argument_list|,
name|show_alpha
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|scale
argument_list|,
name|show_alpha
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|spin
argument_list|,
name|show_alpha
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_set_color (GimpColorSelector * selector,const GimpRGB * rgb,const GimpHSV * hsv)
name|gimp_color_scales_set_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
block|{
name|GimpColorScales
modifier|*
name|scales
init|=
name|GIMP_COLOR_SCALES
argument_list|(
name|selector
argument_list|)
decl_stmt|;
name|gimp_color_scales_update_scales
argument_list|(
name|scales
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_set_channel (GimpColorSelector * selector,GimpColorSelectorChannel channel)
name|gimp_color_scales_set_channel
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
block|{
name|GimpColorScales
modifier|*
name|scales
init|=
name|GIMP_COLOR_SCALES
argument_list|(
name|selector
argument_list|)
decl_stmt|;
if|if
condition|(
name|scales
operator|->
name|toggles
index|[
name|channel
index|]
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|scales
operator|->
name|toggles
index|[
name|channel
index|]
argument_list|,
name|gimp_color_scales_toggle_changed
argument_list|,
name|scales
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|scales
operator|->
name|toggles
index|[
name|channel
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|scales
operator|->
name|toggles
index|[
name|channel
index|]
argument_list|,
name|gimp_color_scales_toggle_changed
argument_list|,
name|scales
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_set_config (GimpColorSelector * selector,GimpColorConfig * config)
name|gimp_color_scales_set_config
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpColorScales
modifier|*
name|scales
init|=
name|GIMP_COLOR_SCALES
argument_list|(
name|selector
argument_list|)
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
literal|10
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|scales
operator|->
name|sliders
index|[
name|i
index|]
condition|)
name|gimp_color_scale_set_color_config
argument_list|(
name|GIMP_COLOR_SCALE
argument_list|(
name|scales
operator|->
name|sliders
index|[
name|i
index|]
argument_list|)
argument_list|,
name|config
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_update_scales (GimpColorScales * scales,gint skip)
name|gimp_color_scales_update_scales
parameter_list|(
name|GimpColorScales
modifier|*
name|scales
parameter_list|,
name|gint
name|skip
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|scales
argument_list|)
decl_stmt|;
name|GimpLCH
name|lch
decl_stmt|;
name|gdouble
name|values
index|[
literal|10
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|babl_process
argument_list|(
name|fish_rgb_to_lch
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|lch
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_HUE
index|]
operator|=
name|selector
operator|->
name|hsv
operator|.
name|h
operator|*
literal|360.0
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_SATURATION
index|]
operator|=
name|selector
operator|->
name|hsv
operator|.
name|s
operator|*
literal|100.0
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_VALUE
index|]
operator|=
name|selector
operator|->
name|hsv
operator|.
name|v
operator|*
literal|100.0
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_RED
index|]
operator|=
name|selector
operator|->
name|rgb
operator|.
name|r
operator|*
literal|100.0
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_GREEN
index|]
operator|=
name|selector
operator|->
name|rgb
operator|.
name|g
operator|*
literal|100.0
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_BLUE
index|]
operator|=
name|selector
operator|->
name|rgb
operator|.
name|b
operator|*
literal|100.0
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_ALPHA
index|]
operator|=
name|selector
operator|->
name|rgb
operator|.
name|a
operator|*
literal|100.0
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_LCH_LIGHTNESS
index|]
operator|=
name|lch
operator|.
name|l
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_LCH_CHROMA
index|]
operator|=
name|lch
operator|.
name|c
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_LCH_HUE
index|]
operator|=
name|lch
operator|.
name|h
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|10
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|!=
name|skip
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|scales
operator|->
name|slider_data
index|[
name|i
index|]
argument_list|,
name|gimp_color_scales_scale_changed
argument_list|,
name|scales
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|scales
operator|->
name|slider_data
index|[
name|i
index|]
argument_list|)
argument_list|,
name|values
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|scales
operator|->
name|slider_data
index|[
name|i
index|]
argument_list|,
name|gimp_color_scales_scale_changed
argument_list|,
name|scales
argument_list|)
expr_stmt|;
block|}
name|gimp_color_scale_set_color
argument_list|(
name|GIMP_COLOR_SCALE
argument_list|(
name|scales
operator|->
name|sliders
index|[
name|i
index|]
argument_list|)
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|selector
operator|->
name|hsv
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_toggle_changed (GtkWidget * widget,GimpColorScales * scales)
name|gimp_color_scales_toggle_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorScales
modifier|*
name|scales
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|scales
argument_list|)
decl_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
condition|)
block|{
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
literal|10
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|widget
operator|==
name|scales
operator|->
name|toggles
index|[
name|i
index|]
condition|)
block|{
name|selector
operator|->
name|channel
operator|=
operator|(
name|GimpColorSelectorChannel
operator|)
name|i
expr_stmt|;
break|break;
block|}
name|gimp_color_selector_channel_changed
argument_list|(
name|selector
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_scales_scale_changed (GtkAdjustment * adjustment,GimpColorScales * scales)
name|gimp_color_scales_scale_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorScales
modifier|*
name|scales
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|scales
argument_list|)
decl_stmt|;
name|gdouble
name|value
init|=
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
decl_stmt|;
name|GimpLCH
name|lch
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
literal|10
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|scales
operator|->
name|slider_data
index|[
name|i
index|]
operator|==
name|GTK_OBJECT
argument_list|(
name|adjustment
argument_list|)
condition|)
break|break;
switch|switch
condition|(
name|i
condition|)
block|{
case|case
name|GIMP_COLOR_SELECTOR_HUE
case|:
name|selector
operator|->
name|hsv
operator|.
name|h
operator|=
name|value
operator|/
literal|360.0
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_SATURATION
case|:
name|selector
operator|->
name|hsv
operator|.
name|s
operator|=
name|value
operator|/
literal|100.0
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_VALUE
case|:
name|selector
operator|->
name|hsv
operator|.
name|v
operator|=
name|value
operator|/
literal|100.0
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_RED
case|:
name|selector
operator|->
name|rgb
operator|.
name|r
operator|=
name|value
operator|/
literal|100.0
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_GREEN
case|:
name|selector
operator|->
name|rgb
operator|.
name|g
operator|=
name|value
operator|/
literal|100.0
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_BLUE
case|:
name|selector
operator|->
name|rgb
operator|.
name|b
operator|=
name|value
operator|/
literal|100.0
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_ALPHA
case|:
name|selector
operator|->
name|hsv
operator|.
name|a
operator|=
name|selector
operator|->
name|rgb
operator|.
name|a
operator|=
name|value
operator|/
literal|100.0
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_LCH_LIGHTNESS
case|:
name|babl_process
argument_list|(
name|fish_rgb_to_lch
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|lch
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|lch
operator|.
name|l
operator|=
name|value
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_LCH_CHROMA
case|:
name|babl_process
argument_list|(
name|fish_rgb_to_lch
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|lch
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|lch
operator|.
name|c
operator|=
name|value
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_LCH_HUE
case|:
name|babl_process
argument_list|(
name|fish_rgb_to_lch
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|lch
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|lch
operator|.
name|h
operator|=
name|value
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|(
name|i
operator|>=
name|GIMP_COLOR_SELECTOR_HUE
operator|)
operator|&&
operator|(
name|i
operator|<=
name|GIMP_COLOR_SELECTOR_VALUE
operator|)
condition|)
block|{
name|gimp_hsv_to_rgb
argument_list|(
operator|&
name|selector
operator|->
name|hsv
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|i
operator|>=
name|GIMP_COLOR_SELECTOR_LCH_LIGHTNESS
operator|)
operator|&&
operator|(
name|i
operator|<=
name|GIMP_COLOR_SELECTOR_LCH_HUE
operator|)
condition|)
block|{
name|babl_process
argument_list|(
name|fish_lch_to_rgb
argument_list|,
operator|&
name|lch
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|selector
operator|->
name|hsv
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|i
operator|>=
name|GIMP_COLOR_SELECTOR_RED
operator|)
operator|&&
operator|(
name|i
operator|<=
name|GIMP_COLOR_SELECTOR_BLUE
operator|)
condition|)
block|{
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|selector
operator|->
name|hsv
argument_list|)
expr_stmt|;
block|}
name|gimp_color_scales_update_scales
argument_list|(
name|scales
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|gimp_color_selector_color_changed
argument_list|(
name|selector
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

