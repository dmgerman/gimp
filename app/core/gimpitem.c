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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-parasites.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
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
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasitelist.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28d471a50103
block|{
DECL|enumerator|REMOVED
name|REMOVED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_item_class_init
parameter_list|(
name|GimpItemClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_init
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
name|gimp_item_finalize
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
name|gimp_item_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gsize
name|gimp_item_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpItem
modifier|*
name|gimp_item_real_duplicate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_real_rename
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|gimp_item_signals
specifier|static
name|guint
name|gimp_item_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpViewableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_item_get_type (void)
name|gimp_item_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|item_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|item_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|item_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpItemClass
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
name|gimp_item_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpItem
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_item_init
block|,       }
decl_stmt|;
name|item_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_VIEWABLE
argument_list|,
literal|"GimpItem"
argument_list|,
operator|&
name|item_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|item_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_class_init (GimpItemClass * klass)
name|gimp_item_class_init
parameter_list|(
name|GimpItemClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_object_class
operator|=
name|GIMP_OBJECT_CLASS
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
name|gimp_item_signals
index|[
name|REMOVED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"removed"
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
name|GimpItemClass
argument_list|,
name|removed
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_item_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|name_changed
operator|=
name|gimp_item_name_changed
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_item_get_memsize
expr_stmt|;
name|klass
operator|->
name|removed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|duplicate
operator|=
name|gimp_item_real_duplicate
expr_stmt|;
name|klass
operator|->
name|rename
operator|=
name|gimp_item_real_rename
expr_stmt|;
name|klass
operator|->
name|scale
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|resize
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_init (GimpItem * item)
name|gimp_item_init
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
name|item
operator|->
name|ID
operator|=
literal|0
expr_stmt|;
name|item
operator|->
name|tattoo
operator|=
literal|0
expr_stmt|;
name|item
operator|->
name|gimage
operator|=
name|NULL
expr_stmt|;
name|item
operator|->
name|parasites
operator|=
name|gimp_parasite_list_new
argument_list|()
expr_stmt|;
name|item
operator|->
name|width
operator|=
literal|0
expr_stmt|;
name|item
operator|->
name|height
operator|=
literal|0
expr_stmt|;
name|item
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|item
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_finalize (GObject * object)
name|gimp_item_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|item
operator|->
name|gimage
operator|&&
name|item
operator|->
name|gimage
operator|->
name|gimp
condition|)
block|{
name|g_hash_table_remove
argument_list|(
name|item
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|item_table
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|item
operator|->
name|ID
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|->
name|gimage
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|item
operator|->
name|parasites
condition|)
block|{
name|g_object_unref
argument_list|(
name|item
operator|->
name|parasites
argument_list|)
expr_stmt|;
name|item
operator|->
name|parasites
operator|=
name|NULL
expr_stmt|;
block|}
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

begin_function
specifier|static
name|void
DECL|function|gimp_item_name_changed (GimpObject * object)
name|gimp_item_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
expr_stmt|;
comment|/*  if no other items to check name against  */
if|if
condition|(
name|item
operator|->
name|gimage
operator|==
name|NULL
condition|)
return|return;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|item
argument_list|)
condition|)
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|item
operator|->
name|gimage
operator|->
name|layers
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|item
argument_list|)
condition|)
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|item
operator|->
name|gimage
operator|->
name|channels
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_VECTORS
argument_list|(
name|item
argument_list|)
condition|)
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|item
operator|->
name|gimage
operator|->
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
name|gimp_list_uniquefy_name
argument_list|(
name|list
argument_list|,
name|object
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gsize
DECL|function|gimp_item_get_memsize (GimpObject * object)
name|gimp_item_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|gsize
name|memsize
init|=
literal|0
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
operator|->
name|parasites
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpItem
modifier|*
DECL|function|gimp_item_real_duplicate (GimpItem * item,GType new_type,gboolean add_alpha)
name|gimp_item_real_duplicate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
block|{
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
name|gchar
modifier|*
name|new_name
decl_stmt|;
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
name|GIMP_IS_IMAGE
argument_list|(
name|item
operator|->
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|new_type
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  formulate the new name  */
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|ext
decl_stmt|;
name|gint
name|number
decl_stmt|;
name|gint
name|len
decl_stmt|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ext
operator|=
name|strrchr
argument_list|(
name|name
argument_list|,
literal|'#'
argument_list|)
expr_stmt|;
name|len
operator|=
name|strlen
argument_list|(
name|_
argument_list|(
literal|"copy"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|strlen
argument_list|(
name|name
argument_list|)
operator|>=
name|len
operator|&&
name|strcmp
argument_list|(
operator|&
name|name
index|[
name|strlen
argument_list|(
name|name
argument_list|)
operator|-
name|len
index|]
argument_list|,
name|_
argument_list|(
literal|"copy"
argument_list|)
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|ext
operator|&&
operator|(
name|number
operator|=
name|atoi
argument_list|(
name|ext
operator|+
literal|1
argument_list|)
operator|)
operator|>
literal|0
operator|&&
operator|(
call|(
name|int
call|)
argument_list|(
name|log10
argument_list|(
name|number
argument_list|)
operator|+
literal|1
argument_list|)
operator|)
operator|==
name|strlen
argument_list|(
name|ext
operator|+
literal|1
argument_list|)
operator|)
condition|)
block|{
comment|/* don't have redundant "copy"s */
name|new_name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new_name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s copy"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
block|}
name|new_item
operator|=
name|g_object_new
argument_list|(
name|new_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_item_configure
argument_list|(
name|new_item
argument_list|,
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|new_name
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_item
operator|->
name|parasites
argument_list|)
expr_stmt|;
name|new_item
operator|->
name|parasites
operator|=
name|gimp_parasite_list_copy
argument_list|(
name|item
operator|->
name|parasites
argument_list|)
expr_stmt|;
return|return
name|new_item
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_real_rename (GimpItem * item,const gchar * new_name,const gchar * undo_desc)
name|gimp_item_real_rename
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
if|if
condition|(
name|item
operator|->
name|gimage
condition|)
name|gimp_image_undo_push_item_rename
argument_list|(
name|item
operator|->
name|gimage
argument_list|,
name|undo_desc
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_removed (GimpItem * item)
name|gimp_item_removed
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|item
argument_list|,
name|gimp_item_signals
index|[
name|REMOVED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_configure (GimpItem * item,GimpImage * gimage,const gchar * name)
name|gimp_item_configure
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
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
name|item
operator|->
name|ID
operator|==
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|item
operator|->
name|gimage
operator|==
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|->
name|ID
operator|=
name|gimage
operator|->
name|gimp
operator|->
name|next_item_ID
operator|++
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|item_table
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|item
operator|->
name|ID
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|gimp_item_set_image
argument_list|(
name|item
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
name|name
condition|?
name|name
else|:
name|_
argument_list|(
literal|"Unnamed"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_duplicate (GimpItem * item,GType new_type,gboolean add_alpha)
name|gimp_item_duplicate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
block|{
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
name|GIMP_IS_IMAGE
argument_list|(
name|item
operator|->
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|new_type
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_ITEM_GET_CLASS
argument_list|(
name|item
argument_list|)
operator|->
name|duplicate
argument_list|(
name|item
argument_list|,
name|new_type
argument_list|,
name|add_alpha
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_rename (GimpItem * item,const gchar * new_name)
name|gimp_item_rename
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|)
block|{
name|GimpItemClass
modifier|*
name|item_class
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|item_class
operator|=
name|GIMP_ITEM_GET_CLASS
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|new_name
operator|||
operator|!
operator|*
name|new_name
condition|)
name|new_name
operator|=
name|item_class
operator|->
name|default_name
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|new_name
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|)
argument_list|)
condition|)
name|item_class
operator|->
name|rename
argument_list|(
name|item
argument_list|,
name|new_name
argument_list|,
name|item_class
operator|->
name|rename_desc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_scale (GimpItem * item,gint new_width,gint new_height,gint new_offset_x,gint new_offset_y,GimpInterpolationType interpolation_type)
name|gimp_item_scale
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|new_offset_x
parameter_list|,
name|gint
name|new_offset_y
parameter_list|,
name|GimpInterpolationType
name|interpolation_type
parameter_list|)
block|{
name|GimpItemClass
modifier|*
name|item_class
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_width
operator|<
literal|1
operator|||
name|new_height
operator|<
literal|1
condition|)
return|return;
name|item_class
operator|=
name|GIMP_ITEM_GET_CLASS
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|scale
argument_list|(
name|item
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
name|new_offset_x
argument_list|,
name|new_offset_y
argument_list|,
name|interpolation_type
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_resize (GimpItem * item,gint new_width,gint new_height,gint offset_x,gint offset_y)
name|gimp_item_resize
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
block|{
name|GimpItemClass
modifier|*
name|item_class
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_width
operator|<
literal|1
operator|||
name|new_height
operator|<
literal|1
condition|)
return|return;
name|item_class
operator|=
name|GIMP_ITEM_GET_CLASS
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|resize
argument_list|(
name|item
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_item_get_ID (GimpItem * item)
name|gimp_item_get_ID
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|item
operator|->
name|ID
return|;
block|}
end_function

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_get_by_ID (Gimp * gimp,gint item_id)
name|gimp_item_get_by_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|item_id
parameter_list|)
block|{
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
if|if
condition|(
name|gimp
operator|->
name|item_table
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
return|return
operator|(
name|GimpItem
operator|*
operator|)
name|g_hash_table_lookup
argument_list|(
name|gimp
operator|->
name|item_table
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|item_id
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpTattoo
DECL|function|gimp_item_get_tattoo (const GimpItem * item)
name|gimp_item_get_tattoo
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|item
operator|->
name|tattoo
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_set_tattoo (GimpItem * item,GimpTattoo tattoo)
name|gimp_item_set_tattoo
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpTattoo
name|tattoo
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|->
name|tattoo
operator|=
name|tattoo
expr_stmt|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_item_get_image (const GimpItem * item)
name|gimp_item_get_image
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
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
return|return
name|item
operator|->
name|gimage
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_set_image (GimpItem * item,GimpImage * gimage)
name|gimp_item_set_image
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
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
name|NULL
condition|)
block|{
name|item
operator|->
name|tattoo
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|item
operator|->
name|tattoo
operator|==
literal|0
operator|||
name|item
operator|->
name|gimage
operator|!=
name|gimage
condition|)
block|{
name|item
operator|->
name|tattoo
operator|=
name|gimp_image_get_new_tattoo
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
name|item
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_parasite_attach (GimpItem * item,GimpParasite * parasite)
name|gimp_item_parasite_attach
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  only set the dirty bit manually if we can be saved and the new    *  parasite differs from the current one and we arn't undoable    */
if|if
condition|(
name|gimp_parasite_is_undoable
argument_list|(
name|parasite
argument_list|)
condition|)
block|{
comment|/* do a group in case we have attach_parent set */
name|gimp_image_undo_group_start
argument_list|(
name|item
operator|->
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_PARASITE_ATTACH
argument_list|,
name|_
argument_list|(
literal|"Attach Parasite"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_push_item_parasite
argument_list|(
name|item
operator|->
name|gimage
argument_list|,
name|NULL
argument_list|,
name|item
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_parasite_is_persistent
argument_list|(
name|parasite
argument_list|)
operator|&&
operator|!
name|gimp_parasite_compare
argument_list|(
name|parasite
argument_list|,
name|gimp_item_parasite_find
argument_list|(
name|item
argument_list|,
name|gimp_parasite_name
argument_list|(
name|parasite
argument_list|)
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_image_undo_push_cantundo
argument_list|(
name|item
operator|->
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Attach Parasite to Item"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_parasite_list_add
argument_list|(
name|item
operator|->
name|parasites
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_parasite_has_flag
argument_list|(
name|parasite
argument_list|,
name|GIMP_PARASITE_ATTACH_PARENT
argument_list|)
condition|)
block|{
name|gimp_parasite_shift_parent
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|item
operator|->
name|gimage
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_parasite_has_flag
argument_list|(
name|parasite
argument_list|,
name|GIMP_PARASITE_ATTACH_GRANDPARENT
argument_list|)
condition|)
block|{
name|gimp_parasite_shift_parent
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_shift_parent
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_attach
argument_list|(
name|item
operator|->
name|gimage
operator|->
name|gimp
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_parasite_is_undoable
argument_list|(
name|parasite
argument_list|)
condition|)
block|{
name|gimp_image_undo_group_end
argument_list|(
name|item
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_parasite_detach (GimpItem * item,const gchar * name)
name|gimp_item_parasite_detach
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_list_find
argument_list|(
name|item
operator|->
name|parasites
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parasite
condition|)
return|return;
if|if
condition|(
name|gimp_parasite_is_undoable
argument_list|(
name|parasite
argument_list|)
condition|)
block|{
name|gimp_image_undo_push_item_parasite_remove
argument_list|(
name|item
operator|->
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Remove Parasite from Item"
argument_list|)
argument_list|,
name|item
argument_list|,
name|gimp_parasite_name
argument_list|(
name|parasite
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_parasite_is_persistent
argument_list|(
name|parasite
argument_list|)
condition|)
block|{
name|gimp_image_undo_push_cantundo
argument_list|(
name|item
operator|->
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Remove Parasite from Item"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_parasite_list_remove
argument_list|(
name|item
operator|->
name|parasites
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_item_parasite_find (const GimpItem * item,const gchar * name)
name|gimp_item_parasite_find
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
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
return|return
name|gimp_parasite_list_find
argument_list|(
name|item
operator|->
name|parasites
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_parasite_list_foreach_func (gchar * name,GimpParasite * parasite,gchar *** cur)
name|gimp_item_parasite_list_foreach_func
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|cur
parameter_list|)
block|{
operator|*
operator|(
operator|*
name|cur
operator|)
operator|++
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_item_parasite_list (const GimpItem * item,gint * count)
name|gimp_item_parasite_list
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|cur
decl_stmt|;
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
name|count
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|count
operator|=
name|gimp_parasite_list_length
argument_list|(
name|item
operator|->
name|parasites
argument_list|)
expr_stmt|;
name|cur
operator|=
name|list
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|count
argument_list|)
expr_stmt|;
name|gimp_parasite_list_foreach
argument_list|(
name|item
operator|->
name|parasites
argument_list|,
operator|(
name|GHFunc
operator|)
name|gimp_item_parasite_list_foreach_func
argument_list|,
operator|&
name|cur
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

end_unit

