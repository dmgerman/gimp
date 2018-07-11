begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationlayermode-composite.c  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *               2017 Ãyvind KolÃ¥s<pippin@gimp.org>  *               2017 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"../operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlayermode-composite.h"
end_include

begin_comment
comment|/*  non-subtractive compositing functions.  these functions expect comp[ALPHA]  *  to be the same as layer[ALPHA].  when in[ALPHA] or layer[ALPHA] are zero,  *  the value of comp[RED..BLUE] is unconstrained (in particular, it may be  *  NaN).  */
end_comment

begin_function
name|void
DECL|function|gimp_operation_layer_mode_composite_union (const gfloat * in,const gfloat * layer,const gfloat * comp,const gfloat * mask,gfloat opacity,gfloat * out,gint samples)
name|gimp_operation_layer_mode_composite_union
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|layer
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|comp
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gint
name|samples
parameter_list|)
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|new_alpha
decl_stmt|;
name|gfloat
name|in_alpha
init|=
name|in
index|[
name|ALPHA
index|]
decl_stmt|;
name|gfloat
name|layer_alpha
init|=
name|layer
index|[
name|ALPHA
index|]
operator|*
name|opacity
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|layer_alpha
operator|*=
operator|*
name|mask
expr_stmt|;
name|new_alpha
operator|=
name|layer_alpha
operator|+
operator|(
literal|1.0f
operator|-
name|layer_alpha
operator|)
operator|*
name|in_alpha
expr_stmt|;
if|if
condition|(
name|layer_alpha
operator|==
literal|0.0f
operator|||
name|new_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|in
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|in
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|in
index|[
name|BLUE
index|]
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|in_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|layer
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|layer
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|layer
index|[
name|BLUE
index|]
expr_stmt|;
block|}
else|else
block|{
name|gfloat
name|ratio
init|=
name|layer_alpha
operator|/
name|new_alpha
decl_stmt|;
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
name|out
index|[
name|b
index|]
operator|=
name|ratio
operator|*
operator|(
name|in_alpha
operator|*
operator|(
name|comp
index|[
name|b
index|]
operator|-
name|layer
index|[
name|b
index|]
operator|)
operator|+
name|layer
index|[
name|b
index|]
operator|-
name|in
index|[
name|b
index|]
operator|)
operator|+
name|in
index|[
name|b
index|]
expr_stmt|;
block|}
name|out
index|[
name|ALPHA
index|]
operator|=
name|new_alpha
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|layer
operator|+=
literal|4
expr_stmt|;
name|comp
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_operation_layer_mode_composite_clip_to_backdrop (const gfloat * in,const gfloat * layer,const gfloat * comp,const gfloat * mask,gfloat opacity,gfloat * out,gint samples)
name|gimp_operation_layer_mode_composite_clip_to_backdrop
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|layer
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|comp
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gint
name|samples
parameter_list|)
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|layer_alpha
init|=
name|comp
index|[
name|ALPHA
index|]
operator|*
name|opacity
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|layer_alpha
operator|*=
operator|*
name|mask
expr_stmt|;
if|if
condition|(
name|in
index|[
name|ALPHA
index|]
operator|==
literal|0.0f
operator|||
name|layer_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|in
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|in
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|in
index|[
name|BLUE
index|]
expr_stmt|;
block|}
else|else
block|{
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
name|out
index|[
name|b
index|]
operator|=
name|comp
index|[
name|b
index|]
operator|*
name|layer_alpha
operator|+
name|in
index|[
name|b
index|]
operator|*
operator|(
literal|1.0f
operator|-
name|layer_alpha
operator|)
expr_stmt|;
block|}
name|out
index|[
name|ALPHA
index|]
operator|=
name|in
index|[
name|ALPHA
index|]
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|comp
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_operation_layer_mode_composite_clip_to_layer (const gfloat * in,const gfloat * layer,const gfloat * comp,const gfloat * mask,gfloat opacity,gfloat * out,gint samples)
name|gimp_operation_layer_mode_composite_clip_to_layer
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|layer
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|comp
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gint
name|samples
parameter_list|)
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|layer_alpha
init|=
name|layer
index|[
name|ALPHA
index|]
operator|*
name|opacity
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|layer_alpha
operator|*=
operator|*
name|mask
expr_stmt|;
if|if
condition|(
name|layer_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|in
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|in
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|in
index|[
name|BLUE
index|]
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|in
index|[
name|ALPHA
index|]
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|layer
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|layer
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|layer
index|[
name|BLUE
index|]
expr_stmt|;
block|}
else|else
block|{
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
name|out
index|[
name|b
index|]
operator|=
name|comp
index|[
name|b
index|]
operator|*
name|in
index|[
name|ALPHA
index|]
operator|+
name|layer
index|[
name|b
index|]
operator|*
operator|(
literal|1.0f
operator|-
name|in
index|[
name|ALPHA
index|]
operator|)
expr_stmt|;
block|}
name|out
index|[
name|ALPHA
index|]
operator|=
name|layer_alpha
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|layer
operator|+=
literal|4
expr_stmt|;
name|comp
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_operation_layer_mode_composite_intersection (const gfloat * in,const gfloat * layer,const gfloat * comp,const gfloat * mask,gfloat opacity,gfloat * out,gint samples)
name|gimp_operation_layer_mode_composite_intersection
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|layer
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|comp
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gint
name|samples
parameter_list|)
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|new_alpha
init|=
name|in
index|[
name|ALPHA
index|]
operator|*
name|comp
index|[
name|ALPHA
index|]
operator|*
name|opacity
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|new_alpha
operator|*=
operator|*
name|mask
expr_stmt|;
if|if
condition|(
name|new_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|in
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|in
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|in
index|[
name|BLUE
index|]
expr_stmt|;
block|}
else|else
block|{
name|out
index|[
name|RED
index|]
operator|=
name|comp
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|comp
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|comp
index|[
name|BLUE
index|]
expr_stmt|;
block|}
name|out
index|[
name|ALPHA
index|]
operator|=
name|new_alpha
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|comp
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  subtractive compositing functions.  these functions expect comp[ALPHA] to  *  specify the modified alpha of the overlapping content, as a fraction of the  *  original overlapping content (i.e., an alpha of 1.0 specifies that no  *  content is subtracted.)  when in[ALPHA] or layer[ALPHA] are zero, the value  *  of comp[RED..BLUE] is unconstrained (in particular, it may be NaN).  */
end_comment

begin_function
name|void
DECL|function|gimp_operation_layer_mode_composite_union_sub (const gfloat * in,const gfloat * layer,const gfloat * comp,const gfloat * mask,gfloat opacity,gfloat * out,gint samples)
name|gimp_operation_layer_mode_composite_union_sub
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|layer
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|comp
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gint
name|samples
parameter_list|)
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|in_alpha
init|=
name|in
index|[
name|ALPHA
index|]
decl_stmt|;
name|gfloat
name|layer_alpha
init|=
name|layer
index|[
name|ALPHA
index|]
operator|*
name|opacity
decl_stmt|;
name|gfloat
name|comp_alpha
init|=
name|comp
index|[
name|ALPHA
index|]
decl_stmt|;
name|gfloat
name|new_alpha
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|layer_alpha
operator|*=
operator|*
name|mask
expr_stmt|;
name|new_alpha
operator|=
name|in_alpha
operator|+
name|layer_alpha
operator|-
operator|(
literal|2.0f
operator|-
name|comp_alpha
operator|)
operator|*
name|in_alpha
operator|*
name|layer_alpha
expr_stmt|;
if|if
condition|(
name|layer_alpha
operator|==
literal|0.0f
operator|||
name|new_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|in
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|in
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|in
index|[
name|BLUE
index|]
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|in_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|layer
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|layer
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|layer
index|[
name|BLUE
index|]
expr_stmt|;
block|}
else|else
block|{
name|gfloat
name|ratio
init|=
name|in_alpha
operator|/
name|new_alpha
decl_stmt|;
name|gfloat
name|layer_coeff
init|=
literal|1.0f
operator|/
name|in_alpha
operator|-
literal|1.0f
decl_stmt|;
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
name|out
index|[
name|b
index|]
operator|=
name|ratio
operator|*
operator|(
name|layer_alpha
operator|*
operator|(
name|comp_alpha
operator|*
name|comp
index|[
name|b
index|]
operator|+
name|layer_coeff
operator|*
name|layer
index|[
name|b
index|]
operator|-
name|in
index|[
name|b
index|]
operator|)
operator|+
name|in
index|[
name|b
index|]
operator|)
expr_stmt|;
block|}
name|out
index|[
name|ALPHA
index|]
operator|=
name|new_alpha
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|layer
operator|+=
literal|4
expr_stmt|;
name|comp
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_operation_layer_mode_composite_clip_to_backdrop_sub (const gfloat * in,const gfloat * layer,const gfloat * comp,const gfloat * mask,gfloat opacity,gfloat * out,gint samples)
name|gimp_operation_layer_mode_composite_clip_to_backdrop_sub
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|layer
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|comp
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gint
name|samples
parameter_list|)
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|layer_alpha
init|=
name|layer
index|[
name|ALPHA
index|]
operator|*
name|opacity
decl_stmt|;
name|gfloat
name|comp_alpha
init|=
name|comp
index|[
name|ALPHA
index|]
decl_stmt|;
name|gfloat
name|new_alpha
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|layer_alpha
operator|*=
operator|*
name|mask
expr_stmt|;
name|comp_alpha
operator|*=
name|layer_alpha
expr_stmt|;
name|new_alpha
operator|=
literal|1.0f
operator|-
name|layer_alpha
operator|+
name|comp_alpha
expr_stmt|;
if|if
condition|(
name|in
index|[
name|ALPHA
index|]
operator|==
literal|0.0f
operator|||
name|comp_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|in
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|in
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|in
index|[
name|BLUE
index|]
expr_stmt|;
block|}
else|else
block|{
name|gfloat
name|ratio
init|=
name|comp_alpha
operator|/
name|new_alpha
decl_stmt|;
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
name|out
index|[
name|b
index|]
operator|=
name|comp
index|[
name|b
index|]
operator|*
name|ratio
operator|+
name|in
index|[
name|b
index|]
operator|*
operator|(
literal|1.0f
operator|-
name|ratio
operator|)
expr_stmt|;
block|}
name|new_alpha
operator|*=
name|in
index|[
name|ALPHA
index|]
expr_stmt|;
name|out
index|[
name|ALPHA
index|]
operator|=
name|new_alpha
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|layer
operator|+=
literal|4
expr_stmt|;
name|comp
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_operation_layer_mode_composite_clip_to_layer_sub (const gfloat * in,const gfloat * layer,const gfloat * comp,const gfloat * mask,gfloat opacity,gfloat * out,gint samples)
name|gimp_operation_layer_mode_composite_clip_to_layer_sub
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|layer
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|comp
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gint
name|samples
parameter_list|)
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|in_alpha
init|=
name|in
index|[
name|ALPHA
index|]
decl_stmt|;
name|gfloat
name|layer_alpha
init|=
name|layer
index|[
name|ALPHA
index|]
operator|*
name|opacity
decl_stmt|;
name|gfloat
name|comp_alpha
init|=
name|comp
index|[
name|ALPHA
index|]
decl_stmt|;
name|gfloat
name|new_alpha
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|layer_alpha
operator|*=
operator|*
name|mask
expr_stmt|;
name|comp_alpha
operator|*=
name|in_alpha
expr_stmt|;
name|new_alpha
operator|=
literal|1.0f
operator|-
name|in_alpha
operator|+
name|comp_alpha
expr_stmt|;
if|if
condition|(
name|layer_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|in
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|in
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|in
index|[
name|BLUE
index|]
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|in_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|layer
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|layer
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|layer
index|[
name|BLUE
index|]
expr_stmt|;
block|}
else|else
block|{
name|gfloat
name|ratio
init|=
name|comp_alpha
operator|/
name|new_alpha
decl_stmt|;
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
name|out
index|[
name|b
index|]
operator|=
name|comp
index|[
name|b
index|]
operator|*
name|ratio
operator|+
name|layer
index|[
name|b
index|]
operator|*
operator|(
literal|1.0f
operator|-
name|ratio
operator|)
expr_stmt|;
block|}
name|new_alpha
operator|*=
name|layer_alpha
expr_stmt|;
name|out
index|[
name|ALPHA
index|]
operator|=
name|new_alpha
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|layer
operator|+=
literal|4
expr_stmt|;
name|comp
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_operation_layer_mode_composite_intersection_sub (const gfloat * in,const gfloat * layer,const gfloat * comp,const gfloat * mask,gfloat opacity,gfloat * out,gint samples)
name|gimp_operation_layer_mode_composite_intersection_sub
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|layer
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|comp
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gint
name|samples
parameter_list|)
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|new_alpha
init|=
name|in
index|[
name|ALPHA
index|]
operator|*
name|layer
index|[
name|ALPHA
index|]
operator|*
name|comp
index|[
name|ALPHA
index|]
operator|*
name|opacity
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|new_alpha
operator|*=
operator|*
name|mask
expr_stmt|;
if|if
condition|(
name|new_alpha
operator|==
literal|0.0f
condition|)
block|{
name|out
index|[
name|RED
index|]
operator|=
name|in
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|in
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|in
index|[
name|BLUE
index|]
expr_stmt|;
block|}
else|else
block|{
name|out
index|[
name|RED
index|]
operator|=
name|comp
index|[
name|RED
index|]
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|comp
index|[
name|GREEN
index|]
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|comp
index|[
name|BLUE
index|]
expr_stmt|;
block|}
name|out
index|[
name|ALPHA
index|]
operator|=
name|new_alpha
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|layer
operator|+=
literal|4
expr_stmt|;
name|comp
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

end_unit

