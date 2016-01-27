begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsymmetryeditor.c  * Copyright (C) 2015 Jehan<jehan@girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"config/gimpguiconfig.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-symmetry.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpsymmetry.h"
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
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpspinscale.h"
end_include

begin_include
include|#
directive|include
file|"gimpsymmetryeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a23acb60103
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
DECL|struct|_GimpSymmetryEditorPrivate
struct|struct
name|_GimpSymmetryEditorPrivate
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|menu
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
DECL|member|options_frame
name|GtkWidget
modifier|*
name|options_frame
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_symmetry_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Signal handlers on the GObject. */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_symmetry_editor_constructed
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
name|gimp_symmetry_editor_dispose
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
name|gimp_symmetry_editor_set_property
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
name|gimp_symmetry_editor_get_property
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

begin_comment
comment|/* Signal handlers on the context. */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_symmetry_editor_image_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSymmetryEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Signal handlers on the contextual image. */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_symmetry_editor_symmetry_notify
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpSymmetryEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Signal handlers on the symmetry. */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_symmetry_editor_symmetry_updated
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSymmetryEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Private functions. */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_symmetry_editor_set_options
parameter_list|(
name|GimpSymmetryEditor
modifier|*
name|editor
parameter_list|,
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpSymmetryEditor,gimp_symmetry_editor,GIMP_TYPE_EDITOR,G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,gimp_symmetry_editor_docked_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpSymmetryEditor
argument_list|,
argument|gimp_symmetry_editor
argument_list|,
argument|GIMP_TYPE_EDITOR
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_symmetry_editor_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_symmetry_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_symmetry_editor_class_init
parameter_list|(
name|GimpSymmetryEditorClass
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
name|gimp_symmetry_editor_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_symmetry_editor_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_symmetry_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_symmetry_editor_get_property
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
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpSymmetryEditorPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_symmetry_editor_docked_iface_init (GimpDockedInterface * docked_iface)
name|gimp_symmetry_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_symmetry_editor_init (GimpSymmetryEditor * editor)
name|gimp_symmetry_editor_init
parameter_list|(
name|GimpSymmetryEditor
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
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|editor
argument_list|,
name|GIMP_TYPE_SYMMETRY_EDITOR
argument_list|,
name|GimpSymmetryEditorPrivate
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
comment|/* Scrolled window to keep the dock size reasonable. */
name|scrolled_window
operator|=
name|GTK_SCROLLED_WINDOW
argument_list|(
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|scrolled_window
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
name|scrolled_window
argument_list|)
argument_list|)
expr_stmt|;
comment|/* A frame to hold the symmetry options. */
name|editor
operator|->
name|p
operator|->
name|options_frame
operator|=
name|gimp_frame_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_add_with_viewport
argument_list|(
name|scrolled_window
argument_list|,
name|editor
operator|->
name|p
operator|->
name|options_frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_symmetry_editor_constructed (GObject * object)
name|gimp_symmetry_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSymmetryEditor
modifier|*
name|editor
init|=
name|GIMP_SYMMETRY_EDITOR
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
literal|"image-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_symmetry_editor_image_changed
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_symmetry_editor_image_changed
argument_list|(
name|user_context
argument_list|,
name|gimp_context_get_image
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
DECL|function|gimp_symmetry_editor_dispose (GObject * object)
name|gimp_symmetry_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSymmetryEditor
modifier|*
name|editor
init|=
name|GIMP_SYMMETRY_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|editor
operator|->
name|p
operator|->
name|image
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
DECL|function|gimp_symmetry_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_symmetry_editor_set_property
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
name|GimpSymmetryEditor
modifier|*
name|editor
init|=
name|GIMP_SYMMETRY_EDITOR
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
DECL|function|gimp_symmetry_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_symmetry_editor_get_property
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
name|GimpSymmetryEditor
modifier|*
name|editor
init|=
name|GIMP_SYMMETRY_EDITOR
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
name|void
DECL|function|gimp_symmetry_editor_image_changed (GimpContext * context,GimpImage * image,GimpSymmetryEditor * editor)
name|gimp_symmetry_editor_image_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSymmetryEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|guiconfig
decl_stmt|;
if|if
condition|(
name|image
operator|==
name|editor
operator|->
name|p
operator|->
name|image
condition|)
return|return;
name|guiconfig
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|editor
operator|->
name|p
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
comment|/* Disconnect and unref the previous image. */
if|if
condition|(
name|editor
operator|->
name|p
operator|->
name|image
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|p
operator|->
name|image
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_symmetry_editor_symmetry_notify
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|editor
operator|->
name|p
operator|->
name|image
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|image
operator|=
name|NULL
expr_stmt|;
block|}
comment|/* Destroy the previous menu. */
if|if
condition|(
name|editor
operator|->
name|p
operator|->
name|menu
condition|)
name|gtk_widget_destroy
argument_list|(
name|editor
operator|->
name|p
operator|->
name|menu
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|menu
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|image
operator|&&
name|guiconfig
operator|->
name|playground_symmetry
condition|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|GList
modifier|*
name|syms
decl_stmt|;
name|GList
modifier|*
name|sym_iter
decl_stmt|;
name|GimpSymmetry
modifier|*
name|symmetry
decl_stmt|;
name|store
operator|=
name|gimp_int_store_new
argument_list|()
expr_stmt|;
comment|/* The menu of available symmetries. */
name|syms
operator|=
name|gimp_image_symmetry_list
argument_list|()
expr_stmt|;
for|for
control|(
name|sym_iter
operator|=
name|syms
init|;
name|sym_iter
condition|;
name|sym_iter
operator|=
name|g_list_next
argument_list|(
name|sym_iter
argument_list|)
control|)
block|{
name|GimpSymmetryClass
modifier|*
name|klass
decl_stmt|;
name|GType
name|type
decl_stmt|;
name|type
operator|=
operator|(
name|GType
operator|)
name|sym_iter
operator|->
name|data
expr_stmt|;
name|klass
operator|=
name|g_type_class_ref
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|gtk_list_store_prepend
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|klass
operator|->
name|label
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
name|sym_iter
operator|->
name|data
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|klass
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|syms
argument_list|)
expr_stmt|;
name|gtk_list_store_prepend
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|_
argument_list|(
literal|"None"
argument_list|)
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
name|G_TYPE_NONE
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|menu
operator|=
name|gimp_prop_int_combo_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"symmetry"
argument_list|,
name|GIMP_INT_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_label
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|editor
operator|->
name|p
operator|->
name|menu
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Symmetry"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|editor
operator|->
name|p
operator|->
name|menu
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|,
name|NULL
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
name|menu
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
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
name|menu
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
name|menu
argument_list|)
expr_stmt|;
comment|/* Connect to symmetry change. */
name|g_signal_connect
argument_list|(
name|image
argument_list|,
literal|"notify::symmetry"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_symmetry_editor_symmetry_notify
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
comment|/* Update the symmetry options. */
name|symmetry
operator|=
name|gimp_image_symmetry_selected
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_symmetry_editor_set_options
argument_list|(
name|editor
argument_list|,
name|symmetry
argument_list|)
expr_stmt|;
name|editor
operator|->
name|p
operator|->
name|image
operator|=
name|g_object_ref
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|guiconfig
operator|->
name|playground_symmetry
condition|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
comment|/* Display a text when the feature is disabled. */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Symmetry Painting is disabled.\n"
literal|"You can enable the feature in the "
literal|"\"Experimental Playground\" section of \"Preferences\"."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
operator|->
name|p
operator|->
name|options_frame
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
name|gtk_widget_show
argument_list|(
name|editor
operator|->
name|p
operator|->
name|options_frame
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_symmetry_editor_symmetry_notify (GimpImage * image,GParamSpec * pspec,GimpSymmetryEditor * editor)
name|gimp_symmetry_editor_symmetry_notify
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpSymmetryEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpSymmetry
modifier|*
name|symmetry
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|image
operator|&&
operator|(
name|symmetry
operator|=
name|gimp_image_symmetry_selected
argument_list|(
name|image
argument_list|)
operator|)
condition|)
block|{
name|g_signal_connect
argument_list|(
name|symmetry
argument_list|,
literal|"update-ui"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_symmetry_editor_symmetry_updated
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
name|gimp_symmetry_editor_set_options
argument_list|(
name|editor
argument_list|,
name|symmetry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_symmetry_editor_symmetry_updated (GimpSymmetry * symmetry,GimpImage * image,GimpSymmetryEditor * editor)
name|gimp_symmetry_editor_symmetry_updated
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSymmetryEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SYMMETRY
argument_list|(
name|symmetry
argument_list|)
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|image
operator|!=
name|context
operator|->
name|image
operator|||
name|symmetry
operator|!=
name|gimp_image_symmetry_selected
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|symmetry
argument_list|)
argument_list|,
name|gimp_symmetry_editor_symmetry_updated
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_symmetry_editor_set_options
argument_list|(
name|editor
argument_list|,
name|symmetry
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_symmetry_editor_set_options (GimpSymmetryEditor * editor,GimpSymmetry * symmetry)
name|gimp_symmetry_editor_set_options
parameter_list|(
name|GimpSymmetryEditor
modifier|*
name|editor
parameter_list|,
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|)
block|{
name|GimpSymmetryClass
modifier|*
name|klass
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GParamSpec
modifier|*
modifier|*
name|specs
decl_stmt|;
name|gint
name|n_properties
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|frame
operator|=
name|editor
operator|->
name|p
operator|->
name|options_frame
expr_stmt|;
comment|/* Clean the old frame */
name|gtk_widget_hide
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_container_foreach
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
operator|(
name|GtkCallback
operator|)
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|symmetry
operator|||
name|symmetry
operator|->
name|type
operator|==
name|GIMP_TYPE_SYMMETRY
condition|)
return|return;
name|klass
operator|=
name|g_type_class_ref
argument_list|(
name|symmetry
operator|->
name|type
argument_list|)
expr_stmt|;
name|gtk_frame_set_label
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|klass
operator|->
name|label
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
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
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|specs
operator|=
name|gimp_symmetry_get_settings
argument_list|(
name|symmetry
argument_list|,
operator|&
name|n_properties
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
name|n_properties
condition|;
name|i
operator|++
control|)
block|{
name|GParamSpec
modifier|*
name|spec
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|blurb
decl_stmt|;
if|if
condition|(
name|specs
index|[
name|i
index|]
operator|==
name|NULL
condition|)
block|{
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
name|separator
operator|=
name|gtk_hseparator_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|separator
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
name|separator
argument_list|)
expr_stmt|;
continue|continue;
block|}
name|spec
operator|=
name|G_PARAM_SPEC
argument_list|(
name|specs
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_param_spec_get_name
argument_list|(
name|spec
argument_list|)
expr_stmt|;
name|blurb
operator|=
name|g_param_spec_get_blurb
argument_list|(
name|spec
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|spec
operator|->
name|value_type
condition|)
block|{
case|case
name|G_TYPE_BOOLEAN
case|:
block|{
name|GtkWidget
modifier|*
name|checkbox
decl_stmt|;
name|checkbox
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|symmetry
argument_list|)
argument_list|,
name|name
argument_list|,
name|blurb
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|checkbox
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
name|checkbox
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|G_TYPE_DOUBLE
case|:
case|case
name|G_TYPE_INT
case|:
case|case
name|G_TYPE_UINT
case|:
block|{
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|gdouble
name|minimum
decl_stmt|;
name|gdouble
name|maximum
decl_stmt|;
if|if
condition|(
name|spec
operator|->
name|value_type
operator|==
name|G_TYPE_DOUBLE
condition|)
block|{
name|minimum
operator|=
name|G_PARAM_SPEC_DOUBLE
argument_list|(
name|spec
argument_list|)
operator|->
name|minimum
expr_stmt|;
name|maximum
operator|=
name|G_PARAM_SPEC_DOUBLE
argument_list|(
name|spec
argument_list|)
operator|->
name|maximum
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|spec
operator|->
name|value_type
operator|==
name|G_TYPE_INT
condition|)
block|{
name|minimum
operator|=
name|G_PARAM_SPEC_INT
argument_list|(
name|spec
argument_list|)
operator|->
name|minimum
expr_stmt|;
name|maximum
operator|=
name|G_PARAM_SPEC_INT
argument_list|(
name|spec
argument_list|)
operator|->
name|maximum
expr_stmt|;
block|}
else|else
block|{
name|minimum
operator|=
name|G_PARAM_SPEC_UINT
argument_list|(
name|spec
argument_list|)
operator|->
name|minimum
expr_stmt|;
name|maximum
operator|=
name|G_PARAM_SPEC_UINT
argument_list|(
name|spec
argument_list|)
operator|->
name|maximum
expr_stmt|;
block|}
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|G_OBJECT
argument_list|(
name|symmetry
argument_list|)
argument_list|,
name|name
argument_list|,
name|blurb
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_spin_scale_set_scale_limits
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|minimum
argument_list|,
name|maximum
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
comment|/* Type of parameter we haven't handled yet. */
continue|continue;
block|}
block|}
name|g_free
argument_list|(
name|specs
argument_list|)
expr_stmt|;
comment|/* Finally show the frame. */
name|gtk_widget_show
argument_list|(
name|frame
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
DECL|function|gimp_symmetry_editor_new (Gimp * gimp,GimpImage * image,GimpMenuFactory * menu_factory)
name|gimp_symmetry_editor_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GimpSymmetryEditor
modifier|*
name|editor
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
name|g_return_val_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_SYMMETRY_EDITOR
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
return|;
block|}
end_function

end_unit

