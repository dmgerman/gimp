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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpbufferview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerlistview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimplistitem.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"buffers-commands.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|buffers_menu_set_sensitivity
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functionss */
end_comment

begin_function
name|void
DECL|function|buffers_paste_buffer_cmd_callback (GtkWidget * widget,gpointer data)
name|buffers_paste_buffer_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpBufferView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
operator|(
name|GimpBufferView
operator|*
operator|)
name|gimp_widget_get_callback_context
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|view
condition|)
return|return;
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|paste_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|buffers_paste_buffer_into_cmd_callback (GtkWidget * widget,gpointer data)
name|buffers_paste_buffer_into_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpBufferView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
operator|(
name|GimpBufferView
operator|*
operator|)
name|gimp_widget_get_callback_context
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|view
condition|)
return|return;
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|paste_into_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|buffers_paste_buffer_as_new_cmd_callback (GtkWidget * widget,gpointer data)
name|buffers_paste_buffer_as_new_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpBufferView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
operator|(
name|GimpBufferView
operator|*
operator|)
name|gimp_widget_get_callback_context
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|view
condition|)
return|return;
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|paste_as_new_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|buffers_delete_buffer_cmd_callback (GtkWidget * widget,gpointer data)
name|buffers_delete_buffer_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpBufferView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
operator|(
name|GimpBufferView
operator|*
operator|)
name|gimp_widget_get_callback_context
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|view
condition|)
return|return;
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|delete_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|buffers_show_context_menu (GimpContainerEditor * editor)
name|buffers_show_context_menu
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|buffers_menu_set_sensitivity
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|item_factory
operator|=
name|gtk_item_factory_from_path
argument_list|(
literal|"<Buffers>"
argument_list|)
expr_stmt|;
name|gimp_item_factory_popup_with_data
argument_list|(
name|item_factory
argument_list|,
name|editor
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
DECL|function|buffers_menu_set_sensitivity (GimpContainerEditor * editor)
name|buffers_menu_set_sensitivity
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|buffer
operator|=
name|gimp_context_get_buffer
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
expr_stmt|;
DECL|macro|SET_SENSITIVE (menu,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|menu
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_menu_item_set_sensitive ("<Buffers>/" menu, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"Paste Buffer"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"Paste Buffer Into"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"Paste Buffer as New"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"Delete Buffer"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

