begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-quick-mask.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcairo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-appearance.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-callbacks.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-draw.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-preview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scroll.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-selection.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-title.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagewindow.h"
end_include

begin_include
include|#
directive|include
file|"gimpnavigationeditor.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_vscrollbar_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_hscrollbar_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_display_shell_vscrollbar_update_range
parameter_list|(
name|GtkRange
modifier|*
name|range
parameter_list|,
name|GtkScrollType
name|scroll
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_display_shell_hscrollbar_update_range
parameter_list|(
name|GtkRange
modifier|*
name|range
parameter_list|,
name|GtkScrollType
name|scroll
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_canvas_expose_image
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_canvas_expose_drop_zone
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_canvas_realize (GtkWidget * canvas,GimpDisplayShell * shell)
name|gimp_display_shell_canvas_realize
parameter_list|(
name|GtkWidget
modifier|*
name|canvas
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpCanvasPaddingMode
name|padding_mode
decl_stmt|;
name|GimpRGB
name|padding_color
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|canvas
argument_list|)
expr_stmt|;
name|gimp_display_shell_get_padding
argument_list|(
name|shell
argument_list|,
operator|&
name|padding_mode
argument_list|,
operator|&
name|padding_color
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_padding
argument_list|(
name|shell
argument_list|,
name|padding_mode
argument_list|,
operator|&
name|padding_color
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|canvas
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|gimp_display_shell_title_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|shell
operator|->
name|disp_width
operator|=
name|allocation
operator|.
name|width
expr_stmt|;
name|shell
operator|->
name|disp_height
operator|=
name|allocation
operator|.
name|height
expr_stmt|;
comment|/*  set up the scrollbar observers  */
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|hsbdata
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_hscrollbar_update
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|vsbdata
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_vscrollbar_update
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|hsb
argument_list|,
literal|"change-value"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_hscrollbar_update_range
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|vsb
argument_list|,
literal|"change-value"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_vscrollbar_update_range
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
comment|/*  allow shrinking  */
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_canvas_size_allocate (GtkWidget * widget,GtkAllocation * allocation,GimpDisplayShell * shell)
name|gimp_display_shell_canvas_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
comment|/*  are we in destruction?  */
if|if
condition|(
operator|!
name|shell
operator|->
name|display
operator|||
operator|!
name|gimp_display_get_shell
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
return|return;
if|if
condition|(
operator|(
name|shell
operator|->
name|disp_width
operator|!=
name|allocation
operator|->
name|width
operator|)
operator|||
operator|(
name|shell
operator|->
name|disp_height
operator|!=
name|allocation
operator|->
name|height
operator|)
condition|)
block|{
if|if
condition|(
name|shell
operator|->
name|zoom_on_resize
operator|&&
name|shell
operator|->
name|disp_width
operator|>
literal|64
operator|&&
name|shell
operator|->
name|disp_height
operator|>
literal|64
operator|&&
name|allocation
operator|->
name|width
operator|>
literal|64
operator|&&
name|allocation
operator|->
name|height
operator|>
literal|64
condition|)
block|{
name|gdouble
name|scale
init|=
name|gimp_zoom_model_get_factor
argument_list|(
name|shell
operator|->
name|zoom
argument_list|)
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
comment|/* FIXME: The code is a bit of a mess */
comment|/*  multiply the zoom_factor with the ratio of the new and            *  old canvas diagonals            */
name|scale
operator|*=
operator|(
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|allocation
operator|->
name|width
argument_list|)
operator|+
name|SQR
argument_list|(
name|allocation
operator|->
name|height
argument_list|)
argument_list|)
operator|/
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|shell
operator|->
name|disp_width
argument_list|)
operator|+
name|SQR
argument_list|(
name|shell
operator|->
name|disp_height
argument_list|)
argument_list|)
operator|)
expr_stmt|;
name|offset_x
operator|=
name|UNSCALEX
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|offset_x
argument_list|)
expr_stmt|;
name|offset_y
operator|=
name|UNSCALEX
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_zoom_model_zoom
argument_list|(
name|shell
operator|->
name|zoom
argument_list|,
name|GIMP_ZOOM_TO
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|shell
operator|->
name|offset_x
operator|=
name|SCALEX
argument_list|(
name|shell
argument_list|,
name|offset_x
argument_list|)
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|=
name|SCALEY
argument_list|(
name|shell
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
block|}
name|shell
operator|->
name|disp_width
operator|=
name|allocation
operator|->
name|width
expr_stmt|;
name|shell
operator|->
name|disp_height
operator|=
name|allocation
operator|->
name|height
expr_stmt|;
comment|/* When we size-allocate due to resize of the top level window,        * we want some additional logic. Don't apply it on        * zoom_on_resize though.        */
if|if
condition|(
name|shell
operator|->
name|size_allocate_from_configure_event
operator|&&
operator|!
name|shell
operator|->
name|zoom_on_resize
condition|)
block|{
name|gboolean
name|center_horizontally
decl_stmt|;
name|gboolean
name|center_vertically
decl_stmt|;
name|gint
name|target_offset_x
decl_stmt|;
name|gint
name|target_offset_y
decl_stmt|;
name|gint
name|sw
decl_stmt|;
name|gint
name|sh
decl_stmt|;
name|gimp_display_shell_draw_get_scaled_image_size
argument_list|(
name|shell
argument_list|,
operator|&
name|sw
argument_list|,
operator|&
name|sh
argument_list|)
expr_stmt|;
name|center_horizontally
operator|=
name|sw
operator|<=
name|shell
operator|->
name|disp_width
expr_stmt|;
name|center_vertically
operator|=
name|sh
operator|<=
name|shell
operator|->
name|disp_height
expr_stmt|;
name|gimp_display_shell_scroll_center_image
argument_list|(
name|shell
argument_list|,
name|center_horizontally
argument_list|,
name|center_vertically
argument_list|)
expr_stmt|;
comment|/* This is basically the best we can do before we get an            * API for storing the image offset at the start of an            * image window resize using the mouse            */
name|target_offset_x
operator|=
name|shell
operator|->
name|offset_x
expr_stmt|;
name|target_offset_y
operator|=
name|shell
operator|->
name|offset_y
expr_stmt|;
if|if
condition|(
operator|!
name|center_horizontally
condition|)
block|{
name|target_offset_x
operator|=
name|MAX
argument_list|(
name|shell
operator|->
name|offset_x
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|center_vertically
condition|)
block|{
name|target_offset_y
operator|=
name|MAX
argument_list|(
name|shell
operator|->
name|offset_y
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gimp_display_shell_scroll_set_offset
argument_list|(
name|shell
argument_list|,
name|target_offset_x
argument_list|,
name|target_offset_y
argument_list|)
expr_stmt|;
block|}
name|gimp_display_shell_scroll_clamp_and_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_scaled
argument_list|(
name|shell
argument_list|)
expr_stmt|;
comment|/* Reset */
name|shell
operator|->
name|size_allocate_from_configure_event
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_is_double_buffered (GimpDisplayShell * shell)
name|gimp_display_shell_is_double_buffered
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
return|return
name|TRUE
return|;
comment|/* FIXME: repair this after cairo tool drawing is done */
comment|/*  always double-buffer if there are overlay children or a    *  transform preview, or they will flicker badly. Also double    *  buffer when we are editing paths.    */
if|#
directive|if
literal|0
block|if (GIMP_OVERLAY_BOX (shell->canvas)->children    ||       gimp_display_shell_get_show_transform (shell) ||       GIMP_IS_VECTOR_TOOL (tool_manager_get_active (shell->display->gimp)))     return TRUE;
endif|#
directive|endif
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_canvas_expose (GtkWidget * widget,GdkEventExpose * eevent,GimpDisplayShell * shell)
name|gimp_display_shell_canvas_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
comment|/*  are we in destruction?  */
if|if
condition|(
operator|!
name|shell
operator|->
name|display
operator|||
operator|!
name|gimp_display_get_shell
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
return|return
name|TRUE
return|;
comment|/*  ignore events on overlays  */
if|if
condition|(
name|eevent
operator|->
name|window
operator|==
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|cairo_t
modifier|*
name|cr
decl_stmt|;
if|if
condition|(
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
block|{
name|gimp_display_shell_pause
argument_list|(
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_display_shell_is_double_buffered
argument_list|(
name|shell
argument_list|)
condition|)
name|gdk_window_begin_paint_region
argument_list|(
name|eevent
operator|->
name|window
argument_list|,
name|eevent
operator|->
name|region
argument_list|)
expr_stmt|;
block|}
comment|/*  create the cairo_t after enabling double buffering, or we        *  will get the wrong window destination surface        */
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_cairo_region
argument_list|(
name|cr
argument_list|,
name|eevent
operator|->
name|region
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
block|{
name|gimp_display_shell_canvas_expose_image
argument_list|(
name|shell
argument_list|,
name|eevent
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_display_shell_canvas_expose_drop_zone
argument_list|(
name|shell
argument_list|,
name|eevent
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_canvas_expose_after (GtkWidget * widget,GdkEventExpose * eevent,GimpDisplayShell * shell)
name|gimp_display_shell_canvas_expose_after
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
comment|/*  are we in destruction?  */
if|if
condition|(
operator|!
name|shell
operator|->
name|display
operator|||
operator|!
name|gimp_display_get_shell
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
return|return
name|TRUE
return|;
comment|/*  ignore events on overlays  */
if|if
condition|(
name|eevent
operator|->
name|window
operator|==
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
condition|)
block|{
if|if
condition|(
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
block|{
if|if
condition|(
name|gimp_display_shell_is_double_buffered
argument_list|(
name|shell
argument_list|)
condition|)
name|gdk_window_end_paint
argument_list|(
name|eevent
operator|->
name|window
argument_list|)
expr_stmt|;
name|gimp_display_shell_resume
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_origin_button_press (GtkWidget * widget,GdkEventButton * event,GimpDisplayShell * shell)
name|gimp_display_shell_origin_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
operator|!
name|shell
operator|->
name|display
operator|->
name|gimp
operator|->
name|busy
condition|)
block|{
if|if
condition|(
name|event
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gboolean
name|unused
decl_stmt|;
name|g_signal_emit_by_name
argument_list|(
name|shell
argument_list|,
literal|"popup-menu"
argument_list|,
operator|&
name|unused
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* Return TRUE to stop signal emission so the button doesn't grab the    * pointer away from us.    */
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_quick_mask_button_press (GtkWidget * widget,GdkEventButton * bevent,GimpDisplayShell * shell)
name|gimp_display_shell_quick_mask_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
operator|(
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
operator|)
operator|&&
operator|(
name|bevent
operator|->
name|button
operator|==
literal|3
operator|)
condition|)
block|{
name|GimpImageWindow
modifier|*
name|window
init|=
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
decl_stmt|;
if|if
condition|(
name|window
condition|)
block|{
name|GimpUIManager
modifier|*
name|manager
init|=
name|gimp_image_window_get_ui_manager
argument_list|(
name|window
argument_list|)
decl_stmt|;
name|gimp_ui_manager_ui_popup
argument_list|(
name|manager
argument_list|,
literal|"/quick-mask-popup"
argument_list|,
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
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
block|}
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
DECL|function|gimp_display_shell_quick_mask_toggled (GtkWidget * widget,GimpDisplayShell * shell)
name|gimp_display_shell_quick_mask_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
decl_stmt|;
name|gboolean
name|active
init|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|active
operator|!=
name|gimp_image_get_quick_mask_state
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|gimp_image_set_quick_mask_state
argument_list|(
name|image
argument_list|,
name|active
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_nav_button_press (GtkWidget * widget,GdkEventButton * bevent,GimpDisplayShell * shell)
name|gimp_display_shell_nav_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
operator|(
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
operator|)
operator|&&
operator|(
name|bevent
operator|->
name|button
operator|==
literal|1
operator|)
condition|)
block|{
name|gimp_navigation_editor_popup
argument_list|(
name|shell
argument_list|,
name|widget
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_vscrollbar_update (GtkAdjustment * adjustment,GimpDisplayShell * shell)
name|gimp_display_shell_vscrollbar_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
comment|/* If we are panning with mouse, scrollbars are to be ignored    * or they will cause jitter in motion    */
if|if
condition|(
operator|!
name|shell
operator|->
name|scrolling
condition|)
name|gimp_display_shell_scroll
argument_list|(
name|shell
argument_list|,
literal|0
argument_list|,
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
operator|-
name|shell
operator|->
name|offset_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_hscrollbar_update (GtkAdjustment * adjustment,GimpDisplayShell * shell)
name|gimp_display_shell_hscrollbar_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
comment|/* If we are panning with mouse, scrollbars are to be ignored    * or they will cause jitter in motion    */
if|if
condition|(
operator|!
name|shell
operator|->
name|scrolling
condition|)
name|gimp_display_shell_scroll
argument_list|(
name|shell
argument_list|,
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
operator|-
name|shell
operator|->
name|offset_x
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_hscrollbar_update_range (GtkRange * range,GtkScrollType scroll,gdouble value,GimpDisplayShell * shell)
name|gimp_display_shell_hscrollbar_update_range
parameter_list|(
name|GtkRange
modifier|*
name|range
parameter_list|,
name|GtkScrollType
name|scroll
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
operator|!
name|shell
operator|->
name|display
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
operator|(
name|scroll
operator|==
name|GTK_SCROLL_JUMP
operator|)
operator|||
operator|(
name|scroll
operator|==
name|GTK_SCROLL_PAGE_BACKWARD
operator|)
operator|||
operator|(
name|scroll
operator|==
name|GTK_SCROLL_PAGE_FORWARD
operator|)
condition|)
return|return
name|FALSE
return|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|hsbdata
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_scroll_setup_hscrollbar
argument_list|(
name|shell
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|hsbdata
argument_list|)
argument_list|)
expr_stmt|;
comment|/* emits "changed" */
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_vscrollbar_update_range (GtkRange * range,GtkScrollType scroll,gdouble value,GimpDisplayShell * shell)
name|gimp_display_shell_vscrollbar_update_range
parameter_list|(
name|GtkRange
modifier|*
name|range
parameter_list|,
name|GtkScrollType
name|scroll
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
operator|!
name|shell
operator|->
name|display
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
operator|(
name|scroll
operator|==
name|GTK_SCROLL_JUMP
operator|)
operator|||
operator|(
name|scroll
operator|==
name|GTK_SCROLL_PAGE_BACKWARD
operator|)
operator|||
operator|(
name|scroll
operator|==
name|GTK_SCROLL_PAGE_FORWARD
operator|)
condition|)
return|return
name|FALSE
return|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|vsbdata
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_scroll_setup_vscrollbar
argument_list|(
name|shell
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|vsbdata
argument_list|)
argument_list|)
expr_stmt|;
comment|/* emits "changed" */
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_canvas_expose_image (GimpDisplayShell * shell,GdkEventExpose * eevent,cairo_t * cr)
name|gimp_display_shell_canvas_expose_image
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GdkRegion
modifier|*
name|clear_region
decl_stmt|;
name|GdkRegion
modifier|*
name|image_region
decl_stmt|;
name|GdkRectangle
name|image_rect
decl_stmt|;
name|GdkRectangle
modifier|*
name|rects
decl_stmt|;
name|gint
name|n_rects
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/*  first, clear the exposed part of the region that is outside the    *  image, which is the exposed region minus the image rectangle    */
name|clear_region
operator|=
name|gdk_region_copy
argument_list|(
name|eevent
operator|->
name|region
argument_list|)
expr_stmt|;
name|image_rect
operator|.
name|x
operator|=
operator|-
name|shell
operator|->
name|offset_x
expr_stmt|;
name|image_rect
operator|.
name|y
operator|=
operator|-
name|shell
operator|->
name|offset_y
expr_stmt|;
name|gimp_display_shell_draw_get_scaled_image_size
argument_list|(
name|shell
argument_list|,
operator|&
name|image_rect
operator|.
name|width
argument_list|,
operator|&
name|image_rect
operator|.
name|height
argument_list|)
expr_stmt|;
name|image_region
operator|=
name|gdk_region_rectangle
argument_list|(
operator|&
name|image_rect
argument_list|)
expr_stmt|;
name|gdk_region_subtract
argument_list|(
name|clear_region
argument_list|,
name|image_region
argument_list|)
expr_stmt|;
name|gdk_region_destroy
argument_list|(
name|image_region
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gdk_region_empty
argument_list|(
name|clear_region
argument_list|)
condition|)
block|{
name|gdk_region_get_rectangles
argument_list|(
name|clear_region
argument_list|,
operator|&
name|rects
argument_list|,
operator|&
name|n_rects
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
name|n_rects
condition|;
name|i
operator|++
control|)
name|gdk_window_clear_area
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|y
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|width
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|height
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rects
argument_list|)
expr_stmt|;
block|}
comment|/*  then, draw the exposed part of the region that is inside the    *  image, which is the exposed region minus the region used for    *  clearing above    */
name|image_region
operator|=
name|gdk_region_copy
argument_list|(
name|eevent
operator|->
name|region
argument_list|)
expr_stmt|;
name|gdk_region_subtract
argument_list|(
name|image_region
argument_list|,
name|clear_region
argument_list|)
expr_stmt|;
name|gdk_region_destroy
argument_list|(
name|clear_region
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gdk_region_empty
argument_list|(
name|image_region
argument_list|)
condition|)
block|{
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gimp_display_shell_draw_checkerboard
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|,
name|image_rect
operator|.
name|x
argument_list|,
name|image_rect
operator|.
name|y
argument_list|,
name|image_rect
operator|.
name|width
argument_list|,
name|image_rect
operator|.
name|height
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gdk_region_get_rectangles
argument_list|(
name|image_region
argument_list|,
operator|&
name|rects
argument_list|,
operator|&
name|n_rects
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
name|n_rects
condition|;
name|i
operator|++
control|)
name|gimp_display_shell_draw_image
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|y
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|width
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|height
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rects
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
name|gdk_region_destroy
argument_list|(
name|image_region
argument_list|)
expr_stmt|;
comment|/*  finally, draw all the remaining image window stuff on top    */
comment|/* draw the transform tool preview */
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gimp_display_shell_preview_transform
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
comment|/* draw canvas items */
name|gimp_canvas_item_draw
argument_list|(
name|shell
operator|->
name|canvas_item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
comment|/* restart (and recalculate) the selection boundaries */
name|gimp_display_shell_selection_restart
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_canvas_expose_drop_zone (GimpDisplayShell * shell,GdkEventExpose * eevent,cairo_t * cr)
name|gimp_display_shell_canvas_expose_drop_zone
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GdkRectangle
modifier|*
name|rects
decl_stmt|;
name|gint
name|n_rects
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gdk_region_get_rectangles
argument_list|(
name|eevent
operator|->
name|region
argument_list|,
operator|&
name|rects
argument_list|,
operator|&
name|n_rects
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
name|n_rects
condition|;
name|i
operator|++
control|)
block|{
name|gdk_window_clear_area
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|y
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|width
argument_list|,
name|rects
index|[
name|i
index|]
operator|.
name|height
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|rects
argument_list|)
expr_stmt|;
name|gimp_cairo_draw_drop_wilber
argument_list|(
name|shell
operator|->
name|canvas
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

