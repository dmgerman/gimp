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
file|<stdio.h>
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
file|"libgimpcolor/gimpcolor.h"
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
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdnd.h"
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
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"device-status-dialog.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|CELL_SIZE
define|#
directive|define
name|CELL_SIZE
value|20
end_define

begin_comment
DECL|macro|CELL_SIZE
comment|/* The size of the preview cells */
end_comment

begin_typedef
DECL|typedef|DeviceStatusDialog
typedef|typedef
name|struct
name|_DeviceStatusDialog
name|DeviceStatusDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_DeviceStatusDialog
struct|struct
name|_DeviceStatusDialog
block|{
DECL|member|num_devices
name|gint
name|num_devices
decl_stmt|;
DECL|member|current
name|GdkDevice
modifier|*
name|current
decl_stmt|;
DECL|member|devices
name|GdkDevice
modifier|*
modifier|*
name|devices
decl_stmt|;
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|table
name|GtkWidget
modifier|*
name|table
decl_stmt|;
DECL|member|frames
name|GtkWidget
modifier|*
modifier|*
name|frames
decl_stmt|;
DECL|member|tools
name|GtkWidget
modifier|*
modifier|*
name|tools
decl_stmt|;
DECL|member|foregrounds
name|GtkWidget
modifier|*
modifier|*
name|foregrounds
decl_stmt|;
DECL|member|backgrounds
name|GtkWidget
modifier|*
modifier|*
name|backgrounds
decl_stmt|;
DECL|member|brushes
name|GtkWidget
modifier|*
modifier|*
name|brushes
decl_stmt|;
DECL|member|patterns
name|GtkWidget
modifier|*
modifier|*
name|patterns
decl_stmt|;
DECL|member|gradients
name|GtkWidget
modifier|*
modifier|*
name|gradients
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local functions */
end_comment

begin_function_decl
specifier|static
name|void
name|device_status_destroy_callback
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|device_status_dialog_update
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|,
name|DeviceStatusDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|device_status_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|device_status_foreground_changed
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
specifier|static
name|void
name|device_status_background_changed
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
specifier|static
name|void
name|device_status_drop_brush
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|device_status_drop_pattern
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|device_status_drop_gradient
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  local data  */
end_comment

begin_decl_stmt
DECL|variable|deviceD
specifier|static
name|DeviceStatusDialog
modifier|*
name|deviceD
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
DECL|function|device_status_dialog_create (Gimp * gimp)
name|device_status_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
name|deviceD
condition|)
return|return
name|deviceD
operator|->
name|shell
return|;
name|deviceD
operator|=
name|g_new0
argument_list|(
name|DeviceStatusDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Device Status"
argument_list|)
argument_list|,
literal|"device_status"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/device_status.html"
argument_list|,
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_CLOSE
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
name|GTK_STOCK_SAVE
argument_list|,
name|gimp_devices_save
argument_list|,
name|NULL
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|num_devices
operator|=
name|g_list_length
argument_list|(
name|gdk_devices_list
argument_list|()
argument_list|)
expr_stmt|;
comment|/*  devices table  */
name|deviceD
operator|->
name|table
operator|=
name|gtk_table_new
argument_list|(
name|deviceD
operator|->
name|num_devices
argument_list|,
literal|7
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|deviceD
operator|->
name|table
argument_list|)
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|deviceD
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|deviceD
operator|->
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|deviceD
operator|->
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|deviceD
operator|->
name|table
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|devices
operator|=
name|g_new
argument_list|(
name|GdkDevice
operator|*
argument_list|,
name|deviceD
operator|->
name|num_devices
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|frames
operator|=
name|g_new
argument_list|(
name|GtkWidget
operator|*
argument_list|,
name|deviceD
operator|->
name|num_devices
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|tools
operator|=
name|g_new
argument_list|(
name|GtkWidget
operator|*
argument_list|,
name|deviceD
operator|->
name|num_devices
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|foregrounds
operator|=
name|g_new
argument_list|(
name|GtkWidget
operator|*
argument_list|,
name|deviceD
operator|->
name|num_devices
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|backgrounds
operator|=
name|g_new
argument_list|(
name|GtkWidget
operator|*
argument_list|,
name|deviceD
operator|->
name|num_devices
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|brushes
operator|=
name|g_new
argument_list|(
name|GtkWidget
operator|*
argument_list|,
name|deviceD
operator|->
name|num_devices
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|patterns
operator|=
name|g_new
argument_list|(
name|GtkWidget
operator|*
argument_list|,
name|deviceD
operator|->
name|num_devices
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|gradients
operator|=
name|g_new
argument_list|(
name|GtkWidget
operator|*
argument_list|,
name|deviceD
operator|->
name|num_devices
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gdk_devices_list
argument_list|()
operator|,
name|i
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|,
name|i
operator|++
control|)
block|{
name|device_info
operator|=
name|gimp_device_info_get_by_device
argument_list|(
name|GDK_DEVICE
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|device_info
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|device_status_dialog_update
argument_list|)
argument_list|,
name|deviceD
argument_list|)
expr_stmt|;
name|deviceD
operator|->
name|devices
index|[
name|i
index|]
operator|=
name|device_info
operator|->
name|device
expr_stmt|;
comment|/*  the device name  */
name|deviceD
operator|->
name|frames
index|[
name|i
index|]
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|deviceD
operator|->
name|frames
index|[
name|i
index|]
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|deviceD
operator|->
name|table
argument_list|)
argument_list|,
name|deviceD
operator|->
name|frames
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
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|device_info
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|gtk_misc_set_padding
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|deviceD
operator|->
name|frames
index|[
name|i
index|]
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/*  the tool  */
name|deviceD
operator|->
name|tools
index|[
name|i
index|]
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"tool_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|deviceD
operator|->
name|tools
index|[
name|i
index|]
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|deviceD
operator|->
name|tools
index|[
name|i
index|]
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|device_status_drop_tool
argument_list|,
name|device_info
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|deviceD
operator|->
name|table
argument_list|)
argument_list|,
name|deviceD
operator|->
name|tools
index|[
name|i
index|]
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/*  the foreground color  */
name|deviceD
operator|->
name|foregrounds
index|[
name|i
index|]
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|color
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|deviceD
operator|->
name|foregrounds
index|[
name|i
index|]
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|deviceD
operator|->
name|foregrounds
index|[
name|i
index|]
argument_list|,
literal|"color_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|device_status_foreground_changed
argument_list|)
argument_list|,
name|device_info
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|deviceD
operator|->
name|table
argument_list|)
argument_list|,
name|deviceD
operator|->
name|foregrounds
index|[
name|i
index|]
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/*  the background color  */
name|deviceD
operator|->
name|backgrounds
index|[
name|i
index|]
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|color
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|deviceD
operator|->
name|backgrounds
index|[
name|i
index|]
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|deviceD
operator|->
name|backgrounds
index|[
name|i
index|]
argument_list|,
literal|"color_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|device_status_background_changed
argument_list|)
argument_list|,
name|device_info
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|deviceD
operator|->
name|table
argument_list|)
argument_list|,
name|deviceD
operator|->
name|backgrounds
index|[
name|i
index|]
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
literal|0
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/*  the brush  */
name|deviceD
operator|->
name|brushes
index|[
name|i
index|]
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"brush_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|deviceD
operator|->
name|brushes
index|[
name|i
index|]
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|deviceD
operator|->
name|brushes
index|[
name|i
index|]
argument_list|,
name|GIMP_TYPE_BRUSH
argument_list|,
name|device_status_drop_brush
argument_list|,
name|device_info
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|deviceD
operator|->
name|table
argument_list|)
argument_list|,
name|deviceD
operator|->
name|brushes
index|[
name|i
index|]
argument_list|,
literal|4
argument_list|,
literal|5
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/*  the pattern  */
name|deviceD
operator|->
name|patterns
index|[
name|i
index|]
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"pattern_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|deviceD
operator|->
name|patterns
index|[
name|i
index|]
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|deviceD
operator|->
name|patterns
index|[
name|i
index|]
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
name|device_status_drop_pattern
argument_list|,
name|device_info
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|deviceD
operator|->
name|table
argument_list|)
argument_list|,
name|deviceD
operator|->
name|patterns
index|[
name|i
index|]
argument_list|,
literal|5
argument_list|,
literal|6
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/*  the gradient  */
name|deviceD
operator|->
name|gradients
index|[
name|i
index|]
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
name|CELL_SIZE
operator|*
literal|2
argument_list|,
name|CELL_SIZE
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"gradient_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|deviceD
operator|->
name|gradients
index|[
name|i
index|]
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|deviceD
operator|->
name|gradients
index|[
name|i
index|]
argument_list|,
name|GIMP_TYPE_GRADIENT
argument_list|,
name|device_status_drop_gradient
argument_list|,
name|device_info
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|deviceD
operator|->
name|table
argument_list|)
argument_list|,
name|deviceD
operator|->
name|gradients
index|[
name|i
index|]
argument_list|,
literal|6
argument_list|,
literal|7
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|device_status_dialog_update
argument_list|(
name|device_info
argument_list|,
name|deviceD
argument_list|)
expr_stmt|;
block|}
name|deviceD
operator|->
name|current
operator|=
name|NULL
expr_stmt|;
name|device_status_dialog_update_current
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|deviceD
operator|->
name|shell
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|device_status_destroy_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|deviceD
operator|->
name|shell
return|;
block|}
end_function

begin_function
name|void
DECL|function|device_status_dialog_update_current (Gimp * gimp)
name|device_status_dialog_update_current
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|deviceD
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|deviceD
operator|->
name|num_devices
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|deviceD
operator|->
name|devices
index|[
name|i
index|]
operator|==
name|deviceD
operator|->
name|current
condition|)
block|{
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|deviceD
operator|->
name|frames
index|[
name|i
index|]
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|deviceD
operator|->
name|devices
index|[
name|i
index|]
operator|==
name|gimp_devices_get_current
argument_list|(
name|gimp
argument_list|)
condition|)
block|{
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|deviceD
operator|->
name|frames
index|[
name|i
index|]
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
block|}
block|}
name|deviceD
operator|->
name|current
operator|=
name|gimp_devices_get_current
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|device_status_destroy_callback (void)
name|device_status_destroy_callback
parameter_list|(
name|void
parameter_list|)
block|{
name|g_free
argument_list|(
name|deviceD
operator|->
name|devices
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|deviceD
operator|->
name|frames
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|deviceD
operator|->
name|tools
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|deviceD
operator|->
name|foregrounds
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|deviceD
operator|->
name|backgrounds
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|deviceD
operator|->
name|brushes
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|deviceD
operator|->
name|patterns
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|deviceD
operator|->
name|gradients
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|deviceD
argument_list|)
expr_stmt|;
name|deviceD
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|device_status_dialog_update (GimpDeviceInfo * device_info,DeviceStatusDialog * dialog)
name|device_status_dialog_update
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|,
name|DeviceStatusDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|guchar
name|red
decl_stmt|,
name|green
decl_stmt|,
name|blue
decl_stmt|;
name|gchar
name|ttbuf
index|[
literal|64
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|device_info
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
name|dialog
operator|->
name|num_devices
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|dialog
operator|->
name|devices
index|[
name|i
index|]
operator|==
name|device_info
operator|->
name|device
condition|)
break|break;
block|}
name|g_return_if_fail
argument_list|(
name|i
operator|<
name|dialog
operator|->
name|num_devices
argument_list|)
expr_stmt|;
if|if
condition|(
name|device_info
operator|->
name|device
operator|->
name|mode
operator|==
name|GDK_MODE_DISABLED
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|frames
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|tools
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|foregrounds
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|backgrounds
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|brushes
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|patterns
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|dialog
operator|->
name|gradients
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|frames
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|tools
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
comment|/*  foreground color  */
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|dialog
operator|->
name|foregrounds
index|[
name|i
index|]
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|foregrounds
index|[
name|i
index|]
argument_list|)
expr_stmt|;
comment|/*  Set the tip to be the RGB value  */
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|red
argument_list|,
operator|&
name|green
argument_list|,
operator|&
name|blue
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|ttbuf
argument_list|,
sizeof|sizeof
argument_list|(
name|ttbuf
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Foreground: %d, %d, %d"
argument_list|)
argument_list|,
name|red
argument_list|,
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|dialog
operator|->
name|foregrounds
index|[
name|i
index|]
argument_list|,
name|GDK_ENTER_NOTIFY_MASK
operator||
name|GDK_LEAVE_NOTIFY_MASK
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|dialog
operator|->
name|foregrounds
index|[
name|i
index|]
argument_list|,
name|ttbuf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  background color  */
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|dialog
operator|->
name|backgrounds
index|[
name|i
index|]
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|backgrounds
index|[
name|i
index|]
argument_list|)
expr_stmt|;
comment|/*  Set the tip to be the RGB value  */
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|red
argument_list|,
operator|&
name|green
argument_list|,
operator|&
name|blue
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|ttbuf
argument_list|,
sizeof|sizeof
argument_list|(
name|ttbuf
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Background: %d, %d, %d"
argument_list|)
argument_list|,
name|red
argument_list|,
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|dialog
operator|->
name|backgrounds
index|[
name|i
index|]
argument_list|,
name|GDK_ENTER_NOTIFY_MASK
operator||
name|GDK_LEAVE_NOTIFY_MASK
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|dialog
operator|->
name|backgrounds
index|[
name|i
index|]
argument_list|,
name|ttbuf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|brushes
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|patterns
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|gradients
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|device_status_drop_tool (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|device_status_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|device_info
operator|=
operator|(
name|GimpDeviceInfo
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|device_info
operator|&&
name|device_info
operator|->
name|device
condition|)
block|{
name|gimp_context_set_tool
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
argument_list|,
name|GIMP_TOOL_INFO
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|device_status_foreground_changed (GtkWidget * widget,gpointer data)
name|device_status_foreground_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|device_info
operator|=
operator|(
name|GimpDeviceInfo
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|device_info
operator|&&
name|device_info
operator|->
name|device
condition|)
block|{
name|gimp_color_area_get_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_context_set_foreground
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|device_status_background_changed (GtkWidget * widget,gpointer data)
name|device_status_background_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|device_info
operator|=
operator|(
name|GimpDeviceInfo
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|device_info
operator|&&
name|device_info
operator|->
name|device
condition|)
block|{
name|gimp_color_area_get_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_context_set_background
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|device_status_drop_brush (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|device_status_drop_brush
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|device_info
operator|=
operator|(
name|GimpDeviceInfo
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|device_info
operator|&&
name|device_info
operator|->
name|device
condition|)
block|{
name|gimp_context_set_brush
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
argument_list|,
name|GIMP_BRUSH
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|device_status_drop_pattern (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|device_status_drop_pattern
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|device_info
operator|=
operator|(
name|GimpDeviceInfo
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|device_info
operator|&&
name|device_info
operator|->
name|device
condition|)
block|{
name|gimp_context_set_pattern
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
argument_list|,
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|device_status_drop_gradient (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|device_status_drop_gradient
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|device_info
operator|=
operator|(
name|GimpDeviceInfo
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|device_info
operator|&&
name|device_info
operator|->
name|device
condition|)
block|{
name|gimp_context_set_gradient
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
argument_list|,
name|GIMP_GRADIENT
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

