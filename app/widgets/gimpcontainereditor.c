begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainereditor.c  * Copyright (C) 2001-2011 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainereditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainergridview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainericonview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainertreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
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
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2746673f0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_VIEW_TYPE
name|PROP_VIEW_TYPE
block|,
DECL|enumerator|PROP_CONTAINER
name|PROP_CONTAINER
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_VIEW_SIZE
name|PROP_VIEW_SIZE
block|,
DECL|enumerator|PROP_VIEW_BORDER_WIDTH
name|PROP_VIEW_BORDER_WIDTH
block|,
DECL|enumerator|PROP_MENU_FACTORY
name|PROP_MENU_FACTORY
block|,
DECL|enumerator|PROP_MENU_IDENTIFIER
name|PROP_MENU_IDENTIFIER
block|,
DECL|enumerator|PROP_UI_PATH
name|PROP_UI_PATH
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpContainerEditorPrivate
struct|struct
name|_GimpContainerEditorPrivate
block|{
DECL|member|view_type
name|GimpViewType
name|view_type
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|view_size
name|gint
name|view_size
decl_stmt|;
DECL|member|view_border_width
name|gint
name|view_border_width
decl_stmt|;
DECL|member|menu_factory
name|GimpMenuFactory
modifier|*
name|menu_factory
decl_stmt|;
DECL|member|menu_identifier
name|gchar
modifier|*
name|menu_identifier
decl_stmt|;
DECL|member|ui_path
name|gchar
modifier|*
name|ui_path
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_docked_iface_init
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
name|gimp_container_editor_constructed
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
name|gimp_container_editor_dispose
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
name|gimp_container_editor_set_property
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
name|gimp_container_editor_get_property
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
name|gboolean
name|gimp_container_editor_select_item
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
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_activate_item
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
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_context_item
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
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_real_context_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_container_editor_get_preview
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
name|void
name|gimp_container_editor_set_context
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
name|GimpUIManager
modifier|*
name|gimp_container_editor_get_menu
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|ui_path
parameter_list|,
name|gpointer
modifier|*
name|popup_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_container_editor_has_button_bar
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
name|gimp_container_editor_set_show_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_container_editor_get_show_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpContainerEditor,gimp_container_editor,GTK_TYPE_BOX,G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,gimp_container_editor_docked_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpContainerEditor
argument_list|,
argument|gimp_container_editor
argument_list|,
argument|GTK_TYPE_BOX
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_container_editor_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_container_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_container_editor_class_init
parameter_list|(
name|GimpContainerEditorClass
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
name|gimp_container_editor_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_container_editor_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_container_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_container_editor_get_property
expr_stmt|;
name|klass
operator|->
name|select_item
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|activate_item
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|context_item
operator|=
name|gimp_container_editor_real_context_item
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VIEW_TYPE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"view-type"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VIEW_TYPE
argument_list|,
name|GIMP_VIEW_TYPE_LIST
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
name|PROP_CONTAINER
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"container"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTAINER
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
name|PROP_VIEW_SIZE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"view-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|GIMP_VIEWABLE_MAX_PREVIEW_SIZE
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VIEW_BORDER_WIDTH
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"view-border-width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GIMP_VIEW_MAX_BORDER_WIDTH
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MENU_FACTORY
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"menu-factory"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_MENU_FACTORY
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
name|PROP_MENU_IDENTIFIER
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"menu-identifier"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|PROP_UI_PATH
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"ui-path"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpContainerEditorPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_docked_iface_init (GimpDockedInterface * iface)
name|gimp_container_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|get_preview
operator|=
name|gimp_container_editor_get_preview
expr_stmt|;
name|iface
operator|->
name|set_context
operator|=
name|gimp_container_editor_set_context
expr_stmt|;
name|iface
operator|->
name|get_menu
operator|=
name|gimp_container_editor_get_menu
expr_stmt|;
name|iface
operator|->
name|has_button_bar
operator|=
name|gimp_container_editor_has_button_bar
expr_stmt|;
name|iface
operator|->
name|set_show_button_bar
operator|=
name|gimp_container_editor_set_show_button_bar
expr_stmt|;
name|iface
operator|->
name|get_show_button_bar
operator|=
name|gimp_container_editor_get_show_button_bar
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_init (GimpContainerEditor * editor)
name|gimp_container_editor_init
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
name|editor
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|editor
argument_list|,
name|GIMP_TYPE_CONTAINER_EDITOR
argument_list|,
name|GimpContainerEditorPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_constructed (GObject * object)
name|gimp_container_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
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
name|GIMP_IS_CONTAINER
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|container
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|editor
operator|->
name|priv
operator|->
name|view_type
condition|)
block|{
case|case
name|GIMP_VIEW_TYPE_GRID
case|:
if|#
directive|if
literal|0
block|editor->view =         GIMP_CONTAINER_VIEW (gimp_container_icon_view_new (editor->priv->container,                                                            editor->priv->context,                                                            editor->priv->view_size,                                                            editor->priv->view_border_width));
else|#
directive|else
name|editor
operator|->
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|gimp_container_grid_view_new
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|container
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|context
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|view_size
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|view_border_width
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
break|break;
case|case
name|GIMP_VIEW_TYPE_LIST
case|:
name|editor
operator|->
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|gimp_container_tree_view_new
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|container
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|context
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|view_size
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|view_border_width
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_IS_LIST
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|container
argument_list|)
condition|)
name|gimp_container_view_set_reorderable
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
operator|!
name|GIMP_LIST
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|container
argument_list|)
operator|->
name|sort_func
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|priv
operator|->
name|menu_factory
operator|&&
name|editor
operator|->
name|priv
operator|->
name|menu_identifier
operator|&&
name|editor
operator|->
name|priv
operator|->
name|ui_path
condition|)
block|{
name|gimp_editor_create_menu
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|menu_factory
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|menu_identifier
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|ui_path
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|view
argument_list|)
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
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|editor
operator|->
name|view
argument_list|,
literal|"select-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_editor_select_item
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|editor
operator|->
name|view
argument_list|,
literal|"activate-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_editor_activate_item
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|editor
operator|->
name|view
argument_list|,
literal|"context-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_editor_context_item
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|{
name|GimpObject
modifier|*
name|object
init|=
name|gimp_context_get_by_type
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|context
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|container
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_container_editor_select_item
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
operator|(
name|GimpViewable
operator|*
operator|)
name|object
argument_list|,
name|NULL
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
DECL|function|gimp_container_editor_dispose (GObject * object)
name|gimp_container_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|editor
operator|->
name|priv
operator|->
name|container
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|editor
operator|->
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|editor
operator|->
name|priv
operator|->
name|menu_factory
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|editor
operator|->
name|priv
operator|->
name|menu_identifier
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|editor
operator|->
name|priv
operator|->
name|ui_path
argument_list|,
name|g_free
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
DECL|function|gimp_container_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_container_editor_set_property
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
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
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
name|PROP_VIEW_TYPE
case|:
name|editor
operator|->
name|priv
operator|->
name|view_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTAINER
case|:
name|editor
operator|->
name|priv
operator|->
name|container
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTEXT
case|:
name|editor
operator|->
name|priv
operator|->
name|context
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VIEW_SIZE
case|:
name|editor
operator|->
name|priv
operator|->
name|view_size
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VIEW_BORDER_WIDTH
case|:
name|editor
operator|->
name|priv
operator|->
name|view_border_width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MENU_FACTORY
case|:
name|editor
operator|->
name|priv
operator|->
name|menu_factory
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MENU_IDENTIFIER
case|:
name|editor
operator|->
name|priv
operator|->
name|menu_identifier
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UI_PATH
case|:
name|editor
operator|->
name|priv
operator|->
name|ui_path
operator|=
name|g_value_dup_string
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
DECL|function|gimp_container_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_container_editor_get_property
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
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
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
name|PROP_VIEW_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|view_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTAINER
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|container
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
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VIEW_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|view_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VIEW_BORDER_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|view_border_width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MENU_FACTORY
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|menu_factory
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MENU_IDENTIFIER
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|menu_identifier
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UI_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|ui_path
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
name|GtkSelectionMode
DECL|function|gimp_container_editor_get_selection_mode (GimpContainerEditor * editor)
name|gimp_container_editor_get_selection_mode
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
return|return
name|gimp_container_view_get_selection_mode
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_editor_set_selection_mode (GimpContainerEditor * editor,GtkSelectionMode mode)
name|gimp_container_editor_set_selection_mode
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GtkSelectionMode
name|mode
parameter_list|)
block|{
name|gimp_container_view_set_selection_mode
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|mode
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_editor_select_item (GtkWidget * widget,GimpViewable * viewable,gpointer insert_data,GimpContainerEditor * editor)
name|gimp_container_editor_select_item
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
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpContainerEditorClass
modifier|*
name|klass
init|=
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|klass
operator|->
name|select_item
condition|)
name|klass
operator|->
name|select_item
argument_list|(
name|editor
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
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
operator|->
name|view
argument_list|)
argument_list|)
argument_list|,
name|gimp_editor_get_popup_data
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_activate_item (GtkWidget * widget,GimpViewable * viewable,gpointer insert_data,GimpContainerEditor * editor)
name|gimp_container_editor_activate_item
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
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpContainerEditorClass
modifier|*
name|klass
init|=
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|klass
operator|->
name|activate_item
condition|)
name|klass
operator|->
name|activate_item
argument_list|(
name|editor
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_context_item (GtkWidget * widget,GimpViewable * viewable,gpointer insert_data,GimpContainerEditor * editor)
name|gimp_container_editor_context_item
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
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpContainerEditorClass
modifier|*
name|klass
init|=
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|klass
operator|->
name|context_item
condition|)
name|klass
operator|->
name|context_item
argument_list|(
name|editor
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_real_context_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_container_editor_real_context_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
init|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
decl_stmt|;
if|if
condition|(
name|viewable
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_editor_popup_menu
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_container_editor_get_preview (GimpDocked * docked,GimpContext * context,GtkIconSize size)
name|gimp_container_editor_get_preview
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
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
return|return
name|gimp_docked_get_preview
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|context
argument_list|,
name|size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_set_context (GimpDocked * docked,GimpContext * context)
name|gimp_container_editor_set_context
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
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|gimp_docked_set_context
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpUIManager
modifier|*
DECL|function|gimp_container_editor_get_menu (GimpDocked * docked,const gchar ** ui_path,gpointer * popup_data)
name|gimp_container_editor_get_menu
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|ui_path
parameter_list|,
name|gpointer
modifier|*
name|popup_data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
return|return
name|gimp_docked_get_menu
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|ui_path
argument_list|,
name|popup_data
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_editor_has_button_bar (GimpDocked * docked)
name|gimp_container_editor_has_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
return|return
name|gimp_docked_has_button_bar
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_set_show_button_bar (GimpDocked * docked,gboolean show)
name|gimp_container_editor_set_show_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|gimp_docked_set_show_button_bar
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_editor_get_show_button_bar (GimpDocked * docked)
name|gimp_container_editor_get_show_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
return|return
name|gimp_docked_get_show_button_bar
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
return|;
block|}
end_function

end_unit

