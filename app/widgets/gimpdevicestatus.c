begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpdevicestatus.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
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
file|"core/gimplist.h"
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
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdeviceinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdevices.h"
end_include

begin_include
include|#
directive|include
file|"gimpdevicestatus.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
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
comment|/* The size of the view cells */
end_comment

begin_enum
enum|enum
DECL|enum|__anon2afc9eee0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpDeviceStatusEntry
struct|struct
name|_GimpDeviceStatusEntry
block|{
DECL|member|device_info
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
DECL|member|table
name|GtkWidget
modifier|*
name|table
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
decl_stmt|;
DECL|member|arrow
name|GtkWidget
modifier|*
name|arrow
decl_stmt|;
DECL|member|tool
name|GtkWidget
modifier|*
name|tool
decl_stmt|;
DECL|member|foreground
name|GtkWidget
modifier|*
name|foreground
decl_stmt|;
DECL|member|background
name|GtkWidget
modifier|*
name|background
decl_stmt|;
DECL|member|brush
name|GtkWidget
modifier|*
name|brush
decl_stmt|;
DECL|member|pattern
name|GtkWidget
modifier|*
name|pattern
decl_stmt|;
DECL|member|gradient
name|GtkWidget
modifier|*
name|gradient
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_device_status_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_status_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_status_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_status_device_add
parameter_list|(
name|GimpContainer
modifier|*
name|devices
parameter_list|,
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|,
name|GimpDeviceStatus
modifier|*
name|status
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_status_device_remove
parameter_list|(
name|GimpContainer
modifier|*
name|devices
parameter_list|,
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|,
name|GimpDeviceStatus
modifier|*
name|status
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_status_update_entry
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|,
name|GimpDeviceStatusEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_status_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpDeviceStatus
modifier|*
name|status
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_status_view_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDeviceStatus,gimp_device_status,GIMP_TYPE_EDITOR)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDeviceStatus
argument_list|,
argument|gimp_device_status
argument_list|,
argument|GIMP_TYPE_EDITOR
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_device_status_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_device_status_class_init
parameter_list|(
name|GimpDeviceStatusClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkObjectClass
modifier|*
name|gtk_object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_device_status_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_device_status_set_property
expr_stmt|;
name|gtk_object_class
operator|->
name|destroy
operator|=
name|gimp_device_status_destroy
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GIMP
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GIMP
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_status_init (GimpDeviceStatus * status)
name|gimp_device_status_init
parameter_list|(
name|GimpDeviceStatus
modifier|*
name|status
parameter_list|)
block|{
name|status
operator|->
name|gimp
operator|=
name|NULL
expr_stmt|;
name|status
operator|->
name|current_device
operator|=
name|NULL
expr_stmt|;
name|status
operator|->
name|vbox
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
name|status
operator|->
name|vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|status
argument_list|)
argument_list|,
name|status
operator|->
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|status
operator|->
name|vbox
argument_list|)
expr_stmt|;
name|status
operator|->
name|save_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|status
argument_list|)
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
name|_
argument_list|(
literal|"Save device status"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_status_save_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|status
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_device_status_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_device_status_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpDeviceStatus
modifier|*
name|status
decl_stmt|;
name|GimpContainer
modifier|*
name|devices
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_DEVICE_STATUS
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|status
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|devices
operator|=
name|gimp_devices_get_list
argument_list|(
name|status
operator|->
name|gimp
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|devices
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|gimp_device_status_device_add
argument_list|(
name|devices
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|status
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|devices
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_status_device_add
argument_list|)
argument_list|,
name|status
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|devices
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_status_device_remove
argument_list|)
argument_list|,
name|status
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_device_status_update
argument_list|(
name|status
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_status_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_device_status_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpDeviceStatus
modifier|*
name|status
init|=
name|GIMP_DEVICE_STATUS
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_GIMP
case|:
name|status
operator|->
name|gimp
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_status_destroy (GtkObject * object)
name|gimp_device_status_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDeviceStatus
modifier|*
name|status
init|=
name|GIMP_DEVICE_STATUS
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|status
operator|->
name|devices
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|status
operator|->
name|devices
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GimpDeviceStatusEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|entry
operator|->
name|device_info
argument_list|,
name|gimp_device_status_update_entry
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpDeviceStatusEntry
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|status
operator|->
name|devices
argument_list|)
expr_stmt|;
name|status
operator|->
name|devices
operator|=
name|NULL
expr_stmt|;
block|}
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_status_device_add (GimpContainer * devices,GimpDeviceInfo * device_info,GimpDeviceStatus * status)
name|gimp_device_status_device_add
parameter_list|(
name|GimpContainer
modifier|*
name|devices
parameter_list|,
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|,
name|GimpDeviceStatus
modifier|*
name|status
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
decl_stmt|;
name|GimpDeviceStatusEntry
modifier|*
name|entry
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GClosure
modifier|*
name|closure
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/*  only list present devices  */
if|if
condition|(
operator|!
name|device_info
operator|->
name|device
condition|)
return|return;
name|entry
operator|=
name|g_slice_new0
argument_list|(
name|GimpDeviceStatusEntry
argument_list|)
expr_stmt|;
name|status
operator|->
name|devices
operator|=
name|g_list_prepend
argument_list|(
name|status
operator|->
name|devices
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|entry
operator|->
name|device_info
operator|=
name|device_info
expr_stmt|;
name|closure
operator|=
name|g_cclosure_new
argument_list|(
name|G_CALLBACK
argument_list|(
name|gimp_device_status_update_entry
argument_list|)
argument_list|,
name|entry
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_watch_closure
argument_list|(
name|G_OBJECT
argument_list|(
name|status
argument_list|)
argument_list|,
name|closure
argument_list|)
expr_stmt|;
name|g_signal_connect_closure
argument_list|(
name|device_info
argument_list|,
literal|"changed"
argument_list|,
name|closure
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|entry
operator|->
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|7
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
operator|->
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
name|status
operator|->
name|vbox
argument_list|)
argument_list|,
name|entry
operator|->
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
name|entry
operator|->
name|table
argument_list|)
expr_stmt|;
comment|/*  the device name  */
if|if
condition|(
name|device_info
operator|->
name|display
operator|==
name|gdk_display_get_default
argument_list|()
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|device_info
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s (%s)"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|device_info
argument_list|)
argument_list|,
name|gdk_display_get_name
argument_list|(
name|device_info
operator|->
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|entry
operator|->
name|label
operator|=
name|gtk_label_new
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|entry
operator|->
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_WEIGHT
argument_list|,
name|PANGO_WEIGHT_BOLD
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|entry
operator|->
name|label
argument_list|,
operator|-
literal|1
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|entry
operator|->
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
operator|->
name|table
argument_list|)
argument_list|,
name|entry
operator|->
name|label
argument_list|,
literal|1
argument_list|,
literal|7
argument_list|,
literal|0
argument_list|,
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
name|entry
operator|->
name|label
argument_list|)
expr_stmt|;
comment|/*  the arrow  */
name|entry
operator|->
name|arrow
operator|=
name|gtk_arrow_new
argument_list|(
name|GTK_ARROW_RIGHT
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|entry
operator|->
name|arrow
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
operator|->
name|table
argument_list|)
argument_list|,
name|entry
operator|->
name|arrow
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
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
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|hbox
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
operator|->
name|table
argument_list|)
argument_list|,
name|hbox
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
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
name|hbox
argument_list|)
expr_stmt|;
comment|/*  the tool  */
name|entry
operator|->
name|tool
operator|=
name|gimp_prop_view_new
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"tool"
argument_list|,
name|context
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|GIMP_VIEW
argument_list|(
name|entry
operator|->
name|tool
argument_list|)
operator|->
name|clickable
operator|=
name|TRUE
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
operator|->
name|table
argument_list|)
argument_list|,
name|entry
operator|->
name|tool
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
operator|->
name|tool
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
operator|->
name|tool
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_status_view_clicked
argument_list|)
argument_list|,
literal|"gimp-tool-list|gimp-tool-grid"
argument_list|)
expr_stmt|;
comment|/*  the foreground color  */
name|entry
operator|->
name|foreground
operator|=
name|gimp_prop_color_area_new
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"foreground"
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|entry
operator|->
name|foreground
argument_list|,
name|GDK_ENTER_NOTIFY_MASK
operator||
name|GDK_LEAVE_NOTIFY_MASK
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
operator|->
name|table
argument_list|)
argument_list|,
name|entry
operator|->
name|foreground
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
operator|->
name|foreground
argument_list|)
expr_stmt|;
comment|/*  the background color  */
name|entry
operator|->
name|background
operator|=
name|gimp_prop_color_area_new
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"background"
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|entry
operator|->
name|background
argument_list|,
name|GDK_ENTER_NOTIFY_MASK
operator||
name|GDK_LEAVE_NOTIFY_MASK
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
operator|->
name|table
argument_list|)
argument_list|,
name|entry
operator|->
name|background
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
operator|->
name|background
argument_list|)
expr_stmt|;
comment|/*  the brush  */
name|entry
operator|->
name|brush
operator|=
name|gimp_prop_view_new
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"brush"
argument_list|,
name|context
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|GIMP_VIEW
argument_list|(
name|entry
operator|->
name|brush
argument_list|)
operator|->
name|clickable
operator|=
name|TRUE
expr_stmt|;
name|GIMP_VIEW
argument_list|(
name|entry
operator|->
name|brush
argument_list|)
operator|->
name|show_popup
operator|=
name|TRUE
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
operator|->
name|table
argument_list|)
argument_list|,
name|entry
operator|->
name|brush
argument_list|,
literal|4
argument_list|,
literal|5
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
operator|->
name|brush
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
operator|->
name|brush
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_status_view_clicked
argument_list|)
argument_list|,
literal|"gimp-brush-grid|gimp-brush-list"
argument_list|)
expr_stmt|;
comment|/*  the pattern  */
name|entry
operator|->
name|pattern
operator|=
name|gimp_prop_view_new
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"pattern"
argument_list|,
name|context
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|GIMP_VIEW
argument_list|(
name|entry
operator|->
name|pattern
argument_list|)
operator|->
name|clickable
operator|=
name|TRUE
expr_stmt|;
name|GIMP_VIEW
argument_list|(
name|entry
operator|->
name|pattern
argument_list|)
operator|->
name|show_popup
operator|=
name|TRUE
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
operator|->
name|table
argument_list|)
argument_list|,
name|entry
operator|->
name|pattern
argument_list|,
literal|5
argument_list|,
literal|6
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
operator|->
name|pattern
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
operator|->
name|pattern
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_status_view_clicked
argument_list|)
argument_list|,
literal|"gimp-pattern-grid|gimp-pattern-list"
argument_list|)
expr_stmt|;
comment|/*  the gradient  */
name|entry
operator|->
name|gradient
operator|=
name|gimp_prop_view_new
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"gradient"
argument_list|,
name|context
argument_list|,
literal|2
operator|*
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|GIMP_VIEW
argument_list|(
name|entry
operator|->
name|gradient
argument_list|)
operator|->
name|clickable
operator|=
name|TRUE
expr_stmt|;
name|GIMP_VIEW
argument_list|(
name|entry
operator|->
name|gradient
argument_list|)
operator|->
name|show_popup
operator|=
name|TRUE
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
operator|->
name|table
argument_list|)
argument_list|,
name|entry
operator|->
name|gradient
argument_list|,
literal|6
argument_list|,
literal|7
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
operator|->
name|gradient
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
operator|->
name|gradient
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_status_view_clicked
argument_list|)
argument_list|,
literal|"gimp-gradient-list|gimp-gradient-grid"
argument_list|)
expr_stmt|;
name|gimp_device_status_update_entry
argument_list|(
name|device_info
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_status_device_remove (GimpContainer * devices,GimpDeviceInfo * device_info,GimpDeviceStatus * status)
name|gimp_device_status_device_remove
parameter_list|(
name|GimpContainer
modifier|*
name|devices
parameter_list|,
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|,
name|GimpDeviceStatus
modifier|*
name|status
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|status
operator|->
name|devices
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GimpDeviceStatusEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|entry
operator|->
name|device_info
operator|==
name|device_info
condition|)
block|{
name|status
operator|->
name|devices
operator|=
name|g_list_remove
argument_list|(
name|status
operator|->
name|devices
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|entry
operator|->
name|device_info
argument_list|,
name|gimp_device_status_update_entry
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpDeviceStatusEntry
argument_list|,
name|entry
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_device_status_new (Gimp * gimp)
name|gimp_device_status_new
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
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_DEVICE_STATUS
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_device_status_update (GimpDeviceStatus * status)
name|gimp_device_status_update
parameter_list|(
name|GimpDeviceStatus
modifier|*
name|status
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DEVICE_STATUS
argument_list|(
name|status
argument_list|)
argument_list|)
expr_stmt|;
name|status
operator|->
name|current_device
operator|=
name|gimp_devices_get_current
argument_list|(
name|status
operator|->
name|gimp
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|status
operator|->
name|devices
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GimpDeviceStatusEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|entry
operator|->
name|arrow
argument_list|,
name|entry
operator|->
name|device_info
operator|->
name|device
operator|&&
name|entry
operator|->
name|device_info
operator|->
name|device
operator|==
name|status
operator|->
name|current_device
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
DECL|function|gimp_device_status_update_entry (GimpDeviceInfo * device_info,GimpDeviceStatusEntry * entry)
name|gimp_device_status_update_entry
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|,
name|GimpDeviceStatusEntry
modifier|*
name|entry
parameter_list|)
block|{
if|if
condition|(
operator|!
name|device_info
operator|->
name|device
operator|||
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
name|entry
operator|->
name|table
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gchar
name|buf
index|[
literal|64
index|]
decl_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Foreground: %d, %d, %d"
argument_list|)
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|entry
operator|->
name|foreground
argument_list|,
name|buf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Background: %d, %d, %d"
argument_list|)
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|entry
operator|->
name|background
argument_list|,
name|buf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
operator|->
name|table
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_status_save_clicked (GtkWidget * button,GimpDeviceStatus * status)
name|gimp_device_status_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpDeviceStatus
modifier|*
name|status
parameter_list|)
block|{
name|gimp_devices_save
argument_list|(
name|status
operator|->
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_status_view_clicked (GtkWidget * widget,GdkModifierType state,const gchar * identifier)
name|gimp_device_status_view_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
block|{
name|GimpDialogFactory
modifier|*
name|dialog_factory
decl_stmt|;
name|dialog_factory
operator|=
name|gimp_dialog_factory_from_name
argument_list|(
literal|"dock"
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|dialog_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
name|identifier
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

