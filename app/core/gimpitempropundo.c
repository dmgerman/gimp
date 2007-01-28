begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Gimp - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpitempropundo.h"
end_include

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_item_prop_undo_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_prop_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_prop_undo_free
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpItemPropUndo,gimp_item_prop_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpItemPropUndo
argument_list|,
argument|gimp_item_prop_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_item_prop_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_item_prop_undo_class_init
parameter_list|(
name|GimpItemPropUndoClass
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
name|GimpUndoClass
modifier|*
name|undo_class
init|=
name|GIMP_UNDO_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_item_prop_undo_constructor
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_item_prop_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_item_prop_undo_free
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_prop_undo_init (GimpItemPropUndo * undo)
name|gimp_item_prop_undo_init
parameter_list|(
name|GimpItemPropUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_item_prop_undo_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_item_prop_undo_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpItemPropUndo
modifier|*
name|item_prop_undo
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|item_prop_undo
operator|=
name|GIMP_ITEM_PROP_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|item
expr_stmt|;
if|if
condition|(
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_ITEM_RENAME
condition|)
block|{
name|item_prop_undo
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|size
operator|+=
name|strlen
argument_list|(
name|item_prop_undo
operator|->
name|name
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
name|gimp_item_offsets
argument_list|(
name|item
argument_list|,
operator|&
name|item_prop_undo
operator|->
name|offset_x
argument_list|,
operator|&
name|item_prop_undo
operator|->
name|offset_y
argument_list|)
expr_stmt|;
name|item_prop_undo
operator|->
name|visible
operator|=
name|gimp_item_get_visible
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|item_prop_undo
operator|->
name|linked
operator|=
name|gimp_item_get_linked
argument_list|(
name|item
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_prop_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_item_prop_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
block|{
name|GimpItemPropUndo
modifier|*
name|item_prop_undo
init|=
name|GIMP_ITEM_PROP_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
decl_stmt|;
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|pop
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|,
name|accum
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_ITEM_RENAME
condition|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|undo
operator|->
name|size
operator|-=
name|strlen
argument_list|(
name|item_prop_undo
operator|->
name|name
argument_list|)
operator|+
literal|1
expr_stmt|;
name|name
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
name|item_prop_undo
operator|->
name|name
argument_list|)
expr_stmt|;
name|item_prop_undo
operator|->
name|name
operator|=
name|name
expr_stmt|;
name|undo
operator|->
name|size
operator|+=
name|strlen
argument_list|(
name|item_prop_undo
operator|->
name|name
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_ITEM_DISPLACE
condition|)
block|{
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gimp_item_offsets
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|item
argument_list|,
name|item_prop_undo
operator|->
name|offset_x
operator|-
name|offset_x
argument_list|,
name|item_prop_undo
operator|->
name|offset_y
operator|-
name|offset_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|item_prop_undo
operator|->
name|offset_x
operator|=
name|offset_x
expr_stmt|;
name|item_prop_undo
operator|->
name|offset_y
operator|=
name|offset_y
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_ITEM_VISIBILITY
condition|)
block|{
name|gboolean
name|visible
decl_stmt|;
name|visible
operator|=
name|gimp_item_get_visible
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|gimp_item_set_visible
argument_list|(
name|item
argument_list|,
name|item_prop_undo
operator|->
name|visible
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|item_prop_undo
operator|->
name|visible
operator|=
name|visible
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_ITEM_LINKED
condition|)
block|{
name|gboolean
name|linked
decl_stmt|;
name|linked
operator|=
name|gimp_item_get_linked
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|gimp_item_set_linked
argument_list|(
name|item
argument_list|,
name|item_prop_undo
operator|->
name|linked
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|item_prop_undo
operator|->
name|linked
operator|=
name|linked
expr_stmt|;
block|}
else|else
block|{
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_prop_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_item_prop_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpItemPropUndo
modifier|*
name|item_prop_undo
init|=
name|GIMP_ITEM_PROP_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
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
name|item_prop_undo
operator|->
name|name
condition|)
block|{
name|g_free
argument_list|(
name|item_prop_undo
operator|->
name|name
argument_list|)
expr_stmt|;
name|item_prop_undo
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

end_unit

