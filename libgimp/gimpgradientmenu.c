begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpgradientmenu.c  * Copyright (C) 1998 Andy Thomas  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpuitypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradientselectbutton.h"
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimpgradientmenu.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2977f6070108
block|{
DECL|member|callback
name|GimpRunGradientCallback
name|callback
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|typedef|CompatCallbackData
block|}
name|CompatCallbackData
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|compat_callback
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|gradient_button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|,
name|gint
name|width
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|grad_data
parameter_list|,
name|gboolean
name|dialog_closing
parameter_list|,
name|CompatCallbackData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|compat_callback_data_free
parameter_list|(
name|CompatCallbackData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_gradient_select_widget_new:  * @title:         Title of the dialog to use or %NULL to use the default title.  * @gradient_name: Initial gradient name.  * @callback:      A function to call when the selected gradient changes.  * @data:          A pointer to arbitary data to be used in the call to @callback.  *  * Creates a new #GtkWidget that completely controls the selection of  * a gradient.  This widget is suitable for placement in a table in a  * plug-in dialog.  *  * Returns: A #GtkWidget that you can use in your UI.  *  * Since: GIMP 2.2  */
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
name|GtkWidget
modifier|*
name|gradient_button
decl_stmt|;
name|CompatCallbackData
modifier|*
name|compat_data
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
name|gradient_button
operator|=
name|gimp_gradient_select_button_new
argument_list|(
name|title
argument_list|,
name|gradient_name
argument_list|)
expr_stmt|;
name|compat_data
operator|=
name|g_slice_new
argument_list|(
name|CompatCallbackData
argument_list|)
expr_stmt|;
name|compat_data
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|compat_data
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|g_signal_connect_data
argument_list|(
name|gradient_button
argument_list|,
literal|"gradient-set"
argument_list|,
name|G_CALLBACK
argument_list|(
name|compat_callback
argument_list|)
argument_list|,
name|compat_data
argument_list|,
operator|(
name|GClosureNotify
operator|)
name|compat_callback_data_free
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|gradient_button
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_gradient_select_widget_close:  * @widget: A gradient select widget.  *  * Closes the popup window associated with @widget.  */
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
name|g_return_if_fail
argument_list|(
name|widget
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_select_button_close_popup
argument_list|(
name|GIMP_SELECT_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_gradient_select_widget_set;  * @widget:        A gradient select widget.  * @gradient_name: Gradient name to set.  *  * Sets the current gradient for the gradient select widget.  Calls the  * callback function if one was supplied in the call to  * gimp_gradient_select_widget_new().  */
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
name|g_return_if_fail
argument_list|(
name|widget
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gradient_select_button_set_gradient
argument_list|(
name|GIMP_GRADIENT_SELECT_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|,
name|gradient_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|compat_callback (GimpGradientSelectButton * gradient_button,const gchar * gradient_name,gint width,const gdouble * grad_data,gboolean dialog_closing,CompatCallbackData * data)
name|compat_callback
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|gradient_button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|,
name|gint
name|width
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|grad_data
parameter_list|,
name|gboolean
name|dialog_closing
parameter_list|,
name|CompatCallbackData
modifier|*
name|data
parameter_list|)
block|{
name|data
operator|->
name|callback
argument_list|(
name|gradient_name
argument_list|,
name|width
argument_list|,
name|grad_data
argument_list|,
name|dialog_closing
argument_list|,
name|data
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|compat_callback_data_free (CompatCallbackData * data)
name|compat_callback_data_free
parameter_list|(
name|CompatCallbackData
modifier|*
name|data
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|CompatCallbackData
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

