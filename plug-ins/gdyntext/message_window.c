begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999,2000 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"message_window.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|message_window_class_init
parameter_list|(
name|MessageWindowClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|message_window_init
parameter_list|(
name|MessageWindow
modifier|*
name|mw
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|message_window_parent_class
specifier|static
name|GtkWindowClass
modifier|*
name|message_window_parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|guint
DECL|function|message_window_get_type (void)
name|message_window_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
name|mw_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|mw_type
condition|)
block|{
name|GtkTypeInfo
name|mw_info
init|=
block|{
literal|"MessageWindow"
block|,
sizeof|sizeof
argument_list|(
name|MessageWindow
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|MessageWindowClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|message_window_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|message_window_init
block|,
operator|(
name|GtkArgSetFunc
operator|)
name|NULL
block|,
operator|(
name|GtkArgGetFunc
operator|)
name|NULL
block|,
ifdef|#
directive|ifdef
name|GTK_HAVE_FEATURES_1_1_12
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,
endif|#
directive|endif
block|}
decl_stmt|;
name|mw_type
operator|=
name|gtk_type_unique
argument_list|(
name|gtk_window_get_type
argument_list|()
argument_list|,
operator|&
name|mw_info
argument_list|)
expr_stmt|;
block|}
return|return
name|mw_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|message_window_class_init (MessageWindowClass * klass)
name|message_window_class_init
parameter_list|(
name|MessageWindowClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|message_window_parent_class
operator|=
name|gtk_type_class
argument_list|(
name|gtk_window_get_type
argument_list|()
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|message_window_init (MessageWindow * mw)
name|message_window_init
parameter_list|(
name|MessageWindow
modifier|*
name|mw
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox1
decl_stmt|;
name|GtkWidget
modifier|*
name|hbbox1
decl_stmt|;
name|GtkWidget
modifier|*
name|vscrollbar
decl_stmt|;
name|GtkWidget
modifier|*
name|hseparator
decl_stmt|;
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|mw
operator|->
name|contains_messages
operator|=
name|FALSE
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|mw
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|hbox1
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox1
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
name|hbox1
argument_list|)
expr_stmt|;
name|mw
operator|->
name|text
operator|=
name|gtk_text_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox1
argument_list|)
argument_list|,
name|mw
operator|->
name|text
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|mw
operator|->
name|text
argument_list|)
expr_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|mw
operator|->
name|text
argument_list|)
expr_stmt|;
name|gtk_style_unref
argument_list|(
name|style
argument_list|)
expr_stmt|;
name|style
operator|->
name|base
index|[
name|GTK_STATE_NORMAL
index|]
operator|=
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
expr_stmt|;
name|gtk_style_ref
argument_list|(
name|style
argument_list|)
expr_stmt|;
name|gtk_widget_set_style
argument_list|(
name|mw
operator|->
name|text
argument_list|,
name|style
argument_list|)
expr_stmt|;
name|vscrollbar
operator|=
name|gtk_vscrollbar_new
argument_list|(
name|GTK_TEXT
argument_list|(
name|mw
operator|->
name|text
argument_list|)
operator|->
name|vadj
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox1
argument_list|)
argument_list|,
name|vscrollbar
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vscrollbar
argument_list|)
expr_stmt|;
name|hseparator
operator|=
name|gtk_hseparator_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hseparator
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hseparator
argument_list|)
expr_stmt|;
name|hbbox1
operator|=
name|gtk_hbutton_box_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbbox1
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_button_box_set_layout
argument_list|(
name|GTK_BUTTON_BOX
argument_list|(
name|hbbox1
argument_list|)
argument_list|,
name|GTK_BUTTONBOX_END
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbbox1
argument_list|)
expr_stmt|;
name|mw
operator|->
name|dismiss_button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Dismiss"
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|mw
operator|->
name|dismiss_button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbbox1
argument_list|)
argument_list|,
name|mw
operator|->
name|dismiss_button
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_default
argument_list|(
name|mw
operator|->
name|dismiss_button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|mw
operator|->
name|dismiss_button
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|message_window_new (const gchar * title)
name|message_window_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
block|{
name|MessageWindow
modifier|*
name|mw
decl_stmt|;
name|mw
operator|=
name|gtk_type_new
argument_list|(
name|message_window_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|mw
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|gimp_dialog_set_icon
argument_list|(
name|GTK_WINDOW
argument_list|(
name|mw
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|mw
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|mw
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|mw
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|message_window_append (MessageWindow * mw,const gchar * msg)
name|message_window_append
parameter_list|(
name|MessageWindow
modifier|*
name|mw
parameter_list|,
specifier|const
name|gchar
modifier|*
name|msg
parameter_list|)
block|{
name|gtk_widget_realize
argument_list|(
name|mw
operator|->
name|text
argument_list|)
expr_stmt|;
name|gtk_text_freeze
argument_list|(
name|GTK_TEXT
argument_list|(
name|mw
operator|->
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_insert
argument_list|(
name|GTK_TEXT
argument_list|(
name|mw
operator|->
name|text
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"* "
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_text_insert
argument_list|(
name|GTK_TEXT
argument_list|(
name|mw
operator|->
name|text
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|msg
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_text_thaw
argument_list|(
name|GTK_TEXT
argument_list|(
name|mw
operator|->
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|mw
operator|->
name|contains_messages
operator|=
name|TRUE
expr_stmt|;
name|g_print
argument_list|(
literal|"* %s"
argument_list|,
name|msg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|message_window_clear (MessageWindow * mw)
name|message_window_clear
parameter_list|(
name|MessageWindow
modifier|*
name|mw
parameter_list|)
block|{
name|gtk_widget_realize
argument_list|(
name|mw
operator|->
name|text
argument_list|)
expr_stmt|;
name|gtk_text_freeze
argument_list|(
name|GTK_TEXT
argument_list|(
name|mw
operator|->
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_editable_delete_text
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|mw
operator|->
name|text
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_text_thaw
argument_list|(
name|GTK_TEXT
argument_list|(
name|mw
operator|->
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|mw
operator|->
name|contains_messages
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

