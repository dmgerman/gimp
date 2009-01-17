begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"color-balance.h"
end_include

begin_include
include|#
directive|include
file|"pixel-region.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|color_balance_transfer_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|transfer_initialized
specifier|static
name|gboolean
name|transfer_initialized
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  for lightening  */
end_comment

begin_decl_stmt
DECL|variable|highlights_add
specifier|static
name|gdouble
name|highlights_add
index|[
literal|256
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|midtones_add
specifier|static
name|gdouble
name|midtones_add
index|[
literal|256
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shadows_add
specifier|static
name|gdouble
name|shadows_add
index|[
literal|256
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  for darkening  */
end_comment

begin_decl_stmt
DECL|variable|highlights_sub
specifier|static
name|gdouble
name|highlights_sub
index|[
literal|256
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|midtones_sub
specifier|static
name|gdouble
name|midtones_sub
index|[
literal|256
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shadows_sub
specifier|static
name|gdouble
name|shadows_sub
index|[
literal|256
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|color_balance_init (ColorBalance * cb)
name|color_balance_init
parameter_list|(
name|ColorBalance
modifier|*
name|cb
parameter_list|)
block|{
name|GimpTransferMode
name|range
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|cb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|range
operator|=
name|GIMP_SHADOWS
init|;
name|range
operator|<=
name|GIMP_HIGHLIGHTS
condition|;
name|range
operator|++
control|)
block|{
name|cb
operator|->
name|cyan_red
index|[
name|range
index|]
operator|=
literal|0.0
expr_stmt|;
name|cb
operator|->
name|magenta_green
index|[
name|range
index|]
operator|=
literal|0.0
expr_stmt|;
name|cb
operator|->
name|yellow_blue
index|[
name|range
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
name|cb
operator|->
name|preserve_luminosity
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|color_balance_create_lookup_tables (ColorBalance * cb)
name|color_balance_create_lookup_tables
parameter_list|(
name|ColorBalance
modifier|*
name|cb
parameter_list|)
block|{
name|gdouble
modifier|*
name|cyan_red_transfer
index|[
literal|3
index|]
decl_stmt|;
name|gdouble
modifier|*
name|magenta_green_transfer
index|[
literal|3
index|]
decl_stmt|;
name|gdouble
modifier|*
name|yellow_blue_transfer
index|[
literal|3
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint32
name|r_n
decl_stmt|,
name|g_n
decl_stmt|,
name|b_n
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|cb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|transfer_initialized
condition|)
block|{
name|color_balance_transfer_init
argument_list|()
expr_stmt|;
name|transfer_initialized
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/*  Prepare the transfer arrays  (for speed)  */
name|cyan_red_transfer
index|[
name|GIMP_SHADOWS
index|]
operator|=
operator|(
name|cb
operator|->
name|cyan_red
index|[
name|GIMP_SHADOWS
index|]
operator|>
literal|0
operator|)
condition|?
name|shadows_add
else|:
name|shadows_sub
expr_stmt|;
name|cyan_red_transfer
index|[
name|GIMP_MIDTONES
index|]
operator|=
operator|(
name|cb
operator|->
name|cyan_red
index|[
name|GIMP_MIDTONES
index|]
operator|>
literal|0
operator|)
condition|?
name|midtones_add
else|:
name|midtones_sub
expr_stmt|;
name|cyan_red_transfer
index|[
name|GIMP_HIGHLIGHTS
index|]
operator|=
operator|(
name|cb
operator|->
name|cyan_red
index|[
name|GIMP_HIGHLIGHTS
index|]
operator|>
literal|0
operator|)
condition|?
name|highlights_add
else|:
name|highlights_sub
expr_stmt|;
name|magenta_green_transfer
index|[
name|GIMP_SHADOWS
index|]
operator|=
operator|(
name|cb
operator|->
name|magenta_green
index|[
name|GIMP_SHADOWS
index|]
operator|>
literal|0
operator|)
condition|?
name|shadows_add
else|:
name|shadows_sub
expr_stmt|;
name|magenta_green_transfer
index|[
name|GIMP_MIDTONES
index|]
operator|=
operator|(
name|cb
operator|->
name|magenta_green
index|[
name|GIMP_MIDTONES
index|]
operator|>
literal|0
operator|)
condition|?
name|midtones_add
else|:
name|midtones_sub
expr_stmt|;
name|magenta_green_transfer
index|[
name|GIMP_HIGHLIGHTS
index|]
operator|=
operator|(
name|cb
operator|->
name|magenta_green
index|[
name|GIMP_HIGHLIGHTS
index|]
operator|>
literal|0
operator|)
condition|?
name|highlights_add
else|:
name|highlights_sub
expr_stmt|;
name|yellow_blue_transfer
index|[
name|GIMP_SHADOWS
index|]
operator|=
operator|(
name|cb
operator|->
name|yellow_blue
index|[
name|GIMP_SHADOWS
index|]
operator|>
literal|0
operator|)
condition|?
name|shadows_add
else|:
name|shadows_sub
expr_stmt|;
name|yellow_blue_transfer
index|[
name|GIMP_MIDTONES
index|]
operator|=
operator|(
name|cb
operator|->
name|yellow_blue
index|[
name|GIMP_MIDTONES
index|]
operator|>
literal|0
operator|)
condition|?
name|midtones_add
else|:
name|midtones_sub
expr_stmt|;
name|yellow_blue_transfer
index|[
name|GIMP_HIGHLIGHTS
index|]
operator|=
operator|(
name|cb
operator|->
name|yellow_blue
index|[
name|GIMP_HIGHLIGHTS
index|]
operator|>
literal|0
operator|)
condition|?
name|highlights_add
else|:
name|highlights_sub
expr_stmt|;
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
name|r_n
operator|=
name|i
expr_stmt|;
name|g_n
operator|=
name|i
expr_stmt|;
name|b_n
operator|=
name|i
expr_stmt|;
name|r_n
operator|+=
operator|(
name|cb
operator|->
name|cyan_red
index|[
name|GIMP_SHADOWS
index|]
operator|*
name|cyan_red_transfer
index|[
name|GIMP_SHADOWS
index|]
index|[
name|r_n
index|]
operator|)
expr_stmt|;
name|r_n
operator|=
name|CLAMP0255
argument_list|(
name|r_n
argument_list|)
expr_stmt|;
name|r_n
operator|+=
operator|(
name|cb
operator|->
name|cyan_red
index|[
name|GIMP_MIDTONES
index|]
operator|*
name|cyan_red_transfer
index|[
name|GIMP_MIDTONES
index|]
index|[
name|r_n
index|]
operator|)
expr_stmt|;
name|r_n
operator|=
name|CLAMP0255
argument_list|(
name|r_n
argument_list|)
expr_stmt|;
name|r_n
operator|+=
operator|(
name|cb
operator|->
name|cyan_red
index|[
name|GIMP_HIGHLIGHTS
index|]
operator|*
name|cyan_red_transfer
index|[
name|GIMP_HIGHLIGHTS
index|]
index|[
name|r_n
index|]
operator|)
expr_stmt|;
name|r_n
operator|=
name|CLAMP0255
argument_list|(
name|r_n
argument_list|)
expr_stmt|;
name|g_n
operator|+=
operator|(
name|cb
operator|->
name|magenta_green
index|[
name|GIMP_SHADOWS
index|]
operator|*
name|magenta_green_transfer
index|[
name|GIMP_SHADOWS
index|]
index|[
name|g_n
index|]
operator|)
expr_stmt|;
name|g_n
operator|=
name|CLAMP0255
argument_list|(
name|g_n
argument_list|)
expr_stmt|;
name|g_n
operator|+=
operator|(
name|cb
operator|->
name|magenta_green
index|[
name|GIMP_MIDTONES
index|]
operator|*
name|magenta_green_transfer
index|[
name|GIMP_MIDTONES
index|]
index|[
name|g_n
index|]
operator|)
expr_stmt|;
name|g_n
operator|=
name|CLAMP0255
argument_list|(
name|g_n
argument_list|)
expr_stmt|;
name|g_n
operator|+=
operator|(
name|cb
operator|->
name|magenta_green
index|[
name|GIMP_HIGHLIGHTS
index|]
operator|*
name|magenta_green_transfer
index|[
name|GIMP_HIGHLIGHTS
index|]
index|[
name|g_n
index|]
operator|)
expr_stmt|;
name|g_n
operator|=
name|CLAMP0255
argument_list|(
name|g_n
argument_list|)
expr_stmt|;
name|b_n
operator|+=
operator|(
name|cb
operator|->
name|yellow_blue
index|[
name|GIMP_SHADOWS
index|]
operator|*
name|yellow_blue_transfer
index|[
name|GIMP_SHADOWS
index|]
index|[
name|b_n
index|]
operator|)
expr_stmt|;
name|b_n
operator|=
name|CLAMP0255
argument_list|(
name|b_n
argument_list|)
expr_stmt|;
name|b_n
operator|+=
operator|(
name|cb
operator|->
name|yellow_blue
index|[
name|GIMP_MIDTONES
index|]
operator|*
name|yellow_blue_transfer
index|[
name|GIMP_MIDTONES
index|]
index|[
name|b_n
index|]
operator|)
expr_stmt|;
name|b_n
operator|=
name|CLAMP0255
argument_list|(
name|b_n
argument_list|)
expr_stmt|;
name|b_n
operator|+=
operator|(
name|cb
operator|->
name|yellow_blue
index|[
name|GIMP_HIGHLIGHTS
index|]
operator|*
name|yellow_blue_transfer
index|[
name|GIMP_HIGHLIGHTS
index|]
index|[
name|b_n
index|]
operator|)
expr_stmt|;
name|b_n
operator|=
name|CLAMP0255
argument_list|(
name|b_n
argument_list|)
expr_stmt|;
name|cb
operator|->
name|r_lookup
index|[
name|i
index|]
operator|=
name|r_n
expr_stmt|;
name|cb
operator|->
name|g_lookup
index|[
name|i
index|]
operator|=
name|g_n
expr_stmt|;
name|cb
operator|->
name|b_lookup
index|[
name|i
index|]
operator|=
name|b_n
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|color_balance (ColorBalance * cb,PixelRegion * srcPR,PixelRegion * destPR)
name|color_balance
parameter_list|(
name|ColorBalance
modifier|*
name|cb
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|s
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|gboolean
name|alpha
decl_stmt|;
name|gint
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|r_n
decl_stmt|,
name|g_n
decl_stmt|,
name|b_n
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|h
operator|=
name|srcPR
operator|->
name|h
expr_stmt|;
name|src
operator|=
name|srcPR
operator|->
name|data
expr_stmt|;
name|dest
operator|=
name|destPR
operator|->
name|data
expr_stmt|;
name|alpha
operator|=
operator|(
name|srcPR
operator|->
name|bytes
operator|==
literal|4
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
while|while
condition|(
name|h
operator|--
condition|)
block|{
name|w
operator|=
name|srcPR
operator|->
name|w
expr_stmt|;
name|s
operator|=
name|src
expr_stmt|;
name|d
operator|=
name|dest
expr_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|r
operator|=
name|s
index|[
name|RED
index|]
expr_stmt|;
name|g
operator|=
name|s
index|[
name|GREEN
index|]
expr_stmt|;
name|b
operator|=
name|s
index|[
name|BLUE
index|]
expr_stmt|;
name|r_n
operator|=
name|cb
operator|->
name|r_lookup
index|[
name|r
index|]
expr_stmt|;
name|g_n
operator|=
name|cb
operator|->
name|g_lookup
index|[
name|g
index|]
expr_stmt|;
name|b_n
operator|=
name|cb
operator|->
name|b_lookup
index|[
name|b
index|]
expr_stmt|;
if|if
condition|(
name|cb
operator|->
name|preserve_luminosity
condition|)
block|{
name|gimp_rgb_to_hsl_int
argument_list|(
operator|&
name|r_n
argument_list|,
operator|&
name|g_n
argument_list|,
operator|&
name|b_n
argument_list|)
expr_stmt|;
name|b_n
operator|=
name|gimp_rgb_to_l_int
argument_list|(
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|gimp_hsl_to_rgb_int
argument_list|(
operator|&
name|r_n
argument_list|,
operator|&
name|g_n
argument_list|,
operator|&
name|b_n
argument_list|)
expr_stmt|;
block|}
name|d
index|[
name|RED
index|]
operator|=
name|r_n
expr_stmt|;
name|d
index|[
name|GREEN
index|]
operator|=
name|g_n
expr_stmt|;
name|d
index|[
name|BLUE
index|]
operator|=
name|b_n
expr_stmt|;
if|if
condition|(
name|alpha
condition|)
name|d
index|[
name|ALPHA
index|]
operator|=
name|s
index|[
name|ALPHA
index|]
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|->
name|bytes
expr_stmt|;
name|d
operator|+=
name|destPR
operator|->
name|bytes
expr_stmt|;
block|}
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|color_balance_transfer_init (void)
name|color_balance_transfer_init
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
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
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|low
init|=
operator|(
literal|1.075
operator|-
literal|1
operator|/
operator|(
operator|(
name|gdouble
operator|)
name|i
operator|/
literal|16.0
operator|+
literal|1
operator|)
operator|)
decl_stmt|;
name|gdouble
name|mid
init|=
literal|0.667
operator|*
operator|(
literal|1
operator|-
name|SQR
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|i
operator|-
literal|127.0
operator|)
operator|/
literal|127.0
argument_list|)
operator|)
decl_stmt|;
name|shadows_add
index|[
name|i
index|]
operator|=
name|low
expr_stmt|;
name|shadows_sub
index|[
literal|255
operator|-
name|i
index|]
operator|=
name|low
expr_stmt|;
name|midtones_add
index|[
name|i
index|]
operator|=
name|mid
expr_stmt|;
name|midtones_sub
index|[
name|i
index|]
operator|=
name|mid
expr_stmt|;
name|highlights_add
index|[
literal|255
operator|-
name|i
index|]
operator|=
name|low
expr_stmt|;
name|highlights_sub
index|[
name|i
index|]
operator|=
name|low
expr_stmt|;
block|}
block|}
end_function

end_unit

