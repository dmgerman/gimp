begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"pixel_region.h"
end_include

begin_include
include|#
directive|include
file|"scan_convert.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|DEBUG
end_ifdef

begin_define
DECL|macro|TRC (x)
define|#
directive|define
name|TRC
parameter_list|(
name|x
parameter_list|)
value|printf x
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|TRC (x)
define|#
directive|define
name|TRC
parameter_list|(
name|x
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Reveal our private structure */
end_comment

begin_struct
DECL|struct|ScanConverterPrivate
struct|struct
name|ScanConverterPrivate
block|{
DECL|member|width
name|guint
name|width
decl_stmt|;
DECL|member|height
name|guint
name|height
decl_stmt|;
DECL|member|scanlines
name|GSList
modifier|*
modifier|*
name|scanlines
decl_stmt|;
comment|/* array of height*antialias scanlines */
DECL|member|antialias
name|guint
name|antialias
decl_stmt|;
comment|/* how much to oversample by */
comment|/* record the first and last points so we can close the curve */
DECL|member|got_first
name|gboolean
name|got_first
decl_stmt|;
DECL|member|first
name|ScanConvertPoint
name|first
decl_stmt|;
DECL|member|got_last
name|gboolean
name|got_last
decl_stmt|;
DECL|member|last
name|ScanConvertPoint
name|last
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* Local helper routines to scan convert the polygon */
end_comment

begin_function
specifier|static
name|GSList
modifier|*
DECL|function|insert_into_sorted_list (GSList * list,gint x)
name|insert_into_sorted_list
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|gint
name|x
parameter_list|)
block|{
name|GSList
modifier|*
name|orig
init|=
name|list
decl_stmt|;
name|GSList
modifier|*
name|rest
decl_stmt|;
if|if
condition|(
operator|!
name|list
condition|)
return|return
name|g_slist_prepend
argument_list|(
name|list
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|x
argument_list|)
argument_list|)
return|;
while|while
condition|(
name|list
condition|)
block|{
name|rest
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
name|GPOINTER_TO_INT
argument_list|(
name|list
operator|->
name|data
argument_list|)
condition|)
block|{
name|rest
operator|=
name|g_slist_prepend
argument_list|(
name|rest
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|->
name|next
operator|=
name|rest
expr_stmt|;
name|list
operator|->
name|data
operator|=
name|GINT_TO_POINTER
argument_list|(
name|x
argument_list|)
expr_stmt|;
return|return
name|orig
return|;
block|}
elseif|else
if|if
condition|(
operator|!
name|rest
condition|)
block|{
name|g_slist_append
argument_list|(
name|list
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|x
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|orig
return|;
block|}
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
return|return
name|orig
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|convert_segment (ScanConverter * sc,gint x1,gint y1,gint x2,gint y2)
name|convert_segment
parameter_list|(
name|ScanConverter
modifier|*
name|sc
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
block|{
name|gint
name|ydiff
decl_stmt|,
name|y
decl_stmt|,
name|tmp
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|GSList
modifier|*
modifier|*
name|scanlines
decl_stmt|;
name|gfloat
name|xinc
decl_stmt|,
name|xstart
decl_stmt|;
comment|/* pre-calculate invariant commonly used values */
name|width
operator|=
name|sc
operator|->
name|width
operator|*
name|sc
operator|->
name|antialias
expr_stmt|;
name|height
operator|=
name|sc
operator|->
name|height
operator|*
name|sc
operator|->
name|antialias
expr_stmt|;
name|scanlines
operator|=
name|sc
operator|->
name|scanlines
expr_stmt|;
name|x1
operator|=
name|CLAMP
argument_list|(
name|x1
argument_list|,
literal|0
argument_list|,
name|width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y1
argument_list|,
literal|0
argument_list|,
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
argument_list|,
literal|0
argument_list|,
name|width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y2
argument_list|,
literal|0
argument_list|,
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|y1
operator|>
name|y2
condition|)
block|{
name|tmp
operator|=
name|y2
expr_stmt|;
name|y2
operator|=
name|y1
expr_stmt|;
name|y1
operator|=
name|tmp
expr_stmt|;
name|tmp
operator|=
name|x2
expr_stmt|;
name|x2
operator|=
name|x1
expr_stmt|;
name|x1
operator|=
name|tmp
expr_stmt|;
block|}
name|ydiff
operator|=
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
if|if
condition|(
name|ydiff
condition|)
block|{
name|xinc
operator|=
call|(
name|float
call|)
argument_list|(
name|x2
operator|-
name|x1
argument_list|)
operator|/
operator|(
name|float
operator|)
name|ydiff
expr_stmt|;
name|xstart
operator|=
name|x1
operator|+
literal|0.5
operator|*
name|xinc
expr_stmt|;
for|for
control|(
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|y
operator|++
control|)
block|{
name|scanlines
index|[
name|y
index|]
operator|=
name|insert_into_sorted_list
argument_list|(
name|scanlines
index|[
name|y
index|]
argument_list|,
name|ROUND
argument_list|(
name|xstart
argument_list|)
argument_list|)
expr_stmt|;
name|xstart
operator|+=
name|xinc
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/* horizontal line */
name|scanlines
index|[
name|y1
index|]
operator|=
name|insert_into_sorted_list
argument_list|(
name|scanlines
index|[
name|y1
index|]
argument_list|,
name|ROUND
argument_list|(
name|x1
argument_list|)
argument_list|)
expr_stmt|;
name|scanlines
index|[
name|y1
index|]
operator|=
name|insert_into_sorted_list
argument_list|(
name|scanlines
index|[
name|y1
index|]
argument_list|,
name|ROUND
argument_list|(
name|x2
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/* Exported functions */
end_comment

begin_comment
comment|/* Create a new scan conversion context */
end_comment

begin_function
name|ScanConverter
modifier|*
DECL|function|scan_converter_new (guint width,guint height,guint antialias)
name|scan_converter_new
parameter_list|(
name|guint
name|width
parameter_list|,
name|guint
name|height
parameter_list|,
name|guint
name|antialias
parameter_list|)
block|{
name|ScanConverter
modifier|*
name|sc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|antialias
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sc
operator|=
name|g_new0
argument_list|(
name|ScanConverter
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|sc
operator|->
name|antialias
operator|=
name|antialias
expr_stmt|;
name|sc
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|sc
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|sc
operator|->
name|scanlines
operator|=
name|g_new0
argument_list|(
name|GSList
operator|*
argument_list|,
name|height
operator|*
name|antialias
argument_list|)
expr_stmt|;
return|return
name|sc
return|;
block|}
end_function

begin_function
name|void
DECL|function|scan_converter_free (ScanConverter * sc)
name|scan_converter_free
parameter_list|(
name|ScanConverter
modifier|*
name|sc
parameter_list|)
block|{
name|g_free
argument_list|(
name|sc
operator|->
name|scanlines
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|sc
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Add "npoints" from "pointlist" to the polygon currently being  * described by "scan_converter".  */
end_comment

begin_function
name|void
DECL|function|scan_converter_add_points (ScanConverter * sc,guint npoints,ScanConvertPoint * pointlist)
name|scan_converter_add_points
parameter_list|(
name|ScanConverter
modifier|*
name|sc
parameter_list|,
name|guint
name|npoints
parameter_list|,
name|ScanConvertPoint
modifier|*
name|pointlist
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|guint
name|antialias
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|sc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|pointlist
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|antialias
operator|=
name|sc
operator|->
name|antialias
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|got_first
operator|&&
name|npoints
operator|>
literal|0
condition|)
block|{
name|sc
operator|->
name|got_first
operator|=
name|TRUE
expr_stmt|;
name|sc
operator|->
name|first
operator|=
name|pointlist
index|[
literal|0
index|]
expr_stmt|;
block|}
comment|/* link from previous point */
if|if
condition|(
name|sc
operator|->
name|got_last
operator|&&
name|npoints
operator|>
literal|0
condition|)
block|{
name|TRC
argument_list|(
operator|(
literal|"|| %g,%g -> %g,%g\n"
operator|,
name|sc
operator|->
name|last
operator|.
name|x
operator|,
name|sc
operator|->
name|last
operator|.
name|y
operator|,
name|pointlist
index|[
literal|0
index|]
operator|.
name|x
operator|,
name|pointlist
index|[
literal|0
index|]
operator|.
name|y
operator|)
argument_list|)
expr_stmt|;
name|convert_segment
argument_list|(
name|sc
argument_list|,
operator|(
name|int
operator|)
name|sc
operator|->
name|last
operator|.
name|x
operator|*
name|antialias
argument_list|,
operator|(
name|int
operator|)
name|sc
operator|->
name|last
operator|.
name|y
operator|*
name|antialias
argument_list|,
operator|(
name|int
operator|)
name|pointlist
index|[
literal|0
index|]
operator|.
name|x
operator|*
name|antialias
argument_list|,
operator|(
name|int
operator|)
name|pointlist
index|[
literal|0
index|]
operator|.
name|y
operator|*
name|antialias
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|(
name|npoints
operator|-
literal|1
operator|)
condition|;
name|i
operator|++
control|)
block|{
name|convert_segment
argument_list|(
name|sc
argument_list|,
operator|(
name|int
operator|)
name|pointlist
index|[
name|i
index|]
operator|.
name|x
operator|*
name|antialias
argument_list|,
operator|(
name|int
operator|)
name|pointlist
index|[
name|i
index|]
operator|.
name|y
operator|*
name|antialias
argument_list|,
operator|(
name|int
operator|)
name|pointlist
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|x
operator|*
name|antialias
argument_list|,
operator|(
name|int
operator|)
name|pointlist
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|y
operator|*
name|antialias
argument_list|)
expr_stmt|;
block|}
name|TRC
argument_list|(
operator|(
literal|"[] %g,%g -> %g,%g\n"
operator|,
name|pointlist
index|[
literal|0
index|]
operator|.
name|x
operator|,
name|pointlist
index|[
literal|0
index|]
operator|.
name|y
operator|,
name|pointlist
index|[
name|npoints
operator|-
literal|1
index|]
operator|.
name|x
operator|,
name|pointlist
index|[
name|npoints
operator|-
literal|1
index|]
operator|.
name|y
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|npoints
operator|>
literal|0
condition|)
block|{
name|sc
operator|->
name|got_last
operator|=
name|TRUE
expr_stmt|;
name|sc
operator|->
name|last
operator|=
name|pointlist
index|[
name|npoints
operator|-
literal|1
index|]
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* Scan convert the polygon described by the list of points passed to  * scan_convert_add_points, and return a channel with a bits set if  * they fall within the polygon defined.  The polygon is filled  * according to the even-odd rule.  The polygon is closed by  * joining the final point to the initial point.  */
end_comment

begin_function
name|GimpChannel
modifier|*
DECL|function|scan_converter_to_channel (ScanConverter * sc,GimpImage * gimage)
name|scan_converter_to_channel
parameter_list|(
name|ScanConverter
modifier|*
name|sc
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|PixelRegion
name|maskPR
decl_stmt|;
name|guint
name|widtha
decl_stmt|;
name|guint
name|heighta
decl_stmt|;
name|guint
name|antialias
decl_stmt|;
name|guint
name|antialias2
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
modifier|*
name|b
decl_stmt|;
name|gint
modifier|*
name|vals
decl_stmt|;
name|gint
name|val
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|x2
decl_stmt|,
name|w
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|antialias
operator|=
name|sc
operator|->
name|antialias
expr_stmt|;
name|antialias2
operator|=
name|antialias
operator|*
name|antialias
expr_stmt|;
comment|/*  do we need to close the polygon? */
if|if
condition|(
name|sc
operator|->
name|got_first
operator|&&
name|sc
operator|->
name|got_last
operator|&&
operator|(
name|sc
operator|->
name|first
operator|.
name|x
operator|!=
name|sc
operator|->
name|last
operator|.
name|x
operator|||
name|sc
operator|->
name|first
operator|.
name|y
operator|!=
name|sc
operator|->
name|last
operator|.
name|y
operator|)
condition|)
block|{
name|convert_segment
argument_list|(
name|sc
argument_list|,
operator|(
name|int
operator|)
name|sc
operator|->
name|last
operator|.
name|x
operator|*
name|antialias
argument_list|,
operator|(
name|int
operator|)
name|sc
operator|->
name|last
operator|.
name|y
operator|*
name|antialias
argument_list|,
operator|(
name|int
operator|)
name|sc
operator|->
name|first
operator|.
name|x
operator|*
name|antialias
argument_list|,
operator|(
name|int
operator|)
name|sc
operator|->
name|first
operator|.
name|y
operator|*
name|antialias
argument_list|)
expr_stmt|;
block|}
name|mask
operator|=
name|gimp_channel_new_mask
argument_list|(
name|gimage
argument_list|,
name|sc
operator|->
name|width
argument_list|,
name|sc
operator|->
name|height
argument_list|)
expr_stmt|;
name|buf
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|sc
operator|->
name|width
argument_list|)
expr_stmt|;
name|widtha
operator|=
name|sc
operator|->
name|width
operator|*
name|antialias
expr_stmt|;
name|heighta
operator|=
name|sc
operator|->
name|height
operator|*
name|antialias
expr_stmt|;
comment|/* allocate value array  */
name|vals
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|widtha
argument_list|)
expr_stmt|;
comment|/* dump scanlines */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|heighta
condition|;
name|i
operator|++
control|)
block|{
name|list
operator|=
name|sc
operator|->
name|scanlines
index|[
name|i
index|]
expr_stmt|;
name|TRC
argument_list|(
operator|(
literal|"%03d: "
operator|,
name|i
operator|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|TRC
argument_list|(
operator|(
literal|"%3d "
operator|,
name|GPOINTER_TO_INT
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
name|TRC
argument_list|(
operator|(
literal|"\n"
operator|)
argument_list|)
expr_stmt|;
block|}
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|gimp_drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|heighta
condition|;
name|i
operator|++
control|)
block|{
name|list
operator|=
name|sc
operator|->
name|scanlines
index|[
name|i
index|]
expr_stmt|;
comment|/*  zero the vals array  */
if|if
condition|(
operator|!
operator|(
name|i
operator|%
name|antialias
operator|)
condition|)
name|memset
argument_list|(
name|vals
argument_list|,
literal|0
argument_list|,
name|widtha
operator|*
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|x
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|list
condition|)
block|{
name|g_message
argument_list|(
literal|"Cannot properly scanline convert polygon!\n"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  bounds checking  */
name|x
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|widtha
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|GPOINTER_TO_INT
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
literal|0
argument_list|,
name|widtha
argument_list|)
expr_stmt|;
name|w
operator|=
name|x2
operator|-
name|x
expr_stmt|;
if|if
condition|(
name|w
operator|>
literal|0
condition|)
block|{
if|if
condition|(
name|antialias
operator|==
literal|1
condition|)
block|{
name|gimp_channel_add_segment
argument_list|(
name|mask
argument_list|,
name|x
argument_list|,
name|i
argument_list|,
name|w
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|w
condition|;
name|j
operator|++
control|)
name|vals
index|[
name|j
operator|+
name|x
index|]
operator|+=
literal|255
expr_stmt|;
block|}
block|}
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|antialias
operator|!=
literal|1
operator|&&
operator|!
operator|(
operator|(
name|i
operator|+
literal|1
operator|)
operator|%
name|antialias
operator|)
condition|)
block|{
name|b
operator|=
name|buf
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|widtha
condition|;
name|j
operator|+=
name|antialias
control|)
block|{
name|val
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|antialias
condition|;
name|x
operator|++
control|)
name|val
operator|+=
name|vals
index|[
name|j
operator|+
name|x
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
call|(
name|guchar
call|)
argument_list|(
name|val
operator|/
name|antialias2
argument_list|)
expr_stmt|;
block|}
name|pixel_region_set_row
argument_list|(
operator|&
name|maskPR
argument_list|,
literal|0
argument_list|,
operator|(
name|i
operator|/
name|antialias
operator|)
argument_list|,
name|sc
operator|->
name|width
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|vals
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
return|return
name|mask
return|;
block|}
end_function

end_unit

