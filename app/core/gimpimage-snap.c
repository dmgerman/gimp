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
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|5
end_define

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_snap_x (GimpImage * gimage,gdouble x,gint * tx,gboolean snap_to_guides,gboolean snap_to_grid)
name|gimp_image_snap_x
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gint
modifier|*
name|tx
parameter_list|,
name|gboolean
name|snap_to_guides
parameter_list|,
name|gboolean
name|snap_to_grid
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
name|gdouble
name|xspacing
decl_stmt|;
name|gdouble
name|xoffset
decl_stmt|;
name|gdouble
name|mindist
init|=
name|G_MAXDOUBLE
decl_stmt|;
name|gdouble
name|dist
decl_stmt|;
name|gdouble
name|i
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
name|gimage
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
if|if
condition|(
operator|!
name|snap_to_guides
operator|&&
operator|!
name|snap_to_grid
condition|)
return|return
name|FALSE
return|;
operator|*
name|tx
operator|=
name|ROUND
argument_list|(
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|x
operator|>=
name|gimage
operator|->
name|width
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|snap_to_guides
operator|&&
name|gimage
operator|->
name|guides
operator|!=
name|NULL
condition|)
block|{
for|for
control|(
name|list
operator|=
name|gimage
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
name|guide
operator|=
operator|(
name|GimpGuide
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
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
name|EPSILON
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
operator|&&
name|gimage
operator|->
name|grid
operator|!=
name|NULL
condition|)
block|{
name|grid
operator|=
name|gimp_image_get_grid
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
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
name|gimage
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
name|EPSILON
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
return|return
name|snapped
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_snap_y (GimpImage * gimage,gdouble y,gint * ty,gboolean snap_to_guides,gboolean snap_to_grid)
name|gimp_image_snap_y
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
modifier|*
name|ty
parameter_list|,
name|gboolean
name|snap_to_guides
parameter_list|,
name|gboolean
name|snap_to_grid
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
name|gdouble
name|yspacing
decl_stmt|;
name|gdouble
name|yoffset
decl_stmt|;
name|gdouble
name|mindist
init|=
name|G_MAXDOUBLE
decl_stmt|;
name|gdouble
name|dist
decl_stmt|;
name|gdouble
name|i
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
name|gimage
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
if|if
condition|(
operator|!
name|snap_to_guides
operator|&&
operator|!
name|snap_to_grid
condition|)
return|return
name|FALSE
return|;
operator|*
name|ty
operator|=
name|ROUND
argument_list|(
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
operator|||
name|y
operator|>=
name|gimage
operator|->
name|height
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|snap_to_guides
operator|&&
name|gimage
operator|->
name|guides
operator|!=
name|NULL
condition|)
block|{
for|for
control|(
name|list
operator|=
name|gimage
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
name|guide
operator|=
operator|(
name|GimpGuide
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
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
name|EPSILON
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
operator|&&
name|gimage
operator|->
name|grid
operator|!=
name|NULL
condition|)
block|{
name|grid
operator|=
name|gimp_image_get_grid
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
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
name|gimage
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
name|EPSILON
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
return|return
name|snapped
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_snap_point (GimpImage * gimage,gdouble x,gdouble y,gint * tx,gint * ty,gboolean snap_to_guides,gboolean snap_to_grid)
name|gimp_image_snap_point
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
modifier|*
name|tx
parameter_list|,
name|gint
modifier|*
name|ty
parameter_list|,
name|gboolean
name|snap_to_guides
parameter_list|,
name|gboolean
name|snap_to_grid
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|GimpGrid
modifier|*
name|grid
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
name|minxdist
decl_stmt|,
name|minydist
decl_stmt|;
name|gdouble
name|dist
decl_stmt|;
name|gdouble
name|i
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
name|gimage
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
if|if
condition|(
operator|!
name|snap_to_guides
operator|&&
operator|!
name|snap_to_grid
condition|)
return|return
name|FALSE
return|;
operator|*
name|tx
operator|=
name|ROUND
argument_list|(
name|x
argument_list|)
expr_stmt|;
operator|*
name|ty
operator|=
name|ROUND
argument_list|(
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|x
operator|>=
name|gimage
operator|->
name|width
operator|||
name|y
operator|<
literal|0
operator|||
name|y
operator|>=
name|gimage
operator|->
name|height
condition|)
block|{
return|return
name|FALSE
return|;
block|}
name|minxdist
operator|=
name|G_MAXINT
expr_stmt|;
name|minydist
operator|=
name|G_MAXINT
expr_stmt|;
if|if
condition|(
name|snap_to_guides
operator|&&
name|gimage
operator|->
name|guides
operator|!=
name|NULL
condition|)
block|{
for|for
control|(
name|list
operator|=
name|gimage
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
name|guide
operator|=
operator|(
name|GimpGuide
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
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
name|EPSILON
argument_list|,
name|minydist
argument_list|)
condition|)
block|{
name|minydist
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
name|EPSILON
argument_list|,
name|minxdist
argument_list|)
condition|)
block|{
name|minxdist
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
operator|&&
name|gimage
operator|->
name|grid
operator|!=
name|NULL
condition|)
block|{
name|grid
operator|=
name|gimp_image_get_grid
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
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
name|gimage
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
name|EPSILON
argument_list|,
name|minxdist
argument_list|)
condition|)
block|{
name|minxdist
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
name|gimage
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
name|EPSILON
argument_list|,
name|minydist
argument_list|)
condition|)
block|{
name|minydist
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
return|return
name|snapped
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_snap_rectangle (GimpImage * gimage,gdouble x1,gdouble y1,gdouble x2,gdouble y2,gint * tx1,gint * ty1,gboolean snap_to_guides,gboolean snap_to_grid)
name|gimp_image_snap_rectangle
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|gint
modifier|*
name|tx1
parameter_list|,
name|gint
modifier|*
name|ty1
parameter_list|,
name|gboolean
name|snap_to_guides
parameter_list|,
name|gboolean
name|snap_to_grid
parameter_list|)
block|{
name|gint
name|nx1
decl_stmt|,
name|ny1
decl_stmt|;
name|gint
name|nx2
decl_stmt|,
name|ny2
decl_stmt|;
name|gboolean
name|snap1
decl_stmt|,
name|snap2
decl_stmt|,
name|snap3
decl_stmt|,
name|snap4
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
if|if
condition|(
operator|!
name|snap_to_guides
operator|&&
operator|!
name|snap_to_grid
condition|)
return|return
name|FALSE
return|;
operator|*
name|tx1
operator|=
name|ROUND
argument_list|(
name|x1
argument_list|)
expr_stmt|;
operator|*
name|ty1
operator|=
name|ROUND
argument_list|(
name|y1
argument_list|)
expr_stmt|;
name|snap1
operator|=
name|gimp_image_snap_x
argument_list|(
name|gimage
argument_list|,
name|x1
argument_list|,
operator|&
name|nx1
argument_list|,
name|snap_to_guides
argument_list|,
name|snap_to_grid
argument_list|)
expr_stmt|;
name|snap2
operator|=
name|gimp_image_snap_x
argument_list|(
name|gimage
argument_list|,
name|x2
argument_list|,
operator|&
name|nx2
argument_list|,
name|snap_to_guides
argument_list|,
name|snap_to_grid
argument_list|)
expr_stmt|;
name|snap3
operator|=
name|gimp_image_snap_y
argument_list|(
name|gimage
argument_list|,
name|y1
argument_list|,
operator|&
name|ny1
argument_list|,
name|snap_to_guides
argument_list|,
name|snap_to_grid
argument_list|)
expr_stmt|;
name|snap4
operator|=
name|gimp_image_snap_y
argument_list|(
name|gimage
argument_list|,
name|y2
argument_list|,
operator|&
name|ny2
argument_list|,
name|snap_to_guides
argument_list|,
name|snap_to_grid
argument_list|)
expr_stmt|;
if|if
condition|(
name|snap1
operator|&&
name|snap2
condition|)
block|{
if|if
condition|(
name|ABS
argument_list|(
name|x1
operator|-
name|nx1
argument_list|)
operator|>
name|ABS
argument_list|(
name|x2
operator|-
name|nx2
argument_list|)
condition|)
name|snap1
operator|=
name|FALSE
expr_stmt|;
else|else
name|snap2
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|snap1
condition|)
operator|*
name|tx1
operator|=
name|nx1
expr_stmt|;
elseif|else
if|if
condition|(
name|snap2
condition|)
operator|*
name|tx1
operator|=
name|ROUND
argument_list|(
name|x1
operator|+
operator|(
name|nx2
operator|-
name|x2
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|snap3
operator|&&
name|snap4
condition|)
block|{
if|if
condition|(
name|ABS
argument_list|(
name|y1
operator|-
name|ny1
argument_list|)
operator|>
name|ABS
argument_list|(
name|y2
operator|-
name|ny2
argument_list|)
condition|)
name|snap3
operator|=
name|FALSE
expr_stmt|;
else|else
name|snap4
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|snap3
condition|)
operator|*
name|ty1
operator|=
name|ny1
expr_stmt|;
elseif|else
if|if
condition|(
name|snap4
condition|)
operator|*
name|ty1
operator|=
name|ROUND
argument_list|(
name|y1
operator|+
operator|(
name|ny2
operator|-
name|y2
operator|)
argument_list|)
expr_stmt|;
return|return
operator|(
name|snap1
operator|||
name|snap2
operator|||
name|snap3
operator|||
name|snap4
operator|)
return|;
block|}
end_function

end_unit

