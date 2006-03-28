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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-grid.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-snap.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpstroke.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_snap_x (GimpImage * image,gdouble x,gdouble * tx,gdouble epsilon_x,gboolean snap_to_guides,gboolean snap_to_grid,gboolean snap_to_canvas)
name|gimp_image_snap_x
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
modifier|*
name|tx
parameter_list|,
name|gdouble
name|epsilon_x
parameter_list|,
name|gboolean
name|snap_to_guides
parameter_list|,
name|gboolean
name|snap_to_grid
parameter_list|,
name|gboolean
name|snap_to_canvas
parameter_list|)
block|{
name|gdouble
name|mindist
init|=
name|G_MAXDOUBLE
decl_stmt|;
name|gdouble
name|dist
decl_stmt|;
name|gboolean
name|snapped
init|=
name|FALSE
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
name|tx
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
operator|*
name|tx
operator|=
name|x
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|guides
condition|)
name|snap_to_guides
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|grid
condition|)
name|snap_to_grid
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|snap_to_guides
operator|||
name|snap_to_grid
operator|||
name|snap_to_canvas
operator|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|x
operator|<
operator|-
name|epsilon_x
operator|||
name|x
operator|>=
operator|(
name|image
operator|->
name|width
operator|+
name|epsilon_x
operator|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|snap_to_guides
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|image
operator|->
name|guides
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
name|GimpGuide
modifier|*
name|guide
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|guide
operator|->
name|position
operator|<
literal|0
condition|)
continue|continue;
if|if
condition|(
name|guide
operator|->
name|orientation
operator|==
name|GIMP_ORIENTATION_VERTICAL
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|guide
operator|->
name|position
operator|-
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist
argument_list|)
condition|)
block|{
name|mindist
operator|=
name|dist
expr_stmt|;
operator|*
name|tx
operator|=
name|guide
operator|->
name|position
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
block|}
if|if
condition|(
name|snap_to_grid
condition|)
block|{
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gdouble
name|xspacing
decl_stmt|;
name|gdouble
name|xoffset
decl_stmt|;
name|gdouble
name|i
decl_stmt|;
name|g_object_get
argument_list|(
name|grid
argument_list|,
literal|"xspacing"
argument_list|,
operator|&
name|xspacing
argument_list|,
literal|"xoffset"
argument_list|,
operator|&
name|xoffset
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|xoffset
init|;
name|i
operator|<=
name|image
operator|->
name|width
condition|;
name|i
operator|+=
name|xspacing
control|)
block|{
if|if
condition|(
name|i
operator|<
literal|0
condition|)
continue|continue;
name|dist
operator|=
name|ABS
argument_list|(
name|i
operator|-
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist
argument_list|)
condition|)
block|{
name|mindist
operator|=
name|dist
expr_stmt|;
operator|*
name|tx
operator|=
name|i
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|snap_to_canvas
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist
argument_list|)
condition|)
block|{
name|mindist
operator|=
name|dist
expr_stmt|;
operator|*
name|tx
operator|=
literal|0
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
name|dist
operator|=
name|ABS
argument_list|(
name|image
operator|->
name|width
operator|-
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist
argument_list|)
condition|)
block|{
name|mindist
operator|=
name|dist
expr_stmt|;
operator|*
name|tx
operator|=
name|image
operator|->
name|width
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
return|return
name|snapped
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_snap_y (GimpImage * image,gdouble y,gdouble * ty,gdouble epsilon_y,gboolean snap_to_guides,gboolean snap_to_grid,gboolean snap_to_canvas)
name|gimp_image_snap_y
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|ty
parameter_list|,
name|gdouble
name|epsilon_y
parameter_list|,
name|gboolean
name|snap_to_guides
parameter_list|,
name|gboolean
name|snap_to_grid
parameter_list|,
name|gboolean
name|snap_to_canvas
parameter_list|)
block|{
name|gdouble
name|mindist
init|=
name|G_MAXDOUBLE
decl_stmt|;
name|gdouble
name|dist
decl_stmt|;
name|gboolean
name|snapped
init|=
name|FALSE
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
name|ty
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
operator|*
name|ty
operator|=
name|y
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|guides
condition|)
name|snap_to_guides
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|grid
condition|)
name|snap_to_grid
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|snap_to_guides
operator|||
name|snap_to_grid
operator|||
name|snap_to_canvas
operator|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|y
operator|<
operator|-
name|epsilon_y
operator|||
name|y
operator|>=
operator|(
name|image
operator|->
name|height
operator|+
name|epsilon_y
operator|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|snap_to_guides
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|image
operator|->
name|guides
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
name|GimpGuide
modifier|*
name|guide
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|guide
operator|->
name|position
operator|<
literal|0
condition|)
continue|continue;
if|if
condition|(
name|guide
operator|->
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|guide
operator|->
name|position
operator|-
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist
argument_list|)
condition|)
block|{
name|mindist
operator|=
name|dist
expr_stmt|;
operator|*
name|ty
operator|=
name|guide
operator|->
name|position
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
block|}
if|if
condition|(
name|snap_to_grid
condition|)
block|{
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gdouble
name|yspacing
decl_stmt|;
name|gdouble
name|yoffset
decl_stmt|;
name|gdouble
name|i
decl_stmt|;
name|g_object_get
argument_list|(
name|grid
argument_list|,
literal|"yspacing"
argument_list|,
operator|&
name|yspacing
argument_list|,
literal|"yoffset"
argument_list|,
operator|&
name|yoffset
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|yoffset
init|;
name|i
operator|<=
name|image
operator|->
name|height
condition|;
name|i
operator|+=
name|yspacing
control|)
block|{
if|if
condition|(
name|i
operator|<
literal|0
condition|)
continue|continue;
name|dist
operator|=
name|ABS
argument_list|(
name|i
operator|-
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist
argument_list|)
condition|)
block|{
name|mindist
operator|=
name|dist
expr_stmt|;
operator|*
name|ty
operator|=
name|i
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|snap_to_canvas
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist
argument_list|)
condition|)
block|{
name|mindist
operator|=
name|dist
expr_stmt|;
operator|*
name|ty
operator|=
literal|0
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
name|dist
operator|=
name|ABS
argument_list|(
name|image
operator|->
name|height
operator|-
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist
argument_list|)
condition|)
block|{
name|mindist
operator|=
name|dist
expr_stmt|;
operator|*
name|ty
operator|=
name|image
operator|->
name|height
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
return|return
name|snapped
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_snap_point (GimpImage * image,gdouble x,gdouble y,gdouble * tx,gdouble * ty,gdouble epsilon_x,gdouble epsilon_y,gboolean snap_to_guides,gboolean snap_to_grid,gboolean snap_to_canvas,gboolean snap_to_vectors)
name|gimp_image_snap_point
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|tx
parameter_list|,
name|gdouble
modifier|*
name|ty
parameter_list|,
name|gdouble
name|epsilon_x
parameter_list|,
name|gdouble
name|epsilon_y
parameter_list|,
name|gboolean
name|snap_to_guides
parameter_list|,
name|gboolean
name|snap_to_grid
parameter_list|,
name|gboolean
name|snap_to_canvas
parameter_list|,
name|gboolean
name|snap_to_vectors
parameter_list|)
block|{
name|gdouble
name|mindist_x
init|=
name|G_MAXDOUBLE
decl_stmt|;
name|gdouble
name|mindist_y
init|=
name|G_MAXDOUBLE
decl_stmt|;
name|gdouble
name|dist
decl_stmt|;
name|gboolean
name|snapped
init|=
name|FALSE
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
name|tx
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|ty
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
operator|*
name|tx
operator|=
name|x
expr_stmt|;
operator|*
name|ty
operator|=
name|y
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|guides
condition|)
name|snap_to_guides
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|grid
condition|)
name|snap_to_grid
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|active_vectors
condition|)
name|snap_to_vectors
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|snap_to_guides
operator|||
name|snap_to_grid
operator|||
name|snap_to_canvas
operator|||
name|snap_to_vectors
operator|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|x
operator|<
operator|-
name|epsilon_x
operator|||
name|x
operator|>=
operator|(
name|image
operator|->
name|width
operator|+
name|epsilon_x
operator|)
operator|||
name|y
operator|<
operator|-
name|epsilon_y
operator|||
name|y
operator|>=
operator|(
name|image
operator|->
name|height
operator|+
name|epsilon_y
operator|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|snap_to_guides
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|image
operator|->
name|guides
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
name|GimpGuide
modifier|*
name|guide
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|guide
operator|->
name|position
operator|<
literal|0
condition|)
continue|continue;
switch|switch
condition|(
name|guide
operator|->
name|orientation
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|dist
operator|=
name|ABS
argument_list|(
name|guide
operator|->
name|position
operator|-
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty
operator|=
name|guide
operator|->
name|position
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|dist
operator|=
name|ABS
argument_list|(
name|guide
operator|->
name|position
operator|-
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx
operator|=
name|guide
operator|->
name|position
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
block|}
if|if
condition|(
name|snap_to_grid
condition|)
block|{
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gdouble
name|xspacing
decl_stmt|,
name|yspacing
decl_stmt|;
name|gdouble
name|xoffset
decl_stmt|,
name|yoffset
decl_stmt|;
name|gdouble
name|i
decl_stmt|;
name|g_object_get
argument_list|(
name|grid
argument_list|,
literal|"xspacing"
argument_list|,
operator|&
name|xspacing
argument_list|,
literal|"yspacing"
argument_list|,
operator|&
name|yspacing
argument_list|,
literal|"xoffset"
argument_list|,
operator|&
name|xoffset
argument_list|,
literal|"yoffset"
argument_list|,
operator|&
name|yoffset
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|xoffset
init|;
name|i
operator|<=
name|image
operator|->
name|width
condition|;
name|i
operator|+=
name|xspacing
control|)
block|{
if|if
condition|(
name|i
operator|<
literal|0
condition|)
continue|continue;
name|dist
operator|=
name|ABS
argument_list|(
name|i
operator|-
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx
operator|=
name|i
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
for|for
control|(
name|i
operator|=
name|yoffset
init|;
name|i
operator|<=
name|image
operator|->
name|height
condition|;
name|i
operator|+=
name|yspacing
control|)
block|{
if|if
condition|(
name|i
operator|<
literal|0
condition|)
continue|continue;
name|dist
operator|=
name|ABS
argument_list|(
name|i
operator|-
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty
operator|=
name|i
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|snap_to_canvas
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx
operator|=
literal|0
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
name|dist
operator|=
name|ABS
argument_list|(
name|image
operator|->
name|width
operator|-
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx
operator|=
name|image
operator|->
name|width
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
name|dist
operator|=
name|ABS
argument_list|(
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty
operator|=
literal|0
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
name|dist
operator|=
name|ABS
argument_list|(
name|image
operator|->
name|height
operator|-
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty
operator|=
name|image
operator|->
name|height
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|snap_to_vectors
condition|)
block|{
name|GimpVectors
modifier|*
name|vectors
init|=
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
init|=
name|NULL
decl_stmt|;
name|GimpCoords
name|coords
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|coords
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|coords
operator|.
name|y
operator|=
name|y
expr_stmt|;
while|while
condition|(
operator|(
name|stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
operator|)
condition|)
block|{
name|GimpCoords
name|nearest
decl_stmt|;
if|if
condition|(
name|gimp_stroke_nearest_point_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|x
operator|-
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx
operator|=
name|nearest
operator|.
name|x
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|y
operator|-
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty
operator|=
name|nearest
operator|.
name|y
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
block|}
return|return
name|snapped
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_snap_rectangle (GimpImage * image,gdouble x1,gdouble y1,gdouble x2,gdouble y2,gdouble * tx1,gdouble * ty1,gdouble epsilon_x,gdouble epsilon_y,gboolean snap_to_guides,gboolean snap_to_grid,gboolean snap_to_canvas,gboolean snap_to_vectors)
name|gimp_image_snap_rectangle
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|gdouble
modifier|*
name|tx1
parameter_list|,
name|gdouble
modifier|*
name|ty1
parameter_list|,
name|gdouble
name|epsilon_x
parameter_list|,
name|gdouble
name|epsilon_y
parameter_list|,
name|gboolean
name|snap_to_guides
parameter_list|,
name|gboolean
name|snap_to_grid
parameter_list|,
name|gboolean
name|snap_to_canvas
parameter_list|,
name|gboolean
name|snap_to_vectors
parameter_list|)
block|{
name|gdouble
name|nx
decl_stmt|,
name|ny
decl_stmt|;
name|gdouble
name|mindist_x
init|=
name|G_MAXDOUBLE
decl_stmt|;
name|gdouble
name|mindist_y
init|=
name|G_MAXDOUBLE
decl_stmt|;
name|gboolean
name|snapped
init|=
name|FALSE
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
name|tx1
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|ty1
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
operator|*
name|tx1
operator|=
name|x1
expr_stmt|;
operator|*
name|ty1
operator|=
name|y1
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|guides
condition|)
name|snap_to_guides
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|grid
condition|)
name|snap_to_grid
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|active_vectors
condition|)
name|snap_to_vectors
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|snap_to_guides
operator|||
name|snap_to_grid
operator|||
name|snap_to_canvas
operator|||
name|snap_to_vectors
operator|)
condition|)
return|return
name|FALSE
return|;
comment|/*  left edge  */
if|if
condition|(
name|gimp_image_snap_x
argument_list|(
name|image
argument_list|,
name|x1
argument_list|,
operator|&
name|nx
argument_list|,
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
argument_list|,
name|snap_to_guides
argument_list|,
name|snap_to_grid
argument_list|,
name|snap_to_canvas
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|ABS
argument_list|(
name|nx
operator|-
name|x1
argument_list|)
expr_stmt|;
operator|*
name|tx1
operator|=
name|nx
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/*  right edge  */
if|if
condition|(
name|gimp_image_snap_x
argument_list|(
name|image
argument_list|,
name|x2
argument_list|,
operator|&
name|nx
argument_list|,
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
argument_list|,
name|snap_to_guides
argument_list|,
name|snap_to_grid
argument_list|,
name|snap_to_canvas
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|ABS
argument_list|(
name|nx
operator|-
name|x2
argument_list|)
expr_stmt|;
operator|*
name|tx1
operator|=
name|RINT
argument_list|(
name|x1
operator|+
operator|(
name|nx
operator|-
name|x2
operator|)
argument_list|)
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/*  top edge  */
if|if
condition|(
name|gimp_image_snap_y
argument_list|(
name|image
argument_list|,
name|y1
argument_list|,
operator|&
name|ny
argument_list|,
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
argument_list|,
name|snap_to_guides
argument_list|,
name|snap_to_grid
argument_list|,
name|snap_to_canvas
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|ABS
argument_list|(
name|ny
operator|-
name|y1
argument_list|)
expr_stmt|;
operator|*
name|ty1
operator|=
name|ny
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/*  bottom edge  */
if|if
condition|(
name|gimp_image_snap_y
argument_list|(
name|image
argument_list|,
name|y2
argument_list|,
operator|&
name|ny
argument_list|,
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
argument_list|,
name|snap_to_guides
argument_list|,
name|snap_to_grid
argument_list|,
name|snap_to_canvas
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|ABS
argument_list|(
name|ny
operator|-
name|y2
argument_list|)
expr_stmt|;
operator|*
name|ty1
operator|=
name|RINT
argument_list|(
name|y1
operator|+
operator|(
name|ny
operator|-
name|y2
operator|)
argument_list|)
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|snap_to_vectors
condition|)
block|{
name|GimpVectors
modifier|*
name|vectors
init|=
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
init|=
name|NULL
decl_stmt|;
name|GimpCoords
name|coords1
init|=
name|GIMP_COORDS_DEFAULT_VALUES
decl_stmt|;
name|GimpCoords
name|coords2
init|=
name|GIMP_COORDS_DEFAULT_VALUES
decl_stmt|;
while|while
condition|(
operator|(
name|stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
operator|)
condition|)
block|{
name|GimpCoords
name|nearest
decl_stmt|;
name|gdouble
name|dist
decl_stmt|;
comment|/*  top edge  */
name|coords1
operator|.
name|x
operator|=
name|x1
expr_stmt|;
name|coords1
operator|.
name|y
operator|=
name|y1
expr_stmt|;
name|coords2
operator|.
name|x
operator|=
name|x2
expr_stmt|;
name|coords2
operator|.
name|y
operator|=
name|y1
expr_stmt|;
if|if
condition|(
name|gimp_stroke_nearest_tangent_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords1
argument_list|,
operator|&
name|coords2
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|y
operator|-
name|y1
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty1
operator|=
name|nearest
operator|.
name|y
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp_stroke_nearest_intersection_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords1
argument_list|,
operator|&
name|coords2
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|x
operator|-
name|x1
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx1
operator|=
name|nearest
operator|.
name|x
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp_stroke_nearest_intersection_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords2
argument_list|,
operator|&
name|coords1
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|x
operator|-
name|x2
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx1
operator|=
name|RINT
argument_list|(
name|x1
operator|+
operator|(
name|nearest
operator|.
name|x
operator|-
name|x2
operator|)
argument_list|)
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
comment|/*  bottom edge  */
name|coords1
operator|.
name|x
operator|=
name|x1
expr_stmt|;
name|coords1
operator|.
name|y
operator|=
name|y2
expr_stmt|;
name|coords2
operator|.
name|x
operator|=
name|x2
expr_stmt|;
name|coords2
operator|.
name|y
operator|=
name|y2
expr_stmt|;
if|if
condition|(
name|gimp_stroke_nearest_tangent_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords1
argument_list|,
operator|&
name|coords2
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|y
operator|-
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty1
operator|=
name|RINT
argument_list|(
name|y1
operator|+
operator|(
name|nearest
operator|.
name|y
operator|-
name|y2
operator|)
argument_list|)
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp_stroke_nearest_intersection_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords1
argument_list|,
operator|&
name|coords2
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|x
operator|-
name|x1
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx1
operator|=
name|nearest
operator|.
name|x
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp_stroke_nearest_intersection_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords2
argument_list|,
operator|&
name|coords1
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|x
operator|-
name|x2
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx1
operator|=
name|RINT
argument_list|(
name|x1
operator|+
operator|(
name|nearest
operator|.
name|x
operator|-
name|x2
operator|)
argument_list|)
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
comment|/*  left edge  */
name|coords1
operator|.
name|x
operator|=
name|x1
expr_stmt|;
name|coords1
operator|.
name|y
operator|=
name|y1
expr_stmt|;
name|coords2
operator|.
name|x
operator|=
name|x1
expr_stmt|;
name|coords2
operator|.
name|y
operator|=
name|y2
expr_stmt|;
if|if
condition|(
name|gimp_stroke_nearest_tangent_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords1
argument_list|,
operator|&
name|coords2
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|x
operator|-
name|x1
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx1
operator|=
name|nearest
operator|.
name|x
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp_stroke_nearest_intersection_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords1
argument_list|,
operator|&
name|coords2
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|y
operator|-
name|y1
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty1
operator|=
name|nearest
operator|.
name|y
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp_stroke_nearest_intersection_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords2
argument_list|,
operator|&
name|coords1
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|y
operator|-
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty1
operator|=
name|RINT
argument_list|(
name|y1
operator|+
operator|(
name|nearest
operator|.
name|y
operator|-
name|y2
operator|)
argument_list|)
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
comment|/*  right edge  */
name|coords1
operator|.
name|x
operator|=
name|x2
expr_stmt|;
name|coords1
operator|.
name|y
operator|=
name|y1
expr_stmt|;
name|coords2
operator|.
name|x
operator|=
name|x2
expr_stmt|;
name|coords2
operator|.
name|y
operator|=
name|y2
expr_stmt|;
if|if
condition|(
name|gimp_stroke_nearest_tangent_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords1
argument_list|,
operator|&
name|coords2
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|x
operator|-
name|x2
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_x
argument_list|,
name|mindist_x
argument_list|)
condition|)
block|{
name|mindist_x
operator|=
name|dist
expr_stmt|;
operator|*
name|tx1
operator|=
name|RINT
argument_list|(
name|x1
operator|+
operator|(
name|nearest
operator|.
name|x
operator|-
name|x2
operator|)
argument_list|)
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp_stroke_nearest_intersection_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords1
argument_list|,
operator|&
name|coords2
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|y
operator|-
name|y1
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty1
operator|=
name|nearest
operator|.
name|y
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp_stroke_nearest_intersection_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|coords2
argument_list|,
operator|&
name|coords1
argument_list|,
literal|1.0
argument_list|,
operator|&
name|nearest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|dist
operator|=
name|ABS
argument_list|(
name|nearest
operator|.
name|y
operator|-
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist_y
argument_list|)
condition|)
block|{
name|mindist_y
operator|=
name|dist
expr_stmt|;
operator|*
name|ty1
operator|=
name|RINT
argument_list|(
name|y1
operator|+
operator|(
name|nearest
operator|.
name|y
operator|-
name|y2
operator|)
argument_list|)
expr_stmt|;
name|snapped
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
block|}
return|return
name|snapped
return|;
block|}
end_function

end_unit

