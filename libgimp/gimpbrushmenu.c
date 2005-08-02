begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbrushmenu.c  * Copyright (C) 1998 Andy Thomas  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_define
DECL|macro|BRUSH_SELECT_DATA_KEY
define|#
directive|define
name|BRUSH_SELECT_DATA_KEY
value|"gimp-brush-select-data"
end_define

begin_define
DECL|macro|CELL_SIZE
define|#
directive|define
name|CELL_SIZE
value|20
end_define

begin_typedef
DECL|typedef|BrushSelect
typedef|typedef
name|struct
name|_BrushSelect
name|BrushSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_BrushSelect
struct|struct
name|_BrushSelect
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
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|button
name|GtkWidget
modifier|*
name|button
decl_stmt|;
DECL|member|popup
name|GtkWidget
modifier|*
name|popup
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
name|GimpLayerModeEffects
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
DECL|member|temp_brush_callback
specifier|const
name|gchar
modifier|*
name|temp_brush_callback
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_widget_callback
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
name|GimpLayerModeEffects
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_widget_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_widget_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_select_preview_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|gint
name|brush_width
parameter_list|,
name|gint
name|brush_height
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_preview_resize
parameter_list|(
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_popup_open
parameter_list|(
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_popup_close
parameter_list|(
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_drag_data_received
parameter_list|(
name|GtkWidget
modifier|*
name|preview
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
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|target
specifier|static
specifier|const
name|GtkTargetEntry
name|target
init|=
block|{
literal|"application/x-gimp-brush-name"
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**  * gimp_brush_select_widget_new:  * @title:      Title of the dialog to use or %NULL to use the default title.  * @brush_name: Initial brush name or %NULL to use current selection.  * @opacity:    Initial opacity. -1 means to use current opacity.  * @spacing:    Initial spacing. -1 means to use current spacing.  * @paint_mode: Initial paint mode.  -1 means to use current paint mode.  * @callback:   A function to call when the selected brush changes.  * @data:       A pointer to arbitary data to be used in the call to @callback.  *  * Creates a new #GtkWidget that completely controls the selection of  * a #GimpBrush. This widget is suitable for placement in a table in  * a plug-in dialog.  *  * Returns: A #GtkWidget that you can use in your UI.  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_brush_select_widget_new (const gchar * title,const gchar * brush_name,gdouble opacity,gint spacing,GimpLayerModeEffects paint_mode,GimpRunBrushCallback callback,gpointer data)
name|gimp_brush_select_widget_new
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
name|BrushSelect
modifier|*
name|brush_sel
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|gint
name|mask_bpp
decl_stmt|;
name|gint
name|mask_data_size
decl_stmt|;
name|gint
name|color_bpp
decl_stmt|;
name|gint
name|color_data_size
decl_stmt|;
name|guint8
modifier|*
name|color_data
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|title
condition|)
name|title
operator|=
name|_
argument_list|(
literal|"Brush Selection"
argument_list|)
expr_stmt|;
name|brush_sel
operator|=
name|g_new0
argument_list|(
name|BrushSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|brush_sel
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|brush_sel
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|brush_sel
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
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
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|brush_sel
operator|->
name|preview
operator|=
name|gimp_preview_area_new
argument_list|()
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|brush_sel
operator|->
name|preview
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|brush_sel
operator|->
name|preview
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|brush_sel
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|brush_sel
operator|->
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|brush_sel
operator|->
name|preview
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_select_preview_resize
argument_list|)
argument_list|,
name|brush_sel
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|brush_sel
operator|->
name|preview
argument_list|,
literal|"event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_select_preview_events
argument_list|)
argument_list|,
name|brush_sel
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|brush_sel
operator|->
name|preview
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
operator|&
name|target
argument_list|,
literal|1
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|brush_sel
operator|->
name|preview
argument_list|,
literal|"drag-data-received"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_select_drag_data_received
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|brush_sel
operator|->
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Browse..."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|brush_sel
operator|->
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
name|brush_sel
operator|->
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|brush_sel
operator|->
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_select_widget_clicked
argument_list|)
argument_list|,
name|brush_sel
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|brush_sel
operator|->
name|button
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_select_widget_destroy
argument_list|)
argument_list|,
name|brush_sel
argument_list|)
expr_stmt|;
comment|/* Do initial brush setup */
if|if
condition|(
operator|!
name|brush_name
operator|||
operator|!
name|strlen
argument_list|(
name|brush_name
argument_list|)
condition|)
name|brush_sel
operator|->
name|brush_name
operator|=
name|gimp_context_get_brush
argument_list|()
expr_stmt|;
else|else
name|brush_sel
operator|->
name|brush_name
operator|=
name|g_strdup
argument_list|(
name|brush_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_brush_get_pixels
argument_list|(
name|brush_sel
operator|->
name|brush_name
argument_list|,
operator|&
name|brush_sel
operator|->
name|width
argument_list|,
operator|&
name|brush_sel
operator|->
name|height
argument_list|,
operator|&
name|mask_bpp
argument_list|,
operator|&
name|mask_data_size
argument_list|,
operator|&
name|brush_sel
operator|->
name|mask_data
argument_list|,
operator|&
name|color_bpp
argument_list|,
operator|&
name|color_data_size
argument_list|,
operator|&
name|color_data
argument_list|)
condition|)
block|{
if|if
condition|(
name|color_data
condition|)
name|g_free
argument_list|(
name|color_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|opacity
operator|==
operator|-
literal|1
condition|)
name|brush_sel
operator|->
name|opacity
operator|=
name|gimp_context_get_opacity
argument_list|()
expr_stmt|;
else|else
name|brush_sel
operator|->
name|opacity
operator|=
name|opacity
expr_stmt|;
if|if
condition|(
name|paint_mode
operator|==
operator|-
literal|1
condition|)
name|brush_sel
operator|->
name|paint_mode
operator|=
name|gimp_context_get_paint_mode
argument_list|()
expr_stmt|;
else|else
name|brush_sel
operator|->
name|paint_mode
operator|=
name|paint_mode
expr_stmt|;
if|if
condition|(
name|spacing
operator|==
operator|-
literal|1
condition|)
name|gimp_brush_get_spacing
argument_list|(
name|brush_sel
operator|->
name|brush_name
argument_list|,
operator|&
name|brush_sel
operator|->
name|spacing
argument_list|)
expr_stmt|;
else|else
name|brush_sel
operator|->
name|spacing
operator|=
name|spacing
expr_stmt|;
block|}
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|BRUSH_SELECT_DATA_KEY
argument_list|,
name|brush_sel
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_select_widget_close:  * @widget: A brush select widget.  *  * Closes the popup window associated with @widget.  */
end_comment

begin_function
name|void
DECL|function|gimp_brush_select_widget_close (GtkWidget * widget)
name|gimp_brush_select_widget_close
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|BrushSelect
modifier|*
name|brush_sel
decl_stmt|;
name|brush_sel
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|BRUSH_SELECT_DATA_KEY
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|brush_sel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush_sel
operator|->
name|temp_brush_callback
condition|)
block|{
name|gimp_brush_select_destroy
argument_list|(
name|brush_sel
operator|->
name|temp_brush_callback
argument_list|)
expr_stmt|;
name|brush_sel
operator|->
name|temp_brush_callback
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_brush_select_widget_set;  * @widget:     A brush select widget.  * @brush_name: Brush name to set; %NULL means no change.  * @opacity:    Opacity to set. -1.0 means no change.  * @spacing:    Spacing to set. -1 means no change.  * @paint_mode: Paint mode to set.  -1 means no change.  *  * Sets the current brush and other values for the brush select  * widget.  Calls the callback function if one was supplied in the  * call to gimp_brush_select_widget_new().  */
end_comment

begin_function
name|void
DECL|function|gimp_brush_select_widget_set (GtkWidget * widget,const gchar * brush_name,gdouble opacity,gint spacing,GimpLayerModeEffects paint_mode)
name|gimp_brush_select_widget_set
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
name|BrushSelect
modifier|*
name|brush_sel
decl_stmt|;
name|brush_sel
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|BRUSH_SELECT_DATA_KEY
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|brush_sel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush_sel
operator|->
name|temp_brush_callback
condition|)
block|{
name|gimp_brushes_set_popup
argument_list|(
name|brush_sel
operator|->
name|temp_brush_callback
argument_list|,
name|brush_name
argument_list|,
name|opacity
argument_list|,
name|spacing
argument_list|,
name|paint_mode
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|mask_bpp
decl_stmt|;
name|gint
name|mask_data_size
decl_stmt|;
name|guint8
modifier|*
name|mask_data
decl_stmt|;
name|gint
name|color_bpp
decl_stmt|;
name|gint
name|color_data_size
decl_stmt|;
name|guint8
modifier|*
name|color_data
decl_stmt|;
if|if
condition|(
operator|!
name|brush_name
operator|||
operator|!
name|strlen
argument_list|(
name|brush_name
argument_list|)
condition|)
name|name
operator|=
name|gimp_context_get_brush
argument_list|()
expr_stmt|;
else|else
name|name
operator|=
name|g_strdup
argument_list|(
name|brush_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_brush_get_pixels
argument_list|(
name|name
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|mask_bpp
argument_list|,
operator|&
name|mask_data_size
argument_list|,
operator|&
name|mask_data
argument_list|,
operator|&
name|color_bpp
argument_list|,
operator|&
name|color_data_size
argument_list|,
operator|&
name|color_data
argument_list|)
condition|)
block|{
if|if
condition|(
name|color_data
condition|)
name|g_free
argument_list|(
name|color_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|opacity
operator|<
literal|0.0
condition|)
name|opacity
operator|=
name|gimp_context_get_opacity
argument_list|()
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
name|gimp_context_get_paint_mode
argument_list|()
expr_stmt|;
if|if
condition|(
name|spacing
operator|==
operator|-
literal|1
condition|)
name|gimp_brush_get_spacing
argument_list|(
name|name
argument_list|,
operator|&
name|spacing
argument_list|)
expr_stmt|;
name|gimp_brush_select_widget_callback
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
name|FALSE
argument_list|,
name|brush_sel
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|mask_data
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_widget_callback (const gchar * name,gdouble opacity,gint spacing,GimpLayerModeEffects paint_mode,gint width,gint height,const guchar * mask_data,gboolean closing,gpointer data)
name|gimp_brush_select_widget_callback
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
name|GimpLayerModeEffects
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
name|BrushSelect
modifier|*
name|brush_sel
init|=
operator|(
name|BrushSelect
operator|*
operator|)
name|data
decl_stmt|;
name|g_free
argument_list|(
name|brush_sel
operator|->
name|brush_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|brush_sel
operator|->
name|mask_data
argument_list|)
expr_stmt|;
name|brush_sel
operator|->
name|brush_name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|brush_sel
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|brush_sel
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|brush_sel
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
name|brush_sel
operator|->
name|opacity
operator|=
name|opacity
expr_stmt|;
name|brush_sel
operator|->
name|spacing
operator|=
name|spacing
expr_stmt|;
name|brush_sel
operator|->
name|paint_mode
operator|=
name|paint_mode
expr_stmt|;
name|gimp_brush_select_preview_update
argument_list|(
name|brush_sel
operator|->
name|preview
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
name|brush_sel
operator|->
name|callback
condition|)
name|brush_sel
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
name|brush_sel
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|closing
condition|)
name|brush_sel
operator|->
name|temp_brush_callback
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_widget_clicked (GtkWidget * widget,BrushSelect * brush_sel)
name|gimp_brush_select_widget_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|)
block|{
if|if
condition|(
name|brush_sel
operator|->
name|temp_brush_callback
condition|)
block|{
comment|/*  calling gimp_brushes_set_popup() raises the dialog  */
name|gimp_brushes_set_popup
argument_list|(
name|brush_sel
operator|->
name|temp_brush_callback
argument_list|,
name|brush_sel
operator|->
name|brush_name
argument_list|,
name|brush_sel
operator|->
name|opacity
argument_list|,
name|brush_sel
operator|->
name|spacing
argument_list|,
name|brush_sel
operator|->
name|paint_mode
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|brush_sel
operator|->
name|temp_brush_callback
operator|=
name|gimp_brush_select_new
argument_list|(
name|brush_sel
operator|->
name|title
argument_list|,
name|brush_sel
operator|->
name|brush_name
argument_list|,
name|brush_sel
operator|->
name|opacity
argument_list|,
name|brush_sel
operator|->
name|spacing
argument_list|,
name|brush_sel
operator|->
name|paint_mode
argument_list|,
name|gimp_brush_select_widget_callback
argument_list|,
name|brush_sel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_widget_destroy (GtkWidget * widget,BrushSelect * brush_sel)
name|gimp_brush_select_widget_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|)
block|{
if|if
condition|(
name|brush_sel
operator|->
name|temp_brush_callback
condition|)
block|{
name|gimp_brush_select_destroy
argument_list|(
name|brush_sel
operator|->
name|temp_brush_callback
argument_list|)
expr_stmt|;
name|brush_sel
operator|->
name|temp_brush_callback
operator|=
name|NULL
expr_stmt|;
block|}
name|g_free
argument_list|(
name|brush_sel
operator|->
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|brush_sel
operator|->
name|brush_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|brush_sel
operator|->
name|mask_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|brush_sel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_preview_resize (BrushSelect * brush_sel)
name|gimp_brush_select_preview_resize
parameter_list|(
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|)
block|{
if|if
condition|(
name|brush_sel
operator|->
name|width
operator|>
literal|0
operator|&&
name|brush_sel
operator|->
name|height
operator|>
literal|0
condition|)
name|gimp_brush_select_preview_update
argument_list|(
name|brush_sel
operator|->
name|preview
argument_list|,
name|brush_sel
operator|->
name|width
argument_list|,
name|brush_sel
operator|->
name|height
argument_list|,
name|brush_sel
operator|->
name|mask_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_brush_select_preview_events (GtkWidget * widget,GdkEvent * event,BrushSelect * brush_sel)
name|gimp_brush_select_preview_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|)
block|{
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
if|if
condition|(
name|brush_sel
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
name|gimp_brush_select_popup_open
argument_list|(
name|brush_sel
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
name|gimp_brush_select_popup_close
argument_list|(
name|brush_sel
argument_list|)
expr_stmt|;
block|}
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
DECL|function|gimp_brush_select_preview_draw (GimpPreviewArea * area,gint x,gint y,gint width,gint height,const guchar * mask_data,gint rowstride)
name|gimp_brush_select_preview_draw
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
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
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask_data
parameter_list|,
name|gint
name|rowstride
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
argument_list|)
expr_stmt|;
name|src
operator|=
name|mask_data
expr_stmt|;
name|dest
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
name|height
condition|;
name|j
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
condition|;
name|i
operator|++
operator|,
name|s
operator|++
operator|,
name|dest
operator|++
control|)
operator|*
name|dest
operator|=
literal|255
operator|-
operator|*
name|s
expr_stmt|;
name|src
operator|+=
name|rowstride
expr_stmt|;
block|}
name|gimp_preview_area_draw
argument_list|(
name|area
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_GRAY_IMAGE
argument_list|,
name|buf
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_preview_update (GtkWidget * preview,gint brush_width,gint brush_height,const guchar * mask_data)
name|gimp_brush_select_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|gint
name|brush_width
parameter_list|,
name|gint
name|brush_height
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask_data
parameter_list|)
block|{
name|GimpPreviewArea
modifier|*
name|area
init|=
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|width
operator|=
name|MIN
argument_list|(
name|brush_width
argument_list|,
name|preview
operator|->
name|allocation
operator|.
name|width
argument_list|)
expr_stmt|;
name|height
operator|=
name|MIN
argument_list|(
name|brush_height
argument_list|,
name|preview
operator|->
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|x
operator|=
operator|(
operator|(
name|preview
operator|->
name|allocation
operator|.
name|width
operator|-
name|width
operator|)
operator|/
literal|2
operator|)
expr_stmt|;
name|y
operator|=
operator|(
operator|(
name|preview
operator|->
name|allocation
operator|.
name|height
operator|-
name|height
operator|)
operator|/
literal|2
operator|)
expr_stmt|;
if|if
condition|(
name|x
operator|||
name|y
condition|)
name|gimp_preview_area_fill
argument_list|(
name|area
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|preview
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|preview
operator|->
name|allocation
operator|.
name|height
argument_list|,
literal|0xFF
argument_list|,
literal|0xFF
argument_list|,
literal|0xFF
argument_list|)
expr_stmt|;
name|gimp_brush_select_preview_draw
argument_list|(
name|area
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|mask_data
argument_list|,
name|brush_width
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_popup_open (BrushSelect * brush_sel,gint x,gint y)
name|gimp_brush_select_popup_open
parameter_list|(
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
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
if|if
condition|(
name|brush_sel
operator|->
name|popup
condition|)
name|gimp_brush_select_popup_close
argument_list|(
name|brush_sel
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush_sel
operator|->
name|width
operator|<=
name|CELL_SIZE
operator|&&
name|brush_sel
operator|->
name|height
operator|<=
name|CELL_SIZE
condition|)
return|return;
name|brush_sel
operator|->
name|popup
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
name|brush_sel
operator|->
name|popup
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
name|gimp_preview_area_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|preview
argument_list|,
name|brush_sel
operator|->
name|width
argument_list|,
name|brush_sel
operator|->
name|height
argument_list|)
expr_stmt|;
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
comment|/* decide where to put the popup */
name|gdk_window_get_origin
argument_list|(
name|brush_sel
operator|->
name|preview
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
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|brush_sel
operator|->
name|popup
argument_list|)
expr_stmt|;
name|scr_w
operator|=
name|gdk_screen_get_width
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|scr_h
operator|=
name|gdk_screen_get_height
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|x
operator|=
name|x_org
operator|+
name|x
operator|-
operator|(
name|brush_sel
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
name|brush_sel
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
name|brush_sel
operator|->
name|width
operator|>
name|scr_w
operator|)
condition|?
name|scr_w
operator|-
name|brush_sel
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
name|brush_sel
operator|->
name|height
operator|>
name|scr_h
operator|)
condition|?
name|scr_h
operator|-
name|brush_sel
operator|->
name|height
else|:
name|y
expr_stmt|;
name|gtk_window_move
argument_list|(
name|GTK_WINDOW
argument_list|(
name|brush_sel
operator|->
name|popup
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|brush_sel
operator|->
name|popup
argument_list|)
expr_stmt|;
comment|/*  Draw the brush  */
name|gimp_brush_select_preview_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|brush_sel
operator|->
name|width
argument_list|,
name|brush_sel
operator|->
name|height
argument_list|,
name|brush_sel
operator|->
name|mask_data
argument_list|,
name|brush_sel
operator|->
name|width
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_popup_close (BrushSelect * brush_sel)
name|gimp_brush_select_popup_close
parameter_list|(
name|BrushSelect
modifier|*
name|brush_sel
parameter_list|)
block|{
if|if
condition|(
name|brush_sel
operator|->
name|popup
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|brush_sel
operator|->
name|popup
argument_list|)
expr_stmt|;
name|brush_sel
operator|->
name|popup
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_drag_data_received (GtkWidget * preview,GdkDragContext * context,gint x,gint y,GtkSelectionData * selection,guint info,guint time,GtkWidget * widget)
name|gimp_brush_select_drag_data_received
parameter_list|(
name|GtkWidget
modifier|*
name|preview
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
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gchar
modifier|*
name|str
decl_stmt|;
if|if
condition|(
operator|(
name|selection
operator|->
name|format
operator|!=
literal|8
operator|)
operator|||
operator|(
name|selection
operator|->
name|length
operator|<
literal|1
operator|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"Received invalid brush data!"
argument_list|)
expr_stmt|;
return|return;
block|}
name|str
operator|=
name|g_strndup
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|selection
operator|->
name|data
argument_list|,
name|selection
operator|->
name|length
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_utf8_validate
argument_list|(
name|str
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gint
name|pid
decl_stmt|;
name|gpointer
name|unused
decl_stmt|;
name|gint
name|name_offset
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|sscanf
argument_list|(
name|str
argument_list|,
literal|"%i:%p:%n"
argument_list|,
operator|&
name|pid
argument_list|,
operator|&
name|unused
argument_list|,
operator|&
name|name_offset
argument_list|)
operator|>=
literal|2
operator|&&
name|pid
operator|==
name|gimp_getpid
argument_list|()
operator|&&
name|name_offset
operator|>
literal|0
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|str
operator|+
name|name_offset
decl_stmt|;
name|gimp_brush_select_widget_set
argument_list|(
name|widget
argument_list|,
name|name
argument_list|,
operator|-
literal|1.0
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

