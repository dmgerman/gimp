begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Autocrop plug-in version 1.00  * by Tim Newsome<drz@froody.bloke.com>  * thanks to quartic for finding a nasty bug for me  */
end_comment

begin_comment
comment|/* 1999/04/09 -- Sven Neumann<sven@gimp.org>  * Fixed bad crash that occured when running on an entirely blank image.  * Cleaned up the code a bit, while I was at it.   */
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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
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
name|gint
name|colors_equal
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
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
name|doit
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint32
name|image_id
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
literal|"plug_in_autocrop"
argument_list|,
literal|"Automagically crops a picture."
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
literal|"<Image>/Image/Transforms/Autocrop"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
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
DECL|function|run (gchar * name,gint n_params,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|n_params
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
name|GimpRunModeType
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
name|INIT_I18N
argument_list|()
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
if|if
condition|(
name|n_params
operator|!=
literal|3
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
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
name|id
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
operator|||
name|gimp_drawable_is_indexed
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
literal|"Cropping..."
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
name|doit
argument_list|(
name|drawable
argument_list|,
name|image_id
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|doit (GimpDrawable * drawable,gint32 image_id)
name|doit
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint32
name|image_id
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
name|x
decl_stmt|,
name|y
decl_stmt|,
name|abort
decl_stmt|;
name|gint32
name|nx
decl_stmt|,
name|ny
decl_stmt|,
name|nw
decl_stmt|,
name|nh
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
name|nx
operator|=
literal|0
expr_stmt|;
name|ny
operator|=
literal|0
expr_stmt|;
name|nw
operator|=
name|width
expr_stmt|;
name|nh
operator|=
name|height
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
literal|0
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
operator|&&
operator|!
name|abort
condition|;
name|y
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
name|y
argument_list|,
name|width
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
operator|&&
operator|!
name|abort
condition|;
name|x
operator|++
control|)
block|{
name|abort
operator|=
operator|!
name|colors_equal
argument_list|(
name|color
argument_list|,
name|buffer
operator|+
name|x
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|y
operator|==
name|height
operator|&&
operator|!
name|abort
condition|)
block|{
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
name|y
operator|--
expr_stmt|;
name|ny
operator|=
name|y
expr_stmt|;
name|nh
operator|=
name|height
operator|-
name|y
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|0.25
argument_list|)
expr_stmt|;
comment|/* Check how many of the bottom lines are uniform. */
name|abort
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|y
operator|=
name|height
operator|-
literal|1
init|;
name|y
operator|>=
literal|0
operator|&&
operator|!
name|abort
condition|;
name|y
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
name|y
argument_list|,
name|width
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
operator|&&
operator|!
name|abort
condition|;
name|x
operator|++
control|)
block|{
name|abort
operator|=
operator|!
name|colors_equal
argument_list|(
name|color
argument_list|,
name|buffer
operator|+
name|x
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
block|}
name|nh
operator|=
name|y
operator|-
name|ny
operator|+
literal|2
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|0.5
argument_list|)
expr_stmt|;
comment|/* Check how many of the left lines are uniform. */
name|abort
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
operator|&&
operator|!
name|abort
condition|;
name|x
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
name|x
argument_list|,
name|ny
argument_list|,
name|nh
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|nh
operator|&&
operator|!
name|abort
condition|;
name|y
operator|++
control|)
block|{
name|abort
operator|=
operator|!
name|colors_equal
argument_list|(
name|color
argument_list|,
name|buffer
operator|+
name|y
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
block|}
name|x
operator|--
expr_stmt|;
name|nx
operator|=
name|x
expr_stmt|;
name|nw
operator|=
name|width
operator|-
name|x
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|0.75
argument_list|)
expr_stmt|;
comment|/* Check how many of the right lines are uniform. */
name|abort
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|x
operator|=
name|width
operator|-
literal|1
init|;
name|x
operator|>=
literal|0
operator|&&
operator|!
name|abort
condition|;
name|x
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
name|x
argument_list|,
name|ny
argument_list|,
name|nh
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|nh
operator|&&
operator|!
name|abort
condition|;
name|y
operator|++
control|)
block|{
name|abort
operator|=
operator|!
name|colors_equal
argument_list|(
name|color
argument_list|,
name|buffer
operator|+
name|y
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
block|}
name|nw
operator|=
name|x
operator|-
name|nx
operator|+
literal|2
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
name|nw
operator|!=
name|width
operator|||
name|nh
operator|!=
name|height
condition|)
name|gimp_crop
argument_list|(
name|image_id
argument_list|,
name|nw
argument_list|,
name|nh
argument_list|,
name|nx
argument_list|,
name|ny
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
name|gint
DECL|function|colors_equal (guchar * col1,guchar * col2,gint bytes)
name|colors_equal
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
name|gint
name|equal
init|=
literal|1
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
literal|1
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
literal|0
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

