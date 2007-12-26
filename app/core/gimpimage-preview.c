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
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager-preview.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-preview.h"
end_include

begin_include
include|#
directive|include
file|"gimpprojection.h"
end_include

begin_function
name|void
DECL|function|gimp_image_get_preview_size (GimpViewable * viewable,gint size,gboolean is_popup,gboolean dot_for_dot,gint * width,gint * height)
name|gimp_image_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|is_popup
parameter_list|,
name|gboolean
name|dot_for_dot
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
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|,
name|size
argument_list|,
name|size
argument_list|,
name|dot_for_dot
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_get_popup_size (GimpViewable * viewable,gint width,gint height,gboolean dot_for_dot,gint * popup_width,gint * popup_height)
name|gimp_image_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|>
name|width
operator|||
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|>
name|height
condition|)
block|{
name|gboolean
name|scaling_up
decl_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|,
name|width
operator|*
literal|2
argument_list|,
name|height
operator|*
literal|2
argument_list|,
name|dot_for_dot
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|popup_width
argument_list|,
name|popup_height
argument_list|,
operator|&
name|scaling_up
argument_list|)
expr_stmt|;
if|if
condition|(
name|scaling_up
condition|)
block|{
operator|*
name|popup_width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
operator|*
name|popup_height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_image_get_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_image_get_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|image
operator|->
name|preview
operator|&&
name|image
operator|->
name|preview
operator|->
name|width
operator|==
name|width
operator|&&
name|image
operator|->
name|preview
operator|->
name|height
operator|==
name|height
condition|)
block|{
comment|/*  The easy way  */
return|return
name|image
operator|->
name|preview
return|;
block|}
else|else
block|{
comment|/*  The hard way  */
if|if
condition|(
name|image
operator|->
name|preview
condition|)
name|temp_buf_free
argument_list|(
name|image
operator|->
name|preview
argument_list|)
expr_stmt|;
name|image
operator|->
name|preview
operator|=
name|gimp_image_get_new_preview
argument_list|(
name|viewable
argument_list|,
name|context
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
return|return
name|image
operator|->
name|preview
return|;
block|}
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_image_get_new_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_image_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|TempBuf
modifier|*
name|buf
decl_stmt|;
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|gdouble
name|scale_x
decl_stmt|;
name|gdouble
name|scale_y
decl_stmt|;
name|gint
name|level
decl_stmt|;
name|gboolean
name|is_premult
decl_stmt|;
name|scale_x
operator|=
operator|(
name|gdouble
operator|)
name|width
operator|/
operator|(
name|gdouble
operator|)
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|scale_y
operator|=
operator|(
name|gdouble
operator|)
name|height
operator|/
operator|(
name|gdouble
operator|)
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|level
operator|=
name|gimp_projection_get_level
argument_list|(
name|image
operator|->
name|projection
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|)
expr_stmt|;
name|tiles
operator|=
name|gimp_projection_get_tiles_at_level
argument_list|(
name|image
operator|->
name|projection
argument_list|,
name|level
argument_list|,
operator|&
name|is_premult
argument_list|)
expr_stmt|;
name|buf
operator|=
name|tile_manager_get_preview
argument_list|(
name|tiles
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
comment|/* FIXME: We could avoid this if the view renderer and all other    *        preview code would know how to deal with pre-multiply alpha.    */
if|if
condition|(
name|is_premult
condition|)
name|temp_buf_demultiply
argument_list|(
name|buf
argument_list|)
expr_stmt|;
return|return
name|buf
return|;
block|}
end_function

end_unit

