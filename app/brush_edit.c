begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * brush_edit module Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"brush_edit.h"
end_include

begin_include
include|#
directive|include
file|"actionarea.h"
end_include

begin_include
include|#
directive|include
file|"math.h"
end_include

begin_function_decl
specifier|static
name|void
name|brush_edit_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|brush_edit_preview_resize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|BrushEditGeneratedWindow
modifier|*
name|begw
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  the action area structure  */
end_comment

begin_decl_stmt
DECL|variable|action_items
specifier|static
name|ActionAreaItem
name|action_items
index|[]
init|=
block|{
block|{
literal|"Close"
block|,
name|brush_edit_close_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|update_brush_callback (GtkAdjustment * adjustment,BrushEditGeneratedWindow * begw)
name|update_brush_callback
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|BrushEditGeneratedWindow
modifier|*
name|begw
parameter_list|)
block|{
if|if
condition|(
name|begw
operator|->
name|brush
operator|&&
operator|(
operator|(
name|begw
operator|->
name|radius_data
operator|->
name|value
operator|!=
name|gimp_brush_generated_get_radius
argument_list|(
name|begw
operator|->
name|brush
argument_list|)
operator|)
operator|||
operator|(
name|begw
operator|->
name|hardness_data
operator|->
name|value
operator|!=
name|gimp_brush_generated_get_hardness
argument_list|(
name|begw
operator|->
name|brush
argument_list|)
operator|)
operator|||
operator|(
name|begw
operator|->
name|aspect_ratio_data
operator|->
name|value
operator|!=
name|gimp_brush_generated_get_aspect_ratio
argument_list|(
name|begw
operator|->
name|brush
argument_list|)
operator|)
operator|||
operator|(
name|begw
operator|->
name|angle_data
operator|->
name|value
operator|!=
name|gimp_brush_generated_get_angle
argument_list|(
name|begw
operator|->
name|brush
argument_list|)
operator|)
operator|)
condition|)
block|{
name|gimp_brush_generated_freeze
argument_list|(
name|begw
operator|->
name|brush
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_radius
argument_list|(
name|begw
operator|->
name|brush
argument_list|,
name|begw
operator|->
name|radius_data
operator|->
name|value
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_hardness
argument_list|(
name|begw
operator|->
name|brush
argument_list|,
name|begw
operator|->
name|hardness_data
operator|->
name|value
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_aspect_ratio
argument_list|(
name|begw
operator|->
name|brush
argument_list|,
name|begw
operator|->
name|aspect_ratio_data
operator|->
name|value
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_angle
argument_list|(
name|begw
operator|->
name|brush
argument_list|,
name|begw
operator|->
name|angle_data
operator|->
name|value
argument_list|)
expr_stmt|;
name|gimp_brush_generated_thaw
argument_list|(
name|begw
operator|->
name|brush
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|brush_edit_delete_callback (GtkWidget * w,BrushEditGeneratedWindow * begw)
name|brush_edit_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|BrushEditGeneratedWindow
modifier|*
name|begw
parameter_list|)
block|{
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|w
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|w
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_edit_clear_preview (BrushEditGeneratedWindow * begw)
name|brush_edit_clear_preview
parameter_list|(
name|BrushEditGeneratedWindow
modifier|*
name|begw
parameter_list|)
block|{
name|unsigned
name|char
modifier|*
name|buf
decl_stmt|;
name|int
name|i
decl_stmt|;
name|buf
operator|=
operator|(
name|unsigned
name|char
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|char
argument_list|)
operator|*
name|begw
operator|->
name|preview
operator|->
name|requisition
operator|.
name|width
argument_list|)
expr_stmt|;
comment|/*  Set the buffer to white  */
name|memset
argument_list|(
name|buf
argument_list|,
literal|255
argument_list|,
name|begw
operator|->
name|preview
operator|->
name|requisition
operator|.
name|width
argument_list|)
expr_stmt|;
comment|/*  Set the image buffer to white  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|begw
operator|->
name|preview
operator|->
name|requisition
operator|.
name|height
condition|;
name|i
operator|++
control|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|begw
operator|->
name|preview
argument_list|)
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|begw
operator|->
name|preview
operator|->
name|requisition
operator|.
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
name|gint
DECL|function|brush_edit_brush_dirty_callback (GimpBrush * brush,BrushEditGeneratedWindow * begw)
name|brush_edit_brush_dirty_callback
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|BrushEditGeneratedWindow
modifier|*
name|begw
parameter_list|)
block|{
name|int
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|yend
decl_stmt|,
name|ystart
decl_stmt|,
name|xo
decl_stmt|;
name|int
name|scale
decl_stmt|;
name|gchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|buf
decl_stmt|;
name|brush_edit_clear_preview
argument_list|(
name|begw
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|==
name|NULL
condition|)
return|return
name|TRUE
return|;
name|scale
operator|=
name|MAX
argument_list|(
name|ceil
argument_list|(
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
operator|(
name|float
operator|)
name|begw
operator|->
name|preview
operator|->
name|requisition
operator|.
name|width
argument_list|)
argument_list|,
name|ceil
argument_list|(
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
operator|(
name|float
operator|)
name|begw
operator|->
name|preview
operator|->
name|requisition
operator|.
name|height
argument_list|)
argument_list|)
expr_stmt|;
name|ystart
operator|=
literal|0
expr_stmt|;
name|xo
operator|=
name|begw
operator|->
name|preview
operator|->
name|requisition
operator|.
name|width
operator|/
literal|2
operator|-
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
operator|(
literal|2
operator|*
name|scale
operator|)
expr_stmt|;
name|ystart
operator|=
name|begw
operator|->
name|preview
operator|->
name|requisition
operator|.
name|height
operator|/
literal|2
operator|-
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
operator|(
literal|2
operator|*
name|scale
operator|)
expr_stmt|;
name|yend
operator|=
name|ystart
operator|+
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
operator|(
name|scale
operator|)
expr_stmt|;
name|width
operator|=
name|BOUNDS
argument_list|(
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
name|scale
argument_list|,
literal|0
argument_list|,
name|begw
operator|->
name|preview
operator|->
name|requisition
operator|.
name|width
argument_list|)
expr_stmt|;
name|buf
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|src
operator|=
operator|(
name|gchar
operator|*
operator|)
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
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
comment|/*  Invert the mask for display.      */
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
name|buf
index|[
name|x
index|]
operator|=
literal|255
operator|-
name|src
index|[
name|x
operator|*
name|scale
index|]
expr_stmt|;
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|begw
operator|->
name|preview
argument_list|)
argument_list|,
operator|(
name|guchar
operator|*
operator|)
name|buf
argument_list|,
name|xo
argument_list|,
name|y
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|src
operator|+=
name|brush
operator|->
name|mask
operator|->
name|width
operator|*
name|scale
expr_stmt|;
block|}
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|begw
operator|->
name|scale
operator|!=
name|scale
condition|)
block|{
name|char
name|str
index|[
literal|255
index|]
decl_stmt|;
name|begw
operator|->
name|scale
operator|=
name|scale
expr_stmt|;
name|g_snprintf
argument_list|(
name|str
argument_list|,
literal|200
argument_list|,
literal|"%d:1"
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|gtk_label_set
argument_list|(
name|GTK_LABEL
argument_list|(
name|begw
operator|->
name|scale_label
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|gtk_widget_draw
argument_list|(
name|begw
operator|->
name|scale_label
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_draw
argument_list|(
name|begw
operator|->
name|preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|brush_edit_generated_set_brush (BrushEditGeneratedWindow * begw,GimpBrush * gbrush)
name|brush_edit_generated_set_brush
parameter_list|(
name|BrushEditGeneratedWindow
modifier|*
name|begw
parameter_list|,
name|GimpBrush
modifier|*
name|gbrush
parameter_list|)
block|{
name|GimpBrushGenerated
modifier|*
name|brush
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|begw
operator|->
name|brush
operator|==
operator|(
name|GimpBrushGenerated
operator|*
operator|)
name|gbrush
condition|)
return|return;
if|if
condition|(
name|begw
operator|->
name|brush
condition|)
block|{
name|gtk_signal_disconnect_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|begw
operator|->
name|brush
argument_list|)
argument_list|,
name|begw
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|begw
operator|->
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|begw
operator|->
name|brush
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gbrush
operator|||
operator|!
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|gbrush
argument_list|)
condition|)
block|{
name|begw
operator|->
name|brush
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return;
block|}
name|brush
operator|=
name|GIMP_BRUSH_GENERATED
argument_list|(
name|gbrush
argument_list|)
expr_stmt|;
if|if
condition|(
name|begw
condition|)
block|{
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|"dirty"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brush_edit_brush_dirty_callback
argument_list|)
argument_list|,
name|begw
argument_list|)
expr_stmt|;
name|begw
operator|->
name|brush
operator|=
name|NULL
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|begw
operator|->
name|radius_data
argument_list|)
argument_list|,
name|gimp_brush_generated_get_radius
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|begw
operator|->
name|hardness_data
argument_list|)
argument_list|,
name|gimp_brush_generated_get_hardness
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|begw
operator|->
name|angle_data
argument_list|)
argument_list|,
name|gimp_brush_generated_get_angle
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|begw
operator|->
name|aspect_ratio_data
argument_list|)
argument_list|,
name|gimp_brush_generated_get_aspect_ratio
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|begw
operator|->
name|brush
operator|=
name|brush
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|begw
operator|->
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|brush_edit_brush_dirty_callback
argument_list|(
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|begw
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|BrushEditGeneratedWindow
modifier|*
DECL|function|brush_edit_generated_new ()
name|brush_edit_generated_new
parameter_list|()
block|{
name|BrushEditGeneratedWindow
modifier|*
name|begw
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|slider
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|begw
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|BrushEditGeneratedWindow
argument_list|)
argument_list|)
expr_stmt|;
name|begw
operator|->
name|brush
operator|=
name|NULL
expr_stmt|;
name|begw
operator|->
name|shell
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
argument_list|,
literal|"generatedbrusheditor"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
argument_list|,
literal|"Brush Editor"
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* handle the wm close signal */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brush_edit_delete_callback
argument_list|)
argument_list|,
name|begw
argument_list|)
expr_stmt|;
comment|/*  Populate the window with some widgets */
comment|/* brush's preview widget w/frame  */
name|begw
operator|->
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
name|begw
operator|->
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
name|vbox
argument_list|)
argument_list|,
name|begw
operator|->
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|begw
operator|->
name|preview
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
name|begw
operator|->
name|preview
argument_list|)
argument_list|,
literal|125
argument_list|,
literal|100
argument_list|)
expr_stmt|;
name|gtk_signal_connect_after
argument_list|(
name|GTK_OBJECT
argument_list|(
name|begw
operator|->
name|frame
argument_list|)
argument_list|,
literal|"size_allocate"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|brush_edit_preview_resize
argument_list|,
name|begw
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|begw
operator|->
name|frame
argument_list|)
argument_list|,
name|begw
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|begw
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|begw
operator|->
name|frame
argument_list|)
expr_stmt|;
comment|/* table for sliders/labels */
name|begw
operator|->
name|scale_label
operator|=
name|gtk_label_new
argument_list|(
literal|"-1:1"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|begw
operator|->
name|scale_label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|begw
operator|->
name|scale
operator|=
operator|-
literal|1
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|begw
operator|->
name|scale_label
argument_list|)
expr_stmt|;
comment|/* table for sliders/labels */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|4
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* brush radius scale */
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Radius:"
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
comment|/*  gtk_table_attach(GTK_TABLE (table), label, 0, 1, 0, 1, 0, 0, 0, 0); */
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|begw
operator|->
name|radius_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|10.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|begw
operator|->
name|radius_data
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|begw
operator|->
name|radius_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|update_brush_callback
argument_list|,
name|begw
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider
argument_list|)
expr_stmt|;
comment|/* brush hardness scale */
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Hardness:"
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|begw
operator|->
name|hardness_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.01
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|begw
operator|->
name|hardness_data
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|begw
operator|->
name|hardness_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|update_brush_callback
argument_list|,
name|begw
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider
argument_list|)
expr_stmt|;
comment|/* brush aspect ratio scale */
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Aspect Ratio:"
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|begw
operator|->
name|aspect_ratio_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|20.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|begw
operator|->
name|aspect_ratio_data
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|begw
operator|->
name|aspect_ratio_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|update_brush_callback
argument_list|,
name|begw
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider
argument_list|)
expr_stmt|;
comment|/* brush angle scale */
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Angle:"
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|begw
operator|->
name|angle_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|00.0
argument_list|,
literal|0.0
argument_list|,
literal|180.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|begw
operator|->
name|angle_data
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|begw
operator|->
name|angle_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|update_brush_callback
argument_list|,
name|begw
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  The action area  */
name|action_items
index|[
literal|0
index|]
operator|.
name|user_data
operator|=
name|begw
expr_stmt|;
name|build_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
argument_list|,
name|action_items
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return
name|begw
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|brush_edit_preview_resize (GtkWidget * widget,GdkEvent * event,BrushEditGeneratedWindow * begw)
name|brush_edit_preview_resize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|BrushEditGeneratedWindow
modifier|*
name|begw
parameter_list|)
block|{
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|begw
operator|->
name|preview
argument_list|)
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|4
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
literal|4
argument_list|)
expr_stmt|;
comment|/*  update the display  */
if|if
condition|(
name|begw
operator|->
name|brush
condition|)
name|brush_edit_brush_dirty_callback
argument_list|(
name|GIMP_BRUSH
argument_list|(
name|begw
operator|->
name|brush
argument_list|)
argument_list|,
name|begw
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_edit_close_callback (GtkWidget * w,void * data)
name|brush_edit_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|BrushEditGeneratedWindow
modifier|*
name|begw
init|=
operator|(
name|BrushEditGeneratedWindow
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|begw
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

