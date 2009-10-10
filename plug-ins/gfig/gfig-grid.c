begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"gfig.h"
end_include

begin_include
include|#
directive|include
file|"gfig-grid.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* For the isometric grid */
end_comment

begin_define
DECL|macro|SQRT3
define|#
directive|define
name|SQRT3
value|1.73205080756887729353
end_define

begin_comment
DECL|macro|SQRT3
comment|/* Square root of 3 */
end_comment

begin_define
DECL|macro|SIN_1o6PI_RAD
define|#
directive|define
name|SIN_1o6PI_RAD
value|0.5
end_define

begin_comment
DECL|macro|SIN_1o6PI_RAD
comment|/* Sine    1/6 Pi Radians */
end_comment

begin_define
DECL|macro|COS_1o6PI_RAD
define|#
directive|define
name|COS_1o6PI_RAD
value|SQRT3 / 2
end_define

begin_comment
DECL|macro|COS_1o6PI_RAD
comment|/* Cosine  1/6 Pi Radians */
end_comment

begin_define
DECL|macro|TAN_1o6PI_RAD
define|#
directive|define
name|TAN_1o6PI_RAD
value|1 / SQRT3
end_define

begin_comment
DECL|macro|TAN_1o6PI_RAD
comment|/* Tangent 1/6 Pi Radians == SIN / COS */
end_comment

begin_define
DECL|macro|RECIP_TAN_1o6PI_RAD
define|#
directive|define
name|RECIP_TAN_1o6PI_RAD
value|SQRT3
end_define

begin_comment
DECL|macro|RECIP_TAN_1o6PI_RAD
comment|/* Reciprocal of Tangent 1/6 Pi Radians */
end_comment

begin_decl_stmt
DECL|variable|grid_hightlight_drawgc
specifier|static
name|GdkGC
modifier|*
name|grid_hightlight_drawgc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|grid_gc_type
name|gint
name|grid_gc_type
init|=
name|GTK_STATE_NORMAL
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|draw_grid_polar
parameter_list|(
name|GdkGC
modifier|*
name|drawgc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|draw_grid_sq
parameter_list|(
name|GdkGC
modifier|*
name|drawgc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|draw_grid_iso
parameter_list|(
name|GdkGC
modifier|*
name|drawgc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkGC
modifier|*
name|gfig_get_grid_gc
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|gctype
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|find_grid_pos_polar
parameter_list|(
name|GdkPoint
modifier|*
name|p
parameter_list|,
name|GdkPoint
modifier|*
name|gp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/********** PrimeFactors for Shaneyfelt-style Polar Grid **********  * Quickly factor any number up to 17160  * Correctly factors numbers up to 131 * 131 - 1  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon297cd23f0108
block|{
DECL|member|product
name|gint
name|product
decl_stmt|;
DECL|member|remaining
name|gint
name|remaining
decl_stmt|;
DECL|member|current
name|gint
name|current
decl_stmt|;
DECL|member|next
name|gint
name|next
decl_stmt|;
DECL|member|index
name|gint
name|index
decl_stmt|;
DECL|typedef|PrimeFactors
block|}
name|PrimeFactors
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|primes
specifier|static
name|gchar
name|primes
index|[]
init|=
block|{
literal|2
block|,
literal|3
block|,
literal|5
block|,
literal|7
block|,
literal|11
block|,
literal|13
block|,
literal|17
block|,
literal|19
block|,
literal|23
block|,
literal|29
block|,
literal|31
block|,
literal|37
block|,
literal|41
block|,
literal|43
block|,
literal|47
block|,
literal|53
block|,
literal|59
block|,
literal|61
block|,
literal|67
block|,
literal|71
block|,
literal|73
block|,
literal|79
block|,
literal|83
block|,
literal|89
block|,
literal|97
block|,
literal|101
block|,
literal|103
block|,
literal|107
block|,
literal|109
block|,
literal|113
block|,
literal|127
block|}
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|PRIMES_MAX_INDEX
define|#
directive|define
name|PRIMES_MAX_INDEX
value|30
end_define

begin_function
specifier|static
name|gint
DECL|function|prime_factors_get (PrimeFactors * this)
name|prime_factors_get
parameter_list|(
name|PrimeFactors
modifier|*
name|this
parameter_list|)
block|{
name|this
operator|->
name|current
operator|=
name|this
operator|->
name|next
expr_stmt|;
while|while
condition|(
name|this
operator|->
name|index
operator|<=
name|PRIMES_MAX_INDEX
condition|)
block|{
if|if
condition|(
name|this
operator|->
name|remaining
operator|%
name|primes
index|[
name|this
operator|->
name|index
index|]
operator|==
literal|0
condition|)
comment|/* divisible */
block|{
name|this
operator|->
name|remaining
operator|/=
name|primes
index|[
name|this
operator|->
name|index
index|]
expr_stmt|;
name|this
operator|->
name|next
operator|=
name|primes
index|[
name|this
operator|->
name|index
index|]
expr_stmt|;
return|return
name|this
operator|->
name|current
return|;
block|}
name|this
operator|->
name|index
operator|++
expr_stmt|;
block|}
name|this
operator|->
name|next
operator|=
name|this
operator|->
name|remaining
expr_stmt|;
name|this
operator|->
name|remaining
operator|=
literal|1
expr_stmt|;
return|return
name|this
operator|->
name|current
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|prime_factors_lookahead (PrimeFactors * this)
name|prime_factors_lookahead
parameter_list|(
name|PrimeFactors
modifier|*
name|this
parameter_list|)
block|{
return|return
name|this
operator|->
name|next
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|prime_factors_reset (PrimeFactors * this)
name|prime_factors_reset
parameter_list|(
name|PrimeFactors
modifier|*
name|this
parameter_list|)
block|{
name|this
operator|->
name|remaining
operator|=
name|this
operator|->
name|product
expr_stmt|;
name|this
operator|->
name|index
operator|=
literal|0
expr_stmt|;
name|prime_factors_get
argument_list|(
name|this
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|PrimeFactors
modifier|*
DECL|function|prime_factors_new (gint n)
name|prime_factors_new
parameter_list|(
name|gint
name|n
parameter_list|)
block|{
name|PrimeFactors
modifier|*
name|this
init|=
name|g_new
argument_list|(
name|PrimeFactors
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|this
operator|->
name|product
operator|=
name|n
expr_stmt|;
name|prime_factors_reset
argument_list|(
name|this
argument_list|)
expr_stmt|;
return|return
name|this
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|prime_factors_delete (PrimeFactors * this)
name|prime_factors_delete
parameter_list|(
name|PrimeFactors
modifier|*
name|this
parameter_list|)
block|{
name|g_free
argument_list|(
name|this
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/********** ********** **********/
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|sector_size_at_radius (gdouble inner_radius)
name|sector_size_at_radius
parameter_list|(
name|gdouble
name|inner_radius
parameter_list|)
block|{
name|PrimeFactors
modifier|*
name|factors
init|=
name|prime_factors_new
argument_list|(
name|selvals
operator|.
name|opts
operator|.
name|grid_sectors_desired
argument_list|)
decl_stmt|;
name|gint
name|current_sectors
init|=
literal|1
decl_stmt|;
name|gdouble
name|sector_size
init|=
literal|2
operator|*
name|G_PI
operator|/
name|current_sectors
decl_stmt|;
while|while
condition|(
operator|(
name|current_sectors
operator|<
name|selvals
operator|.
name|opts
operator|.
name|grid_sectors_desired
operator|)
operator|&&
operator|(
name|inner_radius
operator|*
name|sector_size
operator|>
operator|(
name|prime_factors_lookahead
argument_list|(
name|factors
argument_list|)
operator|*
name|selvals
operator|.
name|opts
operator|.
name|grid_granularity
operator|)
operator|)
condition|)
block|{
name|current_sectors
operator|*=
name|prime_factors_get
argument_list|(
name|factors
argument_list|)
expr_stmt|;
name|sector_size
operator|=
literal|2
operator|*
name|G_PI
operator|/
name|current_sectors
expr_stmt|;
block|}
name|prime_factors_delete
argument_list|(
name|factors
argument_list|)
expr_stmt|;
return|return
name|sector_size
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|find_grid_pos_polar (GdkPoint * p,GdkPoint * gp)
name|find_grid_pos_polar
parameter_list|(
name|GdkPoint
modifier|*
name|p
parameter_list|,
name|GdkPoint
modifier|*
name|gp
parameter_list|)
block|{
name|gdouble
name|cx
init|=
name|preview_width
operator|/
literal|2.0
decl_stmt|;
name|gdouble
name|cy
init|=
name|preview_height
operator|/
literal|2.0
decl_stmt|;
name|gdouble
name|px
init|=
name|p
operator|->
name|x
operator|-
name|cx
decl_stmt|;
name|gdouble
name|py
init|=
name|p
operator|->
name|y
operator|-
name|cy
decl_stmt|;
name|gdouble
name|x
init|=
literal|0
decl_stmt|;
name|gdouble
name|y
init|=
literal|0
decl_stmt|;
name|gdouble
name|r
init|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|px
argument_list|)
operator|+
name|SQR
argument_list|(
name|py
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|r
operator|>=
name|selvals
operator|.
name|opts
operator|.
name|grid_radius_min
operator|*
literal|0.5
condition|)
block|{
name|gdouble
name|t
decl_stmt|;
name|gdouble
name|sectorSize
decl_stmt|;
name|r
operator|=
name|selvals
operator|.
name|opts
operator|.
name|grid_radius_interval
operator|*
call|(
name|gint
call|)
argument_list|(
literal|0.5
operator|+
operator|(
operator|(
name|r
operator|-
name|selvals
operator|.
name|opts
operator|.
name|grid_radius_min
operator|)
operator|/
name|selvals
operator|.
name|opts
operator|.
name|grid_radius_interval
operator|)
argument_list|)
operator|+
name|selvals
operator|.
name|opts
operator|.
name|grid_radius_min
expr_stmt|;
name|t
operator|=
name|atan2
argument_list|(
name|py
argument_list|,
name|px
argument_list|)
operator|+
literal|2
operator|*
name|G_PI
expr_stmt|;
name|sectorSize
operator|=
name|sector_size_at_radius
argument_list|(
name|r
argument_list|)
expr_stmt|;
name|t
operator|=
name|selvals
operator|.
name|opts
operator|.
name|grid_rotation
operator|+
call|(
name|gint
call|)
argument_list|(
literal|0.5
operator|+
operator|(
operator|(
name|t
operator|-
name|selvals
operator|.
name|opts
operator|.
name|grid_rotation
operator|)
operator|/
name|sectorSize
operator|)
argument_list|)
operator|*
name|sectorSize
expr_stmt|;
name|x
operator|=
name|r
operator|*
name|cos
argument_list|(
name|t
argument_list|)
expr_stmt|;
name|y
operator|=
name|r
operator|*
name|sin
argument_list|(
name|t
argument_list|)
expr_stmt|;
block|}
name|gp
operator|->
name|x
operator|=
name|x
operator|+
name|cx
expr_stmt|;
name|gp
operator|->
name|y
operator|=
name|y
operator|+
name|cy
expr_stmt|;
block|}
end_function

begin_comment
comment|/* find_grid_pos - Given an x, y point return the grid position of it */
end_comment

begin_comment
comment|/* return the new position in the passed point */
end_comment

begin_function
name|void
DECL|function|gfig_grid_colours (GtkWidget * widget)
name|gfig_grid_colours
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GdkColormap
modifier|*
name|colormap
decl_stmt|;
name|GdkGCValues
name|values
decl_stmt|;
name|GdkColor
name|col1
decl_stmt|;
name|GdkColor
name|col2
decl_stmt|;
name|guchar
name|stipple
index|[
literal|8
index|]
init|=
block|{
literal|0xAA
block|,
comment|/*  ####----  */
literal|0x55
block|,
comment|/*  ###----#  */
literal|0xAA
block|,
comment|/*  ##----##  */
literal|0x55
block|,
comment|/*  #----###  */
literal|0xAA
block|,
comment|/*  ----####  */
literal|0x55
block|,
comment|/*  ---####-  */
literal|0xAA
block|,
comment|/*  --####--  */
literal|0x55
block|,
comment|/*  -####---  */
block|}
decl_stmt|;
name|colormap
operator|=
name|gdk_screen_get_rgb_colormap
argument_list|(
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_color_parse
argument_list|(
literal|"gray50"
argument_list|,
operator|&
name|col1
argument_list|)
expr_stmt|;
name|gdk_colormap_alloc_color
argument_list|(
name|colormap
argument_list|,
operator|&
name|col1
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gdk_color_parse
argument_list|(
literal|"gray80"
argument_list|,
operator|&
name|col2
argument_list|)
expr_stmt|;
name|gdk_colormap_alloc_color
argument_list|(
name|colormap
argument_list|,
operator|&
name|col2
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|values
operator|.
name|background
operator|.
name|pixel
operator|=
name|col1
operator|.
name|pixel
expr_stmt|;
name|values
operator|.
name|foreground
operator|.
name|pixel
operator|=
name|col2
operator|.
name|pixel
expr_stmt|;
name|values
operator|.
name|fill
operator|=
name|GDK_OPAQUE_STIPPLED
expr_stmt|;
name|values
operator|.
name|stipple
operator|=
name|gdk_bitmap_create_from_data
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|stipple
argument_list|,
literal|4
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|grid_hightlight_drawgc
operator|=
name|gdk_gc_new_with_values
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|values
argument_list|,
name|GDK_GC_FOREGROUND
operator||
name|GDK_GC_BACKGROUND
operator||
name|GDK_GC_FILL
operator||
name|GDK_GC_STIPPLE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|find_grid_pos (GdkPoint * p,GdkPoint * gp,guint is_butt3)
name|find_grid_pos
parameter_list|(
name|GdkPoint
modifier|*
name|p
parameter_list|,
name|GdkPoint
modifier|*
name|gp
parameter_list|,
name|guint
name|is_butt3
parameter_list|)
block|{
name|gint16
name|x
init|=
name|p
operator|->
name|x
decl_stmt|;
name|gint16
name|y
init|=
name|p
operator|->
name|y
decl_stmt|;
specifier|static
name|GdkPoint
name|cons_pnt
decl_stmt|;
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|gridtype
operator|==
name|RECT_GRID
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|x
operator|%
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
operator|>
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
operator|/
literal|2
condition|)
name|x
operator|+=
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|y
operator|%
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
operator|>
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
operator|/
literal|2
condition|)
name|y
operator|+=
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
expr_stmt|;
name|gp
operator|->
name|x
operator|=
operator|(
name|x
operator|/
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
operator|)
operator|*
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
expr_stmt|;
name|gp
operator|->
name|y
operator|=
operator|(
name|y
operator|/
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
operator|)
operator|*
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
expr_stmt|;
if|if
condition|(
name|is_butt3
condition|)
block|{
if|if
condition|(
name|abs
argument_list|(
name|gp
operator|->
name|x
operator|-
name|cons_pnt
operator|.
name|x
argument_list|)
operator|<
name|abs
argument_list|(
name|gp
operator|->
name|y
operator|-
name|cons_pnt
operator|.
name|y
argument_list|)
condition|)
name|gp
operator|->
name|x
operator|=
name|cons_pnt
operator|.
name|x
expr_stmt|;
else|else
name|gp
operator|->
name|y
operator|=
name|cons_pnt
operator|.
name|y
expr_stmt|;
block|}
else|else
block|{
comment|/* Store the point since might be used later */
name|cons_pnt
operator|=
operator|*
name|gp
expr_stmt|;
comment|/* Structure copy */
block|}
block|}
elseif|else
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|gridtype
operator|==
name|POLAR_GRID
condition|)
block|{
name|find_grid_pos_polar
argument_list|(
name|p
argument_list|,
name|gp
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|gridtype
operator|==
name|ISO_GRID
condition|)
block|{
comment|/*        * This really needs a picture to show the math...        *        * Consider an isometric grid with one of the sets of lines        * parallel to the y axis (vertical alignment). Further define        * that the origin of a Cartesian grid is at a isometric vertex.        * For simplicity consider the first quadrant only.        *        *  - Let one line segment between vertices be r        *  - Define the value of r as the grid spacing        *  - Assign an integer n identifier to each vertical grid line        *    along the x axis.  with n=0 being the y axis. n can be any        *    integer        *  - Let m to be any integer         *  - Let h be the spacing between vertical grid lines measured        *    along the x axis.  It follows from the isometric grid that        *    h has a value of r * COS(1/6 Pi Rad)        *        *  Consider a Vertex V at the Cartesian location [Xv, Yv]        *        *   It follows that vertices belong to the set...        *   V[Xv, Yv] = [ [ n * h ] ,        *                 [ m * r + ( 0.5 * r (n % 2) ) ] ]        *   for all integers n and m        *        * Who cares? Me. It's useful in solving this problem:        * Consider an arbitrary point P[Xp,Yp], find the closest vertex        * in the set V.        *        * Restated this problem is "find values for m and n that are        * drive V closest to P"        *        * A Solution method (there may be a better one?):        *        * Step 1) bound n to the two closest values for Xp        *         n_lo = (int) (Xp / h)        *         n_hi = n_lo + 1        *        * Step 2) Consider the two closes vertices for each n_lo and        *         n_hi. The further of the vertices in each pair can        *         readily be discarded.        *        *         m_lo_n_lo = (int) ( (Yp / r) - 0.5 (n_lo % 2) )        *         m_hi_n_lo = m_lo_n_lo + 1        *        *         m_lo_n_hi = (int) ( (Yp / r) - 0.5 (n_hi % 2) )        *         m_hi_n_hi = m_hi_n_hi        *        * Step 3) compute the distance from P to V1 and V2. Snap to the        *         closer point.        */
name|gint
name|n_lo
decl_stmt|;
name|gint
name|n_hi
decl_stmt|;
name|gint
name|m_lo_n_lo
decl_stmt|;
name|gint
name|m_hi_n_lo
decl_stmt|;
name|gint
name|m_lo_n_hi
decl_stmt|;
name|gint
name|m_hi_n_hi
decl_stmt|;
name|gint
name|m_n_lo
decl_stmt|;
name|gint
name|m_n_hi
decl_stmt|;
name|gdouble
name|r
decl_stmt|;
name|gdouble
name|h
decl_stmt|;
name|gint
name|x1
decl_stmt|;
name|gint
name|x2
decl_stmt|;
name|gint
name|y1
decl_stmt|;
name|gint
name|y2
decl_stmt|;
name|r
operator|=
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
expr_stmt|;
name|h
operator|=
name|COS_1o6PI_RAD
operator|*
name|r
expr_stmt|;
name|n_lo
operator|=
operator|(
name|gint
operator|)
name|x
operator|/
name|h
expr_stmt|;
name|n_hi
operator|=
name|n_lo
operator|+
literal|1
expr_stmt|;
comment|/* evaluate m candidates for n_lo */
name|m_lo_n_lo
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|y
operator|/
name|r
operator|)
operator|-
literal|0.5
operator|*
operator|(
name|n_lo
operator|%
literal|2
operator|)
argument_list|)
expr_stmt|;
name|m_hi_n_lo
operator|=
name|m_lo_n_lo
operator|+
literal|1
expr_stmt|;
comment|/* figure out which is the better candidate */
if|if
condition|(
name|abs
argument_list|(
operator|(
name|m_lo_n_lo
operator|*
name|r
operator|+
operator|(
literal|0.5
operator|*
name|r
operator|*
operator|(
name|n_lo
operator|%
literal|2
operator|)
operator|)
operator|)
operator|-
name|y
argument_list|)
operator|<
name|abs
argument_list|(
operator|(
name|m_hi_n_lo
operator|*
name|r
operator|+
operator|(
literal|0.5
operator|*
name|r
operator|*
operator|(
name|n_lo
operator|%
literal|2
operator|)
operator|)
operator|)
operator|-
name|y
argument_list|)
condition|)
block|{
name|m_n_lo
operator|=
name|m_lo_n_lo
expr_stmt|;
block|}
else|else
block|{
name|m_n_lo
operator|=
name|m_hi_n_lo
expr_stmt|;
block|}
comment|/* evaluate m candidates for n_hi */
name|m_lo_n_hi
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|y
operator|/
name|r
operator|)
operator|-
literal|0.5
operator|*
operator|(
name|n_hi
operator|%
literal|2
operator|)
argument_list|)
expr_stmt|;
name|m_hi_n_hi
operator|=
name|m_lo_n_hi
operator|+
literal|1
expr_stmt|;
comment|/* figure out which is the better candidate */
if|if
condition|(
name|abs
argument_list|(
operator|(
name|m_lo_n_hi
operator|*
name|r
operator|+
operator|(
literal|0.5
operator|*
name|r
operator|*
operator|(
name|n_hi
operator|%
literal|2
operator|)
operator|)
operator|)
operator|-
name|y
argument_list|)
operator|<
name|abs
argument_list|(
operator|(
name|m_hi_n_hi
operator|*
name|r
operator|+
operator|(
literal|0.5
operator|*
name|r
operator|*
operator|(
name|n_hi
operator|%
literal|2
operator|)
operator|)
operator|)
operator|-
name|y
argument_list|)
condition|)
block|{
name|m_n_hi
operator|=
name|m_lo_n_hi
expr_stmt|;
block|}
else|else
block|{
name|m_n_hi
operator|=
name|m_hi_n_hi
expr_stmt|;
block|}
comment|/* Now, which is closer to [x,y]? we can use a somewhat        * abbreviated form of the distance formula since we only care        * about relative values.        */
name|x1
operator|=
call|(
name|gint
call|)
argument_list|(
name|n_lo
operator|*
name|h
argument_list|)
expr_stmt|;
name|y1
operator|=
call|(
name|gint
call|)
argument_list|(
name|m_n_lo
operator|*
name|r
operator|+
operator|(
literal|0.5
operator|*
name|r
operator|*
operator|(
name|n_lo
operator|%
literal|2
operator|)
operator|)
argument_list|)
expr_stmt|;
name|x2
operator|=
call|(
name|gint
call|)
argument_list|(
name|n_hi
operator|*
name|h
argument_list|)
expr_stmt|;
name|y2
operator|=
call|(
name|gint
call|)
argument_list|(
name|m_n_hi
operator|*
name|r
operator|+
operator|(
literal|0.5
operator|*
name|r
operator|*
operator|(
name|n_hi
operator|%
literal|2
operator|)
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|x
operator|-
name|x1
operator|)
operator|*
operator|(
name|x
operator|-
name|x1
operator|)
operator|+
operator|(
name|y
operator|-
name|y1
operator|)
operator|*
operator|(
name|y
operator|-
name|y1
operator|)
operator|)
operator|<
operator|(
operator|(
name|x
operator|-
name|x2
operator|)
operator|*
operator|(
name|x
operator|-
name|x2
operator|)
operator|+
operator|(
name|y
operator|-
name|y2
operator|)
operator|*
operator|(
name|y
operator|-
name|y2
operator|)
operator|)
condition|)
block|{
name|gp
operator|->
name|x
operator|=
name|x1
expr_stmt|;
name|gp
operator|->
name|y
operator|=
name|y1
expr_stmt|;
block|}
else|else
block|{
name|gp
operator|->
name|x
operator|=
name|x2
expr_stmt|;
name|gp
operator|->
name|y
operator|=
name|y2
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_grid_polar (GdkGC * drawgc)
name|draw_grid_polar
parameter_list|(
name|GdkGC
modifier|*
name|drawgc
parameter_list|)
block|{
name|gdouble
name|inner_radius
decl_stmt|;
name|gdouble
name|outer_radius
decl_stmt|;
name|gdouble
name|max_radius
init|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|preview_width
argument_list|)
operator|+
name|SQR
argument_list|(
name|preview_height
argument_list|)
argument_list|)
decl_stmt|;
name|gint
name|current_sectors
init|=
literal|1
decl_stmt|;
name|PrimeFactors
modifier|*
name|factors
init|=
name|prime_factors_new
argument_list|(
name|selvals
operator|.
name|opts
operator|.
name|grid_sectors_desired
argument_list|)
decl_stmt|;
for|for
control|(
name|inner_radius
operator|=
literal|0
operator|,
name|outer_radius
operator|=
name|selvals
operator|.
name|opts
operator|.
name|grid_radius_min
init|;
name|outer_radius
operator|<=
name|max_radius
condition|;
name|inner_radius
operator|=
name|outer_radius
operator|,
name|outer_radius
operator|+=
name|selvals
operator|.
name|opts
operator|.
name|grid_radius_interval
control|)
block|{
name|gdouble
name|t
decl_stmt|;
name|gdouble
name|sector_size
init|=
literal|2
operator|*
name|G_PI
operator|/
name|current_sectors
decl_stmt|;
name|gdk_draw_arc
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|)
argument_list|,
name|drawgc
argument_list|,
literal|0
argument_list|,
literal|0.5
operator|+
operator|(
name|preview_width
operator|/
literal|2
operator|-
name|outer_radius
operator|)
argument_list|,
literal|0.5
operator|+
operator|(
name|preview_height
operator|/
literal|2
operator|-
name|outer_radius
operator|)
argument_list|,
literal|0.5
operator|+
operator|(
name|outer_radius
operator|*
literal|2
operator|)
argument_list|,
literal|0.5
operator|+
operator|(
name|outer_radius
operator|*
literal|2
operator|)
argument_list|,
literal|0
argument_list|,
literal|360
operator|*
literal|64
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|current_sectors
operator|<
name|selvals
operator|.
name|opts
operator|.
name|grid_sectors_desired
operator|)
operator|&&
operator|(
name|inner_radius
operator|*
name|sector_size
operator|>
name|prime_factors_lookahead
argument_list|(
name|factors
argument_list|)
operator|*
name|selvals
operator|.
name|opts
operator|.
name|grid_granularity
operator|)
condition|)
block|{
name|current_sectors
operator|*=
name|prime_factors_get
argument_list|(
name|factors
argument_list|)
expr_stmt|;
name|sector_size
operator|=
literal|2
operator|*
name|G_PI
operator|/
name|current_sectors
expr_stmt|;
block|}
for|for
control|(
name|t
operator|=
literal|0
init|;
name|t
operator|<
literal|2
operator|*
name|G_PI
condition|;
name|t
operator|+=
name|sector_size
control|)
block|{
name|gdouble
name|normal_x
init|=
name|cos
argument_list|(
name|selvals
operator|.
name|opts
operator|.
name|grid_rotation
operator|+
name|t
argument_list|)
decl_stmt|;
name|gdouble
name|normal_y
init|=
name|sin
argument_list|(
name|selvals
operator|.
name|opts
operator|.
name|grid_rotation
operator|+
name|t
argument_list|)
decl_stmt|;
name|gdk_draw_line
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|)
argument_list|,
name|drawgc
argument_list|,
literal|0.5
operator|+
operator|(
name|preview_width
operator|/
literal|2
operator|+
name|inner_radius
operator|*
name|normal_x
operator|)
argument_list|,
literal|0.5
operator|+
operator|(
name|preview_height
operator|/
literal|2
operator|-
name|inner_radius
operator|*
name|normal_y
operator|)
argument_list|,
literal|0.5
operator|+
operator|(
name|preview_width
operator|/
literal|2
operator|+
name|outer_radius
operator|*
name|normal_x
operator|)
argument_list|,
literal|0.5
operator|+
operator|(
name|preview_height
operator|/
literal|2
operator|-
name|outer_radius
operator|*
name|normal_y
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
name|prime_factors_delete
argument_list|(
name|factors
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_grid_sq (GdkGC * drawgc)
name|draw_grid_sq
parameter_list|(
name|GdkGC
modifier|*
name|drawgc
parameter_list|)
block|{
name|gint
name|step
decl_stmt|;
name|gint
name|loop
decl_stmt|;
comment|/* Draw the horizontal lines */
name|step
operator|=
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
expr_stmt|;
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
name|preview_height
condition|;
name|loop
operator|+=
name|step
control|)
block|{
name|gdk_draw_line
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|)
argument_list|,
name|drawgc
argument_list|,
literal|0
argument_list|,
name|loop
argument_list|,
name|preview_width
argument_list|,
name|loop
argument_list|)
expr_stmt|;
block|}
comment|/* Draw the vertical lines */
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
name|preview_width
condition|;
name|loop
operator|+=
name|step
control|)
block|{
name|gdk_draw_line
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|)
argument_list|,
name|drawgc
argument_list|,
name|loop
argument_list|,
literal|0
argument_list|,
name|loop
argument_list|,
name|preview_height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_grid_iso (GdkGC * drawgc)
name|draw_grid_iso
parameter_list|(
name|GdkGC
modifier|*
name|drawgc
parameter_list|)
block|{
comment|/* vstep is an int since it's defined from grid size */
name|gint
name|vstep
decl_stmt|;
name|gdouble
name|loop
decl_stmt|;
name|gdouble
name|hstep
decl_stmt|;
name|gdouble
name|diagonal_start
decl_stmt|;
name|gdouble
name|diagonal_end
decl_stmt|;
name|gdouble
name|diagonal_width
decl_stmt|;
name|gdouble
name|diagonal_height
decl_stmt|;
name|vstep
operator|=
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
expr_stmt|;
name|hstep
operator|=
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
operator|*
name|COS_1o6PI_RAD
expr_stmt|;
comment|/* Draw the vertical lines - These are easy */
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
name|preview_width
condition|;
name|loop
operator|+=
name|hstep
control|)
block|{
name|gdk_draw_line
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|)
argument_list|,
name|drawgc
argument_list|,
operator|(
name|gint
operator|)
name|loop
argument_list|,
operator|(
name|gint
operator|)
literal|0
argument_list|,
operator|(
name|gint
operator|)
name|loop
argument_list|,
operator|(
name|gint
operator|)
name|preview_height
argument_list|)
expr_stmt|;
block|}
comment|/* draw diag lines at a Theta of +/- 1/6 Pi Rad */
name|diagonal_start
operator|=
operator|-
operator|(
operator|(
operator|(
name|int
operator|)
name|preview_width
operator|*
name|TAN_1o6PI_RAD
operator|)
operator|-
operator|(
operator|(
call|(
name|int
call|)
argument_list|(
name|preview_width
operator|*
name|TAN_1o6PI_RAD
argument_list|)
operator|)
operator|%
name|vstep
operator|)
operator|)
expr_stmt|;
name|diagonal_end
operator|=
name|preview_height
operator|+
operator|(
name|preview_width
operator|*
name|TAN_1o6PI_RAD
operator|)
expr_stmt|;
name|diagonal_end
operator|-=
operator|(
operator|(
name|int
operator|)
name|diagonal_end
operator|)
operator|%
name|vstep
expr_stmt|;
name|diagonal_width
operator|=
name|preview_width
expr_stmt|;
name|diagonal_height
operator|=
name|preview_width
operator|*
name|TAN_1o6PI_RAD
expr_stmt|;
comment|/* Draw diag lines */
for|for
control|(
name|loop
operator|=
name|diagonal_start
init|;
name|loop
operator|<
name|diagonal_end
condition|;
name|loop
operator|+=
name|vstep
control|)
block|{
name|gdk_draw_line
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|)
argument_list|,
name|drawgc
argument_list|,
operator|(
name|gint
operator|)
literal|0
argument_list|,
operator|(
name|gint
operator|)
name|loop
argument_list|,
operator|(
name|gint
operator|)
name|diagonal_width
argument_list|,
operator|(
name|gint
operator|)
name|loop
operator|+
name|diagonal_height
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|)
argument_list|,
name|drawgc
argument_list|,
operator|(
name|gint
operator|)
literal|0
argument_list|,
operator|(
name|gint
operator|)
name|loop
argument_list|,
operator|(
name|gint
operator|)
name|diagonal_width
argument_list|,
operator|(
name|gint
operator|)
name|loop
operator|-
name|diagonal_height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GdkGC
modifier|*
DECL|function|gfig_get_grid_gc (GtkWidget * w,gint gctype)
name|gfig_get_grid_gc
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gint
name|gctype
parameter_list|)
block|{
name|GtkStyle
modifier|*
name|style
init|=
name|gtk_widget_get_style
argument_list|(
name|w
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|gctype
condition|)
block|{
case|case
name|GFIG_BLACK_GC
case|:
return|return
name|style
operator|->
name|black_gc
return|;
case|case
name|GFIG_WHITE_GC
case|:
return|return
name|style
operator|->
name|white_gc
return|;
case|case
name|GFIG_GREY_GC
case|:
return|return
name|grid_hightlight_drawgc
return|;
case|case
name|GTK_STATE_NORMAL
case|:
return|return
name|style
operator|->
name|bg_gc
index|[
name|GTK_STATE_NORMAL
index|]
return|;
case|case
name|GTK_STATE_ACTIVE
case|:
return|return
name|style
operator|->
name|bg_gc
index|[
name|GTK_STATE_ACTIVE
index|]
return|;
case|case
name|GTK_STATE_PRELIGHT
case|:
return|return
name|style
operator|->
name|bg_gc
index|[
name|GTK_STATE_PRELIGHT
index|]
return|;
case|case
name|GTK_STATE_SELECTED
case|:
return|return
name|style
operator|->
name|bg_gc
index|[
name|GTK_STATE_SELECTED
index|]
return|;
case|case
name|GTK_STATE_INSENSITIVE
case|:
return|return
name|style
operator|->
name|bg_gc
index|[
name|GTK_STATE_INSENSITIVE
index|]
return|;
default|default:
name|g_warning
argument_list|(
literal|"Unknown type for grid colouring\n"
argument_list|)
expr_stmt|;
return|return
name|style
operator|->
name|bg_gc
index|[
name|GTK_STATE_PRELIGHT
index|]
return|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|draw_grid (void)
name|draw_grid
parameter_list|(
name|void
parameter_list|)
block|{
name|GdkGC
modifier|*
name|drawgc
decl_stmt|;
comment|/* Get the size of the preview and calc where the lines go */
comment|/* Draw in prelight to start with... */
comment|/* Always start in the upper left corner for rect.    */
if|if
condition|(
operator|(
name|preview_width
operator|<
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
operator|&&
name|preview_height
operator|<
name|selvals
operator|.
name|opts
operator|.
name|gridspacing
operator|)
condition|)
block|{
comment|/* Don't draw if they don't fit */
return|return;
block|}
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|drawgrid
condition|)
name|drawgc
operator|=
name|gfig_get_grid_gc
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|,
name|grid_gc_type
argument_list|)
expr_stmt|;
else|else
return|return;
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|gridtype
operator|==
name|RECT_GRID
condition|)
name|draw_grid_sq
argument_list|(
name|drawgc
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|gridtype
operator|==
name|POLAR_GRID
condition|)
name|draw_grid_polar
argument_list|(
name|drawgc
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|gridtype
operator|==
name|ISO_GRID
condition|)
name|draw_grid_iso
argument_list|(
name|drawgc
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

