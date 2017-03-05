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
file|"widgets/gimpdial.h"
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
file|"gimpdisplayshell-rotate.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-rotate-dialog.h"
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon278fd0500108
block|{
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
DECL|member|rotate_adj
name|GtkAdjustment
modifier|*
name|rotate_adj
decl_stmt|;
DECL|member|old_angle
name|gdouble
name|old_angle
decl_stmt|;
DECL|typedef|RotateDialogData
block|}
name|RotateDialogData
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_rotate_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|RotateDialogData
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_rotate_dialog_free
parameter_list|(
name|RotateDialogData
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|rotate_adjustment_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|RotateDialogData
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|display_shell_rotated
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|RotateDialogData
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|deg_to_rad
parameter_list|(
name|GBinding
modifier|*
name|binding
parameter_list|,
specifier|const
name|GValue
modifier|*
name|from_value
parameter_list|,
name|GValue
modifier|*
name|to_value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|rad_to_deg
parameter_list|(
name|GBinding
modifier|*
name|binding
parameter_list|,
specifier|const
name|GValue
modifier|*
name|from_value
parameter_list|,
name|GValue
modifier|*
name|to_value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_display_shell_rotate_dialog:  * @shell: the #GimpDisplayShell  *  * Constructs and displays a dialog allowing the user to enter a  * custom display rotate.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_rotate_dialog (GimpDisplayShell * shell)
name|gimp_display_shell_rotate_dialog
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|RotateDialogData
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
name|spin
decl_stmt|;
name|GtkWidget
modifier|*
name|dial
decl_stmt|;
name|GtkWidget
modifier|*
name|label
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
name|rotate_dialog
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|rotate_dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return;
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
name|RotateDialogData
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
name|old_angle
operator|=
name|shell
operator|->
name|rotate_angle
expr_stmt|;
name|shell
operator|->
name|rotate_dialog
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
literal|"Rotate View"
argument_list|)
argument_list|,
literal|"display-rotate"
argument_list|,
name|GIMP_ICON_OBJECT_ROTATE_180
argument_list|,
name|_
argument_list|(
literal|"Select Rotation Angle"
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_VIEW_ROTATE_OTHER
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
name|shell
operator|->
name|rotate_dialog
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
name|rotate_dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|gimp_display_shell_rotate_dialog_free
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|rotate_dialog
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|shell
operator|->
name|rotate_dialog
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
name|rotate_dialog
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
name|rotate_dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|rotate_dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_rotate_dialog_response
argument_list|)
argument_list|,
name|data
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
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
name|shell
operator|->
name|rotate_dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Angle:"
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
name|data
operator|->
name|rotate_adj
operator|=
operator|(
name|GtkAdjustment
operator|*
operator|)
name|gtk_adjustment_new
argument_list|(
name|shell
operator|->
name|rotate_angle
argument_list|,
literal|0.0
argument_list|,
literal|360.0
argument_list|,
literal|1
argument_list|,
literal|15
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|spin
operator|=
name|gtk_spin_button_new
argument_list|(
name|data
operator|->
name|rotate_adj
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
name|spin
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_wrap
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spin
argument_list|)
argument_list|,
name|TRUE
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
name|_
argument_list|(
literal|"degrees"
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
name|dial
operator|=
name|gimp_dial_new
argument_list|()
expr_stmt|;
name|g_object_set
argument_list|(
name|dial
argument_list|,
literal|"size"
argument_list|,
literal|32
argument_list|,
literal|"background"
argument_list|,
name|GIMP_CIRCLE_BACKGROUND_PLAIN
argument_list|,
literal|"draw-beta"
argument_list|,
name|FALSE
argument_list|,
name|NULL
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
name|g_object_bind_property_full
argument_list|(
name|data
operator|->
name|rotate_adj
argument_list|,
literal|"value"
argument_list|,
name|dial
argument_list|,
literal|"alpha"
argument_list|,
name|G_BINDING_BIDIRECTIONAL
operator||
name|G_BINDING_SYNC_CREATE
argument_list|,
name|deg_to_rad
argument_list|,
name|rad_to_deg
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|rotate_adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|rotate_adjustment_changed
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
argument_list|,
literal|"rotated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|display_shell_rotated
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|rotate_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_rotate_dialog_response (GtkWidget * widget,gint response_id,RotateDialogData * dialog)
name|gimp_display_shell_rotate_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|RotateDialogData
modifier|*
name|dialog
parameter_list|)
block|{
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|RESPONSE_RESET
case|:
name|gtk_adjustment_set_value
argument_list|(
name|dialog
operator|->
name|rotate_adj
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_RESPONSE_CANCEL
case|:
name|gtk_adjustment_set_value
argument_list|(
name|dialog
operator|->
name|rotate_adj
argument_list|,
name|dialog
operator|->
name|old_angle
argument_list|)
expr_stmt|;
comment|/* fall thru */
default|default:
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
name|shell
operator|->
name|rotate_dialog
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_rotate_dialog_free (RotateDialogData * dialog)
name|gimp_display_shell_rotate_dialog_free
parameter_list|(
name|RotateDialogData
modifier|*
name|dialog
parameter_list|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|dialog
operator|->
name|shell
argument_list|,
name|display_shell_rotated
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|RotateDialogData
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_adjustment_changed (GtkAdjustment * adj,RotateDialogData * dialog)
name|rotate_adjustment_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|RotateDialogData
modifier|*
name|dialog
parameter_list|)
block|{
name|gdouble
name|angle
init|=
name|gtk_adjustment_get_value
argument_list|(
name|dialog
operator|->
name|rotate_adj
argument_list|)
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|dialog
operator|->
name|shell
argument_list|,
name|display_shell_rotated
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gimp_display_shell_rotate_to
argument_list|(
name|dialog
operator|->
name|shell
argument_list|,
name|angle
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|dialog
operator|->
name|shell
argument_list|,
name|display_shell_rotated
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|display_shell_rotated (GimpDisplayShell * shell,RotateDialogData * dialog)
name|display_shell_rotated
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|RotateDialogData
modifier|*
name|dialog
parameter_list|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|dialog
operator|->
name|rotate_adj
argument_list|,
name|rotate_adjustment_changed
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|dialog
operator|->
name|rotate_adj
argument_list|,
name|shell
operator|->
name|rotate_angle
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|dialog
operator|->
name|rotate_adj
argument_list|,
name|rotate_adjustment_changed
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|deg_to_rad (GBinding * binding,const GValue * from_value,GValue * to_value,gpointer user_data)
name|deg_to_rad
parameter_list|(
name|GBinding
modifier|*
name|binding
parameter_list|,
specifier|const
name|GValue
modifier|*
name|from_value
parameter_list|,
name|GValue
modifier|*
name|to_value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gdouble
name|value
init|=
name|g_value_get_double
argument_list|(
name|from_value
argument_list|)
decl_stmt|;
name|value
operator|=
literal|360.0
operator|-
name|value
expr_stmt|;
name|value
operator|*=
name|G_PI
operator|/
literal|180.0
expr_stmt|;
name|g_value_set_double
argument_list|(
name|to_value
argument_list|,
name|value
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|rad_to_deg (GBinding * binding,const GValue * from_value,GValue * to_value,gpointer user_data)
name|rad_to_deg
parameter_list|(
name|GBinding
modifier|*
name|binding
parameter_list|,
specifier|const
name|GValue
modifier|*
name|from_value
parameter_list|,
name|GValue
modifier|*
name|to_value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gdouble
name|value
init|=
name|g_value_get_double
argument_list|(
name|from_value
argument_list|)
decl_stmt|;
name|value
operator|*=
literal|180.0
operator|/
name|G_PI
expr_stmt|;
name|value
operator|=
literal|360.0
operator|-
name|value
expr_stmt|;
name|g_value_set_double
argument_list|(
name|to_value
argument_list|,
name|value
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

