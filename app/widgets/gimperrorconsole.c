begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimperrorconsole.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * partly based on errorconsole.c  * Copyright (C) 1998 Nick Fetchak<nuke@bayside.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|S_IRUSR
end_ifndef

begin_define
DECL|macro|S_IRUSR
define|#
directive|define
name|S_IRUSR
value|_S_IREAD
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_IWUSR
end_ifndef

begin_define
DECL|macro|S_IWUSR
define|#
directive|define
name|S_IWUSR
value|_S_IWRITE
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

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
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
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
name|void
name|gimp_error_console_class_init
parameter_list|(
name|GimpErrorConsoleClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_error_console_init
parameter_list|(
name|GimpErrorConsole
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_error_console_destroy
parameter_list|(
name|GtkObject
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

begin_function_decl
specifier|static
name|void
name|gimp_error_console_clear_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_error_console_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_error_console_save_ext_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_error_console_save_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_error_console_write_file
parameter_list|(
name|GtkTextBuffer
modifier|*
name|text_buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|selection_only
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpEditorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_error_console_get_type (void)
name|gimp_error_console_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpErrorConsoleClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_error_console_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpErrorConsole
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_error_console_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_EDITOR
argument_list|,
literal|"GimpErrorConsole"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_console_class_init (GimpErrorConsoleClass * klass)
name|gimp_error_console_class_init
parameter_list|(
name|GimpErrorConsoleClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_error_console_destroy
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
name|gchar
modifier|*
name|str
decl_stmt|;
name|console
operator|->
name|text_buffer
operator|=
name|gtk_text_buffer_new
argument_list|(
name|NULL
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
literal|"weight"
argument_list|,
name|PANGO_WEIGHT_BOLD
argument_list|,
literal|"scale"
argument_list|,
name|PANGO_SCALE_LARGE
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|console
argument_list|)
argument_list|,
name|scrolled_window
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
literal|"button_press_event"
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
name|clear_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|console
argument_list|)
argument_list|,
name|GTK_STOCK_CLEAR
argument_list|,
name|_
argument_list|(
literal|"Clear Errors"
argument_list|)
argument_list|,
name|GIMP_HELP_ERRORS_CLEAR
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_error_console_clear_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|console
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Save all Errors\n"
literal|"%s  Save Selection"
argument_list|)
argument_list|,
name|gimp_get_mod_name_shift
argument_list|()
argument_list|)
expr_stmt|;
name|console
operator|->
name|save_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|console
argument_list|)
argument_list|,
name|GTK_STOCK_SAVE_AS
argument_list|,
name|str
argument_list|,
name|GIMP_HELP_ERRORS_SAVE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_error_console_save_clicked
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_error_console_save_ext_clicked
argument_list|)
argument_list|,
name|console
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
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
name|void
DECL|function|gimp_error_console_destroy (GtkObject * object)
name|gimp_error_console_destroy
parameter_list|(
name|GtkObject
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
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
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
name|NULL
argument_list|)
expr_stmt|;
name|console
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|gimp_editor_create_menu
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|console
argument_list|)
argument_list|,
name|menu_factory
argument_list|,
literal|"<ErrorConsole>"
argument_list|,
literal|"/error-console-popup"
argument_list|,
name|console
argument_list|)
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
DECL|function|gimp_error_console_add (GimpErrorConsole * console,const gchar * stock_id,const gchar * domain,const gchar * message)
name|gimp_error_console_add
parameter_list|(
name|GimpErrorConsole
modifier|*
name|console
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
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
name|stock_id
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
if|if
condition|(
operator|!
name|domain
condition|)
name|domain
operator|=
name|_
argument_list|(
literal|"GIMP"
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
name|stock_id
argument_list|,
name|GTK_ICON_SIZE_MENU
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
name|_
argument_list|(
literal|"%s Message"
argument_list|)
argument_list|,
name|domain
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
condition|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|console
argument_list|)
decl_stmt|;
name|gimp_ui_manager_update
argument_list|(
name|editor
operator|->
name|ui_manager
argument_list|,
name|editor
operator|->
name|popup_data
argument_list|)
expr_stmt|;
name|gimp_ui_manager_ui_popup
argument_list|(
name|editor
operator|->
name|ui_manager
argument_list|,
name|editor
operator|->
name|ui_path
argument_list|,
name|editor
operator|->
name|popup_data
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_console_clear_clicked (GtkWidget * button,GimpErrorConsole * console)
name|gimp_error_console_clear_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
block|{
name|GtkTextIter
name|start_iter
decl_stmt|;
name|GtkTextIter
name|end_iter
decl_stmt|;
name|gtk_text_buffer_get_start_iter
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|start_iter
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_end_iter
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|end_iter
argument_list|)
expr_stmt|;
name|gtk_text_buffer_delete
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|start_iter
argument_list|,
operator|&
name|end_iter
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_console_save_clicked (GtkWidget * button,GimpErrorConsole * console)
name|gimp_error_console_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
block|{
name|gimp_error_console_save_ext_clicked
argument_list|(
name|button
argument_list|,
literal|0
argument_list|,
name|console
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_console_save_ext_clicked (GtkWidget * button,GdkModifierType state,GimpErrorConsole * console)
name|gimp_error_console_save_ext_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
block|{
name|GtkFileChooser
modifier|*
name|chooser
decl_stmt|;
if|if
condition|(
operator|!
name|gtk_text_buffer_get_selection_bounds
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|&&
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot save. Nothing is selected."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|console
operator|->
name|file_dialog
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|console
operator|->
name|file_dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|console
operator|->
name|file_dialog
operator|=
name|gtk_file_chooser_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Save Error Log to File"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_SAVE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|console
operator|->
name|save_selection
operator|=
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|console
operator|->
name|file_dialog
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|console
operator|->
name|file_dialog
argument_list|)
expr_stmt|;
name|chooser
operator|=
name|GTK_FILE_CHOOSER
argument_list|(
name|console
operator|->
name|file_dialog
argument_list|)
expr_stmt|;
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|gtk_window_get_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|console
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
literal|"gimp-save-errors"
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|chooser
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_error_console_save_response
argument_list|)
argument_list|,
name|console
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|chooser
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_connect
argument_list|(
name|GTK_WIDGET
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_ERRORS_DIALOG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|chooser
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_console_save_response (GtkWidget * dialog,gint response_id,GimpErrorConsole * console)
name|gimp_error_console_save_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|gtk_file_chooser_get_filename
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_error_console_write_file
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
name|filename
argument_list|,
name|console
operator|->
name|save_selection
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Error writing file '%s':\n%s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_error_console_write_file (GtkTextBuffer * text_buffer,const gchar * path,gboolean selection_only)
name|gimp_error_console_write_file
parameter_list|(
name|GtkTextBuffer
modifier|*
name|text_buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|selection_only
parameter_list|)
block|{
name|GtkTextIter
name|start_iter
decl_stmt|;
name|GtkTextIter
name|end_iter
decl_stmt|;
name|gint
name|fd
decl_stmt|;
name|gint
name|text_length
decl_stmt|;
name|gint
name|bytes_written
decl_stmt|;
name|gchar
modifier|*
name|text_contents
decl_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|path
argument_list|,
name|O_WRONLY
operator||
name|O_CREAT
operator||
name|O_APPEND
argument_list|,
name|S_IRUSR
operator||
name|S_IWUSR
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|selection_only
condition|)
name|gtk_text_buffer_get_selection_bounds
argument_list|(
name|text_buffer
argument_list|,
operator|&
name|start_iter
argument_list|,
operator|&
name|end_iter
argument_list|)
expr_stmt|;
else|else
name|gtk_text_buffer_get_bounds
argument_list|(
name|text_buffer
argument_list|,
operator|&
name|start_iter
argument_list|,
operator|&
name|end_iter
argument_list|)
expr_stmt|;
name|text_contents
operator|=
name|gtk_text_buffer_get_text
argument_list|(
name|text_buffer
argument_list|,
operator|&
name|start_iter
argument_list|,
operator|&
name|end_iter
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|text_length
operator|=
name|strlen
argument_list|(
name|text_contents
argument_list|)
expr_stmt|;
if|if
condition|(
name|text_contents
operator|&&
operator|(
name|text_length
operator|>
literal|0
operator|)
condition|)
block|{
name|bytes_written
operator|=
name|write
argument_list|(
name|fd
argument_list|,
name|text_contents
argument_list|,
name|text_length
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text_contents
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
name|bytes_written
operator|!=
name|text_length
condition|)
return|return
name|FALSE
return|;
else|else
return|return
name|TRUE
return|;
block|}
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

