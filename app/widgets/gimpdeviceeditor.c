begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdeviceeditor.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainertreestore.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainertreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdeviceeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpdeviceinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdeviceinfoeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpdevicemanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpdevices.h"
end_include

begin_include
include|#
directive|include
file|"gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"gimpmessagedialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c82d4b20103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpDeviceEditorPrivate
typedef|typedef
name|struct
name|_GimpDeviceEditorPrivate
name|GimpDeviceEditorPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDeviceEditorPrivate
struct|struct
name|_GimpDeviceEditorPrivate
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|name_changed_handler
name|GQuark
name|name_changed_handler
decl_stmt|;
DECL|member|treeview
name|GtkWidget
modifier|*
name|treeview
decl_stmt|;
DECL|member|delete_button
name|GtkWidget
modifier|*
name|delete_button
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
decl_stmt|;
DECL|member|image
name|GtkWidget
modifier|*
name|image
decl_stmt|;
DECL|member|notebook
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_DEVICE_EDITOR_GET_PRIVATE (editor)
define|#
directive|define
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
parameter_list|(
name|editor
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (editor, \                                      GIMP_TYPE_DEVICE_EDITOR, \                                      GimpDeviceEditorPrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_device_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_editor_set_property
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
name|gimp_device_editor_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
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
name|gimp_device_editor_add_device
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_editor_remove_device
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_editor_device_changed
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_editor_select_device
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_editor_switch_page
parameter_list|(
name|GtkNotebook
modifier|*
name|notebook
parameter_list|,
name|gpointer
name|page
parameter_list|,
name|guint
name|page_num
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_editor_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDeviceEditor,gimp_device_editor,GTK_TYPE_PANED)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDeviceEditor
argument_list|,
argument|gimp_device_editor
argument_list|,
argument|GTK_TYPE_PANED
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_device_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_device_editor_class_init
parameter_list|(
name|GimpDeviceEditorClass
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
name|object_class
operator|->
name|constructed
operator|=
name|gimp_device_editor_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_device_editor_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_device_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_device_editor_get_property
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
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDeviceEditorPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_editor_init (GimpDeviceEditor * editor)
name|gimp_device_editor_init
parameter_list|(
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|ebox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|gint
name|icon_width
decl_stmt|;
name|gint
name|icon_height
decl_stmt|;
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
name|gtk_icon_size_lookup
argument_list|(
name|GTK_ICON_SIZE_BUTTON
argument_list|,
operator|&
name|icon_width
argument_list|,
operator|&
name|icon_height
argument_list|)
expr_stmt|;
name|private
operator|->
name|treeview
operator|=
name|gimp_container_tree_view_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
name|icon_height
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|private
operator|->
name|treeview
argument_list|,
literal|200
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|editor
argument_list|)
argument_list|,
name|private
operator|->
name|treeview
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|private
operator|->
name|treeview
argument_list|,
literal|"select-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_editor_select_device
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|private
operator|->
name|delete_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
argument_list|,
literal|"edit-delete"
argument_list|,
name|_
argument_list|(
literal|"Delete the selected device"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_editor_delete_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|private
operator|->
name|delete_button
argument_list|,
name|FALSE
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
name|gtk_paned_pack2
argument_list|(
name|GTK_PANED
argument_list|(
name|editor
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|ebox
operator|=
name|gtk_event_box_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_state
argument_list|(
name|ebox
argument_list|,
name|GTK_STATE_SELECTED
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|ebox
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
name|ebox
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
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|ebox
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|private
operator|->
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_ellipsize
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|label
argument_list|)
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|private
operator|->
name|label
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
name|private
operator|->
name|label
argument_list|)
expr_stmt|;
name|private
operator|->
name|image
operator|=
name|gtk_image_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|private
operator|->
name|image
argument_list|,
operator|-
literal|1
argument_list|,
literal|24
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|private
operator|->
name|image
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
name|private
operator|->
name|image
argument_list|)
expr_stmt|;
name|private
operator|->
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_notebook_set_show_border
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|private
operator|->
name|notebook
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_notebook_set_show_tabs
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|private
operator|->
name|notebook
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|private
operator|->
name|notebook
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
name|private
operator|->
name|notebook
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|notebook
argument_list|,
literal|"switch-page"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_editor_switch_page
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_editor_constructed (GObject * object)
name|gimp_device_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDeviceEditor
modifier|*
name|editor
init|=
name|GIMP_DEVICE_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|devices
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_assert
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|private
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|devices
operator|=
name|GIMP_CONTAINER
argument_list|(
name|gimp_devices_get_manager
argument_list|(
name|private
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  connect to "remove" before the container view does so we can get    *  the notebook child stored in its model    */
name|g_signal_connect
argument_list|(
name|devices
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_editor_remove_device
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_container_view_set_container
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
argument_list|,
name|devices
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_context_new
argument_list|(
name|private
operator|->
name|gimp
argument_list|,
literal|"device-editor-list"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_view_set_context
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|devices
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_editor_add_device
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|private
operator|->
name|name_changed_handler
operator|=
name|gimp_container_add_handler
argument_list|(
name|devices
argument_list|,
literal|"name-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_editor_device_changed
argument_list|)
argument_list|,
name|editor
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
name|queue
operator|->
name|head
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gimp_device_editor_add_device
argument_list|(
name|devices
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_editor_dispose (GObject * object)
name|gimp_device_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|devices
decl_stmt|;
name|devices
operator|=
name|GIMP_CONTAINER
argument_list|(
name|gimp_devices_get_manager
argument_list|(
name|private
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|devices
argument_list|,
name|gimp_device_editor_add_device
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|devices
argument_list|,
name|gimp_device_editor_remove_device
argument_list|,
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|name_changed_handler
condition|)
block|{
name|gimp_container_remove_handler
argument_list|(
name|devices
argument_list|,
name|private
operator|->
name|name_changed_handler
argument_list|)
expr_stmt|;
name|private
operator|->
name|name_changed_handler
operator|=
literal|0
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_device_editor_set_property
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
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
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
name|private
operator|->
name|gimp
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't ref */
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
DECL|function|gimp_device_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_device_editor_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
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
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|gimp
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
DECL|function|gimp_device_editor_add_device (GimpContainer * container,GimpDeviceInfo * info,GimpDeviceEditor * editor)
name|gimp_device_editor_add_device
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkTreeIter
modifier|*
name|iter
decl_stmt|;
name|widget
operator|=
name|gimp_device_info_editor_new
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|private
operator|->
name|notebook
argument_list|)
argument_list|,
name|widget
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gimp_container_view_lookup
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|iter
condition|)
block|{
name|GimpContainerTreeView
modifier|*
name|treeview
decl_stmt|;
name|treeview
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
expr_stmt|;
name|gtk_tree_store_set
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|treeview
operator|->
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_USER_DATA
argument_list|,
name|widget
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME_SENSITIVE
argument_list|,
name|gimp_device_info_get_device
argument_list|(
name|info
argument_list|,
name|NULL
argument_list|)
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_editor_remove_device (GimpContainer * container,GimpDeviceInfo * info,GimpDeviceEditor * editor)
name|gimp_device_editor_remove_device
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GtkTreeIter
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gimp_container_view_lookup
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|iter
condition|)
block|{
name|GimpContainerTreeView
modifier|*
name|treeview
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|treeview
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|treeview
operator|->
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_USER_DATA
argument_list|,
operator|&
name|widget
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
condition|)
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_editor_device_changed (GimpDeviceInfo * info,GimpDeviceEditor * editor)
name|gimp_device_editor_device_changed
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GtkTreeIter
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gimp_container_view_lookup
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|iter
condition|)
block|{
name|GimpContainerTreeView
modifier|*
name|treeview
decl_stmt|;
name|treeview
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
expr_stmt|;
name|gtk_tree_store_set
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|treeview
operator|->
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME_SENSITIVE
argument_list|,
name|gimp_device_info_get_device
argument_list|(
name|info
argument_list|,
name|NULL
argument_list|)
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_editor_select_device (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data,GimpDeviceEditor * editor)
name|gimp_device_editor_select_device
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|viewable
operator|&&
name|insert_data
condition|)
block|{
name|GimpContainerTreeView
modifier|*
name|treeview
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|treeview
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|treeview
operator|->
name|model
argument_list|,
name|insert_data
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_USER_DATA
argument_list|,
operator|&
name|widget
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
condition|)
block|{
name|gint
name|page_num
init|=
name|gtk_notebook_page_num
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|private
operator|->
name|notebook
argument_list|)
argument_list|,
name|widget
argument_list|)
decl_stmt|;
name|gtk_notebook_set_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|private
operator|->
name|notebook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_editor_switch_page (GtkNotebook * notebook,gpointer page,guint page_num,GimpDeviceEditor * editor)
name|gimp_device_editor_switch_page
parameter_list|(
name|GtkNotebook
modifier|*
name|notebook
parameter_list|,
name|gpointer
name|page
parameter_list|,
name|guint
name|page_num
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GimpDeviceInfo
modifier|*
name|info
decl_stmt|;
name|gboolean
name|delete_sensitive
init|=
name|FALSE
decl_stmt|;
name|widget
operator|=
name|gtk_notebook_get_nth_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|widget
argument_list|,
literal|"info"
argument_list|,
operator|&
name|info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|label
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_image_set_from_icon_name
argument_list|(
name|GTK_IMAGE
argument_list|(
name|private
operator|->
name|image
argument_list|)
argument_list|,
name|gimp_viewable_get_icon_name
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|info
argument_list|)
argument_list|)
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_device_info_get_device
argument_list|(
name|info
argument_list|,
name|NULL
argument_list|)
condition|)
name|delete_sensitive
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|private
operator|->
name|delete_button
argument_list|,
name|delete_sensitive
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_editor_delete_response (GtkWidget * dialog,gint response_id,GimpDeviceEditor * editor)
name|gimp_device_editor_delete_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GList
modifier|*
name|selected
decl_stmt|;
if|if
condition|(
name|gimp_container_view_get_selected
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
argument_list|,
operator|&
name|selected
argument_list|)
condition|)
block|{
name|GimpContainer
modifier|*
name|devices
decl_stmt|;
name|devices
operator|=
name|GIMP_CONTAINER
argument_list|(
name|gimp_devices_get_manager
argument_list|(
name|private
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_remove
argument_list|(
name|devices
argument_list|,
name|selected
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|selected
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_editor_delete_clicked (GtkWidget * button,GimpDeviceEditor * editor)
name|gimp_device_editor_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpDeviceEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDeviceEditorPrivate
modifier|*
name|private
init|=
name|GIMP_DEVICE_EDITOR_GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GList
modifier|*
name|selected
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_container_view_get_selected
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|private
operator|->
name|treeview
argument_list|)
argument_list|,
operator|&
name|selected
argument_list|)
condition|)
return|return;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Delete Device Settings"
argument_list|)
argument_list|,
name|GIMP_ICON_DIALOG_QUESTION
argument_list|,
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|,
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
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
literal|"_Delete"
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
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
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
name|gimp_device_editor_delete_response
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Delete \"%s\"?"
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|selected
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"You are about to delete this device's "
literal|"stored settings.\n"
literal|"The next time this device is plugged, "
literal|"default settings will be used."
argument_list|)
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|selected
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_device_editor_new (Gimp * gimp)
name|gimp_device_editor_new
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
name|GIMP_TYPE_DEVICE_EDITOR
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

end_unit

