begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  * Copyright (C) 1998 Andy Thomas                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

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

begin_comment
comment|/* Idea is to have a function to call that returns a widget that   * completely controls the selection of a gradient.  * you get a widget returned that you can use in a table say.  * In:- Initial gradient name. Null means use current selection.  *      pointer to func to call when gradient changes (GRunGradientCallback).  * Returned:- Pointer to a widget that you can use in UI.  *   * Widget simply made up of a preview widget (20x40) containing the gradient  * which can be clicked on to changed the gradient selection.  */
end_comment

begin_define
DECL|macro|GSEL_DATA_KEY
define|#
directive|define
name|GSEL_DATA_KEY
value|"__gsel_data"
end_define

begin_define
DECL|macro|CELL_SIZE_HEIGHT
define|#
directive|define
name|CELL_SIZE_HEIGHT
value|18
end_define

begin_define
DECL|macro|CELL_SIZE_WIDTH
define|#
directive|define
name|CELL_SIZE_WIDTH
value|84
end_define

begin_struct
DECL|struct|__gradients_sel
struct|struct
name|__gradients_sel
block|{
DECL|member|dname
name|gchar
modifier|*
name|dname
decl_stmt|;
DECL|member|cback
name|GRunGradientCallback
name|cback
decl_stmt|;
DECL|member|gradient_preview
name|GtkWidget
modifier|*
name|gradient_preview
decl_stmt|;
DECL|member|button
name|GtkWidget
modifier|*
name|button
decl_stmt|;
DECL|member|gradient_popup_pnt
name|GtkWidget
modifier|*
name|gradient_popup_pnt
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|gradient_name
name|gchar
modifier|*
name|gradient_name
decl_stmt|;
comment|/* Local copy */
DECL|member|grad_data
name|gdouble
modifier|*
name|grad_data
decl_stmt|;
comment|/* local copy */
DECL|member|sample_size
name|gint
name|sample_size
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GSelect
typedef|typedef
name|struct
name|__gradients_sel
name|GSelect
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|gradient_pre_update (GtkWidget * gradient_preview,gint width_data,gdouble * grad_data)
name|gradient_pre_update
parameter_list|(
name|GtkWidget
modifier|*
name|gradient_preview
parameter_list|,
name|gint
name|width_data
parameter_list|,
name|gdouble
modifier|*
name|grad_data
parameter_list|)
block|{
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gdouble
modifier|*
name|src
decl_stmt|;
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
name|width
decl_stmt|;
name|width
operator|=
name|width_data
operator|/
literal|4
expr_stmt|;
comment|/*  Draw the gradient  */
name|src
operator|=
name|grad_data
expr_stmt|;
name|p0
operator|=
name|even
operator|=
name|g_malloc
argument_list|(
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
name|width
condition|;
name|x
operator|++
control|)
block|{
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
literal|0
init|;
name|y
operator|<
name|CELL_SIZE_HEIGHT
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|y
operator|/
name|GIMP_CHECK_SIZE_SM
operator|)
operator|&
literal|1
condition|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|gradient_preview
argument_list|)
argument_list|,
operator|(
name|guchar
operator|*
operator|)
name|odd
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
operator|(
name|width
operator|<
name|CELL_SIZE_WIDTH
operator|)
condition|?
name|width
else|:
name|CELL_SIZE_WIDTH
argument_list|)
expr_stmt|;
else|else
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|gradient_preview
argument_list|)
argument_list|,
operator|(
name|guchar
operator|*
operator|)
name|even
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
operator|(
name|width
operator|<
name|CELL_SIZE_WIDTH
operator|)
condition|?
name|width
else|:
name|CELL_SIZE_WIDTH
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|even
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|odd
argument_list|)
expr_stmt|;
comment|/*  Draw the brush preview  */
name|gtk_widget_draw
argument_list|(
name|gradient_preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_select_invoker (gchar * name,gint width,gdouble * grad_data,gint closing,gpointer data)
name|gradient_select_invoker
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|width
parameter_list|,
name|gdouble
modifier|*
name|grad_data
parameter_list|,
name|gint
name|closing
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GSelect
modifier|*
name|gsel
init|=
operator|(
name|GSelect
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|gsel
operator|->
name|grad_data
operator|!=
name|NULL
condition|)
name|g_free
argument_list|(
name|gsel
operator|->
name|grad_data
argument_list|)
expr_stmt|;
name|gsel
operator|->
name|width
operator|=
name|width
expr_stmt|;
if|if
condition|(
name|gsel
operator|->
name|gradient_name
condition|)
name|g_free
argument_list|(
name|gsel
operator|->
name|gradient_name
argument_list|)
expr_stmt|;
name|gsel
operator|->
name|gradient_name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
comment|/* one row only each row has four doubles r,g,b,a */
name|gsel
operator|->
name|grad_data
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  printf("name = %s width = %d\n",name,width);*/
name|g_memmove
argument_list|(
name|gsel
operator|->
name|grad_data
argument_list|,
name|grad_data
argument_list|,
name|width
operator|*
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
name|gradient_pre_update
argument_list|(
name|gsel
operator|->
name|gradient_preview
argument_list|,
name|gsel
operator|->
name|width
argument_list|,
name|gsel
operator|->
name|grad_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gsel
operator|->
name|cback
operator|!=
name|NULL
condition|)
call|(
name|gsel
operator|->
name|cback
call|)
argument_list|(
name|name
argument_list|,
name|width
argument_list|,
name|grad_data
argument_list|,
name|closing
argument_list|,
name|gsel
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|closing
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|gsel
operator|->
name|button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_preview_callback (GtkWidget * widget,gpointer data)
name|gradient_preview_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GSelect
modifier|*
name|gsel
init|=
operator|(
name|GSelect
operator|*
operator|)
name|data
decl_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gsel
operator|->
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gsel
operator|->
name|gradient_popup_pnt
operator|=
name|gimp_interactive_selection_gradient
argument_list|(
operator|(
name|gsel
operator|->
name|dname
operator|)
condition|?
name|gsel
operator|->
name|dname
else|:
literal|"Gradient Plugin Selection"
argument_list|,
name|gsel
operator|->
name|gradient_name
argument_list|,
name|gsel
operator|->
name|sample_size
argument_list|,
name|gradient_select_invoker
argument_list|,
name|gsel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_gradient_select_widget (gchar * dname,gchar * igradient,GRunGradientCallback cback,gpointer data)
name|gimp_gradient_select_widget
parameter_list|(
name|gchar
modifier|*
name|dname
parameter_list|,
name|gchar
modifier|*
name|igradient
parameter_list|,
name|GRunGradientCallback
name|cback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|gradient
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gdouble
modifier|*
name|grad_data
decl_stmt|;
name|gchar
modifier|*
name|gradient_name
decl_stmt|;
name|GSelect
modifier|*
name|gsel
decl_stmt|;
name|gsel
operator|=
name|g_new
argument_list|(
name|GSelect
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
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gradient
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
name|gradient
argument_list|)
argument_list|,
name|CELL_SIZE_WIDTH
argument_list|,
name|CELL_SIZE_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gradient_preview_callback
argument_list|,
operator|(
name|gpointer
operator|)
name|gsel
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gsel
operator|->
name|button
operator|=
name|button
expr_stmt|;
name|gsel
operator|->
name|cback
operator|=
name|cback
expr_stmt|;
name|gsel
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|gsel
operator|->
name|grad_data
operator|=
name|NULL
expr_stmt|;
name|gsel
operator|->
name|gradient_preview
operator|=
name|gradient
expr_stmt|;
name|gsel
operator|->
name|dname
operator|=
name|dname
expr_stmt|;
name|gsel
operator|->
name|gradient_popup_pnt
operator|=
name|NULL
expr_stmt|;
name|gsel
operator|->
name|sample_size
operator|=
name|CELL_SIZE_WIDTH
expr_stmt|;
comment|/* Do initial gradient setup */
name|gradient_name
operator|=
name|gimp_gradient_get_gradient_data
argument_list|(
name|igradient
argument_list|,
operator|&
name|width
argument_list|,
name|CELL_SIZE_WIDTH
argument_list|,
operator|&
name|grad_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient_name
condition|)
block|{
name|gradient_pre_update
argument_list|(
name|gsel
operator|->
name|gradient_preview
argument_list|,
name|width
argument_list|,
name|grad_data
argument_list|)
expr_stmt|;
name|gsel
operator|->
name|grad_data
operator|=
name|grad_data
expr_stmt|;
name|gsel
operator|->
name|gradient_name
operator|=
name|gradient_name
expr_stmt|;
name|gsel
operator|->
name|width
operator|=
name|width
expr_stmt|;
block|}
else|else
block|{
name|gsel
operator|->
name|gradient_name
operator|=
name|g_strdup
argument_list|(
name|igradient
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
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|GSEL_DATA_KEY
argument_list|,
operator|(
name|gpointer
operator|)
name|gsel
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_gradient_select_widget_close_popup (GtkWidget * widget)
name|gimp_gradient_select_widget_close_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gboolean
name|ret_val
init|=
name|FALSE
decl_stmt|;
name|GSelect
modifier|*
name|gsel
decl_stmt|;
name|gsel
operator|=
operator|(
name|GSelect
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GSEL_DATA_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
name|gsel
operator|&&
name|gsel
operator|->
name|gradient_popup_pnt
condition|)
block|{
name|ret_val
operator|=
name|gimp_gradient_close_popup
argument_list|(
name|gsel
operator|->
name|gradient_popup_pnt
argument_list|)
expr_stmt|;
name|gsel
operator|->
name|gradient_popup_pnt
operator|=
name|NULL
expr_stmt|;
block|}
return|return
name|ret_val
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_gradient_select_widget_set_popup (GtkWidget * widget,gchar * gname)
name|gimp_gradient_select_widget_set_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gchar
modifier|*
name|gname
parameter_list|)
block|{
name|gboolean
name|ret_val
init|=
name|FALSE
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gdouble
modifier|*
name|grad_data
decl_stmt|;
name|gchar
modifier|*
name|gradient_name
decl_stmt|;
name|GSelect
modifier|*
name|gsel
decl_stmt|;
name|gsel
operator|=
operator|(
name|GSelect
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GSEL_DATA_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
name|gsel
condition|)
block|{
name|gradient_name
operator|=
name|gimp_gradient_get_gradient_data
argument_list|(
name|gname
argument_list|,
operator|&
name|width
argument_list|,
name|gsel
operator|->
name|sample_size
argument_list|,
operator|&
name|grad_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient_name
condition|)
block|{
name|gradient_select_invoker
argument_list|(
name|gname
argument_list|,
name|width
argument_list|,
name|grad_data
argument_list|,
literal|0
argument_list|,
name|gsel
argument_list|)
expr_stmt|;
if|if
condition|(
name|gsel
operator|->
name|gradient_popup_pnt
operator|&&
name|gimp_gradient_set_popup
argument_list|(
name|gsel
operator|->
name|gradient_popup_pnt
argument_list|,
name|gname
argument_list|)
condition|)
name|ret_val
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
return|return
name|ret_val
return|;
block|}
end_function

end_unit

