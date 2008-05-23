begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpfontmenu.c  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimpfontselectbutton.h"
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimpfontmenu.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27ed987c0108
block|{
DECL|member|callback
name|GimpRunFontCallback
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
name|GimpFontSelectButton
modifier|*
name|font_button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
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
comment|/**  * gimp_font_select_widget_new:  * @title:     Title of the dialog to use or %NULL to use the default title.  * @font_name: Initial font name.  * @callback:  A function to call when the selected font changes.  * @data:      A pointer to arbitary data to be used in the call to @callback.  *  * Creates a new #GtkWidget that completely controls the selection of  * a font.  This widget is suitable for placement in a table in a  * plug-in dialog.  *  * Returns: A #GtkWidget that you can use in your UI.  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_font_select_widget_new (const gchar * title,const gchar * font_name,GimpRunFontCallback callback,gpointer data)
name|gimp_font_select_widget_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
parameter_list|,
name|GimpRunFontCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|font_button
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
name|font_button
operator|=
name|gimp_font_select_button_new
argument_list|(
name|title
argument_list|,
name|font_name
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
name|font_button
argument_list|,
literal|"font-set"
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
name|font_button
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_font_select_widget_close:  * @widget: A font select widget.  *  * Closes the popup window associated with @widget.  */
end_comment

begin_function
name|void
DECL|function|gimp_font_select_widget_close (GtkWidget * widget)
name|gimp_font_select_widget_close
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
comment|/**  * gimp_font_select_widget_set;  * @widget:    A font select widget.  * @font_name: Font name to set; %NULL means no change.  *  * Sets the current font for the font select widget.  Calls the  * callback function if one was supplied in the call to  * gimp_font_select_widget_new().  */
end_comment

begin_function
name|void
DECL|function|gimp_font_select_widget_set (GtkWidget * widget,const gchar * font_name)
name|gimp_font_select_widget_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|widget
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_font_select_button_set_font
argument_list|(
name|GIMP_FONT_SELECT_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|,
name|font_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|compat_callback (GimpFontSelectButton * font_button,const gchar * font_name,gboolean dialog_closing,CompatCallbackData * data)
name|compat_callback
parameter_list|(
name|GimpFontSelectButton
modifier|*
name|font_button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
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
name|font_name
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

