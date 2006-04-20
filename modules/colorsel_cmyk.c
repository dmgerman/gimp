begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP CMYK ColorSelector  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/* definitions and variables */
end_comment

begin_define
DECL|macro|COLORSEL_TYPE_CMYK
define|#
directive|define
name|COLORSEL_TYPE_CMYK
value|(colorsel_cmyk_type)
end_define

begin_define
DECL|macro|COLORSEL_CMYK (obj)
define|#
directive|define
name|COLORSEL_CMYK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), COLORSEL_TYPE_CMYK, ColorselCmyk))
end_define

begin_define
DECL|macro|COLORSEL_CMYK_CLASS (klass)
define|#
directive|define
name|COLORSEL_CMYK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), COLORSEL_TYPE_CMYK, ColorselCmykClass))
end_define

begin_define
DECL|macro|COLORSEL_IS_CMYK (obj)
define|#
directive|define
name|COLORSEL_IS_CMYK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), COLORSEL_TYPE_CMYK))
end_define

begin_define
DECL|macro|COLORSEL_IS_CMYK_CLASS (klass)
define|#
directive|define
name|COLORSEL_IS_CMYK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), COLORSEL_TYPE_CMYK))
end_define

begin_typedef
DECL|typedef|ColorselCmyk
typedef|typedef
name|struct
name|_ColorselCmyk
name|ColorselCmyk
typedef|;
end_typedef

begin_typedef
DECL|typedef|ColorselCmykClass
typedef|typedef
name|struct
name|_ColorselCmykClass
name|ColorselCmykClass
typedef|;
end_typedef

begin_struct
DECL|struct|_ColorselCmyk
struct|struct
name|_ColorselCmyk
block|{
DECL|member|parent_instance
name|GimpColorSelector
name|parent_instance
decl_stmt|;
DECL|member|cmyk
name|GimpCMYK
name|cmyk
decl_stmt|;
DECL|member|pullout
name|gdouble
name|pullout
decl_stmt|;
DECL|member|adj
name|GtkAdjustment
modifier|*
name|adj
index|[
literal|5
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ColorselCmykClass
struct|struct
name|_ColorselCmykClass
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
name|GType
name|colorsel_cmyk_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_cmyk_class_init
parameter_list|(
name|ColorselCmykClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_cmyk_init
parameter_list|(
name|ColorselCmyk
modifier|*
name|cmyk
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_cmyk_set_color
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
name|colorsel_cmyk_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|ColorselCmyk
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_cmyk_pullout_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|ColorselCmyk
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|colorsel_cmyk_info
specifier|static
specifier|const
name|GimpModuleInfo
name|colorsel_cmyk_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"CMYK color selector"
argument_list|)
block|,
literal|"Sven Neumann<sven@gimp.org>"
block|,
literal|"v0.2"
block|,
literal|"(c) 2003, released under the GPL"
block|,
literal|"July 2003"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|colorsel_cmyk_type
specifier|static
name|GType
name|colorsel_cmyk_type
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
DECL|function|gimp_module_query (GTypeModule * module)
name|gimp_module_query
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
return|return
operator|&
name|colorsel_cmyk_info
return|;
block|}
end_function

begin_function
name|G_MODULE_EXPORT
name|gboolean
DECL|function|gimp_module_register (GTypeModule * module)
name|gimp_module_register
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
name|colorsel_cmyk_get_type
argument_list|(
name|module
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GType
DECL|function|colorsel_cmyk_get_type (GTypeModule * module)
name|colorsel_cmyk_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
if|if
condition|(
operator|!
name|colorsel_cmyk_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|select_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|ColorselCmykClass
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
name|colorsel_cmyk_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|ColorselCmyk
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|colorsel_cmyk_init
block|,       }
decl_stmt|;
name|colorsel_cmyk_type
operator|=
name|g_type_module_register_type
argument_list|(
name|module
argument_list|,
name|GIMP_TYPE_COLOR_SELECTOR
argument_list|,
literal|"ColorselCmyk"
argument_list|,
operator|&
name|select_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|colorsel_cmyk_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_cmyk_class_init (ColorselCmykClass * klass)
name|colorsel_cmyk_class_init
parameter_list|(
name|ColorselCmykClass
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
literal|"CMYK"
argument_list|)
expr_stmt|;
name|selector_class
operator|->
name|help_id
operator|=
literal|"gimp-colorselector-cmyk"
expr_stmt|;
name|selector_class
operator|->
name|stock_id
operator|=
name|GTK_STOCK_PRINT
expr_stmt|;
comment|/* FIXME */
name|selector_class
operator|->
name|set_color
operator|=
name|colorsel_cmyk_set_color
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_cmyk_init (ColorselCmyk * module)
name|colorsel_cmyk_init
parameter_list|(
name|ColorselCmyk
modifier|*
name|module
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gint
name|i
decl_stmt|;
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
name|cmyk_labels
index|[]
init|=
block|{
comment|/* Cyan        */
name|N_
argument_list|(
literal|"_C"
argument_list|)
block|,
comment|/* Magenta     */
name|N_
argument_list|(
literal|"_M"
argument_list|)
block|,
comment|/* Yellow      */
name|N_
argument_list|(
literal|"_Y"
argument_list|)
block|,
comment|/* Key (Black) */
name|N_
argument_list|(
literal|"_K"
argument_list|)
block|}
decl_stmt|;
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
name|cmyk_tips
index|[]
init|=
block|{
name|N_
argument_list|(
literal|"Cyan"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Magenta"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Yellow"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Black"
argument_list|)
block|}
decl_stmt|;
name|module
operator|->
name|pullout
operator|=
literal|1.0
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|5
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
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|module
argument_list|)
argument_list|,
name|table
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
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
literal|4
condition|;
name|i
operator|++
control|)
block|{
name|adj
operator|=
name|gimp_scale_entry_new
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
name|cmyk_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|gettext
argument_list|(
name|cmyk_tips
index|[
name|i
index|]
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|colorsel_cmyk_adj_update
argument_list|)
argument_list|,
name|module
argument_list|)
expr_stmt|;
name|module
operator|->
name|adj
index|[
name|i
index|]
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|adj
argument_list|)
expr_stmt|;
block|}
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Black _pullout:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adj
argument_list|,
name|module
operator|->
name|pullout
operator|*
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|spinbutton
argument_list|,
name|_
argument_list|(
literal|"The percentage of black to pull out "
literal|"of the colored inks."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|colorsel_cmyk_pullout_update
argument_list|)
argument_list|,
name|module
argument_list|)
expr_stmt|;
name|module
operator|->
name|adj
index|[
name|i
index|]
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|adj
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_cmyk_set_color (GimpColorSelector * selector,const GimpRGB * rgb,const GimpHSV * hsv)
name|colorsel_cmyk_set_color
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
name|ColorselCmyk
modifier|*
name|module
init|=
name|COLORSEL_CMYK
argument_list|(
name|selector
argument_list|)
decl_stmt|;
name|gimp_rgb_to_cmyk
argument_list|(
name|rgb
argument_list|,
name|module
operator|->
name|pullout
argument_list|,
operator|&
name|module
operator|->
name|cmyk
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|module
operator|->
name|adj
index|[
literal|0
index|]
argument_list|,
name|module
operator|->
name|cmyk
operator|.
name|c
operator|*
literal|100.0
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|module
operator|->
name|adj
index|[
literal|1
index|]
argument_list|,
name|module
operator|->
name|cmyk
operator|.
name|m
operator|*
literal|100.0
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|module
operator|->
name|adj
index|[
literal|2
index|]
argument_list|,
name|module
operator|->
name|cmyk
operator|.
name|y
operator|*
literal|100.0
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|module
operator|->
name|adj
index|[
literal|3
index|]
argument_list|,
name|module
operator|->
name|cmyk
operator|.
name|k
operator|*
literal|100.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_cmyk_adj_update (GtkAdjustment * adj,ColorselCmyk * module)
name|colorsel_cmyk_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|ColorselCmyk
modifier|*
name|module
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|module
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
literal|4
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|module
operator|->
name|adj
index|[
name|i
index|]
operator|==
name|adj
condition|)
break|break;
switch|switch
condition|(
name|i
condition|)
block|{
case|case
literal|0
case|:
name|module
operator|->
name|cmyk
operator|.
name|c
operator|=
name|adj
operator|->
name|value
operator|/
literal|100.0
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|module
operator|->
name|cmyk
operator|.
name|m
operator|=
name|adj
operator|->
name|value
operator|/
literal|100.0
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|module
operator|->
name|cmyk
operator|.
name|y
operator|=
name|adj
operator|->
name|value
operator|/
literal|100.0
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|module
operator|->
name|cmyk
operator|.
name|k
operator|=
name|adj
operator|->
name|value
operator|/
literal|100.0
expr_stmt|;
break|break;
default|default:
return|return;
block|}
name|gimp_cmyk_to_rgb
argument_list|(
operator|&
name|module
operator|->
name|cmyk
argument_list|,
operator|&
name|selector
operator|->
name|rgb
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
name|gimp_color_selector_color_changed
argument_list|(
name|selector
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_cmyk_pullout_update (GtkAdjustment * adj,ColorselCmyk * module)
name|colorsel_cmyk_pullout_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|ColorselCmyk
modifier|*
name|module
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|module
argument_list|)
decl_stmt|;
name|module
operator|->
name|pullout
operator|=
name|adj
operator|->
name|value
operator|/
literal|100.0
expr_stmt|;
name|gimp_color_selector_set_color
argument_list|(
name|selector
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
end_function

end_unit

