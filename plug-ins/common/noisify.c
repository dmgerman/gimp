begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plugin for the GIMP.  *  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1996 Torsten Martinsen  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * This filter adds random noise to an image.  * The amount of noise can be set individually for each RGB channel.  * This filter does not operate on indexed images.  *  * May 2000 tim copperfield [timecop@japan.co.jp]  * Added dynamic preview.  *  * alt@gimp.org. Fixed previews so they handle alpha channels correctly.  */
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
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|125
end_define

begin_define
DECL|macro|TILE_CACHE_SIZE
define|#
directive|define
name|TILE_CACHE_SIZE
value|16
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2754f9120108
block|{
DECL|member|independent
name|gboolean
name|independent
decl_stmt|;
DECL|member|correlated
name|gboolean
name|correlated
decl_stmt|;
DECL|member|noise
name|gdouble
name|noise
index|[
literal|4
index|]
decl_stmt|;
comment|/*  per channel  */
DECL|typedef|NoisifyVals
block|}
name|NoisifyVals
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2754f9120208
block|{
DECL|member|channels
name|gint
name|channels
decl_stmt|;
DECL|member|channel_adj
name|GtkObject
modifier|*
name|channel_adj
index|[
literal|4
index|]
decl_stmt|;
DECL|typedef|NoisifyInterface
block|}
name|NoisifyInterface
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

begin_function_decl
specifier|static
name|void
name|noisify_func
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|noisify
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gauss
parameter_list|(
name|GRand
modifier|*
name|gr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|noisify_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|channels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|noisify_double_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
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
comment|/* init_proc */
name|NULL
block|,
comment|/* quit_proc */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|nvals
specifier|static
name|NoisifyVals
name|nvals
init|=
block|{
name|TRUE
block|,
name|FALSE
block|,
block|{
literal|0.20
block|,
literal|0.20
block|,
literal|0.20
block|,
literal|0.0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|noise_int
specifier|static
name|NoisifyInterface
name|noise_int
init|=
block|{
literal|0
block|,
block|{
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|noise_gr
specifier|static
name|GRand
modifier|*
name|noise_gr
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|noise_gr
comment|/* Global random number object */
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
name|scatter_args
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
name|GIMP_PDB_INT32
block|,
literal|"independent"
block|,
literal|"Noise in channels independent"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"correlated"
block|,
literal|"Noise correlated (i.e. multiplicative not additive)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"noise_1"
block|,
literal|"Noise in the first channel (red, gray)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"noise_2"
block|,
literal|"Noise in the second channel (green, gray_alpha)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"noise_3"
block|,
literal|"Noise in the third channel (blue)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"noise_4"
block|,
literal|"Noise in the fourth channel (alpha)"
block|}
block|}
decl_stmt|;
specifier|static
name|GimpParamDef
name|noisify_args
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
name|GIMP_PDB_INT32
block|,
literal|"independent"
block|,
literal|"Noise in channels independent"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"noise_1"
block|,
literal|"Noise in the first channel (red, gray)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"noise_2"
block|,
literal|"Noise in the second channel (green, gray_alpha)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"noise_3"
block|,
literal|"Noise in the third channel (blue)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"noise_4"
block|,
literal|"Noise in the fourth channel (alpha)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_rgb_noise"
argument_list|,
literal|"Adds random noise to image channels "
argument_list|,
literal|"Add normally distributed (zero mean) random values "
literal|"to image channels.  Noise may be additive "
literal|"(uncorrelated) or multiplicative (correlated - "
literal|"also known as speckle noise). "
literal|"For colour images colour channels may be treated "
literal|"together or independently."
argument_list|,
literal|"Torsten Martinsen"
argument_list|,
literal|"Torsten Martinsen"
argument_list|,
literal|"May 2000"
argument_list|,
name|N_
argument_list|(
literal|"_RGB Noise..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|scatter_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|scatter_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
literal|"plug_in_rgb_noise"
argument_list|,
literal|"<Image>/Filters/Noise"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_noisify"
argument_list|,
literal|"Adds random noise to image channels "
argument_list|,
literal|"Add normally distributed random values to "
literal|"image channels. For colour images each "
literal|"colour channel may be treated together or "
literal|"independently."
argument_list|,
literal|"Torsten Martinsen"
argument_list|,
literal|"Torsten Martinsen"
argument_list|,
literal|"May 2000"
argument_list|,
name|NULL
argument_list|,
literal|"RGB*, GRAY*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|noisify_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|noisify_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

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
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpRunMode
name|run_mode
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
name|INIT_I18N
argument_list|()
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
name|noise_gr
operator|=
name|g_rand_new
argument_list|()
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
name|gimp_tile_cache_ntiles
argument_list|(
name|TILE_CACHE_SIZE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
name|nvals
operator|.
name|noise
index|[
literal|1
index|]
operator|=
literal|0.0
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_scatter_rgb"
argument_list|,
operator|&
name|nvals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|noisify_dialog
argument_list|(
name|drawable
argument_list|,
name|drawable
operator|->
name|bpp
argument_list|)
condition|)
block|{
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_rand_free
argument_list|(
name|noise_gr
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
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug_in_noisify"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|8
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|nvals
operator|.
name|independent
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|nvals
operator|.
name|correlated
operator|=
name|FALSE
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|1
index|]
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|2
index|]
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|3
index|]
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
block|}
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug_in_scatter_rgb"
argument_list|)
operator|==
literal|0
condition|)
block|{
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
name|nvals
operator|.
name|independent
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|nvals
operator|.
name|correlated
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|1
index|]
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|2
index|]
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
name|nvals
operator|.
name|noise
index|[
literal|3
index|]
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
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_scatter_rgb"
argument_list|,
operator|&
name|nvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
comment|/*  Make sure that the drawable is gray or RGB color  */
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Adding Noise..."
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  compute the luminosity which exceeds the luminosity threshold  */
name|gimp_rgn_iterate2
argument_list|(
name|drawable
argument_list|,
literal|0
comment|/* unused */
argument_list|,
name|noisify_func
argument_list|,
name|noise_gr
argument_list|)
expr_stmt|;
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
condition|)
name|gimp_set_data
argument_list|(
literal|"plug_in_scatter_rgb"
argument_list|,
operator|&
name|nvals
argument_list|,
sizeof|sizeof
argument_list|(
name|NoisifyVals
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
name|g_rand_free
argument_list|(
name|noise_gr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|noisify_func (const guchar * src,guchar * dest,gint bpp,gpointer data)
name|noisify_func
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GRand
modifier|*
name|gr
init|=
name|data
decl_stmt|;
name|gint
name|noise
init|=
literal|0
decl_stmt|;
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bpp
condition|;
name|b
operator|++
control|)
block|{
if|if
condition|(
name|b
operator|==
literal|0
operator|||
name|nvals
operator|.
name|independent
operator|||
operator|(
name|b
operator|==
literal|1
operator|&&
name|bpp
operator|==
literal|2
operator|)
operator|||
operator|(
name|b
operator|==
literal|3
operator|&&
name|bpp
operator|==
literal|4
operator|)
condition|)
name|noise
operator|=
call|(
name|gint
call|)
argument_list|(
name|nvals
operator|.
name|noise
index|[
name|b
index|]
operator|*
name|gauss
argument_list|(
name|gr
argument_list|)
operator|*
literal|127
argument_list|)
expr_stmt|;
if|if
condition|(
name|nvals
operator|.
name|noise
index|[
name|b
index|]
operator|>
literal|0.0
condition|)
block|{
name|gint
name|p
decl_stmt|;
if|if
condition|(
name|nvals
operator|.
name|correlated
condition|)
block|{
name|p
operator|=
call|(
name|gint
call|)
argument_list|(
name|src
index|[
name|b
index|]
operator|+
operator|(
name|src
index|[
name|b
index|]
operator|*
operator|(
name|noise
operator|/
literal|127.0
operator|)
operator|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|p
operator|=
name|src
index|[
name|b
index|]
operator|+
name|noise
expr_stmt|;
block|}
name|dest
index|[
name|b
index|]
operator|=
name|CLAMP0255
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|dest
index|[
name|b
index|]
operator|=
name|src
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|noisify (GimpPreview * preview)
name|noisify
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpPixelRgn
name|src_rgn
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dst
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|GRand
modifier|*
name|gr
init|=
name|g_rand_copy
argument_list|(
name|noise_gr
argument_list|)
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_preview_get_drawable
argument_list|(
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_preview_get_position
argument_list|(
name|preview
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_preview_get_size
argument_list|(
name|preview
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|src
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|dst
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
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
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|src
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
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
name|width
operator|*
name|height
condition|;
name|i
operator|++
control|)
name|noisify_func
argument_list|(
name|src
operator|+
name|i
operator|*
name|bpp
argument_list|,
name|dst
operator|+
name|i
operator|*
name|bpp
argument_list|,
name|bpp
argument_list|,
name|gr
argument_list|)
expr_stmt|;
name|gimp_preview_draw_buffer
argument_list|(
name|preview
argument_list|,
name|dst
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dst
argument_list|)
expr_stmt|;
name|g_rand_free
argument_list|(
name|gr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|noisify_add_channel (GtkWidget * table,gint channel,gchar * name,GimpDrawable * drawable,GtkWidget * preview)
name|noisify_add_channel
parameter_list|(
name|GtkWidget
modifier|*
name|table
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
name|GtkObject
modifier|*
name|adj
decl_stmt|;
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
name|channel
operator|+
literal|1
argument_list|,
name|name
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
name|channel
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
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
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"drawable"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|noisify_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
name|channel
index|]
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|noise_int
operator|.
name|channel_adj
index|[
name|channel
index|]
operator|=
name|adj
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|noisify_add_alpha_channel (GtkWidget * table,gint channel,gchar * name,GimpDrawable * drawable,GtkWidget * preview)
name|noisify_add_alpha_channel
parameter_list|(
name|GtkWidget
modifier|*
name|table
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
name|GtkObject
modifier|*
name|adj
decl_stmt|;
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
name|channel
operator|+
literal|1
argument_list|,
name|name
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
name|channel
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
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
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"drawable"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
name|channel
index|]
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|noise_int
operator|.
name|channel_adj
index|[
name|channel
index|]
operator|=
name|adj
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|noisify_dialog (GimpDrawable * drawable,gint channels)
name|noisify_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|channels
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"noisify"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Scatter RGB"
argument_list|)
argument_list|,
literal|"noisify"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"plug-in-noisify"
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
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_drawable_preview_new
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
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
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
argument_list|,
literal|"invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|noisify
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Co_rrelated noise"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|nvals
operator|.
name|correlated
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
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
name|nvals
operator|.
name|correlated
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Independent RGB"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|nvals
operator|.
name|independent
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
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
name|nvals
operator|.
name|independent
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
block|}
name|table
operator|=
name|gtk_table_new
argument_list|(
name|channels
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|noise_int
operator|.
name|channels
operator|=
name|channels
expr_stmt|;
if|if
condition|(
name|channels
operator|==
literal|1
condition|)
block|{
name|noisify_add_channel
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Gray:"
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|channels
operator|==
literal|2
condition|)
block|{
name|noisify_add_channel
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Gray:"
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|noisify_add_alpha_channel
argument_list|(
name|table
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"_Alpha:"
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|15
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|channels
operator|==
literal|3
condition|)
block|{
name|noisify_add_channel
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Red:"
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|noisify_add_channel
argument_list|(
name|table
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"_Green:"
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|noisify_add_channel
argument_list|(
name|table
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"_Blue:"
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|channels
operator|==
literal|4
condition|)
block|{
name|noisify_add_channel
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Red:"
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|noisify_add_channel
argument_list|(
name|table
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"_Green:"
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|noisify_add_channel
argument_list|(
name|table
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"_Blue:"
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|noisify_add_alpha_channel
argument_list|(
name|table
argument_list|,
literal|3
argument_list|,
name|_
argument_list|(
literal|"_Alpha:"
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|3
argument_list|,
literal|15
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|buffer
decl_stmt|;
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
name|channels
condition|;
name|i
operator|++
control|)
block|{
name|buffer
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Channel #%d:"
argument_list|)
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|noisify_add_channel
argument_list|(
name|table
argument_list|,
name|i
argument_list|,
name|buffer
argument_list|,
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

begin_comment
comment|/*  * Return a Gaussian (aka normal) distributed random variable.  *  * Adapted from gauss.c included in GNU scientific library.  *  * Ratio method (Kinderman-Monahan); see Knuth v2, 3rd ed, p130  * K+M, ACM Trans Math Software 3 (1977) 257-260. */
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|gauss (GRand * gr)
name|gauss
parameter_list|(
name|GRand
modifier|*
name|gr
parameter_list|)
block|{
name|gdouble
name|u
decl_stmt|,
name|v
decl_stmt|,
name|x
decl_stmt|;
do|do
block|{
name|v
operator|=
name|g_rand_double
argument_list|(
name|gr
argument_list|)
expr_stmt|;
do|do
name|u
operator|=
name|g_rand_double
argument_list|(
name|gr
argument_list|)
expr_stmt|;
do|while
condition|(
name|u
operator|==
literal|0
condition|)
do|;
comment|/* Const 1.715... = sqrt(8/e) */
name|x
operator|=
literal|1.71552776992141359295
operator|*
operator|(
name|v
operator|-
literal|0.5
operator|)
operator|/
name|u
expr_stmt|;
block|}
do|while
condition|(
name|x
operator|*
name|x
operator|>
operator|-
literal|4.0
operator|*
name|log
argument_list|(
name|u
argument_list|)
condition|)
do|;
return|return
name|x
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|noisify_double_adjustment_update (GtkAdjustment * adjustment,gpointer data)
name|noisify_double_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|n
decl_stmt|;
name|gimp_double_adjustment_update
argument_list|(
name|adjustment
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"drawable"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|nvals
operator|.
name|independent
condition|)
block|{
name|gint
name|i
decl_stmt|;
switch|switch
condition|(
name|noise_int
operator|.
name|channels
condition|)
block|{
case|case
literal|1
case|:
name|n
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|n
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|n
operator|=
literal|3
expr_stmt|;
break|break;
default|default:
name|n
operator|=
literal|3
expr_stmt|;
break|break;
block|}
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
if|if
condition|(
name|adjustment
operator|!=
name|GTK_ADJUSTMENT
argument_list|(
name|noise_int
operator|.
name|channel_adj
index|[
name|i
index|]
argument_list|)
condition|)
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|noise_int
operator|.
name|channel_adj
index|[
name|i
index|]
argument_list|)
argument_list|,
name|adjustment
operator|->
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

