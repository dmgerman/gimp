begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Color To Alpha plug-in v1.0 by Seth Burgess, sjburges@gimp.org 1999/05/14  *  with algorithm by clahey  */
end_comment

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
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PRV_WIDTH
define|#
directive|define
name|PRV_WIDTH
value|40
end_define

begin_define
DECL|macro|PRV_HEIGHT
define|#
directive|define
name|PRV_HEIGHT
value|20
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29d61dc90108
block|{
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
DECL|typedef|C2AValues
block|}
name|C2AValues
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29d61dc90208
block|{
DECL|member|run
name|gboolean
name|run
decl_stmt|;
DECL|typedef|C2AInterface
block|}
name|C2AInterface
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29d61dc90308
block|{
DECL|member|color_button
name|GtkWidget
modifier|*
name|color_button
decl_stmt|;
DECL|typedef|C2APreview
block|}
name|C2APreview
typedef|;
end_typedef

begin_comment
comment|/* Declare local functions.  */
end_comment

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colortoalpha
parameter_list|(
name|GimpRGB
modifier|*
name|src
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|toalpha
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|toalpha_render_row
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src_row
parameter_list|,
name|guchar
modifier|*
name|dest_row
parameter_list|,
name|gint
name|row_width
parameter_list|,
specifier|const
name|gint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* UI stuff */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|colortoalpha_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colortoalpha_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|run_mode
specifier|static
name|GimpRunModeType
name|run_mode
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pvals
specifier|static
name|C2AValues
name|pvals
init|=
block|{
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
comment|/* white default */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pint
specifier|static
name|C2AInterface
name|pint
init|=
block|{
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ppreview
specifier|static
name|C2APreview
name|ppreview
init|=
block|{
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (unused)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,
block|{
name|GIMP_PDB_COLOR
block|,
literal|"color"
block|,
literal|"Color to remove"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_colortoalpha"
argument_list|,
literal|"Convert the color in an image to alpha"
argument_list|,
literal|"This replaces as much of a given color as possible "
literal|"in each pixel with a corresponding amount of alpha, "
literal|"then readjusts the color accordingly."
argument_list|,
literal|"Seth Burgess"
argument_list|,
literal|"Seth Burgess<sjburges@gimp.org>"
argument_list|,
literal|"7th Aug 1999"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Colors/Color to Alpha..."
argument_list|)
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
comment|/*  Get the specified drawable  */
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
argument_list|)
expr_stmt|;
name|image_ID
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|gimp_palette_get_foreground
argument_list|(
operator|&
name|pvals
operator|.
name|color
argument_list|)
expr_stmt|;
name|gimp_get_data
argument_list|(
literal|"plug_in_colortoalpha"
argument_list|,
operator|&
name|pvals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|colortoalpha_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return;
block|}
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|4
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|pvals
operator|.
name|color
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_color
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
literal|"plug_in_colortoalpha"
argument_list|,
operator|&
name|pvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gimp_undo_push_group_start
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
comment|/*  Add alpha if not present */
name|gimp_layer_add_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
comment|/*  Make sure that the drawable is RGB color  */
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|&&
name|gimp_drawable_is_layer
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Removing color..."
argument_list|)
argument_list|)
expr_stmt|;
name|toalpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_undo_push_group_end
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
literal|"plug_in_colortoalpha"
argument_list|,
operator|&
name|pvals
argument_list|,
sizeof|sizeof
argument_list|(
name|pvals
argument_list|)
argument_list|)
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colortoalpha (GimpRGB * src,const GimpRGB * color)
name|colortoalpha
parameter_list|(
name|GimpRGB
modifier|*
name|src
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpRGB
name|alpha
decl_stmt|;
name|alpha
operator|.
name|a
operator|=
name|src
operator|->
name|a
expr_stmt|;
if|if
condition|(
name|color
operator|->
name|r
operator|<
literal|0.0001
condition|)
name|alpha
operator|.
name|r
operator|=
name|src
operator|->
name|r
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|r
operator|>
name|color
operator|->
name|r
condition|)
name|alpha
operator|.
name|r
operator|=
operator|(
name|src
operator|->
name|r
operator|-
name|color
operator|->
name|r
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|color
operator|->
name|r
operator|)
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|r
operator|<
name|color
operator|->
name|r
condition|)
name|alpha
operator|.
name|r
operator|=
operator|(
name|color
operator|->
name|r
operator|-
name|src
operator|->
name|r
operator|)
operator|/
name|color
operator|->
name|r
expr_stmt|;
else|else
name|alpha
operator|.
name|r
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|color
operator|->
name|g
operator|<
literal|0.0001
condition|)
name|alpha
operator|.
name|g
operator|=
name|src
operator|->
name|g
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|g
operator|>
name|color
operator|->
name|g
condition|)
name|alpha
operator|.
name|g
operator|=
operator|(
name|src
operator|->
name|g
operator|-
name|color
operator|->
name|g
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|color
operator|->
name|g
operator|)
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|g
operator|<
name|color
operator|->
name|g
condition|)
name|alpha
operator|.
name|g
operator|=
operator|(
name|color
operator|->
name|g
operator|-
name|src
operator|->
name|g
operator|)
operator|/
operator|(
name|color
operator|->
name|g
operator|)
expr_stmt|;
else|else
name|alpha
operator|.
name|g
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|color
operator|->
name|b
operator|<
literal|0.0001
condition|)
name|alpha
operator|.
name|b
operator|=
name|src
operator|->
name|b
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|b
operator|>
name|color
operator|->
name|b
condition|)
name|alpha
operator|.
name|b
operator|=
operator|(
name|src
operator|->
name|b
operator|-
name|color
operator|->
name|b
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|color
operator|->
name|b
operator|)
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|b
operator|<
name|color
operator|->
name|b
condition|)
name|alpha
operator|.
name|b
operator|=
operator|(
name|color
operator|->
name|b
operator|-
name|src
operator|->
name|b
operator|)
operator|/
operator|(
name|color
operator|->
name|b
operator|)
expr_stmt|;
else|else
name|alpha
operator|.
name|b
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|alpha
operator|.
name|r
operator|>
name|alpha
operator|.
name|g
condition|)
block|{
if|if
condition|(
name|alpha
operator|.
name|r
operator|>
name|alpha
operator|.
name|b
condition|)
block|{
name|src
operator|->
name|a
operator|=
name|alpha
operator|.
name|r
expr_stmt|;
block|}
else|else
block|{
name|src
operator|->
name|a
operator|=
name|alpha
operator|.
name|b
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|alpha
operator|.
name|g
operator|>
name|alpha
operator|.
name|b
condition|)
block|{
name|src
operator|->
name|a
operator|=
name|alpha
operator|.
name|g
expr_stmt|;
block|}
else|else
block|{
name|src
operator|->
name|a
operator|=
name|alpha
operator|.
name|b
expr_stmt|;
block|}
if|if
condition|(
name|src
operator|->
name|a
operator|<
literal|0.0001
condition|)
return|return;
name|src
operator|->
name|r
operator|=
operator|(
name|src
operator|->
name|r
operator|-
name|color
operator|->
name|r
operator|)
operator|/
name|src
operator|->
name|a
operator|+
name|color
operator|->
name|r
expr_stmt|;
name|src
operator|->
name|g
operator|=
operator|(
name|src
operator|->
name|g
operator|-
name|color
operator|->
name|g
operator|)
operator|/
name|src
operator|->
name|a
operator|+
name|color
operator|->
name|g
expr_stmt|;
name|src
operator|->
name|b
operator|=
operator|(
name|src
operator|->
name|b
operator|-
name|color
operator|->
name|b
operator|)
operator|/
name|src
operator|->
name|a
operator|+
name|color
operator|->
name|b
expr_stmt|;
name|src
operator|->
name|a
operator|*=
name|alpha
operator|.
name|a
expr_stmt|;
block|}
end_function

begin_comment
comment|/*<clahey>   so if a1> c1, a2> c2, and a3> c2 and a1 - c1> a2-c2, a3-c3,               then a1 = b1 * alpha + c1 * (1-alpha)               So, maximizing alpha without taking b1 above 1 gives  	     a1 = alpha + c1(1-alpha) and therefore alpha = (a1-c1) / (1-c1).<sjburges> clahey: btw, the ordering of that a2, a3 in the white->alpha didn't               matter<clahey>   sjburges: You mean that it could be either a1, a2, a3 or a1, a3, a2?<sjburges> yeah<sjburges> because neither one uses the other<clahey>   sjburges: That's exactly as it should be.  They are both just getting               reduced to the same amount, limited by the the darkest color.<clahey>   Then a2 = b2 * alpha + c2 * ( 1- alpha).  Solving for b2 gives               b2 = (a1-c2)/alpha + c2.<sjburges> yeah<clahey>   That gives us are formula for if the background is darker than the               foreground? Yep.<clahey>   Next if a1< c1, a2< c2, a3< c3, and c1-a1> c2-a2, c3-a3, and by our               desired result a1 = b1 * alpha + c1 * (1-alpha), we maximize alpha               without taking b1 negative gives alpha = 1 - a1 / c1.<clahey>   And then again, b2 = (a2-c2) / alpha + c2 by the same formula.                (Actually, I think we can use that formula for all cases, though it               may possibly introduce rounding error.<clahey>   sjburges: I like the idea of using floats to avoid rounding error.                Good call. */
end_comment

begin_function
specifier|static
name|void
DECL|function|toalpha_render_row (const guchar * src_data,guchar * dest_data,gint col,const gint bytes)
name|toalpha_render_row
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src_data
parameter_list|,
name|guchar
modifier|*
name|dest_data
parameter_list|,
name|gint
name|col
parameter_list|,
comment|/* row width in pixels */
specifier|const
name|gint
name|bytes
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
while|while
condition|(
name|col
operator|--
condition|)
block|{
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|src_data
index|[
name|col
operator|*
name|bytes
index|]
argument_list|,
name|src_data
index|[
name|col
operator|*
name|bytes
operator|+
literal|1
index|]
argument_list|,
name|src_data
index|[
name|col
operator|*
name|bytes
operator|+
literal|2
index|]
argument_list|,
name|src_data
index|[
name|col
operator|*
name|bytes
operator|+
literal|3
index|]
argument_list|)
expr_stmt|;
name|colortoalpha
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|pvals
operator|.
name|color
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|dest_data
index|[
name|col
operator|*
name|bytes
index|]
argument_list|,
operator|&
name|dest_data
index|[
name|col
operator|*
name|bytes
operator|+
literal|1
index|]
argument_list|,
operator|&
name|dest_data
index|[
name|col
operator|*
name|bytes
operator|+
literal|2
index|]
argument_list|,
operator|&
name|dest_data
index|[
name|col
operator|*
name|bytes
operator|+
literal|3
index|]
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|toalpha_render_region (const GimpPixelRgn srcPR,const GimpPixelRgn destPR)
name|toalpha_render_region
parameter_list|(
specifier|const
name|GimpPixelRgn
name|srcPR
parameter_list|,
specifier|const
name|GimpPixelRgn
name|destPR
parameter_list|)
block|{
name|gint
name|row
decl_stmt|;
name|guchar
modifier|*
name|src_ptr
init|=
name|srcPR
operator|.
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest_ptr
init|=
name|destPR
operator|.
name|data
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
operator|.
name|h
condition|;
name|row
operator|++
control|)
block|{
if|if
condition|(
name|srcPR
operator|.
name|bpp
operator|!=
literal|4
condition|)
block|{
name|gimp_message
argument_list|(
literal|"Not the proper bpp! \n"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
name|toalpha_render_row
argument_list|(
name|src_ptr
argument_list|,
name|dest_ptr
argument_list|,
name|srcPR
operator|.
name|w
argument_list|,
name|srcPR
operator|.
name|bpp
argument_list|)
expr_stmt|;
name|src_ptr
operator|+=
name|srcPR
operator|.
name|rowstride
expr_stmt|;
name|dest_ptr
operator|+=
name|destPR
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|toalpha (GimpDrawable * drawable)
name|toalpha
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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
decl_stmt|,
name|area_so_far
decl_stmt|;
name|gint
name|progress_skip
decl_stmt|;
comment|/* Get the input area. This is the bounding box of the selection in    *  the image (or the entire image if there is no selection). Only    *  operating on the input area is simply an optimization. It doesn't    *  need to be done for correct operation. (It simply makes it go    *  faster, since fewer pixels need to be operated on).    */
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
name|area_so_far
operator|=
literal|0
expr_stmt|;
name|progress_skip
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|total_area
operator|<
literal|1
condition|)
return|return;
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
name|toalpha_render_region
argument_list|(
name|srcPR
argument_list|,
name|destPR
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
operator|)
condition|)
block|{
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
operator|++
name|progress_skip
operator|%
literal|10
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
name|gboolean
DECL|function|colortoalpha_dialog (GimpDrawable * drawable)
name|colortoalpha_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"colortoalpha"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Color to Alpha"
argument_list|)
argument_list|,
literal|"colortoalpha"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/colortoalpha.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|colortoalpha_ok_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"From:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_color_button_new
argument_list|(
name|_
argument_list|(
literal|"Color to Alpha Color Picker"
argument_list|)
argument_list|,
name|PRV_WIDTH
argument_list|,
name|PRV_HEIGHT
argument_list|,
operator|&
name|pvals
operator|.
name|color
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"color_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_color_button_get_color
argument_list|)
argument_list|,
operator|&
name|pvals
operator|.
name|color
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|button
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|ppreview
operator|.
name|color_button
operator|=
name|button
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"to Alpha"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
return|return
name|pint
operator|.
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colortoalpha_ok_callback (GtkWidget * widget,gpointer data)
name|colortoalpha_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|pint
operator|.
name|run
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

