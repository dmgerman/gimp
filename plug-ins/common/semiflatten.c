begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  *  Semi-Flatten plug-in v1.0 by Adam D. Moss, adam@foxbox.org.  1998/01/27  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * TODO:  *     Use tile iteration instead of dumb row-walking  */
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
name|semiflatten
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
name|semiflatten_render_row
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
name|row
parameter_list|,
name|gint
name|row_width
parameter_list|,
name|gint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|bgred
DECL|variable|bggreen
DECL|variable|bgblue
specifier|static
name|guchar
name|bgred
decl_stmt|,
name|bggreen
decl_stmt|,
name|bgblue
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
specifier|static
name|gint
name|nargs
init|=
sizeof|sizeof
argument_list|(
name|args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_semiflatten"
argument_list|,
literal|"Flatten pixels in an RGBA image that aren't "
literal|"completely transparent against the current GIMP "
literal|"background color"
argument_list|,
literal|"This plugin flattens pixels in an RGBA image that "
literal|"aren't completely transparent against the current "
literal|"GIMP background color"
argument_list|,
literal|"Adam D. Moss (adam@foxbox.org)"
argument_list|,
literal|"Adam D. Moss (adam@foxbox.org)"
argument_list|,
literal|"27th January 1998"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Colors/Semi-Flatten"
argument_list|)
argument_list|,
literal|"RGBA"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|nargs
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
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
comment|/*  Make sure that the drawable is indexed or RGB color  */
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Semi-Flatten..."
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
name|semiflatten
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
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
DECL|function|semiflatten_render_row (const guchar * src_row,guchar * dest_row,gint row,gint row_width,gint bytes)
name|semiflatten_render_row
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
name|row
parameter_list|,
name|gint
name|row_width
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
name|gint
name|col
decl_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|row_width
condition|;
name|col
operator|++
control|)
block|{
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|0
index|]
operator|=
operator|(
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|0
index|]
operator|*
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|3
index|]
operator|)
operator|/
literal|255
operator|+
operator|(
name|bgred
operator|*
operator|(
literal|255
operator|-
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|3
index|]
operator|)
operator|)
operator|/
literal|255
expr_stmt|;
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|1
index|]
operator|=
operator|(
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|1
index|]
operator|*
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|3
index|]
operator|)
operator|/
literal|255
operator|+
operator|(
name|bggreen
operator|*
operator|(
literal|255
operator|-
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|3
index|]
operator|)
operator|)
operator|/
literal|255
expr_stmt|;
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|2
index|]
operator|=
operator|(
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|2
index|]
operator|*
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|3
index|]
operator|)
operator|/
literal|255
operator|+
operator|(
name|bgblue
operator|*
operator|(
literal|255
operator|-
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|3
index|]
operator|)
operator|)
operator|/
literal|255
expr_stmt|;
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|3
index|]
operator|=
operator|(
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|3
index|]
operator|==
literal|0
operator|)
condition|?
literal|0
else|:
literal|255
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|semiflatten (GimpDrawable * drawable)
name|semiflatten
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
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|guchar
modifier|*
name|src_row
decl_stmt|;
name|guchar
modifier|*
name|dest_row
decl_stmt|;
name|gint
name|row
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
comment|/* Fetch the GIMP current background colour, to semi-flatten against */
name|gimp_palette_get_background
argument_list|(
operator|&
name|bgred
argument_list|,
operator|&
name|bggreen
argument_list|,
operator|&
name|bgblue
argument_list|)
expr_stmt|;
comment|/* Get the input area. This is the bounding box of the selection in    *  the image (or the entire image if there is no selection). Only    *  operating on the input area is simply an optimization. It doesn't    *  need to be done for correct operation. (It simply makes it go    *  faster, since fewer pixels need to be operated on).    */
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
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
comment|/* Get the size of the input image. (This will/must be the same    *  as the size of the output image.    */
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
comment|/*  allocate row buffers  */
name|src_row
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
name|dest_row
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
comment|/*  initialize the pixel regions  */
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
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|src_row
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
name|semiflatten_render_row
argument_list|(
name|src_row
argument_list|,
name|dest_row
argument_list|,
name|row
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
comment|/*  store the dest  */
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_row
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
if|if
condition|(
operator|(
name|row
operator|%
literal|10
operator|)
operator|==
literal|0
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
name|id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|id
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
name|free
argument_list|(
name|src_row
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|dest_row
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

