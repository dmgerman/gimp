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
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager-crop.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
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
file|"gimpselection.h"
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
specifier|const
name|GimpBuffer
modifier|*
name|gimp_edit_extract
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|cut_pixels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_edit_fill_internal
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
specifier|const
name|GimpBuffer
modifier|*
DECL|function|gimp_edit_cut (GimpImage * gimage,GimpDrawable * drawable,GimpContext * context)
name|gimp_edit_cut
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_edit_extract
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|GimpBuffer
modifier|*
DECL|function|gimp_edit_copy (GimpImage * gimage,GimpDrawable * drawable,GimpContext * context)
name|gimp_edit_copy
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_edit_extract
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_edit_paste (GimpImage * gimage,GimpDrawable * drawable,GimpBuffer * paste,gboolean paste_into,gint viewport_x,gint viewport_y,gint viewport_width,gint viewport_height)
name|gimp_edit_paste
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|GimpImageType
name|type
decl_stmt|;
name|gint
name|center_x
decl_stmt|;
name|gint
name|center_y
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
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
name|type
operator|=
name|gimp_drawable_type_with_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
else|else
name|type
operator|=
name|gimp_image_base_type_with_alpha
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new_from_tiles
argument_list|(
name|paste
operator|->
name|tiles
argument_list|,
name|gimage
argument_list|,
name|type
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
comment|/*  Start a group undo  */
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"Paste"
argument_list|)
argument_list|)
expr_stmt|;
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
name|gimp_item_offsets
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
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
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
name|viewport_width
operator|>
literal|0
operator|&&
name|viewport_height
operator|>
literal|0
operator|&&
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
name|center_x
operator|=
name|paste_x
operator|+
name|paste_width
operator|/
literal|2
expr_stmt|;
name|center_y
operator|=
name|paste_y
operator|+
name|paste_height
operator|/
literal|2
expr_stmt|;
block|}
else|else
block|{
name|center_x
operator|=
name|off_x
operator|+
operator|(
name|x1
operator|+
name|x2
operator|)
operator|/
literal|2
expr_stmt|;
name|center_y
operator|=
name|off_y
operator|+
operator|(
name|y1
operator|+
name|y2
operator|)
operator|/
literal|2
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
name|viewport_height
operator|>
literal|0
condition|)
block|{
comment|/*  if we got a viewport set the offsets to the center of the viewport  */
name|center_x
operator|=
name|viewport_x
operator|+
name|viewport_width
operator|/
literal|2
expr_stmt|;
name|center_y
operator|=
name|viewport_y
operator|+
name|viewport_height
operator|/
literal|2
expr_stmt|;
block|}
else|else
block|{
comment|/*  otherwise the offsets to the center of the image  */
name|center_x
operator|=
name|gimage
operator|->
name|width
operator|/
literal|2
expr_stmt|;
name|center_y
operator|=
name|gimage
operator|->
name|height
operator|/
literal|2
expr_stmt|;
block|}
name|width
operator|=
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|offset_x
operator|=
name|center_x
operator|-
name|width
operator|/
literal|2
expr_stmt|;
name|offset_y
operator|=
name|center_y
operator|-
name|height
operator|/
literal|2
expr_stmt|;
comment|/*  Ensure that the pasted layer is always within the image, if it    *  fits and aligned at top left if it doesn't. (See bug #142944).    */
name|offset_x
operator|=
name|MIN
argument_list|(
name|offset_x
argument_list|,
name|gimage
operator|->
name|width
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
name|gimage
operator|->
name|height
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
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|=
name|offset_x
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
operator|=
name|offset_y
expr_stmt|;
comment|/*  If there is a selection mask clear it--    *  this might not always be desired, but in general,    *  it seems like the correct behavior.    */
if|if
condition|(
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
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
name|gimage
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
name|gimage
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  end the group undo  */
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_edit_paste_as_new (Gimp * gimp,GimpImage * invoke,GimpBuffer * paste)
name|gimp_edit_paste_as_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|invoke
parameter_list|,
name|GimpBuffer
modifier|*
name|paste
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|invoke
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|invoke
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
comment|/*  create a new image  (always of type GIMP_RGB)  */
name|gimage
operator|=
name|gimp_create_image
argument_list|(
name|gimp
argument_list|,
name|gimp_buffer_get_width
argument_list|(
name|paste
argument_list|)
argument_list|,
name|gimp_buffer_get_height
argument_list|(
name|paste
argument_list|)
argument_list|,
name|GIMP_RGB
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|invoke
condition|)
block|{
name|gimp_image_set_resolution
argument_list|(
name|gimage
argument_list|,
name|invoke
operator|->
name|xresolution
argument_list|,
name|invoke
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|gimage
argument_list|,
name|invoke
operator|->
name|unit
argument_list|)
expr_stmt|;
block|}
name|layer
operator|=
name|gimp_layer_new_from_tiles
argument_list|(
name|paste
operator|->
name|tiles
argument_list|,
name|gimage
argument_list|,
name|gimp_image_base_type_with_alpha
argument_list|(
name|gimage
argument_list|)
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
block|{
name|g_object_unref
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|gimp_image_add_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gimp
argument_list|,
name|gimage
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|gimage
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_edit_clear (GimpImage * gimage,GimpDrawable * drawable,GimpContext * context)
name|gimp_edit_clear
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
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
return|return
name|gimp_edit_fill_internal
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|GIMP_TRANSPARENT_FILL
argument_list|,
name|_
argument_list|(
literal|"Clear"
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_edit_fill (GimpImage * gimage,GimpDrawable * drawable,GimpContext * context,GimpFillType fill_type)
name|gimp_edit_fill
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|undo_desc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
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
switch|switch
condition|(
name|fill_type
condition|)
block|{
case|case
name|GIMP_FOREGROUND_FILL
case|:
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with FG Color"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_BACKGROUND_FILL
case|:
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with BG Color"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_WHITE_FILL
case|:
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with White"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSPARENT_FILL
case|:
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with Transparency"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PATTERN_FILL
case|:
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with Pattern"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_NO_FILL
case|:
return|return
name|TRUE
return|;
comment|/*  nothing to do, but the fill succeded  */
default|default:
name|g_warning
argument_list|(
literal|"%s: unknown fill type"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
name|fill_type
operator|=
name|GIMP_BACKGROUND_FILL
expr_stmt|;
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with BG Color"
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|gimp_edit_fill_internal
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|fill_type
argument_list|,
name|undo_desc
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|const
name|GimpBuffer
modifier|*
DECL|function|gimp_edit_extract (GimpImage * gimage,GimpDrawable * drawable,GimpContext * context,gboolean cut_pixels)
name|gimp_edit_extract
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|cut_pixels
parameter_list|)
block|{
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|gboolean
name|empty
decl_stmt|;
comment|/*  See if the gimage mask is empty  */
name|empty
operator|=
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cut_pixels
condition|)
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_CUT
argument_list|,
name|_
argument_list|(
literal|"Cut"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Cut/copy the mask portion from the gimage  */
name|tiles
operator|=
name|gimp_selection_extract
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|cut_pixels
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|cut_pixels
condition|)
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  Only crop if the gimage mask wasn't empty  */
if|if
condition|(
name|tiles
operator|&&
operator|!
name|empty
condition|)
block|{
name|TileManager
modifier|*
name|crop
init|=
name|tile_manager_crop
argument_list|(
name|tiles
argument_list|,
literal|0
argument_list|)
decl_stmt|;
if|if
condition|(
name|crop
operator|!=
name|tiles
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
name|tiles
operator|=
name|crop
expr_stmt|;
block|}
block|}
if|if
condition|(
name|tiles
condition|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
name|gimp_buffer_new
argument_list|(
name|tiles
argument_list|,
literal|"Global Buffer"
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|gimp_set_global_buffer
argument_list|(
name|gimage
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
name|gimage
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
specifier|static
name|gboolean
DECL|function|gimp_edit_fill_internal (GimpImage * gimage,GimpDrawable * drawable,GimpContext * context,GimpFillType fill_type,const gchar * undo_desc)
name|gimp_edit_fill_internal
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|TileManager
modifier|*
name|buf_tiles
decl_stmt|;
name|PixelRegion
name|bufPR
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
name|tiles_bytes
decl_stmt|;
name|guchar
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|TempBuf
modifier|*
name|pat_buf
init|=
name|NULL
decl_stmt|;
name|gboolean
name|new_buf
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
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
name|x1
operator|==
name|x2
operator|||
name|y1
operator|==
name|y2
condition|)
return|return
name|TRUE
return|;
comment|/*  nothing to do, but the fill succeded  */
name|tiles_bytes
operator|=
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|fill_type
condition|)
block|{
case|case
name|GIMP_FOREGROUND_FILL
case|:
name|gimp_image_get_foreground
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|col
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_BACKGROUND_FILL
case|:
case|case
name|GIMP_TRANSPARENT_FILL
case|:
name|gimp_image_get_background
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|col
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_WHITE_FILL
case|:
block|{
name|guchar
name|tmp_col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|tmp_col
index|[
name|RED_PIX
index|]
operator|=
literal|255
expr_stmt|;
name|tmp_col
index|[
name|GREEN_PIX
index|]
operator|=
literal|255
expr_stmt|;
name|tmp_col
index|[
name|BLUE_PIX
index|]
operator|=
literal|255
expr_stmt|;
name|gimp_image_transform_color
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|,
name|GIMP_RGB
argument_list|,
name|tmp_col
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PATTERN_FILL
case|:
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|pat_buf
operator|=
name|gimp_image_transform_temp_buf
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|pattern
operator|->
name|mask
argument_list|,
operator|&
name|new_buf
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
operator|&&
operator|(
name|pat_buf
operator|->
name|bytes
operator|==
literal|2
operator|||
name|pat_buf
operator|->
name|bytes
operator|==
literal|4
operator|)
condition|)
name|tiles_bytes
operator|++
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_NO_FILL
case|:
return|return
name|TRUE
return|;
comment|/*  nothing to do, but the fill succeded  */
block|}
name|buf_tiles
operator|=
name|tile_manager_new
argument_list|(
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|tiles_bytes
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|bufPR
argument_list|,
name|buf_tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pat_buf
condition|)
block|{
name|pattern_region
argument_list|(
operator|&
name|bufPR
argument_list|,
name|NULL
argument_list|,
name|pat_buf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_buf
condition|)
name|temp_buf_free
argument_list|(
name|pat_buf
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|col
index|[
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|bufPR
argument_list|,
name|col
argument_list|)
expr_stmt|;
block|}
name|pixel_region_init
argument_list|(
operator|&
name|bufPR
argument_list|,
name|buf_tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_region
argument_list|(
name|drawable
argument_list|,
operator|&
name|bufPR
argument_list|,
name|TRUE
argument_list|,
name|undo_desc
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
operator|(
name|fill_type
operator|==
name|GIMP_TRANSPARENT_FILL
operator|)
condition|?
name|GIMP_ERASE_MODE
else|:
name|GIMP_NORMAL_MODE
argument_list|,
name|NULL
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|buf_tiles
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

