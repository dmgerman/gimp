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
file|"core/gimp.h"
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
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
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
file|"gimphelp-ids.h"
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
name|gimp_document_view_remove_clicked
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
name|gimp_document_view_refresh_extended_clicked
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

begin_function_decl
specifier|static
name|void
name|gimp_document_view_open_image
parameter_list|(
name|GimpDocumentView
modifier|*
name|view
parameter_list|,
name|GimpImagefile
modifier|*
name|imagefile
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
name|remove_button
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
DECL|function|gimp_document_view_new (GimpViewType view_type,GimpContainer * container,GimpContext * context,gint preview_size,gint preview_border_width,GimpFileOpenDialogFunc file_open_dialog_func,GimpMenuFactory * menu_factory)
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
name|preview_border_width
parameter_list|,
name|GimpFileOpenDialogFunc
name|file_open_dialog_func
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
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
name|gchar
modifier|*
name|str
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|file_open_dialog_func
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|preview_border_width
argument_list|,
name|TRUE
argument_list|,
comment|/* reorderable */
name|menu_factory
argument_list|,
literal|"<Documents>"
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|document_view
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|document_view
operator|->
name|file_open_dialog_func
operator|=
name|file_open_dialog_func
expr_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|document_view
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Open the selected entry\n"
literal|"%s  Raise window if already open\n"
literal|"%s  Open image dialog"
argument_list|)
argument_list|,
name|gimp_get_mod_name_shift
argument_list|()
argument_list|,
name|gimp_get_mod_name_control
argument_list|()
argument_list|)
expr_stmt|;
name|document_view
operator|->
name|open_button
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
name|GTK_STOCK_OPEN
argument_list|,
name|str
argument_list|,
name|GIMP_HELP_DOCUMENT_OPEN
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
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|document_view
operator|->
name|remove_button
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
name|GTK_STOCK_REMOVE
argument_list|,
name|_
argument_list|(
literal|"Remove selected entry"
argument_list|)
argument_list|,
name|GIMP_HELP_DOCUMENT_REMOVE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_document_view_remove_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Recreate preview\n"
literal|"%s  Reload all previews\n"
literal|"%s  Remove Dangling Entries"
argument_list|)
argument_list|,
name|gimp_get_mod_name_shift
argument_list|()
argument_list|,
name|gimp_get_mod_name_control
argument_list|()
argument_list|)
expr_stmt|;
name|document_view
operator|->
name|refresh_button
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
name|GTK_STOCK_REFRESH
argument_list|,
name|str
argument_list|,
name|GIMP_HELP_DOCUMENT_REFRESH
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_document_view_refresh_clicked
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_document_view_refresh_extended_clicked
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
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
name|remove_button
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
name|gimp_document_view_open_image
argument_list|(
name|view
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|view
operator|->
name|file_open_dialog_func
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|NULL
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
name|uri
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
name|uri
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
name|uri
operator|&&
operator|!
name|strcmp
argument_list|(
name|closure
operator|->
name|name
argument_list|,
name|uri
argument_list|)
condition|)
block|{
name|closure
operator|->
name|found
operator|=
name|TRUE
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
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
name|view
operator|->
name|file_open_dialog_func
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
name|gimp_container_foreach
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
operator|->
name|gimp
operator|->
name|displays
argument_list|,
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
name|gimp_document_view_open_image
argument_list|(
name|view
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|view
operator|->
name|file_open_dialog_func
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_remove_clicked (GtkWidget * widget,GimpDocumentView * view)
name|gimp_document_view_remove_clicked
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
name|gimp_imagefile_create_thumbnail
argument_list|(
name|imagefile
argument_list|,
name|editor
operator|->
name|view
operator|->
name|preview_size
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_delete_dangling_foreach (GimpImagefile * imagefile,GimpContainerView * container_view)
name|gimp_document_view_delete_dangling_foreach
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GimpContainerView
modifier|*
name|container_view
parameter_list|)
block|{
name|gimp_imagefile_update
argument_list|(
name|imagefile
argument_list|,
name|container_view
operator|->
name|preview_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
operator|->
name|state
operator|==
name|GIMP_IMAGEFILE_STATE_NOT_FOUND
condition|)
block|{
name|gimp_container_remove
argument_list|(
name|container_view
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
DECL|function|gimp_document_view_update_foreach (GimpImagefile * imagefile,GimpContainerView * container_view)
name|gimp_document_view_update_foreach
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GimpContainerView
modifier|*
name|container_view
parameter_list|)
block|{
name|gimp_imagefile_update
argument_list|(
name|imagefile
argument_list|,
name|container_view
operator|->
name|preview_size
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_refresh_extended_clicked (GtkWidget * widget,guint state,GimpDocumentView * view)
name|gimp_document_view_refresh_extended_clicked
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
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|gimp_container_foreach
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_document_view_delete_dangling_foreach
argument_list|,
name|editor
operator|->
name|view
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
name|gimp_container_foreach
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_document_view_update_foreach
argument_list|,
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
block|}
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
name|remove_sensitive
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
name|remove_sensitive
operator|=
name|TRUE
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|remove_button
argument_list|,
name|remove_sensitive
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

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_open_image (GimpDocumentView * view,GimpImagefile * imagefile)
name|gimp_document_view_open_image
parameter_list|(
name|GimpDocumentView
modifier|*
name|view
parameter_list|,
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gimp
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
operator|->
name|context
operator|->
name|gimp
expr_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|file_open_with_display
argument_list|(
name|gimp
argument_list|,
name|uri
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Opening '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

