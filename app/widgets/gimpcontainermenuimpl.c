begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainermenuimpl.c  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainermenuimpl.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenuitem.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_impl_class_init
parameter_list|(
name|GimpContainerMenuImplClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_impl_init
parameter_list|(
name|GimpContainerMenuImpl
modifier|*
name|panel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_impl_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|gimp_container_menu_impl_insert_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_impl_remove_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_impl_reorder_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_impl_select_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_impl_clear_items
parameter_list|(
name|GimpContainerMenu
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_impl_set_preview_size
parameter_list|(
name|GimpContainerMenu
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_impl_set_history
parameter_list|(
name|GimpContainerMenu
modifier|*
name|view
parameter_list|,
name|gint
name|history
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_impl_item_selected
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpContainerMenuClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_container_menu_impl_get_type (void)
name|gimp_container_menu_impl_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
name|menu_impl_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|menu_impl_type
condition|)
block|{
name|GtkTypeInfo
name|menu_impl_info
init|=
block|{
literal|"GimpContainerMenuImpl"
block|,
sizeof|sizeof
argument_list|(
name|GimpContainerMenuImpl
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpContainerMenuImplClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_container_menu_impl_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_container_menu_impl_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|menu_impl_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_CONTAINER_MENU
argument_list|,
operator|&
name|menu_impl_info
argument_list|)
expr_stmt|;
block|}
return|return
name|menu_impl_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_impl_class_init (GimpContainerMenuImplClass * klass)
name|gimp_container_menu_impl_class_init
parameter_list|(
name|GimpContainerMenuImplClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpContainerMenuClass
modifier|*
name|container_menu_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|container_menu_class
operator|=
operator|(
name|GimpContainerMenuClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_CONTAINER_MENU
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_container_menu_impl_destroy
expr_stmt|;
name|container_menu_class
operator|->
name|insert_item
operator|=
name|gimp_container_menu_impl_insert_item
expr_stmt|;
name|container_menu_class
operator|->
name|remove_item
operator|=
name|gimp_container_menu_impl_remove_item
expr_stmt|;
name|container_menu_class
operator|->
name|reorder_item
operator|=
name|gimp_container_menu_impl_reorder_item
expr_stmt|;
name|container_menu_class
operator|->
name|select_item
operator|=
name|gimp_container_menu_impl_select_item
expr_stmt|;
name|container_menu_class
operator|->
name|clear_items
operator|=
name|gimp_container_menu_impl_clear_items
expr_stmt|;
name|container_menu_class
operator|->
name|set_preview_size
operator|=
name|gimp_container_menu_impl_set_preview_size
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_impl_init (GimpContainerMenuImpl * menu_impl)
name|gimp_container_menu_impl_init
parameter_list|(
name|GimpContainerMenuImpl
modifier|*
name|menu_impl
parameter_list|)
block|{
name|menu_impl
operator|->
name|empty_item
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_impl_destroy (GtkObject * object)
name|gimp_container_menu_impl_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerMenuImpl
modifier|*
name|menu_impl
decl_stmt|;
name|menu_impl
operator|=
name|GIMP_CONTAINER_MENU_IMPL
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
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
name|GtkWidget
modifier|*
DECL|function|gimp_container_menu_new (GimpContainer * container,GimpContext * context,gint preview_size)
name|gimp_container_menu_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|preview_size
parameter_list|)
block|{
name|GimpContainerMenuImpl
modifier|*
name|menu_impl
decl_stmt|;
name|GimpContainerMenu
modifier|*
name|menu
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|container
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|context
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|preview_size
operator|>
literal|0
operator|&&
name|preview_size
operator|<=
literal|64
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|menu_impl
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_CONTAINER_MENU_IMPL
argument_list|)
expr_stmt|;
name|menu
operator|=
name|GIMP_CONTAINER_MENU
argument_list|(
name|menu_impl
argument_list|)
expr_stmt|;
name|menu
operator|->
name|preview_size
operator|=
name|preview_size
expr_stmt|;
name|menu_impl
operator|->
name|empty_item
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
literal|"(none)"
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|menu_impl
operator|->
name|empty_item
argument_list|,
operator|-
literal|1
argument_list|,
name|preview_size
operator|+
literal|2
operator|*
name|menu_impl
operator|->
name|empty_item
operator|->
name|style
operator|->
name|klass
operator|->
name|ythickness
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|menu_impl
operator|->
name|empty_item
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu_impl
operator|->
name|empty_item
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menu_impl
operator|->
name|empty_item
argument_list|)
expr_stmt|;
if|if
condition|(
name|container
condition|)
name|gimp_container_menu_set_container
argument_list|(
name|menu
argument_list|,
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
condition|)
name|gimp_container_menu_set_context
argument_list|(
name|menu
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|menu_impl
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  GimpContainerMenu methods  */
end_comment

begin_function
specifier|static
name|gpointer
DECL|function|gimp_container_menu_impl_insert_item (GimpContainerMenu * menu,GimpViewable * viewable,gint index)
name|gimp_container_menu_impl_insert_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
name|menu_item
operator|=
name|gimp_menu_item_new
argument_list|(
name|viewable
argument_list|,
name|menu
operator|->
name|preview_size
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_container_menu_impl_item_selected
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|gtk_menu_insert
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menu_item
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu_item
argument_list|)
expr_stmt|;
name|gtk_menu_reorder_child
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|GIMP_CONTAINER_MENU_IMPL
argument_list|(
name|menu
argument_list|)
operator|->
name|empty_item
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_list_length
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
argument_list|)
operator|==
literal|2
condition|)
name|gtk_widget_hide
argument_list|(
name|GIMP_CONTAINER_MENU_IMPL
argument_list|(
name|menu
argument_list|)
operator|->
name|empty_item
argument_list|)
expr_stmt|;
return|return
operator|(
name|gpointer
operator|)
name|menu_item
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_impl_remove_item (GimpContainerMenu * menu,GimpViewable * viewable,gpointer insert_data)
name|gimp_container_menu_impl_remove_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
if|if
condition|(
name|insert_data
condition|)
name|menu_item
operator|=
name|GTK_WIDGET
argument_list|(
name|insert_data
argument_list|)
expr_stmt|;
else|else
name|menu_item
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|menu_item
condition|)
block|{
if|if
condition|(
name|g_list_length
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
argument_list|)
operator|==
literal|2
condition|)
name|gtk_widget_show
argument_list|(
name|GIMP_CONTAINER_MENU_IMPL
argument_list|(
name|menu
argument_list|)
operator|->
name|empty_item
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menu_item
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_list_length
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
argument_list|)
operator|==
literal|1
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|GIMP_CONTAINER_MENU_IMPL
argument_list|(
name|menu
argument_list|)
operator|->
name|empty_item
argument_list|)
expr_stmt|;
block|}
comment|/* FIXME: this is due to gtkoptionmenu brokenness */
name|gimp_container_menu_impl_set_history
argument_list|(
name|menu
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_impl_reorder_item (GimpContainerMenu * menu,GimpViewable * viewable,gint new_index,gpointer insert_data)
name|gimp_container_menu_impl_reorder_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
if|if
condition|(
name|insert_data
condition|)
name|menu_item
operator|=
name|GTK_WIDGET
argument_list|(
name|insert_data
argument_list|)
expr_stmt|;
else|else
name|menu_item
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|menu_item
condition|)
block|{
name|active
operator|=
operator|(
name|gtk_menu_get_active
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|)
operator|==
name|menu_item
operator|)
expr_stmt|;
name|gtk_menu_reorder_child
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|menu_item
argument_list|)
argument_list|,
name|new_index
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
condition|)
name|gimp_container_menu_impl_set_history
argument_list|(
name|menu
argument_list|,
name|new_index
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_impl_select_item (GimpContainerMenu * menu,GimpViewable * viewable,gpointer insert_data)
name|gimp_container_menu_impl_select_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
if|if
condition|(
name|insert_data
condition|)
name|menu_item
operator|=
name|GTK_WIDGET
argument_list|(
name|insert_data
argument_list|)
expr_stmt|;
else|else
name|menu_item
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|menu_item
condition|)
block|{
name|gint
name|index
decl_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|menu
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_menu_impl_set_history
argument_list|(
name|menu
argument_list|,
name|index
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_impl_clear_items (GimpContainerMenu * menu)
name|gimp_container_menu_impl_clear_items
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
block|{
while|while
condition|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
condition|)
block|{
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|menu
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|GIMP_CONTAINER_MENU_IMPL
argument_list|(
name|menu
argument_list|)
operator|->
name|empty_item
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_CONTAINER_MENU_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|clear_items
condition|)
name|GIMP_CONTAINER_MENU_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|clear_items
argument_list|(
name|menu
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_impl_set_preview_size (GimpContainerMenu * menu)
name|gimp_container_menu_impl_set_preview_size
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
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
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
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
name|GimpMenuItem
modifier|*
name|menu_item
decl_stmt|;
name|menu_item
operator|=
name|GIMP_MENU_ITEM
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_preview_set_size
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|menu_item
operator|->
name|preview
argument_list|)
argument_list|,
name|menu
operator|->
name|preview_size
argument_list|,
name|GIMP_PREVIEW
argument_list|(
name|menu_item
operator|->
name|preview
argument_list|)
operator|->
name|border_width
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_impl_set_history (GimpContainerMenu * menu,gint history)
name|gimp_container_menu_impl_set_history
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|gint
name|history
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|parent
decl_stmt|;
name|parent
operator|=
name|gtk_menu_get_attach_widget
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent
operator|&&
name|GTK_IS_OPTION_MENU
argument_list|(
name|parent
argument_list|)
condition|)
block|{
name|gtk_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|parent
argument_list|)
argument_list|,
name|history
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_menu_set_active
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|history
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  GtkMenuItem callbacks  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_impl_item_selected (GtkWidget * widget,gpointer data)
name|gimp_container_menu_impl_item_selected
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpMenuItem
modifier|*
name|menu_item
decl_stmt|;
name|menu_item
operator|=
name|GIMP_MENU_ITEM
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gimp_container_menu_item_selected
argument_list|(
name|GIMP_CONTAINER_MENU
argument_list|(
name|data
argument_list|)
argument_list|,
name|GIMP_PREVIEW
argument_list|(
name|menu_item
operator|->
name|preview
argument_list|)
operator|->
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

