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
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_image_view_class_init
parameter_list|(
name|GimpImageViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_view_init
parameter_list|(
name|GimpImageView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_view_raise_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_view_new_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_view_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_view_select_item
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
name|gimp_image_view_activate_item
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
DECL|function|gimp_image_view_get_type (void)
name|gimp_image_view_get_type
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
name|GimpImageViewClass
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
name|gimp_image_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpImageView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_image_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_CONTAINER_EDITOR
argument_list|,
literal|"GimpImageView"
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
DECL|function|gimp_image_view_class_init (GimpImageViewClass * klass)
name|gimp_image_view_class_init
parameter_list|(
name|GimpImageViewClass
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
name|gimp_image_view_select_item
expr_stmt|;
name|editor_class
operator|->
name|activate_item
operator|=
name|gimp_image_view_activate_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_view_init (GimpImageView * view)
name|gimp_image_view_init
parameter_list|(
name|GimpImageView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|raise_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|new_button
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
DECL|function|gimp_image_view_new (GimpViewType view_type,GimpContainer * container,GimpContext * context,gint preview_size,gint preview_border_width,GimpMenuFactory * menu_factory)
name|gimp_image_view_new
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
name|GimpImageView
modifier|*
name|image_view
decl_stmt|;
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|image_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_IMAGE_VIEW
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
name|image_view
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
literal|"<Images>"
argument_list|,
literal|"/images-popup"
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|image_view
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
name|image_view
argument_list|)
expr_stmt|;
name|image_view
operator|->
name|raise_button
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
name|GTK_STOCK_GOTO_TOP
argument_list|,
name|_
argument_list|(
literal|"Raise this image's displays"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_view_raise_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|image_view
operator|->
name|new_button
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
name|GTK_STOCK_NEW
argument_list|,
name|_
argument_list|(
literal|"Create a new display for this image"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_view_new_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|image_view
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
literal|"Delete this image"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_view_delete_clicked
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
name|gimp_context_get_image
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
name|image_view
operator|->
name|raise_button
argument_list|)
argument_list|,
name|GIMP_TYPE_IMAGE
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
name|image_view
operator|->
name|new_button
argument_list|)
argument_list|,
name|GIMP_TYPE_IMAGE
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
name|image_view
operator|->
name|delete_button
argument_list|)
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|image_view
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_view_raise_clicked (GtkWidget * widget,GimpImageView * view)
name|gimp_image_view_raise_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageView
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|image
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
if|if
condition|(
name|image
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
name|image
argument_list|)
argument_list|)
condition|)
block|{
if|if
condition|(
name|view
operator|->
name|raise_displays_func
condition|)
name|view
operator|->
name|raise_displays_func
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_view_new_clicked (GtkWidget * widget,GimpImageView * view)
name|gimp_image_view_new_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageView
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|image
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
if|if
condition|(
name|image
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
name|image
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_create_display
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|image
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_view_delete_clicked (GtkWidget * widget,GimpImageView * view)
name|gimp_image_view_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageView
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|image
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
if|if
condition|(
name|image
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
name|image
argument_list|)
argument_list|)
condition|)
block|{
if|if
condition|(
name|image
operator|->
name|disp_count
operator|==
literal|0
condition|)
name|g_object_unref
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_view_select_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_image_view_select_item
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
name|GimpImageView
modifier|*
name|view
init|=
name|GIMP_IMAGE_VIEW
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|gboolean
name|raise_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|new_sensitive
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
name|raise_sensitive
operator|=
name|TRUE
expr_stmt|;
name|new_sensitive
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|GIMP_IMAGE
argument_list|(
name|viewable
argument_list|)
operator|->
name|disp_count
operator|==
literal|0
condition|)
name|delete_sensitive
operator|=
name|TRUE
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|raise_button
argument_list|,
name|raise_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|new_button
argument_list|,
name|new_sensitive
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
DECL|function|gimp_image_view_activate_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_image_view_activate_item
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
name|GimpImageView
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
name|GIMP_IMAGE_VIEW
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
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|raise_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

