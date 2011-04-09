begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Wilber Cairo rendering  * Copyright (C) 2008  Sven Neumann<sven@gimp.org>  *  * Some code here is based on code from librsvg that was originally  * written by Raph Levien<raph@artofcode.com> for Gill.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gimpcairo-wilber.h>
end_include

begin_comment
comment|/* This string is a path description as found in SVG files.  You can  * use Inkscape to create the SVG file, then copy the path from it.  * It works best if you combine all paths into one. Inkscape has a  * function to do that.  */
end_comment

begin_decl_stmt
DECL|variable|wilber_path
specifier|static
specifier|const
name|gchar
name|wilber_path
index|[]
init|=
literal|"M 509.72445,438.68864 C 501.47706,469.77945 464.95038,491.54566 431.85915,497.74874 C 438.5216,503.01688 442.87782,511.227 442.87782,520.37375 C 442.87783,536.24746 429.95607,549.0223 414.08235,549.0223 C 398.20863,549.0223 385.28688,536.24746 385.28688,520.37375 C 385.28688,511.52403 389.27666,503.61286 395.57098,498.3364 C 359.36952,495.90384 343.70976,463.95812 343.70975,463.95814 L 342.68134,509.64891 C 342.68134,514.35021 342.08391,519.96098 340.18378,528.3072 C 339.84664,527.80364 339.51399,527.33515 339.15537,526.83804 C 330.25511,514.5011 317.25269,507.81431 306.39317,508.76741 C 302.77334,509.08511 299.47017,510.33348 296.54982,512.4403 C 284.86847,520.86757 284.97665,540.94721 296.84366,557.3965 C 306.96274,571.42287 322.32232,578.25612 333.8664,574.73254 C 391.94635,615.17624 532.16931,642.41915 509.72445,438.68864 z M 363.24953,501.1278 C 373.83202,501.12778 382.49549,509.79127 382.49549,520.37375 C 382.49549,530.95624 373.83201,539.47279 363.24953,539.47279 C 352.66706,539.47279 344.1505,530.95624 344.1505,520.37375 C 344.15049,509.79129 352.66706,501.1278 363.24953,501.1278 z M 305.80551,516.1132 C 311.68466,516.11318 316.38344,521.83985 316.38344,528.89486 C 316.38345,535.94982 311.68467,541.67652 305.80551,541.67652 C 299.92636,541.67652 295.08067,535.94987 295.08067,528.89486 C 295.08065,521.83985 299.92636,516.1132 305.80551,516.1132 z M 440.821,552.54828 C 440.821,552.54828 448.7504,554.02388 453.8965,559.45332 C 457.41881,563.16951 457.75208,569.15506 456.98172,577.37703 C 456.21143,573.8833 454.89571,571.76659 453.8965,569.29666 C 443.01388,582.47662 413.42981,583.08929 376.0312,569.88433 C 416.63248,578.00493 437.38806,570.56014 449.48903,561.2163 C 446.29383,557.08917 440.821,552.54828 440.821,552.54828 z M 434.64723,524.59684 C 434.64723,532.23974 428.44429,538.44268 420.80139,538.44268 C 413.15849,538.44268 406.95555,532.23974 406.95555,524.59684 C 406.95555,516.95394 413.15849,510.751 420.80139,510.751 C 428.44429,510.751 434.64723,516.95394 434.64723,524.59684 z M 378.00043,522.99931 C 378.00043,527.70264 374.18324,531.51984 369.47991,531.51984 C 364.77658,531.51984 360.95939,527.70264 360.95939,522.99931 C 360.95939,518.29599 364.77658,514.47879 369.47991,514.47879 C 374.18324,514.47879 378.00043,518.29599 378.00043,522.99931 z "
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|wilber_cairo_path
specifier|static
name|cairo_path_t
modifier|*
name|wilber_cairo_path
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|wilber_x1
DECL|variable|wilber_y1
specifier|static
name|gdouble
name|wilber_x1
decl_stmt|,
name|wilber_y1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|wilber_x2
DECL|variable|wilber_y2
specifier|static
name|gdouble
name|wilber_x2
decl_stmt|,
name|wilber_y2
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|wilber_parse_path_data
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
specifier|const
name|gchar
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|wilber_get_extents
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_cairo_wilber:  * @cr: Cairo context  * @x: x position  * @y: y position  *  * Draw a Wilber path at position @x, @y.  */
end_comment

begin_function
name|void
DECL|function|gimp_cairo_wilber (cairo_t * cr,gdouble x,gdouble y)
name|gimp_cairo_wilber
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|wilber_get_extents
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|x
operator|-
name|wilber_x1
argument_list|,
name|y
operator|-
name|wilber_y1
argument_list|)
expr_stmt|;
name|cairo_append_path
argument_list|(
name|cr
argument_list|,
name|wilber_cairo_path
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cairo_wilber_get_size (cairo_t * cr,gdouble * width,gdouble * height)
name|gimp_cairo_wilber_get_size
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gdouble
modifier|*
name|width
parameter_list|,
name|gdouble
modifier|*
name|height
parameter_list|)
block|{
name|wilber_get_extents
argument_list|(
name|cr
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
name|wilber_x2
operator|-
name|wilber_x1
expr_stmt|;
operator|*
name|height
operator|=
name|wilber_y2
operator|-
name|wilber_y1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|wilber_get_extents (cairo_t * cr)
name|wilber_get_extents
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
if|if
condition|(
operator|!
name|wilber_cairo_path
condition|)
block|{
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|wilber_parse_path_data
argument_list|(
name|cr
argument_list|,
name|wilber_path
argument_list|)
expr_stmt|;
name|cairo_set_operator
argument_list|(
name|cr
argument_list|,
name|CAIRO_OPERATOR_CLEAR
argument_list|)
expr_stmt|;
name|cairo_fill_extents
argument_list|(
name|cr
argument_list|,
operator|&
name|wilber_x1
argument_list|,
operator|&
name|wilber_y1
argument_list|,
operator|&
name|wilber_x2
argument_list|,
operator|&
name|wilber_y2
argument_list|)
expr_stmt|;
name|wilber_cairo_path
operator|=
name|cairo_copy_path
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**********************************************************/
end_comment

begin_comment
comment|/*  Below is the code that parses the actual path data.   */
end_comment

begin_comment
comment|/*                                                        */
end_comment

begin_comment
comment|/*  This code is taken from librsvg and was originally    */
end_comment

begin_comment
comment|/*  written by Raph Levien<raph@artofcode.com> for Gill. */
end_comment

begin_comment
comment|/**********************************************************/
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27c4b90c0108
block|{
DECL|member|cr
name|cairo_t
modifier|*
name|cr
decl_stmt|;
DECL|member|cpx
DECL|member|cpy
name|gdouble
name|cpx
decl_stmt|,
name|cpy
decl_stmt|;
comment|/* current point                               */
DECL|member|rpx
DECL|member|rpy
name|gdouble
name|rpx
decl_stmt|,
name|rpy
decl_stmt|;
comment|/* reflection point (for 's' and 't' commands) */
DECL|member|cmd
name|gchar
name|cmd
decl_stmt|;
comment|/* current command (lowercase)                 */
DECL|member|param
name|gint
name|param
decl_stmt|;
comment|/* number of parameters                        */
DECL|member|rel
name|gboolean
name|rel
decl_stmt|;
comment|/* true if relative coords                     */
DECL|member|params
name|gdouble
name|params
index|[
literal|7
index|]
decl_stmt|;
comment|/* parameters that have been parsed            */
DECL|typedef|ParsePathContext
block|}
name|ParsePathContext
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|parse_path_default_xy
parameter_list|(
name|ParsePathContext
modifier|*
name|ctx
parameter_list|,
name|gint
name|n_params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|parse_path_do_cmd
parameter_list|(
name|ParsePathContext
modifier|*
name|ctx
parameter_list|,
name|gboolean
name|final
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|wilber_parse_path_data (cairo_t * cr,const gchar * data)
name|wilber_parse_path_data
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
specifier|const
name|gchar
modifier|*
name|data
parameter_list|)
block|{
name|ParsePathContext
name|ctx
decl_stmt|;
name|gboolean
name|in_num
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|in_frac
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|in_exp
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|exp_wait_sign
init|=
name|FALSE
decl_stmt|;
name|gdouble
name|val
init|=
literal|0.0
decl_stmt|;
name|gchar
name|c
init|=
literal|0
decl_stmt|;
name|gint
name|sign
init|=
literal|0
decl_stmt|;
name|gint
name|exp
init|=
literal|0
decl_stmt|;
name|gint
name|exp_sign
init|=
literal|0
decl_stmt|;
name|gdouble
name|frac
init|=
literal|0.0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|memset
argument_list|(
operator|&
name|ctx
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|ParsePathContext
argument_list|)
argument_list|)
expr_stmt|;
name|ctx
operator|.
name|cr
operator|=
name|cr
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
condition|;
name|i
operator|++
control|)
block|{
name|c
operator|=
name|data
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
name|c
operator|>=
literal|'0'
operator|&&
name|c
operator|<=
literal|'9'
condition|)
block|{
comment|/* digit */
if|if
condition|(
name|in_num
condition|)
block|{
if|if
condition|(
name|in_exp
condition|)
block|{
name|exp
operator|=
operator|(
name|exp
operator|*
literal|10
operator|)
operator|+
name|c
operator|-
literal|'0'
expr_stmt|;
name|exp_wait_sign
operator|=
name|FALSE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|in_frac
condition|)
name|val
operator|+=
operator|(
name|frac
operator|*=
literal|0.1
operator|)
operator|*
operator|(
name|c
operator|-
literal|'0'
operator|)
expr_stmt|;
else|else
name|val
operator|=
operator|(
name|val
operator|*
literal|10
operator|)
operator|+
name|c
operator|-
literal|'0'
expr_stmt|;
block|}
else|else
block|{
name|in_num
operator|=
name|TRUE
expr_stmt|;
name|in_frac
operator|=
name|FALSE
expr_stmt|;
name|in_exp
operator|=
name|FALSE
expr_stmt|;
name|exp
operator|=
literal|0
expr_stmt|;
name|exp_sign
operator|=
literal|1
expr_stmt|;
name|exp_wait_sign
operator|=
name|FALSE
expr_stmt|;
name|val
operator|=
name|c
operator|-
literal|'0'
expr_stmt|;
name|sign
operator|=
literal|1
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|c
operator|==
literal|'.'
condition|)
block|{
if|if
condition|(
operator|!
name|in_num
condition|)
block|{
name|in_num
operator|=
name|TRUE
expr_stmt|;
name|val
operator|=
literal|0
expr_stmt|;
block|}
name|in_frac
operator|=
name|TRUE
expr_stmt|;
name|frac
operator|=
literal|1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|c
operator|==
literal|'E'
operator|||
name|c
operator|==
literal|'e'
operator|)
operator|&&
name|in_num
condition|)
block|{
name|in_exp
operator|=
name|TRUE
expr_stmt|;
name|exp_wait_sign
operator|=
name|TRUE
expr_stmt|;
name|exp
operator|=
literal|0
expr_stmt|;
name|exp_sign
operator|=
literal|1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|c
operator|==
literal|'+'
operator|||
name|c
operator|==
literal|'-'
operator|)
operator|&&
name|in_exp
condition|)
block|{
name|exp_sign
operator|=
name|c
operator|==
literal|'+'
condition|?
literal|1
else|:
operator|-
literal|1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|in_num
condition|)
block|{
comment|/* end of number */
name|val
operator|*=
name|sign
operator|*
name|pow
argument_list|(
literal|10
argument_list|,
name|exp_sign
operator|*
name|exp
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|.
name|rel
condition|)
block|{
comment|/* Handle relative coordinates. This switch statement attempts                  to determine _what_ the coords are relative to. This is                  underspecified in the 12 Apr working draft. */
switch|switch
condition|(
name|ctx
operator|.
name|cmd
condition|)
block|{
case|case
literal|'l'
case|:
case|case
literal|'m'
case|:
case|case
literal|'c'
case|:
case|case
literal|'s'
case|:
case|case
literal|'q'
case|:
case|case
literal|'t'
case|:
comment|/* rule: even-numbered params are x-relative, odd-numbered                      are y-relative */
if|if
condition|(
operator|(
name|ctx
operator|.
name|param
operator|&
literal|1
operator|)
operator|==
literal|0
condition|)
name|val
operator|+=
name|ctx
operator|.
name|cpx
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|ctx
operator|.
name|param
operator|&
literal|1
operator|)
operator|==
literal|1
condition|)
name|val
operator|+=
name|ctx
operator|.
name|cpy
expr_stmt|;
break|break;
case|case
literal|'a'
case|:
comment|/* rule: sixth and seventh are x and y, rest are not                      relative */
if|if
condition|(
name|ctx
operator|.
name|param
operator|==
literal|5
condition|)
name|val
operator|+=
name|ctx
operator|.
name|cpx
expr_stmt|;
elseif|else
if|if
condition|(
name|ctx
operator|.
name|param
operator|==
literal|6
condition|)
name|val
operator|+=
name|ctx
operator|.
name|cpy
expr_stmt|;
break|break;
case|case
literal|'h'
case|:
comment|/* rule: x-relative */
name|val
operator|+=
name|ctx
operator|.
name|cpx
expr_stmt|;
break|break;
case|case
literal|'v'
case|:
comment|/* rule: y-relative */
name|val
operator|+=
name|ctx
operator|.
name|cpy
expr_stmt|;
break|break;
block|}
block|}
name|ctx
operator|.
name|params
index|[
name|ctx
operator|.
name|param
operator|++
index|]
operator|=
name|val
expr_stmt|;
name|parse_path_do_cmd
argument_list|(
operator|&
name|ctx
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|in_num
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|c
operator|==
literal|'\0'
condition|)
break|break;
elseif|else
if|if
condition|(
operator|(
name|c
operator|==
literal|'+'
operator|||
name|c
operator|==
literal|'-'
operator|)
operator|&&
operator|!
name|exp_wait_sign
condition|)
block|{
name|sign
operator|=
name|c
operator|==
literal|'+'
condition|?
literal|1
else|:
operator|-
literal|1
expr_stmt|;
name|val
operator|=
literal|0
expr_stmt|;
name|in_num
operator|=
name|TRUE
expr_stmt|;
name|in_frac
operator|=
name|FALSE
expr_stmt|;
name|in_exp
operator|=
name|FALSE
expr_stmt|;
name|exp
operator|=
literal|0
expr_stmt|;
name|exp_sign
operator|=
literal|1
expr_stmt|;
name|exp_wait_sign
operator|=
name|FALSE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|c
operator|==
literal|'z'
operator|||
name|c
operator|==
literal|'Z'
condition|)
block|{
if|if
condition|(
name|ctx
operator|.
name|param
condition|)
name|parse_path_do_cmd
argument_list|(
operator|&
name|ctx
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|cairo_close_path
argument_list|(
name|ctx
operator|.
name|cr
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|c
operator|>=
literal|'A'
operator|&&
name|c
operator|<=
literal|'Z'
operator|&&
name|c
operator|!=
literal|'E'
condition|)
block|{
if|if
condition|(
name|ctx
operator|.
name|param
condition|)
name|parse_path_do_cmd
argument_list|(
operator|&
name|ctx
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|ctx
operator|.
name|cmd
operator|=
name|c
operator|+
literal|'a'
operator|-
literal|'A'
expr_stmt|;
name|ctx
operator|.
name|rel
operator|=
name|FALSE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|c
operator|>=
literal|'a'
operator|&&
name|c
operator|<=
literal|'z'
operator|&&
name|c
operator|!=
literal|'e'
condition|)
block|{
if|if
condition|(
name|ctx
operator|.
name|param
condition|)
name|parse_path_do_cmd
argument_list|(
operator|&
name|ctx
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|ctx
operator|.
name|cmd
operator|=
name|c
expr_stmt|;
name|ctx
operator|.
name|rel
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* else c _should_ be whitespace or , */
block|}
block|}
end_function

begin_comment
comment|/* supply defaults for missing parameters, assuming relative coordinates    are to be interpreted as x,y */
end_comment

begin_function
specifier|static
name|void
DECL|function|parse_path_default_xy (ParsePathContext * ctx,gint n_params)
name|parse_path_default_xy
parameter_list|(
name|ParsePathContext
modifier|*
name|ctx
parameter_list|,
name|gint
name|n_params
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|ctx
operator|->
name|rel
condition|)
block|{
for|for
control|(
name|i
operator|=
name|ctx
operator|->
name|param
init|;
name|i
operator|<
name|n_params
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|>
literal|2
condition|)
name|ctx
operator|->
name|params
index|[
name|i
index|]
operator|=
name|ctx
operator|->
name|params
index|[
name|i
operator|-
literal|2
index|]
expr_stmt|;
elseif|else
if|if
condition|(
name|i
operator|==
literal|1
condition|)
name|ctx
operator|->
name|params
index|[
name|i
index|]
operator|=
name|ctx
operator|->
name|cpy
expr_stmt|;
elseif|else
if|if
condition|(
name|i
operator|==
literal|0
condition|)
comment|/* we shouldn't get here (ctx->param> 0 as precondition) */
name|ctx
operator|->
name|params
index|[
name|i
index|]
operator|=
name|ctx
operator|->
name|cpx
expr_stmt|;
block|}
block|}
else|else
block|{
for|for
control|(
name|i
operator|=
name|ctx
operator|->
name|param
init|;
name|i
operator|<
name|n_params
condition|;
name|i
operator|++
control|)
name|ctx
operator|->
name|params
index|[
name|i
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|parse_path_do_cmd (ParsePathContext * ctx,gboolean final)
name|parse_path_do_cmd
parameter_list|(
name|ParsePathContext
modifier|*
name|ctx
parameter_list|,
name|gboolean
name|final
parameter_list|)
block|{
switch|switch
condition|(
name|ctx
operator|->
name|cmd
condition|)
block|{
case|case
literal|'m'
case|:
comment|/* moveto */
if|if
condition|(
name|ctx
operator|->
name|param
operator|==
literal|2
operator|||
name|final
condition|)
block|{
name|parse_path_default_xy
argument_list|(
name|ctx
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|cpx
operator|=
name|ctx
operator|->
name|rpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|0
index|]
expr_stmt|;
name|ctx
operator|->
name|cpy
operator|=
name|ctx
operator|->
name|rpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|1
index|]
expr_stmt|;
name|cairo_move_to
argument_list|(
name|ctx
operator|->
name|cr
argument_list|,
name|ctx
operator|->
name|cpx
argument_list|,
name|ctx
operator|->
name|cpy
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
block|}
break|break;
case|case
literal|'l'
case|:
comment|/* lineto */
if|if
condition|(
name|ctx
operator|->
name|param
operator|==
literal|2
operator|||
name|final
condition|)
block|{
name|parse_path_default_xy
argument_list|(
name|ctx
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|cpx
operator|=
name|ctx
operator|->
name|rpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|0
index|]
expr_stmt|;
name|ctx
operator|->
name|cpy
operator|=
name|ctx
operator|->
name|rpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|1
index|]
expr_stmt|;
name|cairo_line_to
argument_list|(
name|ctx
operator|->
name|cr
argument_list|,
name|ctx
operator|->
name|cpx
argument_list|,
name|ctx
operator|->
name|cpy
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
block|}
break|break;
case|case
literal|'c'
case|:
comment|/* curveto */
if|if
condition|(
name|ctx
operator|->
name|param
operator|==
literal|6
operator|||
name|final
condition|)
block|{
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|parse_path_default_xy
argument_list|(
name|ctx
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|x
operator|=
name|ctx
operator|->
name|params
index|[
literal|0
index|]
expr_stmt|;
name|y
operator|=
name|ctx
operator|->
name|params
index|[
literal|1
index|]
expr_stmt|;
name|ctx
operator|->
name|rpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|2
index|]
expr_stmt|;
name|ctx
operator|->
name|rpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|3
index|]
expr_stmt|;
name|ctx
operator|->
name|cpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|4
index|]
expr_stmt|;
name|ctx
operator|->
name|cpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|5
index|]
expr_stmt|;
name|cairo_curve_to
argument_list|(
name|ctx
operator|->
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|ctx
operator|->
name|rpx
argument_list|,
name|ctx
operator|->
name|rpy
argument_list|,
name|ctx
operator|->
name|cpx
argument_list|,
name|ctx
operator|->
name|cpy
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
block|}
break|break;
case|case
literal|'s'
case|:
comment|/* smooth curveto */
if|if
condition|(
name|ctx
operator|->
name|param
operator|==
literal|4
operator|||
name|final
condition|)
block|{
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|parse_path_default_xy
argument_list|(
name|ctx
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|x
operator|=
literal|2
operator|*
name|ctx
operator|->
name|cpx
operator|-
name|ctx
operator|->
name|rpx
expr_stmt|;
name|y
operator|=
literal|2
operator|*
name|ctx
operator|->
name|cpy
operator|-
name|ctx
operator|->
name|rpy
expr_stmt|;
name|ctx
operator|->
name|rpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|0
index|]
expr_stmt|;
name|ctx
operator|->
name|rpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|1
index|]
expr_stmt|;
name|ctx
operator|->
name|cpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|2
index|]
expr_stmt|;
name|ctx
operator|->
name|cpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|3
index|]
expr_stmt|;
name|cairo_curve_to
argument_list|(
name|ctx
operator|->
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|ctx
operator|->
name|rpx
argument_list|,
name|ctx
operator|->
name|rpy
argument_list|,
name|ctx
operator|->
name|cpx
argument_list|,
name|ctx
operator|->
name|cpy
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
block|}
break|break;
case|case
literal|'h'
case|:
comment|/* horizontal lineto */
if|if
condition|(
name|ctx
operator|->
name|param
operator|==
literal|1
condition|)
block|{
name|ctx
operator|->
name|cpx
operator|=
name|ctx
operator|->
name|rpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|0
index|]
expr_stmt|;
name|cairo_line_to
argument_list|(
name|ctx
operator|->
name|cr
argument_list|,
name|ctx
operator|->
name|cpx
argument_list|,
name|ctx
operator|->
name|cpy
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
block|}
break|break;
case|case
literal|'v'
case|:
comment|/* vertical lineto */
if|if
condition|(
name|ctx
operator|->
name|param
operator|==
literal|1
condition|)
block|{
name|ctx
operator|->
name|cpy
operator|=
name|ctx
operator|->
name|rpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|0
index|]
expr_stmt|;
name|cairo_line_to
argument_list|(
name|ctx
operator|->
name|cr
argument_list|,
name|ctx
operator|->
name|cpx
argument_list|,
name|ctx
operator|->
name|cpy
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
block|}
break|break;
case|case
literal|'q'
case|:
comment|/* quadratic bezier curveto */
if|if
condition|(
name|ctx
operator|->
name|param
operator|==
literal|4
operator|||
name|final
condition|)
block|{
name|parse_path_default_xy
argument_list|(
name|ctx
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|rpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|0
index|]
expr_stmt|;
name|ctx
operator|->
name|rpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|1
index|]
expr_stmt|;
name|ctx
operator|->
name|cpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|2
index|]
expr_stmt|;
name|ctx
operator|->
name|cpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|3
index|]
expr_stmt|;
name|g_warning
argument_list|(
literal|"quadratic bezier curveto not implemented"
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
block|}
break|break;
case|case
literal|'t'
case|:
comment|/* truetype quadratic bezier curveto */
if|if
condition|(
name|ctx
operator|->
name|param
operator|==
literal|2
operator|||
name|final
condition|)
block|{
name|parse_path_default_xy
argument_list|(
name|ctx
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|rpx
operator|=
literal|2
operator|*
name|ctx
operator|->
name|cpx
operator|-
name|ctx
operator|->
name|rpx
expr_stmt|;
name|ctx
operator|->
name|rpy
operator|=
literal|2
operator|*
name|ctx
operator|->
name|cpy
operator|-
name|ctx
operator|->
name|rpy
expr_stmt|;
name|ctx
operator|->
name|cpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|0
index|]
expr_stmt|;
name|ctx
operator|->
name|cpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|1
index|]
expr_stmt|;
name|g_warning
argument_list|(
literal|"truetype quadratic bezier curveto not implemented"
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|final
condition|)
block|{
if|if
condition|(
name|ctx
operator|->
name|param
operator|>
literal|2
condition|)
block|{
name|parse_path_default_xy
argument_list|(
name|ctx
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|rpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|0
index|]
expr_stmt|;
name|ctx
operator|->
name|rpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|1
index|]
expr_stmt|;
name|ctx
operator|->
name|cpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|2
index|]
expr_stmt|;
name|ctx
operator|->
name|cpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|3
index|]
expr_stmt|;
name|g_warning
argument_list|(
literal|"conicto not implemented"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|parse_path_default_xy
argument_list|(
name|ctx
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|cpx
operator|=
name|ctx
operator|->
name|rpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|0
index|]
expr_stmt|;
name|ctx
operator|->
name|cpy
operator|=
name|ctx
operator|->
name|rpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|1
index|]
expr_stmt|;
name|cairo_line_to
argument_list|(
name|ctx
operator|->
name|cr
argument_list|,
name|ctx
operator|->
name|cpx
argument_list|,
name|ctx
operator|->
name|cpy
argument_list|)
expr_stmt|;
block|}
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
block|}
break|break;
case|case
literal|'a'
case|:
if|if
condition|(
name|ctx
operator|->
name|param
operator|==
literal|7
operator|||
name|final
condition|)
block|{
name|ctx
operator|->
name|cpx
operator|=
name|ctx
operator|->
name|rpx
operator|=
name|ctx
operator|->
name|params
index|[
literal|5
index|]
expr_stmt|;
name|ctx
operator|->
name|cpy
operator|=
name|ctx
operator|->
name|rpy
operator|=
name|ctx
operator|->
name|params
index|[
literal|6
index|]
expr_stmt|;
name|g_warning
argument_list|(
literal|"arcto not implemented"
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
block|}
break|break;
default|default:
name|ctx
operator|->
name|param
operator|=
literal|0
expr_stmt|;
break|break;
block|}
block|}
end_function

end_unit

