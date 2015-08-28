begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppickable.c  * Copyright (C) 2004  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* This file contains an interface for pixel objects that their color at  * a given position can be picked. Also included is a utility for  * sampling an average area (which uses the implemented picking  * functions).  */
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
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_pickable_interface_base_init
parameter_list|(
name|GimpPickableInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

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
name|gimp_pickable_interface_base_init
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
specifier|static
name|void
DECL|function|gimp_pickable_interface_base_init (GimpPickableInterface * iface)
name|gimp_pickable_interface_base_init
parameter_list|(
name|GimpPickableInterface
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
name|g_object_interface_install_property
argument_list|(
name|iface
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"buffer"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GEGL_TYPE_BUFFER
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_pickable_flush (GimpPickable * pickable)
name|gimp_pickable_flush
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
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
name|flush
condition|)
name|pickable_iface
operator|->
name|flush
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
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
specifier|const
name|Babl
modifier|*
DECL|function|gimp_pickable_get_format (GimpPickable * pickable)
name|gimp_pickable_get_format
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
name|get_format
condition|)
return|return
name|pickable_iface
operator|->
name|get_format
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
specifier|const
name|Babl
modifier|*
DECL|function|gimp_pickable_get_format_with_alpha (GimpPickable * pickable)
name|gimp_pickable_get_format_with_alpha
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
name|get_format_with_alpha
condition|)
return|return
name|pickable_iface
operator|->
name|get_format_with_alpha
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
name|GimpColorProfile
modifier|*
DECL|function|gimp_pickable_get_color_profile (GimpPickable * pickable)
name|gimp_pickable_get_color_profile
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
name|get_color_profile
condition|)
return|return
name|pickable_iface
operator|->
name|get_color_profile
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
name|GeglBuffer
modifier|*
DECL|function|gimp_pickable_get_buffer (GimpPickable * pickable)
name|gimp_pickable_get_buffer
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
name|get_buffer
condition|)
return|return
name|pickable_iface
operator|->
name|get_buffer
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
name|gboolean
DECL|function|gimp_pickable_get_pixel_at (GimpPickable * pickable,gint x,gint y,const Babl * format,gpointer pixel)
name|gimp_pickable_get_pixel_at
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
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gpointer
name|pixel
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
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|pixel
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|format
condition|)
name|format
operator|=
name|gimp_pickable_get_format
argument_list|(
name|pickable
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
name|get_pixel_at
condition|)
return|return
name|pickable_iface
operator|->
name|get_pixel_at
argument_list|(
name|pickable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|format
argument_list|,
name|pixel
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_pickable_get_color_at (GimpPickable * pickable,gint x,gint y,GimpRGB * color)
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
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|guchar
name|pixel
index|[
literal|32
index|]
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
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_pickable_get_pixel_at
argument_list|(
name|pickable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|NULL
argument_list|,
name|pixel
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|gimp_rgba_set_pixel
argument_list|(
name|color
argument_list|,
name|gimp_pickable_get_format
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|pixel
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_pickable_get_opacity_at (GimpPickable * pickable,gint x,gint y)
name|gimp_pickable_get_opacity_at
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
name|GIMP_OPACITY_TRANSPARENT
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
name|get_opacity_at
condition|)
return|return
name|pickable_iface
operator|->
name|get_opacity_at
argument_list|(
name|pickable
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
return|;
return|return
name|GIMP_OPACITY_TRANSPARENT
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_pickable_pick_color (GimpPickable * pickable,gint x,gint y,gboolean sample_average,gdouble average_radius,gpointer pixel,GimpRGB * color)
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
name|gpointer
name|pixel
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gdouble
name|sample
index|[
literal|4
index|]
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
name|format
operator|=
name|gimp_pickable_get_format
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_pickable_get_pixel_at
argument_list|(
name|pickable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|format
argument_list|,
name|sample
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|gimp_rgba_set_pixel
argument_list|(
name|color
argument_list|,
name|format
argument_list|,
name|sample
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixel
condition|)
name|memcpy
argument_list|(
name|pixel
argument_list|,
name|sample
argument_list|,
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|sample_average
condition|)
block|{
name|gint
name|count
init|=
literal|0
decl_stmt|;
name|gdouble
name|color_avg
index|[
literal|4
index|]
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|}
decl_stmt|;
name|gint
name|radius
init|=
operator|(
name|gint
operator|)
name|average_radius
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
literal|"RGBA double"
argument_list|)
expr_stmt|;
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
name|gimp_pickable_get_pixel_at
argument_list|(
name|pickable
argument_list|,
name|i
argument_list|,
name|j
argument_list|,
name|format
argument_list|,
name|sample
argument_list|)
condition|)
block|{
name|count
operator|++
expr_stmt|;
name|color_avg
index|[
name|RED
index|]
operator|+=
name|sample
index|[
name|RED
index|]
expr_stmt|;
name|color_avg
index|[
name|GREEN
index|]
operator|+=
name|sample
index|[
name|GREEN
index|]
expr_stmt|;
name|color_avg
index|[
name|BLUE
index|]
operator|+=
name|sample
index|[
name|BLUE
index|]
expr_stmt|;
name|color_avg
index|[
name|ALPHA
index|]
operator|+=
name|sample
index|[
name|ALPHA
index|]
expr_stmt|;
block|}
name|sample
index|[
name|RED
index|]
operator|=
name|color_avg
index|[
name|RED
index|]
operator|/
name|count
expr_stmt|;
name|sample
index|[
name|GREEN
index|]
operator|=
name|color_avg
index|[
name|GREEN
index|]
operator|/
name|count
expr_stmt|;
name|sample
index|[
name|BLUE
index|]
operator|=
name|color_avg
index|[
name|BLUE
index|]
operator|/
name|count
expr_stmt|;
name|sample
index|[
name|ALPHA
index|]
operator|=
name|color_avg
index|[
name|ALPHA
index|]
operator|/
name|count
expr_stmt|;
name|gimp_rgba_set_pixel
argument_list|(
name|color
argument_list|,
name|format
argument_list|,
name|sample
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

