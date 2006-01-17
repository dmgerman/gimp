begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*    flame - cosmic recursive fractal flames    Copyright (C) 1992  Scott Draves<spot@cs.cmu.edu>     This program is free software; you can redistribute it and/or modify    it under the terms of the GNU General Public License as published by    the Free Software Foundation; either version 2 of the License, or    (at your option) any later version.     This program is distributed in the hope that it will be useful,    but WITHOUT ANY WARRANTY; without even the implied warranty of    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    GNU General Public License for more details.     You should have received a copy of the GNU General Public License    along with this program; if not, write to the Free Software    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */
end_comment

begin_include
include|#
directive|include
file|"rect.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_comment
comment|/* for batch  *   interpolate  *   compute colormap  *   for subbatch  *     compute samples  *     buckets += cmap[samples]  *   accum += time_filter[batch] * log(buckets)  * image = filter(accum)  */
end_comment

begin_typedef
DECL|typedef|bucket
typedef|typedef
name|short
name|bucket
index|[
literal|4
index|]
typedef|;
end_typedef

begin_comment
comment|/* if you use longs instead of shorts, you    get higher quality, and spend more memory */
end_comment

begin_if
if|#
directive|if
literal|1
end_if

begin_typedef
DECL|typedef|accum_t
typedef|typedef
name|short
name|accum_t
typedef|;
end_typedef

begin_define
DECL|macro|MAXBUCKET
define|#
directive|define
name|MAXBUCKET
value|(1<<14)
end_define

begin_define
DECL|macro|SUB_BATCH_SIZE
define|#
directive|define
name|SUB_BATCH_SIZE
value|10000
end_define

begin_else
else|#
directive|else
end_else

begin_typedef
DECL|typedef|accum_t
typedef|typedef
name|long
name|accum_t
typedef|;
end_typedef

begin_define
DECL|macro|MAXBUCKET
define|#
directive|define
name|MAXBUCKET
value|(1<<30)
end_define

begin_define
DECL|macro|SUB_BATCH_SIZE
define|#
directive|define
name|SUB_BATCH_SIZE
value|10000
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|abucket
typedef|typedef
name|accum_t
name|abucket
index|[
literal|4
index|]
typedef|;
end_typedef

begin_comment
comment|/* allow this many iterations for settling into attractor */
end_comment

begin_define
DECL|macro|FUSE
define|#
directive|define
name|FUSE
value|15
end_define

begin_comment
comment|/* clamp spatial filter to zero at this std dev (2.5 ~= 0.0125) */
end_comment

begin_define
DECL|macro|FILTER_CUTOFF
define|#
directive|define
name|FILTER_CUTOFF
value|2.5
end_define

begin_comment
comment|/* should be MAXBUCKET / (OVERSAMPLE^2) */
end_comment

begin_define
DECL|macro|PREFILTER_WHITE
define|#
directive|define
name|PREFILTER_WHITE
value|(MAXBUCKET>>4)
end_define

begin_define
DECL|macro|bump_no_overflow (dest,delta,type)
define|#
directive|define
name|bump_no_overflow
parameter_list|(
name|dest
parameter_list|,
name|delta
parameter_list|,
name|type
parameter_list|)
value|{ \    type tt_ = dest + delta;            \    if (tt_> dest) dest = tt_;                 \ }
end_define

begin_comment
comment|/* sum of entries of vector to 1 */
end_comment

begin_function
DECL|function|normalize_vector (v,n)
name|void
name|normalize_vector
parameter_list|(
name|v
parameter_list|,
name|n
parameter_list|)
name|double
modifier|*
name|v
decl_stmt|;
name|int
name|n
decl_stmt|;
block|{
name|double
name|t
init|=
literal|0.0
decl_stmt|;
name|int
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
name|t
operator|+=
name|v
index|[
name|i
index|]
expr_stmt|;
name|t
operator|=
literal|1.0
operator|/
name|t
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
name|v
index|[
name|i
index|]
operator|*=
name|t
expr_stmt|;
block|}
end_function

begin_function
DECL|function|render_rectangle (spec,out,out_width,field,nchan,progress)
name|void
name|render_rectangle
parameter_list|(
name|spec
parameter_list|,
name|out
parameter_list|,
name|out_width
parameter_list|,
name|field
parameter_list|,
name|nchan
parameter_list|,
name|progress
parameter_list|)
name|frame_spec
modifier|*
name|spec
decl_stmt|;
name|unsigned
name|char
modifier|*
name|out
decl_stmt|;
name|int
name|out_width
decl_stmt|;
name|int
name|field
decl_stmt|;
name|int
name|nchan
decl_stmt|;
function|int progress
parameter_list|(
name|double
parameter_list|)
function|;
end_function

begin_block
block|{
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|,
name|nsamples
decl_stmt|,
name|nbuckets
decl_stmt|,
name|batch_size
decl_stmt|,
name|batch_num
decl_stmt|,
name|sub_batch
decl_stmt|;
name|bucket
modifier|*
name|buckets
decl_stmt|;
name|abucket
modifier|*
name|accumulate
decl_stmt|;
name|point
modifier|*
name|points
decl_stmt|;
name|double
modifier|*
name|filter
decl_stmt|,
modifier|*
name|temporal_filter
decl_stmt|,
modifier|*
name|temporal_deltas
decl_stmt|;
name|double
name|bounds
index|[
literal|4
index|]
decl_stmt|,
name|size
index|[
literal|2
index|]
decl_stmt|,
name|ppux
decl_stmt|,
name|ppuy
decl_stmt|;
name|int
name|image_width
decl_stmt|,
name|image_height
decl_stmt|;
comment|/* size of the image to produce */
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/* size of histogram */
name|int
name|filter_width
decl_stmt|;
name|int
name|oversample
init|=
name|spec
operator|->
name|cps
index|[
literal|0
index|]
operator|.
name|spatial_oversample
decl_stmt|;
name|int
name|nbatches
init|=
name|spec
operator|->
name|cps
index|[
literal|0
index|]
operator|.
name|nbatches
decl_stmt|;
name|bucket
name|cmap
index|[
name|CMAP_SIZE
index|]
decl_stmt|;
name|int
name|gutter_width
decl_stmt|;
name|int
name|sbc
decl_stmt|;
name|image_width
operator|=
name|spec
operator|->
name|cps
index|[
literal|0
index|]
operator|.
name|width
expr_stmt|;
if|if
condition|(
name|field
condition|)
block|{
name|image_height
operator|=
name|spec
operator|->
name|cps
index|[
literal|0
index|]
operator|.
name|height
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|field
operator|==
name|field_odd
condition|)
name|out
operator|+=
name|nchan
operator|*
name|out_width
expr_stmt|;
name|out_width
operator|*=
literal|2
expr_stmt|;
block|}
else|else
name|image_height
operator|=
name|spec
operator|->
name|cps
index|[
literal|0
index|]
operator|.
name|height
expr_stmt|;
if|if
condition|(
literal|1
condition|)
block|{
name|filter_width
operator|=
operator|(
literal|2.0
operator|*
name|FILTER_CUTOFF
operator|*
name|oversample
operator|*
name|spec
operator|->
name|cps
index|[
literal|0
index|]
operator|.
name|spatial_filter_radius
operator|)
expr_stmt|;
comment|/* make sure it has same parity as oversample */
if|if
condition|(
operator|(
name|filter_width
operator|^
name|oversample
operator|)
operator|&
literal|1
condition|)
name|filter_width
operator|++
expr_stmt|;
name|filter
operator|=
operator|(
name|double
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|double
argument_list|)
operator|*
name|filter_width
operator|*
name|filter_width
argument_list|)
expr_stmt|;
comment|/* fill in the coefs */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|filter_width
condition|;
name|i
operator|++
control|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|filter_width
condition|;
name|j
operator|++
control|)
block|{
name|double
name|ii
init|=
operator|(
operator|(
literal|2.0
operator|*
name|i
operator|+
literal|1.0
operator|)
operator|/
name|filter_width
operator|-
literal|1.0
operator|)
operator|*
name|FILTER_CUTOFF
decl_stmt|;
name|double
name|jj
init|=
operator|(
operator|(
literal|2.0
operator|*
name|j
operator|+
literal|1.0
operator|)
operator|/
name|filter_width
operator|-
literal|1.0
operator|)
operator|*
name|FILTER_CUTOFF
decl_stmt|;
if|if
condition|(
name|field
condition|)
name|jj
operator|*=
literal|2.0
expr_stmt|;
name|filter
index|[
name|i
operator|+
name|j
operator|*
name|filter_width
index|]
operator|=
name|exp
argument_list|(
operator|-
literal|2.0
operator|*
operator|(
name|ii
operator|*
name|ii
operator|+
name|jj
operator|*
name|jj
operator|)
argument_list|)
expr_stmt|;
block|}
name|normalize_vector
argument_list|(
name|filter
argument_list|,
name|filter_width
operator|*
name|filter_width
argument_list|)
expr_stmt|;
block|}
name|temporal_filter
operator|=
operator|(
name|double
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|double
argument_list|)
operator|*
name|nbatches
argument_list|)
expr_stmt|;
name|temporal_deltas
operator|=
operator|(
name|double
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|double
argument_list|)
operator|*
name|nbatches
argument_list|)
expr_stmt|;
if|if
condition|(
name|nbatches
operator|>
literal|1
condition|)
block|{
name|double
name|t
decl_stmt|;
comment|/* fill in the coefs */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nbatches
condition|;
name|i
operator|++
control|)
block|{
name|t
operator|=
name|temporal_deltas
index|[
name|i
index|]
operator|=
operator|(
literal|2.0
operator|*
operator|(
operator|(
name|double
operator|)
name|i
operator|/
operator|(
name|nbatches
operator|-
literal|1
operator|)
operator|)
operator|-
literal|1.0
operator|)
operator|*
name|spec
operator|->
name|temporal_filter_radius
expr_stmt|;
name|temporal_filter
index|[
name|i
index|]
operator|=
name|exp
argument_list|(
operator|-
literal|2.0
operator|*
name|t
operator|*
name|t
argument_list|)
expr_stmt|;
block|}
name|normalize_vector
argument_list|(
name|temporal_filter
argument_list|,
name|nbatches
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|temporal_filter
index|[
literal|0
index|]
operator|=
literal|1.0
expr_stmt|;
name|temporal_deltas
index|[
literal|0
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
if|#
directive|if
literal|0
block|for (j = 0; j< nbatches; j++)       fprintf(stderr, "%4f %4f\n", temporal_deltas[j], temporal_filter[j]);    fprintf(stderr, "\n");
endif|#
directive|endif
comment|/* the number of additional rows of buckets we put at the edge so       that the filter doesn't go off the edge */
name|gutter_width
operator|=
operator|(
name|filter_width
operator|-
name|oversample
operator|)
operator|/
literal|2
expr_stmt|;
name|height
operator|=
name|oversample
operator|*
name|image_height
operator|+
literal|2
operator|*
name|gutter_width
expr_stmt|;
name|width
operator|=
name|oversample
operator|*
name|image_width
operator|+
literal|2
operator|*
name|gutter_width
expr_stmt|;
name|nbuckets
operator|=
name|width
operator|*
name|height
expr_stmt|;
if|if
condition|(
literal|1
condition|)
block|{
specifier|static
name|char
modifier|*
name|last_block
init|=
name|NULL
decl_stmt|;
specifier|static
name|int
name|last_block_size
init|=
literal|0
decl_stmt|;
name|int
name|memory_rqd
init|=
operator|(
sizeof|sizeof
argument_list|(
name|bucket
argument_list|)
operator|*
name|nbuckets
operator|+
sizeof|sizeof
argument_list|(
name|abucket
argument_list|)
operator|*
name|nbuckets
operator|+
sizeof|sizeof
argument_list|(
name|point
argument_list|)
operator|*
name|SUB_BATCH_SIZE
operator|)
decl_stmt|;
if|if
condition|(
name|memory_rqd
operator|>
name|last_block_size
condition|)
block|{
if|if
condition|(
name|last_block
operator|!=
name|NULL
condition|)
name|free
argument_list|(
name|last_block
argument_list|)
expr_stmt|;
name|last_block
operator|=
operator|(
name|char
operator|*
operator|)
name|malloc
argument_list|(
name|memory_rqd
argument_list|)
expr_stmt|;
if|if
condition|(
name|NULL
operator|==
name|last_block
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"render_rectangle: cannot malloc %d bytes.\n"
argument_list|,
name|memory_rqd
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
comment|/* else fprintf(stderr, "render_rectangle: mallocked %dMb.\n", Mb); */
name|last_block_size
operator|=
name|memory_rqd
expr_stmt|;
block|}
name|buckets
operator|=
operator|(
name|bucket
operator|*
operator|)
name|last_block
expr_stmt|;
name|accumulate
operator|=
operator|(
name|abucket
operator|*
operator|)
operator|(
name|last_block
operator|+
sizeof|sizeof
argument_list|(
name|bucket
argument_list|)
operator|*
name|nbuckets
operator|)
expr_stmt|;
name|points
operator|=
operator|(
name|point
operator|*
operator|)
operator|(
name|last_block
operator|+
operator|(
sizeof|sizeof
argument_list|(
name|bucket
argument_list|)
operator|+
sizeof|sizeof
argument_list|(
name|abucket
argument_list|)
operator|)
operator|*
name|nbuckets
operator|)
expr_stmt|;
block|}
name|memset
argument_list|(
operator|(
name|char
operator|*
operator|)
name|accumulate
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|abucket
argument_list|)
operator|*
name|nbuckets
argument_list|)
expr_stmt|;
for|for
control|(
name|batch_num
operator|=
literal|0
init|;
name|batch_num
operator|<
name|nbatches
condition|;
name|batch_num
operator|++
control|)
block|{
name|double
name|batch_time
decl_stmt|;
name|double
name|sample_density
decl_stmt|;
name|control_point
name|cp
decl_stmt|;
name|memset
argument_list|(
operator|(
name|char
operator|*
operator|)
name|buckets
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|bucket
argument_list|)
operator|*
name|nbuckets
argument_list|)
expr_stmt|;
name|batch_time
operator|=
name|spec
operator|->
name|time
operator|+
name|temporal_deltas
index|[
name|batch_num
index|]
expr_stmt|;
comment|/* interpolate and get a control point */
name|interpolate
argument_list|(
name|spec
operator|->
name|cps
argument_list|,
name|spec
operator|->
name|ncps
argument_list|,
name|batch_time
argument_list|,
operator|&
name|cp
argument_list|)
expr_stmt|;
comment|/* compute the colormap entries.  the input colormap is 256 long with 	 entries from 0 to 1.0 */
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|CMAP_SIZE
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
literal|3
condition|;
name|k
operator|++
control|)
block|{
if|#
directive|if
literal|1
name|cmap
index|[
name|j
index|]
index|[
name|k
index|]
operator|=
call|(
name|int
call|)
argument_list|(
name|cp
operator|.
name|cmap
index|[
operator|(
name|j
operator|*
literal|256
operator|)
operator|/
name|CMAP_SIZE
index|]
index|[
name|k
index|]
operator|*
name|cp
operator|.
name|white_level
argument_list|)
expr_stmt|;
else|#
directive|else
comment|/* monochrome if you don't have any cmaps */
name|cmap
index|[
name|j
index|]
index|[
name|k
index|]
operator|=
name|cp
operator|.
name|white_level
expr_stmt|;
endif|#
directive|endif
block|}
name|cmap
index|[
name|j
index|]
index|[
literal|3
index|]
operator|=
name|cp
operator|.
name|white_level
expr_stmt|;
block|}
comment|/* compute camera */
if|if
condition|(
literal|1
condition|)
block|{
name|double
name|t0
decl_stmt|,
name|t1
decl_stmt|,
name|shift
init|=
literal|0.0
decl_stmt|,
name|corner0
decl_stmt|,
name|corner1
decl_stmt|;
name|double
name|scale
decl_stmt|;
name|scale
operator|=
name|pow
argument_list|(
literal|2.0
argument_list|,
name|cp
operator|.
name|zoom
argument_list|)
expr_stmt|;
name|sample_density
operator|=
name|cp
operator|.
name|sample_density
operator|*
name|scale
operator|*
name|scale
expr_stmt|;
name|ppux
operator|=
name|cp
operator|.
name|pixels_per_unit
operator|*
name|scale
expr_stmt|;
name|ppuy
operator|=
name|field
condition|?
operator|(
name|ppux
operator|/
literal|2.0
operator|)
else|:
name|ppux
expr_stmt|;
switch|switch
condition|(
name|field
condition|)
block|{
case|case
name|field_both
case|:
name|shift
operator|=
literal|0.0
expr_stmt|;
break|break;
case|case
name|field_even
case|:
name|shift
operator|=
operator|-
literal|0.5
expr_stmt|;
break|break;
case|case
name|field_odd
case|:
name|shift
operator|=
literal|0.5
expr_stmt|;
break|break;
block|}
name|shift
operator|=
name|shift
operator|/
name|ppux
expr_stmt|;
name|t0
operator|=
operator|(
name|double
operator|)
name|gutter_width
operator|/
operator|(
name|oversample
operator|*
name|ppux
operator|)
expr_stmt|;
name|t1
operator|=
operator|(
name|double
operator|)
name|gutter_width
operator|/
operator|(
name|oversample
operator|*
name|ppuy
operator|)
expr_stmt|;
name|corner0
operator|=
name|cp
operator|.
name|center
index|[
literal|0
index|]
operator|-
name|image_width
operator|/
name|ppux
operator|/
literal|2.0
expr_stmt|;
name|corner1
operator|=
name|cp
operator|.
name|center
index|[
literal|1
index|]
operator|-
name|image_height
operator|/
name|ppuy
operator|/
literal|2.0
expr_stmt|;
name|bounds
index|[
literal|0
index|]
operator|=
name|corner0
operator|-
name|t0
expr_stmt|;
name|bounds
index|[
literal|1
index|]
operator|=
name|corner1
operator|-
name|t1
operator|+
name|shift
expr_stmt|;
name|bounds
index|[
literal|2
index|]
operator|=
name|corner0
operator|+
name|image_width
operator|/
name|ppux
operator|+
name|t0
expr_stmt|;
name|bounds
index|[
literal|3
index|]
operator|=
name|corner1
operator|+
name|image_height
operator|/
name|ppuy
operator|+
name|t1
operator|+
name|shift
expr_stmt|;
name|size
index|[
literal|0
index|]
operator|=
literal|1.0
operator|/
operator|(
name|bounds
index|[
literal|2
index|]
operator|-
name|bounds
index|[
literal|0
index|]
operator|)
expr_stmt|;
name|size
index|[
literal|1
index|]
operator|=
literal|1.0
operator|/
operator|(
name|bounds
index|[
literal|3
index|]
operator|-
name|bounds
index|[
literal|1
index|]
operator|)
expr_stmt|;
block|}
name|nsamples
operator|=
call|(
name|int
call|)
argument_list|(
name|sample_density
operator|*
name|nbuckets
operator|/
operator|(
name|oversample
operator|*
name|oversample
operator|)
argument_list|)
expr_stmt|;
name|batch_size
operator|=
name|nsamples
operator|/
name|cp
operator|.
name|nbatches
expr_stmt|;
name|sbc
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|sub_batch
operator|=
literal|0
init|;
name|sub_batch
operator|<
name|batch_size
condition|;
name|sub_batch
operator|+=
name|SUB_BATCH_SIZE
control|)
block|{
if|if
condition|(
name|progress
operator|&&
operator|!
operator|(
name|sbc
operator|++
operator|&
literal|7
operator|)
condition|)
call|(
modifier|*
name|progress
call|)
argument_list|(
literal|0.5
operator|*
name|sub_batch
operator|/
operator|(
name|double
operator|)
name|batch_size
argument_list|)
expr_stmt|;
comment|/* generate a sub_batch_size worth of samples */
name|points
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
name|random_uniform11
argument_list|()
expr_stmt|;
name|points
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
name|random_uniform11
argument_list|()
expr_stmt|;
name|points
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
name|random_uniform01
argument_list|()
expr_stmt|;
name|iterate
argument_list|(
operator|&
name|cp
argument_list|,
name|SUB_BATCH_SIZE
argument_list|,
name|FUSE
argument_list|,
name|points
argument_list|)
expr_stmt|;
comment|/* merge them into buckets, looking up colors */
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|SUB_BATCH_SIZE
condition|;
name|j
operator|++
control|)
block|{
name|int
name|k
decl_stmt|,
name|color_index
decl_stmt|;
name|double
modifier|*
name|p
init|=
name|points
index|[
name|j
index|]
decl_stmt|;
name|bucket
modifier|*
name|b
decl_stmt|;
if|if
condition|(
name|p
index|[
literal|0
index|]
operator|<
name|bounds
index|[
literal|0
index|]
operator|||
name|p
index|[
literal|1
index|]
operator|<
name|bounds
index|[
literal|1
index|]
operator|||
name|p
index|[
literal|0
index|]
operator|>
name|bounds
index|[
literal|2
index|]
operator|||
name|p
index|[
literal|1
index|]
operator|>
name|bounds
index|[
literal|3
index|]
condition|)
continue|continue;
name|color_index
operator|=
call|(
name|int
call|)
argument_list|(
name|p
index|[
literal|2
index|]
operator|*
name|CMAP_SIZE
argument_list|)
expr_stmt|;
if|if
condition|(
name|color_index
operator|<
literal|0
condition|)
name|color_index
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|color_index
operator|>
operator|(
name|CMAP_SIZE
operator|-
literal|1
operator|)
condition|)
name|color_index
operator|=
name|CMAP_SIZE
operator|-
literal|1
expr_stmt|;
name|b
operator|=
name|buckets
operator|+
call|(
name|int
call|)
argument_list|(
name|width
operator|*
operator|(
name|p
index|[
literal|0
index|]
operator|-
name|bounds
index|[
literal|0
index|]
operator|)
operator|*
name|size
index|[
literal|0
index|]
argument_list|)
operator|+
name|width
operator|*
call|(
name|int
call|)
argument_list|(
name|height
operator|*
operator|(
name|p
index|[
literal|1
index|]
operator|-
name|bounds
index|[
literal|1
index|]
operator|)
operator|*
name|size
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
literal|4
condition|;
name|k
operator|++
control|)
name|bump_no_overflow
argument_list|(
name|b
index|[
literal|0
index|]
index|[
name|k
index|]
argument_list|,
name|cmap
index|[
name|color_index
index|]
index|[
name|k
index|]
argument_list|,
name|short
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
literal|1
condition|)
block|{
name|double
name|k1
init|=
operator|(
name|cp
operator|.
name|contrast
operator|*
name|cp
operator|.
name|brightness
operator|*
name|PREFILTER_WHITE
operator|*
literal|268.0
operator|*
name|temporal_filter
index|[
name|batch_num
index|]
operator|)
operator|/
literal|256
decl_stmt|;
name|double
name|area
init|=
name|image_width
operator|*
name|image_height
operator|/
operator|(
name|ppux
operator|*
name|ppuy
operator|)
decl_stmt|;
name|double
name|k2
init|=
operator|(
name|oversample
operator|*
name|oversample
operator|*
name|nbatches
operator|)
operator|/
operator|(
name|cp
operator|.
name|contrast
operator|*
name|area
operator|*
name|cp
operator|.
name|white_level
operator|*
name|sample_density
operator|)
decl_stmt|;
comment|/* log intensity in hsv space */
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|height
condition|;
name|j
operator|++
control|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
condition|;
name|i
operator|++
control|)
block|{
name|abucket
modifier|*
name|a
init|=
name|accumulate
operator|+
name|i
operator|+
name|j
operator|*
name|width
decl_stmt|;
name|bucket
modifier|*
name|b
init|=
name|buckets
operator|+
name|i
operator|+
name|j
operator|*
name|width
decl_stmt|;
name|double
name|c
index|[
literal|4
index|]
decl_stmt|,
name|ls
decl_stmt|;
name|c
index|[
literal|0
index|]
operator|=
operator|(
name|double
operator|)
name|b
index|[
literal|0
index|]
index|[
literal|0
index|]
expr_stmt|;
name|c
index|[
literal|1
index|]
operator|=
operator|(
name|double
operator|)
name|b
index|[
literal|0
index|]
index|[
literal|1
index|]
expr_stmt|;
name|c
index|[
literal|2
index|]
operator|=
operator|(
name|double
operator|)
name|b
index|[
literal|0
index|]
index|[
literal|2
index|]
expr_stmt|;
name|c
index|[
literal|3
index|]
operator|=
operator|(
name|double
operator|)
name|b
index|[
literal|0
index|]
index|[
literal|3
index|]
expr_stmt|;
if|if
condition|(
literal|0.0
operator|==
name|c
index|[
literal|3
index|]
condition|)
continue|continue;
name|ls
operator|=
operator|(
name|k1
operator|*
name|log
argument_list|(
literal|1.0
operator|+
name|c
index|[
literal|3
index|]
operator|*
name|k2
argument_list|)
operator|)
operator|/
name|c
index|[
literal|3
index|]
expr_stmt|;
name|c
index|[
literal|0
index|]
operator|*=
name|ls
expr_stmt|;
name|c
index|[
literal|1
index|]
operator|*=
name|ls
expr_stmt|;
name|c
index|[
literal|2
index|]
operator|*=
name|ls
expr_stmt|;
name|c
index|[
literal|3
index|]
operator|*=
name|ls
expr_stmt|;
name|bump_no_overflow
argument_list|(
name|a
index|[
literal|0
index|]
index|[
literal|0
index|]
argument_list|,
name|c
index|[
literal|0
index|]
operator|+
literal|0.5
argument_list|,
name|accum_t
argument_list|)
expr_stmt|;
name|bump_no_overflow
argument_list|(
name|a
index|[
literal|0
index|]
index|[
literal|1
index|]
argument_list|,
name|c
index|[
literal|1
index|]
operator|+
literal|0.5
argument_list|,
name|accum_t
argument_list|)
expr_stmt|;
name|bump_no_overflow
argument_list|(
name|a
index|[
literal|0
index|]
index|[
literal|2
index|]
argument_list|,
name|c
index|[
literal|2
index|]
operator|+
literal|0.5
argument_list|,
name|accum_t
argument_list|)
expr_stmt|;
name|bump_no_overflow
argument_list|(
name|a
index|[
literal|0
index|]
index|[
literal|3
index|]
argument_list|,
name|c
index|[
literal|3
index|]
operator|+
literal|0.5
argument_list|,
name|accum_t
argument_list|)
expr_stmt|;
block|}
block|}
block|}
comment|/*     * filter the accumulation buffer down into the image     */
if|if
condition|(
literal|1
condition|)
block|{
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|double
name|t
index|[
literal|4
index|]
decl_stmt|;
name|double
name|g
init|=
literal|1.0
operator|/
name|spec
operator|->
name|cps
index|[
literal|0
index|]
operator|.
name|gamma
decl_stmt|;
name|y
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|image_height
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|progress
operator|&&
operator|!
operator|(
name|j
operator|&
literal|15
operator|)
condition|)
call|(
modifier|*
name|progress
call|)
argument_list|(
literal|0.5
operator|+
literal|0.5
operator|*
name|j
operator|/
operator|(
name|double
operator|)
name|image_height
argument_list|)
expr_stmt|;
name|x
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|image_width
condition|;
name|i
operator|++
control|)
block|{
name|int
name|ii
decl_stmt|,
name|jj
decl_stmt|,
name|a
decl_stmt|;
name|unsigned
name|char
modifier|*
name|p
decl_stmt|;
name|t
index|[
literal|0
index|]
operator|=
name|t
index|[
literal|1
index|]
operator|=
name|t
index|[
literal|2
index|]
operator|=
name|t
index|[
literal|3
index|]
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|ii
operator|=
literal|0
init|;
name|ii
operator|<
name|filter_width
condition|;
name|ii
operator|++
control|)
for|for
control|(
name|jj
operator|=
literal|0
init|;
name|jj
operator|<
name|filter_width
condition|;
name|jj
operator|++
control|)
block|{
name|double
name|k
init|=
name|filter
index|[
name|ii
operator|+
name|jj
operator|*
name|filter_width
index|]
decl_stmt|;
name|abucket
modifier|*
name|a
init|=
name|accumulate
operator|+
name|x
operator|+
name|ii
operator|+
operator|(
name|y
operator|+
name|jj
operator|)
operator|*
name|width
decl_stmt|;
name|t
index|[
literal|0
index|]
operator|+=
name|k
operator|*
name|a
index|[
literal|0
index|]
index|[
literal|0
index|]
expr_stmt|;
name|t
index|[
literal|1
index|]
operator|+=
name|k
operator|*
name|a
index|[
literal|0
index|]
index|[
literal|1
index|]
expr_stmt|;
name|t
index|[
literal|2
index|]
operator|+=
name|k
operator|*
name|a
index|[
literal|0
index|]
index|[
literal|2
index|]
expr_stmt|;
name|t
index|[
literal|3
index|]
operator|+=
name|k
operator|*
name|a
index|[
literal|0
index|]
index|[
literal|3
index|]
expr_stmt|;
block|}
name|p
operator|=
name|out
operator|+
name|nchan
operator|*
operator|(
name|i
operator|+
name|j
operator|*
name|out_width
operator|)
expr_stmt|;
name|a
operator|=
literal|256.0
operator|*
name|pow
argument_list|(
operator|(
name|double
operator|)
name|t
index|[
literal|0
index|]
operator|/
name|PREFILTER_WHITE
argument_list|,
name|g
argument_list|)
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
name|a
operator|<
literal|0
condition|)
name|a
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|a
operator|>
literal|255
condition|)
name|a
operator|=
literal|255
expr_stmt|;
name|p
index|[
literal|0
index|]
operator|=
name|a
expr_stmt|;
name|a
operator|=
literal|256.0
operator|*
name|pow
argument_list|(
operator|(
name|double
operator|)
name|t
index|[
literal|1
index|]
operator|/
name|PREFILTER_WHITE
argument_list|,
name|g
argument_list|)
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
name|a
operator|<
literal|0
condition|)
name|a
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|a
operator|>
literal|255
condition|)
name|a
operator|=
literal|255
expr_stmt|;
name|p
index|[
literal|1
index|]
operator|=
name|a
expr_stmt|;
name|a
operator|=
literal|256.0
operator|*
name|pow
argument_list|(
operator|(
name|double
operator|)
name|t
index|[
literal|2
index|]
operator|/
name|PREFILTER_WHITE
argument_list|,
name|g
argument_list|)
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
name|a
operator|<
literal|0
condition|)
name|a
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|a
operator|>
literal|255
condition|)
name|a
operator|=
literal|255
expr_stmt|;
name|p
index|[
literal|2
index|]
operator|=
name|a
expr_stmt|;
if|if
condition|(
name|nchan
operator|>
literal|3
condition|)
block|{
name|a
operator|=
literal|256.0
operator|*
name|pow
argument_list|(
operator|(
name|double
operator|)
name|t
index|[
literal|3
index|]
operator|/
name|PREFILTER_WHITE
argument_list|,
name|g
argument_list|)
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
name|a
operator|<
literal|0
condition|)
name|a
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|a
operator|>
literal|255
condition|)
name|a
operator|=
literal|255
expr_stmt|;
name|p
index|[
literal|3
index|]
operator|=
name|a
expr_stmt|;
block|}
name|x
operator|+=
name|oversample
expr_stmt|;
block|}
name|y
operator|+=
name|oversample
expr_stmt|;
block|}
block|}
name|free
argument_list|(
name|filter
argument_list|)
expr_stmt|;
block|}
end_block

end_unit

