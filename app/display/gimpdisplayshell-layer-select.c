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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpview.h"
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
file|"gimpdisplayshell-layer-select.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

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
DECL|member|view
name|GtkWidget
modifier|*
name|view
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|orig_layer
name|GimpLayer
modifier|*
name|orig_layer
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|LayerSelect
modifier|*
name|layer_select_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
name|view_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|layer_select_destroy
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
name|gboolean
name|layer_select_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|LayerSelect
modifier|*
name|layer_select
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_layer_select_init (GimpDisplayShell * shell,gint move,guint32 time)
name|gimp_display_shell_layer_select_init
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|move
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|LayerSelect
modifier|*
name|layer_select
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|shell
operator|->
name|gdisp
operator|->
name|image
expr_stmt|;
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|layer
condition|)
return|return;
name|layer_select
operator|=
name|layer_select_new
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|layer_preview_size
argument_list|)
expr_stmt|;
name|layer_select_advance
argument_list|(
name|layer_select
argument_list|,
name|move
argument_list|)
expr_stmt|;
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|LayerSelect
modifier|*
DECL|function|layer_select_new (GimpImage * image,GimpLayer * layer,gint view_size)
name|layer_select_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
name|view_size
parameter_list|)
block|{
name|LayerSelect
modifier|*
name|layer_select
decl_stmt|;
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
name|layer_select
operator|=
name|g_new0
argument_list|(
name|LayerSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|layer_select
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|layer_select
operator|->
name|orig_layer
operator|=
name|layer
expr_stmt|;
name|layer_select
operator|->
name|shell
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_POPUP
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
argument_list|,
literal|"gimp-layer-select"
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
name|g_signal_connect
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|,
literal|"event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|layer_select_events
argument_list|)
argument_list|,
name|layer_select
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
name|gtk_widget_show
argument_list|(
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
name|gtk_widget_show
argument_list|(
name|frame2
argument_list|)
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|6
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
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
comment|/*  The view  */
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
name|view
operator|=
name|gimp_view_new_by_types
argument_list|(
name|GIMP_TYPE_VIEW
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|,
name|view_size
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|layer_select
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|layer
argument_list|)
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
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|layer_select
operator|->
name|view
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
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
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
name|layer_select
operator|->
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
name|layer_select
operator|->
name|label
argument_list|)
expr_stmt|;
return|return
name|layer_select
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|layer_select_destroy (LayerSelect * layer_select,guint32 time)
name|layer_select_destroy
parameter_list|(
name|LayerSelect
modifier|*
name|layer_select
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|gdk_display_keyboard_ungrab
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
argument_list|,
name|time
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|layer_select
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_select
operator|->
name|orig_layer
operator|!=
name|gimp_image_get_active_layer
argument_list|(
name|layer_select
operator|->
name|image
argument_list|)
condition|)
block|{
name|gimp_image_flush
argument_list|(
name|layer_select
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|layer_select
argument_list|)
expr_stmt|;
block|}
end_function

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
name|GimpLayer
modifier|*
name|current_layer
decl_stmt|;
name|GimpLayer
modifier|*
name|next_layer
decl_stmt|;
name|gint
name|index
decl_stmt|;
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
name|image
argument_list|)
condition|)
return|return;
name|current_layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|layer_select
operator|->
name|image
argument_list|)
expr_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|layer_select
operator|->
name|image
operator|->
name|layers
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|current_layer
argument_list|)
argument_list|)
expr_stmt|;
name|index
operator|+=
name|move
expr_stmt|;
if|if
condition|(
name|index
operator|<
literal|0
condition|)
name|index
operator|=
name|gimp_container_num_children
argument_list|(
name|layer_select
operator|->
name|image
operator|->
name|layers
argument_list|)
operator|-
literal|1
expr_stmt|;
elseif|else
if|if
condition|(
name|index
operator|>=
name|gimp_container_num_children
argument_list|(
name|layer_select
operator|->
name|image
operator|->
name|layers
argument_list|)
condition|)
name|index
operator|=
literal|0
expr_stmt|;
name|next_layer
operator|=
operator|(
name|GimpLayer
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|layer_select
operator|->
name|image
operator|->
name|layers
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|next_layer
operator|&&
name|next_layer
operator|!=
name|current_layer
condition|)
block|{
name|current_layer
operator|=
name|gimp_image_set_active_layer
argument_list|(
name|layer_select
operator|->
name|image
argument_list|,
name|next_layer
argument_list|)
expr_stmt|;
if|if
condition|(
name|current_layer
condition|)
block|{
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|layer_select
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|current_layer
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|layer_select
operator|->
name|label
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|current_layer
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|layer_select_events (GtkWidget * widget,GdkEvent * event,LayerSelect * layer_select)
name|layer_select_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|LayerSelect
modifier|*
name|layer_select
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
name|layer_select_destroy
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
name|layer_select_advance
argument_list|(
name|layer_select
argument_list|,
literal|1
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_ISO_Left_Tab
case|:
name|layer_select_advance
argument_list|(
name|layer_select
argument_list|,
operator|-
literal|1
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
case|case
name|GDK_Shift_L
case|:
case|case
name|GDK_Shift_R
case|:
name|kevent
operator|->
name|state
operator|&=
operator|~
name|GDK_SHIFT_MASK
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
name|GDK_CONTROL_MASK
operator|)
condition|)
name|layer_select_destroy
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

end_unit

