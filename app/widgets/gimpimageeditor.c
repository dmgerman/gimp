begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
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
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_image_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_editor_dispose
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
name|gimp_image_editor_real_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_editor_image_flush
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|invalidate_preview
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpImageEditor,gimp_image_editor,GIMP_TYPE_EDITOR,G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,gimp_image_editor_docked_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpImageEditor
argument_list|,
argument|gimp_image_editor
argument_list|,
argument|GIMP_TYPE_EDITOR
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_image_editor_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_image_editor_class_init
parameter_list|(
name|GimpImageEditorClass
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
name|dispose
operator|=
name|gimp_image_editor_dispose
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
name|image
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
DECL|function|gimp_image_editor_docked_iface_init (GimpDockedInterface * iface)
name|gimp_image_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|set_context
operator|=
name|gimp_image_editor_set_context
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_editor_set_context (GimpDocked * docked,GimpContext * context)
name|gimp_image_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|editor
init|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|context
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|gimp_image_editor_set_image
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
block|}
name|editor
operator|->
name|context
operator|=
name|context
expr_stmt|;
if|if
condition|(
name|context
condition|)
block|{
name|g_object_ref
argument_list|(
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|context
argument_list|,
literal|"image-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_editor_set_image
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
name|gimp_image_editor_set_image
argument_list|(
name|editor
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_editor_dispose (GObject * object)
name|gimp_image_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|editor
init|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|image
condition|)
name|gimp_image_editor_set_image
argument_list|(
name|editor
argument_list|,
name|NULL
argument_list|)
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
DECL|function|gimp_image_editor_real_set_image (GimpImageEditor * editor,GimpImage * image)
name|gimp_image_editor_real_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|image
condition|)
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|image
argument_list|,
name|gimp_image_editor_image_flush
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|image
operator|=
name|image
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|image
condition|)
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|image
argument_list|,
literal|"flush"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_editor_image_flush
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|image
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
DECL|function|gimp_image_editor_set_image (GimpImageEditor * editor,GimpImage * image)
name|gimp_image_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|image
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
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|!=
name|editor
operator|->
name|image
condition|)
block|{
name|GIMP_IMAGE_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
operator|->
name|set_image
argument_list|(
name|editor
argument_list|,
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
condition|)
name|gimp_ui_manager_update
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|,
name|gimp_editor_get_popup_data
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_editor_get_image (GimpImageEditor * editor)
name|gimp_image_editor_get_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE_EDITOR
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
name|image
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_image_editor_image_flush (GimpImage * image,gboolean invalidate_preview,GimpImageEditor * editor)
name|gimp_image_editor_image_flush
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|invalidate_preview
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
condition|)
name|gimp_ui_manager_update
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|,
name|gimp_editor_get_popup_data
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

