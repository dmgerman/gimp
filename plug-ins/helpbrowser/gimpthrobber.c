begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpThrobber  * Copyright (C) 2005  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpthrobber.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a2125850103
block|{
DECL|enumerator|CLICKED
name|CLICKED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a2125850203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_STOCK_ID
name|PROP_STOCK_ID
block|,
DECL|enumerator|PROP_IMAGE
name|PROP_IMAGE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_throbber_class_init
parameter_list|(
name|GimpThrobberClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_throbber_init
parameter_list|(
name|GimpThrobber
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_throbber_set_property
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
name|gimp_throbber_get_property
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
name|gimp_throbber_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_throbber_create_menu_proxy
parameter_list|(
name|GtkToolItem
modifier|*
name|tool_item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_throbber_toolbar_reconfigured
parameter_list|(
name|GtkToolItem
modifier|*
name|tool_item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_throbber_button_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpThrobber
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_throbber_construct_contents
parameter_list|(
name|GtkToolItem
modifier|*
name|tool_item
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|toolbutton_signals
specifier|static
name|guint
name|toolbutton_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|GIMP_THROBBER_GET_PRIVATE (obj)
define|#
directive|define
name|GIMP_THROBBER_GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_PRIVATE ((obj), GIMP_TYPE_THROBBER, GimpThrobberPrivate))
end_define

begin_struct
DECL|struct|_GimpThrobberPrivate
struct|struct
name|_GimpThrobberPrivate
block|{
DECL|member|button
name|GtkWidget
modifier|*
name|button
decl_stmt|;
DECL|member|image
name|GtkWidget
modifier|*
name|image
decl_stmt|;
DECL|member|stock_id
name|gchar
modifier|*
name|stock_id
decl_stmt|;
block|}
struct|;
end_struct

begin_function
name|GType
DECL|function|gimp_throbber_get_type (void)
name|gimp_throbber_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpThrobberClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_throbber_class_init
block|,
operator|(
name|GClassFinalizeFunc
operator|)
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpThrobber
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_throbber_init
block|,         }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_TOOL_ITEM
argument_list|,
literal|"GimpThrobber"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_throbber_class_init (GimpThrobberClass * klass)
name|gimp_throbber_class_init
parameter_list|(
name|GimpThrobberClass
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
name|GtkToolItemClass
modifier|*
name|tool_item_class
init|=
name|GTK_TOOL_ITEM_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_throbber_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_throbber_get_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_throbber_finalize
expr_stmt|;
name|tool_item_class
operator|->
name|create_menu_proxy
operator|=
name|gimp_throbber_create_menu_proxy
expr_stmt|;
name|tool_item_class
operator|->
name|toolbar_reconfigured
operator|=
name|gimp_throbber_toolbar_reconfigured
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
name|NULL
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"image"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_TYPE_IMAGE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|toolbutton_signals
index|[
name|CLICKED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"clicked"
argument_list|,
name|G_OBJECT_CLASS_TYPE
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpThrobberClass
argument_list|,
name|clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpThrobberPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_throbber_init (GimpThrobber * button)
name|gimp_throbber_init
parameter_list|(
name|GimpThrobber
modifier|*
name|button
parameter_list|)
block|{
name|GtkToolItem
modifier|*
name|toolitem
init|=
name|GTK_TOOL_ITEM
argument_list|(
name|button
argument_list|)
decl_stmt|;
name|button
operator|->
name|priv
operator|=
name|GIMP_THROBBER_GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_tool_item_set_homogeneous
argument_list|(
name|toolitem
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|button
operator|->
name|priv
operator|->
name|button
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_BUTTON
argument_list|,
literal|"yalign"
argument_list|,
literal|0.0
argument_list|,
literal|"focus-on-click"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|button
operator|->
name|priv
operator|->
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_throbber_button_clicked
argument_list|)
argument_list|,
name|button
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|button
operator|->
name|priv
operator|->
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
operator|->
name|priv
operator|->
name|button
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_throbber_construct_contents (GtkToolItem * tool_item)
name|gimp_throbber_construct_contents
parameter_list|(
name|GtkToolItem
modifier|*
name|tool_item
parameter_list|)
block|{
name|GimpThrobber
modifier|*
name|button
init|=
name|GIMP_THROBBER
argument_list|(
name|tool_item
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|image
operator|&&
name|button
operator|->
name|priv
operator|->
name|image
operator|->
name|parent
condition|)
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
operator|->
name|priv
operator|->
name|image
operator|->
name|parent
argument_list|)
argument_list|,
name|button
operator|->
name|priv
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_BIN
argument_list|(
name|button
operator|->
name|priv
operator|->
name|button
argument_list|)
operator|->
name|child
condition|)
name|gtk_widget_destroy
argument_list|(
name|GTK_BIN
argument_list|(
name|button
operator|->
name|priv
operator|->
name|button
argument_list|)
operator|->
name|child
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tool_item_get_toolbar_style
argument_list|(
name|tool_item
argument_list|)
operator|==
name|GTK_TOOLBAR_TEXT
condition|)
block|{
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|button
operator|->
name|priv
operator|->
name|stock_id
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|image
condition|)
block|{
name|image
operator|=
name|button
operator|->
name|priv
operator|->
name|image
expr_stmt|;
block|}
else|else
block|{
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|button
operator|->
name|priv
operator|->
name|stock_id
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
block|}
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
operator|->
name|priv
operator|->
name|button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gtk_button_set_relief
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
operator|->
name|priv
operator|->
name|button
argument_list|)
argument_list|,
name|gtk_tool_item_get_relief_style
argument_list|(
name|tool_item
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_queue_resize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_throbber_set_property (GObject * object,guint prop_id,const GValue * value,GParamSpec * pspec)
name|gimp_throbber_set_property
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
name|GimpThrobber
modifier|*
name|button
init|=
name|GIMP_THROBBER
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
name|PROP_STOCK_ID
case|:
name|gimp_throbber_set_stock_id
argument_list|(
name|button
argument_list|,
name|g_value_get_string
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE
case|:
name|gimp_throbber_set_image
argument_list|(
name|button
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
DECL|function|gimp_throbber_get_property (GObject * object,guint prop_id,GValue * value,GParamSpec * pspec)
name|gimp_throbber_get_property
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
name|GimpThrobber
modifier|*
name|button
init|=
name|GIMP_THROBBER
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
name|PROP_STOCK_ID
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|button
operator|->
name|priv
operator|->
name|stock_id
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|button
operator|->
name|priv
operator|->
name|image
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
DECL|function|gimp_throbber_finalize (GObject * object)
name|gimp_throbber_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpThrobber
modifier|*
name|button
init|=
name|GIMP_THROBBER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|stock_id
condition|)
name|g_free
argument_list|(
name|button
operator|->
name|priv
operator|->
name|stock_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|image
condition|)
name|g_object_unref
argument_list|(
name|button
operator|->
name|priv
operator|->
name|image
argument_list|)
expr_stmt|;
name|parent_class
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
DECL|function|gimp_throbber_button_clicked (GtkWidget * widget,GimpThrobber * button)
name|gimp_throbber_button_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpThrobber
modifier|*
name|button
parameter_list|)
block|{
name|g_signal_emit_by_name
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_throbber_create_menu_proxy (GtkToolItem * tool_item)
name|gimp_throbber_create_menu_proxy
parameter_list|(
name|GtkToolItem
modifier|*
name|tool_item
parameter_list|)
block|{
name|gtk_tool_item_set_proxy_menu_item
argument_list|(
name|tool_item
argument_list|,
literal|"gimp-throbber-menu-id"
argument_list|,
name|NULL
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
DECL|function|gimp_throbber_toolbar_reconfigured (GtkToolItem * tool_item)
name|gimp_throbber_toolbar_reconfigured
parameter_list|(
name|GtkToolItem
modifier|*
name|tool_item
parameter_list|)
block|{
name|gimp_throbber_construct_contents
argument_list|(
name|tool_item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkToolItem
modifier|*
DECL|function|gimp_throbber_new (const gchar * stock_id)
name|gimp_throbber_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_THROBBER
argument_list|,
literal|"stock-id"
argument_list|,
name|stock_id
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_throbber_set_stock_id (GimpThrobber * button,const gchar * stock_id)
name|gimp_throbber_set_stock_id
parameter_list|(
name|GimpThrobber
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
name|gchar
modifier|*
name|old_stock_id
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_THROBBER
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|old_stock_id
operator|=
name|button
operator|->
name|priv
operator|->
name|stock_id
expr_stmt|;
name|button
operator|->
name|priv
operator|->
name|stock_id
operator|=
name|g_strdup
argument_list|(
name|stock_id
argument_list|)
expr_stmt|;
name|gimp_throbber_construct_contents
argument_list|(
name|GTK_TOOL_ITEM
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"stock-id"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|old_stock_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_throbber_get_stock_id (GimpThrobber * button)
name|gimp_throbber_get_stock_id
parameter_list|(
name|GimpThrobber
modifier|*
name|button
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_THROBBER
argument_list|(
name|button
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|button
operator|->
name|priv
operator|->
name|stock_id
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_throbber_set_image (GimpThrobber * button,GtkWidget * image)
name|gimp_throbber_set_image
parameter_list|(
name|GimpThrobber
modifier|*
name|button
parameter_list|,
name|GtkWidget
modifier|*
name|image
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_THROBBER
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GTK_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|!=
name|button
operator|->
name|priv
operator|->
name|image
condition|)
block|{
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|image
condition|)
block|{
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|image
operator|->
name|parent
condition|)
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
operator|->
name|priv
operator|->
name|image
operator|->
name|parent
argument_list|)
argument_list|,
name|button
operator|->
name|priv
operator|->
name|image
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|button
operator|->
name|priv
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|image
condition|)
name|g_object_ref_sink
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|button
operator|->
name|priv
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|gimp_throbber_construct_contents
argument_list|(
name|GTK_TOOL_ITEM
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"image"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_throbber_get_image (GimpThrobber * button)
name|gimp_throbber_get_image
parameter_list|(
name|GimpThrobber
modifier|*
name|button
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_THROBBER
argument_list|(
name|button
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|button
operator|->
name|priv
operator|->
name|image
return|;
block|}
end_function

end_unit

