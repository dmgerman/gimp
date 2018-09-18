begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball  *  * gimplayermodecombobox.c  * Copyright (C) 2017  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gegl.h>
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
file|"operations/layer-modes/gimp-layer-modes.h"
end_include

begin_include
include|#
directive|include
file|"gimplayermodecombobox.h"
end_include

begin_comment
comment|/**  * SECTION: gimplayermodecombobox  * @title: GimpLayerModeComboBox  * @short_description: A #GimpEnumComboBox subclass for selecting a layer mode.  *  * A #GtkComboBox subclass for selecting a layer mode  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon28f5e7720103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_LAYER_MODE
name|PROP_LAYER_MODE
block|,
DECL|enumerator|PROP_GROUP
name|PROP_GROUP
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpLayerModeComboBoxPrivate
struct|struct
name|_GimpLayerModeComboBoxPrivate
block|{
DECL|member|context
name|GimpLayerModeContext
name|context
decl_stmt|;
DECL|member|layer_mode
name|GimpLayerMode
name|layer_mode
decl_stmt|;
DECL|member|group
name|GimpLayerModeGroup
name|group
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_layer_mode_combo_box_constructed
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
name|gimp_layer_mode_combo_box_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|gimp_layer_mode_combo_box_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|gimp_layer_mode_combo_box_changed
parameter_list|(
name|GtkComboBox
modifier|*
name|gtk_combo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_mode_combo_box_update_model
parameter_list|(
name|GimpLayerModeComboBox
modifier|*
name|combo
parameter_list|,
name|gboolean
name|change_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_layer_mode_combo_box_separator_func
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpLayerModeComboBox,gimp_layer_mode_combo_box,GIMP_TYPE_ENUM_COMBO_BOX)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpLayerModeComboBox
argument_list|,
argument|gimp_layer_mode_combo_box
argument_list|,
argument|GIMP_TYPE_ENUM_COMBO_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_layer_mode_combo_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_layer_mode_combo_box_class_init
parameter_list|(
name|GimpLayerModeComboBoxClass
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
name|GtkComboBoxClass
modifier|*
name|combo_class
init|=
name|GTK_COMBO_BOX_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_layer_mode_combo_box_constructed
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_layer_mode_combo_box_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_layer_mode_combo_box_get_property
expr_stmt|;
name|combo_class
operator|->
name|changed
operator|=
name|gimp_layer_mode_combo_box_changed
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTEXT
argument_list|,
name|g_param_spec_flags
argument_list|(
literal|"context"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_LAYER_MODE_CONTEXT
argument_list|,
name|GIMP_LAYER_MODE_CONTEXT_ALL
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
name|PROP_LAYER_MODE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"layer-mode"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_LAYER_MODE
argument_list|,
name|GIMP_LAYER_MODE_NORMAL
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
name|PROP_GROUP
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"group"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_LAYER_MODE_GROUP
argument_list|,
name|GIMP_LAYER_MODE_GROUP_DEFAULT
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_mode_combo_box_init (GimpLayerModeComboBox * combo)
name|gimp_layer_mode_combo_box_init
parameter_list|(
name|GimpLayerModeComboBox
modifier|*
name|combo
parameter_list|)
block|{
name|combo
operator|->
name|priv
operator|=
name|gimp_layer_mode_combo_box_get_instance_private
argument_list|(
name|combo
argument_list|)
expr_stmt|;
name|gtk_combo_box_set_row_separator_func
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|gimp_layer_mode_combo_box_separator_func
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_LAYER_MODE_SEPARATOR
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_mode_combo_box_constructed (GObject * object)
name|gimp_layer_mode_combo_box_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpLayerModeComboBox
modifier|*
name|combo
init|=
name|GIMP_LAYER_MODE_COMBO_BOX
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
name|gimp_layer_mode_combo_box_update_model
argument_list|(
name|combo
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|combo
operator|->
name|priv
operator|->
name|layer_mode
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_mode_combo_box_set_property (GObject * object,guint prop_id,const GValue * value,GParamSpec * pspec)
name|gimp_layer_mode_combo_box_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GimpLayerModeComboBox
modifier|*
name|combo
init|=
name|GIMP_LAYER_MODE_COMBO_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|prop_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
name|gimp_layer_mode_combo_box_set_context
argument_list|(
name|combo
argument_list|,
name|g_value_get_flags
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LAYER_MODE
case|:
name|gimp_layer_mode_combo_box_set_mode
argument_list|(
name|combo
argument_list|,
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GROUP
case|:
name|gimp_layer_mode_combo_box_set_group
argument_list|(
name|combo
argument_list|,
name|g_value_get_enum
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
name|prop_id
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
DECL|function|gimp_layer_mode_combo_box_get_property (GObject * object,guint prop_id,GValue * value,GParamSpec * pspec)
name|gimp_layer_mode_combo_box_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GimpLayerModeComboBox
modifier|*
name|combo
init|=
name|GIMP_LAYER_MODE_COMBO_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|prop_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
name|g_value_set_flags
argument_list|(
name|value
argument_list|,
name|combo
operator|->
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LAYER_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|combo
operator|->
name|priv
operator|->
name|layer_mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GROUP
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|combo
operator|->
name|priv
operator|->
name|group
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|prop_id
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
DECL|function|gimp_layer_mode_combo_box_changed (GtkComboBox * gtk_combo)
name|gimp_layer_mode_combo_box_changed
parameter_list|(
name|GtkComboBox
modifier|*
name|gtk_combo
parameter_list|)
block|{
name|GimpLayerModeComboBox
modifier|*
name|combo
init|=
name|GIMP_LAYER_MODE_COMBO_BOX
argument_list|(
name|gtk_combo
argument_list|)
decl_stmt|;
name|GimpLayerMode
name|mode
decl_stmt|;
if|if
condition|(
name|gimp_int_combo_box_get_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
operator|(
name|gint
operator|*
operator|)
operator|&
name|mode
argument_list|)
condition|)
block|{
name|combo
operator|->
name|priv
operator|->
name|layer_mode
operator|=
name|mode
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|combo
argument_list|)
argument_list|,
literal|"layer-mode"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_layer_mode_combo_box_new:  * Foo.  *  * Return value: a new #GimpLayerModeComboBox.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_layer_mode_combo_box_new (GimpLayerModeContext context)
name|gimp_layer_mode_combo_box_new
parameter_list|(
name|GimpLayerModeContext
name|context
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_LAYER_MODE_COMBO_BOX
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_layer_mode_combo_box_set_context (GimpLayerModeComboBox * combo,GimpLayerModeContext context)
name|gimp_layer_mode_combo_box_set_context
parameter_list|(
name|GimpLayerModeComboBox
modifier|*
name|combo
parameter_list|,
name|GimpLayerModeContext
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER_MODE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
operator|!=
name|combo
operator|->
name|priv
operator|->
name|context
condition|)
block|{
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
name|combo
operator|->
name|priv
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|combo
argument_list|)
argument_list|,
literal|"context"
argument_list|)
expr_stmt|;
name|gimp_layer_mode_combo_box_update_model
argument_list|(
name|combo
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpLayerModeContext
DECL|function|gimp_layer_mode_combo_box_get_context (GimpLayerModeComboBox * combo)
name|gimp_layer_mode_combo_box_get_context
parameter_list|(
name|GimpLayerModeComboBox
modifier|*
name|combo
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER_MODE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_CONTEXT_ALL
argument_list|)
expr_stmt|;
return|return
name|combo
operator|->
name|priv
operator|->
name|context
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_layer_mode_combo_box_set_mode (GimpLayerModeComboBox * combo,GimpLayerMode mode)
name|gimp_layer_mode_combo_box_set_mode
parameter_list|(
name|GimpLayerModeComboBox
modifier|*
name|combo
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER_MODE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_layer_mode_get_context
argument_list|(
name|mode
argument_list|)
operator|&
name|combo
operator|->
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|mode
operator|!=
name|combo
operator|->
name|priv
operator|->
name|layer_mode
condition|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|dummy
decl_stmt|;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_int_store_lookup_by_value
argument_list|(
name|model
argument_list|,
name|mode
argument_list|,
operator|&
name|dummy
argument_list|)
condition|)
block|{
name|combo
operator|->
name|priv
operator|->
name|group
operator|=
name|gimp_layer_mode_get_group
argument_list|(
name|mode
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|combo
argument_list|)
argument_list|,
literal|"group"
argument_list|)
expr_stmt|;
name|gimp_layer_mode_combo_box_update_model
argument_list|(
name|combo
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpLayerMode
DECL|function|gimp_layer_mode_combo_box_get_mode (GimpLayerModeComboBox * combo)
name|gimp_layer_mode_combo_box_get_mode
parameter_list|(
name|GimpLayerModeComboBox
modifier|*
name|combo
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER_MODE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_NORMAL
argument_list|)
expr_stmt|;
return|return
name|combo
operator|->
name|priv
operator|->
name|layer_mode
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_layer_mode_combo_box_set_group (GimpLayerModeComboBox * combo,GimpLayerModeGroup group)
name|gimp_layer_mode_combo_box_set_group
parameter_list|(
name|GimpLayerModeComboBox
modifier|*
name|combo
parameter_list|,
name|GimpLayerModeGroup
name|group
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER_MODE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|group
operator|!=
name|combo
operator|->
name|priv
operator|->
name|group
condition|)
block|{
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
name|combo
operator|->
name|priv
operator|->
name|group
operator|=
name|group
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|combo
argument_list|)
argument_list|,
literal|"group"
argument_list|)
expr_stmt|;
name|gimp_layer_mode_combo_box_update_model
argument_list|(
name|combo
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpLayerModeGroup
DECL|function|gimp_layer_mode_combo_box_get_group (GimpLayerModeComboBox * combo)
name|gimp_layer_mode_combo_box_get_group
parameter_list|(
name|GimpLayerModeComboBox
modifier|*
name|combo
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER_MODE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_GROUP_DEFAULT
argument_list|)
expr_stmt|;
return|return
name|combo
operator|->
name|priv
operator|->
name|group
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_enum_store_add_value (GtkListStore * store,GEnumClass * enum_class,GEnumValue * value)
name|gimp_enum_store_add_value
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|GEnumClass
modifier|*
name|enum_class
parameter_list|,
name|GEnumValue
modifier|*
name|value
parameter_list|)
block|{
name|GtkTreeIter
name|iter
init|=
block|{
literal|0
block|, }
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|abbrev
decl_stmt|;
name|gchar
modifier|*
name|stripped
decl_stmt|;
name|desc
operator|=
name|gimp_enum_value_get_desc
argument_list|(
name|enum_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|abbrev
operator|=
name|gimp_enum_value_get_abbrev
argument_list|(
name|enum_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
comment|/* no mnemonics in combo boxes */
name|stripped
operator|=
name|gimp_strip_uline
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|gtk_list_store_append
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
name|GIMP_INT_STORE_VALUE
argument_list|,
name|value
operator|->
name|value
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|stripped
argument_list|,
name|GIMP_INT_STORE_ABBREV
argument_list|,
name|abbrev
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stripped
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_store_add_separator (GtkListStore * store)
name|gimp_enum_store_add_separator
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|)
block|{
name|GtkTreeIter
name|iter
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gtk_list_store_append
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
name|GIMP_INT_STORE_VALUE
argument_list|,
name|GIMP_LAYER_MODE_SEPARATOR
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkListStore
modifier|*
DECL|function|gimp_enum_store_new_from_array (GType enum_type,gint n_values,const gint * values,GimpLayerModeContext context)
name|gimp_enum_store_new_from_array
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|n_values
parameter_list|,
specifier|const
name|gint
modifier|*
name|values
parameter_list|,
name|GimpLayerModeContext
name|context
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|value
decl_stmt|;
name|gboolean
name|first_item
init|=
name|TRUE
decl_stmt|;
name|gboolean
name|prepend_separator
init|=
name|FALSE
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_values
operator|>
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_STORE
argument_list|,
literal|"enum-type"
argument_list|,
name|enum_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
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
name|n_values
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|values
index|[
name|i
index|]
operator|!=
name|GIMP_LAYER_MODE_SEPARATOR
condition|)
block|{
if|if
condition|(
name|gimp_layer_mode_get_context
argument_list|(
name|values
index|[
name|i
index|]
argument_list|)
operator|&
name|context
condition|)
block|{
name|value
operator|=
name|g_enum_get_value
argument_list|(
name|enum_class
argument_list|,
name|values
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
block|{
if|if
condition|(
name|prepend_separator
condition|)
block|{
name|gimp_enum_store_add_separator
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|prepend_separator
operator|=
name|FALSE
expr_stmt|;
block|}
name|gimp_enum_store_add_value
argument_list|(
name|store
argument_list|,
name|enum_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|first_item
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
if|if
condition|(
operator|!
name|first_item
condition|)
name|prepend_separator
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
return|return
name|store
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_mode_combo_box_update_model (GimpLayerModeComboBox * combo,gboolean change_mode)
name|gimp_layer_mode_combo_box_update_model
parameter_list|(
name|GimpLayerModeComboBox
modifier|*
name|combo
parameter_list|,
name|gboolean
name|change_mode
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
specifier|const
name|GimpLayerMode
modifier|*
name|modes
decl_stmt|;
name|gint
name|n_modes
decl_stmt|;
name|modes
operator|=
name|gimp_layer_mode_get_group_array
argument_list|(
name|combo
operator|->
name|priv
operator|->
name|group
argument_list|,
operator|&
name|n_modes
argument_list|)
expr_stmt|;
name|store
operator|=
name|gimp_enum_store_new_from_array
argument_list|(
name|GIMP_TYPE_LAYER_MODE
argument_list|,
name|n_modes
argument_list|,
operator|(
name|gint
operator|*
operator|)
name|modes
argument_list|,
name|combo
operator|->
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
name|gtk_combo_box_set_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|GTK_TREE_MODEL
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
if|if
condition|(
name|change_mode
condition|)
block|{
name|GimpLayerMode
name|new_mode
decl_stmt|;
if|if
condition|(
name|gimp_layer_mode_get_for_group
argument_list|(
name|combo
operator|->
name|priv
operator|->
name|layer_mode
argument_list|,
name|combo
operator|->
name|priv
operator|->
name|group
argument_list|,
operator|&
name|new_mode
argument_list|)
operator|&&
operator|(
name|gimp_layer_mode_get_context
argument_list|(
name|new_mode
argument_list|)
operator|&
name|combo
operator|->
name|priv
operator|->
name|context
operator|)
condition|)
block|{
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|new_mode
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
comment|/*  switch to the first mode, which will be one of the "normal"  */
name|gtk_tree_model_get_iter_first
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_combo_box_set_active_iter
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_layer_mode_combo_box_separator_func (GtkTreeModel * model,GtkTreeIter * iter,gpointer data)
name|gimp_layer_mode_combo_box_separator_func
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
name|value
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
operator|&
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|value
operator|==
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
return|;
block|}
end_function

end_unit

