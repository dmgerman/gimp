begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpiconpicker.c  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptemplate.h"
end_include

begin_include
include|#
directive|include
file|"gimpiconpicker.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewablebutton.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28be146a0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|,
DECL|enumerator|PROP_STOCK_ID
name|PROP_STOCK_ID
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpIconPickerPrivate
typedef|typedef
name|struct
name|_GimpIconPickerPrivate
name|GimpIconPickerPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpIconPickerPrivate
struct|struct
name|_GimpIconPickerPrivate
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|stock_id
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|stock_id_container
name|GimpContainer
modifier|*
name|stock_id_container
decl_stmt|;
DECL|member|stock_id_context
name|GimpContext
modifier|*
name|stock_id_context
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (picker)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|picker
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (picker, \                                      GIMP_TYPE_ICON_PICKER, \                                      GimpIconPickerPrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_icon_picker_constructed
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
name|gimp_icon_picker_finalize
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
name|gimp_icon_picker_set_property
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
name|gimp_icon_picker_get_property
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
name|gimp_icon_picker_icon_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GimpIconPicker
modifier|*
name|picker
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpIconPicker,gimp_icon_picker,GTK_TYPE_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpIconPicker
argument_list|,
argument|gimp_icon_picker
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_icon_picker_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_icon_picker_class_init
parameter_list|(
name|GimpIconPickerClass
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
name|gimp_icon_picker_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_icon_picker_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_icon_picker_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_icon_picker_get_property
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
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_STOCK_ID
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"stock-id"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"gimp-toilet-paper"
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpIconPickerPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_icon_picker_init (GimpIconPicker * picker)
name|gimp_icon_picker_init
parameter_list|(
name|GimpIconPicker
modifier|*
name|picker
parameter_list|)
block|{
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|picker
argument_list|)
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_icon_picker_constructed (GObject * object)
name|gimp_icon_picker_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpIconPicker
modifier|*
name|picker
init|=
name|GIMP_ICON_PICKER
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpIconPickerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GSList
modifier|*
name|stock_list
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
condition|)
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
name|GIMP_IS_GIMP
argument_list|(
name|private
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|stock_id_container
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_TEMPLATE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|private
operator|->
name|stock_id_context
operator|=
name|gimp_context_new
argument_list|(
name|private
operator|->
name|gimp
argument_list|,
literal|"foo"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|stock_id_context
argument_list|,
literal|"template-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_icon_picker_icon_changed
argument_list|)
argument_list|,
name|picker
argument_list|)
expr_stmt|;
name|stock_list
operator|=
name|gtk_stock_list_ids
argument_list|()
expr_stmt|;
for|for
control|(
name|list
operator|=
name|stock_list
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpObject
modifier|*
name|object
init|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEMPLATE
argument_list|,
literal|"name"
argument_list|,
name|list
operator|->
name|data
argument_list|,
literal|"stock-id"
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gimp_container_add
argument_list|(
name|private
operator|->
name|stock_id_container
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|stock_id
operator|&&
name|strcmp
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|private
operator|->
name|stock_id
argument_list|)
operator|==
literal|0
condition|)
name|gimp_context_set_template
argument_list|(
name|private
operator|->
name|stock_id_context
argument_list|,
name|GIMP_TEMPLATE
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_slist_foreach
argument_list|(
name|stock_list
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|stock_list
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_viewable_button_new
argument_list|(
name|private
operator|->
name|stock_id_container
argument_list|,
name|private
operator|->
name|stock_id_context
argument_list|,
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_viewable_button_set_view_type
argument_list|(
name|GIMP_VIEWABLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|GIMP_VIEW_TYPE_GRID
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|picker
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_icon_picker_finalize (GObject * object)
name|gimp_icon_picker_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpIconPickerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|stock_id
condition|)
block|{
name|g_free
argument_list|(
name|private
operator|->
name|stock_id
argument_list|)
expr_stmt|;
name|private
operator|->
name|stock_id
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|private
operator|->
name|stock_id_container
condition|)
block|{
name|g_object_unref
argument_list|(
name|private
operator|->
name|stock_id_container
argument_list|)
expr_stmt|;
name|private
operator|->
name|stock_id_container
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|private
operator|->
name|stock_id_context
condition|)
block|{
name|g_object_unref
argument_list|(
name|private
operator|->
name|stock_id_context
argument_list|)
expr_stmt|;
name|private
operator|->
name|stock_id_context
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_icon_picker_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_icon_picker_set_property
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
name|GimpIconPickerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
case|case
name|PROP_STOCK_ID
case|:
name|gimp_icon_picker_set_stock_id
argument_list|(
name|GIMP_ICON_PICKER
argument_list|(
name|object
argument_list|)
argument_list|,
name|g_value_get_string
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
DECL|function|gimp_icon_picker_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_icon_picker_get_property
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
name|GimpIconPickerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
case|case
name|PROP_STOCK_ID
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|stock_id
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
name|GtkWidget
modifier|*
DECL|function|gimp_icon_picker_new (Gimp * gimp)
name|gimp_icon_picker_new
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
name|GIMP_TYPE_ICON_PICKER
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
specifier|const
name|gchar
modifier|*
DECL|function|gimp_icon_picker_get_stock_id (GimpIconPicker * picker)
name|gimp_icon_picker_get_stock_id
parameter_list|(
name|GimpIconPicker
modifier|*
name|picker
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ICON_PICKER
argument_list|(
name|picker
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|picker
argument_list|)
operator|->
name|stock_id
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_icon_picker_set_stock_id (GimpIconPicker * picker,const gchar * stock_id)
name|gimp_icon_picker_set_stock_id
parameter_list|(
name|GimpIconPicker
modifier|*
name|picker
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
name|GimpIconPickerPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ICON_PICKER
argument_list|(
name|picker
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|stock_id
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|picker
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|private
operator|->
name|stock_id
argument_list|)
expr_stmt|;
name|private
operator|->
name|stock_id
operator|=
name|g_strdup
argument_list|(
name|stock_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|stock_id_container
condition|)
block|{
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|gimp_container_get_child_by_name
argument_list|(
name|private
operator|->
name|stock_id_container
argument_list|,
name|stock_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
condition|)
name|gimp_context_set_template
argument_list|(
name|private
operator|->
name|stock_id_context
argument_list|,
name|GIMP_TEMPLATE
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|picker
argument_list|)
argument_list|,
literal|"stock-id"
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
DECL|function|gimp_icon_picker_icon_changed (GimpContext * context,GimpTemplate * template,GimpIconPicker * picker)
name|gimp_icon_picker_icon_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GimpIconPicker
modifier|*
name|picker
parameter_list|)
block|{
name|gimp_icon_picker_set_stock_id
argument_list|(
name|picker
argument_list|,
name|gimp_object_get_name
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

