begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/****************************************************************************  * This is a plugin for the GIMP v 0.99.8 or later.  Documentation is  * available at http://www.rru.com/~meo/gimp/ .  *  * Copyright (C) 1997-98 Miles O'Neal<meo@rru.com>  http://www.rru.com/~meo/  * Blur code Copyright (C) 1995 Spencer Kimball and Peter Mattis  * GUI based on GTK code from:  *    alienmap (Copyright (C) 1996, 1997 Daniel Cotting)  *    plasma   (Copyright (C) 1996 Stephen Norris),  *    oilify   (Copyright (C) 1996 Torsten Martinsen),  *    ripple   (Copyright (C) 1997 Brian Degenhardt) and  *    whirl    (Copyright (C) 1997 Federico Mena Quintero).  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  ****************************************************************************/
end_comment

begin_comment
comment|/****************************************************************************  * Blur:  *  * blur version 2.0 (1 May 1998, MEO)  * history  *     2.0 -  1 May 1998 MEO  *         based on randomize 1.7  *  * Please send any patches or suggestions to the author: meo@rru.com .  *  * Blur applies a 3x3 blurring convolution kernel to the specified drawable.  *  * For each pixel in the selection or image,  * whether to change the pixel is decided by picking a  * random number, weighted by the user's "randomization" percentage.  * If the random number is in range, the pixel is modified.  For  * blurring, an average is determined from the current and adjacent  * pixels. *(Except for the random factor, the blur code came  * straight from the original S&P blur plug-in.)*  *  * This works only with RGB and grayscale images.  *  ****************************************************************************/
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_CONFIG_H
end_ifdef

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

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

begin_comment
comment|/*********************************  *  *  PLUGIN-SPECIFIC CONSTANTS  *  ********************************/
end_comment

begin_comment
comment|/*  *  progress meter update frequency  */
end_comment

begin_define
DECL|macro|PROG_UPDATE_TIME
define|#
directive|define
name|PROG_UPDATE_TIME
value|((row % 10) == 0)
end_define

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"plug_in_blur"
end_define

begin_define
DECL|macro|HELP_ID
define|#
directive|define
name|HELP_ID
value|"plug-in-blur"
end_define

begin_define
DECL|macro|SEED_DEFAULT
define|#
directive|define
name|SEED_DEFAULT
value|10
end_define

begin_define
DECL|macro|SEED_USER
define|#
directive|define
name|SEED_USER
value|11
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|64
end_define

begin_comment
comment|/*********************************  *  *  PLUGIN-SPECIFIC STRUCTURES AND DATA  *  ********************************/
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29b213b00108
block|{
DECL|member|blur_pct
name|gdouble
name|blur_pct
decl_stmt|;
comment|/* likelihood of randomization (as %age) */
DECL|member|blur_rcount
name|gdouble
name|blur_rcount
decl_stmt|;
comment|/* repeat count */
DECL|member|blur_randomize
name|gboolean
name|blur_randomize
decl_stmt|;
comment|/* Generate a random seed value */
DECL|member|blur_seed
name|guint
name|blur_seed
decl_stmt|;
comment|/* seed value for g_random_set_seed() function */
DECL|typedef|BlurVals
block|}
name|BlurVals
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|pivals
specifier|static
name|BlurVals
name|pivals
init|=
block|{
literal|100.0
block|,
literal|1.0
block|,
name|FALSE
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*********************************  *  *  LOCAL FUNCTIONS  *  ********************************/
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
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
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

begin_function_decl
specifier|static
name|void
name|blur
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|inline
name|void
name|blur_prepare_row
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pixel_rgn
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|blur_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/************************************ Guts ***********************************/
end_comment

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_comment
comment|/*********************************  *  *  query() - query_proc  *  *      called by the GIMP to learn about this plug-in  *  ********************************/
end_comment

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
name|args_ni
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"non-interactive"
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
block|}
decl_stmt|;
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
name|GIMP_PDB_FLOAT
block|,
literal|"blur_pct"
block|,
literal|"Randomization percentage (1 - 100)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"blur_rcount"
block|,
literal|"Repeat count(1 - 100)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"randomize"
block|,
literal|"Use a random seed (TRUE, FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"seed"
block|,
literal|"Seed value (used only if randomize is FALSE)"
block|}
block|}
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|blurb
init|=
literal|"Apply a 3x3 blurring convolution kernel to the specified drawable."
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help
init|=
literal|"This plug-in randomly blurs the specified drawable, using a 3x3 blur.  You control the percentage of the pixels that are blurred and the number of times blurring is applied.  Indexed images are not supported."
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|author
init|=
literal|"Miles O'Neal<meo@rru.com>"
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|copyrights
init|=
literal|"Miles O'Neal, Spencer Kimball, Peter Mattis, Torsten Martinsen, Brian Degenhardt, Federico Mena Quintero, Stephen Norris, Daniel Cotting"
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|copyright_date
init|=
literal|"1995-1998"
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_blur_randomize"
argument_list|,
name|blurb
argument_list|,
name|help
argument_list|,
name|author
argument_list|,
name|copyrights
argument_list|,
name|copyright_date
argument_list|,
name|N_
argument_list|(
literal|"_Blur..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
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
name|gimp_plugin_menu_register
argument_list|(
literal|"plug_in_blur_randomize"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Blur"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_NAME
argument_list|,
name|blurb
argument_list|,
name|help
argument_list|,
name|author
argument_list|,
name|copyrights
argument_list|,
name|copyright_date
argument_list|,
name|NULL
argument_list|,
literal|"RGB*, GRAY*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args_ni
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args_ni
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*********************************  *  *  run() - main routine  *  *  This handles the main interaction with the GIMP itself,  *  and invokes the routine that actually does the work.  *  ********************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
comment|/* assume the best! */
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*    *  Get the specified drawable, do standard initialization.    */
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
comment|/*    *  Make sure the drawable type is appropriate.    */
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|run_mode
condition|)
block|{
comment|/*            *  If we're running interactively, pop up the dialog box.            */
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|pivals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|blur_dialog
argument_list|()
condition|)
comment|/* return on Cancel */
return|return;
break|break;
comment|/*            *  If we're not interactive (probably scripting), we            *  get the parameters from the param[] array, since            *  we don't use the dialog box.  Make sure all            *  parameters have legitimate values.            */
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug_in_blur_randomize"
argument_list|)
operator|==
literal|0
operator|)
operator|&&
operator|(
name|nparams
operator|==
literal|7
operator|)
condition|)
block|{
name|pivals
operator|.
name|blur_pct
operator|=
operator|(
name|gdouble
operator|)
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|pivals
operator|.
name|blur_pct
operator|=
operator|(
name|gdouble
operator|)
name|MIN
argument_list|(
literal|100.0
argument_list|,
name|pivals
operator|.
name|blur_pct
argument_list|)
expr_stmt|;
name|pivals
operator|.
name|blur_pct
operator|=
operator|(
name|gdouble
operator|)
name|MAX
argument_list|(
literal|1.0
argument_list|,
name|pivals
operator|.
name|blur_pct
argument_list|)
expr_stmt|;
name|pivals
operator|.
name|blur_rcount
operator|=
operator|(
name|gdouble
operator|)
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|pivals
operator|.
name|blur_rcount
operator|=
operator|(
name|gdouble
operator|)
name|MIN
argument_list|(
literal|100.0
argument_list|,
name|pivals
operator|.
name|blur_rcount
argument_list|)
expr_stmt|;
name|pivals
operator|.
name|blur_rcount
operator|=
operator|(
name|gdouble
operator|)
name|MAX
argument_list|(
literal|1.0
argument_list|,
name|pivals
operator|.
name|blur_rcount
argument_list|)
expr_stmt|;
name|pivals
operator|.
name|blur_randomize
operator|=
operator|(
name|gboolean
operator|)
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|pivals
operator|.
name|blur_seed
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
name|pivals
operator|.
name|blur_randomize
condition|)
name|pivals
operator|.
name|blur_seed
operator|=
name|g_random_int
argument_list|()
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_NAME
argument_list|)
operator|==
literal|0
operator|)
operator|&&
operator|(
name|nparams
operator|==
literal|3
operator|)
condition|)
block|{
name|pivals
operator|.
name|blur_pct
operator|=
operator|(
name|gdouble
operator|)
literal|100.0
expr_stmt|;
name|pivals
operator|.
name|blur_rcount
operator|=
operator|(
name|gdouble
operator|)
literal|1.0
expr_stmt|;
name|pivals
operator|.
name|blur_randomize
operator|=
name|FALSE
expr_stmt|;
name|pivals
operator|.
name|blur_seed
operator|=
name|g_random_int
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
break|break;
comment|/*            *  If we're running with the last set of values, get those values.            */
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|pivals
argument_list|)
expr_stmt|;
if|if
condition|(
name|pivals
operator|.
name|blur_randomize
condition|)
name|pivals
operator|.
name|blur_seed
operator|=
name|g_random_int
argument_list|()
expr_stmt|;
break|break;
comment|/*            *  Hopefully we never get here!            */
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
comment|/*            *  JUST DO IT!            */
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Blurring..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
literal|2
operator|*
operator|(
name|drawable
operator|->
name|width
operator|/
name|gimp_tile_width
argument_list|()
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
name|g_random_set_seed
argument_list|(
name|pivals
operator|.
name|blur_seed
argument_list|)
expr_stmt|;
name|blur
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
comment|/*            *  If we ran interactively (even repeating) update the display.            */
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
comment|/*            *  If we use the dialog popup, set the data for future use.            */
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|gimp_set_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|pivals
argument_list|,
sizeof|sizeof
argument_list|(
name|BlurVals
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
comment|/*        *  If we got the wrong drawable type, we need to complain.        */
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
comment|/*    *  DONE!    *  Set the status where the GIMP can see it, and let go    *  of the drawable.    */
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*********************************  *  *  blur_prepare_row()  *  *  Get a row of pixels.  If the requested row  *  is off the edge, clone the edge row.  *  ********************************/
end_comment

begin_function
specifier|static
specifier|inline
name|void
DECL|function|blur_prepare_row (GimpPixelRgn * pixel_rgn,guchar * data,gint x,gint y,gint w)
name|blur_prepare_row
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pixel_rgn
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|)
block|{
name|int
name|b
decl_stmt|;
name|y
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|1
argument_list|,
name|pixel_rgn
operator|->
name|h
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
name|pixel_rgn
argument_list|,
name|data
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|)
expr_stmt|;
comment|/*    *  Fill in edge pixels    */
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|pixel_rgn
operator|->
name|bpp
condition|;
name|b
operator|++
control|)
block|{
name|data
index|[
operator|-
operator|(
name|gint
operator|)
name|pixel_rgn
operator|->
name|bpp
operator|+
name|b
index|]
operator|=
name|data
index|[
name|b
index|]
expr_stmt|;
name|data
index|[
name|w
operator|*
name|pixel_rgn
operator|->
name|bpp
operator|+
name|b
index|]
operator|=
name|data
index|[
operator|(
name|w
operator|-
literal|1
operator|)
operator|*
name|pixel_rgn
operator|->
name|bpp
operator|+
name|b
index|]
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*********************************  *  *  blur()  *  *  Actually mess with the image.  *  ********************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|blur (GimpDrawable * drawable)
name|blur
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
decl_stmt|,
name|destPR2
decl_stmt|,
modifier|*
name|sp
decl_stmt|,
modifier|*
name|dp
decl_stmt|,
modifier|*
name|tp
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|guchar
modifier|*
name|prev_row
decl_stmt|,
modifier|*
name|pr
decl_stmt|;
name|guchar
modifier|*
name|cur_row
decl_stmt|,
modifier|*
name|cr
decl_stmt|;
name|guchar
modifier|*
name|next_row
decl_stmt|,
modifier|*
name|nr
decl_stmt|;
name|guchar
modifier|*
name|tmp
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
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
name|cnt
decl_stmt|,
name|ind
decl_stmt|;
name|gint
name|repeat_count
decl_stmt|;
name|gboolean
name|has_alpha
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
comment|/*    *  Get the size of the input image. (This will/must be the same    *  as the size of the output image.  Also get alpha info.    */
name|width
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
name|bytes
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
comment|/*    *  allocate row buffers    */
name|prev_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|+
literal|2
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|cur_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|+
literal|2
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|next_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|+
literal|2
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/*    *  initialize the pixel regions    */
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
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
name|destPR
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|destPR2
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|sp
operator|=
operator|&
name|srcPR
expr_stmt|;
name|dp
operator|=
operator|&
name|destPR
expr_stmt|;
name|tp
operator|=
name|NULL
expr_stmt|;
name|pr
operator|=
name|prev_row
operator|+
name|bytes
expr_stmt|;
name|cr
operator|=
name|cur_row
operator|+
name|bytes
expr_stmt|;
name|nr
operator|=
name|next_row
operator|+
name|bytes
expr_stmt|;
name|repeat_count
operator|=
operator|(
name|gint
operator|)
name|pivals
operator|.
name|blur_rcount
expr_stmt|;
for|for
control|(
name|cnt
operator|=
literal|1
init|;
name|cnt
operator|<=
name|repeat_count
condition|;
name|cnt
operator|++
control|)
block|{
comment|/*        *  prepare the first row and previous row        */
name|blur_prepare_row
argument_list|(
name|sp
argument_list|,
name|pr
argument_list|,
name|x1
argument_list|,
name|y1
operator|-
literal|1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|blur_prepare_row
argument_list|(
name|dp
argument_list|,
name|cr
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
argument_list|)
expr_stmt|;
comment|/*        *  loop through the rows, applying the selected convolution        */
for|for
control|(
name|row
operator|=
name|y1
init|;
name|row
operator|<
name|y2
condition|;
name|row
operator|++
control|)
block|{
comment|/*  prepare the next row  */
name|blur_prepare_row
argument_list|(
name|sp
argument_list|,
name|nr
argument_list|,
name|x1
argument_list|,
name|row
operator|+
literal|1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|d
operator|=
name|dest
expr_stmt|;
name|ind
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
condition|;
name|col
operator|++
control|)
block|{
if|if
condition|(
name|g_random_int_range
argument_list|(
literal|0
argument_list|,
literal|100
argument_list|)
operator|<=
operator|(
name|gint
operator|)
name|pivals
operator|.
name|blur_pct
condition|)
block|{
name|ind
operator|++
expr_stmt|;
if|if
condition|(
name|ind
operator|==
name|bytes
operator|||
operator|!
name|has_alpha
condition|)
block|{
comment|/*                        *  If no alpha channel,                        *   or if there is one and this is it...                        */
operator|*
name|d
operator|++
operator|=
operator|(
operator|(
name|gint
operator|)
name|pr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
operator|(
name|gint
operator|)
name|pr
index|[
name|col
index|]
operator|+
operator|(
name|gint
operator|)
name|pr
index|[
name|col
operator|+
name|bytes
index|]
operator|+
operator|(
name|gint
operator|)
name|cr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
operator|(
name|gint
operator|)
name|cr
index|[
name|col
index|]
operator|+
operator|(
name|gint
operator|)
name|cr
index|[
name|col
operator|+
name|bytes
index|]
operator|+
operator|(
name|gint
operator|)
name|nr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
operator|(
name|gint
operator|)
name|nr
index|[
name|col
index|]
operator|+
operator|(
name|gint
operator|)
name|nr
index|[
name|col
operator|+
name|bytes
index|]
operator|)
operator|/
literal|9
expr_stmt|;
name|ind
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
comment|/*                        *  otherwise we have an alpha channel,                        *   but this is a color channel                        */
operator|*
name|d
operator|++
operator|=
operator|(
call|(
name|gint
call|)
argument_list|(
operator|(
call|(
name|gdouble
call|)
argument_list|(
name|pr
index|[
name|col
operator|-
name|bytes
index|]
operator|*
name|pr
index|[
name|col
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|pr
index|[
name|col
index|]
operator|*
name|pr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|pr
index|[
name|col
operator|+
name|bytes
index|]
operator|*
name|pr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|cr
index|[
name|col
operator|-
name|bytes
index|]
operator|*
name|cr
index|[
name|col
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|cr
index|[
name|col
index|]
operator|*
name|cr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|cr
index|[
name|col
operator|+
name|bytes
index|]
operator|*
name|cr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|nr
index|[
name|col
operator|-
name|bytes
index|]
operator|*
name|nr
index|[
name|col
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|nr
index|[
name|col
index|]
operator|*
name|nr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|nr
index|[
name|col
operator|+
name|bytes
index|]
operator|*
name|nr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|)
operator|/
operator|(
operator|(
name|gdouble
operator|)
name|pr
index|[
name|col
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|pr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|pr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|cr
index|[
name|col
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|cr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|cr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|nr
index|[
name|col
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|nr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|nr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
operator|)
argument_list|)
operator|)
expr_stmt|;
block|}
comment|/*                    *  Otherwise, this pixel was not selected for randomization,                    *  so use the current value.                    */
block|}
else|else
block|{
operator|*
name|d
operator|++
operator|=
operator|(
name|gint
operator|)
name|cr
index|[
name|col
index|]
expr_stmt|;
block|}
block|}
comment|/*            *  Save the modified row, shuffle the row pointers, and every            *  so often, update the progress meter.            */
name|gimp_pixel_rgn_set_row
argument_list|(
name|dp
argument_list|,
name|dest
argument_list|,
name|x1
argument_list|,
name|row
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|pr
expr_stmt|;
name|pr
operator|=
name|cr
expr_stmt|;
name|cr
operator|=
name|nr
expr_stmt|;
name|nr
operator|=
name|tmp
expr_stmt|;
if|if
condition|(
name|PROG_UPDATE_TIME
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|row
operator|/
call|(
name|double
call|)
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*        *  if we have more cycles to perform, swap the src and dest Pixel Regions        */
if|if
condition|(
name|cnt
operator|<
name|repeat_count
condition|)
block|{
if|if
condition|(
name|tp
operator|!=
name|NULL
condition|)
block|{
name|tp
operator|=
name|dp
expr_stmt|;
name|dp
operator|=
name|sp
expr_stmt|;
name|sp
operator|=
name|tp
expr_stmt|;
block|}
else|else
block|{
name|tp
operator|=
operator|&
name|srcPR
expr_stmt|;
name|sp
operator|=
operator|&
name|destPR
expr_stmt|;
name|dp
operator|=
operator|&
name|destPR2
expr_stmt|;
block|}
block|}
block|}
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
literal|100
argument_list|)
expr_stmt|;
comment|/*    *  update the blurred region    */
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
comment|/*    *  clean up after ourselves.    */
name|g_free
argument_list|(
name|prev_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cur_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|next_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*********************************  *  GUI ROUTINES  ********************************/
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|blur_dialog (void)
name|blur_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|seed_hbox
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"blur"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Blur"
argument_list|)
argument_list|,
literal|"blur"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|HELP_ID
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    *  Parameter settings    *    *  First set up the basic containers, label them, etc.    */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
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
name|gtk_table_set_row_spacings
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
literal|12
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
name|table
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  Random Seed  */
name|seed_hbox
operator|=
name|gimp_random_seed_new
argument_list|(
operator|&
name|pivals
operator|.
name|blur_seed
argument_list|,
operator|&
name|pivals
operator|.
name|blur_randomize
argument_list|)
expr_stmt|;
name|label
operator|=
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Random _seed:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|seed_hbox
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GIMP_RANDOM_SEED_SPINBUTTON
argument_list|(
name|seed_hbox
argument_list|)
argument_list|)
expr_stmt|;
comment|/*    *  Randomization percentage label& scale (1 to 100)    */
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"R_andomization %:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|pivals
operator|.
name|blur_pct
argument_list|,
literal|1.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Percentage of pixels to be filtered"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|pivals
operator|.
name|blur_pct
argument_list|)
expr_stmt|;
comment|/*    *  Repeat count label& scale (1 to 100)    */
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"R_epeat:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|pivals
operator|.
name|blur_rcount
argument_list|,
literal|1.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Number of times to apply filter"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|pivals
operator|.
name|blur_rcount
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dlg
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

