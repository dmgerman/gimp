begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdock.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpdialogfactory.h"
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

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_dock_class_init
parameter_list|(
name|GimpDockClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_init
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_dock_separator_new
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_destroy
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
name|gimp_dock_separator_button_press
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
name|gboolean
name|gimp_dock_separator_button_release
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

begin_comment
comment|/* static void        gimp_dock_separator_drag_begin     (GtkWidget      *widget, 			  			       GdkDragContext *context, 						       gpointer        data); static void        gimp_dock_separator_drag_end       (GtkWidget      *widget, 						       GdkDragContext *context, 						       gpointer        data); */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_dock_separator_drag_drop
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
name|GtkWindowClass
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
DECL|function|gimp_dock_get_type (void)
name|gimp_dock_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|dock_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|dock_type
condition|)
block|{
specifier|static
specifier|const
name|GtkTypeInfo
name|dock_info
init|=
block|{
literal|"GimpDock"
block|,
sizeof|sizeof
argument_list|(
name|GimpDock
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpDockClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_dock_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_dock_init
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
name|dock_type
operator|=
name|gtk_type_unique
argument_list|(
name|GTK_TYPE_WINDOW
argument_list|,
operator|&
name|dock_info
argument_list|)
expr_stmt|;
block|}
return|return
name|dock_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_class_init (GimpDockClass * klass)
name|gimp_dock_class_init
parameter_list|(
name|GimpDockClass
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
name|GTK_TYPE_WINDOW
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_dock_destroy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_init (GimpDock * dock)
name|gimp_dock_init
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dock
operator|->
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dock
argument_list|)
argument_list|,
name|dock
operator|->
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dock
operator|->
name|vbox
argument_list|)
expr_stmt|;
name|separator
operator|=
name|gimp_dock_separator_new
argument_list|(
name|dock
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dock
operator|->
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_destroy (GtkObject * object)
name|gimp_dock_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDock
modifier|*
name|dock
decl_stmt|;
name|dock
operator|=
name|GIMP_DOCK
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|dock
operator|->
name|dockbooks
argument_list|)
expr_stmt|;
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
DECL|function|gimp_dock_new (GimpDialogFactory * factory)
name|gimp_dock_new
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
block|{
name|GimpDock
modifier|*
name|dock
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|factory
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dock
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_DOCK
argument_list|)
expr_stmt|;
name|dock
operator|->
name|factory
operator|=
name|factory
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_dock_separator_new (GimpDock * dock)
name|gimp_dock_separator_new
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|event_box
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|event_box
operator|=
name|gtk_event_box_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|event_box
argument_list|,
operator|-
literal|1
argument_list|,
literal|8
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
name|event_box
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
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|event_box
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
name|event_box
argument_list|)
argument_list|,
literal|"drag_drop"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dock_separator_drag_drop
argument_list|)
argument_list|,
name|dock
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|event_box
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dock_separator_button_press
argument_list|)
argument_list|,
name|dock
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|event_box
argument_list|)
argument_list|,
literal|"button_release_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dock_separator_button_release
argument_list|)
argument_list|,
name|dock
argument_list|)
expr_stmt|;
return|return
name|event_box
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_add (GimpDock * dock,GimpDockable * dockable,gint section,gint position)
name|gimp_dock_add
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|gint
name|section
parameter_list|,
name|gint
name|position
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|dock
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
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
name|dockbook
operator|=
name|GIMP_DOCKBOOK
argument_list|(
name|dock
operator|->
name|dockbooks
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_dockbook_add
argument_list|(
name|dockbook
argument_list|,
name|dockable
argument_list|,
name|position
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_remove (GimpDock * dock,GimpDockable * dockable)
name|gimp_dock_remove
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|dock
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
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
operator|->
name|dock
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dockable
operator|->
name|dockbook
operator|->
name|dock
operator|==
name|dock
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_add_book (GimpDock * dock,GimpDockbook * dockbook,gint index)
name|gimp_dock_add_book
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
name|gint
name|length
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|dock
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
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
name|dockbook
operator|->
name|dock
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|length
operator|=
name|g_list_length
argument_list|(
name|dock
operator|->
name|dockbooks
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|>=
name|length
operator|||
name|index
operator|<
literal|0
condition|)
name|index
operator|=
name|length
expr_stmt|;
name|dockbook
operator|->
name|dock
operator|=
name|dock
expr_stmt|;
name|dock
operator|->
name|dockbooks
operator|=
name|g_list_insert
argument_list|(
name|dock
operator|->
name|dockbooks
argument_list|,
name|dockbook
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|index
operator|*=
literal|2
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dock
operator|->
name|vbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|dock
operator|->
name|vbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|separator
operator|=
name|gimp_dock_separator_new
argument_list|(
name|dock
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dock
operator|->
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
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|dock
operator|->
name|vbox
argument_list|)
argument_list|,
name|separator
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|separator
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_remove_book (GimpDock * dock,GimpDockbook * dockbook)
name|gimp_dock_remove_book
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
block|{
name|GList
modifier|*
name|children
decl_stmt|;
name|gint
name|length
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|gint
name|book_index
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|dock
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
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
name|dockbook
operator|->
name|dock
operator|==
name|dock
argument_list|)
expr_stmt|;
name|length
operator|=
name|g_list_length
argument_list|(
name|dock
operator|->
name|dockbooks
argument_list|)
expr_stmt|;
name|index
operator|=
name|g_list_index
argument_list|(
name|dock
operator|->
name|dockbooks
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
name|dockbook
operator|->
name|dock
operator|=
name|NULL
expr_stmt|;
name|dock
operator|->
name|dockbooks
operator|=
name|g_list_remove
argument_list|(
name|dock
operator|->
name|dockbooks
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dock
operator|->
name|vbox
argument_list|)
argument_list|)
expr_stmt|;
name|book_index
operator|=
name|g_list_index
argument_list|(
name|children
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
if|if
condition|(
name|length
operator|!=
literal|1
condition|)
block|{
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
if|if
condition|(
name|index
operator|==
name|length
operator|-
literal|1
condition|)
block|{
name|separator
operator|=
name|g_list_nth_data
argument_list|(
name|children
argument_list|,
name|book_index
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|separator
operator|=
name|g_list_nth_data
argument_list|(
name|children
argument_list|,
name|book_index
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dock
operator|->
name|vbox
argument_list|)
argument_list|,
name|separator
argument_list|)
expr_stmt|;
block|}
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dock
operator|->
name|vbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|length
operator|==
literal|1
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dock_separator_button_press (GtkWidget * widget,GdkEventButton * bevent,gpointer data)
name|gimp_dock_separator_button_press
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
if|if
condition|(
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
block|{
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gtk_grab_add
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dock_separator_button_release (GtkWidget * widget,GdkEventButton * bevent,gpointer data)
name|gimp_dock_separator_button_release
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
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gtk_grab_remove
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/* static void gimp_dock_tab_drag_begin (GtkWidget      *widget, 			  GdkDragContext *context, 			  gpointer        data) {   GimpDockable *dockable;   GtkWidget    *window;   GtkWidget    *frame;   GtkWidget    *label;    dockable = GIMP_DOCKABLE (data);    window = gtk_window_new (GTK_WINDOW_POPUP);    frame = gtk_frame_new (NULL);   gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_OUT);   gtk_container_add (GTK_CONTAINER (window), frame);   gtk_widget_show (frame);    label = gtk_label_new (dockable->name);   gtk_misc_set_padding (GTK_MISC (label), 10, 5);   gtk_container_add (GTK_CONTAINER (frame), label);   gtk_widget_show (label);    gtk_widget_show (window);    gtk_object_set_data_full (GTK_OBJECT (dockable), "gimp_dock_drag_widget", 			    window, 			    (GtkDestroyNotify) gtk_widget_destroy);    gtk_drag_set_icon_widget (context, window, 			    -8, -8); }  static void gimp_dock_tab_drag_end (GtkWidget      *widget, 			GdkDragContext *context, 			gpointer        data) {   GimpDockable *dockable;   GtkWidget    *drag_widget;    dockable = GIMP_DOCKABLE (data);    drag_widget = gtk_object_get_data (GTK_OBJECT (dockable), 				     "gimp_dock_drag_widget");    if (drag_widget)     {       GtkWidget *dock;        gtk_object_set_data (GTK_OBJECT (dockable), "gimp_dock_drag_widget", NULL);        dock = gimp_dock_new ();        gtk_window_set_position (GTK_WINDOW (dock), GTK_WIN_POS_MOUSE);        gtk_object_ref (GTK_OBJECT (dockable));        gimp_dock_remove (dockable->dock, dockable);       gimp_dock_add (GIMP_DOCK (dock), dockable, -1, -1);        gtk_object_unref (GTK_OBJECT (dockable));        gtk_widget_show (dock);     } } */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dock_separator_drag_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time,gpointer data)
name|gimp_dock_separator_drag_drop
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
name|GimpDock
modifier|*
name|dock
decl_stmt|;
name|GtkWidget
modifier|*
name|source
decl_stmt|;
name|dock
operator|=
name|GIMP_DOCK
argument_list|(
name|data
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
name|GtkWidget
modifier|*
name|dockbook
decl_stmt|;
name|GList
modifier|*
name|children
decl_stmt|;
name|gint
name|index
decl_stmt|;
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
name|children
operator|=
name|gtk_container_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
operator|->
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|index
operator|=
name|g_list_index
argument_list|(
name|children
argument_list|,
name|widget
argument_list|)
operator|/
literal|2
expr_stmt|;
name|dockbook
operator|=
name|gimp_dockbook_new
argument_list|()
expr_stmt|;
name|gimp_dock_add_book
argument_list|(
name|dock
argument_list|,
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|index
argument_list|)
expr_stmt|;
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
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|src_dockable
argument_list|,
operator|-
literal|1
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
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

