begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdeviceinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdevices.h"
end_include

begin_include
include|#
directive|include
file|"device-status-dialog.h"
end_include

begin_include
include|#
directive|include
file|"input-dialog.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes */
end_comment

begin_function_decl
specifier|static
name|void
name|input_dialog_able_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDevice
modifier|*
name|device
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|input_dialog
specifier|static
name|GtkWidget
modifier|*
name|input_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|input_dialog_create (Gimp * gimp)
name|input_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|input_dialog
condition|)
return|return
name|input_dialog
return|;
name|input_dialog
operator|=
name|gtk_input_dialog_new
argument_list|()
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|G_OBJECT
argument_list|(
name|GTK_INPUT_DIALOG
argument_list|(
name|input_dialog
argument_list|)
operator|->
name|save_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_devices_save
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|G_OBJECT
argument_list|(
name|GTK_INPUT_DIALOG
argument_list|(
name|input_dialog
argument_list|)
operator|->
name|close_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|input_dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|input_dialog
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|input_dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|input_dialog
argument_list|)
argument_list|,
literal|"enable_device"
argument_list|,
name|G_CALLBACK
argument_list|(
name|input_dialog_able_callback
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|input_dialog
argument_list|)
argument_list|,
literal|"disable_device"
argument_list|,
name|G_CALLBACK
argument_list|(
name|input_dialog_able_callback
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
comment|/*  Connect the "F1" help key  */
name|gimp_help_connect
argument_list|(
name|input_dialog
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/input_devices.html"
argument_list|)
expr_stmt|;
return|return
name|input_dialog
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|input_dialog_able_callback (GtkWidget * widget,GdkDevice * device,Gimp * gimp)
name|input_dialog_able_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDevice
modifier|*
name|device
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gimp_device_info_changed_by_device
argument_list|(
name|device
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

