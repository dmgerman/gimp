begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<strings.h>
end_include

begin_include
include|#
directive|include
file|"gimpdrawableP.h"
end_include

begin_include
include|#
directive|include
file|"gimpsignal.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasite.h"
end_include

begin_include
include|#
directive|include
file|"parasitelist.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/parasite.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_enum
DECL|enum|__anon2a56ef830103
enum|enum
block|{
DECL|enumerator|INVALIDATE_PREVIEW
name|INVALIDATE_PREVIEW
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_drawable_class_init
parameter_list|(
name|GimpDrawableClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_init
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_drawable_signals
specifier|static
name|guint
name|gimp_drawable_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDrawableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_drawable_get_type ()
name|gimp_drawable_get_type
parameter_list|()
block|{
specifier|static
name|GtkType
name|type
decl_stmt|;
name|GIMP_TYPE_INIT
argument_list|(
name|type
argument_list|,
name|GimpDrawable
argument_list|,
name|GimpDrawableClass
argument_list|,
name|gimp_drawable_init
argument_list|,
name|gimp_drawable_class_init
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
expr_stmt|;
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_class_init (GimpDrawableClass * class)
name|gimp_drawable_class_init
parameter_list|(
name|GimpDrawableClass
modifier|*
name|class
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkType
name|type
init|=
name|GIMP_TYPE_DRAWABLE
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|class
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|)
expr_stmt|;
name|gimp_drawable_signals
index|[
name|INVALIDATE_PREVIEW
index|]
operator|=
name|gimp_signal_new
argument_list|(
literal|"invalidate_pr"
argument_list|,
name|GTK_RUN_LAST
argument_list|,
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpDrawableClass
argument_list|,
name|invalidate_preview
argument_list|)
argument_list|,
name|gimp_sigtype_void
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|gimp_drawable_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_drawable_destroy
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  *  Static variables  */
end_comment

begin_decl_stmt
DECL|variable|global_drawable_ID
name|int
name|global_drawable_ID
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_drawable_table
specifier|static
name|GHashTable
modifier|*
name|gimp_drawable_table
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**************************/
end_comment

begin_comment
comment|/*  Function definitions  */
end_comment

begin_function
name|GimpDrawable
modifier|*
DECL|function|gimp_drawable_get_ID (int drawable_id)
name|gimp_drawable_get_ID
parameter_list|(
name|int
name|drawable_id
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_table
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
return|return
operator|(
name|GimpDrawable
operator|*
operator|)
name|g_hash_table_lookup
argument_list|(
name|gimp_drawable_table
argument_list|,
operator|(
name|gpointer
operator|)
name|drawable_id
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_merge_shadow (GimpDrawable * drawable,int undo)
name|gimp_drawable_merge_shadow
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|undo
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|PixelRegion
name|shadowPR
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return;
comment|/*  A useful optimization here is to limit the update to the    *  extents of the selection mask, as it cannot extend beyond    *  them.    */
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
name|pixel_region_init
argument_list|(
operator|&
name|shadowPR
argument_list|,
name|gimage
operator|->
name|shadow
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimage_apply_image
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
operator|&
name|shadowPR
argument_list|,
name|undo
argument_list|,
name|OPAQUE_OPACITY
argument_list|,
name|REPLACE_MODE
argument_list|,
name|NULL
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_fill (GimpDrawable * drawable,guchar r,guchar g,guchar b,guchar a)
name|gimp_drawable_fill
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|,
name|guchar
name|a
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|guchar
name|c
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|guchar
name|i
decl_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
case|case
name|RGB_GIMAGE
case|:
case|case
name|RGBA_GIMAGE
case|:
name|c
index|[
name|RED_PIX
index|]
operator|=
name|r
expr_stmt|;
name|c
index|[
name|GREEN_PIX
index|]
operator|=
name|g
expr_stmt|;
name|c
index|[
name|BLUE_PIX
index|]
operator|=
name|b
expr_stmt|;
if|if
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|RGBA_GIMAGE
condition|)
name|c
index|[
name|ALPHA_PIX
index|]
operator|=
name|a
expr_stmt|;
break|break;
case|case
name|GRAY_GIMAGE
case|:
case|case
name|GRAYA_GIMAGE
case|:
name|c
index|[
name|GRAY_PIX
index|]
operator|=
name|r
expr_stmt|;
if|if
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|GRAYA_GIMAGE
condition|)
name|c
index|[
name|ALPHA_G_PIX
index|]
operator|=
name|a
expr_stmt|;
break|break;
case|case
name|INDEXED_GIMAGE
case|:
case|case
name|INDEXEDA_GIMAGE
case|:
name|c
index|[
name|RED_PIX
index|]
operator|=
name|r
expr_stmt|;
name|c
index|[
name|GREEN_PIX
index|]
operator|=
name|g
expr_stmt|;
name|c
index|[
name|BLUE_PIX
index|]
operator|=
name|b
expr_stmt|;
name|gimage_transform_color
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|c
argument_list|,
operator|&
name|i
argument_list|,
name|RGB
argument_list|)
expr_stmt|;
name|c
index|[
name|INDEXED_PIX
index|]
operator|=
name|i
expr_stmt|;
if|if
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXEDA_GIMAGE
condition|)
name|c
index|[
name|ALPHA_I_PIX
index|]
operator|=
name|a
expr_stmt|;
break|break;
default|default:
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Can't fill unknown image type."
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|destPR
argument_list|,
name|c
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_mask_bounds (GimpDrawable * drawable,int * x1,int * y1,int * x2,int * y2)
name|gimp_drawable_mask_bounds
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
modifier|*
name|x1
parameter_list|,
name|int
modifier|*
name|y1
parameter_list|,
name|int
modifier|*
name|x2
parameter_list|,
name|int
modifier|*
name|y2
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|gimage_mask_bounds
argument_list|(
name|gimage
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
condition|)
block|{
name|gimp_drawable_offsets
argument_list|(
name|drawable
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
operator|*
name|x1
operator|=
name|CLAMP
argument_list|(
operator|*
name|x1
operator|-
name|off_x
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|y1
operator|=
name|CLAMP
argument_list|(
operator|*
name|y1
operator|-
name|off_y
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|x2
operator|=
name|CLAMP
argument_list|(
operator|*
name|x2
operator|-
name|off_x
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|y2
operator|=
name|CLAMP
argument_list|(
operator|*
name|y2
operator|-
name|off_y
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
block|{
operator|*
name|x2
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
operator|*
name|y2
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_invalidate_preview (GimpDrawable * drawable)
name|gimp_drawable_invalidate_preview
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
name|drawable
operator|->
name|preview_valid
operator|=
name|FALSE
expr_stmt|;
if|#
directive|if
literal|0
block|gtk_signal_emit (GTK_OBJECT(drawable), gimp_drawable_signals[INVALIDATE_PREVIEW]);
endif|#
directive|endif
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|gimage
operator|->
name|comp_preview_valid
index|[
literal|0
index|]
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|->
name|comp_preview_valid
index|[
literal|1
index|]
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|->
name|comp_preview_valid
index|[
literal|2
index|]
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_dirty (GimpDrawable * drawable)
name|gimp_drawable_dirty
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|dirty
operator|=
operator|(
name|drawable
operator|->
name|dirty
operator|<
literal|0
operator|)
condition|?
literal|2
else|:
name|drawable
operator|->
name|dirty
operator|+
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_clean (GimpDrawable * drawable)
name|gimp_drawable_clean
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|dirty
operator|=
operator|(
name|drawable
operator|->
name|dirty
operator|<=
literal|0
operator|)
condition|?
literal|0
else|:
name|drawable
operator|->
name|dirty
operator|-
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_drawable_gimage (GimpDrawable * drawable)
name|gimp_drawable_gimage
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|g_assert
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|drawable
operator|->
name|gimage
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_set_gimage (GimpDrawable * drawable,GimpImage * gimage)
name|gimp_drawable_set_gimage
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_assert
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|==
name|NULL
condition|)
name|drawable
operator|->
name|tattoo
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|drawable
operator|->
name|tattoo
operator|==
literal|0
operator|||
name|drawable
operator|->
name|gimage
operator|!=
name|gimage
condition|)
name|drawable
operator|->
name|tattoo
operator|=
name|gimp_image_get_new_tattoo
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_type (GimpDrawable * drawable)
name|gimp_drawable_type
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|type
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_has_alpha (GimpDrawable * drawable)
name|gimp_drawable_has_alpha
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|has_alpha
return|;
else|else
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_visible (GimpDrawable * drawable)
name|gimp_drawable_visible
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
return|return
name|drawable
operator|->
name|visible
return|;
block|}
end_function

begin_function
name|char
modifier|*
DECL|function|gimp_drawable_get_name (GimpDrawable * drawable)
name|gimp_drawable_get_name
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
return|return
name|drawable
operator|->
name|name
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_set_name (GimpDrawable * drawable,char * name)
name|gimp_drawable_set_name
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|char
modifier|*
name|name
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|,
modifier|*
name|listb
decl_stmt|,
modifier|*
name|base_list
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawableb
decl_stmt|;
name|int
name|number
init|=
literal|1
decl_stmt|;
name|char
modifier|*
name|newname
decl_stmt|;
name|char
modifier|*
name|ext
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|drawable
operator|->
name|name
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|gimage
operator|==
literal|0
operator|||
name|drawable
operator|->
name|gimage
operator|->
name|layers
operator|==
literal|0
condition|)
block|{
comment|/* no other layers to check name against */
name|drawable
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
name|base_list
operator|=
name|drawable
operator|->
name|gimage
operator|->
name|layers
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|drawable
argument_list|)
condition|)
name|base_list
operator|=
name|drawable
operator|->
name|gimage
operator|->
name|channels
expr_stmt|;
else|else
name|base_list
operator|=
name|NULL
expr_stmt|;
name|list
operator|=
name|base_list
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|drawableb
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|!=
name|drawableb
operator|&&
name|strcmp
argument_list|(
name|name
argument_list|,
name|gimp_drawable_get_name
argument_list|(
name|drawableb
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* names conflict */
name|newname
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|10
argument_list|)
expr_stmt|;
comment|/* if this aint enough  						 yer screwed */
name|strcpy
argument_list|(
name|newname
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|ext
operator|=
name|strrchr
argument_list|(
name|newname
argument_list|,
literal|'#'
argument_list|)
operator|)
condition|)
block|{
name|number
operator|=
name|atoi
argument_list|(
name|ext
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|&
name|ext
index|[
call|(
name|int
call|)
argument_list|(
name|log10
argument_list|(
name|number
argument_list|)
operator|+
literal|1
argument_list|)
index|]
operator|!=
operator|&
name|newname
index|[
name|strlen
argument_list|(
name|newname
argument_list|)
operator|-
literal|1
index|]
condition|)
block|{
name|number
operator|=
literal|1
expr_stmt|;
name|ext
operator|=
operator|&
name|newname
index|[
name|strlen
argument_list|(
name|newname
argument_list|)
index|]
expr_stmt|;
block|}
block|}
else|else
block|{
name|number
operator|=
literal|1
expr_stmt|;
name|ext
operator|=
operator|&
name|newname
index|[
name|strlen
argument_list|(
name|newname
argument_list|)
index|]
expr_stmt|;
block|}
name|sprintf
argument_list|(
name|ext
argument_list|,
literal|"#%d"
argument_list|,
name|number
operator|+
literal|1
argument_list|)
expr_stmt|;
name|listb
operator|=
name|base_list
expr_stmt|;
while|while
condition|(
name|listb
condition|)
comment|/* make sure the new name is unique */
block|{
name|drawableb
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|listb
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|!=
name|drawableb
operator|&&
name|strcmp
argument_list|(
name|newname
argument_list|,
name|gimp_drawable_get_name
argument_list|(
name|drawableb
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
name|number
operator|++
expr_stmt|;
name|sprintf
argument_list|(
name|ext
argument_list|,
literal|"#%d"
argument_list|,
name|number
operator|+
literal|1
argument_list|)
expr_stmt|;
name|listb
operator|=
name|base_list
expr_stmt|;
block|}
name|listb
operator|=
name|listb
operator|->
name|next
expr_stmt|;
block|}
name|drawable
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|newname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|newname
argument_list|)
expr_stmt|;
return|return;
block|}
name|list
operator|=
name|list
operator|->
name|next
expr_stmt|;
block|}
name|drawable
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Parasite
modifier|*
DECL|function|gimp_drawable_find_parasite (const GimpDrawable * drawable,const char * name)
name|gimp_drawable_find_parasite
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|char
modifier|*
name|name
parameter_list|)
block|{
return|return
name|parasite_list_find
argument_list|(
name|drawable
operator|->
name|parasites
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_attach_parasite (GimpDrawable * drawable,Parasite * parasite)
name|gimp_drawable_attach_parasite
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|Parasite
modifier|*
name|parasite
parameter_list|)
block|{
name|parasite_list_add
argument_list|(
name|drawable
operator|->
name|parasites
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite_is_persistent
argument_list|(
name|parasite
argument_list|)
condition|)
comment|/* make sure we can be saved */
name|gimp_image_dirty
argument_list|(
name|drawable
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite_has_flag
argument_list|(
name|parasite
argument_list|,
name|PARASITE_ATTACH_PARENT
argument_list|)
condition|)
block|{
name|parasite_shift_parent
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_image_attach_parasite
argument_list|(
name|drawable
operator|->
name|gimage
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|parasite_has_flag
argument_list|(
name|parasite
argument_list|,
name|PARASITE_ATTACH_GRANDPARENT
argument_list|)
condition|)
block|{
name|parasite_shift_parent
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|parasite_shift_parent
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_attach_parasite
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_detach_parasite (GimpDrawable * drawable,const char * parasite)
name|gimp_drawable_detach_parasite
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|char
modifier|*
name|parasite
parameter_list|)
block|{
name|Parasite
modifier|*
name|p
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|p
operator|=
name|parasite_list_find
argument_list|(
name|drawable
operator|->
name|parasites
argument_list|,
name|parasite
argument_list|)
operator|)
condition|)
return|return;
if|if
condition|(
name|parasite_is_persistent
argument_list|(
name|p
argument_list|)
condition|)
name|gimp_image_dirty
argument_list|(
name|drawable
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|parasite_list_remove
argument_list|(
name|drawable
operator|->
name|parasites
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Tattoo
DECL|function|gimp_drawable_get_tattoo (const GimpDrawable * drawable)
name|gimp_drawable_get_tattoo
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
return|return
name|drawable
operator|->
name|tattoo
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_type_with_alpha (GimpDrawable * drawable)
name|gimp_drawable_type_with_alpha
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|int
name|type
init|=
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|int
name|has_alpha
init|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
if|if
condition|(
name|has_alpha
condition|)
return|return
name|type
return|;
else|else
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|RGB_GIMAGE
case|:
return|return
name|RGBA_GIMAGE
return|;
break|break;
case|case
name|GRAY_GIMAGE
case|:
return|return
name|GRAYA_GIMAGE
return|;
break|break;
case|case
name|INDEXED_GIMAGE
case|:
return|return
name|INDEXEDA_GIMAGE
return|;
break|break;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_color (GimpDrawable * drawable)
name|gimp_drawable_color
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|RGBA_GIMAGE
operator|||
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|RGB_GIMAGE
condition|)
return|return
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_gray (GimpDrawable * drawable)
name|gimp_drawable_gray
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|GRAYA_GIMAGE
operator|||
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|GRAY_GIMAGE
condition|)
return|return
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_indexed (GimpDrawable * drawable)
name|gimp_drawable_indexed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXEDA_GIMAGE
operator|||
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXED_GIMAGE
condition|)
return|return
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|gimp_drawable_data (GimpDrawable * drawable)
name|gimp_drawable_data
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|tiles
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|gimp_drawable_shadow (GimpDrawable * drawable)
name|gimp_drawable_shadow
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|drawable
condition|)
return|return
name|gimage_shadow
argument_list|(
name|gimage
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|drawable
operator|->
name|bytes
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_bytes (GimpDrawable * drawable)
name|gimp_drawable_bytes
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|bytes
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_width (GimpDrawable * drawable)
name|gimp_drawable_width
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|width
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_drawable_height (GimpDrawable * drawable)
name|gimp_drawable_height
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
return|return
name|drawable
operator|->
name|height
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_offsets (GimpDrawable * drawable,int * off_x,int * off_y)
name|gimp_drawable_offsets
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
modifier|*
name|off_x
parameter_list|,
name|int
modifier|*
name|off_y
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
block|{
operator|*
name|off_x
operator|=
name|drawable
operator|->
name|offset_x
expr_stmt|;
operator|*
name|off_y
operator|=
name|drawable
operator|->
name|offset_y
expr_stmt|;
block|}
else|else
operator|*
name|off_x
operator|=
operator|*
name|off_y
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
name|unsigned
name|char
modifier|*
DECL|function|gimp_drawable_cmap (GimpDrawable * drawable)
name|gimp_drawable_cmap
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return
name|gimage
operator|->
name|cmap
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_deallocate (GimpDrawable * drawable)
name|gimp_drawable_deallocate
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
operator|->
name|tiles
condition|)
name|tile_manager_destroy
argument_list|(
name|drawable
operator|->
name|tiles
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_init (GimpDrawable * drawable)
name|gimp_drawable_init
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|drawable
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|tiles
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|visible
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|->
name|width
operator|=
name|drawable
operator|->
name|height
operator|=
literal|0
expr_stmt|;
name|drawable
operator|->
name|offset_x
operator|=
name|drawable
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
name|drawable
operator|->
name|bytes
operator|=
literal|0
expr_stmt|;
name|drawable
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|->
name|gimage
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|type
operator|=
operator|-
literal|1
expr_stmt|;
name|drawable
operator|->
name|has_alpha
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|->
name|preview
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|preview_valid
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|->
name|parasites
operator|=
name|parasite_list_new
argument_list|()
expr_stmt|;
name|drawable
operator|->
name|tattoo
operator|=
literal|0
expr_stmt|;
name|gimp_matrix_identity
argument_list|(
name|drawable
operator|->
name|transform
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|ID
operator|=
name|global_drawable_ID
operator|++
expr_stmt|;
if|if
condition|(
name|gimp_drawable_table
operator|==
name|NULL
condition|)
name|gimp_drawable_table
operator|=
name|g_hash_table_new
argument_list|(
name|g_direct_hash
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|gimp_drawable_table
argument_list|,
operator|(
name|gpointer
operator|)
name|drawable
operator|->
name|ID
argument_list|,
operator|(
name|gpointer
operator|)
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_destroy (GtkObject * object)
name|gimp_drawable_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|object
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_hash_table_remove
argument_list|(
name|gimp_drawable_table
argument_list|,
operator|(
name|gpointer
operator|)
name|drawable
operator|->
name|ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|drawable
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|tiles
condition|)
name|tile_manager_destroy
argument_list|(
name|drawable
operator|->
name|tiles
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|preview
condition|)
name|temp_buf_free
argument_list|(
name|drawable
operator|->
name|preview
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|parasites
condition|)
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|drawable
operator|->
name|parasites
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
operator|(
operator|*
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
operator|)
operator|(
name|object
operator|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_configure (GimpDrawable * drawable,GimpImage * gimage,int width,int height,int type,char * name)
name|gimp_drawable_configure
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|int
name|type
parameter_list|,
name|char
modifier|*
name|name
parameter_list|)
block|{
name|int
name|bpp
decl_stmt|;
name|int
name|alpha
decl_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
name|_
argument_list|(
literal|"unnamed"
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|RGB_GIMAGE
case|:
name|bpp
operator|=
literal|3
expr_stmt|;
name|alpha
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|GRAY_GIMAGE
case|:
name|bpp
operator|=
literal|1
expr_stmt|;
name|alpha
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|RGBA_GIMAGE
case|:
name|bpp
operator|=
literal|4
expr_stmt|;
name|alpha
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GRAYA_GIMAGE
case|:
name|bpp
operator|=
literal|2
expr_stmt|;
name|alpha
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|INDEXED_GIMAGE
case|:
name|bpp
operator|=
literal|1
expr_stmt|;
name|alpha
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|INDEXEDA_GIMAGE
case|:
name|bpp
operator|=
literal|2
expr_stmt|;
name|alpha
operator|=
literal|1
expr_stmt|;
break|break;
default|default:
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Layer type %d not supported."
argument_list|)
argument_list|,
name|type
argument_list|)
expr_stmt|;
return|return;
block|}
name|drawable
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|drawable
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|drawable
operator|->
name|bytes
operator|=
name|bpp
expr_stmt|;
name|drawable
operator|->
name|type
operator|=
name|type
expr_stmt|;
name|drawable
operator|->
name|has_alpha
operator|=
name|alpha
expr_stmt|;
name|drawable
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|drawable
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|tiles
condition|)
name|tile_manager_destroy
argument_list|(
name|drawable
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|tiles
operator|=
name|tile_manager_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|bpp
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|->
name|visible
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
name|gimp_drawable_set_gimage
argument_list|(
name|drawable
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|gimp_drawable_set_name
argument_list|(
name|drawable
argument_list|,
name|name
argument_list|)
expr_stmt|;
comment|/*  preview variables  */
name|drawable
operator|->
name|preview
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|preview_valid
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

