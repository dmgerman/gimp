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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageeditor.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_image_editor_class_init
parameter_list|(
name|GimpImageEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_editor_init
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_editor_destroy
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
name|gimp_image_editor_real_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
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
DECL|function|gimp_image_editor_get_type (void)
name|gimp_image_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|editor_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|editor_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|editor_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpImageEditorClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_image_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpImageEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_image_editor_init
block|,       }
decl_stmt|;
name|editor_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_EDITOR
argument_list|,
literal|"GimpImageEditor"
argument_list|,
operator|&
name|editor_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|editor_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_editor_class_init (GimpImageEditorClass * klass)
name|gimp_image_editor_class_init
parameter_list|(
name|GimpImageEditorClass
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
name|GTK_OBJECT_CLASS
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
name|gimp_image_editor_destroy
expr_stmt|;
name|klass
operator|->
name|set_image
operator|=
name|gimp_image_editor_real_set_image
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_editor_init (GimpImageEditor * editor)
name|gimp_image_editor_init
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
block|{
name|editor
operator|->
name|gimage
operator|=
name|NULL
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_editor_destroy (GtkObject * object)
name|gimp_image_editor_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|gimage
condition|)
name|gimp_image_editor_set_image
argument_list|(
name|editor
argument_list|,
name|NULL
argument_list|)
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
DECL|function|gimp_image_editor_real_set_image (GimpImageEditor * editor,GimpImage * gimage)
name|gimp_image_editor_real_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|editor
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|gimage
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_image_editor_set_image (GimpImageEditor * editor,GimpImage * gimage)
name|gimp_image_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|gimage
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|==
name|editor
operator|->
name|gimage
condition|)
return|return;
name|GIMP_IMAGE_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
operator|->
name|set_image
argument_list|(
name|editor
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

