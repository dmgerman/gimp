begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpgradientmenu.c  * Copyright (C) 1998 Andy Thomas  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
DECL|macro|GRADIENT_SELECT_DATA_KEY
define|#
directive|define
name|GRADIENT_SELECT_DATA_KEY
value|"gimp-grdient-select-data"
end_define

begin_define
DECL|macro|CELL_HEIGHT
define|#
directive|define
name|CELL_HEIGHT
value|18
end_define

begin_define
DECL|macro|CELL_WIDTH
define|#
directive|define
name|CELL_WIDTH
value|84
end_define

begin_typedef
DECL|typedef|GradientSelect
typedef|typedef
name|struct
name|_GradientSelect
name|GradientSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_GradientSelect
struct|struct
name|_GradientSelect
block|{
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|callback
name|GimpRunGradientCallback
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
DECL|member|gradient_name
name|gchar
modifier|*
name|gradient_name
decl_stmt|;
comment|/* Local copy */
DECL|member|sample_size
name|gint
name|sample_size
decl_stmt|;
DECL|member|reverse
name|gboolean
name|reverse
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|gradient_data
name|gdouble
modifier|*
name|gradient_data
decl_stmt|;
comment|/* Local copy */
DECL|member|temp_gradient_callback
specifier|const
name|gchar
modifier|*
name|temp_gradient_callback
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
name|gimp_gradient_select_widget_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|width
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|gradient_data
parameter_list|,
name|gint
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
name|gimp_gradient_select_widget_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GradientSelect
modifier|*
name|gradient_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gradient_select_widget_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GradientSelect
modifier|*
name|gradient_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gradient_select_preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GradientSelect
modifier|*
name|gradient_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gradient_select_preview_expose
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|,
name|GradientSelect
modifier|*
name|gradient_sel
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_gradient_select_widget_new:  * @title:         Title of the dialog to use or %NULL to use the default title.  * @gradient_name: Initial gradient name or %NULL to use current selection.  * @callback:      A function to call when the selected gradient changes.  * @data:          A pointer to arbitary data to be used in the call to  *                 @callback.  *  * Creates a new #GtkWidget that completely controls the selection of  * a gradient.  This widget is suitable for placement in a table in a  * plug-in dialog.  *  * Returns: A #GtkWidget that you can use in your UI.  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_gradient_select_widget_new (const gchar * title,const gchar * gradient_name,GimpRunGradientCallback callback,gpointer data)
name|gimp_gradient_select_widget_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|,
name|GimpRunGradientCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gradient_sel
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
literal|"Gradient Selection"
argument_list|)
expr_stmt|;
name|gradient_sel
operator|=
name|g_new0
argument_list|(
name|GradientSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gradient_sel
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gradient_sel
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|gradient_sel
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|gradient_sel
operator|->
name|sample_size
operator|=
name|CELL_WIDTH
expr_stmt|;
name|gradient_sel
operator|->
name|reverse
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|gradient_name
operator|||
operator|!
name|strlen
argument_list|(
name|gradient_name
argument_list|)
condition|)
name|gradient_sel
operator|->
name|gradient_name
operator|=
name|gimp_context_get_gradient
argument_list|()
expr_stmt|;
else|else
name|gradient_sel
operator|->
name|gradient_name
operator|=
name|g_strdup
argument_list|(
name|gradient_name
argument_list|)
expr_stmt|;
name|gradient_sel
operator|->
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gradient_sel
operator|->
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gradient_select_widget_clicked
argument_list|)
argument_list|,
name|gradient_sel
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gradient_sel
operator|->
name|button
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gradient_select_widget_destroy
argument_list|)
argument_list|,
name|gradient_sel
argument_list|)
expr_stmt|;
name|gradient_sel
operator|->
name|preview
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|gradient_sel
operator|->
name|preview
argument_list|,
name|CELL_WIDTH
argument_list|,
name|CELL_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|gradient_sel
operator|->
name|button
argument_list|)
argument_list|,
name|gradient_sel
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gradient_sel
operator|->
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gradient_sel
operator|->
name|preview
argument_list|,
literal|"size_allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gradient_select_preview_size_allocate
argument_list|)
argument_list|,
name|gradient_sel
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gradient_sel
operator|->
name|preview
argument_list|,
literal|"expose_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gradient_select_preview_expose
argument_list|)
argument_list|,
name|gradient_sel
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gradient_sel
operator|->
name|button
argument_list|)
argument_list|,
name|GRADIENT_SELECT_DATA_KEY
argument_list|,
name|gradient_sel
argument_list|)
expr_stmt|;
return|return
name|gradient_sel
operator|->
name|button
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_gradient_select_widget_close;  * @widget: A gradient select widget.  *  * Closes the popup window associated with @widget.  */
end_comment

begin_function
name|void
DECL|function|gimp_gradient_select_widget_close (GtkWidget * widget)
name|gimp_gradient_select_widget_close
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gradient_sel
decl_stmt|;
name|gradient_sel
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GRADIENT_SELECT_DATA_KEY
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gradient_sel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient_sel
operator|->
name|temp_gradient_callback
condition|)
block|{
name|gimp_gradient_select_destroy
argument_list|(
name|gradient_sel
operator|->
name|temp_gradient_callback
argument_list|)
expr_stmt|;
name|gradient_sel
operator|->
name|temp_gradient_callback
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_gradient_select_widget_set:  * @widget:        A gradient select widget.  * @gradient_name: Gradient name to set.  *  * Sets the current gradient for the gradient select widget.  Calls  * the callback function if one was supplied in the call to  * gimp_gradient_select_widget_new().  */
end_comment

begin_function
name|void
DECL|function|gimp_gradient_select_widget_set (GtkWidget * widget,const gchar * gradient_name)
name|gimp_gradient_select_widget_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gradient_sel
decl_stmt|;
name|gradient_sel
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GRADIENT_SELECT_DATA_KEY
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gradient_sel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient_sel
operator|->
name|temp_gradient_callback
condition|)
block|{
name|gimp_gradients_set_popup
argument_list|(
name|gradient_sel
operator|->
name|temp_gradient_callback
argument_list|,
name|gradient_name
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
name|n_samples
decl_stmt|;
name|gdouble
modifier|*
name|samples
decl_stmt|;
if|if
condition|(
operator|!
name|gradient_name
operator|||
operator|!
name|strlen
argument_list|(
name|gradient_name
argument_list|)
condition|)
name|name
operator|=
name|gimp_context_get_gradient
argument_list|()
expr_stmt|;
else|else
name|name
operator|=
name|g_strdup
argument_list|(
name|gradient_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_gradient_get_uniform_samples
argument_list|(
name|name
argument_list|,
name|gradient_sel
operator|->
name|sample_size
argument_list|,
name|gradient_sel
operator|->
name|reverse
argument_list|,
operator|&
name|n_samples
argument_list|,
operator|&
name|samples
argument_list|)
condition|)
block|{
name|gimp_gradient_select_widget_callback
argument_list|(
name|name
argument_list|,
name|n_samples
argument_list|,
name|samples
argument_list|,
name|FALSE
argument_list|,
name|gradient_sel
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|samples
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
DECL|function|gimp_gradient_select_widget_callback (const gchar * name,gint width,const gdouble * gradient_data,gint closing,gpointer data)
name|gimp_gradient_select_widget_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|width
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|gradient_data
parameter_list|,
name|gint
name|closing
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GradientSelect
modifier|*
name|gradient_sel
init|=
operator|(
name|GradientSelect
operator|*
operator|)
name|data
decl_stmt|;
name|g_free
argument_list|(
name|gradient_sel
operator|->
name|gradient_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gradient_sel
operator|->
name|gradient_data
argument_list|)
expr_stmt|;
name|gradient_sel
operator|->
name|gradient_name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gradient_sel
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|gradient_sel
operator|->
name|gradient_data
operator|=
name|g_memdup
argument_list|(
name|gradient_data
argument_list|,
name|width
operator|*
literal|4
operator|*
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|gradient_sel
operator|->
name|preview
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient_sel
operator|->
name|callback
condition|)
name|gradient_sel
operator|->
name|callback
argument_list|(
name|name
argument_list|,
name|width
argument_list|,
name|gradient_data
argument_list|,
name|closing
argument_list|,
name|gradient_sel
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|closing
condition|)
name|gradient_sel
operator|->
name|temp_gradient_callback
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_widget_clicked (GtkWidget * widget,GradientSelect * gradient_sel)
name|gimp_gradient_select_widget_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GradientSelect
modifier|*
name|gradient_sel
parameter_list|)
block|{
if|if
condition|(
name|gradient_sel
operator|->
name|temp_gradient_callback
condition|)
block|{
comment|/*  calling gimp_gradients_set_popup() raises the dialog  */
name|gimp_gradients_set_popup
argument_list|(
name|gradient_sel
operator|->
name|temp_gradient_callback
argument_list|,
name|gradient_sel
operator|->
name|gradient_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gradient_sel
operator|->
name|temp_gradient_callback
operator|=
name|gimp_gradient_select_new
argument_list|(
name|gradient_sel
operator|->
name|title
argument_list|,
name|gradient_sel
operator|->
name|gradient_name
argument_list|,
name|gradient_sel
operator|->
name|sample_size
argument_list|,
name|gimp_gradient_select_widget_callback
argument_list|,
name|gradient_sel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_widget_destroy (GtkWidget * widget,GradientSelect * gradient_sel)
name|gimp_gradient_select_widget_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GradientSelect
modifier|*
name|gradient_sel
parameter_list|)
block|{
if|if
condition|(
name|gradient_sel
operator|->
name|temp_gradient_callback
condition|)
block|{
name|gimp_gradient_select_destroy
argument_list|(
name|gradient_sel
operator|->
name|temp_gradient_callback
argument_list|)
expr_stmt|;
name|gradient_sel
operator|->
name|temp_gradient_callback
operator|=
name|NULL
expr_stmt|;
block|}
name|g_free
argument_list|(
name|gradient_sel
operator|->
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gradient_sel
operator|->
name|gradient_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gradient_sel
operator|->
name|gradient_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gradient_sel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_preview_size_allocate (GtkWidget * widget,GtkAllocation * allocation,GradientSelect * gradient_sel)
name|gimp_gradient_select_preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GradientSelect
modifier|*
name|gradient_sel
parameter_list|)
block|{
name|gint
name|n_samples
decl_stmt|;
name|gdouble
modifier|*
name|samples
decl_stmt|;
if|if
condition|(
name|gimp_gradient_get_uniform_samples
argument_list|(
name|gradient_sel
operator|->
name|gradient_name
argument_list|,
name|allocation
operator|->
name|width
argument_list|,
name|gradient_sel
operator|->
name|reverse
argument_list|,
operator|&
name|n_samples
argument_list|,
operator|&
name|samples
argument_list|)
condition|)
block|{
name|gradient_sel
operator|->
name|sample_size
operator|=
name|allocation
operator|->
name|width
expr_stmt|;
name|gradient_sel
operator|->
name|width
operator|=
name|n_samples
expr_stmt|;
name|g_free
argument_list|(
name|gradient_sel
operator|->
name|gradient_data
argument_list|)
expr_stmt|;
name|gradient_sel
operator|->
name|gradient_data
operator|=
name|samples
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_preview_expose (GtkWidget * widget,GdkEventExpose * event,GradientSelect * gradient_sel)
name|gimp_gradient_select_preview_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|,
name|GradientSelect
modifier|*
name|gradient_sel
parameter_list|)
block|{
specifier|const
name|gdouble
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|p0
decl_stmt|;
name|guchar
modifier|*
name|p1
decl_stmt|;
name|guchar
modifier|*
name|even
decl_stmt|;
name|guchar
modifier|*
name|odd
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|src
operator|=
name|gradient_sel
operator|->
name|gradient_data
expr_stmt|;
if|if
condition|(
operator|!
name|src
condition|)
return|return;
name|p0
operator|=
name|even
operator|=
name|g_malloc
argument_list|(
name|gradient_sel
operator|->
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|p1
operator|=
name|odd
operator|=
name|g_malloc
argument_list|(
name|gradient_sel
operator|->
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|gradient_sel
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
name|gdouble
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
name|gdouble
name|c0
decl_stmt|,
name|c1
decl_stmt|;
name|r
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|0
index|]
expr_stmt|;
name|g
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|1
index|]
expr_stmt|;
name|b
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|2
index|]
expr_stmt|;
name|a
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|3
index|]
expr_stmt|;
if|if
condition|(
operator|(
name|x
operator|/
name|GIMP_CHECK_SIZE_SM
operator|)
operator|&
literal|1
condition|)
block|{
name|c0
operator|=
name|GIMP_CHECK_LIGHT
expr_stmt|;
name|c1
operator|=
name|GIMP_CHECK_DARK
expr_stmt|;
block|}
else|else
block|{
name|c0
operator|=
name|GIMP_CHECK_DARK
expr_stmt|;
name|c1
operator|=
name|GIMP_CHECK_LIGHT
expr_stmt|;
block|}
operator|*
name|p0
operator|++
operator|=
operator|(
name|c0
operator|+
operator|(
name|r
operator|-
name|c0
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p0
operator|++
operator|=
operator|(
name|c0
operator|+
operator|(
name|g
operator|-
name|c0
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p0
operator|++
operator|=
operator|(
name|c0
operator|+
operator|(
name|b
operator|-
name|c0
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
operator|(
name|c1
operator|+
operator|(
name|r
operator|-
name|c1
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
operator|(
name|c1
operator|+
operator|(
name|g
operator|-
name|c1
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
operator|(
name|c1
operator|+
operator|(
name|b
operator|-
name|c1
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
block|}
for|for
control|(
name|y
operator|=
name|event
operator|->
name|area
operator|.
name|y
init|;
name|y
operator|<
name|event
operator|->
name|area
operator|.
name|y
operator|+
name|event
operator|->
name|area
operator|.
name|height
condition|;
name|y
operator|++
control|)
block|{
name|guchar
modifier|*
name|buf
init|=
operator|(
operator|(
name|y
operator|/
name|GIMP_CHECK_SIZE_SM
operator|)
operator|&
literal|1
operator|)
condition|?
name|odd
else|:
name|even
decl_stmt|;
name|gdk_draw_rgb_image_dithalign
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|fg_gc
index|[
name|widget
operator|->
name|state
index|]
argument_list|,
name|event
operator|->
name|area
operator|.
name|x
argument_list|,
name|y
argument_list|,
name|event
operator|->
name|area
operator|.
name|width
argument_list|,
literal|1
argument_list|,
name|GDK_RGB_DITHER_MAX
argument_list|,
name|buf
operator|+
name|event
operator|->
name|area
operator|.
name|x
operator|*
literal|3
argument_list|,
name|gradient_sel
operator|->
name|width
operator|*
literal|3
argument_list|,
operator|-
name|event
operator|->
name|area
operator|.
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|odd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|even
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

