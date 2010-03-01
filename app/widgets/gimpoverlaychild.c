begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoverlaychild.c  * Copyright (C) 2009 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_undef
undef|#
directive|undef
name|GSEAL_ENABLE
end_undef

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmath/gimpmath.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoverlaybox.h"
end_include

begin_include
include|#
directive|include
file|"gimpoverlaychild.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_overlay_child_transform_bounds
parameter_list|(
name|GimpOverlayChild
modifier|*
name|child
parameter_list|,
name|GdkRectangle
modifier|*
name|bounds_child
parameter_list|,
name|GdkRectangle
modifier|*
name|bounds_box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_child_from_embedder
parameter_list|(
name|GdkWindow
modifier|*
name|child_window
parameter_list|,
name|gdouble
name|box_x
parameter_list|,
name|gdouble
name|box_y
parameter_list|,
name|gdouble
modifier|*
name|child_x
parameter_list|,
name|gdouble
modifier|*
name|child_y
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_child_to_embedder
parameter_list|(
name|GdkWindow
modifier|*
name|child_window
parameter_list|,
name|gdouble
name|child_x
parameter_list|,
name|gdouble
name|child_y
parameter_list|,
name|gdouble
modifier|*
name|box_x
parameter_list|,
name|gdouble
modifier|*
name|box_y
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpOverlayChild
modifier|*
DECL|function|gimp_overlay_child_new (GimpOverlayBox * box,GtkWidget * widget,gdouble xalign,gdouble yalign,gdouble angle,gdouble opacity)
name|gimp_overlay_child_new
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|xalign
parameter_list|,
name|gdouble
name|yalign
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
block|{
name|GimpOverlayChild
modifier|*
name|child
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|child
operator|=
name|g_slice_new0
argument_list|(
name|GimpOverlayChild
argument_list|)
expr_stmt|;
name|child
operator|->
name|widget
operator|=
name|widget
expr_stmt|;
name|child
operator|->
name|xalign
operator|=
name|CLAMP
argument_list|(
name|xalign
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|child
operator|->
name|yalign
operator|=
name|CLAMP
argument_list|(
name|yalign
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|child
operator|->
name|x
operator|=
literal|0.0
expr_stmt|;
name|child
operator|->
name|y
operator|=
literal|0.0
expr_stmt|;
name|child
operator|->
name|has_position
operator|=
name|FALSE
expr_stmt|;
name|child
operator|->
name|angle
operator|=
name|angle
expr_stmt|;
name|child
operator|->
name|opacity
operator|=
name|CLAMP
argument_list|(
name|opacity
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|cairo_matrix_init_identity
argument_list|(
operator|&
name|child
operator|->
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_REALIZED
argument_list|(
name|box
argument_list|)
condition|)
name|gimp_overlay_child_realize
argument_list|(
name|box
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|gtk_widget_set_parent
argument_list|(
name|widget
argument_list|,
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|child
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_child_free (GimpOverlayBox * box,GimpOverlayChild * child)
name|gimp_overlay_child_free
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|child
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_unparent
argument_list|(
name|child
operator|->
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_REALIZED
argument_list|(
name|box
argument_list|)
condition|)
name|gimp_overlay_child_unrealize
argument_list|(
name|box
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpOverlayChild
argument_list|,
name|child
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpOverlayChild
modifier|*
DECL|function|gimp_overlay_child_find (GimpOverlayBox * box,GtkWidget * widget)
name|gimp_overlay_child_find
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gtk_widget_get_parent
argument_list|(
name|widget
argument_list|)
operator|==
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|box
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
name|GimpOverlayChild
modifier|*
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|child
operator|->
name|widget
operator|==
name|widget
condition|)
return|return
name|child
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_child_realize (GimpOverlayBox * box,GimpOverlayChild * child)
name|gimp_overlay_child_realize
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|GtkAllocation
name|child_allocation
decl_stmt|;
name|GdkWindowAttr
name|attributes
decl_stmt|;
name|gint
name|attributes_mask
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|child
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|widget
operator|=
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|display
operator|=
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_widget_get_visible
argument_list|(
name|child
operator|->
name|widget
argument_list|)
condition|)
block|{
name|attributes
operator|.
name|width
operator|=
name|child_allocation
operator|.
name|width
expr_stmt|;
name|attributes
operator|.
name|height
operator|=
name|child_allocation
operator|.
name|height
expr_stmt|;
block|}
else|else
block|{
name|attributes
operator|.
name|width
operator|=
literal|1
expr_stmt|;
name|attributes
operator|.
name|height
operator|=
literal|1
expr_stmt|;
block|}
name|attributes
operator|.
name|x
operator|=
name|child_allocation
operator|.
name|x
expr_stmt|;
name|attributes
operator|.
name|y
operator|=
name|child_allocation
operator|.
name|y
expr_stmt|;
name|attributes
operator|.
name|window_type
operator|=
name|GDK_WINDOW_OFFSCREEN
expr_stmt|;
name|attributes
operator|.
name|wclass
operator|=
name|GDK_INPUT_OUTPUT
expr_stmt|;
name|attributes
operator|.
name|visual
operator|=
name|gtk_widget_get_visual
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|attributes
operator|.
name|colormap
operator|=
name|gtk_widget_get_colormap
argument_list|(
name|widget
argument_list|)
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
name|attributes
operator|.
name|cursor
operator|=
name|gdk_cursor_new_for_display
argument_list|(
name|display
argument_list|,
name|GDK_LEFT_PTR
argument_list|)
expr_stmt|;
name|attributes_mask
operator|=
operator|(
name|GDK_WA_X
operator||
name|GDK_WA_Y
operator||
name|GDK_WA_VISUAL
operator||
name|GDK_WA_COLORMAP
operator||
name|GDK_WA_CURSOR
operator|)
expr_stmt|;
name|child
operator|->
name|window
operator|=
name|gdk_window_new
argument_list|(
name|gtk_widget_get_root_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|attributes
argument_list|,
name|attributes_mask
argument_list|)
expr_stmt|;
name|gdk_window_set_user_data
argument_list|(
name|child
operator|->
name|window
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_set_parent_window
argument_list|(
name|child
operator|->
name|widget
argument_list|,
name|child
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_offscreen_window_set_embedder
argument_list|(
name|child
operator|->
name|window
argument_list|,
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_cursor_unref
argument_list|(
name|attributes
operator|.
name|cursor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|child
operator|->
name|window
argument_list|,
literal|"from-embedder"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_overlay_child_from_embedder
argument_list|)
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|child
operator|->
name|window
argument_list|,
literal|"to-embedder"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_overlay_child_to_embedder
argument_list|)
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|gtk_style_set_background
argument_list|(
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
argument_list|,
name|child
operator|->
name|window
argument_list|,
name|GTK_STATE_NORMAL
argument_list|)
expr_stmt|;
name|gdk_window_show
argument_list|(
name|child
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_child_unrealize (GimpOverlayBox * box,GimpOverlayChild * child)
name|gimp_overlay_child_unrealize
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|child
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gdk_window_set_user_data
argument_list|(
name|child
operator|->
name|window
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_window_destroy
argument_list|(
name|child
operator|->
name|window
argument_list|)
expr_stmt|;
name|child
operator|->
name|window
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_child_size_request (GimpOverlayBox * box,GimpOverlayChild * child)
name|gimp_overlay_child_size_request
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|)
block|{
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|child
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_size_request
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_child_size_allocate (GimpOverlayBox * box,GimpOverlayChild * child)
name|gimp_overlay_child_size_allocate
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|GtkAllocation
name|child_allocation
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|child
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|widget
operator|=
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|gtk_widget_get_child_requisition
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
name|child_allocation
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|child_allocation
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|child_allocation
operator|.
name|width
operator|=
name|child_requisition
operator|.
name|width
expr_stmt|;
name|child_allocation
operator|.
name|height
operator|=
name|child_requisition
operator|.
name|height
expr_stmt|;
name|gtk_widget_size_allocate
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_REALIZED
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GdkRectangle
name|old_allocation
decl_stmt|;
name|GdkRectangle
name|old_bounds
decl_stmt|;
name|gdk_window_get_position
argument_list|(
name|child
operator|->
name|window
argument_list|,
operator|&
name|old_allocation
operator|.
name|x
argument_list|,
operator|&
name|old_allocation
operator|.
name|y
argument_list|)
expr_stmt|;
name|gdk_drawable_get_size
argument_list|(
name|child
operator|->
name|window
argument_list|,
operator|&
name|old_allocation
operator|.
name|width
argument_list|,
operator|&
name|old_allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|gimp_overlay_child_transform_bounds
argument_list|(
name|child
argument_list|,
operator|&
name|old_allocation
argument_list|,
operator|&
name|old_bounds
argument_list|)
expr_stmt|;
name|gdk_window_invalidate_rect
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|old_bounds
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gdk_window_move_resize
argument_list|(
name|child
operator|->
name|window
argument_list|,
name|child_allocation
operator|.
name|x
argument_list|,
name|child_allocation
operator|.
name|y
argument_list|,
name|child_allocation
operator|.
name|width
argument_list|,
name|child_allocation
operator|.
name|height
argument_list|)
expr_stmt|;
block|}
name|cairo_matrix_init_identity
argument_list|(
operator|&
name|child
operator|->
name|matrix
argument_list|)
expr_stmt|;
comment|/* local transform */
name|cairo_matrix_rotate
argument_list|(
operator|&
name|child
operator|->
name|matrix
argument_list|,
name|child
operator|->
name|angle
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
operator|->
name|has_position
condition|)
block|{
name|x
operator|=
name|child
operator|->
name|x
expr_stmt|;
name|y
operator|=
name|child
operator|->
name|y
expr_stmt|;
block|}
else|else
block|{
name|GdkRectangle
name|bounds
decl_stmt|;
name|gint
name|border
decl_stmt|;
name|gint
name|available_width
decl_stmt|;
name|gint
name|available_height
decl_stmt|;
name|gimp_overlay_child_transform_bounds
argument_list|(
name|child
argument_list|,
operator|&
name|child_allocation
argument_list|,
operator|&
name|bounds
argument_list|)
expr_stmt|;
name|border
operator|=
name|gtk_container_get_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|available_width
operator|=
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|border
expr_stmt|;
name|available_height
operator|=
name|allocation
operator|.
name|height
operator|-
literal|2
operator|*
name|border
expr_stmt|;
name|x
operator|=
name|border
expr_stmt|;
name|y
operator|=
name|border
expr_stmt|;
if|if
condition|(
name|available_width
operator|>
name|bounds
operator|.
name|width
condition|)
name|x
operator|+=
name|child
operator|->
name|xalign
operator|*
operator|(
name|available_width
operator|-
name|bounds
operator|.
name|width
operator|)
operator|-
name|bounds
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|available_height
operator|>
name|bounds
operator|.
name|height
condition|)
name|y
operator|+=
name|child
operator|->
name|yalign
operator|*
operator|(
name|available_height
operator|-
name|bounds
operator|.
name|height
operator|)
operator|-
name|bounds
operator|.
name|y
expr_stmt|;
block|}
name|cairo_matrix_init_translate
argument_list|(
operator|&
name|child
operator|->
name|matrix
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
comment|/* local transform */
name|cairo_matrix_rotate
argument_list|(
operator|&
name|child
operator|->
name|matrix
argument_list|,
name|child
operator|->
name|angle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_overlay_child_expose (GimpOverlayBox * box,GimpOverlayChild * child,GdkEventExpose * event)
name|gimp_overlay_child_expose
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|child
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|event
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|widget
operator|=
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
expr_stmt|;
if|if
condition|(
name|event
operator|->
name|window
operator|==
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GtkAllocation
name|child_allocation
decl_stmt|;
name|GdkRectangle
name|bounds
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
name|gimp_overlay_child_transform_bounds
argument_list|(
name|child
argument_list|,
operator|&
name|child_allocation
argument_list|,
operator|&
name|bounds
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_widget_get_visible
argument_list|(
name|child
operator|->
name|widget
argument_list|)
operator|&&
name|gdk_rectangle_intersect
argument_list|(
operator|&
name|event
operator|->
name|area
argument_list|,
operator|&
name|bounds
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GdkPixmap
modifier|*
name|pixmap
init|=
name|gdk_offscreen_window_get_pixmap
argument_list|(
name|child
operator|->
name|window
argument_list|)
decl_stmt|;
name|cairo_t
modifier|*
name|cr
init|=
name|gdk_cairo_create
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|cairo_transform
argument_list|(
name|cr
argument_list|,
operator|&
name|child
operator|->
name|matrix
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_pixmap
argument_list|(
name|cr
argument_list|,
name|pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_paint_with_alpha
argument_list|(
name|cr
argument_list|,
name|child
operator|->
name|opacity
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|event
operator|->
name|window
operator|==
name|child
operator|->
name|window
condition|)
block|{
name|gtk_paint_flat_box
argument_list|(
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
argument_list|,
name|event
operator|->
name|window
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_NONE
argument_list|,
operator|&
name|event
operator|->
name|area
argument_list|,
name|widget
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_propagate_expose
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|,
name|child
operator|->
name|widget
argument_list|,
name|event
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_overlay_child_damage (GimpOverlayBox * box,GimpOverlayChild * child,GdkEventExpose * event)
name|gimp_overlay_child_damage
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|child
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|event
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|widget
operator|=
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
expr_stmt|;
if|if
condition|(
name|event
operator|->
name|window
operator|==
name|child
operator|->
name|window
condition|)
block|{
name|GdkRectangle
name|bounds
decl_stmt|;
name|gimp_overlay_child_transform_bounds
argument_list|(
name|child
argument_list|,
operator|&
name|event
operator|->
name|area
argument_list|,
operator|&
name|bounds
argument_list|)
expr_stmt|;
name|gdk_window_invalidate_rect
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|bounds
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_child_invalidate (GimpOverlayBox * box,GimpOverlayChild * child)
name|gimp_overlay_child_invalidate
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|)
block|{
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|child
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|window
operator|=
name|gtk_widget_get_window
argument_list|(
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|window
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|child
operator|->
name|widget
argument_list|)
condition|)
block|{
name|GtkAllocation
name|child_allocation
decl_stmt|;
name|GdkRectangle
name|bounds
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
name|gimp_overlay_child_transform_bounds
argument_list|(
name|child
argument_list|,
operator|&
name|child_allocation
argument_list|,
operator|&
name|bounds
argument_list|)
expr_stmt|;
name|gdk_window_invalidate_rect
argument_list|(
name|window
argument_list|,
operator|&
name|bounds
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_overlay_child_pick (GimpOverlayBox * box,GimpOverlayChild * child,gdouble box_x,gdouble box_y)
name|gimp_overlay_child_pick
parameter_list|(
name|GimpOverlayBox
modifier|*
name|box
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|,
name|gdouble
name|box_x
parameter_list|,
name|gdouble
name|box_y
parameter_list|)
block|{
name|GtkAllocation
name|child_allocation
decl_stmt|;
name|gdouble
name|child_x
decl_stmt|;
name|gdouble
name|child_y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|child
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_overlay_child_from_embedder
argument_list|(
name|child
operator|->
name|window
argument_list|,
name|box_x
argument_list|,
name|box_y
argument_list|,
operator|&
name|child_x
argument_list|,
operator|&
name|child_y
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
if|if
condition|(
name|child_x
operator|>=
literal|0
operator|&&
name|child_x
operator|<
name|child_allocation
operator|.
name|width
operator|&&
name|child_y
operator|>=
literal|0
operator|&&
name|child_y
operator|<
name|child_allocation
operator|.
name|height
condition|)
block|{
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_child_transform_bounds (GimpOverlayChild * child,GdkRectangle * bounds_child,GdkRectangle * bounds_box)
name|gimp_overlay_child_transform_bounds
parameter_list|(
name|GimpOverlayChild
modifier|*
name|child
parameter_list|,
name|GdkRectangle
modifier|*
name|bounds_child
parameter_list|,
name|GdkRectangle
modifier|*
name|bounds_box
parameter_list|)
block|{
name|gdouble
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|x3
decl_stmt|,
name|x4
decl_stmt|;
name|gdouble
name|y1
decl_stmt|,
name|y2
decl_stmt|,
name|y3
decl_stmt|,
name|y4
decl_stmt|;
name|x1
operator|=
name|bounds_child
operator|->
name|x
expr_stmt|;
name|y1
operator|=
name|bounds_child
operator|->
name|y
expr_stmt|;
name|x2
operator|=
name|bounds_child
operator|->
name|x
operator|+
name|bounds_child
operator|->
name|width
expr_stmt|;
name|y2
operator|=
name|bounds_child
operator|->
name|y
expr_stmt|;
name|x3
operator|=
name|bounds_child
operator|->
name|x
expr_stmt|;
name|y3
operator|=
name|bounds_child
operator|->
name|y
operator|+
name|bounds_child
operator|->
name|height
expr_stmt|;
name|x4
operator|=
name|bounds_child
operator|->
name|x
operator|+
name|bounds_child
operator|->
name|width
expr_stmt|;
name|y4
operator|=
name|bounds_child
operator|->
name|y
operator|+
name|bounds_child
operator|->
name|height
expr_stmt|;
name|cairo_matrix_transform_point
argument_list|(
operator|&
name|child
operator|->
name|matrix
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|cairo_matrix_transform_point
argument_list|(
operator|&
name|child
operator|->
name|matrix
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|cairo_matrix_transform_point
argument_list|(
operator|&
name|child
operator|->
name|matrix
argument_list|,
operator|&
name|x3
argument_list|,
operator|&
name|y3
argument_list|)
expr_stmt|;
name|cairo_matrix_transform_point
argument_list|(
operator|&
name|child
operator|->
name|matrix
argument_list|,
operator|&
name|x4
argument_list|,
operator|&
name|y4
argument_list|)
expr_stmt|;
DECL|macro|MIN4 (a,b,c,d)
define|#
directive|define
name|MIN4
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|,
name|d
parameter_list|)
value|MIN(MIN((a),(b)),MIN((c),(d)))
DECL|macro|MAX4 (a,b,c,d)
define|#
directive|define
name|MAX4
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|,
name|d
parameter_list|)
value|MAX(MAX((a),(b)),MAX((c),(d)))
name|bounds_box
operator|->
name|x
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|MIN4
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|,
name|x3
argument_list|,
name|x4
argument_list|)
argument_list|)
expr_stmt|;
name|bounds_box
operator|->
name|y
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|MIN4
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|,
name|y3
argument_list|,
name|y4
argument_list|)
argument_list|)
expr_stmt|;
name|bounds_box
operator|->
name|width
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
name|MAX4
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|,
name|x3
argument_list|,
name|x4
argument_list|)
argument_list|)
operator|-
name|bounds_box
operator|->
name|x
expr_stmt|;
name|bounds_box
operator|->
name|height
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
name|MAX4
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|,
name|y3
argument_list|,
name|y4
argument_list|)
argument_list|)
operator|-
name|bounds_box
operator|->
name|y
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_child_from_embedder (GdkWindow * child_window,gdouble box_x,gdouble box_y,gdouble * child_x,gdouble * child_y,GimpOverlayChild * child)
name|gimp_overlay_child_from_embedder
parameter_list|(
name|GdkWindow
modifier|*
name|child_window
parameter_list|,
name|gdouble
name|box_x
parameter_list|,
name|gdouble
name|box_y
parameter_list|,
name|gdouble
modifier|*
name|child_x
parameter_list|,
name|gdouble
modifier|*
name|child_y
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|)
block|{
name|cairo_matrix_t
name|inverse
init|=
name|child
operator|->
name|matrix
decl_stmt|;
operator|*
name|child_x
operator|=
name|box_x
expr_stmt|;
operator|*
name|child_y
operator|=
name|box_y
expr_stmt|;
name|cairo_matrix_invert
argument_list|(
operator|&
name|inverse
argument_list|)
expr_stmt|;
name|cairo_matrix_transform_point
argument_list|(
operator|&
name|inverse
argument_list|,
name|child_x
argument_list|,
name|child_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_child_to_embedder (GdkWindow * child_window,gdouble child_x,gdouble child_y,gdouble * box_x,gdouble * box_y,GimpOverlayChild * child)
name|gimp_overlay_child_to_embedder
parameter_list|(
name|GdkWindow
modifier|*
name|child_window
parameter_list|,
name|gdouble
name|child_x
parameter_list|,
name|gdouble
name|child_y
parameter_list|,
name|gdouble
modifier|*
name|box_x
parameter_list|,
name|gdouble
modifier|*
name|box_y
parameter_list|,
name|GimpOverlayChild
modifier|*
name|child
parameter_list|)
block|{
operator|*
name|box_x
operator|=
name|child_x
expr_stmt|;
operator|*
name|box_y
operator|=
name|child_y
expr_stmt|;
name|cairo_matrix_transform_point
argument_list|(
operator|&
name|child
operator|->
name|matrix
argument_list|,
name|box_x
argument_list|,
name|box_y
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

