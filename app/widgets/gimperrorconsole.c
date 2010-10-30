begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimperrorconsole.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * partly based on errorconsole.c  * Copyright (C) 1998 Nick Fetchak<nuke@bayside.net>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimperrorconsole.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimptextbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_error_console_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_error_console_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_error_console_unmap
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_error_console_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpErrorConsole,gimp_error_console,GIMP_TYPE_EDITOR)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpErrorConsole
argument_list|,
argument|gimp_error_console
argument_list|,
argument|GIMP_TYPE_EDITOR
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_error_console_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_error_console_class_init
parameter_list|(
name|GimpErrorConsoleClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_error_console_constructor
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_error_console_dispose
expr_stmt|;
name|widget_class
operator|->
name|unmap
operator|=
name|gimp_error_console_unmap
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_console_init (GimpErrorConsole * console)
name|gimp_error_console_init
parameter_list|(
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|console
operator|->
name|text_buffer
operator|=
name|GTK_TEXT_BUFFER
argument_list|(
name|gimp_text_buffer_new
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_text_buffer_create_tag
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
literal|"title"
argument_list|,
literal|"scale"
argument_list|,
name|PANGO_SCALE_LARGE
argument_list|,
literal|"weight"
argument_list|,
name|PANGO_WEIGHT_BOLD
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_buffer_create_tag
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
literal|"message"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|scrolled_window
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|console
argument_list|)
argument_list|,
name|scrolled_window
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
name|scrolled_window
argument_list|)
expr_stmt|;
name|console
operator|->
name|text_view
operator|=
name|gtk_text_view_new_with_buffer
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|)
expr_stmt|;
name|gtk_text_view_set_editable
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|console
operator|->
name|text_view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_text_view_set_wrap_mode
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|console
operator|->
name|text_view
argument_list|)
argument_list|,
name|GTK_WRAP_WORD
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|console
operator|->
name|text_view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|console
operator|->
name|text_view
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|console
operator|->
name|text_view
argument_list|,
literal|"button-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_error_console_button_press
argument_list|)
argument_list|,
name|console
argument_list|)
expr_stmt|;
name|console
operator|->
name|file_dialog
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_error_console_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_error_console_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpErrorConsole
modifier|*
name|console
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|console
operator|=
name|GIMP_ERROR_CONSOLE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|console
operator|->
name|clear_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|console
argument_list|)
argument_list|,
literal|"error-console"
argument_list|,
literal|"error-console-clear"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|console
operator|->
name|save_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|console
argument_list|)
argument_list|,
literal|"error-console"
argument_list|,
literal|"error-console-save-all"
argument_list|,
literal|"error-console-save-selection"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_console_dispose (GObject * object)
name|gimp_error_console_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpErrorConsole
modifier|*
name|console
init|=
name|GIMP_ERROR_CONSOLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|console
operator|->
name|file_dialog
condition|)
name|gtk_widget_destroy
argument_list|(
name|console
operator|->
name|file_dialog
argument_list|)
expr_stmt|;
name|console
operator|->
name|gimp
operator|->
name|message_handler
operator|=
name|GIMP_MESSAGE_BOX
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_console_unmap (GtkWidget * widget)
name|gimp_error_console_unmap
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpErrorConsole
modifier|*
name|console
init|=
name|GIMP_ERROR_CONSOLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|console
operator|->
name|file_dialog
condition|)
name|gtk_widget_destroy
argument_list|(
name|console
operator|->
name|file_dialog
argument_list|)
expr_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|unmap
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_error_console_new (Gimp * gimp,GimpMenuFactory * menu_factory)
name|gimp_error_console_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GimpErrorConsole
modifier|*
name|console
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|console
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ERROR_CONSOLE
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<ErrorConsole>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/error-console-popup"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|console
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|console
operator|->
name|gimp
operator|->
name|message_handler
operator|=
name|GIMP_ERROR_CONSOLE
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|console
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_error_console_add (GimpErrorConsole * console,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gimp_error_console_add
parameter_list|(
name|GimpErrorConsole
modifier|*
name|console
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
name|GtkTextIter
name|end
decl_stmt|;
name|GtkTextMark
modifier|*
name|end_mark
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ERROR_CONSOLE
argument_list|(
name|console
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|domain
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|message
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_MESSAGE_SEVERITY
argument_list|,
name|severity
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_end_iter
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gtk_widget_render_icon
argument_list|(
name|console
operator|->
name|text_view
argument_list|,
name|gimp_get_message_stock_id
argument_list|(
name|severity
argument_list|)
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert_pixbuf
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|end
argument_list|,
name|pixbuf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|end
argument_list|,
literal|"  "
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s %s"
argument_list|,
name|domain
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|end
argument_list|,
name|str
argument_list|,
operator|-
literal|1
argument_list|,
literal|"title"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|end
argument_list|,
literal|"\n"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|end
argument_list|,
name|message
argument_list|,
operator|-
literal|1
argument_list|,
literal|"message"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|end
argument_list|,
literal|"\n\n"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|end_mark
operator|=
name|gtk_text_buffer_create_mark
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
name|NULL
argument_list|,
operator|&
name|end
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_text_view_scroll_to_mark
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|console
operator|->
name|text_view
argument_list|)
argument_list|,
name|end_mark
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_text_buffer_delete_mark
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
name|end_mark
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_error_console_button_press (GtkWidget * widget,GdkEventButton * bevent,GimpErrorConsole * console)
name|gimp_error_console_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
block|{
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|3
operator|&&
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
block|{
return|return
name|gimp_editor_popup_menu
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|console
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

