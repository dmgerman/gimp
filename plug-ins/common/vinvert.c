begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Value-Invert plug-in v1.1 by Adam D. Moss, adam@foxbox.org.  1999/02/27  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * BUGS:  *     Is not undoable when operating on indexed images - GIMP's fault.  */
end_comment

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
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpcolorspace.h"
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
name|indexed_vinvert
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
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
name|GDrawable
modifier|*
name|drawable
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

begin_decl_stmt
DECL|variable|run_mode
specifier|static
name|GRunModeType
name|run_mode
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
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

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|()
block|{
specifier|static
name|GParamDef
name|args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (used for indexed images)"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,   }
decl_stmt|;
specifier|static
name|GParamDef
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
specifier|static
name|int
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
specifier|static
name|int
name|nreturn_vals
init|=
literal|0
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_vinvert"
argument_list|,
name|_
argument_list|(
literal|"Invert the 'value' componant of an indexed/RGB image in HSV colourspace"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"This function takes an indexed/RGB image and inverts its 'value' in HSV space.  The upshot of this is that the colour and saturation at any given point remains the same, but its brightness is effectively inverted.  Quite strange.  Sometimes produces unpleasant colour artifacts on images from lossy sources (ie. JPEG)."
argument_list|)
argument_list|,
literal|"Adam D. Moss (adam@foxbox.org)"
argument_list|,
literal|"Adam D. Moss (adam@foxbox.org)"
argument_list|,
literal|"27th March 1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Colors/Value Invert"
argument_list|)
argument_list|,
literal|"RGB*, INDEXED*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nargs
argument_list|,
name|nreturn_vals
argument_list|,
name|args
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (char * name,int nparams,GParam * param,int * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
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
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|PARAM_STATUS
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
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
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
if|if
condition|(
name|run_mode
operator|!=
name|RUN_NONINTERACTIVE
condition|)
block|{
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_progress_init
argument_list|(
literal|"Value Invert..."
argument_list|)
expr_stmt|;
block|}
name|vinvert
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|RUN_NONINTERACTIVE
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
name|id
argument_list|)
condition|)
block|{
name|indexed_vinvert
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|STATUS_EXECUTION_ERROR
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
DECL|function|indexed_vinvert (gint32 image_ID)
name|indexed_vinvert
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
name|gimp_image_get_cmap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|ncols
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmap
operator|==
name|NULL
condition|)
block|{
name|printf
argument_list|(
literal|"vinvert: cmap was NULL!  Quitting...\n"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
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
name|gimp_image_set_cmap
argument_list|(
name|image_ID
argument_list|,
name|cmap
argument_list|,
name|ncols
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|vinvert_render_row (const guchar * src_data,guchar * dest_data,gint col,const gint bytes)
name|vinvert_render_row
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
while|while
condition|(
name|col
operator|--
condition|)
block|{
name|int
name|v1
decl_stmt|,
name|v2
decl_stmt|,
name|v3
decl_stmt|;
name|v1
operator|=
name|src_data
index|[
name|col
operator|*
name|bytes
index|]
expr_stmt|;
name|v2
operator|=
name|src_data
index|[
name|col
operator|*
name|bytes
operator|+
literal|1
index|]
expr_stmt|;
name|v3
operator|=
name|src_data
index|[
name|col
operator|*
name|bytes
operator|+
literal|2
index|]
expr_stmt|;
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|v1
argument_list|,
operator|&
name|v2
argument_list|,
operator|&
name|v3
argument_list|)
expr_stmt|;
name|v3
operator|=
literal|255
operator|-
name|v3
expr_stmt|;
name|gimp_hsv_to_rgb
argument_list|(
operator|&
name|v1
argument_list|,
operator|&
name|v2
argument_list|,
operator|&
name|v3
argument_list|)
expr_stmt|;
name|dest_data
index|[
name|col
operator|*
name|bytes
index|]
operator|=
name|v1
expr_stmt|;
name|dest_data
index|[
name|col
operator|*
name|bytes
operator|+
literal|1
index|]
operator|=
name|v2
expr_stmt|;
name|dest_data
index|[
name|col
operator|*
name|bytes
operator|+
literal|2
index|]
operator|=
name|v3
expr_stmt|;
if|if
condition|(
name|bytes
operator|>
literal|3
condition|)
block|{
name|gint
name|bytenum
decl_stmt|;
for|for
control|(
name|bytenum
operator|=
literal|3
init|;
name|bytenum
operator|<
name|bytes
condition|;
name|bytenum
operator|++
control|)
block|{
name|dest_data
index|[
name|col
operator|*
name|bytes
operator|+
name|bytenum
index|]
operator|=
name|src_data
index|[
name|col
operator|*
name|bytes
operator|+
name|bytenum
index|]
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|vinvert_render_region (const GPixelRgn srcPR,const GPixelRgn destPR)
name|vinvert_render_region
parameter_list|(
specifier|const
name|GPixelRgn
name|srcPR
parameter_list|,
specifier|const
name|GPixelRgn
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
name|vinvert_render_row
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
DECL|function|vinvert (GDrawable * drawable)
name|vinvert
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GPixelRgn
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
name|vinvert_render_region
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
name|RUN_NONINTERACTIVE
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
operator|(
operator|(
name|progress_skip
operator|++
operator|)
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
name|area_so_far
operator|/
operator|(
name|double
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
block|}
end_function

end_unit

