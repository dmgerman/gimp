begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpitem-exclusive.c  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpitem-exclusive.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemstack.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemtree.h"
end_include

begin_include
include|#
directive|include
file|"gimpundostack.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|GList
modifier|*
name|gimp_item_exclusive_get_ancestry
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_exclusive_get_lists
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property
parameter_list|,
name|GList
modifier|*
modifier|*
name|on
parameter_list|,
name|GList
modifier|*
modifier|*
name|off
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_item_toggle_exclusive_visible (GimpItem * item,GimpContext * context)
name|gimp_item_toggle_exclusive_visible
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GList
modifier|*
name|ancestry
decl_stmt|;
name|GList
modifier|*
name|on
decl_stmt|;
name|GList
modifier|*
name|off
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|ancestry
operator|=
name|gimp_item_exclusive_get_ancestry
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|gimp_item_exclusive_get_lists
argument_list|(
name|item
argument_list|,
literal|"visible"
argument_list|,
operator|&
name|on
argument_list|,
operator|&
name|off
argument_list|)
expr_stmt|;
if|if
condition|(
name|on
operator|||
name|off
operator|||
operator|!
name|gimp_item_is_visible
argument_list|(
name|item
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|gboolean
name|push_undo
init|=
name|TRUE
decl_stmt|;
name|undo
operator|=
name|gimp_image_undo_can_compress
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_UNDO_STACK
argument_list|,
name|GIMP_UNDO_GROUP_ITEM_VISIBILITY
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|&&
operator|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|,
literal|"exclusive-visible-item"
argument_list|)
operator|==
operator|(
name|gpointer
operator|)
name|item
operator|)
condition|)
name|push_undo
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
block|{
if|if
condition|(
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_ITEM_VISIBILITY
argument_list|,
name|_
argument_list|(
literal|"Set Item Exclusive Visible"
argument_list|)
argument_list|)
condition|)
block|{
name|undo
operator|=
name|gimp_image_undo_can_compress
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_UNDO_STACK
argument_list|,
name|GIMP_UNDO_GROUP_ITEM_VISIBILITY
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
condition|)
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|,
literal|"exclusive-visible-item"
argument_list|,
operator|(
name|gpointer
operator|)
name|item
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|ancestry
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_image_undo_push_item_visibility
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|on
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_image_undo_push_item_visibility
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|off
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_image_undo_push_item_visibility
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_undo_refresh_preview
argument_list|(
name|undo
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|ancestry
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_item_set_visible
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|on
condition|)
block|{
for|for
control|(
name|list
operator|=
name|on
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_item_set_visible
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|off
condition|)
block|{
for|for
control|(
name|list
operator|=
name|off
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_item_set_visible
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|on
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|off
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|ancestry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_toggle_exclusive_linked (GimpItem * item,GimpContext * context)
name|gimp_item_toggle_exclusive_linked
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GList
modifier|*
name|on
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|off
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_item_get_container_iter
argument_list|(
name|item
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpItem
modifier|*
name|other
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|other
operator|!=
name|item
condition|)
block|{
if|if
condition|(
name|gimp_item_get_linked
argument_list|(
name|other
argument_list|)
condition|)
name|on
operator|=
name|g_list_prepend
argument_list|(
name|on
argument_list|,
name|other
argument_list|)
expr_stmt|;
else|else
name|off
operator|=
name|g_list_prepend
argument_list|(
name|off
argument_list|,
name|other
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|on
operator|||
name|off
operator|||
operator|!
name|gimp_item_get_linked
argument_list|(
name|item
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|gboolean
name|push_undo
init|=
name|TRUE
decl_stmt|;
name|undo
operator|=
name|gimp_image_undo_can_compress
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_UNDO_STACK
argument_list|,
name|GIMP_UNDO_GROUP_ITEM_LINKED
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|&&
operator|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|,
literal|"exclusive-linked-item"
argument_list|)
operator|==
operator|(
name|gpointer
operator|)
name|item
operator|)
condition|)
name|push_undo
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
block|{
if|if
condition|(
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_ITEM_LINKED
argument_list|,
name|_
argument_list|(
literal|"Set Item Exclusive Linked"
argument_list|)
argument_list|)
condition|)
block|{
name|undo
operator|=
name|gimp_image_undo_can_compress
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_UNDO_STACK
argument_list|,
name|GIMP_UNDO_GROUP_ITEM_LINKED
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
condition|)
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|,
literal|"exclusive-linked-item"
argument_list|,
operator|(
name|gpointer
operator|)
name|item
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_push_item_linked
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|item
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|on
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_image_undo_push_item_linked
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|off
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_image_undo_push_item_linked
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_undo_refresh_preview
argument_list|(
name|undo
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|off
operator|||
operator|!
name|gimp_item_get_linked
argument_list|(
name|item
argument_list|)
condition|)
block|{
name|gimp_item_set_linked
argument_list|(
name|item
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|off
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_item_set_linked
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|list
operator|=
name|on
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_item_set_linked
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|on
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|off
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_item_exclusive_get_ancestry (GimpItem * item)
name|gimp_item_exclusive_get_ancestry
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
name|GimpViewable
modifier|*
name|parent
decl_stmt|;
name|GList
modifier|*
name|ancestry
init|=
name|NULL
decl_stmt|;
for|for
control|(
name|parent
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
init|;
name|parent
condition|;
name|parent
operator|=
name|gimp_viewable_get_parent
argument_list|(
name|parent
argument_list|)
control|)
block|{
name|ancestry
operator|=
name|g_list_prepend
argument_list|(
name|ancestry
argument_list|,
name|parent
argument_list|)
expr_stmt|;
block|}
return|return
name|ancestry
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_exclusive_get_lists (GimpItem * item,const gchar * property,GList ** on,GList ** off)
name|gimp_item_exclusive_get_lists
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property
parameter_list|,
name|GList
modifier|*
modifier|*
name|on
parameter_list|,
name|GList
modifier|*
modifier|*
name|off
parameter_list|)
block|{
name|GimpItemTree
modifier|*
name|tree
decl_stmt|;
name|GList
modifier|*
name|items
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
operator|*
name|on
operator|=
name|NULL
expr_stmt|;
operator|*
name|off
operator|=
name|NULL
expr_stmt|;
name|tree
operator|=
name|gimp_item_get_tree
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|items
operator|=
name|gimp_item_stack_get_item_list
argument_list|(
name|GIMP_ITEM_STACK
argument_list|(
name|tree
operator|->
name|container
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|items
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpItem
modifier|*
name|other
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|other
operator|!=
name|item
condition|)
block|{
comment|/* we are only interested in same level items.            */
if|if
condition|(
name|gimp_viewable_get_parent
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|other
argument_list|)
argument_list|)
operator|==
name|gimp_viewable_get_parent
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|)
condition|)
block|{
name|gboolean
name|value
decl_stmt|;
name|g_object_get
argument_list|(
name|other
argument_list|,
name|property
argument_list|,
operator|&
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
operator|*
name|on
operator|=
name|g_list_prepend
argument_list|(
operator|*
name|on
argument_list|,
name|other
argument_list|)
expr_stmt|;
else|else
operator|*
name|off
operator|=
name|g_list_prepend
argument_list|(
operator|*
name|off
argument_list|,
name|other
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|g_list_free
argument_list|(
name|items
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

