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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemundo.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_item_undo_class_init
parameter_list|(
name|GimpItemUndoClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_undo_init
parameter_list|(
name|GimpItemUndo
modifier|*
name|undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpUndoClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_item_undo_get_type (void)
name|gimp_item_undo_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|undo_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|undo_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|undo_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpItemUndoClass
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
name|gimp_item_undo_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpItemUndo
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_item_undo_init
block|,       }
decl_stmt|;
name|undo_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_UNDO
argument_list|,
literal|"GimpItemUndo"
argument_list|,
operator|&
name|undo_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|undo_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_undo_class_init (GimpItemUndoClass * klass)
name|gimp_item_undo_class_init
parameter_list|(
name|GimpItemUndoClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpUndoClass
modifier|*
name|undo_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|undo_class
operator|=
name|GIMP_UNDO_CLASS
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
name|undo_class
operator|->
name|free
operator|=
name|gimp_item_undo_free
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_undo_init (GimpItemUndo * undo)
name|gimp_item_undo_init
parameter_list|(
name|GimpItemUndo
modifier|*
name|undo
parameter_list|)
block|{
name|undo
operator|->
name|item
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_item_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpItemUndo
modifier|*
name|item_undo
decl_stmt|;
name|item_undo
operator|=
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
expr_stmt|;
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|free
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_undo
operator|->
name|item
condition|)
block|{
name|g_object_unref
argument_list|(
name|item_undo
operator|->
name|item
argument_list|)
expr_stmt|;
name|item_undo
operator|->
name|item
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpUndo
modifier|*
DECL|function|gimp_item_undo_new (GimpImage * gimage,GimpItem * item,GimpUndoType undo_type,const gchar * name,gpointer data,gint64 size,gboolean dirties_image,GimpUndoPopFunc pop_func,GimpUndoFreeFunc free_func)
name|gimp_item_undo_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpUndoType
name|undo_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint64
name|size
parameter_list|,
name|gboolean
name|dirties_image
parameter_list|,
name|GimpUndoPopFunc
name|pop_func
parameter_list|,
name|GimpUndoFreeFunc
name|free_func
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|size
operator|==
literal|0
operator|||
name|data
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
name|gimp_undo_type_to_name
argument_list|(
name|undo_type
argument_list|)
expr_stmt|;
name|undo
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ITEM_UNDO
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|undo
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|undo
operator|->
name|undo_type
operator|=
name|undo_type
expr_stmt|;
name|undo
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|undo
operator|->
name|size
operator|=
name|size
expr_stmt|;
name|undo
operator|->
name|dirties_image
operator|=
name|dirties_image
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|undo
operator|->
name|pop_func
operator|=
name|pop_func
expr_stmt|;
name|undo
operator|->
name|free_func
operator|=
name|free_func
expr_stmt|;
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
operator|=
name|g_object_ref
argument_list|(
name|item
argument_list|)
expr_stmt|;
return|return
name|undo
return|;
block|}
end_function

end_unit

