begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppickable.c  * Copyright (C) 2004  Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_function
name|GType
DECL|function|gimp_pickable_interface_get_type (void)
name|gimp_pickable_interface_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|pickable_iface_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|pickable_iface_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|pickable_iface_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPickableInterface
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
block|,       }
decl_stmt|;
name|pickable_iface_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_INTERFACE
argument_list|,
literal|"GimpPickableInterface"
argument_list|,
operator|&
name|pickable_iface_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_interface_add_prerequisite
argument_list|(
name|pickable_iface_type
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
expr_stmt|;
block|}
return|return
name|pickable_iface_type
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_pickable_get_image (GimpPickable * pickable)
name|gimp_pickable_get_image
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
block|{
name|GimpPickableInterface
modifier|*
name|pickable_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pickable_iface
operator|=
name|GIMP_PICKABLE_GET_INTERFACE
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
if|if
condition|(
name|pickable_iface
operator|->
name|get_image
condition|)
return|return
name|pickable_iface
operator|->
name|get_image
argument_list|(
name|pickable
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpImageType
DECL|function|gimp_pickable_get_image_type (GimpPickable * pickable)
name|gimp_pickable_get_image_type
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
block|{
name|GimpPickableInterface
modifier|*
name|pickable_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pickable_iface
operator|=
name|GIMP_PICKABLE_GET_INTERFACE
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
if|if
condition|(
name|pickable_iface
operator|->
name|get_image_type
condition|)
return|return
name|pickable_iface
operator|->
name|get_image_type
argument_list|(
name|pickable
argument_list|)
return|;
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|gimp_pickable_get_tiles (GimpPickable * pickable)
name|gimp_pickable_get_tiles
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
block|{
name|GimpPickableInterface
modifier|*
name|pickable_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pickable_iface
operator|=
name|GIMP_PICKABLE_GET_INTERFACE
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
if|if
condition|(
name|pickable_iface
operator|->
name|get_tiles
condition|)
return|return
name|pickable_iface
operator|->
name|get_tiles
argument_list|(
name|pickable
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|gimp_pickable_get_color_at (GimpPickable * pickable,gint x,gint y)
name|gimp_pickable_get_color_at
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GimpPickableInterface
modifier|*
name|pickable_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pickable_iface
operator|=
name|GIMP_PICKABLE_GET_INTERFACE
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
if|if
condition|(
name|pickable_iface
operator|->
name|get_color_at
condition|)
return|return
name|pickable_iface
operator|->
name|get_color_at
argument_list|(
name|pickable
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_pickable_pick_color (GimpPickable * pickable,gint x,gint y,gboolean sample_average,gdouble average_radius,GimpRGB * color,gint * color_index)
name|gimp_pickable_pick_color
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gboolean
name|sample_average
parameter_list|,
name|gdouble
name|average_radius
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
modifier|*
name|color_index
parameter_list|)
block|{
name|guchar
modifier|*
name|col
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|col
operator|=
name|gimp_pickable_get_color_at
argument_list|(
name|pickable
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
operator|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|sample_average
condition|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gint
name|count
init|=
literal|0
decl_stmt|;
name|gint
name|color_avg
index|[
literal|4
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|guchar
modifier|*
name|tmp_col
decl_stmt|;
name|gint
name|radius
init|=
operator|(
name|gint
operator|)
name|average_radius
decl_stmt|;
for|for
control|(
name|i
operator|=
name|x
operator|-
name|radius
init|;
name|i
operator|<=
name|x
operator|+
name|radius
condition|;
name|i
operator|++
control|)
for|for
control|(
name|j
operator|=
name|y
operator|-
name|radius
init|;
name|j
operator|<=
name|y
operator|+
name|radius
condition|;
name|j
operator|++
control|)
if|if
condition|(
operator|(
name|tmp_col
operator|=
name|gimp_pickable_get_color_at
argument_list|(
name|pickable
argument_list|,
name|i
argument_list|,
name|j
argument_list|)
operator|)
condition|)
block|{
name|count
operator|++
expr_stmt|;
name|color_avg
index|[
name|RED_PIX
index|]
operator|+=
name|tmp_col
index|[
name|RED_PIX
index|]
expr_stmt|;
name|color_avg
index|[
name|GREEN_PIX
index|]
operator|+=
name|tmp_col
index|[
name|GREEN_PIX
index|]
expr_stmt|;
name|color_avg
index|[
name|BLUE_PIX
index|]
operator|+=
name|tmp_col
index|[
name|BLUE_PIX
index|]
expr_stmt|;
name|color_avg
index|[
name|ALPHA_PIX
index|]
operator|+=
name|tmp_col
index|[
name|ALPHA_PIX
index|]
expr_stmt|;
name|g_free
argument_list|(
name|tmp_col
argument_list|)
expr_stmt|;
block|}
name|col
index|[
name|RED_PIX
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|color_avg
index|[
name|RED_PIX
index|]
operator|/
name|count
argument_list|)
expr_stmt|;
name|col
index|[
name|GREEN_PIX
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|color_avg
index|[
name|GREEN_PIX
index|]
operator|/
name|count
argument_list|)
expr_stmt|;
name|col
index|[
name|BLUE_PIX
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|color_avg
index|[
name|BLUE_PIX
index|]
operator|/
name|count
argument_list|)
expr_stmt|;
name|col
index|[
name|ALPHA_PIX
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|color_avg
index|[
name|ALPHA_PIX
index|]
operator|/
name|count
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|color
condition|)
name|gimp_rgba_set_uchar
argument_list|(
name|color
argument_list|,
name|col
index|[
name|RED_PIX
index|]
argument_list|,
name|col
index|[
name|GREEN_PIX
index|]
argument_list|,
name|col
index|[
name|BLUE_PIX
index|]
argument_list|,
name|col
index|[
name|ALPHA_PIX
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|color_index
condition|)
operator|*
name|color_index
operator|=
name|sample_average
condition|?
operator|-
literal|1
else|:
name|col
index|[
literal|4
index|]
expr_stmt|;
name|g_free
argument_list|(
name|col
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

