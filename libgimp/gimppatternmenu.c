begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppatternmenu.c  * Copyright (C) 1998 Andy Thomas  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
DECL|macro|PATTERN_SELECT_DATA_KEY
define|#
directive|define
name|PATTERN_SELECT_DATA_KEY
value|"gimp-pattern-select-data"
end_define

begin_define
DECL|macro|CELL_SIZE
define|#
directive|define
name|CELL_SIZE
value|20
end_define

begin_typedef
DECL|typedef|PatternSelect
typedef|typedef
name|struct
name|_PatternSelect
name|PatternSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_PatternSelect
struct|struct
name|_PatternSelect
block|{
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|callback
name|GimpRunPatternCallback
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
DECL|member|pattern_name
name|gchar
modifier|*
name|pattern_name
decl_stmt|;
comment|/* Local copy */
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|bytes
name|gint
name|bytes
decl_stmt|;
DECL|member|mask_data
name|guchar
modifier|*
name|mask_data
decl_stmt|;
comment|/* local copy */
DECL|member|temp_pattern_callback
specifier|const
name|gchar
modifier|*
name|temp_pattern_callback
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_pattern_select_widget_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bytes
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
name|gimp_pattern_select_widget_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PatternSelect
modifier|*
name|pattern_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pattern_select_widget_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PatternSelect
modifier|*
name|pattern_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_pattern_select_preview_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|PatternSelect
modifier|*
name|pattern_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pattern_select_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bytes
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
name|gimp_pattern_select_preview_resize
parameter_list|(
name|PatternSelect
modifier|*
name|pattern_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pattern_select_popup_open
parameter_list|(
name|PatternSelect
modifier|*
name|pattern_sel
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
name|gimp_pattern_select_popup_close
parameter_list|(
name|PatternSelect
modifier|*
name|pattern_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pattern_select_drag_data_received
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
literal|"application/x-gimp-pattern-name"
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**  * gimp_pattern_select_widget_new:  * @title:        Title of the dialog to use or %NULL to use the default title.  * @pattern_name: Initial pattern name or %NULL to use current selection.  * @callback:     A function to call when the selected pattern changes.  * @data:         A pointer to arbitary data to be used in the call to @callback.  *  * Creates a new #GtkWidget that completely controls the selection of  * a pattern. This widget is suitable for placement in a table in a  * plug-in dialog.  *  * Returns: A #GtkWidget that you can use in your UI.  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_pattern_select_widget_new (const gchar * title,const gchar * pattern_name,GimpRunPatternCallback callback,gpointer data)
name|gimp_pattern_select_widget_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
parameter_list|,
name|GimpRunPatternCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PatternSelect
modifier|*
name|pattern_sel
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
name|mask_data_size
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
literal|"Pattern Selection"
argument_list|)
expr_stmt|;
name|pattern_sel
operator|=
name|g_new0
argument_list|(
name|PatternSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pattern_sel
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|pattern_sel
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|pattern_sel
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
name|pattern_sel
operator|->
name|preview
operator|=
name|gimp_preview_area_new
argument_list|()
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|pattern_sel
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
name|pattern_sel
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
name|pattern_sel
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pattern_sel
operator|->
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|pattern_sel
operator|->
name|preview
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pattern_select_preview_resize
argument_list|)
argument_list|,
name|pattern_sel
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|pattern_sel
operator|->
name|preview
argument_list|,
literal|"event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pattern_select_preview_events
argument_list|)
argument_list|,
name|pattern_sel
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|pattern_sel
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
name|pattern_sel
operator|->
name|preview
argument_list|,
literal|"drag-data-received"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pattern_select_drag_data_received
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|pattern_sel
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|pattern_sel
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
name|pattern_sel
operator|->
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|pattern_sel
operator|->
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pattern_select_widget_clicked
argument_list|)
argument_list|,
name|pattern_sel
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|pattern_sel
operator|->
name|button
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pattern_select_widget_destroy
argument_list|)
argument_list|,
name|pattern_sel
argument_list|)
expr_stmt|;
comment|/* Do initial pattern setup */
if|if
condition|(
operator|!
name|pattern_name
operator|||
operator|!
name|strlen
argument_list|(
name|pattern_name
argument_list|)
condition|)
name|pattern_sel
operator|->
name|pattern_name
operator|=
name|gimp_context_get_pattern
argument_list|()
expr_stmt|;
else|else
name|pattern_sel
operator|->
name|pattern_name
operator|=
name|g_strdup
argument_list|(
name|pattern_name
argument_list|)
expr_stmt|;
name|gimp_pattern_get_pixels
argument_list|(
name|pattern_sel
operator|->
name|pattern_name
argument_list|,
operator|&
name|pattern_sel
operator|->
name|width
argument_list|,
operator|&
name|pattern_sel
operator|->
name|height
argument_list|,
operator|&
name|pattern_sel
operator|->
name|bytes
argument_list|,
operator|&
name|mask_data_size
argument_list|,
operator|&
name|pattern_sel
operator|->
name|mask_data
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|PATTERN_SELECT_DATA_KEY
argument_list|,
name|pattern_sel
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pattern_select_widget_close:  * @widget: A pattern select widget.  *  * Closes the popup window associated with @widget.  */
end_comment

begin_function
name|void
DECL|function|gimp_pattern_select_widget_close (GtkWidget * widget)
name|gimp_pattern_select_widget_close
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|PatternSelect
modifier|*
name|pattern_sel
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|pattern_sel
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|PATTERN_SELECT_DATA_KEY
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|pattern_sel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern_sel
operator|->
name|temp_pattern_callback
condition|)
block|{
name|gimp_pattern_select_destroy
argument_list|(
name|pattern_sel
operator|->
name|temp_pattern_callback
argument_list|)
expr_stmt|;
name|pattern_sel
operator|->
name|temp_pattern_callback
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_pattern_select_widget_set:  * @widget:       A pattern select widget.  * @pattern_name: Pattern name to set. NULL means no change.  *  * Sets the current pattern for the pattern select widget.  Calls the  * callback function if one was supplied in the call to  * gimp_pattern_select_widget_new().  */
end_comment

begin_function
name|void
DECL|function|gimp_pattern_select_widget_set (GtkWidget * widget,const gchar * pattern_name)
name|gimp_pattern_select_widget_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
parameter_list|)
block|{
name|PatternSelect
modifier|*
name|pattern_sel
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|pattern_sel
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|PATTERN_SELECT_DATA_KEY
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|pattern_sel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern_sel
operator|->
name|temp_pattern_callback
condition|)
block|{
name|gimp_patterns_set_popup
argument_list|(
name|pattern_sel
operator|->
name|temp_pattern_callback
argument_list|,
name|pattern_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|bytes
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
if|if
condition|(
operator|!
name|pattern_name
operator|||
operator|!
name|strlen
argument_list|(
name|pattern_name
argument_list|)
condition|)
name|name
operator|=
name|gimp_context_get_pattern
argument_list|()
expr_stmt|;
else|else
name|name
operator|=
name|g_strdup
argument_list|(
name|pattern_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_pattern_get_pixels
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
name|bytes
argument_list|,
operator|&
name|mask_data_size
argument_list|,
operator|&
name|mask_data
argument_list|)
condition|)
block|{
name|gimp_pattern_select_widget_callback
argument_list|(
name|name
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bytes
argument_list|,
name|mask_data
argument_list|,
name|FALSE
argument_list|,
name|pattern_sel
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
DECL|function|gimp_pattern_select_widget_callback (const gchar * name,gint width,gint height,gint bytes,const guchar * mask_data,gboolean closing,gpointer data)
name|gimp_pattern_select_widget_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bytes
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
name|PatternSelect
modifier|*
name|pattern_sel
init|=
operator|(
name|PatternSelect
operator|*
operator|)
name|data
decl_stmt|;
name|g_free
argument_list|(
name|pattern_sel
operator|->
name|pattern_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern_sel
operator|->
name|mask_data
argument_list|)
expr_stmt|;
name|pattern_sel
operator|->
name|pattern_name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|pattern_sel
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|pattern_sel
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|pattern_sel
operator|->
name|bytes
operator|=
name|bytes
expr_stmt|;
name|pattern_sel
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
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|gimp_pattern_select_preview_update
argument_list|(
name|pattern_sel
operator|->
name|preview
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bytes
argument_list|,
name|mask_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern_sel
operator|->
name|callback
condition|)
name|pattern_sel
operator|->
name|callback
argument_list|(
name|name
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bytes
argument_list|,
name|mask_data
argument_list|,
name|closing
argument_list|,
name|pattern_sel
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|closing
condition|)
name|pattern_sel
operator|->
name|temp_pattern_callback
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_select_widget_clicked (GtkWidget * widget,PatternSelect * pattern_sel)
name|gimp_pattern_select_widget_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PatternSelect
modifier|*
name|pattern_sel
parameter_list|)
block|{
if|if
condition|(
name|pattern_sel
operator|->
name|temp_pattern_callback
condition|)
block|{
comment|/*  calling gimp_patterns_set_popup() raises the dialog  */
name|gimp_patterns_set_popup
argument_list|(
name|pattern_sel
operator|->
name|temp_pattern_callback
argument_list|,
name|pattern_sel
operator|->
name|pattern_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|pattern_sel
operator|->
name|temp_pattern_callback
operator|=
name|gimp_pattern_select_new
argument_list|(
name|pattern_sel
operator|->
name|title
argument_list|,
name|pattern_sel
operator|->
name|pattern_name
argument_list|,
name|gimp_pattern_select_widget_callback
argument_list|,
name|pattern_sel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_select_widget_destroy (GtkWidget * widget,PatternSelect * pattern_sel)
name|gimp_pattern_select_widget_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PatternSelect
modifier|*
name|pattern_sel
parameter_list|)
block|{
if|if
condition|(
name|pattern_sel
operator|->
name|temp_pattern_callback
condition|)
block|{
name|gimp_pattern_select_destroy
argument_list|(
name|pattern_sel
operator|->
name|temp_pattern_callback
argument_list|)
expr_stmt|;
name|pattern_sel
operator|->
name|temp_pattern_callback
operator|=
name|NULL
expr_stmt|;
block|}
name|g_free
argument_list|(
name|pattern_sel
operator|->
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern_sel
operator|->
name|pattern_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern_sel
operator|->
name|mask_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern_sel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_select_preview_resize (PatternSelect * pattern_sel)
name|gimp_pattern_select_preview_resize
parameter_list|(
name|PatternSelect
modifier|*
name|pattern_sel
parameter_list|)
block|{
if|if
condition|(
name|pattern_sel
operator|->
name|width
operator|>
literal|0
operator|&&
name|pattern_sel
operator|->
name|height
operator|>
literal|0
condition|)
name|gimp_pattern_select_preview_update
argument_list|(
name|pattern_sel
operator|->
name|preview
argument_list|,
name|pattern_sel
operator|->
name|width
argument_list|,
name|pattern_sel
operator|->
name|height
argument_list|,
name|pattern_sel
operator|->
name|bytes
argument_list|,
name|pattern_sel
operator|->
name|mask_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_pattern_select_preview_events (GtkWidget * widget,GdkEvent * event,PatternSelect * pattern_sel)
name|gimp_pattern_select_preview_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|PatternSelect
modifier|*
name|pattern_sel
parameter_list|)
block|{
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
if|if
condition|(
name|pattern_sel
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
name|gimp_pattern_select_popup_open
argument_list|(
name|pattern_sel
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
name|gimp_pattern_select_popup_close
argument_list|(
name|pattern_sel
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
DECL|function|gimp_pattern_select_preview_update (GtkWidget * preview,gint width,gint height,gint bytes,const guchar * mask_data)
name|gimp_pattern_select_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bytes
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask_data
parameter_list|)
block|{
name|GimpImageType
name|type
decl_stmt|;
switch|switch
condition|(
name|bytes
condition|)
block|{
case|case
literal|1
case|:
name|type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|type
operator|=
name|GIMP_GRAYA_IMAGE
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
break|break;
default|default:
return|return;
block|}
name|gimp_preview_area_draw
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
name|width
argument_list|,
name|height
argument_list|,
name|type
argument_list|,
name|mask_data
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_select_popup_open (PatternSelect * pattern_sel,gint x,gint y)
name|gimp_pattern_select_popup_open
parameter_list|(
name|PatternSelect
modifier|*
name|pattern_sel
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
name|pattern_sel
operator|->
name|popup
condition|)
name|gimp_pattern_select_popup_close
argument_list|(
name|pattern_sel
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern_sel
operator|->
name|width
operator|<=
name|CELL_SIZE
operator|&&
name|pattern_sel
operator|->
name|height
operator|<=
name|CELL_SIZE
condition|)
return|return;
name|pattern_sel
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
name|pattern_sel
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
name|pattern_sel
operator|->
name|width
argument_list|,
name|pattern_sel
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
name|pattern_sel
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
name|pattern_sel
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
name|pattern_sel
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
name|pattern_sel
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
name|pattern_sel
operator|->
name|width
operator|>
name|scr_w
operator|)
condition|?
name|scr_w
operator|-
name|pattern_sel
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
name|pattern_sel
operator|->
name|height
operator|>
name|scr_h
operator|)
condition|?
name|scr_h
operator|-
name|pattern_sel
operator|->
name|height
else|:
name|y
expr_stmt|;
name|gtk_window_move
argument_list|(
name|GTK_WINDOW
argument_list|(
name|pattern_sel
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
name|pattern_sel
operator|->
name|popup
argument_list|)
expr_stmt|;
comment|/*  Draw the pattern  */
name|gimp_pattern_select_preview_update
argument_list|(
name|preview
argument_list|,
name|pattern_sel
operator|->
name|width
argument_list|,
name|pattern_sel
operator|->
name|height
argument_list|,
name|pattern_sel
operator|->
name|bytes
argument_list|,
name|pattern_sel
operator|->
name|mask_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_select_popup_close (PatternSelect * pattern_sel)
name|gimp_pattern_select_popup_close
parameter_list|(
name|PatternSelect
modifier|*
name|pattern_sel
parameter_list|)
block|{
if|if
condition|(
name|pattern_sel
operator|->
name|popup
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|pattern_sel
operator|->
name|popup
argument_list|)
expr_stmt|;
name|pattern_sel
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
DECL|function|gimp_pattern_select_drag_data_received (GtkWidget * preview,GdkDragContext * context,gint x,gint y,GtkSelectionData * selection,guint info,guint time,GtkWidget * widget)
name|gimp_pattern_select_drag_data_received
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
literal|"Received invalid pattern data!"
argument_list|)
expr_stmt|;
return|return;
block|}
name|str
operator|=
name|g_strndup
argument_list|(
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
name|gimp_pattern_select_widget_set
argument_list|(
name|widget
argument_list|,
name|name
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

