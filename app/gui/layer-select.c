begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"layer-select.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"layers_dialogP.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|PREVIEW_EVENT_MASK
define|#
directive|define
name|PREVIEW_EVENT_MASK
value|GDK_EXPOSURE_MASK | GDK_ENTER_NOTIFY_MASK
end_define

begin_typedef
DECL|typedef|LayerSelect
typedef|typedef
name|struct
name|_LayerSelect
name|LayerSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_LayerSelect
struct|struct
name|_LayerSelect
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|layer_preview
name|GtkWidget
modifier|*
name|layer_preview
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
decl_stmt|;
DECL|member|layer_pixmap
name|GdkPixmap
modifier|*
name|layer_pixmap
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|current_layer
name|GimpLayer
modifier|*
name|current_layer
decl_stmt|;
DECL|member|dirty
name|gboolean
name|dirty
decl_stmt|;
DECL|member|image_width
name|gint
name|image_width
decl_stmt|;
DECL|member|image_height
name|gint
name|image_height
decl_stmt|;
DECL|member|ratio
name|gdouble
name|ratio
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  layer widget function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|layer_select_advance
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|,
name|gint
name|move
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|layer_select_forward
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|layer_select_backward
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|layer_select_end
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|layer_select_set_gimage
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|layer_select_set_layer
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|layer_select_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|preview_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|preview_redraw
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  *  Local variables  */
end_comment

begin_decl_stmt
DECL|variable|layer_select
name|LayerSelect
modifier|*
name|layer_select
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  Public functions  */
end_comment

begin_comment
comment|/**********************/
end_comment

begin_function
name|void
DECL|function|layer_select_init (GimpImage * gimage,gint move,guint32 time)
name|layer_select_init
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|move
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame1
decl_stmt|;
name|GtkWidget
modifier|*
name|frame2
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
if|if
condition|(
operator|!
name|layer_select
condition|)
block|{
name|layer_select
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|LayerSelect
argument_list|)
argument_list|)
expr_stmt|;
name|layer_select
operator|->
name|layer_pixmap
operator|=
name|NULL
expr_stmt|;
name|layer_select
operator|->
name|layer_preview
operator|=
name|NULL
expr_stmt|;
name|layer_select
operator|->
name|preview
operator|=
name|NULL
expr_stmt|;
name|layer_select
operator|->
name|image_width
operator|=
name|layer_select
operator|->
name|image_height
operator|=
literal|0
expr_stmt|;
name|layer_select_set_gimage
argument_list|(
name|layer_select
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|layer_select_advance
argument_list|(
name|layer_select
argument_list|,
name|move
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview_size
condition|)
block|{
name|layer_select
operator|->
name|preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|layer_select
operator|->
name|preview
argument_list|)
argument_list|,
name|preview_size
argument_list|,
name|preview_size
argument_list|)
expr_stmt|;
block|}
comment|/*  The shell and main vbox  */
name|layer_select
operator|->
name|shell
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_POPUP
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
argument_list|,
literal|"layer_select"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Layer Select"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
argument_list|,
literal|"event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|layer_select_events
argument_list|,
name|layer_select
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|,
operator|(
name|GDK_KEY_PRESS_MASK
operator||
name|GDK_KEY_RELEASE_MASK
operator||
name|GDK_BUTTON_PRESS_MASK
operator|)
argument_list|)
expr_stmt|;
name|frame1
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
name|frame1
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
argument_list|,
name|frame1
argument_list|)
expr_stmt|;
name|frame2
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
name|frame2
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame1
argument_list|)
argument_list|,
name|frame2
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame2
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
comment|/*  The preview  */
name|alignment
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|alignment
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
name|alignment
argument_list|)
expr_stmt|;
name|layer_select
operator|->
name|layer_preview
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_drawing_area_size
argument_list|(
name|GTK_DRAWING_AREA
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|)
argument_list|,
name|layer_select
operator|->
name|image_width
argument_list|,
name|layer_select
operator|->
name|image_height
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|,
name|PREVIEW_EVENT_MASK
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|)
argument_list|,
literal|"event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|preview_events
argument_list|,
name|layer_select
argument_list|)
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|)
argument_list|,
name|layer_select
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
name|layer_select
operator|->
name|layer_preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|alignment
argument_list|)
expr_stmt|;
comment|/*  the layer name label */
name|layer_select
operator|->
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Layer"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|layer_select
operator|->
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
name|layer_select
operator|->
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|layer_select_set_gimage
argument_list|(
name|layer_select
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|layer_select_advance
argument_list|(
name|layer_select
argument_list|,
name|move
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_draw
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gdk_key_repeat_disable
argument_list|()
expr_stmt|;
name|gdk_keyboard_grab
argument_list|(
name|layer_select
operator|->
name|shell
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
name|time
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|layer_select_update_preview_size (void)
name|layer_select_update_preview_size
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|layer_select
operator|!=
name|NULL
condition|)
block|{
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|layer_select
operator|->
name|preview
argument_list|)
argument_list|,
name|preview_size
argument_list|,
name|preview_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_draw
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/***********************/
end_comment

begin_comment
comment|/*  Private functions  */
end_comment

begin_comment
comment|/***********************/
end_comment

begin_function
specifier|static
name|void
DECL|function|layer_select_advance (LayerSelect * layer_select,gint move)
name|layer_select_advance
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|,
name|gint
name|move
parameter_list|)
block|{
name|gint
name|index
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|GSList
modifier|*
name|nth
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|index
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|move
operator|==
literal|0
condition|)
return|return;
comment|/*  If there is a floating selection, allow no advancement  */
if|if
condition|(
name|gimp_image_floating_sel
argument_list|(
name|layer_select
operator|->
name|gimage
argument_list|)
condition|)
return|return;
for|for
control|(
name|list
operator|=
name|layer_select
operator|->
name|gimage
operator|->
name|layer_stack
operator|,
name|count
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
operator|,
name|count
operator|++
control|)
block|{
name|layer
operator|=
operator|(
name|GimpLayer
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|layer
operator|==
name|layer_select
operator|->
name|current_layer
condition|)
name|index
operator|=
name|count
expr_stmt|;
block|}
name|index
operator|+=
name|move
expr_stmt|;
name|index
operator|=
name|CLAMP
argument_list|(
name|index
argument_list|,
literal|0
argument_list|,
name|count
operator|-
literal|1
argument_list|)
expr_stmt|;
name|nth
operator|=
name|g_slist_nth
argument_list|(
name|layer_select
operator|->
name|gimage
operator|->
name|layer_stack
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|nth
condition|)
block|{
name|layer
operator|=
operator|(
name|GimpLayer
operator|*
operator|)
name|nth
operator|->
name|data
expr_stmt|;
name|layer_select
operator|->
name|current_layer
operator|=
name|layer
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|layer_select_forward (LayerSelect * layer_select)
name|layer_select_forward
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|)
block|{
name|layer_select_advance
argument_list|(
name|layer_select
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|layer_select
operator|->
name|dirty
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_draw
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|layer_select_backward (LayerSelect * layer_select)
name|layer_select_backward
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|)
block|{
name|layer_select_advance
argument_list|(
name|layer_select
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|layer_select
operator|->
name|dirty
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_draw
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|layer_select_end (LayerSelect * layer_select,guint32 time)
name|layer_select_end
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|gdk_key_repeat_restore
argument_list|()
expr_stmt|;
name|gdk_keyboard_ungrab
argument_list|(
name|time
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/*  only reset the active layer if a new layer was specified  */
if|if
condition|(
name|layer_select
operator|->
name|current_layer
operator|!=
name|gimp_image_get_active_layer
argument_list|(
name|layer_select
operator|->
name|gimage
argument_list|)
condition|)
block|{
name|gimp_image_set_active_layer
argument_list|(
name|layer_select
operator|->
name|gimage
argument_list|,
name|layer_select
operator|->
name|current_layer
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|layer_select_set_gimage (LayerSelect * layer_select,GimpImage * gimage)
name|layer_select_set_gimage
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|gint
name|image_width
decl_stmt|;
name|gint
name|image_height
decl_stmt|;
name|layer_select
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|layer_select
operator|->
name|current_layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|layer_select
operator|->
name|dirty
operator|=
name|TRUE
expr_stmt|;
comment|/*  Get the image width and height variables, based on the gimage  */
if|if
condition|(
name|gimage
operator|->
name|width
operator|>
name|gimage
operator|->
name|height
condition|)
name|layer_select
operator|->
name|ratio
operator|=
name|MIN
argument_list|(
literal|1.0
argument_list|,
operator|(
name|gdouble
operator|)
name|preview_size
operator|/
operator|(
name|gdouble
operator|)
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
else|else
name|layer_select
operator|->
name|ratio
operator|=
name|MIN
argument_list|(
literal|1.0
argument_list|,
operator|(
name|gdouble
operator|)
name|preview_size
operator|/
operator|(
name|gdouble
operator|)
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|image_width
operator|=
call|(
name|gint
call|)
argument_list|(
name|layer_select
operator|->
name|ratio
operator|*
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|image_height
operator|=
call|(
name|gint
call|)
argument_list|(
name|layer_select
operator|->
name|ratio
operator|*
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_select
operator|->
name|image_width
operator|!=
name|image_width
operator|||
name|layer_select
operator|->
name|image_height
operator|!=
name|image_height
condition|)
block|{
name|layer_select
operator|->
name|image_width
operator|=
name|image_width
expr_stmt|;
name|layer_select
operator|->
name|image_height
operator|=
name|image_height
expr_stmt|;
if|if
condition|(
name|layer_select
operator|->
name|layer_preview
condition|)
name|gtk_widget_set_usize
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|,
name|layer_select
operator|->
name|image_width
argument_list|,
name|layer_select
operator|->
name|image_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_select
operator|->
name|layer_pixmap
condition|)
block|{
name|gdk_pixmap_unref
argument_list|(
name|layer_select
operator|->
name|layer_pixmap
argument_list|)
expr_stmt|;
name|layer_select
operator|->
name|layer_pixmap
operator|=
name|NULL
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|layer_select_set_layer (LayerSelect * layer_select)
name|layer_select_set_layer
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|layer
operator|=
operator|(
name|layer_select
operator|->
name|current_layer
operator|)
operator|)
condition|)
return|return;
comment|/*  Set the layer label  */
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|layer_select
operator|->
name|label
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|layer_select_events (GtkWidget * widget,GdkEvent * event)
name|layer_select_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|GdkEventKey
modifier|*
name|kevent
decl_stmt|;
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
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
name|layer_select_end
argument_list|(
name|layer_select
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_KEY_PRESS
case|:
name|kevent
operator|=
operator|(
name|GdkEventKey
operator|*
operator|)
name|event
expr_stmt|;
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_Tab
case|:
if|if
condition|(
name|kevent
operator|->
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
name|layer_select_forward
argument_list|(
name|layer_select
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|kevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|layer_select_backward
argument_list|(
name|layer_select
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|TRUE
return|;
break|break;
case|case
name|GDK_KEY_RELEASE
case|:
name|kevent
operator|=
operator|(
name|GdkEventKey
operator|*
operator|)
name|event
expr_stmt|;
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_Alt_L
case|:
case|case
name|GDK_Alt_R
case|:
name|kevent
operator|->
name|state
operator|&=
operator|~
name|GDK_MOD1_MASK
expr_stmt|;
break|break;
case|case
name|GDK_Control_L
case|:
case|case
name|GDK_Control_R
case|:
name|kevent
operator|->
name|state
operator|&=
operator|~
name|GDK_CONTROL_MASK
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|!
operator|(
name|kevent
operator|->
name|state
operator|&
operator|(
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
operator|)
operator|)
condition|)
name|layer_select_end
argument_list|(
name|layer_select
argument_list|,
name|kevent
operator|->
name|time
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
break|break;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|preview_events (GtkWidget * widget,GdkEvent * event)
name|preview_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
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
if|if
condition|(
name|layer_select
operator|->
name|dirty
condition|)
block|{
comment|/*  If a preview exists, draw it  */
if|if
condition|(
name|preview_size
condition|)
name|preview_redraw
argument_list|(
name|layer_select
argument_list|)
expr_stmt|;
comment|/*  Change the layer name label  */
name|layer_select_set_layer
argument_list|(
name|layer_select
argument_list|)
expr_stmt|;
name|layer_select
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|preview_size
condition|)
name|gdk_draw_pixmap
argument_list|(
name|layer_select
operator|->
name|layer_preview
operator|->
name|window
argument_list|,
name|layer_select
operator|->
name|layer_preview
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|layer_select
operator|->
name|layer_pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|layer_select
operator|->
name|image_width
argument_list|,
name|layer_select
operator|->
name|image_height
argument_list|)
expr_stmt|;
break|break;
default|default:
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
DECL|function|preview_redraw (LayerSelect * layer_select)
name|preview_redraw
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|TempBuf
modifier|*
name|preview_buf
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|offx
decl_stmt|,
name|offy
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|layer
operator|=
operator|(
name|layer_select
operator|->
name|current_layer
operator|)
operator|)
condition|)
return|return;
if|if
condition|(
operator|!
name|layer_select
operator|->
name|layer_pixmap
condition|)
name|layer_select
operator|->
name|layer_pixmap
operator|=
name|gdk_pixmap_new
argument_list|(
name|layer_select
operator|->
name|layer_preview
operator|->
name|window
argument_list|,
name|layer_select
operator|->
name|image_width
argument_list|,
name|layer_select
operator|->
name|image_height
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|render_fs_preview
argument_list|(
name|layer_select
operator|->
name|layer_preview
argument_list|,
name|layer_select
operator|->
name|layer_pixmap
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|off_x
decl_stmt|;
name|gint
name|off_y
decl_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
comment|/*  determine width and height  */
name|w
operator|=
call|(
name|gint
call|)
argument_list|(
name|layer_select
operator|->
name|ratio
operator|*
name|gimp_drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|h
operator|=
call|(
name|gint
call|)
argument_list|(
name|layer_select
operator|->
name|ratio
operator|*
name|gimp_drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|offx
operator|=
call|(
name|gint
call|)
argument_list|(
name|layer_select
operator|->
name|ratio
operator|*
name|off_x
argument_list|)
expr_stmt|;
name|offy
operator|=
call|(
name|gint
call|)
argument_list|(
name|layer_select
operator|->
name|ratio
operator|*
name|off_y
argument_list|)
expr_stmt|;
name|preview_buf
operator|=
name|gimp_viewable_get_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|preview_buf
operator|->
name|x
operator|=
name|offx
expr_stmt|;
name|preview_buf
operator|->
name|y
operator|=
name|offy
expr_stmt|;
name|render_preview
argument_list|(
name|preview_buf
argument_list|,
name|layer_select
operator|->
name|preview
argument_list|,
name|layer_select
operator|->
name|image_width
argument_list|,
name|layer_select
operator|->
name|image_height
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/*  Set the layer pixmap  */
name|gtk_preview_put
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|layer_select
operator|->
name|preview
argument_list|)
argument_list|,
name|layer_select
operator|->
name|layer_pixmap
argument_list|,
name|layer_select
operator|->
name|layer_preview
operator|->
name|style
operator|->
name|black_gc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|layer_select
operator|->
name|image_width
argument_list|,
name|layer_select
operator|->
name|image_height
argument_list|)
expr_stmt|;
comment|/*  make sure the image has been transfered completely         *  to the pixmap before we use it again...        */
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

end_unit

