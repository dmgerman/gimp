begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
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
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-edit.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawableundo.h"
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
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer-new.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"gimpselection.h"
end_include

begin_include
include|#
directive|include
file|"gimptempbuf.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function protypes  */
end_comment

begin_function_decl
specifier|static
name|GimpBuffer
modifier|*
name|gimp_edit_extract
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|cut_pixels
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpBuffer
modifier|*
DECL|function|gimp_edit_cut (GimpImage * image,GimpDrawable * drawable,GimpContext * context,GError ** error)
name|gimp_edit_cut
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_edit_extract
argument_list|(
name|image
argument_list|,
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|context
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
block|{
name|gimp_set_global_buffer
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|image
operator|->
name|gimp
operator|->
name|global_buffer
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpBuffer
modifier|*
DECL|function|gimp_edit_copy (GimpImage * image,GimpDrawable * drawable,GimpContext * context,GError ** error)
name|gimp_edit_copy
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_edit_extract
argument_list|(
name|image
argument_list|,
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|context
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
block|{
name|gimp_set_global_buffer
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|image
operator|->
name|gimp
operator|->
name|global_buffer
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpBuffer
modifier|*
DECL|function|gimp_edit_copy_visible (GimpImage * image,GimpContext * context,GError ** error)
name|gimp_edit_copy_visible
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_edit_extract
argument_list|(
name|image
argument_list|,
name|GIMP_PICKABLE
argument_list|(
name|image
argument_list|)
argument_list|,
name|context
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
block|{
name|gimp_set_global_buffer
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|image
operator|->
name|gimp
operator|->
name|global_buffer
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_edit_paste (GimpImage * image,GimpDrawable * drawable,GimpBuffer * paste,gboolean paste_into,gint viewport_x,gint viewport_y,gint viewport_width,gint viewport_height)
name|gimp_edit_paste
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpBuffer
modifier|*
name|paste
parameter_list|,
name|gboolean
name|paste_into
parameter_list|,
name|gint
name|viewport_x
parameter_list|,
name|gint
name|viewport_y
parameter_list|,
name|gint
name|viewport_width
parameter_list|,
name|gint
name|viewport_height
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|image_width
decl_stmt|;
name|gint
name|image_height
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gboolean
name|clamp_to_image
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|==
name|NULL
operator|||
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|==
name|NULL
operator|||
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BUFFER
argument_list|(
name|paste
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Make a new layer: if drawable == NULL,    *  user is pasting into an empty image.    */
if|if
condition|(
name|drawable
condition|)
name|format
operator|=
name|gimp_drawable_get_format_with_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
else|else
name|format
operator|=
name|gimp_image_get_layer_format
argument_list|(
name|image
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new_from_buffer
argument_list|(
name|paste
argument_list|,
name|image
argument_list|,
name|format
argument_list|,
name|_
argument_list|(
literal|"Pasted Layer"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|layer
condition|)
return|return
name|NULL
return|;
name|image_width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|image_height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewport_width
operator|==
name|image_width
operator|&&
name|viewport_height
operator|==
name|image_height
condition|)
block|{
comment|/* if the whole image is visible, act as if there was no viewport */
name|viewport_x
operator|=
literal|0
expr_stmt|;
name|viewport_y
operator|=
literal|0
expr_stmt|;
name|viewport_width
operator|=
literal|0
expr_stmt|;
name|viewport_height
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|drawable
condition|)
block|{
comment|/*  if pasting to a drawable  */
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|paste_x
decl_stmt|,
name|paste_y
decl_stmt|;
name|gint
name|paste_width
decl_stmt|,
name|paste_height
decl_stmt|;
name|gboolean
name|have_mask
decl_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|have_mask
operator|=
name|gimp_item_mask_bounds
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|have_mask
operator|&&
comment|/* if we have no mask */
name|viewport_width
operator|>
literal|0
operator|&&
comment|/* and we have a viewport */
name|viewport_height
operator|>
literal|0
operator|&&
operator|(
name|width
operator|<
operator|(
name|x2
operator|-
name|x1
operator|)
operator|||
comment|/* and the paste is smaller than the target */
name|height
operator|<
operator|(
name|y2
operator|-
name|y1
operator|)
operator|)
operator|&&
comment|/* and the viewport intersects with the target */
name|gimp_rectangle_intersect
argument_list|(
name|viewport_x
argument_list|,
name|viewport_y
argument_list|,
name|viewport_width
argument_list|,
name|viewport_height
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
operator|&
name|paste_x
argument_list|,
operator|&
name|paste_y
argument_list|,
operator|&
name|paste_width
argument_list|,
operator|&
name|paste_height
argument_list|)
condition|)
block|{
comment|/*  center on the viewport  */
name|offset_x
operator|=
name|paste_x
operator|+
operator|(
name|paste_width
operator|-
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|offset_y
operator|=
name|paste_y
operator|+
operator|(
name|paste_height
operator|-
name|height
operator|)
operator|/
literal|2
expr_stmt|;
block|}
else|else
block|{
comment|/*  otherwise center on the target  */
name|offset_x
operator|=
name|off_x
operator|+
operator|(
operator|(
name|x1
operator|+
name|x2
operator|)
operator|-
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|offset_y
operator|=
name|off_y
operator|+
operator|(
operator|(
name|y1
operator|+
name|y2
operator|)
operator|-
name|height
operator|)
operator|/
literal|2
expr_stmt|;
comment|/*  and keep it that way  */
name|clamp_to_image
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|viewport_width
operator|>
literal|0
operator|&&
comment|/* if we have a viewport */
name|viewport_height
operator|>
literal|0
operator|&&
operator|(
name|width
operator|<
name|image_width
operator|||
comment|/* and the paste is       */
name|height
operator|<
name|image_height
operator|)
condition|)
comment|/* smaller than the image */
block|{
comment|/*  center on the viewport  */
name|offset_x
operator|=
name|viewport_x
operator|+
operator|(
name|viewport_width
operator|-
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|offset_y
operator|=
name|viewport_y
operator|+
operator|(
name|viewport_height
operator|-
name|height
operator|)
operator|/
literal|2
expr_stmt|;
block|}
else|else
block|{
comment|/*  otherwise center on the image  */
name|offset_x
operator|=
operator|(
name|image_width
operator|-
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|offset_y
operator|=
operator|(
name|image_height
operator|-
name|height
operator|)
operator|/
literal|2
expr_stmt|;
comment|/*  and keep it that way  */
name|clamp_to_image
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|clamp_to_image
condition|)
block|{
comment|/*  Ensure that the pasted layer is always within the image, if it        *  fits and aligned at top left if it doesn't. (See bug #142944).        */
name|offset_x
operator|=
name|MIN
argument_list|(
name|offset_x
argument_list|,
name|image_width
operator|-
name|width
argument_list|)
expr_stmt|;
name|offset_y
operator|=
name|MIN
argument_list|(
name|offset_y
argument_list|,
name|image_height
operator|-
name|height
argument_list|)
expr_stmt|;
name|offset_x
operator|=
name|MAX
argument_list|(
name|offset_x
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|offset_y
operator|=
name|MAX
argument_list|(
name|offset_y
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gimp_item_set_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
comment|/*  Start a group undo  */
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Paste"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  If there is a selection mask clear it--    *  this might not always be desired, but in general,    *  it seems like the correct behavior.    */
if|if
condition|(
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
operator|&&
operator|!
name|paste_into
condition|)
name|gimp_channel_clear
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  if there's a drawable, add a new floating selection  */
if|if
condition|(
name|drawable
condition|)
name|floating_sel_attach
argument_list|(
name|layer
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
else|else
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  end the group undo  */
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_edit_named_cut (GimpImage * image,const gchar * name,GimpDrawable * drawable,GimpContext * context,GError ** error)
name|gimp_edit_named_cut
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_edit_extract
argument_list|(
name|image
argument_list|,
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|context
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
block|{
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|named_buffers
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|gimp_object_get_name
argument_list|(
name|buffer
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_edit_named_copy (GimpImage * image,const gchar * name,GimpDrawable * drawable,GimpContext * context,GError ** error)
name|gimp_edit_named_copy
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_edit_extract
argument_list|(
name|image
argument_list|,
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|context
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
block|{
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|named_buffers
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|gimp_object_get_name
argument_list|(
name|buffer
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_edit_named_copy_visible (GimpImage * image,const gchar * name,GimpContext * context,GError ** error)
name|gimp_edit_named_copy_visible
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_edit_extract
argument_list|(
name|image
argument_list|,
name|GIMP_PICKABLE
argument_list|(
name|image
argument_list|)
argument_list|,
name|context
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
block|{
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|named_buffers
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|gimp_object_get_name
argument_list|(
name|buffer
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_edit_clear (GimpImage * image,GimpDrawable * drawable,GimpContext * context)
name|gimp_edit_clear
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpFillOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
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
name|options
operator|=
name|gimp_fill_options_new
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|gimp_fill_options_set_by_fill_type
argument_list|(
name|options
argument_list|,
name|context
argument_list|,
name|GIMP_FILL_TRANSPARENT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|gimp_fill_options_set_by_fill_type
argument_list|(
name|options
argument_list|,
name|context
argument_list|,
name|GIMP_FILL_BACKGROUND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_edit_fill
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|options
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Clear"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_edit_fill (GimpImage * image,GimpDrawable * drawable,GimpFillOptions * options,const gchar * undo_desc)
name|gimp_edit_fill
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|GimpPattern
modifier|*
name|pattern
init|=
name|NULL
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_mask_intersect
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
return|return;
comment|/*  nothing to do, but the fill succeeded  */
switch|switch
condition|(
name|gimp_fill_options_get_style
argument_list|(
name|options
argument_list|)
condition|)
block|{
case|case
name|GIMP_FILL_STYLE_SOLID
case|:
name|gimp_context_get_foreground
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_FILL_STYLE_PATTERN
case|:
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|pattern
operator|&&
name|babl_format_has_alpha
argument_list|(
name|gimp_temp_buf_get_format
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
argument_list|)
operator|&&
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|format
operator|=
name|gimp_drawable_get_format_with_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|format
operator|=
name|gimp_drawable_get_format
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
name|dest_buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|format
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern
condition|)
block|{
name|GeglBuffer
modifier|*
name|src_buffer
init|=
name|gimp_pattern_create_buffer
argument_list|(
name|pattern
argument_list|)
decl_stmt|;
name|gegl_buffer_set_pattern
argument_list|(
name|dest_buffer
argument_list|,
name|NULL
argument_list|,
name|src_buffer
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GeglColor
modifier|*
name|gegl_color
init|=
name|gimp_gegl_color_new
argument_list|(
operator|&
name|color
argument_list|)
decl_stmt|;
name|gegl_buffer_set_color
argument_list|(
name|dest_buffer
argument_list|,
name|NULL
argument_list|,
name|gegl_color
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gegl_color
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|undo_desc
condition|)
name|undo_desc
operator|=
name|gimp_fill_options_get_undo_desc
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_buffer
argument_list|(
name|drawable
argument_list|,
name|dest_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|undo_desc
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
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
name|gboolean
DECL|function|gimp_edit_fade (GimpImage * image,GimpContext * context)
name|gimp_edit_fade
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpDrawableUndo
modifier|*
name|undo
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|undo
operator|=
name|GIMP_DRAWABLE_UNDO
argument_list|(
name|gimp_image_undo_get_fadeable
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|&&
name|undo
operator|->
name|applied_buffer
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|undo
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|g_object_ref
argument_list|(
name|undo
operator|->
name|applied_buffer
argument_list|)
expr_stmt|;
name|gimp_image_undo
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_buffer
argument_list|(
name|drawable
argument_list|,
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|undo
operator|->
name|buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|undo
operator|->
name|buffer
argument_list|)
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|gimp_object_get_name
argument_list|(
name|undo
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|undo
operator|->
name|x
argument_list|,
name|undo
operator|->
name|y
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|undo
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpBuffer
modifier|*
DECL|function|gimp_edit_extract (GimpImage * image,GimpPickable * pickable,GimpContext * context,gboolean cut_pixels,GError ** error)
name|gimp_edit_extract
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|cut_pixels
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
if|if
condition|(
name|cut_pixels
condition|)
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_CUT
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Cut"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Cut/copy the mask portion from the image  */
name|buffer
operator|=
name|gimp_selection_extract
argument_list|(
name|GIMP_SELECTION
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|,
name|pickable
argument_list|,
name|context
argument_list|,
name|cut_pixels
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|cut_pixels
condition|)
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
block|{
name|GimpBuffer
modifier|*
name|gimp_buffer
init|=
name|gimp_buffer_new
argument_list|(
name|buffer
argument_list|,
name|_
argument_list|(
literal|"Global Buffer"
argument_list|)
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_COLOR_MANAGED
argument_list|(
name|pickable
argument_list|)
condition|)
block|{
name|GimpColorProfile
modifier|*
name|profile
init|=
name|gimp_color_managed_get_color_profile
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|pickable
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|profile
condition|)
name|gimp_buffer_set_color_profile
argument_list|(
name|gimp_buffer
argument_list|,
name|profile
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_buffer
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

