begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* Value-Invert plug-in v1.1 by Adam D. Moss, adam@foxbox.org.  1999/02/27  *  * RGB<->HSV math optimizations by Mukund Sivaraman<muks@mukund.org>  * makes the plug-in 2-3 times faster. Using gimp_pixel_rgns_process()  * also makes memory management nicer. June 12, 2006.  *  * The plug-in only does v = 255 - v; for each pixel in the image, or  * each entry in the colormap depending upon the type of image, where 'v'  * is the value in HSV color model.  *  * The plug-in code is optimized towards this, in that it is not a full  * RGB->HSV->RGB transform, but shortcuts many of the calculations to  * effectively only do v = 255 - v. In fact, hue (0-360) is never  * calculated. The shortcuts can be derived from running a set of r, g, b  * values through the RGB->HSV transform and then from HSV->RGB and solving  * out the redundant portions.  *  * The plug-in also uses integer code exclusively for the main transform.  */
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

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-vinvert"
end_define

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
name|vinvert
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
name|vinvert_indexed
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|vinvert_render_row
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
name|width
parameter_list|,
name|gint
name|bpp
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
literal|"Input image (used for indexed images)"
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
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Invert the brightness of each pixel"
argument_list|)
argument_list|,
literal|"This function takes an indexed/RGB image and "
literal|"inverts its 'value' in HSV space.  The upshot of "
literal|"this is that the color and saturation at any given "
literal|"point remains the same, but its brightness is "
literal|"effectively inverted.  Quite strange.  Sometimes "
literal|"produces unpleasant color artifacts on images from "
literal|"lossy sources (ie. JPEG)."
argument_list|,
literal|"Adam D. Moss (adam@foxbox.org), "
literal|"Mukund Sivaraman<muks@mukund.org>"
argument_list|,
literal|"Adam D. Moss (adam@foxbox.org), "
literal|"Mukund Sivaraman<muks@mukund.org>"
argument_list|,
literal|"27th March 1997, "
literal|"12th June 2006"
argument_list|,
name|N_
argument_list|(
literal|"_Value Invert"
argument_list|)
argument_list|,
literal|"RGB*, INDEXED*"
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
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Colors/Invert"
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
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
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
comment|/*  Make sure that the drawable is indexed or RGB color  */
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
name|vinvert
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
elseif|else
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|vinvert_indexed
argument_list|(
name|image_ID
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|vinvert (GimpDrawable * drawable)
name|vinvert
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|total
decl_stmt|,
name|processed
decl_stmt|;
name|gint
name|update
decl_stmt|;
name|gint
name|channels
decl_stmt|;
name|GimpPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
decl_stmt|;
name|guchar
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|dest_row
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
return|return;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Value Invert"
argument_list|)
argument_list|)
expr_stmt|;
name|channels
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
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
name|dest_rgn
argument_list|,
name|drawable
argument_list|,
name|x
argument_list|,
name|y
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
name|total
operator|=
name|width
operator|*
name|height
expr_stmt|;
name|processed
operator|=
literal|0.0
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
operator|,
name|update
operator|=
literal|0
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
operator|,
name|update
operator|++
control|)
block|{
name|src_row
operator|=
name|src_rgn
operator|.
name|data
expr_stmt|;
name|dest_row
operator|=
name|dest_rgn
operator|.
name|data
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|src_rgn
operator|.
name|h
condition|;
name|i
operator|++
control|)
block|{
name|vinvert_render_row
argument_list|(
name|src_row
argument_list|,
name|dest_row
argument_list|,
name|src_rgn
operator|.
name|w
argument_list|,
name|channels
argument_list|)
expr_stmt|;
name|src_row
operator|+=
name|src_rgn
operator|.
name|rowstride
expr_stmt|;
name|dest_row
operator|+=
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
block|}
name|processed
operator|+=
name|src_rgn
operator|.
name|w
operator|*
name|src_rgn
operator|.
name|h
expr_stmt|;
name|update
operator|%=
literal|16
expr_stmt|;
if|if
condition|(
name|update
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
name|processed
operator|/
name|total
argument_list|)
expr_stmt|;
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
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
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|vinvert_indexed (gint32 image_ID)
name|vinvert_indexed
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|gint
name|ncols
decl_stmt|;
name|cmap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|ncols
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|cmap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|vinvert_render_row
argument_list|(
name|cmap
argument_list|,
name|cmap
argument_list|,
name|ncols
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gimp_image_set_colormap
argument_list|(
name|image_ID
argument_list|,
name|cmap
argument_list|,
name|ncols
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|vinvert_render_row (const guchar * src,guchar * dest,gint width,gint bpp)
name|vinvert_render_row
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
name|width
parameter_list|,
comment|/* in pixels */
name|gint
name|bpp
parameter_list|)
block|{
name|gint
name|j
decl_stmt|;
name|gint
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|value
decl_stmt|,
name|value2
decl_stmt|,
name|min
decl_stmt|;
name|gint
name|delta
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
block|{
name|r
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|g
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|b
operator|=
operator|*
name|src
operator|++
expr_stmt|;
if|if
condition|(
name|r
operator|>
name|g
condition|)
block|{
name|value
operator|=
name|MAX
argument_list|(
name|r
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|value
operator|=
name|MAX
argument_list|(
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|r
argument_list|,
name|b
argument_list|)
expr_stmt|;
block|}
name|delta
operator|=
name|value
operator|-
name|min
expr_stmt|;
if|if
condition|(
operator|(
name|value
operator|==
literal|0
operator|)
operator|||
operator|(
name|delta
operator|==
literal|0
operator|)
condition|)
block|{
name|r
operator|=
literal|255
operator|-
name|value
expr_stmt|;
name|g
operator|=
literal|255
operator|-
name|value
expr_stmt|;
name|b
operator|=
literal|255
operator|-
name|value
expr_stmt|;
block|}
else|else
block|{
name|value2
operator|=
name|value
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|r
operator|==
name|value
condition|)
block|{
name|r
operator|=
literal|255
operator|-
name|r
expr_stmt|;
name|b
operator|=
operator|(
operator|(
name|r
operator|*
name|b
operator|)
operator|+
name|value2
operator|)
operator|/
name|value
expr_stmt|;
name|g
operator|=
operator|(
operator|(
name|r
operator|*
name|g
operator|)
operator|+
name|value2
operator|)
operator|/
name|value
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g
operator|==
name|value
condition|)
block|{
name|g
operator|=
literal|255
operator|-
name|g
expr_stmt|;
name|r
operator|=
operator|(
operator|(
name|g
operator|*
name|r
operator|)
operator|+
name|value2
operator|)
operator|/
name|value
expr_stmt|;
name|b
operator|=
operator|(
operator|(
name|g
operator|*
name|b
operator|)
operator|+
name|value2
operator|)
operator|/
name|value
expr_stmt|;
block|}
else|else
block|{
name|b
operator|=
literal|255
operator|-
name|b
expr_stmt|;
name|g
operator|=
operator|(
operator|(
name|b
operator|*
name|g
operator|)
operator|+
name|value2
operator|)
operator|/
name|value
expr_stmt|;
name|r
operator|=
operator|(
operator|(
name|b
operator|*
name|r
operator|)
operator|+
name|value2
operator|)
operator|/
name|value
expr_stmt|;
block|}
block|}
operator|*
name|dest
operator|++
operator|=
name|r
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|g
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|b
expr_stmt|;
if|if
condition|(
name|bpp
operator|==
literal|4
condition|)
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
block|}
block|}
end_function

end_unit

