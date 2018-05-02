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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"print-size-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|RESPONSE_RESET
define|#
directive|define
name|RESPONSE_RESET
value|1
end_define

begin_define
DECL|macro|SB_WIDTH
define|#
directive|define
name|SB_WIDTH
value|8
end_define

begin_typedef
DECL|typedef|PrintSizeDialog
typedef|typedef
name|struct
name|_PrintSizeDialog
name|PrintSizeDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_PrintSizeDialog
struct|struct
name|_PrintSizeDialog
block|{
DECL|member|image
name|GimpImage
modifier|*
name|image
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
DECL|member|xres
name|gdouble
name|xres
decl_stmt|;
DECL|member|yres
name|gdouble
name|yres
decl_stmt|;
DECL|member|callback
name|GimpResolutionCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|print_size_dialog_free
parameter_list|(
name|PrintSizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|PrintSizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_dialog_reset
parameter_list|(
name|PrintSizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_dialog_size_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PrintSizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_dialog_resolution_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PrintSizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_size_dialog_set_size
parameter_list|(
name|PrintSizeDialog
modifier|*
name|private
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
name|print_size_dialog_set_resolution
parameter_list|(
name|PrintSizeDialog
modifier|*
name|private
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|print_size_dialog_new (GimpImage * image,GimpContext * context,const gchar * title,const gchar * role,GtkWidget * parent,GimpHelpFunc help_func,const gchar * help_id,GimpResolutionCallback callback,gpointer user_data)
name|print_size_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpResolutionCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|PrintSizeDialog
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|width
decl_stmt|;
name|GtkWidget
modifier|*
name|height
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|chain
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|GList
modifier|*
name|focus_chain
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
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
name|callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_slice_new0
argument_list|(
name|PrintSizeDialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|private
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|private
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|private
operator|->
name|xres
argument_list|,
operator|&
name|private
operator|->
name|yres
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
argument_list|,
name|context
argument_list|,
name|title
argument_list|,
name|role
argument_list|,
name|GIMP_ICON_DOCUMENT_PRINT_RESOLUTION
argument_list|,
name|title
argument_list|,
name|parent
argument_list|,
name|help_func
argument_list|,
name|help_id
argument_list|,
name|_
argument_list|(
literal|"_Reset"
argument_list|)
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_OK"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|print_size_dialog_free
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|print_size_dialog_response
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Print Size"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
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
literal|4
argument_list|,
literal|3
argument_list|,
name|FALSE
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
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
literal|2
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
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  the print size entry  */
name|adj
operator|=
operator|(
name|GtkAdjustment
operator|*
operator|)
name|gtk_adjustment_new
argument_list|(
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
argument_list|)
expr_stmt|;
name|width
operator|=
name|gtk_spin_button_new
argument_list|(
name|adj
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|width
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|width
argument_list|)
argument_list|,
name|SB_WIDTH
argument_list|)
expr_stmt|;
name|adj
operator|=
operator|(
name|GtkAdjustment
operator|*
operator|)
name|gtk_adjustment_new
argument_list|(
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
argument_list|)
expr_stmt|;
name|height
operator|=
name|gtk_spin_button_new
argument_list|(
name|adj
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|height
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|height
argument_list|)
argument_list|,
name|SB_WIDTH
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gimp_size_entry_new
argument_list|(
literal|0
argument_list|,
name|gimp_get_default_unit
argument_list|()
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
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|)
expr_stmt|;
name|private
operator|->
name|size_entry
operator|=
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Width:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|width
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
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
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
name|label
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"H_eight:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|height
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
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
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
name|label
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|hbox
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
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
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|entry
argument_list|)
argument_list|,
name|height
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|height
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
name|width
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|entry
argument_list|)
argument_list|,
name|width
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|width
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
name|private
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
name|private
operator|->
name|yres
argument_list|,
name|FALSE
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
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
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
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
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
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
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
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  the resolution entry  */
name|adj
operator|=
operator|(
name|GtkAdjustment
operator|*
operator|)
name|gtk_adjustment_new
argument_list|(
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
argument_list|)
expr_stmt|;
name|width
operator|=
name|gtk_spin_button_new
argument_list|(
name|adj
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|width
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|width
argument_list|)
argument_list|,
name|SB_WIDTH
argument_list|)
expr_stmt|;
name|adj
operator|=
operator|(
name|GtkAdjustment
operator|*
operator|)
name|gtk_adjustment_new
argument_list|(
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
argument_list|)
expr_stmt|;
name|height
operator|=
name|gtk_spin_button_new
argument_list|(
name|adj
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|height
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|height
argument_list|)
argument_list|,
name|SB_WIDTH
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_X resolution:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|width
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
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
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
name|label
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Y resolution:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|height
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
literal|0
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
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
name|label
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|hbox
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|,
literal|4
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
literal|0
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
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
name|private
operator|->
name|resolution_entry
operator|=
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
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
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|entry
argument_list|)
argument_list|,
name|height
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|height
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
name|width
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|entry
argument_list|)
argument_list|,
name|width
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|width
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
name|private
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
name|private
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
if|if
condition|(
name|ABS
argument_list|(
name|private
operator|->
name|xres
operator|-
name|private
operator|->
name|yres
argument_list|)
operator|<
name|GIMP_MIN_RESOLUTION
condition|)
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
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|entry
argument_list|)
argument_list|,
name|chain
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|chain
argument_list|)
expr_stmt|;
name|private
operator|->
name|chain
operator|=
name|GIMP_CHAIN_BUTTON
argument_list|(
name|chain
argument_list|)
expr_stmt|;
name|focus_chain
operator|=
name|g_list_prepend
argument_list|(
name|focus_chain
argument_list|,
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
operator|->
name|unitmenu
argument_list|)
expr_stmt|;
name|focus_chain
operator|=
name|g_list_prepend
argument_list|(
name|focus_chain
argument_list|,
name|chain
argument_list|)
expr_stmt|;
name|focus_chain
operator|=
name|g_list_prepend
argument_list|(
name|focus_chain
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|focus_chain
operator|=
name|g_list_prepend
argument_list|(
name|focus_chain
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|gtk_container_set_focus_chain
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|entry
argument_list|)
argument_list|,
name|focus_chain
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|focus_chain
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|size_entry
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|print_size_dialog_size_changed
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|resolution_entry
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|print_size_dialog_resolution_changed
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|print_size_dialog_free (PrintSizeDialog * private)
name|print_size_dialog_free
parameter_list|(
name|PrintSizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|PrintSizeDialog
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_dialog_response (GtkWidget * dialog,gint response_id,PrintSizeDialog * private)
name|print_size_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|PrintSizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|GimpSizeEntry
modifier|*
name|entry
init|=
name|private
operator|->
name|resolution_entry
decl_stmt|;
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|RESPONSE_RESET
case|:
name|print_size_dialog_reset
argument_list|(
name|private
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
name|private
operator|->
name|callback
argument_list|(
name|dialog
argument_list|,
name|private
operator|->
name|image
argument_list|,
name|gimp_size_entry_get_refval
argument_list|(
name|entry
argument_list|,
literal|0
argument_list|)
argument_list|,
name|gimp_size_entry_get_refval
argument_list|(
name|entry
argument_list|,
literal|1
argument_list|)
argument_list|,
name|gimp_size_entry_get_unit
argument_list|(
name|entry
argument_list|)
argument_list|,
name|private
operator|->
name|user_data
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_dialog_reset (PrintSizeDialog * private)
name|print_size_dialog_reset
parameter_list|(
name|PrintSizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|gimp_size_entry_set_unit
argument_list|(
name|private
operator|->
name|resolution_entry
argument_list|,
name|gimp_get_default_unit
argument_list|()
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|private
operator|->
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|print_size_dialog_set_resolution
argument_list|(
name|private
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
DECL|function|print_size_dialog_size_changed (GtkWidget * widget,PrintSizeDialog * private)
name|print_size_dialog_size_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PrintSizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|private
operator|->
name|image
decl_stmt|;
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
name|scale
operator|=
name|gimp_unit_get_factor
argument_list|(
name|gimp_size_entry_get_unit
argument_list|(
name|private
operator|->
name|size_entry
argument_list|)
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_size_entry_get_value
argument_list|(
name|private
operator|->
name|size_entry
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_size_entry_get_value
argument_list|(
name|private
operator|->
name|size_entry
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|xres
operator|=
name|scale
operator|*
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|/
name|MAX
argument_list|(
literal|0.001
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|yres
operator|=
name|scale
operator|*
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|/
name|MAX
argument_list|(
literal|0.001
argument_list|,
name|height
argument_list|)
expr_stmt|;
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
name|print_size_dialog_set_resolution
argument_list|(
name|private
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|print_size_dialog_set_size
argument_list|(
name|private
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_dialog_resolution_changed (GtkWidget * widget,PrintSizeDialog * private)
name|print_size_dialog_resolution_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PrintSizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|GimpSizeEntry
modifier|*
name|entry
init|=
name|private
operator|->
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
name|print_size_dialog_set_resolution
argument_list|(
name|private
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
DECL|function|print_size_dialog_set_size (PrintSizeDialog * private,gdouble width,gdouble height)
name|print_size_dialog_set_size
parameter_list|(
name|PrintSizeDialog
modifier|*
name|private
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
name|private
operator|->
name|size_entry
argument_list|,
name|print_size_dialog_size_changed
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|private
operator|->
name|size_entry
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|private
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
name|private
operator|->
name|size_entry
argument_list|,
name|print_size_dialog_size_changed
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_size_dialog_set_resolution (PrintSizeDialog * private,gdouble xres,gdouble yres)
name|print_size_dialog_set_resolution
parameter_list|(
name|PrintSizeDialog
modifier|*
name|private
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
block|{
if|if
condition|(
name|private
operator|->
name|chain
operator|&&
name|gimp_chain_button_get_active
argument_list|(
name|private
operator|->
name|chain
argument_list|)
condition|)
block|{
if|if
condition|(
name|xres
operator|!=
name|private
operator|->
name|xres
condition|)
name|yres
operator|=
name|xres
expr_stmt|;
else|else
name|xres
operator|=
name|yres
expr_stmt|;
block|}
name|private
operator|->
name|xres
operator|=
name|xres
expr_stmt|;
name|private
operator|->
name|yres
operator|=
name|yres
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|private
operator|->
name|resolution_entry
argument_list|,
name|print_size_dialog_resolution_changed
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|private
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
name|private
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
name|private
operator|->
name|resolution_entry
argument_list|,
name|print_size_dialog_resolution_changed
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|private
operator|->
name|size_entry
argument_list|,
name|print_size_dialog_size_changed
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|private
operator|->
name|size_entry
argument_list|,
literal|0
argument_list|,
name|xres
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|private
operator|->
name|size_entry
argument_list|,
literal|1
argument_list|,
name|yres
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|private
operator|->
name|size_entry
argument_list|,
name|print_size_dialog_size_changed
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

