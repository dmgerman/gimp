begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprojectable.c  * Copyright (C) 2008  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpprojectable.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon279246c80103
block|{
DECL|enumerator|INVALIDATE
name|INVALIDATE
block|,
DECL|enumerator|FLUSH
name|FLUSH
block|,
DECL|enumerator|STRUCTURE_CHANGED
name|STRUCTURE_CHANGED
block|,
DECL|enumerator|BOUNDS_CHANGED
name|BOUNDS_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_macro
name|G_DEFINE_INTERFACE
argument_list|(
argument|GimpProjectable
argument_list|,
argument|gimp_projectable
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|guint
name|projectable_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_projectable_default_init (GimpProjectableInterface * iface)
name|gimp_projectable_default_init
parameter_list|(
name|GimpProjectableInterface
modifier|*
name|iface
parameter_list|)
block|{
name|projectable_signals
index|[
name|INVALIDATE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"invalidate"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|iface
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpProjectableInterface
argument_list|,
name|invalidate
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__INT_INT_INT_INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|4
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|projectable_signals
index|[
name|FLUSH
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"flush"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|iface
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpProjectableInterface
argument_list|,
name|flush
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__BOOLEAN
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|)
expr_stmt|;
name|projectable_signals
index|[
name|STRUCTURE_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"structure-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|iface
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpProjectableInterface
argument_list|,
name|structure_changed
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
name|projectable_signals
index|[
name|BOUNDS_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"bounds-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|iface
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpProjectableInterface
argument_list|,
name|bounds_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__INT_INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_projectable_invalidate (GimpProjectable * projectable,gint x,gint y,gint width,gint height)
name|gimp_projectable_invalidate
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|projectable
argument_list|,
name|projectable_signals
index|[
name|INVALIDATE
index|]
argument_list|,
literal|0
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_projectable_flush (GimpProjectable * projectable,gboolean preview_invalidated)
name|gimp_projectable_flush
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gboolean
name|preview_invalidated
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|projectable
argument_list|,
name|projectable_signals
index|[
name|FLUSH
index|]
argument_list|,
literal|0
argument_list|,
name|preview_invalidated
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_projectable_structure_changed (GimpProjectable * projectable)
name|gimp_projectable_structure_changed
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|projectable
argument_list|,
name|projectable_signals
index|[
name|STRUCTURE_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_projectable_bounds_changed (GimpProjectable * projectable,gint old_x,gint old_y)
name|gimp_projectable_bounds_changed
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gint
name|old_x
parameter_list|,
name|gint
name|old_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|projectable
argument_list|,
name|projectable_signals
index|[
name|BOUNDS_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|old_x
argument_list|,
name|old_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_projectable_get_image (GimpProjectable * projectable)
name|gimp_projectable_get_image
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
block|{
name|GimpProjectableInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_PROJECTABLE_GET_INTERFACE
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_image
condition|)
return|return
name|iface
operator|->
name|get_image
argument_list|(
name|projectable
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_projectable_get_format (GimpProjectable * projectable)
name|gimp_projectable_get_format
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
block|{
name|GimpProjectableInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_PROJECTABLE_GET_INTERFACE
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_format
condition|)
return|return
name|iface
operator|->
name|get_format
argument_list|(
name|projectable
argument_list|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_projectable_get_offset (GimpProjectable * projectable,gint * x,gint * y)
name|gimp_projectable_get_offset
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
block|{
name|GimpProjectableInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|x
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|y
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_PROJECTABLE_GET_INTERFACE
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
operator|*
name|x
operator|=
literal|0
expr_stmt|;
operator|*
name|y
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_offset
condition|)
name|iface
operator|->
name|get_offset
argument_list|(
name|projectable
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GeglRectangle
DECL|function|gimp_projectable_get_bounding_box (GimpProjectable * projectable)
name|gimp_projectable_get_bounding_box
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
block|{
name|GimpProjectableInterface
modifier|*
name|iface
decl_stmt|;
name|GeglRectangle
name|result
init|=
block|{}
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|,
name|result
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_PROJECTABLE_GET_INTERFACE
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_bounding_box
condition|)
name|result
operator|=
name|iface
operator|->
name|get_bounding_box
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|GeglNode
modifier|*
DECL|function|gimp_projectable_get_graph (GimpProjectable * projectable)
name|gimp_projectable_get_graph
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
block|{
name|GimpProjectableInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_PROJECTABLE_GET_INTERFACE
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_graph
condition|)
return|return
name|iface
operator|->
name|get_graph
argument_list|(
name|projectable
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_projectable_begin_render (GimpProjectable * projectable)
name|gimp_projectable_begin_render
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
block|{
name|GimpProjectableInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_PROJECTABLE_GET_INTERFACE
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|begin_render
condition|)
name|iface
operator|->
name|begin_render
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_projectable_end_render (GimpProjectable * projectable)
name|gimp_projectable_end_render
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
block|{
name|GimpProjectableInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_PROJECTABLE_GET_INTERFACE
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|end_render
condition|)
name|iface
operator|->
name|end_render
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_projectable_invalidate_preview (GimpProjectable * projectable)
name|gimp_projectable_invalidate_preview
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
block|{
name|GimpProjectableInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROJECTABLE
argument_list|(
name|projectable
argument_list|)
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_PROJECTABLE_GET_INTERFACE
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|invalidate_preview
condition|)
name|iface
operator|->
name|invalidate_preview
argument_list|(
name|projectable
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

