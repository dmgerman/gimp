begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockbook.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockbook.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_class_init
parameter_list|(
name|GimpDockbookClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_init
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dockbook_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dockbook_tab_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_tab_drag_begin
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_tab_drag_end
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dockbook_tab_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkNotebookClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dialog_target_table
specifier|static
name|GtkTargetEntry
name|dialog_target_table
index|[]
init|=
block|{
name|GIMP_TARGET_DIALOG
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|n_dialog_targets
specifier|static
name|guint
name|n_dialog_targets
init|=
operator|(
sizeof|sizeof
argument_list|(
name|dialog_target_table
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|dialog_target_table
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_dockbook_get_type (void)
name|gimp_dockbook_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|dockbook_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|dockbook_type
condition|)
block|{
specifier|static
specifier|const
name|GtkTypeInfo
name|dockbook_info
init|=
block|{
literal|"GimpDockbook"
block|,
sizeof|sizeof
argument_list|(
name|GimpDockbook
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpDockbookClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_dockbook_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_dockbook_init
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
block|,       }
decl_stmt|;
name|dockbook_type
operator|=
name|gtk_type_unique
argument_list|(
name|GTK_TYPE_NOTEBOOK
argument_list|,
operator|&
name|dockbook_info
argument_list|)
expr_stmt|;
block|}
return|return
name|dockbook_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_class_init (GimpDockbookClass * klass)
name|gimp_dockbook_class_init
parameter_list|(
name|GimpDockbookClass
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
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|widget_class
operator|=
operator|(
name|GtkWidgetClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GTK_TYPE_NOTEBOOK
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_dockbook_destroy
expr_stmt|;
name|widget_class
operator|->
name|drag_drop
operator|=
name|gimp_dockbook_drag_drop
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_init (GimpDockbook * dockbook)
name|gimp_dockbook_init
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
block|{
name|dockbook
operator|->
name|dock
operator|=
name|NULL
expr_stmt|;
name|gtk_notebook_set_tab_border
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_notebook_popup_enable
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_notebook_set_scrollable
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|dialog_target_table
argument_list|,
name|n_dialog_targets
argument_list|,
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_destroy (GtkObject * object)
name|gimp_dockbook_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
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
DECL|function|gimp_dockbook_new (void)
name|gimp_dockbook_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|GTK_WIDGET
argument_list|(
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_DOCKBOOK
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dockbook_drag_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time)
name|gimp_dockbook_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|source
decl_stmt|;
name|source
operator|=
name|gtk_drag_get_source_widget
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|source
condition|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|source
argument_list|)
argument_list|,
literal|"gimp_dockable"
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
block|{
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"gimp_dock_drag_widget"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|->
name|dockbook
operator|!=
name|GIMP_DOCKBOOK
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dockbook_remove
argument_list|(
name|dockable
operator|->
name|dockbook
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|gimp_dockbook_add
argument_list|(
name|GIMP_DOCKBOOK
argument_list|(
name|widget
argument_list|)
argument_list|,
name|dockable
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockbook_add (GimpDockbook * dockbook,GimpDockable * dockable,gint position)
name|gimp_dockbook_add
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|gint
name|position
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|tab_widget
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_widget
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|dockbook
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dockable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dockable
operator|->
name|dockbook
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|tab_widget
operator|=
name|gimp_dockable_get_tab_widget
argument_list|(
name|dockable
argument_list|,
literal|24
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|tab_widget
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|event_box
decl_stmt|;
name|event_box
operator|=
name|gtk_event_box_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|event_box
argument_list|)
argument_list|,
name|tab_widget
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tab_widget
argument_list|)
expr_stmt|;
name|tab_widget
operator|=
name|event_box
expr_stmt|;
block|}
name|gimp_help_set_help_data
argument_list|(
name|tab_widget
argument_list|,
name|dockable
operator|->
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
literal|"gimp_dockable"
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dockbook_tab_button_press
argument_list|)
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|menu_widget
operator|=
name|gimp_dockable_get_tab_widget
argument_list|(
name|dockable
argument_list|,
literal|16
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_IS_LABEL
argument_list|(
name|menu_widget
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|menu_widget
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
name|menu_widget
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|dockable
operator|->
name|name
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|menu_widget
operator|=
name|hbox
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_destroy
argument_list|(
name|menu_widget
argument_list|)
expr_stmt|;
name|menu_widget
operator|=
name|gtk_label_new
argument_list|(
name|dockable
operator|->
name|name
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|menu_widget
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|position
operator|==
operator|-
literal|1
condition|)
block|{
name|gtk_notebook_append_page_menu
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|tab_widget
argument_list|,
name|menu_widget
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_notebook_insert_page_menu
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|tab_widget
argument_list|,
name|menu_widget
argument_list|,
name|position
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_drag_source_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
argument_list|,
name|dialog_target_table
argument_list|,
name|n_dialog_targets
argument_list|,
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
literal|"drag_begin"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dockbook_tab_drag_begin
argument_list|)
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
literal|"drag_end"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dockbook_tab_drag_end
argument_list|)
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|dialog_target_table
argument_list|,
name|n_dialog_targets
argument_list|,
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
literal|"drag_drop"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dockbook_tab_drag_drop
argument_list|)
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|dockbook
operator|=
name|dockbook
expr_stmt|;
if|if
condition|(
name|g_list_length
argument_list|(
name|gtk_container_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dockbook
argument_list|)
argument_list|)
argument_list|)
operator|==
literal|1
condition|)
block|{
name|GtkWidget
modifier|*
name|item
decl_stmt|;
name|item
operator|=
name|gtk_menu_item_new
argument_list|()
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
operator|->
name|menu
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|item
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|item
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
literal|"Test"
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
operator|->
name|menu
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockbook_remove (GimpDockbook * dockbook,GimpDockable * dockable)
name|gimp_dockbook_remove
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|dockbook
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dockable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dockable
operator|->
name|dockbook
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dockable
operator|->
name|dockbook
operator|==
name|dockbook
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_list_length
argument_list|(
name|gtk_container_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dockbook
argument_list|)
argument_list|)
argument_list|)
operator|==
literal|1
condition|)
block|{
while|while
condition|(
name|GTK_MENU_SHELL
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
operator|->
name|menu
argument_list|)
operator|->
name|children
operator|->
name|next
condition|)
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
operator|->
name|menu
argument_list|)
operator|->
name|children
operator|->
name|next
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|dockable
operator|->
name|dockbook
operator|=
name|NULL
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_list_length
argument_list|(
name|gtk_container_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dockbook
argument_list|)
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_dock_remove_book
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dockbook_tab_button_press (GtkWidget * widget,GdkEventButton * bevent,gpointer data)
name|gimp_dockbook_tab_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|gint
name|page_num
decl_stmt|;
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|data
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|bevent
operator|->
name|button
condition|)
block|{
case|case
literal|3
case|:
name|gtk_menu_popup
argument_list|(
name|GTK_MENU
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockable
operator|->
name|dockbook
argument_list|)
operator|->
name|menu
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|3
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
break|break;
default|default:
name|page_num
operator|=
name|gtk_notebook_page_num
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockable
operator|->
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_notebook_set_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockable
operator|->
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_tab_drag_begin (GtkWidget * widget,GdkDragContext * context,gpointer data)
name|gimp_dockbook_tab_drag_begin
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|GtkWidget
modifier|*
name|window
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|window
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_POPUP
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|window
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_dockable_get_tab_widget
argument_list|(
name|dockable
argument_list|,
literal|24
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_IS_LABEL
argument_list|(
name|preview
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|preview
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
name|preview
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|dockable
operator|->
name|name
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|preview
operator|=
name|hbox
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_destroy
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gtk_label_new
argument_list|(
name|dockable
operator|->
name|name
argument_list|)
expr_stmt|;
name|gtk_misc_set_padding
argument_list|(
name|GTK_MISC
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|10
argument_list|,
literal|5
argument_list|)
expr_stmt|;
block|}
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|gtk_object_set_data_full
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"gimp_dock_drag_widget"
argument_list|,
name|window
argument_list|,
operator|(
name|GtkDestroyNotify
operator|)
name|gtk_widget_destroy
argument_list|)
expr_stmt|;
name|gtk_drag_set_icon_widget
argument_list|(
name|context
argument_list|,
name|window
argument_list|,
operator|-
literal|8
argument_list|,
operator|-
literal|8
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_tab_drag_end (GtkWidget * widget,GdkDragContext * context,gpointer data)
name|gimp_dockbook_tab_drag_end
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|GtkWidget
modifier|*
name|drag_widget
decl_stmt|;
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|drag_widget
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"gimp_dock_drag_widget"
argument_list|)
expr_stmt|;
if|if
condition|(
name|drag_widget
condition|)
block|{
name|GtkWidget
modifier|*
name|dock
decl_stmt|;
name|GtkWidget
modifier|*
name|dockbook
decl_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"gimp_dock_drag_widget"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dock
operator|=
name|gimp_dock_new
argument_list|()
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|dockbook
operator|=
name|gimp_dockbook_new
argument_list|()
expr_stmt|;
name|gimp_dock_add_book
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dockbook_remove
argument_list|(
name|dockable
operator|->
name|dockbook
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|gimp_dockbook_add
argument_list|(
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|dockable
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dock
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dockbook_tab_drag_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time,gpointer data)
name|gimp_dockbook_tab_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dest_dockable
decl_stmt|;
name|GtkWidget
modifier|*
name|source
decl_stmt|;
name|dest_dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_dockable"
argument_list|)
expr_stmt|;
name|source
operator|=
name|gtk_drag_get_source_widget
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|source
condition|)
block|{
name|GimpDockable
modifier|*
name|src_dockable
decl_stmt|;
name|src_dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|source
argument_list|)
argument_list|,
literal|"gimp_dockable"
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_dockable
condition|)
block|{
name|gint
name|page_index
decl_stmt|;
name|page_index
operator|=
name|gtk_notebook_page_num
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dest_dockable
operator|->
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dest_dockable
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|src_dockable
argument_list|)
argument_list|,
literal|"gimp_dock_drag_widget"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_dockable
operator|->
name|dockbook
operator|!=
name|dest_dockable
operator|->
name|dockbook
condition|)
block|{
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|src_dockable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dockbook_remove
argument_list|(
name|src_dockable
operator|->
name|dockbook
argument_list|,
name|src_dockable
argument_list|)
expr_stmt|;
name|gimp_dockbook_add
argument_list|(
name|dest_dockable
operator|->
name|dockbook
argument_list|,
name|src_dockable
argument_list|,
name|page_index
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|src_dockable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
elseif|else
if|if
condition|(
name|src_dockable
operator|!=
name|dest_dockable
condition|)
block|{
name|gtk_notebook_reorder_child
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|src_dockable
operator|->
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|src_dockable
argument_list|)
argument_list|,
name|page_index
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

