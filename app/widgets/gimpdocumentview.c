begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdocumentview.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"core/gimpedit.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"gui/file-open-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocumentview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_document_view_class_init
parameter_list|(
name|GimpDocumentViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_document_view_init
parameter_list|(
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_document_view_open_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_document_view_open_extended_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|state
parameter_list|,
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_document_view_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_document_view_refresh_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_document_view_select_item
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
name|gimp_document_view_activate_item
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
DECL|function|gimp_document_view_get_type (void)
name|gimp_document_view_get_type
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
name|GimpDocumentViewClass
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
name|gimp_document_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpDocumentView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_document_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_CONTAINER_EDITOR
argument_list|,
literal|"GimpDocumentView"
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
DECL|function|gimp_document_view_class_init (GimpDocumentViewClass * klass)
name|gimp_document_view_class_init
parameter_list|(
name|GimpDocumentViewClass
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
name|gimp_document_view_select_item
expr_stmt|;
name|editor_class
operator|->
name|activate_item
operator|=
name|gimp_document_view_activate_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_init (GimpDocumentView * view)
name|gimp_document_view_init
parameter_list|(
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|open_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|delete_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|refresh_button
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_document_view_new (GimpViewType view_type,GimpContainer * container,GimpContext * context,gint preview_size,gint min_items_x,gint min_items_y,const gchar * item_factory)
name|gimp_document_view_new
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
name|min_items_x
parameter_list|,
name|gint
name|min_items_y
parameter_list|,
specifier|const
name|gchar
modifier|*
name|item_factory
parameter_list|)
block|{
name|GimpDocumentView
modifier|*
name|document_view
decl_stmt|;
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|document_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DOCUMENT_VIEW
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
name|document_view
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
name|TRUE
argument_list|,
comment|/* reorderable */
name|min_items_x
argument_list|,
name|min_items_y
argument_list|,
name|item_factory
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|document_view
argument_list|)
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
name|document_view
argument_list|)
expr_stmt|;
name|document_view
operator|->
name|open_button
operator|=
name|gimp_container_view_add_button
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
name|_
argument_list|(
literal|"Open the selected entry\n"
literal|"<Shift> Raise window if already open\n"
literal|"<Ctrl> Open image dialog"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_document_view_open_clicked
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_document_view_open_extended_clicked
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|document_view
operator|->
name|delete_button
operator|=
name|gimp_container_view_add_button
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|_
argument_list|(
literal|"Remove selected entry"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_document_view_delete_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|document_view
operator|->
name|refresh_button
operator|=
name|gimp_container_view_add_button
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_STOCK_REFRESH
argument_list|,
name|_
argument_list|(
literal|"Refresh (check files for existence)"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_document_view_refresh_clicked
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
name|gimp_context_get_imagefile
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
name|document_view
operator|->
name|open_button
argument_list|)
argument_list|,
name|GIMP_TYPE_IMAGEFILE
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
name|document_view
operator|->
name|delete_button
argument_list|)
argument_list|,
name|GIMP_TYPE_IMAGEFILE
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|document_view
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_open_clicked (GtkWidget * widget,GimpDocumentView * view)
name|gimp_document_view_open_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_context_get_imagefile
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
name|imagefile
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
name|imagefile
argument_list|)
argument_list|)
condition|)
block|{
name|file_open_with_display
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|file_open_dialog_show
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_typedef
DECL|typedef|RaiseClosure
typedef|typedef
name|struct
name|_RaiseClosure
name|RaiseClosure
typedef|;
end_typedef

begin_struct
DECL|struct|_RaiseClosure
struct|struct
name|_RaiseClosure
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|found
name|gboolean
name|found
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_raise_display (gpointer data,gpointer user_data)
name|gimp_document_view_raise_display
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|RaiseClosure
modifier|*
name|closure
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GimpDisplay
operator|*
operator|)
name|data
expr_stmt|;
name|closure
operator|=
operator|(
name|RaiseClosure
operator|*
operator|)
name|user_data
expr_stmt|;
name|filename
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
operator|&&
operator|!
name|strcmp
argument_list|(
name|closure
operator|->
name|name
argument_list|,
name|filename
argument_list|)
condition|)
block|{
name|closure
operator|->
name|found
operator|=
name|TRUE
expr_stmt|;
name|gdk_window_raise
argument_list|(
name|gdisp
operator|->
name|shell
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_open_extended_clicked (GtkWidget * widget,guint state,GimpDocumentView * view)
name|gimp_document_view_open_extended_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|state
parameter_list|,
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_context_get_imagefile
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
name|imagefile
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
name|imagefile
argument_list|)
argument_list|)
condition|)
block|{
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|file_open_dialog_show
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
name|RaiseClosure
name|closure
decl_stmt|;
name|closure
operator|.
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|closure
operator|.
name|found
operator|=
name|FALSE
expr_stmt|;
name|gdisplays_foreach
argument_list|(
name|gimp_document_view_raise_display
argument_list|,
operator|&
name|closure
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|closure
operator|.
name|found
condition|)
block|{
name|file_open_with_display
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|closure
operator|.
name|name
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|file_open_dialog_show
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_delete_clicked (GtkWidget * widget,GimpDocumentView * view)
name|gimp_document_view_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_context_get_imagefile
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
name|imagefile
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
name|imagefile
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
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_refresh_clicked (GtkWidget * widget,GimpDocumentView * view)
name|gimp_document_view_refresh_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"refresh clicked\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_select_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_document_view_select_item
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
name|GimpDocumentView
modifier|*
name|view
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
name|view
operator|=
name|GIMP_DOCUMENT_VIEW
argument_list|(
name|editor
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
name|delete_sensitive
operator|=
name|TRUE
expr_stmt|;
block|}
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
DECL|function|gimp_document_view_activate_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_document_view_activate_item
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
name|GimpDocumentView
modifier|*
name|view
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
name|view
operator|=
name|GIMP_DOCUMENT_VIEW
argument_list|(
name|editor
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
name|gimp_document_view_open_clicked
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

