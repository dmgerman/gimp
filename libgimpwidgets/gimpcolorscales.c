begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorscales.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on color_notebook module  * Copyright (C) 1998 Austin Donnelly<austin@greenend.org.uk>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
literal|7
index|]
decl_stmt|;
DECL|member|sliders
name|GtkWidget
modifier|*
name|sliders
index|[
literal|7
index|]
decl_stmt|;
DECL|member|slider_data
name|GtkObject
modifier|*
name|slider_data
index|[
literal|7
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
name|gimp_color_scales_class_init
parameter_list|(
name|GimpColorScalesClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_scales_init
parameter_list|(
name|GimpColorScales
modifier|*
name|scales
parameter_list|)
function_decl|;
end_function_decl

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
name|gimp_color_scales_toggle_update
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
name|gimp_color_scales_scale_update
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpColorSelectorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_color_scales_get_type (void)
name|gimp_color_scales_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|scales_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|scales_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|scales_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpColorScalesClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_color_scales_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorScales
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_scales_init
block|,       }
decl_stmt|;
name|scales_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_COLOR_SELECTOR
argument_list|,
literal|"GimpColorScales"
argument_list|,
operator|&
name|scales_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|scales_type
return|;
block|}
end_function

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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|stock_id
operator|=
name|GIMP_STOCK_TOOL_OPTIONS
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
specifier|static
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
block|}
decl_stmt|;
specifier|static
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
literal|255
block|,
literal|255
block|,
literal|255
block|,
literal|100
block|}
decl_stmt|;
specifier|static
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
literal|7
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
literal|3
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
literal|3
argument_list|)
expr_stmt|;
comment|/* rgb<-> alpha */
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
name|GIMP_COLOR_SELECTOR_HUE
init|;
name|i
operator|<=
name|GIMP_COLOR_SELECTOR_ALPHA
condition|;
name|i
operator|++
control|)
block|{
name|GimpEnumDesc
modifier|*
name|enum_desc
decl_stmt|;
name|enum_desc
operator|=
name|gimp_enum_get_desc
argument_list|(
name|enum_class
argument_list|,
name|i
argument_list|)
expr_stmt|;
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
name|gimp_color_scales_toggle_update
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
literal|0.0
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
literal|0
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
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_scales_scale_update
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
literal|6
condition|;
name|i
operator|++
control|)
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
literal|6
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|visible
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
else|else
name|gtk_widget_hide
argument_list|(
name|scales
operator|->
name|toggles
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
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
if|if
condition|(
name|show_alpha
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spin
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_hide
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|scale
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|spin
argument_list|)
expr_stmt|;
block|}
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
name|channel
operator|>=
literal|0
operator|&&
name|channel
operator|<=
literal|7
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
name|gimp_color_scales_toggle_update
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
name|gimp_color_scales_toggle_update
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
name|gint
name|values
index|[
literal|7
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_HUE
index|]
operator|=
name|ROUND
argument_list|(
name|selector
operator|->
name|hsv
operator|.
name|h
operator|*
literal|360.0
argument_list|)
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_SATURATION
index|]
operator|=
name|ROUND
argument_list|(
name|selector
operator|->
name|hsv
operator|.
name|s
operator|*
literal|100.0
argument_list|)
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_VALUE
index|]
operator|=
name|ROUND
argument_list|(
name|selector
operator|->
name|hsv
operator|.
name|v
operator|*
literal|100.0
argument_list|)
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_RED
index|]
operator|=
name|ROUND
argument_list|(
name|selector
operator|->
name|rgb
operator|.
name|r
operator|*
literal|255.0
argument_list|)
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_GREEN
index|]
operator|=
name|ROUND
argument_list|(
name|selector
operator|->
name|rgb
operator|.
name|g
operator|*
literal|255.0
argument_list|)
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_BLUE
index|]
operator|=
name|ROUND
argument_list|(
name|selector
operator|->
name|rgb
operator|.
name|b
operator|*
literal|255.0
argument_list|)
expr_stmt|;
name|values
index|[
name|GIMP_COLOR_SELECTOR_ALPHA
index|]
operator|=
name|ROUND
argument_list|(
name|selector
operator|->
name|rgb
operator|.
name|a
operator|*
literal|100.0
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
literal|7
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
name|gimp_color_scales_scale_update
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
name|gimp_color_scales_scale_update
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
DECL|function|gimp_color_scales_toggle_update (GtkWidget * widget,GimpColorScales * scales)
name|gimp_color_scales_toggle_update
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
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
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
literal|6
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
DECL|function|gimp_color_scales_scale_update (GtkAdjustment * adjustment,GimpColorScales * scales)
name|gimp_color_scales_scale_update
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
literal|7
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
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
operator|->
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
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
operator|->
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
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
operator|->
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
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
operator|->
name|value
operator|/
literal|255.0
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
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
operator|->
name|value
operator|/
literal|255.0
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
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
operator|->
name|value
operator|/
literal|255.0
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
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
operator|->
name|value
operator|/
literal|100.0
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

