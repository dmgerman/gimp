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
file|"libgimpbase/gimplimits.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-appearance.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"grid-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GRID_COLOR_SIZE
define|#
directive|define
name|GRID_COLOR_SIZE
value|20
end_define

begin_comment
comment|/*  local functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|remove_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public function  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|grid_dialog_new (GimpDisplay * gdisp)
name|grid_dialog_new
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpGrid
modifier|*
name|grid_orig
decl_stmt|;
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|type
decl_stmt|;
name|GtkWidget
modifier|*
name|color_button
decl_stmt|;
name|GtkWidget
modifier|*
name|sizeentry
decl_stmt|;
name|GtkWidget
modifier|*
name|show_button
decl_stmt|;
name|GtkWidget
modifier|*
name|snap_button
decl_stmt|;
name|gboolean
name|show_grid
decl_stmt|;
name|gboolean
name|snap_to_grid
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|grid_orig
operator|=
name|gimp_image_get_grid
argument_list|(
name|GIMP_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|grid
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
comment|/* the dialog */
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Configure Grid"
argument_list|)
argument_list|,
literal|"configure_grid"
argument_list|,
name|GIMP_STOCK_GRID
argument_list|,
name|_
argument_list|(
literal|"Configure Image Grid"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/configure_grid.html"
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|reset_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_REMOVE
argument_list|,
name|remove_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|cancel_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|ok_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* the main vbox */
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
comment|/* misc options */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|show_button
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Show Grid"
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
name|show_button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|show_grid
operator|=
name|gimp_display_shell_get_show_grid
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|show_button
argument_list|)
argument_list|,
name|show_grid
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|show_button
argument_list|)
expr_stmt|;
name|snap_button
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Snap to Grid"
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
name|snap_button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|snap_to_grid
operator|=
name|gimp_display_shell_get_snap_to_grid
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|snap_button
argument_list|)
argument_list|,
name|snap_to_grid
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|snap_button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/* the appearence frame */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Appearence"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|2
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|type
operator|=
name|gimp_prop_enum_option_menu_new
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|"type"
argument_list|,
name|GIMP_GRID_TYPE_INTERSECTION
argument_list|,
name|GIMP_GRID_TYPE_SOLID
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
literal|"Line Style:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|type
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_button
operator|=
name|gimp_prop_color_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|"fgcolor"
argument_list|,
name|_
argument_list|(
literal|"Grid Foreground Color"
argument_list|)
argument_list|,
name|GRID_COLOR_SIZE
argument_list|,
name|GRID_COLOR_SIZE
argument_list|,
name|GIMP_COLOR_AREA_FLAT
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
literal|"Foreground Color:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|color_button
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_button
operator|=
name|gimp_prop_color_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|"bgcolor"
argument_list|,
name|_
argument_list|(
literal|"Grid Background Color"
argument_list|)
argument_list|,
name|GRID_COLOR_SIZE
argument_list|,
name|GRID_COLOR_SIZE
argument_list|,
name|GIMP_COLOR_AREA_FLAT
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
literal|2
argument_list|,
name|_
argument_list|(
literal|"Background Color:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|color_button
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/* the spacing frame */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Spacing"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|sizeentry
operator|=
name|gimp_prop_coordinates_new
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|"xspacing"
argument_list|,
literal|"yspacing"
argument_list|,
literal|"spacing-unit"
argument_list|,
literal|"%a"
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|1.0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Width"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Height"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Pixels"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|sizeentry
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
name|sizeentry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
comment|/* the offset frame */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Offset"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|sizeentry
operator|=
name|gimp_prop_coordinates_new
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|"xoffset"
argument_list|,
literal|"yoffset"
argument_list|,
literal|"offset-unit"
argument_list|,
literal|"%a"
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Width"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Height"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Pixels"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|sizeentry
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
name|sizeentry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
if|if
condition|(
name|grid_orig
condition|)
block|{
name|gimp_config_copy_properties
argument_list|(
name|G_OBJECT
argument_list|(
name|grid_orig
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_config_reset_properties
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|"spacing-unit"
argument_list|,
name|gimage
operator|->
name|unit
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|"offset-unit"
argument_list|,
name|gimage
operator|->
name|unit
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimage"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"grid"
argument_list|,
name|grid
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"show-button"
argument_list|,
name|show_button
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"snap-button"
argument_list|,
name|snap_button
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/*  local functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|reset_callback (GtkWidget * widget,GtkWidget * dialog)
name|reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpGrid
modifier|*
name|grid_orig
decl_stmt|;
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
name|GimpUnit
name|unit_orig
decl_stmt|;
name|GtkWidget
modifier|*
name|show_button
decl_stmt|;
name|GtkWidget
modifier|*
name|snap_button
decl_stmt|;
name|gboolean
name|show_grid
decl_stmt|;
name|gboolean
name|snap_to_grid
decl_stmt|;
name|gimage
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimage"
argument_list|)
expr_stmt|;
name|grid
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"grid"
argument_list|)
expr_stmt|;
name|shell
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"shell"
argument_list|)
expr_stmt|;
name|show_button
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"show-button"
argument_list|)
expr_stmt|;
name|snap_button
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"snap-button"
argument_list|)
expr_stmt|;
name|grid_orig
operator|=
name|gimp_image_get_grid
argument_list|(
name|GIMP_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|unit_orig
operator|=
name|gimp_image_get_unit
argument_list|(
name|GIMP_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|grid_orig
condition|)
block|{
name|gimp_config_copy_properties
argument_list|(
name|G_OBJECT
argument_list|(
name|grid_orig
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_reset_properties
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|"spacing-unit"
argument_list|,
name|unit_orig
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|"offset-unit"
argument_list|,
name|unit_orig
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|show_grid
operator|=
name|gimp_display_shell_get_show_grid
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|show_button
argument_list|)
argument_list|,
name|show_grid
argument_list|)
expr_stmt|;
name|snap_to_grid
operator|=
name|gimp_display_shell_get_snap_to_grid
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|snap_button
argument_list|)
argument_list|,
name|snap_to_grid
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|remove_callback (GtkWidget * widget,GtkWidget * dialog)
name|remove_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
name|gimage
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimage"
argument_list|)
expr_stmt|;
name|grid
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"grid"
argument_list|)
expr_stmt|;
name|gimp_image_set_grid
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cancel_callback (GtkWidget * widget,GtkWidget * dialog)
name|cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
name|grid
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"grid"
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ok_callback (GtkWidget * widget,GtkWidget * dialog)
name|ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
name|GimpGrid
modifier|*
name|grid_orig
decl_stmt|;
name|GtkWidget
modifier|*
name|show_button
decl_stmt|;
name|GtkWidget
modifier|*
name|snap_button
decl_stmt|;
name|gboolean
name|show_grid
decl_stmt|;
name|gboolean
name|snap_to_grid
decl_stmt|;
name|gimage
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimage"
argument_list|)
expr_stmt|;
name|grid
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"grid"
argument_list|)
expr_stmt|;
name|shell
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"shell"
argument_list|)
expr_stmt|;
name|show_button
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"show-button"
argument_list|)
expr_stmt|;
name|snap_button
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"snap-button"
argument_list|)
expr_stmt|;
name|grid_orig
operator|=
name|gimp_image_get_grid
argument_list|(
name|GIMP_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|grid_orig
operator|==
name|NULL
operator|||
name|gimp_config_diff
argument_list|(
name|G_OBJECT
argument_list|(
name|grid_orig
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|)
condition|)
name|gimp_image_set_grid
argument_list|(
name|GIMP_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|grid
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
name|show_grid
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|show_button
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_grid
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|show_grid
argument_list|)
expr_stmt|;
name|snap_to_grid
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|snap_button
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_snap_to_grid
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|snap_to_grid
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

