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
DECL|macro|FONT_SELECT_DATA_KEY
define|#
directive|define
name|FONT_SELECT_DATA_KEY
value|"gimp-font-selct-data"
end_define

begin_typedef
DECL|typedef|FontSelect
typedef|typedef
name|struct
name|_FontSelect
name|FontSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_FontSelect
struct|struct
name|_FontSelect
block|{
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|callback
name|GimpRunFontCallback
name|callback
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|member|button
name|GtkWidget
modifier|*
name|button
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
decl_stmt|;
DECL|member|font_name
name|gchar
modifier|*
name|font_name
decl_stmt|;
comment|/* Local copy */
DECL|member|temp_font_callback
specifier|const
name|gchar
modifier|*
name|temp_font_callback
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
name|gimp_font_select_widget_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|gimp_font_select_widget_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|FontSelect
modifier|*
name|font_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_select_widget_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|FontSelect
modifier|*
name|font_sel
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_font_select_widget_new:  * @title:     Title of the dialog to use or %NULL means to use the default  *             title.  * @font_name: Initial font name.  * @callback:  A function to call when the selected font changes.  * @data:      A pointer to arbitary data to be used in the call to @callback.  *  * Creates a new #GtkWidget that completely controls the selection of  * a font.  This widget is suitable for placement in a table in a  * plug-in dialog.  *  * Returns: A #GtkWidget that you can use in your UI.  */
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
name|FontSelect
modifier|*
name|font_sel
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|image
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
literal|"Font Selection"
argument_list|)
expr_stmt|;
name|font_sel
operator|=
name|g_new0
argument_list|(
name|FontSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|font_sel
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|font_sel
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|font_sel
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|font_sel
operator|->
name|font_name
operator|=
name|g_strdup
argument_list|(
name|font_name
argument_list|)
expr_stmt|;
name|font_sel
operator|->
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|g_signal_connect
argument_list|(
name|font_sel
operator|->
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_font_select_widget_clicked
argument_list|)
argument_list|,
name|font_sel
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|font_sel
operator|->
name|button
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_font_select_widget_destroy
argument_list|)
argument_list|,
name|font_sel
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|font_sel
operator|->
name|button
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
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|GIMP_STOCK_FONT
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|image
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
name|image
argument_list|)
expr_stmt|;
name|font_sel
operator|->
name|label
operator|=
name|gtk_label_new
argument_list|(
name|font_name
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|font_sel
operator|->
name|label
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|font_sel
operator|->
name|label
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|font_sel
operator|->
name|button
argument_list|)
argument_list|,
name|FONT_SELECT_DATA_KEY
argument_list|,
name|font_sel
argument_list|)
expr_stmt|;
return|return
name|font_sel
operator|->
name|button
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
name|FontSelect
modifier|*
name|font_sel
decl_stmt|;
name|font_sel
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FONT_SELECT_DATA_KEY
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|font_sel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|font_sel
operator|->
name|temp_font_callback
condition|)
block|{
name|gimp_font_select_destroy
argument_list|(
name|font_sel
operator|->
name|temp_font_callback
argument_list|)
expr_stmt|;
name|font_sel
operator|->
name|temp_font_callback
operator|=
name|NULL
expr_stmt|;
block|}
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
name|FontSelect
modifier|*
name|font_sel
decl_stmt|;
name|font_sel
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FONT_SELECT_DATA_KEY
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|font_sel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|font_sel
operator|->
name|temp_font_callback
condition|)
name|gimp_fonts_set_popup
argument_list|(
name|font_sel
operator|->
name|temp_font_callback
argument_list|,
name|font_name
argument_list|)
expr_stmt|;
else|else
name|gimp_font_select_widget_callback
argument_list|(
name|font_name
argument_list|,
name|FALSE
argument_list|,
name|font_sel
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_font_select_widget_callback (const gchar * name,gboolean closing,gpointer data)
name|gimp_font_select_widget_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gboolean
name|closing
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|FontSelect
modifier|*
name|font_sel
init|=
operator|(
name|FontSelect
operator|*
operator|)
name|data
decl_stmt|;
name|g_free
argument_list|(
name|font_sel
operator|->
name|font_name
argument_list|)
expr_stmt|;
name|font_sel
operator|->
name|font_name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|font_sel
operator|->
name|label
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|font_sel
operator|->
name|callback
condition|)
name|font_sel
operator|->
name|callback
argument_list|(
name|name
argument_list|,
name|closing
argument_list|,
name|font_sel
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|closing
condition|)
name|font_sel
operator|->
name|temp_font_callback
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_select_widget_clicked (GtkWidget * widget,FontSelect * font_sel)
name|gimp_font_select_widget_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|FontSelect
modifier|*
name|font_sel
parameter_list|)
block|{
if|if
condition|(
name|font_sel
operator|->
name|temp_font_callback
condition|)
block|{
comment|/*  calling gimp_fonts_set_popup() raises the dialog  */
name|gimp_fonts_set_popup
argument_list|(
name|font_sel
operator|->
name|temp_font_callback
argument_list|,
name|font_sel
operator|->
name|font_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|font_sel
operator|->
name|temp_font_callback
operator|=
name|gimp_font_select_new
argument_list|(
name|font_sel
operator|->
name|title
argument_list|,
name|font_sel
operator|->
name|font_name
argument_list|,
name|gimp_font_select_widget_callback
argument_list|,
name|font_sel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_select_widget_destroy (GtkWidget * widget,FontSelect * font_sel)
name|gimp_font_select_widget_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|FontSelect
modifier|*
name|font_sel
parameter_list|)
block|{
if|if
condition|(
name|font_sel
operator|->
name|temp_font_callback
condition|)
block|{
name|gimp_font_select_destroy
argument_list|(
name|font_sel
operator|->
name|temp_font_callback
argument_list|)
expr_stmt|;
name|font_sel
operator|->
name|temp_font_callback
operator|=
name|NULL
expr_stmt|;
block|}
name|g_free
argument_list|(
name|font_sel
operator|->
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|font_sel
operator|->
name|font_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|font_sel
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

