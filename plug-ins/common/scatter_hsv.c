begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* scatter_hsv.c -- This is a plug-in for GIMP (1.0's API)  * Author: Shuji Narazaki<narazaki@InetQ.or.jp>  * Time-stamp:<2000-01-08 02:49:39 yasuhiro>  * Version: 0.42  *  * Copyright (C) 1997 Shuji Narazaki<narazaki@InetQ.or.jp>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|HSV_NOISE_PROC
define|#
directive|define
name|HSV_NOISE_PROC
value|"plug-in-hsv-noise"
end_define

begin_define
DECL|macro|SCATTER_HSV_PROC
define|#
directive|define
name|SCATTER_HSV_PROC
value|"plug-in-scatter-hsv"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"scatter_hsv"
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|100
end_define

begin_define
DECL|macro|ENTRY_WIDTH
define|#
directive|define
name|ENTRY_WIDTH
value|3
end_define

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
name|scatter_hsv
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|scatter_hsv_dialog
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
name|scatter_hsv_preview
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|scatter_hsv_scatter
parameter_list|(
name|guchar
modifier|*
name|r
parameter_list|,
name|guchar
modifier|*
name|g
parameter_list|,
name|guchar
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|randomize_value
parameter_list|(
name|gint
name|now
parameter_list|,
name|gint
name|min
parameter_list|,
name|gint
name|max
parameter_list|,
name|gboolean
name|wraps_around
parameter_list|,
name|gint
name|rand_max
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon298db6b10108
block|{
DECL|member|holdness
name|gint
name|holdness
decl_stmt|;
DECL|member|hue_distance
name|gint
name|hue_distance
decl_stmt|;
DECL|member|saturation_distance
name|gint
name|saturation_distance
decl_stmt|;
DECL|member|value_distance
name|gint
name|value_distance
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|ValueType
block|}
name|ValueType
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|VALS
specifier|static
name|ValueType
name|VALS
init|=
block|{
literal|2
block|,
literal|3
block|,
literal|10
block|,
literal|10
block|,
name|TRUE
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
specifier|const
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (not used)"
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
literal|"holdness"
block|,
literal|"convolution strength"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"hue-distance"
block|,
literal|"scattering of hue angle [0,180]"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"saturation-distance"
block|,
literal|"distribution distance on saturation axis [0,255]"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"value-distance"
block|,
literal|"distribution distance on value axis [0,255]"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|HSV_NOISE_PROC
argument_list|,
name|N_
argument_list|(
literal|"Randomize hue/saturation/value independently"
argument_list|)
argument_list|,
literal|"Scattering pixel values in HSV space"
argument_list|,
literal|"Shuji Narazaki (narazaki@InetQ.or.jp)"
argument_list|,
literal|"Shuji Narazaki"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"HSV Noise..."
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
name|gimp_plugin_menu_register
argument_list|(
name|HSV_NOISE_PROC
argument_list|,
literal|"<Image>/Filters/Noise"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SCATTER_HSV_PROC
argument_list|,
literal|"Scattering pixel values in HSV space"
argument_list|,
literal|"Scattering pixel values in HSV space"
argument_list|,
literal|"Shuji Narazaki (narazaki@InetQ.or.jp)"
argument_list|,
literal|"Shuji Narazaki"
argument_list|,
literal|"1997"
argument_list|,
name|NULL
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
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|INIT_I18N
argument_list|()
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
name|d_int32
argument_list|)
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|gimp_get_data
argument_list|(
name|HSV_NOISE_PROC
argument_list|,
operator|&
name|VALS
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"Cannot operate on non-RGB drawables."
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|scatter_hsv_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|VALS
operator|.
name|holdness
operator|=
name|CLAMP
argument_list|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
literal|1
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|VALS
operator|.
name|hue_distance
operator|=
name|CLAMP
argument_list|(
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
literal|0
argument_list|,
literal|180
argument_list|)
expr_stmt|;
name|VALS
operator|.
name|saturation_distance
operator|=
name|CLAMP
argument_list|(
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|VALS
operator|.
name|value_distance
operator|=
name|CLAMP
argument_list|(
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|HSV_NOISE_PROC
argument_list|,
operator|&
name|VALS
argument_list|)
expr_stmt|;
break|break;
block|}
name|scatter_hsv
argument_list|(
name|drawable
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
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
operator|&&
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|gimp_set_data
argument_list|(
name|HSV_NOISE_PROC
argument_list|,
operator|&
name|VALS
argument_list|,
sizeof|sizeof
argument_list|(
name|ValueType
argument_list|)
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|scatter_hsv_func (const guchar * src,guchar * dest,gint bpp,gpointer data)
name|scatter_hsv_func
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
name|guchar
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|h
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|s
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|v
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
name|scatter_hsv_scatter
argument_list|(
operator|&
name|h
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
name|h
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|s
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|v
expr_stmt|;
if|if
condition|(
name|bpp
operator|==
literal|4
condition|)
name|dest
index|[
literal|3
index|]
operator|=
name|src
index|[
literal|3
index|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|scatter_hsv (GimpDrawable * drawable)
name|scatter_hsv
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
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
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"HSV Noise"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rgn_iterate2
argument_list|(
name|drawable
argument_list|,
literal|0
comment|/* unused */
argument_list|,
name|scatter_hsv_func
argument_list|,
name|NULL
argument_list|)
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
name|gint
DECL|function|randomize_value (gint now,gint min,gint max,gboolean wraps_around,gint rand_max)
name|randomize_value
parameter_list|(
name|gint
name|now
parameter_list|,
name|gint
name|min
parameter_list|,
name|gint
name|max
parameter_list|,
name|gboolean
name|wraps_around
parameter_list|,
name|gint
name|rand_max
parameter_list|)
block|{
name|gint
name|flag
decl_stmt|,
name|new
decl_stmt|,
name|steps
decl_stmt|,
name|index
decl_stmt|;
name|gdouble
name|rand_val
decl_stmt|;
name|steps
operator|=
name|max
operator|-
name|min
operator|+
literal|1
expr_stmt|;
name|rand_val
operator|=
name|g_random_double
argument_list|()
expr_stmt|;
for|for
control|(
name|index
operator|=
literal|1
init|;
name|index
operator|<
name|VALS
operator|.
name|holdness
condition|;
name|index
operator|++
control|)
block|{
name|double
name|tmp
init|=
name|g_random_double
argument_list|()
decl_stmt|;
if|if
condition|(
name|tmp
operator|<
name|rand_val
condition|)
name|rand_val
operator|=
name|tmp
expr_stmt|;
block|}
if|if
condition|(
name|g_random_double
argument_list|()
operator|<
literal|0.5
condition|)
name|flag
operator|=
operator|-
literal|1
expr_stmt|;
else|else
name|flag
operator|=
literal|1
expr_stmt|;
name|new
operator|=
name|now
operator|+
name|flag
operator|*
operator|(
call|(
name|int
call|)
argument_list|(
name|rand_max
operator|*
name|rand_val
argument_list|)
operator|%
name|steps
operator|)
expr_stmt|;
if|if
condition|(
name|new
operator|<
name|min
condition|)
block|{
if|if
condition|(
name|wraps_around
operator|==
name|TRUE
condition|)
name|new
operator|+=
name|steps
expr_stmt|;
else|else
name|new
operator|=
name|min
expr_stmt|;
block|}
if|if
condition|(
name|max
operator|<
name|new
condition|)
block|{
if|if
condition|(
name|wraps_around
operator|==
name|TRUE
condition|)
name|new
operator|-=
name|steps
expr_stmt|;
else|else
name|new
operator|=
name|max
expr_stmt|;
block|}
return|return
name|new
return|;
block|}
end_function

begin_function
DECL|function|scatter_hsv_scatter (guchar * r,guchar * g,guchar * b)
specifier|static
name|void
name|scatter_hsv_scatter
parameter_list|(
name|guchar
modifier|*
name|r
parameter_list|,
name|guchar
modifier|*
name|g
parameter_list|,
name|guchar
modifier|*
name|b
parameter_list|)
block|{
name|gint
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|gint
name|h1
decl_stmt|,
name|s1
decl_stmt|,
name|v1
decl_stmt|;
name|gint
name|h2
decl_stmt|,
name|s2
decl_stmt|,
name|v2
decl_stmt|;
name|h
operator|=
operator|*
name|r
expr_stmt|;
name|s
operator|=
operator|*
name|g
expr_stmt|;
name|v
operator|=
operator|*
name|b
expr_stmt|;
name|gimp_rgb_to_hsv_int
argument_list|(
operator|&
name|h
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
literal|0
operator|<
name|VALS
operator|.
name|hue_distance
condition|)
name|h
operator|=
name|randomize_value
argument_list|(
name|h
argument_list|,
literal|0
argument_list|,
literal|360
argument_list|,
name|TRUE
argument_list|,
name|VALS
operator|.
name|hue_distance
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
literal|0
operator|<
name|VALS
operator|.
name|saturation_distance
operator|)
condition|)
name|s
operator|=
name|randomize_value
argument_list|(
name|s
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|,
name|FALSE
argument_list|,
name|VALS
operator|.
name|saturation_distance
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
literal|0
operator|<
name|VALS
operator|.
name|value_distance
operator|)
condition|)
name|v
operator|=
name|randomize_value
argument_list|(
name|v
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|,
name|FALSE
argument_list|,
name|VALS
operator|.
name|value_distance
argument_list|)
expr_stmt|;
name|h1
operator|=
name|h
expr_stmt|;
name|s1
operator|=
name|s
expr_stmt|;
name|v1
operator|=
name|v
expr_stmt|;
name|gimp_hsv_to_rgb_int
argument_list|(
operator|&
name|h
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
comment|/* don't believe ! */
name|h2
operator|=
name|h
expr_stmt|;
name|s2
operator|=
name|s
expr_stmt|;
name|v2
operator|=
name|v
expr_stmt|;
name|gimp_rgb_to_hsv_int
argument_list|(
operator|&
name|h2
argument_list|,
operator|&
name|s2
argument_list|,
operator|&
name|v2
argument_list|)
expr_stmt|;
comment|/* h2 should be h1. But... */
if|if
condition|(
operator|(
name|abs
argument_list|(
name|h1
operator|-
name|h2
argument_list|)
operator|<=
name|VALS
operator|.
name|hue_distance
operator|)
operator|&&
operator|(
name|abs
argument_list|(
name|s1
operator|-
name|s2
argument_list|)
operator|<=
name|VALS
operator|.
name|saturation_distance
operator|)
operator|&&
operator|(
name|abs
argument_list|(
name|v1
operator|-
name|v2
argument_list|)
operator|<=
name|VALS
operator|.
name|value_distance
operator|)
condition|)
block|{
operator|*
name|r
operator|=
name|h
expr_stmt|;
operator|*
name|g
operator|=
name|s
expr_stmt|;
operator|*
name|b
operator|=
name|v
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|scatter_hsv_preview (GimpPreview * preview)
name|scatter_hsv_preview
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
name|scatter_hsv_func
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
name|NULL
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
block|}
end_function

begin_comment
comment|/* dialog stuff */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|scatter_hsv_dialog (GimpDrawable * drawable)
name|scatter_hsv_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|table
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
name|PLUG_IN_BINARY
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Scatter HSV"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|HSV_NOISE_PROC
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
name|gimp_window_set_transient
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
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
operator|&
name|VALS
operator|.
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
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
name|scatter_hsv_preview
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
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
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Holdness:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|ENTRY_WIDTH
argument_list|,
name|VALS
operator|.
name|holdness
argument_list|,
literal|1
argument_list|,
literal|8
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
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
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|holdness
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
literal|"H_ue:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|ENTRY_WIDTH
argument_list|,
name|VALS
operator|.
name|hue_distance
argument_list|,
literal|0
argument_list|,
literal|180
argument_list|,
literal|1
argument_list|,
literal|6
argument_list|,
literal|0
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
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|hue_distance
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
literal|"_Saturation:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|ENTRY_WIDTH
argument_list|,
name|VALS
operator|.
name|saturation_distance
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|,
literal|1
argument_list|,
literal|8
argument_list|,
literal|0
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
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|saturation_distance
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
literal|"_Value:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|ENTRY_WIDTH
argument_list|,
name|VALS
operator|.
name|value_distance
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|,
literal|1
argument_list|,
literal|8
argument_list|,
literal|0
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
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|value_distance
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

end_unit

