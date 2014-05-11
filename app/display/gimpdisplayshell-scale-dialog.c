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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
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
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scale.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scale-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|SCALE_EPSILON
define|#
directive|define
name|SCALE_EPSILON
value|0.0001
end_define

begin_define
DECL|macro|SCALE_EQUALS (a,b)
define|#
directive|define
name|SCALE_EQUALS
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|(fabs ((a) - (b))< SCALE_EPSILON)
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b750b950108
block|{
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
DECL|member|model
name|GimpZoomModel
modifier|*
name|model
decl_stmt|;
DECL|member|scale_adj
name|GtkAdjustment
modifier|*
name|scale_adj
decl_stmt|;
DECL|member|num_adj
name|GtkAdjustment
modifier|*
name|num_adj
decl_stmt|;
DECL|member|denom_adj
name|GtkAdjustment
modifier|*
name|denom_adj
decl_stmt|;
DECL|typedef|ScaleDialogData
block|}
name|ScaleDialogData
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_scale_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ScaleDialogData
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_scale_dialog_free
parameter_list|(
name|ScaleDialogData
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|update_zoom_values
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|ScaleDialogData
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_display_shell_scale_dialog:  * @shell: the #GimpDisplayShell  *  * Constructs and displays a dialog allowing the user to enter a  * custom display scale.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scale_dialog (GimpDisplayShell * shell)
name|gimp_display_shell_scale_dialog
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|ScaleDialogData
modifier|*
name|data
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|toplevel
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
name|spin
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gint
name|num
decl_stmt|,
name|denom
decl_stmt|,
name|row
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|scale_dialog
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|scale_dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|SCALE_EQUALS
argument_list|(
name|shell
operator|->
name|other_scale
argument_list|,
literal|0.0
argument_list|)
condition|)
block|{
comment|/* other_scale not yet initialized */
name|shell
operator|->
name|other_scale
operator|=
name|gimp_zoom_model_get_factor
argument_list|(
name|shell
operator|->
name|zoom
argument_list|)
expr_stmt|;
block|}
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
name|data
operator|=
name|g_slice_new
argument_list|(
name|ScaleDialogData
argument_list|)
expr_stmt|;
name|data
operator|->
name|shell
operator|=
name|shell
expr_stmt|;
name|data
operator|->
name|model
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ZOOM_MODEL
argument_list|,
literal|"value"
argument_list|,
name|fabs
argument_list|(
name|shell
operator|->
name|other_scale
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|shell
operator|->
name|scale_dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_get_user_context
argument_list|(
name|shell
operator|->
name|display
operator|->
name|gimp
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Zoom Ratio"
argument_list|)
argument_list|,
literal|"display_scale"
argument_list|,
literal|"zoom-original"
argument_list|,
name|_
argument_list|(
literal|"Select Zoom Ratio"
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_VIEW_ZOOM_OTHER
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
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
name|shell
operator|->
name|scale_dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|scale_dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|gimp_display_shell_scale_dialog_free
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|scale_dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_object_unref
argument_list|,
name|data
operator|->
name|model
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|scale_dialog
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|shell
operator|->
name|scale_dialog
argument_list|)
expr_stmt|;
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|scale_dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|toplevel
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_destroy_with_parent
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|scale_dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|scale_dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_scale_dialog_response
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
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
literal|12
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
name|gtk_table_set_row_spacings
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
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|shell
operator|->
name|scale_dialog
argument_list|)
argument_list|)
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
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|row
operator|=
literal|0
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
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
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Zoom ratio:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|hbox
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_zoom_model_get_fraction
argument_list|(
name|data
operator|->
name|model
argument_list|,
operator|&
name|num
argument_list|,
operator|&
name|denom
argument_list|)
expr_stmt|;
name|spin
operator|=
name|gimp_spin_button_new
argument_list|(
operator|(
name|GtkObject
operator|*
operator|*
operator|)
operator|&
name|data
operator|->
name|num_adj
argument_list|,
name|num
argument_list|,
literal|1
argument_list|,
literal|256
argument_list|,
literal|1
argument_list|,
literal|8
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spin
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|":"
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
name|spin
operator|=
name|gimp_spin_button_new
argument_list|(
operator|(
name|GtkObject
operator|*
operator|*
operator|)
operator|&
name|data
operator|->
name|denom_adj
argument_list|,
name|denom
argument_list|,
literal|1
argument_list|,
literal|256
argument_list|,
literal|1
argument_list|,
literal|8
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spin
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
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
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Zoom:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|hbox
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|spin
operator|=
name|gimp_spin_button_new
argument_list|(
operator|(
name|GtkObject
operator|*
operator|*
operator|)
operator|&
name|data
operator|->
name|scale_adj
argument_list|,
name|fabs
argument_list|(
name|shell
operator|->
name|other_scale
argument_list|)
operator|*
literal|100
argument_list|,
literal|100.0
operator|/
literal|256.0
argument_list|,
literal|25600.0
argument_list|,
literal|10
argument_list|,
literal|50
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spin
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"%"
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
name|g_signal_connect
argument_list|(
name|data
operator|->
name|scale_adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|update_zoom_values
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|num_adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|update_zoom_values
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|denom_adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|update_zoom_values
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|scale_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_scale_dialog_response (GtkWidget * widget,gint response_id,ScaleDialogData * dialog)
name|gimp_display_shell_scale_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ScaleDialogData
modifier|*
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|gdouble
name|scale
decl_stmt|;
name|scale
operator|=
name|gtk_adjustment_get_value
argument_list|(
name|dialog
operator|->
name|scale_adj
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale
argument_list|(
name|dialog
operator|->
name|shell
argument_list|,
name|GIMP_ZOOM_TO
argument_list|,
name|scale
operator|/
literal|100.0
argument_list|,
name|GIMP_ZOOM_FOCUS_BEST_GUESS
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  need to emit "scaled" to get the menu updated  */
name|gimp_display_shell_scaled
argument_list|(
name|dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|->
name|shell
operator|->
name|other_scale
operator|=
operator|-
name|fabs
argument_list|(
name|dialog
operator|->
name|shell
operator|->
name|other_scale
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
name|shell
operator|->
name|scale_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_scale_dialog_free (ScaleDialogData * dialog)
name|gimp_display_shell_scale_dialog_free
parameter_list|(
name|ScaleDialogData
modifier|*
name|dialog
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|ScaleDialogData
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|update_zoom_values (GtkAdjustment * adj,ScaleDialogData * dialog)
name|update_zoom_values
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|ScaleDialogData
modifier|*
name|dialog
parameter_list|)
block|{
name|gint
name|num
decl_stmt|,
name|denom
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|dialog
operator|->
name|scale_adj
argument_list|,
name|update_zoom_values
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|dialog
operator|->
name|num_adj
argument_list|,
name|update_zoom_values
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|dialog
operator|->
name|denom_adj
argument_list|,
name|update_zoom_values
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|adj
operator|==
name|dialog
operator|->
name|scale_adj
condition|)
block|{
name|scale
operator|=
name|gtk_adjustment_get_value
argument_list|(
name|dialog
operator|->
name|scale_adj
argument_list|)
expr_stmt|;
name|gimp_zoom_model_zoom
argument_list|(
name|dialog
operator|->
name|model
argument_list|,
name|GIMP_ZOOM_TO
argument_list|,
name|scale
operator|/
literal|100.0
argument_list|)
expr_stmt|;
name|gimp_zoom_model_get_fraction
argument_list|(
name|dialog
operator|->
name|model
argument_list|,
operator|&
name|num
argument_list|,
operator|&
name|denom
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|dialog
operator|->
name|num_adj
argument_list|,
name|num
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|dialog
operator|->
name|denom_adj
argument_list|,
name|denom
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* fraction adjustments */
block|{
name|scale
operator|=
operator|(
name|gtk_adjustment_get_value
argument_list|(
name|dialog
operator|->
name|num_adj
argument_list|)
operator|/
name|gtk_adjustment_get_value
argument_list|(
name|dialog
operator|->
name|denom_adj
argument_list|)
operator|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|dialog
operator|->
name|scale_adj
argument_list|,
name|scale
operator|*
literal|100
argument_list|)
expr_stmt|;
block|}
name|g_signal_handlers_unblock_by_func
argument_list|(
name|dialog
operator|->
name|scale_adj
argument_list|,
name|update_zoom_values
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|dialog
operator|->
name|num_adj
argument_list|,
name|update_zoom_values
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|dialog
operator|->
name|denom_adj
argument_list|,
name|update_zoom_values
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

