begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbrushmenu.c  * Copyright (C) 1998 Andy Thomas                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_comment
comment|/* Idea is to have a function to call that returns a widget that   * completely controls the selection of a brush.  * you get a widget returned that you can use in a table say.  * In:- Initial brush name. Null means use current selection.  *      pointer to func to call when brush changes (GimpRunBrushCallback).  * Returned:- Pointer to a widget that you can use in UI.  *   * Widget simply made up of a preview widget (20x20) containing the brush  * mask and a button that can be clicked on to change the brush.  */
end_comment

begin_define
DECL|macro|BSEL_DATA_KEY
define|#
directive|define
name|BSEL_DATA_KEY
value|"__bsel_data"
end_define

begin_define
DECL|macro|CELL_SIZE
define|#
directive|define
name|CELL_SIZE
value|20
end_define

begin_define
DECL|macro|BRUSH_EVENT_MASK
define|#
directive|define
name|BRUSH_EVENT_MASK
value|GDK_EXPOSURE_MASK       | \                           GDK_BUTTON_PRESS_MASK   | \ 			  GDK_BUTTON_RELEASE_MASK | \                           GDK_BUTTON1_MOTION_MASK
end_define

begin_struct
DECL|struct|__brushes_sel
struct|struct
name|__brushes_sel
block|{
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|callback
name|GimpRunBrushCallback
name|callback
decl_stmt|;
DECL|member|brush_preview
name|GtkWidget
modifier|*
name|brush_preview
decl_stmt|;
DECL|member|device_brushpopup
name|GtkWidget
modifier|*
name|device_brushpopup
decl_stmt|;
DECL|member|device_brushpreview
name|GtkWidget
modifier|*
name|device_brushpreview
decl_stmt|;
DECL|member|button
name|GtkWidget
modifier|*
name|button
decl_stmt|;
DECL|member|top_hbox
name|GtkWidget
modifier|*
name|top_hbox
decl_stmt|;
DECL|member|brush_name
name|gchar
modifier|*
name|brush_name
decl_stmt|;
comment|/* Local copy */
DECL|member|opacity
name|gdouble
name|opacity
decl_stmt|;
DECL|member|spacing
name|gint
name|spacing
decl_stmt|;
DECL|member|paint_mode
name|gint
name|paint_mode
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|mask_data
name|guchar
modifier|*
name|mask_data
decl_stmt|;
comment|/* local copy */
DECL|member|brush_popup_pnt
name|gchar
modifier|*
name|brush_popup_pnt
decl_stmt|;
comment|/* used to control the popup */
DECL|member|data
name|gpointer
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|BSelect
typedef|typedef
name|struct
name|__brushes_sel
name|BSelect
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|brush_popup_open (BSelect * bsel,gint x,gint y)
name|brush_popup_open
parameter_list|(
name|BSelect
modifier|*
name|bsel
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|s
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
modifier|*
name|b
decl_stmt|;
name|gint
name|x_org
decl_stmt|;
name|gint
name|y_org
decl_stmt|;
name|gint
name|scr_w
decl_stmt|;
name|gint
name|scr_h
decl_stmt|;
comment|/* make sure the popup exists and is not visible */
if|if
condition|(
operator|!
name|bsel
operator|->
name|device_brushpopup
condition|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|bsel
operator|->
name|device_brushpopup
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
name|bsel
operator|->
name|device_brushpopup
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
name|bsel
operator|->
name|device_brushpreview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_GRAYSCALE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|bsel
operator|->
name|device_brushpreview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|bsel
operator|->
name|device_brushpreview
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_hide
argument_list|(
name|bsel
operator|->
name|device_brushpopup
argument_list|)
expr_stmt|;
block|}
comment|/* decide where to put the popup */
name|gdk_window_get_origin
argument_list|(
name|bsel
operator|->
name|brush_preview
operator|->
name|window
argument_list|,
operator|&
name|x_org
argument_list|,
operator|&
name|y_org
argument_list|)
expr_stmt|;
name|scr_w
operator|=
name|gdk_screen_width
argument_list|()
expr_stmt|;
name|scr_h
operator|=
name|gdk_screen_height
argument_list|()
expr_stmt|;
name|x
operator|=
name|x_org
operator|+
name|x
operator|-
operator|(
name|bsel
operator|->
name|width
operator|/
literal|2
operator|)
expr_stmt|;
name|y
operator|=
name|y_org
operator|+
name|y
operator|-
operator|(
name|bsel
operator|->
name|height
operator|/
literal|2
operator|)
expr_stmt|;
name|x
operator|=
operator|(
name|x
operator|<
literal|0
operator|)
condition|?
literal|0
else|:
name|x
expr_stmt|;
name|y
operator|=
operator|(
name|y
operator|<
literal|0
operator|)
condition|?
literal|0
else|:
name|y
expr_stmt|;
name|x
operator|=
operator|(
name|x
operator|+
name|bsel
operator|->
name|width
operator|>
name|scr_w
operator|)
condition|?
name|scr_w
operator|-
name|bsel
operator|->
name|width
else|:
name|x
expr_stmt|;
name|y
operator|=
operator|(
name|y
operator|+
name|bsel
operator|->
name|height
operator|>
name|scr_h
operator|)
condition|?
name|scr_h
operator|-
name|bsel
operator|->
name|height
else|:
name|y
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|bsel
operator|->
name|device_brushpreview
argument_list|)
argument_list|,
name|bsel
operator|->
name|width
argument_list|,
name|bsel
operator|->
name|height
argument_list|)
expr_stmt|;
name|gtk_window_move
argument_list|(
name|GTK_WINDOW
argument_list|(
name|bsel
operator|->
name|device_brushpopup
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|bsel
operator|->
name|device_brushpopup
argument_list|)
expr_stmt|;
comment|/*  Draw the brush  */
name|buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|bsel
operator|->
name|width
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|buf
argument_list|,
literal|255
argument_list|,
name|bsel
operator|->
name|width
argument_list|)
expr_stmt|;
name|src
operator|=
name|bsel
operator|->
name|mask_data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|bsel
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
name|int
name|j
decl_stmt|;
name|s
operator|=
name|src
expr_stmt|;
name|b
operator|=
name|buf
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|bsel
operator|->
name|width
condition|;
name|j
operator|++
control|)
operator|*
name|b
operator|++
operator|=
literal|255
operator|-
operator|*
name|s
operator|++
expr_stmt|;
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|bsel
operator|->
name|device_brushpreview
argument_list|)
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|bsel
operator|->
name|width
argument_list|)
expr_stmt|;
name|src
operator|+=
name|bsel
operator|->
name|width
expr_stmt|;
block|}
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|bsel
operator|->
name|device_brushpreview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_popup_close (BSelect * bsel)
name|brush_popup_close
parameter_list|(
name|BSelect
modifier|*
name|bsel
parameter_list|)
block|{
if|if
condition|(
name|bsel
operator|->
name|device_brushpopup
condition|)
name|gtk_widget_hide
argument_list|(
name|bsel
operator|->
name|device_brushpopup
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|brush_preview_events (GtkWidget * widget,GdkEvent * event,gpointer data)
name|brush_preview_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
name|BSelect
modifier|*
name|bsel
init|=
operator|(
name|BSelect
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|bsel
operator|->
name|mask_data
condition|)
block|{
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_EXPOSE
case|:
break|break;
case|case
name|GDK_BUTTON_PRESS
case|:
name|bevent
operator|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
expr_stmt|;
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
name|brush_popup_open
argument_list|(
name|bsel
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
break|break;
case|case
name|GDK_BUTTON_RELEASE
case|:
name|bevent
operator|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
expr_stmt|;
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
name|brush_popup_close
argument_list|(
name|bsel
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GDK_DELETE
case|:
break|break;
default|default:
break|break;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_preview_update (GtkWidget * brush_preview,gint brush_width,gint brush_height,const gchar * mask_data)
name|brush_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|brush_preview
parameter_list|,
name|gint
name|brush_width
parameter_list|,
name|gint
name|brush_height
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mask_data
parameter_list|)
block|{
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
modifier|*
name|b
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|s
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
name|gint
name|ystart
decl_stmt|,
name|yend
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/*  Draw the brush  */
name|buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
comment|/* Set buffer to white */
name|memset
argument_list|(
name|buf
argument_list|,
literal|255
argument_list|,
name|CELL_SIZE
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
name|CELL_SIZE
condition|;
name|i
operator|++
control|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|brush_preview
argument_list|)
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
comment|/* Limit to cell size */
name|width
operator|=
operator|(
name|brush_width
operator|>
name|CELL_SIZE
operator|)
condition|?
name|CELL_SIZE
else|:
name|brush_width
expr_stmt|;
name|height
operator|=
operator|(
name|brush_height
operator|>
name|CELL_SIZE
operator|)
condition|?
name|CELL_SIZE
else|:
name|brush_height
expr_stmt|;
name|offset_x
operator|=
operator|(
operator|(
name|CELL_SIZE
operator|-
name|width
operator|)
operator|/
literal|2
operator|)
expr_stmt|;
name|offset_y
operator|=
operator|(
operator|(
name|CELL_SIZE
operator|-
name|height
operator|)
operator|/
literal|2
operator|)
expr_stmt|;
name|ystart
operator|=
name|CLAMP
argument_list|(
name|offset_y
argument_list|,
literal|0
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|yend
operator|=
name|CLAMP
argument_list|(
name|offset_y
operator|+
name|height
argument_list|,
literal|0
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|src
operator|=
name|mask_data
expr_stmt|;
for|for
control|(
name|y
operator|=
name|ystart
init|;
name|y
operator|<
name|yend
condition|;
name|y
operator|++
control|)
block|{
name|gint
name|j
decl_stmt|;
name|s
operator|=
name|src
expr_stmt|;
name|b
operator|=
name|buf
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
operator|*
name|b
operator|++
operator|=
literal|255
operator|-
operator|*
name|s
operator|++
expr_stmt|;
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|brush_preview
argument_list|)
argument_list|,
name|buf
argument_list|,
name|offset_x
argument_list|,
name|y
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|src
operator|+=
name|brush_width
expr_stmt|;
block|}
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|brush_preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_select_invoker (const gchar * name,gdouble opacity,gint spacing,gint paint_mode,gint width,gint height,const guchar * mask_data,gboolean closing,gpointer data)
name|brush_select_invoker
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|gint
name|paint_mode
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask_data
parameter_list|,
name|gboolean
name|closing
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BSelect
modifier|*
name|bsel
init|=
operator|(
name|BSelect
operator|*
operator|)
name|data
decl_stmt|;
name|g_free
argument_list|(
name|bsel
operator|->
name|brush_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bsel
operator|->
name|mask_data
argument_list|)
expr_stmt|;
name|bsel
operator|->
name|brush_name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|bsel
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|bsel
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|bsel
operator|->
name|mask_data
operator|=
name|g_memdup
argument_list|(
name|mask_data
argument_list|,
name|width
operator|*
name|height
argument_list|)
expr_stmt|;
name|bsel
operator|->
name|opacity
operator|=
name|opacity
expr_stmt|;
name|bsel
operator|->
name|spacing
operator|=
name|spacing
expr_stmt|;
name|bsel
operator|->
name|paint_mode
operator|=
name|paint_mode
expr_stmt|;
name|brush_preview_update
argument_list|(
name|bsel
operator|->
name|brush_preview
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|mask_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|bsel
operator|->
name|callback
condition|)
name|bsel
operator|->
name|callback
argument_list|(
name|name
argument_list|,
name|opacity
argument_list|,
name|spacing
argument_list|,
name|paint_mode
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|mask_data
argument_list|,
name|closing
argument_list|,
name|bsel
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|closing
condition|)
name|bsel
operator|->
name|brush_popup_pnt
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_select_callback (GtkWidget * widget,gpointer data)
name|brush_select_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BSelect
modifier|*
name|bsel
init|=
operator|(
name|BSelect
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|bsel
operator|->
name|brush_popup_pnt
condition|)
block|{
comment|/*  calling gimp_brushes_set_popup() raises the dialog  */
name|gimp_brushes_set_popup
argument_list|(
name|bsel
operator|->
name|brush_popup_pnt
argument_list|,
name|bsel
operator|->
name|brush_name
argument_list|,
name|bsel
operator|->
name|opacity
argument_list|,
name|bsel
operator|->
name|spacing
argument_list|,
name|bsel
operator|->
name|paint_mode
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|bsel
operator|->
name|brush_popup_pnt
operator|=
name|gimp_interactive_selection_brush
argument_list|(
name|bsel
operator|->
name|title
condition|?
name|bsel
operator|->
name|title
else|:
name|_
argument_list|(
literal|"Brush Selection"
argument_list|)
argument_list|,
name|bsel
operator|->
name|brush_name
argument_list|,
name|bsel
operator|->
name|opacity
argument_list|,
name|bsel
operator|->
name|spacing
argument_list|,
name|bsel
operator|->
name|paint_mode
argument_list|,
name|brush_select_invoker
argument_list|,
name|bsel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_brush_select_widget:  * @title: Title of the dialog to use or %NULL to use the default title.  * @brush_name: Initial brush name or %NULL to use current selection.   * @opacity: Initial opacity. -1 means to use current opacity.  * @spacing: Initial spacing. -1 means to use current spacing.  * @paint_mode: Initial paint mode.  -1 means to use current paint mode.  * @callback: a function to call when the selected brush changes.  * @data: a pointer to arbitary data to be used in the call to @callback.  *  * Creates a new #GtkWidget that completely controls the selection of a   * #GimpBrush.  This widget is suitable for placement in a table in a  * plug-in dialog.  *  * Returns: A #GtkWidget that you can use in your UI.  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_brush_select_widget (const gchar * title,const gchar * brush_name,gdouble opacity,gint spacing,GimpLayerModeEffects paint_mode,GimpRunBrushCallback callback,gpointer data)
name|gimp_brush_select_widget
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|brush_name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpRunBrushCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|brush
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|init_spacing
decl_stmt|;
name|GimpLayerModeEffects
name|init_paint_mode
decl_stmt|;
name|gdouble
name|init_opacity
decl_stmt|;
name|gint
name|mask_data_size
decl_stmt|;
name|guint8
modifier|*
name|mask_data
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|BSelect
modifier|*
name|bsel
decl_stmt|;
name|bsel
operator|=
name|g_new0
argument_list|(
name|BSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
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
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|brush
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_GRAYSCALE
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|brush
argument_list|)
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|brush
argument_list|,
name|BRUSH_EVENT_MASK
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|brush
argument_list|,
literal|"event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_preview_events
argument_list|)
argument_list|,
name|bsel
argument_list|)
expr_stmt|;
name|bsel
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|bsel
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|bsel
operator|->
name|device_brushpopup
operator|=
name|bsel
operator|->
name|device_brushpreview
operator|=
name|NULL
expr_stmt|;
name|bsel
operator|->
name|brush_preview
operator|=
name|brush
expr_stmt|;
name|bsel
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
comment|/* Do initial brush setup */
name|name
operator|=
name|gimp_brushes_get_brush_data
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|brush_name
argument_list|,
operator|&
name|init_opacity
argument_list|,
operator|&
name|init_spacing
argument_list|,
operator|&
name|init_paint_mode
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|mask_data_size
argument_list|,
operator|&
name|mask_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
condition|)
block|{
name|bsel
operator|->
name|brush_name
operator|=
name|name
expr_stmt|;
name|bsel
operator|->
name|opacity
operator|=
operator|(
name|opacity
operator|==
operator|-
literal|1.0
operator|)
condition|?
name|init_opacity
else|:
name|opacity
expr_stmt|;
name|bsel
operator|->
name|spacing
operator|=
operator|(
name|spacing
operator|==
operator|-
literal|1
operator|)
condition|?
name|init_spacing
else|:
name|spacing
expr_stmt|;
name|bsel
operator|->
name|paint_mode
operator|=
operator|(
name|paint_mode
operator|==
operator|-
literal|1
operator|)
condition|?
name|init_paint_mode
else|:
name|paint_mode
expr_stmt|;
name|bsel
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|bsel
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|bsel
operator|->
name|mask_data
operator|=
name|mask_data
expr_stmt|;
name|brush_preview_update
argument_list|(
name|bsel
operator|->
name|brush_preview
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|mask_data
argument_list|)
expr_stmt|;
block|}
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"... "
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|bsel
operator|->
name|button
operator|=
name|button
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_select_callback
argument_list|)
argument_list|,
name|bsel
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|BSEL_DATA_KEY
argument_list|,
name|bsel
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_select_widget_close_popup:  * @widget: A brush select widget.  *  * Closes the popup window associated with @widget.  */
end_comment

begin_function
name|void
DECL|function|gimp_brush_select_widget_close_popup (GtkWidget * widget)
name|gimp_brush_select_widget_close_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|BSelect
modifier|*
name|bsel
decl_stmt|;
name|bsel
operator|=
operator|(
name|BSelect
operator|*
operator|)
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|BSEL_DATA_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
name|bsel
operator|&&
name|bsel
operator|->
name|brush_popup_pnt
condition|)
block|{
name|gimp_brushes_close_popup
argument_list|(
name|bsel
operator|->
name|brush_popup_pnt
argument_list|)
expr_stmt|;
name|bsel
operator|->
name|brush_popup_pnt
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_brush_select_widget_set_popup:  * @widget: A brush select widget.  * @brush_name: Brush name to set; %NULL means no change.   * @opacity: Opacity to set. -1 means no change.  * @spacing: Spacing to set. -1 means no change.  * @paint_mode: Paint mode to set.  -1 means no change.  *  * Sets the current brush and other values for the brush  * select widget.  Calls the callback function if one was  * supplied in the call to gimp_brush_select_widget().  */
end_comment

begin_function
name|void
DECL|function|gimp_brush_select_widget_set_popup (GtkWidget * widget,const gchar * brush_name,gdouble opacity,gint spacing,GimpLayerModeEffects paint_mode)
name|gimp_brush_select_widget_set_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|brush_name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|init_spacing
decl_stmt|;
name|GimpLayerModeEffects
name|init_paint_mode
decl_stmt|;
name|gdouble
name|init_opacity
decl_stmt|;
name|gint
name|mask_data_size
decl_stmt|;
name|guint8
modifier|*
name|mask_data
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|BSelect
modifier|*
name|bsel
decl_stmt|;
name|bsel
operator|=
operator|(
name|BSelect
operator|*
operator|)
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|BSEL_DATA_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
name|bsel
condition|)
block|{
name|name
operator|=
name|gimp_brushes_get_brush_data
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|brush_name
argument_list|,
operator|&
name|init_opacity
argument_list|,
operator|&
name|init_spacing
argument_list|,
operator|&
name|init_paint_mode
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|mask_data_size
argument_list|,
operator|&
name|mask_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|opacity
operator|==
operator|-
literal|1.0
condition|)
name|opacity
operator|=
name|init_opacity
expr_stmt|;
if|if
condition|(
name|spacing
operator|==
operator|-
literal|1
condition|)
name|spacing
operator|=
name|init_spacing
expr_stmt|;
if|if
condition|(
name|paint_mode
operator|==
operator|-
literal|1
condition|)
name|paint_mode
operator|=
name|init_paint_mode
expr_stmt|;
name|brush_select_invoker
argument_list|(
name|brush_name
argument_list|,
name|opacity
argument_list|,
name|spacing
argument_list|,
name|paint_mode
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|mask_data
argument_list|,
literal|0
argument_list|,
name|bsel
argument_list|)
expr_stmt|;
if|if
condition|(
name|bsel
operator|->
name|brush_popup_pnt
condition|)
name|gimp_brushes_set_popup
argument_list|(
name|bsel
operator|->
name|brush_popup_pnt
argument_list|,
name|name
argument_list|,
name|opacity
argument_list|,
name|spacing
argument_list|,
name|paint_mode
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|mask_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

