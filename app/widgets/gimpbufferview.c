begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbufferview.c  * Copyright (C) 2001-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|FIXME #include "display/display-types.h"
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"display/display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-edit.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpbufferview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_buffer_view_class_init
parameter_list|(
name|GimpBufferViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_view_init
parameter_list|(
name|GimpBufferView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_view_paste
parameter_list|(
name|GimpBufferView
modifier|*
name|view
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_view_paste_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBufferView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_view_paste_into_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBufferView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_view_paste_as_new_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBufferView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_view_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBufferView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_view_select_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_view_activate_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpContainerEditorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_buffer_view_get_type (void)
name|gimp_buffer_view_get_type
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
name|GimpBufferViewClass
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
name|gimp_buffer_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpBufferView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_buffer_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_CONTAINER_EDITOR
argument_list|,
literal|"GimpBufferView"
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
DECL|function|gimp_buffer_view_class_init (GimpBufferViewClass * klass)
name|gimp_buffer_view_class_init
parameter_list|(
name|GimpBufferViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpContainerEditorClass
modifier|*
name|editor_class
decl_stmt|;
name|editor_class
operator|=
name|GIMP_CONTAINER_EDITOR_CLASS
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
name|editor_class
operator|->
name|select_item
operator|=
name|gimp_buffer_view_select_item
expr_stmt|;
name|editor_class
operator|->
name|activate_item
operator|=
name|gimp_buffer_view_activate_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_view_init (GimpBufferView * view)
name|gimp_buffer_view_init
parameter_list|(
name|GimpBufferView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|paste_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|paste_into_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|paste_as_new_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|delete_button
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_buffer_view_new (GimpViewType view_type,GimpContainer * container,GimpContext * context,gint preview_size,gint preview_border_width,GimpMenuFactory * menu_factory)
name|gimp_buffer_view_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|preview_size
parameter_list|,
name|gint
name|preview_border_width
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GimpBufferView
modifier|*
name|buffer_view
decl_stmt|;
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|buffer_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BUFFER_VIEW
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_container_editor_construct
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|buffer_view
argument_list|)
argument_list|,
name|view_type
argument_list|,
name|container
argument_list|,
name|context
argument_list|,
name|preview_size
argument_list|,
name|preview_border_width
argument_list|,
name|TRUE
argument_list|,
comment|/* reorderable */
name|menu_factory
argument_list|,
literal|"<Buffers>"
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|buffer_view
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|buffer_view
argument_list|)
expr_stmt|;
name|buffer_view
operator|->
name|paste_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GTK_STOCK_PASTE
argument_list|,
name|_
argument_list|(
literal|"Paste"
argument_list|)
argument_list|,
name|GIMP_HELP_BUFFER_PASTE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_buffer_view_paste_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|buffer_view
operator|->
name|paste_into_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_STOCK_PASTE_INTO
argument_list|,
name|_
argument_list|(
literal|"Paste Into"
argument_list|)
argument_list|,
name|GIMP_HELP_BUFFER_PASTE_INTO
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_buffer_view_paste_into_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|buffer_view
operator|->
name|paste_as_new_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_STOCK_PASTE_AS_NEW
argument_list|,
name|_
argument_list|(
literal|"Paste as New"
argument_list|)
argument_list|,
name|GIMP_HELP_BUFFER_PASTE_AS_NEW
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_buffer_view_paste_as_new_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|buffer_view
operator|->
name|delete_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|_
argument_list|(
literal|"Delete"
argument_list|)
argument_list|,
name|GIMP_HELP_BUFFER_DELETE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_buffer_view_delete_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
comment|/*  set button sensitivity  */
if|if
condition|(
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
operator|->
name|select_item
condition|)
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
operator|->
name|select_item
argument_list|(
name|editor
argument_list|,
operator|(
name|GimpViewable
operator|*
operator|)
name|gimp_context_get_buffer
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_BUTTON
argument_list|(
name|buffer_view
operator|->
name|paste_button
argument_list|)
argument_list|,
name|GIMP_TYPE_BUFFER
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_BUTTON
argument_list|(
name|buffer_view
operator|->
name|paste_into_button
argument_list|)
argument_list|,
name|GIMP_TYPE_BUFFER
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_BUTTON
argument_list|(
name|buffer_view
operator|->
name|paste_as_new_button
argument_list|)
argument_list|,
name|GIMP_TYPE_BUFFER
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_BUTTON
argument_list|(
name|buffer_view
operator|->
name|delete_button
argument_list|)
argument_list|,
name|GIMP_TYPE_BUFFER
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|buffer_view
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_view_paste (GimpBufferView * view,gboolean paste_into)
name|gimp_buffer_view_paste
parameter_list|(
name|GimpBufferView
modifier|*
name|view
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
decl_stmt|;
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
if|if
condition|(
name|buffer
operator|&&
name|gimp_container_have
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
condition|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
init|=
name|gimp_context_get_display
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
init|=
name|NULL
decl_stmt|;
name|gint
name|x
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|y
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|width
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|height
init|=
operator|-
literal|1
decl_stmt|;
if|if
condition|(
name|gdisp
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
decl_stmt|;
name|gimp_display_shell_untransform_viewport
argument_list|(
name|shell
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
block|}
else|else
block|{
name|gimage
operator|=
name|gimp_context_get_image
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimage
condition|)
block|{
name|gimp_edit_paste
argument_list|(
name|gimage
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|buffer
argument_list|,
name|paste_into
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_view_paste_clicked (GtkWidget * widget,GimpBufferView * view)
name|gimp_buffer_view_paste_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBufferView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_buffer_view_paste
argument_list|(
name|view
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_view_paste_into_clicked (GtkWidget * widget,GimpBufferView * view)
name|gimp_buffer_view_paste_into_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBufferView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_buffer_view_paste
argument_list|(
name|view
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_view_paste_as_new_clicked (GtkWidget * widget,GimpBufferView * view)
name|gimp_buffer_view_paste_as_new_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBufferView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
decl_stmt|;
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
if|if
condition|(
name|buffer
operator|&&
name|gimp_container_have
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
init|=
name|gimp_context_get_image
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimage
condition|)
name|gimp_edit_paste_as_new
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|gimage
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_view_delete_clicked (GtkWidget * widget,GimpBufferView * view)
name|gimp_buffer_view_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBufferView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
decl_stmt|;
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
if|if
condition|(
name|buffer
operator|&&
name|gimp_container_have
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_container_remove
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_view_select_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_buffer_view_select_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpBufferView
modifier|*
name|view
init|=
name|GIMP_BUFFER_VIEW
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|gboolean
name|paste_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|paste_into_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|paste_as_new_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|delete_sensitive
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
condition|)
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
argument_list|(
name|editor
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
operator|&&
name|gimp_container_have
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
name|paste_sensitive
operator|=
name|TRUE
expr_stmt|;
name|paste_into_sensitive
operator|=
name|TRUE
expr_stmt|;
name|paste_as_new_sensitive
operator|=
name|TRUE
expr_stmt|;
name|delete_sensitive
operator|=
name|TRUE
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|paste_button
argument_list|,
name|paste_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|paste_into_button
argument_list|,
name|paste_into_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|paste_as_new_button
argument_list|,
name|paste_as_new_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|delete_button
argument_list|,
name|delete_sensitive
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_view_activate_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_buffer_view_activate_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpBufferView
modifier|*
name|view
init|=
name|GIMP_BUFFER_VIEW
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|activate_item
condition|)
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|activate_item
argument_list|(
name|editor
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
operator|&&
name|gimp_container_have
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_buffer_view_paste_clicked
argument_list|(
name|NULL
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

