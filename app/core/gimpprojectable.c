begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprojectable.c  * Copyright (C) 2008  Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|enum|__anon2a15d2ec0103
block|{
DECL|enumerator|UPDATE
name|UPDATE
block|,
DECL|enumerator|FLUSH
name|FLUSH
block|,
DECL|enumerator|STRUCTURE_CHANGED
name|STRUCTURE_CHANGED
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
name|gimp_projectable_iface_base_init
parameter_list|(
name|GimpProjectableInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|projectable_signals
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

begin_function
name|GType
DECL|function|gimp_projectable_interface_get_type (void)
name|gimp_projectable_interface_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|projectable_iface_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|projectable_iface_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|projectable_iface_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpProjectableInterface
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|gimp_projectable_iface_base_init
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|projectable_iface_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_INTERFACE
argument_list|,
literal|"GimpProjectableInterface"
argument_list|,
operator|&
name|projectable_iface_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_interface_add_prerequisite
argument_list|(
name|projectable_iface_type
argument_list|,
name|GIMP_TYPE_VIEWABLE
argument_list|)
expr_stmt|;
block|}
return|return
name|projectable_iface_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_projectable_iface_base_init (GimpProjectableInterface * iface)
name|gimp_projectable_iface_base_init
parameter_list|(
name|GimpProjectableInterface
modifier|*
name|iface
parameter_list|)
block|{
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
name|initialized
condition|)
block|{
name|projectable_signals
index|[
name|UPDATE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"update"
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
name|update
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
name|initialized
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_projectable_update (GimpProjectable * projectable,gint x,gint y,gint width,gint height)
name|gimp_projectable_update
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
name|UPDATE
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
name|void
DECL|function|gimp_projectable_get_size (GimpProjectable * projectable,gint * width,gint * height)
name|gimp_projectable_get_size
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
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
name|width
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|height
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
name|width
operator|=
literal|0
expr_stmt|;
operator|*
name|height
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_size
condition|)
name|iface
operator|->
name|get_size
argument_list|(
name|projectable
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
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

begin_function
name|GList
modifier|*
DECL|function|gimp_projectable_get_layers (GimpProjectable * projectable)
name|gimp_projectable_get_layers
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
name|get_layers
condition|)
return|return
name|iface
operator|->
name|get_layers
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
name|GList
modifier|*
DECL|function|gimp_projectable_get_channels (GimpProjectable * projectable)
name|gimp_projectable_get_channels
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
name|get_channels
condition|)
return|return
name|iface
operator|->
name|get_channels
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
name|gboolean
modifier|*
DECL|function|gimp_projectable_get_components (GimpProjectable * projectable)
name|gimp_projectable_get_components
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
name|get_components
condition|)
return|return
name|iface
operator|->
name|get_components
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
name|guchar
modifier|*
DECL|function|gimp_projectable_get_colormap (GimpProjectable * projectable)
name|gimp_projectable_get_colormap
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
name|get_colormap
condition|)
return|return
name|iface
operator|->
name|get_colormap
argument_list|(
name|projectable
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

