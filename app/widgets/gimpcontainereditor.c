begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainereditor.c  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
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
file|"gimpcontainerlistview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_class_init
parameter_list|(
name|GimpContainerEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_init
parameter_list|(
name|GimpContainerEditor
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_destroy
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
name|gimp_container_editor_viewable_dropped
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
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
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
name|GtkType
DECL|function|gimp_container_editor_get_type (void)
name|gimp_container_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
name|GtkTypeInfo
name|view_info
init|=
block|{
literal|"GimpContainerEditor"
block|,
sizeof|sizeof
argument_list|(
name|GimpContainerEditor
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpContainerEditorClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_container_editor_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_container_editor_init
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
name|view_type
operator|=
name|gtk_type_unique
argument_list|(
name|GTK_TYPE_VBOX
argument_list|,
operator|&
name|view_info
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_class_init (GimpContainerEditorClass * klass)
name|gimp_container_editor_class_init
parameter_list|(
name|GimpContainerEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GTK_TYPE_VBOX
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_container_editor_destroy
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_init (GimpContainerEditor * view)
name|gimp_container_editor_init
parameter_list|(
name|GimpContainerEditor
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|context_func
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|view
operator|=
name|NULL
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|view
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|view
operator|->
name|button_box
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
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
name|view
operator|->
name|button_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_destroy (GtkObject * object)
name|gimp_container_editor_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
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
name|gboolean
DECL|function|gimp_container_editor_construct (GimpContainerEditor * editor,GimpViewType view_type,GimpContainer * container,GimpContext * context,gint preview_size,gint min_items_x,gint min_items_y,GimpContainerContextFunc context_func)
name|gimp_container_editor_construct
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
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
parameter_list|,
name|gint
name|min_items_x
parameter_list|,
name|gint
name|min_items_y
parameter_list|,
name|GimpContainerContextFunc
name|context_func
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
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
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|min_items_x
operator|>
literal|0
operator|&&
name|min_items_x
operator|<=
literal|64
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|min_items_y
operator|>
literal|0
operator|&&
name|min_items_y
operator|<=
literal|64
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|editor
operator|->
name|context_func
operator|=
name|context_func
expr_stmt|;
switch|switch
condition|(
name|view_type
condition|)
block|{
case|case
name|GIMP_VIEW_TYPE_GRID
case|:
name|editor
operator|->
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|gimp_container_grid_view_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|preview_size
argument_list|,
name|min_items_x
argument_list|,
name|min_items_y
argument_list|)
argument_list|)
expr_stmt|;
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
name|gimp_container_list_view_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|preview_size
argument_list|,
name|min_items_x
argument_list|,
name|min_items_y
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"%s(): unknown GimpViewType passed"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
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
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
literal|"select_item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_editor_select_item
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
name|g_signal_connect_object
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
literal|"activate_item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_editor_activate_item
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
name|g_signal_connect_object
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
literal|"context_item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_editor_context_item
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
comment|/*  select the active item  */
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
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|container
operator|->
name|children_type
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_container_editor_add_button (GimpContainerEditor * editor,gchar ** xpm_data,const gchar * tooltip,const gchar * help_data,GCallback callback)
name|gimp_container_editor_add_button
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|gchar
modifier|*
modifier|*
name|xpm_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
name|GCallback
name|callback
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|pixmap
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|xpm_data
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new
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
name|help_data
condition|)
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|tooltip
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|callback
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|gimp_pixmap_new
argument_list|(
name|xpm_data
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|pixmap
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_editor_enable_dnd (GimpContainerEditor * editor,GtkButton * button)
name|gimp_container_editor_enable_dnd
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GtkButton
modifier|*
name|button
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|editor
operator|->
name|view
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gtk_drag_dest_set_by_type
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|editor
operator|->
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|,
name|editor
operator|->
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|gimp_container_editor_viewable_dropped
argument_list|,
name|editor
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
DECL|function|gimp_container_editor_viewable_dropped (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|gimp_container_editor_viewable_dropped
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
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
operator|(
name|GimpContainerEditor
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|viewable
operator|&&
name|gimp_container_have
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_context_set_by_type
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|,
name|editor
operator|->
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
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
decl_stmt|;
name|klass
operator|=
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|klass
operator|=
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|klass
operator|=
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|viewable
operator|&&
name|gimp_container_have
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
if|if
condition|(
name|editor
operator|->
name|context_func
condition|)
name|editor
operator|->
name|context_func
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

