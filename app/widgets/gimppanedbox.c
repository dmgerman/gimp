begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppanedbox.c  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  * Copyright (C)      2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
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
file|"gimpmenudock.h"
end_include

begin_include
include|#
directive|include
file|"gimppanedbox.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_comment
comment|/**  * Defines the size of the area that dockables can be dropped on in  * order to be inserted and get space on their own (rather than  * inserted among others and sharing space)  */
end_comment

begin_define
DECL|macro|DROP_AREA_SIZE
define|#
directive|define
name|DROP_AREA_SIZE
value|5
end_define

begin_define
DECL|macro|INSERT_INDEX_UNUSED
define|#
directive|define
name|INSERT_INDEX_UNUSED
value|G_MININT
end_define

begin_struct
DECL|struct|_GimpPanedBoxPrivate
struct|struct
name|_GimpPanedBoxPrivate
block|{
comment|/* Widgets that are separated by panes */
DECL|member|widgets
name|GList
modifier|*
name|widgets
decl_stmt|;
comment|/* Window used for drag-and-drop output */
DECL|member|dnd_window
name|GdkWindow
modifier|*
name|dnd_window
decl_stmt|;
comment|/* The insert index to use on drop */
DECL|member|insert_index
name|gint
name|insert_index
decl_stmt|;
comment|/* Callback on drop */
DECL|member|dropped_cb
name|GimpPanedBoxDroppedFunc
name|dropped_cb
decl_stmt|;
DECL|member|dropped_cb_data
name|gpointer
name|dropped_cb_data
decl_stmt|;
comment|/* A drag handler offered to handle drag events */
DECL|member|drag_handler
name|GimpPanedBox
modifier|*
name|drag_handler
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_paned_box_dispose
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
name|gimp_paned_box_drag_leave
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|guint
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_paned_box_drag_motion
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
name|gimp_paned_box_drag_drop
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
name|void
name|gimp_paned_box_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paned_box_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paned_box_set_widget_drag_handler
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpPanedBox
modifier|*
name|handler
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPanedBox
argument_list|,
argument|gimp_paned_box
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_paned_box_parent_class
end_define

begin_decl_stmt
specifier|static
specifier|const
name|GtkTargetEntry
name|dialog_target_table
index|[]
init|=
block|{
name|GIMP_TARGET_DIALOG
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_paned_box_class_init (GimpPanedBoxClass * klass)
name|gimp_paned_box_class_init
parameter_list|(
name|GimpPanedBoxClass
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
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_paned_box_dispose
expr_stmt|;
name|widget_class
operator|->
name|drag_leave
operator|=
name|gimp_paned_box_drag_leave
expr_stmt|;
name|widget_class
operator|->
name|drag_motion
operator|=
name|gimp_paned_box_drag_motion
expr_stmt|;
name|widget_class
operator|->
name|drag_drop
operator|=
name|gimp_paned_box_drag_drop
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_paned_box_realize
expr_stmt|;
name|widget_class
operator|->
name|unrealize
operator|=
name|gimp_paned_box_unrealize
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpPanedBoxPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paned_box_init (GimpPanedBox * paned_box)
name|gimp_paned_box_init
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|)
block|{
name|paned_box
operator|->
name|p
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|paned_box
argument_list|,
name|GIMP_TYPE_PANED_BOX
argument_list|,
name|GimpPanedBoxPrivate
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|paned_box
argument_list|)
argument_list|,
literal|0
argument_list|,
name|dialog_target_table
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dialog_target_table
argument_list|)
argument_list|,
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paned_box_dispose (GObject * object)
name|gimp_paned_box_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPanedBox
modifier|*
name|paned_box
init|=
name|GIMP_PANED_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
while|while
condition|(
name|paned_box
operator|->
name|p
operator|->
name|widgets
condition|)
name|gimp_paned_box_remove_widget
argument_list|(
name|paned_box
argument_list|,
name|paned_box
operator|->
name|p
operator|->
name|widgets
operator|->
name|data
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
DECL|function|gimp_paned_box_realize (GtkWidget * widget)
name|gimp_paned_box_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|realize
argument_list|(
name|widget
argument_list|)
expr_stmt|;
comment|/* We realize() dnd_window on demand in    * gimp_paned_box_show_separators()    */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paned_box_unrealize (GtkWidget * widget)
name|gimp_paned_box_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpPanedBox
modifier|*
name|paned_box
init|=
name|GIMP_PANED_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
condition|)
block|{
name|gdk_window_set_user_data
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_window_destroy
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
argument_list|)
expr_stmt|;
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
operator|=
name|NULL
expr_stmt|;
block|}
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|unrealize
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paned_box_set_widget_drag_handler (GtkWidget * widget,GimpPanedBox * drag_handler)
name|gimp_paned_box_set_widget_drag_handler
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpPanedBox
modifier|*
name|drag_handler
parameter_list|)
block|{
comment|/* Hook us in for drag events. We could abstract this properly and    * put gimp_paned_box_will_handle_drag() in an interface for    * example, but it doesn't feel worth it at this point    *    * Note that we don't have 'else if's because a widget can be both a    * dock and a toolbox for example, in which case we want to set a    * drag handler in two ways    *    * We so need to introduce som abstractions here...    */
if|if
condition|(
name|GIMP_IS_DOCKBOOK
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|gimp_dockbook_set_drag_handler
argument_list|(
name|GIMP_DOCKBOOK
argument_list|(
name|widget
argument_list|)
argument_list|,
name|drag_handler
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_IS_DOCK
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GimpPanedBox
modifier|*
name|dock_paned_box
init|=
name|NULL
decl_stmt|;
name|dock_paned_box
operator|=
name|GIMP_PANED_BOX
argument_list|(
name|gimp_dock_get_vbox
argument_list|(
name|GIMP_DOCK
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_paned_box_set_drag_handler
argument_list|(
name|dock_paned_box
argument_list|,
name|drag_handler
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_IS_TOOLBOX
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GimpToolbox
modifier|*
name|toolbox
init|=
name|GIMP_TOOLBOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gimp_toolbox_set_drag_handler
argument_list|(
name|toolbox
argument_list|,
name|drag_handler
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paned_box_position_drop_indicator (GimpPanedBox * paned_box,gint x,gint y,gint width,gint height)
name|gimp_paned_box_position_drop_indicator
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|paned_box
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|gtk_widget_is_drawable
argument_list|(
name|widget
argument_list|)
condition|)
return|return;
comment|/* Create or move the GdkWindow in place */
if|if
condition|(
operator|!
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
condition|)
block|{
name|GtkStyle
modifier|*
name|style
init|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|GdkWindowAttr
name|attributes
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|attributes
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|attributes
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|attributes
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|attributes
operator|.
name|height
operator|=
name|height
expr_stmt|;
name|attributes
operator|.
name|window_type
operator|=
name|GDK_WINDOW_CHILD
expr_stmt|;
name|attributes
operator|.
name|wclass
operator|=
name|GDK_INPUT_OUTPUT
expr_stmt|;
name|attributes
operator|.
name|event_mask
operator|=
name|gtk_widget_get_events
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
operator|=
name|gdk_window_new
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|attributes
argument_list|,
name|GDK_WA_X
operator||
name|GDK_WA_Y
argument_list|)
expr_stmt|;
name|gdk_window_set_user_data
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|gdk_window_set_background
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_SELECTED
index|]
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_window_move_resize
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
name|gdk_window_show
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paned_box_hide_drop_indicator (GimpPanedBox * paned_box)
name|gimp_paned_box_hide_drop_indicator
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|)
block|{
if|if
condition|(
operator|!
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
condition|)
return|return;
name|gdk_window_hide
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|dnd_window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paned_box_drag_leave (GtkWidget * widget,GdkDragContext * context,guint time)
name|gimp_paned_box_drag_leave
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|gimp_paned_box_hide_drop_indicator
argument_list|(
name|GIMP_PANED_BOX
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_highlight_widget
argument_list|(
name|widget
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_paned_box_drag_motion (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time)
name|gimp_paned_box_drag_motion
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
name|GimpPanedBox
modifier|*
name|paned_box
init|=
name|GIMP_PANED_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|insert_index
init|=
name|INSERT_INDEX_UNUSED
decl_stmt|;
name|gint
name|dnd_window_x
init|=
literal|0
decl_stmt|;
name|gint
name|dnd_window_y
init|=
literal|0
decl_stmt|;
name|gint
name|dnd_window_w
init|=
literal|0
decl_stmt|;
name|gint
name|dnd_window_h
init|=
literal|0
decl_stmt|;
name|GtkOrientation
name|orientation
init|=
literal|0
decl_stmt|;
name|GtkAllocation
name|allocation
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gboolean
name|handle
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|gimp_paned_box_will_handle_drag
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|drag_handler
argument_list|,
name|widget
argument_list|,
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|time
argument_list|)
condition|)
block|{
comment|/* A parent widget will handle the event, just go to the end */
name|handle
operator|=
name|FALSE
expr_stmt|;
goto|goto
name|finish
goto|;
block|}
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
comment|/* See if we're at the edge of the dock */
name|orientation
operator|=
name|gtk_orientable_get_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|paned_box
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|orientation
operator|==
name|GTK_ORIENTATION_HORIZONTAL
condition|)
block|{
name|dnd_window_y
operator|=
literal|0
expr_stmt|;
name|dnd_window_w
operator|=
name|DROP_AREA_SIZE
expr_stmt|;
name|dnd_window_h
operator|=
name|allocation
operator|.
name|height
expr_stmt|;
if|if
condition|(
name|x
operator|<
name|DROP_AREA_SIZE
condition|)
block|{
name|insert_index
operator|=
literal|0
expr_stmt|;
name|dnd_window_x
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|>
name|allocation
operator|.
name|width
operator|-
name|DROP_AREA_SIZE
condition|)
block|{
name|insert_index
operator|=
operator|-
literal|1
expr_stmt|;
name|dnd_window_x
operator|=
name|allocation
operator|.
name|width
operator|-
name|DROP_AREA_SIZE
expr_stmt|;
block|}
block|}
else|else
comment|/* if (orientation = GTK_ORIENTATION_VERTICAL) */
block|{
name|dnd_window_x
operator|=
literal|0
expr_stmt|;
name|dnd_window_w
operator|=
name|allocation
operator|.
name|width
expr_stmt|;
name|dnd_window_h
operator|=
name|DROP_AREA_SIZE
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|DROP_AREA_SIZE
condition|)
block|{
name|insert_index
operator|=
literal|0
expr_stmt|;
name|dnd_window_y
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|>
name|allocation
operator|.
name|height
operator|-
name|DROP_AREA_SIZE
condition|)
block|{
name|insert_index
operator|=
operator|-
literal|1
expr_stmt|;
name|dnd_window_y
operator|=
name|allocation
operator|.
name|height
operator|-
name|DROP_AREA_SIZE
expr_stmt|;
block|}
block|}
comment|/* If we are at the edge, show a GdkWindow to communicate that a    * drop will create a new dock column    */
name|handle
operator|=
operator|(
name|insert_index
operator|!=
name|INSERT_INDEX_UNUSED
operator|)
expr_stmt|;
if|if
condition|(
name|handle
condition|)
block|{
name|gimp_paned_box_position_drop_indicator
argument_list|(
name|paned_box
argument_list|,
name|allocation
operator|.
name|x
operator|+
name|dnd_window_x
argument_list|,
name|allocation
operator|.
name|y
operator|+
name|dnd_window_y
argument_list|,
name|dnd_window_w
argument_list|,
name|dnd_window_h
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_paned_box_hide_drop_indicator
argument_list|(
name|paned_box
argument_list|)
expr_stmt|;
block|}
comment|/* Save the insert index for drag-drop */
name|paned_box
operator|->
name|p
operator|->
name|insert_index
operator|=
name|insert_index
expr_stmt|;
name|finish
label|:
name|gdk_drag_status
argument_list|(
name|context
argument_list|,
name|handle
condition|?
name|GDK_ACTION_MOVE
else|:
literal|0
argument_list|,
name|time
argument_list|)
expr_stmt|;
name|gimp_highlight_widget
argument_list|(
name|widget
argument_list|,
name|handle
argument_list|)
expr_stmt|;
return|return
name|handle
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_paned_box_drag_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time)
name|gimp_paned_box_drag_drop
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
name|gboolean
name|found
init|=
name|FALSE
decl_stmt|;
name|GimpPanedBox
modifier|*
name|paned_box
init|=
name|GIMP_PANED_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp_paned_box_will_handle_drag
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|drag_handler
argument_list|,
name|widget
argument_list|,
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|time
argument_list|)
condition|)
block|{
comment|/* A parent widget will handle the event, just go to the end */
name|found
operator|=
name|FALSE
expr_stmt|;
goto|goto
name|finish
goto|;
block|}
if|if
condition|(
name|paned_box
operator|->
name|p
operator|->
name|dropped_cb
condition|)
block|{
name|GtkWidget
modifier|*
name|source
init|=
name|gtk_drag_get_source_widget
argument_list|(
name|context
argument_list|)
decl_stmt|;
if|if
condition|(
name|source
condition|)
name|found
operator|=
name|paned_box
operator|->
name|p
operator|->
name|dropped_cb
argument_list|(
name|source
argument_list|,
name|paned_box
operator|->
name|p
operator|->
name|insert_index
argument_list|,
name|paned_box
operator|->
name|p
operator|->
name|dropped_cb_data
argument_list|)
expr_stmt|;
block|}
name|finish
label|:
if|if
condition|(
name|found
condition|)
name|gtk_drag_finish
argument_list|(
name|context
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|time
argument_list|)
expr_stmt|;
return|return
name|found
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_paned_box_new (gboolean homogeneous,gint spacing,GtkOrientation orientation)
name|gimp_paned_box_new
parameter_list|(
name|gboolean
name|homogeneous
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GtkOrientation
name|orientation
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_PANED_BOX
argument_list|,
literal|"homogeneous"
argument_list|,
name|homogeneous
argument_list|,
literal|"spacing"
argument_list|,
literal|0
argument_list|,
literal|"orientation"
argument_list|,
name|orientation
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_paned_box_set_dropped_cb (GimpPanedBox * paned_box,GimpPanedBoxDroppedFunc dropped_cb,gpointer dropped_cb_data)
name|gimp_paned_box_set_dropped_cb
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|,
name|GimpPanedBoxDroppedFunc
name|dropped_cb
parameter_list|,
name|gpointer
name|dropped_cb_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PANED_BOX
argument_list|(
name|paned_box
argument_list|)
argument_list|)
expr_stmt|;
name|paned_box
operator|->
name|p
operator|->
name|dropped_cb
operator|=
name|dropped_cb
expr_stmt|;
name|paned_box
operator|->
name|p
operator|->
name|dropped_cb_data
operator|=
name|dropped_cb_data
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_paned_box_add_widget:  * @paned_box: A #GimpPanedBox  * @widget:    The #GtkWidget to add  * @index:     Where to add the @widget  *  * Add a #GtkWidget to the #GimpPanedBox in a hierarchy of #GtkPaned:s  * so the space can be manually distributed between the widgets.  **/
end_comment

begin_function
name|void
DECL|function|gimp_paned_box_add_widget (GimpPanedBox * paned_box,GtkWidget * widget,gint index)
name|gimp_paned_box_add_widget
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|gint
name|old_length
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PANED_BOX
argument_list|(
name|paned_box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
literal|"Adding GtkWidget %p to GimpPanedBox %p"
argument_list|,
name|widget
argument_list|,
name|paned_box
argument_list|)
expr_stmt|;
comment|/* Calculate length */
name|old_length
operator|=
name|g_list_length
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|widgets
argument_list|)
expr_stmt|;
comment|/* If index is invalid append at the end */
if|if
condition|(
name|index
operator|>=
name|old_length
operator|||
name|index
operator|<
literal|0
condition|)
block|{
name|index
operator|=
name|old_length
expr_stmt|;
block|}
comment|/* Insert into the list */
name|paned_box
operator|->
name|p
operator|->
name|widgets
operator|=
name|g_list_insert
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|widgets
argument_list|,
name|widget
argument_list|,
name|index
argument_list|)
expr_stmt|;
comment|/* Hook us in for drag events. We could abstract this but it doesn't    * seem worth it at this point    */
name|gimp_paned_box_set_widget_drag_handler
argument_list|(
name|widget
argument_list|,
name|paned_box
argument_list|)
expr_stmt|;
comment|/* Insert into the GtkPaned hierarchy */
if|if
condition|(
name|old_length
operator|==
literal|0
condition|)
block|{
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|paned_box
argument_list|)
argument_list|,
name|widget
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|old_widget
decl_stmt|;
name|GtkWidget
modifier|*
name|parent
decl_stmt|;
name|GtkWidget
modifier|*
name|paned
decl_stmt|;
name|GtkOrientation
name|orientation
decl_stmt|;
comment|/* Figure out what widget to detach */
if|if
condition|(
name|index
operator|==
literal|0
condition|)
block|{
name|old_widget
operator|=
name|g_list_nth_data
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|widgets
argument_list|,
name|index
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|old_widget
operator|=
name|g_list_nth_data
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|widgets
argument_list|,
name|index
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|parent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|old_widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_length
operator|>
literal|1
operator|&&
name|index
operator|>
literal|0
condition|)
block|{
name|GtkWidget
modifier|*
name|grandparent
init|=
name|gtk_widget_get_parent
argument_list|(
name|parent
argument_list|)
decl_stmt|;
name|old_widget
operator|=
name|parent
expr_stmt|;
name|parent
operator|=
name|grandparent
expr_stmt|;
block|}
comment|/* Deatch the widget and bulid up a new hierarchy */
name|g_object_ref
argument_list|(
name|old_widget
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|parent
argument_list|)
argument_list|,
name|old_widget
argument_list|)
expr_stmt|;
comment|/* GtkPaned is abstract :( */
name|orientation
operator|=
name|gtk_orientable_get_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|paned_box
argument_list|)
argument_list|)
expr_stmt|;
name|paned
operator|=
operator|(
name|orientation
operator|==
name|GTK_ORIENTATION_VERTICAL
condition|?
name|gtk_vpaned_new
argument_list|()
else|:
name|gtk_hpaned_new
argument_list|()
operator|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_PANED
argument_list|(
name|parent
argument_list|)
condition|)
block|{
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|parent
argument_list|)
argument_list|,
name|paned
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|parent
argument_list|)
argument_list|,
name|paned
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|paned
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
literal|0
condition|)
block|{
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|widget
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_paned_pack2
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|old_widget
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|old_widget
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_paned_pack2
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|widget
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|old_widget
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_paned_box_remove_widget:  * @paned_box: A #GimpPanedBox  * @widget:    The #GtkWidget to remove  *  * Remove a #GtkWidget from a #GimpPanedBox added with  * gimp_widgets_add_paned_widget().  **/
end_comment

begin_function
name|void
DECL|function|gimp_paned_box_remove_widget (GimpPanedBox * paned_box,GtkWidget * widget)
name|gimp_paned_box_remove_widget
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gint
name|old_length
init|=
literal|0
decl_stmt|;
name|gint
name|index
init|=
literal|0
decl_stmt|;
name|GtkWidget
modifier|*
name|other_widget
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|parent
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|grandparent
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PANED_BOX
argument_list|(
name|paned_box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
literal|"Removing GtkWidget %p from GimpPanedBox %p"
argument_list|,
name|widget
argument_list|,
name|paned_box
argument_list|)
expr_stmt|;
comment|/* Calculate length and index */
name|old_length
operator|=
name|g_list_length
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|widgets
argument_list|)
expr_stmt|;
name|index
operator|=
name|g_list_index
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|widgets
argument_list|,
name|widget
argument_list|)
expr_stmt|;
comment|/* Remove from list */
name|paned_box
operator|->
name|p
operator|->
name|widgets
operator|=
name|g_list_remove
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|widgets
argument_list|,
name|widget
argument_list|)
expr_stmt|;
comment|/* Reset the drag events hook */
name|gimp_paned_box_set_widget_drag_handler
argument_list|(
name|widget
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Remove from widget hierarchy */
if|if
condition|(
name|old_length
operator|==
literal|1
condition|)
block|{
comment|/* The widget might already be parent-less if we are in        * destruction, .e.g when closing a dock window.        */
if|if
condition|(
name|gtk_widget_get_parent
argument_list|(
name|widget
argument_list|)
operator|!=
name|NULL
condition|)
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|paned_box
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_object_ref
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|parent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|GTK_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|grandparent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
literal|0
condition|)
name|other_widget
operator|=
name|gtk_paned_get_child2
argument_list|(
name|GTK_PANED
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|other_widget
operator|=
name|gtk_paned_get_child1
argument_list|(
name|GTK_PANED
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|other_widget
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|parent
argument_list|)
argument_list|,
name|other_widget
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|parent
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|grandparent
argument_list|)
argument_list|,
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_PANED
argument_list|(
name|grandparent
argument_list|)
condition|)
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|grandparent
argument_list|)
argument_list|,
name|other_widget
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
else|else
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|paned_box
argument_list|)
argument_list|,
name|other_widget
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
name|other_widget
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_paned_box_will_handle_drag:  * @paned_box: A #GimpPanedBox  * @widget:    The widget that got the drag event  * @context:   Context from drag event  * @x:         x from drag event  * @y:         y from drag event  * @time:      time from drag event  *  * Returns: %TRUE if the drag event on @widget will be handled by  *          @paned_box.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_paned_box_will_handle_drag (GimpPanedBox * paned_box,GtkWidget * widget,GdkDragContext * context,gint x,gint y,gint time)
name|gimp_paned_box_will_handle_drag
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|,
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
name|gint
name|time
parameter_list|)
block|{
name|gint
name|paned_box_x
init|=
literal|0
decl_stmt|;
name|gint
name|paned_box_y
init|=
literal|0
decl_stmt|;
name|GtkAllocation
name|allocation
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|GtkOrientation
name|orientation
init|=
literal|0
decl_stmt|;
name|gboolean
name|will_handle
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|paned_box
operator|==
name|NULL
operator|||
name|GIMP_IS_PANED_BOX
argument_list|(
name|paned_box
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Check for NULL to allow cleaner client code */
if|if
condition|(
name|paned_box
operator|==
name|NULL
condition|)
return|return
name|FALSE
return|;
comment|/* Our handler might handle it */
if|if
condition|(
name|gimp_paned_box_will_handle_drag
argument_list|(
name|paned_box
operator|->
name|p
operator|->
name|drag_handler
argument_list|,
name|widget
argument_list|,
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|time
argument_list|)
condition|)
block|{
comment|/* Return TRUE so the client will pass on the drag event */
return|return
name|TRUE
return|;
block|}
comment|/* If we don't have a common ancenstor we will not handle it */
if|if
condition|(
operator|!
name|gtk_widget_translate_coordinates
argument_list|(
name|widget
argument_list|,
name|GTK_WIDGET
argument_list|(
name|paned_box
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|paned_box_x
argument_list|,
operator|&
name|paned_box_y
argument_list|)
condition|)
block|{
comment|/* Return FALSE so the client can take care of the drag event */
return|return
name|FALSE
return|;
block|}
comment|/* We now have paned_box coordinates, see if the paned_box will    * handle the event    */
name|gtk_widget_get_allocation
argument_list|(
name|GTK_WIDGET
argument_list|(
name|paned_box
argument_list|)
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|orientation
operator|=
name|gtk_orientable_get_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|paned_box
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|orientation
operator|==
name|GTK_ORIENTATION_HORIZONTAL
condition|)
block|{
name|will_handle
operator|=
operator|(
name|paned_box_x
operator|<
name|DROP_AREA_SIZE
operator|||
name|paned_box_x
operator|>
name|allocation
operator|.
name|width
operator|-
name|DROP_AREA_SIZE
operator|)
expr_stmt|;
block|}
else|else
comment|/*if (orientation = GTK_ORIENTATION_VERTICAL)*/
block|{
name|will_handle
operator|=
operator|(
name|paned_box_y
operator|<
name|DROP_AREA_SIZE
operator|||
name|paned_box_y
operator|>
name|allocation
operator|.
name|height
operator|-
name|DROP_AREA_SIZE
operator|)
expr_stmt|;
block|}
return|return
name|will_handle
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_paned_box_set_drag_handler (GimpPanedBox * paned_box,GimpPanedBox * drag_handler)
name|gimp_paned_box_set_drag_handler
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|,
name|GimpPanedBox
modifier|*
name|drag_handler
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PANED_BOX
argument_list|(
name|paned_box
argument_list|)
argument_list|)
expr_stmt|;
name|paned_box
operator|->
name|p
operator|->
name|drag_handler
operator|=
name|drag_handler
expr_stmt|;
block|}
end_function

end_unit

