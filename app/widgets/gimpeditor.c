begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpeditor.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpenummenu.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_define
DECL|macro|DEFAULT_CONTENT_SPACING
define|#
directive|define
name|DEFAULT_CONTENT_SPACING
value|2
end_define

begin_define
DECL|macro|DEFAULT_BUTTON_SPACING
define|#
directive|define
name|DEFAULT_BUTTON_SPACING
value|2
end_define

begin_define
DECL|macro|DEFAULT_BUTTON_ICON_SIZE
define|#
directive|define
name|DEFAULT_BUTTON_ICON_SIZE
value|GTK_ICON_SIZE_MENU
end_define

begin_function_decl
specifier|static
name|void
name|gimp_editor_class_init
parameter_list|(
name|GimpEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_editor_init
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_editor_destroy
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
name|gimp_editor_style_set
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
name|GimpItemFactory
modifier|*
name|gimp_editor_get_menu
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|gpointer
modifier|*
name|item_factory_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkIconSize
name|gimp_editor_ensure_button_box
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkVBoxClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_editor_get_type (void)
name|gimp_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
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
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpEditorClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_editor_init
block|,       }
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|docked_iface_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_editor_docked_iface_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_VBOX
argument_list|,
literal|"GimpEditor"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_DOCKED
argument_list|,
operator|&
name|docked_iface_info
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
DECL|function|gimp_editor_class_init (GimpEditorClass * klass)
name|gimp_editor_class_init
parameter_list|(
name|GimpEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_editor_destroy
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_editor_style_set
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"content_spacing"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_CONTENT_SPACING
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"button_spacing"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_BUTTON_SPACING
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"button_icon_size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_TYPE_ICON_SIZE
argument_list|,
name|DEFAULT_BUTTON_ICON_SIZE
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_editor_init (GimpEditor * editor)
name|gimp_editor_init
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|)
block|{
name|editor
operator|->
name|menu_factory
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|item_factory
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|item_factory_data
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|button_box
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_editor_docked_iface_init (GimpDockedInterface * docked_iface)
name|gimp_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
block|{
name|docked_iface
operator|->
name|get_menu
operator|=
name|gimp_editor_get_menu
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_editor_destroy (GtkObject * object)
name|gimp_editor_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|GIMP_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|item_factory
condition|)
block|{
name|g_object_unref
argument_list|(
name|editor
operator|->
name|item_factory
argument_list|)
expr_stmt|;
name|editor
operator|->
name|item_factory
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
DECL|function|gimp_editor_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_editor_style_set
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
name|GimpEditor
modifier|*
name|editor
decl_stmt|;
name|GtkIconSize
name|button_icon_size
decl_stmt|;
name|gint
name|button_spacing
decl_stmt|;
name|gint
name|content_spacing
decl_stmt|;
name|editor
operator|=
name|GIMP_EDITOR
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"button_icon_size"
argument_list|,
operator|&
name|button_icon_size
argument_list|,
literal|"button_spacing"
argument_list|,
operator|&
name|button_spacing
argument_list|,
literal|"content_spacing"
argument_list|,
operator|&
name|content_spacing
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
name|content_spacing
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|button_box
condition|)
block|{
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|button_box
argument_list|)
argument_list|,
name|button_spacing
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
operator|->
name|button_box
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
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
name|GtkBin
modifier|*
name|bin
decl_stmt|;
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|bin
operator|=
name|GTK_BIN
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gtk_image_get_stock
argument_list|(
name|GTK_IMAGE
argument_list|(
name|bin
operator|->
name|child
argument_list|)
argument_list|,
operator|&
name|stock_id
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_image_set_from_stock
argument_list|(
name|GTK_IMAGE
argument_list|(
name|bin
operator|->
name|child
argument_list|)
argument_list|,
name|stock_id
argument_list|,
name|button_icon_size
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
condition|)
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
block|}
end_function

begin_function
specifier|static
name|GimpItemFactory
modifier|*
DECL|function|gimp_editor_get_menu (GimpDocked * docked,gpointer * item_factory_data)
name|gimp_editor_get_menu
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|gpointer
modifier|*
name|item_factory_data
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
operator|*
name|item_factory_data
operator|=
name|editor
operator|->
name|item_factory_data
expr_stmt|;
return|return
name|editor
operator|->
name|item_factory
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_editor_new (void)
name|gimp_editor_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_EDITOR
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

begin_function
name|void
DECL|function|gimp_editor_create_menu (GimpEditor * editor,GimpMenuFactory * menu_factory,const gchar * menu_identifier,gpointer callback_data)
name|gimp_editor_create_menu
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_identifier
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|menu_identifier
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|item_factory
condition|)
name|g_object_unref
argument_list|(
name|editor
operator|->
name|item_factory
argument_list|)
expr_stmt|;
name|editor
operator|->
name|menu_factory
operator|=
name|menu_factory
expr_stmt|;
name|editor
operator|->
name|item_factory
operator|=
name|gimp_menu_factory_menu_new
argument_list|(
name|menu_factory
argument_list|,
name|menu_identifier
argument_list|,
name|GTK_TYPE_MENU
argument_list|,
name|callback_data
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|editor
operator|->
name|item_factory_data
operator|=
name|callback_data
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_editor_add_button (GimpEditor * editor,const gchar * stock_id,const gchar * tooltip,const gchar * help_id,GCallback callback,GCallback extended_callback,gpointer callback_data)
name|gimp_editor_add_button
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|GCallback
name|extended_callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|GtkIconSize
name|button_icon_size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|stock_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button_icon_size
operator|=
name|gimp_editor_ensure_button_box
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_button_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|button_box
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
if|if
condition|(
name|tooltip
operator|||
name|help_id
condition|)
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|tooltip
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|extended_callback
condition|)
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"extended_clicked"
argument_list|,
name|extended_callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|stock_id
argument_list|,
name|button_icon_size
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
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
return|return
name|button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_editor_add_stock_box (GimpEditor * editor,GType enum_type,const gchar * stock_prefix,GCallback callback,gpointer callback_data)
name|gimp_editor_add_stock_box
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|,
name|GType
name|enum_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_prefix
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|first_button
decl_stmt|;
name|GtkIconSize
name|button_icon_size
decl_stmt|;
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|enum_type
argument_list|,
name|G_TYPE_ENUM
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|stock_prefix
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button_icon_size
operator|=
name|gimp_editor_ensure_button_box
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gimp_enum_stock_box_new
argument_list|(
name|enum_type
argument_list|,
name|stock_prefix
argument_list|,
name|button_icon_size
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|,
operator|&
name|first_button
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
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
name|GtkWidget
modifier|*
name|button
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_object_ref
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|button_box
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
return|return
name|first_button
return|;
block|}
end_function

begin_function
specifier|static
name|GtkIconSize
DECL|function|gimp_editor_ensure_button_box (GimpEditor * editor)
name|gimp_editor_ensure_button_box
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkIconSize
name|button_icon_size
decl_stmt|;
name|gint
name|button_spacing
decl_stmt|;
name|gtk_widget_style_get
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"button_icon_size"
argument_list|,
operator|&
name|button_icon_size
argument_list|,
literal|"button_spacing"
argument_list|,
operator|&
name|button_spacing
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|editor
operator|->
name|button_box
condition|)
block|{
name|editor
operator|->
name|button_box
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
name|button_spacing
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|editor
operator|->
name|button_box
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
name|button_box
argument_list|)
expr_stmt|;
block|}
return|return
name|button_icon_size
return|;
block|}
end_function

end_unit

