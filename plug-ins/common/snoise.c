begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Solid Noise plug-in -- creates solid noise textures  * Copyright (C) 1997, 1998 Marcelo de Gomensoro Malheiros  *  * The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* Solid Noise plug-in version 1.03, Apr 1998  *  * This plug-in generates solid noise textures based on the  * `Noise' and `Turbulence' functions described in the paper  *     *    Perlin, K, and Hoffert, E. M., "Hypertexture",  *    Computer Graphics 23, 3 (August 1989)  *  * The algorithm implemented here also makes possible the  * creation of seamless tiles.  *  * You can contact me at<malheiro@dca.fee.unicamp.br>.  * Comments and improvements for this code are welcome.  *  * The overall plug-in structure is based on the Whirl plug-in,  * which is Copyright (C) 1997 Federico Mena Quintero  */
end_comment

begin_comment
comment|/* Version 1.03:  *  *  Added patch from Kevin Turner<kevint@poboxes.com> to use the  *  current time as the random seed. Thank you!  *  Incorporated some portability changes from the GIMP distribution.  *  * Version 1.02:  *  *  Fixed a stupid bug with the alpha channel.  *  Fixed a rounding bug for small tilable textures.  *  Now the dialog is more compact; using the settings from gtkrc.  *  * Version 1.01:  *  *  Quick fix for wrong pdb declaration. Also changed default seed to 1.  *  Thanks to Adrian Likins and Federico Mena for the patch!  *  * Version 1.0:  *  *  Initial release.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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
comment|/*---- Defines ----*/
end_comment

begin_define
DECL|macro|TABLE_SIZE
define|#
directive|define
name|TABLE_SIZE
value|64
end_define

begin_define
DECL|macro|WEIGHT (T)
define|#
directive|define
name|WEIGHT
parameter_list|(
name|T
parameter_list|)
value|((2.0*fabs(T)-3.0)*(T)*(T)+1.0)
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|128
end_define

begin_define
DECL|macro|SCALE_MAX
define|#
directive|define
name|SCALE_MAX
value|16.0
end_define

begin_comment
comment|/*---- Typedefs ----*/
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27935faa0108
block|{
DECL|member|tilable
name|gint
name|tilable
decl_stmt|;
DECL|member|turbulent
name|gint
name|turbulent
decl_stmt|;
DECL|member|seed
name|gint
name|seed
decl_stmt|;
DECL|member|detail
name|gint
name|detail
decl_stmt|;
DECL|member|xsize
name|gdouble
name|xsize
decl_stmt|;
DECL|member|ysize
name|gdouble
name|ysize
decl_stmt|;
DECL|typedef|SolidNoiseValues
block|}
name|SolidNoiseValues
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27935faa0208
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|SolidNoiseInterface
block|}
name|SolidNoiseInterface
typedef|;
end_typedef

begin_comment
comment|/*---- Prototypes ----*/
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
name|solid_noise
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
name|solid_noise_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|plain_noise
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guint
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|noise
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|solid_noise_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dialog_ok_callback
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

begin_comment
comment|/*---- Variables ----*/
end_comment

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
DECL|variable|snvals
specifier|static
name|SolidNoiseValues
name|snvals
init|=
block|{
literal|0
block|,
comment|/* tilable       */
literal|0
block|,
comment|/* turbulent     */
literal|0
block|,
comment|/* seed          */
literal|1
block|,
comment|/* detail        */
literal|4.0
block|,
comment|/* xsize         */
literal|4.0
block|,
comment|/* ysize         */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|snint
specifier|static
name|SolidNoiseInterface
name|snint
init|=
block|{
name|FALSE
comment|/* run */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xclip
DECL|variable|yclip
specifier|static
name|gint
name|xclip
decl_stmt|,
name|yclip
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|offset
DECL|variable|factor
specifier|static
name|gdouble
name|offset
decl_stmt|,
name|factor
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xsize
DECL|variable|ysize
specifier|static
name|gdouble
name|xsize
decl_stmt|,
name|ysize
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|perm_tab
specifier|static
name|gint
name|perm_tab
index|[
name|TABLE_SIZE
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|grad_tab
specifier|static
name|GimpVector2
name|grad_tab
index|[
name|TABLE_SIZE
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*---- Functions ----*/
end_comment

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
literal|"Input image"
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
name|GIMP_PDB_INT32
block|,
literal|"tilable"
block|,
literal|"Create a tilable output (n=0/y=1)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"turbulent"
block|,
literal|"Make a turbulent noise (n=0/y=1)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"seed"
block|,
literal|"Random seed"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"detail"
block|,
literal|"Detail level (0 - 15)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"xsize"
block|,
literal|"Horizontal texture size"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"ysize"
block|,
literal|"Vertical texture size"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_solid_noise"
argument_list|,
literal|"Creates a grayscale noise texture"
argument_list|,
literal|"Generates 2D textures using Perlin's classic solid noise function."
argument_list|,
literal|"Marcelo de Gomensoro Malheiros"
argument_list|,
literal|"Marcelo de Gomensoro Malheiros"
argument_list|,
literal|"Apr 1998, v1.03"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Render/Clouds/Solid Noise..."
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
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
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
comment|/*  See how we will run  */
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_solid_noise"
argument_list|,
operator|&
name|snvals
argument_list|)
expr_stmt|;
comment|/*  Get information from the dialog  */
if|if
condition|(
operator|!
name|solid_noise_dialog
argument_list|()
condition|)
return|return;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Test number of arguments  */
if|if
condition|(
name|nparams
operator|!=
literal|9
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|snvals
operator|.
name|tilable
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|snvals
operator|.
name|turbulent
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|snvals
operator|.
name|seed
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|snvals
operator|.
name|detail
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|snvals
operator|.
name|xsize
operator|=
name|param
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|snvals
operator|.
name|ysize
operator|=
name|param
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_solid_noise"
argument_list|,
operator|&
name|snvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
comment|/*  Create texture  */
if|if
condition|(
operator|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|)
operator|&&
operator|(
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
operator|)
condition|)
block|{
comment|/*  Set the tile cache size  */
name|gimp_tile_cache_ntiles
argument_list|(
operator|(
name|drawable
operator|->
name|width
operator|+
name|gimp_tile_width
argument_list|()
operator|-
literal|1
operator|)
operator|/
name|gimp_tile_width
argument_list|()
argument_list|)
expr_stmt|;
comment|/*  Run!  */
name|solid_noise
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
comment|/*  If run mode is interactive, flush displays  */
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
comment|/*  Store data  */
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
operator|||
name|run_mode
operator|==
name|GIMP_RUN_WITH_LAST_VALS
condition|)
name|gimp_set_data
argument_list|(
literal|"plug_in_solid_noise"
argument_list|,
operator|&
name|snvals
argument_list|,
sizeof|sizeof
argument_list|(
name|SolidNoiseValues
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* gimp_message ("solid noise: cannot operate on indexed color images"); */
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
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

begin_function
specifier|static
name|void
DECL|function|solid_noise (GimpDrawable * drawable)
name|solid_noise
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpPixelRgn
name|dest_rgn
decl_stmt|;
name|gint
name|chns
decl_stmt|,
name|i
decl_stmt|,
name|has_alpha
decl_stmt|,
name|row
decl_stmt|,
name|col
decl_stmt|;
name|gint
name|sel_x1
decl_stmt|,
name|sel_y1
decl_stmt|,
name|sel_x2
decl_stmt|,
name|sel_y2
decl_stmt|;
name|gint
name|sel_width
decl_stmt|,
name|sel_height
decl_stmt|;
name|gint
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|,
modifier|*
name|dest_row
decl_stmt|;
name|guchar
name|val
decl_stmt|;
comment|/*  Get selection area  */
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|sel_x1
argument_list|,
operator|&
name|sel_y1
argument_list|,
operator|&
name|sel_x2
argument_list|,
operator|&
name|sel_y2
argument_list|)
expr_stmt|;
name|sel_width
operator|=
name|sel_x2
operator|-
name|sel_x1
expr_stmt|;
name|sel_height
operator|=
name|sel_y2
operator|-
name|sel_y1
expr_stmt|;
comment|/*  Initialization  */
name|solid_noise_init
argument_list|()
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Solid Noise..."
argument_list|)
argument_list|)
expr_stmt|;
name|progress
operator|=
literal|0
expr_stmt|;
name|max_progress
operator|=
name|sel_width
operator|*
name|sel_height
expr_stmt|;
name|chns
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|chns
operator|--
expr_stmt|;
name|has_alpha
operator|=
literal|1
expr_stmt|;
block|}
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|drawable
argument_list|,
name|sel_x1
argument_list|,
name|sel_y1
argument_list|,
name|sel_width
argument_list|,
name|sel_height
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  One, two, three, go!  */
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|dest_rgn
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
name|dest_row
operator|=
name|dest_rgn
operator|.
name|data
expr_stmt|;
for|for
control|(
name|row
operator|=
name|dest_rgn
operator|.
name|y
init|;
name|row
operator|<
operator|(
name|dest_rgn
operator|.
name|y
operator|+
name|dest_rgn
operator|.
name|h
operator|)
condition|;
name|row
operator|++
control|)
block|{
name|dest
operator|=
name|dest_row
expr_stmt|;
for|for
control|(
name|col
operator|=
name|dest_rgn
operator|.
name|x
init|;
name|col
operator|<
operator|(
name|dest_rgn
operator|.
name|x
operator|+
name|dest_rgn
operator|.
name|w
operator|)
condition|;
name|col
operator|++
control|)
block|{
name|val
operator|=
operator|(
name|guchar
operator|)
name|floor
argument_list|(
literal|255.0
operator|*
name|noise
argument_list|(
call|(
name|double
call|)
argument_list|(
name|col
operator|-
name|sel_x1
argument_list|)
operator|/
name|sel_width
argument_list|,
call|(
name|double
call|)
argument_list|(
name|row
operator|-
name|sel_y1
argument_list|)
operator|/
name|sel_height
argument_list|)
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
name|chns
condition|;
name|i
operator|++
control|)
operator|*
name|dest
operator|++
operator|=
name|val
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
operator|*
name|dest
operator|++
operator|=
literal|255
expr_stmt|;
block|}
name|dest_row
operator|+=
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
empty_stmt|;
block|}
comment|/*  Update progress  */
name|progress
operator|+=
name|dest_rgn
operator|.
name|w
operator|*
name|dest_rgn
operator|.
name|h
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|progress
operator|/
operator|(
name|double
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
comment|/*  Update the drawable  */
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
name|sel_x1
argument_list|,
name|sel_y1
argument_list|,
name|sel_width
argument_list|,
name|sel_height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|solid_noise_init (void)
name|solid_noise_init
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|,
name|t
decl_stmt|;
name|gdouble
name|m
decl_stmt|;
name|GRand
modifier|*
name|gr
decl_stmt|;
name|gr
operator|=
name|g_rand_new
argument_list|()
expr_stmt|;
comment|/*  Force sane parameters  */
if|if
condition|(
name|snvals
operator|.
name|detail
operator|<
literal|0
condition|)
name|snvals
operator|.
name|detail
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|snvals
operator|.
name|detail
operator|>
literal|15
condition|)
name|snvals
operator|.
name|detail
operator|=
literal|15
expr_stmt|;
if|if
condition|(
name|snvals
operator|.
name|seed
operator|<
literal|0
condition|)
name|snvals
operator|.
name|seed
operator|=
literal|0
expr_stmt|;
comment|/*  Set scaling factors  */
if|if
condition|(
name|snvals
operator|.
name|tilable
condition|)
block|{
name|xsize
operator|=
name|ceil
argument_list|(
name|snvals
operator|.
name|xsize
argument_list|)
expr_stmt|;
name|ysize
operator|=
name|ceil
argument_list|(
name|snvals
operator|.
name|ysize
argument_list|)
expr_stmt|;
name|xclip
operator|=
operator|(
name|int
operator|)
name|xsize
expr_stmt|;
name|yclip
operator|=
operator|(
name|int
operator|)
name|ysize
expr_stmt|;
block|}
else|else
block|{
name|xsize
operator|=
name|snvals
operator|.
name|xsize
expr_stmt|;
name|ysize
operator|=
name|snvals
operator|.
name|ysize
expr_stmt|;
block|}
comment|/*  Set totally empiric normalization values  */
if|if
condition|(
name|snvals
operator|.
name|turbulent
condition|)
block|{
name|offset
operator|=
literal|0.0
expr_stmt|;
name|factor
operator|=
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|offset
operator|=
literal|0.94
expr_stmt|;
name|factor
operator|=
literal|0.526
expr_stmt|;
block|}
comment|/*  Initialize the permutation table  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|TABLE_SIZE
condition|;
name|i
operator|++
control|)
name|perm_tab
index|[
name|i
index|]
operator|=
name|i
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|(
name|TABLE_SIZE
operator|>>
literal|1
operator|)
condition|;
name|i
operator|++
control|)
block|{
name|j
operator|=
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|0
argument_list|,
name|TABLE_SIZE
argument_list|)
expr_stmt|;
name|k
operator|=
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|0
argument_list|,
name|TABLE_SIZE
argument_list|)
expr_stmt|;
name|t
operator|=
name|perm_tab
index|[
name|j
index|]
expr_stmt|;
name|perm_tab
index|[
name|j
index|]
operator|=
name|perm_tab
index|[
name|k
index|]
expr_stmt|;
name|perm_tab
index|[
name|k
index|]
operator|=
name|t
expr_stmt|;
block|}
comment|/*  Initialize the gradient table  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|TABLE_SIZE
condition|;
name|i
operator|++
control|)
block|{
do|do
block|{
name|grad_tab
index|[
name|i
index|]
operator|.
name|x
operator|=
name|g_rand_double_range
argument_list|(
name|gr
argument_list|,
operator|-
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|grad_tab
index|[
name|i
index|]
operator|.
name|y
operator|=
name|g_rand_double_range
argument_list|(
name|gr
argument_list|,
operator|-
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|m
operator|=
name|grad_tab
index|[
name|i
index|]
operator|.
name|x
operator|*
name|grad_tab
index|[
name|i
index|]
operator|.
name|x
operator|+
name|grad_tab
index|[
name|i
index|]
operator|.
name|y
operator|*
name|grad_tab
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
block|}
do|while
condition|(
name|m
operator|==
literal|0.0
operator|||
name|m
operator|>
literal|1.0
condition|)
do|;
name|m
operator|=
literal|1.0
operator|/
name|sqrt
argument_list|(
name|m
argument_list|)
expr_stmt|;
name|grad_tab
index|[
name|i
index|]
operator|.
name|x
operator|*=
name|m
expr_stmt|;
name|grad_tab
index|[
name|i
index|]
operator|.
name|y
operator|*=
name|m
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|plain_noise (gdouble x,gdouble y,guint s)
name|plain_noise
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guint
name|s
parameter_list|)
block|{
name|GimpVector2
name|v
decl_stmt|;
name|gint
name|a
decl_stmt|,
name|b
decl_stmt|,
name|i
decl_stmt|,
name|j
decl_stmt|,
name|n
decl_stmt|;
name|gdouble
name|sum
decl_stmt|;
name|sum
operator|=
literal|0.0
expr_stmt|;
name|x
operator|*=
name|s
expr_stmt|;
name|y
operator|*=
name|s
expr_stmt|;
name|a
operator|=
operator|(
name|int
operator|)
name|floor
argument_list|(
name|x
argument_list|)
expr_stmt|;
name|b
operator|=
operator|(
name|int
operator|)
name|floor
argument_list|(
name|y
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
literal|2
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
literal|2
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|snvals
operator|.
name|tilable
condition|)
name|n
operator|=
name|perm_tab
index|[
operator|(
operator|(
operator|(
name|a
operator|+
name|i
operator|)
operator|%
operator|(
name|xclip
operator|*
name|s
operator|)
operator|)
operator|+
name|perm_tab
index|[
operator|(
operator|(
name|b
operator|+
name|j
operator|)
operator|%
operator|(
name|yclip
operator|*
name|s
operator|)
operator|)
operator|%
name|TABLE_SIZE
index|]
operator|)
operator|%
name|TABLE_SIZE
index|]
expr_stmt|;
else|else
name|n
operator|=
name|perm_tab
index|[
operator|(
name|a
operator|+
name|i
operator|+
name|perm_tab
index|[
operator|(
name|b
operator|+
name|j
operator|)
operator|%
name|TABLE_SIZE
index|]
operator|)
operator|%
name|TABLE_SIZE
index|]
expr_stmt|;
name|v
operator|.
name|x
operator|=
name|x
operator|-
name|a
operator|-
name|i
expr_stmt|;
name|v
operator|.
name|y
operator|=
name|y
operator|-
name|b
operator|-
name|j
expr_stmt|;
name|sum
operator|+=
name|WEIGHT
argument_list|(
name|v
operator|.
name|x
argument_list|)
operator|*
name|WEIGHT
argument_list|(
name|v
operator|.
name|y
argument_list|)
operator|*
operator|(
name|grad_tab
index|[
name|n
index|]
operator|.
name|x
operator|*
name|v
operator|.
name|x
operator|+
name|grad_tab
index|[
name|n
index|]
operator|.
name|y
operator|*
name|v
operator|.
name|y
operator|)
expr_stmt|;
block|}
return|return
name|sum
operator|/
name|s
return|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|noise (gdouble x,gdouble y)
name|noise
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|guint
name|s
decl_stmt|;
name|gdouble
name|sum
decl_stmt|;
name|s
operator|=
literal|1
expr_stmt|;
name|sum
operator|=
literal|0.0
expr_stmt|;
name|x
operator|*=
name|xsize
expr_stmt|;
name|y
operator|*=
name|ysize
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<=
name|snvals
operator|.
name|detail
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|snvals
operator|.
name|turbulent
condition|)
name|sum
operator|+=
name|fabs
argument_list|(
name|plain_noise
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|s
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|sum
operator|+=
name|plain_noise
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|s
operator|<<=
literal|1
expr_stmt|;
block|}
return|return
operator|(
name|sum
operator|+
name|offset
operator|)
operator|*
name|factor
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|solid_noise_dialog (void)
name|solid_noise_dialog
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
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
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"snoise"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  Dialog initialization  */
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Solid Noise"
argument_list|)
argument_list|,
literal|"snoise"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/snoise.html"
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
name|dialog_ok_callback
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
name|g_signal_connect
argument_list|(
name|dlg
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
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
literal|"Parameter Settings"
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
comment|/*  Table  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|4
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
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
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
comment|/*  Random Seed  */
name|seed_hbox
operator|=
name|gimp_random_seed_new
argument_list|(
operator|&
name|snvals
operator|.
name|seed
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
literal|"_Random Seed:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|seed_hbox
argument_list|,
literal|1
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
comment|/*  Detail  */
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adj
argument_list|,
name|snvals
operator|.
name|detail
argument_list|,
literal|1
argument_list|,
literal|15
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
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
literal|"_Detail:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|,
name|TRUE
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
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|snvals
operator|.
name|detail
argument_list|)
expr_stmt|;
comment|/*  Turbulent  */
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"T_urbulent"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|toggle
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|snvals
operator|.
name|turbulent
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|snvals
operator|.
name|turbulent
argument_list|)
expr_stmt|;
comment|/*  Tilable  */
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"T_ilable"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|toggle
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|snvals
operator|.
name|tilable
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|snvals
operator|.
name|tilable
argument_list|)
expr_stmt|;
comment|/*  X Size  */
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
literal|"_X Size:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|snvals
operator|.
name|xsize
argument_list|,
literal|0.1
argument_list|,
name|SCALE_MAX
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
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
name|snvals
operator|.
name|xsize
argument_list|)
expr_stmt|;
comment|/*  Y Size  */
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
literal|3
argument_list|,
name|_
argument_list|(
literal|"_Y Size:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|snvals
operator|.
name|ysize
argument_list|,
literal|0.1
argument_list|,
name|SCALE_MAX
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
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
name|snvals
operator|.
name|ysize
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
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
name|snint
operator|.
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_ok_callback (GtkWidget * widget,gpointer data)
name|dialog_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|snint
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

