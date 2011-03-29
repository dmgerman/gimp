begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextProxy  * Copyright (C) 2009-2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimptextproxy.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon295987770103
block|{
DECL|enumerator|CHANGE_SIZE
name|CHANGE_SIZE
block|,
DECL|enumerator|CHANGE_BASELINE
name|CHANGE_BASELINE
block|,
DECL|enumerator|CHANGE_KERNING
name|CHANGE_KERNING
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_text_proxy_move_cursor
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|,
name|GtkMovementStep
name|step
parameter_list|,
name|gint
name|count
parameter_list|,
name|gboolean
name|extend_selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_proxy_insert_at_cursor
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|,
specifier|const
name|gchar
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_proxy_delete_from_cursor
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|,
name|GtkDeleteType
name|type
parameter_list|,
name|gint
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_proxy_backspace
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_proxy_cut_clipboard
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_proxy_copy_clipboard
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_proxy_paste_clipboard
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_proxy_toggle_overwrite
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTextProxy
argument_list|,
argument|gimp_text_proxy
argument_list|,
argument|GTK_TYPE_TEXT_VIEW
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|guint
name|proxy_signals
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
DECL|function|gimp_text_proxy_class_init (GimpTextProxyClass * klass)
name|gimp_text_proxy_class_init
parameter_list|(
name|GimpTextProxyClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkTextViewClass
modifier|*
name|tv_class
init|=
name|GTK_TEXT_VIEW_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkBindingSet
modifier|*
name|binding_set
decl_stmt|;
name|tv_class
operator|->
name|move_cursor
operator|=
name|gimp_text_proxy_move_cursor
expr_stmt|;
name|tv_class
operator|->
name|insert_at_cursor
operator|=
name|gimp_text_proxy_insert_at_cursor
expr_stmt|;
name|tv_class
operator|->
name|delete_from_cursor
operator|=
name|gimp_text_proxy_delete_from_cursor
expr_stmt|;
name|tv_class
operator|->
name|backspace
operator|=
name|gimp_text_proxy_backspace
expr_stmt|;
name|tv_class
operator|->
name|cut_clipboard
operator|=
name|gimp_text_proxy_cut_clipboard
expr_stmt|;
name|tv_class
operator|->
name|copy_clipboard
operator|=
name|gimp_text_proxy_copy_clipboard
expr_stmt|;
name|tv_class
operator|->
name|paste_clipboard
operator|=
name|gimp_text_proxy_paste_clipboard
expr_stmt|;
name|tv_class
operator|->
name|toggle_overwrite
operator|=
name|gimp_text_proxy_toggle_overwrite
expr_stmt|;
name|proxy_signals
index|[
name|CHANGE_SIZE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"change-size"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
operator||
name|G_SIGNAL_ACTION
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpTextProxyClass
argument_list|,
name|change_size
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|proxy_signals
index|[
name|CHANGE_BASELINE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"change-baseline"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
operator||
name|G_SIGNAL_ACTION
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpTextProxyClass
argument_list|,
name|change_baseline
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|proxy_signals
index|[
name|CHANGE_KERNING
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"change-kerning"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
operator||
name|G_SIGNAL_ACTION
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpTextProxyClass
argument_list|,
name|change_kerning
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|binding_set
operator|=
name|gtk_binding_set_by_class
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_plus
argument_list|,
name|GDK_MOD1_MASK
argument_list|,
literal|"change-size"
argument_list|,
literal|1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_minus
argument_list|,
name|GDK_MOD1_MASK
argument_list|,
literal|"change-size"
argument_list|,
literal|1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_Up
argument_list|,
name|GDK_MOD1_MASK
argument_list|,
literal|"change-baseline"
argument_list|,
literal|1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_Down
argument_list|,
name|GDK_MOD1_MASK
argument_list|,
literal|"change-baseline"
argument_list|,
literal|1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_Left
argument_list|,
name|GDK_MOD1_MASK
argument_list|,
literal|"change-kerning"
argument_list|,
literal|1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_Right
argument_list|,
name|GDK_MOD1_MASK
argument_list|,
literal|"change-kerning"
argument_list|,
literal|1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_proxy_init (GimpTextProxy * text_proxy)
name|gimp_text_proxy_init
parameter_list|(
name|GimpTextProxy
modifier|*
name|text_proxy
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_proxy_move_cursor (GtkTextView * text_view,GtkMovementStep step,gint count,gboolean extend_selection)
name|gimp_text_proxy_move_cursor
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|,
name|GtkMovementStep
name|step
parameter_list|,
name|gint
name|count
parameter_list|,
name|gboolean
name|extend_selection
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_proxy_insert_at_cursor (GtkTextView * text_view,const gchar * str)
name|gimp_text_proxy_insert_at_cursor
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|,
specifier|const
name|gchar
modifier|*
name|str
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_proxy_delete_from_cursor (GtkTextView * text_view,GtkDeleteType type,gint count)
name|gimp_text_proxy_delete_from_cursor
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|,
name|GtkDeleteType
name|type
parameter_list|,
name|gint
name|count
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_proxy_backspace (GtkTextView * text_view)
name|gimp_text_proxy_backspace
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_proxy_cut_clipboard (GtkTextView * text_view)
name|gimp_text_proxy_cut_clipboard
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_proxy_copy_clipboard (GtkTextView * text_view)
name|gimp_text_proxy_copy_clipboard
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_proxy_paste_clipboard (GtkTextView * text_view)
name|gimp_text_proxy_paste_clipboard
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_proxy_toggle_overwrite (GtkTextView * text_view)
name|gimp_text_proxy_toggle_overwrite
parameter_list|(
name|GtkTextView
modifier|*
name|text_view
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_text_proxy_new (void)
name|gimp_text_proxy_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
init|=
name|gtk_text_buffer_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|proxy
decl_stmt|;
name|proxy
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT_PROXY
argument_list|,
literal|"buffer"
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|proxy
return|;
block|}
end_function

end_unit

