begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpregioniterator.c  *  * FIXME: fix the following comment:  * Contains all kinds of miscellaneous routines factored out from different  * plug-ins. They stay here until their API has crystalized a bit and we can  * put them into the file where they belong (Maurits Rijk  *<lpeek.mrijk@consunet.nl> if you want to blame someone for this mess)  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpregioniterator.h"
end_include

begin_struct
DECL|struct|_GimpRgnIterator
struct|struct
name|_GimpRgnIterator
block|{
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|x1
DECL|member|y1
DECL|member|x2
DECL|member|y2
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_rgn_iterator_iter_single
parameter_list|(
name|GimpRgnIterator
modifier|*
name|iter
parameter_list|,
name|GimpPixelRgn
modifier|*
name|srcPR
parameter_list|,
name|GimpRgnFuncSrc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rgn_render_row
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|col
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|GimpRgnFunc2
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rgn_render_region
parameter_list|(
specifier|const
name|GimpPixelRgn
modifier|*
name|srcPR
parameter_list|,
specifier|const
name|GimpPixelRgn
modifier|*
name|destPR
parameter_list|,
name|GimpRgnFunc2
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_rgn_iterator_new:  * @drawable: a #GimpDrawable  * @unused:   ignored  *  * Creates a new #GimpRgnIterator for @drawable. The #GimpRunMode  * parameter is ignored.  *  * Return value: a newly allocated #GimpRgnIterator.  **/
end_comment

begin_function
name|GimpRgnIterator
modifier|*
DECL|function|gimp_rgn_iterator_new (GimpDrawable * drawable,GimpRunMode unused)
name|gimp_rgn_iterator_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRunMode
name|unused
parameter_list|)
block|{
name|GimpRgnIterator
modifier|*
name|iter
init|=
name|g_new
argument_list|(
name|GimpRgnIterator
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|iter
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|iter
operator|->
name|x1
argument_list|,
operator|&
name|iter
operator|->
name|y1
argument_list|,
operator|&
name|iter
operator|->
name|x2
argument_list|,
operator|&
name|iter
operator|->
name|y2
argument_list|)
expr_stmt|;
return|return
name|iter
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgn_iterator_free:  * @iter: a #GimpRgnIterator  *  * Frees the resources allocated for @iter.  **/
end_comment

begin_function
name|void
DECL|function|gimp_rgn_iterator_free (GimpRgnIterator * iter)
name|gimp_rgn_iterator_free
parameter_list|(
name|GimpRgnIterator
modifier|*
name|iter
parameter_list|)
block|{
name|g_free
argument_list|(
name|iter
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgn_iterator_src (GimpRgnIterator * iter,GimpRgnFuncSrc func,gpointer data)
name|gimp_rgn_iterator_src
parameter_list|(
name|GimpRgnIterator
modifier|*
name|iter
parameter_list|,
name|GimpRgnFuncSrc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
decl_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|iter
operator|->
name|drawable
argument_list|,
name|iter
operator|->
name|x1
argument_list|,
name|iter
operator|->
name|y1
argument_list|,
name|iter
operator|->
name|x2
operator|-
name|iter
operator|->
name|x1
argument_list|,
name|iter
operator|->
name|y2
operator|-
name|iter
operator|->
name|y1
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_rgn_iterator_iter_single
argument_list|(
name|iter
argument_list|,
operator|&
name|srcPR
argument_list|,
name|func
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgn_iterator_src_dest (GimpRgnIterator * iter,GimpRgnFuncSrcDest func,gpointer data)
name|gimp_rgn_iterator_src_dest
parameter_list|(
name|GimpRgnIterator
modifier|*
name|iter
parameter_list|,
name|GimpRgnFuncSrcDest
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
decl_stmt|,
name|destPR
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
name|bpp
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|gint
name|total_area
decl_stmt|;
name|gint
name|area_so_far
decl_stmt|;
name|x1
operator|=
name|iter
operator|->
name|x1
expr_stmt|;
name|y1
operator|=
name|iter
operator|->
name|y1
expr_stmt|;
name|x2
operator|=
name|iter
operator|->
name|x2
expr_stmt|;
name|y2
operator|=
name|iter
operator|->
name|y2
expr_stmt|;
name|total_area
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
name|area_so_far
operator|=
literal|0
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|iter
operator|->
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
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|iter
operator|->
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
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|srcPR
operator|.
name|bpp
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|gint
name|y
decl_stmt|;
name|guchar
modifier|*
name|src
init|=
name|srcPR
operator|.
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|destPR
operator|.
name|data
decl_stmt|;
for|for
control|(
name|y
operator|=
name|srcPR
operator|.
name|y
init|;
name|y
operator|<
name|srcPR
operator|.
name|y
operator|+
name|srcPR
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|gint
name|x
decl_stmt|;
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
for|for
control|(
name|x
operator|=
name|srcPR
operator|.
name|x
init|;
name|x
operator|<
name|srcPR
operator|.
name|x
operator|+
name|srcPR
operator|.
name|w
condition|;
name|x
operator|++
control|)
block|{
name|func
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|s
argument_list|,
name|d
argument_list|,
name|bpp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|s
operator|+=
name|bpp
expr_stmt|;
name|d
operator|+=
name|bpp
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|.
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|.
name|rowstride
expr_stmt|;
block|}
name|area_so_far
operator|+=
name|srcPR
operator|.
name|w
operator|*
name|srcPR
operator|.
name|h
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|area_so_far
operator|/
operator|(
name|gdouble
operator|)
name|total_area
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_flush
argument_list|(
name|iter
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|iter
operator|->
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|iter
operator|->
name|drawable
operator|->
name|drawable_id
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgn_iterator_dest (GimpRgnIterator * iter,GimpRgnFuncDest func,gpointer data)
name|gimp_rgn_iterator_dest
parameter_list|(
name|GimpRgnIterator
modifier|*
name|iter
parameter_list|,
name|GimpRgnFuncDest
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPixelRgn
name|destPR
decl_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|iter
operator|->
name|drawable
argument_list|,
name|iter
operator|->
name|x1
argument_list|,
name|iter
operator|->
name|y1
argument_list|,
name|iter
operator|->
name|x2
operator|-
name|iter
operator|->
name|x1
argument_list|,
name|iter
operator|->
name|y2
operator|-
name|iter
operator|->
name|y1
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_rgn_iterator_iter_single
argument_list|(
name|iter
argument_list|,
operator|&
name|destPR
argument_list|,
operator|(
name|GimpRgnFuncSrc
operator|)
name|func
argument_list|,
name|data
argument_list|)
expr_stmt|;
comment|/*  update the processed region  */
name|gimp_drawable_flush
argument_list|(
name|iter
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|iter
operator|->
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|iter
operator|->
name|drawable
operator|->
name|drawable_id
argument_list|,
name|iter
operator|->
name|x1
argument_list|,
name|iter
operator|->
name|y1
argument_list|,
name|iter
operator|->
name|x2
operator|-
name|iter
operator|->
name|x1
argument_list|,
name|iter
operator|->
name|y2
operator|-
name|iter
operator|->
name|y1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgn_iterate1 (GimpDrawable * drawable,GimpRunMode unused,GimpRgnFunc1 func,gpointer data)
name|gimp_rgn_iterate1
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRunMode
name|unused
parameter_list|,
name|GimpRgnFunc1
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
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
name|gpointer
name|pr
decl_stmt|;
name|gint
name|total_area
decl_stmt|;
name|gint
name|area_so_far
decl_stmt|;
name|gint
name|progress_skip
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
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
name|total_area
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
if|if
condition|(
name|total_area
operator|<=
literal|0
condition|)
return|return;
name|area_so_far
operator|=
literal|0
expr_stmt|;
name|progress_skip
operator|=
literal|0
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
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
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|srcPR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|guchar
modifier|*
name|src
init|=
name|srcPR
operator|.
name|data
decl_stmt|;
name|gint
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|srcPR
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|gint
name|x
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|srcPR
operator|.
name|w
condition|;
name|x
operator|++
control|)
block|{
name|func
argument_list|(
name|s
argument_list|,
name|srcPR
operator|.
name|bpp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|.
name|bpp
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|.
name|rowstride
expr_stmt|;
block|}
name|area_so_far
operator|+=
name|srcPR
operator|.
name|w
operator|*
name|srcPR
operator|.
name|h
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|progress_skip
operator|++
operator|)
operator|%
literal|10
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|area_so_far
operator|/
operator|(
name|gdouble
operator|)
name|total_area
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgn_iterate2 (GimpDrawable * drawable,GimpRunMode unused,GimpRgnFunc2 func,gpointer data)
name|gimp_rgn_iterate2
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRunMode
name|unused
parameter_list|,
name|GimpRgnFunc2
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
decl_stmt|,
name|destPR
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
name|gpointer
name|pr
decl_stmt|;
name|gint
name|total_area
decl_stmt|;
name|gint
name|area_so_far
decl_stmt|;
name|gint
name|progress_skip
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
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
name|total_area
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
if|if
condition|(
name|total_area
operator|<=
literal|0
condition|)
return|return;
name|area_so_far
operator|=
literal|0
expr_stmt|;
name|progress_skip
operator|=
literal|0
expr_stmt|;
comment|/* Initialize the pixel regions. */
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
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
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|drawable
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
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|gimp_rgn_render_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|,
name|func
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|area_so_far
operator|+=
name|srcPR
operator|.
name|w
operator|*
name|srcPR
operator|.
name|h
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|progress_skip
operator|++
operator|)
operator|%
literal|10
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|area_so_far
operator|/
operator|(
name|gdouble
operator|)
name|total_area
argument_list|)
expr_stmt|;
block|}
comment|/*  update the processed region  */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|drawable_id
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
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rgn_iterator_iter_single (GimpRgnIterator * iter,GimpPixelRgn * srcPR,GimpRgnFuncSrc func,gpointer data)
name|gimp_rgn_iterator_iter_single
parameter_list|(
name|GimpRgnIterator
modifier|*
name|iter
parameter_list|,
name|GimpPixelRgn
modifier|*
name|srcPR
parameter_list|,
name|GimpRgnFuncSrc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gpointer
name|pr
decl_stmt|;
name|gint
name|total_area
decl_stmt|;
name|gint
name|area_so_far
decl_stmt|;
name|total_area
operator|=
operator|(
name|iter
operator|->
name|x2
operator|-
name|iter
operator|->
name|x1
operator|)
operator|*
operator|(
name|iter
operator|->
name|y2
operator|-
name|iter
operator|->
name|y1
operator|)
expr_stmt|;
name|area_so_far
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
name|srcPR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|guchar
modifier|*
name|src
init|=
name|srcPR
operator|->
name|data
decl_stmt|;
name|gint
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
name|srcPR
operator|->
name|y
init|;
name|y
operator|<
name|srcPR
operator|->
name|y
operator|+
name|srcPR
operator|->
name|h
condition|;
name|y
operator|++
control|)
block|{
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|gint
name|x
decl_stmt|;
for|for
control|(
name|x
operator|=
name|srcPR
operator|->
name|x
init|;
name|x
operator|<
name|srcPR
operator|->
name|x
operator|+
name|srcPR
operator|->
name|w
condition|;
name|x
operator|++
control|)
block|{
name|func
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|s
argument_list|,
name|srcPR
operator|->
name|bpp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|->
name|bpp
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
block|}
name|area_so_far
operator|+=
name|srcPR
operator|->
name|w
operator|*
name|srcPR
operator|->
name|h
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|area_so_far
operator|/
operator|(
name|gdouble
operator|)
name|total_area
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rgn_render_row (guchar * src,guchar * dest,gint col,gint bpp,GimpRgnFunc2 func,gpointer data)
name|gimp_rgn_render_row
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|col
parameter_list|,
comment|/* row width in pixels */
name|gint
name|bpp
parameter_list|,
name|GimpRgnFunc2
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
while|while
condition|(
name|col
operator|--
condition|)
block|{
name|func
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|bpp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|src
operator|+=
name|bpp
expr_stmt|;
name|dest
operator|+=
name|bpp
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rgn_render_region (const GimpPixelRgn * srcPR,const GimpPixelRgn * destPR,GimpRgnFunc2 func,gpointer data)
name|gimp_rgn_render_region
parameter_list|(
specifier|const
name|GimpPixelRgn
modifier|*
name|srcPR
parameter_list|,
specifier|const
name|GimpPixelRgn
modifier|*
name|destPR
parameter_list|,
name|GimpRgnFunc2
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|guchar
modifier|*
name|src
init|=
name|srcPR
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|destPR
operator|->
name|data
decl_stmt|;
name|gint
name|row
decl_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|srcPR
operator|->
name|h
condition|;
name|row
operator|++
control|)
block|{
name|gimp_rgn_render_row
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|srcPR
operator|->
name|w
argument_list|,
name|srcPR
operator|->
name|bpp
argument_list|,
name|func
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

end_unit

