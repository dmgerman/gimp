begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawablemodundo.h"
end_include

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_drawable_mod_undo_constructor
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
name|gint64
name|gimp_drawable_mod_undo_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_mod_undo_pop
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
name|gimp_drawable_mod_undo_free
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
DECL|function|G_DEFINE_TYPE (GimpDrawableModUndo,gimp_drawable_mod_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDrawableModUndo
argument_list|,
argument|gimp_drawable_mod_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_drawable_mod_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_drawable_mod_undo_class_init
parameter_list|(
name|GimpDrawableModUndoClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
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
name|gimp_drawable_mod_undo_constructor
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_drawable_mod_undo_get_memsize
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_drawable_mod_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_drawable_mod_undo_free
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_mod_undo_init (GimpDrawableModUndo * undo)
name|gimp_drawable_mod_undo_init
parameter_list|(
name|GimpDrawableModUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_drawable_mod_undo_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_drawable_mod_undo_constructor
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
name|GimpDrawableModUndo
modifier|*
name|drawable_mod_undo
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
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
name|drawable_mod_undo
operator|=
name|GIMP_DRAWABLE_MOD_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|item
argument_list|)
expr_stmt|;
name|drawable_mod_undo
operator|->
name|tiles
operator|=
name|tile_manager_ref
argument_list|(
name|drawable
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|drawable_mod_undo
operator|->
name|type
operator|=
name|drawable
operator|->
name|type
expr_stmt|;
name|drawable_mod_undo
operator|->
name|offset_x
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
operator|->
name|offset_x
expr_stmt|;
name|drawable_mod_undo
operator|->
name|offset_y
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
operator|->
name|offset_y
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|gint64
DECL|function|gimp_drawable_mod_undo_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_drawable_mod_undo_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpDrawableModUndo
modifier|*
name|drawable_mod_undo
init|=
name|GIMP_DRAWABLE_MOD_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|tile_manager_get_memsize
argument_list|(
name|drawable_mod_undo
operator|->
name|tiles
argument_list|,
name|FALSE
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
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_mod_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_drawable_mod_undo_pop
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
name|GimpDrawableModUndo
modifier|*
name|drawable_mod_undo
init|=
name|GIMP_DRAWABLE_MOD_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_DRAWABLE
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
argument_list|)
decl_stmt|;
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|GimpImageType
name|type
decl_stmt|;
name|gint
name|offset_x
decl_stmt|,
name|offset_y
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
name|tiles
operator|=
name|drawable_mod_undo
operator|->
name|tiles
expr_stmt|;
name|type
operator|=
name|drawable_mod_undo
operator|->
name|type
expr_stmt|;
name|offset_x
operator|=
name|drawable_mod_undo
operator|->
name|offset_x
expr_stmt|;
name|offset_y
operator|=
name|drawable_mod_undo
operator|->
name|offset_y
expr_stmt|;
name|drawable_mod_undo
operator|->
name|tiles
operator|=
name|tile_manager_ref
argument_list|(
name|drawable
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|drawable_mod_undo
operator|->
name|type
operator|=
name|drawable
operator|->
name|type
expr_stmt|;
name|drawable_mod_undo
operator|->
name|offset_x
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
operator|->
name|offset_x
expr_stmt|;
name|drawable_mod_undo
operator|->
name|offset_y
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
operator|->
name|offset_y
expr_stmt|;
name|gimp_drawable_set_tiles_full
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|tiles
argument_list|,
name|type
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_mod_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_drawable_mod_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpDrawableModUndo
modifier|*
name|drawable_mod_undo
init|=
name|GIMP_DRAWABLE_MOD_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
if|if
condition|(
name|drawable_mod_undo
operator|->
name|tiles
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|drawable_mod_undo
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|drawable_mod_undo
operator|->
name|tiles
operator|=
name|NULL
expr_stmt|;
block|}
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
block|}
end_function

end_unit

