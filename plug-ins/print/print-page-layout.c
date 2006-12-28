begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"print.h"
end_include

begin_include
include|#
directive|include
file|"print-page-layout.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon292d4f7e0108
block|{
DECL|member|data
name|PrintData
modifier|*
name|data
decl_stmt|;
DECL|member|size_entry
name|GimpSizeEntry
modifier|*
name|size_entry
decl_stmt|;
DECL|member|resolution_entry
name|GimpSizeEntry
modifier|*
name|resolution_entry
decl_stmt|;
DECL|member|chain
name|GimpChainButton
modifier|*
name|chain
decl_stmt|;
DECL|member|area_label
name|GtkWidget
modifier|*
name|area_label
decl_stmt|;
DECL|typedef|PrintSizeInfo
block|}
name|PrintSizeInfo
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|run_page_setup_dialog
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|print_size_frame
parameter_list|(
name|PrintData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_info_size_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_info_resolution_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_info_unit_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_info_chain_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_info_set_size
parameter_list|(
name|PrintSizeInfo
modifier|*
name|info
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_info_set_resolution
parameter_list|(
name|PrintSizeInfo
modifier|*
name|info
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_info_set_page_setup
parameter_list|(
name|PrintSizeInfo
modifier|*
name|info
parameter_list|,
name|GtkPageSetup
modifier|*
name|setup
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|info
specifier|static
name|PrintSizeInfo
name|info
decl_stmt|;
end_decl_stmt

begin_function
name|GtkWidget
modifier|*
DECL|function|print_page_layout_gui (PrintData * data)
name|print_page_layout_gui
parameter_list|(
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|main_vbox
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
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Adjust Page Size "
literal|"and Orientation"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|run_page_setup_dialog
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
comment|/* Commented out until the header becomes a little more configurable    * and we can provide a user interface to include/exclude information.    */
block|button = gtk_check_button_new_with_label ("Print image header");   gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button),                                 data->show_info_header);   gtk_box_pack_end (GTK_BOX (hbox), button, FALSE, FALSE, 0);   g_signal_connect (G_OBJECT (button), "toggled",                     G_CALLBACK (gimp_toggle_button_update),&data->show_info_header);   gtk_widget_show (button);
endif|#
directive|endif
comment|/* label for the printable area */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Printable area:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|info
operator|.
name|area_label
operator|=
name|label
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|info
operator|.
name|area_label
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
name|info
operator|.
name|area_label
argument_list|)
expr_stmt|;
comment|/* size entry area for the image's print size */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|print_size_frame
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
return|return
name|main_vbox
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run_page_setup_dialog (GtkWidget * widget,PrintData * data)
name|run_page_setup_dialog
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
name|GtkPrintOperation
modifier|*
name|operation
decl_stmt|;
name|GtkPrintSettings
modifier|*
name|settings
decl_stmt|;
name|GtkPageSetup
modifier|*
name|page_setup
decl_stmt|;
name|GtkWidget
modifier|*
name|toplevel
decl_stmt|;
name|operation
operator|=
name|data
operator|->
name|operation
expr_stmt|;
comment|/* find a transient parent if possible */
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_TOPLEVEL
argument_list|(
name|toplevel
argument_list|)
condition|)
name|toplevel
operator|=
name|NULL
expr_stmt|;
name|settings
operator|=
name|gtk_print_operation_get_print_settings
argument_list|(
name|operation
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|settings
condition|)
name|settings
operator|=
name|gtk_print_settings_new
argument_list|()
expr_stmt|;
name|page_setup
operator|=
name|gtk_print_operation_get_default_page_setup
argument_list|(
name|operation
argument_list|)
expr_stmt|;
name|page_setup
operator|=
name|gtk_print_run_page_setup_dialog
argument_list|(
name|GTK_WINDOW
argument_list|(
name|toplevel
argument_list|)
argument_list|,
name|page_setup
argument_list|,
name|settings
argument_list|)
expr_stmt|;
name|gtk_print_operation_set_default_page_setup
argument_list|(
name|operation
argument_list|,
name|page_setup
argument_list|)
expr_stmt|;
name|print_size_info_set_page_setup
argument_list|(
operator|&
name|info
argument_list|,
name|page_setup
argument_list|)
expr_stmt|;
block|}
end_function

begin_define
DECL|macro|SB_WIDTH
define|#
directive|define
name|SB_WIDTH
value|8
end_define

begin_comment
comment|/*  * the code below is copied from app/dialogs/print-size-dialog.c  * with minimal changes.  Bleeah!  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|print_size_frame (PrintData * data)
name|print_size_frame
parameter_list|(
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
name|GtkPageSetup
modifier|*
name|setup
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkWidget
modifier|*
name|height
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
name|chain
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkSizeGroup
modifier|*
name|label_group
decl_stmt|;
name|GtkSizeGroup
modifier|*
name|entry_group
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gdouble
name|image_width
decl_stmt|;
name|gdouble
name|image_height
decl_stmt|;
name|info
operator|.
name|data
operator|=
name|data
expr_stmt|;
name|image_width
operator|=
operator|(
name|gimp_image_width
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
operator|*
name|gimp_unit_get_factor
argument_list|(
name|data
operator|->
name|unit
argument_list|)
operator|/
name|data
operator|->
name|xres
operator|)
expr_stmt|;
name|image_height
operator|=
operator|(
name|gimp_image_height
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
operator|*
name|gimp_unit_get_factor
argument_list|(
name|data
operator|->
name|unit
argument_list|)
operator|/
name|data
operator|->
name|yres
operator|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Image Size"
argument_list|)
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|label_group
operator|=
name|gtk_size_group_new
argument_list|(
name|GTK_SIZE_GROUP_HORIZONTAL
argument_list|)
expr_stmt|;
name|entry_group
operator|=
name|gtk_size_group_new
argument_list|(
name|GTK_SIZE_GROUP_HORIZONTAL
argument_list|)
expr_stmt|;
comment|/*  the print size entry  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gimp_size_entry_new
argument_list|(
literal|1
argument_list|,
name|data
operator|->
name|unit
argument_list|,
literal|"%p"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|SB_WIDTH
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_NONE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|entry
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
name|entry
argument_list|)
expr_stmt|;
name|info
operator|.
name|size_entry
operator|=
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adj
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_size_entry_add_field
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_SPIN_BUTTON
argument_list|(
name|height
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
name|height
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|height
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|entry_group
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|entry_group
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Width:"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Height:"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|label_group
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|label_group
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|data
operator|->
name|xres
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|data
operator|->
name|yres
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|setup
operator|=
name|gtk_print_operation_get_default_page_setup
argument_list|(
name|data
operator|->
name|operation
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_value
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|image_width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_value
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|image_height
argument_list|)
expr_stmt|;
comment|/*  the resolution entry  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gimp_size_entry_new
argument_list|(
literal|1
argument_list|,
name|data
operator|->
name|unit
argument_list|,
name|_
argument_list|(
literal|"pixels/%a"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|SB_WIDTH
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_RESOLUTION
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|entry
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
name|entry
argument_list|)
expr_stmt|;
name|info
operator|.
name|resolution_entry
operator|=
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adj
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_size_entry_add_field
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_SPIN_BUTTON
argument_list|(
name|height
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
name|height
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|height
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|entry_group
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_X resolution:"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Y resolution:"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|label_group
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|GIMP_MIN_RESOLUTION
argument_list|,
name|GIMP_MAX_RESOLUTION
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|GIMP_MIN_RESOLUTION
argument_list|,
name|GIMP_MAX_RESOLUTION
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|data
operator|->
name|xres
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|data
operator|->
name|yres
argument_list|)
expr_stmt|;
name|chain
operator|=
name|gimp_chain_button_new
argument_list|(
name|GIMP_CHAIN_RIGHT
argument_list|)
expr_stmt|;
name|gimp_chain_button_set_active
argument_list|(
name|GIMP_CHAIN_BUTTON
argument_list|(
name|chain
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
name|chain
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|chain
argument_list|)
expr_stmt|;
name|info
operator|.
name|chain
operator|=
name|GIMP_CHAIN_BUTTON
argument_list|(
name|chain
argument_list|)
expr_stmt|;
name|print_size_info_set_page_setup
argument_list|(
operator|&
name|info
argument_list|,
name|setup
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|info
operator|.
name|size_entry
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|print_size_info_size_changed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|info
operator|.
name|resolution_entry
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|print_size_info_resolution_changed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|info
operator|.
name|size_entry
argument_list|,
literal|"unit-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|print_size_info_unit_changed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|info
operator|.
name|chain
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|print_size_info_chain_toggled
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|frame
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_info_size_changed (GtkWidget * widget)
name|print_size_info_size_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gdouble
name|width
decl_stmt|;
name|gdouble
name|height
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|PrintData
modifier|*
name|data
init|=
name|info
operator|.
name|data
decl_stmt|;
name|gint
name|image_width
init|=
name|gimp_image_width
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
decl_stmt|;
name|gint
name|image_height
init|=
name|gimp_image_height
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
decl_stmt|;
name|scale
operator|=
name|gimp_unit_get_factor
argument_list|(
name|gimp_size_entry_get_unit
argument_list|(
name|info
operator|.
name|size_entry
argument_list|)
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_size_entry_get_value
argument_list|(
name|info
operator|.
name|size_entry
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_size_entry_get_value
argument_list|(
name|info
operator|.
name|size_entry
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|xres
operator|=
name|scale
operator|*
name|image_width
operator|/
name|MAX
argument_list|(
literal|0.0001
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|yres
operator|=
name|scale
operator|*
name|image_height
operator|/
name|MAX
argument_list|(
literal|0.0001
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|print_size_info_set_resolution
argument_list|(
operator|&
name|info
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_info_resolution_changed (GtkWidget * widget)
name|print_size_info_resolution_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpSizeEntry
modifier|*
name|entry
init|=
name|info
operator|.
name|resolution_entry
decl_stmt|;
name|gdouble
name|xres
init|=
name|gimp_size_entry_get_refval
argument_list|(
name|entry
argument_list|,
literal|0
argument_list|)
decl_stmt|;
name|gdouble
name|yres
init|=
name|gimp_size_entry_get_refval
argument_list|(
name|entry
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|print_size_info_set_resolution
argument_list|(
operator|&
name|info
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_info_unit_changed (GtkWidget * widget)
name|print_size_info_unit_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|PrintData
modifier|*
name|data
init|=
name|info
operator|.
name|data
decl_stmt|;
name|GimpSizeEntry
modifier|*
name|entry
init|=
name|info
operator|.
name|size_entry
decl_stmt|;
name|gdouble
name|factor
init|=
name|gimp_unit_get_factor
argument_list|(
name|data
operator|->
name|unit
argument_list|)
decl_stmt|;
name|gdouble
name|w
decl_stmt|,
name|h
decl_stmt|;
name|data
operator|->
name|unit
operator|=
name|gimp_size_entry_get_unit
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|data
operator|->
name|unit
argument_list|)
operator|/
name|factor
expr_stmt|;
name|w
operator|=
name|gimp_size_entry_get_value
argument_list|(
name|entry
argument_list|,
literal|0
argument_list|)
operator|*
name|factor
expr_stmt|;
name|h
operator|=
name|gimp_size_entry_get_value
argument_list|(
name|entry
argument_list|,
literal|1
argument_list|)
operator|*
name|factor
expr_stmt|;
name|print_size_info_set_page_setup
argument_list|(
operator|&
name|info
argument_list|,
name|gtk_print_operation_get_default_page_setup
argument_list|(
name|data
operator|->
name|operation
argument_list|)
argument_list|)
expr_stmt|;
name|print_size_info_set_size
argument_list|(
operator|&
name|info
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_info_chain_toggled (GtkWidget * widget)
name|print_size_info_chain_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|PrintData
modifier|*
name|data
init|=
name|info
operator|.
name|data
decl_stmt|;
name|print_size_info_set_page_setup
argument_list|(
operator|&
name|info
argument_list|,
name|gtk_print_operation_get_default_page_setup
argument_list|(
name|data
operator|->
name|operation
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_info_set_size (PrintSizeInfo * info,gdouble width,gdouble height)
name|print_size_info_set_size
parameter_list|(
name|PrintSizeInfo
modifier|*
name|info
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|info
operator|->
name|size_entry
argument_list|,
name|print_size_info_size_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_value
argument_list|(
name|info
operator|->
name|size_entry
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_value
argument_list|(
name|info
operator|->
name|size_entry
argument_list|,
literal|1
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|info
operator|->
name|size_entry
argument_list|,
name|print_size_info_size_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_info_set_resolution (PrintSizeInfo * info,gdouble xres,gdouble yres)
name|print_size_info_set_resolution
parameter_list|(
name|PrintSizeInfo
modifier|*
name|info
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
block|{
name|PrintData
modifier|*
name|data
init|=
name|info
operator|->
name|data
decl_stmt|;
name|xres
operator|=
name|CLAMP
argument_list|(
name|xres
argument_list|,
name|GIMP_MIN_RESOLUTION
argument_list|,
name|GIMP_MAX_RESOLUTION
argument_list|)
expr_stmt|;
name|yres
operator|=
name|CLAMP
argument_list|(
name|yres
argument_list|,
name|GIMP_MIN_RESOLUTION
argument_list|,
name|GIMP_MAX_RESOLUTION
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|chain
operator|&&
name|gimp_chain_button_get_active
argument_list|(
name|info
operator|->
name|chain
argument_list|)
condition|)
block|{
if|if
condition|(
name|xres
operator|!=
name|data
operator|->
name|xres
condition|)
block|{
name|yres
operator|=
name|xres
expr_stmt|;
block|}
else|else
block|{
name|xres
operator|=
name|yres
expr_stmt|;
block|}
block|}
name|data
operator|->
name|xres
operator|=
name|xres
expr_stmt|;
name|data
operator|->
name|yres
operator|=
name|yres
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|info
operator|->
name|resolution_entry
argument_list|,
name|print_size_info_resolution_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|info
operator|->
name|resolution_entry
argument_list|,
literal|0
argument_list|,
name|xres
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|info
operator|->
name|resolution_entry
argument_list|,
literal|1
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|info
operator|->
name|resolution_entry
argument_list|,
name|print_size_info_resolution_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|info
operator|->
name|size_entry
argument_list|,
name|print_size_info_size_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_value
argument_list|(
name|info
operator|->
name|size_entry
argument_list|,
literal|0
argument_list|,
name|gimp_image_width
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
operator|*
name|gimp_unit_get_factor
argument_list|(
name|data
operator|->
name|unit
argument_list|)
operator|/
name|xres
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_value
argument_list|(
name|info
operator|->
name|size_entry
argument_list|,
literal|1
argument_list|,
name|gimp_image_height
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
operator|*
name|gimp_unit_get_factor
argument_list|(
name|data
operator|->
name|unit
argument_list|)
operator|/
name|yres
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|info
operator|->
name|size_entry
argument_list|,
name|print_size_info_size_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_info_set_page_setup (PrintSizeInfo * info,GtkPageSetup * setup)
name|print_size_info_set_page_setup
parameter_list|(
name|PrintSizeInfo
modifier|*
name|info
parameter_list|,
name|GtkPageSetup
modifier|*
name|setup
parameter_list|)
block|{
name|PrintData
modifier|*
name|data
init|=
name|info
operator|->
name|data
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|gint
name|image_width
init|=
name|gimp_image_width
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
decl_stmt|;
name|gint
name|image_height
init|=
name|gimp_image_height
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
decl_stmt|;
name|gdouble
name|page_width
decl_stmt|;
name|gdouble
name|page_height
decl_stmt|;
name|gdouble
name|x
decl_stmt|;
name|gdouble
name|y
decl_stmt|;
name|page_width
operator|=
operator|(
name|gtk_page_setup_get_page_width
argument_list|(
name|setup
argument_list|,
name|GTK_UNIT_INCH
argument_list|)
operator|*
name|gimp_unit_get_factor
argument_list|(
name|data
operator|->
name|unit
argument_list|)
operator|)
expr_stmt|;
name|page_height
operator|=
operator|(
name|gtk_page_setup_get_page_height
argument_list|(
name|setup
argument_list|,
name|GTK_UNIT_INCH
argument_list|)
operator|*
name|gimp_unit_get_factor
argument_list|(
name|data
operator|->
name|unit
argument_list|)
operator|)
expr_stmt|;
name|text
operator|=
name|g_strdup_printf
argument_list|(
literal|"%g x %g %s"
argument_list|,
name|page_width
argument_list|,
name|page_height
argument_list|,
name|gimp_unit_get_plural
argument_list|(
name|data
operator|->
name|unit
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|info
operator|->
name|area_label
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|x
operator|=
name|page_width
expr_stmt|;
name|y
operator|=
name|page_height
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|chain
operator|&&
name|gimp_chain_button_get_active
argument_list|(
name|info
operator|->
name|chain
argument_list|)
condition|)
block|{
name|gdouble
name|ratio
init|=
operator|(
name|gdouble
operator|)
name|image_width
operator|/
operator|(
name|gdouble
operator|)
name|image_height
decl_stmt|;
if|if
condition|(
name|ratio
operator|<
literal|1.0
condition|)
name|x
operator|=
name|y
operator|*
name|ratio
expr_stmt|;
else|else
name|y
operator|=
name|x
operator|/
name|ratio
expr_stmt|;
block|}
name|gimp_size_entry_set_value_boundaries
argument_list|(
name|info
operator|->
name|size_entry
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_value_boundaries
argument_list|(
name|info
operator|->
name|size_entry
argument_list|,
literal|1
argument_list|,
literal|0.0
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|x
operator|=
name|image_width
operator|/
name|page_width
expr_stmt|;
name|y
operator|=
name|image_height
operator|/
name|page_height
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|chain
operator|&&
name|gimp_chain_button_get_active
argument_list|(
name|info
operator|->
name|chain
argument_list|)
condition|)
block|{
name|gdouble
name|max
init|=
name|MAX
argument_list|(
name|x
argument_list|,
name|y
argument_list|)
decl_stmt|;
name|x
operator|=
name|y
operator|=
name|max
expr_stmt|;
block|}
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|info
operator|->
name|resolution_entry
argument_list|,
literal|0
argument_list|,
name|x
argument_list|,
name|GIMP_MAX_RESOLUTION
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|info
operator|->
name|resolution_entry
argument_list|,
literal|1
argument_list|,
name|y
argument_list|,
name|GIMP_MAX_RESOLUTION
argument_list|)
expr_stmt|;
comment|/* FIXME: is this still needed at all? */
name|data
operator|->
name|orientation
operator|=
name|gtk_page_setup_get_orientation
argument_list|(
name|setup
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

