begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptooloptionseditor.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
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
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptionseditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c7704080103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|, }
enum|;
end_enum

begin_struct
DECL|struct|_GimpToolOptionsEditorPrivate
struct|struct
name|_GimpToolOptionsEditorPrivate
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|scrolled_window
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
DECL|member|options_vbox
name|GtkWidget
modifier|*
name|options_vbox
decl_stmt|;
DECL|member|title_label
name|GtkWidget
modifier|*
name|title_label
decl_stmt|;
DECL|member|save_button
name|GtkWidget
modifier|*
name|save_button
decl_stmt|;
DECL|member|restore_button
name|GtkWidget
modifier|*
name|restore_button
decl_stmt|;
DECL|member|delete_button
name|GtkWidget
modifier|*
name|delete_button
decl_stmt|;
DECL|member|reset_button
name|GtkWidget
modifier|*
name|reset_button
decl_stmt|;
DECL|member|visible_tool_options
name|GimpToolOptions
modifier|*
name|visible_tool_options
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_docked_iface_init
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
name|gimp_tool_options_editor_constructed
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
name|gimp_tool_options_editor_dispose
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
name|gimp_tool_options_editor_set_property
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
name|gimp_tool_options_editor_get_property
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
name|GtkWidget
modifier|*
name|gimp_tool_options_editor_get_preview
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_tool_options_editor_get_title
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_tool_options_editor_get_prefer_icon
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
name|gimp_tool_options_editor_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_restore_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
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
name|gimp_tool_options_editor_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_presets_update
parameter_list|(
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpToolOptionsEditor,gimp_tool_options_editor,GIMP_TYPE_EDITOR,G_ADD_PRIVATE (GimpToolOptionsEditor)G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,gimp_tool_options_editor_docked_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpToolOptionsEditor
argument_list|,
argument|gimp_tool_options_editor
argument_list|,
argument|GIMP_TYPE_EDITOR
argument_list|,
argument|G_ADD_PRIVATE (GimpToolOptionsEditor)                          G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_tool_options_editor_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_options_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tool_options_editor_class_init
parameter_list|(
name|GimpToolOptionsEditorClass
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
name|gimp_tool_options_editor_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_tool_options_editor_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_tool_options_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_tool_options_editor_get_property
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_docked_iface_init (GimpDockedInterface * docked_iface)
name|gimp_tool_options_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
block|{
name|docked_iface
operator|->
name|get_preview
operator|=
name|gimp_tool_options_editor_get_preview
expr_stmt|;
name|docked_iface
operator|->
name|get_title
operator|=
name|gimp_tool_options_editor_get_title
expr_stmt|;
name|docked_iface
operator|->
name|get_prefer_icon
operator|=
name|gimp_tool_options_editor_get_prefer_icon
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_init (GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_init
parameter_list|(
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkScrolledWindow
modifier|*
name|scrolled_window
decl_stmt|;
name|editor
operator|->
name|p
operator|=
name|gimp_tool_options_editor_get_instance_private
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|200
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|gimp_tool_options_editor_drop_tool
argument_list|,
name|editor
argument_list|)
expr_stmt|;
comment|/*  The label containing the tool options title */
name|editor
operator|->
name|p
operator|->
name|title_label
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
name|editor
operator|->
name|p
operator|->
name|title_label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|p
operator|->
name|title_label
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
name|editor
argument_list|)
argument_list|,
name|editor
operator|->
name|p
operator|->
name|title_label
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
name|p
operator|->
name|title_label
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|scrolled_window
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|scrolled_window
operator|=
name|GTK_SCROLLED_WINDOW
argument_list|(
name|editor
operator|->
name|p
operator|->
name|scrolled_window
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|scrolled_window
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_overlay_scrolling
argument_list|(
name|scrolled_window
argument_list|,
name|FALSE
argument_list|)
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
name|p
operator|->
name|scrolled_window
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
name|editor
operator|->
name|p
operator|->
name|scrolled_window
argument_list|)
expr_stmt|;
comment|/*  The vbox containing the tool options  */
name|editor
operator|->
name|p
operator|->
name|options_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|editor
operator|->
name|p
operator|->
name|options_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
operator|->
name|p
operator|->
name|options_vbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_constructed (GObject * object)
name|gimp_tool_options_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|user_context
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
name|editor
operator|->
name|p
operator|->
name|save_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GIMP_ICON_DOCUMENT_SAVE
argument_list|,
name|_
argument_list|(
literal|"Save Tool Preset..."
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_SAVE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_save_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|restore_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GIMP_ICON_DOCUMENT_REVERT
argument_list|,
name|_
argument_list|(
literal|"Restore Tool Preset..."
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_RESTORE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_restore_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|delete_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GIMP_ICON_EDIT_DELETE
argument_list|,
name|_
argument_list|(
literal|"Delete Tool Preset..."
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DELETE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_delete_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|reset_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"tool-options"
argument_list|,
literal|"tool-options-reset"
argument_list|,
literal|"tool-options-reset-all"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|editor
operator|->
name|p
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|user_context
argument_list|,
literal|"tool-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_tool_changed
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_tool_options_editor_tool_changed
argument_list|(
name|user_context
argument_list|,
name|gimp_context_get_tool
argument_list|(
name|user_context
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
DECL|function|gimp_tool_options_editor_dispose (GObject * object)
name|gimp_tool_options_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|p
operator|->
name|options_vbox
condition|)
block|{
name|GList
modifier|*
name|options
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|options
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
operator|->
name|p
operator|->
name|options_vbox
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|options
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
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
operator|->
name|p
operator|->
name|options_vbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|options_vbox
operator|=
name|NULL
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
DECL|function|gimp_tool_options_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_tool_options_editor_set_property
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
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
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
name|editor
operator|->
name|p
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
DECL|function|gimp_tool_options_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_tool_options_editor_get_property
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
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
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
name|editor
operator|->
name|p
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
name|GtkWidget
modifier|*
DECL|function|gimp_tool_options_editor_get_preview (GimpDocked * docked,GimpContext * context,GtkIconSize size)
name|gimp_tool_options_editor_get_preview
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gtk_icon_size_lookup
argument_list|(
name|size
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|view
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
name|height
argument_list|)
expr_stmt|;
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
operator|->
name|size
operator|=
operator|-
literal|1
expr_stmt|;
name|gimp_view_renderer_set_size_full
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|view
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_tool_options_editor_get_title (GimpDocked * docked)
name|gimp_tool_options_editor_get_title
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|editor
operator|->
name|p
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
name|tool_info
condition|?
name|g_strdup
argument_list|(
name|tool_info
operator|->
name|label
argument_list|)
else|:
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_tool_options_editor_get_prefer_icon (GimpDocked * docked)
name|gimp_tool_options_editor_get_prefer_icon
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
comment|/* We support get_preview() for tab tyles, but we prefer to show our    * icon    */
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_tool_options_editor_new (Gimp * gimp,GimpMenuFactory * menu_factory)
name|gimp_tool_options_editor_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_OPTIONS_EDITOR
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<ToolOptions>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/tool-options-popup"
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpToolOptions
modifier|*
DECL|function|gimp_tool_options_editor_get_tool_options (GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_get_tool_options
parameter_list|(
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_OPTIONS_EDITOR
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
name|p
operator|->
name|visible_tool_options
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_menu_popup (GimpToolOptionsEditor * editor,GtkWidget * button,const gchar * path)
name|gimp_tool_options_editor_menu_popup
parameter_list|(
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|,
name|GtkWidget
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|gimp_editor
init|=
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|gimp_ui_manager_get_widget
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|gimp_editor
argument_list|)
argument_list|,
name|gimp_editor_get_ui_path
argument_list|(
name|gimp_editor
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_ui_manager_update
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|gimp_editor
argument_list|)
argument_list|,
name|gimp_editor_get_popup_data
argument_list|(
name|gimp_editor
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_ui_manager_ui_popup_at_widget
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|gimp_editor
argument_list|)
argument_list|,
name|path
argument_list|,
name|button
argument_list|,
name|GDK_GRAVITY_WEST
argument_list|,
name|GDK_GRAVITY_NORTH_EAST
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_save_clicked (GtkWidget * widget,GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|gtk_widget_get_sensitive
argument_list|(
name|editor
operator|->
name|p
operator|->
name|restore_button
argument_list|)
comment|/* evil but correct */
condition|)
block|{
name|gimp_tool_options_editor_menu_popup
argument_list|(
name|editor
argument_list|,
name|widget
argument_list|,
literal|"/tool-options-popup/Save"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_ui_manager_activate_action
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|,
literal|"tool-options"
argument_list|,
literal|"tool-options-save-new-preset"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_restore_clicked (GtkWidget * widget,GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_restore_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_tool_options_editor_menu_popup
argument_list|(
name|editor
argument_list|,
name|widget
argument_list|,
literal|"/tool-options-popup/Restore"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_delete_clicked (GtkWidget * widget,GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_tool_options_editor_menu_popup
argument_list|(
name|editor
argument_list|,
name|widget
argument_list|,
literal|"/tool-options-popup/Delete"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_drop_tool (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|gimp_tool_options_editor_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|editor
operator|->
name|p
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gimp_context_set_tool
argument_list|(
name|context
argument_list|,
name|GIMP_TOOL_INFO
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_tool_changed (GimpContext * context,GimpToolInfo * tool_info,GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|presets
decl_stmt|;
name|GtkWidget
modifier|*
name|options_gui
decl_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|tool_info
operator|->
name|tool_options
operator|==
name|editor
operator|->
name|p
operator|->
name|visible_tool_options
condition|)
return|return;
if|if
condition|(
name|editor
operator|->
name|p
operator|->
name|visible_tool_options
condition|)
block|{
name|presets
operator|=
name|editor
operator|->
name|p
operator|->
name|visible_tool_options
operator|->
name|tool_info
operator|->
name|presets
expr_stmt|;
if|if
condition|(
name|presets
condition|)
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|presets
argument_list|,
name|gimp_tool_options_editor_presets_update
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|options_gui
operator|=
name|gimp_tools_get_tool_options_gui
argument_list|(
name|editor
operator|->
name|p
operator|->
name|visible_tool_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|options_gui
condition|)
name|gtk_widget_hide
argument_list|(
name|options_gui
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|visible_tool_options
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|&&
name|tool_info
operator|->
name|tool_options
condition|)
block|{
name|presets
operator|=
name|tool_info
operator|->
name|presets
expr_stmt|;
if|if
condition|(
name|presets
condition|)
block|{
name|g_signal_connect_object
argument_list|(
name|presets
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_presets_update
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|presets
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_presets_update
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|presets
argument_list|,
literal|"thaw"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_presets_update
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
block|}
name|options_gui
operator|=
name|gimp_tools_get_tool_options_gui
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_widget_get_parent
argument_list|(
name|options_gui
argument_list|)
condition|)
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|p
operator|->
name|options_vbox
argument_list|)
argument_list|,
name|options_gui
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
name|options_gui
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|visible_tool_options
operator|=
name|tool_info
operator|->
name|tool_options
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|editor
operator|->
name|p
operator|->
name|scrolled_window
argument_list|,
name|NULL
argument_list|,
name|tool_info
operator|->
name|help_id
argument_list|)
expr_stmt|;
name|gimp_tool_options_editor_presets_update
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|editor
operator|->
name|p
operator|->
name|title_label
operator|!=
name|NULL
condition|)
block|{
name|gchar
modifier|*
name|title
decl_stmt|;
name|title
operator|=
name|gimp_docked_get_title
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|p
operator|->
name|title_label
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
block|}
name|gimp_docked_title_changed
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_presets_update (GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_presets_update
parameter_list|(
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|editor
operator|->
name|p
operator|->
name|visible_tool_options
operator|->
name|tool_info
decl_stmt|;
name|gboolean
name|save_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|restore_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|delete_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|reset_sensitive
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|presets
condition|)
block|{
name|save_sensitive
operator|=
name|TRUE
expr_stmt|;
name|reset_sensitive
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_container_is_empty
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|)
condition|)
block|{
name|restore_sensitive
operator|=
name|TRUE
expr_stmt|;
name|delete_sensitive
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|p
operator|->
name|save_button
argument_list|,
name|save_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|p
operator|->
name|restore_button
argument_list|,
name|restore_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|p
operator|->
name|delete_button
argument_list|,
name|delete_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|p
operator|->
name|reset_button
argument_list|,
name|reset_sensitive
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

