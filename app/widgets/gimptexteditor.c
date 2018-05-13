begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextEditor  * Copyright (C) 2002-2003, 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptext.h"
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
file|"gimptextbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimptexteditor.h"
end_include

begin_include
include|#
directive|include
file|"gimptextstyleeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c94b5310103
block|{
DECL|enumerator|TEXT_CHANGED
name|TEXT_CHANGED
block|,
DECL|enumerator|DIR_CHANGED
name|DIR_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_text_editor_finalize
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
name|gimp_text_editor_text_changed
parameter_list|(
name|GtkTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpTextEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_editor_font_toggled
parameter_list|(
name|GtkToggleButton
modifier|*
name|button
parameter_list|,
name|GimpTextEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTextEditor
argument_list|,
argument|gimp_text_editor
argument_list|,
argument|GIMP_TYPE_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_text_editor_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|text_editor_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_text_editor_class_init (GimpTextEditorClass * klass)
name|gimp_text_editor_class_init
parameter_list|(
name|GimpTextEditorClass
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_text_editor_finalize
expr_stmt|;
name|klass
operator|->
name|text_changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|dir_changed
operator|=
name|NULL
expr_stmt|;
name|text_editor_signals
index|[
name|TEXT_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"text-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpTextEditorClass
argument_list|,
name|text_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|text_editor_signals
index|[
name|DIR_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"dir-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpTextEditorClass
argument_list|,
name|dir_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_editor_init (GimpTextEditor * editor)
name|gimp_text_editor_init
parameter_list|(
name|GimpTextEditor
modifier|*
name|editor
parameter_list|)
block|{
name|editor
operator|->
name|view
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|file_dialog
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|ui_manager
operator|=
name|NULL
expr_stmt|;
switch|switch
condition|(
name|gtk_widget_get_default_direction
argument_list|()
condition|)
block|{
case|case
name|GTK_TEXT_DIR_NONE
case|:
case|case
name|GTK_TEXT_DIR_LTR
case|:
name|editor
operator|->
name|base_dir
operator|=
name|GIMP_TEXT_DIRECTION_LTR
expr_stmt|;
break|break;
case|case
name|GTK_TEXT_DIR_RTL
case|:
name|editor
operator|->
name|base_dir
operator|=
name|GIMP_TEXT_DIRECTION_RTL
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_editor_finalize (GObject * object)
name|gimp_text_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTextEditor
modifier|*
name|editor
init|=
name|GIMP_TEXT_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|editor
operator|->
name|font_name
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|editor
operator|->
name|ui_manager
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_text_editor_new (const gchar * title,GtkWindow * parent,Gimp * gimp,GimpMenuFactory * menu_factory,GimpText * text,GimpTextBuffer * text_buffer,gdouble xres,gdouble yres)
name|gimp_text_editor_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GtkWindow
modifier|*
name|parent
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|,
name|GimpTextBuffer
modifier|*
name|text_buffer
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
block|{
name|GimpTextEditor
modifier|*
name|editor
decl_stmt|;
name|GtkWidget
modifier|*
name|content_area
decl_stmt|;
name|GtkWidget
modifier|*
name|toolbar
decl_stmt|;
name|GtkWidget
modifier|*
name|style_editor
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|gboolean
name|use_header_bar
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parent
operator|==
name|NULL
operator|||
name|GTK_IS_WINDOW
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT
argument_list|(
name|text
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT_BUFFER
argument_list|(
name|text_buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|gtk_settings_get_default
argument_list|()
argument_list|,
literal|"gtk-dialogs-use-header"
argument_list|,
operator|&
name|use_header_bar
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT_EDITOR
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"role"
argument_list|,
literal|"gimp-text-editor"
argument_list|,
literal|"transient-for"
argument_list|,
name|parent
argument_list|,
literal|"help-func"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"help-id"
argument_list|,
name|GIMP_HELP_TEXT_EDITOR_DIALOG
argument_list|,
literal|"use-header-bar"
argument_list|,
name|use_header_bar
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|editor
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Close"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|text_buffer
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_editor_text_changed
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|editor
operator|->
name|ui_manager
operator|=
name|gimp_menu_factory_manager_new
argument_list|(
name|menu_factory
argument_list|,
literal|"<TextEditor>"
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|content_area
operator|=
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|toolbar
operator|=
name|gtk_ui_manager_get_widget
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|editor
operator|->
name|ui_manager
argument_list|)
argument_list|,
literal|"/text-editor-toolbar"
argument_list|)
expr_stmt|;
if|if
condition|(
name|toolbar
condition|)
block|{
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|content_area
argument_list|)
argument_list|,
name|toolbar
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
name|toolbar
argument_list|)
expr_stmt|;
block|}
name|style_editor
operator|=
name|gimp_text_style_editor_new
argument_list|(
name|gimp
argument_list|,
name|text
argument_list|,
name|text_buffer
argument_list|,
name|gimp
operator|->
name|fonts
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|content_area
argument_list|)
argument_list|,
name|style_editor
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
name|style_editor
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|content_area
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
name|editor
operator|->
name|view
operator|=
name|gtk_text_view_new_with_buffer
argument_list|(
name|GTK_TEXT_BUFFER
argument_list|(
name|text_buffer
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_view_set_wrap_mode
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GTK_WRAP_WORD_CHAR
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|editor
operator|->
name|base_dir
condition|)
block|{
case|case
name|GIMP_TEXT_DIRECTION_LTR
case|:
name|gtk_widget_set_direction
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_TEXT_DIR_LTR
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_DIRECTION_RTL
case|:
name|gtk_widget_set_direction
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_TEXT_DIR_RTL
argument_list|)
expr_stmt|;
break|break;
block|}
name|gtk_widget_set_size_request
argument_list|(
name|editor
operator|->
name|view
argument_list|,
literal|200
argument_list|,
literal|64
argument_list|)
expr_stmt|;
name|editor
operator|->
name|font_toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Use selected font"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|content_area
argument_list|)
argument_list|,
name|editor
operator|->
name|font_toggle
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
name|editor
operator|->
name|font_toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|font_toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_editor_font_toggled
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gimp_ui_manager_update
argument_list|(
name|editor
operator|->
name|ui_manager
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_editor_set_text (GimpTextEditor * editor,const gchar * text,gint len)
name|gimp_text_editor_set_text
parameter_list|(
name|GimpTextEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|len
parameter_list|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|text
operator|!=
name|NULL
operator|||
name|len
operator|==
literal|0
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
name|gtk_text_buffer_set_text
argument_list|(
name|buffer
argument_list|,
name|text
argument_list|,
name|len
argument_list|)
expr_stmt|;
else|else
name|gtk_text_buffer_set_text
argument_list|(
name|buffer
argument_list|,
literal|""
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_text_editor_get_text (GimpTextEditor * editor)
name|gimp_text_editor_get_text
parameter_list|(
name|GimpTextEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|gimp_text_buffer_get_text
argument_list|(
name|GIMP_TEXT_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_editor_set_direction (GimpTextEditor * editor,GimpTextDirection base_dir)
name|gimp_text_editor_set_direction
parameter_list|(
name|GimpTextEditor
modifier|*
name|editor
parameter_list|,
name|GimpTextDirection
name|base_dir
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|base_dir
operator|==
name|base_dir
condition|)
return|return;
name|editor
operator|->
name|base_dir
operator|=
name|base_dir
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|view
condition|)
block|{
switch|switch
condition|(
name|editor
operator|->
name|base_dir
condition|)
block|{
case|case
name|GIMP_TEXT_DIRECTION_LTR
case|:
name|gtk_widget_set_direction
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_TEXT_DIR_LTR
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_DIRECTION_RTL
case|:
name|gtk_widget_set_direction
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_TEXT_DIR_RTL
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|gimp_ui_manager_update
argument_list|(
name|editor
operator|->
name|ui_manager
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|editor
argument_list|,
name|text_editor_signals
index|[
name|DIR_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpTextDirection
DECL|function|gimp_text_editor_get_direction (GimpTextEditor * editor)
name|gimp_text_editor_get_direction
parameter_list|(
name|GimpTextEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GIMP_TEXT_DIRECTION_LTR
argument_list|)
expr_stmt|;
return|return
name|editor
operator|->
name|base_dir
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_editor_set_font_name (GimpTextEditor * editor,const gchar * font_name)
name|gimp_text_editor_set_font_name
parameter_list|(
name|GimpTextEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|font_name
condition|)
name|g_free
argument_list|(
name|editor
operator|->
name|font_name
argument_list|)
expr_stmt|;
name|editor
operator|->
name|font_name
operator|=
name|g_strdup
argument_list|(
name|font_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|editor
operator|->
name|font_toggle
argument_list|)
argument_list|)
condition|)
block|{
name|PangoFontDescription
modifier|*
name|font_desc
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|font_name
condition|)
name|font_desc
operator|=
name|pango_font_description_from_string
argument_list|(
name|font_name
argument_list|)
expr_stmt|;
name|gtk_widget_override_font
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|font_desc
argument_list|)
expr_stmt|;
if|if
condition|(
name|font_desc
condition|)
name|pango_font_description_free
argument_list|(
name|font_desc
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_text_editor_get_font_name (GimpTextEditor * editor)
name|gimp_text_editor_get_font_name
parameter_list|(
name|GimpTextEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|editor
operator|->
name|font_name
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_text_editor_text_changed (GtkTextBuffer * buffer,GimpTextEditor * editor)
name|gimp_text_editor_text_changed
parameter_list|(
name|GtkTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpTextEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_signal_emit
argument_list|(
name|editor
argument_list|,
name|text_editor_signals
index|[
name|TEXT_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_editor_font_toggled (GtkToggleButton * button,GimpTextEditor * editor)
name|gimp_text_editor_font_toggled
parameter_list|(
name|GtkToggleButton
modifier|*
name|button
parameter_list|,
name|GimpTextEditor
modifier|*
name|editor
parameter_list|)
block|{
name|PangoFontDescription
modifier|*
name|font_desc
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|button
argument_list|)
operator|&&
name|editor
operator|->
name|font_name
condition|)
name|font_desc
operator|=
name|pango_font_description_from_string
argument_list|(
name|editor
operator|->
name|font_name
argument_list|)
expr_stmt|;
name|gtk_widget_override_font
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|font_desc
argument_list|)
expr_stmt|;
if|if
condition|(
name|font_desc
condition|)
name|pango_font_description_free
argument_list|(
name|font_desc
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

