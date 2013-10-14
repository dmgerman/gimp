begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpvectors-compat.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"vectors-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpanchor.h"
end_include

begin_include
include|#
directive|include
file|"gimpbezierstroke.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectors-compat.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c303e060103
block|{
DECL|enumerator|GIMP_VECTORS_COMPAT_ANCHOR
name|GIMP_VECTORS_COMPAT_ANCHOR
init|=
literal|1
block|,
DECL|enumerator|GIMP_VECTORS_COMPAT_CONTROL
name|GIMP_VECTORS_COMPAT_CONTROL
init|=
literal|2
block|,
DECL|enumerator|GIMP_VECTORS_COMPAT_NEW_STROKE
name|GIMP_VECTORS_COMPAT_NEW_STROKE
init|=
literal|3
block|}
enum|;
end_enum

begin_decl_stmt
DECL|variable|default_coords
specifier|static
specifier|const
name|GimpCoords
name|default_coords
init|=
name|GIMP_COORDS_DEFAULT_VALUES
decl_stmt|;
end_decl_stmt

begin_function
name|GimpVectors
modifier|*
DECL|function|gimp_vectors_compat_new (GimpImage * image,const gchar * name,GimpVectorsCompatPoint * points,gint n_points,gboolean closed)
name|gimp_vectors_compat_new
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
name|GimpVectorsCompatPoint
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gboolean
name|closed
parameter_list|)
block|{
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
decl_stmt|;
name|GimpCoords
modifier|*
name|curr_stroke
decl_stmt|;
name|GimpCoords
modifier|*
name|curr_coord
decl_stmt|;
name|gint
name|i
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
name|points
operator|!=
name|NULL
operator|||
name|n_points
operator|==
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_points
operator|>=
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vectors
operator|=
name|gimp_vectors_new
argument_list|(
name|image
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|coords
operator|=
name|g_new0
argument_list|(
name|GimpCoords
argument_list|,
name|n_points
operator|+
literal|1
argument_list|)
expr_stmt|;
name|curr_stroke
operator|=
name|curr_coord
operator|=
name|coords
expr_stmt|;
comment|/*  skip the first control point, will set it later  */
name|curr_coord
operator|++
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_points
condition|;
name|i
operator|++
control|)
block|{
operator|*
name|curr_coord
operator|=
name|default_coords
expr_stmt|;
name|curr_coord
operator|->
name|x
operator|=
name|points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|curr_coord
operator|->
name|y
operator|=
name|points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
comment|/*  copy the first anchor to be the first control point  */
if|if
condition|(
name|curr_coord
operator|==
name|curr_stroke
operator|+
literal|1
condition|)
operator|*
name|curr_stroke
operator|=
operator|*
name|curr_coord
expr_stmt|;
comment|/*  found new stroke start  */
if|if
condition|(
name|points
index|[
name|i
index|]
operator|.
name|type
operator|==
name|GIMP_VECTORS_COMPAT_NEW_STROKE
condition|)
block|{
comment|/*  copy the last control point to the beginning of the stroke  */
operator|*
name|curr_stroke
operator|=
operator|*
operator|(
name|curr_coord
operator|-
literal|1
operator|)
expr_stmt|;
name|stroke
operator|=
name|gimp_bezier_stroke_new_from_coords
argument_list|(
name|curr_stroke
argument_list|,
name|curr_coord
operator|-
name|curr_stroke
operator|-
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_vectors_stroke_add
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|stroke
argument_list|)
expr_stmt|;
comment|/*  start a new stroke  */
name|curr_stroke
operator|=
name|curr_coord
operator|-
literal|1
expr_stmt|;
comment|/*  copy the first anchor to be the first control point  */
operator|*
name|curr_stroke
operator|=
operator|*
name|curr_coord
expr_stmt|;
block|}
name|curr_coord
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|closed
condition|)
block|{
comment|/*  copy the last control point to the beginning of the stroke  */
name|curr_coord
operator|--
expr_stmt|;
operator|*
name|curr_stroke
operator|=
operator|*
name|curr_coord
expr_stmt|;
block|}
name|stroke
operator|=
name|gimp_bezier_stroke_new_from_coords
argument_list|(
name|curr_stroke
argument_list|,
name|curr_coord
operator|-
name|curr_stroke
argument_list|,
name|closed
argument_list|)
expr_stmt|;
name|gimp_vectors_stroke_add
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|stroke
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|coords
argument_list|)
expr_stmt|;
return|return
name|vectors
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_vectors_compat_is_compatible (GimpImage * image)
name|gimp_vectors_compat_is_compatible
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GList
modifier|*
name|list
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
for|for
control|(
name|list
operator|=
name|gimp_image_get_vectors_iter
argument_list|(
name|image
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpVectors
modifier|*
name|vectors
init|=
name|GIMP_VECTORS
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|strokes
decl_stmt|;
name|gint
name|open_count
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
condition|)
return|return
name|FALSE
return|;
for|for
control|(
name|strokes
operator|=
name|vectors
operator|->
name|strokes
init|;
name|strokes
condition|;
name|strokes
operator|=
name|g_list_next
argument_list|(
name|strokes
argument_list|)
control|)
block|{
name|GimpStroke
modifier|*
name|stroke
init|=
name|GIMP_STROKE
argument_list|(
name|strokes
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_BEZIER_STROKE
argument_list|(
name|stroke
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|!
name|stroke
operator|->
name|closed
condition|)
name|open_count
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|open_count
operator|>=
literal|2
condition|)
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GimpVectorsCompatPoint
modifier|*
DECL|function|gimp_vectors_compat_get_points (GimpVectors * vectors,gint32 * n_points,gint32 * closed)
name|gimp_vectors_compat_get_points
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|gint32
modifier|*
name|n_points
parameter_list|,
name|gint32
modifier|*
name|closed
parameter_list|)
block|{
name|GimpVectorsCompatPoint
modifier|*
name|points
decl_stmt|;
name|GList
modifier|*
name|strokes
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GList
modifier|*
name|postponed
init|=
name|NULL
decl_stmt|;
comment|/* for the one open stroke... */
name|gint
name|open_count
decl_stmt|;
name|gboolean
name|first_stroke
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_points
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|closed
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|n_points
operator|=
literal|0
expr_stmt|;
operator|*
name|closed
operator|=
name|TRUE
expr_stmt|;
name|open_count
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|strokes
operator|=
name|vectors
operator|->
name|strokes
init|;
name|strokes
condition|;
name|strokes
operator|=
name|g_list_next
argument_list|(
name|strokes
argument_list|)
control|)
block|{
name|GimpStroke
modifier|*
name|stroke
init|=
name|strokes
operator|->
name|data
decl_stmt|;
name|gint
name|n_anchors
decl_stmt|;
if|if
condition|(
operator|!
name|stroke
operator|->
name|closed
condition|)
block|{
name|open_count
operator|++
expr_stmt|;
name|postponed
operator|=
name|strokes
expr_stmt|;
operator|*
name|closed
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|open_count
operator|>=
literal|2
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_vectors_compat_get_points(): convert failed"
argument_list|)
expr_stmt|;
operator|*
name|n_points
operator|=
literal|0
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
name|n_anchors
operator|=
name|g_list_length
argument_list|(
name|stroke
operator|->
name|anchors
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|stroke
operator|->
name|closed
condition|)
name|n_anchors
operator|--
expr_stmt|;
operator|*
name|n_points
operator|+=
name|n_anchors
expr_stmt|;
block|}
name|points
operator|=
name|g_new0
argument_list|(
name|GimpVectorsCompatPoint
argument_list|,
operator|*
name|n_points
argument_list|)
expr_stmt|;
name|i
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|strokes
operator|=
name|vectors
operator|->
name|strokes
init|;
name|strokes
operator|||
name|postponed
condition|;
name|strokes
operator|=
name|g_list_next
argument_list|(
name|strokes
argument_list|)
control|)
block|{
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
name|GList
modifier|*
name|anchors
decl_stmt|;
if|if
condition|(
name|strokes
condition|)
block|{
if|if
condition|(
name|postponed
operator|&&
name|strokes
operator|==
name|postponed
condition|)
comment|/* we need to visit the open stroke last... */
continue|continue;
else|else
name|stroke
operator|=
name|GIMP_STROKE
argument_list|(
name|strokes
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|stroke
operator|=
name|GIMP_STROKE
argument_list|(
name|postponed
operator|->
name|data
argument_list|)
expr_stmt|;
name|postponed
operator|=
name|NULL
expr_stmt|;
block|}
for|for
control|(
name|anchors
operator|=
name|stroke
operator|->
name|anchors
init|;
name|anchors
condition|;
name|anchors
operator|=
name|g_list_next
argument_list|(
name|anchors
argument_list|)
control|)
block|{
name|GimpAnchor
modifier|*
name|anchor
init|=
name|anchors
operator|->
name|data
decl_stmt|;
comment|/*  skip the first anchor, will add it at the end if needed  */
if|if
condition|(
operator|!
name|anchors
operator|->
name|prev
condition|)
continue|continue;
switch|switch
condition|(
name|anchor
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_ANCHOR_ANCHOR
case|:
if|if
condition|(
name|anchors
operator|->
name|prev
operator|==
name|stroke
operator|->
name|anchors
operator|&&
operator|!
name|first_stroke
condition|)
name|points
index|[
name|i
index|]
operator|.
name|type
operator|=
name|GIMP_VECTORS_COMPAT_NEW_STROKE
expr_stmt|;
else|else
name|points
index|[
name|i
index|]
operator|.
name|type
operator|=
name|GIMP_VECTORS_COMPAT_ANCHOR
expr_stmt|;
break|break;
case|case
name|GIMP_ANCHOR_CONTROL
case|:
name|points
index|[
name|i
index|]
operator|.
name|type
operator|=
name|GIMP_VECTORS_COMPAT_CONTROL
expr_stmt|;
break|break;
block|}
name|points
index|[
name|i
index|]
operator|.
name|x
operator|=
name|anchor
operator|->
name|position
operator|.
name|x
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|y
operator|=
name|anchor
operator|->
name|position
operator|.
name|y
expr_stmt|;
name|i
operator|++
expr_stmt|;
comment|/*  write the skipped control point  */
if|if
condition|(
operator|!
name|anchors
operator|->
name|next
operator|&&
name|stroke
operator|->
name|closed
condition|)
block|{
name|anchor
operator|=
name|GIMP_ANCHOR
argument_list|(
name|stroke
operator|->
name|anchors
operator|->
name|data
argument_list|)
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|type
operator|=
name|GIMP_VECTORS_COMPAT_CONTROL
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|x
operator|=
name|anchor
operator|->
name|position
operator|.
name|x
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|y
operator|=
name|anchor
operator|->
name|position
operator|.
name|y
expr_stmt|;
name|i
operator|++
expr_stmt|;
block|}
block|}
name|first_stroke
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|points
return|;
block|}
end_function

end_unit

