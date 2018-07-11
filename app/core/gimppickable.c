begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppickable.c  * Copyright (C) 2004  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"libgimpmath/gimpmath.h"
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

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_pickable_real_get_pixel_average
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gpointer
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_INTERFACE (GimpPickable,gimp_pickable,GIMP_TYPE_OBJECT)
name|G_DEFINE_INTERFACE
argument_list|(
argument|GimpPickable
argument_list|,
argument|gimp_pickable
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
name|gimp_pickable_default_init
parameter_list|(
name|GimpPickableInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|get_pixel_average
operator|=
name|gimp_pickable_real_get_pixel_average
expr_stmt|;
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pickable_real_get_pixel_average (GimpPickable * pickable,const GeglRectangle * rect,const Babl * format,gpointer pixel)
name|gimp_pickable_real_get_pixel_average
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
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
specifier|const
name|Babl
modifier|*
name|average_format
init|=
name|babl_format
argument_list|(
literal|"RaGaBaA double"
argument_list|)
decl_stmt|;
name|gdouble
name|average
index|[
literal|4
index|]
init|=
block|{}
decl_stmt|;
name|gint
name|n
init|=
literal|0
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gint
name|c
decl_stmt|;
for|for
control|(
name|y
operator|=
name|rect
operator|->
name|y
init|;
name|y
operator|<
name|rect
operator|->
name|y
operator|+
name|rect
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
name|rect
operator|->
name|x
init|;
name|x
operator|<
name|rect
operator|->
name|x
operator|+
name|rect
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
name|gdouble
name|sample
index|[
literal|4
index|]
decl_stmt|;
if|if
condition|(
name|gimp_pickable_get_pixel_at
argument_list|(
name|pickable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|average_format
argument_list|,
name|sample
argument_list|)
condition|)
block|{
for|for
control|(
name|c
operator|=
literal|0
init|;
name|c
operator|<
literal|4
condition|;
name|c
operator|++
control|)
name|average
index|[
name|c
index|]
operator|+=
name|sample
index|[
name|c
index|]
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|n
operator|>
literal|0
condition|)
block|{
for|for
control|(
name|c
operator|=
literal|0
init|;
name|c
operator|<
literal|4
condition|;
name|c
operator|++
control|)
name|average
index|[
name|c
index|]
operator|/=
name|n
expr_stmt|;
block|}
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
name|average_format
argument_list|,
name|format
argument_list|)
argument_list|,
name|average
argument_list|,
name|pixel
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

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
name|void
DECL|function|gimp_pickable_get_pixel_average (GimpPickable * pickable,const GeglRectangle * rect,const Babl * format,gpointer pixel)
name|gimp_pickable_get_pixel_average
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|pixel
operator|!=
name|NULL
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
name|get_pixel_average
condition|)
name|pickable_iface
operator|->
name|get_pixel_average
argument_list|(
name|pickable
argument_list|,
name|rect
argument_list|,
name|format
argument_list|,
name|pixel
argument_list|)
expr_stmt|;
else|else
name|memset
argument_list|(
name|pixel
argument_list|,
literal|0
argument_list|,
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
argument_list|)
expr_stmt|;
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
name|gimp_pickable_pixel_to_srgb
argument_list|(
name|pickable
argument_list|,
name|NULL
argument_list|,
name|pixel
argument_list|,
name|color
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
name|void
DECL|function|gimp_pickable_pixel_to_srgb (GimpPickable * pickable,const Babl * format,gpointer pixel,GimpRGB * color)
name|gimp_pickable_pixel_to_srgb
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gpointer
name|pixel
parameter_list|,
name|GimpRGB
modifier|*
name|color
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
name|g_return_if_fail
argument_list|(
name|pixel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
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
name|pixel_to_srgb
condition|)
block|{
name|pickable_iface
operator|->
name|pixel_to_srgb
argument_list|(
name|pickable
argument_list|,
name|format
argument_list|,
name|pixel
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_rgba_set_pixel
argument_list|(
name|color
argument_list|,
name|format
argument_list|,
name|pixel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_pickable_srgb_to_pixel (GimpPickable * pickable,const GimpRGB * color,const Babl * format,gpointer pixel)
name|gimp_pickable_srgb_to_pixel
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|pixel
operator|!=
name|NULL
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
name|srgb_to_pixel
condition|)
block|{
name|pickable_iface
operator|->
name|srgb_to_pixel
argument_list|(
name|pickable
argument_list|,
name|color
argument_list|,
name|format
argument_list|,
name|pixel
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_rgba_get_pixel
argument_list|(
name|color
argument_list|,
name|format
argument_list|,
name|pixel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_pickable_srgb_to_image_color (GimpPickable * pickable,const GimpRGB * color,GimpRGB * image_color)
name|gimp_pickable_srgb_to_image_color
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpRGB
modifier|*
name|image_color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|image_color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_pickable_srgb_to_pixel
argument_list|(
name|pickable
argument_list|,
name|color
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
argument_list|,
name|image_color
argument_list|)
expr_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
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
name|radius
init|=
name|floor
argument_list|(
name|average_radius
argument_list|)
decl_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
literal|"RaGaBaA double"
argument_list|)
expr_stmt|;
name|gimp_pickable_get_pixel_average
argument_list|(
name|pickable
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
operator|-
name|radius
argument_list|,
name|y
operator|-
name|radius
argument_list|,
literal|2
operator|*
name|radius
operator|+
literal|1
argument_list|,
literal|2
operator|*
name|radius
operator|+
literal|1
argument_list|)
argument_list|,
name|format
argument_list|,
name|sample
argument_list|)
expr_stmt|;
block|}
name|gimp_pickable_pixel_to_srgb
argument_list|(
name|pickable
argument_list|,
name|format
argument_list|,
name|sample
argument_list|,
name|color
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

