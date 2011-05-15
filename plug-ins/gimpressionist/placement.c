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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"gimpressionist.h"
end_include

begin_include
include|#
directive|include
file|"placement.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|NUM_PLACE_RADIO
define|#
directive|define
name|NUM_PLACE_RADIO
value|2
end_define

begin_decl_stmt
DECL|variable|placement_radio
specifier|static
name|GtkWidget
modifier|*
name|placement_radio
index|[
name|NUM_PLACE_RADIO
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|placement_center
specifier|static
name|GtkWidget
modifier|*
name|placement_center
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brush_density_adjust
specifier|static
name|GtkAdjustment
modifier|*
name|brush_density_adjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|place_restore (void)
name|place_restore
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|placement_radio
index|[
name|pcvals
operator|.
name|place_type
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|placement_center
argument_list|)
argument_list|,
name|pcvals
operator|.
name|placement_center
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brush_density_adjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|brush_density
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|place_type_input (int in)
name|place_type_input
parameter_list|(
name|int
name|in
parameter_list|)
block|{
return|return
name|CLAMP_UP_TO
argument_list|(
name|in
argument_list|,
name|NUM_PLACE_RADIO
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|place_store (void)
name|place_store
parameter_list|(
name|void
parameter_list|)
block|{
name|pcvals
operator|.
name|placement_center
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|placement_center
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|create_placementpage (GtkNotebook * notebook)
name|create_placementpage
parameter_list|(
name|GtkNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|,
modifier|*
name|tmpw
decl_stmt|,
modifier|*
name|table
decl_stmt|,
modifier|*
name|frame
decl_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Pl_acement"
argument_list|)
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_int_radio_group_new
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Placement"
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|place_type
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Randomly"
argument_list|)
argument_list|,
name|PLACEMENT_TYPE_RANDOM
argument_list|,
operator|&
name|placement_radio
index|[
name|PLACEMENT_TYPE_RANDOM
index|]
argument_list|,
name|_
argument_list|(
literal|"Evenly distributed"
argument_list|)
argument_list|,
name|PLACEMENT_TYPE_EVEN_DIST
argument_list|,
operator|&
name|placement_radio
index|[
name|PLACEMENT_TYPE_EVEN_DIST
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|placement_radio
index|[
name|PLACEMENT_TYPE_RANDOM
index|]
argument_list|,
name|_
argument_list|(
literal|"Place strokes randomly around the image"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|placement_radio
index|[
name|PLACEMENT_TYPE_EVEN_DIST
index|]
argument_list|,
name|_
argument_list|(
literal|"The strokes are evenly distributed across the image"
argument_list|)
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
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|placement_radio
index|[
name|pcvals
operator|.
name|place_type
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|placement_center
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Centered"
argument_list|)
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|placement_center
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|tmpw
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
name|tmpw
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|tmpw
argument_list|,
name|_
argument_list|(
literal|"Focus the brush strokes around the center of the image"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|pcvals
operator|.
name|placement_center
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
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
literal|6
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
name|brush_density_adjust
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
literal|"Stroke _density:"
argument_list|)
argument_list|,
literal|100
argument_list|,
operator|-
literal|1
argument_list|,
name|pcvals
operator|.
name|brush_density
argument_list|,
literal|1.0
argument_list|,
literal|50.0
argument_list|,
literal|1.0
argument_list|,
literal|5.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"The relative density of the brush strokes"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|brush_density_adjust
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|brush_density
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page_menu
argument_list|(
name|notebook
argument_list|,
name|vbox
argument_list|,
name|label
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

