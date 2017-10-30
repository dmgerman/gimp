begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdataeditor.c  * Copyright (C) 2002-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|<gdk/gdkkeysyms.h>
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
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdataeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo-aux.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|DEFAULT_MINIMAL_HEIGHT
define|#
directive|define
name|DEFAULT_MINIMAL_HEIGHT
value|96
end_define

begin_enum
enum|enum
DECL|enum|__anon28ff99030103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DATA_FACTORY
name|PROP_DATA_FACTORY
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_DATA
name|PROP_DATA
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_constructed
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
name|gimp_data_editor_dispose
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
name|gimp_data_editor_set_property
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
name|gimp_data_editor_get_property
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
name|gimp_data_editor_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_set_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GList
modifier|*
name|gimp_data_editor_get_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_data_editor_get_title
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_real_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_data_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_data_editor_name_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_name_activate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_data_editor_name_focus_out
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_data_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_save_dirty
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpDataEditor
argument_list|,
argument|gimp_data_editor
argument_list|,
argument|GIMP_TYPE_EDITOR
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_data_editor_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_data_editor_parent_class
end_define

begin_decl_stmt
specifier|static
name|GimpDockedInterface
modifier|*
name|parent_docked_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_class_init (GimpDataEditorClass * klass)
name|gimp_data_editor_class_init
parameter_list|(
name|GimpDataEditorClass
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
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_data_editor_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_data_editor_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_data_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_data_editor_get_property
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_data_editor_style_set
expr_stmt|;
name|klass
operator|->
name|set_data
operator|=
name|gimp_data_editor_real_set_data
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DATA_FACTORY
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"data-factory"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DATA_FACTORY
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTEXT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"context"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTEXT
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DATA
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"data"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DATA
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"minimal-height"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|32
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_MINIMAL_HEIGHT
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_docked_iface_init (GimpDockedInterface * iface)
name|gimp_data_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|parent_docked_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|iface
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parent_docked_iface
condition|)
name|parent_docked_iface
operator|=
name|g_type_default_interface_peek
argument_list|(
name|GIMP_TYPE_DOCKED
argument_list|)
expr_stmt|;
name|iface
operator|->
name|set_context
operator|=
name|gimp_data_editor_set_context
expr_stmt|;
name|iface
operator|->
name|set_aux_info
operator|=
name|gimp_data_editor_set_aux_info
expr_stmt|;
name|iface
operator|->
name|get_aux_info
operator|=
name|gimp_data_editor_get_aux_info
expr_stmt|;
name|iface
operator|->
name|get_title
operator|=
name|gimp_data_editor_get_title
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_init (GimpDataEditor * editor)
name|gimp_data_editor_init
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|editor
operator|->
name|data_factory
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|data_editable
operator|=
name|FALSE
expr_stmt|;
name|editor
operator|->
name|name_entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|editor
operator|->
name|name_entry
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
name|editor
operator|->
name|name_entry
argument_list|)
expr_stmt|;
name|gtk_editable_set_editable
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|,
literal|"key-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_editor_name_key_press
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_editor_name_activate
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|,
literal|"focus-out-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_editor_name_focus_out
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
DECL|function|gimp_data_editor_constructed (GObject * object)
name|gimp_data_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|object
argument_list|)
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
name|g_assert
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|editor
operator|->
name|data_factory
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|editor
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_data_editor_set_edit_active
argument_list|(
name|editor
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_dispose (GObject * object)
name|gimp_data_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
comment|/* Save dirty data before we clear out */
name|gimp_data_editor_save_dirty
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|gimp_data_editor_set_data
argument_list|(
name|editor
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|editor
operator|->
name|context
condition|)
name|gimp_docked_set_context
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
DECL|function|gimp_data_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_data_editor_set_property
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
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
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
name|PROP_DATA_FACTORY
case|:
name|editor
operator|->
name|data_factory
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTEXT
case|:
name|gimp_docked_set_context
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|object
argument_list|)
argument_list|,
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DATA
case|:
name|gimp_data_editor_set_data
argument_list|(
name|editor
argument_list|,
name|g_value_get_object
argument_list|(
name|value
argument_list|)
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
DECL|function|gimp_data_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_data_editor_get_property
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
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
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
name|PROP_DATA_FACTORY
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|data_factory
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTEXT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DATA
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|data
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
DECL|function|gimp_data_editor_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_data_editor_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|minimal_height
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"minimal-height"
argument_list|,
operator|&
name|minimal_height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|view
condition|)
name|gtk_widget_set_size_request
argument_list|(
name|editor
operator|->
name|view
argument_list|,
operator|-
literal|1
argument_list|,
name|minimal_height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_set_context (GimpDocked * docked,GimpContext * context)
name|gimp_data_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
if|if
condition|(
name|context
operator|==
name|editor
operator|->
name|context
condition|)
return|return;
if|if
condition|(
name|parent_docked_iface
operator|->
name|set_context
condition|)
name|parent_docked_iface
operator|->
name|set_context
argument_list|(
name|docked
argument_list|,
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|context
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|gimp_data_editor_data_changed
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
block|}
name|editor
operator|->
name|context
operator|=
name|context
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|context
condition|)
block|{
name|GType
name|data_type
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|g_object_ref
argument_list|(
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
name|data_type
operator|=
name|gimp_data_factory_get_data_type
argument_list|(
name|editor
operator|->
name|data_factory
argument_list|)
expr_stmt|;
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|gimp_context_get_by_type
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|data_type
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|gimp_context_type_to_signal_name
argument_list|(
name|data_type
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_editor_data_changed
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_data_editor_data_changed
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|data
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_define
DECL|macro|AUX_INFO_EDIT_ACTIVE
define|#
directive|define
name|AUX_INFO_EDIT_ACTIVE
value|"edit-active"
end_define

begin_define
DECL|macro|AUX_INFO_CURRENT_DATA
define|#
directive|define
name|AUX_INFO_CURRENT_DATA
value|"current-data"
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_set_aux_info (GimpDocked * docked,GList * aux_info)
name|gimp_data_editor_set_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|parent_docked_iface
operator|->
name|set_aux_info
argument_list|(
name|docked
argument_list|,
name|aux_info
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|aux_info
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
name|GimpSessionInfoAux
modifier|*
name|aux
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|aux
operator|->
name|name
argument_list|,
name|AUX_INFO_EDIT_ACTIVE
argument_list|)
condition|)
block|{
name|gboolean
name|edit_active
decl_stmt|;
name|edit_active
operator|=
operator|!
name|g_ascii_strcasecmp
argument_list|(
name|aux
operator|->
name|value
argument_list|,
literal|"true"
argument_list|)
expr_stmt|;
name|gimp_data_editor_set_edit_active
argument_list|(
name|editor
argument_list|,
name|edit_active
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|aux
operator|->
name|name
argument_list|,
name|AUX_INFO_CURRENT_DATA
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|editor
operator|->
name|edit_active
condition|)
block|{
name|GimpData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|editor
operator|->
name|data_factory
argument_list|)
argument_list|,
name|aux
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
name|gimp_data_editor_set_data
argument_list|(
name|editor
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_data_editor_get_aux_info (GimpDocked * docked)
name|gimp_data_editor_get_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|aux_info
decl_stmt|;
name|GimpSessionInfoAux
modifier|*
name|aux
decl_stmt|;
name|aux_info
operator|=
name|parent_docked_iface
operator|->
name|get_aux_info
argument_list|(
name|docked
argument_list|)
expr_stmt|;
name|aux
operator|=
name|gimp_session_info_aux_new
argument_list|(
name|AUX_INFO_EDIT_ACTIVE
argument_list|,
name|editor
operator|->
name|edit_active
condition|?
literal|"true"
else|:
literal|"false"
argument_list|)
expr_stmt|;
name|aux_info
operator|=
name|g_list_append
argument_list|(
name|aux_info
argument_list|,
name|aux
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|value
decl_stmt|;
name|value
operator|=
name|gimp_object_get_name
argument_list|(
name|editor
operator|->
name|data
argument_list|)
expr_stmt|;
name|aux
operator|=
name|gimp_session_info_aux_new
argument_list|(
name|AUX_INFO_CURRENT_DATA
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|aux_info
operator|=
name|g_list_append
argument_list|(
name|aux_info
argument_list|,
name|aux
argument_list|)
expr_stmt|;
block|}
return|return
name|aux_info
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_data_editor_get_title (GimpDocked * docked)
name|gimp_data_editor_get_title
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GimpDataEditorClass
modifier|*
name|editor_class
init|=
name|GIMP_DATA_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|data_editable
condition|)
return|return
name|g_strdup
argument_list|(
name|editor_class
operator|->
name|title
argument_list|)
return|;
else|else
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s (read only)"
argument_list|)
argument_list|,
name|editor_class
operator|->
name|title
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_real_set_data (GimpDataEditor * editor,GimpData * data)
name|gimp_data_editor_real_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|gboolean
name|editable
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
name|gimp_data_editor_save_dirty
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|data
argument_list|,
name|gimp_data_editor_data_name_changed
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|editor
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|editor
operator|->
name|data
operator|=
name|data
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
name|g_object_ref
argument_list|(
name|editor
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|data
argument_list|,
literal|"name-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_editor_data_name_changed
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|editor
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
name|gtk_editable_set_editable
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|)
argument_list|,
name|editor
operator|->
name|data
operator|&&
name|gimp_viewable_is_name_editable
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|editor
operator|->
name|data
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|editable
operator|=
operator|(
name|editor
operator|->
name|data
operator|&&
name|gimp_data_is_writable
argument_list|(
name|editor
operator|->
name|data
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|data_editable
operator|!=
name|editable
condition|)
block|{
name|editor
operator|->
name|data_editable
operator|=
name|editable
expr_stmt|;
name|gimp_docked_title_changed
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_editor_set_data (GimpDataEditor * editor,GimpData * data)
name|gimp_data_editor_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|data
operator|==
name|NULL
operator|||
name|GIMP_IS_DATA
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|data
operator|==
name|NULL
operator|||
name|g_type_is_a
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|data
argument_list|)
argument_list|,
name|gimp_data_factory_get_data_type
argument_list|(
name|editor
operator|->
name|data_factory
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
operator|!=
name|data
condition|)
block|{
name|GIMP_DATA_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
operator|->
name|set_data
argument_list|(
name|editor
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"data"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
condition|)
name|gimp_ui_manager_update
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|,
name|gimp_editor_get_popup_data
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_data_editor_get_data (GimpDataEditor * editor)
name|gimp_data_editor_get_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|editor
operator|->
name|data
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_editor_set_edit_active (GimpDataEditor * editor,gboolean edit_active)
name|gimp_data_editor_set_edit_active
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|gboolean
name|edit_active
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|edit_active
operator|!=
name|edit_active
condition|)
block|{
name|editor
operator|->
name|edit_active
operator|=
name|edit_active
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|edit_active
operator|&&
name|editor
operator|->
name|context
condition|)
block|{
name|GType
name|data_type
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|data_type
operator|=
name|gimp_data_factory_get_data_type
argument_list|(
name|editor
operator|->
name|data_factory
argument_list|)
expr_stmt|;
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|gimp_context_get_by_type
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|data_type
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_data_editor_set_data
argument_list|(
name|editor
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_data_editor_get_edit_active (GimpDataEditor * editor)
name|gimp_data_editor_get_edit_active
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|editor
operator|->
name|edit_active
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_data_changed (GimpContext * context,GimpData * data,GimpDataEditor * editor)
name|gimp_data_editor_data_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|edit_active
condition|)
name|gimp_data_editor_set_data
argument_list|(
name|editor
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_data_editor_name_key_press (GtkWidget * widget,GdkEventKey * kevent,GimpDataEditor * editor)
name|gimp_data_editor_name_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|kevent
operator|->
name|keyval
operator|==
name|GDK_KEY_Escape
condition|)
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|editor
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_name_activate (GtkWidget * widget,GimpDataEditor * editor)
name|gimp_data_editor_name_activate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
name|gchar
modifier|*
name|new_name
decl_stmt|;
name|new_name
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|new_name
operator|=
name|g_strstrip
argument_list|(
name|new_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|strlen
argument_list|(
name|new_name
argument_list|)
operator|&&
name|g_strcmp0
argument_list|(
name|new_name
argument_list|,
name|gimp_object_get_name
argument_list|(
name|editor
operator|->
name|data
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|editor
operator|->
name|data
argument_list|)
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|editor
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|new_name
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_data_editor_name_focus_out (GtkWidget * widget,GdkEvent * event,GimpDataEditor * editor)
name|gimp_data_editor_name_focus_out
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_data_editor_name_activate
argument_list|(
name|widget
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_data_name_changed (GimpObject * object,GimpDataEditor * editor)
name|gimp_data_editor_data_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_save_dirty (GimpDataEditor * editor)
name|gimp_data_editor_save_dirty
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpData
modifier|*
name|data
init|=
name|editor
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|data
operator|&&
name|gimp_data_is_dirty
argument_list|(
name|data
argument_list|)
operator|&&
name|gimp_data_is_writable
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_data_factory_data_save_single
argument_list|(
name|editor
operator|->
name|data_factory
argument_list|,
name|data
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp_data_factory_get_gimp
argument_list|(
name|editor
operator|->
name|data_factory
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

