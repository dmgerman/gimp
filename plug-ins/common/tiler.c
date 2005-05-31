begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Tiler v0.31  * 22 May 1997  * Tim Rowley<tor@cs.brown.edu>  *  * The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimp/stdplugins-intl.h"
end_include

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
name|tile
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_make_seamless"
argument_list|,
literal|"Seamless tile creation"
argument_list|,
literal|"This plugin creates a seamless tileable from "
literal|"the input drawable"
argument_list|,
literal|"Tim Rowley"
argument_list|,
literal|"Tim Rowley"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Make Seamless"
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
literal|"plug_in_make_seamless"
argument_list|,
literal|"<Image>/Filters/Map"
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
name|GimpRunMode
name|run_mode
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
name|INIT_I18N
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
comment|/*  Make sure that the drawable is gray or RGB color  */
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
name|tile
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
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
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
DECL|function|weld_pixels (guchar * dest1,guchar * dest2,gint width,gint height,gint x,gint y,guint bpp,guchar * src1,guchar * src2)
name|weld_pixels
parameter_list|(
name|guchar
modifier|*
name|dest1
parameter_list|,
name|guchar
modifier|*
name|dest2
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|bpp
parameter_list|,
name|guchar
modifier|*
name|src1
parameter_list|,
name|guchar
modifier|*
name|src2
parameter_list|)
block|{
name|gdouble
name|a
init|=
operator|(
name|ABS
argument_list|(
name|x
operator|-
name|width
argument_list|)
operator|-
literal|1
operator|)
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|width
operator|-
literal|1
argument_list|)
decl_stmt|;
name|gdouble
name|b
init|=
operator|(
name|ABS
argument_list|(
name|y
operator|-
name|height
argument_list|)
operator|-
literal|1
operator|)
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|height
operator|-
literal|1
argument_list|)
decl_stmt|;
name|gdouble
name|w
decl_stmt|;
name|guint
name|i
decl_stmt|;
comment|/* mimic ambiguous point handling in original algorithm */
if|if
condition|(
name|a
operator|<
literal|1e-8
operator|&&
name|b
operator|>
literal|0.99999999
condition|)
name|w
operator|=
literal|1.0
expr_stmt|;
elseif|else
if|if
condition|(
name|a
operator|>
literal|0.99999999
operator|&&
name|b
operator|<
literal|1e-8
condition|)
name|w
operator|=
literal|0.0
expr_stmt|;
else|else
name|w
operator|=
literal|1.0
operator|-
name|a
operator|*
name|b
operator|/
operator|(
name|a
operator|*
name|b
operator|+
operator|(
literal|1.0
operator|-
name|a
operator|)
operator|*
operator|(
literal|1.0
operator|-
name|b
operator|)
operator|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bpp
condition|;
name|i
operator|++
control|)
name|dest1
index|[
name|i
index|]
operator|=
name|dest2
index|[
name|i
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|w
operator|*
name|src1
index|[
name|i
index|]
operator|+
operator|(
literal|1.0
operator|-
name|w
operator|)
operator|*
name|src2
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|weld_pixels_alpha (guchar * dest1,guchar * dest2,gint width,gint height,gint x,gint y,guint bpp,guchar * src1,guchar * src2)
name|weld_pixels_alpha
parameter_list|(
name|guchar
modifier|*
name|dest1
parameter_list|,
name|guchar
modifier|*
name|dest2
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|bpp
parameter_list|,
name|guchar
modifier|*
name|src1
parameter_list|,
name|guchar
modifier|*
name|src2
parameter_list|)
block|{
name|gdouble
name|a
init|=
operator|(
name|ABS
argument_list|(
name|x
operator|-
name|width
argument_list|)
operator|-
literal|1
operator|)
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|width
operator|-
literal|1
argument_list|)
decl_stmt|;
name|gdouble
name|b
init|=
operator|(
name|ABS
argument_list|(
name|y
operator|-
name|height
argument_list|)
operator|-
literal|1
operator|)
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|height
operator|-
literal|1
argument_list|)
decl_stmt|;
name|gdouble
name|w
decl_stmt|;
name|gdouble
name|alpha
decl_stmt|;
name|guint
name|ai
init|=
name|bpp
operator|-
literal|1
decl_stmt|;
name|guint
name|i
decl_stmt|;
comment|/* mimic ambiguous point handling in original algorithm */
if|if
condition|(
name|a
operator|<
literal|1e-8
operator|&&
name|b
operator|>
literal|0.99999999
condition|)
name|w
operator|=
literal|1.0
expr_stmt|;
elseif|else
if|if
condition|(
name|a
operator|>
literal|0.99999999
operator|&&
name|b
operator|<
literal|1e-8
condition|)
name|w
operator|=
literal|0.0
expr_stmt|;
else|else
name|w
operator|=
literal|1.0
operator|-
name|a
operator|*
name|b
operator|/
operator|(
name|a
operator|*
name|b
operator|+
operator|(
literal|1.0
operator|-
name|a
operator|)
operator|*
operator|(
literal|1.0
operator|-
name|b
operator|)
operator|)
expr_stmt|;
name|alpha
operator|=
name|w
operator|*
name|src1
index|[
name|ai
index|]
operator|+
operator|(
literal|1.0
operator|-
name|w
operator|)
operator|*
name|src2
index|[
name|ai
index|]
expr_stmt|;
name|dest1
index|[
name|ai
index|]
operator|=
name|dest2
index|[
name|ai
index|]
operator|=
operator|(
name|guchar
operator|)
name|alpha
expr_stmt|;
if|if
condition|(
name|dest1
index|[
name|ai
index|]
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ai
condition|;
name|i
operator|++
control|)
name|dest1
index|[
name|i
index|]
operator|=
name|dest2
index|[
name|i
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
name|w
operator|*
name|src1
index|[
name|i
index|]
operator|*
name|src1
index|[
name|ai
index|]
operator|+
operator|(
literal|1.0
operator|-
name|w
operator|)
operator|*
name|src2
index|[
name|i
index|]
operator|*
name|src2
index|[
name|ai
index|]
operator|)
operator|/
name|alpha
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_region (GimpDrawable * drawable,gboolean left,gint x1,gint y1,gint x2,gint y2)
name|tile_region
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|left
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
block|{
name|glong
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
name|wodd
decl_stmt|,
name|hodd
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|,
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|rgn1_x
decl_stmt|,
name|rgn2_x
decl_stmt|,
name|off_x
decl_stmt|;
specifier|static
name|gint
name|progress
init|=
literal|0
decl_stmt|;
name|gint
name|max_progress
decl_stmt|;
name|GimpPixelRgn
name|src1_rgn
decl_stmt|,
name|src2_rgn
decl_stmt|,
name|dest1_rgn
decl_stmt|,
name|dest2_rgn
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|guint
name|asymmetry_correction
decl_stmt|;
name|bpp
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
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|wodd
operator|=
name|width
operator|&
literal|1
expr_stmt|;
name|hodd
operator|=
name|height
operator|&
literal|1
expr_stmt|;
name|w
operator|=
name|width
operator|/
literal|2
expr_stmt|;
name|h
operator|=
name|height
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|left
condition|)
block|{
name|rgn1_x
operator|=
name|x1
expr_stmt|;
name|rgn2_x
operator|=
name|x1
operator|+
name|w
operator|+
name|wodd
expr_stmt|;
name|off_x
operator|=
name|w
operator|+
name|wodd
expr_stmt|;
block|}
else|else
block|{
name|rgn1_x
operator|=
name|x1
operator|+
name|w
operator|+
name|wodd
expr_stmt|;
name|rgn2_x
operator|=
name|x1
expr_stmt|;
name|off_x
operator|=
operator|-
name|w
operator|-
name|wodd
expr_stmt|;
block|}
name|asymmetry_correction
operator|=
operator|!
name|wodd
operator|&&
operator|!
name|left
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src1_rgn
argument_list|,
name|drawable
argument_list|,
name|rgn1_x
argument_list|,
name|y1
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest1_rgn
argument_list|,
name|drawable
argument_list|,
name|rgn1_x
argument_list|,
name|y1
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src2_rgn
argument_list|,
name|drawable
argument_list|,
name|rgn2_x
argument_list|,
name|y1
operator|+
name|h
operator|+
name|hodd
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest2_rgn
argument_list|,
name|drawable
argument_list|,
name|rgn2_x
argument_list|,
name|y1
operator|+
name|h
operator|+
name|hodd
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|max_progress
operator|=
name|width
operator|*
name|height
operator|/
literal|2
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|4
argument_list|,
operator|&
name|src1_rgn
argument_list|,
operator|&
name|dest1_rgn
argument_list|,
operator|&
name|src2_rgn
argument_list|,
operator|&
name|dest2_rgn
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
name|guchar
modifier|*
name|src1
init|=
name|src1_rgn
operator|.
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest1
init|=
name|dest1_rgn
operator|.
name|data
decl_stmt|;
name|guchar
modifier|*
name|src2
init|=
name|src2_rgn
operator|.
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest2
init|=
name|dest2_rgn
operator|.
name|data
decl_stmt|;
name|gint
name|row
init|=
name|src1_rgn
operator|.
name|y
operator|-
name|y1
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|src1_rgn
operator|.
name|h
condition|;
name|y
operator|++
operator|,
name|row
operator|++
control|)
block|{
name|guchar
modifier|*
name|s1
init|=
name|src1
decl_stmt|;
name|guchar
modifier|*
name|s2
init|=
name|src2
decl_stmt|;
name|guchar
modifier|*
name|d1
init|=
name|dest1
decl_stmt|;
name|guchar
modifier|*
name|d2
init|=
name|dest2
decl_stmt|;
name|gint
name|col
init|=
name|src1_rgn
operator|.
name|x
operator|-
name|x1
decl_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|src1_rgn
operator|.
name|w
condition|;
name|x
operator|++
operator|,
name|col
operator|++
control|)
block|{
name|weld_pixels_alpha
argument_list|(
name|d1
argument_list|,
name|d2
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|col
operator|+
name|asymmetry_correction
argument_list|,
name|row
argument_list|,
name|bpp
argument_list|,
name|s1
argument_list|,
name|s2
argument_list|)
expr_stmt|;
name|s1
operator|+=
name|bpp
expr_stmt|;
name|s2
operator|+=
name|bpp
expr_stmt|;
name|d1
operator|+=
name|bpp
expr_stmt|;
name|d2
operator|+=
name|bpp
expr_stmt|;
block|}
block|}
else|else
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|src1_rgn
operator|.
name|w
condition|;
name|x
operator|++
operator|,
name|col
operator|++
control|)
block|{
name|weld_pixels
argument_list|(
name|d1
argument_list|,
name|d2
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|col
operator|+
name|asymmetry_correction
argument_list|,
name|row
argument_list|,
name|bpp
argument_list|,
name|s1
argument_list|,
name|s2
argument_list|)
expr_stmt|;
name|s1
operator|+=
name|bpp
expr_stmt|;
name|s2
operator|+=
name|bpp
expr_stmt|;
name|d1
operator|+=
name|bpp
expr_stmt|;
name|d2
operator|+=
name|bpp
expr_stmt|;
block|}
block|}
name|src1
operator|+=
name|src1_rgn
operator|.
name|rowstride
expr_stmt|;
name|src2
operator|+=
name|src2_rgn
operator|.
name|rowstride
expr_stmt|;
name|dest1
operator|+=
name|dest1_rgn
operator|.
name|rowstride
expr_stmt|;
name|dest2
operator|+=
name|dest2_rgn
operator|.
name|rowstride
expr_stmt|;
block|}
name|progress
operator|+=
name|src1_rgn
operator|.
name|w
operator|*
name|src1_rgn
operator|.
name|h
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|progress
operator|/
operator|(
name|gdouble
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|copy_region (GimpDrawable * drawable,gint x,gint y,gint w,gint h)
name|copy_region
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
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
name|src_rgn
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
name|gint
name|k
decl_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|src_rgn
operator|.
name|h
condition|;
name|k
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|dest_rgn
operator|.
name|data
operator|+
name|k
operator|*
name|dest_rgn
operator|.
name|rowstride
argument_list|,
name|src_rgn
operator|.
name|data
operator|+
name|k
operator|*
name|src_rgn
operator|.
name|rowstride
argument_list|,
name|src_rgn
operator|.
name|w
operator|*
name|src_rgn
operator|.
name|bpp
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile (GimpDrawable * drawable)
name|tile
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|glong
name|width
decl_stmt|,
name|height
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
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Tiler..."
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
if|if
condition|(
name|width
operator|&
literal|1
condition|)
comment|/* Copy middle column */
block|{
name|copy_region
argument_list|(
name|drawable
argument_list|,
name|x1
operator|+
name|width
operator|/
literal|2
argument_list|,
name|y1
argument_list|,
literal|1
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|height
operator|&
literal|1
condition|)
comment|/* Copy middle row */
block|{
name|copy_region
argument_list|(
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
name|height
operator|/
literal|2
argument_list|,
name|width
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
name|tile_region
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|tile_region
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
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
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

