begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * "$Id$"  *  *   Main window code for Print plug-in for the GIMP.  *  *   Copyright 1997-2000 Michael Sweet (mike@easysw.com),  *	Robert Krawitz (rlk@alum.mit.edu), Steve Miller (smiller@rni.net)  *      and Michael Natterer (mitch@gimp.org)  *  *   This program is free software; you can redistribute it and/or modify it  *   under the terms of the GNU General Public License as published by the Free  *   Software Foundation; either version 2 of the License, or (at your option)  *   any later version.  *  *   This program is distributed in the hope that it will be useful, but  *   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  *   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License  *   for more details.  *  *   You should have received a copy of the GNU General Public License  *   along with this program; if not, write to the Free Software  *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"print_gimp.h"
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_1_0
end_ifndef

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
specifier|extern
name|vars_t
name|vars
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|plist_count
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Number of system printers */
end_comment

begin_decl_stmt
specifier|extern
name|gint
name|plist_current
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Current system printer */
end_comment

begin_decl_stmt
specifier|extern
name|plist_t
modifier|*
name|plist
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* System printers */
end_comment

begin_decl_stmt
DECL|variable|gimp_color_adjust_dialog
name|GtkWidget
modifier|*
name|gimp_color_adjust_dialog
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brightness_adjustment
specifier|static
name|GtkObject
modifier|*
name|brightness_adjustment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|saturation_adjustment
specifier|static
name|GtkObject
modifier|*
name|saturation_adjustment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|density_adjustment
specifier|static
name|GtkObject
modifier|*
name|density_adjustment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|contrast_adjustment
specifier|static
name|GtkObject
modifier|*
name|contrast_adjustment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|red_adjustment
specifier|static
name|GtkObject
modifier|*
name|red_adjustment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|green_adjustment
specifier|static
name|GtkObject
modifier|*
name|green_adjustment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|blue_adjustment
specifier|static
name|GtkObject
modifier|*
name|blue_adjustment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gamma_adjustment
specifier|static
name|GtkObject
modifier|*
name|gamma_adjustment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dither_algo_button
specifier|static
name|GtkWidget
modifier|*
name|dither_algo_button
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dither_algo_menu
specifier|static
name|GtkWidget
modifier|*
name|dither_algo_menu
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|gimp_brightness_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_saturation_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_density_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_contrast_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_red_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_green_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_blue_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gamma_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dither_algo_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_build_dither_menu
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * gimp_create_color_adjust_window (void)  *  * NOTES:  *   creates the color adjuster popup, allowing the user to adjust brightness,  *   contrast, saturation, etc.  */
end_comment

begin_function
name|void
DECL|function|gimp_create_color_adjust_window (void)
name|gimp_create_color_adjust_window
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|gimp_color_adjust_dialog
operator|=
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Print Color Adjust"
argument_list|)
argument_list|,
literal|"print"
argument_list|,
name|gimp_plugin_help_func
argument_list|,
literal|"filters/print.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Close"
argument_list|)
argument_list|,
name|gtk_widget_hide
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|9
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
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
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|7
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
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
comment|/*    * Brightness slider...    */
name|brightness_adjustment
operator|=
name|gimp_scale_entry_new
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
literal|"Brightness:"
argument_list|)
argument_list|,
literal|200
argument_list|,
literal|0
argument_list|,
name|vars
operator|.
name|brightness
argument_list|,
literal|0.0
argument_list|,
literal|400.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brightness_adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_brightness_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * Contrast slider...    */
name|contrast_adjustment
operator|=
name|gimp_scale_entry_new
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
literal|"Contrast:"
argument_list|)
argument_list|,
literal|200
argument_list|,
literal|0
argument_list|,
name|vars
operator|.
name|contrast
argument_list|,
literal|25.0
argument_list|,
literal|400.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|contrast_adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_contrast_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * Red slider...    */
name|red_adjustment
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"Red:"
argument_list|)
argument_list|,
literal|200
argument_list|,
literal|0
argument_list|,
name|vars
operator|.
name|red
argument_list|,
literal|0.0
argument_list|,
literal|200.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|red_adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_red_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * Green slider...    */
name|green_adjustment
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
name|_
argument_list|(
literal|"Green:"
argument_list|)
argument_list|,
literal|200
argument_list|,
literal|0
argument_list|,
name|vars
operator|.
name|green
argument_list|,
literal|0.0
argument_list|,
literal|200.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|green_adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_green_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * Blue slider...    */
name|blue_adjustment
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|,
name|_
argument_list|(
literal|"Blue:"
argument_list|)
argument_list|,
literal|200
argument_list|,
literal|0
argument_list|,
name|vars
operator|.
name|blue
argument_list|,
literal|0.0
argument_list|,
literal|200.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|blue_adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_blue_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * Saturation slider...    */
name|saturation_adjustment
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|5
argument_list|,
name|_
argument_list|(
literal|"Saturation:"
argument_list|)
argument_list|,
literal|200
argument_list|,
literal|0
argument_list|,
name|vars
operator|.
name|saturation
argument_list|,
literal|0
argument_list|,
literal|10.0
argument_list|,
literal|0.001
argument_list|,
literal|0.01
argument_list|,
literal|3
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|saturation_adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_saturation_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * Density slider...    */
name|density_adjustment
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|6
argument_list|,
name|_
argument_list|(
literal|"Density:"
argument_list|)
argument_list|,
literal|200
argument_list|,
literal|0
argument_list|,
name|vars
operator|.
name|density
argument_list|,
literal|0.1
argument_list|,
literal|3.0
argument_list|,
literal|0.001
argument_list|,
literal|0.01
argument_list|,
literal|3
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|density_adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_density_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * Gamma slider...    */
name|gamma_adjustment
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|7
argument_list|,
name|_
argument_list|(
literal|"Gamma:"
argument_list|)
argument_list|,
literal|200
argument_list|,
literal|0
argument_list|,
name|vars
operator|.
name|gamma
argument_list|,
literal|0.1
argument_list|,
literal|4.0
argument_list|,
literal|0.001
argument_list|,
literal|0.01
argument_list|,
literal|3
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gamma_adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_gamma_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * Dither algorithm option menu...    */
name|dither_algo_button
operator|=
name|gtk_option_menu_new
argument_list|()
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
literal|8
argument_list|,
name|_
argument_list|(
literal|"Dither Algorithm:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|dither_algo_button
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_build_dither_menu
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_update (GtkAdjustment * adjustment)
name|gimp_brightness_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
if|if
condition|(
name|vars
operator|.
name|brightness
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|vars
operator|.
name|brightness
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|brightness
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_contrast_update (GtkAdjustment * adjustment)
name|gimp_contrast_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
if|if
condition|(
name|vars
operator|.
name|contrast
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|vars
operator|.
name|contrast
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|contrast
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_red_update (GtkAdjustment * adjustment)
name|gimp_red_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
if|if
condition|(
name|vars
operator|.
name|red
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|vars
operator|.
name|red
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|red
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_green_update (GtkAdjustment * adjustment)
name|gimp_green_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
if|if
condition|(
name|vars
operator|.
name|green
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|vars
operator|.
name|green
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|green
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blue_update (GtkAdjustment * adjustment)
name|gimp_blue_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
if|if
condition|(
name|vars
operator|.
name|blue
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|vars
operator|.
name|blue
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|blue
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_saturation_update (GtkAdjustment * adjustment)
name|gimp_saturation_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
if|if
condition|(
name|vars
operator|.
name|saturation
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|vars
operator|.
name|saturation
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|saturation
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_density_update (GtkAdjustment * adjustment)
name|gimp_density_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
if|if
condition|(
name|vars
operator|.
name|density
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|vars
operator|.
name|density
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|density
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gamma_update (GtkAdjustment * adjustment)
name|gimp_gamma_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
if|if
condition|(
name|vars
operator|.
name|gamma
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|vars
operator|.
name|gamma
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|gamma
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_do_color_updates (void)
name|gimp_do_color_updates
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brightness_adjustment
argument_list|)
argument_list|,
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|brightness
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|gamma_adjustment
argument_list|)
argument_list|,
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|gamma
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|contrast_adjustment
argument_list|)
argument_list|,
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|contrast
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|red_adjustment
argument_list|)
argument_list|,
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|red
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|green_adjustment
argument_list|)
argument_list|,
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|green
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|blue_adjustment
argument_list|)
argument_list|,
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|blue
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|saturation_adjustment
argument_list|)
argument_list|,
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|saturation
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|density_adjustment
argument_list|)
argument_list|,
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|density
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_build_dither_menu (void)
name|gimp_build_dither_menu
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|item
decl_stmt|;
name|GtkWidget
modifier|*
name|item0
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|dither_algo_menu
operator|!=
name|NULL
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dither_algo_menu
argument_list|)
expr_stmt|;
name|dither_algo_menu
operator|=
name|NULL
expr_stmt|;
block|}
name|dither_algo_menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|num_dither_algos
operator|==
literal|0
condition|)
block|{
name|item
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Standard"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|dither_algo_menu
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|dither_algo_button
argument_list|)
argument_list|,
name|dither_algo_menu
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|dither_algo_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return;
block|}
else|else
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|dither_algo_button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_dither_algos
condition|;
name|i
operator|++
control|)
block|{
name|item
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|gettext
argument_list|(
name|dither_algo_names
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|0
condition|)
name|item0
operator|=
name|item
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|dither_algo_menu
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dither_algo_callback
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|i
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|dither_algo_button
argument_list|)
argument_list|,
name|dither_algo_menu
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
name|num_dither_algos
condition|;
name|i
operator|++
control|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|g_print
argument_list|(
literal|"item[%d] = \'%s\'\n"
argument_list|,
name|i
argument_list|,
name|dither_algo_names
index|[
name|i
index|]
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
if|if
condition|(
name|strcmp
argument_list|(
name|dither_algo_names
index|[
name|i
index|]
argument_list|,
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|dither_algorithm
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gtk_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|dither_algo_button
argument_list|)
argument_list|,
name|i
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|i
operator|==
name|num_dither_algos
condition|)
block|{
name|gtk_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|dither_algo_button
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_emit_by_name
argument_list|(
name|GTK_OBJECT
argument_list|(
name|item0
argument_list|)
argument_list|,
literal|"activate"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dither_algo_callback (GtkWidget * widget,gpointer data)
name|gimp_dither_algo_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|strcpy
argument_list|(
name|vars
operator|.
name|dither_algorithm
argument_list|,
name|dither_algo_names
index|[
operator|(
name|gint
operator|)
name|data
index|]
argument_list|)
expr_stmt|;
name|strcpy
argument_list|(
name|plist
index|[
name|plist_current
index|]
operator|.
name|v
operator|.
name|dither_algorithm
argument_list|,
name|dither_algo_names
index|[
operator|(
name|gint
operator|)
name|data
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ! GIMP_1_0 */
end_comment

end_unit

