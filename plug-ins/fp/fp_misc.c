begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"fp.h"
end_include

begin_decl_stmt
specifier|extern
name|FP_Params
name|Current
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GDrawable
modifier|*
name|drawable
decl_stmt|,
modifier|*
name|mask
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ReducedImage
modifier|*
name|reduced
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|nudgeArray
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|colorSign
name|gint
name|colorSign
index|[
literal|3
index|]
index|[
name|ALL_PRIMARY
index|]
init|=
block|{
block|{
literal|1
block|,
operator|-
literal|1
block|,
operator|-
literal|1
block|,
operator|-
literal|1
block|,
literal|1
block|,
literal|1
block|}
block|,
block|{
operator|-
literal|1
block|,
literal|1
block|,
operator|-
literal|1
block|,
literal|1
block|,
literal|1
block|,
operator|-
literal|1
block|}
block|,
block|{
operator|-
literal|1
block|,
operator|-
literal|1
block|,
literal|1
block|,
literal|1
block|,
operator|-
literal|1
block|,
literal|1
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|initializeFilterPacks ()
name|void
name|initializeFilterPacks
parameter_list|()
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
for|for
control|(
name|j
operator|=
name|BY_HUE
init|;
name|j
operator|<
name|JUDGE_BY
condition|;
name|j
operator|++
control|)
block|{
name|Current
operator|.
name|redAdj
index|[
name|j
index|]
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
name|Current
operator|.
name|greenAdj
index|[
name|j
index|]
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
name|Current
operator|.
name|blueAdj
index|[
name|j
index|]
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
name|Current
operator|.
name|satAdj
index|[
name|j
index|]
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|resetFilterPacks ()
name|void
name|resetFilterPacks
parameter_list|()
block|{
name|initializeFilterPacks
argument_list|()
expr_stmt|;
name|refreshPreviews
argument_list|(
name|Current
operator|.
name|VisibleFrames
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|Reduce_The_Image (GDrawable * drawable,GDrawable * mask,gint LongerSize,gint Slctn)
name|ReducedImage
modifier|*
name|Reduce_The_Image
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|GDrawable
modifier|*
name|mask
parameter_list|,
name|gint
name|LongerSize
parameter_list|,
name|gint
name|Slctn
parameter_list|)
block|{
name|gint
name|RH
decl_stmt|,
name|RW
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|,
name|bytes
init|=
name|drawable
operator|->
name|bpp
decl_stmt|;
name|ReducedImage
modifier|*
name|temp
init|=
operator|(
name|ReducedImage
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ReducedImage
argument_list|)
argument_list|)
decl_stmt|;
name|guchar
modifier|*
name|tempRGB
decl_stmt|,
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|tempmask
decl_stmt|,
modifier|*
name|src_mask_row
decl_stmt|,
name|R
decl_stmt|,
name|G
decl_stmt|,
name|B
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|whichcol
decl_stmt|,
name|whichrow
decl_stmt|,
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|GPixelRgn
name|srcPR
decl_stmt|,
name|srcMask
decl_stmt|;
name|gint
name|NoSelectionMade
init|=
name|TRUE
decl_stmt|;
name|hsv
modifier|*
name|tempHSV
decl_stmt|,
name|H
decl_stmt|,
name|S
decl_stmt|,
name|V
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
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
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
if|if
condition|(
name|width
operator|!=
name|drawable
operator|->
name|width
operator|&&
name|height
operator|!=
name|drawable
operator|->
name|height
condition|)
name|NoSelectionMade
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|Slctn
operator|==
literal|0
condition|)
block|{
name|x1
operator|=
literal|0
expr_stmt|;
name|x2
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|y1
operator|=
literal|0
expr_stmt|;
name|y2
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
block|}
if|if
condition|(
name|Slctn
operator|==
literal|2
condition|)
block|{
name|x1
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|x1
operator|-
name|width
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MIN
argument_list|(
name|drawable
operator|->
name|width
argument_list|,
name|x2
operator|+
name|width
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|y1
operator|-
name|height
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MIN
argument_list|(
name|drawable
operator|->
name|height
argument_list|,
name|y2
operator|+
name|height
operator|/
literal|2.0
argument_list|)
expr_stmt|;
block|}
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
if|if
condition|(
name|width
operator|>
name|height
condition|)
block|{
name|RW
operator|=
name|LongerSize
expr_stmt|;
name|RH
operator|=
operator|(
name|float
operator|)
name|height
operator|*
operator|(
name|float
operator|)
name|LongerSize
operator|/
operator|(
name|float
operator|)
name|width
expr_stmt|;
block|}
else|else
block|{
name|RH
operator|=
name|LongerSize
expr_stmt|;
name|RW
operator|=
operator|(
name|float
operator|)
name|width
operator|*
operator|(
name|float
operator|)
name|LongerSize
operator|/
operator|(
name|float
operator|)
name|height
expr_stmt|;
block|}
name|tempRGB
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
name|RW
operator|*
name|RH
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|tempHSV
operator|=
operator|(
name|hsv
operator|*
operator|)
name|malloc
argument_list|(
name|RW
operator|*
name|RH
operator|*
name|bytes
operator|*
sizeof|sizeof
argument_list|(
name|hsv
argument_list|)
argument_list|)
expr_stmt|;
name|tempmask
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
name|RW
operator|*
name|RH
argument_list|)
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
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcMask
argument_list|,
name|mask
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|src_row
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|src_mask_row
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
name|width
operator|*
name|bytes
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
name|RH
condition|;
name|i
operator|++
control|)
block|{
name|whichrow
operator|=
operator|(
name|float
operator|)
name|i
operator|*
operator|(
name|float
operator|)
name|height
operator|/
operator|(
name|float
operator|)
name|RH
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|src_row
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
name|whichrow
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcMask
argument_list|,
name|src_mask_row
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
name|whichrow
argument_list|,
name|width
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|RW
condition|;
name|j
operator|++
control|)
block|{
name|whichcol
operator|=
operator|(
name|float
operator|)
name|j
operator|*
operator|(
name|float
operator|)
name|width
operator|/
operator|(
name|float
operator|)
name|RW
expr_stmt|;
if|if
condition|(
name|NoSelectionMade
condition|)
name|tempmask
index|[
name|i
operator|*
name|RW
operator|+
name|j
index|]
operator|=
literal|255
expr_stmt|;
else|else
name|tempmask
index|[
name|i
operator|*
name|RW
operator|+
name|j
index|]
operator|=
name|src_mask_row
index|[
name|whichcol
index|]
expr_stmt|;
name|R
operator|=
name|src_row
index|[
name|whichcol
operator|*
name|bytes
operator|+
literal|0
index|]
expr_stmt|;
name|G
operator|=
name|src_row
index|[
name|whichcol
operator|*
name|bytes
operator|+
literal|1
index|]
expr_stmt|;
name|B
operator|=
name|src_row
index|[
name|whichcol
operator|*
name|bytes
operator|+
literal|2
index|]
expr_stmt|;
name|H
operator|=
name|R
operator|/
literal|255.0
expr_stmt|;
name|S
operator|=
name|G
operator|/
literal|255.0
expr_stmt|;
name|V
operator|=
name|B
operator|/
literal|255.0
expr_stmt|;
name|gimp_rgb_to_hsv_double
argument_list|(
operator|&
name|H
argument_list|,
operator|&
name|S
argument_list|,
operator|&
name|V
argument_list|)
expr_stmt|;
name|tempRGB
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|0
index|]
operator|=
name|R
expr_stmt|;
name|tempRGB
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|1
index|]
operator|=
name|G
expr_stmt|;
name|tempRGB
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|2
index|]
operator|=
name|B
expr_stmt|;
name|tempHSV
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|0
index|]
operator|=
name|H
expr_stmt|;
name|tempHSV
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|1
index|]
operator|=
name|S
expr_stmt|;
name|tempHSV
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|2
index|]
operator|=
name|V
expr_stmt|;
if|if
condition|(
name|bytes
operator|==
literal|4
condition|)
name|tempRGB
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|3
index|]
operator|=
name|src_row
index|[
name|whichcol
operator|*
name|bytes
operator|+
literal|3
index|]
expr_stmt|;
block|}
block|}
name|temp
operator|->
name|width
operator|=
name|RW
expr_stmt|;
name|temp
operator|->
name|height
operator|=
name|RH
expr_stmt|;
name|temp
operator|->
name|rgb
operator|=
name|tempRGB
expr_stmt|;
name|temp
operator|->
name|hsv
operator|=
name|tempHSV
expr_stmt|;
name|temp
operator|->
name|mask
operator|=
name|tempmask
expr_stmt|;
return|return
name|temp
return|;
block|}
end_function

begin_comment
comment|/*************************************************************/
end_comment

begin_comment
comment|/************** The Preview Function *************************/
end_comment

begin_function
name|void
DECL|function|fp_render_preview (GtkWidget * preview,gint changewhat,gint changewhich)
name|fp_render_preview
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|gint
name|changewhat
parameter_list|,
name|gint
name|changewhich
parameter_list|)
block|{
name|guchar
modifier|*
name|a
decl_stmt|;
name|gint
name|Inten
decl_stmt|,
name|bytes
init|=
name|drawable
operator|->
name|bpp
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|,
name|nudge
decl_stmt|,
name|M
decl_stmt|,
name|m
decl_stmt|,
name|middle
decl_stmt|,
name|JudgeBy
decl_stmt|;
name|float
name|partial
decl_stmt|;
name|gint
name|RW
init|=
name|reduced
operator|->
name|width
decl_stmt|;
name|gint
name|RH
init|=
name|reduced
operator|->
name|height
decl_stmt|;
name|gint
name|backupP
index|[
literal|3
index|]
decl_stmt|,
name|P
index|[
literal|3
index|]
decl_stmt|,
name|tempSat
index|[
name|JUDGE_BY
index|]
index|[
literal|256
index|]
decl_stmt|;
name|a
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
name|bytes
operator|*
name|RW
argument_list|)
expr_stmt|;
if|if
condition|(
name|changewhat
operator|==
name|SATURATION
condition|)
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
literal|256
condition|;
name|k
operator|++
control|)
block|{
for|for
control|(
name|JudgeBy
operator|=
name|BY_HUE
init|;
name|JudgeBy
operator|<
name|JUDGE_BY
condition|;
name|JudgeBy
operator|++
control|)
name|tempSat
index|[
name|JudgeBy
index|]
index|[
name|k
index|]
operator|=
literal|0
expr_stmt|;
name|tempSat
index|[
name|Current
operator|.
name|ValueBy
index|]
index|[
name|k
index|]
operator|+=
name|changewhich
operator|*
name|nudgeArray
index|[
operator|(
name|k
operator|+
name|Current
operator|.
name|Offset
operator|)
operator|%
literal|256
index|]
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
name|RH
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|RW
condition|;
name|j
operator|++
control|)
block|{
name|backupP
index|[
literal|0
index|]
operator|=
name|P
index|[
literal|0
index|]
operator|=
operator|(
name|int
operator|)
name|reduced
operator|->
name|rgb
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|0
index|]
expr_stmt|;
name|backupP
index|[
literal|1
index|]
operator|=
name|P
index|[
literal|1
index|]
operator|=
operator|(
name|int
operator|)
name|reduced
operator|->
name|rgb
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|1
index|]
expr_stmt|;
name|backupP
index|[
literal|2
index|]
operator|=
name|P
index|[
literal|2
index|]
operator|=
operator|(
name|int
operator|)
name|reduced
operator|->
name|rgb
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|2
index|]
expr_stmt|;
name|m
operator|=
name|MIN
argument_list|(
name|MIN
argument_list|(
name|P
index|[
literal|0
index|]
argument_list|,
name|P
index|[
literal|1
index|]
argument_list|)
argument_list|,
name|P
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|M
operator|=
name|MAX
argument_list|(
name|MAX
argument_list|(
name|P
index|[
literal|0
index|]
argument_list|,
name|P
index|[
literal|1
index|]
argument_list|)
argument_list|,
name|P
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|middle
operator|=
operator|(
name|M
operator|+
name|m
operator|)
operator|/
literal|2
expr_stmt|;
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
if|if
condition|(
name|P
index|[
name|k
index|]
operator|!=
name|m
operator|&&
name|P
index|[
name|k
index|]
operator|!=
name|M
condition|)
name|middle
operator|=
name|P
index|[
name|k
index|]
expr_stmt|;
name|partial
operator|=
name|reduced
operator|->
name|mask
index|[
name|i
operator|*
name|RW
operator|+
name|j
index|]
operator|/
literal|255.0
expr_stmt|;
for|for
control|(
name|JudgeBy
operator|=
name|BY_HUE
init|;
name|JudgeBy
operator|<
name|JUDGE_BY
condition|;
name|JudgeBy
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|Current
operator|.
name|Touched
index|[
name|JudgeBy
index|]
condition|)
continue|continue;
name|Inten
operator|=
name|reduced
operator|->
name|hsv
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
name|JudgeBy
index|]
operator|*
literal|255.0
expr_stmt|;
comment|/*DO SATURATION FIRST*/
if|if
condition|(
name|changewhat
operator|!=
name|NONEATALL
condition|)
block|{
if|if
condition|(
name|M
operator|!=
name|m
condition|)
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
if|if
condition|(
name|backupP
index|[
name|k
index|]
operator|==
name|M
condition|)
name|P
index|[
name|k
index|]
operator|=
name|MAX
argument_list|(
name|P
index|[
name|k
index|]
operator|+
name|partial
operator|*
name|Current
operator|.
name|satAdj
index|[
name|JudgeBy
index|]
index|[
name|Inten
index|]
argument_list|,
name|middle
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|backupP
index|[
name|k
index|]
operator|==
name|m
condition|)
name|P
index|[
name|k
index|]
operator|=
name|MIN
argument_list|(
name|P
index|[
name|k
index|]
operator|-
name|partial
operator|*
name|Current
operator|.
name|satAdj
index|[
name|JudgeBy
index|]
index|[
name|Inten
index|]
argument_list|,
name|middle
argument_list|)
expr_stmt|;
block|}
name|P
index|[
literal|0
index|]
operator|+=
name|partial
operator|*
name|Current
operator|.
name|redAdj
index|[
name|JudgeBy
index|]
index|[
name|Inten
index|]
expr_stmt|;
name|P
index|[
literal|1
index|]
operator|+=
name|partial
operator|*
name|Current
operator|.
name|greenAdj
index|[
name|JudgeBy
index|]
index|[
name|Inten
index|]
expr_stmt|;
name|P
index|[
literal|2
index|]
operator|+=
name|partial
operator|*
name|Current
operator|.
name|blueAdj
index|[
name|JudgeBy
index|]
index|[
name|Inten
index|]
expr_stmt|;
block|}
block|}
name|Inten
operator|=
name|reduced
operator|->
name|hsv
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
name|Current
operator|.
name|ValueBy
index|]
operator|*
literal|255.0
expr_stmt|;
name|nudge
operator|=
name|partial
operator|*
name|nudgeArray
index|[
operator|(
name|Inten
operator|+
name|Current
operator|.
name|Offset
operator|)
operator|%
literal|256
index|]
expr_stmt|;
switch|switch
condition|(
name|changewhat
condition|)
block|{
case|case
name|HUE
case|:
name|P
index|[
literal|0
index|]
operator|+=
name|colorSign
index|[
name|RED
index|]
index|[
name|changewhich
index|]
operator|*
name|nudge
expr_stmt|;
name|P
index|[
literal|1
index|]
operator|+=
name|colorSign
index|[
name|GREEN
index|]
index|[
name|changewhich
index|]
operator|*
name|nudge
expr_stmt|;
name|P
index|[
literal|2
index|]
operator|+=
name|colorSign
index|[
name|BLUE
index|]
index|[
name|changewhich
index|]
operator|*
name|nudge
expr_stmt|;
break|break;
case|case
name|SATURATION
case|:
for|for
control|(
name|JudgeBy
operator|=
name|BY_HUE
init|;
name|JudgeBy
operator|<
name|JUDGE_BY
condition|;
name|JudgeBy
operator|++
control|)
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
if|if
condition|(
name|M
operator|!=
name|m
condition|)
block|{
if|if
condition|(
name|backupP
index|[
name|k
index|]
operator|==
name|M
condition|)
name|P
index|[
name|k
index|]
operator|=
name|MAX
argument_list|(
name|P
index|[
name|k
index|]
operator|+
name|partial
operator|*
name|tempSat
index|[
name|JudgeBy
index|]
index|[
name|Inten
index|]
argument_list|,
name|middle
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|backupP
index|[
name|k
index|]
operator|==
name|m
condition|)
name|P
index|[
name|k
index|]
operator|=
name|MIN
argument_list|(
name|P
index|[
name|k
index|]
operator|-
name|partial
operator|*
name|tempSat
index|[
name|JudgeBy
index|]
index|[
name|Inten
index|]
argument_list|,
name|middle
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|VALUE
case|:
name|P
index|[
literal|0
index|]
operator|+=
name|changewhich
operator|*
name|nudge
expr_stmt|;
name|P
index|[
literal|1
index|]
operator|+=
name|changewhich
operator|*
name|nudge
expr_stmt|;
name|P
index|[
literal|2
index|]
operator|+=
name|changewhich
operator|*
name|nudge
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|a
index|[
name|j
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|MIN
argument_list|(
name|P
index|[
literal|0
index|]
argument_list|,
literal|255
argument_list|)
argument_list|)
expr_stmt|;
name|a
index|[
name|j
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|MIN
argument_list|(
name|P
index|[
literal|1
index|]
argument_list|,
literal|255
argument_list|)
argument_list|)
expr_stmt|;
name|a
index|[
name|j
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|MIN
argument_list|(
name|P
index|[
literal|2
index|]
argument_list|,
literal|255
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|bytes
operator|==
literal|4
condition|)
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
name|float
name|transp
init|=
name|reduced
operator|->
name|rgb
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|3
index|]
operator|/
literal|255.0
decl_stmt|;
name|a
index|[
literal|3
operator|*
name|j
operator|+
name|k
index|]
operator|=
name|transp
operator|*
name|a
index|[
literal|3
operator|*
name|j
operator|+
name|k
index|]
operator|+
operator|(
literal|1
operator|-
name|transp
operator|)
operator|*
name|fp_fake_transparency
argument_list|(
name|i
argument_list|,
name|j
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|a
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|RW
argument_list|)
expr_stmt|;
block|}
name|free
argument_list|(
name|a
argument_list|)
expr_stmt|;
name|gtk_widget_draw
argument_list|(
name|preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|Update_Current_FP (gint changewhat,gint changewhich)
name|Update_Current_FP
parameter_list|(
name|gint
name|changewhat
parameter_list|,
name|gint
name|changewhich
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|nudge
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|fp_Create_Nudge
argument_list|(
name|nudgeArray
argument_list|)
expr_stmt|;
name|nudge
operator|=
name|nudgeArray
index|[
operator|(
name|i
operator|+
name|Current
operator|.
name|Offset
operator|)
operator|%
literal|256
index|]
expr_stmt|;
switch|switch
condition|(
name|changewhat
condition|)
block|{
case|case
name|HUE
case|:
name|Current
operator|.
name|redAdj
index|[
name|Current
operator|.
name|ValueBy
index|]
index|[
name|i
index|]
operator|+=
name|colorSign
index|[
name|RED
index|]
index|[
name|changewhich
index|]
operator|*
name|nudge
expr_stmt|;
name|Current
operator|.
name|greenAdj
index|[
name|Current
operator|.
name|ValueBy
index|]
index|[
name|i
index|]
operator|+=
name|colorSign
index|[
name|GREEN
index|]
index|[
name|changewhich
index|]
operator|*
name|nudge
expr_stmt|;
name|Current
operator|.
name|blueAdj
index|[
name|Current
operator|.
name|ValueBy
index|]
index|[
name|i
index|]
operator|+=
name|colorSign
index|[
name|BLUE
index|]
index|[
name|changewhich
index|]
operator|*
name|nudge
expr_stmt|;
break|break;
case|case
name|SATURATION
case|:
name|Current
operator|.
name|satAdj
index|[
name|Current
operator|.
name|ValueBy
index|]
index|[
name|i
index|]
operator|+=
name|changewhich
operator|*
name|nudge
expr_stmt|;
break|break;
case|case
name|VALUE
case|:
name|Current
operator|.
name|redAdj
index|[
name|Current
operator|.
name|ValueBy
index|]
index|[
name|i
index|]
operator|+=
name|changewhich
operator|*
name|nudge
expr_stmt|;
name|Current
operator|.
name|greenAdj
index|[
name|Current
operator|.
name|ValueBy
index|]
index|[
name|i
index|]
operator|+=
name|changewhich
operator|*
name|nudge
expr_stmt|;
name|Current
operator|.
name|blueAdj
index|[
name|Current
operator|.
name|ValueBy
index|]
index|[
name|i
index|]
operator|+=
name|changewhich
operator|*
name|nudge
expr_stmt|;
break|break;
default|default:
break|break;
block|}
comment|/* switch */
block|}
comment|/* for */
block|}
end_function

begin_function
name|void
DECL|function|fp_create_smoothness_graph (GtkWidget * preview)
name|fp_create_smoothness_graph
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
name|guchar
name|data
index|[
literal|256
operator|*
literal|3
index|]
decl_stmt|;
name|gint
name|nArray
index|[
literal|256
index|]
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|toBeBlack
decl_stmt|;
name|fp_Create_Nudge
argument_list|(
name|nArray
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
name|MAX_ROUGHNESS
condition|;
name|i
operator|++
control|)
block|{
name|int
name|coor
init|=
name|MAX_ROUGHNESS
operator|-
name|i
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|256
condition|;
name|j
operator|++
control|)
block|{
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|0
index|]
operator|=
literal|255
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|1
index|]
operator|=
literal|255
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|2
index|]
operator|=
literal|255
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|i
operator|%
operator|(
name|MAX_ROUGHNESS
operator|/
literal|4
operator|)
operator|)
condition|)
block|{
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|0
index|]
operator|=
literal|255
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|1
index|]
operator|=
literal|128
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|2
index|]
operator|=
literal|128
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
operator|(
name|j
operator|+
literal|1
operator|)
operator|%
literal|32
operator|)
condition|)
block|{
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|0
index|]
operator|=
literal|255
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|1
index|]
operator|=
literal|128
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|2
index|]
operator|=
literal|128
expr_stmt|;
block|}
name|toBeBlack
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|nArray
index|[
name|j
index|]
operator|==
name|coor
condition|)
name|toBeBlack
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|j
operator|<
literal|255
condition|)
block|{
name|int
name|jump
init|=
name|abs
argument_list|(
name|nArray
index|[
name|j
index|]
operator|-
name|nArray
index|[
name|j
operator|+
literal|1
index|]
argument_list|)
decl_stmt|;
if|if
condition|(
name|abs
argument_list|(
name|coor
operator|-
name|nArray
index|[
name|j
index|]
argument_list|)
operator|<
name|jump
operator|&&
name|abs
argument_list|(
name|coor
operator|-
name|nArray
index|[
name|j
operator|+
literal|1
index|]
argument_list|)
operator|<
name|jump
condition|)
name|toBeBlack
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|toBeBlack
condition|)
block|{
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|1
index|]
operator|=
literal|0
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|2
index|]
operator|=
literal|0
expr_stmt|;
block|}
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|data
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
literal|256
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_draw
argument_list|(
name|preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|fp_range_preview_spill (GtkWidget * preview,int type)
name|fp_range_preview_spill
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|int
name|type
parameter_list|)
block|{
name|guchar
name|data
index|[
literal|256
operator|*
literal|3
index|]
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|hsv
name|R
decl_stmt|,
name|G
decl_stmt|,
name|B
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|RANGE_HEIGHT
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|256
condition|;
name|j
operator|++
control|)
if|if
condition|(
operator|!
operator|(
operator|(
name|j
operator|+
literal|1
operator|)
operator|%
literal|32
operator|)
condition|)
block|{
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|0
index|]
operator|=
literal|255
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|1
index|]
operator|=
literal|128
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|2
index|]
operator|=
literal|128
expr_stmt|;
block|}
else|else
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|BY_VAL
case|:
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|0
index|]
operator|=
name|j
operator|-
name|Current
operator|.
name|Offset
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|1
index|]
operator|=
name|j
operator|-
name|Current
operator|.
name|Offset
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|2
index|]
operator|=
name|j
operator|-
name|Current
operator|.
name|Offset
expr_stmt|;
break|break;
case|case
name|BY_HUE
case|:
name|R
operator|=
call|(
name|hsv
call|)
argument_list|(
operator|(
name|j
operator|-
name|Current
operator|.
name|Offset
operator|+
literal|256
operator|)
operator|%
literal|256
argument_list|)
operator|/
literal|255.0
expr_stmt|;
name|G
operator|=
literal|1.0
expr_stmt|;
name|B
operator|=
literal|.5
expr_stmt|;
name|gimp_hsv_to_rgb_double
argument_list|(
operator|&
name|R
argument_list|,
operator|&
name|G
argument_list|,
operator|&
name|B
argument_list|)
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|0
index|]
operator|=
name|R
operator|*
literal|255
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|1
index|]
operator|=
name|G
operator|*
literal|255
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|2
index|]
operator|=
name|B
operator|*
literal|255
expr_stmt|;
break|break;
case|case
name|BY_SAT
case|:
name|R
operator|=
literal|.5
expr_stmt|;
name|G
operator|=
call|(
name|hsv
call|)
argument_list|(
operator|(
name|j
operator|-
operator|(
name|gint
operator|)
name|Current
operator|.
name|Offset
operator|+
literal|256
operator|)
operator|%
literal|256
argument_list|)
operator|/
literal|255.0
expr_stmt|;
name|B
operator|=
literal|.5
expr_stmt|;
name|gimp_hsv_to_rgb_double
argument_list|(
operator|&
name|R
argument_list|,
operator|&
name|G
argument_list|,
operator|&
name|B
argument_list|)
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|0
index|]
operator|=
name|R
operator|*
literal|255
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|1
index|]
operator|=
name|G
operator|*
literal|255
expr_stmt|;
name|data
index|[
literal|3
operator|*
name|j
operator|+
literal|2
index|]
operator|=
name|B
operator|*
literal|255
expr_stmt|;
break|break;
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|data
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
literal|256
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_draw
argument_list|(
name|preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
DECL|function|fp_Create_Nudge (gint * adjArray)
name|void
name|fp_Create_Nudge
parameter_list|(
name|gint
modifier|*
name|adjArray
parameter_list|)
block|{
name|int
name|left
decl_stmt|,
name|right
decl_stmt|,
name|middle
decl_stmt|,
name|i
decl_stmt|;
comment|/* The following function was determined by trial and error */
name|double
name|Steepness
init|=
name|pow
argument_list|(
literal|1
operator|-
name|Current
operator|.
name|Alias
argument_list|,
literal|4
argument_list|)
operator|*
literal|.8
decl_stmt|;
name|left
operator|=
operator|(
name|Current
operator|.
name|Range
operator|==
name|SHADOWS
operator|)
condition|?
literal|0
else|:
name|Current
operator|.
name|Cutoffs
index|[
name|Current
operator|.
name|Range
operator|-
literal|1
index|]
expr_stmt|;
name|right
operator|=
name|Current
operator|.
name|Cutoffs
index|[
name|Current
operator|.
name|Range
index|]
expr_stmt|;
name|middle
operator|=
operator|(
name|left
operator|+
name|right
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|Current
operator|.
name|Alias
operator|!=
literal|0
condition|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|i
operator|<=
name|middle
condition|)
name|adjArray
index|[
name|i
index|]
operator|=
name|MAX_ROUGHNESS
operator|*
name|Current
operator|.
name|Rough
operator|*
operator|(
literal|1
operator|+
name|tanh
argument_list|(
name|Steepness
operator|*
operator|(
name|i
operator|-
name|left
operator|)
argument_list|)
operator|)
operator|/
literal|2
expr_stmt|;
else|else
name|adjArray
index|[
name|i
index|]
operator|=
name|MAX_ROUGHNESS
operator|*
name|Current
operator|.
name|Rough
operator|*
operator|(
literal|1
operator|+
name|tanh
argument_list|(
name|Steepness
operator|*
operator|(
name|right
operator|-
name|i
operator|)
argument_list|)
operator|)
operator|/
literal|2
expr_stmt|;
else|else
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|left
operator|<=
name|i
operator|&&
name|i
operator|<=
name|right
condition|)
name|adjArray
index|[
name|i
index|]
operator|=
name|MAX_ROUGHNESS
operator|*
name|Current
operator|.
name|Rough
expr_stmt|;
else|else
name|adjArray
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
DECL|function|fp_fake_transparency (gint i,gint j)
name|gint
name|fp_fake_transparency
parameter_list|(
name|gint
name|i
parameter_list|,
name|gint
name|j
parameter_list|)
block|{
if|if
condition|(
operator|(
operator|(
name|i
operator|%
literal|20
operator|)
operator|-
literal|10
operator|)
operator|*
operator|(
operator|(
name|j
operator|%
literal|20
operator|)
operator|-
literal|10
operator|)
operator|>
literal|0
condition|)
return|return
literal|64
return|;
else|else
return|return
literal|196
return|;
block|}
end_function

end_unit

