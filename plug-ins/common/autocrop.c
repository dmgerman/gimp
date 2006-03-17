begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Autocrop plug-in version 1.00  * by Tim Newsome<drz@froody.bloke.com>  */
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
DECL|macro|AUTOCROP_PROC
define|#
directive|define
name|AUTOCROP_PROC
value|"plug-in-autocrop"
end_define

begin_define
DECL|macro|AUTOCROP_LAYER_PROC
define|#
directive|define
name|AUTOCROP_LAYER_PROC
value|"plug-in-autocrop-layer"
end_define

begin_comment
comment|/* Declare local functions. */
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
name|gboolean
name|colors_equal
parameter_list|(
specifier|const
name|guchar
modifier|*
name|col1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|col2
parameter_list|,
name|gint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|guess_bgcolor
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pr
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|guchar
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|autocrop
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gboolean
name|show_progress
parameter_list|,
name|gboolean
name|layer_only
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

begin_decl_stmt
DECL|variable|bytes
specifier|static
name|gint
name|bytes
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
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|AUTOCROP_PROC
argument_list|,
name|N_
argument_list|(
literal|"Remove empty borders from the image"
argument_list|)
argument_list|,
literal|""
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Autocrop Image"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
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
name|AUTOCROP_PROC
argument_list|,
literal|"<Image>/Image/Crop"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|AUTOCROP_LAYER_PROC
argument_list|,
name|N_
argument_list|(
literal|"Remove empty borders from the layer"
argument_list|)
argument_list|,
literal|""
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Autocrop Layer"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
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
name|AUTOCROP_LAYER_PROC
argument_list|,
literal|"<Image>/Layer/Crop"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint n_params,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|n_params
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
name|gint32
name|image_id
decl_stmt|;
name|gboolean
name|interactive
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
name|interactive
operator|=
operator|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
operator|)
expr_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
if|if
condition|(
name|n_params
operator|!=
literal|3
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
goto|goto
name|out
goto|;
block|}
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
name|image_id
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
operator|||
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
if|if
condition|(
name|interactive
condition|)
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Cropping"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
name|MAX
argument_list|(
name|drawable
operator|->
name|width
operator|/
name|gimp_tile_width
argument_list|()
argument_list|,
name|drawable
operator|->
name|height
operator|/
name|gimp_tile_height
argument_list|()
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|autocrop
argument_list|(
name|drawable
argument_list|,
name|image_id
argument_list|,
name|interactive
argument_list|,
name|strcmp
argument_list|(
name|name
argument_list|,
name|AUTOCROP_LAYER_PROC
argument_list|)
operator|==
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|interactive
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
name|out
label|:
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
DECL|function|autocrop (GimpDrawable * drawable,gint32 image_id,gboolean show_progress,gboolean layer_only)
name|autocrop
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gboolean
name|show_progress
parameter_list|,
name|gboolean
name|layer_only
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|,
name|i
decl_stmt|;
name|gboolean
name|abort
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|guchar
name|color
index|[
literal|4
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|gint32
name|layer_id
init|=
literal|0
decl_stmt|;
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
name|gimp_drawable_offsets
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_only
condition|)
block|{
name|layer_id
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_id
operator|==
operator|-
literal|1
condition|)
block|{
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
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
comment|/* First, let's figure out what exactly to crop. */
name|buffer
operator|=
name|g_malloc
argument_list|(
operator|(
name|width
operator|>
name|height
condition|?
name|width
else|:
name|height
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|guess_bgcolor
argument_list|(
operator|&
name|srcPR
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bytes
argument_list|,
name|color
argument_list|)
expr_stmt|;
comment|/* Check how many of the top lines are uniform. */
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|y1
operator|=
literal|0
init|;
name|y1
operator|<
name|height
operator|&&
operator|!
name|abort
condition|;
name|y1
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|buffer
argument_list|,
literal|0
argument_list|,
name|y1
argument_list|,
name|width
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
operator|&&
operator|!
name|abort
condition|;
name|i
operator|++
control|)
name|abort
operator|=
operator|!
name|colors_equal
argument_list|(
name|color
argument_list|,
name|buffer
operator|+
name|i
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|y1
operator|==
name|height
operator|-
literal|1
operator|&&
operator|!
name|abort
condition|)
block|{
comment|/* whee - a plain color drawable. Do nothing. */
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|show_progress
condition|)
name|gimp_progress_update
argument_list|(
literal|0.25
argument_list|)
expr_stmt|;
comment|/* Check how many of the bottom lines are uniform. */
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|y2
operator|=
name|height
operator|-
literal|1
init|;
name|y2
operator|>=
literal|0
operator|&&
operator|!
name|abort
condition|;
name|y2
operator|--
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|buffer
argument_list|,
literal|0
argument_list|,
name|y2
argument_list|,
name|width
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
operator|&&
operator|!
name|abort
condition|;
name|i
operator|++
control|)
name|abort
operator|=
operator|!
name|colors_equal
argument_list|(
name|color
argument_list|,
name|buffer
operator|+
name|i
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
name|y2
operator|+=
literal|1
expr_stmt|;
comment|/* to make y2 - y1 == height */
comment|/* The coordinates are now the first rows which DON'T match    * the color. Crop instead to one row larger:    */
if|if
condition|(
name|y1
operator|>
literal|0
condition|)
operator|--
name|y1
expr_stmt|;
if|if
condition|(
name|y2
operator|<
name|height
operator|-
literal|1
condition|)
operator|++
name|y2
expr_stmt|;
if|if
condition|(
name|show_progress
condition|)
name|gimp_progress_update
argument_list|(
literal|0.5
argument_list|)
expr_stmt|;
comment|/* Check how many of the left lines are uniform. */
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|x1
operator|=
literal|0
init|;
name|x1
operator|<
name|width
operator|&&
operator|!
name|abort
condition|;
name|x1
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_col
argument_list|(
operator|&
name|srcPR
argument_list|,
name|buffer
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|y2
operator|-
name|y1
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
name|y2
operator|-
name|y1
operator|&&
operator|!
name|abort
condition|;
name|i
operator|++
control|)
name|abort
operator|=
operator|!
name|colors_equal
argument_list|(
name|color
argument_list|,
name|buffer
operator|+
name|i
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|show_progress
condition|)
name|gimp_progress_update
argument_list|(
literal|0.75
argument_list|)
expr_stmt|;
comment|/* Check how many of the right lines are uniform. */
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|x2
operator|=
name|width
operator|-
literal|1
init|;
name|x2
operator|>=
literal|0
operator|&&
operator|!
name|abort
condition|;
name|x2
operator|--
control|)
block|{
name|gimp_pixel_rgn_get_col
argument_list|(
operator|&
name|srcPR
argument_list|,
name|buffer
argument_list|,
name|x2
argument_list|,
name|y1
argument_list|,
name|y2
operator|-
name|y1
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
name|y2
operator|-
name|y1
operator|&&
operator|!
name|abort
condition|;
name|i
operator|++
control|)
name|abort
operator|=
operator|!
name|colors_equal
argument_list|(
name|color
argument_list|,
name|buffer
operator|+
name|i
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
name|x2
operator|+=
literal|1
expr_stmt|;
comment|/* to make x2 - x1 == width */
comment|/* The coordinates are now the first columns which DON'T match    * the color. Crop instead to one column larger:    */
if|if
condition|(
name|x1
operator|>
literal|0
condition|)
operator|--
name|x1
expr_stmt|;
if|if
condition|(
name|x2
operator|<
name|width
operator|-
literal|1
condition|)
operator|++
name|x2
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|x2
operator|-
name|x1
operator|!=
name|width
operator|||
name|y2
operator|-
name|y1
operator|!=
name|height
condition|)
block|{
if|if
condition|(
name|layer_only
condition|)
block|{
name|gimp_layer_resize
argument_list|(
name|layer_id
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
operator|-
name|x1
argument_list|,
operator|-
name|y1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* convert to image coordinates */
name|x1
operator|+=
name|off_x
expr_stmt|;
name|x2
operator|+=
name|off_x
expr_stmt|;
name|y1
operator|+=
name|off_y
expr_stmt|;
name|y2
operator|+=
name|off_y
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|x1
operator|<
literal|0
operator|||
name|y1
operator|<
literal|0
operator|||
name|x2
operator|>
name|gimp_image_width
argument_list|(
name|image_id
argument_list|)
operator|||
name|y2
operator|>
name|gimp_image_height
argument_list|(
name|image_id
argument_list|)
condition|)
block|{
comment|/*                * partially outside the image area, we need to                * resize the image to be able to crop properly.                */
name|gimp_image_resize
argument_list|(
name|image_id
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
operator|-
name|x1
argument_list|,
operator|-
name|y1
argument_list|)
expr_stmt|;
name|x2
operator|-=
name|x1
expr_stmt|;
name|y2
operator|-=
name|y1
expr_stmt|;
name|x1
operator|=
name|y1
operator|=
literal|0
expr_stmt|;
block|}
name|gimp_image_crop
argument_list|(
name|image_id
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|show_progress
condition|)
name|gimp_progress_update
argument_list|(
literal|1.00
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|guess_bgcolor (GimpPixelRgn * pr,gint width,gint height,gint bytes,guchar * color)
name|guess_bgcolor
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pr
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|guchar
modifier|*
name|color
parameter_list|)
block|{
name|guchar
name|tl
index|[
literal|4
index|]
decl_stmt|,
name|tr
index|[
literal|4
index|]
decl_stmt|,
name|bl
index|[
literal|4
index|]
decl_stmt|,
name|br
index|[
literal|4
index|]
decl_stmt|;
name|gimp_pixel_rgn_get_pixel
argument_list|(
name|pr
argument_list|,
name|tl
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_pixel
argument_list|(
name|pr
argument_list|,
name|tr
argument_list|,
name|width
operator|-
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_pixel
argument_list|(
name|pr
argument_list|,
name|bl
argument_list|,
literal|0
argument_list|,
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_pixel
argument_list|(
name|pr
argument_list|,
name|br
argument_list|,
name|width
operator|-
literal|1
argument_list|,
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* Algorithm pinched from pnmcrop.    * To guess the background, first see if 3 corners are equal.    * Then if two are equal.    * Otherwise average the colors.    */
if|if
condition|(
name|colors_equal
argument_list|(
name|tr
argument_list|,
name|bl
argument_list|,
name|bytes
argument_list|)
operator|&&
name|colors_equal
argument_list|(
name|tr
argument_list|,
name|br
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|tr
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
return|return
literal|3
return|;
block|}
elseif|else
if|if
condition|(
name|colors_equal
argument_list|(
name|tl
argument_list|,
name|bl
argument_list|,
name|bytes
argument_list|)
operator|&&
name|colors_equal
argument_list|(
name|tl
argument_list|,
name|br
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|tl
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
return|return
literal|3
return|;
block|}
elseif|else
if|if
condition|(
name|colors_equal
argument_list|(
name|tl
argument_list|,
name|tr
argument_list|,
name|bytes
argument_list|)
operator|&&
name|colors_equal
argument_list|(
name|tl
argument_list|,
name|br
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|tl
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
return|return
literal|3
return|;
block|}
elseif|else
if|if
condition|(
name|colors_equal
argument_list|(
name|tl
argument_list|,
name|tr
argument_list|,
name|bytes
argument_list|)
operator|&&
name|colors_equal
argument_list|(
name|tl
argument_list|,
name|bl
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|tl
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
return|return
literal|3
return|;
block|}
elseif|else
if|if
condition|(
name|colors_equal
argument_list|(
name|tl
argument_list|,
name|tr
argument_list|,
name|bytes
argument_list|)
operator|||
name|colors_equal
argument_list|(
name|tl
argument_list|,
name|bl
argument_list|,
name|bytes
argument_list|)
operator|||
name|colors_equal
argument_list|(
name|tl
argument_list|,
name|br
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|tl
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
return|return
literal|2
return|;
block|}
elseif|else
if|if
condition|(
name|colors_equal
argument_list|(
name|tr
argument_list|,
name|bl
argument_list|,
name|bytes
argument_list|)
operator|||
name|colors_equal
argument_list|(
name|tr
argument_list|,
name|bl
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|tr
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
return|return
literal|2
return|;
block|}
elseif|else
if|if
condition|(
name|colors_equal
argument_list|(
name|br
argument_list|,
name|bl
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|br
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
return|return
literal|2
return|;
block|}
else|else
block|{
while|while
condition|(
name|bytes
operator|--
condition|)
block|{
name|color
index|[
name|bytes
index|]
operator|=
operator|(
name|tl
index|[
name|bytes
index|]
operator|+
name|tr
index|[
name|bytes
index|]
operator|+
name|bl
index|[
name|bytes
index|]
operator|+
name|br
index|[
name|bytes
index|]
operator|)
operator|/
literal|4
expr_stmt|;
block|}
return|return
literal|0
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|colors_equal (const guchar * col1,const guchar * col2,gint bytes)
name|colors_equal
parameter_list|(
specifier|const
name|guchar
modifier|*
name|col1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|col2
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
name|gboolean
name|equal
init|=
name|TRUE
decl_stmt|;
name|gint
name|b
decl_stmt|;
if|if
condition|(
operator|(
name|bytes
operator|==
literal|2
operator|||
name|bytes
operator|==
literal|4
operator|)
operator|&&
comment|/* HACK! */
name|col1
index|[
name|bytes
operator|-
literal|1
index|]
operator|==
literal|0
operator|&&
name|col2
index|[
name|bytes
operator|-
literal|1
index|]
operator|==
literal|0
condition|)
block|{
return|return
name|TRUE
return|;
comment|/* handle zero alpha */
block|}
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
block|{
if|if
condition|(
name|col1
index|[
name|b
index|]
operator|!=
name|col2
index|[
name|b
index|]
condition|)
block|{
name|equal
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
block|}
return|return
name|equal
return|;
block|}
end_function

end_unit

